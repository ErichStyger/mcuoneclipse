/* readme.txt */
Configurations:
this project comes with following Processor Expert configurations:
- JM128_RevA_noBL_ECUI_SPI: LCD demo, not enabled for bootloader
- JM128_RevA_BL_ECUI_SPI: same as above, but enabled for bootloader
- JM128_RevA_BL_TWR_I2C: application using the JM128 to send navitation switch messages to the I2C bus for a Tower CPU card.


Jumper settings for the TWR-LCD board:
--------------------------------------
JM128_RevA_noBL_ECUI_SPI and JM128_RevA_BL_ECUI_SPI: The settings are default, as the board is shipped:
1 (PS2)     : OFF  (SPI)
2 (PS1)     : ON   (SPI)
3 (JM_ELE)  : OFF  (SPI from JM128)
4 (EuSD)    : OFF  (uSD to JM128)
5 (SPI_SEL) : OFF  (SPI0 CS0 as chip select)
6 (TP_SEL)  : OFF  (Touch panel to JM128)
7 (BL_CNTRL): ON   (LCD backlight on)
8 (ELE_PWM0): OFF  (Buzzer to JM128)

JM128_RevA_BL_TWR_I2C, with CN128 driving display over FlexBus:
1 (PS2)     : ON   (FlexBus)
2 (PS1)     : OFF  (FlexBus)
3 (JM_ELE)  : ON   (Elevator controlling LCD)
4 (EuSD)    : OFF  (uSD to JM128)
5 (SPI_SEL) : OFF  (SPI0 CS0 as chip select)
6 (TP_SEL)  : ON   (Touch panel to elevator)
7 (BL_CNTRL): ON   (LCD backlight on)
8 (ELE_PWM0): ON   (Buzzer to elevator)

Settings for a Bootloader enabled applications
----------------------------------------------
The Processor Expert configuration name enables bootloader defines in Platform.h.
- stack size: 0x100 (or adjust to your needs)
- heap size: 0x20 (minimum)
- Memory Segment 0: start 0x4C00, size 0x1B3E0
- Memory Segment 1: Start 0x8001C0, size 0x3E40
- Fetch vectors from RAM, address 0x4800