/*
  mgi/Control.h
    Copyright (C) 1998, NINTENDO Co,Ltd., MONEGI CORPORATION.
    Oct. 29, 1998.
*/

#ifndef _mgi_Control_h
#define _mgi_Control_h 1

#include "mhc/Node.h"
#include "mhc/NodeHandle.h"
#include "mso/derive.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <ultra64.h>

/* Declare prototype structures */
struct _MgiCharacter;
struct _MhcNode;

/* Declare type of structures */
typedef struct _MgiControl
{
    char		*node_name;
    struct _MhcNode	*node_ptr;
    u32			field;
    u32			size;
    union
    {
	void	*ptr;
	u32	*u32_ptr;
	s32	*s32_ptr;
	float	*float_ptr;
    }			access;
} MgiControl;

/* Declare functions */
extern void mgiControlInit( MgiControl *control_ptr );

extern void mgiControlBind( MgiControl *control_ptr,
			    struct _MgiCharacter *char_ptr );

extern u32 mgiControlGetULong( const MgiControl *control_ptr );
extern s32 mgiControlGetSLong( const MgiControl *control_ptr );
extern float mgiControlGetFloat( const MgiControl *control_ptr );

extern void mgiControlGetULongs( const MgiControl *control_ptr, u32 *array );
extern void mgiControlGetSLongs( const MgiControl *control_ptr, s32 *array );
extern void mgiControlGetFloats( const MgiControl *control_ptr, float *array );

extern void mgiControlSetULong( MgiControl *control_ptr, const u32 value );
extern void mgiControlSetSLong( MgiControl *control_ptr, const s32 value );
extern void mgiControlSetFloat( MgiControl *control_ptr, const float value );

extern void mgiControlSetULongs( MgiControl *control_ptr, const u32 *array );
extern void mgiControlSetSLongs( MgiControl *control_ptr, const s32 *array );
extern void mgiControlSetFloats( MgiControl *control_ptr, const float *array );

#ifdef __cplusplus
}
#endif /* __cplusplus */

/* Declare Macro */
#define _mgiControlUnbind(control_ptr) { (control_ptr)->access.ptr = NULL; }

#endif /* _mgi_Control_h */
