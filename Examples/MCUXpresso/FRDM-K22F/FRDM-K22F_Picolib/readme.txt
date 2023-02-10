readme.txt
----------
Project for the FRDM-K22F using Piclib, see
https://mcuoneclipse.com/2023/02/05/debugging-embedded-targets-with-pyocd-and-eclipse/

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

disable managed linker script.

Linker flags: -specs=picolibc.specs
specs in 
C:\NXP\MCUXpressoIDE_11.7.0_9198\ide\tools\lib\gcc\arm-none-eabi\10.3.1

Options:
-specs=picolibc.specs
--defsym=vfprintf=__i_vfprintf
--defsym=vfscanf=__i_vfscanf
