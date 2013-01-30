Readme.txt
==========

This project uses the TWR-LCD board with the MCF52259 as master using the display.
The onboard serial connector is used for a shell interface.

TWR-MCF52259 Settings:
- LED1_ISO removed (conflicts with buzzer, we use buzzer)

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

TRW-LCD SW5: all ON

Interrupt settings
==================
On the MCF52259, two interrupts shall not share the same level/priority, otherwise strange things can happen.
See the generated vectors.c for the interrupts already used.
