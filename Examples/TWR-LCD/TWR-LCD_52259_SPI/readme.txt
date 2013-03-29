Readme.txt
==========

This project uses the TWR-LCD board with the MCF52259 as master using the display over SPI.

TWR-LCD Settings:
=================
TRW-LCD SW1 settings:
1: OFF (PS2), SPI
2: ON  (PS1), SPI
3: ON  (JM_ELE), Elevator controlling LCD
4: OFF (EuSD), no microSD on Elevator
5: ON  (SPI_SEL), SPI0 CS1, but don't care for mini-Flexbus
6: OFF (TP_SEL), TP to elevator
7: ON  (BL_CNTRL), BL on
8: ON  (ELE_PWM0), Buzzer on elevator

Remove:
- X_ISO, Y_ISO, Z_ISO, POT_ISO (remove connection to accelerometer, conflicts with analog touch screen lines) 

TRW-LCD SW5: all ON
