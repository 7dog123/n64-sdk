/*
  mrn/Light.h
    Copyright (C) 1998, NINTENDO Co,Ltd., MONEGI CORPORATION.
    Sep. 21, 1998.
*/

#ifndef _mrn_Light_h
#define _mrn_Light_h 1

#include "mvm/Color.h"
#include "mvm/Vector.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <ultra64.h>

/* Declare constant macros */
#define MRN_LIGHT_TYPE_DIR	(0)
#define MRN_LIGHT_TYPE_POINT	(1)

/* Declare structures */
typedef struct _MrnPointLight
{
    MvmVector3f	position;
    float	quadric_attenuation;
    float	linear_attenuation;
    float	constant_attenuation;
} MrnPointLight;

typedef struct _MrnLight
{
    u8			type;
    MvmColor3f		color;
    MvmVector3f		direction;
    MrnPointLight	point;		/* use for point light source only */
} MrnLight;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _mrn_Light_h */
