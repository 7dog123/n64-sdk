/*
 * [CCBL]
 *
 * window_out.h
 *
 * Copyright (C) 1998, NINTENDO Co,Ltd.
 * Copyright (C) 1998, MONEGI CORPORATION.
 *
 */
#ifndef _MENU_PUT_H_
#define _MENU_PUT_H_


extern void window_disp_init(int x,int y,int w,int h);
extern void window_disp_cls(void);
extern Gfx *window_disp(Gfx *gp);
extern void window_disp_put(u8 val);

#endif /* !_MENU_PUT_H_ */
