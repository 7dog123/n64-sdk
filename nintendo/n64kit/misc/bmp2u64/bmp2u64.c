/*===========================================================

    bmp2u64 : BMP to U64 converter
    
    BMP->16bitRGBA Converter (for PC)
    
    version 1.0
    Programmed by M.Kawamura    1997.07.11
    Copyright (C) 1997 Nintendo.Co.,Ltd.
   
  ===========================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "bmp.h"

char *progName = "bmp2u64";
char *usage = 
"=== bmp2u64 (version 1.0) ===\n"
"usage: bmp2u64 <bmpFilename> <u64Filename>\n";

void write1bitdata16(FILE *infp, FILE *outfp, unsigned short *palette, long width, long height);
void write4bitdata16(FILE *infp, FILE *outfp, unsigned short *palette, long width, long height);
void write8bitdata16(FILE *infp, FILE *outfp, unsigned short *palette, long width, long height);
void write24bitdata16(FILE *infp, FILE *outfp, long width, long height);

unsigned short chendian16(unsigned short *num);
unsigned long chendian32(unsigned long *num);


main(int argc, char *argv[])
{
	int i;
	
	FILE *infile, *outfile;
	
	BITMAPFILEHEADER bmfh;
	BITMAPINFOHEADER bmih;
	RGBQUAD  aColors[256];
	unsigned short rgba16[256];
	
	if(argc != 3){
		fprintf(stderr, "%s\n", usage);
		exit(1);
	}
	
	if((infile = fopen(argv[1], "rb")) == NULL){
		fprintf(stderr, "%s: cannot open input file [%s].\n", progName, argv[1]);
		exit(1);
	}
	
	fread(&bmfh, sizeof(BITMAPFILEHEADER), 1, infile);
	
	/* Check Header */
	if(bmfh.bfType != 19778){
		fprintf(stderr, "%s: [%s] is not a BMP file.\n", progName, argv[1]);
		fclose(infile);
		exit(1);
	}
	
	fread(&bmih, sizeof(BITMAPINFOHEADER), 1, infile);
	
	printf("===== BMP Image Information =====\n");
	printf("  Width       = %ld\n", bmih.biWidth);
	printf("  Height      = %ld\n", bmih.biHeight);
	printf("  Colors      = ");
	switch(bmih.biBitCount){
		case 1:
			printf("1-bit monochrome\n");
			break;
		case 4:
			printf("4-bit 16 colors\n");
			break;
		case 8:
			printf("8-bit 256 colors\n");
			break;
		case 24:
			printf("24-bit colors\n");
			break;
		default:
			printf("Unknown color format\n");
			break;
	}
	printf("  Compression = ");
	switch(bmih.biCompression){
		case BI_RGB:
			printf("No Compression\n");
			break;
		case BI_RLE8:
			printf("RLE8\n");
			break;
		case BI_RLE4:
			printf("RLE4\n");
			break;
		default:
			printf("Unknown compression format\n");
			break;
	}
	
	printf("---------------------------------\n");
	
	if(bmih.biCompression != BI_RGB){
		fprintf(stderr, "%s: Sorry, RLE bitmap is not supported.\n", progName);
		fclose(infile);
		exit(1);
	}
	
	if(bmih.biBitCount != 24){
		if(!bmih.biClrUsed)	
			bmih.biClrUsed = pow(2, bmih.biBitCount);
		fread(aColors, sizeof(RGBQUAD), bmih.biClrUsed, infile);
		
		for(i = 0; i < bmih.biClrUsed; i++){
			rgba16[i] = ((unsigned short)(aColors[i].rgbRed >> 3) << 11);
			rgba16[i] |= ((unsigned short)(aColors[i].rgbGreen >> 3) << 6);
			rgba16[i] |= ((unsigned short)(aColors[i].rgbBlue >> 3) << 1);
			rgba16[i] |= 0x0001;
			chendian16(&rgba16[i]);
		}
	}
	
	fseek(infile, bmfh.bfOffBits, 0);
	
	if((outfile = fopen(argv[2], "wb")) == NULL){
		fprintf(stderr, "%s: cannot open output file [%s].\n", progName, argv[2]);
		fclose(infile);
		exit(1);
	}
	
	/* Write RGBA data */
	
	switch(bmih.biBitCount){
		case 1:
			write1bitdata16(infile, outfile, rgba16, bmih.biWidth, bmih.biHeight);
			break;
		case 4:
			write4bitdata16(infile, outfile, rgba16, bmih.biWidth, bmih.biHeight);
			break;
		case 8:
			write8bitdata16(infile, outfile, rgba16, bmih.biWidth, bmih.biHeight);
			break;
		case 24:
			write24bitdata16(infile, outfile, bmih.biWidth, bmih.biHeight);
			break;
		default:
			fprintf(stderr, "%s: [%s] is not a BMP file.\n", progName, argv[1]);
			fclose(infile);
			fclose(outfile);
			unlink(argv[2]);
			break;
	}
	
	fclose(outfile);
	fclose(infile);
	
	return EXIT_SUCCESS;
}

void write1bitdata16(FILE *infp, FILE *outfp, unsigned short *palette, long width, long height)
{
	long ptrWd = 0, ptrHt = 0;
	int i;
	unsigned long data;
	unsigned int c;
	
	long ptr = width * (height - 1) * 2;
	
	fseek(outfp, ptr, 0);
	while(fread(&data, 4, 1, infp) == 1){
		chendian32(&data);
		for(i = 31; i >= 0; i--){
			if(ptrWd < width){
				c = (unsigned int)(data >> i) & 0x0001;
				fwrite(palette + c, 2, 1, outfp);
			}
			ptrWd++;
		}
		if(ptrWd >= width){
			ptrWd = 0;
			ptrHt++;
			if(ptrHt >= height)
				return;
			ptr -= width * 2;
			fseek(outfp, ptr, 0);
		}
	}
}


void write4bitdata16(FILE *infp, FILE *outfp, unsigned short *palette, long width, long height)
{
	long ptrWd = 0, ptrHt = 0;
	int i;
	unsigned long data;
	unsigned int c;
	
	long ptr = width * (height - 1) * 2;
	
	fseek(outfp, ptr, 0);
	while(fread(&data, 4, 1, infp) == 1){
		chendian32(&data);
		for(i = 7; i >= 0; i--){
			if(ptrWd < width){
				c = (unsigned int)(data >> (4 * i)) & 0x000f;
				fwrite(palette + c, 2, 1, outfp);
			}
			ptrWd++;
		}
		if(ptrWd >= width){
			ptrWd = 0;
			ptrHt++;
			if(ptrHt >= height)
				return;
			ptr -= width * 2;
			fseek(outfp, ptr, 0);
		}
	}
}


void write8bitdata16(FILE *infp, FILE *outfp, unsigned short *palette, long width, long height)
{
	long ptrWd = 0, ptrHt = 0;
	int i;
	unsigned long data;
	unsigned int c;
	
	long ptr = width * (height - 1) * 2;
	
	fseek(outfp, ptr, 0);
	while(fread(&data, 4, 1, infp) == 1){
		chendian32(&data);
		for(i = 3; i >= 0; i--){
			if(ptrWd < width){
				c = (unsigned int)(data >> (8 * i)) & 0x00ff;
				fwrite(palette + c, 2, 1, outfp);
			}
			ptrWd++;
		}
		if(ptrWd >= width){
			ptrWd = 0;
			ptrHt++;
			if(ptrHt >= height)
				return;
			ptr -= width * 2;
			fseek(outfp, ptr, 0);
		}
	}
}


void write24bitdata16(FILE *infp, FILE *outfp, long width, long height)
{
	long ptrWd = 0, ptrHt = 0;
	unsigned char data[3];
	unsigned short outdata;
	unsigned int c;
	
	long ptr = width * (height - 1) * 2;
	
	fseek(outfp, ptr, 0);
	while(fread(data, 1, 3, infp) == 3){
		outdata = ((unsigned short)(data[2] >> 3) << 11);
		outdata |= ((unsigned short)(data[1] >> 3) << 6);
		outdata |= ((unsigned short)(data[0] >> 3) << 1);
		outdata |= 0x0001;
		
		/* to convert Endian */
		
		chendian16(&outdata);
		
		fwrite(&outdata, 2, 1, outfp);
		ptrWd++;
		if(ptrWd >= width){
			fread(data, 1, (4 - (ptrWd % 4)) % 4, infp);
			ptrWd = 0;
			ptrHt++;
			if(ptrHt >= height)
				return;
			ptr -= width * 2;
			fseek(outfp, ptr, 0);
		}
	}
}


/*
 * chendian16 : Change Endian (16bit)
 */

unsigned short chendian16(unsigned short *num)
{

	unsigned char high, low;
	unsigned short out;

	high = (*num >> 8) & 0x00FF;
	low = *num & 0x00FF;

	out = ((unsigned int)low << 8) | (unsigned int)high;

	*num = out;
	return out;
}


/*
 * chendian32 : Change Endian (32bit)
 */

unsigned long chendian32(unsigned long *num)
{
	unsigned short high, low;
	unsigned long out;

	high = (*num >> 16) & 0x0000FFFF;
	low = *num & 0x0000FFFF;

	high = chendian16(&high);
	low = chendian16(&low);

	out = ((unsigned long)low << 16) | (unsigned long)high;

	*num = out;
	return out;
}
