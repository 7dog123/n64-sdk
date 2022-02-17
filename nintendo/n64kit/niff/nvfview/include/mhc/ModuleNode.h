/*
  mhc/ModuleNode.h
    Copyright (C) 1998, NINTENDO Co,Ltd., MONEGI CORPORATION.
    Oct. 6, 1998.
*/

#ifndef _mhc_ModuleNode_h
#define _mhc_ModuleNode_h 1

#include "mhc/Node.h"
#include "mif/ChunkParser.h"
#include "mso/derive.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <ultra64.h>

/* Declare prototype structures */
struct _MhcNode;
struct _MhcReference;
struct _MhcScene;
struct _MisInput;

/* Declare structures */
typedef struct _MhcModuleNode
{
    _msoDeriveFrom( MhcNode );
    u32	module_id;
} MhcModuleNode;

/* Declare functions   */
extern void mhcModuleNodeInit( MhcModuleNode *module_node_ptr );

/* Declare global variables */
extern MifChunkParser *gMhcModuleChunkParserList[ ];
	/* List of ChunkParser('NHDR','MDUL','XTRN','REFR') which controls the module.                        */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _mhc_ModuleNode_h */
