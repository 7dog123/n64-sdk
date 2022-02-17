#ifndef _NIS_H_
#define _NIS_H_
/* $Id: nis.h,v 0.16 1998/10/22 08:57:16 yoshino Exp $ */
/**************************************************************************
 *	NIS Definitions	NIS = NIff Structure 				  *
 *									  *
 *		Copyright (C) 1998, NINTENDO Co.,Ltd.			  *
 *		Copyright (C) 1998, MONEGI CORPORATION			  *
 *									  *
 **************************************************************************/
#include    "niffn64.h"
#include    "nis2.h"
/*=======================================================*/
/* NIS 1.0 definiton					 */
/* Reference						 */
/* 1997  Nintendo Intermediate File Format  version 1.00 */
/*=======================================================*/
/*---- File Header ----*/
typedef struct _NisFileHeader
{
    u32 version;	    /* version number	    */
    u32 file_size;	    /* (bytes)		    */
    u32 header_tag;	    
    u32 file_header_num;    /* (bytes)		    */
    u32 scene_list_num;	    /* SceneList  (bytes)   */
    u32 env_list_num;	    /* EnvList    (bytes)   */
    u32 cam_list_num;	    /* CamList	  (bytes)   */
    u32 light_list_num;	    /* LightList  (bytes)   */
    u32 obj_list_num;	    /* ObjList	  (bytes)   */
    u32 shape_list_num;	    /* ShapeList  (bytes)   */
    u32 vtx_list_num;	    /* VtxList	  (bytes)   */
    u32 color_list_num;	    /* ColorList  (bytes)   */
    u32 vector_list_num;    /* VectorList (bytes)   */
    u32 st_list_num;	    /* StList	  (bytes)   */
    u32 tri_list_num;	    /* TriList	  (bytes)   */
    u32 part_list_num;	    /* PartList	  (bytes)   */
    u32 mat_list_num;	    /* MatList	  (bytes)   */
    u32 tex_list_num;	    /* TexList	  (bytes)   */
    u32 tex_img_list_num;   /* TexImgList (bytes)   */
    u32 anim_list_num;	    /* AnimList	  (bytes)   */
    u32 coll_list_num;	    /* CollList	  (bytes)   */
    u32 switch_list_num;    /* SwitchList (bytes)   */
    u32 name_list_num;	    /* NameList	  (bytes)   */
    u32 nin_ext_blk_size;   /* Nintendo Extension data block   (bytes) */
    u32 usr_ext_blk_size;   /* User Extension data block (bytes) */
    u32 *n_ext;	    /* Nintendo Extension data block	*/
    u32 *u_ext;	    /* User Extension data block	*/
    NisFileHeaderExt *n2;   /* extending in NIFF2.0 */
} NisFileHeader;

/*---- SceneList ----*/
typedef struct _NisSceneList
{
    u32	scene_header_tag;	/* Scene header tag	    */
    u32 scene_header_size;	/* The number of bytes in SceneHeader area 	    */
    u32 scene_size;		/* The number of bytes in the whole Scene area  	    */
    u32 scene_cfg;		/* Setting to draw a whole scene  */
    u32 scene_name_index;	/* Index number in NameList that describes scene name */
    u32 scene_obj_link_num;	/* The total number of linked Obj nodes	*/
    u32 scene_env_link_num;	/* The total number of linked Env nodes	*/
    u32 scene_cam_link_num;	/* The total number of linked Cam nodes	*/
    u32 scene_light_link_num;	/* The total number of linked Light nodes*/
    u32 nin_ext_blk_size;	/* Nintendo Extension data block   (bytes) */
    u32 usr_ext_blk_size;	/* User Extension data block (bytes) */
    u32	*scene_obj_link_index;	/* Obj link   */
    u32	*scene_env_link_index;	/* Env link   */
    u32	*scene_cam_link_index;	/* Cam link   */
    u32	*scene_light_link_index;/* Light link */
    u32 *n_ext;			/* Nintendo Extension data block	  */
    u32 *u_ext;			/* User Extension data block */
    NisSceneListExt *n2;	/* extending in NIFF2.0 */
} NisSceneList;

/*--------------------- EnvList ------------------------------------*/
typedef struct _NisEnvListHeader
{
    u32 env_list_tag;		/* EnvList area tag	    */
    u32 env_list_header_size;	/* The number of bytes of EnvListHeader area */
    u32 env_list_size;		/* The number of bytes of EnvList area    */
    u32 env_num;		/* env_num is Env area number 	    */
    u32 nin_ext_blk_size;   /* Nintendo Extension data block   (bytes) */
    u32 usr_ext_blk_size;   /* User Extension data block (bytes) */
    u32 *env_num_byte;	/* env_num_byte is the number of bytes for each Env area  */
} NisEnvListHeader; 

/* Env area */
typedef struct _NisEnv
{
    u32 env_tag;	/* Env area tag */
    u32 this_env_index;	/* Index number of this Env area  */
    u32 env_size;	/* The number of bytes in this Env area	*/
    u32 env_name_index;	/* Index number in NameList area that describes Env name */
    u32 fog;		/* Whether or not to use FOG	*/
    u32 fog_color;	/* Set a Fog color as 0xRRGGBBAA when using FOG */
    u32 fog_near;	/* Position where Fogging starts 	*/
    u32 fog_far;	/* Position where Fogging stops	 */
    u32 fill_color;	/* Color for clearing a frame buffer 	    */
    u32 fill_depth;	/* Color for clearing the Z buffer		    */
    u32 bg_sprite_img;	/* Specify an index number in TexList when using a texture image for BG. */
    u32 bg_sprite_depth;/* Specify an index numer in TexList when using a depth image for BG. */
    u32 nin_ext_blk_size;   /* Nintendo Extension data block   (bytes) */
    u32 usr_ext_blk_size;   /* User Extension data block (bytes) */
    u32	*n_ext;		    /* Nintendo Extension data block	  */
    u32	*u_ext;		    /* User Extension data block */
} NisEnv;

typedef	struct _NisEnvList
{
    NisEnvListHeader   *h;
    NisEnv	*env;
    u32		*n_ext;		/* Nintendo Extension data block	  */
    u32		*u_ext;		/* User Extension data block */
} NisEnvList;

/*--------------------- CamList ------------------------------------*/ 
typedef struct _NisCamListHeader
{     
    u32 cam_list_tag;		/* CamList area tag	    */
    u32 cam_list_header_size;	/* The number of bytes in CamListHeader area     */
    u32 cam_list_size;		/* The number of bytes in CamList area	    */
    u32 cam_num;		/* The total number of Cam areas in CamList	    */
    u32 nin_ext_blk_size;   /* Nintendo Extension data block   (bytes) */
    u32 usr_ext_blk_size;   /* User Extension data block (bytes) */
    u32 *cam_num_byte;	    /* The number of bytes in corresponding Cam area */	
} NisCamListHeader; 

/* Cam area */
typedef struct _NisCam
{
    u32 cam_tag;	    /* Cam area tag	    */
    u32 this_cam_index;	    /* Index number of this Cam area	    */
    u32 cam_size;	    /* The number of bytes of this Cam area		    */
    u32 cam_name_index;	    /* Index number in NameList that describes a camera name */
    u32 cam_type;	    /* Specify a camera type		    */
    float cam_near_clip;    /* near clipping plane		    */
    float cam_far_clip;	    /* far clipping plane		    */
    float cam_right_clip;   /* right clipping plane 	    */
    float cam_left_clip;    /* left clipping plane		    */
    float cam_top_clip;	    /* top clipping plane		    */	
    float cam_bottom_clip;  /* bottom clipping plane	    */
    float cam_fovy;	    /* fovy value				    */
    float cam_aspect;	    /* aspect ratio				    */
    float cam_scale;	    /* scale value			    */
    u32 cam_lookat_obj;	    /* Link a focal point of the camera to the object   	    */
    u32 cam_eye_obj;	    /* Link an image point of the camera to the object	    */
    u32 cam_up_obj;	    /* Link up vector of the camera to the object */
    u32 nin_ext_blk_size;   /* Nintendo Extension data block   (bytes) */
    u32 usr_ext_blk_size;   /* User Extension data block (bytes) */
    u32	*n_ext;		    /* Nintendo Extension data block	  */
    u32	*u_ext;		    /* User Extension data block */
    NisCamExt	*n2;	    /* extending in NIFF2.0 */
} NisCam;

typedef	struct _NisCamList
{
    NisCamListHeader   *h;
    NisCam	*cam;
    u32		*n_ext;		/* Nintendo Extension data block	  */
    u32		*u_ext;		/* User Extension data block */
} NisCamList;

/*----------------------------- LightList ----------------------------------*/
typedef struct _NisLightListHeader
{
    u32 light_list_tag;			/* LightList area tag	    */
    u32 light_list_header_size;		/* The number of bytes in LightListHeader area  */
    u32 light_list_size;		/* The number of bytes in LightList area	    */
    u32 light_num;			/* The number of Light areas in LightList	    */
    u32 nin_ext_blk_size;	/* Nintendo Extension data block   (bytes) */
    u32 usr_ext_blk_size;	/* User Extension data block (bytes) */
    u32 *light_num_byte;	/* The number of bytes in the corresponding Light area  */
} NisLightListHeader; 

/* DirLight area */
/* TYPE_DIRECTION */
typedef struct _NisDirLightDirection
{
    u32   dir_light_tag;	/* DirLight area tag TAG_DIR_LIGHT_DIFFUSE */
    u32   this_dir_light_index;	/* Index number of this DirLight area  */
    u32   dir_light_size;	/* The number of bytes in this DirLight area  		*/
    float dir_color_r;		/* Red component for directional light color	*/
    float dir_color_g;		/* Green component for directional light color	*/
    float dir_color_b;		/* Blue component for directional light color	*/
    float dir_x;		/* X directional vector of Diffuse light		*/
    float dir_y;		/* Y directional vector of Diffuse light		*/
    float dir_z;		/* Z directional vector of Diffuse light		*/
} NisDirLightDirection;

/* TYPE_POSITION */
typedef struct _NisDirLightPosition
{
    u32 dir_light_tag;	/* DirLight area tag TAG_DIR_LIGHT_POSITION */
    u32 this_dir_light_index;	/* Index number of this DirLight area */
    u32 dir_light_size;		/* The number of bytes in this DirLight area	*/
    float dir_color_r;		/* Red component for directional light color	*/
    float dir_color_g;		/* Green component for directional light color	*/
    float dir_color_b;		/* Blue component for directional light color	*/
    float pos_x;		/* X coordinate of Positional light(absolute coordinate)	*/
    float pos_y;		/* Y coordinate of Positional light(absolute coordinate)	*/
    float pos_z;		/* Z coordinate of Positional light (absolute coordinate)	*/
    float dir_a1;		/* attenuation factor 1 for Positional light 		*/
    float dir_a2;		/* attenuation factor 2 for Positional light		*/
} NisDirLightPosition;

typedef union _NisDirLight
{
    NisDirLightDirection    dir;
    NisDirLightPosition     pos;
} NisDirLight;

/* Light area */
typedef struct _NisLight
{
    u32 light_tag;	    /* Light area tag			*/
    u32 this_light_index;   /* Index number of this Light area	*/
    u32 light_header_size;  /* The number of bytes in this LightHeader area		*/
    u32 light_size;	    /* The number of bytes in this Light area		*/
    u32 light_name_index;   /* Index in Namelist which describes Light name  */
    u32 light_type;	    /* light type			*/
    float ambient_r;	    /* Red component from ambient light		*/
    float ambient_g;	    /* Green component from ambient light	*/
    float ambient_b;	    /* Blue component from ambient light		*/
    u32 dir_light_num;	    /* The number of DirLight areas			    */
    u32 nin_ext_blk_size;	/* Nintendo Extension data block   (bytes) */
    u32 usr_ext_blk_size;	/* User Extension data block (bytes) */
    NisDirLight	    *dirlight;
    u32	  *n_ext;	    /* Nintendo Extension data block   */
    u32	  *u_ext;	    /* User Extension data block */
} NisLight;

typedef	struct _NisLightList
{
    NisLightListHeader	*h;
    NisLight	*light;
    u32	  *n_ext;	    /* Nintendo Extension data block   */
    u32	  *u_ext;	    /* User Extension data block */
} NisLightList;

/*------------------------- ObjList --------------------------------*/
typedef struct _NisObjListHeader
{
    u32 obj_list_tag;		/* ObjList tag			    */
    u32 obj_list_header_size;	/* The number of bytes in ObjListHeader area	    */
    u32 obj_list_size;		/* The number of bytes in ObjList area		    */
    u32 obj_num;		/* The number of all the objects used in the scene */
    u32 nin_ext_blk_size;	/* Nintendo Extension data block   (bytes) */
    u32 usr_ext_blk_size;	/* User Extension data block (bytes) */
    u32	*obj_num_byte;	/* The number of bytes for each Obj area */
} NisObjListHeader;

/*---- Obj area ----*/
typedef struct _NisObj
{
    u32 obj_tag;	/* Obj area tag	    */
    u32 this_obj_index;
    u32 obj_size;	/* The number of bytes of this Obj area 	    */
    u32 obj_name_index;	/* Index number of the object name  */
    u32 obj_state;	
    u32 obj_type;	
    u32 obj_group;	/* Group ID			    */
    u32 obj_pri;	/* Priority of this object */
    u32 obj_render_cycle_type;	/* Cycle type of N64 RDP		    */
    u32 obj_render_pri;	     /* Priority when rendering object  */
    u32 obj_render_type0;    /* Specify N64 render mode 			    */
    u32 obj_render_type1;    /* Specify N64 render mode 			    */
    u32 have_link_billboard; /* Whether or not to have hierarchical links to billboard object */
    u32 obj_lod_num;	    /* LOD number	    */
    u32 obj_child_num;	    /* Child object number  */
    u32 obj_parent_link;    
    u32 obj_shape_link;	
    u32 obj_mat_link;	
    u32 obj_anim_link;	
    u32 obj_coll_link;	
    u32 nin_ext_blk_size;   /* Nintendo Extension data block   (bytes) */
    u32 usr_ext_blk_size;   /* User Extension data block (bytes) */
    float *obj_lod_dist;    /* Switching distance of LOD level of object 	*/
    u32	  *obj_lod_link;    /* Index number of Obj which links every LOD	*/
    u32   *obj_child_link;  /* Index number of child object 		*/
    u32	  *n_ext;	    /* Nintendo Extension data block   */
    u32	  *u_ext;	    /* User Extension data block */
    NisObjExt *n2;	    /* extending in NIFF2.0 */
} NisObj;

typedef	struct _NisObjList
{		
    NisObjListHeader *h;    /* ObjListHeader	*/
    NisObj	     *obj;  /* Obj area	*/
    u32	    *n_ext;	    /* Nintendo Extension data block   */
    u32	    *u_ext;	    /* User Extension data block */
} NisObjList;

/*---------------------------- ShapeList -----------------------------------*/
typedef struct _NisShapeListHeader
{
    u32 shape_list_tag;		/* ShapeList tag			    */
    u32	shape_list_header_size;	/* The number of bytes in ShapeListHeader area	    */
    u32 shape_list_size;	/* The number of bytes in ShapeList area 		    */
    u32 shape_num;		/* The number of shapes described in ShapeList    */
    u32 nin_ext_blk_size;	/* Nintendo Extension data block   (bytes) */
    u32 usr_ext_blk_size;	/* User Extension data block (bytes) */
    u32	*shape_num_byte;	/* The number of bytes in each Shape area */
} NisShapeListHeader; 

/*---- Shape area ----*/
typedef struct _NisShape
{
    u32 shape_tag;	  /* Shape area tag		    */
    u32 this_shape_index; /* Index number of this Shape area   	    */
    u32 shape_size;	  /* The number of bytes in this Shape area 	 */
    u32 shape_name_index; /* Index number of shape name	    */
    u32 shape_type;	  /* Specify shape type		    */
    u32 shape_tri_link;   /* Index number of TriGroup in TriList */
    u32 shape_mat_link;   /* Index number in MatList	    */
    u32 shape_part_num;   /* The number of parts included in shape  	    */
    u32 nin_ext_blk_size;   /* Nintendo Extension data block   (bytes) */
    u32 usr_ext_blk_size;   /* User Extension data block (bytes) */
    u32	*shape_part_link;   /* Index number in PartList     */
    u32	*n_ext;		    /* Nintendo Extension data block   */
    u32	*u_ext;		    /* User Extension data block */
    NisShapeExt	*n2;	    /* extending in NIFF2.0 */
} NisShape;

typedef	struct _NisShapeList
{		
    NisShapeListHeader *h;
    NisShape	    *shape;
    u32	    *n_ext;	    /* Nintendo Extension data block   */
    u32	    *u_ext;	    /* User Extension data block */
} NisShapeList;

/*---------------------------  VtxList --------------------------------*/
typedef struct _NisVtxListHeader
{
    u32 vtx_list_tag;		/* VtxList area tag		*/
    u32 vtx_list_header_size;	/* The number of bytes in VtxListHeader area	*/
    u32 vtx_list_size;		/* The number of bytes in VtxList area  		*/
    u32 vtx_group_num;		/* The total number of VtxGroup included in VtxList area*/
    u32 nin_ext_blk_size;	/* Nintendo Extension data block   (bytes) */
    u32 usr_ext_blk_size;	/* User Extension data block (bytes) */
    u32 *vtx_group_num_byte;	/* The number of bytes of corresponding VtxGroup */
} NisVtxListHeader; 

/*---- Vtx area  ----*/
typedef struct _NisVtx
{
    float x;  /* x_coordinate;*/	/* X coordinate of vertex  */
    float y;  /* y_coordinate;*/	/* Y coordinate of vertex  */
    float z;  /* z_coordinate;*/	/* Z coordinate of vertex  */
} NisVtx;

/*---- VtxGroup area ----*/
typedef struct _NisVtxGroup
{
    u32 vtx_group_tag;		/* VtxGroup area tag		*/
    u32 this_vtx_group_index;	/* Index number of this VtxGroup area  */
    u32 vtx_group_header_size;	/* The number of bytes in this VtxGroupHeader area   	*/
    u32 vtx_group_size;		/* The number of bytes in this VtxGroup area 		*/
    u32 vtx_group_name_index;	/* Index number of VtxGroup name  		*/
    u32 vtx_num;		/* The total number of Vtx included in this VtxGroup     */
    NisVtx	    *vtx;
} NisVtxGroup;

typedef	struct _NisVtxList
{		
    NisVtxListHeader *h;	/* list header	    */
    NisVtxGroup	     *vtxg;	/* Array of VtxGroup area  */
    u32	*n_ext;		    /* Nintendo Extension data block   */
    u32	*u_ext;		    /* User Extension data block */
} NisVtxList;

/*------------------------ TriList ---------------------------------*/
typedef struct _NisTriListHeader
{
    u32 tri_list_tag;		/* TriList tag		    */
    u32 tri_list_header_size;	/* The number of bytes in TriListHeader area     */
    u32 tri_list_size;		/* The number of bytes in TriList area   	    */
    u32 tri_group_num;		/* The total number of TriGroup included in TriList  */
    u32 nin_ext_blk_size;	/* Nintendo Extension data block   (bytes) */
    u32 usr_ext_blk_size;	/* User Extension data block (bytes) */
    u32	*tri_group_num_byte;	/* The number of bytes of each TriGroup  */
} NisTriListHeader;
				
/* ReferenceVtxData */ 	
typedef struct _NisRefVtxData
{
    u32	vtx_anim_key_num;   /* The total number of keys in case of key frame animation */
    u32	*vtx_anim_key;	    /* Corresponding key frame value 			    */
    u32	*vtx_group_index;   /* Index number of referenced VtxGroup area 	    */
} NisRefVtxData;

/* ReferenceTriColorData */
typedef struct _NisRefTriColorData
{
    u32	tri_color_anim_key_num;	/* The total number of keys in case of key frame animation */
    u32	*tri_color_anim_key;	/* Corresponding key frame value		    */
    u32	*tri_color_group_index;	/* Index number of referenced TriColorGroup   */
} NisRefTriColorData;

/* ReferenceVtxColorData */
typedef struct _NisRefVtxColorData
{
    u32	vtx_color_anim_key_num;	/* The total number of keys in case of key frame animation */
    u32	*vtx_color_anim_key;	/* Corresponding key frame value		    */
    u32	*vtx_color_group_index;	/* Index number of referenced VtxColorGroup  */
} NisRefVtxColorData;

/* ReferenceTriNvData */
typedef struct _NisRefTriNvData
{
    u32	tri_nv_anim_key_num;	/* The total number of keys in case of key frame animation */
    u32	*tri_nv_anim_key;	/* Corresponding key frame value		    */
    u32	*tri_nv_group_index;	/* Index number of referenced TriNvGroup  	    */
} NisRefTriNvData;

/* ReferenceVtxNvData */
typedef struct _NisRefVtxNvData
{
    u32	vtx_nv_anim_key_num;	/* The total number of keys in case of key frame animation */
    u32	*vtx_nv_anim_key;	/* Corresponding key frame value		    */
    u32	*vtx_nv_group_index;	/* Index number of referenced VtxNvGroup	    */
} NisRefVtxNvData;

/* ReferenceStData */
typedef struct _NisRefStData
{
    u32	st_anim_key_num;    /* The total number of keys in case of key frame animation */
    u32	*st_anim_key;	    /* Corresponding key frame value			    */
    u32	*st_group_index;    /* Index number of referenced StGroup area 	    */
} NisRefStData;

/* ---- Tri area ---- */
typedef struct _NisTri 
{
    u32 tri_tag;	/* Tri area tag		*/
    u32 this_tri_index;	/* Index number of this Tri area	*/
    u32 tri_size;	/* The number of bytes in this Tri area 	*/
    u32 tri_nv_index;	/* TriNv index in referenced TriNvGroup  	    */
    u32 tri_color_index;/* TriColor index in referenced TriColorGroup   */
    u32	vtx_index0;	/* Vtx index in referenced VtxGroup 	    */
    u32 st_index0;	/* St index in referenced StGroup 	    */
    u32 vtx_nv_index0;	/* VtxNv index in referenced VtxNvGroup 	    */
    u32 vtx_color_index0;/*VtxColor index in referenced VtxColorGroup   */
    u32	vtx_index1;	
    u32 st_index1;	/* St index in referenced StGroup 	    */
    u32 vtx_nv_index1;	/* VtxNv index in referenced VtxNvGroup */
    u32 vtx_color_index1;/*VtxColor index in referenced VtxColorGroup  */
    u32	vtx_index2;	/* Vtx index in referenced VtxGroup    */
    u32 st_index2;	/* St index in referenced StGroup 	    */
    u32 vtx_nv_index2;	/* VtxNv index in referenced VtxNvGroup */
    u32 vtx_color_index2;/*VtxColor index in referenced VtxColorGroup  */
    u32 nin_ext_blk_size;   /* Nintendo Extension data block   (bytes) */
    u32 usr_ext_blk_size;   /* User Extension data block (bytes) */
    u32	*n_ext;		    /* Nintendo Extension data block   */
    u32	*u_ext;		    /* User Extension data block */
} NisTri;

/*---- TriGroup area ----*/
typedef struct _NisTriGroup
{
    u32 tri_group_tag;	       /* TriGroup area tag	    */
    u32 this_tri_group_index;  /* Index number of this TriGroup    */
    u32 tri_group_header_size; /* The number of bytes in this TriGroupHeader 	    */
    u32 tri_group_size;	       /* The number of bytes in this TriGroup	    */
    u32 tri_group_name_index;  /* Index number of TriGroup name*/
    u32 tri_anim_type;	       /* Specify shape animation type  	*/
    u32 tri_anim_frame_num;    /* The number of shape animation frames    	*/
    u32 tri_num;	       /* The number of Tri areas in this TriGroup	*/
    NisRefVtxData	*refVtx;	    
    NisRefTriColorData	*refTriColor;   
    NisRefVtxColorData  *refVtxColor;   
    NisRefTriNvData     *refTriNv;	    
    NisRefVtxNvData     *refVtxNv;	    
    NisRefStData	*refSt;	    
    NisTri  *tri;
} NisTriGroup;

typedef	struct _NisTriList
{		
    NisTriListHeader *h;    /* List header    */
    NisTriGroup	  *trig;    /* Array of TriGroup area */
    u32	*n_ext;		    /* Nintendo Extension data block   */
    u32	*u_ext;		    /* User Extension data block */
} NisTriList;

/*---------------------- ColorList ------------------------*/
typedef struct _NisColorListHeader
{
    u32 color_list_tag;		/* ColorList tag		    */
    u32 color_list_header_size;	/* The number of bytes in ColorListHeader area   */
    u32 color_list_size;	/* The number of bytes in ColorList area	    */
    u32 tri_color_group_num;	/* TriColorGroup number*/
    u32	vtx_color_group_num;	/* VtxColorGroup number*/
    u32 nin_ext_blk_size;	/* Nintendo Extension data block   (bytes) */
    u32 usr_ext_blk_size;	/* User Extension data block (bytes) */
    u32 *tri_color_group_size;	/* The number of bytes in corresponding TriColorGroup area */
    u32	*vtx_color_group_size;	/* The number of bytes in corresponding VtxColorGroup area */
} NisColorListHeader;

/*---- TriColor area ----*/
typedef struct _NisTriColor
{
    float red;	/*_component;*/	/* Red component of polygon color    */
    float green;/*_component;*/	/* Green component of polygon color */
    float blue;	/*_component;*/	/* Blue component of polygon color  */
    float alpha;/*_component;*/	/* Alpha component of polygon color */
} NisTriColor;

/*---- TriColorGroup area ----*/
typedef struct _NisTriColorGroup
{
    u32 tri_color_group_tag;	    /* TriColorGroup tag		*/
    u32 this_tri_color_group_index; /* Index number of this TriColorGroup */
    u32 tri_color_group_header_size;/* The number of bytes in this TriColorGroupHeader   */
    u32 tri_color_group_size;	    /* The number of bytes in this TriColorGroup area     */
    u32 tri_color_num;		    /* The number of TriColor areas*/
    NisTriColor		*tricolor;
} NisTriColorGroup;

/*---- VtxColor area ----*/
typedef struct _NisVtxColor
{			 
    float red;	    /*_component;*/    /* Red component of polygon color    */
    float green;    /*_component;*/    /* Green component of polygon color */
    float blue;	    /*_component;*/    /* Blue component of polygon color  */
    float alpha;    /*_component;*/    /* Alpha component of polygon color */
} NisVtxColor;

/*---- VtxColorGroup area ----*/
typedef struct _NisVtxColorGroup
{
    u32 vtx_color_group_tag;	    /* VtxColorGroup tag		*/
    u32 this_vtx_color_group_index; /* Index number of this VtxColorGroup   */
    u32 vtx_color_group_header_size;/* The number of bytes in this VtxColorGroupHeader     */
    u32 vtx_color_group_size;	    /* The number of bytes in this VtxColorGroup area   */
    u32 vtx_color_num;	       /* The number of VtxColor areas in this VtxColorGroup */
    NisVtxColor		*vtxcolor;
} NisVtxColorGroup;

typedef	struct _NisColorList
{		
    NisColorListHeader *h;	/* List header		*/
    NisTriColorGroup   *tri_c_g;    /* Array of TriColorGroup area */
    NisVtxColorGroup   *vtx_c_g;    /* Array of VtxColorGroup area */
    u32	*n_ext;			    /* Nintendo Extension data block   */
    u32	*u_ext;			    /* User Extension data block */
} NisColorList;

/*------------------------ VectorList -------------------------*/
typedef struct _NisVectorListHeader
{
    u32 vector_list_tag;	/* VectorList tag		*/
    u32 vector_list_header_size;/* The number of bytes in VectorListHeader  	*/
    u32 vector_list_size;	/* The number of bytes in VectorList		*/
    u32 tri_nv_group_num;	/* Total number of TriNvGroup areas	*/
    u32 vtx_nv_group_num;	/* Total number of VtxNvGroup areas	*/
    u32 nin_ext_blk_size;	/* Nintendo Extension data block   (bytes) */
    u32 usr_ext_blk_size;	/* User Extension data block (bytes) */
    u32 *tri_nv_group_size;	/* The number of bytes of each TriNvGroup area */
    u32 *vtx_nv_group_size;	/* The number of bytes of each VtxNvGroup area */
} NisVectorListHeader; 

/*---- TriNv area ----*/
typedef struct _NisTriNv
{
    float x;  /*_vector;*/	/* X component of normal vector */
    float y;  /*_vector;*/	/* Y component of normal vector */
    float z;  /*_vector;*/	/* Z component of normal vector */
} NisTriNv;

/*---- TriNvGroup area ----*/
typedef struct _NisTriNvGroup
{
    u32 tri_nv_group_tag;	    /* TriNvGroup area tag     */
    u32 this_tri_nv_group_index;    /* Index number of this TriNvGroup*/
    u32 tri_nv_group_header_size;   /* The number of bytes in this TriNvGroupHeader area */
    u32 tri_nv_group_size;	    /* The number of bytes in this TriNvGroup area   	     */
    u32 tri_nv_num;		    /* Total number of TriNv areas		     */
    NisTriNv	*trinv;
} NisTriNvGroup;

/*---- VtxNv area ----*/
typedef struct _NisVtxNv
{
    float x;  /*_vector;*/	/* X component of normal vector */
    float y;  /*_vector;*/	/* Y component of normal vector */
    float z;  /*_vector;*/	/* Z component of normal vector */
} NisVtxNv;

/*---- VtxNvGroup area ----*/
typedef struct _NisVtxNvGroup
{
    u32 vtx_nv_group_tag;	  /* VtxNvGroup area tag		    */
    u32 this_vtx_nv_group_index;  /* Index number of this VtxNvGroup area    */
    u32 vtx_nv_group_header_size; /* The number of bytes in this VtxNvGroupHeader area    */
    u32 vtx_nv_group_size;	  /* The number of bytes in this VtxNvGroup area 	    */
    u32 vtx_nv_num;	          /* Total number of VtxNv areas			    */
    NisVtxNv	*vtxnv;
} NisVtxNvGroup;

typedef	struct _NisVectorList
{		
    NisVectorListHeader *h;	/* List  header		*/
    NisTriNvGroup	*tri_nv_g;  /* Array of TriVectorGroup area*/
    NisVtxNvGroup	*vtx_nv_g;	/* Array of VtxVectorGroup area	*/
    u32	*n_ext;			/* Nintendo Extension data block   */
    u32	*u_ext;			/* User Extension data block */
} NisVectorList;

/*-------------------------- StList ----------------------------*/
typedef struct _NisStListHeader
{
    u32 st_list_tag;		/* StListTag area tag	*/
    u32 st_list_header_size;	/* The number of bytes in StListHeader area */
    u32 st_list_size;		/* The number of bytes in StList area  	*/
    u32 st_group_num;		/* Total number of StGroup area  		*/
    u32 nin_ext_blk_size;	/* Nintendo Extension data block   (bytes) */
    u32 usr_ext_blk_size;	/* User Extension data block (bytes) */
    u32	*st_group_size;		/* The number of bytes of each StGroup   */
} NisStListHeader;

/*---- St area ----*/
typedef struct _NisSt
{
    float s;	/* S texture coordinate */
    float t;	/* T texture coordinate */
} NisSt;

/*---- StGroup area ----*/
typedef struct _NisStGroup
{
    u32 st_group_tag;		/* StGroup area tag		*/
    u32 this_st_group_index;	/* Index number of this StGroup area  	*/
    u32 st_group_header_size;	/* The number of bytes in this StGroupHeader area	*/
    u32 st_group_size;		/* The number of bytes in this StGroup area  		*/
    u32 st_num;			/* The number of St area included in this StGroup area */
    NisSt	*st;
} NisStGroup;

typedef	struct _NisStList
{		
    NisStListHeader *h;	    /* List header	    */
    NisStGroup	    *stg;   /* Array of StGroup area  */
    u32	*n_ext;		    /* Nintendo Extension data block   */
    u32	*u_ext;		    /* User Extension data block */
} NisStList;

/*-------------------------- PartList -------------------------------*/
typedef struct _NisPartListHeader
{
    u32 part_list_tag;		/* PartList tag		    */
    u32 part_list_header_size;	/* The number of bytes in PartListHeader area    */
    u32 part_list_size;		/* The number of bytes in PartList area  	    */
    u32 part_num;		/* Total number of Part areas in PartList  	    */
    u32 nin_ext_blk_size;	/* Nintendo Extension data block   (bytes) */
    u32 usr_ext_blk_size;	/* User Extension data block (bytes) */
    u32	*part_num_byte;		/* The number of bytes of each Part area   */
} NisPartListHeader;

/*---- Part area ----*/
typedef struct _NisPart
{
    u32 part_tag;	/* Part area tag		    */
    u32 this_part_index;/* Index number of this Part area   */
    u32 part_size;	/* Size of this Part area 	    */
    u32 part_name_index;/* Index number of Part name  */
    u32 mat_index;	/* Mat index used in Part*/
    u32 tri_group_index;/* TriGroup index used in this Part*/
    u32 part_tri_num;	/* Triangle number used in this part   */
    u32 nin_ext_blk_size;	/* Nintendo Extension data block   (bytes) */
    u32 usr_ext_blk_size;	/* User Extension data block (bytes) */
    u32	*tri_index; /* Triangle index number   */
    u32	*n_ext;			    /* Nintendo Extension data block   */
    u32	*u_ext;			    /* User Extension data block */
} NisPart;

typedef	struct _NisPartList
{		
    NisPartListHeader  *h;	/* List header	    */
    NisPart	       *part;	/* Array of Part area  	    */
    u32	*n_ext;			/* Nintendo Extension data block     */
    u32	*u_ext;			/* User Extension data block   */
} NisPartList;

/*----------------------------- MatList --------------------------------*/
typedef struct _NisMatListHeader
{
    u32 mat_list_tag;		/* MatList tag		*/
    u32 mat_list_header_size;	/* The number of bytes in this MatListHeader  		*/
    u32 mat_list_size;		/* The number of bytes in this MatList 		*/
    u32 mat_num;	    /* The number of Mat areas described in MatList  */
    u32 nin_ext_blk_size;   /* Nintendo Extension data block   (bytes) */
    u32 usr_ext_blk_size;   /* User Extension data block (bytes) */
    u32	*mat_num_byte;	    /* The number of bytes of each Mat area   */
} NisMatListHeader;

/*---- Mat area ----*/
typedef struct _NisMat
{
    u32 mat_tag;	/* Mat area tag				*/
    u32 this_mat_index;	/* Index number of this Mat area 		*/
    u32 mat_size;	/* Size of this Mat area			*/
    u32 mat_name_index;	/* Index number in NameList which describes Mat name    	*/
    u32 mat_type;	/* Material type: NIFF|N64			*/
    u32 mat_shade_type;	/* Shading		    */
    u32 mat_color_type0; /* Color modulation			    */
    u32 mat_color_type1; /* Color modulation 2 cycle mode only*/
    u32 mat_alpha_type0; /* Alpha modulation		    */
    u32 mat_alpha_type1; /* Alpha modulation 2 cycle mode only*/
    float prim_red;	/* Red component of primitive color	    */
    float prim_green;	/* Green component of primitive color   */
    float prim_blue;	/* Blue component of primitive color	    */
    float prim_alpha;	/* Alpha component of primitive color    */
    u32 usr_flag0;	/* 32bit flag of user definition  */
    u32 usr_flag1;	/* 32bit flag of user definition   */
    u32 usr_flag2;	/* 32bit flag of user definition  */
    u32 usr_flag3;	/* 32bit flag of user definition  */
    u32 usr_flag4;	/* 32bit flag of user definition  */
    u32 usr_flag5;	/* 32bit flag of user definition  */
    u32 usr_flag6;	/* 32bit flag of user definition  */
    u32 usr_flag7;	/* 32bit flag of user definition  */
    u32 local_light_index;
    u32 tex_num;	/* The number of texture used in Mat.  Either 0,1,or 2  */
    u32 nin_ext_blk_size;		/* Nintendo Extension data block   (bytes) */
    u32 usr_ext_blk_size;		/* User Extension data block (bytes) */
    u32	*tex_index;		    /* Index number of texture */
    u32	*n_ext;			    /* Nintendo Extension data block     */
    u32	*u_ext;			    /* User Extension data block   */
    NisMatExt *n2;	    /* extending in NIFF2.0 */
} NisMat;

typedef	struct _NisMatList
{		
    NisMatListHeader	*h; /* List header		*/
    NisMat	      *mat; /* Array of Mat area  		*/
    u32	*n_ext;		    /* Nintendo Extension data block     */
    u32	*u_ext;		    /* User Extension data block	*/
} NisMatList;

/*---------------------- TexList -------------------------*/
typedef struct _NisTexListHeader
{
    u32 tex_list_tag;		/* TexList area tag		    */
    u32 tex_list_header_size;	/* The number of bytes in TexListHeader area 	    */
    u32 tex_list_size;		/* The number of bytes in TexList area		    */
    u32 tex_num;		/* Total number of Tex areas described in TexList    */
    u32 nin_ext_blk_size;		/* Nintendo Extension data block   (bytes) */
    u32 usr_ext_blk_size;		/* User Extension data block (bytes) */
    u32 *tex_num_byte;	/* The number of bytes in each Tex area  */
} NisTexListHeader;

/*---- TexDataArea ----*/
/* Data when TEX_ANIM_OFF is specified  */
typedef struct _NisTexDataAnimOff
{
    u32 tex_img_width;	/* The number of texels in texture image data width    	*/
    u32 tex_img_height;	/* The number of texels in texture image data height   	*/
    u32 tex_tile_width;	/* The number of texels in the width of the portion that is used */
    u32 tex_tile_height;/* The number of texels in the height of the portion that is used*/
    u32 tex_offset_x;	/* X coordinate of upper left texel of the portion that is used */
    u32 tex_offset_y;	/* Y coordinate of upper left texel of the portion that is used */
    u32 tex_img_index;	/* Index number in TexImgList  	*/
} NisTexDataAnimOff;

/* When texture animation is done  
   (when specifying TEX_ANIM FLIPBOOK, TEX_ANIM_FLIPBOOK_KEY, TEX_ANIM_SCROLL_OFFSET,
   TEX_ANIM_SCROLL_OFFSET_KEY, TEX_ANIM_SCROLL_SCALE, 
   TEX_ANIM_SCROLL_SCALE_KEY) */
typedef struct _NisTexDataAnimOn
{
    u32 tex_img_width;	/* The number of texels in texture image data width    */
    u32 tex_img_height;	/* The number of texels in texture image data height   */
    u32 tex_tile_scale_num; 
    u32	tex_tile_offset_num;
    u32	tex_tile_img_num;
    u32	*tex_tile_scale_key;
    u32	*tex_tile_width;
    u32	*tex_tile_height;
    u32	*tex_tile_offset_key;
    u32	*tex_tile_offset_x;
    u32	*tex_tile_offset_y;
    u32	*tex_tile_img_key;
    u32	*tex_tile_img_index;
} NisTexDataAnimOn;

/*---- Tex area  ----*/	
typedef union _NisTexData
{
    NisTexDataAnimOff	anim_off;
    NisTexDataAnimOn	anim_on;
} NisTexData;

typedef struct _NisTex
{
    u32 tex_tag;	 /* Tex area tag		    */
    u32 this_tex_index;	 /* Index number of this Tex area  */
    u32 tex_header_size; /* The number of bytes in this TexHeader area    */
    u32 tex_size;	 /* The number of bytes in this Tex area    			    */
    u32 tex_name_index;	 /* Index number in NameList that describes Tex name   	    */
    u32 tex_type;	 /* Texture format			    */
    u32 tex_wrap_s;	 /* Specification of S direction  texture wrapping   */
    u32 tex_wrap_t;	 /* Specification of T direction texture wrapping    */
    u32 tex_anim;	 /* Setting of texture animaiton   	    */
    u32 tex_data_area_size;	/* The number of bytes in exDataArea portion  		    */
    u32 tex_anim_frame_rate;	/* Frame rate of texture animation    */
    u32 nin_ext_blk_size;	/* Nintendo Extension data block   (bytes) */
    u32 usr_ext_blk_size;	/* User Extension data block (bytes) */
    NisTexData	*texdata;
    u32	*n_ext;			/* Nintendo Extension data block     */
    u32	*u_ext;			/* User Extension data block   */
    NisTexExt *n2;		/* extending in NIFF2.0 */
} NisTex;

typedef	struct _NisTexList
{		
    NisTexListHeader   *h;  /* List header		*/
    NisTex	    *tex;   /* Array of Tex area  		*/
    u32	*n_ext;		    /* Nintendo Extension data block     */
    u32	*u_ext;		    /* User Extension data block   */
} NisTexList;

/*------------------------ TexImgList ------------------------------*/
typedef struct _NisTeximgListHeader
{
    u32 tex_img_list_tag;	    /* TexImgList tag		*/
    u32 tex_img_list_header_size;   /* The number of bytes in TexImgListHeader area   */
    u32 tex_img_list_size;	    /* The number of bytes in whole TexImgList area     */
    u32 tex_img_num;		    /* The number of TexImg areas			*/
    u32 nin_ext_blk_size;	    /* Nintendo Extension data block   (bytes)   */
    u32 usr_ext_blk_size;	    /* User Extension data block (bytes)   */
    u32	*tex_img_num_byte;
} NisTeximgListHeader;

/*---- TexImg area ----*/
typedef struct _NisTeximg
{
    u32 tex_img_tag;		/* TexImg area tag		*/
    u32	this_tex_img_index;	/* Index number of this TexImg area   	*/
    u32 tex_img_header_size;	/* The number of bytes in TexImgHeader area  		*/
    u32 tex_img_size;		/* The number of bytes in this TexImg area  	*/
    u32 nin_ext_blk_size;	/* Nintendo Extension data block   (bytes) */
    u32 usr_ext_blk_size;	/* User Extension data block (bytes) */
    u8  *teximgdata;		/* Texture image char->u8 for win */
    u32	*n_ext;			/* Nintendo Extension data block     */
    u32	*u_ext;			/* User Extension data block   */
    NisTeximgExt    *n2;	/* extending in NIFF2.0 */
} NisTeximg;

typedef struct _NisTeximgList
{
    NisTeximgListHeader *h;	/* List header	*/
    NisTeximg		*teximg;/* Array of TexImg area  	*/
    u32	*n_ext;			/* Nintendo Extension data block     */
    u32	*u_ext;			/* User Extension data block   */
} NisTeximgList;

/*------------------------- AnimList ---------------------------*/
typedef struct _NisAnimListHeader
{
    u32 anim_list_tag;		/* AnimList area tag	    */
    u32 anim_list_header_size;	/* The number of bytes in AnimListHeader area    */
    u32 anim_list_size;		/* The number of bytes in AnimList area  	    */
    u32 anim_group_num;	    /* Total number of AnimGroup areas described in AnimList    */
    u32 nin_ext_blk_size;	/* Nintendo Extension data block   (bytes) */
    u32 usr_ext_blk_size;	/* User Extension data block (bytes) */
    u32 *anim_group_num_byte;	/* The number of bytes of corresponding AnimGroup   */
} NisAnimListHeader;

/*---- Anim area ----*/
typedef struct _NisAnimStatic
{
    u32 anim_tag;	    /* Anim area tag		*/
    u32 this_anim_index;    /* Index number of this Anim area  */
    u32 anim_size;	    /* The number of bytes in this Anim area  		*/
    float translate_x;	    /* X axis directional translation		*/
    float translate_y;	    /* Y axis directional translation		*/
    float translate_z;	    /* Z axis directional translation		*/
    float rotate_axis_x;    /* X component of rotating axis 			*/
    float rotate_axis_y;    /* Y component of rotating axis 			*/
    float rotate_axis_z;    /* Z component of rotating axis 			*/
    u32	  rotate_expand_flag;/* Expansion flag			*/
    float scale_x;	    /* X axis directional scale value 		*/
    float scale_y;	    /* Y axis directional scale value 		*/
    float scale_z;	    /* Z axis directional scale value 		*/
} NisAnimStatic;

typedef NisAnimStatic NisAnimFull;

typedef struct _NisAnimKey
{
    u32 anim_tag;	    /* Anim area tag		*/
    u32 this_anim_index;    /* Index number of this Anim area   */
    u32 anim_size;	    /* The number of bytes in this Anim area  		*/
    u32 key;		    /* Frame value of current key frame 	    */
    u32 next_key;	    /* Frame value of next key frame 	    */
    u32 interpolation_type; /* Interpolation type between this key and the next     */
    float translate_x;	    /* X axis directional translation		    */
    float translate_y;	    /* Y axis directional translation		    */
    float translate_z;	    /* Z axis directional translaiton		    */
    float rotate_axis_x;    /* X component of rotating axis    */
    float rotate_axis_y;    /* Y component of rotating axis    */
    float rotate_axis_z;    /* Z component of rotating axis    */
    u32	  rotate_expand_flag; /* Expansion flag	    */
    float scale_x;	    /* X axis directional scale value  */
    float scale_y;	    /* Y axis directional scale value  */
    float scale_z;	    /* Z axis directional scale value  */
} NisAnimKey;

typedef struct _NisAnimBillboard
{
    u32 anim_tag;	  /* Anim area tag		*/
    u32 this_anim_index;  /* Index number of this Anim area  	*/
    u32 anim_size;	  /* Size of this Anim area  		*/
    u32 lookat_obj_index; /* Specify index number in ObjList	*/
    u32 upper_obj_index;  /* Specify index number in ObjList	*/
} NisAnimBillboard;

typedef union _NisAnim
{
    NisAnimStatic   anim_static;
    NisAnimFull	    full;
    NisAnimKey	    key;
    NisAnimBillboard billboard;
} NisAnim; /* Define structure that complies with anim_type */

/*---- AnimGroup area ----*/
typedef struct _NisAnimGroup
{
    u32 anim_group_tag;		/* AnimGroup area tag		*/
    u32 this_anim_group_index;	/* Index number of this AnimGroup 	*/
    u32 anim_group_header_size;	/* The number of bytes in this AnimGroupHeader area    */
    u32	anim_group_size;	/* The number of bytes in this AnimGroup area	*/
    u32 anim_name_index;    /* Index number in NameList that describes AnimGroup name    */
    u32 anim_type;	    /* Animation type		*/
    u32 frame_rate;	    /* Frame rate of animation 	*/
    u32 anim_num;	    /* Anim area number			*/
    u32 anim_loop;	    /* The number of loops of animation  	*/
    u32	anim_rot_mtx_order;
    u32 nin_ext_blk_size;	/* Nintendo Extension data block   (bytes) */
    u32 usr_ext_blk_size;	/* User Extension data block (bytes) */
    NisAnim	*anim;
    u32	*n_ext;			/* Nintendo Extension data block     */
    u32	*u_ext;			/* User Extension data block   */
    NisAnimGroupExt *n2;	/* extending in NIFF2.0 */
} NisAnimGroup;

typedef	struct _NisAnimList
{		
    NisAnimListHeader  *h;  /* List header		*/
    NisAnimGroup   *animg;  /* Array of Anim area  		*/
    u32	*n_ext;		    /* Nintendo Extension data block     */
    u32	*u_ext;		    /* User Extension data block   */
} NisAnimList;

/*--------------------- CollList ------------------------*/
typedef struct _NisCollListHeader
{
    u32 coll_list_tag;		/* CollList area tag	    */
    u32 coll_list_header_size;	/* The number of bytes in CollListHeader area    */
    u32 coll_list_size;		/* The number of bytes in CollList area 	    */
    u32 coll_group_num;		/* Total number of CollGroup areas in CollList */
    u32 nin_ext_blk_size;	/* Nintendo Extension data block   (bytes) */
    u32 usr_ext_blk_size;	/* User Extension data block (bytes) */
    u32 *coll_group_num_byte;	/* The number of bytes of corresponding CollGroup   */
} NisCollListHeader;

/*---- CollData area ----*/ /* Data structure varies depending upon coll_type. */
typedef struct _NisCollTerrain
{
    u32 coll_data_tag;		/* CollData area tag		*/
    u32 this_coll_data_index;	/* Index number of this CollData area  */
    u32 coll_data_size;		/* The number of bytes in this CollData area  		*/
    u32 x_subdivide;	  /* X directional resolution of whole geographical data */
    u32 z_subdivide;	  /* Z directional resolution of whole geographical data */
    u32	shape_list_index; /* Index number of shape data used for geographical data */
} NisCollTerrain;

typedef struct _NisCollPoint
{  
    u32	  coll_data_tag;	/* CollData area tag	*/
    u32   this_coll_data_index;	/* Index number of this CollData area  */
    u32   coll_data_size;	/* The number of bytes in this CollData area    */
    float coll_point_x;		/* X coordinate of Collision point  		*/
    float coll_point_y;		/* Y coordinate of Collision point 		*/
    float coll_point_z;		/* Z coordinate of Collision point 		*/	
} NisCollPoint;

typedef struct _NisCollCircle
{  
    u32	  coll_data_tag;	/* CollData area tag		*/
    u32   this_coll_data_index;	/* Index number of this CollData area  */
    u32   coll_data_size;	/* The number of bytes in this CollData area 		*/
    float center_x;		/* X coordinate of center of circle 		*/
    float center_y;		/* Y coordinate of center of circle		*/
    float center_z;		/* Z coordinate of center of circle		*/
    float normal_x;		/* X coordinate of normal vector of circle    */
    float normal_y;		/* Y coordinate of normal vector of circle    */
    float normal_z;		/* Z coordinate of normal vector of circle    */
    float radius;		/* Radius of circle		    */			
} NisCollCircle;

typedef struct _NisCollSphere
{  
    u32	  coll_data_tag;	/* CollData area tag		*/
    u32   this_coll_data_index;	/* Index number of this CollData area  */
    u32   coll_data_size;	/* The number of bytes in this CollData area   */
    float center_x;		/* X coordinate of center of sphere		*/
    float center_y;		/* Y coordinate of center of sphere		*/
    float center_z;		/* Z coordinate of center of sphere		*/
    float radius;		/* Radius of sphere			*/
} NisCollSphere;

typedef struct _NisCollCylinder
{  
    u32	  coll_data_tag;	/* CollData area tag		*/
    u32   this_coll_data_index;	/* Index number of this CollData area   */
    u32   coll_data_size;	/* The number of bytes in this CollData area   	*/
    float center_x;		/* X coordinate of center of base circle of cylinder    */
    float center_y;		/* Y coordinate of center of base circle of cylinder     */
    float center_z;		/* Z coordinate of center of base circle of cylinder     */
    float radius;		/* Radius of cylinder			 */
    float height;		/* Height of cylinder			 */		
} NisCollCylinder;

typedef struct _NisCollBox
{  
    u32	  coll_data_tag;	/* CollData area tag	*/
    u32   this_coll_data_index;	/* Index number of this CollData area   */
    u32   coll_data_size;	/* The number of bytes in this CollData area   		*/	
    float center_x;		/* X coordinate of center of cube 	    */
    float center_y;		/* Y coordinate of center of cube 	    */
    float center_z;		/* Z coordinate of center of cube 	    */
    float length_x;		/* Length of X axis direction of cube 	*/
    float length_y;		/* Length of Y axis direction of cube 	*/
    float length_z;		/* Length of X axis direction of cube  	*/
} NisCollBox;

typedef union _NisCollData
{
    NisCollTerrain  terrain;
    NisCollPoint    point;
    NisCollCircle   circle;
    NisCollSphere   sphere;
    NisCollCylinder cylinder;
    NisCollBox	    box;
} NisCollData; /* Define structure that complies with coll_type   */

/*---- Coll area ----*/ 
typedef struct _NisColl
{
    u32 coll_tag;	  /* Coll area tag	    */
    u32 this_coll_index;  /* Index number of this Coll area   	    */
    u32 coll_header_size; /* The number of bytes in this CollHeader  		    */
    u32 coll_size;	  /* The number of bytes in this Coll area  		    */
    u32 coll_name_index;  /* Index number in NameList that describes CollGroup name   */
    u32 coll_type;	  /* Collision type			    */ 
    NisCollData	    *colldata;
} NisColl;

/*---- CollGroup area ----*/
typedef struct _NisCollGroup
{
    u32 coll_group_tag;		/* CollGroup area tag	    */
    u32 this_coll_group_index;	/* Index number of this CollGroup   */
    u32 coll_group_header_size;	/* The number of bytes in this CollGroupHeader    */
    u32	coll_group_size;	/* The number of bytes in this CollGroup area     */
    u32 coll_group_name_index;	/* Index number of CollGroup name       */
    u32 coll_num;		/* Coll area number  			    */
    u32 nin_ext_blk_size;	/* Nintendo Extension data block   (bytes) */
    u32 usr_ext_blk_size;	/* User Extension data block (bytes) */
    u32		    *coll_num_byte;
    NisColl	    *coll;
    u32	*n_ext;			/* Nintendo Extension data block     */
    u32	*u_ext;			/* User Extension data block   */
} NisCollGroup;

typedef	struct _NisCollList
{		
    NisCollListHeader  *h;  /* List header	*/
    NisCollGroup   *collg;  /* Array of CollGroup area  */
    u32	*n_ext;		    /* Nintendo Extension data block     */
    u32	*u_ext;		    /* User Extension data block   */
} NisCollList;

/*-------------------- SwitchList ------------------------*/
typedef struct _NisSwitchListHeader
{
    u32 switch_list_tag;	    /* SwitchList tag */
    u32 switch_list_header_size;    /* The number of bytes in SwitchListHeader area     */
    u32 switch_list_size;	    /* The number of bytes in this SwitchList area         */
    u32 switch_num;		    /* Switch area number    */
    u32 nin_ext_blk_size;	    /* Nintendo Extension data block   (bytes) */
    u32 usr_ext_blk_size;	    /* User Extension data block (bytes) */
    u32 *switch_num_byte;	/* The number of bytes in corresponding Switch area   */
} NisSwitchListHeader;

/*---- Switch area ----*/
typedef struct _NisSwitch
{
    u32 switch_tag;	    /* Switch area tag*/
    u32 this_switch_index;  /* Index number of this Switch area    */
    u32 switch_size;	    /* The number of bytes in this Switch area   */
    u32 link_list_type;	    /* Tag that shows a list to which this Switch node links       */
    u32 default_link_index; /* Index of node that links by default     */
    u32 case_node_num;	    /* The number of nodes that have branch conditions   */
    u32 switch_condition;   /* Conditions when branching   */
    u32 nin_ext_blk_size;   /* Nintendo Extension data block   (bytes) */
    u32 usr_ext_blk_size;   /* User Extension data block (bytes) */
    u32 *case_val;	    /* Constant formula for branch condition    */
    u32 *case_dest_index;   /* Destination of branch when corresponding conditions are met.  */
    u32	*n_ext;		    /* Nintendo Extension data block     */
    u32	*u_ext;		    /* User Extension data block   */
} NisSwitch;

/*---- SwitchList ----*/
typedef struct _NisSwitchList
{
    NisSwitchListHeader	*h;
    NisSwitch		*nisswitch; 
    u32	*n_ext;		/* Nintendo Extension data block     */
    u32	*u_ext;		/* User Extension data block   */
} NisSwitchList;

/*---- NameList ----*/
typedef struct _NisNameListHeader
{
    u32 name_list_tag;		/* NameList area tag	  */
    u32 name_list_header_size;	/* The number of bytes in NameListHeader area  */
    u32 name_list_size;		/* The number of bytes in NameList 		  */
    u32 name_num;		/* Name area number			  */
    u32 nin_ext_blk_size;	/* Nintendo Extension data block   (bytes) */
    u32 usr_ext_blk_size;	/* User Extension data block (bytes) */
    u32	*name_num_byte	;	/* The number of bytes in each Name area    */
} NisNameListHeader; 

/*---- Name area ----*/
typedef struct _NisName
{
    u32 name_tag;	    /* Name area tag		*/
    u32 this_name_index;    /* Index number of this Name area   */
    u32 name_header_size;   /* The number of bytes in NameHeader 		*/
    u32 name_size;	    /* The number of bytes in this Name area		*/
    u32 *node_name; /* Describe node name with ASCII characters   */
} NisName;

typedef	struct _NisNameList
{		
    NisNameListHeader  *h;	/* List header */
    NisName	 *nisname;	/* Array of Name area    	*/
    u32	*n_ext;			/* Nintendo Extension data block */
    u32	*u_ext;			/* User Extension data block  */
} NisNameList;

typedef char	NisFilename;

/*-------------------- NIS1.0 whole  ------------------------*/
typedef struct _Nis 
{
    NisFilename	    *filename;	/* Set to keep an open file name though it is not mentioned in the NIFF specification. Used for niWriteNb(). */
    NisFileHeader   *fh;
    NisSceneList    *scenel;
    NisEnvList	    *envl;
    NisCamList	    *caml;
    NisLightList    *lightl;
    NisObjList	    *objl;
    NisShapeList    *shapel;
    NisVtxList	    *vtxl;
    NisTriList	    *tril;
    NisColorList    *colorl;
    NisVectorList   *vectorl;
    NisStList	    *stl;
    NisPartList	    *partl;
    NisMatList	    *matl;
    NisTexList	    *texl;
    NisTeximgList   *teximgl;
    NisAnimList	    *animl;
    NisCollList	    *colll;
    NisSwitchList   *switchl;
    NisNameList	    *namel; 
/* extending in NIFF2.0 */
    Nis2Lists    *n2;
} Nis;

#endif /* ! _NIS_H_ */