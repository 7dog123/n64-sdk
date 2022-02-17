/*
  msn/Material.h
    Copyright (C) 1998, NINTENDO Co,Ltd., MONEGI CORPORATION.
    Oct. 9, 1998.
*/

#ifndef _msn_Material_h
#define _msn_Material_h 1

#include "mhc/Node.h"
#include "mhc/NodeHandle.h"
#include "mif/ChunkParser.h"
#include "mrn/Material.h"
#include "mso/derive.h"
#include "mvm/Color.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <ultra64.h>

/* Declare constant macro */
#define MSN_MATERIAL_FIELD_AMBIENT		(0)
#define MSN_MATERIAL_FIELD_EMISSION		(1)
#define MSN_MATERIAL_FIELD_DIFFUSE		(2)
#define MSN_MATERIAL_FIELD_PRIMITIVE_COLOR	(3)

/* Declare types of a structure */
typedef struct _MsnMaterial
{
    _msoDeriveFrom( MhcNode );
    MrnMaterial		material;
    MvmColor4f		primitive_color;
    MhcNodeHandle	light_set;
} MsnMaterial;

/* Declare Functions */
extern void msnMaterialInit( MsnMaterial *material_ptr );

/* Declare global variables */
extern MifChunkParser gMsnMaterialChunkParser;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _msn_Material_h */
