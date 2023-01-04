;	@(#)__setjmp.s	6.1	
;
;	M88000 __setjmp, longjmp(3) Routines
;
;	(C) Copyright 1987 by Motorola Inc.
;
;	Written by: Bob Greiner
;
; __setjmp, longjmp - multiple function call level jumps
;
; Input (longjmp):	env, a pointer to the jump buffer
;			val, the value to be returned by setjmp
;
; Output (longjmp):	NEVER RETURNS
;
; Input (setjmp):	env, a pointer to the jump buffer
;
; Output (setjmp):	0 when setjmp first returns
;			val ? val : 1 when longjmp causes return
;
_m4_define_(`env_return', `arg0,0')_m4_dnl_
_m4_define_(`env_sp', `arg0,4')_m4_dnl_
_m4_define_(`env_14', `arg0,8')_m4_dnl_
_m4_define_(`env_15', `arg0,12')_m4_dnl_
_m4_define_(`env_16', `arg0,16')_m4_dnl_
_m4_define_(`env_17', `arg0,20')_m4_dnl_
_m4_define_(`env_18', `arg0,24')_m4_dnl_
_m4_define_(`env_19', `arg0,28')_m4_dnl_
_m4_define_(`env_20', `arg0,32')_m4_dnl_
_m4_define_(`env_21', `arg0,36')_m4_dnl_
_m4_define_(`env_22', `arg0,40')_m4_dnl_
_m4_define_(`env_23', `arg0,44')_m4_dnl_
_m4_define_(`env_24', `arg0,48')_m4_dnl_
_m4_define_(`env_25', `arg0,52')_m4_dnl_
_m4_define_(`env_26', `arg0,56')_m4_dnl_
_m4_define_(`env_27', `arg0,60')_m4_dnl_
_m4_define_(`env_28', `arg0,64')_m4_dnl_
_m4_define_(`env_29', `arg0,68')_m4_dnl_
_m4_define_(`env_30', `arg0,72')_m4_dnl_
_m4_define_(`flag', `arg0,76')_m4_dnl_
_m4_define_(`sigmask', `arg0,80')_m4_dnl_
;
	file	"__setjmp.s"
	text
	global	_setjmp
	global	_longjmp
	global	__sigsetjmp
	global	__siglongjmp
;
_setjmp:
	or	r3,r0,r0
__sigsetjmp:
	st	return,env_return	; save r1, r31 into env
	st	sp,env_sp
	st	r14,env_14
	st	r15,env_15
	st	r16,env_16
	st	r17,env_17
	st	r18,env_18
	st	r19,env_19
	st	r20,env_20
	st	r21,env_21
	st	r22,env_22
	st	r23,env_23
	st	r24,env_24
	st	r25,env_25
	st	r26,env_26
	st	r27,env_27
	st	r28,env_28
	st	r29,env_29
	st	r30,env_30
	st	r3,flag
	bcnd	eq0,r3,@L1
	subu	r31,r31,40		; homing area + space for saving r1
	st	r1,r31,32		; save r1
	addu	r4,sigmask
	or	r2,r0,r0
	or	r3,r0,r0
	bsr	__sigprocmask
	ld	r1,r31,32		; restore r1
	addu	r31,r31,40		; restore r31
@L1:
	or	arg0,zero,0		; return 0
	jmp	return

__siglongjmp:
_longjmp:
	ld	r4,flag
	bcnd	eq0,r4,@L2
	or	r14,r0,r2
	or	r15,r0,r3
	addu	r4,r0,r0
	addu	r3,sigmask
	addu	r2,r0,2			; SIG_SETMASK
	bsr	__sigprocmask
	or	r2,r0,r14
	or	r3,r0,r15
@L2:
	ld	return,env_return	; restore r1, r31 from env
	ld	sp,env_sp
	ld	r14,env_14
	ld	r15,env_15
	ld	r16,env_16
	ld	r17,env_17
	ld	r18,env_18
	ld	r19,env_19
	ld	r20,env_20
	ld	r21,env_21
	ld	r22,env_22
	ld	r23,env_23
	ld	r24,env_24
	ld	r25,env_25
	ld	r26,env_26
	ld	r27,env_27
	ld	r28,env_28
	ld	r29,env_29
	ld	r30,env_30
	or	result,zero,r3		; val
	bcnd	ne0,arg0,L0
	or	result,zero,1		; force return value non-zero
L0:
	jmp	return			; return val (but as if from setjmp)
