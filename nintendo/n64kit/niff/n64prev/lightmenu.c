/*======================================================================*/
/*		NIFFprev						*/
/*		lightmenu.c						*/
/*									*/
/*		Copyright (C) 1997,1998, NINTENDO Co,Ltd.		*/
/*		Copyright (C) 1998, MONEGI CORPORATION.			*/
/*									*/
/*======================================================================*/
/* Revision history							*/
/*  1998/ 6/16	Changed so light color can be set.			*/
/*  1998/ 6/22	Added RESET item.					*/
/*======================================================================*/
/*----------------------------------------------------------------------
  Definition of LIGHT menu
    Not many functions. Menu and data of items only.
    The name of LIGHT menu is gLightMenu.
    Menu structure
      [DEFAULT]/[SCENE] --> Switches lights.
      [AMBIENT] ----------> Sets ambient light.
      [LIGHT1] -----------> Sets light 1. 
      [LIGHT2] -----------> Sets light 2.
      [LIGHT3] -----------> Sets light 3.
      [LIGHT4] -----------> Sets light 4.
      [LIGHT5] -----------> Sets light 5.
      [LIGHT6] -----------> Sets light 6.
      [LIGHT7] -----------> Sets light 7.
      [RESET] ------------> Resets light.
      [EXIT] ------> Closes this menu.
----------------------------------------------------------------------*/

#include "pack.h"
#include "menu.h"
#include "mode.h"
#include "nusys.h"
#include "menudef.h"

/* RGB menu definition macro */
#define RGB_MENU(menu,color,pos_y) \
    static char menu##_label_r[ ] = "R    ";\
    static MENU_DEF_VALUE_ITEM( menu##_r, &(color).r, 0, 255,\
				menu##_label_r, "R %3d" );\
    static char menu##_label_g[ ] = "G    ";\
    static MENU_DEF_VALUE_ITEM( menu##_g, &(color).g, 0, 255,\
				menu##_label_g, "G %3d" );\
    static char menu##_label_b[ ] = "B    ";\
    static MENU_DEF_VALUE_ITEM( menu##_b, &(color).b, 0, 255,\
				menu##_label_b, "B %3d" );\
    static MENU_DEF_EXIT_ITEM( menu##_exit, "EXIT" );\
    static MENU_ITEM *menu##_item_list[ ] = {\
	&menu##_r.base,\
	&menu##_g.base,\
	&menu##_b.base,\
	&menu##_exit\
    };\
    static MENU_DEF_MENU( menu##, &gLightMenu, 23, (pos_y), menu##_item_list )

static MENU *reset_lights( MENU *menu, MENU_ITEM *menu_item, void *option )
{
    ( void )menu_item;
    ( void )option;
    modeResetLights( &gMode );
    return menu;
}

RGB_MENU( ambient_menu, gMode.ambient, LIGHT_MENU_POS_Y + 1 );
RGB_MENU( light1_menu, gMode.light_color[0], LIGHT_MENU_POS_Y + 2 );
RGB_MENU( light2_menu, gMode.light_color[1], LIGHT_MENU_POS_Y + 3 );
RGB_MENU( light3_menu, gMode.light_color[2], LIGHT_MENU_POS_Y + 4 );
RGB_MENU( light4_menu, gMode.light_color[3], LIGHT_MENU_POS_Y + 5 );
RGB_MENU( light5_menu, gMode.light_color[4], LIGHT_MENU_POS_Y + 6 );
RGB_MENU( light6_menu, gMode.light_color[5], LIGHT_MENU_POS_Y + 7 );
RGB_MENU( light7_menu, gMode.light_color[6], LIGHT_MENU_POS_Y + 8 );

static char *light_mode[ ] = { "DEFAULT", "SCENE  " };
static char light_label_mode[ ] = "DEFAULT";
static MENU_DEF_SWITCH_ITEM( light_menu_mode, &gMode.active_light,
			     light_label_mode, light_mode );

static MENU_DEF_LINK_ITEM( light_menu_ambient, "AMBIENT", ambient_menu );
static MENU_DEF_LINK_ITEM( light_menu_light1, "LIGHT1 COLOR", light1_menu );
static MENU_DEF_LINK_ITEM( light_menu_light2, "LIGHT2 COLOR", light2_menu );
static MENU_DEF_LINK_ITEM( light_menu_light3, "LIGHT3 COLOR", light3_menu );
static MENU_DEF_LINK_ITEM( light_menu_light4, "LIGHT4 COLOR", light4_menu );
static MENU_DEF_LINK_ITEM( light_menu_light5, "LIGHT5 COLOR", light5_menu );
static MENU_DEF_LINK_ITEM( light_menu_light6, "LIGHT6 COLOR", light6_menu );
static MENU_DEF_LINK_ITEM( light_menu_light7, "LIGHT7 COLOR", light7_menu );

static MENU_ITEM light_menu_reset = {
    "RESET",
    &light_menu_reset,
    NULL,
    menuItemSetupLabel,
    menuItemNoAction,
    menuItemNoAction,
    reset_lights
};

static MENU_DEF_EXIT_ITEM( light_menu_exit, "EXIT" );

static MENU_ITEM *light_menu_item_list[ ] = {
    &light_menu_mode.base,
    &light_menu_ambient,
    &light_menu_light1,
    &light_menu_light2,
    &light_menu_light3,
    &light_menu_light4,
    &light_menu_light5,
    &light_menu_light6,
    &light_menu_light7,
    &light_menu_reset,
    &light_menu_exit
};

MENU_DEF_MENU( gLightMenu, &gRootMenu, LIGHT_MENU_POS_X, LIGHT_MENU_POS_Y,
	       light_menu_item_list );
