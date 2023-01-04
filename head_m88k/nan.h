#ifndef _NAN_H_
#define _NAN_H_


/*	Copyright (c) 1989 OPUS Systems	*/
/*	      All Rights Reserved 		*/


/*	Copyright (c) 1984 AT&T	*/
/*	  All Rights Reserved  	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/

#ifdef __88000_OCS_DEFINED
#include "File not specified by 88000 OCS."
#endif	/* __88000_OCS_DEFINED */

/* Handling of Not_a_Number's (only in IEEE floating-point standard) */
#if _IEEE
typedef union 
{
         struct	
	 {
	    unsigned sign     : 1;
	    unsigned exponent :11;
            unsigned bits:20;
	    unsigned fraction_low:32;
         } inf_parts;
	 struct 
	 {
	    unsigned sign     : 1;
            unsigned exponent :11;
	    unsigned qnan_bit : 1;
	    unsigned bits     :19;
	    unsigned fraction_low: 32;
         } nan_parts;
	 struct
	 {
	    unsigned sign     : 1;
            unsigned exponent : 8;
	    unsigned fraction : 23;
	 } fs;
         double d;
         float f;
         int i[2];

} dnan; 

	/* IsNANorINF checks that exponent of double == 2047 *
	 * i.e. that number is a NaN or an infinity	     */
	
#define IsNANorINF(X)  (((dnan *)&(X))->nan_parts.exponent == 0x7ff)

	/* IsINF must be used after IsNANorINF		*
 	 * has checked the exponent 			*/

#define IsINF(X)  (((dnan *)&(X))->inf_parts.bits == 0 &&  \
                    ((dnan *)&(X))->inf_parts.fraction_low == 0)

	/* IsPosNAN and IsNegNAN can be used 		*
 	 * to check the sign of infinities too		*/

#define IsPosNAN(X)  (((dnan *)&(X))->nan_parts.sign == 0)

#define IsNegNAN(X)  (((dnan *)&(X))->nan_parts.sign == 1)

	/* GETNaNPC gets the leftmost 32 bits 		*	
	 * of the fraction part				*/

#define GETNaNPC(dval)   (((dnan *)&(dval))->inf_parts.bits << 12 | \
			  ((dnan *)&(dval))->nan_parts.fraction_low>> 20) 

#define KILLFPE()       (void) kill(getpid(), 8)

#define NaN(X)  (((dnan *)&(X))->nan_parts.exponent == 0x7ff) && \
		( (((dnan *)&(X))->nan_parts.bits != 0) || \
		(((dnan *)&(X))->nan_parts.fraction_low != 0) )

#define	NaD(X)	NaN(X)

#define NaF(X)	((((dnan *)&(X))->fs.exponent == 0xff) && \
		 (((dnan *)&(X))->fs.fraction != 0))

#define KILLNaN(X)      if (NaN(X)) KILLFPE()

#else

typedef double dnan;
#define IsINF(X)   0
#define IsPINF(X)  0
#define IsNegNAN(X)  0
#define IsPosNAN(X)  0
#define IsNAN(X)   0
#define GETNaNPC   0L

#define Nan(X)  0
#define KILLNaN(X)
#endif

#endif	/* ! _NAN_H_ */
