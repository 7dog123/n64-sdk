/*======================================================================*/
/*		NuSYS							*/
/*		nudebtaskperfbar1_ex2.c					*/
/*									*/
/*		Copyright (C) 1997, NINTENDO Co,Ltd.			*/
/*									*/
/*----------------------------------------------------------------------*/    
/* Ver 1.2	98/07/06	Created by Kensaku Ohki(SLANP)		*/
/*======================================================================*/
/* $Id: nudebtaskperfbar1_ex2.c,v 1.2 1998/07/12 12:17:39 ohki Exp $	*/
/*======================================================================*/
#define	F3DEX_GBI_2
#include "nusys.h"
#include "nux.h"

#define	VFRAME		280
#define	BAR_WIDTH	2

#define X0		1
#define Y0		2

#define X1		(X0+VFRAME*1)
#define X2		(X0+VFRAME*2)
#define X3		(X0+VFRAME*3)
#define X4		(X0+VFRAME*4)
#define X5		(X0+VFRAME*5)
#define X6		(X0+VFRAME*6)
#define X7		(X0+VFRAME*7)

#define BAR_BETWEEN	BAR_WIDTH+1
#define Y1		(Y0+BAR_BETWEEN)
#define	Y2		(Y1+BAR_BETWEEN)
#define	Y3		(Y2+BAR_BETWEEN)
#define	Y4		(Y3+BAR_BETWEEN)
#define	Y5		(Y4+BAR_BETWEEN)
#define	Y6		(Y5+BAR_BETWEEN)

#define	FRAME_X0	(X0-1)
#define	FRAME_X1	(X7+1)
#define	FRAME_Y0	(Y0-2)
#define	FRAME_Y1	(Y6+1)
#define	FRAME_Y2	(Y0-1)


static const u32 DEPTH_TABLE[] =
{
    G_IM_SIZ_16b,	/*  0:NTSC_LPN1 */
    G_IM_SIZ_16b,	/*  1:NTSC_LPF1 */
    G_IM_SIZ_16b,	/*  2:NTSC_LAN1 */
    G_IM_SIZ_16b,	/*  3:NTSC_LAF1 */
    G_IM_SIZ_32b,	/*  4:NTSC_LPN2 */
    G_IM_SIZ_32b,	/*  5:NTSC_LPF1 */
    G_IM_SIZ_32b,	/*  6:NTSC_LAN2 */
    G_IM_SIZ_32b,	/*  7:NTSC_LAF2 */
    G_IM_SIZ_16b,	/*  8:NTSC_HPN1 */
    G_IM_SIZ_16b,	/*  9:NTSC_HPF1 */
    G_IM_SIZ_16b,	/* 10:NTSC_HAN1 */
    G_IM_SIZ_16b,	/* 11:NTSC_HAF1 */
    G_IM_SIZ_32b,	/* 12:NTSC_HPN2 */
    G_IM_SIZ_32b	/* 13:NTSC_HPF2 */
};

/* The vertex list for the performance bar frame. */
static Vtx perfFrameVtx[] = {
    { FRAME_X0, FRAME_Y0,   0,   0,   0,   0, 0xff, 0xff, 0xff, 0x80},
    { FRAME_X1, FRAME_Y0,   0,   0,   0,   0, 0xff, 0xff, 0xff, 0x80},
    { FRAME_X1, FRAME_Y1,   0,   0,   0,   0, 0xff, 0xff, 0xff, 0x80},
    { FRAME_X0, FRAME_Y1,   0,   0,   0,   0, 0xff, 0xff, 0xff, 0x80},
    
    {   X0, FRAME_Y2,   0,   0,   0,   0, 0x00, 0x00, 0x40, 0x80},
    {   X1, FRAME_Y2,   0,   0,   0,   0, 0x00, 0x00, 0x40, 0x80},
    {   X1,       Y6,   0,   0,   0,   0, 0x00, 0x00, 0x40, 0x80},
    {   X0,       Y6,   0,   0,   0,   0, 0x00, 0x00, 0x40, 0x80},
    
    {   X1, FRAME_Y2,   0,   0,   0,   0, 0x00, 0x00, 0x00, 0xc0},
    {   X2, FRAME_Y2,   0,   0,   0,   0, 0x00, 0x00, 0x00, 0xc0},
    {   X2,       Y6,   0,   0,   0,   0, 0x00, 0x00, 0x00, 0xc0},
    {   X1,       Y6,   0,   0,   0,   0, 0x00, 0x00, 0x00, 0xc0},
    
    {   X2, FRAME_Y2,   0,   0,   0,   0, 0x00, 0x00, 0x00, 0x80},
    {   X3, FRAME_Y2,   0,   0,   0,   0, 0x00, 0x00, 0x00, 0x80},
    {   X3,       Y6,   0,   0,   0,   0, 0x00, 0x00, 0x00, 0x80},
    {   X2,       Y6,   0,   0,   0,   0, 0x00, 0x00, 0x00, 0x80},
    
    {   X3, FRAME_Y2,   0,   0,   0,   0, 0x00, 0x00, 0x00, 0xc0},
    {   X4, FRAME_Y2,   0,   0,   0,   0, 0x00, 0x00, 0x00, 0xc0},
    {   X4,       Y6,   0,   0,   0,   0, 0x00, 0x00, 0x00, 0xc0},
    {   X3,       Y6,   0,   0,   0,   0, 0x00, 0x00, 0x00, 0xc0},
    
    {   X4, FRAME_Y2,   0,   0,   0,   0, 0x00, 0x00, 0x00, 0x80},
    {   X5, FRAME_Y2,   0,   0,   0,   0, 0x00, 0x00, 0x00, 0x80},
    {   X5,       Y6,   0,   0,   0,   0, 0x00, 0x00, 0x00, 0x80},
    {   X4,       Y6,   0,   0,   0,   0, 0x00, 0x00, 0x00, 0x80},
    
    {   X5, FRAME_Y2,   0,   0,   0,   0, 0x00, 0x00, 0x00, 0xc0},
    {   X6, FRAME_Y2,   0,   0,   0,   0, 0x00, 0x00, 0x00, 0xc0},
    {   X6,       Y6,   0,   0,   0,   0, 0x00, 0x00, 0x00, 0xc0},
    {   X5,       Y6,   0,   0,   0,   0, 0x00, 0x00, 0x00, 0xc0},
    
    {   X6, FRAME_Y2,   0,   0,   0,   0, 0x00, 0x00, 0x00, 0x80},
    {   X7, FRAME_Y2,   0,   0,   0,   0, 0x00, 0x00, 0x00, 0x80},
    {   X7,       Y6,   0,   0,   0,   0, 0x00, 0x00, 0x00, 0x80},
    {   X6,       Y6,   0,   0,   0,   0, 0x00, 0x00, 0x00, 0x80},
};

/* The vertex list for the audio task bar. */
static Vtx auTaskVtx[] = {
    { 0, Y5+BAR_WIDTH,  -1,   0,   0,   0, 0xff, 0xff, 0xff, 0xff},
    { 0, Y5+BAR_WIDTH,  -1,   0,   0,   0, 0xff, 0x00, 0xff, 0xff},
    { 0, Y5          ,  -1,   0,   0,   0, 0xff, 0x00, 0xff, 0xff},
    { 0, Y5          ,  -1,   0,   0,   0, 0xff, 0xff, 0xff, 0xff},
    { 0, Y5+BAR_WIDTH,  -1,   0,   0,   0, 0xff, 0xff, 0xff, 0xff},
    { 0, Y5+BAR_WIDTH,  -1,   0,   0,   0, 0xff, 0x00, 0xff, 0xff},
    { 0, Y5          ,  -1,   0,   0,   0, 0xff, 0x00, 0xff, 0xff},
    { 0, Y5          ,  -1,   0,   0,   0, 0xff, 0xff, 0xff, 0xff},
    { 0, Y5+BAR_WIDTH,  -1,   0,   0,   0, 0xff, 0xff, 0xff, 0xff},
    { 0, Y5+BAR_WIDTH,  -1,   0,   0,   0, 0xff, 0x00, 0xff, 0xff},
    { 0, Y5          ,  -1,   0,   0,   0, 0xff, 0x00, 0xff, 0xff},
    { 0, Y5          ,  -1,   0,   0,   0, 0xff, 0xff, 0xff, 0xff},
    { 0, Y5+BAR_WIDTH,  -1,   0,   0,   0, 0xff, 0xff, 0xff, 0xff},
    { 0, Y5+BAR_WIDTH,  -1,   0,   0,   0, 0xff, 0x00, 0xff, 0xff},
    { 0, Y5          ,  -1,   0,   0,   0, 0xff, 0x00, 0xff, 0xff},
    { 0, Y5          ,  -1,   0,   0,   0, 0xff, 0xff, 0xff, 0xff},
};

/* The vertex list for the graphic RSP task bar. */
static Vtx gfxRspTaskVtx[] = {
    {    0, Y4+BAR_WIDTH,   0,   0,   0,   0, 0xff, 0xff, 0x00, 0xff},
    {    0, Y4+BAR_WIDTH,   0,   0,   0,   0, 0xff, 0x00, 0x00, 0xff},
    {    0, Y4          ,   0,   0,   0,   0, 0xff, 0x00, 0x00, 0xff},
    {    0, Y4          ,   0,   0,   0,   0, 0xff, 0xff, 0x00, 0xff},
    {    0, Y4+BAR_WIDTH,   0,   0,   0,   0, 0xff, 0xff, 0x00, 0xff},
    {    0, Y4+BAR_WIDTH,   0,   0,   0,   0, 0xff, 0x00, 0x00, 0xff},
    {    0, Y4          ,   0,   0,   0,   0, 0xff, 0x00, 0x00, 0xff},
    {    0, Y4          ,   0,   0,   0,   0, 0xff, 0xff, 0x00, 0xff},
    {    0, Y4+BAR_WIDTH,   0,   0,   0,   0, 0xff, 0xff, 0x00, 0xff},
    {    0, Y4+BAR_WIDTH,   0,   0,   0,   0, 0xff, 0x00, 0x00, 0xff},
    {    0, Y4          ,   0,   0,   0,   0, 0xff, 0x00, 0x00, 0xff},
    {    0, Y4          ,   0,   0,   0,   0, 0xff, 0xff, 0x00, 0xff},
    {    0, Y4+BAR_WIDTH,   0,   0,   0,   0, 0xff, 0xff, 0x00, 0xff},
    {    0, Y4+BAR_WIDTH,   0,   0,   0,   0, 0xff, 0x00, 0x00, 0xff},
    {    0, Y4          ,   0,   0,   0,   0, 0xff, 0x00, 0x00, 0xff},
    {    0, Y4          ,   0,   0,   0,   0, 0xff, 0xff, 0x00, 0xff},
    {    0, Y4+BAR_WIDTH,   0,   0,   0,   0, 0xff, 0xff, 0x00, 0xff},
    {    0, Y4+BAR_WIDTH,   0,   0,   0,   0, 0xff, 0x00, 0x00, 0xff},
    {    0, Y4          ,   0,   0,   0,   0, 0xff, 0x00, 0x00, 0xff},
    {    0, Y4          ,   0,   0,   0,   0, 0xff, 0xff, 0x00, 0xff},
    {    0, Y4+BAR_WIDTH,   0,   0,   0,   0, 0xff, 0xff, 0x00, 0xff},
    {    0, Y4+BAR_WIDTH,   0,   0,   0,   0, 0xff, 0x00, 0x00, 0xff},
    {    0, Y4          ,   0,   0,   0,   0, 0xff, 0x00, 0x00, 0xff},
    {    0, Y4          ,   0,   0,   0,   0, 0xff, 0xff, 0x00, 0xff},
    {    0, Y4+BAR_WIDTH,   0,   0,   0,   0, 0xff, 0xff, 0x00, 0xff},
    {    0, Y4+BAR_WIDTH,   0,   0,   0,   0, 0xff, 0x00, 0x00, 0xff},
    {    0, Y4          ,   0,   0,   0,   0, 0xff, 0x00, 0x00, 0xff},
    {    0, Y4          ,   0,   0,   0,   0, 0xff, 0xff, 0x00, 0xff},
    {    0, Y4+BAR_WIDTH,   0,   0,   0,   0, 0xff, 0xff, 0x00, 0xff},
    {    0, Y4+BAR_WIDTH,   0,   0,   0,   0, 0xff, 0x00, 0x00, 0xff},
    {    0, Y4          ,   0,   0,   0,   0, 0xff, 0x00, 0x00, 0xff},
    {    0, Y4          ,   0,   0,   0,   0, 0xff, 0xff, 0x00, 0xff},

};

/* The vertex list for the graphic RDP task bar. */
static Vtx gfxRdpTaskVtx[] = {
    {    0, Y3+BAR_WIDTH,   0,   0,   0,   0, 0x00, 0xff, 0x00, 0xff},
    {    0, Y3+BAR_WIDTH,   0,   0,   0,   0, 0xff, 0xff, 0xff, 0xff},
    {    0, Y3          ,   0,   0,   0,   0, 0xff, 0xff, 0xff, 0xff},
    {    0, Y3          ,   0,   0,   0,   0, 0x00, 0xff, 0x00, 0xff},
    {    0, Y3+BAR_WIDTH,   0,   0,   0,   0, 0x00, 0xff, 0x00, 0xff},
    {    0, Y3+BAR_WIDTH,   0,   0,   0,   0, 0xff, 0xff, 0xff, 0xff},
    {    0, Y3          ,   0,   0,   0,   0, 0xff, 0xff, 0xff, 0xff},
    {    0, Y3          ,   0,   0,   0,   0, 0x00, 0xff, 0x00, 0xff},
    {    0, Y3+BAR_WIDTH,   0,   0,   0,   0, 0x00, 0xff, 0x00, 0xff},
    {    0, Y3+BAR_WIDTH,   0,   0,   0,   0, 0xff, 0xff, 0xff, 0xff},
    {    0, Y3          ,   0,   0,   0,   0, 0xff, 0xff, 0xff, 0xff},
    {    0, Y3          ,   0,   0,   0,   0, 0x00, 0xff, 0x00, 0xff},
    {    0, Y3+BAR_WIDTH,   0,   0,   0,   0, 0x00, 0xff, 0x00, 0xff},
    {    0, Y3+BAR_WIDTH,   0,   0,   0,   0, 0xff, 0xff, 0xff, 0xff},
    {    0, Y3          ,   0,   0,   0,   0, 0xff, 0xff, 0xff, 0xff},
    {    0, Y3          ,   0,   0,   0,   0, 0x00, 0xff, 0x00, 0xff},
    {    0, Y3+BAR_WIDTH,   0,   0,   0,   0, 0x00, 0xff, 0x00, 0xff},
    {    0, Y3+BAR_WIDTH,   0,   0,   0,   0, 0xff, 0xff, 0xff, 0xff},
    {    0, Y3          ,   0,   0,   0,   0, 0xff, 0xff, 0xff, 0xff},
    {    0, Y3          ,   0,   0,   0,   0, 0x00, 0xff, 0x00, 0xff},
    {    0, Y3+BAR_WIDTH,   0,   0,   0,   0, 0x00, 0xff, 0x00, 0xff},
    {    0, Y3+BAR_WIDTH,   0,   0,   0,   0, 0xff, 0xff, 0xff, 0xff},
    {    0, Y3          ,   0,   0,   0,   0, 0xff, 0xff, 0xff, 0xff},
    {    0, Y3          ,   0,   0,   0,   0, 0x00, 0xff, 0x00, 0xff},
    {    0, Y3+BAR_WIDTH,   0,   0,   0,   0, 0x00, 0xff, 0x00, 0xff},
    {    0, Y3+BAR_WIDTH,   0,   0,   0,   0, 0xff, 0xff, 0xff, 0xff},
    {    0, Y3          ,   0,   0,   0,   0, 0xff, 0xff, 0xff, 0xff},
    {    0, Y3          ,   0,   0,   0,   0, 0x00, 0xff, 0x00, 0xff},
    {    0, Y3+BAR_WIDTH,   0,   0,   0,   0, 0x00, 0xff, 0x00, 0xff},
    {    0, Y3+BAR_WIDTH,   0,   0,   0,   0, 0xff, 0xff, 0xff, 0xff},
    {    0, Y3          ,   0,   0,   0,   0, 0xff, 0xff, 0xff, 0xff},
    {    0, Y3          ,   0,   0,   0,   0, 0x00, 0xff, 0x00, 0xff},
};
static Vtx gfxRdpCmdVtx[] = {
    {    0, Y2+BAR_WIDTH,   0,   0,   0,   0, 0x00, 0x00, 0xff, 0xff},
    {    0, Y2+BAR_WIDTH,   0,   0,   0,   0, 0xff, 0x00, 0x00, 0xff},
    {    0, Y2          ,   0,   0,   0,   0, 0xff, 0x00, 0x00, 0xff},
    {    0, Y2          ,   0,   0,   0,   0, 0x00, 0x00, 0xff, 0xff},
    {    0, Y2+BAR_WIDTH,   0,   0,   0,   0, 0x00, 0x00, 0xff, 0xff},
    {    0, Y2+BAR_WIDTH,   0,   0,   0,   0, 0xff, 0x00, 0x00, 0xff},
    {    0, Y2          ,   0,   0,   0,   0, 0xff, 0x00, 0x00, 0xff},
    {    0, Y2          ,   0,   0,   0,   0, 0x00, 0x00, 0xff, 0xff},
    {    0, Y2+BAR_WIDTH,   0,   0,   0,   0, 0x00, 0x00, 0xff, 0xff},
    {    0, Y2+BAR_WIDTH,   0,   0,   0,   0, 0xff, 0x00, 0x00, 0xff},
    {    0, Y2          ,   0,   0,   0,   0, 0xff, 0x00, 0x00, 0xff},
    {    0, Y2          ,   0,   0,   0,   0, 0x00, 0x00, 0xff, 0xff},
    {    0, Y2+BAR_WIDTH,   0,   0,   0,   0, 0x00, 0x00, 0xff, 0xff},
    {    0, Y2+BAR_WIDTH,   0,   0,   0,   0, 0xff, 0x00, 0x00, 0xff},
    {    0, Y2          ,   0,   0,   0,   0, 0xff, 0x00, 0x00, 0xff},
    {    0, Y2          ,   0,   0,   0,   0, 0x00, 0x00, 0xff, 0xff},
    {    0, Y2+BAR_WIDTH,   0,   0,   0,   0, 0x00, 0x00, 0xff, 0xff},
    {    0, Y2+BAR_WIDTH,   0,   0,   0,   0, 0xff, 0x00, 0x00, 0xff},
    {    0, Y2          ,   0,   0,   0,   0, 0xff, 0x00, 0x00, 0xff},
    {    0, Y2          ,   0,   0,   0,   0, 0x00, 0x00, 0xff, 0xff},
    {    0, Y2+BAR_WIDTH,   0,   0,   0,   0, 0x00, 0x00, 0xff, 0xff},
    {    0, Y2+BAR_WIDTH,   0,   0,   0,   0, 0xff, 0x00, 0x00, 0xff},
    {    0, Y2          ,   0,   0,   0,   0, 0xff, 0x00, 0x00, 0xff},
    {    0, Y2          ,   0,   0,   0,   0, 0x00, 0x00, 0xff, 0xff},
    {    0, Y2+BAR_WIDTH,   0,   0,   0,   0, 0x00, 0x00, 0xff, 0xff},
    {    0, Y2+BAR_WIDTH,   0,   0,   0,   0, 0xff, 0x00, 0x00, 0xff},
    {    0, Y2          ,   0,   0,   0,   0, 0xff, 0x00, 0x00, 0xff},
    {    0, Y2          ,   0,   0,   0,   0, 0x00, 0x00, 0xff, 0xff},
    {    0, Y2+BAR_WIDTH,   0,   0,   0,   0, 0x00, 0x00, 0xff, 0xff},
    {    0, Y2+BAR_WIDTH,   0,   0,   0,   0, 0xff, 0x00, 0x00, 0xff},
    {    0, Y2          ,   0,   0,   0,   0, 0xff, 0x00, 0x00, 0xff},
    {    0, Y2          ,   0,   0,   0,   0, 0x00, 0x00, 0xff, 0xff},
};
static Vtx gfxRdpPipeVtx[] = {
    {    0, Y1+BAR_WIDTH,   0,   0,   0,   0, 0x00, 0xff, 0xff, 0xff},
    {    0, Y1+BAR_WIDTH,   0,   0,   0,   0, 0xff, 0xff, 0x00, 0xff},
    {    0, Y1          ,   0,   0,   0,   0, 0xff, 0xff, 0x00, 0xff},
    {    0, Y1          ,   0,   0,   0,   0, 0x00, 0xff, 0xff, 0xff},
    {    0, Y1+BAR_WIDTH,   0,   0,   0,   0, 0x00, 0xff, 0xff, 0xff},
    {    0, Y1+BAR_WIDTH,   0,   0,   0,   0, 0xff, 0xff, 0x00, 0xff},
    {    0, Y1          ,   0,   0,   0,   0, 0xff, 0xff, 0x00, 0xff},
    {    0, Y1          ,   0,   0,   0,   0, 0x00, 0xff, 0xff, 0xff},
    {    0, Y1+BAR_WIDTH,   0,   0,   0,   0, 0x00, 0xff, 0xff, 0xff},
    {    0, Y1+BAR_WIDTH,   0,   0,   0,   0, 0xff, 0xff, 0x00, 0xff},
    {    0, Y1          ,   0,   0,   0,   0, 0xff, 0xff, 0x00, 0xff},
    {    0, Y1          ,   0,   0,   0,   0, 0x00, 0xff, 0xff, 0xff},
    {    0, Y1+BAR_WIDTH,   0,   0,   0,   0, 0x00, 0xff, 0xff, 0xff},
    {    0, Y1+BAR_WIDTH,   0,   0,   0,   0, 0xff, 0xff, 0x00, 0xff},
    {    0, Y1          ,   0,   0,   0,   0, 0xff, 0xff, 0x00, 0xff},
    {    0, Y1          ,   0,   0,   0,   0, 0x00, 0xff, 0xff, 0xff},
    {    0, Y1+BAR_WIDTH,   0,   0,   0,   0, 0x00, 0xff, 0xff, 0xff},
    {    0, Y1+BAR_WIDTH,   0,   0,   0,   0, 0xff, 0xff, 0x00, 0xff},
    {    0, Y1          ,   0,   0,   0,   0, 0xff, 0xff, 0x00, 0xff},
    {    0, Y1          ,   0,   0,   0,   0, 0x00, 0xff, 0xff, 0xff},
    {    0, Y1+BAR_WIDTH,   0,   0,   0,   0, 0x00, 0xff, 0xff, 0xff},
    {    0, Y1+BAR_WIDTH,   0,   0,   0,   0, 0xff, 0xff, 0x00, 0xff},
    {    0, Y1          ,   0,   0,   0,   0, 0xff, 0xff, 0x00, 0xff},
    {    0, Y1          ,   0,   0,   0,   0, 0x00, 0xff, 0xff, 0xff},
    {    0, Y1+BAR_WIDTH,   0,   0,   0,   0, 0x00, 0xff, 0xff, 0xff},
    {    0, Y1+BAR_WIDTH,   0,   0,   0,   0, 0xff, 0xff, 0x00, 0xff},
    {    0, Y1          ,   0,   0,   0,   0, 0xff, 0xff, 0x00, 0xff},
    {    0, Y1          ,   0,   0,   0,   0, 0x00, 0xff, 0xff, 0xff},
    {    0, Y1+BAR_WIDTH,   0,   0,   0,   0, 0x00, 0xff, 0xff, 0xff},
    {    0, Y1+BAR_WIDTH,   0,   0,   0,   0, 0xff, 0xff, 0x00, 0xff},
    {    0, Y1          ,   0,   0,   0,   0, 0xff, 0xff, 0x00, 0xff},
    {    0, Y1          ,   0,   0,   0,   0, 0x00, 0xff, 0xff, 0xff},
};
static Vtx gfxRdpTmemVtx[] = {
    {    0, Y0+BAR_WIDTH,   0,   0,   0,   0, 0x80, 0x00, 0xff, 0xff},
    {    0, Y0+BAR_WIDTH,   0,   0,   0,   0, 0x80, 0xff, 0x00, 0xff},
    {    0, Y0          ,   0,   0,   0,   0, 0x80, 0xff, 0x00, 0xff},
    {    0, Y0          ,   0,   0,   0,   0, 0x80, 0x00, 0xff, 0xff},
    {    0, Y0+BAR_WIDTH,   0,   0,   0,   0, 0x80, 0x00, 0xff, 0xff},
    {    0, Y0+BAR_WIDTH,   0,   0,   0,   0, 0x80, 0xff, 0x00, 0xff},
    {    0, Y0          ,   0,   0,   0,   0, 0x80, 0xff, 0x00, 0xff},
    {    0, Y0          ,   0,   0,   0,   0, 0x80, 0x00, 0xff, 0xff},
    {    0, Y0+BAR_WIDTH,   0,   0,   0,   0, 0x80, 0x00, 0xff, 0xff},
    {    0, Y0+BAR_WIDTH,   0,   0,   0,   0, 0x80, 0xff, 0x00, 0xff},
    {    0, Y0          ,   0,   0,   0,   0, 0x80, 0xff, 0x00, 0xff},
    {    0, Y0          ,   0,   0,   0,   0, 0x80, 0x00, 0xff, 0xff},
    {    0, Y0+BAR_WIDTH,   0,   0,   0,   0, 0x80, 0x00, 0xff, 0xff},
    {    0, Y0+BAR_WIDTH,   0,   0,   0,   0, 0x80, 0xff, 0x00, 0xff},
    {    0, Y0          ,   0,   0,   0,   0, 0x80, 0xff, 0x00, 0xff},
    {    0, Y0          ,   0,   0,   0,   0, 0x80, 0x00, 0xff, 0xff},
    {    0, Y0+BAR_WIDTH,   0,   0,   0,   0, 0x80, 0x00, 0xff, 0xff},
    {    0, Y0+BAR_WIDTH,   0,   0,   0,   0, 0x80, 0xff, 0x00, 0xff},
    {    0, Y0          ,   0,   0,   0,   0, 0x80, 0xff, 0x00, 0xff},
    {    0, Y0          ,   0,   0,   0,   0, 0x80, 0x00, 0xff, 0xff},
    {    0, Y0+BAR_WIDTH,   0,   0,   0,   0, 0x80, 0x00, 0xff, 0xff},
    {    0, Y0+BAR_WIDTH,   0,   0,   0,   0, 0x80, 0xff, 0x00, 0xff},
    {    0, Y0          ,   0,   0,   0,   0, 0x80, 0xff, 0x00, 0xff},
    {    0, Y0          ,   0,   0,   0,   0, 0x80, 0x00, 0xff, 0xff},
    {    0, Y0+BAR_WIDTH,   0,   0,   0,   0, 0x80, 0x00, 0xff, 0xff},
    {    0, Y0+BAR_WIDTH,   0,   0,   0,   0, 0x80, 0xff, 0x00, 0xff},
    {    0, Y0          ,   0,   0,   0,   0, 0x80, 0xff, 0x00, 0xff},
    {    0, Y0          ,   0,   0,   0,   0, 0x80, 0x00, 0xff, 0xff},
    {    0, Y0+BAR_WIDTH,   0,   0,   0,   0, 0x80, 0x00, 0xff, 0xff},
    {    0, Y0+BAR_WIDTH,   0,   0,   0,   0, 0x80, 0xff, 0x00, 0xff},
    {    0, Y0          ,   0,   0,   0,   0, 0x80, 0xff, 0x00, 0xff},
    {    0, Y0          ,   0,   0,   0,   0, 0x80, 0x00, 0xff, 0xff},
};
static Vp vp = {
    320*2, 240*2, G_MAXZ/2, 0,	/* scale */
    320*2, 240*2, G_MAXZ/2, 0,	/* translate */
};

static Gfx initRcpDl[] = {
    gsSPSegment(0x0, 0x0),
    gsDPSetScissor(G_SC_NON_INTERLACE, 0, 0, NU_GFX_INIT_SCREEN_WD * 2, NU_GFX_INIT_SCREEN_HT * 2),
    gsSPClearGeometryMode(0xffffffff),
    gsSPSetGeometryMode(G_SHADE | G_SHADING_SMOOTH),
    gsSPTexture(0, 0, 0, 0, G_OFF),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPPipelineMode(G_PM_NPRIMITIVE),
    gsDPSetColorDither(G_CD_BAYER),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsDPPipeSync(),
    gsSPEndDisplayList(),
};

/* Drawing the performance meter frame. */
static Gfx perfFrameDl[] = {
    gsSPVertex(&perfFrameVtx, 32, 0),
    gsSP2Triangles(0, 1, 2, 0, 2, 3, 0, 0),
    gsSPEndDisplayList(),
};


/* Scale values when the number of frames displayed in task bar is changed */
static float frameScale[] = { 1.0, 0.5, 0.3333, 0.25, 0.2, 0.16667};

static Mtx	perf_mtx;
static Mtx	view_mtx;
static Mtx	line_mtx;
static Mtx	scale_mtx;
static Mtx	move_mtx;
static Gfx	glistBuf[2][512];
static u32	glistCnt = 0;

/*----------------------------------------------------------------------*/
/*	Display the performance meter. 					*/
/*	IN:	glist_ptr	Display list buffer.			*/
/*		frameNum	Number of frames displayed (1-6).	*/
/*		y		Display position.			*/
/*	RET:	None							*/
/*----------------------------------------------------------------------*/
void nuxDebTaskPerfBar1EX2( NuxScPerf *perf_ptr, u32 frameNum, u32 y,
			    u32 flag )
{
    u32		cnt;
    s64		taskTime;
    short 	StartX;
    short	EndX;
    u32		vtxIdx;
    float	posY;
    Gfx*	glistPtr;
    u32		viMode;
    u32		scale;

    glistPtr = glistBuf[glistCnt];
    /* Get the current VI mode. */
    viMode = osViGetCurrentMode() % 14;
    if(viMode < 8){
	scale = 1;
    } else {
	y /=2;
	scale = 2;
    }

    vp.vp.vscale[0] = vp.vp.vtrans[0] = 320*2*scale;
    vp.vp.vscale[1] = vp.vp.vtrans[1] = 240*2*scale;
    gSPViewport(glistPtr++, &vp);

    /* Set the RSP and the RDP */
    gSPDisplayList(glistPtr++, OS_K0_TO_PHYSICAL(initRcpDl));
    gDPSetColorImage(glistPtr++, G_IM_FMT_RGBA, DEPTH_TABLE[ viMode ],
		     NU_DEB_CON_WIDTH * scale,
		     osVirtualToPhysical(nuGfxCfb_ptr));

    /* The coordinate origin is on the bottom-left, so convert */
    /* it from the upper-left */
    posY =(240.0 - FRAME_Y1) - y;
    if(posY == 0.0) posY = 0.1;

    /* As a precaution, limit the number of frames displayed. */
    if(frameNum > 5) frameNum = 5;

    guOrtho(&perf_mtx,
	    0.0F, (float)(NU_GFX_INIT_SCREEN_WD * scale),
	    0.0F, (float)(NU_GFX_INIT_SCREEN_HT * scale),
	    -1.0F, 10.0F, 1.0F);
    guLookAt(&view_mtx,
	     0.0, 0.0, 1.0,
	     0.0, 0.0, 0.0,
	     0.0, 1.0, 0.0);
    
    /* Change the scale in the X axis direction to change */
    /* the number of frames displayed  */
    guScale(&scale_mtx, frameScale[frameNum]*(float)scale, (float)scale, 1.0);

    /* Move the left-end position so it becomes the 20-dot position on the screen.*/
    guTranslate(&move_mtx, 20.0/frameScale[frameNum], posY, 0.0);
    gSPMatrix(glistPtr++, &perf_mtx, 
	    G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);
    gSPMatrix(glistPtr++, &view_mtx,
	      G_MTX_PROJECTION | G_MTX_MUL | G_MTX_NOPUSH);
    guMtxIdent(&line_mtx);
    gSPMatrix(glistPtr++, OS_K0_TO_PHYSICAL(&line_mtx),
	      G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
    gSPMatrix(glistPtr++, OS_K0_TO_PHYSICAL(&scale_mtx),
	      G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
    gSPMatrix(glistPtr++, OS_K0_TO_PHYSICAL(&move_mtx),
	      G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);

    

    /* Draw the outer frame of the performance bar display. */
    gSPDisplayList(glistPtr++, OS_K0_TO_PHYSICAL(perfFrameDl));
    perfFrameVtx[1].v.ob[0] = VFRAME * (frameNum + 1) + 2;
    perfFrameVtx[2].v.ob[0] = VFRAME * (frameNum + 1) + 2;

    /* Draw the inner frame for only the number of frames displayed. */
    for(cnt = 0; cnt < frameNum + 1; cnt++){
	vtxIdx = cnt * 4 + 4;
	gSP2Triangles(glistPtr++, vtxIdx+ 0, vtxIdx+1, vtxIdx+2, 0,
		      vtxIdx+2, vtxIdx+3, vtxIdx+0, 0);
    }

    gSPVertex(glistPtr++, auTaskVtx, 16, 0);
    StartX = X0;
    vtxIdx = glistCnt * 4;

    /* Display the audio task bar. */
    taskTime = ( perf_ptr->audio * VFRAME ) / 16666;
    auTaskVtx[vtxIdx+0].v.ob[0] = StartX;
    auTaskVtx[vtxIdx+1].v.ob[0] = StartX + taskTime;
    auTaskVtx[vtxIdx+2].v.ob[0] = StartX + taskTime;
    auTaskVtx[vtxIdx+3].v.ob[0] = StartX;
    gSP2Triangles( glistPtr++, vtxIdx+0, vtxIdx+2, vtxIdx+1, 0,
		   vtxIdx+0, vtxIdx+3, vtxIdx+2, 0 );

    /* Display the graphic RSP task bar. */
    gSPVertex(glistPtr++, gfxRspTaskVtx, 32, 0);
    taskTime = ( perf_ptr->rsp * VFRAME ) / 16666;
    gfxRspTaskVtx[vtxIdx+0].v.ob[0] = StartX;
    gfxRspTaskVtx[vtxIdx+1].v.ob[0] = StartX + taskTime;
    gfxRspTaskVtx[vtxIdx+2].v.ob[0] = StartX + taskTime;
    gfxRspTaskVtx[vtxIdx+3].v.ob[0] = StartX;
    gSP2Triangles( glistPtr++, vtxIdx+0, vtxIdx+2, vtxIdx+1, 0,
		   vtxIdx+0, vtxIdx+3, vtxIdx+2, 0 );

    /* Display the graphic RSP task bar. */
    gSPVertex(glistPtr++, gfxRdpTaskVtx, 32, 0);
    taskTime = ( perf_ptr->rdp * VFRAME ) / 16666;
    gfxRdpTaskVtx[vtxIdx+0].v.ob[0] = StartX;
    gfxRdpTaskVtx[vtxIdx+1].v.ob[0] = StartX + taskTime;
    gfxRdpTaskVtx[vtxIdx+2].v.ob[0] = StartX + taskTime;
    gfxRdpTaskVtx[vtxIdx+3].v.ob[0] = StartX;
    gSP2Triangles( glistPtr++, vtxIdx+0, vtxIdx+2, vtxIdx+1, 0,
		   vtxIdx+0, vtxIdx+3, vtxIdx+2, 0);

    /* RDP-CMD Conter	*/
    gSPVertex(glistPtr++, gfxRdpCmdVtx, 32, 0);
    taskTime = ( perf_ptr->command * VFRAME ) / 16666;
    gfxRdpCmdVtx[vtxIdx+0].v.ob[0] = StartX;
    gfxRdpCmdVtx[vtxIdx+1].v.ob[0] = StartX + taskTime;
    gfxRdpCmdVtx[vtxIdx+2].v.ob[0] = StartX + taskTime;
    gfxRdpCmdVtx[vtxIdx+3].v.ob[0] = StartX;
    gSP2Triangles( glistPtr++, vtxIdx+0, vtxIdx+2, vtxIdx+1, 0,
		   vtxIdx+0, vtxIdx+3, vtxIdx+2, 0 );
    
    /* RDP-PIPE Conter	*/
    gSPVertex(glistPtr++, gfxRdpPipeVtx, 32, 0);
    taskTime = ( perf_ptr->pipe * VFRAME ) / 16666;
    gfxRdpPipeVtx[vtxIdx+0].v.ob[0] = StartX;
    gfxRdpPipeVtx[vtxIdx+1].v.ob[0] = StartX + taskTime;
    gfxRdpPipeVtx[vtxIdx+2].v.ob[0] = StartX + taskTime;
    gfxRdpPipeVtx[vtxIdx+3].v.ob[0] = StartX;
    gSP2Triangles( glistPtr++, vtxIdx+0, vtxIdx+2, vtxIdx+1, 0,
		   vtxIdx+0, vtxIdx+3, vtxIdx+2, 0 );

    /* RDP-Tmem Conter	*/
    gSPVertex(glistPtr++, gfxRdpTmemVtx, 32, 0);
    taskTime = ( perf_ptr->tmem * VFRAME ) / 16666;
    gfxRdpTmemVtx[vtxIdx+0].v.ob[0] = StartX;
    gfxRdpTmemVtx[vtxIdx+1].v.ob[0] = StartX + taskTime;
    gfxRdpTmemVtx[vtxIdx+2].v.ob[0] = StartX + taskTime;
    gfxRdpTmemVtx[vtxIdx+3].v.ob[0] = StartX;
    gSP2Triangles( glistPtr++, vtxIdx+0, vtxIdx+2, vtxIdx+1, 0,
		   vtxIdx+0, vtxIdx+3, vtxIdx+2, 0 );

    gDPFullSync(glistPtr++);
    gSPEndDisplayList(glistPtr++);

#ifdef NU_DEBUG    
    if((u32)(glistPtr - glistBuf[glistCnt]) > 256){
	osSyncPrintf("nuDebTaskPerfBar0: gfx list buffer over.\n");
    }
#endif /* NU_DEBUG */
    
    /* Start graphic task */
    nuGfxTaskStart( glistBuf[glistCnt],
		    ( s32 )( glistPtr - glistBuf[ glistCnt ] ) * sizeof( Gfx ),
		    NU_GFX_UCODE_F3DEX, flag );
    glistCnt++;
    glistCnt &= 0x01;
}
