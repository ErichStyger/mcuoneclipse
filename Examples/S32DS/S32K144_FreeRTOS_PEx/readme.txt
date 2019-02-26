readme.txt
----------

This project shows how to use the McuOnEclipse Processor Expert FreeRTOS component with S32DS.

See
https://mcuoneclipse.com/2018/07/01/tutorial-freertos-10-0-1-with-nxp-s32-design-studio-2018-r1/


How to use the McuOnEclipse FreeRTOS with the S32 SDK OSIF (OS-Interface):
a) name the FreeRTOS component as 'FreeRTOS'
b) in the FreeRTOS component setting, use 'Custom Port' with 'Source Folders' enabled. 
  'Manual Clock Values' disabled
c) This generates FreeRTOS into folders inside the Generated_Code. 
  So you have to add the following to the compiler include path settings:
../Generated_Code/FreeRTOS/Source/include
../Generated_Code/FreeRTOS/config/gcc
../Generated_Code/FreeRTOS/Source/portable/GCC/ARM_CM4F
d) before including events.c, include FreeRTOS.h and task.h
#include "FreeRTOS.h"
#include "task.h"
#include "Events.h"
#include "Events.c"
e) add the following define to the compiler preprocessor settings:
USING_OS_FREERTOS


NOTE:
The subfolder 'SDK' in the project has been removed as the NXP SDK for S32 does not grant redistribution rights.
So you have to add that folder from your SDK locally.
