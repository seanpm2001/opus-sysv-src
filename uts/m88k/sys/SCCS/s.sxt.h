h57815
s 00094/00000/00000
d D 1.1 90/03/06 12:30:30 root 1 0
c date and time created 90/03/06 12:30:30 by root
e
u
U
t
T
I 1
#ifndef _SYS_SXT_H_
#define _SYS_SXT_H_


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
 **	Multiplexed channels driver header
 */

#define	SXTRACE		1		/* 1 to include tracing */

#define	MAXLINKS	32
#define	CHAN(dev)	(dev&CHANMASK)
#define	LINK(dev)	((dev>>CHANBITS)&(0xff>>CHANBITS))
 

#if	(MAXPCHAN*MAXLINKS) > 256
	ERROR -- product cannot be greater than minor(dev)
#endif



struct Channel
{
	struct tty	tty;		/* Virtual tty for this channel */
};

typedef struct Channel *Ch_p;

struct Link
{
	struct tty *	line;		/* Real tty for this link */
	char		controllingtty;	/* the current top dog */
	char		old;		/* Old line discipline for line */
	char		nchans;		/* Number of channels allowed */
	unsigned char	chanmask;	/* Allowable channel bits */
	char		open;		/* Channel open bits */
	char		xopen;		/* Exclusive open bits */
	char		wpending;	/* pending writes/channel */
	char		iblocked;	/* channels blocked for input */
	char		oblocked;	/* channels blocked for output*/
	short		lwchan;		/* Last channel written bit */
	char		wrcnt;		/* Number of writes on last channel written */
	dev_t		dev;		/* major and minor device # */
	struct Channel	chans[1];	/* Array of channels for this link */
};

typedef	struct Link *	Link_p;

/*
**	Ioctl args
*/

#define	SXTIOCLINK	('b'<<8)
#define	SXTIOCTRACE	(SXTIOCLINK|1)
#define	SXTIOCNOTRACE	(SXTIOCLINK|2)
#define SXTIOCSWTCH	(SXTIOCLINK|3)
#define	SXTIOCWF	(SXTIOCLINK|4)
#define SXTIOCBLK	(SXTIOCLINK|5)
#define SXTIOCUBLK	(SXTIOCLINK|6)
#define SXTIOCSTAT	(SXTIOCLINK|7)



/* the following structure is used for the SXTIOCSTAT ioctl call */
struct sxtblock
{
	char	input;		/* channels blocked on input  */
	char	output;		/* channels blocked on output */
};



#define	t_link		t_dstat		/* Use dstat in real tty for linknumber */

#define	MAXPCHAN	8			/* Maximum channel number */
#define	CHANBITS	3			/* Bits for channel number */
#define	CHANMASK	07			/* 2**CHANBITS - 1 */
#define	SXTHOG		2			/* Channel consecutive write limit */

#endif	/* ! _SYS_SXT_H_ */
E 1
