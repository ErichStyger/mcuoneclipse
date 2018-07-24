readme.txt
----------

Example project for the i.MX RT1050 (1052) EVK using the LCD.

See
https://mcuoneclipse.com/2018/07/21/adding-a-rocktech-capacitive-touch-lcd-to-the-nxp-i-mx-rt1052-evk/


FreeRTOS notes:
- delete old freeRTOS
- delete Debug Folder
- copy McuOnEclipse FreeRTOS
- disable exclude from build
- get rid of Source directory structure
- ../FreeRTOS/portable/GCC/ARM_CM4F
  to includes
  
  set core to M7
  #define McuLib_CONFIG_CORTEX_M      (7)
  
- Add
  McuOnEclipse
    src
    config
 - copy McuLib.c/.h and config
 - copy McuRTOS.c/.h and config
 - copy McuUtility.c/.h and config
 - copy FreeRTOSconfig.h, remove original one
  and add config to includes
   ../McuOnEclipse/config
   ../McuOnEclipse/src
   and disable 'exclude from build'
   
Set SDK in McuLibConfig:
  #define McuLib_CONFIG_SDK_VERSION_USED  McuLib_CONFIG_SDK_MCUXPRESSO_2_0

    #define configUSE_SHELL                         (0)
  
  
  remove any existing hooks 
  vApplicationMallocFailedHook
  vApplicationStackOverflowHook
  vApplicationIdleHook
  and use the FreeRTOSHooks.c instead
  
  