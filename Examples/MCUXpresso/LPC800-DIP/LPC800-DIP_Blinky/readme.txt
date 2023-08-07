Project with the MCUXPresso IDE for the NXP LPC800-DIP board.
It implements a blinky with the on-board LEDs.

Note that you need to have the parent project 'lpc_chip_82x' present in the workspace, ad it includes files from there.

Note: because of linker error "cannot move location counter backwards" I had to disable 'automatic placement of Code Read Protection' in the linker settings.

