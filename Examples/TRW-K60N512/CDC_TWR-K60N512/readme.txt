readme.txt
----------
This project demonstrates the USB CDC class for the TWR-K60N512 board with the TWR-SER board.
It echoes the characters received on the USB CDC port, plus on the serial port on the TWR-SER.
The USB CDC driver .inf files are generated into the Documentation sub folder.

- CPU (or more precisely: the USB block) needs to run at 24 MHz
- USBInit:
  - Clock gate: Enabled
  - Interrupt request: Disabled (it gets enabled later)