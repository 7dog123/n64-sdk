/*
 *	meshglobal.h
 *
 *	Definition of structures used in macros and everywhere
 *	There are also some that are not used
 *
 *  Copyright (C) 1998-1999, NINTENDO Co.,Ltd.
 *  Copyright (C) 1998-1999, MONEGI CORPORATION
 */

#ifndef	_MESH_GLOBAL_
#define	_MESH_GLOBAL_

#include	<ultra64.h>

#ifndef	NULL
#define	NULL	(void *)0
#endif

#define	M_FALSE	0
#define	M_TRUE	1

/* Definitions */

#define	PI						(3.14159265359f)
#define	DEF_WIDTH				(320)
#define	DEF_HEIGHT				(240)
#define	DEF_ASPECT				((float)DEF_WIDTH/(float)DEF_HEIGHT)
#define	DEF_DISPLAYLIST_SIZE	(4096)

#define	DEF_MAXFRAME			(3)

#define	MAX_NUM_OF_TEXTURE		(256)
#define	MAX_DISPLAYLIST_MESH	(16384)
#define	LOADMODE_BLOCK			(0)	/* Load texture in units of blocks */
#define	LOADMODE_BLOCK_ONE		(1)	/* Block. If there is a MIP map, load for each tile */
#define	LOADMODE_TILE			(2)	/* Load using tiles */
#define	CC_USE_GLOBAL			(0)
#define	CC_USE_LOCAL			(1)

	/* Presently not being used */
#define	GLOBAL_CC_PRIMITIVE					(0)
#define	GLOBAL_CC_SHADE						(1)
#define	GLOBAL_CC_MODULATEI					(2)
#define	GLOBAL_CC_MODULATEIA				(3)
#define	GLOBAL_CC_MODULATEIDECALA			(4)
#define	GLOBAL_CC_MODULATERGB				(5)
#define	GLOBAL_CC_MODULATERGBA				(6)
#define	GLOBAL_CC_MODULATERGBDECALA			(7)
#define	GLOBAL_CC_MODULATEI_PRIM			(8)
#define	GLOBAL_CC_MODULATEIA_PRIM			(9)
#define	GLOBAL_CC_MODULATEIDECALA_PRIM		(10)
#define	GLOBAL_CC_MODULATERGB_PRIM			(11)
#define	GLOBAL_CC_MODULATERGBA_PRIM			(12)
#define	GLOBAL_CC_MODULATERGBDECALA_PRIM	(13)
#define	GLOBAL_CC_DECALRGB					(14)
#define	GLOBAL_CC_DECALRGBA					(15)
#define	GLOBAL_CC_BLENDI					(16)
#define	GLOBAL_CC_BLENDIA					(17)
#define	GLOBAL_CC_BLENDIDECALA				(18)
#define	GLOBAL_CC_BLENDRGBA					(19)
#define	GLOBAL_CC_BLENDRGBDECALA			(20)
#define	GLOBAL_CC_ADDRGB					(21)
#define	GLOBAL_CC_ADDRGBDECALA				(22)
#define	GLOBAL_CC_REFLECTRGB				(23)
#define	GLOBAL_CC_REFLECTRGBDECALA			(24)
#define	GLOBAL_CC_HILITERGB					(25)
#define	GLOBAL_CC_HILITERGBA				(26)
#define	GLOBAL_CC_HILITERGBDECALA			(27)
#define	GLOBAL_CC_SHADEDECALA				(28)
#define	GLOBAL_CC_BLENDPE					(29)
#define	GLOBAL_CC_BLENDPEDECALA				(30)
#define	GLOBAL_CC_ODD_BLENDPE				(31)
#define	GLOBAL_CC_ODD_BLENDPEDECALA			(32)
#define	GLOBAL_CC_ODD_TWOCOLORTEX			(33)
#define	GLOBAL_CC_SPARSEST					(34)
#define	GLOBAL_CC_TEMPLERP					(35)
#define	GLOBAL_CC_TRILERP					(36)
#define	GLOBAL_CC_INTERFERENCE				(37)
#define	GLOBAL_CC_1CYUV2RGB					(38)
#define	GLOBAL_CC_YUV2RGB					(39)
#define	GLOBAL_CC_PASS2						(40)
#define	GLOBAL_CC_MODULATEI2				(41)
#define	GLOBAL_CC_MODULATEIA2				(42)
#define	GLOBAL_CC_MODULATERGB2				(43)
#define	GLOBAL_CC_MODULATERGBA2				(44)
#define	GLOBAL_CC_MODULATEI_PRIM2			(45)
#define	GLOBAL_CC_MODULATEIA_PRIM2			(46)
#define	GLOBAL_CC_MODULATERGB_PRIM2			(47)
#define	GLOBAL_CC_MODULATERGBA_PRIM2		(48)
#define	GLOBAL_CC_DECALRGB2					(49)
#define	GLOBAL_CC_BLENDI2					(50)
#define	GLOBAL_CC_BLENDIA2					(51)
#define	GLOBAL_CC_CHROMA_KEY2				(52)
#define	GLOBAL_CC_HILITERGB2				(53)
#define	GLOBAL_CC_HILITERGBA2				(54)
#define	GLOBAL_CC_HILITERGBDECALA2			(55)
#define	GLOBAL_CC_HILITERGBPASSA2			(56)

#define	RENDER_OPA_SURF			(0)
#define	RENDER_XLU_SURF			(1)
#define	RENDER_TEX_EDGE			(2)

#define	RENDER_AA_OFF			(0)
#define	RENDER_AA_ON			(1)
#define	RENDER_ZB_OFF			(0)
#define	RENDER_ZB_ON			(1)

#define	FOG_NOUSE				(0)
#define	FOG_USE					(1)

#define	CULL_NONE				(0)
#define	CULL_FRONT				(1)
#define	CULL_BACK				(2)
#define	CULL_BOTH				(3)


/* Structures */

typedef	struct
{
	Mtx	projection;
	Mtx	modeling;
	Mtx viewing;
		Mtx	translate;
		Mtx rotate;
		Mtx scale;
		Mtx	reverse;
} Dynamic;

typedef	union
{
	u32 color;
	struct
	{
		u8	r;
		u8	g;
		u8	b;
		u8	a;
	} rgba;
} RGBA32;

	/* Shared structure for 16bit color */
typedef	union
{
	u16	color;
	struct {
		unsigned	a:1;
		unsigned	b:5;
		unsigned	g:5;
		unsigned	r:5;
	}rgba;
	struct {
		unsigned char	i;
		unsigned char	a;
	}ia;
} RGBA16;


	/*
	 *	Set the load mode
	 */
/*	Header part    16 bytes 	*/
typedef struct {
	char	recognize[8];		/*  Recognition code    TexTvIEw	*/
	u16		num_of_texture;		/* Number of textures      	*/
	u16		num_of_palette;		/* Number of palettes           */
	u32		size_of_pixel_data;	/* Pixel size    */
} tv_file_header;

	/*  Texture, image information */
typedef	struct
{
	u16	imageX;			/* X-coordinate of loaded texture               */
	u16	imageW;			/* Width of loaded texture                      */
	s16 frameX;			/* Upper-left X-coordinate of transferred frame */
	u16 frameW;			/* Width of transferred frame                   */
	u16	imageY;			/* Y-coordinate of loaded texture               */
	u16	imageH;			/* Height of loaded texture                     */
	s16 frameY;			/* Upper-left Y-coordinate of transferred frame */
	u16 frameH;			/* Height of transferred frame                  */

	u32	loadmode;		/* Load mode   MESH_LOADMODE_*		        */
	u32	cms;			/* Horizontal clamp mode                        */
	u32	cmt;			/* Vertical clamp mode                          */

	u32	tlutMode;		/* Palette mode	G_TT_*			        */
	u16	imagePal[8];		/* Palette number 				*/

	u8	imageFmt;		/* Format 	G_IM_FMT_*			*/
	u8	imageSiz;		/* Bit depth    G_IM_SIZ_*b			*/
	u8	mipmapNum;		/* Number of MIP maps				*/
	u8	bg_flag;		/* Is there a background attribute?     	*/
	u8	boundary[4];		/* Adjust to 64-bit boundary			*/

} texture_info_image;

	/*        Texture, drawing-related part         */
typedef	struct
{
	u16	gridW;			/* Width of 2 polygons		                */
	u16	gridH;			/* Height of 2 polygons		                */
	u16	numX;			/* Number in X direction of mesh                */
	u16 numY;			/* Number in Y direction of mesh	        */
	Vtx*	vtxp;			/* Start address of vertex      		*/
	Gfx*	gfxp;			/* Start address of display list 		*/
	Gfx*	setup_gfxp;		/* Start address of Setup DisplayList   	*/
	u8	boundary[4];		/* Adjust to 64-bit boundary    		*/
} texture_info_grid;

/*	Texture-related data    240 bytes	*/
typedef	struct
{
	texture_info_image	image;
	texture_info_grid	grid;
} texture_info;


	/*	Texture-related      */
typedef	struct
{
	u32	persp;		/*	G_TP_* NONE,PERSP			*/
	u32	detail;		/*	G_TD_* CLAMP,SHARPEN,DETAIL	*/
	u32	filter;		/*	G_TF_* POINT,BILERP,AVERAGE	*/
	u32	convert;	/*	G_TC_* CONV,FILTCONV,FILT	*/
} setup_info_texture;

	/*	Color combiner-related        */
typedef	struct
{
	u32	global_local_flag;	/* Whether to make the following global or local   */
	u32	global_cc_1;		/* Combiner for 1st cycle                          */
	u32	global_cc_2;		/* Combiner for 2nd cycle                	   */
	u8	local_color_1_A;	/* Expression for changing 1st cycle's color value */
	u8	local_color_1_B;	/*    (A - B) x C + D		                   */
	u8	local_color_1_C;	/*					*/
	u8	local_color_1_D;	/*
*/
	u8	local_alpha_1_A;	/*    Expression for 1st cycle's alpha value       */
	u8	local_alpha_1_B;	/*	0,TEXEL0,PRIMITIVE,SHADE	*/
	u8	local_alpha_1_C;	/*	ENVIRONMENT,TEXEL0_ALPHA	*/
	u8	local_alpha_1_D;	/*	K4,K5				*/
	u8	local_color_2_A;	/* Expression for changing 2nd cycle's color value */
	u8	local_color_2_B;	/*					*/
	u8	local_color_2_C;	/*					*/
	u8	local_color_2_D;	/*					*/
	u8	local_alpha_2_A;	/*    Expression for 2nd cycle's alpha value       */
	u8	local_alpha_2_B;	/*	0,TEXEL0,TEXEL1,SHADE		*/
	u8	local_alpha_2_C;	/*	COMBINED,PRIMITIVE	        */
	u8	local_alpha_2_D;	/*	LOD_FRACTION		        */
	u8	boundary[4];		/* Adjust to 64-bit boundary	        */
} setup_info_color_combiner;

	/*	Blender settings	*/
typedef	struct
{
	u8	z_compare;		/*	RENDER_ZB_* ON,OFF			*/
	u8	anti_aliasing;		/*	RENDER_AA_* ON,OFF			*/
	u16	render_mode;		/*	RENDER_* OPA_SURF,XLU_SURF,TEX_EDGE	*/
	u32	alpha_compare;		/*	G_AC_* NONE,THRESHOLD,DITHER	*/
	u32	color_dither;		/*	G_CD_* MAGICSQ,BAYER,NOISE	*/
	u32	alpha_dither;		/*	G_AD_* PATTERN,NOTPATTERN,NOISE,DISABLE	*/
} setup_info_blender;

	/*	Fog-related	    */
typedef	struct
{
	u32	use_flag;		/*	Use fog flag			*/
	u32	fog_near;		/*	Fog's near-distance value	*/
	u32	fog_far;		/*	Fog's far-distance value	*/
	RGBA32	color;			/*	Fog color			*/
} setup_info_fog;

	/*	Light-related       */
typedef	struct
{
	RGBA32	ambient_color;		/* Color of ambient light		      */
	RGBA32	defuse_color[7];	/* Color of diffuse light		      */
	u8	defuse_direction[7][4];	/* Direction of diffuse light ,x,y,z,dummy    */
	u32	num_of_defuse_light;	/* Number of diffuse lights                   */
} setup_info_light;

	/*	Vertex color            */
typedef	struct
{
	RGBA32	top_left;		/* Top-left polygon color	  */
	RGBA32	top_right;		/* Top-right polygon color        */
	RGBA32	bottom_left;	        /* Bottom-left polygon color      */
	RGBA32	bottom_right;	        /* Bottom-right polygon color     */
} setup_info_vertex_color;

	/*	Other things	*/
typedef	struct
{
	u32		culling;		/*	What to do about culling	*/
	RGBA32	BG_color;			/*	Background color        	*/
	RGBA32	PRIM_color;			/*	Primitive color                 */
	RGBA32	ENV_color;			/*	Environment color       	*/
} setup_info_etc;

	/*	RSP, RCP information	*/
typedef struct
{
	setup_info_texture			texture;
	setup_info_color_combiner	combiner;
	setup_info_blender			blender;
	setup_info_fog				fog;
	setup_info_light			light;
	setup_info_vertex_color		vtxcolor;
	setup_info_etc				etc;
} setup_info;

typedef struct
{
	tv_file_header	fh;
	texture_info	ti;
	u8	fill_dummy_texture[256-(sizeof(tv_file_header)+sizeof(texture_info))];
	setup_info		si;
	u8	fill_dummy_setup[256-sizeof(setup_info)];
		/*	Dummy data to make 256 bytes	*/
} texture_viewer_header;

typedef	struct
{
	char			name[16];
	texture_info*	pti;
	RGBA16*			ppal;
	u32				palnum;
	u64*			ppixel[8];
} texture_data;

#define		TVMODE_VIEW		(0)
#define		TVMODE_MENU		(1)
#define		TASKBAR_OFF		(0)
#define		TASKBAR_ON		(1)
#define		BG_NOUSE		(0)
#define		BG_USE			(1)
#define		NAME_NOTDISP	(0)
#define		NAME_DISP		(1)

typedef	struct
{
	u32	texture_number;			/* Texture number                   */
	u32	bg_number;			/* Background number                */
	u8	tvmode;				/* For menu switching               */
	u8	bg_flag;			/* Show/hide background flag        */
	u8	task_flag;			/* Show/hide task bar flag 	    */
	u8	name_flag;			/* Show texture name flag	    */
	u16	speed;				/* Speed                            */
	u16	speed_info_disp_time;	        /* Time remaining to display speed  */
} tvModeData;

Gfx mesh_dl[3][MAX_DISPLAYLIST_MESH];
Gfx	mesh_setup_dl[3][1024];
Vtx mesh_vtx[3][4096];

texture_info	tex_inf[64];
setup_info		set_inf;
RGBA16			palette[64][256];
u64				pixel[0x200000/sizeof(u64)];
u32				num_of_texture;
texture_data	td[MAX_NUM_OF_TEXTURE];

tvModeData	tvmd;

short		center_x;
short		center_y;
short		center_z;
short		change_z;

Dynamic*	back_dynamicp;

u8			contpattern;
NUContData	contdata[4];
Gfx			glist[DEF_MAXFRAME][DEF_DISPLAYLIST_SIZE];
Dynamic		back_dynamic[DEF_MAXFRAME];


#endif	/*_MESH_GLOBAL_*/
