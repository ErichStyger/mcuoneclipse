readme
======

This project demonstrates the USB HID Kbd device class on the DEMOJM board with the S08JM60.
Settings:
- CPU clock: 24 MHz
- disable memory at 0x1860 in CPU build options
- Init_USB
  - Set ISR name to: USB_ISR
  - USB RAM Address at 0x1860 with size 0x40
  - Enable all interrupts
