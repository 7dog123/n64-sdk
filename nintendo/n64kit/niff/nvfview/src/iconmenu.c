/*
  nvfview
  iconmenu.c
    Copyright (C) 1998, NINTENDO Co,Ltd., MONEGI CORPORATION.
    Dec. 14, 1998.
*/

/*----------------------------------------------------------------------
  Definition of ICON Menu
    Not many functions. Menu and data of items only.
    The name of ICON menu is gIconMenu.
    Menu structure
      [OFF]/[ON] ----------> Switch display object
      [EXIT] --------------> Close this menu
----------------------------------------------------------------------*/

#include "pack.h"
#include "menu.h"
#include "mode.h"
#include "nusys.h"
#include "menudef.h"

static char *on_off[ ] = { "OFF", "ON " };
static char icon_label_on_off[ ] = "OFF";
static MENU_DEF_SWITCH_ITEM( icon_menu_on_off, &gMode.icon_visibility,
			     icon_label_on_off, on_off );

static MENU_DEF_EXIT_ITEM( icon_menu_exit, "EXIT" );

static MENU_ITEM *icon_menu_item_list[ ] = {
    &icon_menu_on_off.base,
    &icon_menu_exit
};

MENU_DEF_MENU( gIconMenu, &gRootMenu, ICON_MENU_POS_X, ICON_MENU_POS_Y,
	       icon_menu_item_list );
