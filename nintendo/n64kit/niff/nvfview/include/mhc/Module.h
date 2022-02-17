/*
  mhc/Module.h
    Copyright (C) 1998, NINTENDO Co,Ltd., MONEGI CORPORATION.
    Mar. 9, 1999.
*/

#ifndef _mhc_Module_h
#define _mhc_Module_h 1

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <ultra64.h>
#include "mvm/Matrix.h"
#include "mvm/Vector.h"

/* Declare constant macro */
#define MHC_MODULE_STATUS_NOT_LOADED	(0)
#define MHC_MODULE_STATUS_LOADING	(1)
#define MHC_MODULE_STATUS_LOADED	(2)

/* Declare prototype structure */
struct _MhcNode;
struct _MhcNodeHandle;
struct _MhcReference;
struct _MhcScene;
struct _MisInput;
struct _MifFileParser;

/* Declare types of a structure */
typedef struct _MhcModule
{
    u16				status;
    u16				is_active;
    u32				max_nodes;
    u32				number_of_nodes;
    struct _MhcNode		**node_ptr_array;
    u32				number_of_root_nodes;
    struct _MhcNodeHandle	*root_node_handle_array;
    u32				number_of_references;
    struct _MhcReference	*reference_array;
    char			*symbol_table;
    u32				number_of_external_nodes;
    struct _MhcExternalNode	*external_node_array;

    /* the following is used only in flat mode */
    MvmMatrix33f		orientation;
    MvmMatrix33f		scaled_orientation;
    MvmVector3f			translation;
} MhcModule;

/* Declare Functions */
extern void mhcModuleInit( MhcModule *module_ptr );

extern void mhcModuleDestroy( MhcModule *module_ptr );

extern void mhcModuleBeginEval( MhcModule *module_ptr );

extern struct _MhcNode *mhcModuleGetExternalNode( MhcModule *module_ptr,
				struct _MhcScene *scene_ptr, const u32 index );

extern struct _MhcNode *mhcModuleGetNodeByName( MhcModule *module_ptr,
						const char *node_name );

extern u32 mhcModuleGetNodeByType( MhcModule *module_ptr,
				   const u32 type,
				   const u32 array_size,
				   struct _MhcNode **node_ptr_array );

extern void mhcModuleActivate( MhcModule *module_ptr );

extern void mhcModuleInactivate( MhcModule *module_ptr );

extern void mhcModuleBind( MhcModule *module_ptr,
			   struct _MhcScene *scene_ptr );

extern int mhcModuleLoad( MhcModule *module_ptr,
			  struct _MifFileParser *file_parser_ptr,
			  struct _MisInput *input_ptr );

extern int mhcModuleUnload( MhcModule *module_ptr );

#ifdef __cplusplus
}
#endif /* __cplusplus */

/* Declare macro */
#define _mhcModuleIsActive(module_ptr) ( (module_ptr)->is_active )

#define _mhcModuleGetNodeByIndex(module_ptr,index) \
	( (module_ptr)->node_ptr_array[ (index) ] )

#define _mhcModuleAddNode(module_ptr,node_ptr) \
{ \
    (module_ptr)->node_ptr_array[ (module_ptr)->number_of_nodes++ ] =	\
							(node_ptr);	\
}

#endif /* _mhc_Module_h */
