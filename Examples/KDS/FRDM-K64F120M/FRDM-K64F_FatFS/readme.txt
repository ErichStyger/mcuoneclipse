readme.txt
----------
This is a demo program for the FRDM-K64F board with Eclipse (Kinetis Design Studio V3.2.0) using the SD card.

It can use SPI or SDHC for the SD card.
Note that for the SDHC the driver will have to disable the MPU in the FatFsMemSDHC initialization routine:
MPU_CESR = 0; /* K64F has memory protection unit, disable it! */
