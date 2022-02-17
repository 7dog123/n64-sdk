/*
  msn/TextureImage.h
    Copyright (C) 1998, NINTENDO Co,Ltd., MONEGI CORPORATION.
    Oct. 14, 1998.
*/

#ifndef _msn_TextureImage_h
#define _msn_TextureImage_h 1

#include "mhc/Node.h"
#include "mhc/NodeHandle.h"
#include "mif/ChunkParser.h"
#include "mrn/TextureImage.h"
#include "mso/derive.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <ultra64.h>

/* Declare structures */
typedef struct _MsnTextureImage
{
    _msoDeriveFrom( MhcNode );
    MrnTextureImage	texture_image;
} MsnTextureImage;

/* Declare functions */
extern void msnTextureImageInit( MsnTextureImage *image_ptr );

/* Declare a global variable */
extern MifChunkParser gMsnTextureImageChunkParser;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _msn_TextureImage_h */
