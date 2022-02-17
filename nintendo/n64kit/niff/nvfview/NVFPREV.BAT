@echo off
niff2nvf nvfprev.nif model.nvf
if errorlevel 1 goto error
nvf2bin scene.nvf model.nvf nvfview.bin
if errorlevel 1 goto error
"C:\Program Files\Intelligent Systems\IS-VIEWER64\PROGRAM\nload" -n -e nvfview.N64
if errorlevel 1 goto error
"C:\Program Files\Intelligent Systems\IS-VIEWER64\PROGRAM\nload" -n -s 0x200000 nvfview.bin
if errorlevel 1 goto error
goto done
:error
pause
:done
echo on
