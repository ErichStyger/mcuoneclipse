readme.txt
----------
This is a project implementing a LoRaWAN node using the NXP LPC55S16-EVK and the LoRa SX1261MB2xAS shield.
- https://www.nxp.com/design/development-boards/lpcxpresso-boards/lpcxpresso55s16-development-board:LPC55S16-EVK
- https://www.semtech.com/products/wireless-rf/lora-core/sx1261mb2bas
- https://os.mbed.com/components/SX126xMB2xAS/

Contributing:
- McuLib:    https://github.com/ErichStyger/McuOnEclipseLibrary/tree/master/lib
- LoRa/src:  https://github.com/Lora-net/LoRaMac-node

LoRaWAN Credentials:
Enter your data (App Key, Nwk Key, ...) in following file:
LoRa/src/peripherals/soft-se/se-identity.h
- LORAWAN_DEVICE_EUI
- APP_KEY
- NWK_KEY
