readme.txt
----------
This application implements a simple RNet demo with the FRDM-KL25Z board.
You can load the same software to two boards with a nRF24L01+ transceiver:
- Pressing the reset button on one board for less than one second sends the data value 1 to the other board
- Pressing the reset button for > 1 second will send the data value 2
- If the board receives the data value 1, it will toggle LED1 (Red RGB LED)
- If the board receives the data value 2, it will toggle LED2 (Green RGB LED)

See:
http://mcuoneclipse.com/2014/03/23/rnet-stack-as-component-nrf24l01-with-software-spi/