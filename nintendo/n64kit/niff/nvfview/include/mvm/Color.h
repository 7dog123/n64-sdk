/*
  mvm/Color.h
    Copyright (C) 1998, NINTENDO Co,Ltd., MONEGI CORPORATION.
    Sep. 17, 1998.
*/

#ifndef _mvm_Color_h
#define _mvm_Color_h 1

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <ultra64.h>
#include <mvm/Vector.h>

/* Declare structures */
typedef struct _MvmRgbf
{
    float	r;
    float	g;
    float	b;
} MvmRgbf;

typedef struct _MvmRgbaf
{
    float	r;
    float	g;
    float	b;
    float	a;
} MvmRgbaf;

typedef union _MvmColor3f
{
    MvmRgbf	rgb;
    MvmVector3f	vector;
} MvmColor3f;

typedef union _MvmColor4f
{
    MvmRgbaf	rgba;
    MvmVector4f	vector;
} MvmColor4f;

typedef struct _MvmRgbl
{
    u32	r;
    u32	g;
    u32	b;
} MvmRgbl;

typedef struct _MvmRgbal
{
    u32	r;
    u32	g;
    u32	b;
    u32	a;
} MvmRgbal;

typedef union _MvmColor3l
{
    MvmRgbl		rgb;
    MvmVector3ul	vector;
} MvmColor3l;

typedef union _MvmColor4l
{
    MvmRgbal		rgba;
    MvmVector4ul	vector;
} MvmColor4l;

typedef struct _MvmRgbc
{
    u8	r;
    u8	g;
    u8	b;
} MvmRgbc;

typedef struct _MvmRgbac
{
    u8	r;
    u8	g;
    u8	b;
    u8	a;
} MvmRgbac;

typedef union _MvmColor3c
{
    MvmRgbc		rgb;
    MvmVector3uc	vector;
} MvmColor3c;

typedef union _MvmColor4c
{
    MvmRgbac		rgba;
    MvmVector4uc	vector;
    u32		packed;
} MvmColor4c;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _mvm_Color_h */
