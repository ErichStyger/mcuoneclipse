readme.txt
----------
This is an example project for the Freescale Freedom board (Kinetis KL25Z Freedom Board).
Features:
- Using e-Gizmo HC-05 (EGBT) Bluetooth module
- Shell for AT commands
- Bluetooth module status output

The project settings has been set up to use the http://dx.com/p/jy-mcu-arduino-bluetooth-wireless-serial-port-module-104299
Connections:
- VCC: 3.3V (pin8 on J9)
- GND: GND (pin14 on J9)
- RXD: C4 (pin7 on J1)
- TXD: C3 (pin5 on J1)
Default pairing code is "1234"
Connection to the Bluetooth module is 9600 baud by default.

In addition, the red LED has been configured to use PWM so it is dimmable. 
The shell interface automatically has added a command to dimm it with the 'duty' command.

Toolchain: 
- CodeWarrior for MCU10.3

Components:
- Utility
- Wait
- Shell
- Bluetooth_EGBT

Known issues:
- Processor Expert SCI/SCI component has an issue that baud rate is not correct. See https://community.freescale.com/message/312027

More information: 
- http://mcuoneclipse.wordpress.com/
- http://mcuoneclipse.com/2013/02/14/bluetooth-with-the-freedom-board/
