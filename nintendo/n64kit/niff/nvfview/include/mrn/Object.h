/*
  mrn/Object.h
    Copyright (C) 1998, NINTENDO Co,Ltd., MONEGI CORPORATION.
    Oct. 9, 1998.
*/

#ifndef _mrn_Object_h
#define _mrn_Object_h 1

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <ultra64.h>

/* Declare prototype structures */
struct _MrnContext;
struct _MrnGroup;
struct _MrnLightSet;
struct _MrnMaterial;
struct _MrnObject;
struct _MrnObjectState;
struct _MrnTexture;
struct _MrnTextureImage;
struct _MrnTextureLut;

/* Declare structures */
typedef Gfx *( *MrnObjectDrawFunc )( struct _MrnObject *object_ptr,
				     struct _MrnContext *context_ptr,
				     Gfx *gfx_ptr );

typedef struct _MrnObject
{
    struct _MrnObject		*next_ptr;
    struct _MrnObjectState	*state_ptr;
    struct _MrnTexture		*texture_ptr;
    struct _MrnTextureImage	*texture_image_ptr;
    struct _MrnTextureLut	*texture_lut_ptr;
    struct _MrnLightSet		*light_set_ptr;
    struct _MrnMaterial		*material_ptr;
    MrnObjectDrawFunc		draw;
    Mtx				*mtx_array;
    Vtx				*vtx_array;
    void			*user_data;
} MrnObject;

/* Declare functions */
extern void mrnObjectInit( MrnObject *object_ptr );

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _mrn_Object_h */
