# 	NuSYSTEM samples nuhvqm Makefile

include $(ROOT)/usr/include/make/PRdefs

# Directory holding the NuSYSTEM include file and library
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

#  Directory holding the HVQM2 library (libhvqm2.a)
HVQMLIBDIR = ../libhvqm2/lib
#  Directory holding the HVQM2 include file
HVQMINCDIR = ../libhvqm2/lib

LCDEFS =	-DNU_DEBUG -DF3DEX_GBI_2
# LCDEFS =	-DNDEBUG -DF3DEX_GBI_2
LCINCS =	-I.  -I$(NUSYSINCDIR) -I$(HVQMLIBDIR) -I$(ROOT)/usr/include/PR
LCOPTS =	-G 0
LDFLAGS = $(MKDEPOPT) -L$(LIB) -L$(NUSYSLIBDIR) -L$(HVQMLIBDIR) -lhvqm2 -lnusys_d -lgultra_d -L$(GCCDIR)/mipse/lib -lkmc
# LDFLAGS = $(MKDEPOPT) -L$(LIB) -L$(NUSYSLIBDIR) -L$(HVQMLIBDIR) -lhvqm2 -lnusys -lgultra_rom -L$(GCCDIR)/mipse/lib -lkmc

OPTIMIZER =	-g

APP =		nuhvqm.out

TARGETS =	nuhvqm.n64

HFILES =	main.h graphic.h hvqm.h

CODEFILES   = 	main.c stage00.c graphic.c gfxinit.c \
		stage01.c hvqmmain.c hvqmaudio.c hvqmgfxinit.c \
		hvqmcopyframebuffer.c

CODEOBJECTS =	$(CODEFILES:.c=.o)  $(NUSYSLIBDIR)/nusys.o

DATAFILES   =	hvqmwork.c hvqmaudiobuf.c hvqmvideobuf.c

DATAOBJECTS =	$(DATAFILES:.c=.o)

CODESEGMENT =	codesegment.o

OBJECTS =	$(CODESEGMENT) $(DATAOBJECTS)


default:        $(TARGETS)

include $(COMMONRULES)

$(CODESEGMENT):	$(CODEOBJECTS) Makefile
		$(LD) -o $(CODESEGMENT) -r $(CODEOBJECTS) $(LDFLAGS)

$(TARGETS):	$(OBJECTS) spec
		$(MAKEROM) spec -I$(NUSYSINCDIR) -r $(TARGETS) -e $(APP)

# Simple depends
$(CODEOBJECTS):	$(HFILES)
$(DATAOBJECTS):	hvqm.h
