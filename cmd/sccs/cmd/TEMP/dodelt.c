/*	Copyright (c) 1984 AT&T	*/
/*	  All Rights Reserved  	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/

#ident	"@(#)sccs:lib/comobj/dodelt.c	6.4"
#include	"../../hdr/defines.h"

# define ONEYEAR 31536000L


long	Timenow;

char	Pgmr[LOGSIZE];	/* for rmdel & chghist (rmchg) */
int	First_esc;
int	First_cmt;
int	CDid_mrs;		/* for chghist to check MRs */

struct idel *
dodelt(pkt,statp,sidp,type)
register struct packet *pkt;
struct stats *statp;
struct sid *sidp;
char type;
{
	extern  char	had[26];
	extern	char	*satoi();
	char *c, *getline();
	struct deltab dt;
	register struct idel *rdp;
	extern char *Sflags[];
	int n, founddel;
	long timediff, time();
	register char *p;

	pkt->p_idel = 0;
	founddel = 0;

	time(&Timenow);
	stats_ab(pkt,statp);
	while (getadel(pkt,&dt) == BDELTAB) {
		if (pkt->p_idel == 0) {
			if (Timenow < dt.d_datetime)
				fprintf(stderr,"Time stamp later than current clock time (co10)\n");
			timediff = Timenow - dt.d_datetime;
			pkt->p_idel = (struct idel *)fmalloc(n=((dt.d_serial+1)*
							sizeof(*pkt->p_idel)));
			zero(pkt->p_idel,n);
			pkt->p_apply = (struct apply *)fmalloc(n=((dt.d_serial+1)*
							sizeof(*pkt->p_apply)));
			zero(pkt->p_apply,n);
			pkt->p_idel->i_pred = dt.d_serial;
		}
		if (dt.d_type == 'D') {
			if (sidp && eqsid(&dt.d_sid,sidp)) {
				copy(dt.d_pgmr,Pgmr);	/* for rmchg */
				zero(sidp,sizeof(*sidp));
				founddel = 1;
				First_esc = 1;
				First_cmt = 1;
				CDid_mrs = 0;
				for (p = pkt->p_line; *p && *p != 'D'; p++)
					;
				if (*p)
					*p = type;
			}
			else
				First_esc = founddel = First_cmt = 0;
			pkt->p_maxr = max(pkt->p_maxr,dt.d_sid.s_rel);
			rdp = &pkt->p_idel[dt.d_serial];
			rdp->i_sid.s_rel = dt.d_sid.s_rel;
			rdp->i_sid.s_lev = dt.d_sid.s_lev;
			rdp->i_sid.s_br = dt.d_sid.s_br;
			rdp->i_sid.s_seq = dt.d_sid.s_seq;
			rdp->i_pred = dt.d_pred;
			rdp->i_datetime = dt.d_datetime;
		}
		while ((c = getline(pkt))>        B[c    3       B[c            B[c    <        B[c    @        B[c            B[c    >        B[c    2       B[c    !        B[c    1       B[c    dc88     B[c    !        B[c            B[c     B\�     B[c    1       B[c     B]      B[c            B[c            B[c    opusys   B[c    !        B[c    1       B[c    w       B[c    !        B[c    R       B[c    :        B[c            B[c            B[c    1       B[c    !        B[c    3       B[c    U       B[c    !        B[c            B[c    %        B[c            B[c            B[c    1       B[c    !        B[c    2       B[c    @        B[c    3       B[c    .        B[c    dc88     B[c    .        B[c    opus     B[c     B^�     B[c            B[c            B[c            B[c    5        B[c    1       B[c            B[c    <        B[c    @        B[c    w       B[c    >        B[c            B[c    1       B[c    <        B[c    @        B[c    dc88     B[c    >        B[c    2       B[c            B[c    	NONBLANK(p);
	while (numeric(*p)) {
		p = satoi(p,ip++);
		NONBLANK(p);
	}
	cnt = ip - v;
	for (cur = ixgp; cur = (prev = cur)->i_next; )
		;
	prev->i_next = cur = (struct ixg *) fmalloc(sizeof(*cur) +
						(cnt-1)*sizeof(cur->i_ser[0]));
	cur->i_next = 0;
	cur->i_type = type;
	cur->i_cnt = cnt;
	for (i=0; cnt>0; --cnt)
		cur->i_ser[i++] = *v++;
}
