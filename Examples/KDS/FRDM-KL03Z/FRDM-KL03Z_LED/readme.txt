readme.txt
----------
'Blinky' project for FRDM-KL03Z with KDS V3.2.0 and Processor Expert, using SDK v1.3.

Bootloader mode is entered by pressing SW03 during power-on-reset.
SW3 to GND ==> SW_NMI_b ==> PTB5 (pin 19 on KL03Z16VFK4)

KL03Z Bootloader PinMux:
Port Signal 
PTB0 SPI0_SCK 
PTB1 LPUART0_TX 
PTB2 LPUART0_RX 
PTB3 I2C0_SCL 
PTB4 I2C0_SDA 
PTA5 SPI0_SS_b 
PTA6 SPI0_MISO 
PTA7 SPI0_MOSI

I2C bootloader connection is through:
PTB3: SCL (yellow wire, top postion on header)
PTB4: SDA (green wire, second position on header)

K22:
PTD3: SDA
PTD2: SCL


Example with bootloader running:
(power board with NMI (SW3) pressed)
C:\nxp\NXP_Kinetis_Bootloader_2_0_0\bin\Tools\blhost\win\blhost --port COM9 -d -- get-property 1
[5a a6]
<5a>
Ping responded in 1 attempt(s)
<a7>
<00 00 01 50 00 00 29 ae>
Framing protocol version = 0x50010000, options = 0x0
Inject command 'get-property'
[5a a4 0c 00 4b 33 07 00 00 02 01 00 00 00 00 00 00 00]
<5a>
<a1>
<5a>
<a4>
<0c 00>
<07 7a>
<a7 00 00 02 00 00 00 00 00 00 01 4b>
Successful response to command 'get-property(current-version)'
  - took 0.010 seconds
[5a a1]
Response status = 0 (0x0) Success.
Response word 1 = 1258356736 (0x4b010000)
Current Version = K1.0.0