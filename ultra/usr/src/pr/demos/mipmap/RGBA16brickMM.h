/*
 * Do not edit this file.  It was automatically generated
 * by "rgb2c" from the file "brick.rgb".
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
 *   gsDPLoadTextureBlock (RGBA16brickMM, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, 0
 *     G_TX_WRAP | G_TX_NOMIRROR, G_TX_WRAP | G_TX_NOMIRROR,
 *     G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
 */

#if 0	/* Image preview */
	+--------------------------------+
	|%%oo***%%%####%%%%%%#%%%%#%##%%%|
	|,,,,,,,,%,,,,,,,,,,,,,,~*,,,,,,,|
	|,,,,,,,.#,,,,,,,,,,,,,,,*,,,,,,,|
	|,,,,,,,.#,,,,,,,,.,,,,,.o,,,,,,,|
	|.,,,,,,.#,,,,,,,...,,,,,*,,,,,,,|
	|,,,,,,,,#,,,,,,,,,,,,,,,o,,,,,,,|
	|,,,,,,,,#,,,,,,,,,,,,,,,o,,,,,,,|
	|.......~#~,........,...~*,,.....|
	|%#%%%%%%%%%#%%*%%##%%%%%%%%#*%%%|
	|%,,,,,,,,,,,,,,~#,,,,,,,,,,,,,,~|
	|o,,,,,,,,,.,,.,.#,,,,,,,,,.,,,,~|
	|*,...,,,,,.,.,,.#,..,,,,,,.,.,,,|
	|%,,,.,,,,,,,,,,.%,,,,,,,,,,,,,,~|
	|*,,,,,,,,,,,,,..#,,,,,,,,,,,,,.,|
	|%.,,,,,,,,,,...,%,,.,,,,,,,,.,.~|
	|%o+~++++++~+~++o%%o+~~~~++~~+oo%|
	|%%%*%%%**%oo++o*oo*o*%o*%%%%%%*%|
	|,,,.,,,,#,,,.,,,,,,.,,,,%,,.,,,,|
	|,,,,,,,,#,,,,,,,,,,,,,,.%,,.,,,,|
	|,,,,,,,~#,,,,,.,,,,,,,,.#,,,,,,.|
	|.,,,,,,,#,,,,,,,.,,,,,,.#,,,,,,,|
	|,,.,,,,~%,.,,,,,,,,,,,,,%,,,,,,,|
	|,,,,,,,~%,,,,,,,,,,,,,,.%,,,,,,,|
	|,,,,.,,%%,.............+%,.,,,,,|
	|%%#####%%%%####%%%%%%**%%%**%***|
	|*,,,,,,,,,,,,,,~%,,,,,,,,,,,,,,~|
	|%,,,,,,,,,.,,.,,#,,,,,,,,,,,,,,,|
	|%,...,,,,,,,.,,.#,..,,,,,,.,.,,.|
	|%,,,.,,,,,,,,,,,#,,,,,,,,,,,,,,,|
	|%,,,,,,,,,,,,,..%,,,,,,,,,,,,,..|
	|%,,,,,,,,,,,,,..*,,,,,,,,,,,,,,.|
	|%~,,,,,,,,,,,,,+*o+~++++~+~~~~,+|
	+--------------------------------+
#endif

#ifdef __MWERKS__
#pragma align(16)
#else
static Gfx RGBA16brickMM_dummy_aligner2[] = { gsSPEndDisplayList() };
#endif

unsigned short RGBA16brickMM_buf[] = {
	0xd631, 0xd5ef, 0xace7, 0xa4a3, 	0xbd6b, 0xbd6b, 0xc56b, 0xde73, 
	0xd673, 0xe6f7, 0xef39, 0xf779, 	0xef39, 0xeef9, 0xde71, 0xeef7, 
	0xe6f7, 0xe6b5, 0xe6f7, 0xeeb7, 	0xef37, 0xde33, 0xd671, 0xe6f7, 
	0xdeb5, 0xf739, 0xe6b7, 0xf77b, 	0xf77b, 0xe6b5, 0xe6f5, 0xd5f1, 
	0x8005, 0x6841, 0x7801, 0x8003, 	0x7843, 0x598d, 0x8043, 0x8001, 
	0x7843, 0x7041, 0xde73, 0x78c7, 	0x6801, 0x8043, 0x7003, 0x7843, 
	0x8803, 0x6803, 0x8003, 0x7803, 	0x7841, 0x7295, 0x7841, 0x8003, 
	0x7801, 0x7003, 0xcd6b, 0x7043, 	0x7043, 0x7803, 0x6841, 0x7803, 
	0x8041, 0x8841, 0x8843, 0x7003, 	0x7001, 0x7001, 0x8801, 0x2885, 
	0xef39, 0x8801, 0x6841, 0x7041, 	0x8001, 0x8801, 0x8041, 0x8041, 
	0x8041, 0x8841, 0x8843, 0x7001, 	0x7001, 0x7001, 0x8801, 0x414b, 
	0xcce7, 0x8041, 0x7001, 0x7041, 	0x6843, 0x7041, 0x8041, 0x8041, 
	0x7803, 0x8003, 0x7843, 0x7041, 	0x8043, 0x2085, 0x8003, 0x7801, 
	0x8881, 0x8041, 0xf739, 0x9003, 	0x7801, 0x7803, 0x9041, 0x8801, 
	0x6801, 0x8043, 0x7841, 0x6003, 	0x7841, 0x3887, 0x8003, 0x8001, 
	0x8043, 0x8081, 0xb39d, 0x9001, 	0x7801, 0x7803, 0x7001, 0x7841, 
	0x6003, 0x7801, 0x8041, 0x7043, 	0x7043, 0x6801, 0x7043, 0x3085, 
	0xef39, 0x8003, 0x7041, 0x8043, 	0x8003, 0x8803, 0x8001, 0x7803, 
	0x6801, 0x6001, 0x6003, 0x7043, 	0x6883, 0x6801, 0x7003, 0x4949, 
	0xbce7, 0x8003, 0x6843, 0x8043, 	0x7843, 0x7803, 0x7801, 0x7801, 
	0x7043, 0x7041, 0x6803, 0x8805, 	0x8003, 0x3109, 0x7043, 0x8001, 
	0x8883, 0x8003, 0xf739, 0x7043, 	0x7003, 0x7003, 0x6841, 0x6803, 
	0x6843, 0x7043, 0x6803, 0x7003, 	0x8001, 0x410b, 0x7041, 0x7803, 
	0x8043, 0x8043, 0xbca5, 0x7843, 	0x7003, 0x8003, 0x6801, 0x7843, 
	0x7803, 0x7843, 0x8043, 0x8003, 	0x7003, 0x7843, 0x9003, 0x3109, 
	0xf77d, 0x8041, 0x7003, 0x8003, 	0x7801, 0x9003, 0x8005, 0x8801, 
	0x7803, 0x7843, 0x7843, 0x8003, 	0x6803, 0x8003, 0x8803, 0x38c7, 
	0xbca5, 0x8001, 0x7043, 0x8001, 	0x8003, 0x9003, 0x8803, 0x9003, 
	0x3841, 0x3843, 0x3043, 0x2803, 	0x4041, 0x6a13, 0x3001, 0x3003, 
	0x7043, 0x4003, 0xfffd, 0x9109, 	0x4003, 0x4843, 0x4843, 0x4801, 
	0x5003, 0x6041, 0x5801, 0x4043, 	0x5001, 0x7295, 0x6003, 0x4001, 
	0x5885, 0x4845, 0xcdad, 0x7909, 	0x4043, 0x4843, 0x3043, 0x3801, 
	0xde73, 0xef7b, 0xd631, 0xcdf1, 	0xde73, 0xdeb5, 0xd631, 0xe6f7, 
	0xe6f7, 0xde73, 0xde73, 0xef39, 	0xe6b5, 0xe6f7, 0xd5af, 0xd62f, 
	0xdef7, 0xef39, 0xe739, 0xdeb5, 	0xe6b5, 0xce31, 0xcdf1, 0xe671, 
	0xdeb5, 0xde33, 0xe671, 0xe6f9, 	0xcdab, 0xe6f7, 0xde73, 0xe6b7, 
	0x7843, 0x8085, 0xe673, 0x7003, 	0x8845, 0x9043, 0x8043, 0x8885, 
	0x8045, 0x8043, 0x8045, 0x8043, 	0x7043, 0x69cf, 0x7801, 0x7045, 
	0x7803, 0x7883, 0xf77b, 0x78c7, 	0x8885, 0x9085, 0x8845, 0x8885, 
	0x8845, 0x8845, 0x8885, 0x7841, 	0x7045, 0x6a11, 0x7843, 0x7043, 
	0xbca5, 0x7005, 0x8001, 0x8843, 	0x9003, 0x8043, 0x9045, 0x9003, 
	0x8841, 0x8803, 0x6801, 0x6803, 	0x7003, 0x6001, 0x7005, 0x2843, 
	0xffbd, 0x7045, 0x7801, 0x8003, 	0x9043, 0x8043, 0x9005, 0x9803, 
	0x9043, 0x8083, 0x5003, 0x7001, 	0x7003, 0x6803, 0x6803, 0x59d1, 
	0x5801, 0x5801, 0xc52b, 0x8803, 	0x8043, 0x8801, 0x5801, 0x7845, 
	0x4801, 0x7001, 0x7003, 0x8001, 	0x8843, 0x2805, 0x5801, 0x7801, 
	0x5803, 0x5801, 0xf779, 0x8003, 	0x8003, 0xa003, 0x7043, 0x8085, 
	0x4801, 0x6803, 0x7041, 0x7001, 	0x8003, 0x514b, 0x5801, 0x8001, 
	0xd5ef, 0x7003, 0x7003, 0x6801, 	0x6803, 0x6041, 0x8045, 0x8801, 
	0x7001, 0x7803, 0x7803, 0x8803, 	0x7841, 0x7003, 0x7803, 0x3085, 
	0xeef7, 0x6803, 0x7803, 0x7003, 	0x7801, 0x8043, 0x8085, 0x9801, 
	0x7801, 0x7001, 0x8003, 0x8043, 	0x8003, 0x7003, 0x7803, 0x59cf, 
	0x7801, 0x6843, 0xd5ad, 0x7803, 	0x7843, 0xa801, 0x7803, 0x7003, 
	0x7843, 0x6843, 0x7801, 0x8803, 	0x5803, 0x4085, 0x7005, 0x6843, 
	0x7803, 0x6801, 0xef39, 0x7843, 	0x7803, 0x8843, 0x7845, 0x7003, 
	0x7843, 0x7043, 0x8001, 0x8003, 	0x5803, 0x4109, 0x7045, 0x6803, 
	0xde31, 0x5801, 0x7003, 0x7801, 	0x7003, 0x7843, 0x7003, 0x8001, 
	0x7801, 0x7841, 0x6003, 0x7043, 	0x6001, 0x6001, 0x5803, 0x4109, 
	0xe6b5, 0x7085, 0x7001, 0x6803, 	0x6803, 0x8803, 0x7041, 0x8003, 
	0x7043, 0x7801, 0x6803, 0x7843, 	0x6801, 0x7801, 0x5803, 0x7253, 
	0x839d, 0x6ad7, 0xde73, 0x9c21, 	0x7b9d, 0x6b19, 0x7319, 0x7b9d, 
	0x6ad7, 0x7b9d, 0x6b19, 0x735b, 	0x83df, 0xace7, 0x6295, 0x6b19, 
	0xa4e7, 0x7b9d, 0xde31, 0xd631, 	0x62d7, 0x6ad7, 0x5a53, 0x62d7, 
	0x5a95, 0x6ad7, 0x835d, 0x7bdd, 	0xa4a5, 0xdeb3, 0x7b9f, 0x9421, 
	0xef37, 0xe675, 0xde73, 0xd5ad, 	0xeeb7, 0xeef5, 0xd5ef, 0xc5ad, 
	0xcdad, 0xe673, 0xc4a5, 0xac63, 	0x82d5, 0x9ad7, 0xc4a7, 0xc4e7, 
	0xbca3, 0xbca5, 0xbce9, 0xac1f, 	0xc4a5, 0xd631, 0xbca5, 0xcdad, 
	0xe739, 0xeeb5, 0xdeb5, 0xde73, 	0xe631, 0xd5ef, 0xd56b, 0xde73, 
	0x8803, 0x6803, 0x7803, 0x7801, 	0x6843, 0x514b, 0x7801, 0x8001, 
	0x7803, 0x7001, 0xf739, 0x6883, 	0x7003, 0x7841, 0x6801, 0x7803, 
	0x8803, 0x6801, 0x7801, 0x7803, 	0x7041, 0x50c7, 0x7801, 0x8003, 
	0x7801, 0x6001, 0xde31, 0x7001, 	0x6841, 0x7803, 0x7001, 0x7803, 
	0x8041, 0x8841, 0x8843, 0x7003, 	0x7001, 0x7001, 0x8041, 0x494d, 
	0xff7b, 0x8001, 0x6841, 0x7041, 	0x6803, 0x7041, 0x8041, 0x7041, 
	0x8041, 0x8843, 0x8001, 0x7001, 	0x7001, 0x7003, 0x8801, 0x2885, 
	0xeef7, 0x8001, 0x7001, 0x6041, 	0x6803, 0x7041, 0x8041, 0x8043, 
	0x7803, 0x8003, 0x7003, 0x7041, 	0x8041, 0x59d1, 0x8003, 0x7801, 
	0x8841, 0x8081, 0xff7b, 0x9043, 	0x6801, 0x7001, 0xa801, 0x8001, 
	0x7843, 0x8001, 0x7803, 0x7841, 	0x8001, 0x30c7, 0x8003, 0x7801, 
	0x8043, 0x8041, 0xffbd, 0x9041, 	0x7001, 0x5001, 0x7841, 0x7801, 
	0x6001, 0x7003, 0x6843, 0x6843, 	0x7043, 0x6801, 0x7043, 0x514b, 
	0xef39, 0x8003, 0x7843, 0x6841, 	0x8001, 0x8803, 0x8801, 0x7801, 
	0x6003, 0x7003, 0x6843, 0x7041, 	0x6843, 0x7003, 0x6841, 0x3085, 
	0xff7b, 0x8003, 0x7043, 0x8043, 	0x7001, 0x8003, 0x8001, 0x7803, 
	0x5801, 0x6843, 0x7043, 0x8005, 	0x7841, 0x59cf, 0x7043, 0x8001, 
	0x5003, 0x8041, 0xf6f7, 0x7043, 	0x7843, 0x7805, 0x6803, 0x6801, 
	0x7043, 0x7043, 0x7003, 0x8005, 	0x8001, 0x38c7, 0x7041, 0x8003, 
	0x8883, 0x7803, 0xddef, 0x7043, 	0x7001, 0x7805, 0x6001, 0x7843, 
	0x6803, 0x7043, 0x8001, 0x7843, 	0x7003, 0x8043, 0x8003, 0x7255, 
	0xde2f, 0x8043, 0x7803, 0x8003, 	0x8003, 0x9005, 0x8803, 0x8001, 
	0x7003, 0x7843, 0x7843, 0x7801, 	0x7003, 0x8043, 0x8803, 0x3087, 
	0xe673, 0x8001, 0x7041, 0x8003, 	0x8003, 0x9805, 0x8803, 0x8803, 
	0x40c7, 0x5109, 0x4087, 0x40c5, 	0x590b, 0xe6f7, 0x3887, 0x38c5, 
	0x3843, 0x1843, 0xe673, 0x494b, 	0x1843, 0x3087, 0x2041, 0x1843, 
	0x1803, 0x3085, 0x30c7, 0x3883, 	0x2843, 0x735b, 0x2043, 0x3043, 
	0x4085, 0x38c9, 0xe6f7, 0x714b, 	0x40c7, 0x4909, 0x3107, 0x4109, 
	0xd631, 0xdeb5, 0xef39, 0xf77b, 	0xef39, 0xf77b, 0xf73b, 0xe6f7, 
	0xd671, 0xde33, 0xe6f5, 0xffbd, 	0xf7bd, 0xf77b, 0xf77b, 0xe6f7, 
	0xde73, 0xdef7, 0xd631, 0xcdef, 	0xde73, 0xce31, 0xcdef, 0xde73, 
	0xdeb5, 0xde73, 0xcdf1, 0xc62f, 	0xd673, 0xcdaf, 0xcded, 0xc5af, 
	0x7801, 0x7885, 0xddef, 0x7043, 	0x8085, 0x9043, 0x8885, 0x8885, 
	0x8045, 0x8845, 0x8085, 0x8043, 	0x7045, 0x7a51, 0x7801, 0x6885, 
	0x7003, 0x8083, 0xe675, 0x7883, 	0x8885, 0x9803, 0x8045, 0x8885, 
	0x8085, 0x8843, 0x8885, 0x7843, 	0x7885, 0x7253, 0x7003, 0x6045, 
	0xeeb5, 0x6845, 0x8001, 0x8003, 	0x9043, 0x6803, 0x7803, 0x9043, 
	0x9003, 0x8083, 0x6003, 0x7001, 	0x7803, 0x6003, 0x7003, 0x38c7, 
	0xef79, 0x7005, 0x8001, 0x8043, 	0xa003, 0x8043, 0x9005, 0xa043, 
	0x8803, 0x8083, 0x7803, 0x7001, 	0x7003, 0x6803, 0x6803, 0x3909, 
	0x5001, 0x5801, 0xe675, 0x8801, 	0x7003, 0x9801, 0x6001, 0x7043, 
	0x8001, 0x7001, 0x7043, 0x8801, 	0x8803, 0x3087, 0x5803, 0x8001, 
	0x5001, 0x6001, 0xef39, 0x8803, 	0x9003, 0x8803, 0x9801, 0x8085, 
	0x5801, 0x7001, 0x7801, 0x7803, 	0x8003, 0x3887, 0x5841, 0x8001, 
	0xde31, 0x6803, 0x7003, 0x6801, 	0x6801, 0xb003, 0x7041, 0x8801, 
	0x7001, 0x7801, 0x7003, 0x8043, 	0x8001, 0x7803, 0x7003, 0x38c7, 
	0xef39, 0x6803, 0x7001, 0x7803, 	0x7001, 0x8045, 0x8843, 0x9001, 
	0x6801, 0x7803, 0x8001, 0x8003, 	0x8843, 0x7001, 0x7803, 0x38c9, 
	0x7803, 0x6803, 0xe675, 0x7041, 	0x7801, 0x9043, 0x7003, 0x7043, 
	0x7803, 0x7043, 0x8001, 0x8003, 	0x5803, 0x3087, 0x7045, 0x6843, 
	0x7801, 0x6843, 0xe6b3, 0x7803, 	0x7803, 0x9843, 0x7003, 0x7845, 
	0x7843, 0x7005, 0x8001, 0x8001, 	0x5803, 0x3885, 0x7043, 0x6845, 
	0xe673, 0x7803, 0x7803, 0x7043, 	0x7001, 0x8005, 0x7841, 0x8843, 
	0x7803, 0x8043, 0x7001, 0x8003, 	0x6843, 0x8001, 0x6001, 0x3085, 
	0xcdad, 0x7043, 0x8003, 0x7003, 	0x7803, 0x8803, 0x7043, 0x8843, 
	0x7801, 0x8003, 0x7041, 0x8003, 	0x6043, 0x7803, 0x6843, 0x3885, 
	0x48c9, 0x4949, 0xd631, 0x7295, 	0x494b, 0x494b, 0x410b, 0x598d, 
	0x498d, 0x51cf, 0x3909, 0x498d, 	0x414d, 0x8359, 0x498d, 0x498d, 
	0x8319, 0x6253, 0xcdef, 0xac63, 	0x839d, 0x8b9d, 0x7b19, 0x8319, 
	0x5a13, 0x59cf, 0x7a53, 0x82d7, 	0x51cf, 0x8ad7, 0x5a11, 0x51d1, 
	0xb421, 0x8ad7, 0x8b17, 0x935b, 	0xa4a5, 0xac21, 0xac21, 0xa3df, 
	0xc4a5, 0xb423, 0xb421, 0xac63, 	0xbce7, 0xac21, 0xac21, 0xa3df, 
	0x7801, 0x6843, 0x8041, 0x8043, 	0x8001, 0x8041, 0xa3df, 0x7841, 
	0x7801, 0x7085, 0x8041, 0x7803, 	0x7041, 0x7841, 0x92d7, 0x7841, 
	0x7003, 0x7843, 0x7043, 0x6043, 	0xa3df, 0x8043, 0x8003, 0x7803, 
	0x7003, 0x6803, 0x7043, 0x6843, 	0x9295, 0x7843, 0x7843, 0x7801, 
	0x6803, 0x6885, 0x6803, 0x6843, 	0x7003, 0x7003, 0xac21, 0x7843, 
	0x7003, 0x6845, 0x7003, 0x7043, 	0x7003, 0x7003, 0x92d7, 0x7043, 
	0xac63, 0x9b5b, 0x9b5b, 0xa39d, 	0xc4a5, 0xab9d, 0xa39d, 0x9b5b, 
	0xb4a5, 0xa39d, 0xa35b, 0xa35b, 	0xbc63, 0xab5d, 0x9b5b, 0x9b9d, 
	0x8043, 0x8843, 0x9b19, 0x7803, 	0x7003, 0x6045, 0x8843, 0x7003, 
	0x8043, 0x8845, 0xac21, 0x7003, 	0x7003, 0x6887, 0x8843, 0x6843, 
	0x9b1b, 0x7003, 0x6803, 0x8043, 	0x8001, 0x7803, 0x7003, 0x6043, 
	0xa39f, 0x7003, 0x7843, 0x8043, 	0x8001, 0x7003, 0x7003, 0x6845, 
	0x70c9, 0x7909, 0xac21, 0x7109, 	0x68c7, 0x614b, 0x78c7, 0x7109, 
	0x70c9, 0x78c7, 0xac63, 0x814b, 	0x7109, 0x718f, 0x7909, 0x70c7, 
	0xc4e7, 0xac21, 0xac21, 0xa421, 	0xaca5, 0x9b5b, 0x8253, 0x9b1b, 
	0xb3df, 0xa39d, 0x9b19, 0x9b5b, 	0xb4e9, 0xa421, 0xabe1, 0xb421, 
	0x7801, 0x7085, 0x7841, 0x8003, 	0x7801, 0x7841, 0xb421, 0x7841, 
	0x7801, 0x6843, 0x7841, 0x8001, 	0x7001, 0x7841, 0xa39d, 0x7801, 
	0x7003, 0x7043, 0x7043, 0x7085, 	0xb421, 0x7843, 0x8001, 0x7801, 
	0x7003, 0x7043, 0x7043, 0x6843, 	0xabdf, 0x8043, 0x7801, 0x7801, 
	0x6843, 0x790b, 0x6845, 0x6843, 	0x6803, 0x6803, 0xb421, 0x6843, 
	0x6043, 0x6085, 0x6843, 0x6043, 	0x6845, 0x7045, 0xa39d, 0x7043, 
	0xa421, 0xa3df, 0xabe1, 0xbc63, 	0xbca5, 0xa39d, 0xa3df, 0x9be1, 
	0xac63, 0x935b, 0x935b, 0x9b5b, 	0xbca5, 0x9b5b, 0x935b, 0x935b, 
	0x7843, 0x8043, 0xa39d, 0x7003, 	0x7003, 0x6845, 0x8843, 0x7843, 
	0x8843, 0x9045, 0xa3df, 0x7803, 	0x7003, 0x6885, 0x8843, 0x7843, 
	0x9b5b, 0x6803, 0x7001, 0x8001, 	0x8001, 0x7803, 0x7803, 0x6043, 
	0xa39f, 0x7001, 0x7803, 0x8843, 	0x7801, 0x7803, 0x7843, 0x6043, 
	0x6845, 0x7085, 0xa39d, 0x7085, 	0x6885, 0x5887, 0x7085, 0x7085, 
	0x78c9, 0x8109, 0x9b9d, 0x78c9, 	0x6887, 0x60c7, 0x80c7, 0x70c7, 
	0x9293, 0x81cd, 0x92d7, 0x9251, 	0x9ad7, 0x9253, 0x9ad7, 0x8a53, 
	0x8a11, 0x7803, 0x7803, 0x7043, 	0x818d, 0x7843, 0x7003, 0x7043, 
	0x8a55, 0x89cf, 0xa295, 0x89cf, 	0x9295, 0x89cf, 0x9a55, 0x89cf, 
	0x8043, 0x7045, 0x89d1, 0x7845, 	0x7843, 0x7045, 0x8a13, 0x7845, 
	0xa319, 0x9253, 0x92d7, 0x818d, 	0x9a95, 0x89cf, 0x92d7, 0x9253, 
	0x9253, 0x7801, 0x7043, 0x7043, 	0x8a11, 0x7803, 0x7043, 0x7043, 
	0x8a95, 0x9213, 0xa2d7, 0x8a11, 	0x8a95, 0x81cf, 0x9a95, 0x81cf, 
	0x7843, 0x7043, 0x81d1, 0x7043, 	0x8043, 0x7045, 0x8a11, 0x8045, 
	0x818d, 0x818d, 0x898d, 0x898d, 	0x814d, 0x894d, 0x814d, 0x898d, 
	0x898f, 0x898d, 0x814d, 0x898d, 	0x818d, 0x898d, 0x818d, 0x898d, 
	0x818d, 0x898d, 0x0000, 0x0000, 	0x0000, 0x0000, 0x898d, 0x898d, 
	0x898d, 0x0000, 0x0000, 0x0000, };

Gfx RGBA16brickMM_dl[] = {
	gsDPSetTextureImage( 0, 2, 1, RGBA16brickMM_buf),
	gsDPSetTile( 0, 2, 0, 0, G_TX_LOADTILE, 0, 0, 0, 0, 0, 0, 0),
	gsDPLoadBlock( G_TX_LOADTILE, 0, 0, 1372, 0),
	gsDPSetTile(0, 2, 8, 0, 0, 0, 0, 5, 0, 0, 5, 0),
	gsDPSetTileSize( 0,  0, 0, 31 << G_TEXTURE_IMAGE_FRAC, 31 << G_TEXTURE_IMAGE_FRAC),
	gsDPSetTile(0, 2, 4, 256, 1, 0, 0, 4, 1, 0, 4, 1),
	gsDPSetTileSize( 1,  0, 0, 15 << G_TEXTURE_IMAGE_FRAC, 15 << G_TEXTURE_IMAGE_FRAC),
	gsDPSetTile(0, 2, 2, 320, 2, 0, 0, 3, 2, 0, 3, 2),
	gsDPSetTileSize( 2,  0, 0, 7 << G_TEXTURE_IMAGE_FRAC, 7 << G_TEXTURE_IMAGE_FRAC),
	gsDPSetTile(0, 2, 1, 336, 3, 0, 0, 2, 3, 0, 2, 3),
	gsDPSetTileSize( 3,  0, 0, 3 << G_TEXTURE_IMAGE_FRAC, 3 << G_TEXTURE_IMAGE_FRAC),
	gsDPSetTile(0, 2, 1, 340, 4, 0, 0, 1, 4, 0, 1, 4),
	gsDPSetTileSize( 4,  0, 0, 1 << G_TEXTURE_IMAGE_FRAC, 1 << G_TEXTURE_IMAGE_FRAC),
	gsDPSetTile(0, 2, 1, 342, 5, 0, 0, 0, 5, 0, 0, 5),
	gsDPSetTileSize( 5,  0, 0, 0 << G_TEXTURE_IMAGE_FRAC, 0 << G_TEXTURE_IMAGE_FRAC),
	gsSPEndDisplayList(),
};