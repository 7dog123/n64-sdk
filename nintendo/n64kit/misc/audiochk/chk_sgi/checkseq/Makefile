#
# Makeifle
#
include $(ROOT)/usr/include/make/PRdefs

N64KITDIR	= C:\nintendo\n64kit
NUSYSDIR	= $(N64KITDIR)\nusys
NUSYSINCDIR	= $(NUSYSDIR)\include
NUSYSLIBDIR	= $(NUSYSDIR)\lib

LIB		= $(ROOT)/usr/lib
LPR		= $(LIB)/PR
INC		= $(ROOT)/usr/include
CC		= gcc
LD		= ld
MAKEROM		= mild
RM		= del

LCDEFS		=
LCINCS		= -I. -I$(ROOT)/usr/include/PR
LCOPTS		= -G 0
LDFLAGS		= $(MKDEPOPT) -L../lib -lchk_sgi -L$(LIB) -L$(NUSYSLIBDIR) -lnusys_d -lgultra_d -L$(GCCDIR)/mipse/lib -lkmc

OPTIMIZER	= -O3

TARGETS		= $(BINARYFILE:.bin=.n64)
APP		= $(BINARYFILE:.bin=.out)

HFILES		= params.h
CODEFILES	= params.c
CODEOBJECTS	= $(BINARYFILE) $(CODEFILES:.c=.o) $(NUSYSLIBDIR)/nusys.o
CODESEGMENT	= $(BINARYFILE:.bin=.o)

default:	all

#include $(COMMONRULES)

all:
	$(MAKE) checkseq1.n64 BINARYFILE=checkseq1.bin
	$(MAKE) checkseq2.n64 BINARYFILE=checkseq2.bin

$(CODESEGMENT):	$(CODEOBJECTS) Makefile
	$(LD) -u mainproc -o $(CODESEGMENT) -r $(CODEOBJECTS) $(LDFLAGS)

$(TARGETS):	$(CODESEGMENT) spec
	$(MAKEROM) spec -I$(NUSYSINCDIR) -r $(TARGETS) -e $(APP) -DCODESEGMENT=$(CODESEGMENT) -DAPPNAME=$(APP)

clean:
	$(RM) *.o
	$(RM) *.out
	$(RM) *.n64

# depends
params.o:	params.c params.h Makefile
