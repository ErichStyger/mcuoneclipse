readme.txt
----------

Port of the BusPal for the FRDM-KL25Z for Kinetis Design Studio.

Connect the FRDM-KL25Z to your host system and determine the virtual COM port (using COM6 in the examples below).

C:\nxp\NXP_Kinetis_Bootloader_2_0_0\bin\Tools\blhost\win\blhost --port COM6 --buspal i2c,0x10 -d get-property 1

BusPal muxing for FRDM-KL25Z:
UART0
  RX: PTA1
  TX: PTA2
  
SPI:
  CS: PTD0
  CLK: PTD1
  MOSI: PTD2
  MISO: PTD3
  
I2C0:
  SCL: PTC8
  SDA: PTC9



C:\nxp\NXP_Kinetis_Bootloader_2_0_0\bin\Tools\blhost\win>blhost --port COM6 --buspal i2c,0x10,2k --verbose -n -d get-property 1

