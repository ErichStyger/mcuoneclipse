NOTE: this is still using the M4F FreeRTOS port.

Open points:
- merge CM33 port
- add extra defines
- secure heap handling
- RTT does not recognize the _SEGGER_RTT block
  	Range: 0x20000000 0x1000 (reported to Segger, not yet fixed in V7.20a)
- Drivers: I2C (HW), Flash Programming
- PL_CONFIG_USE_SWO
  With J-Link it changes the SWO baud, need to set it again with SWO_SetSpeed()
  
  Workaround:
  - init, set to 64k
  - Verify: McuSWO send hello
  - suspend
  - resume ITM console
  


For UART over the Debug port:
- JP9 (lower left corner, near PMod connector) has to be open
- Mux pin 92 (FC0_RXDA_SDA) and pin 94 (FC0_TXD_SCL) as FLEXCOMM
- Note UART Tx from host sometimes is garbled? Issue of J-Link firmware?

Article:
https://mcuoneclipse.com/2021/05/15/using-fatfs-and-minini-with-the-nxp-lpc55s16-evk/


Received monitor command: SWO DisableTarget 0xFFFFFFFF
SWO disabled successfully.
Received monitor command: SWO EnableTarget 0 64000 0x1 0
SWO enabled successfully.


Note: with J-Link version V7.22 or later it is possible to attach with SWO:
- [SWOViewer]: Added command line option "-swoattach <OnOff>" that disables all J-Link side initialization of SWO and relies on the target application to perform SWO init.
JLinkSWOViewerCL -swoattach on -swofreq 64000 -device LPC55S16 -itmport 0x1
