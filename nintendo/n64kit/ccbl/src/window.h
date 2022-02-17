/*
 * [CCBL]
 *
 * window.h
 *
 * Copyright (C) 1998, NINTENDO Co,Ltd.
 * Copyright (C) 1998, MONEGI CORPORATION.
 *
 */
#ifndef _WINDOW_H_
#define _WINDOW_H_

#define BASE_CW_WIN_W 36
#define BASE_CW_WIN_H 26

#ifndef NULL
#define NULL 0
#endif

#define CW_ROOT_WINDOW 0

typedef struct CW_WIDGET_s{
  int widget_no;
} CW_WIDGET;

typedef int CW_ID;
typedef char *String;
typedef void (*cwDispfunc)(CW_ID wid);
typedef void (*cwEventfunc)(CW_ID wid);
typedef void (*cwDeletefunc)(CW_ID wid);

typedef struct CW_WINGEO_s {
  int x,y,w,h;
} CW_WINGEO;

typedef struct CW_WINDOW_s {
  CW_ID wid;			/* Window ID */
  int stat;
  cwEventfunc event;
  cwDispfunc disp;		/* Display function */
  cwDeletefunc del;
  CW_WINGEO geo;
  unsigned long atr;			/* Window attributes */
  struct CW_WINDOW_s *prvwin;	/* Previous window */
  struct CW_WINDOW_s *nxtwin;	/* Next window  */
} CW_WINDOW;

enum cw_state {
  CW_ST_LIVE = 0,
  CW_ST_IDLE,
  CW_ST_DEATH
};

#define CW_ATTR_MODELESS 0
#define CW_ATTR_MODAL 1

/* ---- */
extern void cwInitWindowSystem(void );

extern int cwCreateWindow(void );
extern int cwDeleteWindow(CW_ID wid);
extern CW_WINDOW *cwSearchWindowID(CW_ID wid);

extern int cwSetEventFunc(CW_ID wid,cwEventfunc evt);
extern int cwSetDispFunc(CW_ID wid,cwDispfunc dpf);
extern int cwSetDeleteFunc(CW_ID wid,cwDeletefunc dlt);

extern int cwSetGeometry(CW_ID wid,int x,int y,int w,int h);
extern int cwSetAttr(CW_ID wid,unsigned long atr);

extern void cwWindowMain(void );
extern void cwFlushWindow(void);

extern void cwPutBuffer(CW_ID wid,String str,int x,int y);
extern void cwPutWindowFrame(CW_ID wid,int type,String str);
extern void cwPutCursorMB(CW_ID wid,int ypos,int type);
extern void cwPutCursorLabel(CW_ID wid,int xpos,int ypos,int llen,int type);
extern void cwPutSeparater(CW_ID wid,int x,int y,int w,int type);
#endif /* !_WINDOW_H_ */

