readme.txt
==========
Jumper settings on the board:
- IRQ Fault: not populated
- VHOST_EN: OFF position
- VBUS_SEL: VBUS position
- DN_DOWN/J13: on position
- DP_DOWN/J14: on position
- USB_ID: no populated
- PULLUP: not populated
  

Steps to create a USB CDC project for the MCF51JM128 (DEMOJM board)
- Make sure you have the latest and greates components from http://www.steinerberg.com/EmbeddedComponents
- Create a new project with the wizard for Processor Expert
- Configure the CPU clock speed to 24 MHz
  - Enable external clock with 12 MHz crystal
  - In High speed mode, use external clock and set it to 24 MHz
  - Have PLL Engabed for FLL/PLL mode
  - Set Oscillator operating mode to high gain
- Add the Init_USB_OTG component
  - Specify USB_ISR for Interrupts>USB>ISR Name
  - Enable all interrupts in Interrupts>USB (Error and OTG interrupts can remain disabled)
  - Set Initialization>Mode to Device
- Add the FSL_USB_Stack component
  - Set the device to MCF51JM128
- Change project options for the compiler (Code Generation > ColdFire Processor) to Far (32bit) Code Model
- Generate at least once code to have a linker file created.
  - Disable linker file generation: in CPU component > Build options set 'Generate LCF file' to 'no'
  - add following block between .text:{} and .data:{}
    .usb_bdt :
  {
    . = ALIGN(512);
    __BDT_BASE = .;
    *(.usb_bdt) 
    __BDT_END = .;
  } >> userram
- Add 2 LEDs and WAIT to the project (we will us it in our application). Enable Delay100US of the CPU methods.
- Add cdc.c/cdc.h to your application and call CDC_Run() from main().
- If you run the application, LED1 will flash fast if the device is not attached the host. Otherwise LED2 will flash.
- The device will enumerate in your device manager, and you need to install/update the driver.
  All what you need is a .inf file. You find the files here:
  C:\ProgramData\Processor Expert\CW08_PE3_09\Drivers\FSL_USB_Stack\inf\inf.32bit
  C:\ProgramData\Processor Expert\CW08_PE3_09\Drivers\FSL_USB_Stack\inf\inf.64bit
  For 64bit machines, you need to follow the steps in the readme at the same location of the .inf file)
- Plug in the USB cable: the LED2 will flash
- Connect with a terminal to your virtual COM port and type in something: it will be echoed back.

