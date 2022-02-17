/*======================================================================*/
/*		NIFFprev						*/
/*		rootmenu.c						*/
/*									*/
/*		Copyright (C) 1997,1998, NINTENDO Co,Ltd.		*/
/*		Copyright (C) 1998, MONEGI CORPORATION.			*/
/*									*/
/*======================================================================*/
/* Revision history							*/
/*  1998/ 6/ 4	Changed so FOG MENU can be called. 			*/
/*  1998/ 6/ 9	Changed so ANIMATION MENU can be called. 		*/
/*  1998/ 6/10	Changed so CONTROL MENU can be called.			*/
/*  1998/ 6/16	Changed so MENU definition macro can be used.		*/
/*  1998/ 6/19	Changed so VIDEO MENU can be called. 			*/
/*======================================================================*/
/*----------------------------------------------------------------------
  Definition of root menu
    Not a single function. Menu and data of items only.  
  The name of the root menu is gRootMenu.
    Menu structure
      [OBJECT] ----> to gObjectMenu  
      [CAMERA] ----> to gCameraMenu  
      [CONTROL] ---> to gControlMenu  
      [LIGHT] -----> to gLightMenu  
      [FOG] -------> to gFogMenu  
      [BG COLOR] --> to gBGColorMenu  
      [ANIMATION] -> to gAnimMenu  
      [VIDEO] -----> to gVideoMenu  
      [EXIT] ------> close this menu
----------------------------------------------------------------------*/

#include "pack.h"
#include "menu.h"
#include "nusys.h"
#include "menudef.h"

static MENU_DEF_LINK_ITEM( root_menu_object, "OBJECT", gObjectMenu );
static MENU_DEF_LINK_ITEM( root_menu_camera, "CAMERA", gCameraMenu );
static MENU_DEF_LINK_ITEM( root_menu_light, "LIGHT", gLightMenu );
static MENU_DEF_LINK_ITEM( root_menu_bg_color, "BG COLOR", gBGColorMenu );
static MENU_DEF_LINK_ITEM( root_menu_fog, "FOG", gFogMenu );
static MENU_DEF_LINK_ITEM( root_menu_control, "CONTROL", gControlMenu );
static MENU_DEF_LINK_ITEM( root_menu_animation, "ANIMATION", gAnimMenu );
static MENU_DEF_LINK_ITEM( root_menu_video, "VIDEO", gVideoMenu );
static MENU_DEF_EXIT_ITEM( root_menu_exit, "EXIT" );

static MENU_ITEM *root_menu_item_list[ ] = {
    &root_menu_object,
    &root_menu_camera,
    &root_menu_control,
    &root_menu_light,
    &root_menu_fog,
    &root_menu_bg_color,
    &root_menu_animation,
    &root_menu_video,
    &root_menu_exit
};

MENU_DEF_MENU( gRootMenu, NULL, ROOT_MENU_POS_X, ROOT_MENU_POS_Y,
	       root_menu_item_list );
