	
		cpu		8008new
		org 	0

lowScope = 14
highScope = 15


Start:	xra 	a
		out 	lowScope
		out		HighScope

		mvi 	c,4
		mvi 	h,Font/256
		mvi 	l,Font&255
LineLoop:

		mvi 	d,16
CharLoop:
		mov 	a,m
		out 	LowScope
		inr 	l
		mov 	a,m
		out 	HighScope
		inr 	l
		dcr 	d
		jnz 	CharLoop
		mvi 	a,55h
		out 	lowScope
		mvi 	a,0D5h
		out 	HighScope
		dcr 	c
		jnz 	LineLoop
Wait:	jmp 	Wait

Font:	include __starburst.inc