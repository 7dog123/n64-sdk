/*
  mrn/Group.h
    Copyright (C) 1998, NINTENDO Co,Ltd., MONEGI CORPORATION.
    Oct. 28, 1998.
*/

#ifndef _mrn_Group_h
#define _mrn_Group_h 1

#include "mrn/ObjectList.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <ultra64.h>

/* Declare prototype structures */
struct _MrnCamera;
struct _MrnContext;
struct _MrnGroup;
struct _MrnView;

/* Declare structures */
typedef Gfx *( *MrnGroupSetupFunc )( struct _MrnGroup *group_ptr,
			struct _MrnContext *context_ptr, Gfx *gfx_ptr );

typedef struct _MrnGroup
{
    MrnObjectList	object_list;
			/* List of objects which uses the group.
			   Internally, it sorts object. */

    struct _MrnView	*view_ptr;
    struct _MrnCamera	*camera_ptr;

    MrnGroupSetupFunc	setup;
} MrnGroup;

/* Declare functions */
extern void mrnGroupInit( MrnGroup *group_ptr );

extern Gfx *mrnGroupClearView( MrnGroup *group_ptr,
			struct _MrnContext *context_ptr, Gfx *gfx_ptr );

extern Gfx *mrnGroupDrawObjects( MrnGroup *group_ptr,
			struct _MrnContext *context_ptr, Gfx *gfx_ptr );

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _mrn_Group_h */
