Example project for using gcov (GNU Coverage) and MCUXpresso IDE.

The project uses semihosting with File I/O, and this works in MCUXpresso IDE v10.2.0 with the following probes
- Segger J-Link (tested with OpenSDA)
- P&E Multilink Universal (assume it works with OpenSDA too)
- LPC-Link2 debug probe

It has confirmed working with the following libraries:
- newlib (semihosting)
- newlib-nano (semihosting)

It does *not* work currently with:
- redlib (semihosting) (fails in gcov_init(), as there is no list of constructor function pointers?). But file I/O works.
- redlib (semihost-mb) (dito)
additionally, redlib seems not to implement the needed coverage routines (would need standalone implementation)

Which gcov implementation is used is configured in gcov_support.h

Note that with FreeRTOS you should end the scheduler first with INCLUDE_vTaskEndScheduler before writing the coverage data.

See:
- https://mcuoneclipse.com/2017/06/18/adding-gnu-coverage-tools-to-eclipse/
- https://mcuoneclipse.com/2017/06/19/gnu-code-coverage-on-embedded-target-with-eclipse-neon-and-arm-gcc-5/

