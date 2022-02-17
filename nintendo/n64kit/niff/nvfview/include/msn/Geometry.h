/*
  msn/Geometry.h
    Copyright (C) 1998, NINTENDO Co,Ltd., MONEGI CORPORATION.
    Oct. 9, 1998.
*/

#ifndef _msn_Geometry_h
#define _msn_Geometry_h 1

#include "mhc/Node.h"
#include "mhc/NodeHandle.h"
#include "mif/ChunkParser.h"
#include "mso/derive.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <ultra64.h>

/* Declare structures */
typedef struct _MsnGeometry
{
    _msoDeriveFrom( MhcNode );
    Vtx	*vtx_array;
    Gfx	*gfx_array;
} MsnGeometry;

/* Declare functions */
extern void msnGeometryInit( MsnGeometry *geometry_ptr );

/* Declare a global variable */
extern MifChunkParser gMsnGeometryChunkParser;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _msn_Geometry_h */
