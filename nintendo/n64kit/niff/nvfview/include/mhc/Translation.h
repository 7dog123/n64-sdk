/*
  mhc/Translation.h
    Copyright (C) 1999, NINTENDO Co,Ltd., MONEGI CORPORATION.
    Mar. 18, 1999.
*/

#ifndef _mhc_Translation_h
#define _mhc_Translation_h 1

#include "mhc/Node.h"
#include "mhc/NodeHandle.h"
#include "mso/derive.h"
#include "mvm/Vector.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <ultra64.h>

/* Declare prototype structure */
struct _MhcInstance;
struct _MhcScene;

/* Declare types of a structure */
typedef struct _MhcTranslation
{
    _msoDeriveFrom( MhcNode );
    MvmVector3f		translation;
    MvmVector3f		global_position;
    u32			number_of_children;
    MhcNodeHandle	*child_array;
} MhcTranslation;

/* Declare Functions */
extern void mhcTranslationEvaluate( struct _MhcInstance *instance_ptr,
				    struct _MhcScene *scene_ptr );

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _mhc_Translation_h */
