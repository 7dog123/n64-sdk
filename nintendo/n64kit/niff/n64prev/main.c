/*======================================================================*/
/*		NIFFprev						*/
/*		main.c							*/
/*									*/
/*		Copyright (C) 1997, NINTENDO Co,Ltd.			*/
/*		Copyright (C) 1998, MONEGI CORPORATION.			*/
/*									*/
/*======================================================================*/
/* Revision History							*/
/*  1998/ 6/ 3	Define process mode, set to use mode.h 			*/
/*		Set to call menu					*/
/*		Modified to object management				*/
/*  1998/ 6/15	Set to operate object and/or light			*/
/*  1998/ 6/18	Improved the animation operation			*/
/*  1998/ 6/19	Moving assignment of light				*/
/*  1998/ 7/ 7	Camera animation.Bug was fixed.				*/
/*  1998/ 8/20  Support quick preview                                   */
/*  1998/11/25	ST animation						*/
/*======================================================================*/

#include "pack.h"
#include "menu.h"
#include "mode.h"
#ifdef __ISV__
# include "is_debug.h"
# include "is_debug.c"
#endif

#include "nd.h"
#include "model.h"		/* model data header file */
#include "nusys.h"

extern Gfx Gfx_NCube[];
extern MENU gRootMenu;

/* ========================================================================== 
	define
 ========================================================================== */
#define MAX_OBJ 300
#define MAX_SHAPE 300
#define MAX_ANIM 300
#define MAX_RAWVTX 300
#define MAX_RAWVTXCOL 300
#define MAX_RAWVTXNV 300
#define MAX_RAWVTXST 300
#define MODELDATA_ROM_TOP 0x200000

/* ===========================================================================
	variables
 =========================================================================== */
MODE gMode;
EXCONTPAD *pad;
NDD_RESINFO *cur_resource;

static Gfx ForceAlignmentPadding[] = { gsSPEndDisplayList() };

#if 0
static Lights2 default_lightset = gdSPDefLights2(
      120, 120, 120,			 /* ambient light */
        0,   0,   0,  73,  73, -73,	 /* optional light */
      255, 255, 255,  73,  73,  73);	 /* sun light */
#endif

static Lights1 n64cube_lightset = gdSPDefLights1(
      127, 127, 127,
      255, 255, 255,  24,  70,  66);

static Gfx *setup_SP_DP(Gfx *gp)
{
    /* various settings */
    gSPClearGeometryMode( gp++, G_SHADE | G_SHADING_SMOOTH | G_CULL_BOTH
      | G_FOG | G_LIGHTING | G_TEXTURE_GEN
      | G_TEXTURE_GEN_LINEAR | G_LOD );
    gSPSetGeometryMode( gp++, G_SHADE | G_LIGHTING /*| G_SHADING_SMOOTH */
      | G_ZBUFFER | G_CULL_BACK );
    gSPFogPosition( gp++, 996, 1000);
    gSPClipRatio( gp++, FRUSTRATIO_2 );
    gDPSetCombineKey( gp++, G_CK_NONE );
    gSPTexture( gp++, 0, 0, 0, 0, G_OFF );
    gDPSetCycleType( gp++, G_CYC_1CYCLE );
    gDPSetCombineMode( gp++, G_CC_SHADE, G_CC_SHADE );
    gDPSetRenderMode( gp++, G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2 );
    gDPSetAlphaCompare( gp++, G_AC_NONE );
    gDPSetTextureFilter( gp++, G_TF_BILERP);

    gDPSetColorDither( gp++, G_CD_BAYER);

    gDPSetAlphaDither( gp++, G_AD_NOTPATTERN );
    gDPSetBlendMask( gp++, 0xff);
    gDPPipelineMode( gp++, G_PM_NPRIMITIVE);

    return gp;
}

/* ===========================================================================
	functions
 =========================================================================== */
static void resetreg(void)
{
    tbReset();
    crReset();

    gMode.control = CONTROL_OBJECT;
    gMode.control_mode = CONTROL_MODE_TRACKBALL;
    gMode.anim_mode = ANIM_TOGGLE;

    modeResetCamera( &gMode );
    modeResetObject( &gMode );
    modeResetLights( &gMode );
    modeResetBG( &gMode );
    modeResetFog( &gMode );
    modeLoadVideoMode( &gMode );
}

/*
  Find simple inverse matrix
*/
static void invert( float dest[4][4], float src[4][4] )
{
    dest[0][0] = src[0][0];
    dest[0][1] = src[1][0];
    dest[0][2] = src[2][0];
    dest[0][3] = 0.0f;
    dest[1][0] = src[0][1];
    dest[1][1] = src[1][1];
    dest[1][2] = src[2][1];
    dest[1][3] = 0.0f;
    dest[2][0] = src[0][2];
    dest[2][1] = src[1][2];
    dest[2][2] = src[2][2];
    dest[2][3] = 0.0f;
    dest[3][0] = -dest[0][0] * src[3][0] - dest[1][0] * src[3][1] -
		  dest[2][0] * src[3][2];
    dest[3][1] = -dest[0][1] * src[3][0] - dest[1][1] * src[3][1] -
		  dest[2][1] * src[3][2];
    dest[3][2] = -dest[0][2] * src[3][0] - dest[1][2] * src[3][1] -
		  dest[2][2] * src[3][2];
    dest[3][3] = 1.0f;
}

/* ---------------------------------------------------------------------------
	Virtual Camera Function
 --------------------------------------------------------------------------- */
static void camera_action( void )
{
    float	identity[4][4];
    float	caminv[4][4];

    if( ( cur_scene.enacam )&&( gMode.camera_mode == CAMERA_SCENE ) ){
	guMtxIdentF(identity);
	ndEvalInstance( cur_scene.cam[ 0 ].root, identity, 1 );
	ndEvalInstance( cur_scene.cam[ 1 ].root, identity, 1 );
	ndEvalInstance( cur_scene.cam[ 2 ].root, identity, 1 );

	ndMakeCameraMatrix(caminv);

	invert( gMode.camera_transform.matrix, caminv );

	gMode.camera_transform.translation[0] =
				gMode.camera_transform.matrix[3][0];
	gMode.camera_transform.translation[1] =
				gMode.camera_transform.matrix[3][1];
	gMode.camera_transform.translation[2] =
				gMode.camera_transform.matrix[3][2];
    }
}

/* ---------------------------------------------------------------------------
	Controller Function
 --------------------------------------------------------------------------- */
static void control_action(Transform *transform)
{
    static int last_control_mode = CONTROL_MODE_TRACKBALL;
    static int last_control = CONTROL_OBJECT;
    switch( gMode.control_mode ){
	default:
	case CONTROL_MODE_TRACKBALL:
	    /* Virtual Track Ball */
	    tbEmulate(pad, transform);
	    tbBuildMatrix(transform);
	    break;
	case CONTROL_MODE_CRUISE:
	    /* Cruising */
	    if( ( last_control_mode != gMode.control_mode )||
		( last_control != gMode.control ) ) crSetupYPR(transform);
	    crMove(pad);
	    crBuildMatrix(transform);
	    break;
    }
    last_control_mode= gMode.control_mode;
    last_control = gMode.control;
}

/* ---------------------------------------------------------------------------
	Virtual game main function
	It is not true that if enter once, don't get out. This is a function, 
	which process once for one frame.
 --------------------------------------------------------------------------- */
void gamemain(float caminv[4][4])
{
    Transform	*transform_ptr;
    
    switch( gMode.control ){
	default:
	case CONTROL_CAMERA:
	    transform_ptr = &gMode.camera_transform;
	    break;
	case CONTROL_OBJECT:
	    transform_ptr = &gMode.object_transform;
	    break;
	case CONTROL_LIGHT1:
	    transform_ptr = &gMode.light_transform[0];
	    break;
	case CONTROL_LIGHT2:
	    transform_ptr = &gMode.light_transform[1];
	    break;
	case CONTROL_LIGHT3:
	    transform_ptr = &gMode.light_transform[2];
	    break;
	case CONTROL_LIGHT4:
	    transform_ptr = &gMode.light_transform[3];
	    break;
	case CONTROL_LIGHT5:
	    transform_ptr = &gMode.light_transform[4];
	    break;
	case CONTROL_LIGHT6:
	    transform_ptr = &gMode.light_transform[5];
	    break;
	case CONTROL_LIGHT7:
	    transform_ptr = &gMode.light_transform[6];
	    break;
    }

/*
#if !(PREVIEW_TYPE & 0x01)
*/
    /* Start and stop for geometry animation */
    if( gMode.anim_mode == ANIM_STEP ){
	gMode.anim_step = 0.0f;
	if( cur_scene.nobj && pad[0].trigger & CONT_B )
	    gMode.anim_step = -cur_scene.framerate;
	if( cur_scene.nobj && pad[0].trigger & CONT_A )
	    gMode.anim_step = cur_scene.framerate;
    }else{
	if( cur_scene.nobj && pad[0].trigger & CONT_B ){
	    if( gMode.anim_step != 0.0 ) gMode.anim_step = 0.0f;
	    else gMode.anim_step = -1.0;
	}
	if( cur_scene.nobj && pad[0].trigger & CONT_A ){
	    if( gMode.anim_step != 0.0 ) gMode.anim_step = 0.0f;
	    else gMode.anim_step = 1.0;
	}
    }
/*
#endif
*/
    control_action( transform_ptr );
    camera_action( );

    invert( caminv, gMode.camera_transform.matrix );
}

/* ---------------------------------------------------------------------------
	Pseudo Check Function

	It is processed many times in GameMain, an it is seldom divided
	like this.  However, for 3D games, it may be better if the process
	is divided roughly, like this, and the improvement of the game
	system is repeated.
	
	Here, 1 function of Manager is similarly called.
 --------------------------------------------------------------------------- */
static void eval(float mf[4][4])
{
    ndEvalInstance( root_instp, mf, 1);
}

/* ---------------------------------------------------------------------------
	Virtual Draw Function

	For SNES, it was only processed during vertical retrace synchronism
	or during a horizontal blank.
	Thanks to the double frame buffer method, it is possible to draw 
	almost any time, but it will be simplified if drawing is considered
	as the last process of 1 frame as it reflects the last processing 
	result.
	
	At processing time, display list pointer has the scene and model.
 --------------------------------------------------------------------------- */
static Gfx *draw(Gfx *gp, float caminv[4][4])
{
    extern Mtx NCube_mtx;
    Mtx m;
    float tmpmf[4][4];

    guMtxIdentF( tmpmf );
    memcpy( &tmpmf[0][0], &gMode.camera_transform.matrix[0][0],
	    sizeof( float ) * 16 );
    /* Draw polygon */
    switch( gMode.active_object ){
	default:
	case OBJECT_NINTENDO:	/* N-cube */
	    gp = ndBuildSceneGfx(gp, caminv);
	    gp = setup_SP_DP( gp );

#if 1
	    guMtxF2L(gMode.object_transform.matrix, &m);
	    gp = gfxLoadMatrix( gp, &m);
/*
	    gSPNumLights( gp++, 1);
	    gSPSetLights1( gp++, n64cube_lightset);
*/
	    gp = ndSetupLightset( gp, gMode.object_transform.matrix[3],
				  &cur_scene.lightset );
	    gDPSetColorDither( gp++, G_CD_DISABLE);
#endif
	    gSPDisplayList( gp++, Gfx_NCube);
	    break;
	case OBJECT_SCENE:	/* converted objects(scene) */
	    gp = ndBuildSceneGfx(gp, caminv);
	    gp = setup_SP_DP( gp );
#if 0
	    gSPNumLights( gp++, 2);
	    gSPSetLights2( gp++, default_lightset);
#endif
	    gp = ndBuildInstanceGfx( gp, obj_root_instp);
	    break;
    }
    return gp;
}

void setup_default_light( void )
{
    int		i;
    int		light_index;
    NDD_LIGHT	*light;

    light_index = 0;
    for(i=0; i<NUM_LIGHTSET_LIGHTS; ++i){
	if( ( gMode.light_color[i].r != 0 )||( gMode.light_color[i].g != 0 )||
	    ( gMode.light_color[i].b != 0 ) ){
	    light = &cur_scene.lightset.light[light_index];
	    light->flag = NDC_LFLAG_ENABLE;
	    light->color.r = gMode.light_color[i].r;
	    light->color.g = gMode.light_color[i].g;
	    light->color.b = gMode.light_color[i].b;
	    light->fnv[0] = -gMode.light_transform[i].matrix[0][0];
	    light->fnv[1] = -gMode.light_transform[i].matrix[0][1];
	    light->fnv[2] = -gMode.light_transform[i].matrix[0][2];
	    ++light_index;
	}
    }
    for(i=light_index; i<NUM_LIGHTSET_LIGHTS; ++i){
	light = &cur_scene.lightset.light[light_index];
	light->flag = 0;
    }

    cur_scene.lightset.numlights = /*light_index*/NUM_LIGHTSET_LIGHTS;
    cur_scene.lightset.ambient.r = gMode.ambient.r;
    cur_scene.lightset.ambient.g = gMode.ambient.g;
    cur_scene.lightset.ambient.b = gMode.ambient.b;
}

void setup_scene_light( NDR_SCENE *scene )
{
    int i;
    int nlight;
    NDR_SCN_LIGHT *lp;

    /* Reading writing information */
    memcpy(&cur_scene.lightset.ambient, &scene->light.amb_color,
	       sizeof(RGBAQUAD));
    cur_scene.lightset.numlights = nlight = scene->light.nlight;
    lp = scene->light.light;
    for(i=0; i<nlight; ++i){
	    /* Set prepared light as usual */
	memcpy(&cur_scene.lightset.light[i].color, &lp->color,
	       sizeof(RGBAQUAD));
	if(lp->type){
		/* Point light */
	    cur_scene.lightset.light[i].flag =
		  NDC_LFLAG_ENABLE | NDC_LFLAG_HAVEPOS;
	    cur_scene.lightset.light[i].fpos[0] = lp->x;
	    cur_scene.lightset.light[i].fpos[1] = lp->y;
	    cur_scene.lightset.light[i].fpos[2] = lp->z;
	}else{
	    /* Parallel light */
	    cur_scene.lightset.light[i].flag = NDC_LFLAG_ENABLE;
	    cur_scene.lightset.light[i].fnv[0] = lp->x;
	    cur_scene.lightset.light[i].fnv[1] = lp->y;
	    cur_scene.lightset.light[i].fnv[2] = lp->z;
	}
	cur_scene.lightset.light[i].start = lp->a1;
	cur_scene.lightset.light[i].end = lp->a2;
    }
    for(i=nlight; i<NUM_LIGHTSET_LIGHTS; ++i)
		cur_scene.lightset.light[i].flag = 0;
}

static void build_scene( void )
{
    cur_scene.fill_col = Color4iPackRGBA5551( &gMode.bg_color );
    cur_scene.fog.color.r = gMode.fog.color.r;
    cur_scene.fog.color.g = gMode.fog.color.g;
    cur_scene.fog.color.b = gMode.fog.color.b;
    cur_scene.fog.color.a = gMode.fog.color.a;
    cur_scene.fog.near = gMode.fog.near;
    cur_scene.fog.far = gMode.fog.far;
    cur_scene.fog.enable = gMode.fog.enable;
    switch( gMode.active_light ){
	default:
	case LIGHT_DEFAULT:
	    setup_default_light( );
	    break;
	case LIGHT_SCENE:
	    setup_scene_light( RESINFO_NAME.scene );
	    break;
    }
}

NDD_RESINFO *get_cur_res(void)
{
    static char p[16];
    NDD_RESINFO *cur_res;    
    u32          rom_res;
    long         res_len;
    NDR_RESINFO *ram_res;
 
    /* Make sure there is import model data */
    nuPiReadRom( MODELDATA_ROM_TOP, (void*)p, 16 );
    if(p[0]=='n' && p[1]=='i' && p[2]=='f' && p[3]=='f'){
	/* Read import model data as resource */
	rom_res = MODELDATA_ROM_TOP+16;
	res_len = ((u32)(u8)p[12]<<24) + ((u32)(u8)p[13]<<16) 
	  + ((u32)(u8)p[14]<<8) + ((u32)(u8)p[15]);      /* If there is no u8, ot will process wrong */
	res_len -= 16;

	/* Resource ROM to RAM */
	ram_res =malloc( res_len );

	if( ram_res==NULL){
	  cur_res = ndResEntry(&RESINFO_NAME, NDC_RES_USED_ALL);
	  return cur_res;
	}
	nuPiReadRom( rom_res, (void*)ram_res, (u32)res_len );

	/* pointer mapping */
	ndResLinkAbs( ram_res );

	/* register resouce to nd */
	cur_res = ndResEntry(ram_res, NDC_RES_USED_ALL);

	/* display import */
	nuDebConTextPos(0, 30, 4);
	nuDebConTextColor(0, 7);
	nuDebConCPuts(0, "IMPORT");
	
      }
    /* If there is no import model data, use model.c data. */
    else cur_res = ndResEntry(&RESINFO_NAME, NDC_RES_USED_ALL);

    return cur_res;
  }


/* ---------------------------------------------------------------------------
	Main Function

	Main function is user dependent. This won't change.
 --------------------------------------------------------------------------- */
void mainproc(void *arg)
{
    Gfx *gp;

#ifdef __ISV__
    isPrintfInit( );
#endif

    /* Initialize graphic module */
    gfxInit();

    /* Initialize memory manager */
    minit();

    /* Initialize controller */
    expadInitControllers( 4, 20, 4 );

    /* Determine animation flag ahead of time */
    pad = expadReadController();

    /* Initialize 'nd' manager
     ndResInit()defines the entrire number of resource lists to be
     used in the game. The number of resource lists are defined by a
     macro called MAX_* at the beginning of main.c */
    ndInit();
    ndResInit( MAX_OBJ, MAX_SHAPE, MAX_ANIM, MAX_RAWVTX, MAX_RAWVTXCOL,
	       MAX_RAWVTXNV, MAX_RAWVTXST);

    /* Resource register */
/*    cur_resource = ndResEntry(&RESINFO_NAME, NDC_RES_USED_ALL); */
    cur_resource = get_cur_res();

    /* entry of scene of object
	please change the following according to type of view */
#if 1
    /* entry from scene data */
    ndSetupScene( cur_resource, 0, 0x3f/*PREVIEW_TYPE|2|1*/);
    cur_scene.anim_time = 0.0;
    modeLoadDefaultBG( &gMode, &cur_scene );
    modeLoadDefaultFog( &gMode, &cur_scene );
#else
    /* enter single object */
    /* not in use now */
    cur_scene.nobj=1;
    cur_scene.obj=malloc( sizeof( NDD_OBJ_INFO ) );
    cur_scene.obj[0].root=ndEntryObject( NULL, 1,/* cur_resource->obj.ofs,*/
					 cur_resource->shape.ofs,
					 cur_resource->anim.ofs,
					 0,
					 (PREVIEW_TYPE & 1)+2);
    gMode.geom_anim_enable = PREVIEW_TYPE & 1;
#endif
    /* Initialize register for pad (rotation etc.) */
    resetreg();

    while(1){
	static float caminv[4][4];

	build_scene( );

	/* Game main */
	gamemain(caminv);

	/* update object manager */
	eval(gMode.object_transform.matrix);

	/* menu management */
	menu( &gRootMenu, pad, NULL );

	/* display time */
	{
	    static char time[ ] = "          ";
	    nuDebConTextPos(0, 30, 3);
	    nuDebConTextColor(0, 7);
	    if( cur_scene.anim_time >= 0.0 ){
		sprintf( time, "%05d", ( int )( cur_scene.anim_time + 0.5 ) );
	    }else{
		sprintf( time, "%05d", 0 );
	    }
	    nuDebConCPuts(0, time);
	}

	modeStoreVideoMode( &gMode );

	/* construct drawing data */
	if(gp = gfxBegin()){
	    gp = draw( gp, caminv );
	    gfxEnd(gp);
	    gfxFlush();
	}

	/* update pad data */
	pad = expadReadController();

	gfxWaitSync();

	if ( cur_scene.framerate ){
	    cur_scene.anim_time += gMode.anim_step / cur_scene.framerate;
	    if( cur_scene.anim_time > ( float )cur_scene.end_anim )
			cur_scene.anim_time = 0.0;
	    if( cur_scene.anim_time < 0.0 )
			cur_scene.anim_time = ( float )cur_scene.end_anim;
	}
    }
}
