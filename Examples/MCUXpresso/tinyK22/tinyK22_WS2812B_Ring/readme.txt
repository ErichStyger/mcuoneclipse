readme.txt
----------
Project for a tinyK22 board (NXP K22FN512VLH12) with with FreeRTOS running a ring of WS2812B.

WS2818B data: GPIOD (PTD0...PTD7)
RS-485:       EN (PTB19=> UART0 RTS/PTB2, high active for tx), UART0 TX (PTB17), RX (PTB16)
I2C:
OpenSDA UART: LPUART Rx PTC3, Tx PTC4


Open Points
-----------
- LED timer too fast?
- flash programming K22
- watchdog K22


Example commands
================
In terminal with RS-485-2-USB converter (virtual address 0x2):
----------------------------------------
@0x10 2 cmd rs help

@x20 2 cmd matrix q 0 0 1 a 90 10 sh
@x20 2 cmd matrix q 0 0 0 a 270 10 sh
@x0 2 cmd matrix exq

From Master (tinyK22) (address 0x1):
-----------------
rs sendcmd 0x20 rs help

Example hand immediate move (without leds):
rs sendcmd 0x20 matrix r 0 0 0 180 10 cw

rs sendcmd 0x20 matrix q 0 0 0 r 90 8 cc
rs sendcmd 0x20 matrix exq

matrix R 0 0 0 90 2 cw
matrix R 0 0 0 90 2 CC
matrix R 0 0 0 360 1 CW

Issues:
-------
- Problem: STEPBOARD_NormalizePosition() kann race condition generieren! (disabled for now)
- need to use semaphore to matrix queue execution task instead of global variable
- matrix R 0 4 0 360 3 CW
  led is behind, while
  matrix R 0 4 0 360 3 CC
  is ahead?
 - sometimes communication errors? Resistors?
 - measure current
 - after POR, DMA blinky? Goes away after shell interaction? happened after switching from 96 MHz to 120 MHz?
 