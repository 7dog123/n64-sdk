/*======================================================================*/
/*		NIFFprev						*/
/*		fogmenu.c						*/
/*									*/
/*		Copyright (C) 1997,1998, NINTENDO Co,Ltd.		*/
/*		Copyright (C) 1998, MONEGI CORPORATION.			*/
/*									*/
/*======================================================================*/
/* Revision History							*/
/*  1998/ 6/16	Changed so MENU definition macro can be used.  		*/
/*  1998/ 6/19	Added RESET function					*/
/*======================================================================*/
/*----------------------------------------------------------------------
  Definition of FOG menu
    Not many functions. Menu and data of items only.
    The name of FOG menu is gFogMenu.
    Menu structure
      [ON]/[OFF] --> use FOG/not use FOG 
      [R] ---------> set R density 
      [G] ---------> set G density
      [B] ---------> set B density
      [A] ---------> set A density
      [NEAR] ------> set FOG NEAR depth
      [FAR] -------> set FOG FAR depth  
      [RESET] -----> reset parameter  
      [EXIT] ------> close this menu

    With R, G, B, A items, numeric values can be increased/decreased 
    using <--> in the range of 0 - 255.
    With NEAR, FAR items, numeric values can be increased/decreased 
    using <--> in the range of 0 - 1000.  
----------------------------------------------------------------------*/

#include "pack.h"
#include "menu.h"
#include "mode.h"
#include "nusys.h"
#include "menudef.h"

static MENU *reset_fog( MENU *menu, MENU_ITEM *menu_item, void *option )
{
    ( void )menu_item;
    ( void )option;
    modeResetFog( &gMode );
    return menu;
}

/*
  Notes:The following definition defines a variable individually a label without filling a 
label with character string constant. This is because some compiler puts together same character string constants. Also, as these labels will be written to, it is not a correct usage of character string constant, either.  
         
*/
static char *on_off[ ] = { "OFF", "ON " };
static char fog_label_on_off[ ] = "OFF";
static MENU_DEF_SWITCH_ITEM( fog_menu_on_off, &gMode.fog.enable,
			     fog_label_on_off, on_off );

static char fog_label_r[ ] = "R        ";
static MENU_DEF_VALUE_ITEM( fog_menu_r, &gMode.fog.color.r, 0, 255, 
			    fog_label_r, "R     %3d" );

static char fog_label_g[ ] = "G        ";
static MENU_DEF_VALUE_ITEM( fog_menu_g, &gMode.fog.color.g, 0, 255, 
			    fog_label_g, "G     %3d" );

static char fog_label_b[ ] = "B        ";
static MENU_DEF_VALUE_ITEM( fog_menu_b, &gMode.fog.color.b, 0, 255, 
			    fog_label_b, "B     %3d" );

static char fog_label_a[ ] = "A        ";
static MENU_DEF_VALUE_ITEM( fog_menu_a, &gMode.fog.color.a, 0, 255, 
			    fog_label_a, "A     %3d" );

static char fog_label_near[ ] = "NEAR     ";
static MENU_DEF_VALUE_ITEM( fog_menu_near, &gMode.fog.near, 0, 1000, 
			    fog_label_near, "NEAR %4d" );

static char fog_label_far[ ] = "FAR      ";
static MENU_DEF_VALUE_ITEM( fog_menu_far, &gMode.fog.far, 0, 1000, 
			    fog_label_far, "FAR  %4d" );

static MENU_ITEM fog_menu_reset = {
    "RESET",
    &fog_menu_reset,
    NULL,
    menuItemSetupLabel,
    menuItemNoAction,
    menuItemNoAction,
    reset_fog
};

static MENU_DEF_EXIT_ITEM( fog_menu_exit, "EXIT" );

static MENU_ITEM *fog_menu_item_list[ ] = {
    &fog_menu_on_off.base,
    &fog_menu_r.base,
    &fog_menu_g.base,
    &fog_menu_b.base,
    &fog_menu_a.base,
    &fog_menu_near.base,
    &fog_menu_far.base,
    &fog_menu_reset,
    &fog_menu_exit
};

MENU_DEF_MENU( gFogMenu, &gRootMenu, FOG_MENU_POS_X, FOG_MENU_POS_Y,
	       fog_menu_item_list );
