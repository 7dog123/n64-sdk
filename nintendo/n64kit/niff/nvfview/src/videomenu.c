/*======================================================================*/
/*		NIFFprev						*/
/*		videomenu.c						*/
/*									*/
/*		Copyright (C) 1997-1999, NINTENDO Co,Ltd.		*/
/*		Copyright (C) 1998-1999, MONEGI CORPORATION.		*/
/*									*/
/*======================================================================*/
/*----------------------------------------------------------------------
  VIDEO menu definition
    A few functions. Data regarging menus and items.
    VIDEO The name of the menu is gVideoMenu
    Outline of the menu
      [GAMMA ON/OFF] -------------> Enable/Disable gamma correction
      [GAMMA DITHER ON/OFF] ------> Enable/Disable gamma dither
      [DIVOT ON/OFF] -------------> Enable/Disable DIVOT
      [DITHER FILTER ON/OFF] -----> Enable/Disable dither filter
      [PERF BAR ON/OFF] ----------> Show/Hide preference bar
      [320x240 16bpp] ------------> Change screen resolution
      [EXIT] ---------------------> Exit menu
----------------------------------------------------------------------*/

#include "pack.h"
#include "menu.h"
#include "mode.h"
#include "nusys.h"
#include "menudef.h"

/*
  Notes: Variables are individually defined for labels instead of assignning
         string constants. This is because some compilers handle identical 
         string constants improperly.
         Besides, string constants should not be used because the labels are
         overwritten.
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
ON_OFF_ITEM( perf_bar_item, &gMode.perfmon_enable, "PERF BAR" );

static char *resolution[ ] =
{
    "320x240 16bpp ",
    "320x240D 16bpp",
    "320x240 32bpp ",
    "320x240D 32bpp",
    "640x480 16bpp ",
    "640x480I 16bpp"
};

static char resolution_label[ ] = "320x240 16bpp ";
static MENU_DEF_SWITCH_ITEM( resolution_item, &gMode.resolution,
			     resolution_label, resolution );

static MENU_DEF_EXIT_ITEM( video_menu_exit, "EXIT" );

static MENU_ITEM *video_menu_item_list[ ] = {
    &gamma_item.base,
    &gamma_dither_item.base,
    &divot_item.base,
    &dither_filter_item.base,
    &perf_bar_item.base,
    &resolution_item.base,
    &video_menu_exit
};

MENU_DEF_MENU( gVideoMenu, &gRootMenu, VIDEO_MENU_POS_X, VIDEO_MENU_POS_Y,
	       video_menu_item_list );
