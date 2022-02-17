/*======================================================================*/
/*		NIFFprev						*/
/*		controlmenu.c						*/
/*									*/
/*		Copyright (C) 1997,1998, NINTENDO Co,Ltd.		*/
/*		Copyright (C) 1998, MONEGI CORPORATION.			*/
/*									*/
/*======================================================================*/
/*----------------------------------------------------------------------
  Definition of CONTROL menu
    This menu specifies what is to be moved by a pad. 
    Not many functions. Menu and data of items only.
    The name of CONTROL menu is gControlMenu.
    Menu structure
      [CAMERA] ----------------> Moves a camera.
      [OBJECT] ----------------> Moves an object.
      [LIGHT1] -----------------> Moves light 1.
      [LIGHT2] -----------------> Moves light 2.
      [LIGHT3] -----------------> Moves light 3.
      [LIGHT4] -----------------> Moves light 4.
      [LIGHT5] -----------------> Moves light 5.
      [LIGHT6] -----------------> Moves light 6.
      [LIGHT7] -----------------> Moves light 7.
      [TRACKBALL]/[CRUISE] -----> Switches move mode. 
      [EXIT] -------------------> Closes this menu.
----------------------------------------------------------------------*/

#include "pack.h"
#include "menu.h"
#include "mode.h"
#include "nusys.h"
#include "menudef.h"

static void get_control( MENU *menu, void *option );
static MENU *set_control( MENU *menu, MENU_ITEM *item, void *option );

static MENU_ITEM control_menu_camera = {
    "CAMERA",
    &control_menu_camera,
    NULL,
    menuItemSetupLabel,
    menuItemNoAction,
    menuItemNoAction,
    set_control
};

static MENU_ITEM control_menu_object = {
    "OBJECT",
    &control_menu_object,
    NULL,
    menuItemSetupLabel,
    menuItemNoAction,
    menuItemNoAction,
    set_control
};

static MENU_ITEM control_menu_light1 = {
    "LIGHT1",
    &control_menu_light1,
    NULL,
    menuItemSetupLabel,
    menuItemNoAction,
    menuItemNoAction,
    set_control
};

static MENU_ITEM control_menu_light2 = {
    "LIGHT2",
    &control_menu_light2,
    NULL,
    menuItemSetupLabel,
    menuItemNoAction,
    menuItemNoAction,
    set_control
};

static MENU_ITEM control_menu_light3 = {
    "LIGHT3",
    &control_menu_light3,
    NULL,
    menuItemSetupLabel,
    menuItemNoAction,
    menuItemNoAction,
    set_control
};

static MENU_ITEM control_menu_light4 = {
    "LIGHT4",
    &control_menu_light4,
    NULL,
    menuItemSetupLabel,
    menuItemNoAction,
    menuItemNoAction,
    set_control
};

static MENU_ITEM control_menu_light5 = {
    "LIGHT5",
    &control_menu_light5,
    NULL,
    menuItemSetupLabel,
    menuItemNoAction,
    menuItemNoAction,
    set_control
};

static MENU_ITEM control_menu_light6 = {
    "LIGHT6",
    &control_menu_light6,
    NULL,
    menuItemSetupLabel,
    menuItemNoAction,
    menuItemNoAction,
    set_control
};

static MENU_ITEM control_menu_light7 = {
    "LIGHT7",
    &control_menu_light7,
    NULL,
    menuItemSetupLabel,
    menuItemNoAction,
    menuItemNoAction,
    set_control
};

static char *control_mode[ ] = { "TRACKBALL", "CRUISE   " };
static char control_label_mode[ ] = "TRACKBALL";
static MENU_DEF_SWITCH_ITEM( control_menu_mode, &gMode.control_mode,
			     control_label_mode, control_mode );

static MENU_DEF_EXIT_ITEM( control_menu_exit, "EXIT" );

static MENU_ITEM *control_menu_item_list[ ] = {
    &control_menu_camera,
    &control_menu_object,
    &control_menu_light1,
    &control_menu_light2,
    &control_menu_light3,
    &control_menu_light4,
    &control_menu_light5,
    &control_menu_light6,
    &control_menu_light7,
    &control_menu_mode.base,
    &control_menu_exit
};

MENU gControlMenu = {
    CONTROL_MENU_POS_X, CONTROL_MENU_POS_Y,
    sizeof( control_menu_item_list ) / sizeof( MENU_ITEM * ),
    control_menu_item_list,
    0,
    &gRootMenu,
    0,
    get_control,
    menuShow,
    menuHide
};

static void get_control( MENU *menu, void *option )
{
    static const int CONTROL_TO_ITEM_INDEX[ ] = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };

    ( void )option;
    menu->current_item_index = CONTROL_TO_ITEM_INDEX[ gMode.control ];
}

static MENU *set_control( MENU *menu, MENU_ITEM *item, void *option )
{
    static const int ITEM_INDEX_TO_CONTROL[ ] = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };

    gMode.control = ITEM_INDEX_TO_CONTROL[ menu->current_item_index ];
    return menuItemExitAction( menu, item, option );
}
