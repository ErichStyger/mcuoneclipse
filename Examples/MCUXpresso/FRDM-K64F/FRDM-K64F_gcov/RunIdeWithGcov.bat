# Batch file to check and copy the needed tools for gcov/gprof to be used in an Eclipse IDE
# Example for using MCUXpresso IDE
SET TOOLCHAIN_PATH=C:\nxp\MCUXpressoIDE_10.2.0_759\ide\tools\bin
SET IDE=C:\nxp\MCUXpressoIDE_10.2.0_759\ide\mcuxpressoide.exe

ECHO checking gcov/gprof dependencies on binutils
IF NOT EXIST "%TOOLCHAIN_PATH%\gcov.exe"      COPY "%TOOLCHAIN_PATH%\arm-none-eabi-gcov.exe"      "%TOOLCHAIN_PATH%\gcov.exe"
IF NOT EXIST "%TOOLCHAIN_PATH%\addr2line.exe" COPY "%TOOLCHAIN_PATH%\arm-none-eabi-addr2line.exe" "%TOOLCHAIN_PATH%\addr2line.exe"
IF NOT EXIST "%TOOLCHAIN_PATH%\nm.exe"        COPY "%TOOLCHAIN_PATH%\arm-none-eabi-nm.exe"        "%TOOLCHAIN_PATH%\nm.exe"
IF NOT EXIST "%TOOLCHAIN_PATH%\c++filt.exe"   COPY "%TOOLCHAIN_PATH%\arm-none-eabi-c++filt.exe"   "%TOOLCHAIN_PATH%\c++filt.exe"
IF NOT EXIST "%TOOLCHAIN_PATH%\strings.exe"   COPY "%TOOLCHAIN_PATH%\arm-none-eabi-strings.exe"   "%TOOLCHAIN_PATH%\strings.exe"
IF NOT EXIST "%TOOLCHAIN_PATH%\gprof.exe"     COPY "%TOOLCHAIN_PATH%\arm-none-eabi-gprof.exe"     "%TOOLCHAIN_PATH%\gprof.exe"

ECHO Extending PATH
SET PATH=%PATH%;%TOOLCHAIN_PATH%

ECHO Launching Eclipse IDE
"%IDE%"
