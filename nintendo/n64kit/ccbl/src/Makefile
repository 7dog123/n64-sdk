#
# [CCBL]
# 
# Makefile
# 
# Copyright (C) 1998, NINTENDO Co,Ltd.
# Copyright (C) 1998, MONEGI CORPORATION.
# 
# Makefile (GNU make) for exeGCC environment, PC version 
include $(ROOT)/usr/include/make/PRdefs

N64KIT	= c:/nintendo/n64kit
NSYSINCDIR = $(N64KIT)/nusys/include
NSYSLIBDIR = $(N64KIT)/nusys/lib
NSTDINCDIR = $(N64KIT)/nustd/include
NSTDLIBDIR = $(N64KIT)/nustd/lib

APP =		ccbl.out
DPTEST_ROM = dptest.n64
CCBL_ROM = ccbl.n64
FINAL_ROM = final.n64

# FINAL: ROM CART
# DPTEST: dptest.exe target(ALL TARGET)
# ISVIEWER: IS-VIEWER(NLOAD)
# none:	MSP-A B C(DEBUGGER-N64,partner)
ifdef FINAL
#FINAL ROM
OPTIMIZER =	-O
LCDEFS  =	-DFINAL -DF3DEX_GBI -DRSP_DEBUG
TARGETS =	$(FINAL_ROM)
N64LIB	=	-lnusys_d -lgultra_rom -lnustd -lkmc
DO_MAKEMASK =	1
else
#NOT FINAL ROM
OPTIMIZER =	-g
ifdef DPTEST
##DPTEST TARGET
LCDEFS  =	-DDPTEST -DF3DEX_GBI -DRSP_DEBUG
TARGETS =	$(DPTEST_ROM)
N64LIB	=	./lib/libdptstcmd.a -lnusys_d -lgultra_d -lnustd_d -lkmc
DO_MAKEMASK =	1
else
##debugger
ifdef ISVIEWER
### IS-VIEWER
LCDEFS  =	-DISVIEWER -DDEBUG -DF3DEX_GBI -DRSP_DEBUG
TARGETS = 	$(CCBL_ROM)
N64LIB	=	-lnusys_d -lgultra -lnustd_d -lkmc
else
### 
LCDEFS  =	-DDEBUG -DF3DEX_GBI -DRSP_DEBUG
TARGETS = 	$(CCBL_ROM)
N64LIB	=	-lnusys_d -lgultra_d -lnustd_d -lkmc
endif
endif
endif


CODEFILES =	boot.c \
		mysys.c \
		main.c \
		graphics.c \
		pad.c \
		rcp_reg.c \
		cam.c \
		light.c \
		trackball.c \
		window.c \
		menu.c \
		rsp_menu.c \
		rdp_menu.c \
		bl_menu.c \
		vi_menu.c \
		misc_menu.c \
		cc_macro.c \
		bl_macro.c \
		ccbl_host.c \
		model_load.c \
		window_out.c \
		model_out.c

CODEOBJECTS =	$(CODEFILES:.c=.o)
CODESEGMENT =	codesegment.o

MODELFILES =	bg_image.c \
		bg_model.c \
		texture.c
MODELOBJECTS =	$(MODELFILES:.c=.o)
MODELSEGMENT =	modelsegment.o


STATICFILES =	
STATICOBJECTS =	$(STATICFILES:.c=.o)
STATICSEGMENT =	

DATAFILES =	
DATAOBJECTS =	$(DATAFILES:.c=.o)


OBJECTS =	$(CODESEGMENT) $(MODELSEGMENT) heap.o \
		tetra.o cube.o sphere.o xy_yz.o grid.o tri.o text.o \
		mizo.o torus2.o

MAPFILE =	load.map

LCINCS  =	-I. -I$(ROOT)/usr/include/PR -I$(NSYSINCDIR) -I$(NSTDINCDIR) \
		-I$(ROOT)/gcc/mipse/include

LCOPTS  =	-G 0


LDIRT   =	$(APP) $(CCBL_ROM) $(DPTEST_ROM) $(FINAL_ROM) $(MAPFILE)

LDFLAGS =	$(MKDEPOPT) -L$(ROOT)/usr/lib \
		-u sprintf \
		-L$(NSYSLIBDIR) -L$(NSTDLIBDIR) -L$(GCCDIR)/mipse/lib \
		$(N64LIB)



default:	$(TARGETS)

include $(COMMONRULES)

install:	default

$(CODESEGMENT):	$(CODEOBJECTS)
		$(LD) -o $(CODESEGMENT) -r $(CODEOBJECTS) $(LDFLAGS)

$(STATICSEGMENT): $(STATICOBJECTS)
		$(LD) -o $(STATICSEGMENT) -r $(STATICOBJECTS) $(LDFLAGS)

$(MODELSEGMENT): $(MODELOBJECTS)
		$(LD) -o $(MODELSEGMENT) -r $(MODELOBJECTS)

#$(HEAPSEGMENT): $(HEAPOBJECTS)
#		$(LD) -o $(HEAPSEGMENT) -r (HEAPOBJECTS)


ifndef DO_MAKEMASK
$(TARGETS):	spec $(OBJECTS) $(RAWDATAS)
		$(MAKEROM) $(LCDEFS) $(LCINCS) -o -s 9 -r $(TARGETS) spec
else
$(TARGETS):	spec $(OBJECTS) $(RAWDATAS)
		$(MAKEROM) $(LCDEFS) $(LCINCS) -o -s 9 -r $(TARGETS) spec
		makemask $(TARGETS)
endif

# for exeGCC CELF
ifeq ($(GCC_CELF), ON)
CELFDIR = .
include $(CELFRULES)
$(OBJECTS):	$(CELFINFOFILES)
endif

#======== End of Makefile ========
# DO NOT DELETE

