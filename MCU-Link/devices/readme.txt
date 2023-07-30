Directory for created devices for the LinkServer.
Files need to be placed into
C:\NXP\LinkServer<version>\devices
folder (if installed into the default place on Windows).

See 
https://mcuoneclipse.com/2023/05/14/linkserver-for-microcontrollers/


Cheat-Sheet:
linkserver flash K20:FRDM-K20 erase
linkserver flash K20:FRDM-K20 load c:\tmp\FRDM-K20_Blinky.elf
linkserver flash K20:FRDM-K20 load c:\tmp\FRDM-K20_BlinkyRed.bin --addr 0


