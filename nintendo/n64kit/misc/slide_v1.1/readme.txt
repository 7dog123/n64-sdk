N64 Compression/Flexible Library V1.1 (Created by Nintendo EAD)

Summary of the Decompression Method
This program is a tool used to compress (compression/flexible library) files 
with no loss of data.  It's composition is based on a front reference system.  
Since it performs decompression in real time on the actual machine, it needs to be at maximum speed. The compression software is used during the development of 
a game and doesn't need to be fast.  (Decompression takes top priority.)


Revision HIstory from V1.0
Decompression was not completed for some data. The bug was fixed.


Compression Software:

	Unix        SliencV11    Filename                
	Win95       Sliencw11    Filename

Function:
	Compresses the contents of filename.  The compressed data has an 
	extension .szp.	Depending upon the size of data, the compression may 
	take some time.

Main Functionality:  
	It is effective for compressing Vertex data or Texture data.

Example:  

	When Texture data is set to aaa.tex (RGBA16), aaa.szp is made by 
	entering sliencV11 aaa.tex (sliencw11 aaa.tex in Win95).
	After converting this to .c or .s file, put it in N64 software.

Software for Decompression:

	slidec.s
	Source code for N64.  From C, it is called by:

	Void slidstart(unsigned char* and unsigned char *);

	The first arguments are the head address (align4) of compression data, 
	and the next argument is the head address of the destination.


