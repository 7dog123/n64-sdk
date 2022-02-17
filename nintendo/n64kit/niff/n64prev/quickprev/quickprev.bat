@echo off
"C:\Program Files\Intelligent Systems\IS-VIEWER64\PROGRAM\nload" -n -v quickprev.n64
if errorlevel 1 goto error
..\niff2gfx -b quickprev.nif model.bin
if errorlevel 1 goto error
"C:\Program Files\Intelligent Systems\IS-VIEWER64\PROGRAM\nload" -n -v -s0x200000 model.bin
if errorlevel 1 goto error
goto done
:error
pause
:done
echo on
