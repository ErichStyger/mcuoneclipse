readme.txt
----------
Project for CodeWarrior for MCU 10.x using the SD card on the FRDM-K64F board.
The project includes a Shell which communicates to the OpenSDA UART (USB CDC) with 38400 baud.

NOTE:
Somehow this project does not run CodeWarrior (tried with CW for MCU10.7 and 11.0.
It gives an error when mounting the SD card:
CMD> ERROR: mount failed: (1) A hard error occurred in the low level disk I/O layer
The same project runs fine with KDS 3.2.0, so I suspect this might be a compiler issue?

Using SPI access works fine too.



