readme.txt
----------

Board: NXP LPC55S16-EVK
https://www.nxp.com/design/development-boards/lpcxpresso-boards/lpcxpresso55s16-development-board:LPC55S16-EVK

Shield:
SX1261MB2BAS Shield (Mouser 947-SX1261MB2BAS)
https://www.semtech.com/products/wireless-rf/lora-core/sx1261mb2bas


Pins:
----------------------------------------------------------
Shield        LPC Header            LPC55S16
----------------------------------------------------------
- BUSY        ARD_LEDB_PWM          Pin 5, PIO1_6, input 
- DIO1        ARD_LEDR_PWM          Pin 1, PIO1_4, input
- NSS         ARD_BTN_USR_P1_9      Pin 10, PIO1_9, output (pull-up 100k)

- ANT_SW      ARD_P1_8              Pin 24, PIO1_8
- D9          ARD_MIK_P1_5
- D10         ARD_MIK_HSSPI_SSEL1
- MOSI        ARD_MIK_HSSPI_MOSI    Pin 60, PIO0_26
- MISO        ARD_MIK_HSSPI_MISO    Pin 62, PIO1_3
- SCK         ARD_MIK_HSSPI_SCK     Pin 61, PIO1_2
- I2C_SDA     ARD_MIK_FC4_I2C_SDA
- I2C_SCL     ARD_MIK_FC4_I2C_SCL

- A6          FC1_I2C_SCL
- A5          FC1_I2C_SDA
- OPT         EXP_MCLK
- DEVICE_SEL  ARD_CMP0_IN_A         Pin 54, PIO0_0, input
- SX_NRESET   ARD_MIK_ADC0_8_N      Pin 14, PIO0_16, output