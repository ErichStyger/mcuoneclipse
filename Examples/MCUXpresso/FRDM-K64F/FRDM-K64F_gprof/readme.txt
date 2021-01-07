Example project for using gprof(GNU Profiling and MCUXpresso IDE.

The project uses semihosting with File I/O, and this works in MCUXpresso IDE v11.2.1 with the following probes
- Segger J-Link (tested with OpenSDA)
- P&E Multilink Universal (assume it works with OpenSDA too)
- LPC-Link2 debug probe

It has confirmed working with the following libraries:
- newlib (semihost)

See:
- https://mcuoneclipse.com/2015/08/23/tutorial-using-gnu-profiling-gprof-with-arm-cortex-m/


Profiling (per file) option: -pg
 
 Do not instrument gmon.c (recursive calls!). How to disable -pg for a function??
 https://docs.freebsd.org/44doc/psd/18.gprof/paper.pdf
 
 call _monInit() from SystemInit()
 Do *not* instrument System Init (SDK\platform\devices)
