/*
  mrn/TextureLut.h
    Copyright (C) 1998, NINTENDO Co,Ltd., MONEGI CORPORATION.
    Oct. 13, 1998.
*/

#ifndef _mrn_TextureLut_h
#define _mrn_TextureLut_h 1

#include "mrn/ObjectList.h"
#include "mrn/TextureTile.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <ultra64.h>

/* Declare constant macros */
#define MRN_TEXTURE_LUT_FORMAT_IA88	(0)
#define MRN_TEXTURE_LUT_FORMAT_RGBA5551	(1)

/* Declare structures */
typedef struct _MrnTextureLut
{
    struct _MrnTextureLut	*next_ptr;
    MrnObjectList		object_list;
				/* List of objects which uses this TextureLut
				   Internally, it sorts objects. */

    u8				format;
    u16				size;
    u16				*color_table;
} MrnTextureLut;

/* Declare functions */
extern void mrnTextureLutInit( MrnTextureLut *lut_ptr );

extern Gfx *mrnTextureLutGenerateGfx( MrnTextureLut *lut_ptr,
			struct _MrnContext *context_ptr, Gfx *gfx_ptr );

extern Gfx *mrnTextureLutDrawObjects( MrnTextureLut *lut_ptr,
			struct _MrnContext *context_ptr, Gfx *gfx_ptr );

/* Declare a Global variable */
extern MrnTextureLut	gMrnTextureLutNull;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _mrn_TextureLut_h */
