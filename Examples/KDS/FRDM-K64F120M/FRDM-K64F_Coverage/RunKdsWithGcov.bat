SET KDS_PATH=C:\nxp\KDS_3.2.0

ECHO checking depending tools
IF NOT EXIST "%KDS_PATH%\Toolchain\bin\gcov.exe"      COPY "%KDS_PATH%\Toolchain\bin\arm-none-eabi-gcov.exe"      "%KDS_PATH%\Toolchain\bin\gcov.exe"
IF NOT EXIST "%KDS_PATH%\Toolchain\bin\addr2line.exe" COPY "%KDS_PATH%\Toolchain\bin\arm-none-eabi-addr2line.exe" "%KDS_PATH%\Toolchain\bin\addr2line.exe"
IF NOT EXIST "%KDS_PATH%\Toolchain\bin\nm.exe"        COPY "%KDS_PATH%\Toolchain\bin\arm-none-eabi-nm.exe"        "%KDS_PATH%\Toolchain\bin\nm.exe"
IF NOT EXIST "%KDS_PATH%\Toolchain\bin\c++filt.exe"   COPY "%KDS_PATH%\Toolchain\bin\arm-none-eabi-c++filt.exe"   "%KDS_PATH%\Toolchain\bin\c++filt.exe"
IF NOT EXIST "%KDS_PATH%\Toolchain\bin\strings.exe"   COPY "%KDS_PATH%\Toolchain\bin\arm-none-eabi-strings.exe"   "%KDS_PATH%\Toolchain\bin\strings.exe"
IF NOT EXIST "%KDS_PATH%\Toolchain\bin\gprof.exe"     COPY "%KDS_PATH%\Toolchain\bin\arm-none-eabi-gprof.exe"     "%KDS_PATH%\Toolchain\bin\gprof.exe"
IF NOT EXIST "%KDS_PATH%\Toolchain\bin\gdb.exe"       COPY "%KDS_PATH%\Toolchain\bin\arm-none-eabi-gdb.exe"       "%KDS_PATH%\Toolchain\bin\gdb.exe"

ECHO Extending PATH
SET PATH=%PATH%;%KDS_PATH%\Toolchain\bin

ECHO Launching Kinetis Design Studio V3.3.0
"%KDS_PATH%\eclipse\kinetis-design-studio.exe"
