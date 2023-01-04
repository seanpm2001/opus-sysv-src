;	M88000 getpeername(2) Routine
;
;
	file	"getpeername.s"
	text
	global	__getpeername
__getpeername:
	or	r8,r0,0x1		; network vendor id
	or	r9,r0,7		       	; network function id
	tb0	0,r0,449		; trap to Unix
	br	cerror			; return error to caller
	jmp	r1			; return to caller
