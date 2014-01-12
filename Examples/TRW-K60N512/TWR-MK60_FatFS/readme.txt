readme.txt
----------
NOTE: this project is jusing the legacy Freescale ARM (NOT ARM GNU gcc!!!!).
The Freescale legacy compiler is *not* recommended for new design: Freescale has moved to use the ARM GNU gcc.

Project demonstrating FreeRTOS and FatFS on the TWR-K60N512 board.
It creates 4 LED tasks, each blinking an LED on the board, plus a main task which is using
a shell to communicate with the OpenJTAG USB CDT or TWR-SER RS-232 (38400 baud).
To switch between the OpenJTAG or TWR-SER connection, enable/disable the corresponding AS1 (Serial_LDD) component in the project.

Toolchain: 
- CodeWarrior for MCU10.3 with the Freescale ARM compiler
Components:
- FreeRTOS
- LED
- Utility
- FSShell
- RingBufferUInt8
- GenericTimeDate
- FAT_FileSystem
- FatFsMemSDHC
- Wait
- Timeout

See also:
- http://mcuoneclipse.com/2012/07/30/fatfs-with-kinetis/

Known issues
- there are several warnings (expression has no side effect) produced by the compiler because of missing casts in the Processor Expert generated code