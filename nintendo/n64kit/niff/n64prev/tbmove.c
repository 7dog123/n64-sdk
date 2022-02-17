/*======================================================================*/
/*		NIFFprev						*/
/*		tbmove.c						*/
/*									*/
/*		Copyright (C) 1997,1998, NINTENDO Co,Ltd.		*/
/*		Copyright (C) 1998, MONEGI CORPORATION.			*/
/*									*/
/*======================================================================*/
/* Revision History							*/
/*  1998/ 6/ 8	Reference to matrix, set to create quartanian         	*/
/*		        						*/
/*  1998/ 6/10	Except caluculating spin matrix,   			*/
/*		not to use quartanian           			*/
/*  1998/ 6/15	Object(s), except camera, can operate            	*/
/*  1998/ 6/22	Scaling operation					*/
/*  1999/ 7/19  Deleted #include <math.h>                               */
/*======================================================================*/

#ifndef __TBMOVE_C
#define __TBMOVE_C

/* Deleted #include <math.h> (99-07-19) */
#include "pack.h"
#include "nd.h"
#include "mode.h"
extern MODE gMode;

/* ========================================================================== 
	define
 ========================================================================== */
#define STICKLIMIT_X 80
#define STICKLIMIT_Y 80
#define STICKUNSENSEVAL 7

#define SPINNING_BTN CONT_G
#define SCALE_TUNE_ENABLER CONT_L
#define POSITION_TUNE_ENABLER CONT_R
#define MOVER_U_BTN CONT_CU
#define MOVER_D_BTN CONT_CD
#define MOVER_L_BTN CONT_CL
#define MOVER_R_BTN CONT_CR
#define MOVER_ALL_BTN (MOVER_U_BTN|MOVER_D_BTN|MOVER_L_BTN|MOVER_R_BTN)
#define ZOOMER_ZOOM CONT_UP
#define ZOOMER_REDUCTION CONT_DOWN

#define MOVE_S_LIMIT 10
/* Macro, because rsqrtf() has not been defined */
#define rsqrtf(x) (1.0f/sqrtf(x))

/* ==========================================================================
	static
 ========================================================================== */
/* ----------------------------------- */
static u16 btn, trg, rep;
static s8 stx, sty;
static s8 dx, dy;
static int spin_ena;
static float move_s, move_bias;
static float ofsx, ofsy, ofsz;
static float sclx, scly, sclz;
static float bias;

static float curquat[4], lastquat[4];

/* ==========================================================================
	programs
 ========================================================================== */
/* ------------------------------------------------------------------------- */
void tbReset(void)
{
    trackball(curquat, 0, 0, 0, 0);
    trackball(lastquat, 0, 0, 0, 0);

    ofsx =ofsy = 0.0;
    ofsz = -500.0;

    spin_ena = 0;
    bias = 0.1;

    move_bias = move_s = bias;
}

/* ------------------------------------------------------------------------- */
static void mover(void)
{
    float delta;

    ofsx = 0.0f;
    ofsy = 0.0f;
    ofsz = 0.0f;
    sclx = 0.0f;
    scly = 0.0f;
    sclz = 0.0f;

    /* Depth move */
    if(!(btn & SPINNING_BTN) && (btn & POSITION_TUNE_ENABLER) &&
       !(btn & SCALE_TUNE_ENABLER)){
	ofsz -= sty * bias;
    }
    if(!(btn & SPINNING_BTN) && !(btn & POSITION_TUNE_ENABLER) &&
       (btn & SCALE_TUNE_ENABLER)){
	sclx += stx * 0.001;
	scly += sty * 0.001;
    }
    if(!(btn & SPINNING_BTN) && (btn & POSITION_TUNE_ENABLER) &&
       (btn & SCALE_TUNE_ENABLER)){
	sclz += sty * 0.001;
    }
    /* Move up and down (including fine adjustment) */
    delta = (btn & POSITION_TUNE_ENABLER)? bias: move_bias; 
    if(btn & MOVER_U_BTN) ofsy += delta;
    if(btn & MOVER_D_BTN) ofsy -= delta;
    if(btn & MOVER_L_BTN) ofsx -= delta;
    if(btn & MOVER_R_BTN) ofsx += delta;
    if(!(btn & POSITION_TUNE_ENABLER) && (btn & MOVER_ALL_BTN)){
	/* Something is pressing the key */
	move_bias += move_s;
	move_s = move_s * (1.0+bias);
	if(move_s > MOVE_S_LIMIT*bias)
	  move_s = MOVE_S_LIMIT*bias;
    }else{
	/* Has left the key */
	move_bias = move_s = bias;
    }
}

/* ------------------------------------------------------------------------- */
static void rotater(void)
{
    /* If it's pushing down the spin button, update "lastquat" */
    if((btn & SPINNING_BTN) && !(btn & POSITION_TUNE_ENABLER) &&
       !(btn & SCALE_TUNE_ENABLER)){
	trackball(lastquat, 0,0,
		  bias * stx/STICKLIMIT_X,
		  bias * sty/STICKLIMIT_Y);
	if(stx != 0 || sty != 0)
	  spin_ena = 1;
	else
	  spin_ena = 0;
    }
}

/* ------------------------------------------------------------------------- */
void tbEmulate(EXCONTPAD *pad, Transform *transform)
{
    /* Update the register */
    btn = pad[0].button;
    trg = pad[0].trigger;
    rep = pad[0].repeat;

    dx = pad[0].delta_x;
    dy = pad[0].delta_y;
    stx = pad[0].about_x;
    sty = pad[0].about_y;

    /* Update the quartanian */
    rotater();

    /* Update scaling */
    mover();
}

static void normalize( float *x )
{
    float	k;
    k = rsqrtf( x[0] * x[0] + x[1] * x[1] + x[2] * x[2] );
    x[0] *= k;
    x[1] *= k;
    x[2] *= k;
}

static void ortho( float *result, const float *y, const float *x)
/* Caution: x should be formalized */
{
    float	k;
    k = y[0] * x[0] + y[1] * x[1] + y[2] * x[2];
    result[0] = y[0] - k * x[0];
    result[1] = y[1] - k * x[1];
    result[2] = y[2] - k * x[2];
}

static void cross( float *result, const float *x, const float *y)
{
    result[0] = x[1] * y[2] - x[2] * y[1];
    result[1] = x[2] * y[0] - x[0] * y[2];
    result[2] = x[0] * y[1] - x[1] * y[0];
}

static void build_matrix( float ori[4][4], Transform *transform )
{
    float	translation[3];
    transform->orientation[0][0] = ori[0][0];
    transform->orientation[0][1] = ori[0][1];
    transform->orientation[0][2] = ori[0][2];

    /* revising for matrix */
    normalize(transform->orientation[0]);
    ortho(transform->orientation[1], ori[1], transform->orientation[0]);
    normalize(transform->orientation[1]);
    cross(transform->orientation[2], transform->orientation[0],
	  transform->orientation[1]);
    normalize(transform->orientation[2]);

    translation[0] = gMode.camera_transform.orientation[0][0] * ofsx +
		     gMode.camera_transform.orientation[1][0] * ofsy +
		     gMode.camera_transform.orientation[2][0] * ofsz;
    translation[1] = gMode.camera_transform.orientation[0][1] * ofsx +
		     gMode.camera_transform.orientation[1][1] * ofsy +
		     gMode.camera_transform.orientation[2][1] * ofsz;
    translation[2] = gMode.camera_transform.orientation[0][2] * ofsx +
		     gMode.camera_transform.orientation[1][2] * ofsy +
		     gMode.camera_transform.orientation[2][2] * ofsz;
    transform->translation[0] += translation[0];
    transform->translation[1] += translation[1];
    transform->translation[2] += translation[2];
    transform->scale[0] += sclx;
    transform->scale[1] += scly;
    transform->scale[2] += sclz;

    transformBuildMatrix( transform );
}

static void invert_orientation( float inv[4][4], float mat[4][4] )
{
    guMtxIdentF( inv );
    inv[0][0] = mat[0][0]; inv[1][0] = mat[0][1]; inv[2][0] = mat[0][2];
    inv[0][1] = mat[1][0]; inv[1][1] = mat[1][1]; inv[2][1] = mat[1][2];
    inv[0][2] = mat[2][0]; inv[1][2] = mat[2][1]; inv[2][2] = mat[2][2];
}

static void copy_matrix( float dest[4][4], float src[4][4] )
{
    int i;
    for( i = 0; i < 4; ++i ){
	dest[i][0]=src[i][0];
	dest[i][1]=src[i][1];
	dest[i][2]=src[i][2];
	dest[i][3]=src[i][3];
    }
}

/* ------------------------------------------------------------------------- */
void tbBuildMatrix(Transform *transform)
{
    float	spin[4][4];
    float tmpm2[4][4], tmpm3[4][4];

    /* renewal for matrix spin */
    copy_matrix(tmpm2, transform->orientation);
    if(spin_ena){
	build_rotmatrix(spin, lastquat);
	if( transform != &gMode.camera_transform ){
	    float	invcam[4][4];
	    float	oricam[4][4];
	    float	relative[4][4];
	    invert_orientation(invcam, gMode.camera_transform.orientation);
	    invert_orientation(oricam, invcam);
	    guMtxCatF(transform->orientation, invcam, relative);
	    guMtxCatF(relative, spin, tmpm2);
	    guMtxCatF(tmpm2, oricam, tmpm3);
	    copy_matrix(tmpm2, tmpm3);
	}else{
	    /* It is better to reverse, to operate camera spin */
	    invert_orientation(tmpm3, spin);
	    guMtxCatF(tmpm3, transform->orientation, tmpm2);
	}
    }
    build_matrix(tmpm2, transform);
}

#endif /* #ifndef __TBMOVE_C */
