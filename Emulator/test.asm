	
		cpu		8008new
		org 	0

vdu 	= 0eh

		mvi 	a,377o

		out 	vdu
		xra 	a
		out 	vdu
		mov 	b,a
loop
		mov 	a,b
		ori 	200o
		out 	vdu
		xra 	a
		out 	vdu
		mov 	a,b
		ori 	200o
		out 	vdu
		xra 	a
		out 	vdu
skip:
		inr 	b
		jp 		loop
		hlt
