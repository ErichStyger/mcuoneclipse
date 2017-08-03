# Batch file to build an Eclipse project from the command line on Windows
# Example for using MCUXpresso IDE

# path to GNU tools and compiler: arm-none-eabi-gcc.exe, ....
SET TOOLCHAIN_PATH=C:\nxp\MCUXpressoIDE_10.0.2_411\ide\tools\bin

# variable to the command line Eclipse IDE executable
SET IDE=C:\nxp\MCUXpressoIDE_10.0.2_411\ide\mcuxpressoidec.exe

ECHO Extending PATH if not already present
ECHO %PATH%|findstr /i /c:"%TOOLCHAIN_PATH:"=%">nul || set PATH=%PATH%;%TOOLCHAIN_PATH%
SET PATH=%PATH%;%TOOLCHAIN_PATH%

ECHO Launching Eclipse IDE
"%IDE%" -nosplash --launcher.suppressErrors -application org.eclipse.cdt.managedbuilder.core.headlessbuild -data "c:\tmp\wsp" -build frdmk64f_rtos_examples_freertos_event
