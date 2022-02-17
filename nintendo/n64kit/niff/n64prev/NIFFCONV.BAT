@echo off
set root=c:\ultra
set gccdir=%ROOT%\gcc
path %gccdir%\mipse\bin;%root%\sbin;%path%
set gccsw=-mips3 -mgp32 -mfp32 -D_LANGUAGE_C -D_ULTRA64 -D__EXTENSIONS__
set n64align=on
niff2gfx -header model.h niffconv.nif model.c
if errorlevel 1 goto error
goto done
:error
pause
:done
echo on
