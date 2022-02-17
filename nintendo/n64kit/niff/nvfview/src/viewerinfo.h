/*
  nvfview
  viewerinfo.h
    Copyright (C) 1998, NINTENDO Co,Ltd., MONEGI CORPORATION.
    Dec. 14, 1998.
*/

#include <ultratypes.h>
#include "mhc/Scene.h"

#ifndef __viewerinfo_h
#define __viewerinfo_h 1

/*
  File format
    ViewerInfo
      ModuleInfo[ 0 ]
        AnimInfo[ 0 ][ 0 ]
        ...
        AnimInfo[ 0 ][ number_of_anims-1 ]
        NVF[ 0 ]
	( u32 )0
      ...
      ModuleInfo[ number_of_modules-1 ]
        AnimInfo[ number_of_modules-1 ][ 0 ]
        ...
        AnimInfo[ number_of_modules-1 ][ number_of_anims-1 ]
        NVF[ number_of_modules-1 ]
	( u32 )0
*/

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Declare constant macro */
#define	MODEL_ADDR	(0x200000)
#define	MODEL_MAX_SIZE	(0x1000000)

/* Declare type of structure */
typedef struct _AnimInfo
{
    float	start_frame;
    float	end_frame;
    u8		name[ 24 ];
} AnimInfo;

typedef struct _ModuleInfo
{
    u32		number_of_anims;
    u32		nvf_size;
    u8		name[ 24 ];
    AnimInfo	*anim_info_array;
} ModuleInfo;

typedef struct _ViewerInfo
{
    u32		magic;
    u32		number_of_modules;
    ModuleInfo	*module_info_array;
} ViewerInfo;

/* Declare function */
extern int LoadScene( MhcScene *scene_ptr, ViewerInfo *viewer_info_ptr );

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif	/* __viewerinfo_h */
