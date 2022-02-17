/*
  msn/Shape.h
    Copyright (C) 1998, NINTENDO Co,Ltd., MONEGI CORPORATION.
    Oct. 9, 1998.
*/

#ifndef _msn_Shape_h
#define _msn_Shape_h 1

#include "mhc/Node.h"
#include "mhc/NodeHandle.h"
#include "mif/ChunkParser.h"
#include "mrn/ObjectState.h"
#include "mso/derive.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <ultra64.h>

/* Declare structures */
typedef struct _MsnShape
{
    _msoDeriveFrom( MhcNode );
    MrnObjectState	state;
    MhcNodeHandle	geometry;
    MhcNodeHandle	material;
    MhcNodeHandle	texture;
} MsnShape;

/* Declare a function */
extern void msnShapeInit( MsnShape *shape_ptr );

/* Declare global variables */
extern MifChunkParser gMsnShapeChunkParser;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _msn_Shape_h */
