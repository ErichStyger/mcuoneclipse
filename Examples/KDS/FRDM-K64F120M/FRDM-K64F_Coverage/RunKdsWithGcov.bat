ECHO checking depending tools
IF NOT EXIST C:\Freescale\KDS_3.0.0\toolchain\bin\gcov.exe COPY C:\Freescale\KDS_3.0.0\toolchain\bin\arm-none-eabi-gcov.exe C:\Freescale\KDS_3.0.0\toolchain\bin\gcov.exe
IF NOT EXIST C:\Freescale\KDS_3.0.0\toolchain\bin\addr2line.exe COPY C:\Freescale\KDS_3.0.0\toolchain\bin\arm-none-eabi-addr2line.exe C:\Freescale\KDS_3.0.0\toolchain\bin\addr2line.exe
IF NOT EXIST C:\Freescale\KDS_3.0.0\toolchain\bin\nm.exe COPY C:\Freescale\KDS_3.0.0\toolchain\bin\arm-none-eabi-nm.exe C:\Freescale\KDS_3.0.0\toolchain\bin\nm.exe
IF NOT EXIST C:\Freescale\KDS_3.0.0\toolchain\bin\c++filt.exe COPY C:\Freescale\KDS_3.0.0\toolchain\bin\arm-none-eabi-c++filt.exe C:\Freescale\KDS_3.0.0\toolchain\bin\c++filt.exe
IF NOT EXIST C:\Freescale\KDS_3.0.0\toolchain\bin\strings.exe COPY C:\Freescale\KDS_3.0.0\toolchain\bin\arm-none-eabi-strings.exe C:\Freescale\KDS_3.0.0\toolchain\bin\strings.exe

ECHO Extending PATH
SET PATH=%PATH%;C:\Freescale\KDS_3.0.0\toolchain\bin

ECHO Launching Kinetis Design Studio V3.0.0
C:\Freescale\KDS_3.0.0\eclipse\kinetis-design-studio.exe

