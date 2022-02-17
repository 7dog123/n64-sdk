Copyright (C) 1998, 1999 NINTENDO Co,Ltd.
Copyright (C) 1998, 1999 MONEGI CORPORATION.

This document describes how to build ccbl.  For information on its operation, 
see doc/ccbl.html.

[Revision History]

1999/08/04
Deleted is_debug.c and is_debug.h to conform with OS 2.0K.

[Operating System]

N64 OS2.0I + patch5 (or later) and NuSYSTEM ver.1.20 (or later) are required. 
Please install these before building ccbl. Although it is likely ccbl also can 
be built in other environments, this has not been verified. 
		
[Targets]

ccbl supports a great number of debugging targets. 
A rom file for a particular target can be created simply by changing the 
options used with make.

	<SGI Platform>

		emulator board(INDY)
		IS-VIEWER
		ROM CART

	<PC Platform>

		MSP-A B C
		PARTNER-N64
		IS-VIEWER
		ROM CART		

[Build]

1.  Modify the N64KIT variable at the beginning of the makefile to suit the 
    environment.

2. % make

[make Options and the rom File]

Relation between the options used with make when performing a build and	the rom 
file: 

	<SGI Platform>

	% make			->	rom
	% make ISVIEWER=	->	rom
	% make FINAL=		->	final,final.rom(makemask)

	final.rom is final with makemask applied.	

	<PC Platform>

	> make			->	ccbl.n64
	> make ISVIEWER=1	->	ccbl.n64
	> make FINAL=1	->	final.n64(makemask)
	> make DPTEST=1	->	dptest.n64(makemask)

	dptest.n64 is started by dptest.exe. 
