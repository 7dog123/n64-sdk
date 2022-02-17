/*
 * [CCBL]
 *
 * pad.h
 *
 * Copyright (C) 1998, NINTENDO Co,Ltd.
 * Copyright (C) 1998, MONEGI CORPORATION.
 *
 */
#ifndef _PAD_H_
#define _PAD_H_
#ifdef _LANGUAGE_C_PLUS_PLUS
extern "C" {
  //dummy KAKKO }
#endif
#include <PR/os.h>

typedef struct { 
  int pad_stat;
  u16 button;
  u16 trigger;
  u16 repeat;			/* Up, Down, Left, Right only */
  u8 rptc[8];
  s8 x_3D;
  s8 y_3D;
} Pad_D;

/* .pad_stat define*/
#define NO_PAD -1
#define OK_PAD 0
#define INVALID_PAD 1

/* pad button name redefine*/
#define PAD_A CONT_A
#define PAD_B CONT_B
#define PAD_LT CONT_L
#define PAD_RT CONT_R
#define PAD_ZT CONT_G
#define PAD_ST CONT_START
#define PAD_U CONT_UP
#define PAD_L CONT_LEFT
#define PAD_R CONT_RIGHT
#define PAD_D CONT_DOWN
#define PAD_CU CONT_E
#define PAD_CL CONT_C
#define PAD_CR CONT_F
#define PAD_CD CONT_D
#define PAD_CROSS (PAD_U|PAD_D|PAD_R|PAD_L)
#define PAD_CUNIT (PAD_CU|PAD_CD|PAD_CR|PAD_CL)
#define PAD_AB (PAD_A|PAD_B)
#define PAD_LTRT (PAD_LT|PAD_RT)

/* controller no */
#define JOY_1 0
#define JOY_2 1
#define JOY_3 2
#define JOY_4 3

/* prototypes */
extern void init_pad(void );
extern void get_pad(void );

/* variable externs */
extern Pad_D Mpad[];

#ifdef _LANGUAGE_C_PLUS_PLUS
}
#endif

#endif /* !_PAD_H_ */

