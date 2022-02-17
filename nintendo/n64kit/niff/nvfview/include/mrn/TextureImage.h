/*
  mrn/TextureImage.h
    Copyright (C) 1998, NINTENDO Co,Ltd., MONEGI CORPORATION.
    Mar. 23, 1999.
*/

#ifndef _mrn_TextureImage_h
#define _mrn_TextureImage_h 1

#include "mrn/ObjectList.h"
#include "mrn/TextureTile.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <ultra64.h>

/* Declare a prototype structure */
struct _MrnContext;

/* Declare structures */
typedef struct _MrnTextureImage
{
    struct _MrnTextureImage	*next_ptr;
    MrnObjectList		object_list;
			/* List of objects which uses this TextureImage.
			  Internally, it sorts objects. */

    u16				offset[ 2 ];	/* Word unit */
    u16				size[ 2 ];	/* Word unit */
    void			*texel[ 2 ];
} MrnTextureImage;

/* Declare functions */
extern void mrnTextureImageInit( MrnTextureImage *image_ptr );

extern Gfx *mrnTextureImageGenerateGfx( MrnTextureImage *image_ptr,
			struct _MrnContext *context_ptr, Gfx *gfx_ptr );

extern Gfx *mrnTextureImageDrawObjects( MrnTextureImage *image_ptr,
			struct _MrnContext *context_ptr, Gfx *gfx_ptr );

/* Declare a Global variable */
extern MrnTextureImage	gMrnTextureImageNull;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _mrn_TextureImage_h */
