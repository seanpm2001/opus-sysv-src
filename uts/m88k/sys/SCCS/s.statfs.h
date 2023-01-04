h15805
s 00035/00000/00000
d D 1.1 90/03/06 12:30:21 root 1 0
c date and time created 90/03/06 12:30:21 by root
e
u
U
t
T
I 1
#ifndef _SYS_STATFS_H_
#define _SYS_STATFS_H_


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
 * Structure returned by the statfs() system call.
 */

struct	statfs {
	short	f_fstyp;	/* File system type */
	long	f_bsize;	/* Block size */
	long	f_frsize;	/* Fragment size (if supported) */
	long	f_blocks;	/* Total number of blocks on file system */
	long	f_bfree;	/* Total number of free blocks */
	long	f_files;	/* Total number of file nodes (inodes) */
	long	f_ffree;	/* Total number of free file nodes */
	char	f_fname[6];	/* Volume name */
	char	f_fpack[6];	/* Pack name */
};

#endif	/* ! _SYS_STATFS_H_ */
E 1
