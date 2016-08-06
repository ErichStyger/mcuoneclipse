readme.txt
----------

RadioHead project for NXP FRDM-KL25Z:
- Arduino Joystick shield with nRF24L01+ module
- FRDM-KL25Z with Adafruit RFM9X LoRa Module (https://learn.adafruit.com/adafruit-rfm69hcw-and-rfm96-rfm95-rfm98-lora-packet-padio-breakouts/pinouts)

Switch between transceivern is in Platform.h

RH    nRF24L01+   LoRa (RFM9X)
------------------------------
ISR0              G0 PTA13
CE    CE  PTD5
SS    CSN PTD0    CS PTD0
SPI   SPI0          SPI0
MISO  PTD3        MISO PTD3
MOSI  PTD2        MOSI PTD2
SCLK  PTD1        SCK  PTD1