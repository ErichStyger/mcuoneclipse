# this method initializes debug modules which are not affected by software reset 
# register names should be referenced including the register group name to improve performance 

proc init_debug_modules {} {
	# initialize LR to avoid invalid stack after reset
	reg "User\\/System Mode Registers/LR" = 0xFFFFFFFF
	# clear FPB comparators
	reg "Breakpoint Unit Registers/BP_COMP0" = 0x0
	reg "Breakpoint Unit Registers/BP_COMP1" = 0x0
    # clear DWT function registers
	reg "Core Debug Registers/DEMCR" = 0x1000001
	reg "Data Watchpoint and Trace Unit Registers/DWT_FUNCTION0" = 0x0
	reg "Data Watchpoint and Trace Unit Registers/DWT_FUNCTION1" = 0x0
}

proc init_trace_modules {} {
}

proc envsetup {} {
	# Environment Setup
	radix x 
	config hexprefix 0x
	config MemIdentifier p 
	config MemWidth 32 
	config MemAccess 32 
	config MemSwap off
}

#-------------------------------------------------------------------------------
# Main                                                                          
#-------------------------------------------------------------------------------

  envsetup
  init_debug_modules
  init_trace_modules
