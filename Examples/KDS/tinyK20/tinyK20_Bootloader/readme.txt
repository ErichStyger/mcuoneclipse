readme.txt
----------

Bootloader for tinyK20 board with Kinetis Design Studio v3.0.0.

Source files from
https://github.com/mbedmicro/CMSIS-DAP

See:  www.freescale.com/opensda

Notes:
- clear/check << EST
- added __NO_USB_LIB_C preprocessor
- added TARGET_MK20DX
- -fshort-wchar

Enter BOOTLOADER mode:
----------------------
Put PTB1 (pin 28 on package) to GND.

USB
1:GND ......... 10:B1