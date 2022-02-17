N64KITDIR	= c:\nintendo\n64kit
NUSYSINCDIR	= $(N64KITDIR)\nusys\include
NUSYSLIBDIR	= $(N64KITDIR)\nusys\lib

N64GCC_PATH = $(ROOT)\gcc\mipse
N64GCC_BIN	= $(N64GCC_PATH)\bin
N64GCC_INC	= $(ROOT)\usr\include
CC			= $(N64GCC_BIN)\gcc
AS			= $(N64GCC_BIN)\as
LD			= $(N64GCC_BIN)\ld
MAKEROM		= mild

APP			= texv.out

.c.o:
		$(CC) -g -G O -c $(CC_INC) $(CC_DEF) $<

CC_INC		= -I. -I$(N64GCC_INC)\pr -I$(N64GCC_INC) -I$(NUSYSINCDIR)
CC_DEF		= -DF3DEX_GBI -D_WIN32 -D_LANGUAGE_C -D_MIPS_SZLONG=32 -D_MIPS_SZINT=32

OPTIMIZER	= -g

TARGETS		= texv.N64

CODEFILES	= main.c gfx.c game.c mesh.c bg.c letters.c menu.c

DATAOBJECTS	= $(CODEFILES:.c=.o)
CODEOBJECTS	= $(DATAOBJECTS) $(NUSYSLIBDIR)\nusys.o

CODESEGMENT	= codesegment.o

OBJECTS		= $(CODESEGMENT) $(DATAOBJECTS)

LDFLAGS		= $(MKDEPOPT) -L$(ROOT)/usr/lib -L$(NUSYSLIBDIR)	\
				-lnusys_d -lgultra_d -L$(GCCDIR)/mipse/lib -lkmc
DEPENDFILE	= dependfile

default:	$(TARGETS)

clean:
		del *.o
		del *.n64
		del *.out

$(CODESEGMENT) :	$(DATAOBJECTS)
	$(LD) -o $(CODESEGMENT) -r $(CODEOBJECTS) $(LDFLAGS)

$(TARGETS) :	spec $(OBJECTS)
	$(MAKEROM) -s 9 spec -r $(TARGETS) -I$(NUSYSINCDIR) -e $(APP) -m >texv.map
	makemask $(TARGETS)

depend:
	makedepnd -f$(DEPENDFILE) *.c


