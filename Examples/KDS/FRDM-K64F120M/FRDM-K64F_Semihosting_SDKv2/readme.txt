readme.txt
----------

This is project demonstrating semihosting with the NXP FRDM-K64F baord and Kinetis Design Studio V3.2.0

- Exclude utilities/fsl_debug_console.c and utilities/fsl_sbrk.c from build
- only --specs=rdimon.specs in linker flags
- add SDK_DEBUGCONSOLE=0 to defines
- add #include <stdio.h> in fsl_debug_console.h
- remove call to BOARD_InitDebugConsole(); in main
- route semihosting to gdb in launch config


NOTE:
- after launching the debugger, when it is stopped in main(), the Semihosting console shall show something link this:
SEGGER J-Link GDB Server V6.00e - Terminal output channel
If this is NOT the case, this means that semihosting in Segger is *not* enabled.


See
https://mcuoneclipse.com/2016/04/09/semihosting-with-eclipse-and-the-nxp-kinetis-sdk-v2-0/