/*======================================================================*/
/*		NIFFprev						*/
/*		menu.h							*/
/*									*/
/*		Copyright (C) 1997,1998, NINTENDO Co,Ltd.		*/
/*		Copyright (C) 1998, MONEGI CORPORATION.			*/
/*									*/
/*======================================================================*/
/*Revision history							*/
/*  1998/ 6/16	Added MENU_VALUE_ITEM, MENU_SWITCH_ITEM  		*/
/*======================================================================*/
#ifndef __menu_h
#define __menu_h

struct menuTag;
struct menuItemTag;
typedef void ( *MENU_ITEM_SETUP_LABEL )( struct menuItemTag *item,
					 void *option );
typedef struct menuTag *( *MENU_ITEM_ACTION )( struct menuTag *menu,
					       struct menuItemTag *item,
					       void *option );

typedef struct menuItemTag {
    char			*label;
    void			*this;
    struct menuTag		*submenu;
    MENU_ITEM_SETUP_LABEL	setup_label;
    MENU_ITEM_ACTION		on_left_pressed;
    MENU_ITEM_ACTION		on_right_pressed;
    MENU_ITEM_ACTION		on_selected;
} MENU_ITEM;

typedef struct menuValueItemTag {
    MENU_ITEM	base;
    int		min_value;
    int		max_value;
    char	*format;	/* used for sprintf   */
    int		*ptr;		/* pointer of variable to store the value */
} MENU_VALUE_ITEM;

typedef struct menuSwitchItemTag {
    MENU_ITEM	base;
    int		number_of_labels;
    char	**label_array;
    int		*ptr;		/* pointer of variable to store the value*/
} MENU_SWITCH_ITEM;

typedef void ( *MENU_ACTION )( struct menuTag *menu, void *option );

typedef struct menuTag {
    int			pos_x, pos_y;
    int			num_of_items;
    MENU_ITEM		**item_array;
    int			current_item_index;
    struct menuTag	*parent;
    int			is_active;
    MENU_ACTION		enter;
    MENU_ACTION		show;
    MENU_ACTION		hide;	/* ignored for the current version */
} MENU;

extern void menu( MENU *root_menu, EXCONTPAD *pad, void *option );

extern void menuShow( MENU *menu, void *option );
extern void menuHide( MENU *menu, void *option );
extern void menuNoAction( MENU *menu, void *option );

extern MENU *menuItemNoAction( MENU *menu, MENU_ITEM *item, void *option );
extern MENU *menuItemExitAction( MENU *menu, MENU_ITEM *item, void *option );
extern MENU *menuItemSelectAction( MENU *menu, MENU_ITEM *item, void *option );
extern void menuItemSetupLabel( MENU_ITEM *item, void *option );

extern void menuValueItemSetupLabel( MENU_ITEM *item, void *option );
extern MENU *menuValueItemIncreaseAction( MENU *menu, MENU_ITEM *item,
					  void *option );
extern MENU *menuValueItemDecreaseAction( MENU *menu, MENU_ITEM *item,
					  void *option );

extern void menuSwitchItemSetupLabel( MENU_ITEM *item, void *option );
extern MENU *menuSwitchItemToggleAction( MENU *menu, MENU_ITEM *item,
					 void *option );

/* Macro to create an item that becomes a link to menu */
#define MENU_DEF_LINK_ITEM(symbol,label,link) \
MENU_ITEM symbol = {\
    label, &symbol, &link,	\
    menuItemSetupLabel,		\
    menuItemNoAction,		\
    menuItemNoAction,		\
    menuItemSelectAction	\
}

/* Macro to create EXIT item */
#define MENU_DEF_EXIT_ITEM(symbol,label) \
MENU_ITEM symbol = {\
    label, &symbol, NULL,	\
    menuItemSetupLabel,		\
    menuItemNoAction,		\
    menuItemNoAction,		\
    menuItemExitAction		\
}

/* Macro to create an item that sets the value */
#define MENU_DEF_VALUE_ITEM(symbol,vptr,min,max,label,format) \
MENU_VALUE_ITEM symbol = {		\
    label, &symbol, NULL,		\
    menuValueItemSetupLabel,		\
    menuValueItemDecreaseAction,	\
    menuValueItemIncreaseAction,	\
    menuItemNoAction,			\
    min, max,				\
    format,				\
    vptr				\
}

/* Macro to create an item that sets a switch */
#define MENU_DEF_SWITCH_ITEM(symbol,vptr,label,label_array) \
MENU_SWITCH_ITEM symbol = {			\
    label, &symbol, NULL,			\
    menuSwitchItemSetupLabel,			\
    menuItemNoAction,				\
    menuItemNoAction,				\
    menuSwitchItemToggleAction,			\
    sizeof( label_array ) / sizeof( char * ),	\
    &label_array[ 0 ],				\
    vptr					\
}

/* Macro to create simple menu*/
#define MENU_DEF_MENU(symbol,parent,pos_x,pos_y,item_array) \
MENU symbol = {						\
    pos_x, pos_y,					\
    sizeof( item_array ) / sizeof( MENU_ITEM * ),	\
    item_array,						\
    0,							\
    parent,						\
    0,							\
    menuNoAction,					\
    menuShow,						\
    menuHide						\
}

#endif /* __menu_h */
