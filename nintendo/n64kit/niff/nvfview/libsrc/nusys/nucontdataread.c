/*======================================================================*/
/*		NuSYS										*/
/*		nucontmgr.c									*/
/*												*/
/*		Copyright (C) 1997, NINTENDO Co,Ltd.				*/
/*												*/
/*----------------------------------------------------------------------*/    
/* Ver 1.0	97/10/9		Created by Kensaku Ohki(SLANP)		*/
/*======================================================================*/
/* $Id: nucontdataread.c,v 1.3 1997/12/06 08:35:19 ohki Exp $		*/
/*======================================================================*/
#include <nusys.h>

/*----------------------------------------------------------------------*/
/*	nuContDataRead - Read data of the controller 				*/
/*	Send the message of data reading to the controller manager and  	*/
/*	wait for the reading end.  Note that it may take about 2ms.  	*/
/*												*/
/*	IN:	*pad	The reading structure of controller data 			*/
/*	RET:	None 										*/
/*----------------------------------------------------------------------*/
void nuContDataRead(OSContPad* pad)
{
    
    OSMesgQueue		mesgQ;
    OSMesg		mesgBuf;
    NUContReadMesg	readMesg;
    

    if(nuContCallBack.func == NULL){
#ifdef NU_DEBUG    
	osSyncPrintf("nuContDataRead: no controller manager!!\n");
#endif /* NU_DEBUG */
	return;
    }

    
    readMesg.mesg	= NU_CONT_READ_MSG;	/* Read controller data */
    readMesg.rtnMesgQ	= &mesgQ;
    readMesg.pad	= pad;
	
    osCreateMesgQueue(&mesgQ, &mesgBuf, 1);
    osSendMesg(&nuSiMgrMesgQ, (OSMesg*)&readMesg, OS_MESG_BLOCK);
    osRecvMesg(&mesgQ, NULL, OS_MESG_BLOCK);    
}
