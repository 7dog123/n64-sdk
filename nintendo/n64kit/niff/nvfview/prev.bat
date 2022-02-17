@if "%1"=="" goto modelprev
niff2nvf %1 model.nvf
:nvfprev
nvf2bin scene.nvf model.nvf nvfview.bin
nload -n -e nvfview.N64
nload -n -s 0x200000 nvfview.bin
@goto end
:modelprev
niff2nvf model.niff model.nvf
@goto nvfprev
:end
