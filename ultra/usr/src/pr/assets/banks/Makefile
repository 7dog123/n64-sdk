#!smake
#
# Makefile for audio library
#
include $(ROOT)/usr/include/make/PRdefs

TARGETS= $(BANKFILES) $(TABLEFILES)

INSTFILES = GenMidi44k.inst GenMidiBank.inst GenMidiRaw.inst imp.inst tone.inst sfx.inst

BANKFILES=$(INSTFILES:.inst=.ctl)
TABLEFILES=$(INSTFILES:.inst=.tbl)
SYMFILES=$(INSTFILES:.inst=.sym)

LDIRT=$(SYMFILES)

default: $(TARGETS) $(SYMFILES)

include $(COMMONRULES)

banks: $(BANKFILES)

exports: default
	$(INSTALL) -F /usr/lib/PR/soundbanks $(TARGETS)

install: default
	$(INSTALL) -m 444 -F /usr/lib/PR/soundbanks $(TARGETS) $(SYMFILES)
	$(INSTALL) -m 444 -F /usr/src/PR/assets/banks $(INSTFILES) Makefile

.NOTPARALLEL:

.SUFFIXES: .inst .ctl .tbl .sym

.inst.ctl:
	$(IC) -o $* $<

.inst.tbl:
	$(IC) -o $* $<

.inst.sym:
	$(IC) -o $* $<
