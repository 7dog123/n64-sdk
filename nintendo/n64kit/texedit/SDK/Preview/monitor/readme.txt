This directory includes preview program for TextureEditor
that modified from nu2 sample of NuSYSTEM.

[nu2 original sample files]

main.c		main routin/bone of game process

main.h		declare variable instance for main.c

stage00.c	create DL(Display List) for stage 0 and display and game process
			(modified for preview)

stage01.c	create DL for stage 1 and display and game process

graphic.h	declare for graphics libraries.

graphic.c	graphics libraries.

gfxinit.c	static display list for RSP/RDP initialize.

spec		spec file for makerom

[added for preview]

teapi.h		declare functions and variable instance for interface of TextureEditor.

teapi.c		TextureEditor preview program.
			* If you add menus, see teMenuPages and teMenuItem.
			* If you added own menus then you must add 2 functions to teMenuPages.
			  see teMenu_ctrlValue() and teMenu_drawValues() please.

