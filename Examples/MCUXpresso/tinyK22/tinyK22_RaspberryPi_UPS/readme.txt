readme.txt
----------
Project for a tinyK22 board (NXP K22FN512) with a UPS board on the Raspberry Pi.
The application implements a shell interface through SEGGER RTT.

Configuration is in source/platform.h.
McuLib is configured in source/IncludeMcuLibConfig.h

See:
https://mcuoneclipse.com/2019/05/05/building-a-raspberry-pi-ups-and-serial-login-console-with-tinyk22-nxp-k22fn512/
Screensaver by Adafruit: https://learn.adafruit.com/animated-flying-toaster-oled-jewelry/code

Note: USB CDC requires flow control enabled (RTC/CTS) in the terminal program with a baud setting of 115200!
