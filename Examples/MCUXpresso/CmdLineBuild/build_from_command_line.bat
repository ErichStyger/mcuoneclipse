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

@REM -build on project: normal build, does a (re-)build of all targets (Release, Debug): the fact that it does a full build sounds lika an issue in Eclipse CDT 9.4.3?
"%IDE%" -nosplash --launcher.suppressErrors -application org.eclipse.cdt.managedbuilder.core.headlessbuild -data "c:\tmp\wsp" -build MyProject

@REM - build on a build target: only builds the target, this works properly with CDT 9.4.3
@REM "%IDE%" -nosplash --launcher.suppressErrors -application org.eclipse.cdt.managedbuilder.core.headlessbuild -data "c:\tmp\wsp" -build MyProject/Debug

@REM -cleanbuild on project: this does a 'clean' on each build target followed by a build
@REM "%IDE%" -nosplash --launcher.suppressErrors -application org.eclipse.cdt.managedbuilder.core.headlessbuild -data "c:\tmp\wsp" -cleanBuild MyProject

@REM -cleanbuild on a build target: this does a 'clean' only on the build target, no build
@REM "%IDE%" -nosplash --launcher.suppressErrors -application org.eclipse.cdt.managedbuilder.core.headlessbuild -data "c:\tmp\wsp" -cleanBuild MyProject/Debug
