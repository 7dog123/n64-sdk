#!smake -k
# --------------------------------------------------------------------
#        Copyright (C) 1997,1998 Nintendo. (Originated by SGI)
#
#        $RCSfile: Makefile.src,v $
#        $Revision: 1.1 $
#        $Date: 1999/01/12 13:28:00 $
# --------------------------------------------------------------------
#
# Makefile for turbo demo application
#

include $(ROOT)/usr/include/make/PRdefs

#FINAL = YES
ifeq ($(FINAL), YES)
OPTIMIZER       = -O2
LCDEFS          =
N64LIB          = -lgultra_rom
else
OPTIMIZER       = -g
LCDEFS          = -DDEBUG
N64LIB          = -lgultra_d
endif

APP =		gtdemo.out

TARGETS =	gtdemo.n64

TEXHFILES =	../../demos/Texture/RGBA16checkerMM.h

HFILES =	gtdemo.h controller.h turbo.h character.h char_data.h 	\
		timer.h walk.h punch.h

CODEFILES   =	gtdemo.c floor.c turbo.c character.c controller.c 	\
		timer.c walk.c punch.c rdp_output.c rdp_output_len.c

CODEOBJECTS =	$(CODEFILES:.c=.o)

DATAFILES   =	static.c zbuffer.c cfb.c

DATAOBJECTS =	$(DATAFILES:.c=.o)

CODESEGMENT =	codesegment.o

OBJECTS =	$(CODESEGMENT) $(DATAOBJECTS)

LCINCS =	-I. -I$(ROOT)/usr/include/PR -I $(ROOT)/usr/include -I../../demos/Texture
LCOPTS =	-G 0
LDIRT  =	$(APP) *.so

#
# Use non debug library just so we have some demos using it to test it
#
LDFLAGS =	$(MKDEPOPT)  -L$(ROOT)/usr/lib -L$(ROOT)/usr/lib/PR $(N64LIB) -L$(GCCDIR)/mipse/lib -lkmc

default:	$(TARGETS)

include $(COMMONRULES)

$(CODESEGMENT):	$(CODEOBJECTS)
		$(LD) -o $(CODESEGMENT) -r $(CODEOBJECTS) $(LDFLAGS)

ifeq ($(FINAL), YES)
$(TARGETS) $(APP):      spec $(OBJECTS)
	$(MAKEROM) -s 9 -r $(TARGETS) -e $(APP) spec
	makemask $(TARGETS)
else
$(TARGETS) $(APP):      spec $(OBJECTS)
	$(MAKEROM) -r $(TARGETS) -e $(APP) spec
endif


# for exeGCC CELF
ifeq ($(GCC_CELF), ON)
ifneq ($(FINAL), YES)
CELFDIR = .
include $(CELFRULES)
$(CODEOBJECTS) $(DATAOBJECTS) :	$(CELFINFOFILES)
endif
endif
