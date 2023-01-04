h01900
s 00077/00000/00000
d D 1.1 90/03/06 12:29:53 root 1 0
c date and time created 90/03/06 12:29:53 by root
e
u
U
t
T
I 1
#ifndef _SYS_LOG_H_
#define _SYS_LOG_H_


/*	Copyright (c) 1989 Opus Systems	*/
/*	      All Rights Reserved	*/

/*	Copyright (c) 1984 AT&T	*/
/*	  All Rights Reserved  	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/

#ifdef __88000_OCS_DEFINED
#include "Not OCS compliant."
#endif

/*
 * Header file for the Streams Log Driver
 */

struct log {
	unsigned log_state;
	queue_t *log_rdq;
	int 	log_bcnt;
};

/*
 * Driver state values.
 */
#define LOGOPEN 	01

/* 
 * Module information structure fields
 */
#define LOG_MID		44
#define LOG_NAME	"LOG"
#define LOG_MINPS	0
#define LOG_MAXPS	512
#define LOG_HIWAT	512
#define LOG_LOWAT	256

extern strlog();

extern struct log log_log[];		/* sad device state table */
extern int log_cnt;			/* number of configured minor devices */
extern int log_bsz;			/* size of internal buffer of log messages */

/*
 * STRLOG(mid,sid,level,flags,fmt,args) should be used for those trace
 * calls that are only to be made during debugging.
 */
#ifdef DEBUG
#define STRLOG	strlog
#else
#define STRLOG
#endif


/*
 * Utility macros for strlog.
 */

/*
 * logadjust - move a character pointer up to the next int boundary
 * after its current value.  Assumes sizeof(int) is 2**n bytes for some integer n. 
 */
#define logadjust(wp) (char *)(((unsigned)wp + sizeof(int)) & ~(sizeof(int)-1))

/*
 * logstrcpy(dp, sp) copies string sp to dp.
 */

#define logstrcpy(dp, sp)  for (; *dp = *sp; dp++, sp++)

#endif	/* ! _SYS_LOG_H_ */
E 1
