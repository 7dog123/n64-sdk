/*======================================================================*/
/*		NIFFprev						*/
/*		malloc.c						*/
/*									*/
/*		Copyright (C) 1997, NINTENDO Co,Ltd.			*/
/*									*/
/*======================================================================*/
#define __MALLOC_C__

/* :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
	The memory manager
 :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: */

#include "pack.h"

/* ===========================================================================
	static variables
 =========================================================================== */
static MEMCTRL globalmem;
static MEMHEADER mallocspace[ MALLOC_SPACE ];

/* ===========================================================================
	public functions
 =========================================================================== */

/* ----------------------------------------------------------------------------
name:
    minit
synopsis:
    void minit(void);
description:
    Initialize the memory manager
parameter:
return:
notes:
---------------------------------------------------------------------------- */
void minit(void)
{
    MEMHEADER *p;

    globalmem.topadrs = globalmem.searchtop = p = &mallocspace[0];
    globalmem.endadrs = &mallocspace[MALLOC_SPACE-1];

    p->flag = 0;
    p->length = sizeof(MEMHEADER) * MALLOC_SPACE;
}

/* ----------------------------------------------------------------------------
name:
    amalloc
synopsis:
    void *amalloc(int want, void *ap);
description:
   The memory reservation from the areane area
   Retrun memory which could be arranged to the 8-byte boundary. 
parameter:
    int want;
	The number of required bytes. 
    void *ap;
	The pointer of the arena area. 
return:
notes:
---------------------------------------------------------------------------- */
void *amalloc(int want, void *ap)
{
    MEMCTRL *mcp = ap;
    MEMHEADER *p,*ep, *np;
    u32 len8, want8, bytelen;

    /* Detects the head location of data area which is not used in the arena 
	area */
    ep = mcp->endadrs;
    want8 = OCTARY(want) + 1;	/* Think with padding out for MEMCTRL */
    for(p=mcp->searchtop; p<ep; p+=len8){
	len8 = OCTARY(p->length);
	if((!BITTEST(p->flag, MHFLG_USED)) && (len8 >= want8))
	  break;	/* be found */
    }
    if(p>=ep){
	/* No space */
	return NULL;
    }

    /* Divide the memory area */
    if(len8 > want8+1){
	bytelen = want8 * sizeof(MEMHEADER);
	np = &p[want8];
	np->length = p->length - bytelen;
	np->flag = 0;
	p->length = bytelen;
    }

    /* Move the retrieval start-point*/
    if(mcp->searchtop == p)
      mcp->searchtop = &p[OCTARY(p->length)];

    /* Set up the reservation flag */
    BITSET(p->flag, MHFLG_USED);
    np = &p[OCTARY(p->length)];
    BITSET(np->flag, MHFLG_BEFOREUSED);

    return ++p;	/* The proper memory comes after the header */
}

/* ----------------------------------------------------------------------------
name:
    afree
synopsis:
    void afree( void *ptr, void *ap );
description:
    Release the reserved memory from the arena area.
parameter:
    void *ptr;
	The memory pointer to release. 
    void *ap;
	The pointer of the arena area. 
return:
notes:
---------------------------------------------------------------------------- */
void afree( void *ptr, void *ap )
{
    MEMCTRL *mcp = ap;
    MEMHEADER *p, *np;

    if(!ptr) return;
    p = &((MEMHEADER*)ptr)[-1];	 /* The MEMHEADER pointer is just preceding it */

    /* Can it merge with the just-preceding block?*/
    /* To say clearly, this process is heavy. We should do someting */
    if(p != mcp->topadrs && !BITTEST(p->flag, MHFLG_BEFOREUSED)){
	MEMHEADER *tp;
	for(tp=mcp->topadrs; (np = &tp[OCTARY(tp->length)])!=p; tp=np)
	  ;
	tp->length += p->length;
	p = tp;
    }

    /* Can it merge with the just-following block? */
    np = &p[OCTARY(p->length)];
    if(!BITTEST(np->flag, MHFLG_USED))
      p->length += np->length;

    /* Is there any change for the retrieval start-pointer? */
    if((u32)mcp->searchtop > (u32)p)
      mcp->searchtop = p;

    /* Set up the flag */
    BITRESET(p->flag, MHFLG_USED);
    p = &p[OCTARY(p->length)];
    BITRESET(p->flag, MHFLG_BEFOREUSED);
}

/* ----------------------------------------------------------------------------
name:
    malloc
synopsis:
    void *malloc(int want);
description:
    The memory reservation
    Return memory which could be arranged to the 8-byte boundary.
parameter:
    int want;
	The number of required bytes.
return:
    void *;
	The memory pointer which could be reserved.
notes:
    Reserve the arena memory inside for the global area. 
---------------------------------------------------------------------------- */
void *malloc(int want)
{
    return amalloc( want, &globalmem );
}

/* ----------------------------------------------------------------------------
name:
    free
synopsis:
    void free( void *ptr )
description:
    Release the memory
parameter:
    void *ptr;
	The memory pointer to release. 
return:
notes:
    Provide the arena-release inside as the memory pointer reserved for the
    global area. 
---------------------------------------------------------------------------- */
void free( void *ptr )
{
    afree( ptr, &globalmem );
}

/* ----------------------------------------------------------------------------
name:
    acreate
synopsis:
    void *acreate(int want);
description:
    Reserve the arena. 
parameter:
    int want;
	The number of required bytes. Because it takes the header of the arena
	management area from inside of "want," it needs to pass the extra length	for that.
return:
notes:
    Reserve the memory for the global area and initialize it as the arena inside
---------------------------------------------------------------------------- */
void *acreate(int want)
{
    int bytelen, len;
    MEMCTRL *mcp;
    MEMHEADER *p;

    len = OCTARY(want);
    bytelen = len * 8;
    mcp = malloc(sizeof(MEMCTRL));
    mcp->topadrs = mcp->searchtop = p = malloc(bytelen);
    mcp->endadrs = &mcp->topadrs[ len ];

    p->flag = 0;
    p->length = bytelen;

    return mcp;
}

/* ----------------------------------------------------------------------------
name:
    adelete
synopsis:
    void adelete(void *ap);
description:
    Release the arena. 
parameter:
    void *ap;
	The pointer to release. 
return:
notes:
    Provide the releasing process as the reserved memory for the global area 
    inside. 
---------------------------------------------------------------------------- */
void adelete(void *ap)
{
    MEMCTRL *mcp = ap;

    free( mcp->topadrs );
    free( mcp );
}

