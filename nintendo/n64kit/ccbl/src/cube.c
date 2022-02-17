#include "mdl.h"
extern NDR_RESINFO resinfo_cube;
static NDR_RESINFO *ndr = &resinfo_cube;
static Gfx _cube_aligner0[] = { gsSPEndDisplayList() };

static Gfx _cube_aligner1[] = { gsSPEndDisplayList() };

/* ============================================================
          Vtx
 ============================================================ */
static Vtx vtx_Shape_of___POLYHEDRON_23_[] = {
  {  -200,  -200,   200,0, 0x0000,0x0000, 0xb7,0xb7,0x49,0xff }, /*     0 */
  {   200,   200,   200,0, 0x0800,0x0800, 0x49,0x49,0x49,0xff }, /*     1 */
  {  -200,   200,   200,0, 0x0000,0x0800, 0xb7,0x49,0x49,0xff }, /*     2 */
  {   200,  -200,   200,0, 0x0800,0x0000, 0x49,0xb7,0x49,0xff }, /*     3 */
  {  -200,   200,   200,0, 0x0000,0x0000, 0xb7,0x49,0x49,0xff }, /*     4 */
  {   200,   200,   200,0, 0x0800,0x0000, 0x49,0x49,0x49,0xff }, /*     5 */
  {   200,   200,  -200,0, 0x0800,0x0800, 0x49,0x49,0xb7,0xff }, /*     6 */
  {  -200,  -200,  -200,0, 0x0000,0x0800, 0xb7,0xb7,0xb7,0xff }, /*     7 */
  {   200,  -200,   200,0, 0x0000,0x0000, 0x49,0xb7,0x49,0xff }, /*     8 */
  {   200,   200,   200,0, 0x0000,0x0800, 0x49,0x49,0x49,0xff }, /*     9 */
  {  -200,  -200,  -200,0, 0x0800,0x0000, 0xb7,0xb7,0xb7,0xff }, /*    10 */
  {   200,  -200,  -200,0, 0x0800,0x0000, 0x49,0xb7,0xb7,0xff }, /*    11 */
  {  -200,   200,  -200,0, 0x0000,0x0800, 0xb7,0x49,0xb7,0xff }, /*    12 */
  {   200,  -200,  -200,0, 0x0800,0x0800, 0x49,0xb7,0xb7,0xff }, /*    13 */
  {  -200,  -200,  -200,0, 0x0000,0x0000, 0xb7,0xb7,0xb7,0xff }, /*    14 */
  {  -200,   200,  -200,0, 0x0800,0x0800, 0xb7,0x49,0xb7,0xff }, /*    15 */
};

/* ============================================================
          Gfx
 ============================================================ */
static Gfx gfx_Shape_of___POLYHEDRON_23_[] = {
#if 0
  gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_OFF),
  gsSPSetGeometryMode( G_SHADE|G_SHADING_SMOOTH ),
  gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
  gsDPSetTextureLUT( G_TT_NONE ),
  gsDPLoadMultiBlock( SEGADRS(6,0), 0, 0,
    G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, 0,
    2, 2, 5, 5, 0, 0 ),
#endif
  gsSPVertex( SEGADRS(5, 0), 16, 0 ),
  gsSP2Triangles(  0,  1,  2,  0,  0,  3,  1,  0),
  gsSP2Triangles(  4,  5,  6,  0,  7,  3,  0,  0),
  gsSP2Triangles(  8,  6,  9,  0, 10,  0,  2,  0),
  gsSP2Triangles( 11, 12,  6,  0,  7, 13,  3,  0),
  gsSP2Triangles(  8, 11,  6,  0,  4,  6, 12,  0),
  gsSP2Triangles( 11, 14, 12,  0, 10,  2, 15,  0),
  gsSPEndDisplayList(),
};

/* ============================================================
          Shape Structure
 ============================================================ */
static NDR_SHAPE shape_Shape_of___POLYHEDRON_23_ = {
  gfx_Shape_of___POLYHEDRON_23_,
  vtx_Shape_of___POLYHEDRON_23_, 16, 5,
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
static NDR_SHAPE *shapelist_cube[] = {
  &shape_Shape_of___POLYHEDRON_23_,
};

/* ############################################################
          Resource Information
 ############################################################ */
NDR_RESINFO resinfo_cube={
  NULL,
  20.000000,
  NULL,
  shapelist_cube,
  NULL,
  NULL,
  NULL,
  NULL,
  0, 1, 0, 0, 0, 0
};

