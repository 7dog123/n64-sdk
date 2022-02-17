/*
  msn/EnvelopeVertexC.h
    Copyright (C) 1998, NINTENDO Co,Ltd., MONEGI CORPORATION.
    Nov. 6, 1998.
*/

#ifndef _msn_EnvelopeVertexC_h
#define _msn_EnvelopeVertexC_h 1

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
typedef struct _MsnEnvelopeVertexC
{
    _msoDeriveFrom( MhcNode );
    MsnEnvelopeVertex	envelope;
} MsnEnvelopeVertexC;

/* Declare functions */
extern void msnEnvelopeVertexCInit( MsnEnvelopeVertexC *vertex_ptr );

/* Declare a global variable */
extern MifChunkParser gMsnEnvelopeVertexCChunkParser;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _msn_EnvelopeVertexC_h */
