/*======================================================================*/
/*		NIFFprev						*/
/*		nddisp.c						*/
/*									*/
/*		Copyright (C) 1997,1998, NINTENDO Co,Ltd.		*/
/*		Copyright (C) 1998, MONEGI CORPORATION.			*/
/*									*/
/*======================================================================*/
/* Revision History							*/
/*  1998/ 6/ 3	Modify to object manager				*/
/*		Modification due to axis of coordinate of 		*/
/*		ReflectionMapping               			*/
/*  1998/ 6/16	Added color combiner setting for Fog			*/
/*======================================================================*/
#define __NDDISP_C__

/* :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
	Simple 3D manager "ND"

	display driver
 :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: */

#include "pack.h"
#include "nd.h"

/* ===========================================================================
	defines
 =========================================================================== */

/* ===========================================================================
	static variables
 =========================================================================== */
static Gfx ForceAlignmentPadding0[] = { gsSPEndDisplayList() };

/* ---------------------------------------------------------------------------
	Viewport
 --------------------------------------------------------------------------- */
static Vp vp = {
	SCREEN_WD*2, SCREEN_HT*2, G_MAXZ/2, 0,	/* scale */
	SCREEN_WD*2, SCREEN_HT*2, G_MAXZ/2, 0,	/* translate */
};

/* ---------------------------------------------------------------------------
	RDP full initialize
 --------------------------------------------------------------------------- */
Gfx rdpstateinit_dl[] = {

    /* set all of the attribute registers to zero */
    gsDPSetEnvColor(0,0,0,0),
    gsDPSetPrimColor(0,0,0,0,0,0),
    gsDPSetBlendColor(0,0,0,0),
    gsDPSetFogColor(0,0,0,0),
    gsDPSetFillColor(0),
    gsDPSetPrimDepth(0,0),
    gsDPSetConvert(0,0,0,0,0,0),
    gsDPSetKeyR(0,0,0),
    gsDPSetKeyGB(0,0,0,0,0,0),

    /* set combine mode */
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),

    /* initialize the scissor box */
    gsDPSetScissor(G_SC_NON_INTERLACE, 0, 0, SCREEN_WD, SCREEN_HT),

    /* initialize all the texture tile descriptors to zero */
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0),

    gsDPSetTileSize(0, 0, 0, (1 - 1) << G_TEXTURE_IMAGE_FRAC, (1 - 1) <<
		G_TEXTURE_IMAGE_FRAC),
    gsDPSetTileSize(1, 0, 0, (1 - 1) << G_TEXTURE_IMAGE_FRAC, (1 - 1) <<
		G_TEXTURE_IMAGE_FRAC),
    gsDPSetTileSize(2, 0, 0, (1 - 1) << G_TEXTURE_IMAGE_FRAC, (1 - 1) <<
		G_TEXTURE_IMAGE_FRAC),
    gsDPSetTileSize(3, 0, 0, (1 - 1) << G_TEXTURE_IMAGE_FRAC, (1 - 1) <<
		G_TEXTURE_IMAGE_FRAC),
    gsDPSetTileSize(4, 0, 0, (1 - 1) << G_TEXTURE_IMAGE_FRAC, (1 - 1) <<
		G_TEXTURE_IMAGE_FRAC),
    gsDPSetTileSize(5, 0, 0, (1 - 1) << G_TEXTURE_IMAGE_FRAC, (1 - 1) <<
		G_TEXTURE_IMAGE_FRAC),
    gsDPSetTileSize(6, 0, 0, (1 - 1) << G_TEXTURE_IMAGE_FRAC, (1 - 1) <<
		G_TEXTURE_IMAGE_FRAC),
    gsDPSetTileSize(7, 0, 0, (1 - 1) << G_TEXTURE_IMAGE_FRAC, (1 - 1) <<
		G_TEXTURE_IMAGE_FRAC),
    gsDPPipeSync(),
    gsSPEndDisplayList(),
};

/* ---------------------------------------------------------------------------
	RCP basic initialize
 --------------------------------------------------------------------------- */
static Gfx gfxinit_dl[]={
    /* init state */
    gsSPViewport(&vp),
    gsSPClearGeometryMode(G_SHADE | G_SHADING_SMOOTH | G_CULL_BOTH |
			  G_FOG | G_LIGHTING | G_TEXTURE_GEN |
			  G_TEXTURE_GEN_LINEAR | G_LOD),
    gsSPSetGeometryMode(G_SHADE | G_SHADING_SMOOTH),
    gsSPTexture(0, 0, 0, 0, G_OFF),

    /* buffer fill */
    gsDPPipeSync(),
    gsSPDisplayList(rdpstateinit_dl),

    gsSPEndDisplayList(),
};

/* ---------------------------------------------------------------------------
	Z buffer initialize
 --------------------------------------------------------------------------- */
static Gfx clearzbuffer_dl[] = {
    gsDPSetCycleType(G_CYC_FILL),
    gsDPSetRenderMode(G_RM_NOOP, G_RM_NOOP2),
    gsDPSetColorImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WD,
		      SEGTOP(ZBUF_SEGMENT)),
    gsDPFillRectangle(0, 0, SCREEN_WD-1, SCREEN_HT-1),
    gsDPSetDepthImage(SEGTOP(ZBUF_SEGMENT)),
    gsDPPipeSync(),
    gsSPEndDisplayList(),
};

/* ---------------------------------------------------------------------------
	CFB initialize
 --------------------------------------------------------------------------- */
static Gfx clearcfb_dl[] = {
    gsDPSetCycleType(G_CYC_FILL),
    gsDPSetRenderMode(G_RM_NOOP, G_RM_NOOP2),
    gsDPSetColorImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WD,
		      SEGTOP(CFB_SEGMENT)),
    gsDPFillRectangle(0, 0, SCREEN_WD-1, SCREEN_HT-1),
    gsDPPipeSync(),
    gsSPEndDisplayList(),
};

/* ===========================================================================
	public functions
 =========================================================================== */

/* ----------------------------------------------------------------------------
name:
    ndClearFB
synopsis:
    Gfx *ndClearFB(Gfx *gp, u16 fill_depth, u16 fill_col);
description:
parameter:
    Gfx *gp;
	Display list pointer
    u16 fill_depth;
	Values to fill Z-buffer
    u16 fill_col;
	Values to fill color values
return:
    Gfx *gp;
	Display list pointer
notes:
---------------------------------------------------------------------------- */
Gfx *ndClearFB(Gfx *gp, u16 fill_depth, u16 fill_col)
{
    u32 value;

    /* set and initialize Z buffer defaults */
    value = ((u32)fill_depth)&0xffff;
    gDPSetFillColor( gp++, (value|(value<<16)));
    gSPDisplayList( gp++, clearzbuffer_dl );

    /* set and initialize of CFB defaults */
    value = ((u32)fill_col)&0xffff;
    gDPSetFillColor( gp++, (value|(value<<16)));
    gSPDisplayList( gp++, clearcfb_dl );

    return gp;
}

/* ----------------------------------------------------------------------------
name:
    ndEvalLight
synopsis:
    int ndEvalLight(float *tarpos, NDD_LIGHT *lp, RGBAQUAD *color, s8 *nv);
description:
    Updates light information from information of initialize light structure
    and the object location, and returns the color value and light vector.
parameter:
    float *tarpos;
	Target position where light is placed. 3 values - x, y, z.
	If NULL, calculate as the origin (0,0,0)
    NDD_LIGHT *lp;
	Pointer to light structure.
    RGBQUAD *color;
	Pointer for RGBAQUAD structure to store color value. 
    s8 *nv;
	Pointer to store light vector. 3 values in S0.7 form x,y,z (3 byte).
return:
    int;
	When evaluating light, if light is invalid, 0 is returned.
notes:
    NDD_LIGHT structure has following restrictions: 
    Normal given by fnv must be normalized. 
    When NDC_LFLAG_ATTENUATION is set in a flag, it's necessary to assign
	valid values to start and end.
    NDC_LFLAG_CUTOFF is only valid for NDC_LFLAG_HAVEPOS. These can be checked	at the cost of execution speed, but it is ignored as it's manager for
    	games.
      If the return value is 0, color and nv are unfixed.
---------------------------------------------------------------------------- */
int ndEvalLight(float *tarpos, NDD_LIGHT *lp, RGBAQUAD *color, s8 *nv)
{
    int i;
    u32 flag;
    float d, dist, power, *fnv, *ltv, tmpnv[3];
    static float pos_zero[]={ 0, 0, 0 };

    flag = lp->flag;

    /* Provide light source vector in fnv */
    if( BITTEST1(flag, NDC_LFLAG_HAVEPOS) ){
	/* Pseudo point light source */
	dist = ndguCalcNormal(tmpnv, lp->fpos, (tarpos)? tarpos: pos_zero);
	fnv = tmpnv;
	if( BITTEST1(flag, NDC_LFLAG_CUTOFF) ){
	    /* Determine outside the range of light source valid angle by CUTOFF*/
	    ltv = lp->fnv;
	    d = fnv[0]*ltv[0] + fnv[1]*ltv[1] + fnv[2]*ltv[2];  /* inner product*/
	    d = (1.0 - lp->cutoff) + lp->cutoff * d;
	    if(d <= 0) return FALSE;	/* Light is invalid*/
	    power = d;
	}
    }else{
	/* Parallel source light */
	fnv = lp->fnv;
	dist = power = 1.0;
    }

    /* Create parameter to set register */
    d = 127.0/dist;
    nv[0] = fnv[0]*d;
    nv[1] = fnv[1]*d;
    nv[2] = fnv[2]*d;

    /* Re-calculation of color level by the distance between light spot and mode
     Note! values of  start and end are always treated as valid values.
            Please note if unusual value is input, it will run away.
    */
    if( BITTEST(flag, NDC_LFLAG_ATTENUATION) ){
	if(dist < lp->start) return FALSE;  /* Invalid is too close */
	if(dist > lp->end) return FALSE;  /* Invalid is too far */
	power *=
	  1.0 - ((dist - lp->start) / (lp->end - lp->start));
    }

    /* Caluculation and assignment of color information */
    memcpy(color, &lp->color, sizeof(RGBAQUAD));
    i = power * 255.0;
    if(i < 1) return FALSE;	/* Light color is invalid */

    /* Adjust color level */
    ndguCalcFadeColor( color, 0, (i>255)? 255: i, 0 );

    /* This light is valid */
    return TRUE;
}

/* ----------------------------------------------------------------------------
name:
    ndReloadLightReg
synopsis:
    Gfx *ndReloadLightReg(Gfx *gp, NDD_LIGHT *lp, u32 newcolor, s8 *newlvec);
description:
    Update light information relating to light structure.
    Will be called from ndSetupLightset function.
parameter:
    Gfx *gp;
	Display list pointer
    NDD_LIGHT *lp;
	Pointer for light structure
    u32 newcolor;
	Color value to be set anew.  Must be stored in the form of 0xRRGGBB00 
	from upper bit.  The lower 8 bits will be handled as 0x00 inside.
    s8 *newlvec;
	Pointer for vector to be set anew.  Look for 3 values x,y,z (3 byte) in
	the form of S0.7.  NULL won't be accepted.	
    return:
    Gfx *gp;
	Display list pointer
notes:
    Of NDD_LIGHT structure, refer to color, power, and stored_nv, define the 
    heap of necessary portion, and store RSP command in the buffer.
    AS this function is optimized toward the inside usage, please understand
    the contents before using it when calling it at a user's option.
---------------------------------------------------------------------------- */
Gfx *ndReloadLightReg(Gfx *gp, NDD_LIGHT *lp, u32 newcolor, s8 *newlvec)
{
    /* Fix the unfixed portion of color values  */
    newcolor &= 0xffffff00;

    /* In case of setting for the 2nd time or after, update the setting
	 by the finite difference of the previous setting */
    if( BITTEST1(lp->flag, NDC_LFLAG_ALREADY_SETS) ){
	/* Compare with previously set light vector */
	if(lp->stored_nv[0] == newlvec[0] && lp->stored_nv[1] == newlvec[1] &&
	   lp->stored_nv[2] == newlvec[2]){

	    /* Light vector matches, what about color? */
	    if(lp->stored_color == newcolor)
	      return gp;	/* If matches, not necessary to re-set anything */

	    /* Update only the color register */
	    lp->stored_color = newcolor;
	    return ndgSPLightColor(gp, lp->lnum, newcolor);
	}
    }

    /* Store to register */
    memcpy(lp->stored_nv, newlvec, 3);
    lp->stored_color = newcolor;

    /* Create display list */
    gp = gfxSetLight( gp, lp->lnum, newcolor, newlvec);
    BITSET(lp->flag, NDC_LFLAG_ALREADY_SETS);

    return gp;
}

/* ----------------------------------------------------------------------------
name:
    ndSetupLightset
synopsis:
    Gfx *ndSetupLightset(Gfx *gp, float *tarpos, NDD_LIGHTSET *lightset);
description:
    Evaluate the initialized light set passed by lightset, along with the 
    object, and store only the revised portion in the display list.
parameter:
    Gfx *gp;
	Display list pointer.
    float *tarpos;
	Target position where light is placed on.  3 values of x,y,z.
	If NULL calculate as the origin (0,0,0).
    NDD_LIGHTSET *lightset;
	Pointer for light set structure
return:
    Gfx *gp;
	Display list pointer.
notes:
    The argument tarpos is passed to AndEvalLight() as is and evaluated.
    If the result is NULL, it will evaluate replacing with origin.
---------------------------------------------------------------------------- */
Gfx *ndSetupLightset(Gfx *gp, float *tarpos, NDD_LIGHTSET *lightset)
{
    int i;
    union {
	RGBAQUAD rq;
	u32 val;
    } newcolor;
    s8 newlvec[3];
    static s8 dummy_lvec[]={ 0, 0, 127 };
    NDD_LIGHT *lp;
    int lcnt = lightset->numlights;

    if(lcnt){
	/* If there is at least one valid light, set normally */
	for(i=0; i<lcnt; ++i){
	    lp = &lightset->light[i];
	    if( BITTEST1(lp->flag, NDC_LFLAG_ENABLE) ){
		if(ndEvalLight( tarpos, lp, &newcolor.rq, newlvec ))
		  gp = ndReloadLightReg(gp, lp, newcolor.val, newlvec);
		else
		  gp = ndReloadLightReg(gp, lp, 0, dummy_lvec);
	    }
	}
    }else{
	/* If all the lights are invalid, set a colorless light */
	gp = gfxSetLight( gp, 1, 0, dummy_lvec );
	lcnt = 1;
    }

    /* Set ambient color */
    memcpy(&i, &lightset->ambient, 4);
    gp = gfxSetAmbient( gp, lcnt+1, i&0xffffff00);

    gSPNumLights(gp++, lcnt);

    return gp;
}

/* ----------------------------------------------------------------------------
name:
    ndInitLights
synopsis:
    int ndInitLights( NDD_LIGHTSET *lightset );
description:
    Re-set the light setting for RDP, determine the number of lights, 
    and assign light numbers for every light structure.
parameter:
    NDD_LIGHTSET *lightset;
	Pointer for light set structure.
return:
    int;
	The number of valid light.
notes:
    Refer to ENABLE bit of flag for each light structure, sum up the 
    necessary number of lights and assign each light number.
    These numbers are light numbers that are evaluated by RSP actually, 
    but users don't need to be particularly aware of this.  Refer to them
    when re-setting by API function
---------------------------------------------------------------------------- */
int ndInitLights( NDD_LIGHTSET *lightset )
{
    int i, lcnt;
    NDD_LIGHT *lp;

    /* Embeded light number to light structure and clarify the number of
       valid lights */
    lp = &lightset->light[0];
    for( i=lcnt=0; i<NUM_LIGHTSET_LIGHTS; ++i ){
	if( BITTEST1(lp[i].flag, NDC_LFLAG_ENABLE) ){
	    /* allocate light numbers */
	    lp[i].lnum = 1+lcnt;
	    /* Register hasn't been set yet */
	    BITRESET(lp[i].flag, NDC_LFLAG_ALREADY_SETS);
	    ++lcnt;
	}
    }

    return lightset->numlights = lcnt;
}

/* ----------------------------------------------------------------------------
name:
    ndSetupObjectRegister
synopsis:
    Gfx *ndSetupObjectRegister( Gfx *gp, NDD_INST_OBJ *niop );
description:
    Refer to the object instance structure and re-set a register that is
    specified to be re-set.
parameter:
    Gfx *gp;
	Pointer for dislpay list buffer.
    NDD_INST_OBJ *niop;
	Pointer for object instance structure.
return:
    Gfx *;
	Updated Gfx buffer pointer.
notes:
    Will be called from ndDrawObjectInstance.
---------------------------------------------------------------------------- */
Gfx *ndSetupObjectRegister( Gfx *gp, NDD_INST_OBJ *niop )
{
    int mode;
    Gfx *render_mode_gfx = NULL;
    union{
	u32 i;
	u8 c[4];
    }col;
    int flag = niop->flag;

    /* Pipe sync is extended by default */
    gDPPipeSync(gp++);

    /* Set RenderMode */
    if( BITTEST1(flag, NDC_OFLAG_RENDERMODE) )
      render_mode_gfx = gp = ndgDPSetRenderMode(gp, niop->rdmode);

    /* Set AlphaCompare */
    if( BITTEST1(flag, NDC_OFLAG_ALPHACOMPARE) ){
	switch( niop->rdmode & NDC_RM_ALPHA_COMPARE){
	  case NDC_RM_ALPHA_COMPARE_THRESHOLD:
	    mode = G_AC_THRESHOLD;
	    break;
	  case NDC_RM_ALPHA_COMPARE_DITHER:
	    mode = G_AC_DITHER;
	    break;
	  case NDC_RM_ALPHA_COMPARE_NONE:
	  default:
	    mode = G_AC_NONE;
	    break;
	}
	gDPSetAlphaCompare(gp++, mode);
    }

    /* Set AlphaDither */
    if( BITTEST1(flag, NDC_OFLAG_ALPHADITHER) ){
	switch( niop->rdmode & NDC_RM_DITHER_ALPHA){
	  case NDC_RM_DITHER_ALPHA_PATTERN:
	    mode = G_AD_PATTERN;
	    break;
	  case NDC_RM_DITHER_ALPHA_NOPATTERN:
	    mode = G_AD_NOTPATTERN;
	    break;
	  case NDC_RM_DITHER_ALPHA_NOISE:
	    mode = G_AD_NOISE;
	    break;
	  case NDC_RM_DITHER_ALPHA_DISABLE:
	  default:
	    mode = G_AD_DISABLE;
	    break;
	}
	gDPSetAlphaDither(gp++, mode);
    }

    /* Set CycleType */
    if( BITTEST1(flag, NDC_OFLAG_CYCLETYPE) ){
	if(BITTEST1(niop->flag, NDC_OFLAG_2CYC)){
	    /* 2cycle mode */
	    gDPSetCycleType(gp++, G_CYC_2CYCLE);
	}else{
	    /* 1cycle mode */
	    gDPSetCycleType(gp++, G_CYC_1CYCLE);
	}
    }

    /* Set ColorCombineMode */
    if( BITTEST1(flag, NDC_OFLAG_CCMODE) )
      gp = ndgDPSetCombineMode(gp, niop->cc1, niop->cc2);

    /* Set GeomMode */
    if( BITTEST1(flag, NDC_OFLAG_GEOMMODE) ){
	gSPClearGeometryMode(gp++, -1);
	gSPSetGeometryMode(gp++, niop->geommode);
    }

    /* Set PrimColor */
    if( BITTEST1(flag, NDC_OFLAG_PRIMCOLOR) ){
	col.i = niop->primcol;
	gDPSetPrimColor(gp++, niop->prim_m, niop->prim_l,
			col.c[0], col.c[1], col.c[2], col.c[3]);
    }

    /* Set EnvColor */
    if( BITTEST1(flag, NDC_OFLAG_ENVCOLOR) ){
	col.i = niop->envcol;
	gDPSetEnvColor(gp++, col.c[0], col.c[1], col.c[2], col.c[3]);
    }

    /* Set FogColor */
    if( BITTEST1(flag, NDC_OFLAG_FOGCOLOR) ){
	col.i = niop->fogcol;
	gDPSetFogColor(gp++, col.c[0], col.c[1], col.c[2], col.c[3]);
    }

    /* Set BleandColor */
    if( BITTEST1(flag, NDC_OFLAG_BLEANDCOLOR) ){
	col.i = niop->blcol;
	gDPSetBlendColor(gp++, col.c[0], col.c[1], col.c[2], col.c[3]);
    }

    /* Create Mtx structure from 4x4 matrix, and register to GIB
	       as MODELVIEW matrix */
    if( BITTEST1(flag, NDC_OFLAG_MATRIX) ){
	Mtx tmpmtx;

	if(BITTEST1(niop->flag, NDC_OFLAG_BILLBOARD)){
	    /* Make LookAt matrix when the billboard processing is done.
		       caution!  the error processing is not done at all.
		       when a false setting is done, it hangs by guLookAt. */
	    float *eye, *at;
	    float nv[3];
	    eye = &niop->modelview[3][0];
	    at = &niop->bb_obj[0]->u.obj.modelview[3][0];
	    ndguCalcNormal( nv, eye,
			 &niop->bb_obj[1]->u.obj.modelview[3][0]);
	    guLookAt( &tmpmtx,
		     eye[0], eye[1], eye[2],
		     at[0], at[1], at[2],
		     nv[0], nv[1], nv[2]);
	}else{
	    guMtxF2L(niop->modelview, &tmpmtx);
	}
	gp = gfxLoadMatrix(gp, &tmpmtx);
    }

    if( niop->combine_gfx ){
	niop->combine_gfx->words.w0 = niop->combinemode.words.w0;
	niop->combine_gfx->words.w1 = niop->combinemode.words.w1;
    }

    /* This is code for Fog, but it is aggressive method, please don't
	take as reference */
    if(( cur_scene.fog.near != cur_scene.fog.far )&&( cur_scene.fog.enable )){
	gDPSetCycleType(gp++, G_CYC_2CYCLE);
	if(( render_mode_gfx )&&0){
	    gDPSetRenderMode(gp++, G_RM_FOG_SHADE_A,
			render_mode_gfx->words.w1 & ~GBL_c1(3, 3, 3, 3) );
	}else{
	    gDPSetRenderMode(gp++, G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2);
	}
	gDPSetFogColor(gp++, cur_scene.fog.color.r, cur_scene.fog.color.g,
		       cur_scene.fog.color.b, cur_scene.fog.color.a);
	gSPSetGeometryMode(gp++, G_FOG|G_SHADE);
	gSPFogPosition(gp++, cur_scene.fog.near, cur_scene.fog.far);
	if(( niop->combine_gfx )&&( !BITTEST1(niop->flag, NDC_OFLAG_2CYC) )){
	    niop->combine_gfx->words.w0 =
			niop->combinemode.words.w0 & 0xFFFFFE00
				| _SHIFTL(G_CCMUX_0,5,4)
				| _SHIFTL(G_CCMUX_0,0,5);
	    niop->combine_gfx->words.w1 =
			niop->combinemode.words.w1 & 0xF003FE00
				| _SHIFTL(G_CCMUX_0,24,4)
				| _SHIFTL(G_ACMUX_0,21,3)
				| _SHIFTL(G_ACMUX_0,18,3)
				| _SHIFTL(G_CCMUX_COMBINED,6,3)
				| _SHIFTL(G_ACMUX_0,3,3)
				| _SHIFTL(G_ACMUX_COMBINED,0,3);
	}
    }

    return gp;
}

/* ----------------------------------------------------------------------------
name:
    ndDrawShape
synopsis:
    Gfx *ndDrawShape( Gfx *gp, NDR_SHAPE *shp );
description:
    According to the contents of shape structure, store Gfx structure in 
    the drawing buffer.
parameter:
    Gfx *gp;
	Pointer for display list buffer.
    NDR_SHAPE *shp;
	Pointer for shape structure for reference.
return:
    Gfx *;
	Updated Gfx buffer pointer.
notes:
    Will be called from ndDrawObjectInstance.
---------------------------------------------------------------------------- */
Gfx *ndDrawShape( Gfx *gp, NDR_SHAPE *shp )
{
    /* Set segment register */
    if(shp->vtx)
      gSPSegment(gp++, shp->vtxsegno, shp->vtx);
    if(shp->img)
      gSPSegment(gp++, shp->imgsegno, shp->img);
    if(shp->tlut)
      gSPSegment(gp++, shp->tlutsegno, shp->tlut);
    gSPDisplayList(gp++, shp->gfx);

    return gp;
}

/* ----------------------------------------------------------------------------
name:
    ndDrawObjectInstance
synopsis:
    int ndDrawObjectInstance( NDD_INST_OBJ *niop );
description:
    Display 1 object
parameter:
    Gfx *gp;
	Pointer for display list buffer.
    NDD_INST_OBJ *niop;
	Poniter for object instance structure.
return:
    Gfx *;
	Updated Gfx buffer pointer.
notes:
    Will be called from ndBuildInstanceGfx
---------------------------------------------------------------------------- */
Gfx *ndDrawObjectInstance( Gfx *gp, NDD_INST_OBJ *niop )
{
    int flag = niop->flag;

    if(BITTEST(flag, NDC_OFLAG_ENABLE|NDC_OFLAG_VISIBLE)){

	/* Set each register
	 Note:  It's assumed that even without shape, it is possible to 
	 update a register.  Depending on users' needs, it may be better
	 to rewrite composing with the if-sentence below. */
	if( flag & NDC_OFLAG_ALLREG )
	  gp = ndSetupObjectRegister( gp, niop );

	/* Allocate display list */
	if(niop->shape)
	  gp = ndDrawShape( gp, niop->shape );
    }
    return gp;
}

/* ----------------------------------------------------------------------------
name:
    ndBuildInstanceGfxAtPrio
synopsis:
    Gfx *ndBuildInstanceGfxAtPrio(Gfx *gp, NDD_INSTANCE *isp, u16 start, u16 end);
description:
    Draw the instance of the specific priority for the specified instance
    pointer and after.
parameter:
    Gfx *gp;
	Display list pointer.
    NDD_INSTANCE *isp;
	The instance pointer.  If NULL is given, will evaluate all
	under the object list.
    u16 start;
	Priority for drawing.  Stare is also included for drawing.
    u16 end;
	Priority not for drawing.  Please note that end is not drawn.
return:
    Gfx *;
	The updated display list pointer.
notes:
    For the size of start and end, take start have bigger value (higher priority).
---------------------------------------------------------------------------- */
Gfx *ndBuildInstanceGfxAtPrio(Gfx *gp, NDD_INSTANCE *isp, u16 start, u16 end)
{
    /* isp == NULL all */
    if(!isp)
      isp = obj_root_instp;

    /* display evaluation from designated instance */
    for(; isp!=&bottom_inst; isp=isp->next)
      if(isp->type == NDC_ITYPE_OBJECT && isp->prio <= start)
	break;

    /* If nothing is applicable, do nothing */
    if(isp==&bottom_inst)
      return gp;

    /* Display and evaluate from specified instance */
    for(; isp!=&bottom_inst; isp=isp->next){
	if(isp->prio <= end)
	  break;
	if(isp->type == NDC_ITYPE_OBJECT)
	  gp = ndDrawObjectInstance( gp, &isp->u.obj );
    }

    return gp;
}

/* ----------------------------------------------------------------------------
name:
    ndBuildInstanceGfx
synopsis:
    Gfx *ndBuildInstanceGfx(Gfx *gp, NDD_INSTANCE *isp);
description:
    Builds scene part display list from current scene structure.
parameter:
    Gfx *gp;
	Display list pointer.
    NDD_INSTANCE *isp;
	Instance pointer in question.  When NULL is given, it evaluates under
	object route.
return:
    Gfx *;
	The updated display list pointer.
notes:
    Inside.  not ndBuildInstanceGfxAtPrio() is called as giving all the 
    priorities of the object.
---------------------------------------------------------------------------- */
Gfx *ndBuildInstanceGfx(Gfx *gp, NDD_INSTANCE *isp)
{
    return ndBuildInstanceGfxAtPrio( gp, isp,
	    NDC_IPRIO_OBJROOT, NDC_IPRIO_OBJEND+1);
}

/* ----------------------------------------------------------------------------
name:
    ndBuildSceneGfx
synopsis:
    Gfx *ndBuildSceneGfx(Gfx *gp, float mul[4][4]);
description:
    Builds the scene part display list from the current scene structure.
parameter:
    Gfx *gp;
	Display list pointer.
    float mul[4][4];
	Camera matrix.
return:
    Gfx *;
	Display list pointer.
notes:
    mul, which is the camera matrix, carries out multiplication to the 
    projection matrix.
---------------------------------------------------------------------------- */
Gfx *ndBuildSceneGfx(Gfx *gp, float mul[4][4])
{
    /* begin RCP drawing */
    gSPDisplayList( gp++, gfxinit_dl);

    /* Initialize Z-buffer and CFB */
    gp = ndClearFB(gp, cur_scene.fill_depth, cur_scene.fill_col);

    /* reflect fog parameters */
    if(cur_scene.fog.near != cur_scene.fog.far){
	gSPFogPosition(gp++, cur_scene.fog.near, cur_scene.fog.far);
	gDPSetFogColor(gp++, cur_scene.fog.color.r, cur_scene.fog.color.g,
		       cur_scene.fog.color.b, cur_scene.fog.color.a);
    }

    /* reflect camera */
    gp = gfxMulPerspective( gp,
	   cur_scene.camera.fovy,
	   cur_scene.camera.aspect,
	   cur_scene.camera.near,
	   cur_scene.camera.far,
	   cur_scene.camera.scale,
	   mul);

#if 1
    /* Create reflection structure */
    /* reserve: LookAt is created here with values that are parallel with
		    mul which is a camera matrix, as a reflection.  It's up 
		    to a user in reality. */
    {
	float d;
	s8 rv[3], uv[3];

	d = 127.0/sqrtf(mul[0][0]*mul[0][0]+mul[1][0]*mul[1][0]+
			mul[2][0]*mul[2][0]);
	rv[0] = mul[0][0]*d;
	rv[1] = mul[1][0]*d;
	rv[2] = mul[2][0]*d;

	d = 127.0/sqrtf(mul[0][1]*mul[0][1]+mul[1][1]*mul[1][1]+
			mul[2][1]*mul[2][1]);
	uv[0] = mul[0][1]*d;
	uv[1] = mul[1][1]*d;
	uv[2] = mul[2][1]*d;

	gp = gfxLookAtReflect( gp, rv, uv);
    }
#else
    {
	float	at[ 3 ], up[ 3 ], eye[ 3 ];
	static LookAt	lookat;

	/*
	    Mapping for N64 environment is convert normal itself to texture 
	    coordinate to make process simple.
	    So, when view is changed but model doesn't move, 
	    texture doesn't move, and it is not natural.
	    Following codes tone this down. */
	eye[ 0 ] = 0.0;
	eye[ 1 ] = 0.0;
	eye[ 2 ] = 1.5;

	at[ 0 ] = mul[ 0 ][ 2 ];
	at[ 1 ] = mul[ 1 ][ 2 ];
	at[ 2 ] = mul[ 2 ][ 2 ];

	up[ 0 ] = 0.0;
	up[ 1 ] = 1.0;
	up[ 2 ] = 0.0;

	guLookAtReflectF( mul, &lookat, eye[ 0 ], eye[ 1 ], eye[ 2 ],
					at[ 0 ], at[ 1 ], at[ 2 ],
					up[ 0 ], up[ 1 ], up[ 2 ] );
	gSPLookAt( gp++, &lookat );
    }
#endif
#if 0
    gp = gfxLookAtReflect( gp, &cur_scene.reflect.right[0],
			  &cur_scene.reflect.upper[0]);	
#endif

    /* Setting for lighting */
    ndInitLights( &cur_scene.lightset );
    gp = ndSetupLightset(gp, NULL, &cur_scene.lightset);

    return gp;
}
