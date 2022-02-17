/*
 * [CCBL]
 *
 * cam.c
 *
 * Copyright (C) 1998, NINTENDO Co,Ltd.
 * Copyright (C) 1998, MONEGI CORPORATION.
 *
 */
#include "common_include.h"
#include "graphics.h"
#include "cam.h"
#include "pad.h"
#include "trackball.h"

typedef struct fXYZ_s {float x,y,z;} fXYZ;

static fXYZ eyepos;
static fXYZ mdlrot;
static float mdlmtx[4][4];	/*  */
static float curquat[4];
static float lastquat[4];


void
initCam(void )
{
  defaultCam();
}

void
defaultCam(void )
{
  eyepos.x = 0.0;
  eyepos.y = 0.0;
  eyepos.z = 1000.0;

  mdlrot.x = mdlrot.y = mdlrot.z = 0.0;
  trackball(curquat, 0.0, 0.0, 0.0, 0.0);

  guMtxIdentF(mdlmtx);
}

static float theta = 0.0;


/*
 *[Camera Operation]
 *
 *start 		camera reset
 *Z+ Movement of camera on z-axis:
 * 3D_up 	move closer to model
 * 3D_down 	move away from model
 *Z- Track ball operation:
 * 3D_up	rotate view on x-axis
 * 3D_down	rotate view on x-axis 
 * 3D_left 	rotate view on y-axis 
 * 3D_right 	rotate view on y-axis
 */
void
moveCam(void )
{
  Pad_D *pd = &Mpad[0];
  float px,py;

  if(pd->trigger & PAD_ST) defaultCam();

  if(!(pd->button & PAD_ZT)){
    px = 
      ((pd->x_3D > -4) && (pd->x_3D < 4))?
      0.0F:(float)pd->x_3D / 512.0F;
    py = 
      ((pd->y_3D > -4) && (pd->y_3D < 4))?
      0.0F:(float)pd->y_3D / 512.0F;
    trackball(lastquat,
	      0.0F,
	      0.0F,
	      px,
	      py);
    add_quats(lastquat, curquat, curquat);
  }else{
    py = ((pd->y_3D > -4) && (pd->y_3D < 4))?0.0F:(float)pd->y_3D;

    eyepos.z += py;
    if(eyepos.z < 1) 
      eyepos.z = 1.0F;
  }
}


void
makeCam(Dynamic *dynamicp)
{
  u16 persnorm;
  Mtx at;

  moveCam();

  guPerspective(&dynamicp->projection, &persnorm,
		30, 320.0/240.0,500 /*1*/ /*400*/,/*5000*/ 20000, 1.0);
  gSPPerspNormalize(glistp++, persnorm);

  guLookAtReflect(&dynamicp->viewing,&dynamicp->lat,
	   eyepos.x,eyepos.y,eyepos.z,
	   0, 0, 0,
	   0, 1, 0);

  guMtxIdent(&dynamicp->modeling);
  build_rotmatrix(mdlmtx,curquat);
  guMtxF2L(mdlmtx,&at);
  guMtxCatL(&at,&dynamicp->modeling,&dynamicp->modeling);
}


