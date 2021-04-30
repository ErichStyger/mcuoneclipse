NOTE: this is still using the M4F FreeRTOS port.

Open points:
- merge CM33 port
- add extra defines
- secure heap handling
- MCUGPIO muxing (warning)
- native UART support for Shell
- RTT does not recognize the _SEGGER_RTT block
  Range: 0x20000000 0x1000

- Drivers: UART, I2C, SPI (FatFS), Flash Programming