readme.txt
----------
This folder contains three different test projects to test the ROM bootloader on the FRDM-KL03Z.
They all have the BCA disabled (default BCA as with erased FLASH).
 
Example:
blhost --port COM9,19200 -d write-memory 0 "FRDM-KL03Z_LED_blue.bin"