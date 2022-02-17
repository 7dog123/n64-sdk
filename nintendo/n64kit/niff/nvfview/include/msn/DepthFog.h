/*
  msn/DepthFog.h
    Copyright (C) 1998-1999, NINTENDO Co,Ltd., MONEGI CORPORATION.
    Jan. 28, 1999.
*/

#ifndef _msn_DepthFog_h
#define _msn_DepthFog_h 1

#include "mhc/Node.h"
#include "mhc/NodeHandle.h"
#include "mif/ChunkParser.h"
#include "mso/derive.h"
#include "mvm/Vector.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <ultra64.h>

/* Declare constant macros */
#define MSN_DEPTH_FOG_FIELD_NEAR	(0)
#define MSN_DEPTH_FOG_FIELD_FAR		(1)
#define MSN_DEPTH_FOG_FIELD_COLOR	(2)
#define MSN_DEPTH_FOG_FIELD_ACTIVE	(3)

/* Declare structures */
typedef struct _MsnDepthFog
{
    _msoDeriveFrom( MhcNode );
    float	fog_near;
    float	fog_far;
    MvmColor4f	color;
    u32		is_active;
} MsnDepthFog;

/* Declare functions */
extern void msnDepthFogInit( MsnDepthFog *fog_ptr );

/* Declare a global variable */
extern MifChunkParser gMsnDepthFogChunkParser;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _msn_DepthFog_h */
