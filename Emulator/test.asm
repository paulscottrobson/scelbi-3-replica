	
		cpu		8008new
		org 	0

lowScope = 0Eh 													; output port low
highScope = 0Fh													; output port high and start
newLine = 55h 													; code for new line.

Start:	xra 	a
		out 	lowScope
		out		HighScope

		mvi 	e,ScreenMap&255

CharLoop:
		mvi 	h,ScreenMap/256 								; point HL to screen map
		mov 	l,e 
		mov 	a,m 											; read character
		ani 	03Fh											; 6 bit ASCII
		add 	a 												; double
		adi 	Font & 255 										; point HL to font data
		mov 	l,a
		mvi 	h,Font/256
		mov 	a,m 											; output data.
		out 	LowScope		
		inr 	l
		mov 	a,m
		out 	HighScope
		inr 	e 												; next address
		mov 	a,e 											; reached EOL
		ani 	0Fh
		jnz 	CharLoop
		mvi 	a,newLine										; output $5555 with bit 15 set, for a new line.
		out 	lowScope
		mvi 	a,newLine!80h
		out 	HighScope
		mov 	a,e
		xri 	(ScreenMap&255)+040h 							; reached the end of the map.
		jnz 	CharLoop

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

		align 	16

ScreenMap:
		db 		"00000000 COUNTER"
		db 		"HELLO WORLD     "
		db 		"***  LINE 3  ***"
		db 		"END OF PAGE     "

Font:	include __starburst.inc