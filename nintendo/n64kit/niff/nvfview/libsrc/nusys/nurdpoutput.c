/*======================================================================*/
/*		NuSYS										*/
/*		nurdpoutput.c								*/
/*												*/
/*		Copyright (C) 1997, NINTENDO Co,Ltd.				*/
/*												*/
/*----------------------------------------------------------------------*/    
/* Ver 1.0	97/10/9		Created by Kensaku Ohki(SLANP)		*/
/*======================================================================*/
#include <nusys.h>

/*----------------------------------------------------------------------*/
/* The RSP fifo buffer 									*/
/* It is set as the separate object for making the 16-byte boundary sort*/
/*----------------------------------------------------------------------*/
u8 nuRDPOutputBuf[NU_GFX_RDP_OUTPUTBUFF_SIZE];

