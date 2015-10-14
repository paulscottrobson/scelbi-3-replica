	
		cpu		8008new
		org 	0
		mvi 	b,42h
		mvi 	c,55h
		mvi 	h,37h
		mvi 	l,ScreenMap & 255
Start:	call	RepaintScreen

Wait:	in 		4
		ora 	a
		jp 		Wait
		out 	10
		ani	 	7Fh
		cpi 	60h
		jc 		NotLC
		sui 	20h
NotLC:
		mvi 	h,ScreenMap/256
		mov 	m,a
		inr 	l
		mov 	a,l
		cpi 	80
		jnz 	Start
		mvi 	l,0
		jmp 	Start

; ********************************************************************************************************************************
;
;											RAM Storage : A 20 x 4 Display Area.
;
; ********************************************************************************************************************************

ScreenMap: 														; this can move
		db 		"00000000 COUNTERABCD" 						
		db 		"HELLO WORLD     EFGH"						
		db 		"***  LINE 3  ***IJKL"
		db 		"END OF PAGE     MNOP"

_RSStorage:
		db 		0,0,0,0 										; storage for A,C,L,H

_RSLineCount = 4 												; number of display lines, note if more than 4 the ScreenMap must move.
_RSLowScopePort = 08h 											; output port low
_RSHighScopePort = 09h											; output port high and start
_RSNewLineCommand = 55h 										; code for new line.

; ********************************************************************************************************************************
;
;										64 x 2 byte font entries, one for each character
;
; ********************************************************************************************************************************

		align 	2
_RSFont:	
		include __starburst.inc

; ********************************************************************************************************************************
;
;												Repaint the screen.
;
; ********************************************************************************************************************************

RepaintScreen:
		mov 	e,l 											; save HL in DE
		mov 	d,h
		mvi 	h,_RSStorage/256 								; HL points to storage
		mvi 	l,_RSStorage&255
		mov 	m,a 											; save A and C
		inr 	l
		mov 	m,c
		inr 	l
		mov 	m,e 											; save old HL
		inr 	l
		mov 	m,d
		xra 	a 												; write $00 to the scope, which sets B7, homes the cursor
		out 	_RSLowScopePort 	
		out		_RSHighScopePort

		mvi 	e,ScreenMap&255 								; this is where we are drawing from.
		mvi 	d,ScreenMap/256 								; point HL to screen map

_RSLineLoop:
		mvi 	c,20 											; print 20 characters a line.
_RSRenderLoop:
		mov 	l,e 											; copy DE to HL.
		mov 	h,d 	
		mov 	a,m 											; read character from HL.
		ani 	03Fh											; 6 bit ASCII
		add 	a 												; double as 2 bytes per font entry.

		adi 	_RSFont & 255 									; point HL to font data
		mov 	l,a
		mvi 	a,_RSFont/256
		aci 	0
		mov 	h,a

		mov 	a,m 											; output data.
		out 	_RSLowScopePort
		inr 	l
		mov 	a,m
		out 	_RSHighScopePort

		inr 	e 												; bump DE
		jnz 	_RSNoCarry
		inr 	d
_RSNoCarry:
		dcr 	c 												; done a complete line ?
		jnz 	_RSRenderLoop 									; no, loop back and do another character.

		mvi 	a,_RSNewLineCommand								; output $5555 with bit 15 set, for a new line.
		out 	_RSLowScopePort
		mvi 	a,_RSNewLineCommand!80h
		out 	_RSHighScopePort

		mov 	a,e
		xri 	(ScreenMap+_RSLineCount*20) & 255 				; reached the end of the map.
		jnz 	_RSLineLoop

		mvi 	h,_RSStorage/256 								; HL points to storage
		mvi 	l,_RSStorage&255
		mov 	a,m 											; read A 
		inr 	l
		mov 	c,m 											; read C
		inr 	l
		mov 	e,m 											; read L to E
		inr 	l
		mov 	h,m 											; read H
		mov 	l,e 											; fixup L.
		ret
