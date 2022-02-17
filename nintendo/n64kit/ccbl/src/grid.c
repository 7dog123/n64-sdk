#include "mdl.h"
extern NDR_RESINFO resinfo_grid;
static NDR_RESINFO *ndr = &resinfo_grid;

static Gfx _grid_aligner0[] = { gsSPEndDisplayList() };

static Gfx _grid_aligner1[] = { gsSPEndDisplayList() };

/* ============================================================
          Vtx
 ============================================================ */
static Vtx vtx_Shape_of___POLYHEDRON_98_[] = {
  {  -408,   -48,  -408,0, 0xba0d,0x4df3, 0xb5,0xb9,0xb8,0xff }, /*     0 */
  {  -408,    -3,  -326,0, 0xba0d,0x3f29, 0x9a,0xb7,0xf1,0xff }, /*     1 */
  {  -326,    -3,  -408,0, 0xc8d7,0x4df3, 0xee,0xb6,0x9b,0xff }, /*     2 */
  {  -326,   166,  -326,0, 0xc8d7,0x3f29, 0xaf,0x34,0xaf,0xff }, /*     3 */
  {  -244,    36,  -408,0, 0xd7a2,0x4df3, 0x09,0xb1,0x9e,0xff }, /*     4 */
  {  -244,   261,  -326,0, 0xd7a2,0x3f29, 0x00,0x40,0x93,0xff }, /*     5 */
  {  -163,   166,  -326,0, 0xe66c,0x3f29, 0x52,0x34,0xaf,0xff }, /*     6 */
  {  -163,    -3,  -408,0, 0xe66c,0x4df3, 0x25,0xb9,0x9f,0xff }, /*     7 */
  {   -81,    -4,  -326,0, 0xf536,0x3f29, 0x6c,0x3a,0xe1,0xff }, /*     8 */
  {   -81,   -48,  -408,0, 0xf536,0x4df3, 0x68,0xd2,0xca,0xff }, /*     9 */
  {     0,  -141,  -326,0, 0x0400,0x3f29, 0x6d,0x3f,0xf5,0xff }, /*    10 */
  {  -408,    36,  -244,0, 0xba0d,0x305e, 0x9d,0xb2,0x0b,0xff }, /*    11 */
  {     0,  -109,  -408,0, 0x0400,0x4df3, 0x64,0xc5,0x31,0xff }, /*    12 */
  {    81,  -286,  -326,0, 0x12ca,0x3f29, 0x5a,0x55,0xe8,0xff }, /*    13 */
  {  -244,   381,  -244,0, 0xd7a2,0x305e, 0x00,0x7f,0x00,0xff }, /*    14 */
  {    81,  -229,  -408,0, 0x12ca,0x4df3, 0x37,0x30,0x67,0xff }, /*    15 */
  {   163,  -354,  -326,0, 0x2194,0x3f29, 0x00,0x7d,0xea,0xff }, /*    16 */
  {   163,  -288,  -408,0, 0x2194,0x4df3, 0x00,0x45,0x69,0xff }, /*    17 */
  {   -81,    39,  -244,0, 0xf536,0x305e, 0x70,0x38,0xf1,0xff }, /*    18 */
  {   244,  -229,  -408,0, 0x305e,0x4df3, 0xc9,0x30,0x67,0xff }, /*    19 */
  {   244,  -286,  -326,0, 0x305e,0x3f29, 0xa6,0x55,0xe8,0xff }, /*    20 */
  {  -326,   261,  -244,0, 0xc8d7,0x305e, 0x93,0x40,0x00,0xff }, /*    21 */
  {   326,  -109,  -408,0, 0x3f29,0x4df3, 0xa7,0xbb,0x39,0xff }, /*    22 */
  {    81,  -151,  -244,0, 0x12ca,0x305e, 0x21,0x33,0x91,0xff }, /*    23 */
  {   326,  -141,  -326,0, 0x3f29,0x3f29, 0x98,0x46,0xf4,0xff }, /*    24 */
  {   408,   -50,  -326,0, 0x4df3,0x3f29, 0x90,0xc8,0x0c,0xff }, /*    25 */
  {  -163,   261,  -244,0, 0xe66c,0x305e, 0x6d,0x40,0x00,0xff }, /*    26 */
  {   408,   -48,  -408,0, 0x4df3,0x4df3, 0x94,0xd0,0x2c,0xff }, /*    27 */
  {     0,   -76,  -244,0, 0x0400,0x305e, 0x4b,0x42,0xb3,0xff }, /*    28 */
  {   244,  -151,  -244,0, 0x305e,0x305e, 0xdf,0x33,0x91,0xff }, /*    29 */
  {   163,  -183,  -244,0, 0x2194,0x305e, 0x00,0x2e,0x8a,0xff }, /*    30 */
  {   326,   -76,  -244,0, 0x3f29,0x305e, 0xcf,0x4b,0xa7,0xff }, /*    31 */
  {  -326,   166,  -163,0, 0xc8d7,0x2194, 0xaf,0x34,0x51,0xff }, /*    32 */
  {   408,   -42,  -244,0, 0x4df3,0x305e, 0xa3,0xc0,0xc9,0xff }, /*    33 */
  {  -163,   166,  -163,0, 0xe66c,0x2194, 0x4d,0x39,0x52,0xff }, /*    34 */
  {  -408,    -3,  -163,0, 0xba0d,0x2194, 0x9e,0xba,0x27,0xff }, /*    35 */
  {  -244,   261,  -163,0, 0xd7a2,0x2194, 0x00,0x40,0x6d,0xff }, /*    36 */
  {     0,    61,  -163,0, 0x0400,0x2194, 0xe3,0x47,0x9c,0xff }, /*    37 */
  {    81,   110,  -163,0, 0x12ca,0x2194, 0xe9,0x36,0x90,0xff }, /*    38 */
  {   -81,    41,  -163,0, 0xf536,0x2194, 0x2d,0x75,0xf1,0xff }, /*    39 */
  {   163,   131,  -163,0, 0x2194,0x2194, 0x00,0x34,0x8d,0xff }, /*    40 */
  {   244,   110,  -163,0, 0x305e,0x2194, 0x17,0x36,0x90,0xff }, /*    41 */
  {   408,     0,  -163,0, 0x4df3,0x2194, 0x64,0xc7,0xcc,0xff }, /*    42 */
  {  -326,    -3,   -81,0, 0xc8d7,0x12ca, 0xd6,0x51,0x58,0xff }, /*    43 */
  {   326,    61,  -163,0, 0x3f29,0x2194, 0x2e,0x44,0xa1,0xff }, /*    44 */
  {  -244,    36,   -81,0, 0xd7a2,0x12ca, 0xf8,0x35,0x72,0xff }, /*    45 */
  {  -408,   -48,   -81,0, 0xba0d,0x12ca, 0x3a,0x6d,0x1a,0xff }, /*    46 */
  {   -81,    61,   -81,0, 0xf536,0x12ca, 0xb3,0x63,0xf5,0xff }, /*    47 */
  {  -163,    23,   -81,0, 0xe66c,0x12ca, 0xf6,0x44,0x6a,0xff }, /*    48 */
  {    81,   233,   -81,0, 0x12ca,0x12ca, 0xd3,0x48,0xa3,0xff }, /*    49 */
  {   163,   262,   -81,0, 0x2194,0x12ca, 0x00,0x4b,0x9a,0xff }, /*    50 */
  {     0,   156,   -81,0, 0x0400,0x12ca, 0xb6,0x47,0xb6,0xff }, /*    51 */
  {   244,   233,   -81,0, 0x305e,0x12ca, 0x2d,0x48,0xa3,0xff }, /*    52 */
  {   408,    61,   -81,0, 0x4df3,0x12ca, 0x6a,0xce,0xd3,0xff }, /*    53 */
  {  -326,   -48,     0,0, 0xc8d7,0x0400, 0x1f,0x76,0x22,0xff }, /*    54 */
  {   326,   156,   -81,0, 0x3f29,0x12ca, 0x4a,0x47,0xb6,0xff }, /*    55 */
  {  -163,   -94,     0,0, 0xe66c,0x0400, 0xcb,0x4c,0x56,0xff }, /*    56 */
  {  -408,   -48,     0,0, 0xba0d,0x0400, 0x4f,0x08,0x62,0xff }, /*    57 */
  {   -81,    60,     0,0, 0xf536,0x0400, 0x8f,0x37,0x0e,0xff }, /*    58 */
  {  -244,   -92,     0,0, 0xd7a2,0x0400, 0x19,0x5c,0x53,0xff }, /*    59 */
  {    81,   325,     0,0, 0x12ca,0x0400, 0xc0,0x59,0xc0,0xff }, /*    60 */
  {   163,   360,     0,0, 0x2194,0x0400, 0x00,0x67,0xb7,0xff }, /*    61 */
  {     0,   233,     0,0, 0x0400,0x0400, 0x9d,0x43,0xd8,0xff }, /*    62 */
  {   244,   325,     0,0, 0x305e,0x0400, 0x40,0x59,0xc0,0xff }, /*    63 */
  {   326,   233,     0,0, 0x3f29,0x0400, 0x5d,0x49,0xd3,0xff }, /*    64 */
  {  -326,   -52,    81,0, 0xc8d7,0xf536, 0x35,0x73,0x00,0xff }, /*    65 */
  {   408,   114,     0,0, 0x4df3,0x0400, 0x76,0x27,0xed,0xff }, /*    66 */
  {  -244,  -137,    81,0, 0xd7a2,0xf536, 0x45,0x6a,0x00,0xff }, /*    67 */
  {  -163,  -173,    81,0, 0xe66c,0xf536, 0xdb,0x79,0x00,0xff }, /*    68 */
  {  -408,   -48,    81,0, 0xba0d,0xf536, 0x65,0x05,0x4b,0xff }, /*    69 */
  {     0,   257,    81,0, 0x0400,0xf536, 0x93,0x3f,0x00,0xff }, /*    70 */
  {    81,   360,    81,0, 0x12ca,0xf536, 0xb7,0x66,0x0c,0xff }, /*    71 */
  {   -81,    17,    81,0, 0xf536,0xf536, 0x8a,0x2e,0x00,0xff }, /*    72 */
  {   163,   397,    81,0, 0x2194,0xf536, 0x00,0x7e,0x0d,0xff }, /*    73 */
  {   244,   360,    81,0, 0x305e,0xf536, 0x48,0x67,0x0c,0xff }, /*    74 */
  {   326,   262,    81,0, 0x3f29,0xf536, 0x65,0x4c,0x00,0xff }, /*    75 */
  {  -408,   -48,   163,0, 0xba0d,0xe66c, 0x4f,0x08,0x62,0xff }, /*    76 */
  {  -244,   -92,   163,0, 0xd7a2,0xe66c, 0x1d,0x6c,0xc5,0xff }, /*    77 */
  {   408,   134,    81,0, 0x4df3,0xf536, 0x78,0x28,0x00,0xff }, /*    78 */
  {  -163,   -94,   163,0, 0xe66c,0xe66c, 0xc7,0x53,0xb3,0xff }, /*    79 */
  {  -326,   -48,   163,0, 0xc8d7,0xe66c, 0x1f,0x7b,0xfd,0xff }, /*    80 */
  {   -81,    60,   163,0, 0xf536,0xe66c, 0x8f,0x37,0xf2,0xff }, /*    81 */
  {    81,   301,   163,0, 0x12ca,0xe66c, 0xd1,0x50,0x56,0xff }, /*    82 */
  {     0,   232,   163,0, 0x0400,0xe66c, 0xa3,0x49,0x2c,0xff }, /*    83 */
  {   244,   301,   163,0, 0x305e,0xe66c, 0x2f,0x50,0x56,0xff }, /*    84 */
  {   163,   332,   163,0, 0x2194,0xe66c, 0x00,0x51,0x61,0xff }, /*    85 */
  {   408,   114,   163,0, 0x4df3,0xe66c, 0x76,0x27,0x13,0xff }, /*    86 */
  {  -326,   -48,   244,0, 0xc8d7,0xd7a2, 0x00,0x7f,0x00,0xff }, /*    87 */
  {   326,   232,   163,0, 0x3f29,0xe66c, 0x56,0x4f,0x31,0xff }, /*    88 */
  {  -244,   -48,   244,0, 0xd7a2,0xd7a2, 0xed,0x79,0xe1,0xff }, /*    89 */
  {  -408,   -48,   244,0, 0xba0d,0xd7a2, 0x4f,0x08,0x62,0xff }, /*    90 */
  {  -163,   -21,   244,0, 0xe66c,0xd7a2, 0xbb,0x66,0xe4,0xff }, /*    91 */
  {     0,   156,   244,0, 0x0400,0xd7a2, 0xd1,0x52,0x54,0xff }, /*    92 */
  {    81,   166,   244,0, 0x12ca,0xd7a2, 0x07,0x56,0x5c,0xff }, /*    93 */
  {   -81,    61,   244,0, 0xf536,0xd7a2, 0xa5,0x53,0x1d,0xff }, /*    94 */
  {   163,   142,   244,0, 0x2194,0xd7a2, 0x00,0x65,0x4c,0xff }, /*    95 */
  {   244,   166,   244,0, 0x305e,0xd7a2, 0xf9,0x56,0x5c,0xff }, /*    96 */
  {   408,    61,   244,0, 0x4df3,0xd7a2, 0x61,0xd2,0x42,0xff }, /*    97 */
  {  -326,   -48,   326,0, 0xc8d7,0xc8d7, 0x00,0x7f,0x00,0xff }, /*    98 */
  {   326,   156,   244,0, 0x3f29,0xd7a2, 0x2f,0x52,0x54,0xff }, /*    99 */
  {  -244,   -48,   326,0, 0xd7a2,0xc8d7, 0xfc,0x7e,0x00,0xff }, /*   100 */
  {  -163,   -42,   326,0, 0xe66c,0xc8d7, 0xdf,0x78,0x13,0xff }, /*   101 */
  {  -408,   -48,   326,0, 0xba0d,0xc8d7, 0x4f,0x08,0x62,0xff }, /*   102 */
  {   -81,     0,   326,0, 0xf536,0xc8d7, 0xc5,0x5e,0x3b,0xff }, /*   103 */
  {     0,    61,   326,0, 0x0400,0xc8d7, 0xc9,0x4e,0x53,0xff }, /*   104 */
  {    81,   114,   326,0, 0x12ca,0xc8d7, 0xdf,0x5b,0x51,0xff }, /*   105 */
  {   244,   114,   326,0, 0x305e,0xc8d7, 0x21,0x5b,0x51,0xff }, /*   106 */
  {   326,    61,   326,0, 0x3f29,0xc8d7, 0x37,0x4e,0x53,0xff }, /*   107 */
  {   163,   123,   326,0, 0x2194,0xc8d7, 0x00,0x6c,0x42,0xff }, /*   108 */
  {  -326,   -48,   408,0, 0xc8d7,0xba0d, 0x4f,0x08,0x62,0xff }, /*   109 */
  {  -244,   -48,   408,0, 0xd7a2,0xba0d, 0x4f,0x08,0x62,0xff }, /*   110 */
  {   408,     0,   326,0, 0x4df3,0xc8d7, 0x58,0xce,0x4b,0xff }, /*   111 */
  {  -408,   -48,   408,0, 0xba0d,0xba0d, 0x4f,0x08,0x62,0xff }, /*   112 */
  {   -81,   -42,   408,0, 0xf536,0xba0d, 0xf2,0xd1,0x74,0xff }, /*   113 */
  {     0,   -17,   408,0, 0x0400,0xba0d, 0xeb,0xd3,0x74,0xff }, /*   114 */
  {  -163,   -48,   408,0, 0xe66c,0xba0d, 0x22,0xf3,0x79,0xff }, /*   115 */
  {    81,     9,   408,0, 0x12ca,0xba0d, 0xf6,0xd9,0x78,0xff }, /*   116 */
  {   244,     9,   408,0, 0x305e,0xba0d, 0x1d,0xda,0x75,0xff }, /*   117 */
  {   326,   -17,   408,0, 0x3f29,0xba0d, 0x2b,0xd5,0x6f,0xff }, /*   118 */
  {   163,    20,   408,0, 0x2194,0xba0d, 0x00,0x2c,0x76,0xff }, /*   119 */
  {   408,   -42,   408,0, 0x4df3,0xba0d, 0x47,0xda,0x61,0xff }, /*   120 */
};

/* ============================================================
          Gfx
 ============================================================ */
static Gfx gfx_Shape_of___POLYHEDRON_98_[] = {
  gsSPVertex( SEGADRS(5, 0), 32, 0 ),
  gsSP2Triangles(  0,  1,  2,  0,  1,  3,  2,  0),
  gsSP2Triangles(  2,  3,  4,  0,  3,  5,  4,  0),
  gsSP2Triangles(  4,  6,  7,  0,  4,  5,  6,  0),
  gsSP2Triangles(  7,  6,  8,  0,  7,  8,  9,  0),
  gsSP2Triangles(  9,  8, 10,  0,  1, 11,  3,  0),
  gsSP2Triangles(  9, 10, 12,  0, 12, 10, 13,  0),
  gsSP2Triangles(  3, 14,  5,  0, 12, 13, 15,  0),
  gsSP2Triangles(  5, 14,  6,  0, 15, 13, 16,  0),
  gsSP2Triangles( 15, 16, 17,  0,  6, 18,  8,  0),
  gsSP2Triangles( 17, 16, 19,  0,  8, 18, 10,  0),
  gsSP2Triangles( 16, 20, 19,  0, 11, 21,  3,  0),
  gsSP2Triangles( 19, 20, 22,  0,  3, 21, 14,  0),
  gsSP2Triangles( 10, 23, 13,  0, 20, 24, 22,  0),
  gsSP2Triangles( 13, 23, 16,  0, 22, 24, 25,  0),
  gsSP2Triangles( 14, 26,  6,  0, 22, 25, 27,  0),
  gsSP2Triangles(  6, 26, 18,  0, 18, 28, 10,  0),
  gsSP2Triangles( 16, 29, 20,  0, 10, 28, 23,  0),
  gsSP2Triangles( 20, 29, 24,  0, 23, 30, 16,  0),
  gsSP2Triangles( 24, 31, 25,  0, 16, 30, 29,  0),
  gsSPVertex( SEGADRS(5, 512), 11, 0 ),
  gsSP2Triangles( 29, 31, 24,  0, 11,  0, 21,  0),
  gsSP2Triangles( 21,  0, 14,  0, 31,  1, 25,  0),
  gsSP2Triangles( 14,  2, 26,  0, 11,  3,  0,  0),
  gsSP2Triangles( 26,  2, 18,  0,  0,  4, 14,  0),
  gsSP2Triangles( 18,  5, 28,  0, 14,  4,  2,  0),
  gsSP2Triangles( 28,  6, 23,  0,  2,  7, 18,  0),
  gsSP2Triangles( 23,  8, 30,  0, 18,  7,  5,  0),
  gsSP2Triangles( 30,  8, 29,  0, 28,  5,  6,  0),
  gsSP2Triangles( 29,  9, 31,  0, 23,  6,  8,  0),
  gsSP2Triangles( 31, 10,  1,  0,  8,  9, 29,  0),
  gsSPVertex( SEGADRS(5, 688), 18, 11 ),
  gsSP2Triangles(  3, 11,  0,  0,  9, 12, 31,  0),
  gsSP2Triangles( 31, 12, 10,  0,  0, 13,  4,  0),
  gsSP2Triangles(  4, 13,  2,  0,  3, 14, 11,  0),
  gsSP2Triangles(  0, 11, 13,  0,  2, 15,  7,  0),
  gsSP2Triangles(  7, 15,  5,  0, 13, 16,  2,  0),
  gsSP2Triangles(  5, 17,  6,  0,  2, 16, 15,  0),
  gsSP2Triangles(  6, 18,  8,  0,  8, 18,  9,  0),
  gsSP2Triangles( 15, 19,  5,  0,  5, 19, 17,  0),
  gsSP2Triangles(  9, 20, 12,  0,  6, 17, 18,  0),
  gsSP2Triangles( 12, 21, 10,  0, 18, 20,  9,  0),
  gsSP2Triangles( 14, 22, 11,  0, 20, 23, 12,  0),
  gsSP2Triangles( 11, 22, 13,  0, 12, 23, 21,  0),
  gsSP2Triangles( 13, 24, 16,  0, 14, 25, 22,  0),
  gsSP2Triangles( 16, 26, 15,  0, 22, 27, 13,  0),
  gsSP2Triangles( 15, 26, 19,  0, 13, 27, 24,  0),
  gsSP2Triangles( 19, 28, 17,  0, 16, 24, 26,  0),
  gsSPVertex( SEGADRS(5, 976), 3, 29 ),
  gsSP2Triangles( 17, 29, 18,  0, 18, 29, 20,  0),
  gsSP2Triangles( 26, 30, 19,  0, 19, 30, 28,  0),
  gsSP2Triangles( 20, 31, 23,  0, 17, 28, 29,  0),
  gsSPVertex( SEGADRS(5, 1024), 17, 0 ),
  gsSP2Triangles( 23,  0, 21,  0, 29, 31, 20,  0),
  gsSP2Triangles( 25,  1, 22,  0, 31,  0, 23,  0),
  gsSP2Triangles( 22,  1, 27,  0,  0,  2, 21,  0),
  gsSP2Triangles( 27,  3, 24,  0, 24,  4, 26,  0),
  gsSP2Triangles( 25,  5,  1,  0,  1,  3, 27,  0),
  gsSP2Triangles( 26,  6, 30,  0,  3,  4, 24,  0),
  gsSP2Triangles( 30,  7, 28,  0,  4,  8, 26,  0),
  gsSP2Triangles( 28,  9, 29,  0, 26,  8,  6,  0),
  gsSP2Triangles( 29,  9, 31,  0, 30,  6,  7,  0),
  gsSP2Triangles( 31, 10,  0,  0, 28,  7,  9,  0),
  gsSP2Triangles(  0, 11,  2,  0,  9, 10, 31,  0),
  gsSP2Triangles(  5, 12,  1,  0, 10, 11,  0,  0),
  gsSP2Triangles(  1, 13,  3,  0, 11, 14,  2,  0),
  gsSP1Triangle(  3, 15,  4,  0),
  gsSPVertex( SEGADRS(5, 1296), 15, 17 ),
  gsSP2Triangles( 12, 16,  1,  0,  4, 17,  8,  0),
  gsSP2Triangles(  1, 16, 13,  0,  8, 17,  6,  0),
  gsSP2Triangles(  3, 13, 15,  0,  6, 18,  7,  0),
  gsSP2Triangles(  4, 15, 17,  0,  7, 18,  9,  0),
  gsSP2Triangles( 17, 19,  6,  0,  9, 20, 10,  0),
  gsSP2Triangles(  6, 19, 18,  0, 10, 20, 11,  0),
  gsSP2Triangles( 18, 21,  9,  0, 11, 22, 14,  0),
  gsSP2Triangles(  9, 21, 20,  0, 12, 23, 16,  0),
  gsSP2Triangles( 20, 24, 11,  0, 11, 24, 22,  0),
  gsSP2Triangles( 16, 25, 13,  0, 13, 25, 15,  0),
  gsSP2Triangles( 12, 26, 23,  0, 15, 27, 17,  0),
  gsSP2Triangles( 16, 23, 25,  0, 17, 28, 19,  0),
  gsSP2Triangles( 25, 27, 15,  0, 19, 29, 18,  0),
  gsSP1Triangle( 27, 30, 17,  0),
  gsSP2Triangles( 18, 31, 21,  0, 17, 30, 28,  0),
  gsSP2Triangles( 21, 31, 20,  0, 19, 28, 29,  0),
  gsSPVertex( SEGADRS(5, 1536), 17, 0 ),
  gsSP2Triangles( 20,  0, 24,  0, 18, 29, 31,  0),
  gsSP2Triangles( 24,  1, 22,  0, 31,  0, 20,  0),
  gsSP2Triangles( 26,  2, 23,  0,  0,  3, 24,  0),
  gsSP2Triangles( 24,  3,  1,  0, 23,  4, 25,  0),
  gsSP2Triangles( 25,  5, 27,  0, 26,  6,  2,  0),
  gsSP2Triangles( 23,  2,  4,  0, 27,  7, 30,  0),
  gsSP2Triangles( 30,  8, 28,  0, 25,  4,  5,  0),
  gsSP2Triangles( 28,  9, 29,  0, 27,  5,  7,  0),
  gsSP2Triangles( 29,  9, 31,  0, 30,  7,  8,  0),
  gsSP2Triangles( 31, 10,  0,  0, 28,  8,  9,  0),
  gsSP2Triangles(  0, 10,  3,  0,  3, 11,  1,  0),
  gsSP2Triangles(  9, 12, 31,  0, 31, 12, 10,  0),
  gsSP2Triangles(  6, 13,  2,  0, 10, 11,  3,  0),
  gsSP2Triangles(  2, 14,  4,  0, 11, 15,  1,  0),
  gsSP1Triangle(  4, 14,  5,  0),
  gsSP2Triangles(  6, 16, 13,  0,  2, 13, 14,  0),
  gsSPVertex( SEGADRS(5, 1808), 8, 17 ),
  gsSP2Triangles(  5, 17,  7,  0,  7, 18,  8,  0),
  gsSP2Triangles( 14, 19,  5,  0,  8, 20,  9,  0),
  gsSP2Triangles(  5, 19, 17,  0,  9, 20, 12,  0),
  gsSP2Triangles(  7, 17, 18,  0, 12, 21, 10,  0),
  gsSP2Triangles(  8, 18, 20,  0, 10, 21, 11,  0),
  gsSP2Triangles( 11, 22, 15,  0, 20, 23, 12,  0),
  gsSP2Triangles( 12, 23, 21,  0, 21, 22, 11,  0),
  gsSP1Triangle( 22, 24, 15,  0),
  gsSPEndDisplayList(),
};

/* ============================================================
          Shape Structure
 ============================================================ */
static NDR_SHAPE shape_Shape_of___POLYHEDRON_98_ = {
  gfx_Shape_of___POLYHEDRON_98_,
  vtx_Shape_of___POLYHEDRON_98_, 121, 5,
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
static NDR_SHAPE *shapelist_grid[] = {
  &shape_Shape_of___POLYHEDRON_98_,
};

/* ############################################################
          Resource Information
 ############################################################ */
NDR_RESINFO resinfo_grid={
  NULL,
  20.000000,
  NULL,
  shapelist_grid,
  NULL,
  NULL,
  NULL,
  NULL,
  0, 1, 0, 0, 0, 0
};

