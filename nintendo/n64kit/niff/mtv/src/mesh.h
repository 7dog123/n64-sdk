/*
 *		mesh.h
 *
 *		Paste textures which can not be fit within TMEM onto a polygon 
 *      	which is split into small tiles.             
 *
 *	Copyright (C) 1998-1999, NINTENDO Co.,Ltd.
 *  	Copyright (C) 1998-1999, MONEGI CORPORATION
 */


#ifndef	_MESH
#define	_MESH

#include	<ultra64.h>
#include	"meshglobal.h"

typedef struct{
	u16	imageW;
	u16 imageH;
	u16 gridW;
	u16 gridH;
	s16 lastW;
	s16 lastH;
	u16 numX;
	u16 numY;
	u32	t_unit;
	u32	tf;
} MeshManager;

void mesh_Init(texture_data*,int);
int	mesh_CalcGrid(texture_data*);
void mesh_CalcVertex(texture_data*);
void mesh_makeDisplayList(texture_data*);
Gfx *LoadTxTile(Gfx *gp,texture_data *ptxdata ,
				unsigned int,unsigned int,unsigned int,unsigned int);
void setMeshManager(texture_data* ptxdata);
void setRectVtx(Vtx **vt,short x,short y,short width,short height);
void setVtxParam(Vtx *vt,short,short,short,short);
void mesh_MakeSetupDisplayList(texture_data* ptxdata);

#endif	/*_MESH*/
