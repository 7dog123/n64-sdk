/*
  Copyright(C) 1998, NINTENDO Co., Ltd.
  Texture Editor Anime Viewer Converter
*/

#include <nusys.h>
#include "graphic.h"
#include "teapi.h"      /* USE Texture Editor Viewer API */
#include "anmview.h"

/*
========================================================
=== Anime Controler Command
========================================================
*/


/* Next Anime Command */
#define  AnmNextPC(pSelf)    pSelf->m_nCtrlPC++


/* No operation */
static u32 AnmCtrlNoOperation(CAnime* pSelf, CAnmCtrlHeader* pHeader)
{
  AnmNextPC(pSelf);
  return TRUE;
}

/* Set Max Frame */
static u32 AnmCtrlSetMaxFrame(CAnime* pSelf, CAnmCtrlHeader* pHeader)
{
  pSelf->m_nMaxFrame = ((CAnmCtrlSetMaxFrame*)pHeader)->m_nMaxFrame;
  AnmNextPC(pSelf);
  return FALSE;
}

/* Texture View */
static u32 AnmCtrlTexView(CAnime* pSelf, CAnmCtrlHeader* pHeader, Gfx** ppGFX)
{
  CAnmCtrlTxture* pTex = (CAnmCtrlTxture*)pHeader;
  struct teTMF* pTMF = pTex->m_pTMF;

  /* Initial Viewing Frame Counter */
  if (pSelf->m_nState != ANMSTT_TXTVIEW) {
    pSelf->m_nState      = ANMSTT_TXTVIEW;
    pSelf->m_nStateFrame = pTex->m_nFrame;
  }

  /* Display Texture(Call Texture Editor API) */
  *ppGFX = teDrawTexture(*ppGFX, 
             (s16)(pSelf->m_nXPos * 2),
             (s16)((-pSelf->m_nYPos) * 2),
             pTex->m_pTMF->fmt,
             pTex->m_pTMF->siz,
             pTex->m_pTMF->width,
             pTex->m_pTMF->height,
             (u32)pTex->m_pTLF,
			 pTex->m_nPal,
             (u32)pTex->m_pTMF->img
  );

  /* Frame Count down */
  pSelf->m_nStateFrame--;
  if (0 == pSelf->m_nStateFrame) {
    pSelf->m_nState = ANMSTT_NORMAL;
    AnmNextPC(pSelf);
  }
  return TRUE;
}


/* Jump Command(etc.. loop Exec Command) */
static u32 AnmCtrlJump(CAnime* pSelf, CAnmCtrlHeader* pHeader)
{
  pSelf->m_nCtrlPC = ((CAnmCtrlJump*)pHeader)->m_nNewPC;
  return FALSE;
}

/*
========================================================
=== Anime Controler Execute
========================================================
*/

static void AnmExecCmd(CAnime* pSelf, Gfx** ppGFX)
{
  u32 bContinue = FALSE;
  if (!pSelf) return;
  do {
    /* Anime Command */
    CAnmCtrlHeader* pCmd = pSelf->m_ppCtrl[ pSelf->m_nCtrlPC ];

    switch(pCmd->m_nCmd) {

      /* No operation */
      case ANMCTRL_NOP: {  
        bContinue = AnmCtrlNoOperation(pSelf, pCmd);
        break;
      }

      /* Set Max Frame */
      case ANMCTRL_SETMAXFRAME: {
        bContinue = AnmCtrlSetMaxFrame(pSelf, pCmd);
        break;
      }

      /* Texture View */
      case ANMCTRL_TEX_VIEW: {
        bContinue = AnmCtrlTexView(pSelf, pCmd, ppGFX);
        break;
      }

      /* Goto Command */
      case ANMCTRL_JUMP: {
        bContinue = AnmCtrlJump(pSelf, pCmd);
        break;
      }

      /* BugBug Program */
      default: {
#ifdef DEBUG
        osSyncPrintf("\nAnmExecCmd Unknown Cmd(%02x)", nCmd);
#endif
        while(1);
        break;
      }
    }
  }while(FALSE == bContinue);
}

/*
========================================================
=== Anime Controler Public Method
========================================================
*/

/* Construct Anime Controler */
void AnmConstruct(CAnime* pSelf, CAnmCtrlHeader** ppCommand)
{
#if 1
  int i = 0;
  for (i = 0; i < sizeof(CAnime); i++) ((u8*) pSelf)[i] = 0;
#else
  memset(pSelf, 0x00, sizeof(CAnime));
#endif
  pSelf->m_ppCtrl = ppCommand;
}


/* Execute Anime Controler Command */
void AnmViewerMain(CAnime* pSelf, Gfx** ppGFX)
{
  AnmExecCmd(pSelf, ppGFX);
}


/* Set Viewing Position */
void AnmSetViewPosition(CAnime* pSelf, u32 nX, u32 nY)
{
  pSelf->m_nXPos = nX;
  pSelf->m_nYPos = nY;
}

