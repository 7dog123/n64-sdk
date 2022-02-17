#!smake
#SGI Platform Makefile
include $(ROOT)/usr/include/make/PRdefs

N64KIT	= /usr/local/n64kit
NSYSINCDIR = $(N64KIT)/nusys/include
NSYSLIBDIR = $(N64KIT)/nusys/lib
NSTDINCDIR = $(N64KIT)/nustd/include
NSTDLIBDIR = $(N64KIT)/nustd/lib

LCDEFS  =	-DF3DEX_GBI

TARGETS  =	user_model

MODELFILE = 	dummy.c model.c

MODELOBJECT =	$(MODELFILE:.c=.o)

OBJECTS =	$(MODELOBJECT)

MAPFILE =	load.map

LCINCS  =	-I../.. -I. -I$(ROOT)/usr/include/PR -I$(NSYSINCDIR) -I$(NSTDINCDIR)

LCOPTS  =	-fullwarn -wlint,-f -woff 813,819,826,827,852 \
		-non_shared -G 0 -Xcpluscomm


LDIRT   =	*~ Makedepend tuncate user_model dummy

default:	$(TARGETS)

include $(COMMONRULES)

install:	default

$(TARGETS):	spec $(OBJECTS) truncate.c
		$(MAKEROM) $(LCDEFS) $(LCINCS) -o -m -r $(TARGETS) spec
		$(CC) -o truncate truncate.c
		truncate

#======== End of Makefile ========
# DO NOT DELETE

