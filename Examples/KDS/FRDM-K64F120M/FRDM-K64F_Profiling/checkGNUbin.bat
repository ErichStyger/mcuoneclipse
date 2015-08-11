@ECHO OFF
ECHO Checking GNU Binaries and making copies as necessary
SET KDS3=C:\Freescale\KDS_3.0.0
IF NOT EXIST "%KDS3%\toolchain\bin\gcov.exe"      COPY "%KDS3%\toolchain\bin\arm-none-eabi-gcov.exe"      "%KDS3%\toolchain\bin\gcov.exe"
IF NOT EXIST "%KDS3%\toolchain\bin\addr2line.exe" COPY "%KDS3%\toolchain\bin\arm-none-eabi-addr2line.exe" "%KDS3%\toolchain\bin\addr2line.exe"
IF NOT EXIST "%KDS3%\toolchain\bin\nm.exe"        COPY "%KDS3%\toolchain\bin\arm-none-eabi-nm.exe"        "%KDS3%\toolchain\bin\nm.exe"
IF NOT EXIST "%KDS3%\toolchain\bin\c++filt.exe"   COPY "%KDS3%\toolchain\bin\arm-none-eabi-c++filt.exe"   "%KDS3%\toolchain\bin\c++filt.exe"
IF NOT EXIST "%KDS3%\toolchain\bin\strings.exe"   COPY "%KDS3%\toolchain\bin\arm-none-eabi-strings.exe"   "%KDS3%\toolchain\bin\strings.exe"
IF NOT EXIST "%KDS3%\toolchain\bin\gdb.exe"       COPY "%KDS3%\toolchain\bin\arm-none-eabi-gdb.exe"       "%KDS3%\toolchain\bin\gdb.exe"
IF NOT EXIST "%KDS3%\toolchain\bin\gprof.exe"     COPY "%KDS3%\toolchain\bin\arm-none-eabi-gprof.exe"     "%KDS3%\toolchain\bin\gprof.exe"
ECHO Done!
