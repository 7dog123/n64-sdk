/*
  msn/Texture.h
    Copyright (C) 1998, NINTENDO Co,Ltd., MONEGI CORPORATION.
    Oct. 14, 1998.
*/

#ifndef _msn_Texture_h
#define _msn_Texture_h 1

#include "mhc/Node.h"
#include "mhc/NodeHandle.h"
#include "mif/ChunkParser.h"
#include "mrn/Texture.h"
#include "mso/derive.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <ultra64.h>

/* Declare  macro */
#define MSN_TEXTURE_FIELD_S0		(0)
#define MSN_TEXTURE_FIELD_S1		(1)
#define MSN_TEXTURE_FIELD_T0		(2)
#define MSN_TEXTURE_FIELD_T1		(3)

/* Declare structures */
typedef struct _MsnTexture
{
    _msoDeriveFrom( MhcNode );
    MrnTexture		texture;
    MhcNodeHandle	image;
    MhcNodeHandle	lut;
} MsnTexture;

/* Declare functions */
extern void msnTextureInit( MsnTexture *texture_ptr );

/* Declare a global variable */
extern MifChunkParser gMsnTextureChunkParser;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _msn_Texture_h */
