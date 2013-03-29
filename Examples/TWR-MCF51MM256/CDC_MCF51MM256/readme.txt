readme.txt
----------
This project demonstrates USB CDC (virtual COM) on the TWR-MCF51MM256 board in combination with the TWR-SER board.
The application echos all characters read (after a new line) back to the console.

- CPU clock is set to 24 MHz bus clock
- Project options have been set to use far code and data model
- Linker file generation is disabled, and following block has been added to the .lcf file
 .usb_bdt :
  {
    . = ALIGN(512);
    __BDT_BASE = .;
    *(.usb_bdt)
    __BDT_END = .;
  } >> userram
