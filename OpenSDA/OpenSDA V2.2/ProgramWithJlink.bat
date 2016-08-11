REM *******************************************************
REM * Batch file to program a bin file with Segger J-Link *
REM *******************************************************

SET JLINK="C:\Program Files (x86)\SEGGER\JLink_V600e\JLink.exe"

%JLINK% -device MK20DX128xxx5 -CommanderScript ./jlink.script
pause
