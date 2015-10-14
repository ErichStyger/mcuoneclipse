readme.txt
----------
Project demonstrating usage of I2C component for the FRDM-KL25Z in combination with the Arduino Data Logger board.
It allows to dump I2C device memory. On the I2C1 bus there is the Maxim RTC, but other devics on this bus can be inspected.
As shell interface the OpenSDA USB CDC is used. 

Toolchain: 
- CodeWarrior for MCU10.3
Components:
- LED
- Wait
- GenericI2C
- RTC_Maxim
- I2CSpy
- Shell

See also:
- http://mcuoneclipse.com/2012/12/23/csi-crime-scene-investigation-with-i2cspy-and-freedom-board/
- http://mcuoneclipse.com/2012/11/18/arduino-data-logger-shield-with-the-frdm-kl25z-board/ 
