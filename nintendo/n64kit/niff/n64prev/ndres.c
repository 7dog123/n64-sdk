/*======================================================================*/
/*		NIFFprev						*/
/*		ndres.c							*/
/*									*/
/*		Copyright (C) 1997,1998, NINTENDO Co,Ltd.		*/
/*									*/
/*======================================================================*/
#define __NDRES_C__

/* ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
	Simple 3D Manager "ND"

	Resource Manager
 :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: */

#include "pack.h"
#include "nd.h"

/* ===========================================================================
	defines
 =========================================================================== */

/* ===========================================================================
	variables
 =========================================================================== */

/* Global resource list */
NDR_OBJ **objlist;
u16 objlist_top;
u16 objlist_lim;

NDR_SHAPE **shapelist;
u16 shapelist_top;
u16 shapelist_lim;

NDR_ANIM **animlist;
u16 animlist_top;
u16 animlist_lim;

s16 **rawvtxlist;
u16 rawvtxlist_top;
u16 rawvtxlist_lim;

u32 **rawvtxcollist;
u16 rawvtxcollist_top;
u16 rawvtxcollist_lim;

s8 **rawvtxnvlist;
u16 rawvtxnvlist_top;
u16 rawvtxnvlist_lim;

s16 **rawvtxstlist;
u16 rawvtxstlist_top;
u16 rawvtxstlist_lim;

/* ===========================================================================
	functions
 =========================================================================== */

static void initPointerList(void *vp, int vpplen)
{
    void **vpp = vp;
    int i;

    for(i=0; i<vpplen; ++i)
      vpp[i] = NULL;
}

/* ----------------------------------------------------------------------------
name:
    ndResInit
synopsis:
    void ndResInit(int olplim, int slplim, int alplim, int rvlplim, int rvclplim, int rvnlplim);
description:
    Initialize resource module
parameter:
    int olplim;
    int slplim;
    int alplim;
    int rvlplim;
    int rvclplim;
    int rvnlplim;
	Pointer of list management and maximum number for each data class
return:
notes:
    Pointer list is reserved by the system function, malloc().
---------------------------------------------------------------------------- */
void ndResInit(int olplim, int slplim, int alplim, int rvlplim, int rvclplim, int rvnlplim, int rvslplim)
{
    objlist = malloc(olplim << 2);
    objlist_lim = olplim;
    objlist_top = 0;
    initPointerList(objlist, objlist_lim);

    shapelist = malloc(slplim << 2);
    shapelist_lim = slplim;
    shapelist_top = 0;
    initPointerList(shapelist, shapelist_lim);

    animlist = malloc(alplim << 2);
    animlist_lim = alplim;
    animlist_top = 0;
    initPointerList(animlist, animlist_lim);

    rawvtxlist = malloc(rvlplim << 2);
    rawvtxlist_lim = rvlplim;
    rawvtxlist_top = 0;
    initPointerList(rawvtxlist, rawvtxlist_lim);

    rawvtxcollist = malloc(rvclplim << 2);
    rawvtxcollist_lim = rvclplim;
    rawvtxcollist_top = 0;
    initPointerList(rawvtxcollist, rawvtxcollist_lim);

    rawvtxnvlist = malloc(rvnlplim << 2);
    rawvtxnvlist_lim = rvnlplim;
    rawvtxnvlist_top = 0;
    initPointerList(rawvtxnvlist, rawvtxnvlist_lim);

    rawvtxstlist = malloc(rvslplim << 2);
    rawvtxstlist_lim = rvslplim;
    rawvtxstlist_top = 0;
    initPointerList(rawvtxstlist, rawvtxstlist_lim);
}

/* ----------------------------------------------------------------------------
name:
    ndResEntry
synopsis:
    NDD_RESINFO *ndResEntry(NDR_RESINFO *rrp, int usemask);
description:
    Add the specified resource to a global resource list
parameter:
    NDR_RESINFO *rrp;
	Pointer for resource information structure for reference
    int usemask;
	Data type of entries can be specified by bit from the contents of rrp
return:
    NDR_RESINFO *drp;
	Pointer for resource information structure.
notes:
---------------------------------------------------------------------------- */
static int entry_resource( void *dlp, void *slp, int ofs, int cnt, NDD_RESOFFSET *ofsp)
{
    void **dlpp = dlp;
    void **slpp = slp;
    int i;

    for(i=0; i<cnt; ++i){
      dlpp[ofs+i] = slpp[i];
    }

    ofsp->ofs = ofs;
    ofsp->count = cnt;

    return ofs+cnt;
}

NDD_RESINFO *ndResEntry(NDR_RESINFO *rrp, int usemask)
{
    NDD_RESINFO *drp;

    drp = malloc(sizeof(NDD_RESINFO));
    drp->resinfo = rrp;

    if(BITTEST(usemask, NDC_RES_USED_OBJ) && rrp->nobj){
	objlist_top =
	  entry_resource( objlist, rrp->obj, objlist_top, rrp->nobj,
			 &drp->obj);
    }else{
	BITRESET(usemask, NDC_RES_USED_OBJ);
	drp->obj.ofs = drp->obj.count = 0;
    }

    if(BITTEST(usemask, NDC_RES_USED_SHAPE) && rrp->nshape){
	shapelist_top =
	  entry_resource( shapelist, rrp->shape, shapelist_top, rrp->nshape,
			 &drp->shape);
    }else{
	BITRESET(usemask, NDC_RES_USED_SHAPE);
	drp->shape.ofs = drp->shape.count = 0;
    }

    if(BITTEST(usemask, NDC_RES_USED_ANIM) && rrp->nanim){
	animlist_top =
	  entry_resource( animlist, rrp->anim, animlist_top, rrp->nanim,
			 &drp->anim);
    }else{
	BITRESET(usemask, NDC_RES_USED_ANIM);
	drp->anim.ofs = drp->anim.count = 0;
    }

    if(BITTEST(usemask, NDC_RES_USED_RAWVTX) && rrp->nrawvtx){
	rawvtxlist_top =
	  entry_resource( rawvtxlist, rrp->rawvtx, rawvtxlist_top,
			 rrp->nrawvtx, &drp->rawvtx);
    }else{
	BITRESET(usemask, NDC_RES_USED_RAWVTX);
	drp->rawvtx.ofs = drp->rawvtx.count = 0;
    }

    if(BITTEST(usemask, NDC_RES_USED_RAWVTXCOL) && rrp->nrawvtxcol){
	rawvtxcollist_top =
	  entry_resource( rawvtxcollist, rrp->rawvtxcol, rawvtxcollist_top,
			 rrp->nrawvtxcol, &drp->rawvtxcol);
    }else{
	BITRESET(usemask, NDC_RES_USED_RAWVTXCOL);
	drp->rawvtxcol.ofs = drp->rawvtxcol.count = 0;
    }

    if(BITTEST(usemask, NDC_RES_USED_RAWVTXNV) && rrp->nrawvtxnv){
	rawvtxnvlist_top =
	  entry_resource( rawvtxnvlist, rrp->rawvtxnv, rawvtxnvlist_top,
			 rrp->nrawvtxnv, &drp->rawvtxnv);
    }else{
	BITRESET(usemask, NDC_RES_USED_RAWVTXNV);
	drp->rawvtxnv.ofs = drp->rawvtxnv.count = 0;
    }

    if(BITTEST(usemask, NDC_RES_USED_RAWVTXST) && rrp->nrawvtxst){
	rawvtxstlist_top =
	  entry_resource( rawvtxstlist, rrp->rawvtxst, rawvtxstlist_top,
			 rrp->nrawvtxst, &drp->rawvtxst);
    }else{
	BITRESET(usemask, NDC_RES_USED_RAWVTXST);
	drp->rawvtxst.ofs = drp->rawvtxst.count = 0;
    }

    drp->usemask = usemask;

    return drp;
}

/* ----------------------------------------------------------------------------
name:
    ndResRelease
synopsis:
    void ndResRelease(NDD_RESINFO *drp);
description:
    Remove specified resource from the global list
parameter:
    NDD_RESINFO *drp;
	Pointer for resource information structure
return:
notes:
    Argument drp will be released.
    Only resource entered immediately before can be released.
---------------------------------------------------------------------------- */
void ndResRelease(NDD_RESINFO *drp)
{
    objlist_top = drp->obj.ofs;
    shapelist_top = drp->shape.ofs;
    animlist_top = drp->anim.ofs;
    rawvtxlist_top = drp->rawvtx.ofs;
    rawvtxcollist_top = drp->rawvtxcol.ofs;
    rawvtxnvlist_top = drp->rawvtxnv.ofs;
    rawvtxstlist_top = drp->rawvtxst.ofs;

    free(drp);
}

/* ----------------------------------------------------------------------------
name:
    ndResLinkAbs    

synopsis:
    void ndResLinkAbs(NDR_RESINFO *rrp);
description:
    Pointer of reserved resource has to be mapped in address
parameter:
    NDR_RESINFO *rrp;
	Pointer to reference resource information structure
return:
notes:
    Pointer member of structure will map, as offset from rrp is stored.
    This means that rrp will be added to pointer member.
    It depends upon data structure of nd, so if pointer member to NDR_*
    structure is added, this module needs to be revised carefully
---------------------------------------------------------------------------- */

void ndResLinkAbs(NDR_RESINFO *rrp)
{
    u32 basep = (u32)rrp;
    int i,j;

    if(rrp->scene){
	NDR_SCENE *p;
	rrp->scene = p = (NDR_SCENE*)((u32)rrp->scene+basep);
	p->light.light = (NDR_SCN_LIGHT*)((u32)p->light.light+basep);
	p->entryobj = (NDR_SCN_INST_OBJ*)((u32)p->entryobj+basep);
    }

    if(rrp->nobj){
	rrp->obj = (NDR_OBJ**)((u32)rrp->obj+basep);
	for(i=0; i<rrp->nobj; ++i){
	    NDR_OBJ *p;
	    rrp->obj[i] = p = (NDR_OBJ*)((u32)rrp->obj[i]+basep);
	    p->child = (s16*)((u32)p->child+basep);
	}
    }

    if(rrp->nshape){
	rrp->shape = (NDR_SHAPE**)((u32)rrp->shape+basep);
	for(i=0; i<rrp->nshape; ++i){
	    NDR_SHAPE *p;
	    NDR_DEFORM *dp;
	    rrp->shape[i] = p = (NDR_SHAPE*)((u32)rrp->shape[i]+basep);
	    if(p->gfx)
	      p->gfx = (Gfx*)((u32)p->gfx+basep);
	    if(p->vtx)
	      p->vtx = (Vtx*)((u32)p->vtx+basep);
	    if(p->img)
	      p->img = (u8*)((u32)p->img+basep);
	    if(p->tlut)
	      p->tlut = (u16*)((u32)p->tlut+basep);
	    if(p->shaperef)
	      p->shaperef = (s16*)((u32)p->shaperef+basep);
	    if(p->vtx_deform){
		p->vtx_deform = dp =
		  (NDR_DEFORM*)((u32)p->vtx_deform+basep);
		dp->key = (s16*)((u32)dp->key+basep);
		dp->tblno = (s16*)((u32)dp->tblno+basep);
	    }
	    if(p->vtxcol_deform){
		p->vtxcol_deform = dp =
		  (NDR_DEFORM*)((u32)p->vtxcol_deform+basep);
		dp->key = (s16*)((u32)dp->key+basep);
		dp->tblno = (s16*)((u32)dp->tblno+basep);
	    }
	    if(p->vtxnv_deform){
		p->vtxnv_deform = dp =
		  (NDR_DEFORM*)((u32)p->vtxnv_deform+basep);
		dp->key = (s16*)((u32)dp->key+basep);
		dp->tblno = (s16*)((u32)dp->tblno+basep);
	    }
	    if(p->vtxst_deform){
		p->vtxst_deform = dp =
		  (NDR_DEFORM*)((u32)p->vtxst_deform+basep);
		dp->key = (s16*)((u32)dp->key+basep);
		dp->tblno = (s16*)((u32)dp->tblno+basep);
	    }
	}
    }

    if(rrp->nanim){
	rrp->anim = (NDR_ANIM**)((u32)rrp->anim+basep);
	for(i=0; i<rrp->nanim; ++i){
	    NDR_ANIM *p;
	    NDR_ANIM_CHANNEL *cp;
	    rrp->anim[i] = p = (NDR_ANIM*)((u32)rrp->anim[i]+basep);
	    if(p->nch){
		p->chlist = cp = (NDR_ANIM_CHANNEL*)((u32)p->chlist+basep);
		for(j=0; j<p->nch; ++j){
		    cp[j].key = (s16*)((u32)(cp[j].key)+basep);
		    cp[j].value = (float*)((u32)(cp[j].value)+basep);
		}
	    }
	}
    }

    if(rrp->nrawvtx){
	rrp->rawvtx = (s16**)((u32)rrp->rawvtx+basep);
	for(i=0; i<rrp->nrawvtx; ++i)
	  rrp->rawvtx[i] = (s16*)((u32)rrp->rawvtx[i]+basep);
    }

    if(rrp->nrawvtxcol){
	rrp->rawvtxcol = (u32**)((u32)rrp->rawvtxcol+basep);
	for(i=0; i<rrp->nrawvtxcol; ++i)
	  rrp->rawvtxcol[i] = (u32*)((u32)rrp->rawvtxcol[i]+basep);
    }

    if(rrp->nrawvtxnv){
	rrp->rawvtxnv = (s8**)((u32)rrp->rawvtxnv+basep);
	for(i=0; i<rrp->nrawvtxnv; ++i)
	  rrp->rawvtxnv[i] = (s8*)((u32)rrp->rawvtxnv[i]+basep);
    }
    
    if(rrp->nrawvtxst){
	rrp->rawvtxst = (s16**)((u32)rrp->rawvtxst+basep);
	for(i=0; i<rrp->nrawvtxst; ++i)
	  rrp->rawvtxst[i] = (s16*)((u32)rrp->rawvtxst[i]+basep);
    }
}
