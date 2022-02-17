#include "mdl.h"
extern NDR_RESINFO resinfo_xy_yz;
static NDR_RESINFO *ndr = &resinfo_xy_yz;
static Gfx _xy_yz_aligner0[] = { gsSPEndDisplayList() };

static Gfx _xy_yz_aligner1[] = { gsSPEndDisplayList() };

/* ============================================================
          Vtx
 ============================================================ */
static Vtx vtx_Shape_of___POLYHEDRON_206_[] = {
  {     0,  -200,  -200,0, 0x0800,0x0000, 0x00,0xa7,0xa7,0xff }, /*     0 */
  {     0,   200,   200,0, 0x0000,0x0800, 0x00,0x59,0x59,0xff }, /*     1 */
  {     0,  -200,   200,0, 0x0000,0x0000, 0x00,0xa7,0x59,0xff }, /*     2 */
  {     0,   200,  -200,0, 0x0800,0x0800, 0x00,0x59,0xa7,0xff }, /*     3 */
};

/* ============================================================
          Gfx
 ============================================================ */
static Gfx gfx_Shape_of___POLYHEDRON_206_[] = {
  gsSPVertex( SEGADRS(5, 0), 4, 0 ),
  gsSP2Triangles(  0,  1,  2,  0,  0,  3,  1,  0),
  gsSPEndDisplayList(),
};

/* ============================================================
          Shape Structure
 ============================================================ */
static NDR_SHAPE shape_Shape_of___POLYHEDRON_206_ = {
  gfx_Shape_of___POLYHEDRON_206_,
  vtx_Shape_of___POLYHEDRON_206_, 4, 5,
  NULL,
  NULL,
  6, 7,
  NULL,
  NULL,
  NULL,
  NULL
};

static Gfx _xy_yz_aligner2[] = { gsSPEndDisplayList() };

/* ============================================================
          Vtx
 ============================================================ */
static Vtx vtx_Shape_of___POLYHEDRON_211_[] = {
  {   200,   200,     0,0, 0x0800,0x0800, 0x59,0x59,0x00,0xff }, /*     0 */
  {  -200,  -200,     0,0, 0x0000,0x0000, 0xa7,0xa7,0x00,0xff }, /*     1 */
  {   200,  -200,     0,0, 0x0800,0x0000, 0x59,0xa7,0x00,0xff }, /*     2 */
  {  -200,   200,     0,0, 0x0000,0x0800, 0xa7,0x59,0x00,0xff }, /*     3 */
};

/* ============================================================
          Gfx
 ============================================================ */
static Gfx gfx_Shape_of___POLYHEDRON_211_[] = {
  gsSPVertex( SEGADRS(5, 0), 4, 0 ),
  gsSP2Triangles(  0,  1,  2,  0,  0,  3,  1,  0),
  gsSPEndDisplayList(),
};

/* ============================================================
          Shape Structure
 ============================================================ */
static NDR_SHAPE shape_Shape_of___POLYHEDRON_211_ = {
  gfx_Shape_of___POLYHEDRON_211_,
  vtx_Shape_of___POLYHEDRON_211_, 4, 5,
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
static NDR_SHAPE *shapelist_xy_yz[] = {
  &shape_Shape_of___POLYHEDRON_206_,
  &shape_Shape_of___POLYHEDRON_211_,
};

/* ############################################################
          Resource Information
 ############################################################ */
NDR_RESINFO resinfo_xy_yz={
  NULL,
  20.000000,
  NULL,
  shapelist_xy_yz,
  NULL,
  NULL,
  NULL,
  NULL,
  0, 2, 0, 0, 0, 0
};

