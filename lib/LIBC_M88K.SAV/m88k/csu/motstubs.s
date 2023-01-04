;
;		MOTSTUBS.S
;
; This file contains the stubs for the second Silicon test compiler.
; These are used to effect the instructions which cannot be executed
; on the chip. 
;
;   These are
;
; 1) floating point instructions. This compiler does NOT compensate for
;    the lack of these instructions.
; 2) Integer multiply is normally done by the chip in
;    the floating point unit. The above compiler will call functions
;    in this file for these operations.
;
;  The interface for these functions is as below.
;
;	Input	r24,r25
;
;	Output	r24
;	parent function r1 value is saved in r23 DO NOT USE r23!
;	Temporaries for this funtion 	r14 through r22
;	Function is called by bsr so return via jmp r1
;	These functions are intended to be leaf procedures, not to
;	need a stack and not to have to save r1.	
;
;		This file should be appended to the startup file
;		crt0.s. (As of 12/21/87, the compiler will not
;		compensate for the mak,clr,or combination used in
;		bitfield assignments. Opcodes illegal to the assembler
;		"help" will be output instead. This should be watched
;		for when compiling, and will be fixed if a requirement
;		exists.) FIXED AT 01/15/88.
;		The user is relied on not to compile floating
;		point code. 
;		Exception handling during
;		st.d instructions will not be a problem if no floating
;		point is used. Note that all this applies only to code
;		generated by the compiler. Rel 0.5 in particular
;		includes several hand optimized assembly functions
;		which will cause problems. These should be reverted to
;		C compiled versions. 
;
;
        text
	global		$mulmot
$mulmot:
;	or		r22,r0,r24	; done in bsr delay slot
	or		r21,r25,r22	; test for zero
	or		r20,r0,1
	bcnd.n		ne0,r21,motmul1
	or		r24,r0,r0
	jmp.n		r1
	or		r1,r0,r23
motmul1:
	bb0		0,r25,motmul2
; some think the next add should be an addu 
; they were right   CW/SAJ  1/27/88
	addu		r24,r24,r22
motmul2:
	extu		r25,r25,0<1>	; shift right by 1
	bcnd		eq0,r25,motmul3
	rot		r22,r22,0<31>
	br.n		motmul1
	and.c		r22,r22,r20	; shift left by 1
motmul3:
	jmp.n		r1
	or		r1,r0,r23

	data
