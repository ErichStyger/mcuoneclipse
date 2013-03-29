readme.txt
==========

This project demonstrates the FSL USB stack with CDC on the DEMOJM board.
The CPU used is the MCF51JM128.

USB settings on the board:
- IRQ Fault: not populated
- VHOST_EN: OFF position
- VBUS_SEL: VBUS position
- DN_DOWN/J13: on position
- DP_DOWN/J14: on position
- USB_ID: no populated
- PULLUP: not populated

Once running and the device has not been enumerated, the PTE2 LED is flashing fast.
Once the device has been enumerated, PTE2 LED will flash slower.

The first time you plug the USB CDC device into your host, it will require a driver.
The cdc.inf device driver is generated into the 'Documentation' folder of the project.
Please read the corresponding readme how to install the drivers.

Depending on your system, use either the .inf in the inf.32bit or inf.64bit folder.

This then should enumerate the device as virtual COM port.

Below is an example session of a shell session:

help
--------------------------------------------------------------
USB CDC
--------------------------------------------------------------
shell                     ; Group of shell commands
  help|status             ; Print help or status information
my help                   ; My help text
CMD> status
--------------------------------------------------------------
SYSTEM STATUS
--------------------------------------------------------------
TASK LIST:
Name  Status  Prio  Stack TCB#
--------------------------------------------------------------
Shell   R 0 189 0
IDLE    R 0 114 1
--------------------------------------------------------------
RTOS RUN-TIME STATISTICS:
Name  Time (ms) %Time
--------------------------------------------------------------
Shell   49    <1%
IDLE    42218   100%
RTOS ticks   : 100 Hz, 10 ms
Free heap    : 5500 bytes
Firmware     : Mar  8 2012 13:00:38
my status    : My status text
CMD> 

