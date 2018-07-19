Overview
========
The ELCDIF RGB project shows how to drive the RGB interface LCD using eLCDIF driver.
If this example runs correctly, a rectangle is moving in the screen, and the color
changes every time it reaches the edges of the screen.

The rectangle moving speed might be different with Debug target and Release target,
because these two targets spend different time to fill the frame buffer.

Toolchain supported
===================
- Keil MDK 5.24a
- IAR embedded Workbench 8.22.2
- GCC ARM Embedded 7-2017-q4-major
- MCUXpresso10.2.0

Hardware requirements
=====================
- Micro USB cable
- EVKB-IMXRT1050 board
- Personal Computer
- RK043FN02H-CT LCD board

Board settings
==============
1. Connect the RK043FN02H-CT board to J8.

Prepare the Demo
================
1.  Connect a USB cable between the host PC and the OpenSDA USB port on the target board. 
2.  Open a serial terminal with the following settings:
    - 115200 baud rate
    - 8 data bits
    - No parity
    - One stop bit
    - No flow control
3.  Download the program to the target board.
4.  Either press the reset button on your board or launch the debugger in your IDE to begin running the demo.

Running the demo
================
If this example runs correctly, a rectangle is moving in the screen, and the color
changes every time it reaches the edges of the screen.
Customization options
=====================

