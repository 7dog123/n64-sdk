MMVReadme

MMV Image Converter  autoview.exe

---------------------
       Summary
---------------------
Enables viewing of the same image with a different specified format and bit depth.

At the present time, the following formats are supported:

* CITextureEditor Project files (.tpf)
* SGI Image format (.sgi  .rgb  .rgba)
  However, the transformation depends on the number of channels being used, 
  as shown below:
    1 channel: I
    2 channels: IA
    3 channels: RGB
    4 channels: RGBA
* Windows bitmapped graphics, provided they are 1bit, 4bit, 8bit or 24bit images 
  that are not RLE-compressed (.bmp  .dbi)

To learn more about the output file formats, see the section on 
"NIFF MultiTextureViewer" under All Manuals.


---------------------
       Format
---------------------

autoview [-Op] [-Op] ... image File ...

Options

-s  siz/pixel (4,8,16,32)
The number of bits per pixel.
The default is 32 bits, but the size changes depending on the format.  
For example, the size is 16 bits for the AI format, and 8 bits for the I format.

-f Format (RGBA, YUV, IA, I, CI)
The format of the image.  The default is RGBA.

-t Palette (C,I)
The palette type.  Can be set to C or I, becoming either G_TT_RGBA16 or G_TT_IA16.  
The default type is C.

-o filename
Specifies the name of the file that is output.  If no extension is specified, 
the file is output with a .bin extension.  The default filename is out.bin.

-w width
Divides the image horizontally.  Specify the width of each image.  
If the image has a background attribute, it will not be divided.

-h height
Divides the image vertically.  Specify the height of each image.  
If the image has a background attribute, it will not be divided.

-B
Attaches the background attribute to an image.  
This must be specified for each separate image.



---------------------
 NINTENDO64 Controls
---------------------


* When the menu is not displayed:

A button, B button      Switches textures.
C buttons               Move texture up/down/left/right. 
                        Texture moves at double-speed when Z button is held down.
Control Stick           Tilts texture up/down/left/right. Hold the Z button down 
                        to move texture depth-wise forward and backward.
Control Pad             Changes the speed at which the texture moves.  
                        However, this will not change speed at which texture moves 
                        depth-wise forward and backward.
R button                Texture returns to its original position.
START button            Displays the menu.
L button                Toggles between show/hide the texture name.


* When the menu is displayed:

A button, B button      Switches the contents of an item. The same task can be 
                        accomplished with the Z button. When the cursor is over  
                        the color settings, colors can be added or deleted one at 
			a time.
C buttons               Not used.
Control Stick           Moves the cursor. When the cursor is over the color  
                        settings, if you keep the Z button depressed you can use  
                        the Control Stick to increase or decrease colors.  
                        Changes are faster in up/down direction than in 
                        the left/right direction.
Control Pad             Not used.
R button                Not used.
START button            Closes the menu.
L button                Not used.


The Menu:

COMBINE           Sets the combine mode.
BLENDER           Sets the render mode.
FILTER            Sets the texture filter.
TASKBAR           Toggles between show/hide task bar.
BG                Switches background image or turns background off.
BG COLOR          Changes background color.
PRIM COLOR        Changes primitive color.
ENV COLOR         Changes environment color.


---------------------
 Revision History
---------------------

990409  Added version information
990405  For 4bit BMP, set the initial alpha value of color to 0.
990311  Fixed things so RLE-compressed SGI images can be displayed.
990311  Fixed things so files with a .rgba extension can be displayed.
990305  Fixed things so you -w, -h are disabled for background
990217  Fixed things so width and height can be specified.




