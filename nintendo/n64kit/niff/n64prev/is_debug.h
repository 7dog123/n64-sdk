
#ifndef __IS_DEBUG_H__
#define __IS_DEBUG_H__

#ifdef _LANGUAGE_C_PLUS_PLUS   /* for c++ */
extern "C" {
#endif

/* ====================================================================
 * is_debug.h
 *
 * Copyright 1997, Intelligent Systems Co.,Ltd.
 * All Rights Reserved.
 *
 * This header is necessary to use the print debug function for IS-Viewer64.   
 * The procedure to perform print debug is as follows:
 * 
 *
 * 1. Call isPrintInit(); by boot thread of a program for which you want to 
 * debug (around the time after osInitialize(); is called), and initialize the 
 * debug function.  
 *
 * 2. Call the information you want to debug using isPrintf function in the same  
 * manner as printf function.  In this library, both osSyncPrintf and rmonPrintf  
 * override a function as calling isPrintf.  Therefore, you must not link with 
 * libraries that include osSyncPrintf such as libultra_d.a. 
 *
 * 3.A source that utilizes the debug funtion includes is_debug.h. 
 *
 * 4.Add is_debug.c in makefile so that it is compiled together.
 *
 * 5.Execute nload filename.  nload will enter the debug print loop 
 * automatically, and the print information of NUS side can be displayed on the 
 * screen.  
 *
 * 6.The default address that is used for debug print starts from 
 * 0xb1ff0000, however, if it is not convenient, this address can be changed. 
 * Refer to is_debug.c for details.  
 *==================================================================== */

void isPrintfInit(void);
void isPrintf(const char *fmt, ...);

#ifdef _LANGUAGE_C_PLUS_PLUS   /* for c++ */  
}
#endif

#endif

