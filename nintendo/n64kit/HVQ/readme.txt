HVQ/HVQM Package                                             1999/8/4

In this directory a package is included that allows you to use the Still Image 
Compression Method HVQ and the Motion Picture/Animated Image Compression Method 
HVQM with N64.

HVQ and HVQM have the following attributes.

*HVQ 
- Static Image Encoding System 
- HVQ is the acronym for "hybrid vector quantization"
- JPEG compression is being done with DCT Conversion + Entropy Encoding. However, 
  in the case of HVQ compression instead of DCT, Vector Compression is being done 
  with Codebook.
- Similar to JPEG, this is a non-reversible conversion (cannot revert to original 
  image).
- Different from JPEG, it is difficult to block noise with the high frequency 
  portions (areas where color changes are great), so it is possible to compress a 
  high quality image with sharp edges like an animated drawing.
- Better compression by 20-40% compared to a JPEG image with the same quality.
- The decoding speed is 1.8 times (approximately 110 msec) faster than with JPEG.
- The resolution should be 320 x 240. The lower the resolution, the lower the 
  compression ratio will be (less than 1/3 for both vertical/horizontal).

*HVQM 
- Motion picture/animation encoding system
- VQM uses HVQ for compressing the key frame, and it uses H.261, which is used 
  for videophone, for compressing between frames.
- Sound can also be played back (single channel 4-bit ADPCM)
- Playback speed is approximately 12 frames per second
- Compared to MPEG, etc., compression takes more time.

*About Using HVQ:
- No royalties are required with HVQ/HVQM Library. You can use them free of charge.
- When using in games, please display a logo showing that you are using it.
  For details, please refer to the HVQ Logo Directory Document.
