#!smake
include $(ROOT)/usr/include/make/PRdefs

#FINAL = YES

ifeq ($(FINAL), YES)
OPTIMIZER       = -O2
LCDEFS		= -DNDEBUG -D_FINALROM
N64LIB          = -lgultra_rom
else
OPTIMIZER       = -g
LCDEFS          = -DDEBUG
N64LIB          = -lgultra_d
endif

APP =		simple.out

TARGETS =	simple.n64

HFILES =		\
	simple.h	\
	audio.h		\
	gfx.h		\
	misc.h		\
	gfx_tri.h	\
	gfx_vtx.h

CODEFILES =		\
	audio.c		\
	audiomgr.c	\
	controller.c	\
	gfx.c		\
	gfxstack.c	\
	gfxyield.c	\
	misc.c		\
	simple.c

CODEOBJECTS =	$(CODEFILES:.c=.o)

CODESEGMENT =	codesegment.o

# Data files that have thier own segments:

DATAFILES =		\
	gfxdynamic.c	\
	gfxdlists.c	\
	gfxzbuffer.c	\
	gfxinit.c	\
	gfxstatic.c	\
	gfxcfb.c

DATAOBJECTS =	$(DATAFILES:.c=.o)

OBJECTS =	$(CODESEGMENT) $(DATAOBJECTS)

LCINCS =	-I.. -I$(ROOT)/usr/include/PR 
LCOPTS =	$(DFLAG) -G 0
LDFLAGS =	$(MKDEPOPT) -L$(ROOT)/usr/lib $(N64LIB) -L$(GCCDIR)/mipse/lib -lkmc 

LDIRT  =	$(APP)

default:	$(TARGETS)

include $(COMMONRULES)

$(CODESEGMENT):	$(CODEOBJECTS)
		$(LD) -o $(CODESEGMENT) -r $(CODEOBJECTS) $(LDFLAGS)

ifeq ($(FINAL), YES)
$(TARGETS) $(APP):      spec $(OBJECTS)
	$(MAKEROM) -s 9 -r $(TARGETS) spec
	makemask $(TARGETS)
else
$(TARGETS) $(APP):      spec $(OBJECTS)
	$(MAKEROM) -r $(TARGETS) spec
endif

# for exeGCC CELF
ifeq ($(GCC_CELF), ON)
CELFDIR = .
include $(CELFRULES)
$(CODEOBJECTS) $(DATAOBJECTS) :	$(CELFINFOFILES)
endif
