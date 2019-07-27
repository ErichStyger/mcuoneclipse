readme.txt
----------
Project for a 'blinky' on the Seeed Arch Mix (i.MX RT1052) board, running from FLASH.

- project created has no FLASH set.
- copy xip folder from RT1021 and add to the build (note: need to rename)
- set defines
XIP_EXTERNAL_FLASH=1
XIP_BOOT_HEADER_ENABLE=1
XIP_BOOT_HEADER_DCD_ENABLE=1
- add to board.h:
#define BOARD_FLASH_SIZE    (0x800000U)
- add fsl_commmon.h from SDK components


Flash drivers are in (*.cfx)
C:\nxp\MCUXpressoIDE_11.0.0_2516\ide\plugins\com.nxp.mcuxpresso.tools.bin.win32_11.0.0.201905221151\binaries\Flash
==> MIMXRT1050-EVK_IS25WP064A.cfx


Arch Mix: IS25WP064

i.MX RT1021 board:
- 64 MBit (8 MByte) QSPI Flash (U13, IS25LP064A-JBLE)
64 MBit (8 MByte) QSPI Flash (U13, S25LP064A-JBLE):
0x60000000 size 0x800000
MIMXRT1020-EVK_IS25LP064.cfx

RT1021 LinkServer Log:
MCUXpresso IDE RedlinkMulti Driver v11.0 (May 22 2019 13:46:40 - crt_emu_cm_redlink build 6)
Found chip XML file in C:/Users/Erich Styger/Data/GitRepos/McuOnEclipse/Examples/MCUXpresso/i.MX RT1020-EVK/MIMXRT1021_Blinky/Debug\MIMXRT1021xxxxx.xml
Reconnected to existing LinkServer process.
============= SCRIPT: RT1020_connect.scp =============
RT1020 MPU Disable
Finished
============= END SCRIPT =============================
Probe Firmware: DAPLink CMSIS-DAP (ARM)
Serial Number:  0226000040214e4500171019c89200399e11000097969900
VID:PID:  0D28:0204
USB Path: \\?\hid#vid_0d28&pid_0204&mi_03#7&325c4749&0&0000#{4d1e55b2-f16f-11cf-88cb-001111000030}
Using memory from core 0 after searching for a good core
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
NXP: MIMXRT1021xxxxx
DAP stride is 1024 bytes (256 words)
Inspected v.2 External Flash Device on SPI MIMXRT1020-EVK_IS25LP064.cfx
Image 'MIMXRT1020-EVK_IS25LP064A May 22 2019 12:28:10'
Connected: was_reset=false. was_stopped=false
Awaiting telnet connection to port 3331 ...
GDB nonstop mode enabled
Opening flash driver MIMXRT1020-EVK_IS25LP064.cfx
Sending VECTRESET to run flash driver
Flash device supported (8MB = 128*64K at 0x60000000)
Writing 16996 bytes to address 0x60000000 in Flash
60004000 done  96% (16384 out of 16996)
60008000 done 100% (32768 out of 16996)
Erased/Wrote sector  0-0 with 16996 bytes in 1337msec
Closing flash driver MIMXRT1020-EVK_IS25LP064.cfx
Flash Write Done
Flash Program Summary: 16996 bytes in 1.34 seconds (12.41 KB/sec)
Starting execution using system reset and halt target
Note - system reset leaves VTOR at 0x200000 (not 0x60000000 which a booted image might assume)
Stopped (Was Reset)  [Reset from Unknown]
Stopped: Breakpoint #1
