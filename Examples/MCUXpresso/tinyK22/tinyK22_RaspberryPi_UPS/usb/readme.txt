readme usb cdc
--------------
The follwing USB stack sources are taken from the MCUXpresso SDK, with following changes/extensions:
- usb/osa folder is from components/osa
- usb/osa/fsl_component_generic_list.h is from components/lists
- usb/cdc/virtual_com.c/.h are from the example and changed to be used with FreeRTOS
- extension marked with /* << EST */ in virtual_com.h

How to integrate into application
---------------------------------
- Enable USB clock (usually to 48 MHz) in clock configuration

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
- initialize the stack from platform.c:
#if PL_CONFIG_USE_USB_CDC
  USB_APPInit(); /* Initialize USB first before the UART, because this changes the clock settings! */
#endif

- the shell.c shall have USB CDC I/O descriptor enabled


Notes:
- USB_CDC_ABSTRACT_CONTROL_FUNC_DESC in usb_device_descriptor.c
- USB_DEVICE_CDC_REQUEST_SET_CONTROL_LINE_STATE in virtual_com.c
- #define LINE_CODING_DTERATE (115200)
