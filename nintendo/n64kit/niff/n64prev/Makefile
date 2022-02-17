#!smake -k
#=======================================================================#
#		NIFFprev						#
#		Makefile						#
#									#
#		Copyright (C) 1997,1998, NINTENDO Co,Ltd.		#
#		Copyright (C) 1998, MONEGI CORPORATION.			#
#									#
#-----------------------------------------------------------------------#

include $(ROOT)/usr/include/make/PRdefs

# The directory which has the include file and library of NuSYSTEM
#
N64KITDIR    = /usr/local/n64kit
NUSYSINCDIR  = $(N64KITDIR)/nusys/include
NUSYSLIBDIR  = $(N64KITDIR)/nusys/lib

# GBI setting. when use F3DEX2, F3DEX_GBI_2.
GBI =		F3DEX_GBI

APP =		prev

OPTIMIZER =	-g

TARGETS =	rom

CODEFILES   =	main.c malloc.c expad.c gfx.c atan2f.c \
		trckball.c tbmove.c cruise.c \
		ndres.c ndman.c ndeval.c nddisp.c ndstuff.c \
		n64.c premodel.c menu.c mode.c \
		rootmenu.c cameramenu.c lightmenu.c objectmenu.c \
		bgcolormenu.c fogmenu.c controlmenu.c animmenu.c videomenu.c

CODEOBJECTS =	$(CODEFILES:.c=.o) $(NUSYSLIBDIR)/nusys.o

CODESEGMENT =	codesegment.o

OBJECTS =	$(CODESEGMENT)

LCDEFS =	-D$(GBI)

LCINCS =	-I$(NUSYSINCDIR)
LCOPTS =	-fullwarn -wlint,-f -woff 813,819,826,827,852 -non_shared -G 0
#LDFLAGS =	$(MKDEPOPT) -nostdlib -L$(ROOT)/usr/lib -L$(NUSYSLIBDIR) -lnusys_d -lultra_d

LDFLAGS =	$(MKDEPOPT) -nostdlib -L$(ROOT)/usr/lib -L$(NUSYSLIBDIR) -lnusys_d -lultra_rom

LDIRT  =	$(APP)

DEPENDFILE =    dependfile

default:	$(TARGETS)

include $(COMMONRULES)

$(CODESEGMENT):	$(CODEOBJECTS)
	$(LD) -o $(CODESEGMENT) -r $(CODEOBJECTS) $(LDFLAGS)

rom $(APP):	spec $(OBJECTS) $(MAKEROM)
	$(MAKEROM) -D$(GBI) -s 9 -r rom -I$(NUSYSINCDIR) spec
#	makemask rom

#	$(MAKEROM) -D$(GBI) -r rom -I$(NUSYSINCDIR) -m spec | rammap.perl
#	@gnm -B $(APP) | rommap.perl


main.o : model.h

premodel.o : model.c model.h

depend:
	makedepnd -f$(DEPENDFILE) *.c

# DO NOT DELETE
