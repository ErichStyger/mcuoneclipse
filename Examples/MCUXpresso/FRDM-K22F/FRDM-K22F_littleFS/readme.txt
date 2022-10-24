readme.txt
----------
Project for the FRDM-K22F (NXP K22FN512) using the littleFS file system using a Winbond W25Q128 serial flash.
This project is siliar to the one presented in
https://mcuoneclipse.com/2019/01/06/driver-and-shell-for-winbond-w25q128-16mbyte-serial-flash-device/

If configured in platform.h (PL_CONFIG_IS_TINY_K22), the code can run on the tinyK22 board.

tinyK22:
	The SPI connection is configured inside source/IncludeMcuLibConfig.h using
	MCUSPI_CONFIG_HW_TEMPLATE_KINETIS_K22_SPI1
	The pins are configured for SPI in the Pins Tool:
	SPI CLK:  PTD5
	SPI SOUT: PTB16
	SPI SIN:  PTB17
	Configured and muxed by McuGPIO:
	SPI CS:   PTB18 (SPI1_PCS1 is NOT used. Instead, a normal GPIO pin with MCUSPI_CONFIG_HW_CS_GPIO is ocnfigured)

FRDM-K22F: using the RF 2x4 pin connnector near the SD Card
	MCUSPI_CONFIG_HW_TEMPLATE_KINETIS_K22_SPI0
	The pins are configured for SPI in the Pins Tool:
  SPI CLK:  PTD1
  SPI SOUT: PTD2
  SPI SIN:  PTD3
	Configured and muxed by McuGPIO:
	SPI CS:   PTD4 (SPI1_PCS1 is NOT used. Instead, a normal GPIO pin with MCUSPI_CONFIG_HW_CS_GPIO is ocnfigured)
  

Using it:
- connect with SEGGER RTT (RTTViewer) to the board
- 'McuW25 status' reports the device
- 'McuLittleFS format' to format the device
- 'McuLittleFS mount' to mount the device
- 'McuLittleFS benchmark' can be used to test the reading and writing to the device

