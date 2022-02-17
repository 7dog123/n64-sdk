/*
  mrn/Material.h
    Copyright (C) 1998, NINTENDO Co,Ltd., MONEGI CORPORATION.
    Nov. 20, 1998.
*/

#ifndef _mrn_Material_h
#define _mrn_Material_h 1

#include "mvm/Color.h"
#include "mrn/ObjectList.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <ultra64.h>

/* Declare constant macros */
#define MRN_MATERIAL_ENV_EMISSION	(1)
#define MRN_MATERIAL_ENV_AMBIENT	(2)
#define MRN_MATERIAL_EFFECT_NONE	(0)
#define MRN_MATERIAL_EFFECT_SPECULAR	(1)
#define MRN_MATERIAL_EFFECT_REFLECTION	(2)

/* Declare a prototype structure */
struct _MrnContext;

/* Declare structures */
typedef struct _MrnMaterial
{
    struct _MrnMaterial	*next_ptr;
    MrnObjectList	object_list;
			/* List of objects which uses this material.
			   Internally, it sorts objects.*/

    MvmColor4f		emission;
    MvmColor4f		ambient;
    MvmColor4f		diffuse;
    MvmColor4c		primitive_color;
    u8			lighting;
    u8			smooth;
    u8			effect;
    u8			env_mode;
    Gfx			cc_mode_gfx[ 2 ];
} MrnMaterial;

/* Declare functions */
extern void mrnMaterialInit( MrnMaterial *material_ptr );

extern Gfx *mrnMaterialDrawObjects( MrnMaterial *material_ptr,
			struct _MrnContext *context_ptr, Gfx *gfx_ptr );

extern Gfx *mrnMaterialGenerateGfx( MrnMaterial *material_ptr,
			struct _MrnContext *context_ptr, Gfx *gfx_ptr );

/* Declare a Global variable */
extern MrnMaterial	gMrnMaterialNull;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _mrn_Material_h */
