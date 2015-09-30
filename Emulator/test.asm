	
		cpu		8008new
		org 	0

lowScope = 14
highScope = 15


Start:	xra 	a
		out 	lowScope
		out		HighScope

		mvi 	c,4
LineLoop:
		mvi 	h,0
		mvi 	l,1
		mvi 	d,16
CharLoop:
		mov 	a,l
		out 	LowScope
		mov 	a,h
		ori 	080h
		out 	HighScope
		mov 	a,l
		add 	a
		mov 	l,a
		mov 	a,h
		adc 	a
		mov 	h,a
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
