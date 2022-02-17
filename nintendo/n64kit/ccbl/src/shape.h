
/* niff to gfx converter v1.3 */

/* ============================================================
          Header Area
 ============================================================ */

#ifndef __ND_COMMONS__
#define __ND_COMMONS__

/* ------------------ macros */

#define SEGTOP(sno) ((u32)(sno)<<24)
#define SEGADRS(sno,adrs) (SEGTOP(sno)|((u32)(adrs)&0x00ffffff))
/* ------------------ geometric animation */

enum{
  /* NDR_ANIM_CHANNEL.kind */
  NDC_ANIMKIND_TRS_X  = 0x00,
  NDC_ANIMKIND_TRS_Y  = 0x01,
  NDC_ANIMKIND_TRS_Z  = 0x02,
  NDC_ANIMKIND_ROT_X  = 0x03,
  NDC_ANIMKIND_ROT_Y  = 0x04,
  NDC_ANIMKIND_ROT_Z  = 0x05,
  NDC_ANIMKIND_SCL_X  = 0x06,
  NDC_ANIMKIND_SCL_Y  = 0x07,
  NDC_ANIMKIND_SCL_Z  = 0x08
};

typedef struct {
  u16 kind;
  s16 start;
  s16 end;
  s16 nkey;
  s16 *key;
  float *value;
} NDR_ANIM_CHANNEL;

typedef struct {
  NDR_ANIM_CHANNEL *chlist;
  u16 nch;
  u16 total;
} NDR_ANIM;

/* ------------------ shape */

typedef struct{
  s16 *key;
  s16 *tblno;
  u16 nkey;
  u16 nelem;
} NDR_DEFORM;

typedef struct{
  Gfx *gfx;
  Vtx *vtx;
  u16 nvtx;
  u16 vtxsegno;

  /* using texture segment */
  u8 *img;
  u16 *tlut;
  u16 imgsegno, tlutsegno;

  /* shape deform data link */
  s16 *shaperef;
  NDR_DEFORM *vtx_deform;
  NDR_DEFORM *vtxcol_deform;
  NDR_DEFORM *vtxnv_deform;

} NDR_SHAPE;

/* ------------------ object */

enum{
  /* object types */
  NDC_TYPE_NULL = 0x01,
  NDC_TYPE_3D = 0x02,
  NDC_TYPE_BILLBOARD = 0x03,

  /* ColorCombine Mode */
  NDC_CC_COMBINED = 0x00,
  NDC_CC_TEX0 = 0x01,
  NDC_CC_TEX1 = 0x02,
  NDC_CC_PRIMITIVE = 0x03,
  NDC_CC_SHADE = 0x04,
  NDC_CC_ENV = 0x05,
  NDC_CC_KEY_CENTER = 0x10,
  NDC_CC_KEY_SCALE = 0x11,
  NDC_CC_COMBINED_ALPHA = 0x06,
  NDC_CC_TEX0_ALPHA = 0x07,
  NDC_CC_TEX1_ALPHA = 0x08,
  NDC_CC_PRIMITIVE_ALPHA = 0x09,
  NDC_CC_SHADE_ALPHA = 0x0a,
  NDC_CC_ENV_ALPHA = 0x0b,
  NDC_CC_LOD = 0x0c,
  NDC_CC_PRIM_LOD = 0x0d,
  NDC_CC_NOISE = 0x12,
  NDC_CC_K4 = 0x14,
  NDC_CC_K5 = 0x15,
  NDC_CC_1 = 0x0e,
  NDC_CC_0 = 0x0f,

  /* Render Mode(complexed) */
  NDC_RM_AA_EN                     = 0x80000000,
  NDC_RM_Z_CMP                     = 0x40000000,
  NDC_RM_Z_UPD                     = 0x20000000,
  NDC_RM_IM_RD                     = 0x10000000,
  NDC_RM_CVG_DST                   = 0x0c000000,
    NDC_RM_CVG_DST_CLAMP           = 0x00000000,
    NDC_RM_CVG_DST_WRAP            = 0x04000000,
    NDC_RM_CVG_DST_FULL            = 0x08000000,
    NDC_RM_CVG_DST_SAVE            = 0x0c000000,
  NDC_RM_CLR_ON_CVG                = 0x02000000,
  NDC_RM_CVG_X_ALPHA               = 0x01000000,
  NDC_RM_ALPHA_CVG_SEL             = 0x00800000,
  NDC_RM_FORCE_BL                  = 0x00400000,
  NDC_RM_ZMODE                     = 0x00300000,
    NDC_RM_ZMODE_OPA               = 0x00000000,
    NDC_RM_ZMODE_INTER             = 0x00100000,
    NDC_RM_ZMODE_XLU               = 0x00200000,
    NDC_RM_ZMODE_DEC               = 0x00300000,
  NDC_RM_ALPHA_COMPARE             = 0x000c0000,
    NDC_RM_ALPHA_COMPARE_NONE      = 0x00000000,
    NDC_RM_ALPHA_COMPARE_THRESHOLD = 0x00040000,
    NDC_RM_ALPHA_COMPARE_DITHER    = 0x00080000,
  NDC_RM_DITHER_ALPHA              = 0x00030000,
    NDC_RM_DITHER_ALPHA_PATTERN    = 0x00000000,
    NDC_RM_DITHER_ALPHA_NOPATTERN  = 0x00010000,
    NDC_RM_DITHER_ALPHA_NOISE      = 0x00020000,
    NDC_RM_DITHER_ALPHA_DISABLE    = 0x00030000,
  NDC_RM_BLENDER_MUX0              = 0x0000ff00,
  NDC_RM_BLENDER_MUX1              = 0x000000ff,

  /* NDR_OBJ.regflag(bit assign) */
  NDC_REGF_2CYC        = 0x4000
};

typedef struct{
  float tx, ty, tz;
  float rx, ry, rz;
  float sx, sy, sz;
} TRX;

typedef struct ndr_objTag{

  /* object propaties */
  u16 type, gid;
  u32 prio;
  TRX trx;

  /* resourse index */
  s16 shape;

  /* RSP, RDP status register setting */
  u16 regflag;
  u32 geommode;
  u32 rdmode;
  u32 primcol;
  u8 cc1[8], cc2[8];

  /* geometric animation setting */
  s16 geom_anim;
  u16 loop;
  u16 framerate;
  u32 order;

  /* children links */
  s16 bb_obj[2];
  u16 nchild;
  s16 *child;

} NDR_OBJ;

/* ------------------ scene */

typedef struct{
  TRX trx;
  u16 objno;
} NDR_SCN_INST_OBJ;

typedef struct{
  int type;
  u32 color;
  float x, y, z;
  float a1,a2;
} NDR_SCN_LIGHT;

typedef struct{
  struct{
    u16 fog_near, fog_far;
    u8 r,g,b,a;
  }fog;
  struct{
    u32 mode;
    float fovy, aspect, scale;
    u16 top, bottom, left, right, cam_near, cam_far;
    u16 eye_inst, upper_inst, lookat_inst;
  }cam;
  struct{
    u32 amb_color;
    int nlight;
    NDR_SCN_LIGHT *light;
  }light;
  u16 fill_col, fill_depth;
  NDR_SCN_INST_OBJ *entryobj;
  u16 nentobj;
} NDR_SCENE;

typedef struct{
  NDR_SCENE *scene;
  float convert_scale;

  NDR_OBJ **obj;
  NDR_SHAPE **shape;
  NDR_ANIM **anim;
  s16 **rawvtx;
  u32 **rawvtxcol;
  s8 **rawvtxnv;

  u16 nobj;
  u16 nshape;
  u16 nanim;
  u16 nrawvtx;
  u16 nrawvtxcol;
  u16 nrawvtxnv;
} NDR_RESINFO;

#endif    /* #ifndef __ND_COMMONS__ */
