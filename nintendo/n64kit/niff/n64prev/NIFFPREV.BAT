@echo off
set root=c:\ultra
set gccdir=%ROOT%\gcc
path %gccdir%\mipse\bin;%root%\sbin;%path%
set gccsw=-mips3 -mgp32 -mfp32 -D_LANGUAGE_C -D_ULTRA64 -D__EXTENSIONS__
set n64align=on
niff2gfx -header model.h niffprev.nif model.c
if errorlevel 1 goto error
make -f makefile.win
if errorlevel 1 goto error
"C:\Program Files\Intelligent Systems\IS-VIEWER64\PROGRAM\nload" -n -v -s0x200000 "quickprev\clean.bin"
if errorlevel 1 goto error
"C:\Program Files\Intelligent Systems\IS-VIEWER64\PROGRAM\nload" -n -v nuprev.n64
if errorlevel 1 goto error
goto done
:error
pause
:done
echo on
