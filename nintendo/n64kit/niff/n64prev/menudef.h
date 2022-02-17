/*======================================================================*/
/*		NIFFprev						*/
/*		menudef.h						*/
/*									*/
/*		Copyright (C) 1997,1998, NINTENDO Co,Ltd.		*/
/*		Copyright (C) 1998, MONEGI CORPORATION.			*/
/*									*/
/*======================================================================*/
/* Revision history							*/
/*  1998/ 6/19	Definition of VIDEO MENU was added. 				*/
/*======================================================================*/
/*----------------------------------------------------------------------
  A file to determine coordinate of menu.
----------------------------------------------------------------------*/
#ifndef __menudef_h
#define __menudef_h

#include "menu.h"

extern MENU gRootMenu;
extern MENU gObjectMenu;
extern MENU gCameraMenu;
extern MENU gControlMenu;
extern MENU gLightMenu;
extern MENU gFogMenu;
extern MENU gBGColorMenu;
extern MENU gAnimMenu;
extern MENU gVideoMenu;

#define ROOT_MENU_POS_X		(5)
#define ROOT_MENU_POS_Y		(3)

#define OBJECT_MENU_POS_X	(13)
#define OBJECT_MENU_POS_Y	(3)

#define CAMERA_MENU_POS_X	(13)
#define CAMERA_MENU_POS_Y	(4)

#define CONTROL_MENU_POS_X	(13)
#define CONTROL_MENU_POS_Y	(5)

#define LIGHT_MENU_POS_X	(13)
#define LIGHT_MENU_POS_Y	(6)

#define FOG_MENU_POS_X		(13)
#define FOG_MENU_POS_Y		(7)

#define BG_COLOR_MENU_POS_X	(13)
#define BG_COLOR_MENU_POS_Y	(8)

#define ANIM_MENU_POS_X		(13)
#define ANIM_MENU_POS_Y		(9)

#define VIDEO_MENU_POS_X	(13)
#define VIDEO_MENU_POS_Y	(10)

#endif /* __menudef_h */
