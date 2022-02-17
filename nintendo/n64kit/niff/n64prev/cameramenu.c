/*======================================================================*/
/*		NIFFprev						*/
/*		cameramenu.c						*/
/*									*/
/*		Copyright (C) 1997,1998, NINTENDO Co,Ltd.		*/
/*		Copyright (C) 1998, MONEGI CORPORATION.			*/
/*									*/
/*======================================================================*/
/* Revision history							*/
/*  1998/ 6/18	Moved switching of TRACKBALL/CRUISE to CONTROL menu 	*/
/*  1998/ 6/19	Added RESET function.					*/
/*======================================================================*/
/*----------------------------------------------------------------------
  Definition of CAMERA menu
    Not many functions.  Menu and data of items only.
    The name of CAMERA menu is gCameraMenu.
    Menu structure
      [CONTROL]/[SCENE] -----> Controls by controller/scene camera.
      [RESET] ---------------> Resets parameter.
      [EXIT] ----------------> Closes this menu.
----------------------------------------------------------------------*/

#include "pack.h"
#include "menu.h"
#include "mode.h"
#include "nusys.h"
#include "menudef.h"
#include "cruise.h"

static MENU *reset_camera( MENU *menu, MENU_ITEM *menu_item, void *option )
{
    ( void )menu_item;
    ( void )option;
    modeResetCamera( &gMode );
    if ( ( gMode.control_mode == CONTROL_MODE_CRUISE )&&
	 ( gMode.control == CONTROL_CAMERA ) )
    {
	crSetupYPR( &gMode.camera_transform );
    }
    return menu;
}

static char *camera_mode[ ] = { "CONTROL", "SCENE  " };
static char camera_label_mode[ ] = "CONTROL";
static MENU_DEF_SWITCH_ITEM( camera_menu_mode, &gMode.camera_mode,
			     camera_label_mode, camera_mode );

static MENU_ITEM camera_menu_reset = {
    "RESET",
    &camera_menu_reset,
    NULL,
    menuItemSetupLabel,
    menuItemNoAction,
    menuItemNoAction,
    reset_camera
};

static MENU_DEF_EXIT_ITEM( camera_menu_exit, "EXIT" );

static MENU_ITEM *camera_menu_item_list[ ] = {
    &camera_menu_mode.base,
    &camera_menu_reset,
    &camera_menu_exit
};

MENU gCameraMenu = {
    CAMERA_MENU_POS_X, CAMERA_MENU_POS_Y,
    sizeof( camera_menu_item_list ) / sizeof( MENU_ITEM * ),
    camera_menu_item_list,
    0,
    &gRootMenu,
    0,
    menuNoAction,
    menuShow,
    menuHide
};
