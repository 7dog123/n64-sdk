==================================================================================

                        Developers Toolkit Version 5.0
                                 8/4/1999
           
                                                       Nintendo of America Inc.
==================================================================================

Directory structure of "Developers Kit ver5.0" CDROM 

"NIFF," "NuSYSTEM," "N64 Disk Drive Multi File System (MFS)," "ccbl," "HVQ/HVQM," 
"DPTEST," "Monegi Multi Viewer64", and "DDTools" (Windows version only) can be 
installed using this package.  

The latest version of "N64 Sound Tools" is also included. For PC, the N64 Sound 
Tools is not launched from the top level installer. Please double-click 
"\pc\SndTools\Setup.exe" to install it.
Please see readme.txt in the N64 Sound Tools directory for details.  

CD[devkit50]----+--\pc
README.txt	|
CHANGES.txt	|
		+--\sgi




Installation Procedure
----------------------

SGI Workstation

Make a backup copy of the "n64kit" directory (previous version 4.2) by 
renaming etc., and delete it. 

Expand "tar xvzf n64kit50.tar" or "gunzip -c n64kit50.tgz|tar xvf -" 
under the directory "/usr/local/" of a system that uses n64kit42.tgz 
included under  "/sgi/" of this CD.


Windows

Uninstall all previous versions using "Add/Remove Programs" from the 
Control Panel. (Uninstall everything with n64 or n64kit)

Start "\pc\setup.exe" of this CD.  
The main installer will start and will start up installers for each 
component one-by-one (except for N64 Sound Tools). 
Note: It will take some time to install the entire package.


Contents:

NIFF (SGI/PC)
-------------

1. What's included in this release?

The following are distributed for release 5.0.

       Nintendo Intermediate File Format ver1.0 specification HTML version 
       Nitnendo Intermediate File Format ver2.0 specification HTML version
       NIFFeditor for SGI 
       NIFFeditor for WIN 
       NIFFAPI 
       NIFF Tools 
       niff2nvf converter 
       nvfview previewer 
       niff2gfx converter 
       n64prev previewer
       MultiTextureViewer(Windows version only) 

2. Directory structure

     The directory structure is as follows: 

          NIFFDIR = $N64KITDIR/niff

$NIFFDIR/bin/		:  NIFFeditor related
niffapi/		:  NIFFAPI related
nifftools/		:  NIFF tools
nvfview/		:  niff2nvf converter +nvfview previewer
mtv/			:  MultiTextureViewer related
n64prev/		:  niff2gfx converter +n64prev previewer
doc/			:  Documents
sample/			:  Samples
user_data/		:  User data


* By default,  N64KITDIR will be installed in the following directories.  
          (SGI)		N64KITDIR = /usr/local/n64kit
          (Windows)	N64KITDIR = c:\nintendo\n64kit

NIFF editor and converter depend upon the relative relationship of the 
directory structure under niff.   It is important that the relative 
relationship NOT be changed. However, it is possible to specify a 
separate directory for your data directory.  If the structure under niff
remains the same, you can copy the entire n64kit directory and use it 
under a different directory name.

NIFF Editor and converter write files in directories of nvfview and n64prev. 
Please make sure that these directories are not write protected. 

When Preview is executed from the Editor, the same file name is used each time.  
Therefore, if more than one person will be using NIFF Editor with the same 
hardware, make a copy of the niff directory in a different location so that 
nvfview and n64prev will be separate directories. 



NuSystem (SGI/PC)
-----------------

Directory structure

n64kit---/nusys	--/lib		Library
		|-/include	include file
		|-/src		Source file
		|-/doc		Document
		|-/sample	Sample software




64DD Multi File System (SGI/PC)
-------------------------------

n64kit---/mfs	--/lib		Library
		|-/include	include file
		|-/doc		Document
		|-/ddtool	Tools (rombuilder,rameditor,dddump)(PC only)



ccbl (SGI/PC)
-------------

n64kit---/ccbl			RDP function learning sample"ccbl"



DPTEST/MonegiMultiViewer64/N64CITextureEditor (PC only)
-------------------------------------------------------

n64kit---/dptest		DPTEST
	-/Mmv64			MonegiMultiViewer64
	-/texedit		N64CITextureEditor


HVQ/HVQM(SGI/PC)

Hvq------/Hvq			HVQ
	-/Hvqm			HMQM
	-/HVQlogo		logo data for HVQ


NuStd (SGI/PC)
--------------

n64kit---/nustd		(ANSI-based) Standard Function Library



Others (SGI/PC)
---------------

n64kit---/misc---/slide_v1.1	Compression/Decompression Software
		|-/sgi2pc	Audio Tool for SGI Library
				(ic, adpcmenc, etc.) for PC version. *Only PC
		|-/pakfatal	A program that destroies ID area of Controller Pak
		|-/audiochk	A tool that measures audio parameters including DMA 
				buffer size
		|-/bmp2u64	A tool that converts BMP file into 16 bit RGBA (5551) 
				format * Only PC.


Note:

The default setting is recommended for the directory to which the 
file will be installed.  However, if the directory is changed from the default, 
rewrite the Makefile definition (of N64KITDIR) accordingly. 


Support/upgrading
-----------------

Please contact Nintendo Technical Support

Phone: (425) 861-2736
FAX:   (425) 558-7100

Support is also available through our website: www.noa-engineering.com, 
or e-mail: support@noa.com
 
Patches are available through the NOA Engineering Website. 
