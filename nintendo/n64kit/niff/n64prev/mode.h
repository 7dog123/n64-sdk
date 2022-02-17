/*======================================================================*/
/*		NIFFprev						*/
/*		mode.h							*/
/*									*/
/*		Copyright (C) 1997,1998, NINTENDO Co,Ltd.		*/
/*		Copyright (C) 1998, MONEGI CORPORATION.			*/
/*									*/
/*======================================================================*/
#ifndef __mode_h
#define __mode_h

#include "nd.h"

#define OBJECT_NINTENDO		(0)
#define OBJECT_SCENE		(1)

#define CAMERA_CONTROL		(0)
#define CAMERA_SCENE		(1)

#define LIGHT_DEFAULT		(0)
#define LIGHT_SCENE		(1)

#define CONTROL_MODE_TRACKBALL	(0)
#define CONTROL_MODE_CRUISE	(1)

#define CONTROL_CAMERA		(0)
#define CONTROL_OBJECT		(1)
#define CONTROL_LIGHT1		(2)
#define CONTROL_LIGHT2		(3)
#define CONTROL_LIGHT3		(4)
#define CONTROL_LIGHT4		(5)
#define CONTROL_LIGHT5		(6)
#define CONTROL_LIGHT6		(7)
#define CONTROL_LIGHT7		(8)

#define ANIM_TOGGLE		(0)
#define ANIM_STEP		(1)

typedef struct {
    int r, g, b, a;
} Color4i;

typedef struct {
    Color4i	color;
    int 	near, far;
    int		enable;
} Fogi;

typedef struct _Transform {
    float	translation[3];
    float	scale[3];
    float	orientation[4][4];	/* In reality,3x3 but to use gu*().   */
    float	matrix[4][4];		/* only matrix is used for drawing.  */
} Transform;

typedef struct {
    int		active_object;
    int		perfmon_enable;
    int		deform_enable;
    int		gamma_enable;
    int		gamma_dither_enable;
    int		divot_enable;
    int		dither_filter_enable;
    float	anim_step;
    int		camera_mode;
    int		control_mode;
    int		control;
    int		anim_mode;
    Color4i	bg_color;
    Color4i	default_bg_color;
    Color4i	ambient;
    Color4i	light_color[7];
    Fogi	fog;
    Fogi	default_fog;
    int 	active_light;
    Transform	camera_transform;
    Transform	object_transform;
    Transform	light_transform[7];
} MODE;

extern void transformInit( Transform *transform );
extern void transformCopy( Transform *dest, const Transform *src );
extern void transformBuildMatrix( Transform *transform );

extern void modeResetCamera( MODE *mode );
extern void modeResetObject( MODE *mode );
extern void modeResetLights( MODE *mode );
extern void modeResetBG( MODE *mode );
extern void modeResetFog( MODE *mode );
extern void modeLoadDefaultBG( MODE *mode, NDD_SCENE *scene );
extern void modeLoadDefaultFog( MODE *mode, NDD_SCENE *scene );
extern void modeLoadVideoMode( MODE *mode );
extern void modeStoreVideoMode( MODE *mode );

extern MODE gMode;

#define Color4iPackRGBA5551(c) GPACK_RGBA5551((c)->r,(c)->g,(c)->b,(c)->a)
#define Color4iUnpackRGBA5551(c,i) {\
    (c)->r = ( ( (i) & 0xF800 ) >> 8 );\
    (c)->g = ( ( (i) & 0x07C0 ) >> 3 );\
    (c)->b = ( ( (i) & 0x003E ) << 2 );\
    (c)->a = ( (i) & 0x0001 ) ? 0xff : 0;\
    (c)->r |= (c)->r >> 5;\
    (c)->g |= (c)->g >> 5;\
    (c)->b |= (c)->b >> 5;\
}

#endif	/* __mode_h */
