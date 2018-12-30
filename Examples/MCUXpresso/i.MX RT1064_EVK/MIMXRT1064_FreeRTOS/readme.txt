readme.txt
----------
MCUXpresso IDE project for i.MX RT1064-EVK Board, using the McuOnEclipse components.


How to setup a project to use the McuOnEclipse components:
- create a bare metal project, with following components enabled/added
  - fsl_port
- copy the McuOnEclipse sources into the project:
  place the McuOnEclipse folder from https://github.com/ErichStyger/McuOnEclipseMcuOnEclipserary into the project root
- change the folder Properties > C/C++ Build and uncheck 'exclude from build'
- add the following folders to the compiler include path settings:
../McuOnEclipse/config
../McuOnEclipse/config/fonts
../McuOnEclipse/FatFS
../McuOnEclipse/fonts
../McuOnEclipse/FreeRTOS/Source/include
../McuOnEclipse/FreeRTOS/Source/portable/GCC/ARM_CM4F
../McuOnEclipse/SEGGER_RTT
../McuOnEclipse/SEGGER_Sysview
../McuOnEclipse/src
../McuOnEclipse/TraceRecorder
../McuOnEclipse/TraceRecorder/config
../McuOnEclipse/TraceRecorder/include
../McuOnEclipse/TraceRecorder/streamports/Jlink_RTT/include



#define McuMcuOnEclipse_CONFIG_CORTEX_M      (7)
  #define McuMcuOnEclipse_CONFIG_SDK_VERSION_USED  McuMcuOnEclipse_CONFIG_SDK_MCUXPRESSO_2_0

  
\todo
LEDPin1.c:
#include "fsl_port.h" /* include SDK header file for port muxing */
../McuOnEclipse/src/DbgRd1.c:69:12: fatal error: fsl_port.h: No such file or directory  



Flash erase with CMSIS-DAP on board:
Executing flash operation 'Erase' (Erase flash) - Sun Dec 30 08:12:52 CET 2018
Checking MCU info...
Scanning for targets...
Executing flash action...
MCUXpresso IDE RedlinkMulti Driver v10.3 (Nov 28 2018 02:33:57 - crt_emu_cm_redlink.exe build 748)
(  0) Reading remote configuration
Wc(03). No cache support.
Found chip XML file in C:/Users/Erich Styger/Documents/MCUXpressoIDE_10.3.0_2200/workspace/evkmimxrt1064_blinky_led_blinky/Debug\MIMXRT1064xxxxA.xml
(  5) Remote configuration complete
Reconnected to existing link server
Connecting to probe 1 core 0 (using server started externally) gave 'OK'
Probe Firmware: DAPLink CMSIS-DAP (ARM)
Serial Number:  02320000070a5e4100000000000000000000000097969905
VID:PID:  0D28:0204
USB Path: \\?\hid#vid_0d28&pid_0204&mi_03#7&1228a089&0&0000#{4d1e55b2-f16f-11cf-88cb-001111000030}
Using memory from core 0 after searching for a good core
( 30) Emulator Connected
( 40) Debug Halt
( 50) CPU ID
debug interface type      = Cortex-M7 (DAP DP ID 0BD11477) over SWD TAP 0
processor type            = Cortex-M7 (CPU ID 00000C27) on DAP AP 0
number of h/w breakpoints = 8
number of flash patches   = 0
number of h/w watchpoints = 4
Probe(0): Connected&Reset. DpID: 0BD11477. CpuID: 00000C27. Info: <None>
Debug protocol: SWD. RTCK: Disabled. Vector catch: Disabled.
Content of CoreSight Debug ROM(s):
RBASE E00FD000: CID B105100D PID 000008E88C ROM (type 0x1)
ROM 1 E00FE000: CID B105100D PID 04000BB4C8 ROM (type 0x1)
ROM 2 E00FF000: CID B105100D PID 04000BB4C7 ROM (type 0x1)
ROM 3 E000E000: CID B105E00D PID 04000BB00C Gen SCS (type 0x0)
ROM 3 E0001000: CID B105E00D PID 04000BB002 Gen DWT (type 0x0)
ROM 3 E0002000: CID B105E00D PID 04000BB00E Gen (type 0x0)
ROM 3 E0000000: CID B105E00D PID 04000BB001 Gen ITM (type 0x0)
ROM 2 E0041000: CID B105900D PID 04001BB975 CSt ARM ETMv4.0 type 0x13 Trace Source - Core
ROM 2 E0042000: CID B105900D PID 04004BB906 CSt type 0x14 Debug Control - Trigger, e.g. ECT
ROM 1 E0040000: CID B105900D PID 04000BB9A9 CSt type 0x11 Trace Sink - TPIU
ROM 1 E0043000: CID B105F00D PID 04001BB101 Sys (type 0x0)
NXP: MIMXRT1064xxxxA
DAP stride is 1024 bytes (256 words)
Inspected v.2 External Flash Device on SPI using SFDP JEDEC ID MIMXRT1064.cfx
Image 'iMXRT10xx SFDP Aug 13 2018 11:23:59'
Opening flash driver MIMXRT1064.cfx
Sending VECTRESET to run flash driver
Flash variant 'RT1064' detected (4MB = 64*64K at 0x70000000)
Closing flash driver MIMXRT1064.cfx
( 65) Chip Setup Complete
Connected: was_reset=false. was_stopped=false
( 70) License Check Complete
Opening flash driver MIMXRT1064.cfx (already resident)
Sending VECTRESET to run flash driver
Flash variant 'RT1064' detected (4MB = 64*64K at 0x70000000)
Erase flash at 0x70000000
Closing flash driver MIMXRT1064.cfx
Erase completed (in 8897ms)
