@echo off
autoview -f CI -s 8 circle.bmp
if errorlevel 1 goto error
"C:\Program Files\Intelligent Systems\IS-VIEWER64\PROGRAM\nload" -n -v texv.n64
if errorlevel 1 goto error
"C:\Program Files\Intelligent Systems\IS-VIEWER64\PROGRAM\nload" -n -v -s0x400000 out.bin
if errorlevel 1 goto error
goto done
:error
pause
:done
echo on
