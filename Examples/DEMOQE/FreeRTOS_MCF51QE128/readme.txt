readme.txt
==========
This application runs a FreeRTOS demo on the Freescale DEMOQE board, using the MCF51QE128.
Connect a serial cable (38400, 8N1) to your host PC.
Pressing the buttons will report it to the shell and you will hear a sound.
Pressing help in the shell will provide information about the application: 
--------------------------------------------------------------
DEMOQE Board
--------------------------------------------------------------
shell                     ; Group of shell commands
  help|status             ; Print help or status information
CMD> status
--------------------------------------------------------------
SYSTEM STATUS
--------------------------------------------------------------
TASK LIST:
Name  Status  prio  stack TCB#
--------------------------------------------------------------
Shell   R 1 210 0
IDLE    R 0 113 3
Main    B 2 95  1
Sound   S 1 114 2
--------------------------------------------------------------
RTOS RUN-TIME STATISTICS:
Name  Abs Time (ms)   %Time
--------------------------------------------------------------
Shell   319   <1%
IDLE    100057    99%
Main    27    <1%
Sound   5   <1%
RTOS ticks   : 100 Hz, 10 ms
Free heap    : 3512 bytes
Firmware     : Nov 30 2011 08:32:45


Jumper settings:
================
- LED enable: all installed
- KEY enabble: all installed
- COM_EN (PTC5): ON position (PTC5 is used to enable COM port)
- TXD on PTB1, RXD on PTB0
  (alternatively you might route the RS-232 over the P&E USB connection)