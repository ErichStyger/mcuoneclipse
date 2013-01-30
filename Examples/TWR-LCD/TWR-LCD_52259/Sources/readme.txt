readme.txt
==========

This configuration is using the TWR-MCF52259 CPU to drive the TWR-LCD. The 52259 is controlling the LCD with 16bit parallel (mini-FlexBus) 
connection.
It features the microSD card demo. However, as the pins for the microSD card are shared with the accelerometer, the accelerometer demo is 
not possible.
NOTE: in order to use the microSD card detection pin, it needs a pull-up. As such, you need to drive the card detection pin on the JM128 side 
with an internal pull-up, otherwise U5A input is floating.

TRW-LCD SW1 settings:
1: OFF (PS2) (OFF: SPI)
2: ON  (PS1) (ON: SPI)
3: ON (JM_ELE) (ON: CPU access through primary elevator connector, not on-board JM128)
4: ON (EuSD) (ON: MicroSD is connected
5: ON  (SPI_SEL) (ON: use SPI0 CS1)
6: OFF  (TP_SEL) (OFF: Enable MCF51JM connection to the touch panel)
7: ON  (BL_CNTRL)
8: ON (ELE_PWM0)

TRW-LCD SW5:  all ON

TWR-52259:
- TXD_SEL: 1-2
- RXD_SEL: 1-2
