/*
 * Do not edit this file.  It was automatically generated
 * by "rgb2c" from the file "sand.rgb".
 *
/*
 *   Size: 32 x 32
 *   Number of channels: 4
 *   Number of bits per texel: 16 (G_IM_SIZ_16b)
 *   Format of texel: G_IM_FMT_RGBA
 *
 * Example usage:
 *
 *   gsSPTexture (128, 128, (levels-1), G_TX_RENDERTILE, 1),
 *   gsDPPipeSync (),
 *   gsDPSetCombineMode (G_CC_MODULATERGBA, G_CC_MODULATERGBA),
 *   gsDPSetTexturePersp (G_TP_PERSP),
 *   gsDPSetTextureDetail (G_TD_CLAMP),
 *   gsDPSetTextureLOD (G_TL_TILE),
 *   gsDPSetTextureLUT (G_TT_NONE),
 *   gsDPSetTextureFilter (G_TF_BILERP),
 *   gsDPSetTextureConvert(G_TC_FILT),
 *   gsDPLoadTextureBlock (RGBA16sandMM, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, 0
 *     G_TX_WRAP | G_TX_NOMIRROR, G_TX_WRAP | G_TX_NOMIRROR,
 *     G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
 */

#if 0	/* Image preview */
	+--------------------------------+
	|ooo+ooooo+oo+oooo+ooo+oo+oo+ooo+|
	|ooo+ooooo+oo++ooo+ooo+ooooo+ooo+|
	|ooo+ooooo+oo++ooo+ooo+ooooo+ooo+|
	|ooo+ooooo+ooo+ooo+ooo+ooooo+ooo+|
	|ooo+ooooo+ooo+ooo+ooo+oooo++ooo+|
	|ooo+ooooo+ooo+ooo+ooo+oooo++ooo+|
	|ooo++oooo+ooo+ooo+ooo++ooo++ooo+|
	|+oo++oooo+oo++ooo+ooo++ooo++ooo+|
	|+oo++oooo+oo++ooo+ooo++ooo++ooo+|
	|+oo++ooo++ooo+ooo+ooo++ooo+oooo+|
	|+oo++ooo++oo++ooo+ooo++ooo+oooo+|
	|+ooo+ooo++oo++ooo+ooo+oooo+oooo+|
	|+ooo+ooo++oo++ooo+ooo+oooo+oooo+|
	|+ooo+ooo++oo++ooo+ooo+oooo+oooo+|
	|+ooo+ooo+ooo++ooo+ooo+oooo+oooo+|
	|+ooo+ooo++oo++ooo+ooo+oooo+oooo+|
	|+ooo+ooo++oo++ooo+ooo+ooooo+ooo+|
	|+ooo+ooo++oo++ooo+ooo+ooo+o+ooo+|
	|+ooo+ooo++oo++ooo+ooo+ooo+o+ooo+|
	|+ooo+oooo+oo++ooo+ooo+oo++oo+oo+|
	|+ooo+oooo+oo++ooo+ooo+oo++oo+oo+|
	|+ooo+oooo+oo++ooo+ooo+oo++oo+ooo|
	|+ooo+oooo+oo++ooo+ooo+oo++oo+ooo|
	|+ooo+oooo+ooo+ooo+ooo+oo++oo+ooo|
	|+ooo+oooo+ooo+ooo+ooo+oo++oo+ooo|
	|+ooo+oooo+ooo+ooo+ooo+oo++oo+ooo|
	|+ooo+oooo+ooo+ooo+ooo+oo++oo+ooo|
	|+ooo+oooo+ooo+ooo++oo+ooo+oo+ooo|
	|+ooo+ooo*oooo+ooo++oo+oo++oo+ooo|
	|+ooo+oooooooooooo++oo+ooo+oo+ooo|
	|oooo+o*o*ooo+oooo++oo+ooo+oo+ooo|
	|ooo++oooo+oo+ooo+++oo+ooo+oo+ooo|
	+--------------------------------+
#endif

static Gfx RGBA16sandMM_MIP_dummy_aligner1[] = { gsSPEndDisplayList() };

unsigned short RGBA16sandMM_orig[] = {
0xac9f, 0xad21, 0xac9f, 0x7b57, 0xa45d, 0xad21, 0xac9f, 0xb4df, 0xa49f, 0x8397, 0xa49f, 0xb4df, 0x8399, 0xa49f, 0xa45d, 0xa4df, 0xac9f, 0x7b97, 0xa45d, 0xace1, 0xa49d, 0x7b57, 0xb4e1, 0xac9f, 0x8c19, 0xa49f, 0xac9f, 0x83d9, 0x9c1b, 0xac9f, 0xace1, 0x8bd9, 
0xac9f, 0xad21, 0xac5d, 0x7357, 0xa49d, 0xace1, 0xac9f, 0xb4e1, 0x9c5d, 0x7b97, 0x9c5d, 0xb4e1, 0x8bd9, 0x941b, 0xa49d, 0xac9f, 0xa49f, 0x7b57, 0xa45d, 0xb4df, 0x9c9f, 0x7b57, 0xa49d, 0xac9f, 0x941b, 0xa49f, 0xac9f, 0x7b97, 0xa49f, 0xa49f, 0xb4df, 0x8bd9, 
0xa49f, 0xb4df, 0xa49f, 0x7b57, 0x9c5d, 0xb4e1, 0xb4df, 0xad21, 0xac9f, 0x7b57, 0xa49d, 0xb4e1, 0x8bd9, 0x7b99, 0xac9f, 0xac9f, 0xa49f, 0x7b97, 0xa45d, 0xb4df, 0x9c5d, 0x7b97, 0x9c5f, 0xac9f, 0x9c5b, 0xac9f, 0x9c9f, 0x8357, 0xa49d, 0xac9f, 0xac9f, 0x83d9, 
0xa49f, 0xb4df, 0xac9f, 0x7b97, 0x9c1b, 0xace1, 0xacdf, 0xac9f, 0x9c9d, 0x7b57, 0xa45d, 0xace1, 0x9c5d, 0x7b57, 0xac9f, 0xac9f, 0x9c9d, 0x8357, 0xa49f, 0xacdf, 0xa45d, 0x7357, 0x9c5d, 0xac9f, 0xa45d, 0xa4df, 0x9c1b, 0x7b99, 0xa49d, 0xac9f, 0xac9f, 0x7b97, 
0xa45d, 0xad21, 0xac9f, 0x7b57, 0x9c5b, 0xace1, 0xb4e1, 0xb4df, 0x9c5d, 0x7357, 0xac9f, 0xa49f, 0x9c5d, 0x7b55, 0xac9f, 0xace1, 0x9c5d, 0x7355, 0xa49f, 0xb49f, 0xacdf, 0x7357, 0x9c1b, 0xa49f, 0xa49d, 0xa49f, 0x93db, 0x83d9, 0xac9f, 0xacdf, 0xac9f, 0x7b97, 
0x9c5d, 0xb4e1, 0xac9f, 0x7b97, 0x9c1b, 0xacdf, 0xac9f, 0xace1, 0x9c5d, 0x7b57, 0xa4df, 0xb49f, 0x945d, 0x7b55, 0xac9f, 0xac9f, 0x9c9d, 0x7b57, 0xa49f, 0xb49f, 0xa4df, 0x7b57, 0x941b, 0xac9f, 0xac9f, 0xa49f, 0x83d9, 0x8bd9, 0xa49f, 0xac9f, 0xac9f, 0x7357, 
0x9c1b, 0xad21, 0xac9f, 0x7b57, 0x941b, 0xacdf, 0xac9f, 0xace1, 0x9c5b, 0x7b57, 0xa49f, 0xb4e1, 0x941b, 0x7b57, 0xac9f, 0xac9f, 0x9c5d, 0x7355, 0xa49f, 0xac9f, 0xacdf, 0x7b57, 0x8bdb, 0xacdf, 0xac9f, 0xa49f, 0x8397, 0x8bdb, 0xac9f, 0xacdf, 0xac9f, 0x7b97, 
0x8bd9, 0xb4e1, 0xb4df, 0x83d9, 0x93db, 0xacdf, 0xb4df, 0xa49f, 0x9c5d, 0x7357, 0xac9f, 0xacdf, 0x8bd9, 0x8399, 0xacdf, 0xac9f, 0x9c5d, 0x7357, 0xa45d, 0xacdf, 0xb4df, 0x7357, 0x93db, 0xa4df, 0xac9f, 0x9c9d, 0x7b57, 0x8bdb, 0xacdf, 0xac9f, 0x9c9d, 0x7315, 
0x8bd9, 0xb4e1, 0xb4df, 0x83d9, 0x8bd9, 0xace1, 0xb4e1, 0xa4df, 0x9c1b, 0x8399, 0xa49f, 0xb521, 0x93d9, 0x7b97, 0xac9f, 0xac9f, 0x945b, 0x7b57, 0x9c5f, 0xac9f, 0xb51f, 0x7b99, 0x8b99, 0xa49f, 0xac9f, 0xa49f, 0x7355, 0x941b, 0xac9f, 0xac9f, 0xa49f, 0x7b97, 
0x8bd9, 0xacdf, 0xb4df, 0x8bdb, 0x7b97, 0xac9f, 0xb4e1, 0xa4df, 0x93d9, 0x83d9, 0xac9f, 0xb4e1, 0x945d, 0x8b99, 0xad1f, 0xb4e1, 0x9c5d, 0x7357, 0xac9f, 0xac9f, 0xac9f, 0x83d9, 0x8bd9, 0xa49f, 0xac9f, 0xa49f, 0x7355, 0x9c1b, 0xa49f, 0xacdf, 0x9c5f, 0x7b55, 
0x8bd9, 0xace1, 0xb4df, 0x8bdb, 0x8397, 0xacdf, 0xb4e1, 0xb4e1, 0x8c1b, 0x8b99, 0xa4df, 0xac9f, 0x8c1b, 0x8b99, 0xa4df, 0xb4e1, 0xa45d, 0x7357, 0xacdf, 0xacdf, 0xac9f, 0x8399, 0x8c1b, 0xac9f, 0xb4df, 0xa49f, 0x7b57, 0x9c5d, 0xa49f, 0xac9f, 0x9c9d, 0x7315, 
0x8399, 0xb4df, 0xace1, 0x9c5b, 0x7b57, 0xa49f, 0xb4e1, 0xacdf, 0x941b, 0x8bd9, 0xb4e1, 0xa49f, 0x941b, 0x8bd9, 0xac9f, 0xac9f, 0x9c5d, 0x7357, 0xac9f, 0xace1, 0xacdf, 0x8357, 0x941b, 0xa4df, 0xac9f, 0x9c9d, 0x8357, 0x9c9f, 0xb49f, 0xb4df, 0x9c5f, 0x7b55, 
0x8bd9, 0xace1, 0xb4df, 0x9c5d, 0x7b57, 0xb4df, 0xace1, 0xb4df, 0x8bdb, 0x8bd9, 0xb4e1, 0xa49f, 0x8bd9, 0x8bd9, 0xacdf, 0xb4df, 0x9c5d, 0x7b57, 0xac9f, 0xacdf, 0xacdf, 0x7b59, 0x9c5d, 0xac9f, 0xacdf, 0x9c5d, 0x7b57, 0x9c9d, 0xac9f, 0xb4df, 0xa49f, 0x7315, 
0x8bd9, 0xace1, 0xb4e1, 0x945b, 0x7b57, 0xac9f, 0xb521, 0xac9f, 0x8c1b, 0x8bd9, 0xac9f, 0xace1, 0x9419, 0x8399, 0xacdf, 0xaca1, 0x9c5d, 0x8397, 0xa49f, 0xb4df, 0xac9f, 0x7397, 0x9c1d, 0xacdf, 0xb4e1, 0x9c5d, 0x7315, 0xa49f, 0xac9f, 0xac9f, 0xa49f, 0x7315, 
0x7b97, 0xb4e1, 0xb4df, 0x9c5d, 0x7b57, 0xacdf, 0xace1, 0xac9f, 0x8bd9, 0x941b, 0xb4df, 0xac9f, 0x8bdb, 0x8c19, 0xb4e1, 0xa49f, 0x9c5d, 0x8397, 0xa49f, 0xb4df, 0xa45f, 0x7397, 0xa45d, 0xac9f, 0xac9f, 0x9c5d, 0x7357, 0xa49d, 0xac9f, 0xac9f, 0xa49f, 0x7355, 
0x7b97, 0xb49f, 0xace1, 0x9c5b, 0x7357, 0xac9f, 0xb4e1, 0xacdf, 0x8bd9, 0x941b, 0xb4e1, 0xacdf, 0x93db, 0x941b, 0xac9f, 0xb521, 0x941b, 0x8397, 0xa49f, 0xb4e1, 0xa49f, 0x7b57, 0xa49d, 0xac9f, 0xb4df, 0x9c5d, 0x8399, 0x9c5d, 0xac9f, 0xacdf, 0xac9f, 0x7357, 
0x7b97, 0xb4e1, 0xb4e1, 0x9c5d, 0x7355, 0xb4df, 0xace1, 0xb4e1, 0x8c1b, 0x93d9, 0xa49f, 0xac9f, 0x83d9, 0x93db, 0xa4df, 0xb4e1, 0x9c5b, 0x7b99, 0xac9f, 0xb4df, 0xa49f, 0x7b57, 0xa49d, 0xac9f, 0xa49f, 0x9c1d, 0x9c9d, 0x93db, 0xa49d, 0xb4e1, 0xa4df, 0x7b57, 
0x7b97, 0xb49f, 0xb521, 0x9c5d, 0x7b57, 0xa49d, 0xb4e1, 0xacdf, 0x93db, 0x8bdb, 0xacdf, 0xb4e1, 0x83d9, 0x93d9, 0xa4df, 0xaca1, 0x941b, 0x83d7, 0xac9f, 0xac9f, 0x9c9d, 0x8357, 0xa49f, 0xb4e1, 0x9c5b, 0x8c1b, 0xb49f, 0x8c1b, 0xa45d, 0xace1, 0xb4df, 0x7b97, 
0x7357, 0xb4df, 0xb4e1, 0x9c5d, 0x7b57, 0xa49d, 0xb4e1, 0xacdf, 0x941b, 0x8399, 0xacdf, 0xb4e1, 0x8bd9, 0x8bdb, 0xb4df, 0xb4df, 0x941b, 0x7357, 0xb4df, 0xace1, 0x9c5d, 0x7b57, 0xac9f, 0xace1, 0x9c5b, 0x8bdb, 0xb4df, 0x8c1b, 0x9c1d, 0xa49f, 0xb4df, 0x7b97, 
0x7357, 0xb4df, 0xb4e1, 0xa49d, 0x7315, 0xa49f, 0xb4e1, 0xace1, 0x9c5b, 0x8399, 0xa49f, 0xac9f, 0x8c1b, 0x941b, 0xa49f, 0xb4e1, 0x941b, 0x7b97, 0xac9f, 0xac9f, 0x9c5d, 0x7357, 0xac9f, 0xacdf, 0x941b, 0x8399, 0xb4e1, 0x945b, 0x8b99, 0xb521, 0xacdf, 0x8b99, 
0x7357, 0xb4df, 0xb4e1, 0xa49d, 0x7357, 0xa45d, 0xacdf, 0xb4e1, 0x9c5d, 0x8399, 0xb4df, 0xb4df, 0x83d9, 0x8bdb, 0xac9f, 0xac9f, 0x945b, 0x7b57, 0xa49f, 0xb4e1, 0xa45d, 0x7357, 0xacdf, 0xacdf, 0x93d9, 0x8399, 0xb4e1, 0x9c5d, 0x7b97, 0xac9f, 0xb4e1, 0x8bd9, 
0x7315, 0xacdf, 0xace1, 0xa45d, 0x7355, 0x9c5f, 0xb4df, 0xb4e1, 0x9c9d, 0x8397, 0xa49f, 0xb4e1, 0x8bd9, 0x8bd9, 0xa49f, 0xb4e1, 0x9c5d, 0x7b57, 0xa49f, 0xac9f, 0x9c5d, 0x7357, 0xac9f, 0xacdf, 0x941b, 0x8b99, 0xad21, 0xa45d, 0x7b97, 0xac9f, 0xb4e1, 0x941b, 
0x7315, 0xacdf, 0xace1, 0xac9d, 0x6b17, 0x9c5b, 0xb4df, 0xac9f, 0x9c5f, 0x8397, 0xa49d, 0xb4e1, 0x8bdb, 0x8bd9, 0xa49f, 0xac9f, 0x9c5d, 0x7357, 0xa49d, 0xb4e1, 0x9c5d, 0x7b57, 0xac9f, 0xacdf, 0x8bdb, 0x8bd9, 0xacdf, 0xac9f, 0x7357, 0xa45d, 0xb521, 0x9c5d, 
0x7315, 0xacdf, 0xace1, 0xac9d, 0x6b17, 0x9c1b, 0xb521, 0xb4e1, 0xa49d, 0x7b97, 0xac5f, 0xad21, 0x93db, 0x8397, 0xa49f, 0xac9f, 0x9c9d, 0x7b57, 0xa49f, 0xac9f, 0x9c5d, 0x7b57, 0xacdf, 0xacdf, 0x8b99, 0x8bdb, 0xacdf, 0xac9f, 0x7357, 0xa49d, 0xb4e1, 0x9c5d, 
0x7315, 0xacdf, 0xace1, 0xac9f, 0x7357, 0x9c5b, 0xb4e1, 0xb4e1, 0xa4df, 0x7b57, 0xa45d, 0xa49f, 0x9c5b, 0x8399, 0xa49f, 0xac9f, 0x9c9d, 0x7b57, 0xa45d, 0xa45d, 0x9c5d, 0x7b57, 0xa4df, 0xb4df, 0x8b9b, 0x8bd9, 0xace1, 0xac9f, 0x7b57, 0x9c5d, 0xb521, 0x9c5d, 
0x7357, 0xac9d, 0xace1, 0xac9f, 0x7b57, 0x9c5d, 0xacdf, 0xb4e1, 0xa49f, 0x7b55, 0x9c5f, 0xacdf, 0x941b, 0x7b57, 0xac9f, 0xac9f, 0x9c9d, 0x8357, 0x9c5d, 0xa49f, 0x9c1d, 0x7355, 0xacdf, 0xa49f, 0x93db, 0x8bd9, 0xa49f, 0xac9f, 0x7357, 0x9c5d, 0xb4df, 0xa49f, 
0x7b97, 0xac5f, 0xacdf, 0xa49d, 0x7b57, 0xa45d, 0xb521, 0xacdf, 0xb4df, 0x8399, 0x9c5d, 0xb4df, 0x9c5d, 0x7357, 0xac9f, 0xb4df, 0x9c5d, 0x7b97, 0x9c1d, 0x9c5d, 0x9c5d, 0x8357, 0xa4df, 0xb49f, 0x8c1b, 0x8399, 0xac9f, 0xac9f, 0x7357, 0x9c5d, 0xb4e1, 0xacdf, 
0x8399, 0xa49d, 0xb4df, 0xa45f, 0x7b97, 0xa45d, 0xb521, 0xb4e1, 0xb4e1, 0x83d9, 0x9c1b, 0xacdf, 0x9c5d, 0x8397, 0xa49f, 0xb4e1, 0x9c5d, 0x8399, 0x8c19, 0xa45f, 0xa45d, 0x7b97, 0xa49f, 0xb4df, 0x941b, 0x8357, 0xace1, 0xb4df, 0x7b97, 0x941d, 0xb4df, 0xac9f, 
0x8bd9, 0xac9f, 0xa49f, 0x9c5d, 0x8397, 0xa49f, 0xb4df, 0xb4e1, 0xb521, 0x941b, 0x9c5b, 0xa49f, 0x9c1d, 0x83d9, 0xac9f, 0xac9f, 0x945b, 0x8b99, 0x8bd9, 0x9c5d, 0xa49f, 0x7b57, 0xa45d, 0xa49f, 0x941b, 0x7357, 0xac9f, 0xb51f, 0x7b57, 0x9c5d, 0xb4e1, 0xb4e1, 
0x8bd9, 0xac9f, 0xacdf, 0x9c1d, 0x7355, 0xacdf, 0xb4e1, 0xb4e1, 0xb4e1, 0x945b, 0x9c1b, 0xa4df, 0x941b, 0x941b, 0xb4df, 0xb4df, 0x941d, 0x8bd9, 0x8bd9, 0x9c5d, 0xa45d, 0x7357, 0xa49d, 0xace1, 0x9c1b, 0x7357, 0xac9f, 0xac9f, 0x7b97, 0x9c5d, 0xb4e1, 0xb4e1, 
0x9c1b, 0xa49f, 0xacdf, 0x941b, 0x7b57, 0xac9f, 0xb521, 0xb521, 0xb4e1, 0x9c5d, 0x9c5b, 0x9c5f, 0x8bd9, 0x9c1d, 0xacdf, 0xac9f, 0x941b, 0x83d9, 0x8397, 0x9c5f, 0xac9f, 0x7355, 0x9c5d, 0xac9f, 0x9c5d, 0x7355, 0xac9f, 0xac9f, 0x7b97, 0x9c5d, 0xacdf, 0xb4e1, 
0xa45d, 0xa4df, 0xb4e1, 0x8bd9, 0x8b99, 0xacdf, 0xb4e1, 0xace1, 0xb4df, 0x8c1b, 0x9c1b, 0x9c9d, 0x8399, 0xac5f, 0xacdf, 0xacdf, 0x8399, 0x941b, 0x7b57, 0xa49d, 0xa49f, 0x7b57, 0x941b, 0xb521, 0x9c1d, 0x7355, 0xa45d, 0xac9f, 0x7397, 0x9c1b, 0xace1, 0xb4e1, 
};

static Gfx RGBA16sandMM_dummy_aligner2[] = { gsSPEndDisplayList() };

unsigned short RGBA16sandMM_buf[2744] = {
	0xac9f, 0xad21, 0xac9f, 0x7b57, 	0xa45d, 0xad21, 0xac9f, 0xb4df, 
	0xa49f, 0x8397, 0xa49f, 0xb4df, 	0x8399, 0xa49f, 0xa45d, 0xa4df, 
	0xac9f, 0x7b97, 0xa45d, 0xace1, 	0xa49d, 0x7b57, 0xb4e1, 0xac9f, 
	0x8c19, 0xa49f, 0xac9f, 0x83d9, 	0x9c1b, 0xac9f, 0xace1, 0x8bd9, 
	0xac5d, 0x7357, 0xac9f, 0xad21, 	0xac9f, 0xb4e1, 0xa49d, 0xace1, 
	0x9c5d, 0xb4e1, 0x9c5d, 0x7b97, 	0xa49d, 0xac9f, 0x8bd9, 0x941b, 
	0xa45d, 0xb4df, 0xa49f, 0x7b57, 	0xa49d, 0xac9f, 0x9c9f, 0x7b57, 
	0xac9f, 0x7b97, 0x941b, 0xa49f, 	0xb4df, 0x8bd9, 0xa49f, 0xa49f, 
	0xa49f, 0xb4df, 0xa49f, 0x7b57, 	0x9c5d, 0xb4e1, 0xb4df, 0xad21, 
	0xac9f, 0x7b57, 0xa49d, 0xb4e1, 	0x8bd9, 0x7b99, 0xac9f, 0xac9f, 
	0xa49f, 0x7b97, 0xa45d, 0xb4df, 	0x9c5d, 0x7b97, 0x9c5f, 0xac9f, 
	0x9c5b, 0xac9f, 0x9c9f, 0x8357, 	0xa49d, 0xac9f, 0xac9f, 0x83d9, 
	0xac9f, 0x7b97, 0xa49f, 0xb4df, 	0xacdf, 0xac9f, 0x9c1b, 0xace1, 
	0xa45d, 0xace1, 0x9c9d, 0x7b57, 	0xac9f, 0xac9f, 0x9c5d, 0x7b57, 
	0xa49f, 0xacdf, 0x9c9d, 0x8357, 	0x9c5d, 0xac9f, 0xa45d, 0x7357, 
	0x9c1b, 0x7b99, 0xa45d, 0xa4df, 	0xac9f, 0x7b97, 0xa49d, 0xac9f, 
	0xa45d, 0xad21, 0xac9f, 0x7b57, 	0x9c5b, 0xace1, 0xb4e1, 0xb4df, 
	0x9c5d, 0x7357, 0xac9f, 0xa49f, 	0x9c5d, 0x7b55, 0xac9f, 0xace1, 
	0x9c5d, 0x7355, 0xa49f, 0xb49f, 	0xacdf, 0x7357, 0x9c1b, 0xa49f, 
	0xa49d, 0xa49f, 0x93db, 0x83d9, 	0xac9f, 0xacdf, 0xac9f, 0x7b97, 
	0xac9f, 0x7b97, 0x9c5d, 0xb4e1, 	0xac9f, 0xace1, 0x9c1b, 0xacdf, 
	0xa4df, 0xb49f, 0x9c5d, 0x7b57, 	0xac9f, 0xac9f, 0x945d, 0x7b55, 
	0xa49f, 0xb49f, 0x9c9d, 0x7b57, 	0x941b, 0xac9f, 0xa4df, 0x7b57, 
	0x83d9, 0x8bd9, 0xac9f, 0xa49f, 	0xac9f, 0x7357, 0xa49f, 0xac9f, 
	0x9c1b, 0xad21, 0xac9f, 0x7b57, 	0x941b, 0xacdf, 0xac9f, 0xace1, 
	0x9c5b, 0x7b57, 0xa49f, 0xb4e1, 	0x941b, 0x7b57, 0xac9f, 0xac9f, 
	0x9c5d, 0x7355, 0xa49f, 0xac9f, 	0xacdf, 0x7b57, 0x8bdb, 0xacdf, 
	0xac9f, 0xa49f, 0x8397, 0x8bdb, 	0xac9f, 0xacdf, 0xac9f, 0x7b97, 
	0xb4df, 0x83d9, 0x8bd9, 0xb4e1, 	0xb4df, 0xa49f, 0x93db, 0xacdf, 
	0xac9f, 0xacdf, 0x9c5d, 0x7357, 	0xacdf, 0xac9f, 0x8bd9, 0x8399, 
	0xa45d, 0xacdf, 0x9c5d, 0x7357, 	0x93db, 0xa4df, 0xb4df, 0x7357, 
	0x7b57, 0x8bdb, 0xac9f, 0x9c9d, 	0x9c9d, 0x7315, 0xacdf, 0xac9f, 
	0x8bd9, 0xb4e1, 0xb4df, 0x83d9, 	0x8bd9, 0xace1, 0xb4e1, 0xa4df, 
	0x9c1b, 0x8399, 0xa49f, 0xb521, 	0x93d9, 0x7b97, 0xac9f, 0xac9f, 
	0x945b, 0x7b57, 0x9c5f, 0xac9f, 	0xb51f, 0x7b99, 0x8b99, 0xa49f, 
	0xac9f, 0xa49f, 0x7355, 0x941b, 	0xac9f, 0xac9f, 0xa49f, 0x7b97, 
	0xb4df, 0x8bdb, 0x8bd9, 0xacdf, 	0xb4e1, 0xa4df, 0x7b97, 0xac9f, 
	0xac9f, 0xb4e1, 0x93d9, 0x83d9, 	0xad1f, 0xb4e1, 0x945d, 0x8b99, 
	0xac9f, 0xac9f, 0x9c5d, 0x7357, 	0x8bd9, 0xa49f, 0xac9f, 0x83d9, 
	0x7355, 0x9c1b, 0xac9f, 0xa49f, 	0x9c5f, 0x7b55, 0xa49f, 0xacdf, 
	0x8bd9, 0xace1, 0xb4df, 0x8bdb, 	0x8397, 0xacdf, 0xb4e1, 0xb4e1, 
	0x8c1b, 0x8b99, 0xa4df, 0xac9f, 	0x8c1b, 0x8b99, 0xa4df, 0xb4e1, 
	0xa45d, 0x7357, 0xacdf, 0xacdf, 	0xac9f, 0x8399, 0x8c1b, 0xac9f, 
	0xb4df, 0xa49f, 0x7b57, 0x9c5d, 	0xa49f, 0xac9f, 0x9c9d, 0x7315, 
	0xace1, 0x9c5b, 0x8399, 0xb4df, 	0xb4e1, 0xacdf, 0x7b57, 0xa49f, 
	0xb4e1, 0xa49f, 0x941b, 0x8bd9, 	0xac9f, 0xac9f, 0x941b, 0x8bd9, 
	0xac9f, 0xace1, 0x9c5d, 0x7357, 	0x941b, 0xa4df, 0xacdf, 0x8357, 
	0x8357, 0x9c9f, 0xac9f, 0x9c9d, 	0x9c5f, 0x7b55, 0xb49f, 0xb4df, 
	0x8bd9, 0xace1, 0xb4df, 0x9c5d, 	0x7b57, 0xb4df, 0xace1, 0xb4df, 
	0x8bdb, 0x8bd9, 0xb4e1, 0xa49f, 	0x8bd9, 0x8bd9, 0xacdf, 0xb4df, 
	0x9c5d, 0x7b57, 0xac9f, 0xacdf, 	0xacdf, 0x7b59, 0x9c5d, 0xac9f, 
	0xacdf, 0x9c5d, 0x7b57, 0x9c9d, 	0xac9f, 0xb4df, 0xa49f, 0x7315, 
	0xb4e1, 0x945b, 0x8bd9, 0xace1, 	0xb521, 0xac9f, 0x7b57, 0xac9f, 
	0xac9f, 0xace1, 0x8c1b, 0x8bd9, 	0xacdf, 0xaca1, 0x9419, 0x8399, 
	0xa49f, 0xb4df, 0x9c5d, 0x8397, 	0x9c1d, 0xacdf, 0xac9f, 0x7397, 
	0x7315, 0xa49f, 0xb4e1, 0x9c5d, 	0xa49f, 0x7315, 0xac9f, 0xac9f, 
	0x7b97, 0xb4e1, 0xb4df, 0x9c5d, 	0x7b57, 0xacdf, 0xace1, 0xac9f, 
	0x8bd9, 0x941b, 0xb4df, 0xac9f, 	0x8bdb, 0x8c19, 0xb4e1, 0xa49f, 
	0x9c5d, 0x8397, 0xa49f, 0xb4df, 	0xa45f, 0x7397, 0xa45d, 0xac9f, 
	0xac9f, 0x9c5d, 0x7357, 0xa49d, 	0xac9f, 0xac9f, 0xa49f, 0x7355, 
	0xace1, 0x9c5b, 0x7b97, 0xb49f, 	0xb4e1, 0xacdf, 0x7357, 0xac9f, 
	0xb4e1, 0xacdf, 0x8bd9, 0x941b, 	0xac9f, 0xb521, 0x93db, 0x941b, 
	0xa49f, 0xb4e1, 0x941b, 0x8397, 	0xa49d, 0xac9f, 0xa49f, 0x7b57, 
	0x8399, 0x9c5d, 0xb4df, 0x9c5d, 	0xac9f, 0x7357, 0xac9f, 0xacdf, 
	0x7b97, 0xb4e1, 0xb4e1, 0x9c5d, 	0x7355, 0xb4df, 0xace1, 0xb4e1, 
	0x8c1b, 0x93d9, 0xa49f, 0xac9f, 	0x83d9, 0x93db, 0xa4df, 0xb4e1, 
	0x9c5b, 0x7b99, 0xac9f, 0xb4df, 	0xa49f, 0x7b57, 0xa49d, 0xac9f, 
	0xa49f, 0x9c1d, 0x9c9d, 0x93db, 	0xa49d, 0xb4e1, 0xa4df, 0x7b57, 
	0xb521, 0x9c5d, 0x7b97, 0xb49f, 	0xb4e1, 0xacdf, 0x7b57, 0xa49d, 
	0xacdf, 0xb4e1, 0x93db, 0x8bdb, 	0xa4df, 0xaca1, 0x83d9, 0x93d9, 
	0xac9f, 0xac9f, 0x941b, 0x83d7, 	0xa49f, 0xb4e1, 0x9c9d, 0x8357, 
	0xb49f, 0x8c1b, 0x9c5b, 0x8c1b, 	0xb4df, 0x7b97, 0xa45d, 0xace1, 
	0x7357, 0xb4df, 0xb4e1, 0x9c5d, 	0x7b57, 0xa49d, 0xb4e1, 0xacdf, 
	0x941b, 0x8399, 0xacdf, 0xb4e1, 	0x8bd9, 0x8bdb, 0xb4df, 0xb4df, 
	0x941b, 0x7357, 0xb4df, 0xace1, 	0x9c5d, 0x7b57, 0xac9f, 0xace1, 
	0x9c5b, 0x8bdb, 0xb4df, 0x8c1b, 	0x9c1d, 0xa49f, 0xb4df, 0x7b97, 
	0xb4e1, 0xa49d, 0x7357, 0xb4df, 	0xb4e1, 0xace1, 0x7315, 0xa49f, 
	0xa49f, 0xac9f, 0x9c5b, 0x8399, 	0xa49f, 0xb4e1, 0x8c1b, 0x941b, 
	0xac9f, 0xac9f, 0x941b, 0x7b97, 	0xac9f, 0xacdf, 0x9c5d, 0x7357, 
	0xb4e1, 0x945b, 0x941b, 0x8399, 	0xacdf, 0x8b99, 0x8b99, 0xb521, 
	0x7357, 0xb4df, 0xb4e1, 0xa49d, 	0x7357, 0xa45d, 0xacdf, 0xb4e1, 
	0x9c5d, 0x8399, 0xb4df, 0xb4df, 	0x83d9, 0x8bdb, 0xac9f, 0xac9f, 
	0x945b, 0x7b57, 0xa49f, 0xb4e1, 	0xa45d, 0x7357, 0xacdf, 0xacdf, 
	0x93d9, 0x8399, 0xb4e1, 0x9c5d, 	0x7b97, 0xac9f, 0xb4e1, 0x8bd9, 
	0xace1, 0xa45d, 0x7315, 0xacdf, 	0xb4df, 0xb4e1, 0x7355, 0x9c5f, 
	0xa49f, 0xb4e1, 0x9c9d, 0x8397, 	0xa49f, 0xb4e1, 0x8bd9, 0x8bd9, 
	0xa49f, 0xac9f, 0x9c5d, 0x7b57, 	0xac9f, 0xacdf, 0x9c5d, 0x7357, 
	0xad21, 0xa45d, 0x941b, 0x8b99, 	0xb4e1, 0x941b, 0x7b97, 0xac9f, 
	0x7315, 0xacdf, 0xace1, 0xac9d, 	0x6b17, 0x9c5b, 0xb4df, 0xac9f, 
	0x9c5f, 0x8397, 0xa49d, 0xb4e1, 	0x8bdb, 0x8bd9, 0xa49f, 0xac9f, 
	0x9c5d, 0x7357, 0xa49d, 0xb4e1, 	0x9c5d, 0x7b57, 0xac9f, 0xacdf, 
	0x8bdb, 0x8bd9, 0xacdf, 0xac9f, 	0x7357, 0xa45d, 0xb521, 0x9c5d, 
	0xace1, 0xac9d, 0x7315, 0xacdf, 	0xb521, 0xb4e1, 0x6b17, 0x9c1b, 
	0xac5f, 0xad21, 0xa49d, 0x7b97, 	0xa49f, 0xac9f, 0x93db, 0x8397, 
	0xa49f, 0xac9f, 0x9c9d, 0x7b57, 	0xacdf, 0xacdf, 0x9c5d, 0x7b57, 
	0xacdf, 0xac9f, 0x8b99, 0x8bdb, 	0xb4e1, 0x9c5d, 0x7357, 0xa49d, 
	0x7315, 0xacdf, 0xace1, 0xac9f, 	0x7357, 0x9c5b, 0xb4e1, 0xb4e1, 
	0xa4df, 0x7b57, 0xa45d, 0xa49f, 	0x9c5b, 0x8399, 0xa49f, 0xac9f, 
	0x9c9d, 0x7b57, 0xa45d, 0xa45d, 	0x9c5d, 0x7b57, 0xa4df, 0xb4df, 
	0x8b9b, 0x8bd9, 0xace1, 0xac9f, 	0x7b57, 0x9c5d, 0xb521, 0x9c5d, 
	0xace1, 0xac9f, 0x7357, 0xac9d, 	0xacdf, 0xb4e1, 0x7b57, 0x9c5d, 
	0x9c5f, 0xacdf, 0xa49f, 0x7b55, 	0xac9f, 0xac9f, 0x941b, 0x7b57, 
	0x9c5d, 0xa49f, 0x9c9d, 0x8357, 	0xacdf, 0xa49f, 0x9c1d, 0x7355, 
	0xa49f, 0xac9f, 0x93db, 0x8bd9, 	0xb4df, 0xa49f, 0x7357, 0x9c5d, 
	0x7b97, 0xac5f, 0xacdf, 0xa49d, 	0x7b57, 0xa45d, 0xb521, 0xacdf, 
	0xb4df, 0x8399, 0x9c5d, 0xb4df, 	0x9c5d, 0x7357, 0xac9f, 0xb4df, 
	0x9c5d, 0x7b97, 0x9c1d, 0x9c5d, 	0x9c5d, 0x8357, 0xa4df, 0xb49f, 
	0x8c1b, 0x8399, 0xac9f, 0xac9f, 	0x7357, 0x9c5d, 0xb4e1, 0xacdf, 
	0xb4df, 0xa45f, 0x8399, 0xa49d, 	0xb521, 0xb4e1, 0x7b97, 0xa45d, 
	0x9c1b, 0xacdf, 0xb4e1, 0x83d9, 	0xa49f, 0xb4e1, 0x9c5d, 0x8397, 
	0x8c19, 0xa45f, 0x9c5d, 0x8399, 	0xa49f, 0xb4df, 0xa45d, 0x7b97, 
	0xace1, 0xb4df, 0x941b, 0x8357, 	0xb4df, 0xac9f, 0x7b97, 0x941d, 
	0x8bd9, 0xac9f, 0xa49f, 0x9c5d, 	0x8397, 0xa49f, 0xb4df, 0xb4e1, 
	0xb521, 0x941b, 0x9c5b, 0xa49f, 	0x9c1d, 0x83d9, 0xac9f, 0xac9f, 
	0x945b, 0x8b99, 0x8bd9, 0x9c5d, 	0xa49f, 0x7b57, 0xa45d, 0xa49f, 
	0x941b, 0x7357, 0xac9f, 0xb51f, 	0x7b57, 0x9c5d, 0xb4e1, 0xb4e1, 
	0xacdf, 0x9c1d, 0x8bd9, 0xac9f, 	0xb4e1, 0xb4e1, 0x7355, 0xacdf, 
	0x9c1b, 0xa4df, 0xb4e1, 0x945b, 	0xb4df, 0xb4df, 0x941b, 0x941b, 
	0x8bd9, 0x9c5d, 0x941d, 0x8bd9, 	0xa49d, 0xace1, 0xa45d, 0x7357, 
	0xac9f, 0xac9f, 0x9c1b, 0x7357, 	0xb4e1, 0xb4e1, 0x7b97, 0x9c5d, 
	0x9c1b, 0xa49f, 0xacdf, 0x941b, 	0x7b57, 0xac9f, 0xb521, 0xb521, 
	0xb4e1, 0x9c5d, 0x9c5b, 0x9c5f, 	0x8bd9, 0x9c1d, 0xacdf, 0xac9f, 
	0x941b, 0x83d9, 0x8397, 0x9c5f, 	0xac9f, 0x7355, 0x9c5d, 0xac9f, 
	0x9c5d, 0x7355, 0xac9f, 0xac9f, 	0x7b97, 0x9c5d, 0xacdf, 0xb4e1, 
	0xb4e1, 0x8bd9, 0xa45d, 0xa4df, 	0xb4e1, 0xace1, 0x8b99, 0xacdf, 
	0x9c1b, 0x9c9d, 0xb4df, 0x8c1b, 	0xacdf, 0xacdf, 0x8399, 0xac5f, 
	0x7b57, 0xa49d, 0x8399, 0x941b, 	0x941b, 0xb521, 0xa49f, 0x7b57, 
	0xa45d, 0xac9f, 0x9c1d, 0x7355, 	0xace1, 0xb4e1, 0x7397, 0x9c1b, 
	0xa49f, 0xa45d, 0x9c5d, 0xacdf, 	0xa45d, 0x9c5d, 0x941b, 0xa49f, 
	0x9c5d, 0x9c1b, 0x9c5d, 0x9c5d, 	0x9c5d, 0x9c5d, 0x941b, 0xa49f, 
	0x9c5d, 0xacdf, 0xa49d, 0x9c5d, 	0x941b, 0xa45d, 0x9c5d, 0x9c5d, 
	0x9c5d, 0x9c5d, 0x9c5d, 0x9c5d, 	0x9c5d, 0xa45d, 0xa45d, 0x9c5d, 
	0x9c5d, 0xa45d, 0x9c1b, 0xace1, 	0x9c5d, 0x9c5d, 0x941b, 0xa45d, 
	0x945d, 0x9c5d, 0x9c5d, 0x941b, 	0xa49f, 0x941b, 0xa45d, 0x9c5d, 
	0x941b, 0xacdf, 0x941b, 0xa45d, 	0x941b, 0xa45d, 0x941b, 0x9c5d, 
	0xa45d, 0x941b, 0x941b, 0x9c5d, 	0xa49d, 0x9c5d, 0xac9f, 0x8bdb, 
	0x941b, 0xac9f, 0x941b, 0xace1, 	0x941b, 0xa45d, 0x941b, 0xa45d, 
	0x941b, 0x9c1d, 0xa49d, 0x8bdb, 	0xa49f, 0x8bd9, 0xa49f, 0x9c5d, 
	0x8bdb, 0xb4e1, 0x8bd9, 0xac9f, 	0x941b, 0xa49d, 0x941b, 0xa49d, 
	0xa45d, 0x941b, 0x9c1d, 0x9c5d, 	0xa49f, 0x945d, 0xac9f, 0x8bdb, 
	0x8bd9, 0xacdf, 0x93db, 0xace1, 	0x941b, 0xa49f, 0x941b, 0xa49d, 
	0x9c1d, 0x9c5d, 0xa45d, 0x941d, 	0xac9f, 0x8bdb, 0xac9f, 0x9c5d, 
	0x8bdb, 0xace1, 0x8bd9, 0xac9f, 	0x941b, 0xa49f, 0x941b, 0xac9f, 
	0x9c5d, 0x9c5d, 0x9c5d, 0xa45d, 	0xac9f, 0x9c5d, 0xac9f, 0x8bdb, 
	0x8bd9, 0xacdf, 0x8bd9, 0xace1, 	0x941b, 0xa49f, 0x941b, 0xa49f, 
	0x9c5b, 0xa45d, 0x9c5d, 0x9c5d, 	0xa49f, 0x9c5d, 0xa49d, 0x9c5d, 
	0x8bd9, 0xacdf, 0x8bd9, 0xacdf, 	0x941b, 0xa49f, 0x941b, 0xa49f, 
	0x9c5d, 0x9c5d, 0x941b, 0xa45d, 	0x9c5d, 0xa49d, 0x9c5d, 0xa45d, 
	0x8bd9, 0xacdf, 0x8bd9, 0xacdf, 	0x9c5d, 0xa45d, 0x941b, 0xa45f, 
	0x941b, 0x9c5d, 0x9c1d, 0x9c5d, 	0x941b, 0xa45d, 0x941b, 0xac9f, 
	0x8bd9, 0xac9f, 0x8bd9, 0xacdf, 	0x941b, 0xa45d, 0x9c5d, 0xa45d, 
	0x9c1d, 0x9c5d, 0x941d, 0x9c5d, 	0x8bdb, 0xac9f, 0x941b, 0xa49d, 
	0x8bd9, 0xacdf, 0x8bdb, 0xacdf, 	0x9c5d, 0x9c5d, 0x941b, 0x9c5d, 
	0x9c5d, 0x9c1d, 0x941b, 0x9c5d, 	0x941b, 0xa49f, 0x8bdb, 0xac9f, 
	0x93db, 0xacdf, 0x941b, 0xac9f, 	0x941b, 0xa45d, 0xa49d, 0x9c5d, 
	0x941b, 0x9c5d, 0x9c5d, 0x941b, 	0x8bdb, 0xac9f, 0x941b, 0xa45d, 
	0x9c5d, 0xa49f, 0x941b, 0xb4df, 	0xacdf, 0x9c5b, 0x9c5d, 0xa49d, 
	0x9c5d, 0x93db, 0x9c1d, 0x9c5d, 	0x941b, 0xa45d, 0x941b, 0xac9f, 
	0x8bdb, 0xb4e1, 0xa45d, 0xa49f, 	0x941b, 0xac9f, 0xacdf, 0x9c5d, 
	0x9c1d, 0x941b, 0x941b, 0x8bd9, 	0x8c1b, 0xac9f, 0x941b, 0x9c5d, 
	0xa49f, 0xa45d, 0xa49d, 0x9c5d, 	0x9c5d, 0x9c5d, 0x9c5d, 0x9c5d, 
	0x9c5d, 0x9c5d, 0x9c5d, 0xa45d, 	0x9c5d, 0x9c5d, 0x9c5d, 0x9c5d, 
	0x9c5d, 0x9c5d, 0x9c5d, 0x9c5d, 	0x9c1d, 0x9c5d, 0x9c5d, 0x9c5d, 
	0x9c5d, 0x9c5d, 0x941b, 0x9c5d, 	0x9c5d, 0x9c5d, 0x9c5d, 0x9c5d, 
	0x9c5b, 0x9c5d, 0x9c5d, 0x9c5d, 	0x9c5d, 0x9c5d, 0x9c5d, 0xa45d, 
	0xa45d, 0x9c5d, 0x9c5b, 0x9c5d, 	0x9c5d, 0x9c5d, 0x9c5d, 0x9c5d, 
	0x9c5d, 0x9c5d, 0xa49d, 0x9c5d, 	0x9c5d, 0x9c1d, 0x9c5d, 0x9c1d, 
	0xac9f, 0x9c5d, 0xa45d, 0x9c5d, 	0x9c1b, 0x9c5d, 0x9c5d, 0x9c1d, 
	0xa45d, 0xa45d, 0x9c5d, 0x9c5d, 	0x9c5d, 0x9c5d, 0x9c5d, 0x9c5d, 
	0x9c5d, 0x9c5d, 0x9c5d, 0x9c5d, 	0x9c5d, 0x9c5d, 0x9c5d, 0xa45d, 
	0x9c5d, 0x9c5d, 0x0000, 0x0000, 	0x0000, 0x0000, 0x9c5d, 0x9c5d, 
	0x9c5d, 0x0000, 0x0000, 0x0000, };

Gfx RGBA16sandMM_dl[] = {
	gsDPSetTextureImage( 0, 2, 1, RGBA16sandMM_buf),
	gsDPSetTile( 0, 2, 0, 0, G_TX_LOADTILE, 0, 0, 0, 0, 0, 0, 0),
	gsDPLoadBlock( G_TX_LOADTILE, 0, 0, 1372, 0),
	gsDPSetTile(0, 2, 8, 0, 0, 0, 1, 5, 0, 1, 5, 0),
	gsDPSetTileSize( 0,  0, 0, 31 << G_TEXTURE_IMAGE_FRAC, 31 << G_TEXTURE_IMAGE_FRAC),
	gsDPSetTile(0, 2, 4, 256, 1, 0, 1, 4, 1, 1, 4, 1),
	gsDPSetTileSize( 1,  0, 0, 15 << G_TEXTURE_IMAGE_FRAC, 15 << G_TEXTURE_IMAGE_FRAC),
	gsDPSetTile(0, 2, 2, 320, 2, 0, 1, 3, 2, 1, 3, 2),
	gsDPSetTileSize( 2,  0, 0, 7 << G_TEXTURE_IMAGE_FRAC, 7 << G_TEXTURE_IMAGE_FRAC),
	gsDPSetTile(0, 2, 1, 336, 3, 0, 1, 2, 3, 1, 2, 3),
	gsDPSetTileSize( 3,  0, 0, 3 << G_TEXTURE_IMAGE_FRAC, 3 << G_TEXTURE_IMAGE_FRAC),
	gsDPSetTile(0, 2, 1, 340, 4, 0, 1, 1, 4, 1, 1, 4),
	gsDPSetTileSize( 4,  0, 0, 1 << G_TEXTURE_IMAGE_FRAC, 1 << G_TEXTURE_IMAGE_FRAC),
	gsDPSetTile(0, 2, 1, 342, 5, 0, 1, 0, 5, 1, 0, 5),
	gsDPSetTileSize( 5,  0, 0, 0 << G_TEXTURE_IMAGE_FRAC, 0 << G_TEXTURE_IMAGE_FRAC),
	gsSPEndDisplayList(),
};
