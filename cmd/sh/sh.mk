#	Copyright (c) 1984 AT&T
#	  All Rights Reserved

#	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T
#	The copyright notice above does not evidence any
#	actual or intended publication of such source code.

#ident	"@(#)sh:sh.mk	1.18.1.4"

#	Makefile for sh

ROOT =

DEFAULT_SH = sh.sec

DIR = $(ROOT)/bin

INS_DIR = $(ROOT)/usr/adm

INS = install

INC = $(ROOT)/usr/include

LDFLAGS = -s -lgen

CFLAGS = -O -I$(INC) -DNICE -DACCT -DNICEVAL=4 `if m88k;then echo '-W0,-P';fi`

CC = `if m88k; then echo '/usr/bin/cc' ; else echo cc ; fi`

STRIP = strip

SIZE = size

#top#
# Generated by makefile 1.18.1.4

MAKEFILE = sh.mk


MAINS = sh.bck sh.sec

OBJECTS =  args.o blok.o cmd.o ctype.o defs.o echo.o error.o expand.o \
	fault.o func.o hash.o hashserv.o io.o macro.o main.o msg.o name.o \
	print.o profile.o pwd.o service.o setbrk.o stak.o string.o test.o \
	word.o xec.o

SOURCES =  args.c blok.c cmd.c ctype.c defs.c echo.c error.c expand.c \
	fault.c func.c hash.c hashserv.c io.c macro.c main.c msg.c name.c \
	print.c profile.c pwd.c service.c setbrk.c stak.c string.c test.c \
	word.c xec.c

ALL:		$(MAINS)

sh.bck:		main.o args.o blok.o cmd.o defs.o error.o fault.o hash.o \
		hashserv.o io.o	msg.o name.o print.o service.o stak.o \
		string.o word.o	xec.o ctype.o echo.o expand.o func.o \
		macro.o	pwd.o setbrk.o test.o 
	$(CC) $(CFLAGS) -c main.c
	$(CC) $(CFLAGS)  -o sh.bck  main.o args.o blok.o cmd.o defs.o error.o \
	fault.o hash.o hashserv.o io.o msg.o name.o print.o service.o stak.o \
	string.o word.o xec.o ctype.o echo.o expand.o func.o macro.o pwd.o \
	setbrk.o test.o   $(LDFLAGS)

sh.sec:		main.o args.o blok.o cmd.o defs.o error.o fault.o hash.o \
		hashserv.o io.o	msg.o name.o print.o service.o stak.o \
		string.o word.o	xec.o ctype.o echo.o expand.o func.o \
		macro.o	pwd.o setbrk.o test.o 
	$(CC) $(CFLAGS) -DNOPASSIDS -c main.c
	$(CC) $(CFLAGS)  -o sh.sec  main.o args.o blok.o cmd.o defs.o error.o \
	fault.o hash.o hashserv.o io.o msg.o name.o print.o service.o stak.o \
	string.o word.o xec.o ctype.o echo.o expand.o func.o macro.o pwd.o \
	setbrk.o test.o   $(LDFLAGS)

args.o:		 $(INC)/setjmp.h $(INC)/signal.h \
		 $(INC)/sys/signal.h brkincr.h ctype.h defs.h mac.h \
		 mode.h	name.h stak.h 


blok.o:		 $(INC)/setjmp.h $(INC)/signal.h \
		 $(INC)/sys/signal.h brkincr.h ctype.h defs.h mac.h \
		 mode.h	name.h stak.h 


cmd.o:		 $(INC)/setjmp.h $(INC)/signal.h \
		 $(INC)/sys/signal.h brkincr.h ctype.h defs.h mac.h \
		 mode.h	name.h stak.h sym.h 


ctype.o:	 $(INC)/setjmp.h $(INC)/signal.h \
		 $(INC)/sys/signal.h brkincr.h ctype.h defs.h mac.h \
		 mode.h	name.h stak.h 
		 if [ "${_ID_}" ];\
		 then \
			 $(CC) $(CFLAGS) -c ctype.c; \
		 else \
			 CC=$(CC) ; export CC; \
			 sh ./:fix ctype; \
		 fi


defs.o:		 $(INC)/setjmp.h $(INC)/sys/fs/s5param.h \
		 $(INC)/sys/param.h mode.h name.h	


echo.o:		 $(INC)/setjmp.h $(INC)/signal.h \
		 $(INC)/sys/signal.h brkincr.h ctype.h defs.h mac.h \
		 mode.h	name.h stak.h 


error.o:	 $(INC)/setjmp.h $(INC)/signal.h \
		 $(INC)/sys/signal.h brkincr.h ctype.h defs.h mac.h \
		 mode.h	name.h stak.h 


expand.o:	 $(INC)/dirent.h $(INC)/setjmp.h \
		 $(INC)/signal.h $(INC)/sys/dirent.h \
		 $(INC)/sys/signal.h $(INC)/sys/stat.h \
		 $(INC)/sys/types.h brkincr.h ctype.h defs.h mac.h \
		 mode.h	name.h stak.h 


fault.o:	 $(INC)/setjmp.h $(INC)/signal.h \
		 $(INC)/sys/signal.h brkincr.h ctype.h defs.h mac.h \
		 mode.h	name.h stak.h 


func.o:		 $(INC)/setjmp.h $(INC)/signal.h \
		 $(INC)/sys/signal.h brkincr.h ctype.h defs.h mac.h \
		 mode.h	name.h stak.h 


hash.o:		 $(INC)/setjmp.h $(INC)/signal.h \
		 $(INC)/sys/signal.h brkincr.h ctype.h defs.h hash.h \
		 mac.h mode.h name.h stak.h 


hashserv.o:	 $(INC)/errno.h $(INC)/setjmp.h \
		 $(INC)/signal.h $(INC)/sys/errno.h	\
		 $(INC)/sys/signal.h $(INC)/sys/stat.h \
		 $(INC)/sys/types.h brkincr.h ctype.h defs.h hash.h \
		 mac.h mode.h name.h stak.h 


io.o:		 $(INC)/fcntl.h $(INC)/setjmp.h \
		 $(INC)/signal.h $(INC)/sys/fcntl.h	\
		 $(INC)/sys/signal.h brkincr.h ctype.h defs.h dup.h \
		 mac.h mode.h name.h stak.h 


macro.o:	 $(INC)/setjmp.h $(INC)/signal.h \
		 $(INC)/sys/signal.h brkincr.h ctype.h defs.h mac.h \
		 mode.h	name.h stak.h sym.h 


main.o:		 $(INC)/setjmp.h $(INC)/signal.h \
		 $(INC)/sys/signal.h $(INC)/sys/stat.h \
		 $(INC)/sys/types.h brkincr.h ctype.h defs.h dup.h \
		 mac.h mode.h name.h stak.h sym.h timeout.h 


msg.o:		 $(INC)/setjmp.h $(INC)/signal.h \
		 $(INC)/sys/signal.h brkincr.h ctype.h defs.h mac.h \
		 mode.h	name.h stak.h sym.h 
		 if [ "${_ID_}" ];\
		 then \
			 $(CC) $(CFLAGS) -c msg.c; \
		 else \
			 CC=$(CC) ; export CC; \
			 sh ./:fix msg; \
		 fi


name.o:		 $(INC)/setjmp.h $(INC)/signal.h \
		 $(INC)/sys/signal.h brkincr.h ctype.h defs.h mac.h \
		 mode.h	name.h stak.h 


print.o:	 $(INC)/setjmp.h $(INC)/signal.h \
		 $(INC)/sys/fs/s5param.h $(INC)/sys/param.h	\
		 $(INC)/sys/signal.h brkincr.h ctype.h defs.h mac.h \
		 mode.h	name.h stak.h 


profile.o:	 


pwd.o:		 $(INC)/dirent.h $(INC)/sys/dirent.h \
		 $(INC)/sys/stat.h $(INC)/sys/types.h mac.h	


service.o:	 $(INC)/errno.h $(INC)/setjmp.h \
		 $(INC)/signal.h $(INC)/sys/errno.h	\
		 $(INC)/sys/signal.h brkincr.h ctype.h defs.h mac.h \
		 mode.h	name.h stak.h 
		 $(CC) $(CFLAGS) -I$(ROOT)/usr/src/cmd/acct -c service.c


setbrk.o:	 $(INC)/setjmp.h $(INC)/signal.h \
		 $(INC)/sys/signal.h brkincr.h ctype.h defs.h mac.h \
		 mode.h	name.h stak.h 


stak.o:		 $(INC)/setjmp.h $(INC)/signal.h \
		 $(INC)/sys/signal.h brkincr.h ctype.h defs.h mac.h \
		 mode.h	name.h stak.h 


string.o:	 $(INC)/setjmp.h $(INC)/signal.h \
		 $(INC)/sys/signal.h brkincr.h ctype.h defs.h mac.h \
		 mode.h	name.h stak.h 


test.o:		 $(INC)/setjmp.h $(INC)/signal.h \
		 $(INC)/sys/signal.h $(INC)/sys/stat.h \
		 $(INC)/sys/types.h brkincr.h ctype.h defs.h mac.h \
		 mode.h	name.h stak.h 


word.o:		 $(INC)/setjmp.h $(INC)/signal.h \
		 $(INC)/sys/signal.h brkincr.h ctype.h defs.h mac.h \
		 mode.h	name.h stak.h sym.h 


xec.o:		 $(INC)/errno.h $(INC)/setjmp.h \
		 $(INC)/signal.h $(INC)/sys/errno.h	\
		 $(INC)/sys/signal.h $(INC)/sys/times.h \
		 $(INC)/sys/types.h brkincr.h ctype.h defs.h hash.h \
		 mac.h mode.h name.h stak.h sym.h 
		 set +e; if u370;\
		 then\
		 	$(CC) $(CFLAGS) -b1,0 -c xec.c;\
		 else\
			$(CC) $(CFLAGS) -c xec.c;\
		 fi

GLOBALINCS = $(INC)/errno.h $(INC)/setjmp.h \
	$(INC)/signal.h $(INC)/sys/errno.h \
	$(INC)/sys/signal.h $(INC)/sys/times.h \
	$(INC)/sys/types.h 

LOCALINCS = brkincr.h ctype.h defs.h hash.h mac.h mode.h name.h stak.h sym.h

clean:
	rm -f $(OBJECTS)

clobber:
	rm -f $(OBJECTS) $(MAINS)

newmakefile:
	makefile -m -f $(MAKEFILE)  -s INC $(INC)
#bottom#

all : ALL

install: ALL
	$(INS) -f $(INS_DIR) -m 444 sh.bck
	$(INS) -f $(INS_DIR) -m 444 sh.sec
	cp ./$(DEFAULT_SH) ./sh
	$(INS) -o -m 555 -u bin -g root -f $(DIR) sh
	ln -f $(DIR)/sh $(DIR)/rsh

size: ALL
	$(SIZE) $(MAINS)

strip: ALL
	$(STRIP) $(MAINS)

#	These targets are useful but optional

partslist:
	@echo $(MAKEFILE) $(SOURCES) $(LOCALINCS)  |  tr ' ' '\012'  |  sort

productdir:
	@echo $(DIR) | tr ' ' '\012' | sort

product:
	@echo $(MAINS)  |  tr ' ' '\012'  | \
	sed 's;^;$(DIR)/;'

srcaudit:
	@fileaudit $(MAKEFILE) $(LOCALINCS) $(SOURCES) -o $(OBJECTS) $(MAINS)
