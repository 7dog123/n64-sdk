# TextureEditor Preview Plug-In's Monitor Makefile
# modified from
# 	NuSYSTEM samples nu2 Makefile
#   Notice: <<<...>>> is same comment in Japanese (SHIFT JIS code).

include $(ROOT)/usr/include/make/PRdefs

# NuSYSTEM directories containing the include file and the library
# <<< NuSYSTEM のインクルードファイルとライブラリが存在するディレクトリ >>>
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

LCDEFS =	-DNU_DEBUG -DF3DEX_GBI_2
LCINCS =	-I. -I$(NUSYSINCDIR) -I$(ROOT)/usr/include/PR
LCOPTS =	-G 0
LDFLAGS = $(MKDEPOPT) -L$(LIB) -L$(NUSYSLIBDIR) -lnusys_d -lgultra_d -L$(GCCDIR)/mipse/lib -lkmc

#OPTIMIZER =	-g
OPTIMIZER =	-O

.PHONY:	debug_install install clean

APP =		nu2.out

TARGETS =	preview.n64

HFILES =	main.h graphic.h teapi.h

CODEFILES   = 	main.c stage00.c stage01.c graphic.c gfxinit.c teapi.c

CODEOBJECTS =	$(CODEFILES:.c=.o)  $(NUSYSLIBDIR)/nusys.o

DATAFILES   =	

DATAOBJECTS =	$(DATAFILES:.c=.o)

CODESEGMENT =	codesegment.o

OBJECTS =	$(CODESEGMENT) $(DATAOBJECTS)

default: $(TARGETS)

$(CODESEGMENT):	$(CODEOBJECTS) $(DATAOBJECTS) Makefile
		$(LD) -o $(CODESEGMENT) -r $(CODEOBJECTS) $(DATAOBJECTS) $(LDFLAGS)

$(TARGETS):	$(OBJECTS)
		$(MAKEROM) spec -I$(NUSYSINCDIR) -r $(TARGETS) -e $(APP)
		makemask $@

debug_install:	$(TARGETS)
		cp $(TARGETS) ../../Debug/PlugIns

install:	$(TARGETS)
		cp $(TARGETS) ../../Release/PlugIns

clean:
		rm -f *.o *.bak *.out $(TARGETS)

