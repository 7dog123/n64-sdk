/*
  msn/DirectionalLight.h
    Copyright (C) 1998, NINTENDO Co,Ltd., MONEGI CORPORATION.
    Oct. 12, 1998.
*/

#ifndef _msn_DirectionalLight_h
#define _msn_DirectionalLight_h 1

#include "mhc/Node.h"
#include "mhc/NodeHandle.h"
#include "mif/ChunkParser.h"
#include "mrn/Light.h"
#include "mso/derive.h"
#include "mvm/Vector.h"
#include "mvm/Color.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <ultra64.h>

/* Declare constant macros */
#define MSN_DIRECTIONAL_LIGHT_FIELD_DIRECTION	(0)
#define MSN_DIRECTIONAL_LIGHT_FIELD_COLOR	(1)

/* Declare structures */
typedef struct _MsnDirectionalLight
{
    _msoDeriveFrom( MhcNode );
    MvmVector3f	direction;
    MvmColor3f	color;
} MsnDirectionalLight;

/* Declare functions */
extern void msnDirectionalLightInit( MsnDirectionalLight *light_ptr );

/* Declare a global variable */
extern MifChunkParser gMsnDirectionalLightChunkParser;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _msn_DirectionalLight_h */
