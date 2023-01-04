#	Copyright (c) 1984 AT&T
#	  All Rights Reserved

#	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T
#	The copyright notice above does not evidence any
#	actual or intended publication of such source code.

#ident	"@(#)killall:killall.mk	1.1"

#	Makefile for killall 

ROOT =

DIR = $(ROOT)/etc

INC = $(ROOT)/usr/include

LDFLAGS = -s $(LDLIBS)

CFLAGS = -O -I$(INC)

STRIP = strip

SIZE = size

#top#
# Generated by makefile 1.47

MAKEFILE = killall.mk


MAINS = killall

OBJECTS =  killall.o

SOURCES =  killall.c

ALL:		$(MAINS)

killall:	killall.o 
	$(CC) $(CFLAGS)  -o killall  killall.o   $(LDFLAGS)


killall.o:	 $(INC)/stdio.h $(INC)/a.out.h \
		 $(INC)/nlist.h $(INC)/filehdr.h \
		 $(INC)/aouthdr.h	$(INC)/scnhdr.h \
		 $(INC)/reloc.h $(INC)/linenum.h \
		 $(INC)/syms.h $(INC)/storclass.h \
		 $(INC)/fcntl.h $(INC)/sys/types.h \
		 $(INC)/sys/region.h $(INC)/sys/param.h \
		 $(INC)/sys/proc.h $(INC)/sys/var.h	

GLOBALINCS = $(INC)/a.out.h $(INC)/aouthdr.h \
	$(INC)/fcntl.h $(INC)/filehdr.h $(INC)/linenum.h \
	$(INC)/nlist.h $(INC)/reloc.h $(INC)/scnhdr.h \
	$(INC)/stdio.h $(INC)/storclass.h $(INC)/syms.h \
	$(INC)/sys/param.h \
	$(INC)/sys/proc.h $(INC)/sys/region.h \
	$(INC)/sys/types.h \
	$(INC)/sys/var.h 


clean:
	rm -f $(OBJECTS)

clobber:
	rm -f $(OBJECTS) $(MAINS)

newmakefile:
	makefile -m -f $(MAKEFILE)  -s INC $(INC)
#bottom#

all : ALL

install: ALL
	cpset $(MAINS) $(DIR)

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
