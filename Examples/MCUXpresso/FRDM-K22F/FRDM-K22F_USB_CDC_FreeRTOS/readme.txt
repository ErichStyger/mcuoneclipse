readme.txt
----------
Project with MCUXpresso IDE for the FRDM-K22F.
It uses USB CDC with FreeRTOS.

Important: you have to configure flow control (CTS/RTS) in a terminal like Termite!
Otherwise the terminal will block.


Ideas:
- use Rx/Tx ring buffer for UART
- send data blocks to CDC (UART to CDC)
- 1 Hz data rate
- stdio redirection
- use mstoTicks
- 

UART: use SDK_DEBUGCONSOLE=1