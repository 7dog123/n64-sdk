/*======================================================================*/
/*		NuSYS							*/
/*		nudebconsole_ex2.c					*/
/*									*/
/*		Copyright (C) 1997, NINTENDO Co,Ltd.			*/
/*									*/
/*----------------------------------------------------------------------*/    
/* Ver 1.2	97/07/6		Modify  by Kensaku Ohki(SLANP)		*/
/*======================================================================*/
/* $Id: nudebconbuf.c,v 1.1 1998/07/07 12:37:24 ohki Exp $		*/
/*======================================================================*/
#include <nusys.h>
/* Initial setting of console window structure */
NUDebConWindow	nuDebConWin[NU_DEB_CON_WINDOW_NUM] = {

    {TRUE, 0, TRUE, 7, 0, 0, 0, 0, 0, 0, NU_DEB_CON_ROW_MAX, NU_DEB_CON_COLUMN_MAX,},
    {TRUE, 0, TRUE, 7, 0, 0, 0, 0, 0, 0, NU_DEB_CON_ROW_MAX, NU_DEB_CON_COLUMN_MAX,},
    {TRUE, 0, TRUE, 7, 0, 0, 0, 0, 0, 0, NU_DEB_CON_ROW_MAX, NU_DEB_CON_COLUMN_MAX,},
    {TRUE, 0, TRUE, 7, 0, 0, 0, 0, 0, 0, NU_DEB_CON_ROW_MAX, NU_DEB_CON_COLUMN_MAX,},
};

