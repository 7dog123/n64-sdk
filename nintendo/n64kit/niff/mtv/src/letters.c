/*
 *	letters.h
 *
 *	displays letters
 *
 *  Copyright (C) 1998-1999, NINTENDO Co.,Ltd.
 *  Copyright (C) 1998-1999, MONEGI CORPORATION
 */

#include	<ultra64.h>
#include	"nusys.h"
#include	"letters.h"

/************************************************************************************************
 *		letters_init
 *
 *		Initializing character strings display.
 *
 *		Prior to call and other functions, call it first.
 ************************************************************************************************/
Gfx *letters_init( Gfx *gp )
{
	gSPDisplayList( gp++ , LettersInitDL );
	return	gp;
}

/************************************************************************************************
 *		letters_1_letter
 *
 *		Displaying one letter.
 ************************************************************************************************/
Gfx *letters_1_letter(Gfx *gp,short x,short y,unsigned char cLetter,u32 color)
{
	unsigned char	ucChar = cLetter-0x20;

	gDPSetPrimColor(gp++, 0,0,(color&0xff000000)>>24,(color&0xff0000)>>16,(color&0xff00)>>8,color&0xff);
	gSPTextureRectangle(gp++,x<<2,y<<2,(x+6)<<2,(y+8)<<2,
						 G_TX_RENDERTILE,((ucChar&0xf0)/0x10)*8<<5,(ucChar&0xf)*8<<5,1<<10,1<<10);
	return	gp;
}

/************************************************************************************************
 *		letters_set
 *
 *		Display character strings
 *
 *		The character strings should be ended with a NULL.
 ************************************************************************************************/
Gfx *letters_set( Gfx *gp , short x , short y , unsigned char *frase , u32 color )
{
	int	i=0;
	unsigned char	ucChar;
	short	dispx = x;
	gDPSetPrimColor(gp++, 0,0,
						(color&0xff000000)>>24,
						(color&0xff0000)>>16,
						(color&0xff00)>>8,
						color&0xff );
	while( NULL != *frase ){
		ucChar = *frase - 0x20;
		gSPTextureRectangle(gp++,dispx<<2,y<<2,(dispx+8)<<2,(y+8)<<2,
						 G_TX_RENDERTILE,((ucChar&0xf0)/0x10)*8<<5,(ucChar&0xf)*8<<5,1<<10,1<<10);
		frase++;
		dispx += 8;
	}
	return	gp;
}

/************************************************************************************************
 *		letters_num
 *
 *		Displaying numbers
 ************************************************************************************************/
Gfx *letters_num( Gfx *gp , short x , short y , int iNumber , u32 color )
{
	char	output[256];
	i2a( iNumber , output );
	gp = letters_set( gp , x , y , output , color );
	return	gp;
}

/************************************************************************************************
 *		letters_num_right
 *
 *		Displaying numbers right aligned.
 *
 *		Upper right coordinates are assigned in X,Y.
 ************************************************************************************************/
Gfx *letters_num_right( Gfx *gp , short x , short y , int iNumber , u32 color )
{
	char	output[256];
	char	ketasu = i2a( iNumber , output );
	gp = letters_set( gp , x-ketasu*8 , y , output , color );
	return	gp;
}

/************************************************************************************************
 *		i2a
 *
 *		Converting numbers to character strings.
 *
 *		The return value represents digit.       
 ************************************************************************************************/
char	i2a( int iNumber , char *output )
{
	char	flag = (iNumber<0)? 1:0;	/* When the value is negative, the symbol is displayed. */
	int		num = (flag)? -iNumber:iNumber;
	char	amari,tmpketasu=0;
	char	outketasu=0;
	char	tmp[256];
	int		i;
		/* Also, corresponds the value of 0. */
	do {
		amari = num % 10;
		tmp[tmpketasu++] = amari+'0';
		if( num<10 )
			break;
		num /= 10;
	} while( num > 0 );
	if(flag)
		output[outketasu++] = '-';
	for( i=0 ; i<tmpketasu ; i++ )
		output[outketasu++] = tmp[tmpketasu-i-1];
	output[outketasu]=NULL;
	return	outketasu;
}

