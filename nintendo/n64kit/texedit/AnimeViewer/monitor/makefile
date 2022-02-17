# 	NuSYSTEM Anime Viewer Makefile

include $(ROOT)/usr/include/make/PRdefs

# The directory which has the include file and library of NuSYSTEM
#

N64KITDIR	= c:\nintendo\n64kit
NUSYSINCDIR  = $(N64KITDIR)/nusys/include
NUSYSLIBDIR  = $(N64KITDIR)/nusys/lib

#DEBUG  = -DDEBUG

LIB = $(ROOT)/usr/lib
LPR = $(LIB)/PR
INC = $(ROOT)/usr/include
CC  = gcc
LD  = ld
MAKEROM = mild

LCDEFS =	-DNU_DEBUG -DF3DEX_GBI_2
LCINCS =	-I. -I$(NUSYSINCDIR) -I$(ROOT)/usr/include/PR
LCOPTS =	-G 0
LDFLAGS = $(MKDEPOPT) -L$(LIB) -L$(NUSYSLIBDIR) -lnusys_d -lgultra_d -L$(GCCDIR)/mipse/lib -lkmc

OPTIMIZER =	-g

.PHONY:	animation clean

.SUFFIXES:	$(SUFFIXES) .taf

APP =		anmview.out

TARGETS =	anmview.n64

HFILES =	main.h graphic.h teapi.h anmview.h anmdata.h

CODEFILES   = 	main.c stage00.c stage01.c graphic.c gfxinit.c teapi.c anmview.o

CODEOBJECTS =	$(CODEFILES:.c=.o)  $(NUSYSLIBDIR)/nusys.o

DATAFILES   =	anmdata.c

DATAOBJECTS =	$(DATAFILES:.c=.o)

CODESEGMENT =	codesegment.o

OBJECTS =	$(CODESEGMENT)

#LDFLAGS = $(MKDEPOPT) -L$(LIB) -L$(NUSYSLIBDIR) -lnusys_d -lgultra_d -L$(GCCDIR)/mipse/lib -lkmc

default:        animation

$(CODESEGMENT):	$(CODEOBJECTS) $(DATAOBJECTS) Makefile
		$(LD) -o $(CODESEGMENT) -r $(CODEOBJECTS) $(DATAOBJECTS) $(LDFLAGS)

$(TARGETS):	$(OBJECTS)
		$(MAKEROM) spec -I$(NUSYSINCDIR) -r $(TARGETS) -e $(APP)

anmdata.c anmdata.h:	anmview.taf
		./anmview.exe $< -o anmdata.c -e anmdata.h

clean::
		@-del *.BAK
		@-del *.o
		@-del *.out
		@-del $(TARGETS)

animation::	$(TARGETS)
		./nload.exe -n $(TARGETS)

