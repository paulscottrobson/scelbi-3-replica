	
		cpu		8008new
		org 	0

		mov 	a,a
		mvi 	h,34h
		mvi 	l,67h
Start:	call	RepaintScreen
		mvi 	h,ScreenMap/256
		mvi 	l,(ScreenMap+7) & 255
Increment:
		mov 	a,m
		adi 	1
		mov 	m,a
		cpi 	'9'+1
		jnz 	Start
		mvi 	m,'0'
		dcr 	l
		jmp 	Increment


; ********************************************************************************************************************************
; ********************************************************************************************************************************
;
;		This 256 byte block contains the screen refresh code, the memory for the screen and the code to repaint it to the
;		Scope display.
;
; ********************************************************************************************************************************
; ********************************************************************************************************************************

		align 	256

; ********************************************************************************************************************************
;
;							This routine is ROMmable but the ScreenMap and _RSRestore must be in RAM.
;
; ********************************************************************************************************************************

ScreenMap: 														; this can move, but must be on a 16 byte boundary.
		db 		"00000000 COUNTER" 								; if _RSLineCount is increased beyond 4, this driver will not fit
		db 		"HELLO WORLD     "								; in 1/4 k of RAM.
		db 		"***  LINE 3  ***"
		db 		"END OF PAGE     "

_RSRestore:														; HL is saved here.
		dw 		0

_RSLineCount = 4 												; number of display lines, note if more than 4 the ScreenMap must move.
_RSLowScopePort = 0Eh 											; output port low
_RSHighScopePort = 0Fh											; output port high and start
_RSNewLineCommand = 55h 										; code for new line.

; ********************************************************************************************************************************
;
;												Repaint the screen. Breaks AE.
;
; ********************************************************************************************************************************

RepaintScreen:
		mov 	e,l 											; save HL to AE
		mov		a,h
		mvi 	h,_RSRestore/256 								; point HL to the HL store.
		mvi 	l,_RSRestore & 255 	
		mov 	m,e 											; save L (in E) then H (in A) there
		inr 	l
		mov 	m,a
		xra 	a 												; write $00 to the scope, which sets B7, homes the cursor
		out 	_RSLowScopePort 	
		out		_RSHighScopePort

		mvi 	e,ScreenMap&255 								; this is where we are drawing from.
_RSRenderLoop:
		mvi 	h,ScreenMap/256 								; point HL to screen map
		mov 	l,e 
		mov 	a,m 											; read character
		ani 	03Fh											; 6 bit ASCII
		add 	a 												; double
		adi 	_RSFont & 255 									; point HL to font data
		mov 	l,a
		mvi 	h,_RSFont/256
		mov 	a,m 											; output data.
		out 	_RSLowScopePort
		inr 	l
		mov 	a,m
		out 	_RSHighScopePort
		inr 	e 												; next address
		mov 	a,e 											; reached EOL e.g. xxxx0000
		ani 	0Fh
		jnz 	_RSRenderLoop
		mvi 	a,_RSNewLineCommand								; output $5555 with bit 15 set, for a new line.
		out 	_RSLowScopePort
		mvi 	a,_RSNewLineCommand!80h
		out 	_RSHighScopePort
		mov 	a,e
		xri 	(ScreenMap&255)+(_RSLineCount*16) 				; reached the end of the map.
		jnz 	_RSRenderLoop

		mvi 	h,_RSRestore/256 								; point HL to the HL store.
		mvi 	l,_RSRestore & 255 	
		mov 	a,m
		inr 	l
		mov 	h,m
		mov 	l,a
		ret

		align 	128
; ********************************************************************************************************************************
;
;										64 x 2 byte font entries, one for each character
;
; ********************************************************************************************************************************

_RSFont:	
		include __starburst.inc