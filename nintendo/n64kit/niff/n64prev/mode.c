/*======================================================================*/
/*		NIFFprev						*/
/*		mode.c							*/
/*									*/
/*		Copyright (C) 1997,1998, NINTENDO Co,Ltd.		*/
/*		Copyright (C) 1998, MONEGI CORPORATION.			*/
/*									*/
/*======================================================================*/
/* Revision history							*/
/*  1998/ 8/21	Added ULTRA_D_BUG macro				*/
/*======================================================================*/

#include <ultra64.h>
#include "mode.h"

#define ULTRA_D_BUG 1
/*
    Macro to handle a bug that larger value than OS_VI_DITHER_FILTER_OFF cannot be given as an argument of osViSetSpecialFeatures( ) of gultra_d.  
*/

void transformInit( Transform *transform )
{
    int		i, j;
    float	value;

    transform->translation[0] = 0.0;
    transform->translation[1] = 0.0;
    transform->translation[2] = 0.0;

    transform->scale[0] = 1.0;
    transform->scale[1] = 1.0;
    transform->scale[2] = 1.0;

    for(i = 0; i < 4; ++i){
	for(j = 0; j < 4; ++j ){
	    value = (float)( i == j );
	    transform->orientation[i][j] = value;
	    transform->matrix[i][j] = value;
	}
    }
}

void transformCopy( Transform *dest, const Transform *src )
{
    int	i, j;

    for(i = 0; i < 3; ++i){
	dest->translation[i] = src->translation[i];
	dest->scale[i] = src->scale[i];
    }

    for(i = 0; i < 4; ++i){
	for(j = 0; j < 4; ++j ){
	    dest->orientation[i][j] = src->orientation[i][j];
	    dest->matrix[i][j] = src->matrix[i][j];
	}
    }
}

void transformBuildMatrix( Transform *transform )
{
    int	i, j;

    for(i = 0; i < 3; ++i){
	for(j = 0; j < 3; ++j ){
	    transform->matrix[i][j] = transform->orientation[i][j] *
				      transform->scale[i];
	}
    }

    transform->matrix[3][0] = transform->translation[0];
    transform->matrix[3][1] = transform->translation[1];
    transform->matrix[3][2] = transform->translation[2];

    transform->matrix[0][3] = 0.0f;
    transform->matrix[1][3] = 0.0f;
    transform->matrix[2][3] = 0.0f;
    transform->matrix[3][3] = 1.0f;
}

void modeResetLights( MODE *mode )
{
    int	i;

    mode->active_light = LIGHT_DEFAULT;
    mode->ambient.r = 127;
    mode->ambient.g = 127;
    mode->ambient.b = 127;
    for( i = 0; i < 7; ++i ){
	mode->light_color[i].r = 0;
	mode->light_color[i].g = 0;
	mode->light_color[i].b = 0;
	transformInit( &mode->light_transform[i] );
	mode->light_transform[1].matrix[0][0] = 0.0;
	mode->light_transform[1].matrix[0][1] = -1.0;
	mode->light_transform[1].matrix[0][2] = 0.0;
	mode->light_transform[1].matrix[1][0] = 1.0;
	mode->light_transform[1].matrix[1][1] = 0.0;
	mode->light_transform[1].matrix[1][2] = 0.0;
    }
    mode->light_color[0].r = 255;
    mode->light_color[0].g = 255;
    mode->light_color[0].b = 255;
}

void modeLoadDefaultBG( MODE *mode, NDD_SCENE *scene )
{
    Color4iUnpackRGBA5551( &mode->default_bg_color, scene->fill_col );
    mode->default_bg_color.a = 255;
}

void modeLoadDefaultFog( MODE *mode, NDD_SCENE *scene )
{
    mode->fog.color.r = scene->fog.color.r;
    mode->fog.color.g = scene->fog.color.g;
    mode->fog.color.b = scene->fog.color.b;
    mode->fog.color.a = scene->fog.color.a;
    mode->fog.near = scene->fog.near;
    mode->fog.far = scene->fog.far;
    mode->fog.enable = 0;
}

void modeResetBG( MODE *mode )
{
    mode->bg_color = mode->default_bg_color;
}

void modeResetFog( MODE *mode )
{
    mode->fog = mode->default_fog;
}

void modeResetCamera( MODE *mode )
{
    mode->camera_mode = CAMERA_CONTROL;
    transformInit( &mode->camera_transform );
    mode->camera_transform.translation[2] = 500.0;
    mode->camera_transform.matrix[3][2] = 500.0;
}

void modeResetObject( MODE *mode )
{
    mode->active_object = OBJECT_SCENE;
    transformInit( &mode->object_transform );
}

void modeLoadVideoMode( MODE *mode )
{
    u32	video_mode;
    video_mode = osViGetStatus( );
    mode->gamma_enable = ( video_mode & VI_CTRL_GAMMA_ON ) ? 1 : 0;
    mode->gamma_dither_enable =
		( video_mode & VI_CTRL_GAMMA_DITHER_ON ) ? 1 : 0;
    mode->dither_filter_enable =
		( video_mode & VI_CTRL_DITHER_FILTER_ON ) ? 1 : 0;
    mode->divot_enable = ( video_mode & VI_CTRL_DIVOT_ON ) ? 1 : 0;
}

void modeStoreVideoMode( MODE *mode )
{
#ifdef ULTRA_D_BUG
    osViSetSpecialFeatures( ( mode->gamma_enable ) ?
			    OS_VI_GAMMA_ON : OS_VI_GAMMA_OFF );
    osViSetSpecialFeatures( ( mode->gamma_dither_enable ) ?
			    OS_VI_GAMMA_DITHER_ON : OS_VI_GAMMA_DITHER_OFF );
    osViSetSpecialFeatures( ( mode->dither_filter_enable ) ?
			    OS_VI_DITHER_FILTER_ON : OS_VI_DITHER_FILTER_OFF );
    osViSetSpecialFeatures( ( mode->divot_enable ) ?
			    OS_VI_DIVOT_ON : OS_VI_DIVOT_OFF );
#else
    u32 video_mode = 0;
    video_mode |= ( mode->gamma_enable ) ? OS_VI_GAMMA_ON : OS_VI_GAMMA_OFF;
    video_mode |= ( mode->gamma_dither_enable ) ?
			OS_VI_GAMMA_DITHER_ON : OS_VI_GAMMA_DITHER_OFF;
    video_mode |= ( mode->dither_filter_enable ) ?
			OS_VI_DITHER_FILTER_ON : OS_VI_DITHER_FILTER_OFF;
    video_mode |= ( mode->divot_enable ) ? OS_VI_DIVOT_ON : OS_VI_DIVOT_OFF;
    osViSetSpecialFeatures( video_mode );
#endif
}
