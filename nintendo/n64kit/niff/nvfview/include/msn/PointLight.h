/*
  msn/PointLight.h
    Copyright (C) 1998, NINTENDO Co,Ltd., MONEGI CORPORATION.
    Jan. 22, 1999.
*/

#ifndef _msn_PointLight_h
#define _msn_PointLight_h 1

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

/* Declare constant macro */
#define MSN_POINT_LIGHT_FIELD_POSITION			(0)
#define MSN_POINT_LIGHT_FIELD_COLOR			(1)
#define MSN_POINT_LIGHT_FIELD_CONSTANT_ATTENUATION	(2)
#define MSN_POINT_LIGHT_FIELD_LINEAR_ATTENUATION	(3)
#define MSN_POINT_LIGHT_FIELD_QUADRIC_ATTENUATION	(4)

/* Declare types of a structure */
typedef struct _MsnPointLight
{
    _msoDeriveFrom( MhcNode );
    MvmVector3f	position;
    MvmColor3f	color;
    float	attenuation[ 3 ];
} MsnPointLight;

/* Declare Functions */
extern void msnPointLightInit( MsnPointLight *light_ptr );

/* Declare global variables */
extern MifChunkParser gMsnPointLightChunkParser;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _msn_PointLight_h */
