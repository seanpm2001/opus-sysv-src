h48301
s 00028/00000/00000
d D 1.1 90/03/06 12:31:11 root 1 0
c date and time created 90/03/06 12:31:11 by root
e
u
U
t
T
I 1
#ifndef _FS_S5DIR_H_
#define _FS_S5DIR_H_


/*	Copyright (c) 1989 Opus Systems	*/
/*	      All Rights Reserved 	*/

/*	Copyright (c) 1984 AT&T	*/
/*	  All Rights Reserved  	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/

#ifdef __88000_OCS_DEFINED
#include "Not OCS compliant."
#endif

#ifndef	DIRSIZ
#define	DIRSIZ	14
#endif
struct	direct
{
	ushort	d_ino;
	char	d_name[DIRSIZ];
};

#endif	/* ! _FS_S5DIR_H_ */
E 1
