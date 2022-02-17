#include "mdl.h"
extern NDR_RESINFO resinfo_text;
static NDR_RESINFO *ndr = &resinfo_text;
static Gfx _text_aligner0[] = { gsSPEndDisplayList() };

static Gfx _text_aligner1[] = { gsSPEndDisplayList() };

/* ============================================================
          Vtx
 ============================================================ */
static Vtx vtx_Shape_of___POLYHEDRON_355_[] = {
  {    57,  -101,    40,0, 0x0b1a,0xf7e1, 0xdb,0xcf,0x6e,0xff }, /*     0 */
  {    72,  -155,    40,0, 0x0cfd,0xf116, 0xc3,0xaf,0x4b,0xff }, /*     1 */
  {   153,  -155,    40,0, 0x16ea,0xf116, 0x55,0xc4,0x47,0xff }, /*     2 */
  {    50,   142,    40,0, 0x0a45,0x16ea, 0x3b,0x52,0x4b,0xff }, /*     3 */
  {   -50,   142,    40,0, 0xfdbb,0x16ea, 0xc5,0x52,0x4b,0xff }, /*     4 */
  {     0,    93,    40,0, 0x0409,0x10c2, 0x00,0xf1,0x7d,0xff }, /*     5 */
  {    40,   -44,    40,0, 0x0905,0xff3a, 0xdd,0x1a,0x77,0xff }, /*     6 */
  {    -2,    80,    40,0, 0x03a7,0x0f21, 0x57,0xeb,0x59,0xff }, /*     7 */
  {  -153,  -155,    40,0, 0xf116,0xf116, 0xab,0xc4,0x47,0xff }, /*     8 */
  {    -9,    53,    40,0, 0x02c9,0x0bad, 0x56,0xe7,0x59,0xff }, /*     9 */
  {     3,    80,    40,0, 0x046a,0x0f21, 0xa9,0xeb,0x59,0xff }, /*    10 */
  {   -40,   -44,    40,0, 0xff0d,0xff3a, 0x23,0x1a,0x77,0xff }, /*    11 */
  {   -57,  -101,    40,0, 0xfce6,0xf7e1, 0x25,0xce,0x6e,0xff }, /*    12 */
  {   -73,  -155,    40,0, 0xfb00,0xf116, 0x3d,0xaf,0x4b,0xff }, /*    13 */
  {    10,    53,    40,0, 0x0548,0x0bad, 0xaa,0xe7,0x59,0xff }, /*    14 */
  {    72,  -155,   -40,0, 0x0cfd,0xf116, 0xc3,0xaf,0xb5,0xff }, /*    15 */
  {    -4,    74,    40,0, 0x0377,0x0e52, 0x57,0xeb,0x59,0xff }, /*    16 */
  {   -50,   142,   -40,0, 0xfdbb,0x16ea, 0xc5,0x52,0xb5,0xff }, /*    17 */
  {    50,   142,   -40,0, 0x0a45,0x16ea, 0x3b,0x52,0xb5,0xff }, /*    18 */
  {   153,  -155,   -40,0, 0x16ea,0xf116, 0x55,0xc4,0xb9,0xff }, /*    19 */
  {    57,  -101,   -40,0, 0x0b1a,0xf7e1, 0xdb,0xcf,0x92,0xff }, /*    20 */
  {  -153,  -155,   -40,0, 0xf116,0xf116, 0xab,0xc4,0xb9,0xff }, /*    21 */
  {     4,    74,    40,0, 0x049b,0x0e52, 0xa9,0xeb,0x59,0xff }, /*    22 */
  {   -57,  -101,   -40,0, 0xfce6,0xf7e1, 0x25,0xce,0x92,0xff }, /*    23 */
  {    -8,    58,    40,0, 0x02f1,0x0c3a, 0x57,0xe9,0x59,0xff }, /*    24 */
  {    57,  -101,    40,0, 0x0b1a,0xf7e1, 0xdb,0xcf,0x6e,0xff }, /*    25 */
  {   -40,   -44,   -40,0, 0xff0d,0xff3a, 0x23,0x1a,0x89,0xff }, /*    26 */
  {    40,   -44,   -40,0, 0x0905,0xff3a, 0xdd,0x1a,0x89,0xff }, /*    27 */
  {     0,    93,   -40,0, 0x0409,0x10c2, 0x00,0xf1,0x83,0xff }, /*    28 */
  {    -9,    53,   -40,0, 0x02c9,0x0bad, 0x56,0xe7,0xa7,0xff }, /*    29 */
  {     8,    58,    40,0, 0x0520,0x0c3a, 0xa9,0xe9,0x59,0xff }, /*    30 */
  {   153,  -155,    40,0, 0x16ea,0xf116, 0x55,0xc4,0x47,0xff }, /*    31 */
  {    50,   142,    40,0, 0x0a45,0x16ea, 0x3b,0x52,0x4b,0xff }, /*    32 */
  {     3,    80,   -40,0, 0x046a,0x0f21, 0xa9,0xeb,0xa7,0xff }, /*    33 */
  {     3,    80,    40,0, 0x046a,0x0f21, 0xa9,0xeb,0x59,0xff }, /*    34 */
  {     0,    93,    40,0, 0x0409,0x10c2, 0x00,0xf1,0x7d,0xff }, /*    35 */
  {    72,  -155,    40,0, 0x0cfd,0xf116, 0xc3,0xaf,0x4b,0xff }, /*    36 */
  {    40,   -44,    40,0, 0x0905,0xff3a, 0xdd,0x1a,0x77,0xff }, /*    37 */
  {   -40,   -44,    40,0, 0xff0d,0xff3a, 0x23,0x1a,0x77,0xff }, /*    38 */
  {    10,    53,    40,0, 0x0548,0x0bad, 0xaa,0xe7,0x59,0xff }, /*    39 */
  {     8,    58,   -40,0, 0x0520,0x0c3a, 0xa9,0xe9,0xa7,0xff }, /*    40 */
  {     4,    74,   -40,0, 0x049b,0x0e52, 0xa9,0xeb,0xa7,0xff }, /*    41 */
  {   -73,  -155,   -40,0, 0xfb00,0xf116, 0x3d,0xaf,0xb5,0xff }, /*    42 */
  {   -73,  -155,    40,0, 0xfb00,0xf116, 0x3d,0xaf,0x4b,0xff }, /*    43 */
  {    -2,    80,   -40,0, 0x03a7,0x0f21, 0x57,0xeb,0xa7,0xff }, /*    44 */
  {    -2,    80,    40,0, 0x03a7,0x0f21, 0x57,0xeb,0x59,0xff }, /*    45 */
  {    -4,    74,    40,0, 0x0377,0x0e52, 0x57,0xeb,0x59,0xff }, /*    46 */
  {    -8,    58,   -40,0, 0x02f1,0x0c3a, 0x57,0xe9,0xa7,0xff }, /*    47 */
  {    -8,    58,    40,0, 0x02f1,0x0c3a, 0x57,0xe9,0x59,0xff }, /*    48 */
  {    -9,    53,    40,0, 0x02c9,0x0bad, 0x56,0xe7,0x59,0xff }, /*    49 */
  {   -57,  -101,   -40,0, 0xfce6,0xf7e1, 0x25,0xce,0x92,0xff }, /*    50 */
  {     4,    74,    40,0, 0x049b,0x0e52, 0xa9,0xeb,0x59,0xff }, /*    51 */
  {    10,    53,   -40,0, 0x0548,0x0bad, 0xaa,0xe7,0xa7,0xff }, /*    52 */
  {   153,  -155,   -40,0, 0x16ea,0xf116, 0x55,0xc4,0xb9,0xff }, /*    53 */
  {    57,  -101,   -40,0, 0x0b1a,0xf7e1, 0xdb,0xcf,0x92,0xff }, /*    54 */
  {    40,   -44,   -40,0, 0x0905,0xff3a, 0xdd,0x1a,0x89,0xff }, /*    55 */
  {  -153,  -155,   -40,0, 0xf116,0xf116, 0xab,0xc4,0xb9,0xff }, /*    56 */
  {   -40,   -44,   -40,0, 0xff0d,0xff3a, 0x23,0x1a,0x89,0xff }, /*    57 */
  {    -4,    74,   -40,0, 0x0377,0x0e52, 0x57,0xeb,0xa7,0xff }, /*    58 */
  {    -9,    53,   -40,0, 0x02c9,0x0bad, 0x56,0xe7,0xa7,0xff }, /*    59 */
  {     3,    80,   -40,0, 0x046a,0x0f21, 0xa9,0xeb,0xa7,0xff }, /*    60 */
  {     0,    93,    40,0, 0x0409,0x10c2, 0x00,0xf1,0x7d,0xff }, /*    61 */
  {     0,    93,   -40,0, 0x0409,0x10c2, 0x00,0xf1,0x83,0xff }, /*    62 */
  {    72,  -155,   -40,0, 0x0cfd,0xf116, 0xc3,0xaf,0xb5,0xff }, /*    63 */
  {     4,    74,   -40,0, 0x049b,0x0e52, 0xa9,0xeb,0xa7,0xff }, /*    64 */
  {     3,    80,    40,0, 0x046a,0x0f21, 0xa9,0xeb,0x59,0xff }, /*    65 */
  {     8,    58,   -40,0, 0x0520,0x0c3a, 0xa9,0xe9,0xa7,0xff }, /*    66 */
  {   -50,   142,   -40,0, 0xfdbb,0x16ea, 0xc5,0x52,0xb5,0xff }, /*    67 */
  {    50,   142,   -40,0, 0x0a45,0x16ea, 0x3b,0x52,0xb5,0xff }, /*    68 */
  {    -2,    80,   -40,0, 0x03a7,0x0f21, 0x57,0xeb,0xa7,0xff }, /*    69 */
  {    -4,    74,    40,0, 0x0377,0x0e52, 0x57,0xeb,0x59,0xff }, /*    70 */
  {    -8,    58,   -40,0, 0x02f1,0x0c3a, 0x57,0xe9,0xa7,0xff }, /*    71 */
};

/* ============================================================
          Gfx
 ============================================================ */
static Gfx gfx_Shape_of___POLYHEDRON_355_[] = {
  gsSPVertex( SEGADRS(5, 0), 32, 0 ),
  gsSP2Triangles(  0,  1,  2,  0,  3,  4,  5,  0),
  gsSP2Triangles(  2,  6,  0,  0,  7,  4,  8,  0),
  gsSP2Triangles(  7,  5,  4,  0,  8,  9,  7,  0),
  gsSP2Triangles(  2,  3, 10,  0,  3,  5, 10,  0),
  gsSP2Triangles( 11, 12,  0,  0,  8, 13, 12,  0),
  gsSP2Triangles(  8, 11,  9,  0,  6, 11,  0,  0),
  gsSP2Triangles(  2, 14,  6,  0, 15,  1,  0,  0),
  gsSP2Triangles(  2, 10, 14,  0,  8, 12, 11,  0),
  gsSP2Triangles(  9, 16,  7,  0, 17,  4,  3,  0),
  gsSP2Triangles( 18,  3,  2,  0, 19,  2,  1,  0),
  gsSP2Triangles( 20,  0, 12,  0,  8,  4, 17,  0),
  gsSP2Triangles( 13,  8, 21,  0, 10, 22, 14,  0),
  gsSP2Triangles( 23, 12, 13,  0,  9, 24, 16,  0),
  gsSP2Triangles( 15, 25, 20,  0, 26, 11,  6,  0),
  gsSP2Triangles( 27,  6, 14,  0, 28,  5,  7,  0),
  gsSP2Triangles( 29,  9, 11,  0, 22, 30, 14,  0),
  gsSP1Triangle( 21,  8, 17,  0),
  gsSPVertex( SEGADRS(5, 512), 12, 0 ),
  gsSP2Triangles( 18, 31, 19,  0, 17,  0, 18,  0),
  gsSP2Triangles(  1,  2,  3,  0, 20, 12, 23,  0),
  gsSP2Triangles( 19,  4, 15,  0, 26,  5, 27,  0),
  gsSP2Triangles( 20, 26, 27,  0, 29,  6, 26,  0),
  gsSP2Triangles(  7, 30,  8,  0,  9, 22,  2,  0),
  gsSP1Triangle( 20, 23, 26,  0),
  gsSPVertex( SEGADRS(5, 704), 9, 12 ),
  gsSP2Triangles( 10, 11, 21,  0, 12, 13, 14,  0),
  gsSP2Triangles( 15, 16, 17,  0, 18, 11, 10,  0),
  gsSP1Triangle(  8, 30, 19,  0),
  gsSPVertex( SEGADRS(5, 848), 6, 21 ),
  gsSP2Triangles( 27,  7, 20,  0, 21, 22, 23,  0),
  gsSP1Triangle( 24, 25, 18,  0),
  gsSP2Triangles( 26, 14, 16,  0, 20,  7,  8,  0),
  gsSPVertex( SEGADRS(5, 944), 5, 27 ),
  gsSP2Triangles( 15, 17, 27,  0, 18, 10, 24,  0),
  gsSP1Triangle( 28, 29, 30,  0),
  gsSP2Triangles( 21, 31, 22,  0, 24, 27, 25,  0),
  gsSPVertex( SEGADRS(5, 1024), 8, 0 ),
  gsSP2Triangles(  0,  1, 28,  0,  2, 19,  9,  0),
  gsSP2Triangles( 30, 13, 12,  0, 21, 23, 20,  0),
  gsSP2Triangles(  3,  4, 30,  0, 28,  4, 21,  0),
  gsSP2Triangles( 24,  3,  5,  0, 21, 20, 28,  0),
  gsSP2Triangles(  5,  6, 26,  0, 24,  5, 27,  0),
  gsSP2Triangles( 28, 30,  4,  0, 26, 16, 15,  0),
  gsSP2Triangles( 20,  0, 28,  0, 20,  2,  0,  0),
  gsSP2Triangles(  3, 30,  5,  0,  5, 26, 27,  0),
  gsSP1Triangle( 26,  7, 27,  0),
  gsSPEndDisplayList(),
};

/* ============================================================
          Shape Structure
 ============================================================ */
static NDR_SHAPE shape_Shape_of___POLYHEDRON_355_ = {
  gfx_Shape_of___POLYHEDRON_355_,
  vtx_Shape_of___POLYHEDRON_355_, 72, 5,
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
static NDR_SHAPE *shapelist_text[] = {
  &shape_Shape_of___POLYHEDRON_355_,
};

/* ############################################################
          Resource Information
 ############################################################ */
NDR_RESINFO resinfo_text={
  NULL,
  20.000000,
  NULL,
  shapelist_text,
  NULL,
  NULL,
  NULL,
  NULL,
  0, 1, 0, 0, 0, 0
};

