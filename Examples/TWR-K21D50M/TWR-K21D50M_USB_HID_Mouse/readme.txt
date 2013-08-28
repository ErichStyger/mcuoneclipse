readme.txt
==========

This project demonstrates USB Device HID Keyboard with a TWR-K21D50M.
Pressing SW2 will send a 'PrintScreen' request.

Important clock settings (to be confirmed):
CPU component:
- 48 MHz PLL
- PLL/FLL clock selection: PLL (48 MHz)

Init_USB component:
- use PLL/FLL as source
- multiplier/divider: both 1 to get 48 MHz
