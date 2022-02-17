============================================================================
N64-HVQ2 library version 1.2 (PC)

Summary
============================================================================


Summary
=======

This library is a Nintendo 64 runtime library for decoding compressed image data 
output in the "HVQ2 1.0" format using the still image compression tool hvq2enc, and 
expanding the decoded image data in a buffer.

See the file GUIDE.TXT to learn how to use this library and to read about the HVQ2 
file format.  See the file FUNCTIONS.TXT to read about the various library 
functions and microcode.

The PC version library libhvq2.a was created for exeGCC N64 for PC, so it cannot be 
linked in the SGI development environment.  If you are working in the SGI 
development environment, please use of the SGI version of the N64-HVQ2 library.


Directory structure
===================

./
 |--- README.TXT        Summary (this file)
 |--- GUIDE.TXT         Programming guide
 |--- FUNCTIONS.TXT     Function reference manual
 |
 |--- lib/
 |     |--- libhvq2.a   The library itself
 |     |--- hvq2dec.h   Definitions related to the library functions and microcode
 |     |--- HVQ2File.h  HVQ2 file format definitions
 |     |--- HVQmd.h     Machine definitions (included from HVQ2File.h)
 |
 |--- rspcode/
       |--- hvq2sp1.o   Microcode for 16bit RGBA
       |--- hvq2sp2.o   Microcode for 32bit RGBA



Main changes from version 1.1
=============================

-- Setting the pixel alpha value
   Changed it so the value set in the A field of the RGBA pixel is specified in
   the decoder's initialization function (hvq2Init1(), hvq2Init2(), hvq2InitSP()).

-- Fixed the problem in the hvq2sp2 RSP microcode
   The hvq2sp2 microcode had a problem in that it did not set the A field of the 
   pixel. This was corrected.


-- Accelerated the RSP microcode.


