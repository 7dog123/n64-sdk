/*
  mgk/Obj.h
    Copyright (C) 1998, NINTENDO Co,Ltd., MONEGI CORPORATION.
    Feb. 26, 1999.
*/

#ifndef _mgk_Obj_h
#define _mgk_Obj_h 1

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <ultra64.h>

/* Declare constant macro */
#define MGK_OBJ_ROT_XYZ		(0)
#define MGK_OBJ_ROT_XZY		(1)
#define MGK_OBJ_ROT_YZX		(2)
#define MGK_OBJ_ROT_YXZ		(3)
#define MGK_OBJ_ROT_ZXY		(4)
#define MGK_OBJ_ROT_ZYX		(5)
#define MGK_OBJ_ROT_LOOK_AT	(6)

/* Declare structure prototype */
struct _MgkObj;
struct _MhcModule;
struct _MhcScene;

/* Structure types */
typedef struct _MgkObj
{
    MvmVector3f			scale;
    MvmVector3f			rotation;
    MvmVector3f			translation;
    MvmVector3f			at;
    MvmVector3f			up;
    int				rotation_mode;

    u32				module_index;
    u32				*camera_mask_ptr;

    u32				anim_start_frame;
    float			*anim_index_ptr;
    float			*anim_time_ptr;
    float			anim_pitch;
    float			anim_start;
    float			anim_length;
    int				anim_loop;

    void			*user_data;
} MgkObj;

/* Declare Functions */
extern void mgkObjInit( MgkObj *obj_ptr, const u32 module_index );
extern int mgkObjLoad( MgkObj *obj_ptr,
		       const u32 rom_start_addr,
		       const u32 rom_end_addr );
extern void mgkObjUnload( MgkObj *obj_ptr );
extern void mgkObjCreateCamera( MgkObj *obj_ptr,
				const float fov_y,
				const float aspect_ratio,
				const float clip_near,
				const float clip_far );
extern void mgkObjSetAnim( MgkObj *obj_ptr, const s32 anim_index );
extern void mgkObjPlayAnim( MgkObj *obj_ptr,
			    const float start,
			    const float end,
			    const float pitch,
			    const int loop );
extern void mgkObjMove( MgkObj *obj_ptr,
			const float x, const float y, const float z );
extern void mgkObjRotate( MgkObj *obj_ptr, const int mode,
			  const float x, const float y, const float z );
extern void mgkObjLookAt( MgkObj *obj_ptr,
			const float x, const float y, const float z,
			const float x_at, const float y_at, const float z_at,
			const float x_up, const float y_up, const float z_up );
extern void mgkObjScale( MgkObj *obj_ptr,
			 const float x, const float y, const float z );
extern void mgkObjEval( struct _MhcScene *scene_ptr, MgkObj *obj_ptr );

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _mgk_Obj_h */
