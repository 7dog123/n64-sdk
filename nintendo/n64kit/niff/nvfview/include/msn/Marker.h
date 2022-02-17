/*
  msn/Marker.h
    Copyright (C) 1998, NINTENDO Co,Ltd., MONEGI CORPORATION.
    Dec. 4, 1998.
*/

#ifndef _msn_Marker_h
#define _msn_Marker_h 1

#include "mhc/Node.h"
#include "mhc/NodeHandle.h"
#include "mif/ChunkParser.h"
#include "mso/derive.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <ultra64.h>

/* Declare structures */
typedef struct _MsnMarker
{
    _msoDeriveFrom( MhcNode );
    u16	type;
    u16	group_index;
} MsnMarker;

/* Declare functions */
extern void msnMarkerInit( MsnMarker *marker_ptr );

/* Declare global variables */
extern MifChunkParser gMsnMarkerChunkParser;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _msn_Marker_h */
