readme.txt
----------
Project with MCUXpresso IDE for the FRDM-K22F.
It uses USB CDC with FreeRTOS.

Important: you have to configure flow control (CTS/RTS) in a terminal like Termite!
Otherwise the terminal will block!


Ideas:
- use Rx/Tx ring buffer for UART
- send data blocks to CDC (UART to CDC)
- 1 Hz data rate
- stdio redirection
- use mstoTicks
- 

UART: use SDK_DEBUGCONSOLE=1

UART1: 
9600 configuration
115200  (GPS connection)
(interrupt mode)
Still delayed messages
400 bytes every second (with CR/LF at the end)
K22 80 MHz

SPI 3 MHz, 90 ms  (2-3 ms) 2048 bytes
Using SPI RTOS driver
==> make it faster

WriteSPI for each semaphore.
SPI_SendByte (SDK)
SPI bus should protect the semaphore

Memory problem with more tasks => multiple FreeRTOS heaps