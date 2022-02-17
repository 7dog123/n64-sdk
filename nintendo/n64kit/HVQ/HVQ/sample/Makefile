# 
#  N64-HVQ2 library  Sample program
#
#  FILE : Makefile
# 
#  Copyright (C) 1998,1999 NINTENDO Co.,Ltd.
# 

# 1999-02-19

include $(ROOT)/usr/include/make/PRdefs

######################################################################
#  Kind of HVQ2 decoder being used
#    0 : CPU version
#    1 : CPU+RSP version
USE_RSP = 1

#  Format of display-use frame buffer (Selected HVQ2 decoder also reflects on this)
#    1 : 16-bit
#    2 : 32-bit
CFB_FORMAT = 1

#  Maximum size of image [pixel]  (Reflects on the memory reserved for hvqwork.c)
MAXWIDTH  = 320
MAXHEIGHT = 240
######################################################################
#  Directory holding the HVQ2 library (libhvq2.a)
HVQLIBDIR = ../libhvq2/lib

#  Directory holding the HVQ2 include file
HVQINCDIR = ../libhvq2/lib

#  Directory holding the HVQ microcode
HVQUCODEDIR = ..\libhvq2\rspcode
######################################################################

LCINCS = -I. -I$(HVQINCDIR)
LCOPTS = -O2 -G0 -g -Wall
LCDEFS = -D_LANGUAGE_C -DMAXWIDTH=$(MAXWIDTH) -DMAXHEIGHT=$(MAXHEIGHT) -DCFB_FORMAT=$(CFB_FORMAT) -DUSE_RSP=$(USE_RSP)

LIBS = -L$(HVQLIBDIR) -lhvq2 -L$(ROOT)/usr/lib -lgultra -L$(ROOT)/gcc/mipse/lib -lkmc

UCODE = $(HVQUCODEDIR)\hvq2sp$(CFB_FORMAT).o

ROM = sample.n64

SPECFILE = spec

CFILES      = system.c main.c
CODEOBJECTS = $(CFILES:.c=.o)
CODESEGMENT = codesegment.o

DATAFILES   = hvqwork.c hvqbuf.c cfb.c
DATAOBJECTS = $(DATAFILES:.c=.o)

default: $(ROM)

include $(COMMONRULES)

$(ROM): $(CODESEGMENT) $(DATAOBJECTS) $(SPECFILE) sample.hvq
	$(MAKEROM) -DUSE_RSP=$(USE_RSP) -DUCODE="$(UCODE)" -r $(ROM) $(SPECFILE)

$(CODESEGMENT): $(CODEOBJECTS)
	$(LD) -o $(CODESEGMENT) -r $(CODEOBJECTS) $(LIBS)

main.o system.o cfb.o hvqwork.o : Makefile
main.o system.o cfb.o hvqwork.o hvqbuf.o : system.h

######################################################################
