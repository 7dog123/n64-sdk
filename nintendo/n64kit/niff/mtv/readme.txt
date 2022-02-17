Texture Viewer Manual

Outline
Directory Structure
Usage
Outline of each file
  -autoview.exe
  -trans.exe
  -texview.exe
  -image64.dll
  -texprev.bat
  -texv.n64
  -tvBMP.dll
  -tvRGB.dll
Regarding the output C source
Instructions for Nintendo 64 Control Deck

...........................................................................
                                    Outline
...........................................................................


This application program enables the user to view a picture created for 
Nintendo 64.
The same image can be viewed by changing the format or bit depth.
The following format types can be used.
- CITextureEditor project file (.tpf)
- SGI image format (.sgi .rgb .rgba)
  However, the transformation depends on the number of channels being used,
  as shown below:
  1 channel: I
  2 channels: IA
  3 channels: RGB
  4 channels: RGBA
- Windows bitmap files. However the file should not be RLE compressed and 
should be 1, 4, 8 ,24 bit picture. (.bmp .dbi)

...........................................................................
                               Directory Structure
...........................................................................

+-[src]
|   |--- <N64 Source File>
|
+-[exe]
    |--- autoview.exe
    |--- trans.exe
    |--- texview.exe
    |--- image64.dll
    |--- texv.n64
    |--- texprev.bat
    |--- [plugin]
            |---- tvBMP.dll
            |---- tvRGB.dll

...........................................................................
                                Usage
...........................................................................

To view a number of pictures simultaneously.

Use 'autoview.exe'.
For example: In a case where, image1.rgb, image2.bmp, image3.sgi, and 
image4.tpf are viewed simultaneously, from the command line, type: 
>autoview image1.rgb image2.bmp image3.sgi image4.tpf
an 'out.bin' file is created. 
>nload texv.n64
>nload -s0x400000 out.bin
After executing the above lines, the pictures can be viewed using the IS-Viewer.
For later convenience, these files can be stored as batch files. 

Viewing pictures in different formats.

Use 'trans.exe' and 'texview.exe'.
For example, viewing 'image1.rgb' with 256 color index, and viewing 
'image2.bmp' with 256 color intensity. 
>trans -s 8 -f CI -t C image1.rgb
>trans -s 8 -f I image2.bmp
image1.tvd and image2.tvd files are created after executing above lines.
>texview image1 image2
After executing the above line, the 'out.bin' file is created in a similar 
format. 
>nload texv.n64
>nload -s0x400000 out.bin
By executing the above lines, the pictures can be viewed using the IS-Viewer.


Viewing as a background picture.

Use the '-b' option to convert a picture for the background.
Suppose, there are background pictures with extensions 'bg'.'rgb'. 
By using 'autoview.exe', type the following:
>autoview image1.rgb image2.bmp image3.sgi image4.tpf -B bg.rgb 
Also, to use'trans.exe' as 'texview.exe,' type:
>trans -s 16 -f IA -B bg.rgb
After the command is implemented, a 'bg.tvd' file is created. 
Then execute:
>texview image1 image2 bg
'out.bin' is finally created.
Follow the same procedure described in the previous section. 


Outputting the source file in C language.

Use 'trans.exe'. Specify the output file name (.c .cpp .o) properly 
using the '-o' option.
>trans -s 16 -f RGBA -o image1.c image1.rgb
'imagel.c' source file is created after executing the above line.
Also, when specifying 'imagel.h' after the '-o' option, the file can 
be created in the header file format. However, the outputted file can 
only be used with LoadTextureTile.

...........................................................................
                              Outline of each file
...........................................................................

autoview.exe
A number of pictures can be converted into a format which enables them 
to be viewed using Nintendo 64.
Because the program calls 'trans.exe' and 'texview.exe', these files 
should be stored in the same folder.

Format:  trans [-Op] [-Op] ... image File ...
Options
-s siz/pixel(4,8,16,32)
         The number of bits per 1 pixel.
         The default is the maximum value that can be used with the 
         specified format.
         For example, if the format is IA or I, the number of bits are 
         16 or 8.

-f Format(RGBA,YUV,IA,I,CI)
         The format of an image, the default is RGBA.

-t Palette(C,I)
         A kind of palette, specifying 'C' for G_TT_RGBA16, 'I' for 
         G_TT_IA16. 
         The default is 'C'. 
-w width
-h height
        One image can be divided into a number of images.
        At that time, these are used to specify the width and height.
        When the size of the image is not divisible, the fractional part is 
        deleted. Unlike with autoview.exe, this option can also be applied 
        to the background.
-o filename
        Specifies output file name. If no extension is used, '.bin' is 
        assigned. 
        The default is 'out.bin'.

-B
        Assigns a background property, should be specified for each picture. 

Points to note:
Make sure to specify all options first and then describe the name of 
the image file. There is no priority sequence for options except that 
the image file should be specified last. The option specification also 
corresponds to '/'.
Pictures don't have to be the same size, however, all pictures are 
converted to the same format and size. Also, a file with an extension 
'.tvd' is deleted after execution because of its temporary nature.

Example:
autoview -s 16 -f RGBA test.rgb
    'test.rgb' is displayed by OPA_SURF in RGBA16bit format.
autoview -s 8 -f CI -t I  -B back.bmp image.rgb
    'image.rgb' is displayed by the 8 bit color index and IA88 palette. 
    'back.bmp' is also converted in the same manner but is displayed as 
     only for background pictures.
autoview -s 8 -f CI -o abc image.rgb -B back1.bmp char1.tpf -B back2.bmp
    Converts specified file into the 8bit color index and RGBA5551 palette.
    'back1.bmp','back2.bmp' are converted as a background property. 
    The converted data is outputted to 'abc.bin' file.

trans.exe
Converts pictures which can be viewed with Nintendo 64. 
Also, it enables the user to convert files into C language source file.
Format:  trans [-Op] [-Op] ... image File ...
Options
-s siz/pixel(4,8,16,32)
-f Format(RGBA,YUV,IA,I,CI)
-t Palette(C,I)
                  Same as autoview.exe 
-o filename
         Specifies the file name to be output, if the extension is omitted, 
         '.tvd' is assigned automatically. 
         The default is 'the base of an image file name + .tvd'.
         When specifying a file with the extension of '.c','.cpp' and '.h', 
         the file can be outputted in the C source file. 

-w width
-h height
         A picture can be divided into a number of pictures.
	 At that time, these are used to specify the width and height.
         When the size of the image is not divisible, the fractional 
         part is deleted.
         Unlike with autoview.exe, this option can also be applied to the 
         background.

-p
       When the output format is set as 'CI', create only one palette by 
       specifying a number of pictures.

-B
      Adds the background property to a picture. 

Notes:
Make sure to specify all options first and then afterward 
describe the name of the image file.
The option specification also corresponds to '/'.
All pictures should be the same in size when arranging a number of 
pictures in one file.

Example:
trans -s 16 -f RGBA test.rgb
     'test.rgb' is displayed using OPA_SURF in RGBA16bit format.
trans -s 8 -f CI -t I image.rgb
    'image.rgb' is displayed using 8 bit color index and IA88 palette. 
trans -s 8 -f CI -B -o abc image.rgb
    Converts specified file into 8bit color index and RGBA5551 palette.
    However, this image is displayed as if only for a background picture.
    The converted data is output to 'abc.tvd' file.
trans -s 16 -f RGBA -o def image0.rgb image1.rgb image2.sgi
    Converts pictures, 'image0.rgb', 'image1.rgb' and 'image2.rgb' 
    into RGBA5551. 
    The created 'def.tvd' file stores their texture data.
    The format, width and height of three pictures should be the same.
    
trans -s 16 -f RGBA -w 80 -h 40 image.rgb
    Suppose the size of 'image.rgb' is 320x240. By using '-w' 
    and '-h' options, 24 textures (80x40) are created.

texview.exe
A file converted by 'trans' is integrated as a file which can 
be "nloaded".

Format:  texview File Name File Name .c [Op.]
Options
-o filename
    Specify output file name. If the extension is omitted, '.bin' 
    is assigned. 
    The default is 'texview.bin'.

image64.dll
    At the user's option, this 'dll' file converts a picture format 
    which can be displayed on the Nintendo 64. 

texprev.bat
    Batch file which enables the user to view the image.
    Rewrite the file along with the image mode.

    '.bin' file which is output by 'autoview.exe' and 'texview.exe'
     must be be "nloaded" to the address 0x400000. 

texv.n64
    Texture Viewer in Nintendo 64.

tvRGB.dll
    "Plug in" which converts SGI image. 

tvBMP.dll
    "Plug in" which converts 'Windows bitmap'.

..........................................................................
                           Regarding the output C source
..........................................................................

C source can be output using trans.exe. 
In the output source, the palette arrays and pixel arrays are lined up, 
followed by the structures that indicate the correspondence between 
palettes and pixels.  
Macros are defined for the palettes, so that colors can be edited by hand.  
Be sure to load the pixel data using gDPLoadTextureTile.


..........................................................................
                          Operation Method for NINTENDO64 
..........................................................................

The menu is not displayed.

A button, B button   ...Switches texture
C buttons            ...Moves texture up/down/left/right. 
                        Texture moves at double-speed when Z button is 
                        held down.
Control Stick        ...Tilts a texture in any direction. Holding Z button, 
                        moves the texture forward and backward.
Control Pad          ...Controls the texture speed of motion but doesn't 
                        change speed for moving forward or backward.
R button             ...Return to its original position.
START button         ...Displays the menu
L button             ...Switches to display/not-display the name of 
                        a texture


When the menu is displayed. 

A button B button     ...Changes contents of an item.
                         Also, can be changed by Z button.
                         If the cursor is on the color setting, the color 
                         can be increased or decreased one by one.
C buttons             ...Not used.
Control Stick         ...Moves cursor.
                         If the cursor is on the color setting, the color 
                         can be increased or decreased by pressing the Z 
                         button. 
                         Movement in the up and down direction is much 
                         faster than in the right and left direction.
Control Pad          ...Not used.
R button             ...Not used.
START button         ...Closes the menu.             
L button             ...Not used.


Menu
COMBINE              ...Sets the combine mode.
BLENDER              ...Sets the render mode.
FILTER               ...Sets the texture filter.
TASKBAR              ...Switches to display/not-display the task bar.
BG                   ...Changes the background picture or turns it off.
BG COLOR             ...Changes the background color.
PRIM COLOR           ...Changes the primitive color.
ENV COLOR            ...Changes the environmental color.

...........................................................................
                          Revision History
...........................................................................

990419    Changed the C source output
990311    Fixed so that RLE-compressed SGI images can be displayed.
990311    Fixed so that -w, -h are disabled for background
990217    Fixed so that width and height can be specified.

..................................................................................
