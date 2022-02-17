echo off
rem =========================================
rem Texture Editor anmview.bat
rem =========================================
set root=c:\ultra
set gccdir=%ROOT%\gcc
path %gccdir%\mipse\bin;%root%\sbin;%path%
set gccsw=-mips3 -mgp32 -mfp32 -D_LANGUAGE_C -D_ULTRA64 -D__EXTENSIONS__
set n64align=on
make
if errorlevel 1 goto error
goto done
:error
pause
:done
