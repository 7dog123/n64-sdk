/*
  msn/TextureLut.h
    Copyright (C) 1998, NINTENDO Co,Ltd., MONEGI CORPORATION.
    Oct. 14, 1998.
*/

#ifndef _msn_TextureLut_h
#define _msn_TextureLut_h 1

#include "mhc/Node.h"
#include "mhc/NodeHandle.h"
#include "mif/ChunkParser.h"
#include "mrn/TextureLut.h"
#include "mso/derive.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <ultra64.h>

/* Declare structures */
typedef struct _MsnTextureLut
{
    _msoDeriveFrom( MhcNode );
    MrnTextureLut	texture_lut;
} MsnTextureLut;

/* Declare functions */
extern void msnTextureLutInit( MsnTextureLut *lut_ptr );

/* Declare a global variable  */
extern MifChunkParser gMsnTextureLutChunkParser;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _msn_TextureLut_h */
