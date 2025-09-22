@echo off
REM Batch file to set the needed environemnt. Adapt as needed for your system.
REM It sets the variables only if they are not present on the system level

REM Variable pointing to the ARM Cortex Toolchain. Needed for building and debugging:
if not defined TOOLCHAIN_PREFIX (
    set TOOLCHAIN_PREFIX=C:/Raspy/pico/sdk/toolchain
)

REM Variable pointing to the J-Link software, needed for debugging only:
if not defined SEGGER_PATH (
    set SEGGER_PATH=C:/Program Files/SEGGER/JLink
)

REM printing the current variables:
echo TOOLCHAIN_PREFIX=%TOOLCHAIN_PREFIX%
echo SEGGER_PATH=%SEGGER_PATH%

REM checking tools
where cmake >nul || echo "ERROR: cmake not found in PATH!"
where ninja >nul || echo "ERROR: ninja not found in PATH!"

REM Add tools to PATH only if they are not present yet:
path|find /i "%TOOLCHAIN_PREFIX%\bin" >nul || set path=%TOOLCHAIN_PREFIX%\bin;%path%
path|find /i "%SEGGER_PATH%" >nul || set path=%SEGGER_PATH%;%path%

REM printing location of necessary tools: they need to be present in PATH:
where cmake ninja jlink arm-none-eabi-gcc
