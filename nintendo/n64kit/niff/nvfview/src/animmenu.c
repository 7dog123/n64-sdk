/*
  nvfview
  animmenu.c
    Copyright (C) 1998, NINTENDO Co,Ltd., MONEGI CORPORATION.
    Feb. 26, 1999.
*/

/*----------------------------------------------------------------------
  Definition of ANIM PITCH Menu
    Not many functions. Menu and data of items only.
    The name of ANIMATION menu is gAnimMenu.
    Menu structure
      [1]/[0.5]/[0.25]/[2] --> Swithes reset operation
      [####:????] -----------> Select animation
      [EXIT] ----------------> Close this menu
----------------------------------------------------------------------*/

#include "pack.h"
#include "menu.h"
#include "mode.h"
#include "nusys.h"
#include "menudef.h"
#include "viewerinfo.h"

extern ViewerInfo gViewerInfo;

static void anim_index_setup_label( MENU_ITEM *item, void *option );
static MENU *anim_index_prev_anim( MENU *menu, MENU_ITEM *item,
				      void *option );
static MENU *anim_index_next_anim( MENU *menu, MENU_ITEM *item,
				       void *option );

static char *anim_mode[ ] = { "PITCH 1   ", "PITCH 0.5 ", "PITCH 0.25",
			      "PITCH 2   " };
static char anim_label_mode[ ] = "PITCH 1   ";
static MENU_DEF_SWITCH_ITEM( anim_menu_mode, &gMode.anim_pitch,
			     anim_label_mode, anim_mode );
static char anim_label[32];

static MENU_ITEM anim_menu_index = {
    anim_label,
    &anim_menu_index,
    NULL,
    anim_index_setup_label,
    anim_index_prev_anim,
    anim_index_next_anim,
    anim_index_next_anim,
};

static MENU_DEF_EXIT_ITEM( anim_menu_exit, "EXIT" );

static MENU_ITEM *anim_menu_item_list[ ] = {
    &anim_menu_mode.base,
    &anim_menu_index,
    &anim_menu_exit
};

MENU_DEF_MENU( gAnimMenu, &gRootMenu, ANIM_MENU_POS_X, ANIM_MENU_POS_Y,
	       anim_menu_item_list );

static void anim_index_setup_label( MENU_ITEM *item, void *option )
{
    int		i;
    AnimInfo	*anim_info_ptr;

    for ( i = 0; i < sizeof( anim_label ); ++i ) anim_label[ i ] = ' ';
    anim_label[ 24 ] = 0;	/* stop here */

    if ( ( gMode.anim_index <
			gViewerInfo.module_info_array[ 1 ].number_of_anims )&&
	 ( gMode.anim_index >= 0 ) )
    {
	anim_info_ptr = &gViewerInfo.module_info_array[ 1 ].anim_info_array[
							gMode.anim_index ];
	anim_label[ 0 ] = ( ( gMode.anim_index / 1000 ) % 10 ) + '0';
	anim_label[ 1 ] = ( ( gMode.anim_index / 100 ) % 10 ) + '0';
	anim_label[ 2 ] = ( ( gMode.anim_index / 10 ) % 10 ) + '0';
	anim_label[ 3 ] = ( gMode.anim_index % 10 ) + '0';
	for ( i = 0; i < 24; ++i )
	{
	    if ( !anim_info_ptr->name[ i ] ) break;
	    anim_label[ i + 5 ] = anim_info_ptr->name[ i ];
	}
    }
}

static MENU *anim_index_prev_anim( MENU *menu, MENU_ITEM *item, void *option )
{
    ( void )option;
    ( void )item;

    --gMode.anim_index;
    if ( gMode.anim_index < 0 )
    {
	gMode.anim_index = gViewerInfo.module_info_array[ 1 ].number_of_anims -
			   1;
    }

    return menu;
}

static MENU *anim_index_next_anim( MENU *menu, MENU_ITEM *item, void *option )
{
    ( void )option;
    ( void )item;

    ++gMode.anim_index;
    if ( gMode.anim_index >=
		gViewerInfo.module_info_array[ 1 ].number_of_anims )
    {
	gMode.anim_index = 0;
    }

    return menu;
}
