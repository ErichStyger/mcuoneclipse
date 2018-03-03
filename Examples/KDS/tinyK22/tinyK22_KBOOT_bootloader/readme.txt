readme.txt
----------
This is a standalone port of the Kinetis Bootloader (KBOOT) for the tinyK22 board (alternatively, you can use the FRDM-K22F).

To connect to the bootloader, use the KinetisFlashTool with
- USB+HID, VID 0x15A2, PID 0x0073
- UART over OpenSDA, 57600 Baud
- I2C1: SCL PTC10, SDA PTC11 (BL_ENABLE_PINMUX_I2C1)

To enter bootloader mode:
- reset (after 5 seconds it will boot application if applicatin is present
- press bootloader pin (SW3 on FRDM-K22F) during power-on (SW3 is outermost push button near the target USB port)


C:\nxp\NXP_Kinetis_Bootloader_2_0_0\bin\Tools\blhost\win\blhost --port COM6 -d get-property 2

with a all the bootloader features enabled, it needs more than 64KByte of FLASH!
MK22F51212\bootloader_config.h can be used to reduce it (e.g. only to support UART),then the bootloader fits below 0x7FFF, with -O3 below 26 KByte.

Set application start address with BL_APP_VECTOR_TABLE_ADDRESS (bootloader_config.h)

blhost usage:
C:\nxp\NXP_Kinetis_Bootloader_2_0_0\bin\Tools\blhost\win\blhost.exe -p COM6 -- get-property 1

gives
Ping responded in 1 attempt(s)
Inject command 'get-property'
Response status = 0 (0x0) Success.
Response word 1 = 1258422272 (0x4b020000)
Current Version = K2.0.0