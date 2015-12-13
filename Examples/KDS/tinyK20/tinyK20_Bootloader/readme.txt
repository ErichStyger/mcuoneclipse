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

Program Bootloader:
- flash tinyK20_bl_0x0000-0x4FFF.s19
Enter BOOTLOADER mode:
----------------------
Put PTB1 (pin 28 on package, pin between C and clock below uC) to GND.

+5 PTD7 PTD6 PTD5
<-USB     uC    SWD
1:GND ......... 10:B1