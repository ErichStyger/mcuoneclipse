readme.txt
==========

This configuration is using the TWR-CN128 CPU to drive the TWR-LCD.
The CN128 is controlling the LCD with 16bit parallel (mini-FlexBus) connection.
As UI the Embedded Component UI is used. A demo features using the accelerometer to change the display orientation. However, 
as the pins are shared with the microSD card connection, the SD card demo is not available.

TRW-LCD SW1 settings:
1: ON  (PS2), Flexbus
2: OFF (PS1), FlexBus
3: ON  (JM_ELE), Elevator controlling LCD
4: OFF (EuSD), no microSD on Elevator
5: ON  (SPI_SEL), SPI0 CS1, but don't care for mini-Flexbus
6: OFF (TP_SEL), TP to elevator
7: ON  (BL_CNTRL), BL on
8: ON  (ELE_PWM0), Buzzer on elevator

TRW-LCD SW5: all ON

TWR-CN128 Jumper settings:
- TXD_SEL: 1-2
- RXD_SEL: 1-2
- LATCH_SEL: 2-3
- ANA-ISO: all removed (connect signals to elevator)
- ADP3_SEL: 1-2
- J5:
 * 1-2 & 3-4 installed
 * LED2_ISO, LED1_ISO removed
 * Z_ISO, Y_ISO and X_ISO installed (Accelerometer used by CN128)
