readme.txt
----------
MCUXpresso IDE project for i.MX RT1064-EVK Board, using the McuOnEclipse components.


How to setup a project to use the McuOnEclipse components:
- create a bare metal project, with following components enabled/added
  - fsl_port
- copy the McuOnEclipse sources into the project:
  place the McuOnEclipse folder from https://github.com/ErichStyger/McuOnEclipseMcuOnEclipserary into the project root
- change the folder Properties > C/C++ Build and uncheck 'exclude from build'
- add the following folders to the compiler include path settings:
../McuOnEclipse/config
../McuOnEclipse/config/fonts
../McuOnEclipse/FatFS
../McuOnEclipse/fonts
../McuOnEclipse/FreeRTOS/Source/include
../McuOnEclipse/FreeRTOS/Source/portable/GCC/ARM_CM4F
../McuOnEclipse/SEGGER_RTT
../McuOnEclipse/SEGGER_Sysview
../McuOnEclipse/src
../McuOnEclipse/TraceRecorder
../McuOnEclipse/TraceRecorder/config
../McuOnEclipse/TraceRecorder/include
../McuOnEclipse/TraceRecorder/streamports/Jlink_RTT/include



#define McuMcuOnEclipse_CONFIG_CORTEX_M      (7)
  #define McuMcuOnEclipse_CONFIG_SDK_VERSION_USED  McuMcuOnEclipse_CONFIG_SDK_MCUXPRESSO_2_0

  
\todo
LEDPin1.c:
#include "fsl_port.h" /* include SDK header file for port muxing */
../McuOnEclipse/src/DbgRd1.c:69:12: fatal error: fsl_port.h: No such file or directory  