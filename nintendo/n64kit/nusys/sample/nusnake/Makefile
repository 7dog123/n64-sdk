#
#NuSYSTEM Sample Program "SNAKE TAIL HACK"
#
#Makefile
#
#Copyright (C) 1997, NINTENDO Co,Ltd.

include $(ROOT)/usr/include/make/PRdefs

# The directory which has the include file and library of NuSYSTEM
#

N64KITDIR    = c:\nintendo\n64kit
NUSYSINCDIR  = $(N64KITDIR)/nusys/include
NUSYSLIBDIR  = $(N64KITDIR)/nusys/lib

APP =		nusnake.out

OPTIMIZER =	-g

TARGETS =	nusnake.n64

TEXHFILES =

HFILES =	font.h \
		main.h \
		math.h \
		para.h \
		graphic.h

CODEFILES   = 	font.c \
		gamemain.c \
		gametitle.c \
		gameover.c \
		gamepakerr.c \
		gamepakrwerr.c \
		gfxinit.c \
		graphic.c \
		hitchk.c \
		main.c \
		map.c \
		math.c \
		view.c

CODEOBJECTS =	$(CODEFILES:.c=.o)  $(NUSYSLIBDIR)/nusys.o

DATAFILES   =	movieimg.c

DATAOBJECTS =	$(DATAFILES:.c=.o)

CODESEGMENT =	codesegment.o

OBJECTS =	$(CODESEGMENT) $(DATAOBJECTS)

LCDEFS = -DF3DEX_GBI_2
LCINCS =	-I.  -I$(NUSYSINCDIR)
LCOPTS =	-G 0
LDFLAGS =	$(MKDEPOPT) -L$(ROOT)/usr/lib -L$(NUSYSLIBDIR) -lnualsgi_n_d -lnusys_d  -lgn_audio_d -lgultra_d  -L$(GCCDIR)/mipse/lib -lkmc 

LDIRT  =	$(APP)

default:	$(TARGETS)


include $(COMMONRULES)

$(CODESEGMENT):	$(CODEOBJECTS) Makefile
		$(LD) -o $(CODESEGMENT) -r $(CODEOBJECTS) $(LDFLAGS)

$(TARGETS) $(APP):	spec $(OBJECTS)
		$(MAKEROM)  spec -I$(NUSYSINCDIR) -r $(TARGETS) -e $(APP)
