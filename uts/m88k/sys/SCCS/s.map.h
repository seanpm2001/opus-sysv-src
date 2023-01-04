h31708
s 00048/00000/00000
d D 1.1 90/03/06 12:29:56 root 1 0
c date and time created 90/03/06 12:29:56 by root
e
u
U
t
T
I 1
#ifndef _SYS_MAP_H_
#define _SYS_MAP_H_


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
 *		struct map	X[]	.m_size		.m_addr
 *				---	------------	-----------
 *				[0]	mapsize(X)	mapwant(X)
 *					# X[] unused	sleep value
 *
 *		  mapstart(X)->	[1]	# units		unit number
 *				 :	    :		  :
 *				[ ]	    0
 */

struct map
{
	unsigned long m_size;	/* number of units available */
	unsigned long m_addr;	/* address of first available unit */
};

extern struct map sptmap[];	/* Map for system virtual space.   */
extern struct map dmamap[];	/* Map for opmon DMA space */

#define	mapstart(X)	&X[1]		/* start of map array */
#define	mapwant(X)	X[0].m_addr
#define	mapsize(X)	X[0].m_size	/* number of empty slots \
					   remaining in map array */
#define	mapdata(X) {(X)-2, 0} , {0, 0}
#define	mapinit(X, Y)	X[0].m_size = (Y)-2

uint malloc();

#endif	/* ! _SYS_MAP_H_ */
E 1
