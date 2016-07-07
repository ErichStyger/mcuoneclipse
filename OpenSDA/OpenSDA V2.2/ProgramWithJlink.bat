REM *******************************************************
REM * Batch file to program a bin file with Segger J-Link *
REM *******************************************************

SET JLINK="c:\Program Files (x86)\SEGGER\JLink_V541i\JLink.exe"

%JLINK% -device MK20DX128xxx5 -CommanderScript ./jlink.script
pause
