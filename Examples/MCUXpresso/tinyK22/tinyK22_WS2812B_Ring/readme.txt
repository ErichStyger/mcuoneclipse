readme.txt
----------
Project for a tinyK22 board (NXP K22FN512VLH12) with with FreeRTOS running a ring of WS2812B.

WS2818B data: GPIOD (PTD0...PTD7)
RS-485:       EN (PTB19=> UART0 RTS/PTB2, high active for tx), UART0 TX (PTB17), RX (PTB16)
I2C:
OpenSDA UART: LPUART Rx PTC3, Tx PTC4


Open Points
-----------
- buffering/timeout for RTT shell output
- LED timer too fast/slow?
- flash programming
- watchdog


Example commands
================
In terminal with RS-485-2-USB converter (virtual address 0x2):
----------------------------------------
@0x10 0x29 cmd rs help

@x20 2 cmd matrix q 0 0 1 a 90 10 sh
@x20 2 cmd matrix q 0 0 0 a 270 10 sh
@x0 2 cmd matrix exq

In tinyK22 (address 0x1):
-----------------
rs sendcmd 0x10 rs help

Example clock move:
rs sendcmd 0x20 matrix r 0 0 0 180 10 cw
