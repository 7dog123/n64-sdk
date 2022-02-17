anmview.exe anmview.taf -o anmdata.c -e anmdata.h
if errorlevel 1 goto error
make
if ERRORLEVEL == 1 goto end
nload -v -n anmview.n64
:end
