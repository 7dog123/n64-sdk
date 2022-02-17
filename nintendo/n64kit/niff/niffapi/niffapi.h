#ifndef _NIFFAPI_H_
#define _NIFFAPI_H_
/* $Id: niffapi.h,v 0.26 1998/11/12 12:59:18 yoshino Exp yoshino $ */
/**************************************************************************
 *	NIFF API declaration		 				  *
 *									  *
 *		Copyright (C) 1998, NINTENDO Co.,Ltd.			  *
 *		Copyright (C) 1998, MONEGI CORPORATION			  *
 *									  *
 **************************************************************************/
#include    "niffn64.h"
#include    <stdio.h>
#include    <stdlib.h>
#include    <string.h>
#include    <stddef.h>
#include    "nifftags.h"
#include    "niff2tags.h"
#include    "nis.h"

#ifndef TRUE
#define	TRUE    1
#endif
#ifndef FALSE
#define	FALSE   0
#endif
/* #define	ERR	-1 */
/* #define	OK	0  */

/*---- global value -----*/
/* To use global constants,
  #define GLOBAL_VALUE_DEFINE in the file including main(). */

#ifdef GLOBAL_VALUE_DEFINE 
#define GLOBAL
GLOBAL NisRGBA    nisWhite = { 1.0, 1.0, 1.0, 1.0 };
GLOBAL NisXYZ	  nisZ = { 0.0, 0.0, 1.0 };
#else
#define GLOBAL extern
GLOBAL NisRGBA    nisWhite;
GLOBAL NisXYZ	  nisZ;
#endif

#ifdef __cplusplus
extern "C" {
#endif

extern Nis *niNewNis(Nis *nis);		 /* initialize NIS sturucter pointer */

/**************************************************************************
 *  When a function does not return a value specifically, 
 *  it returns TRUE/FALSE.
 *  So you can check to see if a function had an error.
 **************************************************************************/
/*--------------- NIFF binary file operation ----------------*/

/* whole file operation */

extern int niOpenNb(char *filename, Nis *nis); /* NIFF binary file -> NIS */
extern int niSaveAsNb(Nis *nis, char *filename); /* NIS -> NIFF binary file */
extern int niSaveAsNb2(Nis *nis, char *filename); /* NIS2.0 -> NIFF binary file */
extern int niWriteNb(Nis *nis);			 /* NIS -> NIFF binary file */
extern int niNIFFver(NisFileHeader *fh);	 /* NIFF version */

extern FILE *niNbReadOpen(char *filename);   /* only file open, read mode */
extern FILE *niNbWriteOpen(char *filename);  /* only file open, write mode */

/* a part of data operation */

extern int niSetFilename(char *filename, Nis *nis); /* set Nis->Filename */
extern int niReadFileHeader(FILE *fp, Nis *nis);  /* only NIFF FileHeader -> NIS */

/*--------------- NIFF text file operation ------------------*/
extern int niOutputNt(Nis *nis);		 /* output NIFF text to stdout */
extern int niSaveAsNt(Nis *nis, char *filename); /* output NIFF text to file */
extern int niOpenNt(char *filename, Nis *nis);	/* NIFF text file -> NIS1.0 */
	/*  readable only the format outputted by niOutputNt(),niSaveAsNt()
	    (98/9/21 now) */
extern FILE *niNtReadOpen(char *filename);   /* only file open, read mode */
extern FILE *niNtWriteOpen(char *filename);  /* only file open, write mode */

/*--------------- NIS data get --------------------*/
/*--- NameList ---*/
extern char *niGetName(NisName *);   /* get string from NIFF NameList */
extern int   niGetNamelen(NisName *nisname);	/* get length of name string */

/*#####################################################
 #                                                    #
 #	NIS data set                                  #
 #                                                    #
 #####################################################*/
extern void niAdjustListSizeData(Nis *nis, int index, int incsize, u32 tag);

/******************************************************
 *  add node
 ******************************************************/
/* add 1 Envelope */
extern int		/* retunn envelope_num */
niAddEnvelope(Nis *nis,
	      int full_weighted_part_num,   /* each number in this envelope */
	      int weighted_part_num,
	      int morph_part_num,
	      int envelope_tri_num,	    /* tri number in this envleope */
	      u32 shape_index		/* shape, links to this envelope */);
extern int niAddName(Nis*);		/* add 1 name area */
extern void niSetName(Nis*, u32 index, char *name); /* set node_name in name area */

/******************************************************
 *  add link
 *		return FALSE means already linked.
 ******************************************************/
extern int niAddScene_Obj(Nis *nis, u32 obj_index); /* Scene -> Obj */
extern int niAddScene_ChainRoot(Nis *nis, u32 chain_root_index); 
extern int niAddObj_Obj(Nis *nis, u32 obj_index, u32 child_index);
extern int niAddObj_ChainRoot(Nis *nis, u32 obj_index, u32 chain_root_index);
extern int niAddMat_Tex(Nis *nis, u32 mat_index, u32 tex_index);
extern int niAddShape_Envelope(Nis *nis, u32 shape_index, u32 envelope_index);
extern int niAddFullWeightedPart_Obj(Nis *nis, u32 envelope_index,
				     u32 full_weighted_part_index, u32 obj_index);
extern int niAddChainRoot_Obj(Nis *nis, u32 chain_root_index, u32 obj_index);
extern int niAddChainRoot_Anim(Nis *nis, u32 joint_index, u32 anim_group_index);
extern int niAddChainRoot_Joint(Nis *nis, u32 chain_root_index, u32 joint_index);
extern int niAddJoint_Obj(Nis *nis, u32 joint_index, u32 obj_index);
extern int niAddJoint_Anim(Nis *nis, u32 joint_index, u32 anim_group_index);
extern int niAddJoint_Joint(Nis *nis, u32 from_joint_index, u32 to_joint_index);
extern int niAddJoint_Effector(Nis *nis, u32 joint_index, u32 effector_index);
extern int niAddEffector_Obj(Nis *nis, u32 effector_index, u32 obj_index);
extern int niAddEffector_Anim(Nis *nis, u32 effector_index, u32 anim_group_index);

/* MorphPart -> Node */
extern void niAddMorphPart_Node(Nis *nis, u32 envelope_index, u32 morph_part_index,
				u32 node0_kind, u32 node0_index,
				u32 node1_kind, u32 node1_index);

/******************************************************
 *  delete link
 ******************************************************/
extern int niDeleteScene_ChainRoot(Nis *nis, u32 chain_root_index);
extern int niDeleteObj_ChainRoot(Nis *nis, u32 obj_index, u32 chain_root_index);
extern int niDeleteChainRoot_Obj(Nis *nis, u32 chain_root_index, u32 obj_index);
extern int niDeleteChainRoot_Anim(Nis *nis, u32 joint_index);
extern int niDeleteChainRoot_Joint(Nis *nis, u32 chain_root_index);
extern int niDeleteJoint_Obj(Nis *nis, u32 joint_index, u32 obj_index);
extern int niDeleteJoint_Anim(Nis *nis, u32 from_joint_index);
extern int niDeleteJoint_Joint(Nis *nis, u32 from_joint_index);
extern int niDeleteJoint_Effector(Nis *nis, u32 from_joint_index);
extern int niDeleteEffector_Obj(Nis *nis, u32 effector_index, u32 obj_index);
extern int niDeleteEffector_Anim(Nis *nis, u32 effector_index);

#ifdef __cplusplus
}
#endif

#endif	/* ! _NIFFAPI_H_ */
