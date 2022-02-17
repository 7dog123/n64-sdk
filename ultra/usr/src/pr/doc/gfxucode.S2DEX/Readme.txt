------------------------------------------------------------------
	sprite Microcode S2DEX Documentation
	Release 1.07
	Apr 10, 1998.
	Copyright (C) 1997-1998, Nintendo.
	Yoshitaka Yasumoto
	Nintendo Co., Inc. Development Dept. No. 3 
------------------------------------------------------------------
Contents
	1. What is S2DEX Microcode? 

	2. S2DEX Functions
		2.1  Render Primative
		2.2  Self-load Function 
		2.3  DEBUG Microcode 
		2.4  Transfer of commands from RSP to RDP

	3. Compatibility with F3DEX 
		3.1  GBI Supported by Both S2DEX and  F3DEX
		3.2  GBI Not Supported by S2DEX 
		3.3  Newly Added GBI
		3.4  Precautions Regarding GBI

	4. S2DEX,  GBI
		4.1  BG Render GBI
			4.1.1  uObjBg Structures
				4.1.1.1  uObjBg_t Structure 
				4.1.1.2  uObjScaleBg_t Structure
			4.1.2  gSPBgRectCopy
			4.1.3  gSPBgRect1Cyc

		4.2  sprite Rendering GBI 
			4.2.1  uObjsprite Structure
			4.2.2  uObjMtx/uObjSubMtx Structure
			4.2.3  gSPObjRectangle
			4.2.4  gSPObjRectangleR
			4.2.5  gSPObjsprite

		4.3  2D Matrix Operations
			4.3.1  gSPObjMatrix
			4.3.2  gSPObjSubMatrix

		4.4  Setting the Object Rendering Mode 
			4.4.1  gSPObjRenderMode
			4.4.2  About RenderMode During sprite Rendering

		4.5  Texture Loading GBI
			4.5.1  uObjTxtr Structure
			4.5.2  gSPObjLoadTxtr

		4.6  Complex Processing GBI
			4.6.1  uObjTxsprite Structure
			4.6.2  gSPObjLoadTxRect
			4.6.3  gSPObjLoadTxRectR
			4.6.4  gSPObjLoadTxSprite

		4.7  Conditional Branching GBI
			4.7.1  gSPSetStatus
			4.7.2  gSPSelectDL
			4.7.3  gSPSelectBranchDL

	5. Emulation Functions
		5.1  guS2DEmuBgRect1Cyc
		5.2  guS2DEmuSetScissor

	6. DEBUG Data Output Functions

	7. S2DEX Package Installation

	8. Revision History


------------------------------------------------------------------
1. What is S2DEX Microcode? 

S2DEX microcode was developed in order to enable the sprites and 
BG functions which were realized by the hardware in past game 
hardware to be used on the Nintendo 64 (hereinafter, N64).  This 
makes it easier to create sprite games than in the past.  In 
addition, by handling the rendering objects as the two separate 
concepts of sprites and BG Screens, it makes it easier to get 
used to the old method of creating sprite games.  


------------------------------------------------------------------
2. S2DEX Functions


---------------------
2.1 Render Primative 

Since S2DEX has been tuned especially for the processing of 2D 
expressions, it is not capable of supporting the rendering of 3D 
primatives as in Fast3D and F3DEX.  In place of that, the 
following types of primatives can be drawn with the S2DEX 
microcode. 
   
   1) Rectangle A -------- gSPObjRectangle,gSPObjRectangleR (Copy 
				   Mode)

		Fixed size, scaling and rotation are not possible
		Horizontal/vertical texture flipping possible
		Rendering in Copy mode
		Texture interpolated display, sub-pixel motion not 
		possible
		AntiAlias processing not possible
		Texture must already be loaded to TMEM

   2) Rectangle B -------- gSPObjRectangle,gSPObjRectangleR (1,2 
				   Cycle Mode)

		Scaling possible, rotation not possible
		Horizontal/vertical texture flipping possible
		Rendering in 1,2 Cycle Mode
		Texture interpolated display, sub-pixel motion 
		possible
		AntiAlias processing possible
		Texture must already be loaded in TMEM

   3) sprite ------------- gSPObjsprite

		Scaling and rotation possible
		Horizontal/vertical texture flipping possible
		Rendering in Copy Mode
		Texture interpolated display, sub-pixel motion 
		possible
		AntiAlias processing possible
		Texture must already be loaded in TMEM


   4) BackGround(BG) A --- gSPBgRectCopy

		Scaling possible
		Scrolling within respective vertically, horizontally 
		looped closed areas 
		Only horizontal flipping of texture is possible, 
		vertical flipping not possible
		Dedicated for rendering in Copy Mode
		Texture interpolated display, sub-pixel motion not 
		possible
		AntiAlias processing not possible
		Rendering by sequentially loading texture data in 
		DRAM to TMEM

   5) BackGround(BG) B --- gSPBgRect1Cyc
		           Emulation routine performed by CPU

		Scaling possible
		Scrolling within respective vertically, horizontally 
		looped closed areas 
		Only horizontal flipping of texture is possible, 
		vertical flipping not possible
		Dedicated for rendering in 1 Cycle Mode
		Texture interpolated display possible, sub-pixel 
		motion possible only horizontally
		AntiAlias processing not possible
		Rendering by sequentially loading texture data in 
		DRAM to TMEM


   * Some of Past GBI
		Those which can be used
		    FillRectangle
		    TextureRectangle
		    TextureRectangleFlip
		Those which cannot be used 
		    1Triangle
		    2Triangle
		    1Quadrangle

As shown above, S2DEX bears virtually no resemblance to the old 
sprite2D microcode in terms of its functions.  S2DEX is not an 
upgraded version of sprite2D, and is being positioned as an 
entirely new microcode.  In addition, since sprite libraries such 
as spInit(), and the like use 3D microcodes, they cannot be used 
in combination with S2DEX.  S2DEX is different from the sprite 
libraries. 


--------------------
2.2  Self-load Function 

As discussed above, there are no functions in S2DEX for rendering 
3D primatives.  However, the self-load function of the microcode 
that has been supported in F3DEX Release 1.20 and later has been 
installed in 2SDEX.  Because of this, it is possible to render 3D 
primatives by loading the F3DEX microcode.  

However, please be aware that switching between S2DEX is not 
supported unless the F3DEX microcode is Release 1.22 or later or 
Development Environment 2.0I or later. 


------------------------
2.3  DEBUG Data Output Function 

The S2DEX microcode is equipped with two types of code.  One is 
code which is brought into play during normal game shipment, 
while the other is used during debugging.  The DEBUG microcode 
makes has the following functions that the shipping microcode 
does not have. 

	* Display list processing log output
	* The RSP is terminated when there is an improper input 
	  value or an improper command and the CPU is notified. 

Detailed instructions for use are given below. 


-----------------------------------------
2.4  Command Transfer from RSP to RDP

Like the F3DEX series, S2DEX only supports fifo versions. 

However, the FIFO buffer size required by S2DEX is larger than 
that for the F3DEX Series.  While at least 0x300 bytes were 
required for the F3DEX Series, 0x800 bytes or more are needed 
for S2DEX.  Please not that 0x800 bytes or more will be required 
to comply with the S2DEX needs if you wish to share the FIFO 
buffer between the F3DEX Series and S2DEX.  

(*)  The minimum FIFO size in the fifo microcode is given as 
0x100 on some of the manual pages, but that is in error.  The 
required FIFO size differs for each microcode, with F3DEX Series 
and S2DEX requiring the sized noted above, and Fast3D needing 
0x180 bytes. 


------------------------------------------------------------------
3. Compatibility with F3DEX

S2DEX GBI are derived from F3DEX.  Because of this, they are not 
compatible with Fast3D GBI.  When using 2SDEX, as with F3DEX, it 
is necessary to define F3DEX_GBI before including ultra64.h.  

  In addition, in order to use S2DEX GBI, it is necessary to 
include the header file <PR/gs2dex.h>.  Insert the include 
specification after the specification to include <ultra64.h>

At this point, the S2DEX will be explained in contrast with 
F3DEX.  In general, GBI related to 3D primative operations, 4x4 
matrix operations, and write definitions may be considered as not 
being supported by S2DEX. 

Only gSP* and gDP* will be mentioned in the following, but the 
same is true for gsSP* and gsDP*. 


-------------------------------------------
3.1  GBI Supported by Both S2DEX and F3DEX

  ---------------------------------------------------------------
  DL Processing Control	gSPDisplayList(*)	gSPBranchList
			gSPEndDisplayList

  Set Segment	gSPSegment(*)

  Load Microcode 	gSPLoadUcode*

  Scissoring	gDPSetScissor		gDPSetScissorFrac

  RDP Mode Settings	gSPSetOtherMode	gDPSetCycleType
			gDPSetTexturePersp	gDPSetTextureDetail
			gDPSetTextureLOD		gDPSetTextureLUT
			gDPSetTextureFilter	gDPSetTextureConvert
			gDPSetCombineKey		gDPSetColorDither
			gDPSetAlphaDither		gDPSetBlendMask
			gDPSetAlphaCompare	gDPSetDepthSource
			gDPSetRenderMode		gDPSetColorImage
			gDPSetDepthImage		gDPSetTextureImage
			gDPSetCombineMode

  Set Color Values, etc.	gDPSetEnvColor	gDPSetBlendColor
			gDPSetFogColor		gDPSetFillColor
			gDPSetPrimColor		gDPSetPrimDepth
			gDPSetConvert		gDPSetKeyR
			gDPSetKeyGB

  Load to TMEM	gDPSetTileSize		gDPLoadTile
			gDPSetTile			gDPLoadTextureBlock*
			gDPLoadMultiBlock*	gDPLoadTextureTile*
			gDPLoadMultiTile*		gDPLoadTLUT_pal16
			gDPLoadTLUT_pal256

  Primatives 	gDPFillRectangle		gDPScisFillRectangle
			gSPTextureRectangle	gSPScisTextureRectangle
			gsSPTextureRectangleFlip

  Sync Processing		gDPFullSync		gDPTileSync
				gDPPipeSync		gDPLoadSync

  NOOP		gSPNoOp			gDPNoOp
			gDPNoOpTag
  ---------------------------------------------------------------
  (*) In S2DEX, as in F3DEX, 16 segments can be specified by 
  gSPSegment, and the number of DL links which can be specified 
  by gSPDisplayList is 18. 


-------------------------------
3.2  GBI Not Supported by S2DEX

  ---------------------------------------------------------------
  Field Settings		gSPViewport		gSPClipRatio
			gSPPerspNormalize

  Matrix Operations	gSPMatrix		gSPPopMatrix
			gSPInsertMatrix		gSPForceMatrix

  Vertex Operations	gSPVertex		gSPModifyVertex

  Conditional Branching	gSPCullDisplayList	gSPBranchLessZ*

  Set Polygon Type gSPSetGeometryMode	gSPClearGeometryMode
			 gSPTexture			gSPTextureL

  Primatives 	gSP1Triangle		gSP2Triangles
			gSP1Quadrangle		gSPLine3D
			gSPLineW3D

  Lighting 		gSPNumLights		gSPLight
			gSPLightColor		gSPSetLights[0-7]
			gSPLookAt*			gDPSetHilite1Tile
			gDPSetHilite2Tile

  Fog			gSPFogFactor		gSPFogPosition

  For ld sprite2D	gSPsprite2DBase		gSPsprite2DScaleFlip
			gSPsprite2DDraw
  ---------------------------------------------------------------


--------------------
3.3  Newly Added GBI

  ---------------------------------------------------------------
  Render BG		gSPBgRectCopy		gSPBgRect1Cyc
	
  Render Sprinte	gSPObjRectangle		gSPObjRectangleR
			gSPObjsprite

  2D Matrix Operations	gSPObjMatrix	gSPObjSubMatrix

  Set Rendering Mode	gSPObjRenderMode

  Load Texture Processing	gSPObjLoadTxtr

  Complex Commands	gSPObjLoadTxRect	gSPObjLoadTxRectR
				gSPObjLoadTxsprite

  Conditional Branching	gSPSelectDL		gSPSelectBranchDL
  ---------------------------------------------------------------


------------------------------
3.4  Precautions Regarding GBI

About overwriting the mode with OtherMode:

When changing the mode in F3DEX using g[s]SPSetOtherMode, no 
more than a maximum for 31 bits could be set with a single 
g[s]SPSetOtherMode command.  With S2DEX, this has been corrected 
so that 32 bits worth of parameters can be changed with a one 
command. 

In addition, normal operation could not be performed in F3DEX if 
the g[s]DPSetOtherMode command was mixed up with a 
g*SPSetOtherMode type command when overwriting the mode.  
(Normal settings cannot be made with g*SPSetOtherMode.)  This has 
been corrected in S2DEX so that these can coexist. 


------------------------------------------------------------------
4. S2DEX,  GBI


------------------	
4.1  BG Render GBI

S2DEX has been equipped with functions to easily create scroll 
screens in the respective vertically or horizontally looped 
closed areas with which past game hardware was equipped.  This 
will probably reduce the time and labor required to create a 
scrolling game like 2D Mario. 


-----------------------
4.1.1  uObjBg Structure 

The uObjBg structure holds the BG rendering data.  A pointer to 
this structure is provided as an argument for BG rendering GBI.  

The uObjBg accurately comprises 3 common structures.  One is for 
aligning the structures on 8-byte boundaries, and no attention 
need be paid to this one.  The remaining two have data structures 
which correspond with the two BG rendering GBI discussed below. 

The structure which corresponds with the BG rendering GBI by Copy 
mode described in 4.1.2 is uObjBg_t, and the structure which 
corresponds with the BG rendering GBI in 1 Cycle mode is 
uObjScaleBg_t. 

 ----------------------------------------------------------------
  typedef union {
    uObjBg_t        b;
    uObjScaleBg_t   s;
    long long int   force_structure_alignment;
  } uObjBg;
 ----------------------------------------------------------------


---------------------------
4.1.1.1  uObjBg_t Structure 

The members of the uObjGb_t structure are divided into two groups 
-- a front half and a back half. 

The front half are member variables which are directly set by the 
user.  Rendering of the BG screen is controlled by controlling 
these values.  This front half is shared with the uObjScaleBg_t 
structure. 

In contrast to this, the back half comprises member variables for 
which values must be calculated in advance by the CPU in order to 
assist the microcode.  These member variables are set by calling 
the function guS2DInitBg() with the pointer to the uObjBg 
structure as the argument.  However, it is not necessary to call 
guS2DInitBg every time.  

Since the member variables of the latter half are extracted from 
the member variables of the front half --imageLoad, imageFmt, 
imageSiz, imageW, frameW -- It is only necessary to call 
guS2DInitBg immediately after those values have changed.

Since these values normally do not frequently change when uObjBg 
is used as the BG screen, it probably enough to call guS2DInitBg 
only once prior to using a BG screen.  

However, when the uObjBg data have changed due to the 
uObjScaleBg_t  structure, which is shared by uObjBg_t, being 
used, i.e., when the values for the member variables, scaleW, 
scaleH, imageYorig, of the uObjScaleBg_t structure have changed, 
the member variables in the latter half of uObjBg_t may be 
overwritten.  In this kind of situation, it probably will be 
necessary to call guS2DInitBg again. 

Following is the section in the gs2dex.h header file in which 
uObjBg is defined.  The size of uObjBg is 40 bytes and uObjBg 
must be aligned at 8 bytes.  

The front half member is explained under the item describing an 
actual GBI. While the arrangement of the member variables is 
somewhat difficult, please understand that it is an unavoidable 
circumstance in the optimization of RSP processing. 

Please note that the format for the member variables imagePal 
and imageFlip changed from u8 to 816 in S2DEX Release 1.00 and 
later. 

 ----------------------------------------------------------------
  typedef struct  {
    u16   imageX;         // X coordinate at upper-left position 
					of BG image (u10.5)
    u16   imageW;         // BG image width 	(u10.2)
    s16   frameX;         // Upper-left position of transfer 
					frame  (s10.2)
    u16   frameW;         // Transfer frame width 	 (u10.2)

    u16   imageY;         // Y coordinate at upper left position 
					of BG image  (u10.5)
    u16   imageH;         // BG image height   	(u10.2)       
    s16   frameY;         // Upper-left position of transfer 
					frame (s10.2)
    u16   frameH;         // Transfer frame height 	(u10.2)
  
    u64  *imagePtr;       // Texture address at upper-left 
					position of BG image 
    u16   imageLoad;      // Use LoadBlock or LoadTile?
    u8    imageFmt;       // BG image format 	G_IM_FMT_*   
    u8    imageSiz;       // BG image size 	G_IM_SIZ_*   
    u16   imagePal;       // Pallette number 
    u16   imageFlip;      // Flip image with horizontal flip 
					G_BG_FLAG_FLIPS
    // Up to this point is shared by uObgScaleBg_t
  
    // Since the following are set in the initialization routine 
		guS2DInitBg() they 
    // do not need to be set by the user
    u16   tmemW;	// TMEM width Word size for frame 1 
				line
		// When LoadBlock GS_PIX2TMEM(imageW/4,imageSiz) 
		// When LoadTile GS_PIX2TMEM(frameW/4,imageSiz)+1 
    u16   tmemH;	// Quadruple TMEM height (s13.2) which can be 
				loaded at once
		// When normal texture 	512/tmemW*4
		// When CI Texture 	256/tmemW*4
    u16   tmemLoadSH;     // SH value 
                          // When LoadBlock tmemSize/2-1
                          // When LoadTile tmemW*16-1       
    u16   tmemLoadTH;     // TH value or Stride value 
                          // When LoadBlock GS_CALC_DXT(tmemW)
                          // When LoadTile  		tmemH-1
    u16   tmemSizeW;      // imagePtr skip value for one line of 
					image 1 
                          // When LoadBlock 	tmemW*2
		// When LoadTile GS_PIX2TMEM(imageW/4,imageSiz)*2
    u16   tmemSize;       // imagePtr skip value for one load 
					iteration
                          // = tmemSizeW*tmemH
  } uObjBg_t;             // 40 bytes
 ------------------------------------------------------------------

  Definition of initialization function guS2DInitBg
 ------------------------------------------------------------------
	void    guS2DInitBg(uObjBg *bg);

	Description: Initialization of uObjBg structure (uObjBg_t) 
		Used when rendering uObjBg_t with gSPBgRectCopyGBI.  
		Called immediately after substituting default values 
		to uObjBg_t, and immediately after some of member 
		variables imageLoad, imageFmt, imageSiz, imageW, 
		imageH have changed. 

	Argument:	bg	Pointer to uObjBg structure

	Note:	This function must not be called when the 
		uObjScaleBg_t is used.  (The values of the members of 
		uObjScaleBg_t will be destroyed.) 
 ----------------------------------------------------------------

--------------------------------
4.1.1.2  uObjScaleBg_t Structure 

The members of the uObjScaleBg_t structure have no variables for 
which the values must be calculated in advance by the CPU as with 
uObjBg_t.  All of the member variables are directly set by the 
user.  Rendering of the BG screen is controlled in this way. 

In addition, when shared by the uObjBg structure, the 
uObjScaleBg_t member variables from imageX through imageFlip are 
shared by the uObjBg_t structure. 

 -----------------------------------------------------------------
  typedef struct  {
    u16   imageX;         // X coordinate at upper-left position 
					of BG image (u10.5)
    u16   imageW;         // BG image width 	(u10.2)
    s16   frameX;         // Upper-left position of transfer 
					frame 	(s10.2)
    u16   frameW;         // Transfer frame width           (u10.2)

    u16   imageY;         // Y coordinate at upper-left position 
					of BG image (u10.5)
    u16   imageH;         // BG image height 		(u10.2)
    s16   frameY;         // Upper-left position of transfer 
					frame 	(s10.2)
    u16   frameH;         // Transfer frame height 	(u10.2)
  
    u64  *imagePtr;       // Texture address of BG image upper-
					left corner 
    u16   imageLoad;      // Use LoadBlock or LoadTile?
    u8    imageFmt;       // BG image format		G_IM_FMT_*
    u8    imageSiz;       // BG image size 		G_IM_SIZ_*
    u16   imagePal;       // Pallette number
    u16   imageFlip;      // Flip image with horizontal flip 
					G_BG_FLAG_FLIP
    // Up to this point is shared by uObjBG_t

    u16   scaleW;         // Scale value in X direction (u5.10)
    u16   scaleH;         // Scale value in Y direction (u5.10)
    s32   imageYorig;     // Rendering origin in image  (s20.5)
    
    u8    padding[4];
  } uObjScaleBg_t;        // 40 bytes
 -----------------------------------------------------------------


--------------------
4.1.2  gSPBgRectCopy

	----------------------------------------------------------
	 gSPBgRectCopy(Gfx *gdl, uObjBg *bg)
	 gsSPBgRectCopy(uObjBg *bg)

	 Gfx		*gdl;	Display list point
	 uObjBg	*bg;	Pointer to rendering data structure
	----------------------------------------------------------

  g[s]SPBgRectCopy  is one of the BG screen rendering GBI 
  provided by S2DEX, and is the most simple.  It has the 
  following features. 

	------------------------------------------------------------
	 Scaling possible
	 Scrolling is possible in respective vertically and 
	  horizontally looped closed areas
	 Texture can be flipped only horizontally, vertical 
	  flipping is not possible
	 Dedicated for rendering in Copy mode
	 Texture interpolated display, sub-pixel motion not 
	  possible
	 AntiAlias processing not possible
	 Rendering by sequentially loading texture data in DRAM to 
	  TMEM on GBI side
	------------------------------------------------------------

Since rendering in Copy mode is presumed, its greatest advantage 
is its high speed.  Because of this, CycleType must be in Copy 
mode when this GBI is used. 

The BG function in S2DEX transfer data from the BG image buffer 
to a rectangular area in the actual frame buffer, as shown below.  
Scrolling is possible by using imageX and imageY to specify the 
place in the BG image buffer to which the upper-left corner of 
the rectangular area in the frame buffer at that time 
(hereinafter, the transfer frame) corresponds.  These variables 
imageX and imageY can be specified in the (u10.5) format, but due 
to restrictions in using the Copy mode, the values for imageX and 
imageY must be rounded to the nearest integer value.  


        BG image                       Color Frame Buffer
                                     +---------------------+
     +------------+  ^               |(frameX,frameY)      |
     |  |         |  |               |   *-------------+ ^ |
     |--*---------|  |               |   |             | | |
     |  |(imageX, | imageH           |   |             | | |
     |  | imageY) |  |               |   |             |frameH
     |  |         |  |               |   |             | | | 
     +------------+  v               |   |Transfer Frame | |
     <-- imageW -->                  |   +-------------+ v |
                                     |   <-- frameW  -->   |
                                     +---------------------+

The size of the BG image is set with imageW and imageH, and the 
head address (address of the upper-left corner) is specified by 
imagePtr.  In other words, the Bg image can be viewed as imageW 
wide by imageH high texture data whose head is at the address 
imagePtr.  

The width imageW of the BG image must be aligned on 8 bytes.  
Since the values for imageW and imageH which are actually used 
are in (u10.2) format, it is necessary to substitute the 4x 
value.  Taking the (u10.2) format into consideration, the 
concrete limitations on imageW when it has been quadrupled are 
shown below.  There is no need to align imageH. 

      -------------------------------------------------
	G_IM_SIZ_4b:	imageW must be a multiple of 64
	G_IM_SIZ_8b:	imageW must be a multiple of 32
	G_IM_SIZ_16b:	imageW must be multiple of 16
	G_IM_SIZ_32b:	imageW must be multiple of 8
      -------------------------------------------------

In addition, which doing horizontal scrolling, imageW must be 
greater than frameW.  The following values are the values when 
considering the (u10.2) format.  In the case of G_IM_SIZ_16b, 
it must be increased by 4 pixels. 

      -------------------------------------
	G_IM_SIZ_4b:	frameW+64 <= imageW
	G_IM_SIZ_8b:	frameW+32 <= imageW
	G_IM_SIZ_16b:	frameW+16 <= imageW
	G_IM_SIZ_32b:	frameW+ 8 <= imageW
      -------------------------------------
  

The size of the transfer frame is specified by frameW and frameH, 
and the position on the screen of the upper-left corner of the 
transfer frame is specified by frameX and frameY.  The frameW/
frameH parameters are in (u10.2) format, while the frameX/frameY 
parameters are in (s10.2) format.  In other words, negative 
numbers can be specified as the values for frameX and frameY, and 
if the transfer is projected from a scissor box specified by 
g[s]DPSetScissor, the microcode will clip the projecting part. 

There is problem if the BG image is larger than the transfer 
frame, but proper functioning cannot be guaranteed if the 
transfer frame conversely is larger than the BG image.  Please be 
careful that the transfer frame does not become larger than the 
BG image. 

In addition, right edge and left edge of the BG image are shifted 
one step in the Y direction to make a smooth transition.  
Concretely speaking, the one pixel to the right of the pixel at 
the right edge of the BG image (imageW-1,n) is (0,n+1).  This is 
necessary to improve the RDRAM access efficiency when loading the 
Texture.  Persons creating applications should be fully aware of 
this. 

The format and size of textures in the BG image are substituted 
into imageFmt and imageSiz by the macros G_IM_FMT_* and 
G_IM_SIZ_*, respectively.  In addition, when using CI4 textures, 
the TLUT number is specified in imagePal.  

There are two methods for loading textures in a BG image.  These 
are the method of using LoadBlock and that of using LoadTile.  
Since there are various advantages and disadvantages to each of 
these two methods, the user is able to select which of these two 
methods will be used by the member variable imageLoad.  The 
following values (G_BGLT_*) are substituted into imageLoad. 

	-------------------------------
	 imageLoad Value	Meaning
	 G_BGLT_LOADBLOCK	Use LoadBlock 
	 G_BGLT_LOADTILE	Use LoadTile  
	-------------------------------
  
Using LoadBlock will, under certain conditions, yield the maximum 
performance, but it cannot be used unless those conditions are 
met, and it has a great deal of overhead for processing.  In 
contrast, LoadTile performs processing at suitable performance 
under virtually any circumstances.  Consequently, it is 
recommended that you switch back and forth so that you use 
LoadBlock under the conditions in which LoadBlock will operate 
effectively, and use LoadTile in any other situations. 

The conditions under which LoadBlock would be used are those in 
which there are restrictions on the width of the BG image that 
can be used.  The values for imageW which can be processed by 
LoadBlock are as follows, when imageSiz is 16 bits. 

	  4,  8, 12, 16, 20, 24, 28, 32, 36, 40,
	 48, 64, 72, 76,100,108,128,144,152,164,
	200,216,228,256,304,328,432,456,512,684,
	820,912

When imageSiz is 8 bits, the number string when the various items 
in the above number string have each been doubled becomes the 
value for imageW.  Similarly, when it is 4 bits, the numbers are 
quadrupled, and when it is 32 bits, the numbers are halved.  This 
coincides with the expression in Appendix A in Chapter 13 of the 
N64 Programming Manual which states that "there is a limit to the 
number of lines which can be transferred with the LoadBlock 
command."  If the width of the BG image cannot be processed with 
LoadBlock, you have no choice but to use LoadTile. 

In order for LoadBlock to render one line of the transfer frame, 
one entire line worth of the corresponding BG image is loaded.  
Since a normal scrolling BG screen requires that a slightly 
larger BG image be available for the BG refresh area, 
imageW>frameW must be true.  Because of this, excess data are 
loaded when LoadBlock is used. 

In contrast, LoadTile loads no more than the required amount of 
data.  Since the LoadBlock command performs processing faster 
than the LoadTile command, LoadBlock is more advantageous when 
that difference is several pixels, but if imageW is a fair amount 
larger than frameW, the resulting excess load processing produces 
a large overhead and it becomes advantageous to use LoadTile.  
Thus, it is necessary to select which of these to use taking this 
point into consideration. 

As a typical example, a BG screen which covers the entire screen 
(320x240) is defined.  

Because the transfer frame is the entire frame, frameW=320 pixels.  
Then, when 8 pixels are set aside as the BG refresh area, 
imageW=328 pixels.  In this case, since the difference between 
frameW and imageW is slight, LoadBlock may be used at 328 pixels. 

Flipping of the BG image in only the horizontal direction is 
supported by this GBI.  Substitute G_BG_FLAG_FLIPS in the member 
variable imageFlip to flip the texture image.  Substitute a 0 
[zero] for normal display (not flipped).  


----------------------
4.1.3  gSPBgRect1Cyc

	----------------------------------------------------------
	 gSPBgRect1Cyc(Gfx *gdl, uObjBg *bg)
	 gsSPBgRect1Cyc(uObjBg *bg)

	 Gfx		*gdl;	Display list pointer
	 uObjBg	*bg;	Pointer to BG rendering data structure
	----------------------------------------------------------

  g[s]SPBgRect1Cyc is one of the BG screen rendering GBI provided 
  by S2DEX which enables scaling of BG screens.  Its features are 
  shown below. 

	-----------------------------------------------------------
	 Scaling possible
	 Scrolling is possible in respective vertically and 
	  horizontally looped closed areas
	 Texture can be flipped only horizontally, vertical 
	  flipping is not possible
	 Dedicated for rendering in 1 Cycle mode
	 Texture interpolated display possible, sub-pixel motion 
	  possible only in horizontal direction
	 AntiAlias processing not possible
	 Rendering by sequentially loading texture data in DRAM to 
	  TMEM on GBI side
	-----------------------------------------------------------

Please not that this GBI cannot be used in Copy mode. 

The parameters required for rendering with g[s]SPBgRect1Cyc are 
the parameters which are required when using g[s]SPBgRectCopy 
described in 4.1.2, plus scaleW, scaleH, and imageYorig.  See 
Section 4.1.2 for descriptions of the parameters which are common 
with g[s]SPBgRectCopy.  The additional parameters will be 
explained here. 

The biggest difference between g[s]SPBgRect1Cyc and 
g[s]SPBgRectCopy is that it supports BG scaling.  Scaling of the 
BG is controlled by the member variables scaleW and scaleH of the 
uObjScaleBg_t structure.  This scaling is centered on the BG image 
(imageX, imageY).  

In other words, even when the BG image is scaled, it is rendered 
in the same (frameX, frameY) location in the frame buffer as when 
the BG image (imageX,imageY) is not scaled.  (However, when it is 
flipped horizontally, it is rendered at the position 
(frameX+frameW-1,frameY).)

In addition, during enlargement, the image is clamped by the size 
of the frame.  Conversely, during reduction, there are cases in 
which the frame is clamped by the size of the image.  Refer to 
the S2DEX sample program regarding this. 

However, there are cases in which the clamping on the frame 
during reduction is slightly larger or smaller due to calculation 
differences.  If a strict size is required, set the size by 
calculating frameW and frameH on the CPU side. 

Bilinear interpolated display of an image is supported by 
g[s]SPBgRect1Cyc.  When bilinear interpolated display is used, 
jaggies are less apparent in the texels, making them apparently 
more smooth, during enlargement.  However, this effect is 
minimized during reduction. 

When bilinear interpolation is used, RDP rendering performance is 
decreased as compared to when it is not used.  Since the 
percentage of this decrease increases to the extent that the 
number of image lines which can be loaded at once is small, when 
a case in which a 320x240 image is rendered at 1:1 size in a 
320x240 frame is compared with a case in which a 640x480 image 
is rendered reduced by 1/2, the proportion of overhead will 
increase due to the 640x480 image using bilinear interpolation, 
substantially reducing performance even more than when a 640x480 
is similarly reduced and displayed by point sampling.  
Considering that the effect of bilinear interpolation becomes 
minimal during reduction, as explained above, one should also 
look into switching to point sampling during reduction. 

g[s]SPBgRect1Cyc renders an image by automatically dividing it 
into multiple sub-planes, but if this division processing is 
carelessly performed, there is the possibility that unnatural 
wrinkles will appear in the rendering result.  This is especially 
noticeable during scrolling processing,  and uObjScaleBg_t is 
equipped with the member variable imageYorig in order to prevent 
these wrinkles.  The value for imageYorig indicates the Y 
coordinate of the origin of scaling, but it also indicates the 
division origin of the sub-plane.  Thus, is possible to avoid the 
wrinkles described above.  Typically, imageYorig operates as 
follows. 

	o During intialization: 
	The value for imageY is substituted for imageYorig

	o When the value for scale H has been changed: 
	The value for imageY is substituted for imageYorig

	o When imageX and imageY are wrap processed: 
	The same processing that is performed on imageY is 
	performed also on imageYorig.  

	o When only imageY is to be changed. 
	Do not change imageYorig. 

Based on the above, the processing when scrolling the image by 
only dx,dy is shown below. 

	------------------------------------------
	  /* Match the number of digits in imageW and imageH */
	  s16	bg_imageW = bg->s.imageW << 3;
	  s16	bg_imageH = bg->s.imageW << 3;
	  
	  /* Add the scroll value */
	  bg->s.imageX += dx;
	  bg->s.imageY += dy;

	  /* Wrap processing of screen edge */
	  if (bg->s.imageX < 0){
	    bg->s.imageX     += bg_imageW;
	    bg->s.imageY     -= 32;
	    bg->s.imageYorig -= 32;
	  }
	  if (bg->s.imageX >= bg_imageW){
	    bg->s.imageX     -= bg_imageW;
	    bg->s.imageY     += 32;
	    bg->s.imageYorig += 32;
	  }
	  if (bg->s.imageY < 0){
	    bg->s.imageY     += bg_imageH;
	    bg->s.imageYorig += bg_imageH;
	  }
	  if (bg->s.imageY >= bg_imageH){
	    bg->s.imageY     -= bg_imageH;
	    bg->s.imageYorig -= bg_imageH;
	  }
	------------------------------------------

With this GBI, as when in the COPY mode, flipping of the BG image 
in only the horizontal direction is supported.  Substitute 
G_BG_FLAG_FLIPS in the member variable imageFlip to flip the 
texture image.  Substitute a 0 [zero] for normal display (not 
flipped).  


When using this GBI, the value for the member variable imagePtr 
of the uObjScaleBg_t structure is limited.  A location from the 
head of RDRAM to the 4069 byte must not be specified as the value 
of imagePtr.  These are the addresses from 0x00000000 to 
0x00000fff of the so-called physical addresses, and so the value 
for imagePtr after segment conversion must not be in this range.  
Please make a note of this. 

This GBI is installed with S2DEX Release 1.00 and later. 

The function guS2DEmuBgRect1Cyc has been added which emulates 
processing which is equivalent to gSPBgRect1Cyc from S2DEX 
Release 0.75 by combining several GBI such as 
gSPTextureRectangle, etc. It is possible to render scalable BG 
screens even when this is used.  Refer to Chapter 5 for details.  


-------------------------
4.2  sprite Rendering GBI

The sprites referred to here are the same as OBJECTs in past 
Famicom and SuperFamicom.  Since sprites are used to rendered an 
area which is smaller than the BG screen, historically, they have 
come to be well used as Player characters.  With S2DEX, 
processing such as scaling and rotation become possible for 
conventional sprites.  In addition, since bilinear interpolation 
processing is also possible during enlargement, more natural 
realization is made possible. 

A conversion matrix is provided in the 2D coordinate system in 
order to support sprite rotation.  By setting the various 
elements in this matrix, it is possible to freely rotate the 
sprite.  This matrix must be set up prior to rendering processing 
of the sprite.  In addition, unlike the matrixes in Fast3D and 
F3DEX microcodes, since there is no matrix stack, Push/Pop cannot 
be done.  In addition, matrix multiplication is also disabled.  
Only load processing is possible.  (See section 4.3) 

In the S2DEX sprite function, there are specifications that allow 
TMEM loading processing, sprite rendering processing, and there 
are other GBI that perform various other functions.  In other 
words, when rendering a sprite, the texture used by the sprite 
must already be loaded using a texture load GBI (See section 
4.5).  

The rendering modes for sprites can be generally divided into 
those which allow rotation and those which do not, and 
processing is performed by the corresponding GBI, as shown below. 

	---------------------------------------------------------
	 Render mode	Corresponding GBI
	 No rotation	g[s]SPObjRectangle, g[s]SPObjRectangleR
	 Rotation	g[s]SPObjsprite
	---------------------------------------------------------


-------------------------
4.2.1  uObjsprite Structure

The uObjsprite structure is the structure which handles sprite 
information.  Pointers are given in the sprite rendering GBI to 
this structure as arguments. 

 ----------------------------------------------------------------
  typedef struct {
    s16  objX;         // s10.2 X coordinate at upper-left of OBJ
    u16  scaleW;       // u5.10 Scaling in width direction 
    u16  imageW;       // u10.5 Width of texture (length in S 
					direction)
    u16	 paddingX; // Not used    Always 0
  
    s16  objY;         // s10.2 Y coordinate at upper-left of OBJ
    u16  scaleH;       // u5.10 Scaling in height direction 
    u16  imageH;       // u10.5 Height of texture (length in T 
					direction) 
    u16	 paddingY; // Not used   Always 0

    u16  imageStride;  // Texel wrap width (64 bit word units) 
    u16  imageAdrs;    // Texture head position in TMEM (64 bit 
					word units)
   
    u8   imageFmt;     // Texel format  G_IM_FMT_*
    u8   imageSiz;     // Texel size  G_IM_SIZ_*
    u8   imagePal;     // Pallette number
    u8   imageFlags;   // Display flags

  } uObjsprite_t;      // 24 bytes

  typedef union {
    uObjsprite_t    s;
    long long int   force_structure_alignment;
  } uObjsprite;
 -----------------------------------------------------------------

While the arrangement of the member variables is somewhat 
difficult, please understand that, as with the uObjBg structure, 
it is an unavoidable circumstance in the optimization of RSP 
processing. 


------------------------------------
4.2.2  uObjMtx/uObjSubMtx Structures

An area is provided in the S2DEX microcode for maintaining a 2D 
matrix for the control of sprite rotation.  There are 8 
parameters {A, B, C, D, X, Y, BaseScaleX, BaseScaleY). 

The uObjMtx structure is used to alter the entire 2D matrix on a 
1:1 correlation with this 2D matrix area.  See section 4.2.5 
regarding rotation processing using this 2D matrix. 

 ------------------------------------------------------
  typedef struct {
    s32   A, B, C, D;     /* s15.16 */
    s16   X, Y;           /* s10.2  */
    u16   BaseScaleX;     /* u5.10  */
    u16   BaseScaleY;     /* u5.10  */
  } uObjMtx_t;            /* 24 bytes */

  typedef union {
    uObjMtx_t     m;
    long long int force_structure_alignment;
  } uObjMtx;
 ------------------------------------------------------

uObjSubMtx is a subset of uObjMtx which is used to alter only 
those elements outside the 2D matrix rotation matrix {x, y, 
BaseScaleX, BaseScaleY}, and is primarily used when rendering a 
sprite using g[s]SPObgRectangleR.  This is explained in detail 
in section 4.2.4. 

 ------------------------------------------------------  
  typedef struct {
    s16   X, Y;           /* s10.2  */
    u16   BaseScaleX;     /* u5.10  */
    u16   BaseScaleY;     /* u5.10  */
  } uObjSubMtx_t;         /* 8 bytes */

  typedef union {
    uObjSubMtx_t  m;
    long long int force_structure_alignment;
  } uObjSubMtx;
 ------------------------------------------------------

The 8 elements in the 2D matrix {A, B, C, D, W, Y, BaseScaleX, 
BaseScaleY} are referred to by g[s]SPObjsprite and 
g[s]SPRectangleR.  However, this does not necessarily mean that 
all 8 of the elements are referenced.  Reference is done as 
shown below.  {X,Y} are referenced in both cases. 

            +- Referenced by g[s]SPObjsprite -+
            |                          |
            |     A, B   +-------------+----------------+
            |     C, D   |    X, Y     |   BaseScaleX   |
            +------------+-------------+   BaseScaleY   |
                         |                              |
                         +- Referenced by g[s]SPObjRectangleR -+


-----------------------
4.2.3  gSPObjRectangle

	-----------------------------------------------------------
	 gSPObjRectangle(Gfx *gdl, uObjsprite *sp)
	 gsSPObjRectangle(uObjsprite *sp)

	 Gfx		*gdl;	Display list pointer
	 uObjsprite	*sp;	Pointer to sprite rendering data 
				structure 
	-----------------------------------------------------------

g[s]SPObjRectangle is one of the sprite rendering GBI provided 
by S2DEX, and is used to render sprites which do not rotate.  
The processing which occurs inside the RSP is to create a 
TextureRectangle command from the data in the uObjsprite 
structure which has been input, and then send said command to 
the RDP. 

The g[s]SPObjRectangle GBI renders the texture in a rectangular 
area whose screen coordinates at the upper-left corner are (objX, 
objY) and whose coordinates at the lower-right corner are 
(objX+imageW/scaleW-1, objY+imageH/scaleY-1).  The texture area 
which is rendered is the one whose upper-left corner is (0,0) and 
whose lower-right corner is (imageW-1, imageH-1).  If scaleW and 
scaleH are 1<<10, the texture is rendered at 1:1 magnification, 
without any scaling.  


    +--------TMEM--------+      +---------Frame Buffer---------+
    |                    |      |(objX,objY)                   |
    |      (0,0)         |      |  X-------------+             |
  imageAdrs->X---------+ |      |  |             |             |
    |        | Texture | |      |  | sprite Area |             |
    |        |  Area   | | ===> |  |             |             |
    |        |         | |      |  |             |             |
    |        +---------X |      |  |             |             |
    +------------- (imageW-1,   |  +-------------X             |
                    imageH-1)   |       (objX+imageW/scaleW-1, |
                                |        objY+imageH/scaleH-1) |
                                |                              |
                                +------------------------------+

In addition, during sprite rendering, clip processing of the 
rendering area is automatically performed, referring to the 
scissor box which has been set by gDPSetScissor.  Because of 
this, it is also possible to set negative values as the values 
for objX and objY. 

The TMEM address which corresponds with the origin (0,0) of the 
texture area can be specified by imageadrs.  Normally, the head 
load location in TMEM which has been specified int he texture 
loading GBI is specified as imageAdrs.  It would probably be 
convenient to use the macro GS_PIX2TMEM() when making this 
specification.  GS_PIX2TMEME() is a macro which converts the 
numeric value in pixel units to one in TMEM address units, and 
is defined in gs2dex.h. 

	----------------------------------------------
	 GS_PIX2TMEM(pix,siz)
	 pix:	Number of pixels
	 siz:	Specified by size of one texel G_IM_SIZ_*
	----------------------------------------------

In addition, the horizontal width (wrap width) when loading a 
texture is set in imageStride.  This is because there may be a 
difference between the width of the texture when it was loaded 
and the value for imageW for the sprite which is actually 
rendered.  GS_PIX2TMEM() can be used here as well since this is 
also specified in TMEM address units.  

When these imageAdrs and imageStride specifications are employed, 
several small textures (sub-textures) are laded inside TMEM and 
textures can be selected from among these by setting the 
following values in imageAdrs.   

  imageW      = (Sub-texture width);
  imageH      = (Sub-texture height);
  imageAdrs   = GS_PIX2TMEM((S coordinate inside TMEM) + 
			    (T coordinate inside TMEM)*(Texture width 
				when loaded), G_IM_SIZ_*);
  imageStride = GS_PIX2TMEM(Texture width when loaded); 

Concretely, a large texture is prepared first which combines 4 
textures as follows. 

     <---------- 64 --------->
   ^ +-----------+-----+-----+
   | |           |     |     |
   | |           |  B  |  C  | 16
  32 |     A     +-----+-----+
   | |           |           | 
   | |           |     D     | 16
   v +-----------+-----------+ 
     <---- 32 --->  16    16

This texture is loaded as a 64x32 texture, and the various 
textures can be used when actually rendering a sprite by 
respectively specifying it as shown below. 

    Sub-texture A:		imageW = 32;
		imageH = 32;
		imageAdrs   = GS_PIX2TMEM(0*64+0,  G_IM_SIZ_16b);
		imageStride = GS_PIX2TMEM(64, G_IM_SIZ_16b);

    Sub-texture B:		imageW = 16;
		imageH = 16;
		imageAdrs   = GS_PIX2TMEM(0*64+32,  G_IM_SIZ_16b);
		imageStride = GS_PIX2TMEM(64, G_IM_SIZ_16b);

    Sub-texture C: 		imageW = 16;
		imageH = 16;
		imageAdrs   = GS_PIX2TMEM(0*64+48,  G_IM_SIZ_16b);
		imageStride = GS_PIX2TMEM(64, G_IM_SIZ_16b);

    Sub-texture D:		imageW = 32;
		imageH = 16;
		imageAdrs   = GS_PIX2TMEM(16*64+32,  G_IM_SIZ_16b);
		imageStride = GS_PIX2TMEM(64, G_IM_SIZ_16b);


However, there is a restriction in this specification method.  
That is that the shapes in which the texture data are stored in 
TMEM differ between their even numbered lines and their odd 
numbered lines.  Because of this, a TMEM address which 
corresponds to an odd numbered line cannot be specified in 
imageAdrs when loading a texture.  In other words, please 
understand that an odd numbered value cannot be set in (T 
coordinate inside TMEM) in the imageAdrs calculation formula 
described above. 

The texture format and size in g[s]SPObjRectangle are substituted 
into imageFmt and imageSize using the macros G_IM_FMT_* and 
G_IM_SIZ_*, respectively.  In addition, when using CI4 textures, 
the TLUT number is specified in imagePal. 

Flipping of the texture pattern in the S direction and the T 
direction is supported by g[s]SPObjRectangle.  The rendering 
direction is changed by setting the following values in 
imageFlags. 

  ----------------------------------------------------------------
   imageFlags Value			Rendering Direction
   0					No rotation
   G_OBJ_FLAG_FLIPS			Flip in S direction (X)
   G_OBJ_FLAG_FLIPT			Flip in T direction (Y)
   G_OBJ_FLAG_FLIPS|G_OBJ_FLAG_FLIPT	Flip in S direction (X) 
						and T direction (Y)
  ----------------------------------------------------------------

g[s]SPObjRectangle can be used as CycleType in both 1 Cycle, 2 
Cycle modes and the Copy mode.  The rendering speed is faster in 
Copy mode than in the other modes, but on the other hand, there 
are restrictions on the rendering functions in Copy mode. 

Bilinear interpolation, sub-pixel processing, and scaling in the 
X direction are not supported in the Copy mode.  Proper function 
cannot be guaranteed when these functions are used in the Copy 
mode.  In the worst case, the RDP may break down.  It is 
recommended that you use the modes according to the functions 
that are required. 

The rendering results of g[s]SPObjRectangle will change by 
setting binary interpolation and other rendering modes.  This is 
explained in detail in section 4.3 "Setting the Object Rendering 
Mode." 

The 2D matrix settings are not referred to by g[s]SPObjRectangle.  
Because of this, the 2D matrix settings will not affect the 
rendering results of this GBI. 


------------------------
4.2.4  gSPObjRectangleR

	------------------------------------------------------------
	 gSPObjRectangleR(Gfx *gdl, uObjsprite *sp)
	 gsSPObjRectangleR(uObjsprite *sp)

	 Gfx		*gdl;	Display list pointer 
	 uObjsprite	*sp;	Pointer to rendering data structure for 
				sprite 
	------------------------------------------------------------

g[s]SPObjRectangleR is one of the sprite rendering GBI provided 
by S2DEX and, like g[s]SPObjRectangle described above, is used to 
render sprites that do not rotate.  g[s]SPObjRectangleR differs 
from g[s]SPObjRectangle in that it refers to the 2D matrix 
settings and changes the coordinate values of the screen being 
rendered. 

The values {X, Y, BaseScaleX, BaseScaleY} in the 2D matrix are 
referenced by g[s]SPObjRectangleR, and the vertex coordinates of 
the sprite are determined by the following calculation formulas. 

     Upper-left coordinate values	( X + objX / BaseScaleX, 
			Y+objY/BaseScaleY )
     Lower-right coordinate values 	( X + (objX + imageW / scaleW) 
			/ BaseScaleX - 1, Y + (objY + imageH / scaleH) 
			/ BaseScaleY - 1 )

The g[s]SPObjSubMatrix GBI is used to change 
{ X,Y,BaseScaleX,BaseScaleY}.  When X=Y=0 and 
BaseScaleX=BaseScaleY=1.0, the results are the same as with 
g[s]SPObjRectangle. 

By changing these 2D matrix {X, Y, BaseScaleX, BaseScaleY} 
settings, multiple sprites can be moved and/or scaled as a group. 

For example, consider a case in which sprites A, B, and C are 
lined up horizontally, as shown below. 

       32      32      32
    +-------+-------+-------+
    |       |       |       |
 32 |   A   |   B   |   C   |
    |       |       |       |
    +-------+-------+-------+

In order to realize this, data like those below are set in 
(objX, objY). 

    A: (objX, objY) = ( 0<<2, 0<<2)
    B: (objX, objY) = (32<<2, 0<<2)
    C: (objX, objY) = (64<<2, 0<<2)

When X and Y are changed with these settings as the base, these 
3 sprites are moved at once as though they were one large sprite. 
  
However, there are cases in which spaces actually may develop 
between A and B and between B and C due to calculation errors 
resulting from multiplication, etc.  In this case, it would be 
necessary to counter this by slightly overlapping the sprites 
with their adjacent sprite, as shown below. 
 
    B: (objX, objY) = ((32<<2)-2, 0<<2)
    C: (objX, objY) = ((64<<2)-4, 0<<2)

The differences between g[s]SPObjRectangleR and 
g[s]SPObjRectangle are described above.  Please refer to the 
explanation of g[s]SPObjRectangle for a description of the other 
functions. 


--------------------
4.2.5  gSPObjsprite

	-----------------------------------------------------------
	 gSPObjsprite(Gfx *gdl, uObjsprite *sp)
	 gsSPObjsprite(uObjsprite *sp)

	 Gfx		*gdl;	Display list pointer
	 uObjsprite	*sp;	Pointer to rendering data structure for 
				sprite
	-----------------------------------------------------------

g[s]SPObjsprite is one of the sprite rendering GBI provided by 
S2DEX.  This GBI is used to render sprites which rotate.  The 
elements (A,B,C,D,X,Y} of the 2D matrix are used by g[s]SPObjsprite 
to rotate the sprite.  g[s]SPObjMatrix is used to set up this 2D 
matrix.  (See section 4.3.1)

A point (x,y) in a sprite is moved to the following position 
(x',y'), when the sprite is not rotating, by multiplying the 
2D matrix. 

	x' = A * x + B * y + X
	y' = C * x + D * y + Y

The various vertexes of the sprite are also moved in this way, 
and the sprite is rendered in a 4-sided area according to the 
moved vertexes. 

T rotation of the sprite is performed by setting the next 
rotation matrix in the 2D matrix A,B,C,D. 

		|A  B|   |  cosT  sinT |
		|    | = |             |
		|C  D|   | -sinT  cosT |

In this case, the sprite is rotated with the screen coordinates 
(X,Y) as the origin.  Furthermore, when scaling is added, 
multiply the various items {A,B,C,D} by a scale value. 

Which location in the sprite will correspond with the rotational 
center (X,Y) is determined by the values for (objX,objY).  When 
objX=objY=0, the center of rotation for the sprite is the upper-
left vertex when the sprite is not rotated.  At this point, when 
you wish to rotate the sprite centered at this point, set objX 
and objY as follows.  

		objX = - (imageW / scaleW) / 2;
		objY = - (imageH / scaleH) / 2;

In addition, by adjusting the values for objX and objY, as with 
g[s]SPObjRectangleR, several sprites can be rotated at once as a 
group.  In addition, the occurrence of gaps due to computational 
errors can also be minimized by rendering the sprites slightly 
overlapping, as with g[s]SPObjRectangleR.  

The position of the sprite when not rotating (A=D=1.0, B=C=0.0), 
matches the rendering area by g[s]SPObjRectangleR when 
BaseScaleX=BaseScaleY=1.0.  For sprites which rotate and do not 
rotate, it is recommended that you render them by switching back 
and forth so that they are rendered by g[s]SPObjRectangle when 
they are not rotating and are rendered by g[s]SPObjsprite when 
they are rotating.  This is because g[s]SPObjsprite renders a 
sprite by combining two polygons, which increases the processing 
burden on both the RSP and the RDP far more than with 
g[s]SPObjRectangleR. 

In addition, when enlarging a sprite when it is not rotating, 
there are cases in which the rendering result will differ 
slightly from the rendering result by g[s]SPObjRectangle.  Please 
understand that there are some sprites (those in which the 
rectangular rendering will differ when polygons are pasted 
together) with which this is unavoidable due to the differences 
in their rendering methods. 

The settings for the texture which is pasted onto a sprite are 
the same as those for g[s]SPObjRectangle.  Refer to the 
corresponding section above for details. 


-----------------------
4.3  2D Matrix Operations

S2DEX microcode is constructed as described above so that the 2D 
matrix is used as rendering parameters.  Several GBI are 
available to modify this 2D matrix. 


--------------------
4.3.1  gSPObjMatrix

	--------------------------------------------------------
	 gSPObjMatrix(Gfx *gdl, uObjMtx *mtx)
	 gsSPObjMatrix(uObjMtx *mtx)

	 Gfx		*gdl;	Display list pointer
	 uObjMtx	*mtx;	Pointer to 2D matrix structure 
	--------------------------------------------------------

This GBI loads the 2D matrix parameters inside the uObjMtx 
structure to the 2D matrix area inside the RSP.  Normally, this 
GBI is used to set up a rotating sprite. 

Since the 6 matrix elements {A,B,C,D,X,Y} are the only matrix 
elements required for rotation processing, one may think that it 
is not necessary to transfer the entire matrix, but since 
transfers from main memory to the RSP matrix area must be done in 
8 byte units, {BaseScaleX,BaseScaleY} are transferred together 
with the rest as 24 bytes. 

Consequently, the values for BaseScaleX and BaseScaleY will 
certainly be overwritten.  If these parameters will not be used 
(when g[s]SPObjRectangleR will not be used immediately 
subsequently), it is recommended that the default value of 1024 
(1.0 when expressed in s5.10 format) be substituted in the 
meantime as the values for BaseScaleX and BaseScaleY. 


-----------------------
4.3.2  gSPObjSubMatrix

	--------------------------------------------------------
	 gSPObjSubMatrix(Gfx *gdl, uObjMtx *mtx)
	 gsSPObjSubMatrix(uObjMtx *mtx)

	 Gfx		*gdl;	Pointer to display list
	 uObjSubMtx	*mtx;	Pointer to 2D matrix structure
	--------------------------------------------------------

g[s]SPObjSubMatrix loads the data in the uObjSubMtx structure to 
the 2D matrix area in the RSP.  However, the uObjSubMtx structure 
is a subset of the uObjMtx structure, and holds values for the 2D 
matrix elements {X, Y, BaseScaleX, BaseScaleY} used by 
g[s]SPObjRectangleR. 

This GBI changes only the 2D matrix parameters {X, Y, BaseScaleX, 
BaseScaleY} which correspond with the member variables of the 
uObjSubMtx structure, and has no effect on the values for the 
other parameters {A, B, C, D}. 

This GBI is primarily used in association with 
g[s]SPObjRectangleR. 


-------------------------------
4.4  Setting the Object Rendering Mode 

There are a variety of rendering parameters in the RDP, which 
handles the rendering of sprites and BGs.  Polygon rendering 
and rectangle rendering processing is minutely influenced by the 
mode of this RDP.  For example, the texture coordinates shift 0.5 
between when bilinear interpolation is enabled and when it is 
disabled.  With S2DEX, these effects are corrected by the RSP, 
and efforts have been made so that it is hardly necessary for the 
user to be aware of these influences.  The correction processing 
of the RSP corresponds with the mode of the RDP.  The mode of 
this correction processing in the RSP is called the Object 
Rendering Mode (or OBJ Rendering Mode). 

Since having the RSP automatically select this mode increases 
the overhead on the RSP, it current only discerns between Copy 
mode and 1,2 Cycle modes.  The RSP must be informed of other 
modes in the form of GBI.  The Object rendering modes which are 
currently installed, in addition to their function of correcting 
the effects of the RDP mode, also add independent rendering 
functions.  This is discussed in detail in the following 
sections. 


------------------------
4.4.1  gSPObjRenderMode

	--------------------------------------------------------
	 gSPObjRenderMode(Gfx *gdl, u32 mode)
	 gsSPObjRenderMode(u32 mode)

	 Gfx		*gdl;	Display list pointer
	 u32		mode;	Object rendering mode 
	--------------------------------------------------------


g[s]SPObjRenderMode is for changing the object rendering mode in 
the RSP.  This is normally set according to the display mode. 

The flags which can be set are as shown below.  When specifying 
multiple flags, please link them with a logical sum (OR).  
However, G_OBJRM_SHRINKSIZE_1 and G_OBJRM_SHRINKSIZE_2 cannot 
be specified at the same time. 

	-----------------------------------------------------------
	 Macro Name 			Description of Function 
	 G_OBJRM_NOTXCLAMP	Processing to clamp the texture 
					perimeter is disabled
	 G_OBJRM_BILERP		Turned ON during bilinear 
					interpolation
	 G_OBJRM_SHRINKSIZE_1	Shrinks the rendered image by 0.5 
					texel at the perimeter
	 G_OBJRM_SHRINKSIZE_2	Shrinks the rendered image by 1.0 
					texel at the perimeter
	 G_OBJRM_WIDEN		Expands the rendered image by 3/8 
					texel
	-----------------------------------------------------------

Each flag will be explained in detail below. 


o G_OBJRM_NOTXCLAMP:

When a texture is pasted to a sprite, the following 
relationships are true between the size of the texture imageW, 
imageH, the scale value scaleW, scaleH and the size of the sprite 
objW, objH. 

	objW = imageW / scaleW;
	objH = imageH / scaleH;

When the texture is pasted to the sprite, the area (0,0) - 
(imageW-1,imageH-1), in texture coordinates,  is rendered on the 
sprite.  However, due to calculation error, etc., texture outside 
that range is sometimes displayed, even slight, outside the 
perimeter of the sprite. 

In order to avoid this, the RSP will clamp the outside of the 
rendering target range for the texture.  Thus, it is possible to 
avoid the aforementioned problem.  Refer to Chapter 13 Texture 
Mapping in the N64 Manual for details about this. 

The flag G_OBJRM_NOTXCLAMP indicates to the RSP to not perform 
this clamp processing.  Normally, it is not necessary to turn 
this flag ON. 


o G_OBJRM_BILERP

Set this flag when you wish to perform bilinear interpolation on 
a texture.  This flag corrects the 0.5 shift in the texture which 
occurs during bilinear interpolation as mentioned in the example 
in the preceding section. 

In addition, when this flag is in effect, the RSP will use the 
bilinear interpolation function to support movement of the 
internal image in sub-pixel units.  This enables motion in 1/4 
pixel units. 


o G_OBJRM_SHRINKSIZE_1

When you wish to align several bilinear interpolated sprites and 
handle them as a large bilinear interpolated sprite, the 
connectedness between the images at their boundaries becomes 
problematic.  In order to maintain this connectedness, it is 
necessary to overlap the textures of the various sprites by one 
line.  When this is done, the outer 0.5 texel (shown by the # in 
the figure below) becomes unnecessary.   This is because this 
portion gets taken up by the adjacent sprite. 

       0  0.5  1       2       3  S
     0 +-------+-------+-------+--
       |#######|#######|#######|##
   0.5 |###+---+-------+-------+--
       |###|   |       |       |
     1 +---+---+-------+-------+--
       |###|   |       |       |
       |###|   |       |       |
       |###|   |       |       |
     2 +---+---+-------+-------+--
   T   |###|   |       |       |


When the G_OBJRM_SHRINKSIZE_1 flag is ON, the RSP shrinks the 
rendered image of the sprite and renders it using a texture image 
from which the aforementioned outer 0.5 texel is shaved off.  The 
texture images are each 0.5 texels smaller, but since the upper-
left screen coordinate does not change, the rendering effect is 
as shown below. 

                           1/scaleX
       (objX,objY)           -> <-
           +-----------------+-+
           |                 | |
           |              <--+-+--- G_OBJRM_SHRINKSIZE_1 enabled
           |                 | |
           |                 | |<- G_OBJRM_SHRINKSIZE_1 disabled
           |                 | |  
           |                 | |  
         | |                 | |  
         v +-----------------+ |  
1/scaleY   +-------------------+
           ^
           |

o G_OBJRM_SHRINKSIZE_2

This is very similar to G_OBJRM_SHRINKSIZE_1, except for one 
difference, which is that the amount of image reduction is 
doubled.  (1 texel is removed for the outside of each texture.)
  
In cases where subpixel processing is being performed, use this 
flag when you wish to overlap the texels of adjacent sprites by 
two lines, as when seeking even greater connectedness, etc.

o G_OBJRM_WIDEN

This enlarges the rendered image by 3.8 pixel in the positive S 
and T directions. Use this flag to prevent blank gaps at the 
seams between sprites when sprites are combined to display a 
rotating Object, or the like, which is larger than TMEM. 

Since rendering calculation processing for sprites has been made 
even more rigorous with S2DEX Release 1.04 and later, the 
importance of this flag is decreased, but it can still be used. 


#####  NOTE  ##### The following flags are not currently 
supported. 

o G_OBJRM_ANTIALIAS ---- Support was stopped for S2DEX 1.04 and 
  later

This flag corresponds to turning ON/OFF AntiAlias processing in 
the RDP rendering modes.  Turn it ON when using AntiAlias 
(G_RM_AA_*) and ReducedAlias (G_RM_RA_*) as the RDP rendering 
mode. 

When this flag is ON, subpixel calculation is enabled at the 
outer edge.  The outer edge is the outer-most perimeter of the 
sprite rendering area.  This flag has no significance for sprites 
whose entire outer edge is translucent.   

In S2DEX 1.04 and later, this flag can be ignored since this 
processing is left to the video hardware. 


o G_OBJRM_XLU

Set this flag when rendering semitranslucent sprites.  Specify 
G_RM_XLU_SPRITE as the RDP RenderMode in semitranslucent 
rendering. 

This flag was supported by S2DEX 1.02 and later.  It would make 
the seams less apparent when rendering semitranslucent sprites in 
a line.  

In S2DEX 1.04 and later, these seams were eliminated by 
performing rigorous sprite rendering calculations.  
Consequently, this flag can be ignored.  


-------------------------------------------
4.4.2  About RenderMode during sprite Rendering 

The RDP RenderMode which should be set when rendering a sprite 
is defined in the header file gs2dex.h.  Please use this when 
rendering a sprite. 

When AntiAlias off 
	Opaque sprite		G_RM_SPRITE*
	Semitranslucent sprite	G_RM_XLU_SPRITE*

When AntiAlias on  
	Opaque sprite		G_RM_AA_SPRITE* (G_RM_RA_SPRITE*)
	Semitranslucent sprite	G_RM_AA_XLU_SPRITE*

However, when AntiAlias is ON, if two sprites are overlaid by 
using semitranslucent sprites, the edges of the bottom sprite 
may affect the edges of the top sprite.  Since this cannot be 
avoided, please keep this in mind when using G_RM_XLU_SPRITE. 


--------------------------
4.5  Texture Loading GBI

Among the sprite functions in S2DEX, sprite rendering processing 
is as described in the sprite GBI sections.  This is one more 
piece of that, and describes the loading processing for TMEM. 


-----------------------
4.5.1  uObjTxtr Structure 

In the texture loading GBI, 3 different formats of texture data 
are processed by common GBI.  These 3 formats are distinguished 
by the member variable type in the uObjTxtr structure.  Those 3 
formats are shown below. 

    1) Loading textures using LoadBlock
    2) Loading textures using LoadTile  
    3) Loading of TLUT 

1) Loading texture using LoadBlock is able to do processing 
faster than 2) loading with LoadTile, but the width of the 
texture which can be loaded is limited.  Since that limitation is 
as described in regards to LoadBlock in Section 4.1.2, please 
refer to this section for details.  

The various structures which correspond to these various formats 
are respectively defined.  However, these various structures have 
the same structure, except that the names of the member variables 
differ.  Thus, the uObjTxtr structure collects these 3 structures 
are into a common body. 


1) Structure for loading texture using LoadBlock  uObjTxtrBlock_t
-----------------------------------------------------------------
typedef	struct	{
  u32	type;		// Type 		Type G_OBJLT_TXTRBLOCK
  u64	*image;	// Texture source address in DRAM
  u16	tmem;		// TMEM word address of load destination 
				(8 byte word) 
  u16	tsize;	// Texture size 	Specified by the macro 
				GS_TB_TSIZE()
  u16	tline;	// Texture 1 line width. Specified by the macro 
				GS_TB_TLINE()
  u16	sid;		// Status ID  	Select from { 0, 4, 8, 12 }
  u32	flag;		// Status flag
  u32	mask;		// Status mask
} uObjTxtrBlock_t;	// 24 bytes
-----------------------------------------------------------------

2) Structure for loading texture using LoadTile	
   uObjTxtrTile_t
-----------------------------------------------------------------
typedef	struct	{
  u32	type;		// Type 		Type G_OBJLT_TXTRTILE
  u64	*image;	// Texture source address in DRAM
  u16	tmem;		// TMEM words address of load destination 
				(8 byte word) 
  u16	twidth;	// Texture width. Specified by the macro 
				GS_TT_TWIDTH()
  u16	theight;	// Texture height. Specified by the macro 
				GS_TT_THEIGHT()
  u16	sid;		// Status ID. Select from { 0, 4, 8, 12 }
  u32	flag;		// Status flag
  u32	mask;		// Status mask
} uObjTxtrTile_t;	// 24 bytes
-----------------------------------------------------------------

3) Structure for laoding TLUT	uObjTxtrTLUT_t
-----------------------------------------------------------------
typedef	struct	{
  u32	type;		// Type 		Type G_OBJLT_TLUT
  u64	*image;	// Texture source address in DRAM
  u16	phead;	// Number in TLUT area over 256 and under 511 
				of load destination
  u16	pnum;		// Number of TLUT to be loaded - 1
  u16   zero;	// 0 is always substituted
  u16	sid;		// Status ID. Select from { 0, 4, 8, 12 }
  u32	flag;		// Status flag
  u32	mask;		// Status mask
} uObjTxtrTLUT_t;	// 24 bytes
-----------------------------------------------------------------

uObjTxtr Common Body
-----------------------------------------------------------------
typedef union {
  uObjTxtrBlock_t      block;	// Parameter for loading texture 
						with LoadBlock 
  uObjTxtrTile_t       tile;	// Parameter for loading texture 
						with LoadTile
  uObjTxtrTLUT_t       tlut;	// TLUT loading parameter
  long long int        force_structure_alignment;
} uObjTxtr;
-----------------------------------------------------------------


----------------------
4.5.2  gSPObjLoadTxtr

	-----------------------------------------------------------
	 gSPObjLoadTxtr(Gfx *gdl, uObjTxtr *tx)
	 gsSPObjLoadTxtr(uObjTxtr *tx)

	 Gfx		*gdl;	Display list pointer
	 uObjTxtr	*tx;	Pointer to texture load data structure
	-----------------------------------------------------------

gSPObjLoadTxtr performs various loading processing, referring to 
the texture load parameters stored in the 3 different structures 
described above.  The 3 structures have common member variables 
type, image, sid, flag, and mask.  First these5 common member 
variables will be described. 

o type 

gSPObjLoadTxtr discriminates between the various structures by 
the value of the structure member variable type. The structures 
and processing which correspond to the various values for type 
are as shown below. 

-----------------------------------------------------------------
Value for type	Structure		Processing
G_OBJLT_TXTRBLOCK	uObjTxtrBlock_t	Load texture using LoadBlock
G_OBJLT_TXTRTILE	uObjTxtrTile_t	Load texture using LoadTile
G_OBJLT_TLUT	uObjTLUT_t		Load TLUT
-----------------------------------------------------------------

o image

The address of the texture data or TLUT data situated in the main 
memory is specified by the member variable image.  These texture 
data must be aligned in 8 byte units. 

o sid, flag, mask

These 3 member variables are available to make the judgment that 
it is unnecessary to reload a texture which has already been 
loaded.  If it is determined that the texture that you are trying 
to load next has already been loaded, g[s]SPObjLoadTxtr will 
terminate without performing said load. 

Since the determination of whether or not a certain texture 
exists in TMEM is performed entirely by the RSP, each time the 
RSP loads a texture, it must perform an analysis of the load 
destination area.  It would be an incorrect decision to take up 
time with this judgment processing. 

Consequently, in S2DEX, rather than having the RSP perform an 
analysis of the texture to be loaded, the data pertaining to the 
area to be loaded are added in advance to the texture data 
structure, whereby the load judgment can be accomplished with a 
simple computation. 

For example, when loading data to TMEM, a simple load judgment 
can be done by writing an ID which corresponds to the texture 
which is to be loaded to the Status area in the RSP, and then 
doing a comparison of this ID the next time that data are loaded 
to TMEM.  

The load judgment processing which is built into S2DEX expands on 
this concept.  By setting two 32 bit-wide values, flag and mask, 
the load judgment processing can also be applied to situations in 
which the TMEM area is divided and a partial load is performed. 

As in the RSP, four 32 bit Status variables are available as 
Status areas.  When the microcode is started, these values are 0.  
Which Status value to use is determined by sid.  The values 
handled by sid are {0, 4, 8, 12}. 
 
g[s]ObjLoadTxtr actually performs the load judgment by means of 
the following processing, and determines whether or not to load 
a texture. 

  + Check whether (Status[sid] & mask) == flag 
  + If the result is TRUE, it is judged that the texture is 
    already loaded, and load processing is terminated. 
  + If the result is FALSE, the texture is loaded. 
	Status[sid] is updated as follows: 
		Status[sid] = (Status[sid] & ~mask) | (flag & mask);

The simplest method of using flag is to substitute -1(=0xffffffff) 
to mask and the address of the texture source data (=the value for 
the member variable image) to flag.  If there are no other texture 
data starting from the same address, this can be operated as a 
simple texture cache. 

In addition, when (flag&~mask)!=0, since the judgment equation is 
definitely false, the texture will always be loaded. 

The following is an example in which the TMEM is divided in two 
and managed.  Here, bits 31-16 of Status[0] are assigned to the 
front half of the TMEM area, while bits 15-0 are assigned to the 
back half, and serial numbers are assigned to each texture. 

			Area Being Loaded		flag		mask
A: Texture 1	0 to 255			0x00010000	0xffff0000   
B: Texture 2	256 to 511 			0x00000002	0x0000ffff
C: Texture 3	0 to 511			0x00030003	0xffffffff
D: Back 1/2 of	256 to 511			0x00000003	0x0000ffff
   Texture 3 only	

Even though the front half of TMEM from load A is changed after 
the entire texture 3 was loaded in C, since the data for texture 
3 are stored in the back half of TMEM, even though a load of only 
the back half of texture 3 is performed in D, the load is not 
actually performed. 

S2DEX has GBI - gSPSelectDL and gSPSelectBranchDL - which perform 
DL branching by applying this Status-based processing to make 
similar judgments. 


The member variables of the other structures in each various 
processing will be explained next. 

1) Load texture by LoadBlock (uObjTxtrBlock_t structure) 

o tmem

The TMEM address of the load destination is specified in the 
member variable tmem in Double Word units.  It is typical to use 
the value of this load destination as the value of imageAdrs in 
the uObjsprite structure.  When this value is specified as a 
pixel unit, it plays the role of the macro GS_PIX2TMEM() 
described above. 

o tsize

Data on the size of the texture to be loaded are given in the 
member variable tsize.  The macro GS_TB_TSIZE() is used when 
finding this value from the texture size. 

	---------------------------------------------------------
	 GS_TB_TSIZE(pix,siz): tsize setting 
	 pix:	Number of texels to be loaded (=texture horizontal 
		width x vertical width) 
	 siz:	Size of one texel		Specified by G_IM_SIZ_*
	---------------------------------------------------------

o tline

Data on the horizontal width of the texture to be loaded are 
given in the member variable tline.  The macro GS_TB_TLINE() 
is used when finding this value from the width of the texture. 

	-----------------------------------------------------
	GS_TB_TLINE(pix,siz): tline setting 
	pix:	Number of texels in horizontal width of texture
	siz:	Size of one texel		Specified by G_IM_SIZ_*
	-----------------------------------------------------


2) Load texture by LoadTile (uObjTxtrTile_t structure) 

o tmem

This member is the same as when performing load processing with 
LoadBlock.  The TMEM address of the load destination is specified 
in the member variable tmem in Double Word units. 

o twidth

Data pertaining to the width of the texture to be loaded is given 
in the member variable twidth.  The macro GS_TT_TWIDTH() is used 
when finding this value from the width of the texture. 

	---------------------------------------------------------
	GS_TT_TWIDTH(pix,siz): twidth setting 
	pix:	Texture width 
	siz:	Size of one texel		Specified by G_IM_SIZ_*
	---------------------------------------------------------

o theight

Data on the height of the texture to be loaded are given in the 
member variable theight.  The macro GS_TT_THEIGHT() is used when 
finding this value from the height of the texture. 

	-----------------------------------------------------
	GS_TT_THEIGHT(pix,siz): theight setting 
	pix:	Texture height
	siz:	Size of one texel		Specified by G_IM_SIZ_*
	-----------------------------------------------------


3) Load TLUT (uObjTLUT_t structure) 

o phead

The head number of the TLUT area to be loaded is set in the 
member variable phead.  Since the number of the TLUT area is a 
value of the TLUT ID plus 256, the value set should be from 256 
to 511.  The macro GS_PAL_HEAD() is available to make this 
setting. 

	-----------------------------------------------------------
	GS_PAL_HEAD(head): phead setting (Simply add 256 to head) 
	head:	ID of head of  TLUT to be loaded
	-----------------------------------------------------------

o pnum

(TLUT color number being loaded -1) is set in the member variable 
pnum.  The macro GS_PAL_NUM() is avialable to make this setting. 

	----------------------------------------------------------
	GS_PAL_NUM(num): pnum setting (Simply subtract 1 from num)
	num:	Number TLUT to be loaded
	----------------------------------------------------------

o zero

This member is not used by uObjTLUT_t.  However, always 
substitute 0 here for the sake of compatibility with the other 
structures. 


Following are setting examples for the 3 structures. 

  (1) Load RGBA16 Texture with LoadBlock

	uObjTxtr objTxtrBlock_RGBA16 = {
	  G_OBJLT_TXTRBLOCK,                    /* type    */
	  (u64 *)textureRGBA16,                 /* image   */
	  GS_PIX2TMEM(0,     G_IM_SIZ_16b),     /* tmem    */
	  GS_TB_TSIZE(32*32, G_IM_SIZ_16b),     /* tsize   */
	  GS_TB_TLINE(32,    G_IM_SIZ_16b),     /* tline   */
	  0,                                    /* sid     */
	  (u32)textureRGBA16,                   /* flag    */
	  -1                                    /* mask    */
	};

  (2) Load CI4 Texture with LoadTile

	uObjTxtr objTxtrTile_CI4 = {
	  G_OBJLT_TXTRTILE,                     /* type    */
	  (u64 *)textureCI4,                    /* image   */
	  GS_PIX2TMEM  (0,  G_IM_SIZ_4b),	/* tmem    */
	  GS_TT_TWIDTH (32, G_IM_SIZ_4b),	/* twidth  */
	  GS_TT_THEIGHT(32, G_IM_SIZ_4b),	/* theight */
	  0,                                    /* sid     */
	  (u32)textureCI4,                      /* flag    */
	  -1                                    /* mask    */
	};

  (3) Load TLUT

	uObjTxtr objTLUT_CI4 = {
	  G_OBJLT_TLUT,                         /* type    */
	  (u64 *)textureCI4pal,                 /* image   */
	  GS_PAL_HEAD(0),                       /* phead   */
	  GS_PAL_NUM(16),                       /* pnum    */
	  0,                                    /* zero    */
	  0,                                    /* sid     */
	  (u32)textureCI4pal,                   /* flag    */
	  -1                                    /* mask    */
	};


------------------
4.6  Complex Processing GBI

In the creation of an actual game, there are situations in which 
it is advantageous in screens, such as the sprite management, 
etc., to collect the texture loading GBI and sprite rendering GBI 
into one.  S2DEX has a structure which makes it possible to 
process these two GBI as one GBI.  The GBI for this kind of 
complex processing is explained below. 


---------------------------
4.6.1  uObjTxsprite Structure 

The uObjTxsprite structure links a uObjTxtr structure and a 
uObjsprite structure and follows the following format.  Pointers 
to this structure are given as arguments in the complex 
processing GBI. 

		----------------------------------------
		 typedef struct  {
		   uObjTxtr      txtr;
		   uObjsprite    sprite;
		 } uObjTxsprite;         /* 48 bytes */
		----------------------------------------


------------------------
4.6.2  gSPObjLoadTxRect

	-----------------------------------------------------------
	gSPObjLoadTxRect(Gfx *gdl, uObjTxsprite *txsp)
	gsSPObjLoadTxRect(uObjTxsprite *txsp)

	Gfx			*gdl;		Display list pointer
	uObjTxsprite	*txsp;	Pointer to texture loading 
						and sprite rendering data 
						structures
	-----------------------------------------------------------

The g[s]SPObjLoadTxRect GBI performs texture loading processing 
and then performs rendering of a non-rotating sprite. 

This command sequentially processes two GBI g[s]SPObjLoadTxtr 
and g[s]SPObjRectangle as one GBI.  The processing results of (A) 
and (B) below are the same. 

	(A) gsSPObjLoadTxRect(txsp);

	(B) gsSPObjLoadTxtr(&(txsp->txtr));
	    gsSPObjRectangle(&(txsp->sprite));


------------------------
4.6.3  gSPObjLoadTxRectR

	-----------------------------------------------------------
	gSPObjLoadTxRectR(Gfx *gdl, uObjTxsprite *txsp)
	gsSPObjLoadTxRectR(uObjTxsprite *txsp)

	Gfx			*gdl;		Display list pointer
	uObjTxsprite	*txsp;	Pointer to texture loading 
						and sprite rendering data 
						structures
	------------------------------------------------------------

The g[s]SPObjLoadTxRectR GBI performs texture loading processing 
and then performs the rendering of a non-rotating sprite, 
referring to the 2D matrix. 

This command sequentially processes the two GBI g[s]SPObjLoadTxtr 
and g[s]SPObjRectangleR as one GBI.  The processing results of 
(A) and (B) below are the same. 

	(A) gsSPObjLoadTxRectR(txsp);

	(B) gsSPObjLoadTxtr(&(txsp->txtr));
	    gsSPObjRectangleR(&(txsp->sprite));


------------------------
4.6.4  gSPObjLoadTxsprite

	-----------------------------------------------------------
	gSPObjLoadTxsprite(Gfx *gdl, uObjTxsprite *txsp)
	gsSPObjLoadTxsprite(uObjTxsprite *txsp)

	Gfx			*gdl;		Display list pointer
	uObjTxsprite	*txsp;	Pointer to texture loading 
						and sprite rendering data 
						structures
	-----------------------------------------------------------

The g[s]SPObjLoadTxsprite GBI performs texture loading processing 
and then performs rendering of a rotating sprite. 

This command sequentially processes the two GBI g[s]SPObjLoadTxtr 
and g[s]SPObjsprite as one GBI.  The processing results of (A) 
and (B) below are the same. 

	(A) gsSPObjLoadTxsprite(txsp);

	(B) gsSPObjLoadTxtr(&(txsp->txtr));
	    gsSPObjsprite(&(txsp->sprite));


------------------
4.7  Conditional Branching GBI

It has been explained above that texture loading judgment is 
performed in S2DEX using the RSP Status.  GBI which apply this 
Status to DL branching and linking will be explained here. 


--------------------
4.7.1  gSPSetStatus

	-----------------------------------------------------------
	gSPSetStatus(Gfx *gdl, u8 sid, u32 val)
	gsSPSetStatus(u8 sid, u32 val)

	Gfx		*gdl;	Display list pointer
	u8		 sid;	Status ID 	Select from { 0, 4, 8, 12 }
	u32		 val;	Value to be set
	-----------------------------------------------------------

g[s]SPSetStatus substitutes the value for val in the Status area 
specified by sid (Status[sid]).  This Status value is referred to 
during texture loading and during branching decisions. 


-------------------
4.7.2  gSPSelectDL

	-----------------------------------------------------------
	gSPSelectDL(Gfx *gdl, Gfx *ldl, u8 sid, u32 flag, u32 mask)
	gsSPSelectDL(Gfx *ldl, u8 sid, u32 flag, u32 mask)

	Gfx		*gdl;	Display list pointer
	Gfx		*ldl;	Display list to be linked 
	u8		 sid;	Status ID 	Select from { 0, 4, 8, 12 } 
	u32		 flag;	Status flag
	u32		 mask;	Status mask
	-----------------------------------------------------------

g[s]SPSelectDL detects Status[sid] using the judgment formula as 
in texture loading judgment, and calls another display list 
according to the True/False result. 

g[s]SPSelectDL performs branching judgment by the following 
processing and then determines whether or not to call the display 
list. 

  + Check (Status[sid] & mask) == flag 
  + If result is TRUE, terminate GBI without doing anything
  + If result is False, update Status[sid] so that Status[sid] = 
	(Status[sid] & ~mask) | (flag & mask); and call the display 
	list ldl. 


-------------------------
4.7.3  gSPSelectBranchDL

	-----------------------------------------------------------
	gSPSelectBranchDL(Gfx *gdl, Gfx *bdl, u8 sid, u32 flag, 
		u32 mask)
	gsSPSelectBranchDL(Gfx *bdl, u8 sid, u32 flag, u32 mask)

	Gfx		*gdl;	Display list pointer
	Gfx		*link;	Display list to be linked 
	u8		 sid;	Status ID 	Select from { 0, 4, 8, 12 } 
	u32		 flag;	Status flag
	u32		 mask;	Status mask
	-----------------------------------------------------------

g[s]SPSelectBranchDL detects Select[sid] using the judgment 
formula as in texture loading judgment, and calls another display 
list according to the True/False result. 

g[s]SPSelectBranchDL performs branching judgment by the following 
processing and then determines whether or not to call the display 
list. 

  + Check (Status[sid] & mask) == flag 
  + If result is TRUE, terminate GBI without doing anything
  + If result is False, update Status[sid] so that Status[sid] = 
	(Status[sid] & ~mask) | (flag & mask); and branch to the 
	display list bdl. 


------------------------------------------------------------------
5. Emulation Functions

These S2DEX GBI are functions for emulation in the CPU. 

-----------------------
5.1  guS2DEmuBgRect1Cyc

------------------------------------------------------------------
void		guS2DEmuBgRect1Cyc(Gfx **gdl_p, uObjBg *bg);

Description:	Emulate the operation of gSPBgRect1Cyc GBI from 
			the S2DEX microcode in the CPU by combining it 
			with another GBI

Arguments:	gdl_p	Pointer to display list pointer
		* The value for gdl_p is automatically added. 
		bg	Pointer to uObjBg structure
------------------------------------------------------------------

Calling gSPBgRect1Cyc(gdl ++, bg) can be replaced by 
guS2DEmuBgRect1Cyc(&gdl, bg).  See the section on gSPBgRect1Cyc 
for an explanation of the argument bg.  

In addition, in order to announce the setting of a scissoring box 
and the setting of texture filters to this routine, it is 
necessary to call the guS2DEmuSetScissor function described below 
prior to guS2DEmuBgRect1Cyc. 

This function generates GBI which can be processed not only by 
S2DEX, but also by F3DEX.  Because of this, a scaled scrolling 
BG and a 3D model can both be processed by a single microcode, 
even when they are displayed together. 


------------------------
5.2  guS2DEmuSetScissor

------------------------------------------------------------------
void	guS2DEmuSetScissor(u32 ulx, u32 uly,
	                   u32 lrx, u32 lry, u8 bilerp);

Description: 	Sets the scissoring parameters and texture 
			filters referred to during processing of the 
			function guS2DEmuBgRect1Cyc. 
	
Arguments: ulx  X coordinate at upper-left of scissor box (u10.0)
	     uly  Y coordinate at upper-left of scissor box (u10.0)
	     lrx  X coordinate at lower-right of scissor box (u10.0)
	     lry  Y coordinate at lower-right of scissor box (u10.0)
	     bilerp	If Bilerp interpolation processing is being done 
			on an image, any value other than 0 is set, if 
			PointSample is used, 0 is set. 

------------------------------------------------------------------
 
Normally, the scissor box range set by g[s]DPSetScissor is 
conveyed to this function as an argument.  In addition, the 
default values for ulx, uly, lrx, lry, and bilerp are 0, 0, 320, 
240, and 0, respectively, setting to render by PointSample in a 
320x240 pixel frame buffer.  

This function need only be called once prior to calling 
guS2DEmuBgRect1Cyc.  As long as there are no changes to the 
scissor box and the texture filter, this only needs to be called 
once when the game is initializing and there is no need to call 
it every time a frame is rendered. 


------------------------------------------------------------------
6. DEBUG Data Output Functions

Unlike normal microcodes which are assembled at the time of 
shipping, S2DEX provides a microcode for use during debugging.  
The relationship between these two microcodes is the same as the 
relationship between libultra_rom.a and libultra_d.a. 

The debugging microcode S2DEX_D has a slower processing speed 
than the normal microcode, but has the following functions. 

	o  Outputs display list processing log
	o  Stops the RSP and notifies the CPU when an improper 
		input value or undefined command is encountered

Checking the display list processing log makes it particularly 
easy to trace the causes of RSP breakdowns, etc.

An output buffer for the RSP display list processing log must be 
prepared in order use S2DEX_D.  This requires an area which is 
only the same length as the display list.  In addition, it must 
be aligned on 8 bytes. 

Once this area is reserved, set a pointer to the head of the area 
in the data_size member variable of the OSTask structure.  This 
member variable is not used by either the S2DEX or F3DEX series 
to mean the essential DL size.  Merely a vestigial remnant of the 
Ver. 1.0 of the N64 Development Library, it is commonly used as 
the output buffer for the log. 

This address must not be the Segment address.  If 
gspS2DEX.fifo_d.o is subsequently started as the microcode, the 
processing log will be stored in the specified address. 

As for the method of displaying the processing log, please refer 
to the function ucDebugGfxLogPrint() in the included sample 
program uc_assert.c.  In addition, please refer to ucCheckAssert() 
in the same file regarding determining whether the RSP has 
stopped. 

(NOTE) 
S2DEX versions 0.75 and earlier use the yield_data_size member 
variable of the OSTask structure for setting the log buffer, but 
this was changed so that data_size is used in Version 0.76 and 
later.  Please note that the function ucDebugGfxLogPrint() used 
for display was correspondingly corrected. 


------------------------------------------------------------------
7. S2DEX Package Installation 

------------------------------------------------------------------------
This chapter concerns situations in which the S2DEX microcode is 
distributed in a separate package.  If this package is already included 
in the N64 Development Environment, it does not need to be noted here. 
------------------------------------------------------------------

The S2DEX microcode package contains the following files. 

	------------------------------------------------------------
	README			This file
	gspS2DEX.fifo.o		S2DEX microcode
	gspS2DEX.fifo_d.o		S2DEX microcode (for debugging) 
	include/gs2dex.h		S2DEX include file
	libultra/Makefile	libultra 	Update makefile
	libultra/us2dex.o		BG structure initialization routine
	libultra/us2dex_emu.o	Scalable BG rendering routine
	sample/*			S2DEX sample program
	------------------------------------------------------------	

If make is run under the libultra directory, libultra*.a will be 
created.  Copy the libultra*.a which was created to the /usr/lib 
directory. 

In addition, copy gspS2DEX.fifo.o and gspS2DEX.fifo_d.o to the 
/usr/lib/PR directory, and copy include/gs2dex.h to the 
/usr/include/PR directory. 

perl is also required to compile the included sample program.  
Please install the following packages on the IRIX 5.3/6.X CD. 

	eoe2.sw.gifts_perl (for IRIX 5.3)
	eoe.sw.gifts_perl  (for IRIX 6.X)

------------------------------------------------------------------
8. Change History 

03/26/97:
    Release 0.70 (beta 1)
	* Initial version 

03/28/97:
    Release 0.71 (beta 2)
	* Added libultra patch 
	* Revised installation data

04/01/97:
    Release 0.72 (beta 3)
	* Corrected improper S flipping operation in BG rendering 
	* Changed part of sample program

04/10/97:
    Release 0.73 (beta 4)
	* Defined new RenderMode
	* Added new function G_OBJRM_WIDEN to gSPObjRenderMode
	* Modified sample program so that CI8 textures can be 
	  used on semitranslucent sprites and BG

04/21/97:
    Release 0.74 (beta 5)
	* Corrected inadequate checks on buffer status when using 
	  small FIFO buffer
	* Corrected the fact that member variables imageX and 
	  imageY of the uObjBg structure were installed in (u10.2) 
	  format so that they are (u10.5) 
	* Changed frameX and frameY member variables of uObjBg 
	  structure to signed

05/09/97:
    Release 0.75 (beta6)
	* Created guS2DEmuBgRect1Cyc() and guSDEmuSetScissor() 
	  functions which create a DL for scalable BG screens 
	  using the CPU. Distributed as a patch, and section was 
	  added to README regarding this. 
	* No change from 0.74 microcode
	* Added section on perl installation method

05/16/97:
    Release 0.80 (beta7)
	* Changed log output buffer setting method (yield_data_size 
	  -> data_size)
	* Corrected bug in yield processing
	* Added text pertaining to FIFO buffer size to section 2.4 
	  in README file
	* Corrected Sync processing in BG rendering GBI / emulation 
	  functions

06/03/97:
    Release 1.00
	* Installed g[s]SPBgRect1Cyc, a GBI which renders scalable 
	  BG
	* Changed formats of imagePal and imageFlip member 
	  variables in uObjBg_t structure and uObjScaleBg_t 
	  structure from u8 to u16 for alignment
	* Added 3.4  Precautions Regarding GBI to documentation
	* Changed BaseScaleX and BaseScaleY in uObjMtx structure, 
	  and scaleW and scaleH in uObjSprite structure to unsigned

06/13/97:
    Release 1.01
	* Corrected bug in g[s]SPBgRect1Cyc in which unnecessary 
	  texture loading processing was sometimes performed, 
	  vastly increasing RDP processing time

07/03/97:
    Release 1.02
	* Corrected problem in which, when multiple semitranslucent 
	  sprites were joined together, the seam line would be 
	  blended twice, and along with this, added G_OBJRM_XLU as 
	  ObjRenderMode
	* Reduced actual rendered size differences when the same 
	  sprite data were rendered by g[s]SPObjRectangle and 
	  g[s]SPObjSprite 

07/04/97:
    Release 1.03
	* Corrected bug in G_OBJRM_XLU mode
	* Added processing example (render ball) to sample program 
	  of when an object is realized by combining multiple 
	  sprites while Bilerp in effect. 

07/31/97:
    Release 1.04
	* Due to inadequate processing of the line at the seam 
	  during semitransparent display with Release 1.02, to 
	  measures to eradicate the problem.  Concretely, increased 
	  the accuracy of sprite rendering processing.  As a 
	  result, the G_OBJRM_XLU mode and G_OBJRM_ANTIALIAS mode 
	  became unnecessary.  (See 4.4.1)
	* Adjusted definition of RDP RenderMode.  In particular, 
	  isolated the modes during display of semitranslucent 
	  sprites according to when AntiAlias is ON and OFF.  Also 
	  added Section 4.4.2 to explain this. 

08/07/97:
    Release 1.05
	* Corrected problem in which texture which shift when 
	  rendering long, thin sprites by further increasing sprite 
	  rendering precision. 
	* Increase Rectangle calculation accuracy.  This eliminated
	  the gaps that would develop when aligning rectangles 
	  using the RectR commands.  (This was obstructed in the 
	  past by G_OBJRM_WIDEN in the ObjRenderMode.)
	* Added ball using RectR to the sample program.  Also 
	  revised program so that G_OBJRM_WIDEN is not used. 

10/29/97:
    Release 1.06 (N64 Dev Env. 2.0i)
	* Corrected errors in g[s]SPSelectDL and 
	  g[s]SPSelectBranchDL macro definitions. 
	* Corrected improper operation of gSPObjLoadTxRectR after 
	  processing gSPBgRect1Cyc. 
	* Corrected improper operation of gSPObjLoadTxRect. 
	* Reduced size of microcode data area.  This somewhat 
	  increased the RAM area available to the user. 

12/25/97:
    Release 1.06+
	* Corrected errors and difficult to understand points in 
	  this README.txt file. 

04/10/98:
    Release 1.07
	* Corrected abnormal functioning in the rendering processing 
	  of frames with narrow widths by gSPBgRectCopy command. 

------------------------------------------------------------------
