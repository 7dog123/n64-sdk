/*
  mhc/Instance.h
    Copyright (C) 1998, NINTENDO Co,Ltd., MONEGI CORPORATION.
    Jan. 6, 1999
*/

#ifndef _mhc_Instance_h
#define _mhc_Instance_h 1

#include "mhc/Transform.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <ultra64.h>

/* Declare prototype structures  */
struct _MhcNode;
struct _MrnLight;
struct _MrnLightSet;
struct _MrnMaterial;
struct _MrnObject;
struct _MrnTexture;

/* Declare structures */
typedef struct _MhcInstance
{
    struct _MhcInstance	*next_ptr;
    struct _MhcInstance	*prev_ptr;
    struct _MhcNode	*node_ptr;
    MhcTransform	transform;
    struct _MrnObject	*object_ptr;
    struct _MrnTexture	*texture_ptr;
    struct _MrnMaterial	*material_ptr;
    struct _MrnLight	*light_ptr;
    struct _MrnLightSet	*light_set_ptr;
} MhcInstance;

/* Declare functions */
extern void mhcInstanceInit( MhcInstance *instance_ptr,
			     struct _MhcNode *node_ptr );

#ifdef __cplusplus
}
#endif /* __cplusplus */

/* Declare macros */
#define _mhcInstanceCopyContext(dest_ptr,src_ptr) \
{ \
    _mhcTransformCopy( &(dest_ptr)->transform, &(src_ptr)->transform ); \
    (dest_ptr)->object_ptr	= (src_ptr)->object_ptr;	\
    (dest_ptr)->texture_ptr	= (src_ptr)->texture_ptr;	\
    (dest_ptr)->material_ptr	= (src_ptr)->material_ptr;	\
    (dest_ptr)->light_ptr	= (src_ptr)->light_ptr;		\
    (dest_ptr)->light_set_ptr	= (src_ptr)->light_set_ptr;	\
}

#define _mhcInstanceIsReady(instance_ptr) \
	( (instance_ptr)->node_ptr->resolve_mask == 0 )

#endif /* _mhc_Instance_h */
