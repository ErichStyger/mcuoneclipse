readme.txt
----------
Example using ITM console over SWO as well for power profiling.
Make sure that in the power profiling the sample rate is set to a high value (832 ticks won't work).

Set a breakpoint in main() after PL_Init() (after the clocking has been configured).
Check SWO configuration in MCUXpresso IDE using the menu Analysis > SWO Trace config. Clock speed should be 12 MHz.
Then use the MCUXpresso IDE menu Analysis > SWO ITM Console to open the console.
Then use the 'play' button in that view to start it.

See as well:
- https://mcuoneclipse.com/2021/05/22/swo-with-arm-cortex-m33/
