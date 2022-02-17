/*
  Copyright(C) 1998, NINTENDO Co., Ltd.
  Texture Editor Anime Viewer Converter
*/

#ifndef __ANMVIEWER_H__
#define __ANMVIEWER_H__

#include "anmdata.h"

/*
========================================================
=== Anime Controler Command
========================================================
*/

/* Anime Controler Command */
enum {
  ANMCTRL_NOP,            /* No operation  */
  ANMCTRL_SETMAXFRAME,    /* Set Max Frame */
  ANMCTRL_TEX_VIEW,       /* Texture View  */
  ANMCTRL_JUMP,           /* Goto Command  */
};


/* Anime Ctrl Header  */
typedef struct {
  u32 m_nCmd;
} CAnmCtrlHeader;

/* No operation */
typedef struct {
  CAnmCtrlHeader m_header;
} CAnmCtrlNop;

/* Anime Set Max Frame */
typedef struct {
  CAnmCtrlHeader m_header;
  u32 m_nMaxFrame;
} CAnmCtrlSetMaxFrame;

/* Anime Texture Data Command */
typedef struct {
  CAnmCtrlHeader m_header;
  struct teTMF*	 m_pTMF;
  u16* m_pTLF;
  u32  m_nPal;
  u32 m_nFrame;
} CAnmCtrlTxture;

/* Jump Command */
typedef struct {
  CAnmCtrlHeader m_header;
  u32 m_nNewPC;
} CAnmCtrlJump;

/*
========================================================
=== Anime Controler Method
========================================================
*/

typedef struct {
  u32 m_nXPos;                 /* Anime Display Position */
  u32 m_nYPos;                 /* */
  u32 m_nState;                /* state NORMAL / Now Tex Viewing */
  u32 m_nStateFrame;           /* state count down */
  u32 m_nMaxFrame;             /* max frame */
  u32 m_nNowFrame;             /* now frame */
  CAnmCtrlHeader** m_ppCtrl;   /* Anime Ctrl */
  u32 m_nCtrlPC;               /* Now Exec PC(for m_ppCtrl) */
} CAnime;


enum {
  ANMSTT_NORMAL    = 0,     /* Normal */
  ANMSTT_TXTVIEW,           /* Texture Viewing  */
};

/* Anime Control Public Mothod */
void AnmConstruct(CAnime* pSelf, CAnmCtrlHeader** ppCommand);
void AnmSetViewPosition(CAnime* pSelf, u32 nX, u32 nY);
void AnmViewerMain(CAnime* pSelf, Gfx** ppGFX);

#endif	__ANMVIEWER_H__

