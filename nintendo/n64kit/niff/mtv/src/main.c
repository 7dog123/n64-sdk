/*
 *	main.c
 *
 *	initialize app, and call main routine
 *
 *  Copyright (C) 1998-1999, NINTENDO Co.,Ltd.
 *  Copyright (C) 1998-1999, MONEGI CORPORATION
 */

#include	"main.h"
#include	"nusys.h"

extern	void	game(void);

extern	RGBA16			palette[64][256];
extern	u64				pixel[];
extern	texture_info	tex_inf[];
extern	setup_info		set_inf;
extern	tvModeData		tvmd;
extern	u32				num_of_texture;
extern	texture_data	td[];

/************************************************************************************************
 *	mainproc
 *
 *	initialize app and specify callback function
 ************************************************************************************************/

void	mainproc( void )
{
	static	u8	firsttime = 1;
	nuGfxInit();
	nuGfxDisplayOff();
	contpattern = nuContInit();
	nuContDataReadStart();
	num_of_texture = 0;
	mesh_LoadResource();
	tv_memcpy( (void*)&set_inf,(void*)&start_set_inf,sizeof(setup_info) );
	init_modedata();
	center_x = center_y = center_z = 0;
	guMtxIdent(&(back_dynamic[0].rotate));
	while(1)
	{
			/* Call back function */
		nuGfxFuncSet((NUGfxFunc)game);
		if( firsttime )
		{
			firsttime = 0;
			nuGfxDisplayOn();
		}
	}
}

/************************************************************************************************
 *	mesh_LoadResource
 *
 *	analyse .bin file
 ************************************************************************************************/
void mesh_LoadResource(void)
{
	u32		ptr_of_texture_data;
	u32		ptr_of_pixel_data;
	u32		header_ptr;
	int		iRet;
	int		i,j,k;
	RGBA16*	l_ppal;
	u64*	l_ppixel;
	u32		size_of_one_texture;
	u8		fmt,siz;
	char	name[16];
	u8		mipmapnum;
	u32		pixel_size_for_mipmap;
	u32		pixel_size_one_for_mipmap;
	u16		width;
	u16		height;
	u32		tvh_index = 0;
	u32		palette_index = 0;
	u32		pixel_index = 0;
	u32		num_of_texture_data = 0;
	u32		num_of_palette_data = 0;
	u16		global_palette_number;
	u16		local_palette_number;
	u8		Buf[16];
	u8*		pBuf;
	texture_viewer_header	tvh;
	texture_viewer_header*	ptvh = &tvh;
	texture_data*			ptd;

	nuPiReadRom( 0x400000,(void*)&Buf[0],16 );
	if( Buf[0]=='T' && Buf[1]=='e' && Buf[2]=='x' && Buf[3]=='V' &&
		Buf[4]=='H' && Buf[5]=='e' && Buf[6]=='a' && Buf[7]=='D' ){
		pBuf = &Buf[12];
		getDword(&num_of_texture_data,&pBuf);
	}
	header_ptr = 0x400010;
		/*	Tracing the ROM address sequence.	*/
	for( i=0 ; i<num_of_texture_data ; i++ ){
			/*	first, the read address	*/
		nuPiReadRom(header_ptr,(void*)&Buf[0],4);
		pBuf = &Buf[0];
		header_ptr += 4;
		getDword(&ptr_of_texture_data,&pBuf);
		iRet = get_tv_header(ptvh,ptr_of_texture_data);
		l_ppal = NULL;
		if( iRet != M_FALSE ){
			tv_memcpy((void*)&tex_inf[tvh_index],(void*)(&ptvh->ti),sizeof(texture_info));
			size_of_one_texture = ptvh->fh.size_of_pixel_data;
			fmt = ptvh->ti.image.imageFmt;
			siz = ptvh->ti.image.imageSiz;
			mipmapnum = ptvh->ti.image.mipmapNum;
			ptr_of_pixel_data = ptr_of_texture_data + 0x100;
				/*	read palette	*/
			if( fmt == G_IM_FMT_CI ){
				l_ppal = &palette[palette_index][0];
				num_of_palette_data = ptvh->fh.num_of_palette;
				if( G_IM_SIZ_4b == siz )
					num_of_palette_data = (num_of_palette_data+15)/16;
				for( j=0;j<num_of_palette_data;j++ ){
					nuPiReadRom( ptr_of_pixel_data , (void*)&palette[palette_index][0] ,
								 sizeof(RGBA16)*256 );
					palette_index++;
					ptr_of_pixel_data += 0x200;
				}
			}
				/*	Reading pixel data	*/
			for( j=0;j<ptvh->fh.num_of_texture;j++ ){
					/*	first, texture name	*/
				nuPiReadRom(ptr_of_pixel_data,(void*)&name[0],16 );
				pBuf = &name[12];
				getWord( &global_palette_number,&pBuf );
				getWord( &local_palette_number,&pBuf );
				l_ppixel = &pixel[pixel_index];
				nuPiReadRom(ptr_of_pixel_data+16,(void*)l_ppixel,
							 (ptvh->fh.size_of_pixel_data+1)&-2 );
				ptd = &td[num_of_texture];
				for( k=0;k<16;k++ )
					ptd->name[k] = name[k];
				ptd->pti = &tex_inf[tvh_index];
				ptd->ppal = l_ppal+global_palette_number*256;
				ptd->palnum = (u32)local_palette_number;
				width = ptvh->ti.image.imageW;
				height = ptvh->ti.image.imageH;
				pixel_size_for_mipmap = 0;
				for( k=0;k<=mipmapnum;k++ ){
					ptd->ppixel[k] = &pixel[pixel_index+pixel_size_for_mipmap/sizeof(u64)];
					switch(siz){
						case G_IM_SIZ_4b :
							pixel_size_one_for_mipmap = ((width+1)/2)*height;
							break;
						case G_IM_SIZ_16b :
							pixel_size_one_for_mipmap = width*height*2;
							break;
						case G_IM_SIZ_32b :
							pixel_size_one_for_mipmap = width*height*4;
							break;
						default :
							pixel_size_one_for_mipmap = width*height;
							break;
					}
					pixel_size_one_for_mipmap = (pixel_size_one_for_mipmap+7)&-8;
					pixel_size_for_mipmap += pixel_size_one_for_mipmap;
					width/=2;
					height/=2;
				}
				num_of_texture++;
				pixel_index += (ptvh->fh.size_of_pixel_data+sizeof(u64)-1)/sizeof(u64);
				ptr_of_pixel_data += (16+ptvh->fh.size_of_pixel_data);
			}
			tvh_index++;
		}	/*	if(iRet!=M_FALSE)	*/
	}	/*	for(ptr)	*/
}

/************************************************************************************************
 *	get_tv_header
 *
 *	read setup data from ROM
 ************************************************************************************************/
int	get_tv_header(texture_viewer_header* ptvh,u32 rom_ptr)
{
	static	u8	setpBuf[0x100];
	u8* BufTmp = setpBuf;
	u32	size_of_pixel;
	u16	num_of_texture_in_header;
	u16	num_of_palette_in_header;
	int	i;
			/*	read 256 bytes from ROM	*/
	nuPiReadRom( rom_ptr,(void*)BufTmp,256 );
	if( setpBuf[0]=='T' && setpBuf[1]=='e' && setpBuf[2]=='x' && setpBuf[3]=='T' &&
		setpBuf[4]=='v' && setpBuf[5]=='I' && setpBuf[6]=='E' && setpBuf[7]=='w' )
	{
		BufTmp = &setpBuf[8];
		getWord( &num_of_texture_in_header ,&BufTmp );
		getWord( &num_of_palette_in_header ,&BufTmp );
		getDword( &size_of_pixel,&BufTmp );
		if( (0 == size_of_pixel) || (0 == num_of_texture_in_header) )
			return	M_FALSE;

		BufTmp = &setpBuf[0x10];
		get_texture_info( &ptvh->ti , &BufTmp);
		ptvh->fh.num_of_texture = num_of_texture_in_header;
		ptvh->fh.num_of_palette = num_of_palette_in_header;
		ptvh->fh.size_of_pixel_data = size_of_pixel;

		return	M_TRUE;
	}
	return	M_FALSE;
}

/************************************************************************************************
 *	get_texture_info
 *
 *	get texture_info structure
 ************************************************************************************************/
 void	get_texture_info(texture_info* pti,u8** pp_buf)
{
	int	i;
		/*	read image	*/
	getWord( &pti->image.imageX , pp_buf );
	getWord( &pti->image.imageW , pp_buf );
	getShort(&pti->image.frameX , pp_buf );
	getWord( &pti->image.frameW , pp_buf );
	getWord( &pti->image.imageY , pp_buf );
	getWord( &pti->image.imageH , pp_buf );
	getShort(&pti->image.frameY , pp_buf );
	getWord( &pti->image.frameH , pp_buf );
	getDword( &pti->image.loadmode , pp_buf );
	getDword( &pti->image.cms , pp_buf );
	getDword( &pti->image.cmt , pp_buf );
	getDword( &pti->image.tlutMode , pp_buf );
	for( i=0;i<8;i++ )
		getWord( &pti->image.imagePal[i] , pp_buf );
	getByte( &pti->image.imageFmt , pp_buf );
	getByte( &pti->image.imageSiz , pp_buf );
	getByte( &pti->image.mipmapNum , pp_buf );
	getByte( &pti->image.bg_flag , pp_buf );
	for( i=0;i<4;i++ )
		getByte( &pti->image.boundary[i] , pp_buf );
		/*	read grid	*/
	pti->grid.vtxp = mesh_vtx[0];
	pti->grid.gfxp = mesh_dl[0];
	pti->grid.setup_gfxp = mesh_setup_dl[0];
}

/************************************************************************************************
 *	getByte,getWord,getDword,getChar,getShort,GetLong
 *
 *	Obtains each of these, 'u8','s8','u16','s16','u32','s32' from "unsigned char" type buffer.
 ************************************************************************************************/
void	getByte(u8* data,u8** ppBuf)
{
	*data = **ppBuf;
	(*ppBuf)++;
}

void	getChar(s8* data,u8** ppBuf)
{
	u8	dataTmp;
	getByte(&dataTmp,ppBuf);
	*data = (s8)dataTmp;
}

void	getWord(u16* data,u8** ppBuf)
{
	u8	dataTmp[2];
	getByte(&dataTmp[0],ppBuf);
	getByte(&dataTmp[1],ppBuf);
	*data = (u16)(u8)dataTmp[0]*0x100+(u16)(u8)dataTmp[1];
}

void	getShort(s16* data,u8** ppBuf)
{
	u16	dataTmp;
	getWord( &dataTmp , ppBuf );
	*data = (s16)dataTmp;
}

void	getDword(u32* data,u8** ppBuf)
{
	u8	dataTmp[4];
	getByte(&dataTmp[0],ppBuf);
	getByte(&dataTmp[1],ppBuf);
	getByte(&dataTmp[2],ppBuf);
	getByte(&dataTmp[3],ppBuf);
	*data = (u32)(u8)dataTmp[0]*0x1000000+(u32)(u8)dataTmp[1]*0x10000
			+(u32)(u8)dataTmp[2]*0x100+(u32)(u8)dataTmp[3];
}

void	getLong(s32* data,u8** ppBuf)
{
	u32	dataTmp;
	getDword(&dataTmp,ppBuf);
	*data = (s32)dataTmp;
}

/************************************************************************************************
 *	tv_memcpy
 *
 *	Simple memory copy
 ************************************************************************************************/
void	tv_memcpy(void* pvDest,void* pvSrc,unsigned int size)
{
	unsigned int	i;
	u8*	pcDest = (u8*)pvDest;
	u8* pcSrc  = (u8*)pvSrc;
	for( i=0;i<size;i++ ){
		*pcDest++ = *pcSrc++;
	}
}

