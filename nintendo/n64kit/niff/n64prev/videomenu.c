/*======================================================================*/
/*		NIFFprev						*/
/*		videomenu.c						*/
/*									*/
/*		Copyright (C) 1997,1998, NINTENDO Co,Ltd.		*/
/*		Copyright (C) 1998, MONEGI CORPORATION.			*/
/*									*/
/*======================================================================*/
/*----------------------------------------------------------------------
  Definition of VIDEO menu 
    Not many functions. Menu and data of items only. 
    The name of VIDEO menu is gVideoMenu.
    Menu structure
      [GAMMA ON]/[GAMMA OFF] ----> use/do not use Gamma control 
      [DITHER ON]/[DITHER OFF] --> use/do not use dither 
      [DIVOT ON]/[DIVOT OFF] ----> use/do not use DIVOT 
      [EXIT] --------------------> close this menu
----------------------------------------------------------------------*/

#include "pack.h"
#include "menu.h"
#include "mode.h"
#include "nusys.h"
#include "menudef.h"

/*
  Note: The following definition defines a variable individually without filling a label with character string constant.  This is because
        some compiler puts together same character string constants.  Also, as
        these labels will be written to, it is not a correct usage of 
        character string constant, either. 
        
*/

#define ON_OFF_ITEM( symbol, vptr, label ) \
	static char *symbol##_on_off[ ] = { label" OFF", label" ON " };\
	static char symbol##_label[ ] = label" OFF";\
	static MENU_DEF_SWITCH_ITEM( symbol, vptr, symbol##_label,\
				     symbol##_on_off )

ON_OFF_ITEM( gamma_item, &gMode.gamma_enable, "GAMMA" );
ON_OFF_ITEM( gamma_dither_item, &gMode.gamma_dither_enable, "GAMMA DITHER" );
ON_OFF_ITEM( divot_item, &gMode.divot_enable, "DIVOT" );
ON_OFF_ITEM( dither_filter_item, &gMode.dither_filter_enable,
	     "DITHER FILTER" );
static MENU_DEF_EXIT_ITEM( video_menu_exit, "EXIT" );

static MENU_ITEM *video_menu_item_list[ ] = {
    &gamma_item.base,
    &gamma_dither_item.base,
    &divot_item.base,
    &dither_filter_item.base,
    &video_menu_exit
};

MENU_DEF_MENU( gVideoMenu, &gRootMenu, VIDEO_MENU_POS_X, VIDEO_MENU_POS_Y,
	       video_menu_item_list );
