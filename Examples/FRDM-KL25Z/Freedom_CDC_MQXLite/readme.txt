readme.txt
----------

Init components do not work well with MQX/MQX-Lite, as interrupts need to be installed through the RTOS.
In order to use the USB stack with MQX-Lite:
- Disable ISR installation in USB Init_USB_OTG component
  - have an empty name for the ISR
  - disable all USB interrupts
- Disable 'Call Init method'
- Install the interrupt from the application and then call the Init method:

/* Install usb interrupt */
(void)_int_install_isr(INT_USB0, usb_isr,  (pointer)&usb_data);
/* USB low level init */
USB0_Init();
