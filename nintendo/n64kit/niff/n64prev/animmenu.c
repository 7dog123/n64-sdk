/*======================================================================*/
/*		NIFFprev						*/
/*		animmenu.c						*/
/*									*/
/*		Copyright (C) 1997,1998, NINTENDO Co,Ltd.		*/
/*		Copyright (C) 1998, MONEGI CORPORATION.			*/
/*									*/
/*======================================================================*/
/* Revision history							*/
/*  1998/ 6/18	Changed so MENU definition macro can be used.  			*/
/*======================================================================*/
/*----------------------------------------------------------------------
  Definition of ANIMATION Menu 
    Not many functions. Menu and data of items only.
    The name of ANIMATION menu is gAnimMenu.
    Menu structure
      [TOGGLE]/[STEP] -->Switches reset operation
      [EXIT] ----------->Closes this menu
----------------------------------------------------------------------*/

#include "pack.h"
#include "menu.h"
#include "mode.h"
#include "nusys.h"
#include "menudef.h"

static char *anim_mode[ ] = { "TOGGLE", "STEP  " };
static char anim_label_mode[ ] = "TOGGLE";
static MENU_DEF_SWITCH_ITEM( anim_menu_mode, &gMode.anim_mode,
			     anim_label_mode, anim_mode );

static MENU_DEF_EXIT_ITEM( anim_menu_exit, "EXIT" );

static MENU_ITEM *anim_menu_item_list[ ] = {
    &anim_menu_mode.base,
    &anim_menu_exit
};

MENU_DEF_MENU( gAnimMenu, &gRootMenu, ANIM_MENU_POS_X, ANIM_MENU_POS_Y,
	       anim_menu_item_list );
