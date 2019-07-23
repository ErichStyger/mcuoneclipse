Overview
========
The CSI CCIR656 project shows how to receive the camera data using CSI driver,
the camera interface is CCIR656. In this example, you will see the camera input
image shown in the LCD. Please note that the camera input image resolution
might be smaller than the LCD panel, so part of the LCD panel might be blank.
Hardware requirements
=====================
- Mini/micro USB cable
- EVK-MIMXRT1060 board
- Personal Computer
- RK043FN02H-CT LCD board
- MT9M114 module
This example supports OV7725 too, if OV7725 is used, then MT9M114 is not necessary.

Board settings
==============
1. Connect the RK043FN02H-CT board.
2. Connect the MT9M114 or OV7725 camera module.

Prepare the Demo
================
1.  Connect a USB cable between the host PC and the OpenSDA USB port on the target board. 
2.  Open a serial terminal with the following settings:
    - 115200 baud rate
    - 8 data bits
    - No parity
    - One stop bit
    - No flow control
4.  Download the program to the target board.
5.  Launch the debugger in your IDE to begin running the demo.

Note: If OV7725 is used, change the macro APP_CAMERA_TYPE to APP_CAMERA_OV7725 in
csi_ccir656.c.

Running the demo
================
When the demo runs successfully, the camera received pictures are shown in the LCD.

Toolchain supported
===================
- IAR embedded Workbench  8.32.1
- Keil MDK  5.26
- GCC ARM Embedded  7.3.1
- MCUXpresso 10.3.0

