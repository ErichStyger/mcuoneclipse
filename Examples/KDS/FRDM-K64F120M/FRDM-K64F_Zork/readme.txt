readme.txt
----------
See https://mcuoneclipse.com/2018/12/02/playing-zork-with-freertos-on-arm-in-three-different-ways/

Background:
https://hackaday.com/2018/11/08/put-an-itsybitsy-zork-in-your-pocket/
https://github.com/devshane/zork

mcurses is from
https://github.com/ChrisMicro/mcurses


Configuration of the project is done in Sources/Zork/zork_config.h
If using FatFS with SD card, place the file Sources/Zork/dtextc.dat on the root of the SD card.


Make sure you have enough stack space allocated, if in doubt use 4-8 KByte.
