#ifndef _NIS_2_H_
#define _NIS_2_H_
/* $Id: nis2.h,v 0.18 1999/01/07 08:20:33 yoshino Exp $ */
/**************************************************************************
 *	NIS Definitions	NIS = NIff Structure 				  *
 *									  *
 *		Copyright (C) 1998, NINTENDO Co.,Ltd.			  *
 *		Copyright (C) 1998, MONEGI CORPORATION			  *
 *									  *
 **************************************************************************/
#include    "niffn64.h"
/*=======================================================*/
/* NIS 2.0 definiton					 */
/* Reference						 */
/* 1998  Nintendo Intermediate File Format  version 2.00 */
/*=======================================================*/
/*-------- Common structures ---------*/
typedef struct _NisExternal
{
    u32	file_name;  /* index for names in ExternalNameList */
    u32	name;	    /* index for names in ExternalNameList */
} NisExternal;

typedef struct _NisRGBA  /* RGBA elements for color */
{
    float   red;
    float   green;
    float   blue;
    float   alpha;
} NisRGBA;

typedef struct _NisXYZ	/* x,y,z coordinates */
{
    float   x;
    float   y;
    float   z;
} NisXYZ;

typedef struct _NisVtxTriNvColorSet
{
    u32   vtx_group_index;
    u32   vtx_nv_group_index;
    u32   tri_nv_group_index;
    u32   vtx_color_group_index;
    u32   tri_color_group_index;
} NisVtxTriNvColorSet;

typedef struct _NisNodeIndex
{
    u32 kind;	/* node type */
    u32 index;	/* node index */
} NisNodeIndex;

typedef struct _NisNodeIndex	NisEnvelopePartIndex;

typedef struct _NisElementTop /* Top data for each element(data in the List such node and group) */

{
    u32	tag;
    u32	this_index; /* index for this data */
    u32	size;
    u32	name;	 /* index for names in NameList */
} NisElementTop;

typedef struct _NisListTop /* Top data for each List */
{
    u32	tag;
    u32	header_size;
    u32	list_size;
} NisListTop;

/*----------------------------- FileHeader --------------------------------*/
typedef struct _NisFileHeaderExt
{
    u32 ci_img_list_num;
    u32 color_palette_list_num;
    u32 envelope_list_num;
    u32 cluster_list_num;
    u32 weight_list_num;
    u32 chain_root_list_num;
    u32 joint_list_num;
    u32 effector_list_num;
    u32 external_name_list_num;
} NisFileHeaderExt;

/*----------------------------- SceneList --------------------------------*/
typedef struct _NisSceneListExt
{
    u32 scene_chain_root_link_num;
    u32 external_obj_num;
    u32 external_env_num;
    u32 external_cam_num;
    u32 external_light_num;
    u32 *scene_chain_root_link_index;
    NisExternal	*external_obj;
    NisExternal	*external_env;
    NisExternal	*external_cam;
    NisExternal	*external_light;
} NisSceneListExt;

/*----------------------------- CamList --------------------------------*/
typedef struct _NisCamExt
{
    NisExternal	external_lookat_obj;
    NisExternal	external_eye_obj;
    NisExternal	external_up_obj;
} NisCamExt;

/*----------------------------- ObjList --------------------------------*/
typedef struct _NisObjExt
{
    u32 obj_render_cycle_type_for_fog;
    u32 obj_render_pri_for_fog;
    u32 obj_render_type0_for_fog;
    u32 obj_render_type1_for_fog;
    u32 obj_chain_root_link_num;
    u32 external_lod_obj_num;
    u32 external_obj_num;
    u32 *obj_chain_root_link;
    float *external_lod_obj_dist;
    NisExternal	*external_lod_obj;
    NisExternal	*external_obj;
} NisObjExt;

/*----------------------------- ShapeList --------------------------------*/
typedef struct _NisShapeExt
{
    u32	kind_of_node_for_geometry;
    NisExternal	external_mat;
} NisShapeExt;

/*----------------------------- MatList --------------------------------*/
typedef struct _NisPrimColorAnim
{
    u32   interpolation_type;
    u32   key;
    NisRGBA prim_color;
} NisPrimColorAnim;

typedef	struct _NisPrimColorAnim    NisPrimColorAnimForFog;

typedef struct _NisMatExt
{
    NisRGBA ambient;
    NisRGBA emission;
    NisRGBA diffuse;
    u32	    mat_type_for_fog;
    u32	    mat_color_type0_for_fog;
    u32	    mat_color_type1_for_fog;
    u32	    mat_alpha_type0_for_fog;
    u32	    mat_alpha_type1_for_fog;
    NisRGBA	prim_for_fog;
    NisExternal	external_local_light;
    u32   external_tex_num;
    u32   prim_color_anim_num;
    u32   prim_color_anim_num_for_fog;
    NisExternal		    *external_tex;
    NisPrimColorAnim	    *c_anim;
    NisPrimColorAnimForFog  *c_anim_fog;
} NisMatExt;

/*----------------------------- TexList --------------------------------*/
typedef struct _NisTexExt
{
    u32 tex_filter;
    u32 use_perspective_correction;
    u32 mipmap_level;
    u32 use_color_palette;
    u32 external_tex_img_num;
    u32 *color_palette_index;
    u32 *tlut_palette_number;
    NisExternal	*external_tex_img;
    NisExternal	*external_palette;
} NisTexExt;

/*----------------------------- TeximgList --------------------------------*/
typedef struct _NisTeximgExt
{
    u32 mipmap_max_level;
    u32 *mipmap_img_offset;
} NisTeximgExt;

/*----------------------------- AnimList --------------------------------*/
typedef struct _NisRotateAxis
{
    u32   interpolation_type;
    u32   key;
    NisXYZ  axis;
    float   rotation_angle;
    NisXYZ  differential_axis;
    float   differential_rotation_angle;
} NisRotateAxis;

typedef struct _NisRotateX
{
    u32   interpolation_type;
    u32   key;
    float rotation_angle;
    float differential_rotation_angle;
} NisRotateX;

typedef struct _NisRotateX	NisRotateY;
typedef struct _NisRotateX	NisRotateZ;

typedef struct _NisOrientationXY
{
    u32   interpolation_type;
    u32   key;
    NisXYZ  x_axis;
    NisXYZ  y_axis;
    NisXYZ  differential_x_axis;
    NisXYZ  differential_y_axis;
} NisOrientationXY;

typedef struct _NisTranslation
{
    u32   interpolation_type;
    u32   key;
    NisXYZ  translate;
    NisXYZ  differential_translate;
} NisTranslation;

typedef struct _NisUniqueScale
{
    u32   interpolation_type;
    u32   key;
    NisXYZ  scale;
    NisXYZ  differential_scale;
} NisUniqueScale;

typedef struct _NisUniqueScale    NisClassicScale;

typedef struct _NisAnimGroupExt
{
    u32 use_animation_channel;
    u32 rotate_axis_num;
    u32 rotate_x_num;
    u32 rotate_y_num;
    u32 rotate_z_num;
    u32 orientation_xy_num;
    u32 translation_num;
    u32 unique_scale_num;
    u32 classic_scale_num;
    NisNodeIndex    orientation_constraint_node;
    NisNodeIndex    direction_constraint_node;
    NisNodeIndex    upvector_constraint_node;
    NisNodeIndex    preferred_axis_constraint_node;
    NisNodeIndex    position_constraint_node;
    NisNodeIndex    unique_scale_constraint_node;
    NisNodeIndex    classic_scale_constraint_node;
    NisExternal	external_orientation_constraint;
    NisExternal	external_direction_constraint;
    NisExternal	external_upvector_constraint;
    NisExternal	external_preferred_axis_constraint;
    NisExternal	external_position_constraint;
    NisExternal	external_unique_scale_constraint;
    NisExternal	external_classic_scale_constraint;
    NisRotateAxis   *rot_axis;
    NisRotateX	    *rot_x;
    NisRotateY	    *rot_y;
    NisRotateZ	    *rot_z;
    NisOrientationXY	*orient_xy;
    NisTranslation	*trans;
    NisUniqueScale	*uniq_scale;
    NisClassicScale	*classic_scale;
} NisAnimGroupExt;

/*======================= Added List for NIS2.0  ==========================*/
/*----------------------- CiImgList ------------------------------------*/
typedef struct _NisCiimg
{
    NisElementTop   top;
    u32   ci_img_width;
    u32   ci_img_height;
    u32   ci_img_pixel_depth;
    u32   reserved[12];
    u32   nin_ext_blk_size;
    u32   usr_ext_blk_size;
    u32   *pixel_index_array;
    u32	  *n_ext;		 
    u32	  *u_ext;	
} NisCiimg;

typedef struct _NisCiimgList
{
    NisListTop	top;
    u32   ci_img_num;
    u32   nin_ext_blk_size;
    u32   usr_ext_blk_size;
    u32   *ci_img_num_byte;
    NisCiimg *ciimg;
    u32	     *n_ext;		 
    u32	     *u_ext;	
} NisCiimgList;

/*----------------------- ColorPaletteList -----------------------------*/
typedef struct _NisColorPalette
{
    NisElementTop   top;
    u32   color_num;
    u32   color_type;
    u32   reserved[13];
    u32   nin_ext_blk_size;
    u32   usr_ext_blk_size;
    u32   *color_array;
    u32	  *n_ext;		 
    u32	  *u_ext;	
} NisColorPalette;

typedef struct _NisColorPaletteList
{
    NisListTop	top;
    u32   color_palette_num;
    u32   nin_ext_blk_size;
    u32   usr_ext_blk_size;
    u32   *color_palette_num_byte;
    NisColorPalette *cpalette;
    u32	  *n_ext;		 
    u32	  *u_ext;	
} NisColorPaletteList;

/*----------------------- EnvelopeList ---------------------------------*/
typedef struct _NisFullWeightedPart
{
    NisElementTop	top;
    NisNodeIndex	transform_node_full;
    NisExternal		external_transform_obj;
    NisVtxTriNvColorSet	poly;
    u32			full_weighted_st_group_index;
    u32   nin_ext_blk_size;
    u32   usr_ext_blk_size;
    u32	  *n_ext;		 
    u32	  *u_ext;	
} NisFullWeightedPart;

typedef struct _NisWeightedPart
{
    NisElementTop   top;
    u32   affected_node_num;
    u32   weight_st_group_index;
    u32   external_affected_obj_num;
    u32   nin_ext_blk_size;
    u32   usr_ext_blk_size;
    NisNodeIndex	*affected_node;
    NisExternal	*external_affected_obj;
    u32   *weight_group_index;
    NisVtxTriNvColorSet	*poly;
    u32	  *n_ext;		 
    u32	  *u_ext;	
} NisWeightedPart;

typedef struct _NisMorphPart
{
    NisElementTop   top;
    struct {
	u32   kind;
	u32   index;
	NisExternal external_obj;
    } node[2];
    u32   morph_st_group_index;
    u32   table_num;
    u32   nin_ext_blk_size;
    u32   usr_ext_blk_size;
    NisVtxTriNvColorSet	*poly;
    u32	  *n_ext;		 
    u32	  *u_ext;	
} NisMorphPart;

typedef struct _NisEnvelopeVtx
{
    NisEnvelopePartIndex    envelope_part;
    u32   vtx_index;
    u32   st_index;
    u32   vtx_nv_index;
    u32   vtx_color_index;
    u32	  weight_index;
} NisEnvelopeVtx;

typedef struct _NisEnvelopeTri
{
    u32   envelope_tri_tag;
    u32   this_envelope_tri_index;
    u32   envelope_tri_size;
    NisEnvelopePartIndex envelope_part_for_tri;
    u32   tri_nv_index;
    u32   tri_color_index;
    u32	  weight_index_tri;
    NisEnvelopeVtx  envvtx[3];
} NisEnvelopeTri;

typedef struct _NisEnvelope
{
    NisElementTop   top;
    u32   envelope_type;
    u32   full_weighted_part_num;
    u32   weighted_part_num;
    u32   morph_part_num;
    u32   envelope_tri_num;
    u32   nin_ext_blk_size;
    u32   usr_ext_blk_size;
    NisFullWeightedPart	*fwpart;
    NisWeightedPart	*wtpart;
    NisMorphPart	*mopart;
    NisEnvelopeTri	*envtri;
    u32	  *n_ext;		 
    u32	  *u_ext;	
} NisEnvelope;

typedef struct _NisEnvelopeList
{
    NisListTop	top;
    u32   envelope_num;
    u32   nin_ext_blk_size;
    u32   usr_ext_blk_size;
    u32   *envelope_size;
    NisEnvelope	*envelope;
    u32	  *n_ext;		 
    u32	  *u_ext;	
} NisEnvelopeList;

/*----------------------- ClusterList ---------------------------------*/
typedef struct _NisCluster
{
    NisElementTop	top;
    NisNodeIndex	transform_node;
    NisExternal		external_transform_obj;
    NisVtxTriNvColorSet	poly;
    u32			cluster_st_group_index;
} NisCluster;

typedef struct _NisClusterVtx
{
    NisNodeIndex    cluster;
    u32   vtx_index;
    u32   st_index;
    u32   vtx_nv_index;
    u32   vtx_color_index;
} NisClusterVtx;

typedef struct _NisClusterTri
{
    u32   cluster_tri_tag;
    u32   this_cluster_tri_index;
    u32   cluster_tri_size;
    NisNodeIndex cluster_for_tri;
    u32   tri_nv_index;
    u32   tri_color_index;
    NisClusterVtx  clusvtx[3];
} NisClusterTri;

typedef struct _NisClusterShape
{
    NisElementTop   top;
    u32   cluster_shape_type;
    u32   cluster_num;
    u32   cluster_tri_num;
    u32   nin_ext_blk_size;
    u32   usr_ext_blk_size;
    NisCluster		*cluster;
    NisClusterTri	*clustri;
    u32	  *n_ext;		 
    u32	  *u_ext;	
} NisClusterShape;

typedef struct _NisClusterList
{
    NisListTop	top;
    u32   cluster_shape_num;
    u32   nin_ext_blk_size;
    u32   usr_ext_blk_size;
    u32   *cluster_shape_size;
    NisClusterShape	*clshape;
    u32	  *n_ext;		 
    u32	  *u_ext;	
} NisClusterList;

/*----------------------- WeightList -----------------------------------*/
typedef struct _NisWeightGroup
{
    NisElementTop   top;
    u32   weight_num;
    u32   nin_ext_blk_size;
    u32   usr_ext_blk_size;
    float *weight;
    u32	  *n_ext;		 
    u32	  *u_ext;	
} NisWeightGroup;

typedef struct _NisWeightList
{
    NisListTop	top;
    u32   weight_group_num;
    u32   nin_ext_blk_size;
    u32   usr_ext_blk_size;
    u32   *weight_group_num_byte;
    NisWeightGroup   *wgroup;
    u32	  *n_ext;		 
    u32	  *u_ext;	
} NisWeightList;

/*----------------------- ChainRootList --------------------------------*/
typedef struct _NisChainRoot
{
    NisElementTop   top;
    u32   chain_root_type;
    u32   obj_num;
    u32   external_obj_num;
    u32   anim_index;
    u32   joint_index;
    u32   nin_ext_blk_size;
    u32   usr_ext_blk_size;
    u32   *obj_index;
    NisExternal	*external_obj;
    u32	  *n_ext;		 
    u32	  *u_ext;	
} NisChainRoot;

typedef struct _NisChainRootList
{
    NisListTop	top;
    u32   chain_root_num;
    u32   nin_ext_blk_size;
    u32   usr_ext_blk_size;
    u32   *chain_root_num_byte;
    NisChainRoot    *chroot;
    u32	  *n_ext;		 
    u32	  *u_ext;		 
} NisChainRootList;

/*----------------------- JointList ------------------------------------*/
typedef struct _NisJoint
{
    NisElementTop   top;
    u32   joint_type;
    float joint_length;
    NisXYZ resplane_axis;
    u32   obj_num;
    u32   external_obj_num;
    u32   joint_index;
    u32   effector_index;
    u32   anim_index;
    u32   nin_ext_blk_size;
    u32   usr_ext_blk_size;
    u32   *obj_index;
    NisExternal	*external_obj;
    u32	  *n_ext;		 
    u32	  *u_ext;	
} NisJoint;

typedef struct _NisJointList
{
    NisListTop	top;
    u32   joint_num;
    u32   nin_ext_blk_size;
    u32   usr_ext_blk_size;
    u32   *joint_num_byte;
    NisJoint	*joint;
    u32	  *n_ext;		 
    u32	  *u_ext;	
} NisJointList;

/*----------------------- EffectorList ---------------------------------*/
typedef struct _NisEffector
{
    NisElementTop   top;
    u32   effector_type;
    u32   obj_num;
    u32   external_obj_num;
    u32   anim_index;
    u32   nin_ext_blk_size;
    u32   usr_ext_blk_size;
    u32   *obj_index;
    NisExternal	*external_obj;
    u32	  *n_ext;		 
    u32	  *u_ext;	
} NisEffector;

typedef struct _NisEffectorList
{
    NisListTop	top;
    u32   effector_num;
    u32   nin_ext_blk_size;
    u32   usr_ext_blk_size;
    u32   *effector_num_byte;
    NisEffector	*effector;
    u32	  *n_ext;		 
    u32	  *u_ext;	
} NisEffectorList;

/*----------------------- ExternalNameList ---------------------------------*/
typedef	struct _NisNameList  NisExternalNameList;

/*----------------------- NIS Extended portion ------------------------------------*/
typedef struct _Nis2Lists
{
    NisCiimgList	*ciimgl;
    NisColorPaletteList	*cpalettel;
    NisEnvelopeList	*envelopel;
    NisClusterList	*clusterl;
    NisWeightList	*weightl;
    NisChainRootList	*rootl;
    NisJointList	*jointl;
    NisEffectorList	*effectorl;
    NisExternalNameList *extnamel;
} Nis2Lists;

#endif /* ! _NIS_2_H_ */
