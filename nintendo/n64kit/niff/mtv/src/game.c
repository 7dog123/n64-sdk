/*
 *	game.c
 *
 *	controls/reflects operation
 *
 *  Copyright (C) 1998-1999, NINTENDO Co.,Ltd.
 *  Copyright (C) 1998-1999, MONEGI CORPORATION
 */

#include	<ultra64.h>
#include	"nusys.h"
#include	"game.h"
#include	"gfx.h"

/*
 *	game
 *
 *	Main Module
 */
void	game(int pendingGfx)
{
	int	i;
	static	int	nowUseCfb = 0;
	texture_data*	ptxdata = &td[tvmd.texture_number];
	back_dynamicp=&(back_dynamic[0]);
	switch( tvmd.tvmode ){
		case TVMODE_VIEW :
			view_stickcontrol();
			break;
		case TVMODE_MENU :
			menu_stickcontrol();
			break;
		default :
			break;
	}
	if(pendingGfx<3){
		Gfx *gp,*gpstart;
		gpstart = gp = glist[nowUseCfb];
		gp = gfxInit( gp );
		gp = makedisplaylist(gp,nowUseCfb);
		gp = disp_info(gp);
			/*	Display menu	*/
		if( tvmd.tvmode == TVMODE_MENU ){
			gp = DispMenu(gp);
		}
		gDPFullSync(gp++);
		gSPEndDisplayList(gp++);
			/*	display/don't display the task bar 	*/
		if( TASKBAR_ON == tvmd.task_flag ){
			nuGfxTaskStart( gpstart , (s32)(gp-gpstart)*sizeof(Gfx),
							NU_GFX_UCODE_F3DEX , NU_SC_NOSWAPBUFFER );
		    nuDebTaskPerfBar1( 3, 208, NU_SC_SWAPBUFFER );
		} else {
			nuGfxTaskStart( gpstart , (s32)(gp-gpstart)*sizeof(Gfx),
							NU_GFX_UCODE_F3DEX , NU_SC_SWAPBUFFER );
		}
		nuGfxTaskAllEndWait();
		nowUseCfb++;
		if(nowUseCfb>=DEF_MAXFRAME)
			nowUseCfb = 0;
	}
	nuContDataGetEx( &contdata[0] , 0 );
}

/*
 *	makedisplaylist
 *
 *	Creating display list.
 */
Gfx *makedisplaylist(Gfx *gp,int frame)
{
	u16		perseNorm = 0;
	float	nsqrt=1.0f;
	RGBA32	test_bg;
	texture_data*	ptxdata = &td[tvmd.texture_number];
	guPerspective( &back_dynamicp->projection , &perseNorm ,
					40.0f , DEF_ASPECT ,
					10.0f , 5000.0f , 1.0f );
	gSPPerspNormalize( gp++ , perseNorm );
	guLookAt( &back_dynamicp->viewing ,
				0.0f , 0.0f , 330.0f ,	/*Camera reference*/
				0.0f , 0.0f ,   0.0f ,		/*Focal Point*/
				0.0f , 1.0f ,   0.0f );		/*Up vector*/
		/*	Setting strings	*/
	gSPMatrix( gp++ , OS_K0_TO_PHYSICAL(&(back_dynamicp->projection)),
				G_MTX_PROJECTION|G_MTX_LOAD|G_MTX_NOPUSH );
	gSPMatrix( gp++ , OS_K0_TO_PHYSICAL(&(back_dynamicp->viewing)),
				G_MTX_MODELVIEW|G_MTX_LOAD|G_MTX_NOPUSH );
	gSPMatrix( gp++ , OS_K0_TO_PHYSICAL(&(back_dynamicp->translate)),
				G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_NOPUSH );
	gSPMatrix( gp++ , OS_K0_TO_PHYSICAL(&(back_dynamicp->rotate)),
				G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_NOPUSH );
	ptxdata->pti->grid.setup_gfxp = mesh_setup_dl[frame];
	ptxdata->pti->grid.gfxp = mesh_dl[frame];
	ptxdata->pti->grid.vtxp = mesh_vtx[frame];
	mesh_MakeSetupDisplayList( ptxdata );
	mesh_Init(ptxdata,frame);
	gSPDisplayList( gp++ , ptxdata->pti->grid.setup_gfxp );
	gSPDisplayList( gp++ , ptxdata->pti->grid.gfxp );
	return	gp;
}

/*
 *	view_stickcontrol
 *
 *	Controller process
 */
void	view_stickcontrol(void)
{
	float a,b,c,d;
	Mtx m;
	Mtx oldRotate,newCalRotate;
	short	x = (short)(contdata[0].stick_x);
	short	y = (short)(contdata[0].stick_y);
	float	deg;
	u32		old_texture_number;
	short	changevalue = tvmd.speed;
		/*	Controller process	*/
	if( contdata[0].trigger & (U_JPAD|R_JPAD) ){
		if( tvmd.speed<8 ){
			tvmd.speed++;
			tvmd.speed_info_disp_time = 90;
		}
	}
	if( contdata[0].trigger & (D_JPAD|L_JPAD) ){
		if( tvmd.speed>1 ){
			tvmd.speed--;
			tvmd.speed_info_disp_time = 90;
		}
	}
		/*	Z button	*/
	if( contdata[0].button & Z_TRIG ){
		changevalue *= 2;
	}
		/*	AB button	*/
	if(contdata[0].trigger & A_BUTTON){
		old_texture_number = tvmd.texture_number;
		while(1){
			tvmd.texture_number++;
			if( tvmd.texture_number>=num_of_texture )
				tvmd.texture_number = 0;
			if( !(td[tvmd.texture_number].pti->image.bg_flag) )
				break;
					/*
					 *Avoiding infinite loop. And process,
					 *if the all files have the background
					 */
			if( old_texture_number == tvmd.texture_number )
				break;
		}
	}
	if(contdata[0].trigger & B_BUTTON){
		old_texture_number = tvmd.texture_number;
		while(1){
			if( tvmd.texture_number==0 )
				tvmd.texture_number = num_of_texture-1;
			else
				tvmd.texture_number--;
			if( !(td[tvmd.texture_number].pti->image.bg_flag) )
				break;
			if( old_texture_number == tvmd.texture_number )
				break;
		}
	}
		/*	C button unit	*/
	if(contdata[0].button & D_CBUTTONS )
		center_y -= changevalue;
	if(contdata[0].button & U_CBUTTONS )
		center_y += changevalue;
	if(contdata[0].button & R_CBUTTONS )
		center_x += changevalue;
	if(contdata[0].button & L_CBUTTONS )
		center_x -= changevalue;
		/*	R button	*/
	if(contdata[0].trigger & MESH_CONT_MENU_ONOFF)
		tvmd.tvmode = TVMODE_MENU;
		/*	L button	*/
	if(contdata[0].trigger & MESH_CONT_NAME_DISP_CHANGE)
		tvmd.name_flag = 1-tvmd.name_flag;
		/*	Z button and its trigger time	*/
	x /= 6;
	y /= 6;
	if(contdata[0].button & Z_TRIG){
		deg = sqrtf((float)(x*x+y*y));
		if( 0.0f != deg ){
			guRotate( &(newCalRotate),deg,(float)(-y),(float)(x),0.0f );
			oldRotate = back_dynamicp->rotate;
			guMtxCatL(&oldRotate,&newCalRotate,&back_dynamicp->rotate);
		}
	} else {
		center_z -= y;
	}
		/*	Start button process	*/
	if(contdata[0].trigger & MESH_CONT_START_POSITION ){
		center_x = 0;
		center_y = 0;
		center_z = 0;
		guMtxIdent(&(back_dynamicp->rotate));
	}
	guTranslate( &(back_dynamicp->translate),(float)center_x,(float)center_y,(float)center_z );
}

/*
 *	disp_info
 *
 *	Displays a name of texture and its moving speed information.
 */
Gfx *disp_info(Gfx *gp)
{
	short	nameY = 24;
	short	name_width;
	int	i;
	if( NAME_DISP == tvmd.name_flag ){
		if( TVMODE_MENU == tvmd.tvmode )
			nameY = 92;
		i=0;
		while(NULL != td[tvmd.texture_number].name[++i]);
		name_width = (short)i*8;
		gp = disp_square(gp,24,nameY-1,name_width,10,0xffffffa0);
		gDPPipeSync(gp++);
		gp = letters_init(gp);
		gp = letters_set(gp,24,nameY,(unsigned char*)td[tvmd.texture_number].name,0x000000ff);
	}
	if( tvmd.speed_info_disp_time>0 ){
		tvmd.speed_info_disp_time--;
		nameY = 24;
		if( TVMODE_MENU == tvmd.tvmode )
			nameY = 92;
		gp = letters_init(gp);
		gp = letters_set(gp,176,nameY,"SLOW        FAST",0xffffffb0);

		for( i=1;i<(int)tvmd.speed;i++ )
			gp = letters_num(gp,198+8*i,nameY+8,i,0xffffffd0);
		gp = letters_num(gp,198+8*i,nameY+8,i,0x00ffffff);
		i++;
		for( ;i<=8;i++ )
			gp = letters_num(gp,198+8*i,nameY+8,i,0xffffffd0);
	}
	return	gp;
}

