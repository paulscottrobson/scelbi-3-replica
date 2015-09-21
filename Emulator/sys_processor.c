// *******************************************************************************************************************************
// *******************************************************************************************************************************
//
//		Name:		sys_processor.c
//		Purpose:	Processor Emulation.
//		Created:	21st September 2015
//		Author:		Paul Robson (paul@robsons.org.uk)
//
// *******************************************************************************************************************************
// *******************************************************************************************************************************

#include "sys_processor.h"

// *******************************************************************************************************************************
//															Timing
// *******************************************************************************************************************************
	
#define CYCLES_PER_SECOND	(500000/2)												// Clock at 500Khz, 2 Clocks per T-State	
#define FRAME_RATE			(60)													// Frame rate
#define CYCLES_PER_FRAME	(CYCLES_PER_SECOND/FRAME_RATE)							// T-States per second.

// *******************************************************************************************************************************
//													   Processor status
// *******************************************************************************************************************************

static BYTE8 	A,B,C,D,E,H,L;														// Registers
static BYTE8 	PSZValue,Carry,HaltFlag;											// Flags
#define PCTR 	PC[PCIndex]															// Program counter

static BYTE8  	MB,interruptRequested,PCIndex,cpuPhase,								// Internal states & registers
									interruptMode,singleStepMode,status,opcode;
static WORD16 	PC[8],MA,Cycles; 	

static WORD16 	temp16;																// Work register

// *******************************************************************************************************************************
//														Main Memory
// *******************************************************************************************************************************

static BYTE8 ramMemory[RAMSIZE];													// System RAM.							

// *******************************************************************************************************************************
//											    Memory read and write macros.
// *******************************************************************************************************************************

#define READ() 		MB = ((MA < RAMSIZE) ? ramMemory[MA] : DEFAULT_BUS_VALUE);
#define WRITE() 	if (MA < RAMSIZE) ramMemory[MA] = MB;

// *******************************************************************************************************************************
//											Other macros that link to functions.
// *******************************************************************************************************************************

#define READPORT() 	{}
#define WRITEPORT()	{}

// *******************************************************************************************************************************
//												Parity Checker (true if even)
// *******************************************************************************************************************************

static BYTE8 _CPUParityEven(BYTE8 n) {
	BYTE8 p = 0;
	while (n != 0) {																// While bits set left
		if ((n & 1) != 0) p ^= 1;													// Toggle if bit set
		n = n >> 1;																	// Next bit
	}
	return (p == 0);																// Return true if even.
}

// *******************************************************************************************************************************
//													  Binary addition
// *******************************************************************************************************************************

static inline BYTE8 _CPUAdd(BYTE8 n) {
	temp16 = A + n + Carry; 														// Calculate result
	Carry = temp16 >> 8;															// Calculate carry
	return temp16 & 0xFF;															// Return result
}

// *******************************************************************************************************************************
//													  Binary subtraction
// *******************************************************************************************************************************

static inline BYTE8 _CPUSubtract(BYTE8 n) {
	temp16 = A - n - Carry; 														// Calculate result
	Carry = temp16 >> 8;															// Calculate carry
	return temp16 & 0xFF;															// Return result.
}

// *******************************************************************************************************************************
//														Reset the CPU
// *******************************************************************************************************************************

void CPUReset(void) {
	A = B= C = D = E = H = L = 0;													// Clear registers
	HaltFlag = Carry = Cycles = PCIndex = PSZValue = cpuPhase = status = 0;			// Clear flags & internals
	interruptRequested = 0;interruptMode = 0;singleStepMode = 0;
	for (BYTE8 n = 0;n < 8;n++) PC[n] = 0;											// Zero stack for clarity.
}

// *******************************************************************************************************************************
//													 Execute a single phase.
// *******************************************************************************************************************************

BYTE8 CPUExecuteSinglePhase(void) {
	// Only return frame out when in phase 0.
	/*
	if (HaltFlag == 0) {															// CPU is running (not halt)
		FETCH();																	// Fetch and execute
		switch(MB) {																// Do the selected opcode and phase.
			//#include "__8008opcodes.h"
		}
	}	
	if (interruptRequested != 0) {													// Interrupt requested
		interruptRequested = 0;														// We no longer have a request.
		HaltFlag = 0;																// We are no longer halted.
		PUSH();																		// Do a RST 0.
		PCTR = 0;
	}	 
	if (HaltFlag == 0 && Cycles < CYCLES_PER_FRAME) return 0;						// Frame in progress, return 0.
	if (HaltFlag != 0) Cycles = 0;													// Fix up for HALT.
	Cycles -= CYCLES_PER_FRAME;														// Adjust cycle counter
	HWIEndFrame();																	// Hardware stuff.
	*/
	return FRAME_RATE;																// Return the frame rate for sync speed.
}

// *******************************************************************************************************************************
//											Execute a single instruction
// *******************************************************************************************************************************

BYTE8 CPUExecuteInstruction(void) {
	BYTE8 frameRate;
	do {
		frameRate = CPUExecuteSinglePhase();										// Execute a phase
	} while (cpuPhase != 0);														// Until back at phase zero.
	return frameRate;																// When we can exit.
}

#ifdef INCLUDE_DEBUGGING_SUPPORT

// *******************************************************************************************************************************
//										 Get the step over breakpoint value
// *******************************************************************************************************************************

WORD16 CPUGetStepOverBreakpoint(void) {
	BYTE8 opcode = CPURead(PCTR);													// Read opcode.
	if ((opcode & 0xC7) == 0x07) return ((PCTR+1) & 0x3FFF);						// RST xx
	if ((opcode & 0xC3) == 0x42) return ((PCTR+3) & 0x3FFF);						// CALL xxxx (various calls)
	return 0xFFFF;
}

// *******************************************************************************************************************************
//										Run continuously till breakpoints / Halt.
// *******************************************************************************************************************************

BYTE8 CPUExecute(WORD16 break1,WORD16 break2) {
	BYTE8 rate = 0;
	while(1) {
		rate = CPUExecuteInstruction();												// Execute one instruction phase.
		if (rate != 0) {															// If end of frame, return rate.
			return rate;													
		}
		if (PCTR == break1 || PCTR == break2) return 0;
	} 																				// Until hit a breakpoint or HLT.
}

// *******************************************************************************************************************************
//												Load a binary file into RAM
// *******************************************************************************************************************************

#include <stdio.h>

void CPULoadBinary(char *fileName) {
	FILE *f = fopen(fileName,"rb");
	fread(ramMemory,1,RAMSIZE,f);
	fclose(f);
}

// *******************************************************************************************************************************
//												Gets a pointer to RAM memory
// *******************************************************************************************************************************
	
BYTE8 CPURead(WORD16 address) {
	WORD16 _MA = MA;BYTE8 _MB = MB;BYTE8 result;
	MA = address;READ();result = MB;
	MA = _MA;MB = _MB;
	return result;
}

// *******************************************************************************************************************************
//											Retrieve a snapshot of the processor
// *******************************************************************************************************************************

static CPUSTATUS s;																	// Status area

CPUSTATUS *CPUGetStatus(void) {
	int i;
	s.a = A;s.b = B;s.c = C;s.d = D;s.e = E;s.h = H;s.l = L;						// 8 bit registers
	s.zFlag = (PSZValue == 0);s.cFlag = (Carry != 0);s.hFlag = (HaltFlag != 0);		// Flags
	s.pFlag = _CPUParityEven(PSZValue);s.sFlag = ((PSZValue & 0x80) != 0);
	s.cycles = Cycles;																// Number of cycles.
	for (i = 0;i < 8;i++) s.stack[i] = 0;											// Clear stack.
	s.pc = PCTR;																	// Save PC.
	i = PCIndex-1;s.stackDepth = 0;													// Copy stack.
	while (i >= 0) s.stack[s.stackDepth++] = PC[i--];
	s.hl = (s.h << 8) | s.l;s.m = CPURead(s.hl & 0x3FFF);							// Helpers
	s.status = status;s.interruptMode = interruptMode;								// Internal statuses.
	s.singleStepMode = singleStepMode;s.cpuPhase = cpuPhase;
	return &s;
}
#endif
