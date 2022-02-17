/*
  msn/Nop.h
    Copyright (C) 1998, NINTENDO Co,Ltd., MONEGI CORPORATION.
    Nov. 11, 1998.
*/

#ifndef _msn_Nop_h
#define _msn_Nop_h 1

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
typedef struct _MsnNop
{
    _msoDeriveFrom( MhcNode );
    u32			number_of_children;
    MhcNodeHandle	*child_array;
} MsnNop;

/* Declare functions */
extern void msnNopInit( MsnNop *nop_ptr );

/* Declare global variables */
extern MifChunkParser gMsnNopChunkParser;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _msn_Nop_h */
