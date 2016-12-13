readme.txt
----------
This is a demo program for the FRDM-K64F board with Eclipse Kepler, featuring the nRF24L01+ transceiver.
The board will blink the blue RGB LED every second to indicate to data is sent.
If the board receives a valid PING message from another board, the green RGB LED will blink.

See
http://mcuoneclipse.com/2014/07/01/tutorial-nordic-semiconductor-nrf24l01-with-the-freescale-frdm-k64f-board


nRF24L01 Header pins
--------------------
FRDM-K64F RevD:
- CE: PTC12
- SPI CLK: PTD5
- SPI MISO: PTD7
- CSN: PTD4
- SPI MOSI: PTD6
- IRQ: PTC18

FRDM-K64F RevE:
- CE: PTB20
- SPI CLK: PTD5
- SPI MISO: PTD7
- CSN: PTD4
- SPI MOSI: PTD6
- IRQ: PTC18
