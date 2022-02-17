/*
  mhc/Animation.h
    Copyright (C) 1999, NINTENDO Co,Ltd., MONEGI CORPORATION.
    Mar. 18, 1999.
*/

#ifndef _mhc_Animation_h
#define _mhc_Animation_h 1

#include "mhc/Node.h"
#include "mhc/NodeHandle.h"
#include "mso/derive.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <ultra64.h>

/* Declare prototype structure */
struct _MhcInstance;
struct _MhcScene;

/* Declare types of a structure */
typedef struct _MhcAnimation
{
    _msoDeriveFrom( MhcNode );
    u32			function_index;
    u32			last_function_index;
    float		time;
    u32			key_search_hint;
    u32			number_of_elements;
    float		*value_array;
    float		*differential_array;
    u32			number_of_functions;
    MhcNodeHandle	*function_array;
} MhcAnimation;

/* Declare functions */
extern void mhcAnimationEvaluate( struct _MhcInstance *instance_ptr,
				  struct _MhcScene *scene_ptr );

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _mhc_Animation_h */
