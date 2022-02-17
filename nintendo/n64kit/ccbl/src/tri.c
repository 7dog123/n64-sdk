#include "mdl.h"
extern NDR_RESINFO resinfo_tri;
static NDR_RESINFO *ndr = &resinfo_tri;
static Gfx _tri_aligner0[] = { gsSPEndDisplayList() };

static Gfx _tri_aligner1[] = { gsSPEndDisplayList() };

/* ============================================================
          Vtx
 ============================================================ */
static Vtx vtx_Shape_of___POLYHEDRON_255_[] = {
  {     0,   123,     0,0, 0x03ff,0x07ff, 0x00,0x7f,0x00,0xff }, /*     0 */
  {   -96,   -68,     0,0, 0x0000,0x0000, 0x94,0xbe,0x00,0xff }, /*     1 */
  {    96,   -68,     0,0, 0x0800,0x0000, 0x6c,0xbe,0x00,0xff }, /*     2 */
};

/* ============================================================
          Gfx
 ============================================================ */
static Gfx gfx_Shape_of___POLYHEDRON_255_[] = {
  gsSPVertex( SEGADRS(5, 0), 3, 0 ),
  gsSP1Triangle(  0,  1,  2,  0),
  gsSPEndDisplayList(),
};

/* ============================================================
          Shape Structure
 ============================================================ */
static NDR_SHAPE shape_Shape_of___POLYHEDRON_255_ = {
  gfx_Shape_of___POLYHEDRON_255_,
  vtx_Shape_of___POLYHEDRON_255_, 3, 5,
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
static NDR_SHAPE *shapelist_tri[] = {
  &shape_Shape_of___POLYHEDRON_255_,
};

/* ############################################################
          Resource Information
 ############################################################ */
NDR_RESINFO resinfo_tri={
  NULL,
  20.000000,
  NULL,
  shapelist_tri,
  NULL,
  NULL,
  NULL,
  NULL,
  0, 1, 0, 0, 0, 0
};

