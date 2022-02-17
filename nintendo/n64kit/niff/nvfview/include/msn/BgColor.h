/*
  msn/BgColor.h
    Copyright (C) 1999, NINTENDO Co,Ltd., MONEGI CORPORATION.
    Jan. 28, 1999.
*/

#ifndef _msn_BgColor_h
#define _msn_BgColor_h 1

#include "mhc/Node.h"
#include "mhc/NodeHandle.h"
#include "mif/ChunkParser.h"
#include "mso/derive.h"
#include "mvm/Vector.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <ultra64.h>

/* Declare constant macros */
#define MSN_BG_COLOR_FIELD_COLOR	(0)

/* Declare structures */
typedef struct _MsnBgColor
{
    _msoDeriveFrom( MhcNode );
    MvmColor4f	color;
    short	depth;
} MsnBgColor;

/* Declare functions */
extern void msnBgColorInit( MsnBgColor *color_ptr );

/* Declare a global variable */
extern MifChunkParser gMsnBgColorChunkParser;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _msn_BgColor_h */
