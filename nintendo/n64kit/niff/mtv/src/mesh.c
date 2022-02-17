/*
 *	mesh.c
 *
 *	Split a large texture into tiles.
 *	A small texture can be viewed using wrap.
 *
 *  Copyright (C) 1998-1999, NINTENDO Co.,Ltd.
 *  Copyright (C) 1998-1999, MONEGI CORPORATION
 */

#include	<ultra64.h>
#include	<nusys.h>
#include	"mesh.h"
#include	"gfx.h"

extern	setup_info	set_inf;

MeshManager mm;

	/*	The maximum value of vertex	*/
#define	MAX_VERTEX	(32)
	/*	The maximum number of squares which can be expressed as polygon,when the vertex value is "MAX_VERTEX". */
#define	MAX_SQUARE	(MAX_VERTEX/4)

#define	_TEST_YUV	1

/*****************************************************
 *		mesh_Init
 *
 *		Creating a display list for mesh.
 *****************************************************/
void	mesh_Init(texture_data* ptxdata,int frame)
{
	mesh_CalcGrid(ptxdata);
	mesh_CalcVertex(ptxdata);
	mesh_makeDisplayList(ptxdata);
}

/*******************************************************
 *		mesh_CalcGrid
 *
 *		Calculating the grid in mesh. 
 *******************************************************/
int mesh_CalcGrid(texture_data* ptxdata)
{
	texture_info*	pti = ptxdata->pti;
	u16	gridW,gridH,gridPitchW;
	u16	min_gridW,min_gridH;
	u16	numX,numY;
	u16 imageW,imageH;
	u16	min_numX,min_numY;
	u16	UsableTexel = 4096;
	u16	numMesh,min_numMesh;
	u16	fmt = pti->image.imageFmt;
	u16	siz = pti->image.imageSiz;
	u16	pitch_add_table[] = { 15,7,3,1,1 };
	u16	mipmapNum = pti->image.mipmapNum;
	u16	add = pitch_add_table[siz];
	u16	div;

	imageW = mm.imageW = ptxdata->pti->image.imageW;
	imageH = mm.imageH = ptxdata->pti->image.imageH;
	mm.t_unit = 1<<mipmapNum;

	if( fmt == G_IM_FMT_CI ){
			/*Kicking wired modes*/
		if( siz == G_IM_SIZ_16b || siz == G_IM_SIZ_32b )return	FALSE;
		UsableTexel /= 2;
	}
	if( mipmapNum )
		UsableTexel /= 2;
	switch( siz ){
		case G_IM_SIZ_4b :
			if( G_IM_FMT_RGBA == fmt || G_IM_FMT_YUV == fmt )return	FALSE;
			if( G_IM_FMT_CI != fmt )UsableTexel *= 2;
			if( mm.imageW & 1 )mm.t_unit *= 2;
			break;
		case G_IM_SIZ_16b :
			if( G_IM_FMT_CI == fmt || G_IM_FMT_I == fmt )return	FALSE;
			UsableTexel /= 2;
#if	_TEST_YUV
			if( G_IM_FMT_YUV == fmt ){
				mm.t_unit *= 2;
				UsableTexel /= 2;
			}
#endif
			break;
		case G_IM_SIZ_32b :
			if( G_IM_FMT_RGBA != fmt )return FALSE;
			UsableTexel /= 4;
			break;
		default :	/*G_IM_SIZ_8b*/
			if( G_IM_FMT_RGBA == fmt || G_IM_FMT_YUV == fmt )return	FALSE;
			siz = G_IM_SIZ_8b;
			break;
	}
	mm.tf = (G_TF_POINT == set_inf.texture.filter)? 0:mm.t_unit;
	imageW -= mm.tf;
	imageH -= mm.tf;
	min_numMesh = 4096;
	if( add < mm.t_unit-1 )	add = mm.t_unit-1;
	div = 0xffff - add;
	gridW = mm.t_unit;
	while( gridW <= imageW && gridW <= (256-mm.tf) ){
		gridPitchW = ( gridW + mm.tf + add )&div;
		gridH = UsableTexel/gridPitchW-mm.tf;
		if( gridH >= imageH )
			gridH = imageH;
		gridH &= -mm.t_unit;
		if( 0 == gridH )
			break;
		numX = (imageW-mm.t_unit)/gridW;
		numY = (imageH-mm.t_unit)/gridH;
		numMesh = (numX+1)*(numY+1);
		if( min_numMesh >= numMesh ){
			min_numX = numX;
			min_numY = numY;
			min_gridW = gridW;
			min_gridH = gridH;
			min_numMesh = numMesh;
		}
		gridW += mm.t_unit;
	}

	mm.gridW = pti->grid.gridW = min_gridW;
	mm.gridH = pti->grid.gridH = min_gridH;
	mm.numX = (mm.imageW-mm.t_unit)/mm.gridW;
	mm.numY = (mm.imageH-mm.t_unit)/mm.gridH;
	mm.lastW = (mm.imageW-mm.tf)-mm.gridW*mm.numX;
	if( mm.lastW < 0 )	mm.lastW = 0;
	mm.lastH = (mm.imageH-mm.tf)-mm.gridH*mm.numY;
	if( mm.lastH < 0 )	mm.lastH = 0;
		/* It's not CLAMP. It's WRAP */
	if( 0 == (ptxdata->pti->image.cms & G_TX_CLAMP) ){
		mm.gridW = ptxdata->pti->image.frameW;
		mm.numX = ptxdata->pti->grid.numX = 1;
		mm.lastW = 0;
	}
	if( 0 == (ptxdata->pti->image.cmt & G_TX_CLAMP) ){
		mm.gridH = ptxdata->pti->image.frameH;
		mm.numY = ptxdata->pti->grid.numY = 1;
		mm.lastH = 0;
	}
	return	TRUE;
}

/*******************************************************
 *		mesh_CalcVertex
 *
 *		Calculating the vertex
 *******************************************************/
void mesh_CalcVertex(texture_data* ptxdata)
{
	texture_info*	pti = ptxdata->pti;
	s16	vtxX,vtxY,tmpX,tmpY;
	u8	sw,nextY;
	int	i,j,k;
	u16	vtxChangeY;
	Vtx*	vtxp = ptxdata->pti->grid.vtxp;
	Vtx*	vpstart = vtxp;
		/*Determining a number for x direction and y direction, 
		at the same time, calculating the size of the remainder.*/
	vtxX = tmpX = pti->image.frameX;
	vtxY = tmpY = pti->image.frameY;

		/* Setting the vertex */
	for( i=mm.numY ; i>0 ; i-- ){
		tmpX = vtxX;
		for( j=mm.numX ; j>0 ; j-- ){
			setRectVtx( &vtxp,tmpX,tmpY,mm.gridW,mm.gridH);
			tmpX += mm.gridW;
		}
			/* The remainder of x coordinate is added. If there is any. */
		if( mm.lastW )	{
			setRectVtx( &vtxp,tmpX,tmpY,mm.lastW,mm.gridH);
		}
		tmpY -= mm.gridH;
	}
		/* The remainder of y coordinate is added. If there is any. */
	if( mm.lastH ){
		tmpX = vtxX;
		for( j=mm.numX ; j>0 ; j-- ){
			setRectVtx( &vtxp,tmpX,tmpY,mm.gridW,mm.lastH);
			tmpX += mm.gridW;
		}
			/* Lower right reminder */
		if( mm.lastW ){
			setRectVtx( &vtxp,tmpX,tmpY,mm.lastW,mm.lastH);
		}
	}
}

/******************************************************
 *		mesh_makeDisplayList
 *
 *		Make DisplayList fot Drawing
 ******************************************************/
void mesh_makeDisplayList(texture_data* ptxdata)
{
	texture_info*	pti = ptxdata->pti;
	s16	tmpS,tmpT;
	s16	vtxS,vtxT;
	s8	sw,nextX,nextY;
	int		i,j,k;
	s16	vtxChangeX,vtxChangeY;
	s16	mipmapNum = pti->image.mipmapNum;
	unsigned int	tmem_now,tmem_use;
	Gfx*	gp = pti->grid.gfxp;
	Gfx*	gpstart = gp;
	Vtx*	vtxp = pti->grid.vtxp;
	if(( 0 >= mm.gridW || 0 >= mm.gridH )&&(mm.tf == 0))
		return;
	vtxS = vtxT = 0;

		/*
		 *	Creating display lists for drawing
		 */
	tmpS = vtxS;
	tmpT = vtxT;
	for( j=mm.numY ; j>0 ; j-- ){
		tmpS = vtxS;
		for( i=mm.numX ; i>0 ; i-=MAX_SQUARE ){
			nextX = (i>MAX_SQUARE)? MAX_SQUARE:i;
			gSPVertex( gp++,vtxp,nextX*4,0 );
			vtxp += nextX*4;
			for( k=0 ; k<nextX*4 ; k+=4 ){
				gp = LoadTxTile(gp,ptxdata,tmpS,tmpT,tmpS+mm.gridW,tmpT+mm.gridH);
				gSP2Triangles(gp++, k,k+2,k+1,0,k+1,k+2,k+3,0);
				tmpS += mm.gridW;
			}
		}
		if( mm.lastW ){
			gSPVertex( gp++,vtxp,4,0 );
			vtxp += 4;
			gp = LoadTxTile(gp,ptxdata,tmpS,tmpT,tmpS+mm.lastW,tmpT+mm.gridH);
			gSP2Triangles(gp++, 0,2,1,0,1,2,3,0);
		}
		tmpT += mm.gridH;
	}
	if( mm.lastH ){
		tmpS = vtxS;
		for( i=mm.numX ; i>0 ; i-=MAX_SQUARE ){
			nextX = (i>MAX_SQUARE)? MAX_SQUARE:i;
			gSPVertex( gp++,vtxp,nextX*4,0 );
			vtxp += nextX*4;
			for( k=0 ; k<nextX*4 ; k+=4 ){
				gp = LoadTxTile(gp,ptxdata,tmpS,tmpT,tmpS+mm.gridW,tmpT+mm.lastH);
				gSP2Triangles(gp++, k,k+2,k+1,0,k+1,k+2,k+3,0);
				tmpS += mm.gridW;
			}
		}
		if( mm.lastW ){
			gSPVertex( gp++,vtxp,4,0 );
			gp = LoadTxTile(gp,ptxdata,tmpS,tmpT,tmpS+mm.lastW,tmpT+mm.lastH);
			gSP2Triangles(gp++, 0,2,1,0,1,2,3,0);
		}
	}
	gSPEndDisplayList(gp++);
}

/********************************************************
 *		LoadTxTile
 *
 *		Reading textures
 ********************************************************/
Gfx *LoadTxTile(Gfx *gp,texture_data *ptxdata,unsigned int uls,unsigned int ult,unsigned int lrs,unsigned int lrt )
{
	texture_info*	pti = ptxdata->pti;
	unsigned int	l_uls = uls;
	unsigned int	l_ult = ult;
	unsigned int	l_lrs = lrs;
	unsigned int	l_lrt = lrt;
	unsigned int	fmt = (unsigned int)pti->image.imageFmt;
	unsigned int	siz = (unsigned int)pti->image.imageSiz;
	unsigned int	mipmapNum = (unsigned int)pti->image.mipmapNum;
	unsigned int	tmp_line;
	unsigned char	loadshift;
	int				i;
static	const	unsigned int tmp_line_table[] = {1,2,4,4,4};
	unsigned int	shifts ,shiftt;
	unsigned int	masks = G_TX_NOMASK;
	unsigned int	maskt = G_TX_NOMASK;
	unsigned int	cms = pti->image.cms;
	unsigned int	cmt = pti->image.cmt;
	unsigned int	line;
	unsigned int	pal[8];
	unsigned int	width = (unsigned int)pti->image.imageW;
	unsigned int	timg[8];
	unsigned int	tmem[9];
	unsigned int	LoadSize;
	unsigned int	loadmode = pti->image.loadmode;
	unsigned int	nowtmem,usetmem;
	unsigned int	multi;
	unsigned int	Winfo,Hinfo;
	tmp_line = tmp_line_table[siz];
	multi = tmp_line;
	if( G_IM_SIZ_32b == siz )multi *= 2;
	shiftt = shifts = G_TX_NOLOD;
		/* Address calculation of the texture memory */
	nowtmem = 0;
	Hinfo = mm.gridH;
	usetmem = (mm.gridW+mm.tf)*(mm.gridH+mm.tf)/8;
	Hinfo += mm.tf;
		/* The amount of information for 1 line.  
		  (count 64 bits as 1)*/
	Winfo = (mm.gridW+mm.tf)*multi*4/64;

	for( i=0 ; i<=mipmapNum ; i++ ){
		pal[i] = (unsigned int)pti->image.imagePal[i];
		timg[i] = (unsigned int)ptxdata->ppixel[i];
		tmem[i] = nowtmem;
		usetmem = Winfo*Hinfo;
		nowtmem += Winfo*Hinfo;
		Winfo /= 2;
		if( Winfo == 0 )
			Winfo = 1;
		Hinfo /= 2;
		if( Hinfo == 0 )
			Hinfo = 1;
	}
	if( 0 == mipmapNum )pal[0] = ptxdata->palnum;
	tmem[i] = nowtmem;
	LoadSize = nowtmem*8*2/multi;

		/* Setting the mask value, when wrapping. */
	if( 0 == (pti->image.cms & G_TX_CLAMP) )
		for( i=1; pti->image.imageW>i ; i<<=1 , masks++ );
	if( 0 == (pti->image.cmt & G_TX_CLAMP) )
		for( i=1; pti->image.imageH>i ; i<<=1 , maskt++ );

	l_lrs += mm.tf-1;
	l_lrt += mm.tf-1;
	line = ((((l_lrs-l_uls+1) * tmp_line / 2)+7)>>3);
	gDPPipeSync(gp++);

	for( i=0;i<=mipmapNum;i++ ){
		shiftt=shifts=i;
		loadshift = G_TEXTURE_IMAGE_FRAC-i;
		if( NULL != timg[i] ){
				/*	4 bit mode	*/
			if( siz == G_IM_SIZ_4b ){
				gDPSetTile( gp++,fmt,G_IM_SIZ_8b,line,tmem[i],i,0,cmt,maskt,shiftt,cms,masks,shifts );
				gDPLoadSync(gp++);
				gDPSetTextureImage(gp++,fmt,G_IM_SIZ_8b,(width+1)>>1,timg[i] );
				gDPLoadTileGeneric( gp++,G_LOADTILE,i,
									l_uls<<(loadshift-1),l_ult<<loadshift,
									l_lrs<<(loadshift-1),l_lrt<<loadshift );
			}
				/*	Other	*/
			else{
				gDPSetTile( gp++,fmt,siz,line,tmem[i],i,0,cmt,maskt,shiftt,cms,masks,shifts );
				gDPLoadSync( gp++ );
				gDPSetTextureImage(gp++,fmt,siz,width,timg[i] );
				gDPLoadTileGeneric( gp++,G_LOADTILE,i,
									l_uls<<loadshift,l_ult<<loadshift,
									l_lrs<<loadshift,l_lrt<<loadshift );
			}
		}
		gDPPipeSync( gp++ );
		gDPSetTile( gp++,fmt,siz,line,tmem[i],i,pal[i],cmt,maskt,shiftt,cms,masks,shifts );
		gDPLoadTileGeneric( gp++,G_SETTILESIZE,i,
							0,0,(l_lrs-l_uls)<<loadshift,(l_lrt-l_ult)<<loadshift);

		width++;
		width /=2;
		line = (line*8/2+7)>>3;
		if( masks>0 )masks--;
		if( maskt>0 )maskt--;
	}
	return	gp;
}

/************************************************
 *		setRectVtx
 *
 *		Set Rectangle Vertex
 ************************************************/
void setRectVtx(Vtx **vt,short x,short y,short width,short height)
{
	setVtxParam( (*vt)++ , x      ,y       ,0    ,0 );
	setVtxParam( (*vt)++ , x+width,y       ,width,0 );
	setVtxParam( (*vt)++ , x      ,y-height,0    ,height );
	setVtxParam( (*vt)++ , x+width,y-height,width,height );
}

/************************************************
 *		setVtxParam
 *
 *		Set Parameter to Vertex
 ************************************************/
void setVtxParam(Vtx *vt,short x,short y,short s,short t)
{
	vt->v.ob[0] = x;
	vt->v.ob[1] = y;
	vt->v.tc[0] = s<<6;
	vt->v.tc[1] = t<<6;
}

/*************************************************
 *		mesh_MakeSetupDisplayList
 *
 *		Make DisplayList for Setup Texture
 *************************************************/
void	mesh_MakeSetupDisplayList( texture_data* ptxdata)
{
	unsigned int	GeometryMode;
	unsigned int	imageTF = set_inf.texture.filter;
	int	fog_near	= set_inf.fog.fog_near;
	int	fog_far		= set_inf.fog.fog_far;
	int	meshRenderMode = set_inf.blender.render_mode;
	int	meshCombineMode = set_inf.combiner.global_cc_1;
	unsigned int	CullingTable[3] = {G_CULL_FRONT,G_CULL_BACK,G_CULL_BOTH};
	int	i;
	Gfx*	gp = ptxdata->pti->grid.setup_gfxp;
	unsigned int RenderFirstTable[3] =
		{
			G_RM_AA_OPA_SURF ,
			G_RM_AA_XLU_SURF ,
			G_RM_AA_TEX_EDGE
		};
	unsigned int RenderFirstTableZB[3] =
		{
			G_RM_AA_ZB_OPA_SURF ,
			G_RM_AA_ZB_XLU_SURF ,
			G_RM_AA_ZB_TEX_EDGE
		};
	unsigned int RenderSecondTable[3] =
		{
			G_RM_AA_OPA_SURF2 ,
			G_RM_AA_XLU_SURF2 ,
			G_RM_AA_TEX_EDGE2
		};
	unsigned int RenderSecondTableZB[3] =
		{
			G_RM_AA_ZB_OPA_SURF2 ,
			G_RM_AA_ZB_XLU_SURF2 ,
			G_RM_AA_ZB_TEX_EDGE2
		};
	unsigned int CombineFirstTable1C[3][2] =
		{
			gsDPSetCombineMode( G_CC_DECALRGBA , G_CC_DECALRGBA ),
			gsDPSetCombineMode( G_CC_PRIMITIVE , G_CC_PRIMITIVE ),
			gsDPSetCombineMode( G_CC_BLENDPE , G_CC_BLENDPE )
		};
	unsigned int CombineFirstTable2C[3][2] =
		{
			gsDPSetCombineMode( G_CC_TRILERP , G_CC_DECALRGB2 ),
			gsDPSetCombineMode( G_CC_TRILERP , G_CC_PRIMITIVE ),
			gsDPSetCombineMode( G_CC_TRILERP , G_CC_BLENDPE )
		};
		/*
		 *	Clear ZBuffer And FrameBuffer with BG Color
		 */
	gp = gfxClearCfb( gp , set_inf.etc.BG_color );
		/*
		 *	Set GeometryMode
		 */
	gSPClearGeometryMode(gp++,G_CULL_BOTH|G_TEXTURE_GEN|G_TEXTURE_GEN_LINEAR
						  |G_LIGHTING|G_FOG|G_LOD );
	GeometryMode =	/*G_TEXTURE_ENABLE|*/G_SHADE|G_SHADING_SMOOTH|
					G_ZBUFFER;
/*
	if( set_inf.fog.fog_flag )
		GeometryMode |= G_FOG;
*/
#if	_TEST_YUV
	if( ptxdata->pti->image.imageFmt == G_IM_FMT_YUV )
		GeometryMode |= G_LOD;
#endif
	if( 0<set_inf.etc.culling && set_inf.etc.culling<=3 )
		GeometryMode |= CullingTable[set_inf.etc.culling-1];
	gSPSetGeometryMode(gp++ , GeometryMode );
		/*
		 *	Setting CYCLE TYPE
		 *
		 *	Setting a render mode and a color combiner mode as well
		 */
	gDPPipeSync(gp++);
	if( GeometryMode & G_LOD )
	{
		gDPSetCycleType(gp++,G_CYC_2CYCLE);
		if( GeometryMode & G_ZBUFFER ){
			gDPSetRenderMode(gp++,G_RM_PASS,RenderSecondTableZB[meshRenderMode]);
		}
		else{
			gDPSetRenderMode(gp++,G_RM_PASS,RenderSecondTable[meshRenderMode]);
		}
		gp->words.w0 = CombineFirstTable2C[meshCombineMode][0];
		gp->words.w1 = CombineFirstTable2C[meshCombineMode][1];
		gp++;
		gDPSetTextureLOD(gp++ , G_TL_LOD);
		gDPSetTextureDetail(gp++ , G_TD_CLAMP);
	}
	else
	{
		gDPSetCycleType(gp++,G_CYC_1CYCLE);
		if( GeometryMode & G_ZBUFFER ){
			gDPSetRenderMode(gp++,RenderFirstTableZB[meshRenderMode],RenderSecondTableZB[meshRenderMode]);
		}
		else{
			gDPSetRenderMode(gp++,RenderFirstTable[meshRenderMode],RenderSecondTable[meshRenderMode]);
		}
		gp->words.w0 = CombineFirstTable1C[meshCombineMode][0];
		gp->words.w1 = CombineFirstTable1C[meshCombineMode][1];
		gp++;
		gDPSetTextureLOD(gp++,G_TL_TILE);
	}
		/*
		 *	Setup Fog
		 */
#if	0
	if( GeometryMode & G_FOG )
	{
		if( FogNear<0 )
			FogNear = 0;
		if( FogNear>1000 )
			FogNear=1000;
			/*If a value in FogFar is negative, this section will detect it.*/
		if( FogFar<FogNear )
			FogFar = FogNear;
		if( FogFar>1000 )
			FogFar = 1000;
		gSPFogPosition( gp++ , FogNear , FogFar );
		gDPSetColor( gp++ , G_SETFOGCOLOR , mesh_setp->FogColor.Color );
	}
#endif
		/*
		 *	Setting a color
		 */
	gp->words.w0 =	_SHIFTL(G_SETPRIMCOLOR, 24, 8);
	gp->words.w1 =  set_inf.etc.PRIM_color.color;
	gp++;
	gDPSetColor(gp++,G_SETENVCOLOR,set_inf.etc.ENV_color.color);
		/*
		 *	Other setup
		 */
	gSPTexture(gp++,0x8000,0x8000,ptxdata->pti->image.mipmapNum,G_TX_RENDERTILE,G_ON);
	gDPSetTexturePersp(gp++,set_inf.texture.persp);
	if( imageTF != G_TF_BILERP ){
		if( imageTF != G_TF_AVERAGE )
			imageTF = G_TF_POINT;
	}
	gDPSetTextureFilter(gp++ , imageTF);
		/* If the color format is YUV. */
	if( ptxdata->pti->image.imageFmt == G_IM_FMT_YUV ){
#if	_TEST_YUV
		gDPSetTextureConvert( gp++ , G_TC_FILTCONV );
#else
		gDPSetTextureConvert( gp++ , G_TC_CONV );
#endif
		gDPSetConvert(gp++,G_CV_K0,G_CV_K1,G_CV_K2,G_CV_K3,G_CV_K4,G_CV_K5);
		gDPSetCombineLERP(gp++,TEXEL0,K4,K5,TEXEL0,0,0,0,SHADE,TEXEL0,K4,K5,TEXEL0,0,0,0,SHADE);
	}
	else{	/* Other thanYUV */
		gDPSetTextureConvert( gp++ , G_TC_FILT );
	}

		/* Setting as if using the index color. */
	if( ptxdata->pti->image.imageFmt == G_IM_FMT_CI )
	{
		if( NULL == ptxdata->ppal )
			return;
		if( ptxdata->pti->image.tlutMode != G_TT_IA16 )
			ptxdata->pti->image.tlutMode = G_TT_RGBA16;
		gDPLoadSync(gp++);
		gDPSetTextureLUT( gp++ , ptxdata->pti->image.tlutMode );
		gDPLoadTLUT_pal256(gp++,(unsigned int)(ptxdata->ppal));
	}
	else		/*Index color is not used.*/
		gDPSetTextureLUT( gp++ , G_TT_NONE );
	gSPEndDisplayList( gp++ );
}

/* 
 *
 *
 *
 *
 */
