/*
  nvfview
  menu.c
    Copyright (C) 1998, NINTENDO Co,Ltd., MONEGI CORPORATION.
    Dec. 14, 1998.
*/

/*----------------------------------------------------------------------
  Module to manage Menu
  * Basic operation of Menu
    Up/Down ...... Action various every item.
    Left/Right ...... Usually, nothing happens, but an item with parameters
		uses it to increase/decrease parameters.
    [START] ... Determine item. Action various every item.
		Usually, a sub menu is displayed or 
		the current menu is closed.
		When none of the menus are displayed,
		opens a root menu.
----------------------------------------------------------------------*/

#include "pack.h"
#include "menu.h"
#include "nusys.h"

#define ARRAW_MASK	(CONT_LEFT|CONT_RIGHT|CONT_UP|CONT_DOWN)

#define AUTO_REPEAT_DELAY	(30)
#define AUTO_REPEAT_INTERVAL	(1)

#define LEFT_PRESSED	(1)
#define RIGHT_PRESSED	(2)
#define UP_PRESSED	(3)
#define DOWN_PRESSED	(4)

MENU *gCurrentMenu = NULL;

/*----------------------------------------------------------------------
  Define action of menu that does nothing
----------------------------------------------------------------------*/
void menuNoAction( MENU *menu, void *option )
{
    ( void )menu;
    ( void )option;
}

/*----------------------------------------------------------------------
  Display manu
----------------------------------------------------------------------*/
void menuShow( MENU *menu, void *option )
{
    /* Set color for item
			current menu		other menu
      current item		red(4)		blue(1)
      other items		white(7)	gray(8)
    */
    static const int COLOR[ 2 ][ 2 ] = { 8, 1, 7, 4 };
    int		i;
    const int	*col;

    col = COLOR[ menu == gCurrentMenu ];

    for ( i = 0; i < menu->num_of_items; ++i ){
	nuDebConTextPos( 0, menu->pos_x, menu->pos_y + i );
	nuDebConTextColor( 0, col[ 0 ] );
	if ( i == menu->current_item_index ) nuDebConTextColor( 0, col[ 1 ] );
	menu->item_array[ i ]->setup_label( menu->item_array[ i ], option );
	nuDebConCPuts( 0, menu->item_array[ i ]->label );
    }
}

/*----------------------------------------------------------------------
  Display parent menu recursively
----------------------------------------------------------------------*/
static void show_ancestors( MENU *menu, void *option )
{
    MENU	*parent;
    parent = menu->parent;
    if ( parent ) {
	show_ancestors( parent, option );
	parent->show( parent, option );
    }
}

/*----------------------------------------------------------------------
  Non-display of menu (not used currently)
----------------------------------------------------------------------*/
void menuHide( MENU *menu, void *option )
{
    nuDebConClear( 0 );
    show_ancestors( menu, option );
}

/*----------------------------------------------------------------------
  Define action for item that does nothing
----------------------------------------------------------------------*/
MENU *menuItemNoAction( MENU *menu, MENU_ITEM *item, void *option )
{
    ( void )item;
    ( void )option;

    return menu;
}

/*----------------------------------------------------------------------
  Define action for item that closes menu
----------------------------------------------------------------------*/
MENU *menuItemExitAction( MENU *menu, MENU_ITEM *item, void *option )
{
    ( void )item;
    ( void )option;

    menu->is_active = 0;
    return menu->parent;
}

/*----------------------------------------------------------------------
  Define action for item that opens sub-menu
----------------------------------------------------------------------*/
MENU *menuItemSelectAction( MENU *menu, MENU_ITEM *item, void *option )
{
    ( void )menu;
    ( void )option;

    item->submenu->is_active = 1;
    return item->submenu;
}

/*----------------------------------------------------------------------
  Set label of item
----------------------------------------------------------------------*/
void menuItemSetupLabel( MENU_ITEM *item, void *option )
{
}

/*----------------------------------------------------------------------
  Define action for item that increases value
----------------------------------------------------------------------*/
MENU *menuValueItemIncreaseAction( MENU *menu, MENU_ITEM *item, void *option )
{
    MENU_VALUE_ITEM	*value_item;

    ( void )option;

    value_item = ( MENU_VALUE_ITEM * )item->this;
    if( *value_item->ptr < value_item->max_value ){
	++*value_item->ptr;
    }
    return menu;
}

/*----------------------------------------------------------------------
  Define action for item that decreases value
----------------------------------------------------------------------*/
MENU *menuValueItemDecreaseAction( MENU *menu, MENU_ITEM *item, void *option )
{
    MENU_VALUE_ITEM	*value_item;

    ( void )option;

    value_item = ( MENU_VALUE_ITEM * )item->this;
    if( *value_item->ptr > value_item->min_value ){
	--*value_item->ptr;
    }
    return menu;
}

/*----------------------------------------------------------------------
  Set the value of item to label
----------------------------------------------------------------------*/
void menuValueItemSetupLabel( MENU_ITEM *item, void *option )
{
    MENU_VALUE_ITEM	*value_item;

    ( void )option;

    value_item = ( MENU_VALUE_ITEM * )item->this;
    sprintf( item->label, value_item->format, *value_item->ptr );
}

/*----------------------------------------------------------------------
  Define action for item that changes switch
----------------------------------------------------------------------*/
MENU *menuSwitchItemToggleAction( MENU *menu, MENU_ITEM *item, void *option )
{
    MENU_SWITCH_ITEM	*switch_item;

    ( void )option;

    switch_item = ( MENU_SWITCH_ITEM * )item->this;
    ++*switch_item->ptr;
    while( *switch_item->ptr >= switch_item->number_of_labels )
		*switch_item->ptr -= switch_item->number_of_labels;
    return menu;
}

/*----------------------------------------------------------------------
  Set switch to label
----------------------------------------------------------------------*/
void menuSwitchItemSetupLabel( MENU_ITEM *item, void *option )
{
    MENU_SWITCH_ITEM	*switch_item;
    char		*label;
    char		*cptr;

    ( void )option;

    switch_item = ( MENU_SWITCH_ITEM * )item->this;
    cptr = item->label;
    for( label = switch_item->label_array[ *switch_item->ptr ];
	 *label != 0; ++label ){
	*cptr = *label;
	++cptr;
    }
}

/*----------------------------------------------------------------------
  Analyze input of pad
  A condition to react to a pad is that the button is pressed singly.       
  For example, if <right> and <up> are pressed down simultaneously, it is considered no input.  Also, auto-repeat is realized by this function. 
----------------------------------------------------------------------*/
static int parse_input( NUContData *pad )
{
    static int	last_input = 0;
    static int	delay = 0;

    int	current_input;
    int	return_value;
    int	arraw_button;
    arraw_button = pad[ 0 ].button & ARRAW_MASK;
    switch ( arraw_button ){
	case CONT_LEFT:
	    current_input = LEFT_PRESSED;
	    break;
	case CONT_RIGHT:
	    current_input = RIGHT_PRESSED;
	    break;
	case CONT_UP:
	    current_input = UP_PRESSED;
	    break;
	case CONT_DOWN:
	    current_input = DOWN_PRESSED;
	    break;
	default:
	    current_input = 0;
	    break;
    }
    return_value = 0;
    if ( last_input != current_input ){
	delay = AUTO_REPEAT_DELAY;
	return_value = current_input;
    } else {
	--delay;
	if ( delay <= 0 ){
	    delay = AUTO_REPEAT_INTERVAL;
	    return_value = current_input;
	}
    }
    last_input = current_input;

    return return_value;
}

/*----------------------------------------------------------------------
  Menu processing every frame
   The application calls this function in a loop.
----------------------------------------------------------------------*/
void menu( MENU *root_menu, NUContData *pad, void *option )
{
    MENU	*new_menu;
    MENU_ITEM	*item;
    int		input;

    input = parse_input( pad );
    item = NULL;
    if ( gCurrentMenu ) item = gCurrentMenu->item_array[
					gCurrentMenu->current_item_index ];
    if ( pad[0].trigger & CONT_START ){
	/* Choice*/
	if ( !gCurrentMenu ) new_menu = root_menu;
	else new_menu = item->on_selected( gCurrentMenu, item, option );
	if ( new_menu ) new_menu->enter( new_menu, option );
	else nuDebConClear( 0 );
	gCurrentMenu = new_menu;
    } else {
	switch( input ){
	    case LEFT_PRESSED:
		if ( item ) new_menu = item->on_left_pressed( gCurrentMenu,
							      item, option );
		break;
	    case RIGHT_PRESSED:
		if ( item ) new_menu = item->on_right_pressed( gCurrentMenu,
							       item, option );
		break;
	    case UP_PRESSED:
		if ( gCurrentMenu ) --gCurrentMenu->current_item_index;
		break;
	    case DOWN_PRESSED:
		if ( gCurrentMenu ) ++gCurrentMenu->current_item_index;
		break;
	    default:
		break;
	}
    }
    if ( gCurrentMenu ){
	while( gCurrentMenu->current_item_index >= gCurrentMenu->num_of_items )
		gCurrentMenu->current_item_index -= gCurrentMenu->num_of_items;
	while( gCurrentMenu->current_item_index < 0 )
		gCurrentMenu->current_item_index += gCurrentMenu->num_of_items;
	nuDebConClear( 0 );
	show_ancestors( gCurrentMenu, option );
	gCurrentMenu->show( gCurrentMenu, option );
    }
}
