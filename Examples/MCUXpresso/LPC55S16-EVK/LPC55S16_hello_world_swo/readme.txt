Application with SWO and LPC55S16, including standard I/O redirection.

Running the J-Link SWO utility (command line), only supports sending data from the target:
JLinkSWOViewerCL -swoattach on -swofreq 4000000 -device LPC55S16 -itmport 0x0


Sending/receiving works with the on-board LinkServer.
NOTE: as of 26-Jan-23, SEGGER J-Link and PEMIRCO Multilink FX only can send data to the host, but not receiving it.

The McuSWO module in the McuLib does all the lifting, including muxing, and clock setting for tested/supported cores.

The source/IncludeMcuLibConfig.h configures the SWO, for example:
McuSWO_CONFIG_DO_SWO_INIT is set to 0 (do not initilize by application, but initialize by debugger)

Using it:
Set a breakpoint in main() *after* PL_Init(), as SWO muxing and SWO clocking has to be done first.
Then in the SWO Trace Config (menu Analysis > SWO Trace Config) check with the button the Target Clock speed.
Use the SWO ITM Console (menu Analysis > SWO ITM Console) and start recording with the 'play' button.
Continue running with the debugger: you should see the text output in the SWO ITM Console.
To enter text, you have to press the <ENTER> key at the end: then you should see the entered text shown in the console too.


Status:
- P&E and SEGGER: output works, input fails
- McuSWO dedicated routines work
- scanf() works
- printf(), putc() and putchar() ok
- getc() and getchar() ok
- redlib fails
- newlib and newlib-nano works (nohost)
- should use (none)

NOTE: Do not debug code, as it interfere with the debugger engine?