/*======================================================================*/
/*		NIFFprev						*/
/*		cruise.c						*/
/*									*/
/*		Copyright (C) 1997, NINTENDO Co,Ltd.			*/
/*		Copyright (C) 1998, MONEGI CORPORATION.			*/
/*									*/
/*======================================================================*/
/* revision history							*/
/*  1998/ 6/18	Added  crSetupYPR, so that it is easier to swich from    */
/*		other mode.	                                        */
/*  1999/ 7/19  Deleted #include <math.h>                               */
/*		                				        */
/*======================================================================*/

#define __CRUISE_C

/* Deleted #include <math.h> (99-07-19) */
#include "pack.h"
#include "mode.h"

extern float atan2f(float y, float x);
extern float asinf(float x);

/* ==========================================================================
	define
 ========================================================================== */
#define ANALOG_V_LIM 73
#define ANALOG_H_LIM 70

#define YAW_LIM DEG2RAD(15.0)

#define HOLD_ANGLE_BTN 0

#define MISSION_CHANGE_UP CONT_UP
#define MISSION_CHANGE_DOWN CONT_DOWN

#define ACCEL_FORWARD_BTN CONT_R
#define ACCEL_BACKWARD_BTN CONT_L

#define ACCEL_UP_BTN CONT_CU
#define ACCEL_DOWN_BTN CONT_CD
#define ACCEL_LEFT_BTN CONT_CL
#define ACCEL_RIGHT_BTN CONT_CR

#define SIN60 (0.8660254037844)

/* ===========================================================================
	variables
 =========================================================================== */

static float yaw_ratio, pitch_ratio, roll_ratio;
static float accel;
static float speed_limit;

static int mission;

static float roll, pitch, yaw;
static float yaw_true;
static float x_speed, y_speed, z_speed;
static float ex,ey,ez;

static float mission_ratio[]={10, 20, 40, 80, 160, 320};

#define MISSION_LIM 6

/* ===========================================================================
	functions
 =========================================================================== */
/* ---------------------------------------------------------------------------
	Initialization of the camera
 --------------------------------------------------------------------------- */
void crReset(void)
{
    ex=ey=0.0; ez= -500;
    roll=pitch=yaw=yaw_true=0.0;
    yaw_ratio = YAW_LIM/ANALOG_H_LIM;
    pitch_ratio = DEG2RAD(90)/ANALOG_V_LIM;
    roll_ratio = DEG2RAD(30)/ANALOG_H_LIM;
    speed_limit = 100;
    accel = 0.0;
    mission = 2;
    x_speed=y_speed=z_speed=0.0;
}

float slowin(float val, float lim)
{
    return val*val/lim*SIGN(val);
}

float interp(float now, float tar, float div, float min, float max)
{
    float a;

    a = (tar-now)*div;
    if(ABS(a) > max) a = max*SIGN(a);
    if(ABS(a) < min) a = min*SIGN(a);

    return now + a;
}

/* Keep the "rad" range from 0 - 2 Pi. */

float round_rad(float rad)
{
    while(rad < 0) rad += PI2;
    while(rad > PI2) rad -= PI2;
    return rad;
}

/* Keep the "rad" range from - Pi to Pi. */
float normal_rad(float rad)
{
    rad = round_rad(rad);
    if(rad > PI) rad -= PI2;
    return rad;
}

float interp_rad(float now, float tar, float div, float min, float max)
{
    float a;

    a = normal_rad(tar-now);
    if(ABS(a) > min)
      a = interp(now, now+a, div, 0, max);
    else
      a = now;

    return round_rad(a);
}

void crSetupYPR(Transform *transform)
{
    if( transform->orientation[2][1] > SIN60 ){
	pitch = -PI / 3;
    }else if( transform->orientation[2][1] < -SIN60 ){
	pitch = PI / 3;
    }else pitch = asinf( -transform->orientation[2][1] );
    roll = atan2f( transform->orientation[0][1],
		   transform->orientation[1][1] );
    yaw = atan2f( transform->orientation[2][0],
		  transform->orientation[2][2] );

    ex = transform->translation[0];
    ey = transform->translation[1];
    ez = transform->translation[2];
}

/* ---------------------------------------------------------------------------
	3D cruising
 --------------------------------------------------------------------------- */
void crMove(EXCONTPAD *pad)
{
    float yaw_vec, pitch_true, roll_true;
    float x_accel, y_accel, z_accel;
    float fg;

    yaw_vec = pitch_true = roll_true = 0.0;
    x_accel = y_accel = z_accel = 0.0;

    /* Incline the camera with the 3D stick */
    yaw_vec = yaw_ratio * slowin(-pad[0].about_x, ANALOG_H_LIM);
    pitch_true = pitch_ratio * slowin(pad[0].about_y, ANALOG_V_LIM);
    roll_true = roll_ratio * pad[0].about_x;

    /* Shift change */
    if(pad[0].trigger & MISSION_CHANGE_UP && mission < MISSION_LIM-1)
      ++mission;
    if(pad[0].trigger & MISSION_CHANGE_DOWN && mission > 0)
      --mission;

    /* Accel control */
    if(pad[0].button & ACCEL_FORWARD_BTN) accel -= 0.1;
    else if(pad[0].button & ACCEL_BACKWARD_BTN) accel += 0.1;
    else accel *= 0.1;

    if(accel>1.0) accel = 1.0;
    if(accel<-1.0) accel = -1.0;
    if(ABS(accel)<0.01) accel = 0.0;

    /* The acceleration process */
    z_accel = accel * mission_ratio[mission];

    /* Evaluation of translating */
    if(pad[0].button & ACCEL_LEFT_BTN)
      x_accel = 0.5 * mission_ratio[mission];
    else if(pad[0].button & ACCEL_RIGHT_BTN)
      x_accel = -0.5 * mission_ratio[mission];
    if(pad[0].button & ACCEL_UP_BTN)
      y_accel = 0.5 * mission_ratio[mission];
    else if(pad[0].button & ACCEL_DOWN_BTN)
      y_accel = -0.5 * mission_ratio[mission];

    /* Updaate inertia */
    yaw_true += yaw_vec;
    fg = normal_rad(yaw_true-yaw);
    if(ABS(fg) > YAW_LIM)
      yaw_true = yaw + 1.0 * YAW_LIM * SIGN(fg);
    x_speed = interp(x_speed, x_accel, 1.0/8, 0, speed_limit);
    y_speed = interp(y_speed, y_accel, 1.0/8, 0, speed_limit);
    z_speed = interp(z_speed, z_accel, 1.0/8, 0, speed_limit);

    /* Update "yaw," "pitch" and "roll" */
    if(!(pad[0].button & HOLD_ANGLE_BTN)){
	yaw = interp_rad(yaw, yaw_true, 1.0/10, 0, DEG2RAD(30));
	pitch = interp_rad(pitch, pitch_true, 1.0/20, 0, DEG2RAD(30));
	roll = interp_rad(roll, roll_true, 1.0/20, 0, DEG2RAD(30));
    }

    /* Progress of the camera position */
    x_speed *= 0.3;
    y_speed *= 0.3;
    z_speed *= 0.3;
    ex +=
      x_speed * (cosf(roll)*cosf(yaw)+sinf(pitch)*sinf(roll)*sinf(yaw)) +
      y_speed * (-cosf(yaw)*sinf(roll)+cosf(roll)*sinf(pitch)*sinf(yaw)) +
      z_speed * cosf(pitch)*sinf(yaw);
    ey +=
      x_speed * cosf(pitch) * sinf(roll) +
      y_speed * cosf(pitch) * cosf(roll) +
      z_speed * -sinf(pitch);
    ez +=
      x_speed * (cosf(yaw)*sinf(pitch)*sinf(roll)-cosf(roll)*sinf(yaw)) +
      y_speed * (cosf(roll)*cosf(yaw)*sinf(pitch)+sinf(roll)*sinf(yaw)) +
      z_speed * cosf(pitch)*cosf(yaw);
}

/* ---------------------------------------------------------------------------
	Return the matrix of the current camera position.
 --------------------------------------------------------------------------- */
void crBuildMatrix(Transform *transform)
{
    float	cy, sy, cp, sp, cr, sr;
    cy = cosf( yaw );	sy = sinf( yaw );
    cp = cosf( pitch );	sp = sinf( pitch );
    cr = cosf( roll );	sr = sinf( roll );

    transform->orientation[0][0] = sy * sp * sr + cy * cr;
    transform->orientation[0][1] = cp * sr;
    transform->orientation[0][2] = cy * sp * sr - sy * cr;

    transform->orientation[1][0] = sy * sp * cr - cy * sr;
    transform->orientation[1][1] = cp * cr;
    transform->orientation[1][2] = cy * sp * cr + sy * sr;

    transform->orientation[2][0] = sy * cp;
    transform->orientation[2][1] = -sp;
    transform->orientation[2][2] = cy * cp;

    transform->translation[0] = ex;
    transform->translation[1] = ey;
    transform->translation[2] = ez;

    transformBuildMatrix( transform );
}
