readme.txt
----------

This is a RAM project for debugging the Seeed Studio Arch RT1052 (CVL5B) board ().

Notes:
- BOARD_InitBootPeripherals() currently causes a hard fault
- only works with a LPC-Link. Segger J-Link (Mini EDU) fails to properly debug the target.

