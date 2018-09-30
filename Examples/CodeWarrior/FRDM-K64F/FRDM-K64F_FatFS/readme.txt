readme.txt
----------
Project for CodeWarrior for MCU 10.x using the SD card on the FRDM-K64F board.
The project includes a Shell which communicates to the OpenSDA UART (USB CDC) with 38400 baud.

The project offers three different ways to communicate with the SD card:
- SPI (Syncromaster)
- SPI_LDD (SPIMaster_LDD)
- SDHC (FatFsMemSDHC)

NOTE:
for SDHC to work on the K64F the MPU has to be turned OFF!
The latest SDHC component has a setting to turn it off (in the Init()), otherwise add the following to your application:

#if 1 // FATM1_CONFIG_DISABLE_MPU
  MPU_CESR = 0; /* K64F has memory protection unit, disable it! */
#endif
