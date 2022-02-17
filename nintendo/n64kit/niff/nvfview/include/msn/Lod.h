/*
  msn/Lod.h
    Copyright (C) 1998, NINTENDO Co,Ltd., MONEGI CORPORATION.
    Nov. 10, 1998.
*/

#ifndef _msn_Lod_h
#define _msn_Lod_h 1

#include "mhc/Node.h"
#include "mhc/NodeHandle.h"
#include "mif/ChunkParser.h"
#include "mso/derive.h"
#include "mvm/Vector.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <ultra64.h>

/* Declare structures */
typedef struct _MsnLod
{
    _msoDeriveFrom( MhcNode );
    u16			group_index;
    u16			number_of_levels;
    float		*range_array;
    MhcNodeHandle	*level_array;
} MsnLod;

/* Declare functions */
extern void msnLodInit( MsnLod *lod_ptr );

/* Declare global variables */
extern MifChunkParser gMsnLodChunkParser;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _msn_Lod_h */
