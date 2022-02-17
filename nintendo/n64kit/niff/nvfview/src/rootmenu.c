/*
  nvfview
  rootmenu.h
    Copyright (C) 1998, NINTENDO Co,Ltd., MONEGI CORPORATION.
    Dec. 14, 1998.
*/

/*----------------------------------------------------------------------
  Definition of root menu
    Not a single function. Menu and data of items only.
    The name of the root menu is gRootMenu.
    Menu structure
      [OBJECT] ----> gObjectMenu 
      [CAMERA] ----> gCameraMenu 
      [FOG] -------> gFogMenu 
      [BG COLOR] --> gBGColorMenu
      [ANIMATION] -> gAnimMenu 
      [VIDEO] -----> gVideoMenu 
      [ICON] ------> gIconMenu 
      [EXIT] ------> close this menu
----------------------------------------------------------------------*/

#include "pack.h"
#include "menu.h"
#include "nusys.h"
#include "menudef.h"

static MENU_DEF_LINK_ITEM( root_menu_object, "OBJECT", gObjectMenu );
static MENU_DEF_LINK_ITEM( root_menu_camera, "CAMERA", gCameraMenu );
static MENU_DEF_LINK_ITEM( root_menu_fog, "FOG", gFogMenu );
static MENU_DEF_LINK_ITEM( root_menu_bg_color, "BG COLOR", gBGColorMenu );
static MENU_DEF_LINK_ITEM( root_menu_animation, "ANIMATION", gAnimMenu );
static MENU_DEF_LINK_ITEM( root_menu_video, "VIDEO", gVideoMenu );
static MENU_DEF_LINK_ITEM( root_menu_icon, "ICON", gIconMenu );
static MENU_DEF_EXIT_ITEM( root_menu_exit, "EXIT" );

static MENU_ITEM *root_menu_item_list[ ] = {
    &root_menu_object,
    &root_menu_camera,
    &root_menu_fog,
    &root_menu_bg_color,
    &root_menu_animation,
    &root_menu_video,
    &root_menu_icon,
    &root_menu_exit
};

MENU_DEF_MENU( gRootMenu, NULL, ROOT_MENU_POS_X, ROOT_MENU_POS_Y,
	       root_menu_item_list );
