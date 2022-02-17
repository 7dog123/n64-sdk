/* 2D Animation Previewer for NINTENDO64 */ 
/* This file created by anmview.exe */ 
/* Do not edit */ 

#ifndef  __ANIMEVIEWERDATA__ 
#define  __ANIMEVIEWERDATA__ 

/* Texture structure */
#ifndef	_teTMF_
#define	_teTMF_

struct teTMF {
	u32*	img;
	u32		fmt;
	u32		siz;
	u32		width;
	u32		height;
};

#endif

/* Palette structure */

#ifndef	_teTLF_
#define	_teTLF_

struct teTLF {
	u32		type;
	u16*	tlut;
	u16		size;
};

#endif
#endif // __ANIMEVIEWERDATA__
