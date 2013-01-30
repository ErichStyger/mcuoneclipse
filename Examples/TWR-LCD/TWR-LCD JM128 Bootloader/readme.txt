/* readme.txt */
Jumper settings for the TWR-LCD board, using JM128 standalone and in bootloader mode:
The settings are default, as the board is shipped:
(OFF means switch is to the board boarder side)
1:OFF  (SPI to display)
2:ON   (SPI to display)
3:OFF  (SPI from JM128)
4:OFF  (uSD to JM128)
5:OFF  (SPI0 CS0 as chip select)
6:OFF  (Touch screen by JM128)
7:ON   (LCD backlight on)
8:OFF  (Buzzer to JM128)

This project implements a bootloader for the MCF51JM128 on the TWR-LCD board.
If there is no application flashed, or the user presses SW4/BTLD switch during startup,
the application will prompt a message on the screen and enumerates as a mass storage device.
Then you can drag&drop a new S19 file to the device and the application part will be flashed with the new application.

CPU component settings:
- Stack size: 0x300
- RAM/ROM Segments:
    Segment 0:
      Start: 0x410
      Size: 0x43F0
    Segment 1:
      Start: 0x800000
      Size:  0xA00
- User Data Initialization:
  #include "Bootloader.h"
- User code before PE initialization:
  BL_CheckForUserApp(); /* check if we shall directly call the user app */
