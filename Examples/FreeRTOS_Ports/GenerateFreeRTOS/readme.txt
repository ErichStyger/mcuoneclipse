readme.txt
==========
This project is used to generate differnt ports of FreeRTOS for different cores and toolchains.
This is useful for anyone who (for whatever reason?) does not want to use Processor Expert.
This project works 'as is' with the FRDM-KL25Z board.

Settings for CodeWarrior, FRDM-KL25Z board:
--------------------------------------
- Compiler: ARM gcc
- Manual Clock Values:
  configCPU_CLOCK_HZ: 20971520U
  configBUS_CLOCK_HZ: 20971520U
- Scheduler > Kinetis
  ARM Family: Cortex M0+
  Max SysCAll: 1 (or any value from 1-3)
  RTOS Interrupt Priority: 3 (lowest priority)

Settings for CodeWarrior, FRDM-K20D50M board:
--------------------------------------
- Compiler: ARM gcc
- Manual Clock Values:
  configCPU_CLOCK_HZ: 20971520U
  configBUS_CLOCK_HZ: 20971520U
- Scheduler > Kinetis
  ARM Family: Cortex M4
  Max SysCAll: 1 (or any value from 1-15)
  RTOS Interrupt Priority: 15 (lowest priority)
- Note that the user data section name for heap is ".user_data2"

Settings for IAR, KL25Z board:
------------------------------
- Compiler: ARM IAR
- Manual Clock Values:
  configCPU_CLOCK_HZ: 48000000u
  configBUS_CLOCK_HZ: 48000000u
- Scheduler > Kinetis
  ARM Family: Cortex M0+
  Max SysCAll: 1 (or any value from 1-3)
  RTOS Interrupt Priority: 3 (lowest priority)
 
Settings for Kinetis SDK (Ports are in ..\..\KSDK)
 - Compiler: ARM Keil
 - Port Folder: FreeRTOS\port\mdk
IAR:
 - Compiler: ARM IAR
 - Port Folder: FreeRTOS\port\iar
KDS/GCC:
 - Compiler: ARM gcc
 - Port Folder: FreeRTOS\port\gcc
 Produce config files:
 - compiler:
 - set configPEX_KINETIS_SDK to 1
 - tick rate 1000 Hz
 - memory scheme: 3
 
 How to use the generated files:
 -------------------------------
 The FreeRTOS port is generated inside the Generated_Code\FreeRTOS folder.
 You can copy the files into your project.
 Changing/configuring the RTOS is done inside FreeRTOSConfig.h 