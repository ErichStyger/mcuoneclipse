REM Run Eclipse with gcov environment

REM Check that path setup is correct
call addPath.bat

REM Check that GNU tools are present
call checkGNUbin.bat

REM launch Eclipse
C:\nxp\KDS_3.2.0\eclipse\kinetis-design-studio.exe
