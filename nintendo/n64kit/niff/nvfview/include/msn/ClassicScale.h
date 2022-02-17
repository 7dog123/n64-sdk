/*
  msn/ClassicScale.h
    Copyright (C) 1998, NINTENDO Co,Ltd., MONEGI CORPORATION.
    Oct. 14, 1998.
*/

#ifndef _msn_ClassicScale_h
#define _msn_ClassicScale_h 1

#include "mhc/Node.h"
#include "mhc/NodeHandle.h"
#include "mif/ChunkParser.h"
#include "mso/derive.h"
#include "mvm/Matrix.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <ultra64.h>

/* Declare constant macros */
#define MSN_CLASSIC_SCALE_FIELD_SCALE			(0)
#define MSN_CLASSIC_SCALE_FIELD_SCALED_ORIENTATION	(1)

/* Declare structures */
typedef struct _MsnClassicScale
{
    _msoDeriveFrom( MhcNode );
    MvmVector3f		scale;
    MvmMatrix33f	scaled_orientation;
    u32			number_of_children;
    MhcNodeHandle	*child_array;
} MsnClassicScale;

/* Declare functions */
extern void msnClassicScaleInit( MsnClassicScale *scale_ptr );

/* Declare global variables */
extern MifChunkParser gMsnClassicScaleChunkParser;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _msn_ClassicScale_h */
