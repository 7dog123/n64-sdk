# 
#  N64-HVQM2 library  Sample program
#
#  FILE : Makefile
# 
#  Copyright (C) 1998,1999 NINTENDO Co.,Ltd.
# 

# 1999-04-21

include $(ROOT)/usr/include/make/PRdefs

######################################################################
#  Kind of HVQM2 decoder being used
#    0 : CPU version
#    1 : CPU+RSP version
USE_RSP = 1

#  Whether to forcedly synchronize video to audio when video playback is late
#    0 : Decode every frame (do not synchronize)
#    1 : Skip frames to force video into sync
SYNC_VIDEO = 1

#  Format of display-use frame buffer (selected HVQM2 decoder also reflects on this)
#    1 : 16-bit
#    2 : 32-bit
CFB_FORMAT = 1

#  Maximum size of image [pixel]  (reflects on memory reserved for hvqmwork.c)
MAXWIDTH  = 320
MAXHEIGHT = 240

######################################################################
#  The directory holding the HVQM2 library (libhvqm2.a)
HVQMLIBDIR = ../libhvqm2/lib

#  The directory holding the HVQM2 include file
HVQMINCDIR = ../libhvqm2/lib

#  The directory holding the HVQM2 microcode
HVQMUCODEDIR = ../libhvqm2/rspcode
######################################################################

LCINCS = -I. -I$(HVQMINCDIR)
LCOPTS = -O2 -G0 -g
LCDEFS = -D_LANGUAGE_C -DMAXWIDTH=$(MAXWIDTH) -DMAXHEIGHT=$(MAXHEIGHT) -DCFB_FORMAT=$(CFB_FORMAT) -DUSE_RSP=$(USE_RSP) -DSYNC_VIDEO=$(SYNC_VIDEO)

LIBS = -L$(HVQMLIBDIR) -lhvqm2 -L$(ROOT)/usr/lib -lgultra -L$(ROOT)/gcc/mipse/lib -lkmc

#UCODE = $(HVQMUCODEDIR)/hvqm2sp$(CFB_FORMAT).o

NAME = sample

TARGETDIR = .
ROM = $(TARGETDIR)/$(NAME).n64
SYM = $(TARGETDIR)/$(NAME).out

HVQMFILE  = sample.hvqm

SPECFILE = spec

CFILES      = system.c main.c cfbkeep.c getrecord.c timekeeper.c
CODEOBJECTS = $(CFILES:.c=.o)
CODESEGMENT = codesegment.o

DATAFILES   = hvqmwork.c adpcmbuf.c hvqbuf.c pcmbuf.c cfb.c
DATAOBJECTS = $(DATAFILES:.c=.o)

default: $(ROM)

include $(COMMONRULES)

$(ROM): $(CODESEGMENT) $(DATAOBJECTS) $(HVQMFILE) $(SPECFILE) Makefile
	$(MAKEROM) -E -DUSE_RSP=$(USE_RSP) -DHVQMFILE="$(HVQMFILE)" -r $(ROM) -e $(SYM) $(SPECFILE)

$(CODESEGMENT): $(CODEOBJECTS)
	$(LD) -o $(CODESEGMENT) -r $(CODEOBJECTS) $(LIBS)

system.o main.o cfbkeep.o getrecord.o timekeeper.o \
hvqmwork.o adpcmbuf.o hvqbuf.o pcmbuf.o cfb.o :  system.h

main.o timekeeper.o :  timekeeper.h

system.o main.o hvqmwork.o cfb.o :  Makefile

######################################################################
