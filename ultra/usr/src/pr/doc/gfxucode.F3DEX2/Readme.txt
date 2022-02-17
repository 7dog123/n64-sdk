------------------------------------------------------------------
	F3DEX2 Micro code (F3DEX Level2) document
	Release 2.08
	Jan 5, 1999.
	Copyright (C) 1999, Nintendo.
	NCL R & D 3    Yoshitaka Yasumoto
------------------------------------------------------------------

Table of contents 

	1. Special features of F3DEX2 Micro code
	2. Details of F3DEX2 usage
	3. Appendix
	4. History of revisions

------------------------------------------------------------------
1. Special features of F3DEX2 micro code

F3DEX2 micro code is the reconstructed F3DEX microcode which has 
been released formerly. so the calculation speed of RSP became 
faster. 


The following are the characteristics.  

	o GBI command set is compatible with F3DEX. (except some 
	  GBI)
	o High speed processing of RSP is possible.  
	o Not only FIFO format but XBUS format are supported 

------------------------------------------------------------------
2. Details of F3DEX2 usage

* Compatibility of GBI

GBI used for F3DEX2 series is compatible with GBI for 
Fast3D/F3DEX series at the source level.  The codes created by 
Fast3D/F3DEX can be used for F3DEX2 by re-compiling.  Please note
that there is no compatibility between them at the binary level.     
 
Specifically, it is necessary to define a macro F3DEX_GBI_2 when 
compiling. 

Add -DF3DEX_GBI_2 to an option of the C compiler (cc/gcc), or add
the define sentence before the include sentence of ultra64.h of 
the source file as follows:      
 
|
|#define	F3DEX_GBI_2
|#include	<ultra64.h>
|

The following GBI is  not supported.  

  g[s]SPInsertMatrix()


* Supporting  F3DEX2, F3DEX2.NoN, F3DEX2.Rej, F3DLX2.Rej, L3DEX2 

F3DLX / F3DLX.NoN (the version without sub-pixel calculation of 
F3DEX) that was supported for F3DEX and F3DLP.Rej (the version 
without texture correction of F3DLX.Rej) are no longer supported.
This is because as a result of optimization of F3DEX micro code,
there is not much merit in omitting the sub-pixel calculation or 
the texture correction processing.  So, those who use these micro
codes need to switch them as shown below. More detailed 
information on the comparison of micro codes is found in the 
Appendix A. 

  if gspF3DLX.fifo.o	 is used ----> use gspF3DEX2.fifo.o      
  if gspF3DLX.NoN.fifo.o is used ----> use gspF3DEX2.NoN.fifo.o  
  if gspF3DLP.Rej.fifo.o is used ----> use gspF3DLX2.Rej.fifo.o 
			   or gspF3DEX2.Rej.fifo.o 

And, F3DEX2.Rej, which is F3DLX2.Rej that does sub-pixel 
calculation is now supported. Unlike F3DEX2, this does not 
perform the Clipping, but performs the Rejection processing, and 
has 64 vertex caches.  The process speed is faster than F3DEX2 
and slower than F3DLX2.Rej.As the quality of screen is about same
as that of F3DEX2, it might be a good idea to use both F3DLX2.Rej
and F3DEX2.Rej properly depending on the situation. 


* Supporting S2DEX2

S2DEX2 is provided instead of S2DEX as a sprite micro code.  Use 
this when self-loading with F3DEX2 series using gSPLoadUcode. 

	use gspS2DEX.fifo.o --> use gspS2DEX2.fifo.o

The performance of S2DEX2 micro code has not been changed at all 
from that of S2DEX. It just can load with F3DEX2 series mutually,
so there should be no problem if S2DEX is used as long as it is 
not mixed with F3DEX2. 

XBUS version is supported for S2DEX2 just like F3DEX2, however, 
be aware that S2DEX_d micro code, a micro code for debugging, 
which was being supported for S2DEX is not supported for S2DEX2.

The usage for S2DEX2 micro code is as follows, which is same as 
F3DEX2.  

	* Define a macro F3DEX_GBI_2 by a compile option, or 
	  define it by "define sentence " before "include 
	  sentence" of ultra64.h.
	* "Include" a header file PR/gs2dex.h after "include 
	  sentence" of ultra64h.

	Examples of when "define sentence" is used

		#define		F3DEX_GBI_2
		#include	<ultra64.h>
		#include	<PR/gs2dex.h>
	
* Improving the speed of RSP calculation 

Compared with F3DEX series, F3DEX2 series can reduce the process 
time by 5 - 70%.  Since switching F3DEX to F3DEX2 has the largest
effect of reduction, there is a possibility that the calculation 
speed of RSP may improve dramtically by this change. The effect 
of reduction by switching F3DLX.Rej to F3DLX2.Rej is not as large
as the case with F3DEX, however,   the reduction is by 5 - 15%. 
It may be worth trying.  
 
* Supporting XBUS micro code 

The graphic micro code finally performs a drawing by creating RDP
command array from GBI command array and transferring it to RDP. 
To transfer RDP command array to RDP, there are three methods, 
XBUS method, FIFO method, and DRAM(DUMP) method.  
  
FIFO method expands RDP command in RDRAM as a FIFO buffer, and 
send it to RDP.  For F3DEX series, only this method is supported.

XBUS method sends RDP command to RDP through the internal buffer 
(XBUS) which connects RSP and RDP directly.  Therefore, unlike 
FIFO, it does not use RDRAM.  Most of the sample programs which 
are attached to the current library use this micro code.      

DRAM(DUMP) method only expands RDP command in RDRAM, and the 
process to start sending to RDP needs to be done by CPU. As the 
amount used for RDRAM is too much, this is not efficient.  

In the past, the first micro code, Fast3D (the original version 
of F3DEX) micro code series had micro codes for each of three 
methods. However, XBUS micro code is no longer supported because 
with XBUS method, F3DEX has used the internal buffer that is used
to send a RDP command, as a vertex cache area in order to 
increase the number of vertex cache from 16 to 32.  And, unlike 
FIFO micro code, XBUS micro code cannot make RDP do the drawing 
processing during the operation of Audio micro code, and the 
performance as a whole does not improve, hence the support of 
XBUS was given up.

On releasing F3DEX2 series, the micro code of XBUS method is now 
supported keeping the same number of vertex cache as F3DEX 
series, by optimizing the usage of this internal buffer.

With a micro code of XBUS version, since the size of the internal
buffer to be used to send a RDP command is smaller than that of 
normal FIFO micro code (about 1KBytes), if a large OBJECT that 
requires a lot of time for drawing processing of RDP is drawn 
repeatedly, the internal buffer becomes full and RSP needs to 
stop until there is a space in the internal buffer. This will be 
a bottleneck, and the RSP processing could become slower.  And, 
a parallel processing of Audio by RSP and drawing by RDP cannot
be done as mentioned above.  However, due to less I/O for RDRAM 
than FIFO (about 1/2), XBUS micro code could become an effective 
way for speed reduction of CPU/RDP caused by a conflict with 
RDRAM bus.  When using XBUS micro code, try various combination.

For those who could not use F3DEX till now as XBUS micro code of 
Fast3D has been used, it is recommended to switch to F3DEX2 
micro code. Refer to Appendix A, "Comparison of new micro code 
with old micro code" for information of the micro code 
comparison.

* Fog processing for Flat Shading polygon

Fog processing can be done now for a polygon that was processed 
with Flat Shading processing (drawn by G_SHADING_SMOOTH=OFF)    

* Changing default value of CLIPRATIO  

The default value of CLIPRATIO which specifies the size of 
CLIPBOX for Fast3D/F3DEX was changed from 1 to 2.      
 

* Increasing minimum required size of FIFO buffer

The minimum required size of FIFO buffer for FIFO micro code 
(output_buff for OSTask structure) became larger.  It was 0x300 
Bytes for gspF3DEX, but now changed to,  

	0x410 Bytes for gspF3DEX2(.NoN)   
	0x600 Bytes for gspF3DLX2.Rej
	0x600 Bytes for gspF3DLX2.Rej  
	0x540 Bytes for gspL3DEX2    
	0x800 Bytes for gspS2DEX2   

When FIFO buffer is shared by more than one micro code, it is 
necessary to set it to the micro code of which required size is 
the largest. FIFO buffer is not necessary for XBUS micro code.  
 

* Change of self-loading processing of Micro code

Changed so that several parameters can be kept when micro code is
self-loaded.  The parameters to be kept are shown below.    

	o DisplayList stack
	o Matrix stack
	o ModelView  matrix
	o Projection matrix
	o Segment table
	o Range of Scissor Box  
	o SetOtherMode parameter
	o Value of PerspNormalize 
	o ViewPort parameter

GeometryMode, Light, or vertex cache other than those above are 
not to be kept.  Model and Projection matrix are kept, however, 
MP matrix is not kept. It is necessary to load either M or P 
matrix once again and reconstruct MP matrix.   

Please note that along with these changes, self-loading with the 
previous F3DEX/S2DEX micro code is no longer possible. Self-
loading is available only between F3DEX2 series, or between 
F3DEX2 and S2DEX2 micro codes.  

Self-loading between FIFO micro code and XBUS micro code is 
possible.  
 
* Loading of 64 vertexes of F3DLX2.Rej at once became possible.

For the old version of F3DLX.Rej, the number of vertex cache was 
64, however, the number of vertex that can be loaded at once was 
limited to 32.  Therefore, in order to load data of 64 vertex, it
was necessary to issue two gSPVertex commands.  There is no such 
limit for  F3DLX2.Rej, which is to be released this time.  Now it
is possible to load data of 1 - 64 vertex at once by just one 
gSPVertex command.  This applies to F3DEX2.Rej also. 

* Supporting CULL_FRONT of F3DLX2.Rej  

For the old version of F3DLX.Rej, CULL_FRONT/CULL_BOTH was not 
supported.  For F3DLX2.Rej,  both are supported. Of course, 
CULL_FRONT/CULL_BOTH are supported for F3DEX2.Rej.  


* Change of GBI number for gSPForceMatrix

For Fast3D/F3DEX series, gSPForceMatrix was a combined command 
with four GBI's, however, for F3DEX2 series, it has been changed 
to a combined command with two GBI's.  Any source codes that 
depend upon this matter need to be modified.  See the following 
examples for reference.  

<Example> Source code that needs modification

	Gfx*gp=glist; -----> Gfx*gp=glist;
	gSPForceMatrix(gp,mptr);	gSPForceMatrix(gp,mptr);
	gp+=4;	gp+=2;
	  ~~~     ~~~

<Example> Source code that does not need modification

	Gfx*gp=glist;
	gSPForceMatrix(gp++,mptr);

* Coexisting with FillRectangle/TextureRectangle in Line Micro 
Code.

The problem that unless Scissor Box is specified again after 
drawing Line using a Line micro code, sometimes FillRectangle/
TextureRectangle does not perform a normal drawing was fixed for 
L3DEX2.  Hence, in case that it is changed to L3DEX2 --> F3DEX2 
by LoadUCode, now it is possible to draw without re-setting 
Scissor Box.


* 'F3DEX2d' Micro code for Debugging.
The micro code 'F3DEX2d' supports debugging for RSP/RDP of an 
application which uses 'F3DEX2'. 'F3DEX2D' is compatible with 
F3DEX2; therefore, use it with replacing F3DEX2 while debugging.

Features of 'F3DEX2d' 

	+ When the program is crashed, a physical address of the 
	  last processed Display List can be obtained. 
	+ Automatically performs Sync process of RDP pipe line. 

Due to above features, the process is slower than 'F3DEX2'. 

Include the 'ucode-debug.h ' file defined by 'extern' in the 
micro code entry. 

	|
	|#include  <ucode_debug.h>
	|

By using macro 'DEBUG_DL_PTR()'. The last implemented (or 
intended to implement) physical address of Display List can be 
obtained, (when the program crashes).  

	|
	|	u32	dl_adrs;
	|
	|	dl_adrs = DEBUG_DL_PTR();
	|

However, if the program is completely crashed, data in the 
physical address can also be destroyed. So the function can not 
guarantee to obtain the address successfully. Normally, the 
function returns useful information to users.      



------------------------------------------------------------------
3. Appendix

[A] Comparison of new micro code with old micro code

	------------------------------------------------------
	  (old)Fast3D/F3DEX series	(new)F3DEX2 series	
	------------------------------------------------------
	<FIFO>
  	  gspFast3D.fifo.o
	  gspF3DEX.fifo.o      		gspF3DEX2.fifo.o
	  gspF3DLX.fifo.o
	<XBUS>
	  gspFast3D.o			gspF3DEX2.xbus.o
	------------------------------------------------------
	<FIFO>
	  gspF3DNoN.fifo.o
	  gspF3DEX.NoN.fifo.o		gspF3DEX2.NoN.fifo.o
	  gspF3DLX.NoN.fifo.o
	<XBUS>
	  gspF3DNoN.o			gspF3DEX2.NoN.xbus.o
	------------------------------------------------------
	<FIFO>
	  gspF3DLP.Rej.fifo.o
	  gspF3DLX.Rej.fifo.o		gspF3DLX2.Rej.fifo.o 
					gspF3DEX2.Rej.fifo.o 
	<XBUS>
	  not applicable		gspF3DLX2.Rej.fifo.o 
					gspF3DEX2.Rej.fifo.o 
	------------------------------------------------------
	<FIFO>
	  gspLine3D.fifo.o
	  gspL3DEX.fifo.o		gspL3DEX2.fifo.o
	<XBUS>
	  gspLine3D.o			gspL3DEX2.xbus.o
	------------------------------------------------------
	<FIFO>
	  gspS2DEX.fifo.o		gspS2DEX2.fifo.o
	  gspS2DEX_d.fifo.o		no support
	<XBUS>
	  not applicable		gspS2DEX2.xbus.o

------------------------------------------------------------------
[B] Explanation of each micro code

	gspF3DEX2.fifo.o/gspF3DEX2.xbus.o
		the number of vertex cache :32
		with sub pixel calculation option
                with clipping option 	 		
	gspF3DEX2.NoN.fifo.o/gspF3DEX2.NoN.xbus.o
		the number of vertex cache :32
		with sub pixel calculation option
		with clipping option by a plane other than 
		NearPlane 
		
	gspF3DEX2.Rej.fifo.o/gspF3DEX2.Rej.xbus.o
		the number of vertex cache :64
		with sub pixel calculation option
		with rejection processing
		(if a part of a triangle is outside the CLIPBOX, 
		stop rendering of the who le triangle.)  

	gspF3DLX2.Rej.fifo.o/gspF3DLX2.Rej.xbus.o
		the number of vertex cache :64
		without sub pixel calculation option
		with rejection processing
		(if a part of a triangle is outside the CLIPBOX, 
		stop rendering of the who le triangle.)

	gspL3DEX2.fifo.o/gspL3DEX2.xbus.o
		Line micro code
		the numbef of vertex cache :32
		with sub pixel calculation option
		with clipping option

	gspS2DEX2.fifo.o/gspS2DEX2.xbus.o
		Sprite micro code

------------------------------------------------------------------
4. History of revisions

03/26/98:
    Release 2.00
	* officially released

03/30/98:
    Release 2.01
	* F3DEX2.Rej was added, speed of F3DLX2.Rej was slightly 
	  increased. 

04/16/98:
    Release 2.02 (patchNg980421 version)
	* Information on change of the number of GBI for 
	  gSPForceMatrix and Coexistence with FillRectangle/
	  TextureRectangle in case of Line micro code was added.
	* The hung up that occurs when gSPPopMatrix processing is
	  done for an empty stack was fixed.  Changed so that 
	  when a stack is empty gSPPopMatrix is ignored. 
	* S2DEX2 micro code that is possible to load mutually 
	  with F3DEX2 series using gSPL oadUcodeL was added to 
	  the package and its explanation was added.  
	* Drawing process was not performed correctly for narrow 
	  frames using gSPBgRectCopy command for S2DEX 1.06.  The
	  problem was fixed.
 	* If clipping process occurs when Flat Shading is used, 
	  colors of Flat Shading beca me irregular.  The problem 
	  was fixed.
	* The assignments other than LIGHT_1 for gSPLightColor 
	  were incorrect.  The problem was fixed.

04/23/98:
    Release 2.03
	* gSPBranchLessZ* command did not run correctly.  The 
	  problem was fixed.
	* When more than three lights were used, colors did not 
	  come out right.  The problem was fixed.

05/20/98:
    Release 2.04
	* The lighting calculation problem has been fixed.  When 
	  a normal vector is normalized by 128, the calculation 
	  was not correct.

5/28/98:
    Release 2.04 (patchNg980610 version)
	* gbi.h was changed in order to invalidate 
	  G_TEXTURE_ENABLE.
	* No changes of the micro code after 05/20/98 version.

6/15/98:
    Release 2.05
	* The operation of G_TEXTURE_GEN_LINEAR was modified. 
	* Z value of the polygon between the image point and Near
	  plane in F3DEX2.NoN was beyond the scope of definition. It has been solved.
	* The drawing method was changed in order to make a 
	  drawing method when polygon is clipped by clipping 
	  process in F3DEX2 similar to a drawing method when 
	  polygon is clipped by cliggping process in F3DEX as 
	  much as possible.

07/29/98:
    Release 2.06
	* Fixed the problem with NearClip processing for 
	  F3DEX2.NoN

10/0/98:
    Release 2.07
	* Sometimes small holes were made in boundary of the 
	  adjoining polygon with F3DEX2, F3DEX2.NoN, and 
	  F3DEX2.Rej. It was fixed.

01/05/99:
    Release 2.08
	* Fixed the problem. When 'F3DEX2' is started, 
	  initialization of register sometimes doesn't work 
	  properly after starting up a part of micro code.  
	* Micro code for Debug is added. The related details are 
	  in Chapter 2 in this document.