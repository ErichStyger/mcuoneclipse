readme.txt
----------
This is a standalone port of the Kinetis Bootloader (KBOOT) for the FRDM-K22F.

To connect to the bootloader, use the KinetisFlashTool with
- USB+HID, VID 0x15A2, PID 0x0073
- UART over OpenSDA, 57600 Baud

with a all the bootloader features enabled, it needs more than 64KByte of FLASH!
MK22F51212\bootloader_config.h can be used to reduce it (e.g. only to support UART),then the bootloader fits below 0x7FFF, with -O3 below 26 KByte..

Set application start address withi BL_APP_VECTOR_TABLE_ADDRESS (bootloader_config.h)

