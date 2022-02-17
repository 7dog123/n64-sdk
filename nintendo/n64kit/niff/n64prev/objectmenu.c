/*======================================================================*/
/*		NIFFprev						*/
/*		rootmenu.c						*/
/*									*/
/*		Copyright (C) 1997,1998, NINTENDO Co,Ltd.		*/
/*		Copyright (C) 1998, MONEGI CORPORATION.			*/
/*									*/
/*======================================================================*/
/* Revision history							*/
/*  1998/ 6/19	Added RESET function					*/
/*======================================================================*/
/*----------------------------------------------------------------------
  Definition of OBJECT menu
    Not many functions. Menu and data of items only.
    The name of OBJECT menu is gObjectMenu.
    Menu structure
      [NINTENDO]/[SCENE] --> Switches display object
      [RESET] -------------> Resets parameter
      [EXIT] --------------> Closes this menu
----------------------------------------------------------------------*/

#include "pack.h"
#include "menu.h"
#include "mode.h"
#include "nusys.h"
#include "menudef.h"
#include "cruise.h"

static MENU *reset_object( MENU *menu, MENU_ITEM *menu_item, void *option )
{
    ( void )menu_item;
    ( void )option;
    modeResetObject( &gMode );
    if ( ( gMode.control_mode == CONTROL_MODE_CRUISE )&&
	 ( gMode.control == CONTROL_OBJECT ) )
    {
	crSetupYPR( &gMode.object_transform );
    }
    return menu;
}

static char *object_name[ ] = { "NINTENDO", "SCENE   " };
static char object_label_object[ ] = "NINTENDO";
static MENU_DEF_SWITCH_ITEM( object_menu_object, &gMode.active_object,
			     object_label_object, object_name );

static MENU_ITEM object_menu_reset = {
    "RESET",
    &object_menu_reset,
    NULL,
    menuItemSetupLabel,
    menuItemNoAction,
    menuItemNoAction,
    reset_object
};

static MENU_DEF_EXIT_ITEM( object_menu_exit, "EXIT" );

static MENU_ITEM *object_menu_item_list[ ] = {
    &object_menu_object.base,
    &object_menu_reset,
    &object_menu_exit
};

MENU_DEF_MENU( gObjectMenu, &gRootMenu, OBJECT_MENU_POS_X, OBJECT_MENU_POS_Y,
	       object_menu_item_list );
