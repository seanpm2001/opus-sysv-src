/*	@(#)allo.c	1.3	*/
# include "mfile2"

NODE resc[3];

int busy[REGSZ];

int maxa, mina, maxb, minb;

# ifndef ALLO0
allo0(){ /* free everything */

	register i;

	maxa = maxb = -1;
	mina = minb = 0;

	REGLOOP(i){
		busy[i] = 0;
		if( rstatus[i] & STAREG ){
			if( maxa<0 ) mina = i;
			maxa = i;
			}
		if( rstatus[i] & STBREG ){
			if( maxb<0 ) minb = i;
			maxb = i;
			}
		}
	}
# endif

# define TBUSY 01000

# ifndef ALLO
allo( p, q ) NODE *p; struct optab *q; {

	register n, i, j;
	int either;

	n = q->needs;
	either = ( EITHER & n );
	i = 0;

	while( n & NACOUNT ){
		resc[i].in.op = REG;
		resc[i].tn.rval = freereg( p, n&NAMASK );
		resc[i].tn.lval = 0;
#ifdef FLEXNAMES
		resc[i].in.name = "";
#else	
		resc[i].in.name[0] = '\0';
#endif
		n -= NAREG;
		++i;
		}

	if (either) { /* all or nothing at all */
		for( j = 0; j < i; j++ )
			if( resc[j].tn.rval < 0 ) { /* nothing */
				i = 0;
				break;
				}
		if( i != 0 ) goto ok; /* all */
		}

	while( n & NBCOUNT ){
		resc[i].in.op = REG;
		resc[i].tn.rval = freereg( p, n&NBMASK );
		resc[i].tn.lval = 0;
#ifdef FLEXNAMES
		resc[i].in.name = "";
#else
		resc[i].in.name[0] = '\0';
#endif
		n -= NBREG;
		++i;
		}
	if (either) { /* all or nothing at all */
		for( j = 0; j < i; j++ )
			if( resc[j].tn.rval < 0 ) { /* nothing */
				i = 0;
				break;
				}
		if( i != 0 ) goto ok; /* all */
		}

	if( n & NTMASK ){
		resc[i].in.op = OREG;
		resc[i].tn.rval = TMPREG;
		if( p->in.op == STCALL || p->in.op == STARG || p->in.op == UNARY STCALL || p->in.op == STASG ){
			resc[i].tn.lval = freetemp( (SZCHAR*p->stn.stsize + (SZINT-1))/SZINT );
			}
		else {
			resc[i].tn.lval = freetemp( (n&NTMASK)/NTEMP );
			}
#ifdef FLEXNAMES
#ifdef FORT
		resc[i].in.name = "\0\0\1";
#else
		resc[i].in.name = "";
#endif
#else
		resc[i].in.name[0] = '\0';
#ifdef FORT
		resc[i].in.name[2] = '\1';
#endif
#endif
		resc[i].tn.lval = BITOOR(resc[i].tn.lval);
		++i;
		}

	/* turn off "temporarily busy" bit */

	ok:
	REGLOOP(j){
		busy[j] &= ~TBUSY;
		}

	for( j=0; j<i; ++j ) if( resc[j].tn.rval < 0 ) return(0);
	return(1);

	}
# endif

extern unsigned int offsz;
freetemp( k ){ /* allocate k integers worth of temp space */
	/* we also make the convention that, if the number of words is more than 1,
	/* it must be aligned for storing doubles... */

# ifndef BACKTEMP
	int t;

	if( k>1 ){
		SETOFF( tmpoff, ALDOUBLE );
		}

	t = tmpoff;
	tmpoff += k*SZINT;
	if( tmpoff > maxoff ) maxoff = tmpoff;
	if( tmpoff >= offsz )
		cerror( "stack overflow" );
	if( tmpoff-baseoff > maxtemp ) maxtemp = tmpoff-baseoff;
	return(t);

# else
	tmpoff += k*SZINT;
	if( k>1 ) {
		SETOFF( tmpoff, ALDOUBLE );
		}
	if( tmpoff > maxoff ) maxoff = tmpoff;
#ifndef FORT
	/* these two lines blow f77*/
	if( tmpoff >= offsz )
		cerror( "stack overflow" );
#endif
	if( tmpoff-baseoff > maxtemp ) maxtemp = tmpoff-baseoff;
	return( -tmpoff );
# endif
	}

# ifndef FREEREG
freereg( p, n ) NODE *p; {
	/* allocate a register of type n */
	/* p gives the type, if floating */

	register j;

	/* not general; means that only one register (the result) OK for call */
	if( callop(p->in.op) ){
		j = callreg(p);
		if( usable( p, n, j ) ) return( j );
		/* have allocated callreg first */
		}
	j = p->in.rall & ~MUSTDO;
	if( j!=NOPREF && usable(p,n,j) ){ /* needed and not allocated */
		return( j );
		}
	if( n&NAMASK ){
		for( j=mina; j<=maxa; ++j ) if( rstatus[j]&STAREG ){
			if( usable(p,n,j) ){
				return( j );
				}
			}
		}
	else if( n &NBMASK ){
		for( j=minb; j<=maxb; ++j ) if( rstatus[j]&STBREG ){
			if( usable(p,n,j) ){
				return(j);
				}
			}
		}

	return( -1 );
	}
# endif

# ifndef USABLE
usable( p, n, r ) NODE *p; {
	/* decide if register r is usable in tree p to satisfy need n */

	/* checks, for the moment */
	if( !istreg(r) ) cerror( "usable asked about nontemp register" );

	if( busy[r] > 1 ) return(0);
	if( isbreg(r) ){
		if( n&NAMASK ) return(0);
		}
	else {
		if( n & NBMASK ) return(0);
		}
	if( (n&NAMASK) && (szty(p->in.type) == 2) ){ /* only do the pairing for real regs */
#if !MC88K
		if( r&01 ) return(0);
#endif
		if( !istreg(r+1) ) return( 0 );
		if( busy[r+1] > 1 ) return( 0 );
		if( busy[r] == 0 && busy[r+1] == 0  ||
		    busy[r+1] == 0 && shareit( p, r, n ) ||
		    busy[r] == 0 && shareit( p, r+1, n ) ){
			busy[r] |= TBUSY;
			busy[r+1] |= TBUSY;
			return(1);
			}
		else return(0);
		}
	if( busy[r] == 0 ) {
		busy[r] |= TBUSY;
		return(1);
		}

	/* busy[r] is 1: is there chance for sharing */
	return( shareit( p, r, n ) );

	}
# endif

shareit( p, r, n ) NODE *p; {
	/* can we make register r available by sharing from p
	   given that the need is n */
	if( (n&(NASL|NBSL)) && ushare( p, 'L', r ) ) return(1);
	if( (n&(NASR|NBSR)) && ushare( p, 'R', r ) ) return(1);
	return(0);
	}

# ifndef USHARE
ushare( p, f, r ) NODE *p; {
	/* can we find a register r to share on the left or right
		(as f=='L' or 'R', respectively) of p */
	p = getlr( p, f );
	if( p->in.op == UNARY MUL ) p = p->in.left;
	if( p->in.op == OREG ){
		if( R2TEST(p->tn.rval) ){
			return( r==R2UPK1(p->tn.rval) || r==R2UPK2(p->tn.rval) );
			}
		else return( r == p->tn.rval );
		}
	if( p->in.op == REG ){
		return( r == p->tn.rval || ( szty(p->in.type) == 2 && r==p->tn.rval+1 ) );
		}
	return(0);
	}
# endif

recl2( p ) register NODE *p; {
	register r = p->tn.rval;
	if( p->in.op == REG ) rfree( r, p->in.type );
	else if( p->in.op == OREG ) {
		if( R2TEST( r ) ) {
			if( R2UPK1( r ) != R2NOBASE )
				rfree( R2UPK1( r ), PTR+INT );
			rfree( R2UPK2( r ), INT );
			}
		else {
			rfree( r, PTR+INT );
			}
		}
	}

int rdebug = 0;

# ifndef RFREE
rfree( r, t ) TWORD t; {
	/* mark register r free, if it is legal to do so */
	/* t is the type */

# ifndef BUG3
	if( rdebug ){
		printf( "rfree( %s ), size %d\n", rnames[r], szty(t) );
		}
# endif

#if CLIPPER
	if( istreg(r) || r == R0 || r == R1 || r == F1 )
#else
#if MC88000
	if( istreg(r) || r < R10 )
#else
	if( istreg(r) )
#endif
#endif
	{
		if( --busy[r] < 0 ) cerror( "register overfreed");
		if( szty(t) == 2 ){
#if MC88K
			if( (istreg(r)^istreg(r+1)) ) cerror( "illegal free" );
#else
			if( (r&01) || (istreg(r)^istreg(r+1)) ) cerror( "illegal free" );
#endif
			if( --busy[r+1] < 0 ) cerror( "register overfreed" );
			}
		}
	}
# endif

# ifndef RBUSY
rbusy(r,t) TWORD t; {
	/* mark register r busy */
	/* t is the type */

# ifndef BUG3
	if( rdebug ){
		printf( "rbusy( %s ), size %d\n", rnames[r], szty(t) );
		}
# endif

	if( istreg(r) ) ++busy[r];
	if( szty(t) == 2 ){
		if( istreg(r+1) ) ++busy[r+1];
#if !N16
		if( /*(r&01) ||*/ (istreg(r)^istreg(r+1)) ) cerror( "illegal register pair freed" );
#else
		if( (r&01) || (istreg(r)^istreg(r+1)) ) cerror( "illegal register pair freed" );
#endif
		}
	}
# endif

# ifndef BUG3
rwprint( rw ){ /* print rewriting rule */
	register i, flag;
	static char * rwnames[] = {

		"RLEFT",
		"RRIGHT",
		"RESC1",
		"RESC2",
		"RESC3",
		0,
		};

	if( rw == RNULL ){
		printf( "RNULL" );
		return;
		}

	if( rw == RNOP ){
		printf( "RNOP" );
		return;
		}

	flag = 0;
	for( i=0; rwnames[i]; ++i ){
		if( rw & (1<<i) ){
			if( flag ) printf( "|" );
			++flag;
			printf( rwnames[i] );
			}
		}
	}
# endif

reclaim( p, rw, cookie ) NODE *p; {
	register NODE **qq;
	register NODE *q;
	register i;
	NODE *recres[5];
	struct respref *r;

	/* get back stuff */

# ifndef BUG3
	if( rdebug ){
		printf( "reclaim( %o, ", p );
		rwprint( rw );
		printf( ", " );
		prcook( cookie );
		printf( " )\n" );
		}
# endif

	if( rw == RNOP || ( p->in.op==FREE && rw==RNULL ) ) return;  /* do nothing */

	walkf( p, recl2 );

	if( callop(p->in.op) ){
		/* check that all scratch regs are free */
		callchk(p);  /* ordinarily, this is the same as allchk() */
		}

	if( rw == RNULL || (cookie&FOREFF) ){ /* totally clobber, leaving nothing */
		tfree(p);
		return;
		}

	/* handle condition codes specially */

	if( (cookie & FORCC) && (rw&RESCC)) {
		/* result is CC register */
		tfree(p);
		p->in.op = CCODES;
		p->tn.lval = 0;
		p->tn.rval = 0;
		return;
		}

	/* locate results */

	qq = recres;

	if( rw&RLEFT) *qq++ = getlr( p, 'L' );
	if( rw&RRIGHT ) *qq++ = getlr( p, 'R' );
	if( rw&RESC1 ) *qq++ = &resc[0];
	if( rw&RESC2 ) *qq++ = &resc[1];
	if( rw&RESC3 ) *qq++ = &resc[2];

	if( qq == recres ){
		cerror( "illegal reclaim");
		}

	*qq = NIL;

	/* now, select the best result, based on the cookie */

	for( r=respref; r->cform; ++r ){
		if( cookie & r->cform ){
			for( qq=recres; (q= *qq) != NIL; ++qq ){
				if( tshape( q, r->mform ) ) goto gotit;
				}
			}
		}

	/* we can't do it; die */
	cerror( "cannot reclaim");

	gotit:

	if( p->in.op == STARG ) p = p->in.left;  /* STARGs are still STARGS */

	q->in.type = p->in.type;  /* to make multi-register allocations work */
		/* maybe there is a better way! */
#if CLIPPER
	q->tn.arg = p->tn.arg;
	q->tn.dst = p->tn.dst;
	q->tn.off = p->tn.off;
#endif
#if MC88000
	q->tn.arg = p->tn.arg;
	q->tn.dst = p->tn.dst;
	q->tn.off = p->tn.off;
	q->tn.alink = p->tn.alink;
#endif
	q = tcopy(q);

	tfree(p);

	p->in.op = q->in.op;
	p->tn.lval = q->tn.lval;
	p->tn.rval = q->tn.rval;
#ifdef FLEXNAMES
	p->in.name = q->in.name;
#ifdef ONEPASS				/* is this REALLY needed?? */
	p->in.stalign = q->in.stalign;
#endif
#else
	for( i=0; i<NCHNAM; ++i )
		p->in.name[i] = q->in.name[i];
#endif

	q->in.op = FREE;

	/* if the thing is in a register, adjust the type */

	switch( p->in.op ){

	case REG:
		if( !rtyflg ){
			/* the C language requires intermediate results to change type */
			/* this is inefficient or impossible on some machines */
			/* the "T" command in match supresses this type changing */
			if( p->in.type == CHAR || p->in.type == SHORT ) p->in.type = INT;
			else if( p->in.type == UCHAR || p->in.type == USHORT ) p->in.type = UNSIGNED;
			else if( p->in.type == FLOAT ) p->in.type = DOUBLE;
			}
		if( ! (p->in.rall & MUSTDO ) ) return;  /* unless necessary, ignore it */
		i = p->in.rall & ~MUSTDO;
		if( i & NOPREF ) return;
		if( i != p->tn.rval ){
#ifdef MC88000
			if( busy[i] ){
				cerror( "faulty register move" );
				}
			if (szty(p->in.type) == 2) {
				/* 
				 * break the move into 2 INTS and keep the 
				 * the busy array happy
				 */
				rbusy( i, INT );
				rfree( p->tn.rval, INT );
				rmove( i, p->tn.rval, INT );
				if( busy[i+1] ){
					cerror( "faulty register(2) move" );
					}
				rbusy( i+1, INT );
				rfree( p->tn.rval+1, INT );
				rmove( i+1, p->tn.rval+1, INT );
				p->tn.rval = i;
			}
			else {
#endif
			if( busy[i] || ( szty(p->in.type)==2 && busy[i+1] ) ){
				cerror( "faulty register move" );
				}
			rbusy( i, p->in.type );
			rfree( p->tn.rval, p->in.type );
			rmove( i, p->tn.rval, p->in.type );
			p->tn.rval = i;
#ifdef MC88000
				}
#endif
			}

	case OREG:
		if( R2TEST(p->tn.rval) ){
			int r1, r2;
			r1 = R2UPK1(p->tn.rval);
			r2 = R2UPK2(p->tn.rval);
			if( r1 != R2NOBASE )
				if( (busy[r1]>1 && istreg(r1)) || (busy[r2]>1 && istreg(r2)) ){
					cerror( "potential register overwrite" );
				}
			}
		else if( (busy[p->tn.rval]>1) && istreg(p->tn.rval) ) cerror( "potential register overwrite");

		}

	}

NODE *
tcopy( p ) register NODE *p; {
	/* make a fresh copy of p */

	register NODE *q;
	register r;

	q = talloc();
	*q = *p;

	r = p->tn.rval;
	if( p->in.op == REG ) rbusy( r, p->in.type );
	else if( p->in.op == OREG ) {
		if( R2TEST(r) ){
			if( R2UPK1(r) != R2NOBASE ) rbusy( R2UPK1(r), PTR+INT );
			rbusy( R2UPK2(r), INT );
			}
		else {
			rbusy( r, PTR+INT );
			}
		}

	switch( optype(q->in.op) ){

	case BITYPE:
		q->in.right = tcopy(p->in.right);
	case UTYPE:
		q->in.left = tcopy(p->in.left);
		}

	return(q);
	}

allchk(){
	/* check to ensure that all register are free */

	register i;

	REGLOOP(i){
		if( istreg(i) && busy[i] ){
			cerror( "register allocation error");
			}
		}

	}
