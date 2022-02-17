/*
 *	menu.c
 *
 *	process menu
 *
 *  Copyright (C) 1998-1999, NINTENDO Co.,Ltd.
 *  Copyright (C) 1998-1999, MONEGI CORPORATION
 */

#include	<ultra64.h>
#include	"nusys.h"
#include	"game.h"
#include	"gfx.h"

static	u8	cursor_pos = 0;
static	u8	cursor_index = 0;

/***************************************************************************************
 *	DispMenu
 *
 *	Displaying the menu screen
 ***************************************************************************************/
Gfx	*DispMenu(Gfx *gp)
{
	texture_data*	ptxdata = &td[tvmd.texture_number];
	static	short	x[] = {24,24,24,180,180,24,24,24};
	static	short	y[] = {24,34,44,24,34,56,66,76};
	static	char	*menuname[] = {
		"COMBINE","BLENDER","FILTER",
		"TASKBAR","BG",
		"BG COLOR","PRIM COLOR","ENV COLOR"};
	static	char	*combine_name[] = {
		"DECAL","PRIMITIVE","BLENDPE"};
	static	char	*render_name[] = {
		"OPA_SURF","XLU_SURF","TEX_EDGE"};
	static	char	*filter_name[] = {
		"POINT","BILERP","AVERAGE"};
	static	char	*offon[] = {"OFF","ON"};
	int	i;
	u8	tf;
	RGBA32	Color;
	switch(set_inf.texture.filter)
	{
		case G_TF_POINT :
			tf = 0;
			break;
		case G_TF_BILERP :
			tf = 1;
			break;
		case G_TF_AVERAGE :
			tf = 2;
			break;
		default :
			break;
	}
	gp = disp_square(gp,16,16,298,74,0x000000a0);
	gp = disp_cursor(gp);
	gDPPipeSync(gp++);

	gp = letters_init(gp);

		/*	Displaying menu items	*/
	for( i=0;i<cursor_index;i++ ){
		gp = letters_set(gp,x[i],y[i],menuname[i],0xffffffff);
	}
	gp = letters_set(gp,x[i],y[i],menuname[i],0x00ffffff);
	i++;
	for( ;i<8;i++ ){
		gp = letters_set(gp,x[i],y[i],menuname[i],0xffffffff);
	}

		/*	Displaying the first 3 values of the menu.	*/
	gp = letters_set(gp,88,24,combine_name[set_inf.combiner.global_cc_1],0xffffffff);
	gp = letters_set(gp,88,34,render_name[set_inf.blender.render_mode],0xffffffff);
	gp = letters_set(gp,88,44,filter_name[tf],0xffffffff);

		/*	Displaying Task Bar's ON/OFF	*/
	gp = letters_set(gp,252,24,offon[tvmd.task_flag],0xffffffff);
		/*	Displaying a background name (BG).	*/
	if( 0 == tvmd.bg_number ){
		gp = letters_set(gp,220,34,offon[0],0xffffffff);
	} else {
		gp = letters_set(gp,220,34,td[tvmd.bg_number-1].name,0xffffffff);
	}

		/*	Displaying the element values of each color	*/
	Color = set_inf.etc.BG_color;
	gp = letters_num_right(gp,144,56,Color.rgba.r,0xff0000ff);
	gp = letters_num_right(gp,176,56,Color.rgba.g,0x00ff00ff);
	gp = letters_num_right(gp,208,56,Color.rgba.b,0x6060ffff);
	gp = letters_num_right(gp,240,56,Color.rgba.a,0xffffffff);
	Color = set_inf.etc.PRIM_color;
	gp = letters_num_right(gp,144,66,Color.rgba.r,0xff0000ff);
	gp = letters_num_right(gp,176,66,Color.rgba.g,0x00ff00ff);
	gp = letters_num_right(gp,208,66,Color.rgba.b,0x6060ffff);
	gp = letters_num_right(gp,240,66,Color.rgba.a,0xffffffff);
	Color = set_inf.etc.ENV_color;
	gp = letters_num_right(gp,144,76,Color.rgba.r,0xff0000ff);
	gp = letters_num_right(gp,176,76,Color.rgba.g,0x00ff00ff);
	gp = letters_num_right(gp,208,76,Color.rgba.b,0x6060ffff);
	gp = letters_num_right(gp,240,76,Color.rgba.a,0xffffffff);
	gDPPipeSync( gp++ );

	return	gp;
}

/***************************************************************************************
 *	init_modedata
 *
 *	Initializing a value
 ***************************************************************************************/
void	init_modedata(void)
{
	u32	u;
	tvmd.texture_number = 0;
	for( u=0;u<num_of_texture;u++ ){
		if( !(td[u].pti->image.bg_flag) ){
			tvmd.texture_number = u;
			break;
		}
	}
	tvmd.bg_number = 0;
	for( u=0;u<num_of_texture;u++ ){
		if( td[u].pti->image.bg_flag ){
			tvmd.bg_number = u+1;
			break;
		}
	}
	tvmd.task_flag = TASKBAR_ON;
	tvmd.name_flag = NAME_DISP;
	tvmd.speed = 3;
	tvmd.speed_info_disp_time = 0;
}

/***************************************************************************************
 *	menu_stickcontrol
 *
 *	Controller processing while the menu is being displayed.
 ***************************************************************************************/
void	menu_stickcontrol(void)
{
	float a,b,c,d;
	Mtx m;
	short	x = (short)(contdata[0].stick_x);
	short	y = (short)(contdata[0].stick_y);
	float	deg;
	u8*		changecolorp;
	s16		colorvalue;
	static	u8	u_change[] = {0,0,1,3,3,2,2,2,2,5,6,7,8,9,10,11,12};
	static	u8	d_change[] = {1,2,5,4,2,9,10,11,12,13,14,15,16,13,14,15,16};
	static	u8	l_change[] = {0,1,2,0,1,5,5,6,7,9,9,10,11,13,13,14,15};
	static	u8	r_change[] = {3,4,4,3,4,6,7,8,8,10,11,12,12,14,15,16,16};
	static	index_by_pos[] = {0,1,2,3,4,5,5,5,5,6,6,6,6,7,7,7,7};
	short	changevalue = 2;
	static	char	u_change_value = 26;
	static	char	d_change_value = 26;
	static	char	l_change_value = 26;
	static	char	r_change_value = 26;
	texture_data*	ptxdata = &td[tvmd.texture_number];
	u32		old_bg_number;
		/*	Moving the cursor location using Control Stick.	*/
	if(!(contdata[0].button & Z_TRIG)){
		if( x >= 20 ){
			r_change_value += x/20;
			if( r_change_value >= 30 ){
				cursor_pos = r_change[cursor_pos];
				r_change_value = 0;
			}
		} else {
			r_change_value = 26;
		}
		if( x <= -20 ){
			l_change_value -= x/20;
			if( l_change_value >= 30 ){
				cursor_pos = l_change[cursor_pos];
				l_change_value = 0;
			}
		} else {
			l_change_value = 26;
		}
		if( y >= 20 ){
			u_change_value += y/20;
			if( u_change_value >= 30 ){
				cursor_pos = u_change[cursor_pos];
				u_change_value = 0;
			}
		} else {
			u_change_value = 26;
		}
		if( y <= -20 ){
			d_change_value -= y/20;
			if( d_change_value >= 30 ){
				cursor_pos = d_change[cursor_pos];
				d_change_value = 0;
			}
		} else {
			d_change_value = 26;
		}
	}
		/*	Handling R button	*/
	if(contdata[0].trigger & MESH_CONT_MENU_ONOFF)
		tvmd.tvmode = TVMODE_VIEW;

	cursor_index = index_by_pos[cursor_pos];
		/*	Handling START button. 	*/
		/*	Handling Control Stick. Process by the cursor location.	*/
	switch(cursor_pos){
		case 0 :	/*	Setting a combiner	*/
			if(contdata[0].trigger & Z_TRIG){
				set_inf.combiner.global_cc_1++;
				if( set_inf.combiner.global_cc_1 >= 3 ){
					set_inf.combiner.global_cc_1 = 0;
				}
			} else {
				if( (contdata[0].trigger & B_BUTTON) &&
					(set_inf.combiner.global_cc_1 > 0 ) )
					set_inf.combiner.global_cc_1--;
				if( (contdata[0].trigger & A_BUTTON) &&
					(set_inf.combiner.global_cc_1 < 2 ) )
					set_inf.combiner.global_cc_1++;
			}
			break;
		case 1 :	/*	Setting a render mode.	*/
			if(contdata[0].trigger & Z_TRIG){
				set_inf.blender.render_mode++;
				if( set_inf.blender.render_mode >= 3 ){
					set_inf.blender.render_mode = 0;
				}
			} else {
				if( (contdata[0].trigger & B_BUTTON) &&
					(set_inf.blender.render_mode > 0 ) )
					set_inf.blender.render_mode--;
				if( (contdata[0].trigger & A_BUTTON) &&
					(set_inf.blender.render_mode < 2 ) )
					set_inf.blender.render_mode++;
			}
			break;
		case 2 :	/*	Setting a filter	*/
			if(contdata[0].trigger & (Z_TRIG|A_BUTTON)){
				switch(set_inf.texture.filter){
					case G_TF_POINT :
						set_inf.texture.filter = G_TF_BILERP;
						break;
					case G_TF_BILERP :
						set_inf.texture.filter = G_TF_AVERAGE;
						break;
					case G_TF_AVERAGE :
						set_inf.texture.filter = G_TF_POINT;
						break;
					default :
						break;
				}
			} else {
				if( contdata[0].trigger & B_BUTTON ){
					switch(set_inf.texture.filter){
						case G_TF_POINT :
							set_inf.texture.filter = G_TF_AVERAGE;
							break;
						case G_TF_BILERP :
							set_inf.texture.filter = G_TF_POINT;
							break;
						case G_TF_AVERAGE :
							set_inf.texture.filter = G_TF_BILERP;
							break;
						default :
							break;
					}
				}
			}
			break;
		case 3 :	/*	Switch to display/not display Task Bar. 	*/
			if( contdata[0].trigger & (Z_TRIG|A_BUTTON|B_BUTTON) ){
				tvmd.task_flag = 1-tvmd.task_flag;
			}
			break;
		case 4 :	/*	Switching BG.
				* Reminder: If a value in 'bg_ number' is
			* 0, BG is not displayed, otherwise the texture
			* in 'bg_number-1' is displayed as the background.
					 */
			if(contdata[0].trigger & (Z_TRIG|A_BUTTON)){
				old_bg_number = tvmd.bg_number;
				while(1){
					tvmd.bg_number++;
					if( tvmd.bg_number>num_of_texture ){
						tvmd.bg_number = 0;
						break;
					} else {
						if( td[tvmd.bg_number-1].pti->image.bg_flag )
							break;
					}
					if( old_bg_number == tvmd.bg_number )
						break;
				}
			}
			if(contdata[0].trigger & B_BUTTON){
				old_bg_number = tvmd.bg_number;
				while(1){
					if( tvmd.bg_number== 0 ){
						tvmd.bg_number = num_of_texture;
					} else {
						tvmd.bg_number--;
					}
					if( tvmd.bg_number == 0 ){
						break;
					} else {
						if( td[tvmd.bg_number-1].pti->image.bg_flag )
							break;
					}
					if( old_bg_number == tvmd.bg_number )
						break;
				}
			}
			break;
		default :
			break;
	}
		/*	Change colors	*/
	if( cursor_pos >= 5 )
	{
		switch(cursor_pos)
		{
			case 5 :
				changecolorp = &set_inf.etc.BG_color.rgba.r;
				break;
			case 6 :
				changecolorp = &set_inf.etc.BG_color.rgba.g;
				break;
			case 7 :
				changecolorp = &set_inf.etc.BG_color.rgba.b;
				break;
			case 8 :
				changecolorp = &set_inf.etc.BG_color.rgba.a;
				break;
			case 9 :
				changecolorp = &set_inf.etc.PRIM_color.rgba.r;
				break;
			case 10 :
				changecolorp = &set_inf.etc.PRIM_color.rgba.g;
				break;
			case 11 :
				changecolorp = &set_inf.etc.PRIM_color.rgba.b;
				break;
			case 12 :
				changecolorp = &set_inf.etc.PRIM_color.rgba.a;
				break;
			case 13 :
				changecolorp = &set_inf.etc.ENV_color.rgba.r;
				break;
			case 14 :
				changecolorp = &set_inf.etc.ENV_color.rgba.g;
				break;
			case 15 :
				changecolorp = &set_inf.etc.ENV_color.rgba.b;
				break;
			case 16 :
				changecolorp = &set_inf.etc.ENV_color.rgba.a;
				break;
			default :
				break;
		}
		colorvalue = (s16)(*changecolorp);
			/*	If Z button is being pressed, corresponds Control Stick	*/
		if(contdata[0].button & Z_TRIG){
			colorvalue += x/40;
			colorvalue += y/10;
		}
		if( contdata[0].trigger & B_BUTTON )
			colorvalue--;
		if( contdata[0].trigger & A_BUTTON )
			colorvalue++;
		if( colorvalue < 0 )
			colorvalue = 0;
		if( colorvalue > 255 )
			colorvalue = 255;
		*changecolorp = (u8)colorvalue;
	}
}

/***************************************************************************************
 *	disp_cursor
 *
 *	The cursor display at menu. 
 ***************************************************************************************/
Gfx *disp_cursor(Gfx *gp)
{
	static short x[] = {88,88,88,252,220,
						120,152,184,216,
						120,152,184,216,
						120,152,184,216,};
	static short y[] = {24,34,44,24,34,56,56,56,56,66,66,66,66,76,76,76,76};
	static short width[] = {72,64,56,24,64,24,24,24,24,24,24,24,24,24,24,24,24};
	static u32 color[] = {0xffffff00,0xffffff00,0xffffff00,0xffffff00,0xffffff00,
						  0xff000000,0x00ff0000,0x4040ff00,0xffffff00,
						  0xff000000,0x00ff0000,0x4040ff00,0xffffff00,
						  0xff000000,0x00ff0000,0x4040ff00,0xffffff00};
	static u8 alpha = 0x80;
	static s8 alpha_ch = 3;
	u32 cscolor = (color[cursor_pos] & 0xffffff00) | alpha;
	alpha += alpha_ch;
	if( alpha >= 0xb0 )
		alpha_ch = -3;
	if( alpha <= 0x50 )
		alpha_ch = 3;
	return	disp_square(gp,x[cursor_pos],y[cursor_pos],width[cursor_pos],8,cscolor);
}

/***************************************************************************************
 *	disp_square
 *
 *	Displaying a single color square.  
 ***************************************************************************************/
Gfx	*disp_square(Gfx *gp,short x,short y,short width,short height,u32 color)
{
	gDPPipeSync( gp++ );
	gDPSetPrimColor(gp++,0,0,color>>24,(color>>16)&0xff,(color>>8)&0xff,color&0xff);
	gDPSetCombineMode(gp++,G_CC_PRIMITIVE,G_CC_PRIMITIVE);
	gDPSetRenderMode(gp++,G_RM_XLU_SURF,G_RM_XLU_SURF2);
	gSPTextureRectangle(gp++,x<<2,y<<2,(x+width)<<2,(y+height)<<2,
						0,0,0,0,0);
	return	gp;
}

