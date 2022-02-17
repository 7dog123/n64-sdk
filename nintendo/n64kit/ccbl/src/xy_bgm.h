static Gfx _xy_bmg_aligner0[] = { gsSPEndDisplayList() };

static Gfx _xy_bmg_aligner1[] = { gsSPEndDisplayList() };

/* ============================================================
          Vtx
 ============================================================ */
static Vtx vtx_Shape_of___POLYHEDRON_23_[] = {
  {   200,   200,     0,0, 0x0000,0x0000, 0x00,0x00,0x81,0xff }, /*     0 */
  {  -200,  -200,     0,0, 0x0000,0x0000, 0xa7,0xa7,0x00,0xff }, /*     1 */
  {  -200,   200,     0,0, 0x0000,0x0000, 0xa7,0x59,0x00,0xff }, /*     2 */
  {   200,  -200,     0,0, 0x0000,0x0000, 0x59,0xa7,0x00,0xff }, /*     3 */
};

/* ============================================================
          Gfx
 ============================================================ */
static Gfx gfx_Shape_of___POLYHEDRON_23_[] = {
  gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_OFF),
  gsDPSetEnvColor(0xff, 0xa0, 0x80, 0x80),
  gsSPSetGeometryMode( G_SHADE ),
  gsDPSetCombineLERP(1, 0, ENVIRONMENT, 0, 0, 0, ENVIRONMENT, 0, 1, 0, ENVIRONMENT, 0, 0, 0, ENVIRONMENT, 0),
  gsSPVertex( SEGADRS(5, 0), 4, 0 ),
  gsSP2Triangles(  0,  1,  2,  0,  0,  3,  1,  0),
  gsSPEndDisplayList(),
};

/* ============================================================
          Shape Structure
 ============================================================ */
static NDR_SHAPE shape_Shape_of___POLYHEDRON_23_ = {
  gfx_Shape_of___POLYHEDRON_23_,
  vtx_Shape_of___POLYHEDRON_23_, 4, 5,
  NULL,
  NULL,
  6, 7,
  NULL,
  NULL,
  NULL,
  NULL
};

/* ============================================================
          Shape Structure List
 ============================================================ */
static NDR_SHAPE *shapelist_xy_bmg[] = {
  &shape_Shape_of___POLYHEDRON_23_,
};

/* ############################################################
          Resource Information
 ############################################################ */
NDR_RESINFO resinfo_xy_bgm={
  NULL,
  20.000000,
  NULL,
  shapelist_xy_bmg,
  NULL,
  NULL,
  NULL,
  NULL,
  0, 1, 0, 0, 0, 0
};

