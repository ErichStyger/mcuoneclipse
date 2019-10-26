readme.txt
----------

Project with MCUXpresso IDE, MCUXpresso SDK and the McuLib for the Adafruit LCD display with capacitive touch.

2.8" TFT Touch Shield for Arduino w/Capacitive Touch (I2C):
https://www.adafruit.com/product/1947

https://github.com/adafruit/Adafruit-2.8-TFT-Shield-v2-PCB

Featherwing LCD:
https://www.adafruit.com/product/3315

ILI9341 LCD:
https://github.com/adafruit/Adafruit_ILI9341

Capacitive touch controller (FT6206):
https://github.com/adafruit/Adafruit_FT6206_Library

Resistive touch controller: 
https://github.com/adafruit/Adafruit_STMPE610

Pin Connections:
LPC55S69-EVK      Adafruit board (#1947)
GND               GND 
LSPI_HS_SCK       D13 SCLK_5V
LSPI_HS_MISO      D12 MISO
LSPI_HS_MOSI      D11 MOSI_5V
LSPI_HS_SSEL1     D10 TFT_CS_5V
PIO1_5_GPIO_ARD   D9  TFT_DC_5V
PIO1_8_GPIO_ARD   D8  (RT_CS_5V)

Open points:
- use C33 port (currently M4F)
- merge back GUI with Raspberry Pi project
- use HW I2C
- implement display and touch orientation

