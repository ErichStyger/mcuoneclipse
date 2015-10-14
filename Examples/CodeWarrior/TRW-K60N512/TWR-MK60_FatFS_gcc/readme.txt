readme.txt
----------
Project demonstrating FreeRTOS and FatFS on the TWR-K60N512 board.
It creates 4 LED tasks, each blinking an LED on the board, plus a main task which is using
a shell to communicate with the OpenJTAG USB CDT.

Toolchain: 
- CodeWarrior for MCU10.3 with the GNU ARM gcc compiler
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
- none