/*======================================================================*/
/*		NuSYS							*/
/*		nupireadsram.c						*/
/*									*/
/*		Copyright (C) 1997, NINTENDO Co,Ltd.			*/
/*									*/
/*----------------------------------------------------------------------*/
/* Ver 1.2	98/07/11	Created by Kensaku Ohki(SLANP)		*/
/*----------------------------------------------------------------------*/
/* $Id: nupireadwritesram.c,v 1.1 1998/07/11 11:22:33 ohki Exp $		*/
/*======================================================================*/
#include <nusys.h>

/*----------------------------------------------------------------------*/
/*	nuPiReadWriteSram  - DMA transfers data to and from SRAM.		*/
/*	The message queue is a local variable so it can be used          */
/*     between threads.                                                 */
/*	IN:	addr	      SRAM address. 					*/
/*		buf_ptr	RDRAM address. 					*/
/*		size	      Transfer size. 					*/
/*	RET:	None							*/
/*----------------------------------------------------------------------*/
void nuPiReadWriteSram(u32 addr, void* buf_ptr, u32 size, s32 flag)
{
    OSIoMesg	dmaIoMesgBuf;
    OSMesgQueue dmaMesgQ;
    OSMesg	dmaMesgBuf;

    

    
#ifdef	USE_EPI
#ifdef NU_DEBUG
    if(addr & 0x00000001){
	osSyncPrintf("nuPiReadWriteSram: SRAM address is odd!!\n");
    }
    if((u32)buf_ptr & 0x07){
	osSyncPrintf("nuPiReadWriteSram: RDRAM address must align 8!!\n");
    }
    if(size & 0x00000001){
	osSyncPrintf("nuPiReadWriteSram: DMA size is odd!!\n");
    }
#endif /* NU_DEBUG */
    /* Create the message queue. */
    osCreateMesgQueue(&dmaMesgQ, &dmaMesgBuf, 1);

    dmaIoMesgBuf.hdr.pri      = OS_MESG_PRI_NORMAL;
    dmaIoMesgBuf.hdr.retQueue = &dmaMesgQ;
    dmaIoMesgBuf.dramAddr     = buf_ptr;
    dmaIoMesgBuf.devAddr      = (u32)addr;
    dmaIoMesgBuf.size         = size;

    /* Make CPU cache invalid. */
    osInvalDCache((void*)buf_ptr, (s32)size);
    
    osEPiStartDma(nuPiSramHandle, &dmaIoMesgBuf, flag);

    /* Wait for the end. */
    (void)osRecvMesg(&dmaMesgQ, &dmaMesgBuf, OS_MESG_BLOCK);
#endif /* USE_EPI */
}

