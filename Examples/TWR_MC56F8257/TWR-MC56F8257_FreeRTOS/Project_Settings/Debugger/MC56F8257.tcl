radix x 
config hexprefix 0x
config MemWidth 16
config MemAccess 16
config MemSwap off

#------------------------------------------------------------------------------

#  MC56F825x initialization file for flash
#  Freescale sample code

#------------------------------------------------------------------------------
# see below for version history 
#------------------------------------------------------------------------------
# NOTE: 56F825x does not have EMI 

# Enable Reset.  GPIOD4 will be forced by the debugger to configure pin for reset function.
# GPIO D BASE + 3 is register address.  We need to set bit 4.
# Content is 1 which means peripheral owns the pin.  No GPSn registers
# need to be set for this device in order to reset the device, since the only peripheral other than GPIOD4 is RESETB/VPP
change x:0xF173 0x1000

# set Flash Clock Divider (write 0x27)
change x:0xF400 0x2700

# unlock protection
change x:0xF401 0x0000

# unprotect
change x:0xF410 0x0000