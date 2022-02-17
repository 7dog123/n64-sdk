/*
  msn/EnvelopeVertexN.h
    Copyright (C) 1998, NINTENDO Co,Ltd., MONEGI CORPORATION.
    Oct. 21, 1998.
*/

#ifndef _msn_EnvelopeVertexN_h
#define _msn_EnvelopeVertexN_h 1

#include "mhc/Node.h"
#include "mhc/NodeHandle.h"
#include "mif/ChunkParser.h"
#include "msn/EnvelopeVertex.h"
#include "mso/Allocator.h"
#include "mso/derive.h"
#include "mvm/Vector.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <ultra64.h>

/* Declare structures */
typedef struct _MsnEnvelopeVertexN
{
    _msoDeriveFrom( MhcNode );
    MsnEnvelopeVertex	envelope;
} MsnEnvelopeVertexN;

/* Declare functions */
extern void msnEnvelopeVertexNInit( MsnEnvelopeVertexN *vertex_ptr );

/* Declare a global variable */
extern MifChunkParser gMsnEnvelopeVertexNChunkParser;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _msn_EnvelopeVertexN_h */
