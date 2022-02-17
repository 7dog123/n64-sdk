#!smake -k
#
# Makefile for  NINTENDO64 SAMPLE PROGRAM 1
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
LCDEFS          = -DF3DEX_GBI_2 -D_AUDIO_DEBUG_
N64LIB          = -lgultra_d
endif

APP =		nnsample1.out

TARGETS =	nnsample1.n64

TEXHFILES =

HFILES =	def.h message.h vram.h nnsched.h segment.h main.h  \
		controller.h audio.h graphic.h main01.h cont_finish.h \
		fiter_1s1.h fiter_2s1.h reflect.h

CODEFILES   = 	boot.c rdp_output.c dram_stack.c \
		main.c message.c nnsched.c main00.c controller.c audio.c \
		graphic.c graphic_00.c gfxyield.c gfxinit.c main01.c  \
		graphic_01.c

CODEOBJECTS =	$(CODEFILES:.c=.o)

DATAFILES   =	cfb.c zbuf.c gfxdlistbuf.c fiter_1s1.c  fiter_2s1.c \
		cont_finish.c

DATAOBJECTS =	$(DATAFILES:.c=.o)

CODESEGMENT =	codesegment.o

OBJECTS =	$(CODESEGMENT) $(DATAOBJECTS)

LCINCS =	-I.
LCOPTS =	-G 0
LDFLAGS =	$(MKDEPOPT)  -L$(ROOT)/usr/lib $(N64LIB) -L$(GCCDIR)/mipse/lib -lkmc

LDIRT  =	$(APP)

default:	$(TARGETS)

include $(COMMONRULES)

$(CODESEGMENT):	$(CODEOBJECTS) Makefile
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
