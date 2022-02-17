/*
  nvfview
  mode.h
    Copyright (C) 1998-1999, NINTENDO Co,Ltd., MONEGI CORPORATION.
    Jan. 28, 1999.
*/

#ifndef __mode_h
#define __mode_h

#include "mhc/Node.h"
#include "mvm/Color.h"

#define OBJECT_NINTENDO		(0)
#define OBJECT_SCENE		(1)

#define CAMERA_CONTROL		(0)
#define CAMERA_SCENE		(1)

#define LIGHT_DEFAULT		(0)
#define LIGHT_SCENE		(1)

#define ANIM_PITCH_1		(0)
#define ANIM_PITCH_HALF		(1)
#define ANIM_PITCH_QUARTER	(2)
#define ANIM_PITCH_2		(3)

typedef struct {
    MvmColor4l	color;
    int 	near, far;
    int		is_active;

    MhcNode	*node_ptr;
    float	*near_ptr;
    float	*far_ptr;
    float	*color_ptr;
    u32		*flags_ptr;
} Fogi;

typedef struct {
    int		active_object;
    int		perfmon_enable;
    int		gamma_enable;
    int		gamma_dither_enable;
    int		divot_enable;
    int		dither_filter_enable;
    int		camera_mode;
    int		scene_camera_enable;
    int		anim_pitch;
    int		anim_index;
    int		resolution;
    int		icon_visibility;
    MvmColor4l	bg_color;
    MhcNode	*bg_node_ptr;
    float	*bg_color_ptr;
    MvmColor4l	default_bg_color;
    Fogi	fog;
    Fogi	default_fog;
    int		camera_reset_request;
    int		object_reset_request;
} MODE;

extern void modeResetCamera( MODE *mode );
extern void modeResetObject( MODE *mode );
extern void modeResetBG( MODE *mode );
extern void modeResetFog( MODE *mode );
extern void modeLoadVideoMode( MODE *mode );
extern void modeStoreBG( MODE *mode );
extern void modeStoreFog( MODE *mode );
extern void modeStoreVideoMode( MODE *mode );

extern MODE gMode;

#endif	/* __mode_h */
