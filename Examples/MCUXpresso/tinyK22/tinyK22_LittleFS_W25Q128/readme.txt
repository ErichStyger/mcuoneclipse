readme.txt
----------
Project for the tinyK22 (NXP K22FN512) siliar to the project presented in
https://mcuoneclipse.com/2019/01/06/driver-and-shell-for-winbond-w25q128-16mbyte-serial-flash-device/
using littleFS with the Winbond W25Q128 SPI flash.

The SPI connection is configured inside source/IncludeMcuLibConfig.h using
MCUSPI_CONFIG_HW_TEMPLATE_KINETIS_K22_SPI1
The pins are configured for SPI in the Pins Tool:
SPI CLK:  PTD5
SPI SOUT: PTB16
SPI SIN:  PTB17
SPI CS:   PTE0 (SPI1_PCS1)
