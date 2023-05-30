# GDB script to catch ARM bkpt instruction and move over it.
catch signal SIGTRAP
commands
  # check if it is a BKPT (0xbe) instruction:
  if (*(unsigned char*)($pc+1)) == 0xbe
    # check if it is a BKPT #1 instruction:
    if (*(unsigned char*)($pc)) == 0x01
      # yes: move PC after bkpt instruction
      set $pc=$pc+2
    else
      # in case of BKPT #2, skip it and continue
      if (*(unsigned char*)($pc)) == 0x02
        set $pc=$pc+2
        continue
      end
    end
  end
end
