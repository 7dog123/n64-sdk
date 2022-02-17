#!smake -k
#
# Makefile for  NINTENDO64 SAMPLE PROGRAM 2
#
#	Copyright (C) 1997, NINTENDO Co,Ltd.
#

include $(ROOT)/usr/include/make/PRdefs

#FINAL = YES
ifeq ($(FINAL), YES)
OPTIMIZER       = -O2
LCDEFS          = -DNDEBUG -D_FINALROM -DF3DEX_GBI_2
N64LIB          = -lgultra_rom
else
OPTIMIZER       = -g
LCDEFS          = -DF3DEX_GBI_2 -D_AUDIO_DEBUG
N64LIB          = -lgultra_d
endif

APP =		nnsample2.out

TARGETS =	nnsample2.n64

TEXHFILES =

HFILES =	def.h message.h vram.h nnsched.h segment.h main.h  \
		audio.h graphic.h controller.h far_.h middle_.h near_.h

CODEFILES   = 	boot.c rdp_output.c dram_stack.c \
		main.c message.c nnsched.c main00.c controller.c audio.c \
		graphic.c graphic_00.c gfxyield.c gfxinit.c \
		gfxperfm.c

CODEOBJECTS =	$(CODEFILES:.c=.o)

DATAFILES   =	cfb.c zbuf.c gfxdlistbuf.c lodmodel.c

DATAOBJECTS =	$(DATAFILES:.c=.o)

CODESEGMENT =	codesegment.o

OBJECTS =	$(CODESEGMENT) $(DATAOBJECTS)

LCINCS =	-I.
LCOPTS =	-G 0
LDFLAGS =	$(MKDEPOPT)  -L$(ROOT)/usr/lib $(N64LIB) -L$(GCCDIR)/mipse/lib -lkmc

LDIRT  =	$(APP)

default:	$(TARGETS)

include $(COMMONRULES)

$(CODESEGMENT):	$(CODEOBJECTS)
		$(LD) -o $(CODESEGMENT) -r $(CODEOBJECTS) $(LDFLAGS)

ifeq ($(FINAL), YES)
$(TARGETS) $(APP):      spec $(OBJECTS)
	$(MAKEROM) -r $(TARGETS) -e $(APP) spec
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
