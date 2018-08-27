readme.txt
----------
This project is a MCUXpresso IDE 10.2.1 project using the McuOnEclipse library files:
https://github.com/ErichStyger/McuOnEclipseLibrary


- create a new (bare metal) project for your board with default settings
- Optional
	- add mex file (config tools support)
	- remove release target
	- change main file to main.c
- Create folder McuOnEclipseLib
- for McuArmTools, add fsl_sim component
- copy files from library
- add include file paths

../McuOnEclipseLib/config
../McuOnEclipseLib/config/fonts
../McuOnEclipseLib/src
../McuOnEclipseLib/FreeRTOS/Source/include
../McuOnEclipseLib/FreeRTOS/Source/portable/GCC/ARM_CM4F
../McuOnEclipseLib/SEGGER_RTT
../McuOnEclipseLib/SEGGER_Sysview
../McuOnEclipseLib/TraceRecorder/config
../McuOnEclipseLib/TraceRecorder/include
../McuOnEclipseLib/TraceRecorder/streamports/Jlink_RTT/include

*** Todo: need to exclude from build several files
*** Todo: merge HardFault_Handler (for semihosting), otherwise rename

- uncheck 'ignore for build'
- verify/change config/McuLibConfig.h
	cpu
	cortex
	SDK McuLib_CONFIG_SDK_MCUXPRESSO_2_0
- add Init code