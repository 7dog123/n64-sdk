===========================================================
bmp2u64 : BMP-16bitRGBA Converter  version 1.0
Copyright (C) 1997 Nintendo Co.,Ltd
===========================================================

The bmp2u64 tool, which is a PC tool, converts BMP files to Nintendo 64 format.

The current version only supports 16bitRGBA(5551) format.

BMP files that can be converted with the current version are the following four 
files.

	1bit, black/white, BMP
	4bit, 16 colors, BMP
	8bit, 256 colors, BMP
	24bitBMP

The current version does not support run length encoding (RLE) bitmap.

Use an ordinary non-compressed bitmap file.




Usage



Enter from DOS console as follows:

	bmp2u64 <infile> <outfile>

	infile  :  BMP file name to be input
	outfile :  U64 file name to be output