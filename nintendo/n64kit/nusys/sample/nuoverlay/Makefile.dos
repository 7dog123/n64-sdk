# 	NuSYSTEM samples nuoverlay Makefile
#       Copyright (C) 1997-1999, NINTENDO Co,Ltd.

include $(ROOT)/usr/include/make/PRdefs

# The directory which has the include file and library of NuSYSTEM
#
N64KITDIR    = c:\nintendo\n64kit
NUSYSINCDIR  = $(N64KITDIR)/nusys/include
NUSYSLIBDIR  = $(N64KITDIR)/nusys/lib

LIB = $(ROOT)/usr/lib
LPR = $(LIB)/PR
INC = $(ROOT)/usr/include
CC  = gcc
LD  = ld
MAKEROM = mild

NUAUDIOLIB = -lnualsgi_n_d -lgn_audio_d

LCDEFS =	-DNU_DEBUG -DF3DEX_GBI_2
LCINCS =	-I. -I$(NUSYSINCDIR) -I$(ROOT)/usr/include/PR
LCOPTS =	-G 0
LDFLAGS =	$(MKDEPOPT) -L$(LIB) -L$(NUSYSLIBDIR) $(NUAUDIOLIB) -lnusys_d -lgultra_d -L$(GCCDIR)/mipse/lib -lkmc

OPTIMIZER =	-g

APP =		nuoverlay.out

TARGETS =	nuoverlay.n64

HFILES =	main.h graphic.h segment.h

CODEFILES   = 	main.c graphic.c gfxinit.c

CODEOBJECTS =	$(CODEFILES:.c=.o)  $(NUSYSLIBDIR)/nusys.o

STAGE00FILES	= stage00.c

STAGE00OBJECTS	= $(STAGE00FILES:.c=.o)

STAGE01FILES	= stage01.c

STAGE01OBJECTS	= $(STAGE01FILES:.c=.o)

DATAFILES   =	

DATAOBJECTS =	$(DATAFILES:.c=.o)

CODESEGMENT =	codesegment.o

OBJECTS =	$(CODESEGMENT) $(DATAOBJECTS)

FORCELINK =	-u guOrtho \
		-u guRotate \
		-u guTranslate \
		-u nuContDataGetEx \
		-u nuDebConCPuts \
		-u nuDebConDispEX2 \
		-u nuDebConTextPos \
		-u nuDebTaskPerfBar0EX2 \
		-u sprintf

default:        $(TARGETS)

include $(COMMONRULES)

$(CODESEGMENT):	$(CODEOBJECTS) Makefile
		$(LD) $(FORCELINK) -o $(CODESEGMENT) -r $(CODEOBJECTS) $(LDFLAGS)

$(TARGETS):	$(OBJECTS) $(STAGE00OBJECTS) $(STAGE01OBJECTS)
		$(MAKEROM) spec -I$(NUSYSINCDIR) -r $(TARGETS) -e $(APP)
