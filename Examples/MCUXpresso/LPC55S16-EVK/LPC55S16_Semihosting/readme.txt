Project for the LPC55S16-EVK with semihosting.

To run it without IDE/Debugger, one can use the LinkServer:

LinkServer run --mode semihost --send "help" lpc55s16 "Debug\LPC55S16_Semihosting.axf"

See:
- https://mcuoneclipse.com/2025/01/27/standalone-semihosting-host-target-console-with-ci-cd-runner-and-cmsis-dap/

