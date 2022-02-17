/*
  Copyright(C) 1998, NINTENDO Co., Ltd.
  Texture Editor Anime Viewer Converter
*/
/*
   stage01.c 
   Camera angle anime stage
*/

#include <assert.h>
#include <nusys.h>
#include "main.h"
#include "graphic.h"
#include "anmview.h"


/* Camera matrix created with converter */
extern CAnmCtrlTxture* gCamMatrix[];
extern u32 gCamXSize;
extern u32 gCamYSize;


/* Data for anime controller */
static CAnime gAnime;
static CAnmCtrlSetMaxFrame gAnimeFrame = {{ANMCTRL_SETMAXFRAME},1}; /* Set total number of frames */ 
static CAnmCtrlJump        gAnimeJump  = {{ANMCTRL_JUMP},1};        /* Anime loops back to the start  */
static CAnmCtrlHeader* gAnimeCmd[] = {
  (CAnmCtrlHeader*)&gAnimeFrame, /* Set frame units to display */
  (CAnmCtrlHeader*)NULL,         /* Set texture displayed with SelectTexture()  */
  (CAnmCtrlHeader*)&gAnimeJump,  /* Loop in order to display texture */
};


static s32 gAngleX = 0;		        /* Current angle */
static s32 gAngleY = 0;
static float gPanelAngleX = 0.0F; /* Angle of 1 frame */
static float gPanelAngleY = 0.0F;
static BOOL gbTextPrint = TRUE;   /* Display text */


/* Display text on screen */
static void TextPrint(void)
{
  if (TRUE == gbTextPrint) {
    u8 buf[256];
    nuDebConTextPos(NU_DEB_CON_WINDOW0,10,5);	
    nuDebConCPuts(NU_DEB_CON_WINDOW0, "2D CAMERA ANGLE VIEW");
    sprintf(buf, "ANGLE(%3d,%3d)", gAngleX, gAngleY);
    nuDebConTextPos(NU_DEB_CON_WINDOW0,20,24);	
    nuDebConCPuts(NU_DEB_CON_WINDOW0, buf);
  } else {
    nuDebConClear(NU_DEB_CON_WINDOW0);
    nuDebConTextPos(NU_DEB_CON_WINDOW0,0,0);	
    nuDebConCPuts(NU_DEB_CON_WINDOW0, "_");
  }
}

/* Prepare corresponding texture */
static void SelectTexture(void)
{
  CAnmCtrlTxture*  pTex = NULL;
  u32 nX = (gAngleX + 0);
  u32 nY = (gAngleY + 0);
  nX = (nX >= 360) ? (nX - 360) : nX;
  nY = (nY >= 360) ? (nY - 360) : nY;
  nX /= gPanelAngleX;
  nY /= gPanelAngleY;

#if 1
  {
    u8 buf[128];
    sprintf(buf, "Select Texture(%3d,%3d) = %2d", nX, nY, (nY * gCamXSize) + nX);
    nuDebConTextPos(0,5,7);	nuDebConCPuts(0, buf);
  }
#endif
  pTex = gCamMatrix[(nY * gCamXSize) + nX];
  gAnimeCmd[1] = (CAnmCtrlHeader*)pTex;  /* Sets texture which displays */
}


/* Initialize Stage 1 */
void initStage01(void)
{
  if (gCamXSize && gCamYSize) {
    gPanelAngleX = 360 / gCamXSize;  /* Angle of 1 screen */
    gPanelAngleY = 360 / gCamYSize;  /* Angle of 1 screen */
  }
  /* Anime Controler Initialize */
  AnmConstruct(&gAnime, gAnimeCmd);
}


/* Make display list for Stage 1 and run task */
void makeDL01(void)
{
  Dynamic* dynamicp;
  dynamicp = &gfx_dynamic[gfx_gtask_no];

  /* Display list buffer settings */
  glistp = &gfx_glist[gfx_gtask_no][0];

  /*  Initialize RCP */
  gfxRCPInit();

  /* Clear frame buffer and Z buffer */
  gfxClearCfb();


  if (gCamXSize && gCamYSize) {
    /* Set texture to display this time */
    SelectTexture();

    /* Display the selected texture using anime controller */
    AnmViewerMain(&gAnime, &glistp);
  }
  gDPFullSync(glistp++);
  gSPEndDisplayList(glistp++);
  assert((glistp - gfx_glist[gfx_gtask_no]) < GFX_GLIST_LEN);
  /* Display the selected texture using anime controller */
  nuGfxTaskStart(&gfx_glist[gfx_gtask_no][0],
		 (s32)(glistp - gfx_glist[gfx_gtask_no]) * sizeof (Gfx),
		 NU_GFX_UCODE_F3DEX , NU_SC_NOSWAPBUFFER);

  TextPrint();
  nuDebConDisp(NU_SC_SWAPBUFFER);

  /* Swap display list buffer */
  gfx_gtask_no ^= 1;
}


static void Stick(NUContData* pCont)
{
  nuContDataGetEx(gContdata,0);

  /* Turn display of text ON/OFF with Z BUTTON */
  if(pCont->trigger & Z_TRIG) {
    gbTextPrint = (gbTextPrint) ? 0 : 1;
  }

  /* Move to Stage 0 after pressing Start button */
  if(pCont->trigger & (L_TRIG | R_TRIG)) {
      nuGfxFuncRemove();	/* Remove callback function */
      gStage = 0;  			/* Indicate next stage to Main */
  }

  /* Change angle with controller */
  {
    /* Stick */
   	if (abs(pCont->stick_x) > 4) {
      gAngleX += (pCont->stick_x >> 4);
    }
    if (abs(pCont->stick_y) > 4) {
      gAngleY -= (pCont->stick_y >> 4);
    }
    /* + key */
    {
      /* Faster with pushing A_BUTTON */
      u32 nSpeed = (pCont->button & A_BUTTON) ? 4 : 1;
      gAngleX += ((pCont->button & CONT_RIGHT) ? nSpeed : 0)
               - ((pCont->button & CONT_LEFT)  ? nSpeed : 0);
      gAngleY += ((pCont->button & CONT_DOWN)  ? nSpeed : 0)
               - ((pCont->button & CONT_UP)    ? nSpeed : 0);
    }
    gAngleX = (gAngleX >= 360) ? (gAngleX - 360) : gAngleX;
    gAngleX = (gAngleX <    0) ? (360 + gAngleX) : gAngleX;
    gAngleY = (gAngleY >= 360) ? (gAngleY - 360) : gAngleY;
    gAngleY = (gAngleY <    0) ? (360 + gAngleY) : gAngleY;
  }
}

/* Advance game process for Stage 1 */
void updateGame01(void)
{  
  /* Read Controller 1 data */
  Stick(gContdata);
}

