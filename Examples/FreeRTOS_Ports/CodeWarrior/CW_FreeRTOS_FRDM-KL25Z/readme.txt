readme.txt
==========
FreeRTOS port for the FRDM-KL25Z board using CodeWarrior for MCU.
The RTOS port is inside the FreeRTOS subfolder inside the Sources folder.

To make the same for your own Kinetis-L project:
- Place the FreeRTOS folder into your project, and make sure the compiler finds the files and header files.
- in kinetis_sysinit.c:
  - add #include "FreeRTOS.h"
  - in the vector table, assign the interrupts used by the RTOS: 
    - /*SVC_Handler*/ vPortSVCHandler,
    - /*PendSV_Handler*/ vPortPendSVHandler
    - /*SysTick_Handler*/vPortTickHandler
- In FreeRTOSConfig.h you need to specify the CPU bus and clock speed:
    #define configCPU_CLOCK_HZ                        20971530U
    #define configBUS_CLOCK_HZ                        20971520U
- Update FreeRTOSConfig.h as needed to enable/disable RTOS functionality (see FreeRTOS.org)
  

