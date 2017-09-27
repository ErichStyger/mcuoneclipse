readme.txt
----------
nRF24L01+ remote control:
-------------------------
Orientation: USB cable to the right
G: Center Button Joystick: remote on
F: remote off
E: start line following/maze

Music-Maker Shield on Robot:

Signal    Arduino Robo
--------------------------------------------------------
SPI CLK   D13     D7:NRF24_SPI1_CLK:PTB11
SPI MISO  D12     D9:NRF24_SPI_MISO:PTB17
SPI MOSI  D11     D8:NRF24_SPI_MOSI:PTB16

RST
SPK Shutdown
OFF
TX
RX
SD CD     D9      D13:D13:PTE3
MCS       D7      A0:A0:PTE2
DCS       D6      A1:MC13129_RESET:PTC1

SD CCS    D4      D4:SPI0_CLK_PTA15
DREQ      D3      A2:MC13192_CE:PTC0

Other pins:
A5:NRF24_CSN:PTB0
A4:NRF24_IRQ:PTB1
A3:NRF24_CE:PTB10
D2:US_TRIGGER:PTA5
D3:US_ECHO:PTA12

http://brettbeauregard.com/blog/2011/04/improving-the-beginner%E2%80%99s-pid-reset-windup/