Application with SWO and LPC55S16, including standard I/O redirection.

JLinkSWOViewerCL -swoattach on -swofreq 4000000 -device LPC55S16 -itmport 0x0


With the MCUXpresso IDE Debugger:
set McuSWO_CONFIG_DO_SWO_INIT to 0 (do not initilize by application, but initialize by debugger)

