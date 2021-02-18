@cd..
@cd..
@cd..
@rem make clean
@if exist Output rmdir /s /q Output
@mkdir Output
@chdir Output
@mkdir Bin
@mkdir Obj
@mkdir Map
@mkdir Log
@cd..

perl BuildTime.pl
@cd Project
@cd S2MUA01_Examples
@cd FUELGAUGE
make -j8 > .\..\..\..\Output\Log\compile.log && type .\..\..\..\Output\Log\compile.log
@cd..
@cd..
@cd..
perl BIN_TO_FLASH.pl .\Output\Bin\fw_flash.bin
pause > nul
