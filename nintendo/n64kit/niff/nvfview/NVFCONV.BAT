@echo off
niff2nvf nvfconv.nif model.nvf
if errorlevel 1 goto error
goto done
:error
pause
:done
echo on
