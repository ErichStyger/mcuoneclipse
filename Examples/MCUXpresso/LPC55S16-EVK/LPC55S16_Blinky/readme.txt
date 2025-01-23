readme.txt
----------

For UART over the (J-Link or LinkServer) Debug virtual COM port:
- JP9 (lower left corner, near PMod connector) has to be *open*, and JP12 (left of JP3/UART Header) needs to be *closed*, 
  see https://mcuoneclipse.com/2024/10/20/on-target-testing-with-linkserver-runner-and-vs-code/ with
  https://mcuoneclipse.com/wp-content/uploads/2024/10/lpc55s16-evk-with-on-board-debug-probe.jpg
- Mux pin 92 (FC0_RXDA_SDA) and pin 94 (FC0_TXD_SCL) as FLEXCOMM0 in the pins tool

- PL_CONFIG_USE_SWO
  Start the J-Link SWO viewer in 'attach mode' on port 0:
  JLinkSWOViewerCL -swoattach on -swofreq 64000 -device LPC55S16 -itmport 0x0
  Match the swofreq to the baud configured for SWO.
  SWO baud rate is configured with McuSWO_CONFIG_SPEED_BAUD.
  

Notes:
with J-Link version V7.22 or later it is possible to attach with SWO so it does not change the SWO:
- [SWOViewer]: Added command line option "-swoattach <OnOff>" that disables all J-Link side initialization of SWO and relies on the target application to perform SWO init.
JLinkSWOViewerCL -swoattach on -swofreq 5625000 -device LPC55S16 -itmport 0x0
  See: https://mcuoneclipse.com/2021/07/12/standalone-swo/
  Note: J-Link is able to deal with a SWO frequency up to 5625 kHz.

The IDE 11.5.0 has standalone SWO functionality too, see https://mcuoneclipse.com/2022/01/24/mcuxpresso-ide-11-5-0/


Upgrade/Change Debug Firmware
-----------------------------
JP6 is DFU jumper, located near the LINK2 USB Connector.
Power Cycle the board.
run script in LPCScrypt*\scripts

Open points:
- merge CM33 port
- secure heap handling

Articles:
- https://mcuoneclipse.com/2021/05/15/using-fatfs-and-minini-with-the-nxp-lpc55s16-evk/
