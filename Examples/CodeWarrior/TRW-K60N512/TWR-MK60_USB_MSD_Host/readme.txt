readme.txt
----------
This project implements USB MSD host stack for the TWR-K60N512 board.

The application communicates with a shell over the OSJTAG USB CDC connection
(the same USB port for OJTAG debugging on the TWR-K60 card)

TWR-SER Jumper settings:
- J10 (VBDEV): 1-2 (supply 5V to bus, host mode)
- J16 (USB mode): 1-2 (host mode)
