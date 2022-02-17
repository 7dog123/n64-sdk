/*
 *	game.h
 *
 *	manages operation and drawing
 *
 *  Copyright (C) 1998-1999, NINTENDO Co.,Ltd.
 *  Copyright (C) 1998-1999, MONEGI CORPORATION
 */

#ifndef	_GAME
#define	_GAME

#include	"main.h"

#define	MESH_CONT_START_POSITION	R_TRIG
#define	MESH_CONT_MENU_ONOFF		START_BUTTON
#define	MESH_CONT_NAME_DISP_CHANGE	L_TRIG

/*************************************************************************
 *				extern functions in letters.c
 ************************************************************************/
extern	Gfx *letters_init( Gfx *gp );
extern	Gfx *letters_1_letter(Gfx *gp,short,short,unsigned char,u32);
extern	Gfx *letters_set(Gfx *gp,short,short,unsigned char *letter,u32);
extern	Gfx *letters_num( Gfx *gp,short,short,int,u32);
extern	Gfx *letters_num_right( Gfx *gp,short,short,int,u32);
extern	char	i2a(int,char *output);

extern	unsigned char	letter[];


/*************************************************************************
 *				functions
 ************************************************************************/
void	game(int);
Gfx 	*makedisplaylist(Gfx *gp,int);
void	view_stickcontrol(void);
Gfx		*disp_info(Gfx *gp);

Gfx		*DispMenu(Gfx *gp);
void	init_modedata();
void	menu_stickcontrol(void);

Gfx		*disp_square(Gfx *gp,short,short,short,short,u32);
Gfx		*disp_cursor(Gfx *gp);

#endif	/* _GAME */
