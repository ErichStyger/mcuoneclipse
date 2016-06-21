@ECHO off
ECHO Adding GNU tools to PATH
SET KDSBIN=C:\nxp\KDS_3.2.0\bin
SET KDSTOOLBIN=C:\nxp\KDS_3.2.0\toolchain\bin
ECHO %PATH%|findstr /i /c:"%KDSBIN:"=%">nul || set PATH=%PATH%;%KDSBIN%
ECHO %PATH%|findstr /i /c:"%KDSTOOLBIN:"=%">nul || set PATH=%PATH%;%KDSTOOLBIN%
ECHO %PATH%