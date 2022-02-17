/*======================================================================*/
/*		NIFFprev						*/
/*		ndeval.c						*/
/*									*/
/*		Copyright (C) 1997,1998, NINTENDO Co,Ltd.		*/
/*		Copyright (C) 1998, MONEGI CORPORATION.			*/
/*									*/
/*======================================================================*/
/* Revision History							*/
/*  1998/ 6/ 3  Change to object management				*/
/*  1998/ 6/ 5  Manage global time					*/
/*  1998/ 6/13  Change Deform method					*/
/*  1998/ 6/19  Manage scene time					*/
/*  1998/11/25	ST animation						*/
/*======================================================================*/
#define __NDEVAL_C__

/* ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
	Simple 3D manager "ND"

	Evaluation functions
 :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: */

#include "pack.h"
#include "nd.h"

/* ===========================================================================
	defines
 =========================================================================== */

/* ===========================================================================
	variables
 =========================================================================== */

/* ----------------------------------------------------------------------------
name:
    ndGetInstanceTRXPointer
synopsis:
    TRX *ndGetInstanceTRXPointer(NDD_INSTANCE *isp);
description:
    Return the pointer of the transform buffer from the instance pointer
parameter:
    NDD_INSTANCE *isp;
	The instance pointer
return:
notes:
    Why there is such a function is because the TRX position of the
    instance structure varies depending on data types.
---------------------------------------------------------------------------- */
TRX *ndGetInstanceTRXPointer(NDD_INSTANCE *isp)
{
    if(isp->type == NDC_ITYPE_OBJECT){
	return &isp->u.obj.trx;
    }if(isp->type == NDC_ITYPE_NULL){
	return &isp->u.obj.trx;
    }

    return NULL;
}

/* ----------------------------------------------------------------------------
name:
    ndSetupIdentTRX
synopsis:
    void ndSetupIdentTRX(TRX *p)
description:
    Return the unit matrix.
parameter:
    TRX *p;
	The pointer for the transform matrix.
return:
notes:
	Substitute 0, 0, 0, 0, 0, 0, 1, 1 and 1, which are equivalent to the
      unit matrix, to the total of 9 parameters of translating, rotating 
      and scaling. respectively.
---------------------------------------------------------------------------- */
void ndSetupIdentTRX(TRX *p)
{
    static TRX ident={0,0,0, 0,0,0, 1,1,1};

    memcpy(p, &ident, sizeof(TRX));
}

/* ----------------------------------------------------------------------------
name:
    ndMakeCameraMatrix
synopsis:
    void ndMakeCameraMatrix(float mf[4][4])
description:
    Create the camera matrix(LookAt) from the camera information.
parameter:
return:
notes:
    Be careful that it is not the matrix related to "PROJECTION_VIEW" 
    like "Perspective," etc.
---------------------------------------------------------------------------- */
void ndMakeCameraMatrix(float mf[4][4])
{
    TRX *ep, *up, *ap;

    if(cur_scene.enacam){
	ep = ndGetInstanceTRXPointer(cur_scene.cam[0].root);
	up = ndGetInstanceTRXPointer(cur_scene.cam[1].root);
	ap = ndGetInstanceTRXPointer(cur_scene.cam[2].root);
	guLookAtF(mf, ep->tx, ep->ty, ep->tz,
	          ap->tx, ap->ty, ap->tz,
	          up->tx - ep->tx, up->ty - ep->ty, up->tz - ep->tz);
    }else{
	guMtxIdentF( mf );
    }
}

/* ---------------------------------------------------------------------------
name:
    ndProgressAnimTime
synopsis:
    int ndProgressAnimTime(NDD_INST_ANIMTK *ntkp);
description:
    The time progressing process of the time keeper.
parameter:
    NDD_INST_ANIMTK *ntkp
	Pointer for animation time keeper instance.
return:
    int;
	Execution result.  Currently 1 is always returned.
notes:
    Will be called from ndEvalInstance
 --------------------------------------------------------------------------- */
int ndProgressAnimTime(NDD_INST_ANIMTK *ntkp)
{
    float time;
    int i;

    /* Move the time ahead */
    if ( cur_scene.anim_time < 0.0 ) time = ntkp->time + ntkp->timescale;
    else time = cur_scene.anim_time;

    /* Examine if it goes beyond the end time */
    if(time > ntkp->end){
	/* reserve: Foricibly loop for now */
	time = ntkp->start;
    }

    /* Determine the time */
    ntkp->time = time;

    /* Deliver the time value to the entered animation instance */
    for(i=0; i<ntkp->naniminst; ++i)
      ntkp->animinst[i]->u.anim.time = time;

    return TRUE;
}

/* ---------------------------------------------------------------------------
name:
    ndSetAnimChannel
synopsis:
    int ndSetAnimChannel(NDD_INST_ANIM *niap);
description:
    The channel process of the key frame animation.
parameter:
    NDD_INST_ANIM *niap;
	Pointer from animation instance.
return:
    Execution result.
notes:
    will be called from ndEvalInstance 
 --------------------------------------------------------------------------- */
int ndSetAnimChannel(NDD_INST_ANIM *niap)
{
    int i;
    float c1, c2, time, v1, v2;
    float *fvp;

    /* Watch the time */
    time = niap->time;

    /* Get out if it is not in the replay range */
    if(time < niap->start || time > niap->end)
      return FALSE;

    /* -----------------------------------------------------------
       It is traced which key correspondeds with the present time
	 value if it is in replay range (Otherwise, data is wrong)
       ----------------------------------------------------------- */

    /* Look for key that the self should refer to  */
    i = niap->nowkeypos;
    if(time < niap->key[i]){
	/* The time seemed to move to opposite direction */
	for(--i; time < niap->key[i]; --i)
	  ;
    }else{
	/* Search in order from key value that you had referred just before */
	for(; time > (float)niap->key[i]; ++i)
	  ;
	--i;
    }

    /* Get the TRX pointer of the host instance */
    fvp = (float*)ndGetInstanceTRXPointer(niap->tarinst);

    /* Take next "Key" and compare with the present time */
    c2 = niap->key[i+1];
    if(time == c2){
	/* If they match, set there to "nowkeypos" and return "value[nowkeypos]" */
	niap->nowkeypos = i+1;
	fvp[niap->kind] = niap->value[niap->nowkeypos];
    }else{
	/* nterpolate between c1 and c2.  Only "Linear" at present */
	c1 = niap->key[i];
	v1 = niap->value[i];
	v2 = niap->value[i+1];
	fvp[niap->kind] = v1+(v2-v1)/(c2-c1)*(time-c1);
    }

    /* Instruct the matrix recalculation  */
    BITRESET(niap->tarinst->flag, NDC_IFLAG_MTX_READY);
    return TRUE;
}

/* ---------------------------------------------------------------------------
name:
    ndReloadDynamicVertex
synopsis:
    void ndReloadDynamicVertex(NDD_INST_DYNAMICVTX *nidp);
description:
    Refer to the modulation table of various deform instances and make Vtx.
parameter:
    NDD_INST_DYNAMICVTX *nidp;
	Pointer for internal structure of active instance.
return:
notes:
    Depends partially on the drawing driver, and two Vtx tables to be set
    are prepared.
 --------------------------------------------------------------------------- */
void ndReloadDynamicVertex(NDD_INST_DYNAMICVTX *nidp)
{
    int i, j, nvtx;
    NDR_SHAPE *dsp;
    Vtx *tar;
    s16 *vmap;
    s32 *mvp;
    s16 *mnp, *mcp;
    s32 *msp;

    if ( building_gb == -1 ) return;
	/* this is still initialize time, get out with doing nothing */

    /* Change shape Vtx of host object */
    dsp = nidp->dyn_shape;
    tar = nidp->tarvtx[building_gb];
    vmap = dsp->shaperef;
    mvp = (nidp->dfminst[0])?
      nidp->dfminst[0]->u.dfm_vtx.modify_vtx: NULL;
    mcp = (nidp->dfminst[1])?
      nidp->dfminst[1]->u.dfm_vtxcol.modify_vtxcol: NULL;
    mnp = (nidp->dfminst[2])?
      nidp->dfminst[2]->u.dfm_vtxnv.modify_vtxnv: NULL;
    msp = (nidp->dfminst[3])?
      nidp->dfminst[3]->u.dfm_vtxst.modify_vtxst: NULL;

    nvtx = dsp->nvtx;
    for(i=0; i<nvtx; ++i){
	/* vertex */
	if(mvp && (*vmap>=0)){
	    j = *vmap + (*vmap<<1);
	    tar[i].n.ob[0] = mvp[j++] >> 16;
	    tar[i].n.ob[1] = mvp[j++] >> 16;
	    tar[i].n.ob[2] = mvp[j] >> 16;
	}
	++vmap;

	/* vertex color */
	if(mcp && (*vmap>=0)){
	    j = *vmap<<2;
	    tar[i].v.cn[0] = mcp[j++] >> 8;
	    tar[i].v.cn[1] = mcp[j++] >> 8;
	    tar[i].v.cn[2] = mcp[j++] >> 8;
	    tar[i].v.cn[3] = mcp[j] >> 8;
	}
	++vmap;

	/* vertex nv */
	if(mnp && (*vmap>=0)){
	    j = *vmap + (*vmap<<1);
	    tar[i].n.n[0] = mnp[j++] >> 8;
	    tar[i].n.n[1] = mnp[j++] >> 8;
	    tar[i].n.n[2] = mnp[j] >> 8;
	}
	++vmap;

	/* vertex st */
	if(msp && (*vmap>=0)){
	    j = *vmap<<1;
	    tar[i].v.tc[0] = msp[j++] >> 16;
	    tar[i].v.tc[1] = msp[j] >> 16;
	}
	++vmap;
    }

    /* List the Vtx buffer cache that was re-written */
    osWritebackDCache(tar, nvtx*sizeof(Vtx));

    /* Change shape Vtx of host object */
    dsp->vtx = tar;
}

/* ---------------------------------------------------------------------------
name:
    ndDeformVertex
synopsis:
    void ndDeformVertex(NDD_INST_DEFORM_VTX *nidvp);
description:
    Perform the vertex deform
parameter:
    NDD_INST_DEFORM_VTX *nidvp;
	Pointer for internal structure of vertex deform instance.
return:
notes:
 --------------------------------------------------------------------------- */
void ndDeformVertex(NDD_INST_DEFORM_VTX *nidvp)
{
    int i,nelem;
    s32 *mvp;
    s16	*s0, *s1;
#ifdef _FAST_DEFORM_
    s32 *delta;
#endif

    nelem = nidvp->nelem+(nidvp->nelem<<1);  /* x3 */
    mvp = nidvp->modify_vtx;

#ifdef _FAST_DEFORM_
    delta = nidvp->delta;
    if(nidvp->downcounter){
	/* Modulate vertex color for amount of finite difference */
	for(i=0; i<nelem; ++i)
	  mvp[i] += delta[i];
	--nidvp->downcounter;
    }else{
	int key, dc;
	float div;

	/* Advance key */
	key = ++nidvp->nowkey;
	if(key >= nidvp->nkey)
	  key=1;
	nidvp->nowkey = key;

	/* Initialize modulation vertex position, and calculate fininte difference */
	s0 = nidvp->rawvtx[key-1];
	s1 = nidvp->rawvtx[key];
	dc = nidvp->key[key] - nidvp->key[key-1];
	div = 65536.0/dc;
	for(i=0; i<nelem; ++i){
	    mvp[i] = (s32)s0[i]<<16;
	    delta[i] = (s32)(((float)s1[i]-s0[i])*div);
	}

	/* Set new value for downcounter */
	nidvp->downcounter = dc;
    }
#else
    if( cur_scene.anim_time < 0.0 ){
	/* Initialize key */
	nidvp->nowkey = 1;

	/* Initialize modulation vertex position */
	s0 = nidvp->rawvtx[0];
	for(i=0; i<nelem; ++i){
	    mvp[i] = (s32)s0[i]<<16;
	}
	nidvp->downcounter = 0;
    }else{
	int	key;
	float	time;
	float	weight;
	float	comp;

	key = nidvp->nowkey;
	if ( key < 1 ) key = 1;
	time = cur_scene.anim_time - nidvp->downcounter;
	while( time < nidvp->key[key-1] ){
	    --key;
	    if( key <= 0 ){
		key = nidvp->nkey-1;
	    }
	}
	while( time > nidvp->key[key] ){
	    ++key;
	    if( key >= nidvp->nkey ){
		key = 1;
	    }
	}
	nidvp->nowkey = key;
	weight = ( time - nidvp->key[key-1] ) /
		 ( float )( nidvp->key[key] - nidvp->key[key-1] );
	comp = 1.0f - weight;
	weight *= 65536.0;
	comp *= 65536.0;
	s0 = nidvp->rawvtx[key-1];
	s1 = nidvp->rawvtx[key];
	for(i=0; i<nelem; ++i){
	    mvp[i] = s0[i] * comp + s1[i] * weight;
	}
    }
#endif
}

/* ---------------------------------------------------------------------------
name:
    ndDeformVertexNv
synopsis:
    void ndDeformVertexNv(NDD_INST_DEFORM_VTXNV *nidcp);
description:
    Perform vertex normal deform.
parameter:
    NDD_INST_DEFORM_VTXNV *nidcp;
	Pointer for internal structure of vertex normal deform instance.
return:
notes:
 --------------------------------------------------------------------------- */
void ndDeformVertexNv(NDD_INST_DEFORM_VTXNV *nidcp)
{
    int i,nelem;
    s16 *mcp;
    s8 *s0, *s1;
#ifdef _FAST_DEFORM_
    s16 *delta;
#endif

    nelem = nidcp->nelem+(nidcp->nelem<<1);  /* x3 */
    mcp = nidcp->modify_vtxnv;

#ifdef _FAST_DEFORM_
    delta = nidcp->delta;
    if(nidcp->downcounter){
	/* Modulate vertex color for amount of finite difference */
	for(i=0; i<nelem; ++i)
	  mcp[i] += delta[i];
	--nidcp->downcounter;
    }else{
	int key, dc;
	float div;

	/* Advance key */
	key = ++nidcp->nowkey;
	if(key >= nidcp->nkey)
	  key=1;
	nidcp->nowkey = key;

	/* Initialize modulation vertex position, and calculate fininte difference  */
	s0 = nidcp->rawvtxnv[key-1];
	s1 = nidcp->rawvtxnv[key];
	dc = nidcp->key[key] - nidcp->key[key-1];
	div = 256.0/dc;
	for(i=0; i<nelem; ++i){
	    mcp[i] = (s16)s0[i]<<8;
	    delta[i] = (s16)(((float)s1[i]-s0[i])*div);
	}

	/* Set new value for downcounter */
	nidcp->downcounter = dc;
    }
#else
    if( cur_scene.anim_time < 0.0 ){
	/* Initialize key */
	nidcp->nowkey = 1;

	/* Initialize modulation vertex position */
	s0 = nidcp->rawvtxnv[0];
	for(i=0; i<nelem; ++i){
	    mcp[i] = (s16)s0[i]<<8;
	}
	nidcp->downcounter = 0;
    }else{
	int	key;
	float	time;
	float	weight;
	float	comp;

	key = nidcp->nowkey;
	if ( key < 1 ) key = 1;
	time = cur_scene.anim_time - nidcp->downcounter;
	while( time < nidcp->key[key-1] ){
	    --key;
	    if( key <= 0 ){
		key = nidcp->nkey-1;
	    }
	}
	while( time > nidcp->key[key] ){
	    ++key;
	    if( key >= nidcp->nkey ){
		key = 1;
	    }
	}
	nidcp->nowkey = key;
	weight = ( time - nidcp->key[key-1] ) /
		 ( float )( nidcp->key[key] - nidcp->key[key-1] );
	comp = 1.0f - weight;
	weight *= 256.0;
	comp *= 256.0;
	s0 = nidcp->rawvtxnv[key-1];
	s1 = nidcp->rawvtxnv[key];
	for(i=0; i<nelem; ++i){
	    mcp[i] = s0[i] * comp + s1[i] * weight;
	}
    }
#endif
}

/* ---------------------------------------------------------------------------
name:
    ndDeformVertexColor
synopsis:
    void ndDeformVertexColor(NDD_INST_DEFORM_VTXCOL *nidcp);
description:
    Perform the vertex color deform.
parameter:
    NDD_INST_DEFORM_VTXCOL *nidcp;
	Pointer for internal structure of vertex normal deform instance.
return:
notes:
 --------------------------------------------------------------------------- */
void ndDeformVertexColor(NDD_INST_DEFORM_VTXCOL *nidcp)
{
    int i,nelem;
    s16 *mcp;
    u8 *s0, *s1;
#ifdef _FAST_DEFORM_
    s16 *delta;
#endif

    nelem = nidcp->nelem<<2;  /* x4 */
    mcp = nidcp->modify_vtxcol;

#ifdef _FAST_DEFORM_
    delta = nidcp->delta;
    if(nidcp->downcounter){
	/* Modulate vertex color for amount of finite difference */
	for(i=0; i<nelem; ++i)
	  mcp[i] += delta[i];
	--nidcp->downcounter;
    }else{
	int key, dc;
	float div;

	/* Advance key */
	key = ++nidcp->nowkey;
	if(key >= nidcp->nkey)
	  key=1;
	nidcp->nowkey = key;

	/* Initialize modulation vertex position, and calculate fininte difference */
	s0 = (u8*)nidcp->rawvtxcol[key-1];
	s1 = (u8*)nidcp->rawvtxcol[key];
	dc = nidcp->key[key] - nidcp->key[key-1];
	div = 256.0/dc;
	for(i=0; i<nelem; ++i){
	    mcp[i] = (s16)s0[i]<<8;
	    delta[i] = (s16)(((float)s1[i]-s0[i])*div);
	}

	/* Set new value for downcounter */
	nidcp->downcounter = dc;
    }
#else
    if( cur_scene.anim_time < 0.0 ){
	/* Initialize key */
	nidcp->nowkey = 1;

	/* Initialize modulation vertex position */
	s0 = (u8*)nidcp->rawvtxcol[0];
	for(i=0; i<nelem; ++i){
	    mcp[i] = (s16)s0[i]<<8;
	}
	nidcp->downcounter = 0;
    }else{
	int	key;
	float	time;
	float	weight;
	float	comp;

	key = nidcp->nowkey;
	if ( key < 1 ) key = 1;
	time = cur_scene.anim_time - nidcp->downcounter;
	while( time < nidcp->key[key-1] ){
	    --key;
	    if( key <= 0 ){
		key = nidcp->nkey-1;
	    }
	}
	while( time > nidcp->key[key] ){
	    ++key;
	    if( key >= nidcp->nkey ){
		key = 1;
	    }
	}
	nidcp->nowkey = key;
	weight = ( time - nidcp->key[key-1] ) /
		 ( float )( nidcp->key[key] - nidcp->key[key-1] );
	comp = 1.0f - weight;
	weight *= 256.0;
	comp *= 256.0;
	s0 = (u8*)nidcp->rawvtxcol[key-1];
	s1 = (u8*)nidcp->rawvtxcol[key];
	for(i=0; i<nelem; ++i){
	    mcp[i] = s0[i] * comp + s1[i] * weight;
	}
    }
#endif
}

/* ---------------------------------------------------------------------------
name:
    ndDeformVertexSt
synopsis:
    void ndDeformVertexSt(NDD_INST_DEFORM_VTXST *nidcp);
description:
    Perfomn vertex texture deform
parameter:
    NDD_INST_DEFORM_VTXST *nidcp;
	Pointer for internal structure of vertex normal deform instance.
return:
notes:
 --------------------------------------------------------------------------- */
void ndDeformVertexSt(NDD_INST_DEFORM_VTXST *nidcp)
{
    int i,nelem;
    s32 *mvp;
    s16	*s0, *s1;
#ifdef _FAST_DEFORM_
    s32 *delta;
#endif

    nelem = nidcp->nelem<<1;  /* x2 */
    mvp = nidcp->modify_vtxst;

#ifdef _FAST_DEFORM_
    delta = nidvp->delta;
    if(nidvp->downcounter){
	/* Modulate vertex color for amount of finite difference */
	for(i=0; i<nelem; ++i)
	  mvp[i] += delta[i];
	--nidcp->downcounter;
    }else{
	int key, dc;
	float div;

	/* Advance key */
	key = ++nidcp->nowkey;
	if(key >= nidcp->nkey)
	  key=1;
	nidcp->nowkey = key;

	/* Initialize modulation vertex position, and calculate fininte difference */
	s0 = nidcp->rawvtx[key-1];
	s1 = nidcp->rawvtx[key];
	dc = nidcp->key[key] - nidcp->key[key-1];
	div = 65536.0/dc;
	for(i=0; i<nelem; ++i){
	    mvp[i] = (s32)s0[i]<<16;
	    delta[i] = (s32)(((float)s1[i]-s0[i])*div);
	}

	/* Set new value for downcounter */
	nidcp->downcounter = dc;
    }
#else
    if( cur_scene.anim_time < 0.0 ){
	/* Initialize key */
	nidcp->nowkey = 1;

	/* Initialize modulation vertex position */
	s0 = nidcp->rawvtxst[0];
	for(i=0; i<nelem; ++i){
	    mvp[i] = (s32)s0[i]<<16;
	}
	nidcp->downcounter = 0;
    }else{
	int	key;
	float	time;
	float	weight;
	float	comp;

	key = nidcp->nowkey;
	if ( key < 1 ) key = 1;
	time = cur_scene.anim_time - nidcp->downcounter;
	while( time < nidcp->key[key-1] ){
	    --key;
	    if( key <= 0 ){
		key = nidcp->nkey-1;
	    }
	}
	while( time > nidcp->key[key] ){
	    ++key;
	    if( key >= nidcp->nkey ){
		key = 1;
	    }
	}
	nidcp->nowkey = key;
	weight = ( time - nidcp->key[key-1] ) /
		 ( float )( nidcp->key[key] - nidcp->key[key-1] );
	comp = 1.0f - weight;
	weight *= 65536.0;
	comp *= 65536.0;
	s0 = nidcp->rawvtxst[key-1];
	s1 = nidcp->rawvtxst[key];
	for(i=0; i<nelem; ++i){
	    mvp[i] = s0[i] * comp + s1[i] * weight;
	}
    }
#endif
}

/* ----------------------------------------------------------------------------
name:
    ndMultiTrx
synopsis:
    void ndMultiTrx(float mf[4][4], TRX *trxp, u32 order);
description:
    Evaluate the TRX structure and create 4x4 matrix.
parameter:
    float mf[4][4];
	The buffer which stores the matrix to create.
    TRX *trxp;
	The transform data structure which becomes the origin of the matrix.
    u32 order;
	The evaluation order of rotational components.
return:
    None
notes:
    The created "4x4" matrix is put on the buffer within the instance 
    work and used for displaying.
---------------------------------------------------------------------------- */
void ndMultiTrx(float mf[4][4], TRX *trxp, u32 order)
{
    /* If you customize this part adjusting to each game content to create,
       you can speed up effectively */
    ndguTranslateF(mf, trxp->tx, trxp->ty, trxp->tz);

    /* Reflect rotational elements of every axes */
    if(trxp->rx!=0.0 || trxp->ry!=0.0 || trxp->rz!=0.0){
	switch(order){
	  case NDC_ROTORDER_XYZ:
	    ndguRotateXYZF( mf, RAD2DEG(trxp->rx),
			   RAD2DEG(trxp->ry), RAD2DEG(trxp->rz) );
	    break;
	  case NDC_ROTORDER_ZYX:
	    ndguRotateZYXF( mf, RAD2DEG(trxp->rx),
			   RAD2DEG(trxp->ry), RAD2DEG(trxp->rz) );
	    break;
	  case NDC_ROTORDER_ZXY:
	    ndguRotateZXYF( mf, RAD2DEG(trxp->rx),
			   RAD2DEG(trxp->ry), RAD2DEG(trxp->rz) );
	    break;
	  default:
	    {
		/* Evaluate rotations following the order */
		int i, ir;

		for(i=0; i<3; ++i, order>>=8){
		    ir = order & 0xff;
		    if(ir == 0x01)
		      ndguRotateXF( mf, RAD2DEG(trxp->rx));
		    if(ir == 0x02)
		      ndguRotateYF( mf, RAD2DEG(trxp->ry));
		    if(ir == 0x03)
		      ndguRotateZF( mf, RAD2DEG(trxp->rz));
		}
	    }
	    break;
	}
    }
    ndguScaleF(mf, trxp->sx, trxp->sy, trxp->sz);
}

/* ----------------------------------------------------------------------------
name:
    ndEvalInstanceOne
synopsis:
    int ndEvalInstanceOne(NDD_INSTANCE *isp, float mf[4][4], float cmf[4][4], int forceupd);
description:
    Evaluate the frame for the instance specified by isp.
parameter:
    NDD_INSTANCE *isp;
	The pointer for the instance.
    float mf[4][4];
	The model view matrix.
    float cmf[4][4];
	The model view matrix updated by instance.
    int forceupd;
	A flag to create the matrix by force.  Forced by 1.
return:
    int;
	When the calue of matirx argument, forceudp and its own matrix are
	updated, the value that performed or to 1 is returned.
notes:
     mf is used as the basic model view matrix.  
    When matrix evaluation isn't done, mf will return to cmf.
---------------------------------------------------------------------------- */
int ndEvalInstanceOne(NDD_INSTANCE *isp, float mf[4][4], float cmf[4][4], int forceupd)
{
    int child_update = 0;

    /* Inform the callback */
    if(isp->instCB)
      (*isp->instCB)(isp, NDC_ICB_EVAL);

    /* Copy the matrix */
    memcpy(cmf, mf, sizeof(float[4][4]));
    switch(isp->type){
      case NDC_ITYPE_ANIMTK:
	/* Move time ahead */
	if(!BITTEST1(isp->u.animtk.tarinst->u.obj.flag, NDC_OFLAG_PAUSE_ANIM))
	  ndProgressAnimTime( &isp->u.animtk );
	break;

      case NDC_ITYPE_ANIM:
	/* Progress of animation
	 Note:  This instance needs to be active in the pause condition
              of NDC_OFLAG_PAUSE_ANIM */
	ndSetAnimChannel( &isp->u.anim );
	break;

      case NDC_ITYPE_OBJECT:
	if(forceupd || !BITTEST1(isp->flag, NDC_IFLAG_MTX_READY)){
	    /* Progress of animation
	 Note:  This instance needs to be active in the pause condition
              of NDC_OFLAG_PAUSE_ANIM */
	    ndMultiTrx(cmf, &isp->u.obj.trx, isp->u.obj.order);
	    memcpy(isp->u.obj.modelview, cmf, sizeof(float[4][4]));
	    BITSET(isp->flag, NDC_IFLAG_MTX_READY);
	    child_update = 1;
	}
	break;

      case NDC_ITYPE_DYNVTX:
	ndReloadDynamicVertex(&isp->u.dynvtx);
	break;

      case NDC_ITYPE_DEFORM_VTX:
	ndDeformVertex(&isp->u.dfm_vtx);
	break;

      case NDC_ITYPE_DEFORM_VTXNV:
	ndDeformVertexNv(&isp->u.dfm_vtxnv);
	break;

      case NDC_ITYPE_DEFORM_VTXCOL:
	ndDeformVertexColor(&isp->u.dfm_vtxcol);
	break;

      case NDC_ITYPE_DEFORM_VTXST:
	ndDeformVertexSt(&isp->u.dfm_vtxst);
	break;

      case NDC_ITYPE_NULL:
      case NDC_ITYPE_ROOT:
	child_update = forceupd;
	break;
    }

    return child_update;
}

/* ----------------------------------------------------------------------------
name:
    ndEvalInstance
synopsis:
    void ndEvalInstance(NDD_INSTANCE *isp, float mf[4][4], int forceupd);
description:
    Progress of animation
	 Note:  This instance needs to be active in the pause condition
              of NDC_OFLAG_PAUSE_ANIM
parameter:
    NDD_INSTANCE *isp;
	The pointer for the instance.
    float mf[4][4];
	The model view matrix.
    int forceupd;
	A flag to create the matrix by force.  Forced by 1.
return:
notes:
     mf is used as the basic model view matrix.  
    It recurs, and furthermore, it has prepared the 64-byte buffer in the 
    local; so it nearly consumes the stack. 
---------------------------------------------------------------------------- */
void ndEvalInstance(NDD_INSTANCE *isp, float mf[4][4], int forceupd)
{
    NDD_INSTANCE *bros;
    float cmf[4][4];

    /* Expand self */
    forceupd |= ndEvalInstanceOne(isp, mf, cmf, forceupd);

    /* Expand child's link */
    if(isp->nchild)
      for(bros=isp->child; bros; bros=bros->bros)
	ndEvalInstance(bros, cmf, forceupd);
}
