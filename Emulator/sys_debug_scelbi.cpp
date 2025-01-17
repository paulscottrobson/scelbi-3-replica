// *******************************************************************************************************************************
// *******************************************************************************************************************************
//
//		Name:		sys_debug_scelbi.c
//		Purpose:	Debugger Code (System Dependent)
//		Created:	21st September 2015
//		Author:		Paul Robson (paul@robsons.org.uk)
//
// *******************************************************************************************************************************
// *******************************************************************************************************************************

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gfx.h"
#include "sys_processor.h"
#include "sys_debug_system.h"
#include "debugger.h"
#include "drivers.h"

#include "__8008mnemonics.h"														// 8008 new style mnemonics

#define DBGC_ADDRESS 	(0x0F0)														// Colour scheme.
#define DBGC_DATA 		(0x0FF)														// (Background is in main.c)
#define DBGC_HIGHLIGHT 	(0xFF0)

static int xDisplay,yDisplay;														// Display position.
static BYTE8 displayMemory[20*4];													// Video Memory
static WORD16 scopeMemory[20*4];													// Scope memory.
static BYTE8 isScopeEnabled; 														// Non zero if scope display.

static void _DBGXDrawStarburst(SDL_Rect *rc,WORD16 pattern);
static void _DBGXDiagonal(int x1,int y1,int x2,int y2,int w);

// *******************************************************************************************************************************
//												Reset the 8008
// *******************************************************************************************************************************

void DBGXReset(void) {
	CPUReset();
	isScopeEnabled = 0;
}

// *******************************************************************************************************************************
//											Write to display memory
// *******************************************************************************************************************************

void DBGXWriteDisplay(BYTE8 x,BYTE8 y,BYTE8 ch) {
	if (x < 20) xDisplay = x;
	if (y < 4) yDisplay = y;
	displayMemory[xDisplay+yDisplay*20] = ch;
	if (++xDisplay == 20) {
		xDisplay = 0;yDisplay = (yDisplay + 1) % 4;
	}
}

// *******************************************************************************************************************************
//										Write to scope display memory
// *******************************************************************************************************************************

void DBGXWriteScopeCharacter(BYTE8 x,BYTE8 y,WORD16 latches) {
	isScopeEnabled = 1;
	scopeMemory[x+y*20] = latches;
}

// *******************************************************************************************************************************
//											Switched back to LED display
// *******************************************************************************************************************************

void DBGXSetLEDDisplay(void) {
	isScopeEnabled = 0;
}

// *******************************************************************************************************************************
//										  This renders the debug screen
// *******************************************************************************************************************************

//	s.status = status;s.interruptMode = interruptMode;								// Internal statuses.
//	s.singleStepMode = singleStepMode;s.cpuPhase = cpuPhase;

void DBGXRender(int *address,int showDisplay) {
	int n;
	char buffer[32];
	GFXSetCharacterSize(32,25);

	CPUSTATUS *s = CPUGetStatus();													// Get the CPU Status

	const char *labels[] = { "A","B","C","D","E","H","L","M","C","Z","S","P","H","HL","BP","CY",NULL };
	n = 0;
	while (labels[n] != NULL) {
		GFXString(GRID(15,n),labels[n],GRIDSIZE,DBGC_ADDRESS,-1);
		n++;
	}
	const char *labels2[] = { "ST","IM","SS","PH","AD","DA","TS","","PC","SK",NULL };
	n = 0;
	while (labels2[n] != NULL) {
		GFXString(GRID(25,n),labels2[n],GRIDSIZE,DBGC_ADDRESS,-1);
		n++;
	}

	n = address[1];																	// Dump memory.
	for (int row = 17;row < 25;row++) {
		GFXNumber(GRID(1,row),n & 0x3FFF,16,4,GRIDSIZE,DBGC_ADDRESS,-1);			// Head of line
		GFXCharacter(GRID(6,row),':',GRIDSIZE,DBGC_HIGHLIGHT,-1);
		for (int col = 0;col < 8;col++) {											// Data on line
			GFXNumber(GRID(8+col*3,row),CPURead(n & 0x3FFF),16,2,GRIDSIZE,DBGC_DATA,-1);
			n++;
		}
	}
																					// Output text labels.																					// Macros to simplify dump drawing.
	#define DD(value,width)	GFXNumber(GRID(18,n++),value,16,width,GRIDSIZE,DBGC_DATA,-1)
	#define DDC(value) GFXNumber(GRID(18,n++),value,16,1,GRIDSIZE,DBGC_DATA,-1)

	n = 0;																			// Draw the registers
	DD(s->a,2);DD(s->b,2);DD(s->c,2);DD(s->d,2);DD(s->e,2);DD(s->h,2);DD(s->l,2);DD(s->m,2);
	DDC(s->cFlag);DDC(s->zFlag);DDC(s->sFlag);DDC(s->pFlag);DDC(s->hFlag);			// Draw the flags
	DD(s->hl,4);DD(address[3],4);DD(s->cycles,4);									// The rest.

	n = 9;																			// PCTR
	GFXNumber(GRID(28,n),s->pc,16,4,GRIDSIZE,DBGC_DATA,-1);
	n++;
	GFXString(GRID(28,n),"----",GRIDSIZE,DBGC_DATA,-1);								// Translated stack.
	for (int i = 0;i < s->stackDepth;i++) 
		GFXNumber(GRID(28,n++),s->stack[i],16,4,GRIDSIZE,DBGC_DATA,-1);

	GFXNumber(GRID(28,0),s->status >> 1,16,1,GRIDSIZE,DBGC_DATA,-1);
	GFXNumber(GRID(30,0),s->status & 1,16,1,GRIDSIZE,DBGC_DATA,-1);
	GFXNumber(GRID(28,1),s->interruptMode & 1,16,1,GRIDSIZE,DBGC_DATA,-1);
	GFXNumber(GRID(28,2),s->singleStepMode & 1,16,1,GRIDSIZE,DBGC_DATA,-1);
	GFXNumber(GRID(28,3),s->cpuPhase,16,1,GRIDSIZE,DBGC_DATA,-1);
	GFXNumber(GRID(28,4),s->addressLamps,16,4,GRIDSIZE,DBGC_DATA,-1);
	GFXNumber(GRID(28,5),s->dataLamps,16,2,GRIDSIZE,DBGC_DATA,-1);
	GFXNumber(GRID(28,6),DRVReadToggleSwitches(),16,2,GRIDSIZE,DBGC_DATA,-1);
	GFXNumber(GRID(28,7),DRVReadToggleSwitches(),8,3,GRIDSIZE,DBGC_DATA,-1);

	//if (showCPU == 0) return;

	n = address[0]; 																// Dump code.
	for (int row = 0;row < 16;row++) {
		int isPC = (n & 0x3FFF) == (s->pc);											// Check for breakpoint and being at PC
		int isBrk = ((n & 0x3FFF) == address[3]);
		GFXNumber(GRID(0,row),n & 0x3FFF,16,4,GRIDSIZE,isPC ? DBGC_HIGHLIGHT : DBGC_ADDRESS,isBrk ? 0xF00 : -1);
		strcpy(buffer,__mnemonics[CPURead(n & 0x3FFF)]);							// Get mnemonic
		n++;
		if (buffer[strlen(buffer)-2] == '@') {										// Replace @1 @2 with 1/2 byte operands
			switch(buffer[strlen(buffer)-1]) {
				case '1':
					sprintf(buffer+strlen(buffer)-2,"%02x",CPURead((n) & 0x3FFF));
					n++;
					break;
				case '2':
					sprintf(buffer+strlen(buffer)-2,"%02x%02x",(CPURead((n+1) & 0x3FFF)) & 0x3F,CPURead((n) & 0x3FFF));
					n += 2;
					break;
			}
		}
		GFXString(GRID(5,row),buffer,GRIDSIZE,isPC ? DBGC_HIGHLIGHT : DBGC_DATA,-1);
	}

	if (showDisplay == 0) return;

	SDL_Rect rc,rc2;
	rc.w = 20 * 8 * 4;rc.h = 4 * 10 * 4;
	rc.x = (WIN_WIDTH-rc.w)/2;rc.y = WIN_HEIGHT-64-rc.h;
	rc2 = rc;rc.x--;rc.y--;rc.w += 2;rc.h += 2;GFXRectangle(&rc,0xFFF);
	GFXRectangle(&rc2,0x000);
	for (int x = 0;x < 20;x++) {
		for (int y = 0;y < 4;y++) {
			rc.x = rc2.x + x * 8 * 4;
			rc.y = rc2.y + y * 10 * 4;
			rc.w = 8 * 4;
			rc.h = 10 * 4;
			if (isScopeEnabled) {
				_DBGXDrawStarburst(&rc,scopeMemory[x+y*20]);
			} else {
				GFXCharacter(rc.x,rc.y+3,displayMemory[x+y*20],4,0x0FF,-1);
			}
		}
	}
}	

// *******************************************************************************************************************************
//													Draw starburst
// *******************************************************************************************************************************

#define BDRAW(xo,yo,m) { rBar.x = r.x+xo;rBar.y = r.y+yo; if ((pattern & m) != 0) GFXRectangle(&rBar,0xF80); }

static void _DBGXDrawStarburst(SDL_Rect *rc,WORD16 pattern) {
	SDL_Rect r = *rc;
	SDL_Rect rBar;
	int w = rc->h/16;
	if (w < 1) w = 1;
	int b = rc->h/8;
	r.x += b;r.y += b;r.h -= b * 2;r.w -= b*2;

	// Half height vertical
	rBar.w = w;rBar.h = r.h/2;
	BDRAW(0,r.h/2,0x0001);															// A0
	BDRAW(0,0,0x0002);																// A1
	BDRAW(r.w,0,0x0008);															// A3
	BDRAW(r.w,r.h/2,0x0010);														// A4
	// Full height vertical
	rBar.h = r.h;BDRAW(r.w/2,0,0x0400);												// B2
	// Full width horizontal
	rBar.w = r.w;rBar.h = w;
	BDRAW(0,0,0x0004);																// A2
	// Half width horizontal
	rBar.w = r.w/2;
	BDRAW(r.w/2,r.h,0x0020);														// A5
	BDRAW(0,r.h,0x0040);															// A6
	BDRAW(0,r.h/2,0x2000);															// B5
	BDRAW(r.w/2,r.h/2,0x4000);														// B6
	// Full stop
	rBar.h = w;rBar.w = w;
	BDRAW(r.w/2,r.h/2,0x0100);														// B0
	// Diagonals.
	if ((pattern & 0x0080) != 0) _DBGXDiagonal(r.x+r.w/2,r.y+r.h/2,r.x,r.y+r.h,w);	// A7
	if ((pattern & 0x0200) != 0) _DBGXDiagonal(r.x+r.w/2,r.y+r.h/2,r.x+r.w,r.y,w);	// B1
	if ((pattern & 0x0800) != 0) _DBGXDiagonal(r.x+r.w/2,r.y+r.h/2,r.x+r.w,r.y+r.h,w);// B3
	if ((pattern & 0x1000) != 0) _DBGXDiagonal(r.x+r.w/2,r.y+r.h/2,r.x,r.y,w);		// B4
}

// *******************************************************************************************************************************
//													Draw diagonal line
// *******************************************************************************************************************************

static void _DBGXDiagonal(int x1,int y1,int x2,int y2,int w) {
	int s = abs(x1-x2)+abs(y1-y2);
	SDL_Rect rc;rc.w = rc.h = w;
	for (int i = 0;i <= s;i++) {
		rc.x = (x2 - x1) * i / s + x1;
		rc.y = (y2 - y1) * i / s + y1;
		GFXRectangle(&rc,0xF80);
	}
}