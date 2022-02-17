/*
 * [CCBL]
 *
 * light.c
 *
 * Copyright (C) 1998, NINTENDO Co,Ltd.
 * Copyright (C) 1998, MONEGI CORPORATION.
 *
 */
#include "common_include.h"
#include "graphics.h"
#include "light.h"
#include "pad.h"

static Lights7 ccbl_light[2];

static Lights7 d_ccbl_light =	/* Use directional only (except Light 7) */
 gdSPDefLights7(
		0x40,0x40,0x40,	/* ambient light*/
		0xc0,0x00,0x00,
		0,0,80,		/* Light 1  front*/
		0x00,0xc0,0x00,
		0,80,0,		/* Light 2  top */
		0x00,0x00,0xc0,
		80,0,0,		/* Light 3  right */
		0x00,0x00,0x00,
		0,-80,0,		/* Light 4 bottom */
		0x00,0x00,0x00,
		-80,0,0,		/* Light 5 left */
		0x00,0x00,0x00,
	       -80,80,80,	/* Light 6 left upper*/
		0x00,0x00,0x00,
		0,0,0		/* Light 7 orbiter */
		);

static float orbiter_angle;


void
init_light_sys(void )
{
  bcopy(&d_ccbl_light,&ccbl_light[0],sizeof(Lights7));
  bcopy(&d_ccbl_light,&ccbl_light[1],sizeof(Lights7));
  orbiter_angle = 0;
}


void
orbiter_light_move(void )
{
  orbiter_angle +=0.5;
  if(orbiter_angle > 360.0) orbiter_angle = 0.0;

}

Lights7 *
make_ccbl_light(int frame)
{
  float x,z;

  x = sinf((orbiter_angle/180.0)*3.141559) * 80.0;
  z = cosf((orbiter_angle/180.0)*3.141559) * 80.0;

  ccbl_light[frame].l[6].l.dir[0] = (s8)x;
  ccbl_light[frame].l[6].l.dir[1] = 0;
  ccbl_light[frame].l[6].l.dir[2] = (s8)z;
  return &ccbl_light[frame];
}

