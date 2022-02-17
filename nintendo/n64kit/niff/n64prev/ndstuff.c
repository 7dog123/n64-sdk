/*======================================================================*/
/*		NIFFprev						*/
/*		ndstuff.c						*/
/*									*/
/*		Copyright (C) 1997,1998, NINTENDO Co,Ltd.		*/
/*									*/
/*======================================================================*/
#define __NDSTUFF_C

/* :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
	Simple 3D Manager "ND"

	Expansion functions: "gu" and "g"
 :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: */

#include "pack.h"
#include "nd.h"

/* ===========================================================================
	static variables
 =========================================================================== */

/* ===========================================================================
	public functions
 =========================================================================== */

/* ----------------------------------------------------------------------------
name:
  ndguTranslateF, ndguScaleF, ndguRotateRPYF, ndguRotateXF, ndguRotateYF,
  ndguRotateZF, ndguMtxCatF33
synopsis:
  void ndguTranslateF(float mf[4][4], float x, float y, float z);
  void ndguScaleF(float mf[4][4], float x, float y, float z);
  void ndguRotateXYZF(float mf[4][4], float r, float p, float h);
  void ndguRotateZXYF(float mf[4][4], float r, float p, float h);
  void ndguRotateZYXF(float mf[4][4], float r, float p, float h);
  void ndguRotateXF(float mf[4][4], float rot);
  void ndguRotateYF(float mf[4][4], float rot);
  void ndguRotateZF(float mf[4][4], float rot);
  void ndguMtxCatF33(float ans[4][4], float ml[3][3]);
description:
 A group of matrix operation functuons of the simple version.
  Each of ndguTranslateF, ndguScaleF, ndguRotateXYZF, ndguRotateXF, ndguRotateYFand ndguRotateZF is the extended version fo functions supplied within           "libultra."
  ndguMtxCatF33 is a module which provides the matrix multiplication between the 3x3 matrix and the 4x4 matrix.
  
parameter:
  float mf[4][4];
  float ans[4][4];
	The matrix which becomes the operating object. 
  float x,y,z;
	Any of the moving amount of each axis (ndguTranslateF), the angle (ndguRotate*)
	or the scale value(ndguScaleF)
  float rot;
	Teh rotational angle. A DEGREE
  float ml[4][4];
	The matrix which becomes the operation.
notes:
---------------------------------------------------------------------------- */
void ndguTranslateF(float mf[4][4], float x, float y, float z)
{
    int i;

    for(i=0; i<4; ++i)
      mf[3][i] += mf[0][i]*x + mf[1][i]*y + mf[2][i]*z;
}

void ndguScaleF(float mf[4][4], float x, float y, float z)
{
    int i;

    for (i=0; i<3; i++) {
	mf[0][i] *= x;
	mf[1][i] *= y;
	mf[2][i] *= z;
    }	
}

void ndguMtxCatF33(float ans[4][4], float ml[3][3])
{
    int	i, j, k;
    float temp[3][3];

    for (i=0; i<3; i++) {
	for (j=0; j<3; j++) {
	    temp[i][j] = 0.0;
	    for (k=0; k<3; k++) {
		temp[i][j] += ml[i][k] * ans[k][j];
	    }
	}
    }

    /* make sure we handle case where result is an input */
    for (i=0; i<3; i++) {
	for (j=0; j<3; j++) {
	    ans[i][j] = temp[i][j];
	}
    }
}

void ndguRotateF(float mf[4][4], float a, float x, float y, float z)
{
    float ans[3][3];
    static float dtor = 3.1415926 / 180.0;
    float sine;
    float cosine;
    float ab, bc, ca, t;

    guNormalize(&x, &y, &z);
    a *= dtor;
    sine = sinf(a);
    cosine = cosf(a);
    t = (1-cosine);
    ab = x*y*t;
    bc = y*z*t;
    ca = z*x*t;

    t = x*x;
    ans[0][0] = t+cosine*(1-t);
    ans[2][1] = bc-x*sine;
    ans[1][2] = bc+x*sine;

    t = y*y;
    ans[1][1] = t+cosine*(1-t);
    ans[2][0] = ca+y*sine;
    ans[0][2] = ca-y*sine;

    t = z*z;
    ans[2][2] = t+cosine*(1-t);
    ans[1][0] = ab-z*sine;
    ans[0][1] = ab+z*sine;

    ndguMtxCatF33(mf, ans);
}

/* Old xguRotateRPYF() */
void ndguRotateXYZF(float mf[4][4], float x, float y, float z)
{
    float ans[3][3];
    static float dtor = 3.1415926 / 180.0;
    float sinx, siny, sinz;
    float cosx, cosy, cosz;

    x *= dtor;
    y *= dtor;
    z *= dtor;
    sinx = sinf(x);
    cosx = cosf(x);
    siny = sinf(y);
    cosy = cosf(y);
    sinz = sinf(z);
    cosz = cosf(z);

    ans[0][0] = cosy*cosz;
    ans[0][1] = cosy*sinz;
    ans[0][2] = -siny;

    ans[1][0] = sinx*siny*cosz - cosx*sinz;
    ans[1][1] = sinx*siny*sinz + cosx*cosz;
    ans[1][2] = sinx*cosy;

    ans[2][0] = cosx*siny*cosz + sinx*sinz;
    ans[2][1] = cosx*siny*sinz - sinx*cosz;
    ans[2][2] = cosx*cosy;

    ndguMtxCatF33(mf, ans);
}

void ndguRotateZYXF(float mf[4][4], float x, float y, float z)
{
    float ans[3][3];
    static float dtor = 3.1415926 / 180.0;
    float sinx,cosx,siny,cosy,sinz,cosz;
    float t;

    x *= dtor;
    y *= dtor;
    z *= dtor;
    sinx = sinf(x);
    cosx = cosf(x);
    siny = sinf(y);
    cosy = cosf(y);
    sinz = sinf(z);
    cosz = cosf(z);

    t = cosz*siny;
    ans[0][0] = cosy*cosz;
    ans[0][1] = sinx*t + cosx*sinz;
    ans[0][2] =-cosx*t + sinx*sinz;

    t = siny*sinz;
    ans[1][0] =-cosy*sinz;
    ans[1][1] = cosx*cosz - sinx*t;
    ans[1][2] = cosz*sinx + cosx*t;

    ans[2][0] = siny;
    ans[2][1] =-cosy*sinx;
    ans[2][2] = cosx*cosy;

    ndguMtxCatF33(mf, ans);
}

void ndguRotateZXYF(float mf[4][4], float x, float y, float z)
{
    float ans[3][3];
    static float dtor = 3.1415926 / 180.0;
    float sinx,cosx,siny,cosy,sinz,cosz;
    float t;

    x *= dtor;
    y *= dtor;
    z *= dtor;
    sinx = sinf(x);
    cosx = cosf(x);
    siny = sinf(y);
    cosy = cosf(y);
    sinz = sinf(z);
    cosz = cosf(z);

    t = sinx*sinz;
    ans[0][0] =  cosy*cosz + siny*t;
    ans[0][1] =  cosx*sinz;
    ans[0][2] = -cosz*siny + cosy*t;

    t = cosz*sinx;
    ans[1][0] =  siny*t - cosy*sinz;
    ans[1][1] =  cosx*cosz;
    ans[1][2] =  cosy*t + siny*sinz;

    ans[2][0] =  cosx*siny;
    ans[2][1] = -sinx;
    ans[2][2] =  cosx*cosy;

    ndguMtxCatF33(mf, ans);
}

void ndguRotateXF(float mf[4][4], float rot)
{
    int i;
    static float dtor = 3.1415926 / 180.0;
    float sinx, cosx;
    float ftmp[4];

    ftmp[0] = rot*dtor;
    sinx = sinf(ftmp[0]);
    cosx = cosf(ftmp[0]);

    for(i=0; i<3; ++i)
      ftmp[i] = mf[1][i];

    for(i=0; i<3; ++i){
	mf[1][i] =  ftmp[i]*cosx + mf[2][i]*sinx;
	mf[2][i] = -ftmp[i]*sinx + mf[2][i]*cosx;
    }
}

void ndguRotateYF(float mf[4][4], float rot)
{
    int i;
    static float dtor = 3.1415926 / 180.0;
    float siny, cosy;
    float ftmp[4];

    ftmp[0] = rot*dtor;
    siny = sinf(ftmp[0]);
    cosy = cosf(ftmp[0]);

    for(i=0; i<3; ++i)
      ftmp[i] = mf[0][i];

    for(i=0; i<3; ++i){
	mf[0][i] = ftmp[i]*cosy - mf[2][i]*siny;
	mf[2][i] = ftmp[i]*siny + mf[2][i]*cosy;
    }
}

void ndguRotateZF(float mf[4][4], float rot)
{
    int i;
    static float dtor = 3.1415926 / 180.0;
    float sinz, cosz;
    float ftmp[4];

    ftmp[0] = rot*dtor;
    sinz = sinf(ftmp[0]);
    cosz = cosf(ftmp[0]);

    for(i=0; i<3; ++i)
      ftmp[i] = mf[0][i];

    for(i=0; i<3; ++i){
	mf[0][i] =  ftmp[i]*cosz + mf[1][i]*sinz;
	mf[1][i] = -ftmp[i]*sinz + mf[1][i]*cosz;
    }
}

/* ----------------------------------------------------------------------------
name:
  ndgDPSetCombineMode
synopsis:
  Gfx *ndgDPSetCombineMode(Gfx *glp, u8 a[8], u8 b[8]);
description:
  A function which supplies method to specify RDP mode setting, dynamically.
parameter:
  Gfx *glp;
	The constructing destination of the display list.
  u8 a[8];
	CC or AC modes on the cycle 1 side.  (Composed of "NDR_CC_*")
  u8 b[8];
	CC or AC modes on the cycle 2 side.  (Composed of "NDR_CC_*")
return:
  Gfx *;
	The updated Gfx pointer.
---------------------------------------------------------------------------- */
Gfx *ndgDPSetCombineMode(Gfx *glp, u8 a[8], u8 b[8])
{
    unsigned int i;

    i =  G_SETCOMBINE << 24;
    i |= ((a[0]&15)<<20) | ((a[2]&31)<<15) | (a[4]<<12) | (a[6]<<9);
    i |= ((b[0]&15)<<5) | (b[2]&31);
    glp->words.w0 = i;
    i =  ((a[1]&15)<<28) | ((a[3]&7)<<15) | (a[5]<<12) | (a[7]<<9);
    i |= ((b[1]&15)<<24) | (b[4]<<21) | (b[6]<<18) | ((b[3]&7)<<6)
      | (b[5]<<3) | b[7];
    glp->words.w1 = i;

    return ++glp;
}

/* ----------------------------------------------------------------------------
name:
  ndgDPSetRenderMode
synopsis:
  Gfx *ndgDPSetRenderMode(Gfx *glp, u32 rdmode);
description:
 A function which supplies method to specify RDP mode setting, dynamically.  
parameter:
  Gfx *glp;
	The constructing destination of the display list. 
  u32 rdmode;
        The RenderMode value composed of the constant value and "NDC_RM_*." 
return:
  Gfx *;
	The updated Gfx pointer
---------------------------------------------------------------------------- */
static u32 sv(u32 *a, u32 val)
{
    int i;

    for(i=0; a[i] != 0xffffffff; i+=2)
      if(a[i] ==  val)
	return a[i+1];

    return 0xffffffff;
}

static u32 mux(u32 val)
{
    u32 f;

    f  = ((val&0xc0) >> 6) << 30;
    f |= ((val&0x30) >> 4) << 26;
    f |= ((val&0x0c) >> 2) << 22;
    f |= ( val&0x03      ) << 18;

    return f;
}

Gfx *ndgDPSetRenderMode(Gfx *glp, u32 src)
{
    static u32 cvgdst[]={
	NDC_RM_CVG_DST_CLAMP, CVG_DST_CLAMP,
	NDC_RM_CVG_DST_WRAP, CVG_DST_WRAP,
	NDC_RM_CVG_DST_FULL, CVG_DST_FULL,
	NDC_RM_CVG_DST_SAVE, CVG_DST_SAVE,
	0xffffffff, 0xffffffff,
    };
    static u32 zmode[]={
	NDC_RM_ZMODE_OPA, ZMODE_OPA,
	NDC_RM_ZMODE_INTER, ZMODE_INTER,
	NDC_RM_ZMODE_XLU, ZMODE_XLU,
	NDC_RM_ZMODE_DEC, ZMODE_DEC,
	0xffffffff, 0xffffffff,
    };
    u32 tar;

    tar = 0;
    if( src & NDC_RM_AA_EN ) tar |= AA_EN;
    if( src & NDC_RM_Z_CMP ) tar |= Z_CMP;
    if( src & NDC_RM_Z_UPD ) tar |= Z_UPD;
    if( src & NDC_RM_IM_RD ) tar |= IM_RD;
    tar |= sv(cvgdst, src & NDC_RM_CVG_DST);
    if( src & NDC_RM_CLR_ON_CVG ) tar |= CLR_ON_CVG;
    if( src & NDC_RM_CVG_X_ALPHA ) tar |= CVG_X_ALPHA;
    if( src & NDC_RM_ALPHA_CVG_SEL ) tar |= ALPHA_CVG_SEL;
    if( src & NDC_RM_FORCE_BL ) tar |= FORCE_BL;
    tar |= sv(zmode, src & NDC_RM_ZMODE);
    tar |= mux((src & NDC_RM_BLENDER_MUX0)>>8);
    tar |= mux(src & NDC_RM_BLENDER_MUX1)>>2;

    glp->words.w0 = (G_SETOTHERMODE_L<<24)|(G_MDSFT_RENDERMODE<<8)|29;
    glp->words.w1 = tar;

    return ++glp;
}

/* ----------------------------------------------------------------------------
name:
    ndguRGBA32ToRGBA16
synopsis:
    u16 bmConvRGBA32ToRGBA16( u32 col );
description:
    Convert RGBA color values of 32 bits to RGBA color values of 16 bits
    (5, 5, 5, 1). 
parameter:
    u32 col;
	The 32-bit color values (R,G,B,A = 8,8,8,8)
return:
    u16;
	The 16-bit color values (R,G,B,A=5,5,5,1)
notes:
    The A component of the 16-bit color value after the conversion is 1 bit.
    But, be careful that this is a copy of the most significant bit of the 
    original A component.
---------------------------------------------------------------------------- */
u16 ndguRGBA32ToRGBA16( u32 col )
{
    return
      ((col & 0xf8000000) >> 16) | 
      ((col & 0x00f80000) >> 13) |
      ((col & 0x0000f800) >> 10) |
      ((col & 0x00000080) >> 7);
}

/* ----------------------------------------------------------------------------
name:
    ndguCalcFadeColor
synopsis:
    RGBAQUAD *ndguCalcFadeColor(RGBAQUAD *tar, int ofs, int wlev)
description:
    Modulates the brightness and density, specified by "ofs" and "wlev" 
    respectively, of the color specified by "tar," and then returns the 
    modulated color. 
parameter:
    RGBAQUAD *tar;
	The pointer for the color value which can write the modulation.
    int ofs;
	The brightness level.  0~255.  The larger it is, the brighter it is.
    int wlev;
	The white level.  0~255.  The larger it is, the whiter it becomes.  
return:
    RGBQUAD *;
	"tar" returns as it is.  
notes:
    Be careful that it hasn't provided the over check.
---------------------------------------------------------------------------- */
RGBAQUAD *ndguCalcFadeColor(RGBAQUAD *tar, int flag, int ofs, int wlev)
{
    int i, m;
    u8 *up;

    up = (u8*)tar;
    m = 0x08;
    for(i=0; i<4; ++i, m>>=1)
      if(flag & m)
	up[i] = (((u32)up[i] * ofs) >> 8) + wlev;

    return tar;
}

/* ----------------------------------------------------------------------------
name:
    ndguCalcGradationColor
synopsis:
    RGBAQUAD *ndguCalcGradationColor(RGBAQUAD *tar, int flag, RGBAQUAD *fact, int lev)
description:
    Mix 2 color values of "tar" with "fact" by using "lev," and then return
    the mixed color to "tar."   
    The calculation method is (tar*(255-lev) + fact*lev) >> 8. 
proparameter:
    RGBAQUAD *tar;
	The color of the source of the blend. 
    int flag;
	Specify the color channel, which becomes the object of the blend, with b	its.  
	  bit 0(0x01) ... Red
	  bit 1(0x02) ... Green
	  bit 2(0x04) ... Blue
	  bit 3(0x08) ... Alpha
    RGBAQUAD *fact;
	The color for mixing with "tar."  
    int lev;
	The blend ratio of "fact."  Also, a reciprocal of brightness of "tar."  0~255
return:
    RGBAQUAD *;
	"tar" returns as it is. 
notes:
---------------------------------------------------------------------------- */
RGBAQUAD *ndguCalcGradationColor(RGBAQUAD *tar, int flag, RGBAQUAD *fact, int lev)
{
    int i, m, rlev;
    u8 *up1, *up2;

    rlev =255-lev;
    up1 = (u8*)tar;
    up2 = (u8*)fact;
    m = 0x01;
    for(i=0; i<4; ++i, m<<=1)
      if(flag & m)
	up1[i] = ((up1[i] * lev) + (up2[i] * rlev)) >> 8;

    return tar;
}

/* ----------------------------------------------------------------------------
name:
    ndguNormalize
synopsis:
    void ndguNormalize(float nv[3]);
description:
    Consider nv as float[3] and normalize it
parameter:
    float nv[3];
	Pointer that is stored with information of un-normalized normal
return:
    float;
	Length of vector
---------------------------------------------------------------------------- */
float ndguNormalize(float nv[3])
{
    float retval, d;

    retval = sqrtf(nv[0]*nv[0] + nv[1]*nv[1] + nv[2]*nv[2]);
    d = 1.0 / retval;

    nv[0] *= d;
    nv[1] *= d;
    nv[2] *= d;

    return retval;
}

/* ----------------------------------------------------------------------------
name:
    ndguCalcNormal
synopsis:
    void ndguCalcNormal(float nv[3], float *a, float *b);
description:
    Consider that a and b are arrays stored the vertex of float[3]; and 
    calculate the normal vector when b looks at a.  Then, store it in "nv".
parameter:
    float nv[3];
	The buffer pointer which stores the created normal vector. 
    float *a;
	The gazing point
    float *b;
	The view
return:
    float;
	Length of vector
---------------------------------------------------------------------------- */
float ndguCalcNormal(float nv[3], float *a, float *b)
{
    int i;

    for(i=0; i<3; ++i)
      nv[i] = a[i]-b[i];

    return ndguNormalize(nv);
}

/* ==========================================================================
	end of file.						%eof
 ========================================================================== */
