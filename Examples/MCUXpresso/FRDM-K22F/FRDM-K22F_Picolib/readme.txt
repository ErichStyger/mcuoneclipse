readme.txt
----------
Project for the FRDM-K22F using Piclib


Links:
https://github.com/picolibc/picolibc
https://keithp.com/picolibc/



gcc version:
C:\NXP\MCUXpressoIDE_11.7.0_9198\ide\tools\share\doc\gcc-arm-none-eabi
****************************************************
GNU Arm Embedded Toolchain 10.3-2021.10
****************************************************

Prebuilt libraries for GNU ARM Embedded:
https://keithp.com/picolibc/dist/gnu-arm-embedded/

Zip/backup C:\NXP\MCUXpressoIDE_11.7.0_9198\ide\tools

unpack the zip file there.

old:
arm-none-eabi-gcc -nostdlib -Xlinker -Map="FRDM-K22F_Picolib.map" -Xlinker --gc-sections -Xlinker -print-memory-usage -Xlinker --sort-section=alignment -Xlinker --cref -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -T FRDM-K22F_Picolib_Debug.ld -o "FRDM-K22F_Picolib.axf" ./utilities/fsl_assert.o ./utilities/fsl_debug_console.o ./utilities/fsl_str.o  ./startup/startup_mk22f51212.o  ./source/main.o ./source/semihost_hardfault.o  ./drivers/fsl_clock.o ./drivers/fsl_common.o ./drivers/fsl_common_arm.o ./drivers/fsl_gpio.o ./drivers/fsl_i2c.o ./drivers/fsl_rtc.o ./drivers/fsl_smc.o ./drivers/fsl_uart.o  ./device/system_MK22F51212.o  ./component/uart/fsl_adapter_uart.o  ./component/serial_manager/fsl_component_serial_manager.o ./component/serial_manager/fsl_component_serial_port_uart.o  ./component/lists/fsl_component_generic_list.o  ./board/board.o ./board/clock_config.o ./board/peripherals.o ./board/pin_mux.o   

disable managed linker script.

Linker flags: -specs=picolibc.specs
specs in 
C:\NXP\MCUXpressoIDE_11.7.0_9198\ide\tools\lib\gcc\arm-none-eabi\10.3.1


INCLUDE picolibc.ld
is in
C:\NXP\MCUXpressoIDE_11.7.0_9198\ide\tools\arm-none-eabi\picolibc\arm-none-eabi\lib\release


Picolib:
- disable managed linker file
- change linker file to pico....
- have ../picolib as path
- linker flags:
  -specs=picolibc.specs


https://github.com/picolibc/picolibc/blob/main/doc/printf.md
newlib (full), semihost:
Memory region         Used Size  Region Size  %age Used
   PROGRAM_FLASH:       37924 B       512 KB      7.23%
      SRAM_UPPER:       10840 B        64 KB     16.54%
      SRAM_LOWER:          0 GB        64 KB      0.00%

NewLib-nano with float/double, semihost
Memory region         Used Size  Region Size  %age Used
   PROGRAM_FLASH:       29440 B       512 KB      5.62%
      SRAM_UPPER:        8784 B        64 KB     13.40%
      SRAM_LOWER:          0 GB        64 KB      0.00%

Redlib, semihost
Memory region         Used Size  Region Size  %age Used
   PROGRAM_FLASH:       15136 B       512 KB      2.89%
      SRAM_UPPER:        8732 B        64 KB     13.32%
      SRAM_LOWER:          0 GB        64 KB      0.00%


NewLib-nano with without float/double, semihost
Memory region         Used Size  Region Size  %age Used
   PROGRAM_FLASH:       10368 B       512 KB      1.98%
      SRAM_UPPER:        8416 B        64 KB     12.84%
      SRAM_LOWER:          0 GB        64 KB      0.00%


Picolib float/double:

arm-none-eabi-gcc -nostdlib -specs=picolibc.specs -Xlinker -Map="FRDM-K22F_Picolib.map" -Xlinker --gc-sections -Xlinker -print-memory-usage -Xlinker --sort-section=alignment -Xlinker --cref -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -T Picolib_Debug.ld -L ../picolib -o "FRDM-K22F_Picolib.axf" ./utilities/fsl_assert.o ./utilities/fsl_debug_console.o ./utilities/fsl_str.o  ./startup/startup_mk22f51212.o  ./source/main.o ./source/semihost_hardfault.o  ./drivers/fsl_clock.o ./drivers/fsl_common.o ./drivers/fsl_common_arm.o ./drivers/fsl_gpio.o ./drivers/fsl_i2c.o ./drivers/fsl_rtc.o ./drivers/fsl_smc.o ./drivers/fsl_uart.o  ./device/system_MK22F51212.o  ./component/uart/fsl_adapter_uart.o  ./component/serial_manager/fsl_component_serial_manager.o ./component/serial_manager/fsl_component_serial_port_uart.o  ./component/lists/fsl_component_generic_list.o  ./board/board.o ./board/clock_config.o ./board/peripherals.o ./board/pin_mux.o   
__d_vprintf 2.68 KB
Memory region         Used Size  Region Size  %age Used
   PROGRAM_FLASH:       12376 B       512 KB      2.36%
      SRAM_UPPER:        8256 B        64 KB     12.60%
      SRAM_LOWER:          0 GB        64 KB      0.00%

--defsym=vfprintf=__i_vfprintf
arm-none-eabi-gcc -nostdlib -specs=picolibc.specs -Xlinker -Map="FRDM-K22F_Picolib.map" -Xlinker --gc-sections -Xlinker -print-memory-usage -Xlinker --sort-section=alignment -Xlinker --cref -Xlinker --defsym=vfprintf=__i_vfprintf -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -T Picolib_Debug.ld -L ../picolib -o "FRDM-K22F_Picolib.axf" ./utilities/fsl_assert.o ./utilities/fsl_debug_console.o ./utilities/fsl_str.o  ./startup/startup_mk22f51212.o  ./source/main.o ./source/semihost_hardfault.o  ./drivers/fsl_clock.o ./drivers/fsl_common.o ./drivers/fsl_common_arm.o ./drivers/fsl_gpio.o ./drivers/fsl_i2c.o ./drivers/fsl_rtc.o ./drivers/fsl_smc.o ./drivers/fsl_uart.o  ./device/system_MK22F51212.o  ./component/uart/fsl_adapter_uart.o  ./component/serial_manager/fsl_component_serial_manager.o ./component/serial_manager/fsl_component_serial_port_uart.o  ./component/lists/fsl_component_generic_list.o  ./board/board.o ./board/clock_config.o ./board/peripherals.o ./board/pin_mux.o   
Memory region         Used Size  Region Size  %age Used
   PROGRAM_FLASH:        6408 B       512 KB      1.22%
      SRAM_UPPER:        8256 B        64 KB     12.60%
      SRAM_LOWER:          0 GB        64 KB      0.00%

-specs=picolibc.specs
--defsym=vfprintf=__i_vfprintf

/build/picolibc/builds/build-arm-tk/../../newlib/libc/picolib/picosbrk.c:49: undefined reference to `__heap_start'
