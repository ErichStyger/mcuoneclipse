readme.txt
----------

This project implements a 'blinky' with I2C OLED (SSD1306) support for the NXP LPC55S69 EVK.
Support for the OLED can be switched on/off in platform.h
The I2C connection to the OLED is configured in IncludeMcuLibConfig.h and i2clibconfig.h

The project supports direct connection to the OLED using the MikroE headers.
Otherwise the LoRa Shield created by Corsin Obrist can be used: Set PL_CONFIG_USE_LORA_SHIELD in IncludeLibConfig.h

Have fun :-)