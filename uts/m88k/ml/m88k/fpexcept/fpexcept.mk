# ****************************************************************************
# makefile for floating point exception libraries
#****************************************************************************
.SUFFIXES: .m4 .o .s .a 

LIBNAME=../../$(LIBDIR)/lib.ml

all: pickup $(LIBNAME)

shrink:
	rm *.o
clobber:
	rm *.o
	-rm $(LIBNAME)

FILES = $(LIBNAME)(fpup.o) \
	$(LIBNAME)(fpui.o) \
	$(LIBNAME)(FPintover.o) \
	$(LIBNAME)(FPunimp.o) \
	$(LIBNAME)(FPpriviol.o) \
	$(LIBNAME)(FPresoper.o) \
	$(LIBNAME)(FPdivzero.o) \
	$(LIBNAME)(FPundflow.o) \
	$(LIBNAME)(FPovrflow.o) \
	$(LIBNAME)(NaN.o) \
	$(LIBNAME)(infinity.o) \
	$(LIBNAME)(zero.o) \
	$(LIBNAME)(denorm.o) \
	$(LIBNAME)(unixrout.o) \
	$(LIBNAME)(handler.o)  \
	$(LIBNAME)(fpehndlr.o)

$(LIBNAME) : $(FILES)
	$(AR) ruv $(LIBNAME) *.o
	rm -f *.o

pickup:
	-@if [ "`ls *.o 2>/dev/null`" ] ; \
	then \
		echo "\t$(AR) ruv $(LIBNAME) *.o" ; \
		$(AR) ruv $(LIBNAME) *.o ; \
		echo "\trm -f *.o" ; \
		rm -f *.o  ; \
	fi

.m4.a:
	m4 $< >$*.s
	$(CC) -c $*.s

