/*	Copyright (c) 1984 AT&T	*/
/*	  All Rights Reserved  	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/

#ident	"@(#)sccs:lib/comobj/dolist.c	6.2"
# include	"../../hdr/defines.h"


static char br[]  =  "bad range (co12)";

dolist(pkt,list,ch)
struct packet *pkt;
register char *list;
char ch;
{
	char *getasid();
	struct sid lowsid, highsid, sid;
	int n;

	while (*list) {
		list = getasid(list,&lowsid);
		if (*list == '-') {
			++list;
			list = getasid(list,&highsid);
			if (lowsid.s_br == 0) {
				if ((highsid.s_br || highsid.s_seq ||
					highsid.s_rel < lowsid.s_rel ||
					(highsid.s_rel == lowsid.s_rel &&
					highsid.s_lev < lowsid.s_lev)))
						fatal(br);
				sid.s_br = sid.s_seq = 0;
				for (sid.s_rel = lowsid.s_rel; sid.s_rel <= highsid.s_rel; sid.s_rel++) {
					sid.s_lev = (sid.s_rel == lowsid.s_rel ? lowsid.s_lev : 1);
					for ( ; n = sidtoser(&sid,pkt); sid.s_lev++)      @          A��    j Sendmail v/Z ready at b    A��     A�� A�� A�h                   A��     A� A A�� �                   A��     A�( A�� A��                   A��     A�� A�� A��                   A��     A�@ A�� A�             @     A��     A�� A�  A�0             @     A��     A�X A� A�X 4                  A��     A�  A�0 A��                    A��     A�� A�p A��                    A��     A�� A��                        A��     A� A�� A�� A�� A�� A�  A�     A��     A�  A�0 A�@ A�P A�` A�p A�     A��     A� A�  A�0 A�@ A�P A�` A�p     A��     A� A� A�� A�� A�� A�� A��     A��     A�h A�x A�� A�� A� A�(         A��     A�8 A�H A�X A�h A�x A�� A��     A��     A�h A�x A�� A�� A�� A��         A��     A�� A�� A�� A�� A� A�         A��     A�( A�8 A�H A�X A�h A�x         A��     B  B0 B@ BP B` Bp         A��     B  B B  B0 B@ BP         A��  