------------------------------------------------------------------
The structure of this directory is described below.
------------------------------------------------------------------

Because versions of the PC OS do not include audio tools, make 
cannot be used for sound sequence data files.  Using make requires 
the SGI OS.  Sound development with only a PC requires N64 Sound 
Tools.

banks:
Contains a sample of the .inst files used when a bank is created.
Using make creates a sample bank file.

sequences:
Contains sample sequence data.  Using make creates uncompressed and
compressed sequence bank files.

sfx:
Contains samples of uncompressed sound effects waveform data.  
Using make creates compressed data in the special Nintendo ADPCM 
format from the waveform data. 

sounds:
Contains samples of uncompressed sound source waveform data. Using 
make creates compressed data in the unique Nintendo ADPCM format 
from the waveform data. 


ddfonts:
Contains the font data contained in 64DD DDROM as image data in RGB
format.

ddsound:
Contains the sound data contained in 64DD DDROM as an .aifc file.