#!smake -k
# 	NuSYSTEM samples nuhvq Makefile

include $(ROOT)\usr\include\make\PRdefs

# Directory holding NuSYSTEM include file and library
#
N64KITDIR    = c:\nintendo\n64kit
NUSYSINCDIR  = $(N64KITDIR)/nusys/include
NUSYSLIBDIR  = $(N64KITDIR)/nusys/lib
LIB = $(ROOT)/usr/lib
#  Directory holding the HVQ2 library  (libhvq.a)
HVQLIBDIR = ..\libhvq2\lib
#  Directory holding the HVQ2 include file
HVQINCDIR = ../libhvq2/lib
#  Directory holding the HVQ2 microcode
HVQUCODEDIR = ..\libhvq2\rspcode
# If you are using the old audio microcode please
# comment this out
N_AUDIO = yes

#ifdef N_AUDIO
NUAUDIOLIB = -lnualstl_n_d -ln_gmus_d -ln_gaudio_sc
#else
NUAUDIOLIB = -lnualstl_d -lgmus_d
#endif
#  Maximum size of image [pixel]  (Reflects on the memory reserved for hvqwork.c)
MAXWIDTH  = 320
MAXHEIGHT = 240
APP =		nuhvq.out

#OPTIMIZER =	-g

TARGETS =	nuhvq.n64

HFILES =	main.h

CODEFILES   = 	main.c stage00.c appgfxinit.c

CODEOBJECTS =	$(CODEFILES:.c=.o)  $(NUSYSLIBDIR)\nusys.o

DATAFILES   =	hvqwork.c hvqbuf.c hvqimg.c

DATAOBJECTS =	$(DATAFILES:.c=.o)

CODESEGMENT =	codesegment.o

OBJECTS =	$(CODESEGMENT) $(DATAOBJECTS)

LCDEFS =  -DMAXWIDTH=$(MAXWIDTH) -DMAXHEIGHT=$(MAXHEIGHT) 

LCINCS =	-I. -I$(HVQINCDIR) -I$(NUSYSINCDIR) -I$(ROOT)/usr/include/PR
LCOPTS =	-G 0
LDFLAGS =	$(MKDEPOPT) -L$(LIB) -L$(NUSYSLIBDIR) $(NUAUDIOLIB) -lnusys_d -lgultra_d -L$(GCCDIR)/mipse/lib -lkmc -L$(HVQLIBDIR) -lhvq2
LDIRT  =	$(APP)

default:	$(TARGETS)

include $(COMMONRULES)

$(CODESEGMENT):	$(CODEOBJECTS) Makefile
		$(LD) -o $(CODESEGMENT) -r $(CODEOBJECTS) $(LDFLAGS)

$(TARGETS) $(APP):	spec $(OBJECTS)
		$(MAKEROM)  spec  -I$(NUSYSINCDIR) -r $(TARGETS) -e $(APP)
