/*
  msn/Switch.h
    Copyright (C) 1998, NINTENDO Co,Ltd., MONEGI CORPORATION.
    Oct. 16, 1998.
*/

#ifndef _msn_Switch_h
#define _msn_Switch_h 1

#include "mhc/Node.h"
#include "mhc/NodeHandle.h"
#include "mif/ChunkParser.h"
#include "mso/derive.h"
#include "mvm/Vector.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <ultra64.h>

/* Declare constant value macros */
#define MSN_SWITCH_FIELD_WHICH_CHOICE	(0)

/* Declare structures */
typedef struct _MsnSwitch
{
    _msoDeriveFrom( MhcNode );
    u32			which_choice;
    u32			number_of_children;
    MhcNodeHandle	*child_array;
} MsnSwitch;

/* Declare functions */
extern void msnSwitchInit( MsnSwitch *switch_ptr );

/* Declare a global variable */
extern MifChunkParser gMsnSwitchChunkParser;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _msn_Switch_h */
