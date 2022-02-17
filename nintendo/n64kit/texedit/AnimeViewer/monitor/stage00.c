/*
  Copyright(C) 1998, NINTENDO Co., Ltd.
  Texture Editor Anime Viewer Converter
*/
/*
   stage00.c 
   2D Anime Viewer state
*/

#include <assert.h>
#include <nusys.h>
#include "main.h"
#include "graphic.h"
#include "teapi.h"
#include "anmview.h"

/* Anime data */
#include "anmdata.h"
static CAnime gAnime;               /* Anime object */
extern CAnmCtrlHeader* gAnimeCmd[]; /* Anime command output by the converter */

static BOOL gbTextPrint = TRUE;   /* Display of text */


/* Peform 2D anime stage text display */
static void TextPrint(void)
{
  /* Change position of display of characters */
  if (gbTextPrint) {
    nuDebConClear(NU_DEB_CON_WINDOW0);
    nuDebConTextPos(NU_DEB_CON_WINDOW0,13,5);
    nuDebConCPuts(NU_DEB_CON_WINDOW0, "2D ANIME VIEW");
  } else {
    nuDebConClear(NU_DEB_CON_WINDOW0);
    nuDebConTextPos(NU_DEB_CON_WINDOW0,0,0);	
    nuDebConCPuts(NU_DEB_CON_WINDOW0, "_");
  }
}


/* Initialize 2D anime stage */
void initStage00(void)
{
  /* Anime Controler Initialize */
  AnmConstruct(&gAnime, gAnimeCmd);
}

  
/* Make display list and start task */
void makeDL00(void)
{
  /* Display list buffer settings */
  glistp = &gfx_glist[gfx_gtask_no][0];

  /*  Initialize RCP */
  gfxRCPInit();

  /* Clear frame buffer and Z buffer */
  gfxClearCfb();

  /* Clear frame buffer and Z buffer */
  AnmViewerMain(&gAnime, &glistp);

  gDPFullSync(glistp++);
  gSPEndDisplayList(glistp++);
  assert((glistp - gfx_glist[gfx_gtask_no]) < GFX_GLIST_LEN);

  /* Start task, swap display buffer */
  nuGfxTaskStart(&gfx_glist[gfx_gtask_no][0],
		 (s32)(glistp - gfx_glist[gfx_gtask_no]) * sizeof (Gfx),
		 NU_GFX_UCODE_F3DEX , NU_SC_NOSWAPBUFFER);

  /* Display title, etc. */
  TextPrint();

  /* Swap buffer */
  nuDebConDisp(NU_SC_SWAPBUFFER);

  /* Swap display list buffer */
  gfx_gtask_no ^= 1;
}

static void Stick(NUContData* pCont)
{
  nuContDataGetEx(pCont,0);

  /* Turn text display ON/OFF with Z BUTTON */
  if(pCont->trigger & Z_TRIG) {
    gbTextPrint = (gbTextPrint) ? 0 : 1;
  }
  /* Move to Stage 1 after pressing Start button */
  if(pCont->trigger & (L_TRIG | R_TRIG)) {
    /* Remove callback function */
    nuGfxFuncRemove();
    /* Indicate next stage to Main */
    gStage = 1;
  }
}


/* Advance game process for Stage 0 */
void updateGame00(void)
{  
  /* Read Controller 1 data */
  Stick(gContdata);

  /* Change display position according to stick data */
  AnmSetViewPosition(&gAnime, gContdata->stick_x, gContdata->stick_y);
}

