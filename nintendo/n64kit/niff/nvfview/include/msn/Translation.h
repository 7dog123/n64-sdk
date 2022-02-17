/*
  msn/Translation.h
    Copyright (C) 1999, NINTENDO Co,Ltd., MONEGI CORPORATION.
    Mar. 18, 1999.
*/

#ifndef _msn_Translation_h
#define _msn_Translation_h 1

#include "mhc/Node.h"
#include "mhc/NodeHandle.h"
#include "mhc/Translation.h"
#include "mif/ChunkParser.h"
#include "mso/derive.h"
#include "mvm/Vector.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <ultra64.h>

/* Declare constant macro */
#define MSN_TRANSLATION_FIELD_TRANSLATION	(0)
#define MSN_TRANSLATION_FIELD_GLOBAL_POSITION	(1)

/* Declare types of a structure */
typedef MhcTranslation MsnTranslation;

/* Declare Functions */
extern void msnTranslationInit( MsnTranslation *translation_ptr );

/* Declare global variables */
extern MifChunkParser gMsnTranslationChunkParser;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _msn_Translation_h */
