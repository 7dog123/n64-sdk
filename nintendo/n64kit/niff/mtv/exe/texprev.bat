REM
REM		This is Sample.
REM
@echo off
trans -s 8 -f CI -t C -B -p -o aa bg.rgb BG_book4.rgb
if errorlevel 1 goto error
trans -s 16 -f RGBA -t C -w 80 -h 80 -o ab image.bmp
if errorlevel 1 goto error
trans -s 8 -f CI -t I -o ac cite.tpf
if errorlevel 1 goto error
trans -s 4 -f I -o bb sgiimg.sgi
if errorlevel 1 goto error
TexView	aa ab ac bb cc back -o abcde.bin
if errorlevel 1 goto error
"C:\Program Files\Intelligent Systems\IS-VIEWER64\PROGRAM\nload" -n -v texv.n64
if errorlevel 1 goto error
"C:\Program Files\Intelligent Systems\IS-VIEWER64\PROGRAM\nload" -n -v -s0x400000 abcde.bin
if errorlevel 1 goto error
goto done
:error
pause
:done
echo on
