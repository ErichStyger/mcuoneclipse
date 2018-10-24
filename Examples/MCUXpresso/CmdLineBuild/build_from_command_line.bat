REM Batch file to build an Eclipse project from the command line on Windows
REM Example for using MCUXpresso IDE

@REM path of the IDE
SET IDE_PATH=C:\nxp\MCUXpressoIDE_10.2.1_795

@REM path to GNU tools and compiler: arm-none-eabi-gcc.exe, ....
SET TOOLCHAIN_PATH=%IDE_PATH%\ide\tools\bin

@REM variable to the command line Eclipse IDE executable
SET IDE=%IDE_PATH%\ide\mcuxpressoidec.exe

ECHO Extending PATH if not already present
ECHO %PATH%|findstr /i /c:"%TOOLCHAIN_PATH:"=%">nul || set PATH=%PATH%;%TOOLCHAIN_PATH%

ECHO Launching Eclipse IDE

@REM normal build (but rebuilds all?)
REM "%IDE%" -nosplash --launcher.suppressErrors -application org.eclipse.cdt.managedbuilder.core.headlessbuild -data "c:\tmp\wsp" -build MyProject

@REM build (does a build of all targets)
"%IDE%" -nosplash --launcher.suppressErrors -application org.eclipse.cdt.managedbuilder.core.headlessbuild -data "c:\tmp\wsp" -build MyProject/Debug

@REM cleanbuild of Debug only: this does a 'clean' only
@REM "%IDE%" -nosplash --launcher.suppressErrors -application org.eclipse.cdt.managedbuilder.core.headlessbuild -data "c:\tmp\wsp" -cleanBuild MyProject/Debug
