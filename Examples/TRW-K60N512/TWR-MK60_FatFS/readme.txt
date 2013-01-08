readme.txt
----------
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

See
- http://mcuoneclipse.com/2012/09/07/tutorial-enlighting-the-freedom-kl25z-board/

Known issues
- there are 5 warnings (expression has no side effect) produced by the compiler because of missing casts in the Processor Expert generated code