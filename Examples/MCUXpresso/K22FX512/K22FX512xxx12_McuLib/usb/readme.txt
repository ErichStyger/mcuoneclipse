readme usb cdc
--------------
- add following to the compiler defines:
USB_STACK_BM

- add the following to the include path settings
../usb/device/source/khci
../usb/include
../usb/device/include
../usb/device/source
../usb/device/class
../usb/device/class/cdc
../usb/osa
../usb/cdc

- add the following to platform.h
#define PL_CONFIG_USE_USB_CDC (1)

- add the following to platform.c:
#if PL_CONFIG_USE_USB_CDC
  #include "virtual_com.h"
#endif

#if PL_CONFIG_USE_USB_CDC
  USB_APPInit(); /* Initialize USB first before the UART, because this changes the clock settings! */
#endif

- the shell.c shall have USB CDC I/O descriptor enabled



Notes:
- USB_CDC_ABSTRACT_CONTROL_FUNC_DESC in usb_device_descriptor.c
- USB_DEVICE_CDC_REQUEST_SET_CONTROL_LINE_STATE in virtual_com.c
- #define LINE_CODING_DTERATE (115200)

Termite needs Flow Control (RTS/CTS) enabled!
The 'fix' in https://community.nxp.com/thread/493438 did not work :-(

Termite: 115200, RTS/CTC enabled, append CR+LF
SmarTTY: