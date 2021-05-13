NOTE: this is still using the M4F FreeRTOS port.

Open points:
- merge CM33 port
- add extra defines
- secure heap handling
- RTT does not recognize the _SEGGER_RTT block
  Range: 0x20000000 0x1000 (reported to Segger)
- Drivers: I2C, SPI (FatFS), Flash Programming
- SD & FatFS


For UART over the Debug port:
- JP9 (lower left corner, near PMod connector) has to be open
- Mux pin 92 (FC0_RXDA_SDA) and pin 94 (FC0_TXD_SCL) as FLEXCOMM
- Note Tx from host sometimes is garbled? Issue of J-Link firmware?