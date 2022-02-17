
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
 * This header file is necessary in order to use the print debugging features of
 * IS-Viewer64.  Methods of print debugging are as follows.
 * 
 *
 * 1. Issue a isPrintInit(); call in the boot thread of the program to be debugged (after 
 *   each osInitialize(); call) to initialize the debugging feature.
 * 
 * 2. Using the same format as for the printf function, call the data to be debugged using 
 *   the isPrintf function.  In this library, both osSyncPrintf and rmonPrintf override
 *   functions so that isPrintf is called.  Consequently, this library cannot be linked
 *   with
 *   libultra_d.a and other libraries that include osSyncPrintf. 
 *   
 * 3. Include is_debug.h in source code that uses the debugging features. 
 *
 * 4. Make additions to the makefile so that is_debug.c is included in compiling
 *   and linking. 
 * 5. Use nload filename.  nload will automatically enter a debug print loop,
 *   allowing NUS print data to be displayed to the screen. 
 *   
 * 6. The default address used for debug printing is 0xb1ff0000.  If this address is 
 *   unsuitable, however, it can be changed.  For more information, see is_debug.c.
 *   
 * 
 *==================================================================== */

void isPrintfInit(OSPiHandle *pih);
void isPrintf(const char *fmt, ...);

#ifdef _LANGUAGE_C_PLUS_PLUS   /* for c++ */  
}
#endif

#endif


