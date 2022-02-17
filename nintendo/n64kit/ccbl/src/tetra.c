#include "mdl.h"
extern NDR_RESINFO resinfo_tetra;
static NDR_RESINFO *ndr = &resinfo_tetra;
static Gfx _tetra_aligner0[] = { gsSPEndDisplayList() };

static Gfx _tetra_aligner1[] = { gsSPEndDisplayList() };

/* ============================================================
          Vtx
 ============================================================ */
static Vtx vtx_Shape_of___POLYHEDRON_8_[] = {
  {     0,   200,     0,0, 0x03ff,0x0dd5, 0x00,0x7f,0x00,0xff }, /*     0 */
  {     0,   -66,   188,0, 0xfc31,0xfe36, 0x00,0xd6,0x77,0xff }, /*     1 */
  {   163,   -66,   -94,0, 0x0bcf,0xfe36, 0x67,0xd6,0xc5,0xff }, /*     2 */
  {     0,   200,     0,0, 0x0400,0x0dd5, 0x00,0x7f,0x00,0xff }, /*     3 */
  {  -163,   -66,   -94,0, 0xfc31,0xfe36, 0x99,0xd6,0xc5,0xff }, /*     4 */
  {     0,   -66,   188,0, 0x0bcf,0xfe36, 0x00,0xd6,0x77,0xff }, /*     5 */
  {   163,   -66,   -94,0, 0xfc31,0xfe36, 0x67,0xd6,0xc5,0xff }, /*     6 */
  {  -163,   -66,   -94,0, 0x0bcf,0xfe36, 0x99,0xd6,0xc5,0xff }, /*     7 */
  {     0,   -66,   188,0, 0x0400,0x0800, 0x00,0xd6,0x77,0xff }, /*     8 */
  {  -163,   -66,   -94,0, 0x0000,0x0000, 0x99,0xd6,0xc5,0xff }, /*     9 */
  {   163,   -66,   -94,0, 0x0800,0x0000, 0x67,0xd6,0xc5,0xff }, /*    10 */
};

/* ============================================================
          Gfx
 ============================================================ */
static Gfx gfx_Shape_of___POLYHEDRON_8_[] = {
#if 0
  gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_OFF),
  gsSPSetGeometryMode( G_SHADE|G_SHADING_SMOOTH ),
  gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
  gsDPSetTextureLUT( G_TT_NONE ),
  gsDPLoadMultiBlock( SEGADRS(6,0), 0, 0,
    G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, 0,
    2, 2, 5, 5, 0, 0 ),
#endif
  gsSPVertex( SEGADRS(5, 0), 11, 0 ),
  gsSP2Triangles(  0,  1,  2,  0,  3,  4,  5,  0),
  gsSP2Triangles(  3,  6,  7,  0,  8,  9, 10,  0),
  gsSPEndDisplayList(),
};

/* ============================================================
          Shape Structure
 ============================================================ */
static NDR_SHAPE shape_Shape_of___POLYHEDRON_8_ = {
  gfx_Shape_of___POLYHEDRON_8_,
  vtx_Shape_of___POLYHEDRON_8_, 11, 5,
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
static NDR_SHAPE *shapelist_tetra[] = {
  &shape_Shape_of___POLYHEDRON_8_,
};

/* ############################################################
          Resource Information
 ############################################################ */
NDR_RESINFO resinfo_tetra={
  NULL,
  20.000000,
  NULL,
  shapelist_tetra,
  NULL,
  NULL,
  NULL,
  NULL,
  0, 1, 0, 0, 0, 0
};

