/*
  nvfview
  bgcolormenu.c
    Copyright (C) 1998, NINTENDO Co,Ltd., MONEGI CORPORATION.
    Dec. 14, 1998.
*/

/*----------------------------------------------------------------------
  Definition of BG COLOR menu
    Not many functions. Menu and data of items only.
    The name of BG COLOR menu is gBGColorMenu.
    Menu structure
      [R] ---------> Sets R brightness.
      [G] ---------> Sets G brightness.
      [B] ---------> Sets B brightness.
      [RESET] -----> Resets parameter.
      [EXIT] ------> Closes this menu.

    R, G, & items can increase and decrease numeric values useing<-- --> within the range of 0 - 255.
----------------------------------------------------------------------*/

#include "pack.h"
#include "menu.h"
#include "mode.h"
#include "nusys.h"
#include "menudef.h"

static MENU *reset_bg_color( MENU *menu, MENU_ITEM *menu_item, void *option )
{
    ( void )menu_item;
    ( void )option;
    modeResetBG( &gMode );
    return menu;
}

static char bg_color_label_r[ ] = "R    ";
static MENU_DEF_VALUE_ITEM( bg_color_menu_r, ( int * )&gMode.bg_color.rgba.r,
			    0, 255, bg_color_label_r, "R %3d" );

static char bg_color_label_g[ ] = "G    ";
static MENU_DEF_VALUE_ITEM( bg_color_menu_g, ( int * )&gMode.bg_color.rgba.g,
			    0, 255, bg_color_label_g, "G %3d" );

static char bg_color_label_b[ ] = "B    ";
static MENU_DEF_VALUE_ITEM( bg_color_menu_b, ( int * )&gMode.bg_color.rgba.b,
			    0, 255, bg_color_label_b, "B %3d" );

static MENU_ITEM bg_color_menu_reset = {
    "RESET",
    &bg_color_menu_reset,
    NULL,
    menuItemSetupLabel,
    menuItemNoAction,
    menuItemNoAction,
    reset_bg_color
};

static MENU_DEF_EXIT_ITEM( bg_color_menu_exit, "EXIT" );

static MENU_ITEM *bg_color_menu_item_list[ ] = {
    &bg_color_menu_r.base,
    &bg_color_menu_g.base,
    &bg_color_menu_b.base,
    &bg_color_menu_reset,
    &bg_color_menu_exit
};

MENU_DEF_MENU( gBGColorMenu, &gRootMenu,
	       BG_COLOR_MENU_POS_X, BG_COLOR_MENU_POS_Y,
	       bg_color_menu_item_list );
