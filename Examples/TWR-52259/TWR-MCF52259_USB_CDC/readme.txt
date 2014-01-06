readme.txt
==========
Note: Make sure that no interrupt source is sharing the same level+sublevel (inspect vector.c for this).

Jumper settings:
- basically all jumpers are on default position, except for the connection of LED_4 to the Motor line:
  Connect a wire from LED_4 (pin close to the potentiometer) to FLW_SEL pin 4)
- all jumpers set on the POT_ISO to X_ISO jumper row,
  except LED_4_ISO (pin close to potentiometer), which is connected to J11, pin 4.
- TX_SEL and RX_SEL (J12/J13): both on 1-2 (using the onboard connector)
- J14 (JTAG), J15 (PSTCLK) and J16 (CLKOUT) on default (1-2)
- MCU_IDD: on
- J3 (CLK_MOD1): both jumpers on 1-2 (default)
- J5 (CLK_SEL): 1-2 (default)
- SW2 (dip switch): all on ON position
- J120 (OSBDM bootloader): not set
- Motor: GND (either black or brown, single wire) is on primary (white stripe) board side

Settings for CDC USB Support:
============================= 
- Add Init_USB_OTG to the project and configure it to 24 MHz clock frequency
- disable linker .lcf generation and add following:
     . = ALIGN(512);
     __BDT_BASE = .;
     *(.usb_bdt) 
     __BDT_END = .;
  at the end of the .data section:   
  } > data

TWR-SER jumper settings for USB CDC:
- J10 (USB VBUS Select): 1-2 (Supply 5V on USB Connector (Host Mode)
- J16 (USB Mode Select): 3-4 (device mode, source 5V from VBUS
