readme.txt
----------
This is a project implementing a LoRaWAN node using the NXP LPC55S16-EVK and the LoRa SX1261MB2xAS shield.
- https://www.nxp.com/design/development-boards/lpcxpresso-boards/lpcxpresso55s16-development-board:LPC55S16-EVK
- https://www.semtech.com/products/wireless-rf/lora-core/sx1261mb2bas
- https://os.mbed.com/components/SX126xMB2xAS/

Alternatively, the SX1262MB2 can be used. This project is described in following blog article:
https://mcuoneclipse.com/2021/12/30/lorawan-with-nxp-lpc55s16-and-arm-cortex-m33/

Contributing:
- McuLib:    https://github.com/ErichStyger/McuOnEclipseLibrary/tree/master/lib
- LoRa/src:  https://github.com/Lora-net/LoRaMac-node

LoRaWAN Credentials:
Enter your data (App Key, Nwk Key, ...) in following file:
LoRa/src/peripherals/soft-se/se-identity.h
- LORAWAN_DEVICE_EUI
- APP_KEY
- NWK_KEY

Memory/NVMC Management:
See platform.h about the needed NVMC storage

For UART over the (J-Link or LinkServer) Debug virtual COM port (not possible if LoRa shield with OLED is used):
- JP9 (lower left corner, near PMod connector) has to be open, and JP12 (left of JP3/UART Header) needs to be closed, see https://mcuoneclipse.com/2021/12/30/lorawan-with-nxp-lpc55s16-and-arm-cortex-m33/
- Mux pin 92 (FC0_RXDA_SDA) and pin 94 (FC0_TXD_SCL) as FLEXCOMM0 in the pins tool

If using the LoRa Shield with OLED: use external J-Link for debug, power the board with EXT Usb

