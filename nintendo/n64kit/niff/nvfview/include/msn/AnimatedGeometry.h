/*
  msn/AnimatedGeometry.h
    Copyright (C) 1998, NINTENDO Co,Ltd., MONEGI CORPORATION.
    Oct. 19, 1998.
*/

#ifndef _msn_AnimatedGeometry_h
#define _msn_AnimatedGeometry_h 1

#include "mhc/Node.h"
#include "mhc/NodeHandle.h"
#include "mif/ChunkParser.h"
#include "mso/derive.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <ultra64.h>

/* Declare a constant macro */
#define MSN_ANIMATED_GEOMETRY_FIELD_TIME	(0)

/* Declare a structure */
typedef struct _MsnAnimatedGeometry
{
    _msoDeriveFrom( MhcNode );
    float		time;
    MhcNodeHandle	vertex;
} MsnAnimatedGeometry;

/* Declare functions */
extern void msnAnimatedGeometryInit( MsnAnimatedGeometry *geometry_ptr );

/* Declare a global variable */
extern MifChunkParser gMsnAnimatedGeometryChunkParser;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _msn_AnimatedGeometry_h */
