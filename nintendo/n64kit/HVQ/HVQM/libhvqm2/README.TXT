============================================================================
N64-HVQM2 library   version 1.2 (PC)

Summary
============================================================================


Summary
=======

This library enables "HVQM2 1.0" format HVQM2 data output by the motion picture 
compression tool hvqm2enc to be used in the development of Nintendo64 applications.  
It is a runtime library that has library functions to decode video records 
(HVQM-Movie compressed image data) included in the HVQM2 data and to expand the 
data in a buffer, together with library functions to decode audio records (ADPCM 
data) and expand the PCM data in a buffer, and executable RSP microcode that 
speeds up some of the image decoding.

See GUIDE.TXT to read about use of the library and about the HVQM2 file format.  
See FUNCTIONS.TXT to read details about the various functions and microcode.

The PC version library libhvqm2.a was created for exeGCC N64 for PC, so it cannot 
be linked in the SGI development environment.  If you are working in the SGI 
development environment, please use of the SGI version of the N64-HVQM2 library.



Directory Structure
===================

./
 |--- README.TXT         Summary (this file)
 |--- GUIDE.TXT          Programming guide
 |--- FUNCTIONS.TXT      Function reference manual
 |
 |--- lib/
 |     |--- libhvqm2.a   The library itself
 |     |--- hvqm2dec.h   Definitions relating to the image decoding library 
 |     |                 functions and microcode
 |     |--- adpcmdec.h	 Definitions relating to the audio decoding library
 |     |--- HVQM2File.h	 HVQM2 file format definitions
 |     |--- HVQmd.h	 Machine definitions (included from HVQM2File.h)
 |
 |--- rspcode/
       |--- hvqm2sp1.o   RSP microcode for 16bit RGBA
       |--- hvqm2sp2.o   RSP microcode for 32bit RGBA



Main Changes from Version 1.1 
=============================

-- Setting the pixel alpha value
   Changed it so the value set in the A field of the RGBA pixel is specified in
   the decoder's initialization function (hvqm2Init1(), hvqm2Init2(), 
   hvqm2InitSP1(), hvqm2InitSP2()).

-- Fixed a problem in the hvqm2sp2 RSP microcode (1)
   The hvqm2sp2 microcode had a problem in that it did not set the A field of the 
   pixel. This was corrected.

-- Fixed a problem in the hvqm2sp2 RSP microcode (2)
   Fixed problem with incorrect processing of yield resumption

-- Accelerated the RSP microcode.
