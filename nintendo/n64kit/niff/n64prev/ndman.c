/*======================================================================*/
/*		NIFFprev						*/
/*		ndman.c							*/
/*									*/
/*		Copyright (C) 1997,1998, NINTENDO Co,Ltd.		*/
/*		Copyright (C) 1998, MONEGI CORPORATION.			*/
/*									*/
/*======================================================================*/
/* Revision History							*/
/*  1998/ 6/ 3	Change to object management				*/
/*  1998/ 6/16	Change to record position and content of color combiner */
/*              to NDD_INST_IBJ						*/
/*  1998/ 8/21	Set ndSetupScene to run, even scene == NULL 		*/
/*  1998/11/25	ST animation						*/
/*======================================================================*/
#define __NDMAN_C__

/* ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
	The simple 3D manager, "ND"

	The manager
 :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: */

#include "pack.h"
#include "nd.h"

/* ===========================================================================
	defines
 =========================================================================== */

/* ===========================================================================
	variables
 =========================================================================== */

int ndinst_cnt;

NDD_SCENE cur_scene;		/* current scene*/
NDD_INSTANCE top_inst;		/* top instance */
NDD_INSTANCE bottom_inst;	/* terminater instance */
NDD_INSTANCE *root_instp;	/* root instance pointer */
NDD_INSTANCE *obj_root_instp;	/* root of the object entry */
NDD_INSTANCE *anim_root_instp;	/* root of the animation entry */
NDD_INSTANCE *deform_root_instp; /* root of deform entry */
NDD_INSTANCE *dynvtx_root_instp; /* root of active vertex entry */

/* ===========================================================================
	functions
 =========================================================================== */

/* ----------------------------------------------------------------------------
	Add isp to parent as youngest child
 --------------------------------------------------------------------------- */
static void addChild(NDD_INSTANCE *parent, NDD_INSTANCE *isp)
{
    NDD_INSTANCE **pp;

    isp->parent = parent;
    for(pp=&parent->child; *pp; pp=&((*pp)->bros))
      ;

    *pp = isp;
    ++parent->nchild;
}

/* ----------------------------------------------------------------------------
	Delete isp link with parent
 --------------------------------------------------------------------------- */
static void delChild(NDD_INSTANCE *isp)
{

    if(isp->parent->child == isp){
	isp->parent->child = isp->bros;
    }else{
	NDD_INSTANCE **pp;

	for(pp=&isp->parent->child; *pp!=isp; pp=&((*pp)->bros))
	  ;
	*pp = isp->bros;
    }

    --isp->parent->nchild;
}

/* ----------------------------------------------------------------------------
name:
    ndGenInstance
synopsis:
    NDD_INSTANCE *ndGenInstance(NDD_INSTANCE *parent, u16 type, u16 prio, int gid);
description:
    Create instance structures and link them
parameter:
    NDD_INSTANCE *parent;
	Pointer of parent instance
    u16 type;
	Instance type
    u16 prio;
	Proirity code.  Affects an evaluation order of displayed instances.
	Range to specify is determined by type
    int gid;
	Group ID of instance
return:
    NDD_INSTANCE *;
	Instance pointer created
notes:
    Create instance.  A characteristic is determined by type.
 --------------------------------------------------------------------------- */
NDD_INSTANCE *ndGenInstance(NDD_INSTANCE *parent, u16 type, u16 prio, int gid)
{
    NDD_INSTANCE *bp, *isp;

    /* If a parent specifies NULL, connect it with the root */
    if(!parent)
      parent = root_instp;

    /* Look for the position to insert */
    for(bp=top_inst.next; bp->prio>prio; bp=bp->next)
      ;

    isp = malloc( sizeof(NDD_INSTANCE) );
    isp->flag = 0;
    /* Reput the link */
    isp->next = bp;
    isp->back = bp->back;
    bp->back->next = isp;
    bp->back = isp;

    /* One hasn't had a child, yet */
    isp->bros = isp->child = NULL;
    isp->nchild = 0;

    /* Connect with the parent */
    addChild(parent, isp);

    /* No call-back */
    isp->instCB = NULL;

    /* Copy the register */
    isp->type = type;
    isp->prio = prio;
    isp->gid = gid;

    /* Add the total number of instances */
    ++ndinst_cnt;

    return isp;
}

/* ----------------------------------------------------------------------------
name:
    ndDeleteInstance
synopsis:
    void ndDeleteInstance(NDD_INSTANCE *isp);
description:
    Deletes instance.  Its child is also deleted.
parameter:
return:
notes:
    Caution) Can't be used inside instance callback.
---------------------------------------------------------------------------- */
void ndDeleteInstance(NDD_INSTANCE *isp)
{
    NDD_INSTANCE *bp;

    /*  Because zombie is dead, do nothing (a zombie is instance to be deleted) */
    if(BITTEST1( isp->flag, NDC_IFLAG_ZONBIE ))
      return;

    /* Becomes a zombie */
    BITSET( isp->flag, NDC_IFLAG_ZONBIE );

    /* Inform callback of deletion */
    if(isp->instCB)
      (*isp->instCB)(isp, NDC_ICB_DIE);

    /* Delete child */
    if(isp->child){
	for(bp=isp->child; bp; bp=bp->bros)
	  ndDeleteInstance(bp);
    }

    /* Detach parent */
    delChild(isp);

    /* Remove from vertical link */
    bp = isp->next;
    bp->back = isp->back;
    bp->back->next = bp;

    /* Remove from vertical link */
    free(isp);
}

/* ----------------------------------------------------------------------------
name:
    ndChangePriority
synopsis:
    u16 ndChangePriority(NDD_INSTANCE *isp, u16 newprio);
description:
    Changes priority of one instance.
parameter:
    NDD_INSTANCE *isp;
	Instance pointer
    u16 newprio;
	New priority value
return:
    u16;
	Old priority value
notes:
    Links to the top of the specified priority
 --------------------------------------------------------------------------- */
u16 ndChangePriority(NDD_INSTANCE *isp, u16 newprio)
{
    u16 oldprio;
    NDD_INSTANCE *link;

    /* Remove from current link position */
    isp->next->back = isp->back;
    isp->back->next = isp->next;

    if(isp->prio <= newprio){
	/* Start searching from location of instance to be changed toward 
	   higher priority position */
	for(link = isp->back; link!=&top_inst; link=link->back)
	  if( link->prio > newprio )
	    break;
	link = link->next;
    }else{
	/* Start searching from location of instance to be changed toward 
	   lower priority position */
	for(link = isp->next; link!=&bottom_inst; link=link->next)
	  if( link->prio <= newprio )
	    break;
    }

    /* Re-connect link */
    isp->back = link->back;
    isp->next = link;
    link->back->next = isp;
    link->back = isp;

    /* Set priority */
    oldprio = isp->prio;
    isp->prio = newprio;

    return oldprio;
}

/* ----------------------------------------------------------------------------
name:
    ndChangeParent
synopsis:
    NDD_INSTANCE ndChangeParent(NDD_INSTANCE *isp, NDD_INSTANCE *newparent);
description:
    Change the parent of instance.
parameter:
    NDD_INSTANCE *isp;
	Pointer of instance
    NDD_INSTANCE *newparent;
	Pointer of new parent instance
return:
    NDD_INSTANCE *;
	Previous parent of instance
notes:
    newparent must not be NULL
 --------------------------------------------------------------------------- */
NDD_INSTANCE *ndChangeParent(NDD_INSTANCE *isp, NDD_INSTANCE *newparent)
{
    NDD_INSTANCE *oldparent;

    /* Reserve old parent */
    oldparent = isp->parent;

    /* Detach from old parent */
    delChild(isp);

    /* Add to new child */
    addChild(newparent, isp);

    return oldparent;
}

/* ----------------------------------------------------------------------------
name:
    ndDeleteInstanceGID
synopsis:
    void ndDeleteInstanceGID(NDD_INSTANCE *isp, int type, int gid, int mask);
description:
    Delete the instance specified by type, gid, and mask which matches  
    with the parameter.
    In reality something that is <TYPE> == type and <GID> & mask == gid 
    will be deleted.  However, if -1 is specified as type, type won't be 
    checked.
    Evaluate all of the isp children.  When parent is found, children under
    will be deleted unconditionally.
parameter:
    NDD_INSTANCE *isp;
    int type;
    int gid;
    int mask;
return:
notes:
    Caution) Can't be used inside instance callback.
---------------------------------------------------------------------------- */
void ndDeleteInstanceGID(NDD_INSTANCE *isp, int type, int gid, int mask)
{
    if((type<0 || isp->type == type) && (isp->gid & mask) == gid){
	/* Delete */
	ndDeleteInstance(isp);
    }else{
	/* Delete and evaluate child */
	NDD_INSTANCE *bp;

	if(isp->child){
	    for(bp=isp->child; bp; bp=bp->bros)
	      ndDeleteInstanceGID(bp, type, gid, mask);
	}
    }
}

/* ----------------------------------------------------------------------------
name:
    ndInit
synopsis:
    void ndInit(void);
description:
    Initialize module
parameter:
return:
notes:
    Needs to call before the start of the use of API for all 'nd'.
    It prepares current scene.  Even though there is no stting for the scene,
    base to display object is prepared.
---------------------------------------------------------------------------- */
void ndInit(void)
{
    NDD_INSTANCE *isp;
    int i;

    /* Initialize the instance table */
    top_inst.next = &bottom_inst;
    top_inst.back = NULL;
    top_inst.type = NDC_ITYPE_NULL;
    top_inst.prio = NDC_IPRIO_SYSTEM_TOP;
    bottom_inst.next = NULL;
    bottom_inst.back = &top_inst;
    bottom_inst.type = NDC_ITYPE_NULL;
    bottom_inst.prio = NDC_IPRIO_SYSTEM_BOTTOM;

    ndinst_cnt = 0;

    /* Initialize the current scene */
    cur_scene.top = 0;
    cur_scene.bottom = SCREEN_HT;
    cur_scene.left = 0;
    cur_scene.right = SCREEN_WD;
    cur_scene.fog.near=
      cur_scene.fog.far=0.0;	/* near == far then fog off */
    cur_scene.fog.color.r=
      cur_scene.fog.color.g=
	cur_scene.fog.color.b=
	  cur_scene.fog.color.a=0;
    cur_scene.camera.mode = 0;
    cur_scene.camera.fovy = 45.0;
    cur_scene.camera.aspect = 4.0/3.0;
    cur_scene.camera.near = 50;
    cur_scene.camera.far = 20000;
    cur_scene.camera.scale = 1.0;
    cur_scene.camera.top = -SCREEN_HT/2;
    cur_scene.camera.bottom = SCREEN_HT/2;
    cur_scene.camera.left = -SCREEN_WD/2;
    cur_scene.camera.right = SCREEN_WD/2;
    cur_scene.fill_col = GPACK_RGBA5551(0, 80, 100, 255);
    cur_scene.fill_depth = GPACK_ZDZ(G_MAXFBZ, 0);
    cur_scene.cam[0].root=cur_scene.cam[1].root=cur_scene.cam[2].root=NULL;
    cur_scene.cam[0].objno=cur_scene.cam[1].objno=cur_scene.cam[2].objno=0;
    cur_scene.enacam = 0;
    cur_scene.reflect.right[0] = 1;
    cur_scene.reflect.right[1] = 0;
    cur_scene.reflect.right[2] = 0;
    cur_scene.reflect.upper[0] = 0;
    cur_scene.reflect.upper[1] = 1;
    cur_scene.reflect.upper[2] = 0;
    cur_scene.lightset.numlights = 1;
    cur_scene.lightset.ambient.r = 127;
    cur_scene.lightset.ambient.g = 127;
    cur_scene.lightset.ambient.b = 127;
    cur_scene.lightset.light[0].flag = NDC_LFLAG_ENABLE;
    cur_scene.lightset.light[0].color.r = 255;
    cur_scene.lightset.light[0].color.g = 255;
    cur_scene.lightset.light[0].color.b = 255;
    cur_scene.lightset.light[0].fnv[0] = 0.0;
    cur_scene.lightset.light[0].fnv[1] = 1.0;
    cur_scene.lightset.light[0].fnv[2] = 0.0;
    for(i=1; i<NUM_LIGHTSET_LIGHTS; ++i)
      cur_scene.lightset.light[i].flag = 0;

    /* Create the root-object instance */
    root_instp = isp = malloc( sizeof(NDD_INSTANCE) );
    /* Reput the link */
    isp->next = &bottom_inst;
    isp->back = &top_inst;
    top_inst.next = isp;
    bottom_inst.back = isp;
    isp->bros = isp->child = NULL;
    isp->nchild= 0;
    isp->instCB = NULL;
    /* Copy the register */
    isp->type = NDC_ITYPE_NULL;
    isp->prio = NDC_IPRIO_ROOT;
    /* Include the root to the number */
    ++ndinst_cnt;

    /* For instantiation of the following, order is important */

    /* The root of the animation entry */
    anim_root_instp =
      ndGenInstance( root_instp, NDC_ITYPE_NULL, NDC_IPRIO_ANIMROOT, 0 );
    deform_root_instp =
      ndGenInstance( anim_root_instp, NDC_ITYPE_NULL, NDC_IPRIO_DEFORM, 0 );
    dynvtx_root_instp =
      ndGenInstance( anim_root_instp, NDC_ITYPE_NULL, NDC_IPRIO_DYNVTX, 0 );

    /* Create the root of the object entry */
    obj_root_instp =
      ndGenInstance( root_instp, NDC_ITYPE_ROOT, NDC_IPRIO_OBJROOT, 0 );
}

/* ---------------------------------------------------------------------------
name:
    ndEntryObjectRaw
synopsis:
    NDD_INSTANCE *ndEntryObjectRaw(NDD_INSTANCE *parent, NDR_OBJ *rop, int gid);
description:
    Create one instance from the object reference table.  It doesn't
    follow the link nor create instance.
parameter:
    NDD_INSTANCE *parent;
	Pointer of parent instance.  If NULL, it will link root of object
    NDR_OBJ *rop;
	Pointer for object reference table
    int gid;
	Base value of instance ID.  This value added by gidthat is specified
      by NDR_OBJ, will be allocated to the object instance structure that
      is to be created.
return:
    NDD_INSTANCE *;
	Pointer of the created instance
notes:
    Caution) Can't be used inside instance callback.
 --------------------------------------------------------------------------- */
NDD_INSTANCE *ndEntryObjectRaw(NDD_INSTANCE *parent, NDR_OBJ *rop, int gid)
{
    NDD_INSTANCE *isp;

    /* Making structure */
    isp = ndGenInstance( parent, NDC_ITYPE_OBJECT,
			 rop->prio | NDC_IPRIO_OBJ, gid+rop->gid );

    /* Copy register */
    isp->u.obj.order = rop->order;
    isp->u.obj.flag = NDC_OFLAG_ENABLE|NDC_OFLAG_ALLREG|rop->regflag;
    memcpy( &isp->u.obj.trx, &rop->trx, sizeof(TRX));

    isp->u.obj.geommode = rop->geommode;
    isp->u.obj.rdmode = rop->rdmode;
    memcpy( isp->u.obj.cc1, rop->cc1, sizeof(char)*8);
    memcpy( isp->u.obj.cc2, rop->cc2, sizeof(char)*8);
    isp->u.obj.primcol = rop->primcol;

#if 0
    isp->u.obj.bb_obj[0] = rop->bb_obj[0];
    isp->u.obj.bb_obj[1] = rop->bb_obj[1];
#else
    isp->u.obj.bb_obj[0] = NULL;
    isp->u.obj.bb_obj[1] = NULL;
#endif

    return isp;
}

/* ----------------------------------------------------------------------------
name:
    ndEntryAnimationRaw
synopsis:
    NDD_INSTANCE *ndEntryAnimationRaw(NDD_INSTANCE *parent, NDR_ANIM *anp, int gid, NDD_INSTANCE *tarinst);
description:
    Create one time keeper instance and the animation instance for the number
    of channels from the animation reference table.
parameter:
    NDD_INSTANCE *parent;
	Pointer of the parent instance
    NDR_ANIM *anp;
	Pointer for animation reference table
    int gid;
	Instance group ID
    NDD_INSTANCE *tarinst;
	Instance pointer to attach the animation
return:
    NDD_INSTANCE *;
	Pointer of the animation time-keeper instance 
notes:
    Caution) Can't be used within callback
---------------------------------------------------------------------------- */
NDD_INSTANCE *ndEntryAnimationRaw(NDD_INSTANCE *parent, NDR_ANIM *anp, int gid, NDD_INSTANCE *tarinst)
{
    NDD_INSTANCE *tkp, *isp;
    NDR_ANIM_CHANNEL *ch;
    int i;

    /* Is the "parent" correct? */
    if(!parent)
      parent = anim_root_instp;

    /* Create the time keeper */
    tkp = ndGenInstance( parent, NDC_ITYPE_ANIMTK, NDC_IPRIO_ANIMTK, gid );

    /* Copy the register */
    tkp->flag = 0;
    tkp->u.animtk.tarinst = tarinst;
    tkp->u.animtk.time = 0.0;
    tkp->u.animtk.timescale = 1.0;
    tkp->u.animtk.start = 0;
    tkp->u.animtk.end = anp->total;
    tkp->u.animtk.naniminst = anp->nch;

    ch = anp->chlist;
    for(i=0; i<anp->nch; ++i){
	/* Create the animation channel */
	isp = ndGenInstance( tkp, NDC_ITYPE_ANIM, NDC_IPRIO_ANIM, gid );

	tkp->u.animtk.animinst[i] = isp;

	/* Copy the register */
	isp->u.anim.time = 0.0;
	isp->u.anim.tarinst = tarinst;
	isp->u.anim.kind = ch[i].kind;
	isp->u.anim.start = ch[i].start;
	isp->u.anim.end = ch[i].end;
	isp->u.anim.nowkeypos = 0;
	isp->u.anim.nkey = ch[i].nkey;
	isp->u.anim.key = ch[i].key;
	isp->u.anim.value = ch[i].value;
    }

    return tkp;
}

/* ---------------------------------------------------------------------------
name:
    ndEntryObject
synopsis:
    NDD_INSTANCE *ndEntryObject(NDD_INSTANCE *parent, int objno, int shapeno, int animno, int gid, int flag);
description:
    Copy the register
parameter:
    NDD_INSTANCE *parent;
	The pointer of the parent instance. If it is NULL, it connects with the         object root.
    int objno;
	Index of object reference table.
    int shapeno;
	Offset of shape reference table. 
	As a shape held by object, the list in the object reference table, which 	is located at the sum of the shape and the specified value, will be 
	allocated.
    int animno;
	Offset of animation reference table.
	When entering animation simultaneously, make an animation entry of the
	NDR_OBJ.geom_anim table value added by this value.
    int gid;
	Base value of Instance ID.  This value, added by gid that is specified 		by NDR_OBJ, will be allocated to the object instance structure being 
	created.
    int flag;
	The bit assigned created flag becomes effective whin the bit is 1.
	  bit 0 ... Set the animation link of NDR_OBJ together
	  bit 1 ... Trace the link and evaluate toward the end of parent/child 
			relationship
return:
    NDD_INSTANCE *;
	Pointer of the first parent among the created instances.
notes:
    ndEntryObjectRaw is called inside.
    Caution) Can't be used within callback
 --------------------------------------------------------------------------- */
NDD_INSTANCE *ndEntryObject(NDD_INSTANCE *parent, int objno, int shapeno, int animno, int gid, int flag)
{
    NDD_INSTANCE *isp;
    NDR_OBJ *rop;
    int i;
    Gfx	*gfx;

    if(!parent)
      parent = obj_root_instp;

    /* Create the entity */
    rop = objlist[objno];
    isp = ndEntryObjectRaw(parent, rop, gid);

    /* Take in shape */
    if(rop->shape >= 0){
	isp->u.obj.shape = shapelist[shapeno + rop->shape];
 	isp->u.obj.flag |= NDC_OFLAG_VISIBLE;
	isp->u.obj.combine_gfx = NULL;
	/* Setting combiner, seaching Gfx 
	   This method had difficulties, please don't take as reference */
	for(i = 0; i < 6; ++i){
	    gfx = &isp->u.obj.shape->gfx[i];
	    if( ( gfx->words.w0 & 0xFF000000 ) == 0xFC000000 ){
		isp->u.obj.combine_gfx = gfx;
		isp->u.obj.combinemode = *gfx;
	    }
	}

    }else{
	isp->u.obj.shape = NULL;
    }

    /* If it keeps the animation, enter together */
    if((flag & 0x01) && (rop->geom_anim >= 0)){
	NDD_INSTANCE *tkp;
	float end_anim;
	tkp = ndEntryAnimationRaw(NULL, animlist[animno + rop->geom_anim],
			       gid, isp);
	tkp->u.animtk.loop = rop->loop;
	tkp->u.animtk.timescale = 1.0 / rop->framerate;
	end_anim = ( float )tkp->u.animtk.end;
	if( cur_scene.end_anim < end_anim ) cur_scene.end_anim = end_anim;
	if( cur_scene.framerate < rop->framerate )
			cur_scene.framerate = rop->framerate;
    }

    /* Create and link children */
    if((flag & 0x02) && rop->nchild){
	int i;
	NDD_INSTANCE **pp;
	for(pp=&isp->child, i=0; i<rop->nchild; pp=&((*pp)->bros), ++i)
	{
	  *pp = ndEntryObject(isp, objno+rop->child[i],
			      shapeno, animno, gid, flag);
	}
    }

    return isp;
}

/* ---------------------------------------------------------------------------
name:
    ndAttachAnimation
synopsis:
    void ndAttachAnimation(NDD_INSTANCE *parent, NDD_INSTANCE *isp, int objno, int animno, int gid, int flag)
description:
    Refer to animation link of object reference table, and attach information
    to the existing object instance.
parameter:
    NDD_INSTANCE *parent;
	Parent instance pointer. If NULL it will link the animation root.
    NDD_INSTANCE *isp;
	Object instance pointer that attaches animation.
    int objno;
	Object number on global resource list.
    int animno;
	Animation reference table offset. When entering animation
	simultaneously, make an entry animation of the table of 
	NDR_OBJ.geom_anim value added by this value.
    int gid;
	Base value of instance ID. This value added by gid, that is specified 
	by NDR_OBJ, will be allocated to the object instance structure that is 
	being created.
    int flag;
	The bit assigned created flag becomes effective whin the bit is 1.
	  bit 0 ... Set the animation link of NDR_OBJ together
	  bit 1 ... Trace the link and evaluate toward the end of parent/child 
			relationship
return:
    NDD_INSTANCE *;
	Pointer of the first parent among the created instances.
notes:
    Object instance passed using isp is handled as if it was created by
    NDR_OBJ structure list that is specified by objno.
    Can't be used within callback
 --------------------------------------------------------------------------- */
void ndAttachAnimation(NDD_INSTANCE *parent, NDD_INSTANCE *isp, int objno, int animno, int gid, int flag)
{
    NDR_OBJ *rop;

    rop = objlist[objno];

    /* If animation is possesed, make entry together */
    if(rop->geom_anim >= 0){
	NDD_INSTANCE *tkp;
	tkp = ndEntryAnimationRaw(parent, animlist[animno+rop->geom_anim],
			       gid, isp);
	tkp->u.animtk.loop = rop->loop;
	tkp->u.animtk.timescale = 1.0 / rop->framerate;
    }

    /* Create and link child */
    if(flag & 0x02){
	int i;
	NDD_INSTANCE *cp;

	for(cp=isp->child, i=0; cp && i<rop->nchild; cp=cp->bros, ++i)
	  ndAttachAnimation(parent, cp, objno+rop->child[i], animno,
			    gid, flag);
    }
}

/* ----------------------------------------------------------------------------
name:
    ndEntryDeformVtx
synopsis:
    NDD_INSTANCE *ndEntryDeformVtx(NDD_INSTANCE *isp, NDR_DEFORM *dmfp, int ofs, int gid);
description:
    Make an vertex deform instance entry.
parameter:
    NDD_INSTANCE *isp;
	Active vertex instance pointer.
    NDR_DEFORM *dmfp;
	Vertex deform structure pointer.
    int ofs;
	Offset for referring raw vertex data list.
    int gid;
	Instance group ID
return:
    NDD_INSTANCE *;
	Created vertex deform instance pointer.
notes:
    This instance will link exclusive parent (deform_root_instp).
---------------------------------------------------------------------------- */
static void exitDeformVtx(NDD_INSTANCE *isp, int type)
{
    NDD_INST_DEFORM_VTX *nidp;

    if(type == NDC_ICB_DIE){
	nidp = &isp->u.dfm_vtx;
	free(nidp->rawvtx);
	free(nidp->modify_vtx);
#ifdef _FAST_DEFORM_
	free(nidp->delta);
#endif
    }
}

NDD_INSTANCE *ndEntryDeformVtx(NDD_INSTANCE *isp, NDR_DEFORM *dmfp, int ofs, int gid)
{
    int i, alloclen;
    NDD_INSTANCE *new_isp;
    NDD_INST_DEFORM_VTX *nidp;
    float end_anim;

    /* If there is no animation setting, ignore it */
    if(isp->type != NDC_ITYPE_DYNVTX || !dmfp)
      return NULL;

    /* Create vetex interpolation instance */
    new_isp = ndGenInstance( deform_root_instp, NDC_ITYPE_DEFORM_VTX,
			    NDC_IPRIO_DEFORM, gid );
    new_isp->instCB = exitDeformVtx;
    nidp = &new_isp->u.dfm_vtx;
    nidp->tarinst = isp;

    /* Create animation table, and copu pointer and counter */
    nidp->key = dmfp->key;
    nidp->nkey = dmfp->nkey;
    nidp->nelem = dmfp->nelem;

    end_anim = ( float )nidp->key[ nidp->nkey - 1 ];
    if( cur_scene.end_anim < end_anim ) cur_scene.end_anim = end_anim;

    nidp->rawvtx = malloc(sizeof(s16*) * nidp->nkey);
    for(i=0; i<nidp->nkey; ++i)
      nidp->rawvtx[i] = rawvtxlist[dmfp->tblno[i]+ofs];

    /* Reserve modulation buffter of rawvtx */
    alloclen = nidp->nelem * sizeof(s32) * 3;
    nidp->modify_vtx = malloc( alloclen );
#ifdef _FAST_DEFORM_
    nidp->delta = malloc( alloclen );
#endif
    nidp->nowkey = nidp->downcounter = 0;

    return new_isp;
}

/* ----------------------------------------------------------------------------
name:
    ndEntryDeformVtxcol
synopsis:
    NDD_INSTANCE *ndEntryDeformVtxcol(NDD_INSTANCE *isp, NDR_DEFORM *dmfp, int ofs, int gid);
description:
    Make an entry of vertex color deform instance.
parameter:
    NDD_INSTANCE *isp;
	Active vertex instance pointer
    NDR_DEFORM *dmfp;
	Vertex color deform structure pointer.
    int ofs;
	Offset for referring raw vertex data list.
    int gid;
	Instance group ID
return:
    NDD_INSTANCE *;
	Created vertex color deform instance pointer.
notes:
    This instance will link exclusive parent (deform_root_instp).
    Three memories are reserved inside using the system function, malloc().
    Also, it will set callback for ending, and release the memory reserved
    in callback routine using malloc().
---------------------------------------------------------------------------- */
static void exitDeformVtxcol(NDD_INSTANCE *isp, int type)
{
    NDD_INST_DEFORM_VTXCOL *nidp;

    if(type == NDC_ICB_DIE){
	nidp = &isp->u.dfm_vtxcol;
	free(nidp->rawvtxcol);
	free(nidp->modify_vtxcol);
#ifdef _FAST_DEFORM_
	free(nidp->delta);
#endif
    }
}

NDD_INSTANCE *ndEntryDeformVtxcol(NDD_INSTANCE *isp, NDR_DEFORM *dmfp, int ofs, int gid)
{
    int i, alloclen;
    NDD_INSTANCE *new_isp;
    NDD_INST_DEFORM_VTXCOL *nidp;

    /* If there is no animation setting, ignore it */
    if(isp->type != NDC_ITYPE_DYNVTX || !dmfp)
      return NULL;

    /* Create vetex color interpolation instance */
    new_isp = ndGenInstance( deform_root_instp, NDC_ITYPE_DEFORM_VTXCOL,
			    NDC_IPRIO_DEFORM, gid );
    new_isp->instCB = exitDeformVtxcol;
    nidp = &new_isp->u.dfm_vtxcol;
    nidp->tarinst = isp;

    /* Create animation table, and copy pointer and counter */
    nidp->key = dmfp->key;
    nidp->nkey = dmfp->nkey;
    nidp->nelem = dmfp->nelem;
    nidp->rawvtxcol = malloc(sizeof(u32*) * nidp->nkey);
    for(i=0; i<nidp->nkey; ++i)
      nidp->rawvtxcol[i] = rawvtxcollist[dmfp->tblno[i]+ofs];

    /* Reserve modulation buffer of rawvtxcol */
    alloclen = nidp->nelem * sizeof(s16) * 4;
    nidp->modify_vtxcol = malloc( alloclen );
#ifdef _FAST_DEFORM_
    nidp->delta = malloc( alloclen );
#endif
    nidp->nowkey = nidp->downcounter = 0;

    return new_isp;
}

/* ----------------------------------------------------------------------------
name:
    ndEntryDeformVtxnv
synopsis:
    NDD_INSTANCE *ndEntryDeformVtxnv(NDD_INSTANCE *isp, NDR_DEFORM *dmfp, int ofs, int gid);
description:
    Make an entry of vertex normal deform instance.
parameter:
    NDD_INSTANCE *isp;
	Active vertex instance pointer
    NDR_DEFORM *dmfp;
	Vertex normal deform structure pointer.
    int ofs;
	Offset for referring raw vertex data list.
    int gid;
	Instance group ID
return:
    NDD_INSTANCE *;
	Created vertex normal deform instance pointer.
notes:
    This instance will link exclusive parent (deform_root_instp).
    Three memories are reserved inside using the system function, malloc().
    Also, it will set callback for ending, and release the memory reserved
    in callback routine using malloc().
---------------------------------------------------------------------------- */
static void exitDeformVtxnv(NDD_INSTANCE *isp, int type)
{
    NDD_INST_DEFORM_VTXNV *nidp;

    if(type == NDC_ICB_DIE){
	nidp = &isp->u.dfm_vtxnv;
	free(nidp->rawvtxnv);
	free(nidp->modify_vtxnv);
#ifdef _FAST_DEFORM_
	free(nidp->delta);
#endif
    }
}

NDD_INSTANCE *ndEntryDeformVtxnv(NDD_INSTANCE *isp, NDR_DEFORM *dmfp, int ofs, int gid)
{
    int i, alloclen;
    NDD_INSTANCE *new_isp;
    NDD_INST_DEFORM_VTXNV *nidp;

    /* If there is no animation setting, ignore it */
    if(isp->type != NDC_ITYPE_DYNVTX || !dmfp)
      return NULL;

    /* Create vetex normal interpolation instance */
    new_isp = ndGenInstance( deform_root_instp, NDC_ITYPE_DEFORM_VTXNV,
			    NDC_IPRIO_DEFORM, gid );
    new_isp->instCB = exitDeformVtxnv;
    nidp = &new_isp->u.dfm_vtxnv;
    nidp->tarinst = isp;

    /* Create animation table, and copy pointer and counter */
    nidp->key = dmfp->key;
    nidp->nkey = dmfp->nkey;
    nidp->nelem = dmfp->nelem;
    nidp->rawvtxnv = malloc(sizeof(u32*) * nidp->nkey);
    for(i=0; i<nidp->nkey; ++i)
      nidp->rawvtxnv[i] = rawvtxnvlist[dmfp->tblno[i]+ofs];

    /* Reserve modulation buffer of rawvtxnv */
    alloclen = nidp->nelem * sizeof(s16) * 3;
    nidp->modify_vtxnv = malloc( alloclen );
#ifdef _FAST_DEFORM_
    nidp->delta = malloc( alloclen );
#endif
    nidp->nowkey = nidp->downcounter = 0;

    return new_isp;
}

/* ----------------------------------------------------------------------------
name:
    ndEntryDeformVtxst
synopsis:
    NDD_INSTANCE *ndEntryDeformVtxst(NDD_INSTANCE *isp, NDR_DEFORM *dmfp, int ofs, int gid);
description:
    Make an entry of vertex texture deform instance
parameter:
    NDD_INSTANCE *isp;
	Active vertex instance pointer
    NDR_DEFORM *dmfp;
	Vertex normal deform structure pointer
    int ofs;
	Offset for referring raw vertex data list.
    int gid;
	Instance group ID
return:
    NDD_INSTANCE *;
	Created vertex normal deform instance pointer
notes:
    This instance will link to exclusive parent(deform_root_instp)
---------------------------------------------------------------------------- */
static void exitDeformVtxst(NDD_INSTANCE *isp, int type)
{
    NDD_INST_DEFORM_VTXST *nidp;

    if(type == NDC_ICB_DIE){
	nidp = &isp->u.dfm_vtxst;
	free(nidp->rawvtxst);
	free(nidp->modify_vtxst);
#ifdef _FAST_DEFORM_
	free(nidp->delta);
#endif
    }
}

NDD_INSTANCE *ndEntryDeformVtxst(NDD_INSTANCE *isp, NDR_DEFORM *dmfp, int ofs, int gid)
{
    int i, alloclen;
    NDD_INSTANCE *new_isp;
    NDD_INST_DEFORM_VTXST *nidp;
    float end_anim;

    /* If there is no animation setting, ignore it */
    if(isp->type != NDC_ITYPE_DYNVTX || !dmfp)
      return NULL;

    /* Create vetex normal interpolation instance */
    new_isp = ndGenInstance( deform_root_instp, NDC_ITYPE_DEFORM_VTXST,
			    NDC_IPRIO_DEFORM, gid );
    new_isp->instCB = exitDeformVtxst;
    nidp = &new_isp->u.dfm_vtxst;
    nidp->tarinst = isp;

    /* Create animation table, and copy pointer and counter */
    nidp->key = dmfp->key;
    nidp->nkey = dmfp->nkey;
    nidp->nelem = dmfp->nelem;

    end_anim = ( float )nidp->key[ nidp->nkey - 1 ];
    if( cur_scene.end_anim < end_anim ) cur_scene.end_anim = end_anim;

    nidp->rawvtxst = malloc(sizeof(s16*) * nidp->nkey);
    for(i=0; i<nidp->nkey; ++i)
      nidp->rawvtxst[i] = rawvtxstlist[dmfp->tblno[i]+ofs];

    /* Reserve modulation buffer of rawvtxst */
    alloclen = nidp->nelem * sizeof(s32) * 2;
    nidp->modify_vtxst = malloc( alloclen );
#ifdef _FAST_DEFORM_
    nidp->delta = malloc( alloclen );
#endif
    nidp->nowkey = nidp->downcounter = 0;

    return new_isp;
}

/* ----------------------------------------------------------------------------
name:
    ndEntryDeformShape
synopsis:
    NDD_INSTANCE *ndEntryDeformShape(NDD_INSTANCE *isp, int ofs_rawvtx, int ofs_rawvtxcol, int ofs_rawvtxnv, int gid, int flag);
description:
    Take over the shape to which object instance refers, and change it for 
    modulated vertex information.
parameter:
    NDD_INSTANCE *isp;
	Pointer for object instance that is to be modulated.
    int ofs_rawvtx;
    int ofs_rawvtxcol;
    int ofs_rawvtxnv;
	Offset for referring each data list
    int gid;
	Instance group ID
    int flag;
	The bit assigned created flag becomes effective whin the bit is 1.
	  bit 0 ... Make an entry of vertex deform
	  bit 1 ... Make an entry of vertex color deform
	  bit 2 ... Make an entry of vertex normal deform
return:
    NDD_INSTANCE *;
	Created active vertex instance pointer
notes:
      ndEntryDeformVtx(), ndEntryDeformVtxnv(), ndEntryDeformVtxcol()
    Creates upper instance.
      Evaluates creation of each deform instance and watches flag of the
    parameter at the same time, within the function.
      In order to be consistent with the asynchronism of Gfx construction, 
    there are 2 Vtx buffers.  Inside, three memories are reserved using 
    the system function, malloc().  Also, it will set callback for ending,
    and release the memory reserved in callback routine using malloc().
---------------------------------------------------------------------------- */
static void exitDynamicVtx(NDD_INSTANCE *isp, int type)
{
    NDD_INST_DYNAMICVTX *dvip;

    if(type == NDC_ICB_DIE){
	dvip = &isp->u.dynvtx;
	/* Put back the shape of object for target */
	dvip->tarinst->u.obj.shape = dvip->src_shape;
	/* Note:  Pointer is released whether it is still used for drawing
	   or not for the following, so be aware of this when deleting instances */
	free(dvip->tarvtx[0]);
	free(dvip->tarvtx[1]);
	free(dvip->dyn_shape);
    }
}

NDD_INSTANCE *ndEntryDeformShape(NDD_INSTANCE *isp, int ofs_rawvtx, int ofs_rawvtxcol, int ofs_rawvtxnv, int ofs_rawvtxst, int gid, int flag)
{
    int i;
    NDD_INSTANCE *new_isp;
    NDD_INST_DYNAMICVTX *dvip;
    NDR_SHAPE *src_shape, *new_shape;

    /* When other than object instance, or if doesn't have shaperef, ignore it */
    if(isp->type != NDC_ITYPE_OBJECT || !isp->u.obj.shape ||
       !isp->u.obj.shape->shaperef)
      return NULL;

    /* Create active vertex instance (link the object) */
    new_isp = ndGenInstance( dynvtx_root_instp, NDC_ITYPE_DYNVTX,
			NDC_IPRIO_DYNVTX, gid );
    new_isp->instCB = exitDynamicVtx;
    dvip = &new_isp->u.dynvtx;
    dvip->tarinst = isp;

    /* Reserve active vertex buffer and copy the controls */
    src_shape = isp->u.obj.shape;
    i = sizeof(Vtx)*src_shape->nvtx;
    dvip->tarvtx[0] = malloc(i);
    memcpy(dvip->tarvtx[0], src_shape->vtx, i);
    dvip->tarvtx[1] = malloc(i);
    memcpy(dvip->tarvtx[1], src_shape->vtx, i);

    /* Create NDR_SHAPE anew and copy the contents */
    dvip->dyn_shape = new_shape = malloc(sizeof(NDR_SHAPE));
    memcpy(new_shape, isp->u.obj.shape, sizeof(NDR_SHAPE));

    /* Replace NDR_SHAPE of host object */
    dvip->src_shape = isp->u.obj.shape;  /* Back -up */
    isp->u.obj.shape = dvip->dyn_shape;

    /* Initialize modulation instance for each table */
    for(i=0; i<4; ++i)
      dvip->dfminst[i] = NULL;

    /* Create modulation instance for each table */
    if(flag & 0x01)
      dvip->dfminst[0] = ndEntryDeformVtx(new_isp, new_shape->vtx_deform,
			   ofs_rawvtx, gid);
    if(flag & 0x02)
      dvip->dfminst[1] = ndEntryDeformVtxcol(new_isp,
			   new_shape->vtxcol_deform, ofs_rawvtxcol, gid);
    if(flag & 0x04)
      dvip->dfminst[2] = ndEntryDeformVtxnv(new_isp, new_shape->vtxnv_deform,
			   ofs_rawvtxnv, gid);
    if(flag & 0x08)
      dvip->dfminst[3] = ndEntryDeformVtxst(new_isp, new_shape->vtxst_deform,
			   ofs_rawvtxst, gid);

    return new_isp;
}

/* ---------------------------------------------------------------------------
name:
    ndAttachDeform
synopsis:
    void ndAttachDeform(NDD_INSTANCE *isp, int rawvtxno, int rawvtxcolno, int rawvtxnvno, int rawvtxstno, int gid, int flag);
description:
    When deformed is prepared for object instance that is layaered, make
    an entry.
parameter:
    NDD_INSTANCE *isp;
	Object instance pointer, which is created object of active vertex deform 	instance
    int rawvtxno;
    int rawvtxcolno;
    int rawvtxnvno;
    int rawvtxstno;
	Offset for referencing each data list
    int gid;
	Instance group ID
    int flag;
	The bit assigned created flag becomes effective whin the bit is 1.
	  bit 0 ... unused
	  bit 1 ... Evaluate towards edge of parent-child relation along link
	  bit 2 ... Enable vertex deform
	  bit 3 ... Enable vertex color deform
	  bit 4 ... Make and entry of vertex normal deform
	  bit 5 ... Entry vertex texture deform
return:
notes:
 --------------------------------------------------------------------------- */
void ndAttachDeform(NDD_INSTANCE *isp, int rawvtxno, int rawvtxcolno, int rawvtxnvno, int rawvtxstno, int gid, int flag)
{
    if(isp->type == NDC_ITYPE_OBJECT && isp->u.obj.shape &&
       isp->u.obj.shape->shaperef)
      ndEntryDeformShape(isp, rawvtxno, rawvtxcolno, rawvtxnvno, rawvtxstno,
			 gid, (flag&0x3c) >> 2);

    /* Create and link child */
    if(flag & 0x02){
	NDD_INSTANCE *cp;

	for(cp=isp->child; cp; cp=cp->bros)
	  ndAttachDeform(cp, rawvtxno, rawvtxcolno, rawvtxnvno, rawvtxstno,
			 gid, flag);
    }
}

/* ----------------------------------------------------------------------------
name:
    ndSetupScene
synopsis:
    void ndSetupScene(NDD_RESINFO *rip, int gid, int flag);
description:
    Build scene from scene reference table
parameter:
    NDD_RESINFO *rip;
	Resource information
    int gid;
	Group ID for allocation object instance
    int flag;
	Flag to set creation status
	Creation flag. When each bit is 1 the following become effective.
	  bit 0 ... Set animation link for NDR_OBJ together
	  bit 1 ... Trace link and evalute end of parent/child relationship
	  bit 2 ... Make and entry of vertex deform
	  bit 3 ... Make and entry of vertex color deform
	  bit 4 ... Make and entry of vertex normal deform
	  bit 5 ... Entry vertex texture deform
return:
notes:
    Scene data structure to be used for setting will refer to 
    rip->resinfo->scene.
---------------------------------------------------------------------------- */
void ndSetupScene(NDD_RESINFO *rip, int gid, int flag)
{
    NDR_SCENE *scene;
    NDR_SCN_INST_OBJ *sio;
    NDR_SCN_LIGHT *lp;
    int i,nlight;

    scene = rip->resinfo->scene;

    cur_scene.cam[0].root=cur_scene.cam[1].root=cur_scene.cam[2].root=NULL;
    cur_scene.cam[0].objno=cur_scene.cam[1].objno=cur_scene.cam[2].objno=0;
    cur_scene.enacam = 0;

    cur_scene.fog.near = 0;
    cur_scene.fog.far = 0;
    cur_scene.fog.color.r = 0;
    cur_scene.fog.color.g = 0;
    cur_scene.fog.color.b = 0;
    cur_scene.fog.color.a = 0;

    cur_scene.start_anim = cur_scene.end_anim = 0.0;
    cur_scene.anim_time = 0.0;
    cur_scene.framerate = 1.0;

    if(scene){
	/* When scene is valid */
	cur_scene.fog.near=scene->fog.near;
	cur_scene.fog.far=scene->fog.far;
	cur_scene.fog.color.r=scene->fog.r;
	cur_scene.fog.color.g=scene->fog.g;
	cur_scene.fog.color.b=scene->fog.b;
	cur_scene.fog.color.a=scene->fog.a;

	cur_scene.camera.mode = scene->cam.mode;
	cur_scene.camera.fovy = scene->cam.fovy;
	cur_scene.camera.aspect = scene->cam.aspect;
	cur_scene.camera.scale = 1.0;  /* scene->cam.scale; */
	cur_scene.camera.top = scene->cam.top;
	cur_scene.camera.bottom = scene->cam.bottom;
	cur_scene.camera.left = scene->cam.left;
	cur_scene.camera.right = scene->cam.right;
	if((cur_scene.camera.near = scene->cam.near)<50)
	  cur_scene.camera.near = 50;
	cur_scene.camera.far = scene->cam.far;

	cur_scene.fill_col = scene->fill_col;

	/* Instantiate the object */
	sio = scene->entryobj;
	cur_scene.obj = ( NDD_OBJ_INFO * )malloc( sizeof( NDD_OBJ_INFO ) *
						  scene->nentobj );
		/* Camera object is not registed as object, so actual number of 		   object is less than that. But for in case, keep space for 
		   scene->nentobj. */
	cur_scene.nobj = 0;
	for(i=0; i<scene->nentobj; ++i){
	    NDD_INSTANCE *isp;
	    isp = ndEntryObject(NULL, rip->obj.ofs + sio[i].objno,
		    rip->shape.ofs, rip->anim.ofs, gid, flag & 0x03);
	    memcpy(ndGetInstanceTRXPointer(isp), &sio[i].trx, sizeof(TRX));

	    if(flag & 0x3c)
	      ndAttachDeform(isp, rip->rawvtx.ofs, rip->rawvtxnv.ofs,
	        rip->rawvtxcol.ofs, rip->rawvtxst.ofs, gid, (flag &0x3c)+2);

	    if(i == scene->cam.eye_inst){
		cur_scene.cam[0].root=isp;
		cur_scene.cam[0].objno=rip->obj.ofs + sio[i].objno;
	    }else if(i == scene->cam.upper_inst){
		cur_scene.cam[1].root=isp;
		cur_scene.cam[1].objno=rip->obj.ofs + sio[i].objno;
	    }else if(i == scene->cam.lookat_inst){
		cur_scene.cam[2].root=isp;
		cur_scene.cam[2].objno=rip->obj.ofs + sio[i].objno;
	    }else{
		cur_scene.obj[cur_scene.nobj].root=isp;
		cur_scene.obj[cur_scene.nobj].objno=
						rip->obj.ofs + sio[i].objno;
		++cur_scene.nobj;
	    }
	}

	/* Read writing information */
	memcpy(&cur_scene.lightset.ambient, &scene->light.amb_color,
	       sizeof(RGBAQUAD));
	cur_scene.lightset.numlights = nlight = scene->light.nlight;
	lp = scene->light.light;
	for(i=0; i<nlight; ++i){
	    /* Set prepared light source normally */
	    memcpy(&cur_scene.lightset.light[i].color, &lp->color,
		   sizeof(RGBAQUAD));
	    if(lp->type){
		/* Point light source */
		cur_scene.lightset.light[i].flag =
		  NDC_LFLAG_ENABLE | NDC_LFLAG_HAVEPOS;
		cur_scene.lightset.light[i].fpos[0] = lp->x;
		cur_scene.lightset.light[i].fpos[1] = lp->y;
		cur_scene.lightset.light[i].fpos[2] = lp->z;
	    }else{
		/* Parallel light source */
		cur_scene.lightset.light[i].flag = NDC_LFLAG_ENABLE;
		cur_scene.lightset.light[i].fnv[0] = lp->x;
		cur_scene.lightset.light[i].fnv[1] = lp->y;
		cur_scene.lightset.light[i].fnv[2] = lp->z;
	    }
	    cur_scene.lightset.light[i].start = lp->a1;
	    cur_scene.lightset.light[i].end = lp->a2;
	}
#if 0
    }else{
	/* When scene is invalid, set-up default camera info */
	cur_scene.camera.mode = 0;
	cur_scene.camera.fovy = 45.0;
	cur_scene.camera.aspect = 1.0*SCREEN_WD/SCREEN_HT;
	cur_scene.camera.scale = 1.0;
	cur_scene.camera.top = -SCREEN_HT/2;
	cur_scene.camera.bottom = SCREEN_HT/2;
	cur_scene.camera.left = -SCREEN_WD/2;
	cur_scene.camera.right = SCREEN_WD/2;
	cur_scene.camera.near = 50;
	cur_scene.camera.far = 20000;
	cur_scene.fill_col = GPACK_RGBA5551(120, 0, 0, 255);
#endif
    }

    /* If the camera is set to the 3-object control,  make it valid */
    if(cur_scene.cam[0].root && cur_scene.cam[1].root &&
       cur_scene.cam[2].root){
	TRX *ep, *up, *ap;

	cur_scene.enacam = 1;
	/* Check position of 3 objects that are attached to the 
	   adjusted camera */
	ep = ndGetInstanceTRXPointer(cur_scene.cam[0].root);
	up = ndGetInstanceTRXPointer(cur_scene.cam[1].root);
	ap = ndGetInstanceTRXPointer(cur_scene.cam[2].root);
	if( ep->tx == up->tx && ep->tx == ap->tx &&
	    ep->ty == up->ty && ep->ty == ap->ty &&
	    ep->tz == up->tz && ep->tz == ap->tz ){
	    ep->tx = ep->ty = 0.0; ep->tz = -500;
	    ap->tx = ap->ty = ap->tz = 0.0;
	    up->tx = ep->tx; up->ty = ep->ty+1.0; up->tz = ep->tz;
	}
    }
}

/* ----------------------------------------------------------------------------
name:
    ndSetScreen
synopsis:
    void ndSetScreen(int top, int bottom, int left, int right);
description:
    Set screen width and height of screen display area.
parameter:
    int top;
    int bottom;
    int left;
    int right;
	Range for display by a pixel unit.
return:
notes:
---------------------------------------------------------------------------- */
void ndSetScreen(int top, int bottom, int left, int right)
{
    cur_scene.top = top;
    cur_scene.bottom = bottom;
    cur_scene.left = left;
    cur_scene.right = right;
}
