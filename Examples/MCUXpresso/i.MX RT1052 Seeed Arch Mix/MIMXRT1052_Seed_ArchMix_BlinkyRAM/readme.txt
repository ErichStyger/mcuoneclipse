readme.txt
----------

This is a RAM project for debugging the Seeed Studio Arch RT1052 (CVL5B) board ().

Notes:
- BOARD_InitBootPeripherals() currently causes a hard fault
- only works with a LPC-Link. Segger J-Link (Mini EDU) fails to properly debug the target.

Arch Mix: IS25WP064

i.MX RT1021 board:
- 64 MBit (8 MByte) QSPI Flash (U13, IS25LP064A-JBLE)
64 MBit (8 MByte) QSPI Flash (U13, S25LP064A-JBLE):
0x60000000 size 0x800000
MIMXRT1020-EVK_IS25LP064.cfx