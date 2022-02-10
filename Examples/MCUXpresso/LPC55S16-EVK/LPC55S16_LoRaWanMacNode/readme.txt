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

For UART over the (J-Link or LinkServer) Debug virtual COM port:
- JP9 (lower left corner, near PMod connector) has to be open, and JP12 (left of JP3/UART Header) needs to be closed, see https://mcuoneclipse.com/2021/12/30/lorawan-with-nxp-lpc55s16-and-arm-cortex-m33/
- Mux pin 92 (FC0_RXDA_SDA) and pin 94 (FC0_TXD_SCL) as FLEXCOMM0 in the pins tool

No rtos:
Application name   : periodic-uplink-lpp
Application version: 1.2.0
GitHub base version: 5.0.0

###### ===================================== ######

######   Board UUID: {0x00,0x1B,0x51,0xAF,0x8E,0x43,0x7A,0x5E,0xA6,0xB4,0x90,0xF0,0xCB,0x6C,0x78,0xBE}   ######


###### =========== CTXS RESTORED =========== ######
Size        : 1096

DevEui      : 70-B3-D5-7E-D0-04-98-67
JoinEui     : 00-00-00-00-00-00-00-00
Pin         : 00-00-00-00


###### =========== MLME-Request ============ ######
######               MLME_JOIN               ######
###### ===================================== ######
STATUS      : OK

###### =========== MLME-Confirm ============ ######
STATUS      : Tx timeout

###### =========== MLME-Request ============ ######
######               MLME_JOIN               ######
###### ===================================== ######
STATUS      : OK

###### =========== MLME-Confirm ============ ######
STATUS      : Rx 1 timeout

###### =========== MLME-Request ============ ######
######               MLME_JOIN               ######
###### ===================================== ######
STATUS      : OK

###### =========== MLME-Confirm ============ ######
STATUS      : OK
###### ===========   JOINED     ============ ######

OTAA

DevAddr     :  260B16C5


DATA RATE   : DR_0


###### ========== MLME-Indication ========== ######
STATUS      : OK

###### ============ CTXS STORED ============ ######
Size        : 1068


###### =========== MCPS-Request ============ ######
######           MCPS_UNCONFIRMED            ######
###### ===================================== ######
STATUS      : OK

###### =========== MCPS-Confirm ============ ######
STATUS      : OK

###### =====   UPLINK FRAME        1   ===== ######

CLASS       : A

TX PORT     : 0

DATA RATE   : DR_0
U/L FREQ    : 867900000
TX POWER    : 0
CHANNEL MASK: 00FF 


###### ========== MCPS-Indication ========== ######
STATUS      : OK

###### =====  DOWNLINK FRAME        1  ===== ######
RX WINDOW   : 1
RX PORT     : 1
RX DATA     : 
EE 

DATA RATE   : DR_0
RX RSSI     : -39
RX SNR      : 4


###### ============ CTXS STORED ============ ######
Size        : 452


###### =========== MCPS-Request ============ ######
######           MCPS_UNCONFIRMED            ######
###### ===================================== ######
STATUS      : OK

###### =========== MCPS-Confirm ============ ######
STATUS      : OK

###### =====   UPLINK FRAME        2   ===== ######

CLASS       : A

TX PORT     : 0

DATA RATE   : DR_0
U/L FREQ    : 867500000
TX POWER    : 0
CHANNEL MASK: 00FF 


###### ============ CTXS STORED ============ ######
Size        : 88

