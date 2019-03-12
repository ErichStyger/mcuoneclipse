readme.txt
----------
This is an example project for Kinetis Design Studio demonstrating the 
Kinetis SDK with Processor Expert to demonstrate GNU profiling.

Tools used:
- Kinetis Design Studio v3.0.0 with Processor Expert
- Kinetis SDK v1.2.0

Note that this project uses semihosting (linker option -specs=rdimon.specs instead of -specs=nosys.specs),
and the project will *NOT* run without a debugger attached!

Profiling (per file) option: -pg
 
 Do not instrument gmon.c (recursive calls!). How to disable -pg for a function??
 https://docs.freebsd.org/44doc/psd/18.gprof/paper.pdf
 
 call _monInit() from SystemInit()
 Do *not* instrument System Init (SDK\platform\devices)

 
 Rename SysTick_Handler() in osa1.c to OSA_SysTick_Handler().