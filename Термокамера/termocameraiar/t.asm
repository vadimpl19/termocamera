	NAME main
	ORG 0x00 	; reset vector address
	RJMP main

RSEG CODE:CODE
main	ldi r16,0
	out 0x05,r16
	rjmp main
	end main