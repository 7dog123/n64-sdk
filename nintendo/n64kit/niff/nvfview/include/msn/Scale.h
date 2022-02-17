/*
  msn/Scale.h
    Copyright (C) 1998, NINTENDO Co,Ltd., MONEGI CORPORATION.
    Oct. 20, 1998.
*/

#ifndef _msn_Scale_h
#define _msn_Scale_h 1

#include "mhc/Node.h"
#include "mhc/NodeHandle.h"
#include "mif/ChunkParser.h"
#include "mso/derive.h"
#include "mvm/Matrix.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <ultra64.h>

/* Declare constant value macros */
#define MSN_SCALE_FIELD_SCALE		(0)
#define MSN_SCALE_FIELD_GLOBAL_SCALE	(1)

/* Declare structures */
typedef struct _MsnScale
{
    _msoDeriveFrom( MhcNode );
    MvmVector3f		scale;
    MvmVector3f		global_scale;
    u32			number_of_children;
    MhcNodeHandle	*child_array;
} MsnScale;

/* Declare functions */
extern void msnScaleInit( MsnScale *ptr );

/* Declare global variables */
extern MifChunkParser gMsnScaleChunkParser;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _msn_Scale_h */
