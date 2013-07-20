#
#       !!!! Do NOT edit this makefile with an editor which replace tabs by spaces !!!!   
#
##############################################################################################
#
# On command line:
#
# make all = Create project
#
# make clean = Clean project files.
#
# To rebuild project do "make clean" and "make all".
#
# Provided originally by Hussam Al-Hertani
# Modified by Erich Styger
# Use at your own risk!!!!!
##############################################################################################
# Start of default section
#
TRGT = arm-none-eabi-
CC   = $(TRGT)gcc
CP   = $(TRGT)objcopy
AS   = $(TRGT)gcc -x assembler-with-cpp
HEX  = $(CP) -O ihex
BIN  = $(CP) -O binary -S
MCU  = cortex-m0
 
# List all default C defines here, like -D_DEBUG=1
DDEFS = 

# List all default ASM defines here, like -D_DEBUG=1
DADEFS =
 
# List all default directories to look for include files here
DINCDIR =
 
# List the default directory to look for the libraries here
DLIBDIR =
 
# List all default libraries here
DLIBS =
 
#
# End of default section
##############################################################################################
 
##############################################################################################
# Start of user section
#
 
#
# Define project name
PROJECT        = LED_Toggle
 
# List all user C define here, like -D_DEBUG=1
UDEFS =
 
# Define ASM defines here
UADEFS =
 
LIBSDIR    = 
LINKER = .\Project_Settings\Linker_Files

# List C source files here
SRC  = .\Sources\main.c
SRC += .\Sources\sa_mtb.c
SRC += .\Project_Settings\Startup_Code\kinetis_sysinit.c

# List ASM source files here
ASRC = Project_Settings\Startup_Code\startup.s
 
# List all user directories here
UINCDIR = \
  .\Project_Headers \
  .\Project_Settings\Startup_code

# List the user directory to look for the libraries here
ULIBDIR =
 
# List all user libraries here
ULIBS =
 
# Define optimisation level here
OPT = -O0
#
# End of user defines
##############################################################################################
#
# Define linker script file here
#
LDSCRIPT = $(LINKER)\MKL25Z128_flash.ld
FULL_PRJ = $(PROJECT)_flash
 
INCDIR  = $(patsubst %,-I%,$(DINCDIR) $(UINCDIR))
LIBDIR  = $(patsubst %,-L%,$(DLIBDIR) $(ULIBDIR))
 
DEFS    = $(DDEFS) $(UDEFS)
 
ADEFS   = $(DADEFS) $(UADEFS)
OBJS    = $(ASRC:.s=.o) $(SRC:.c=.o)
LIBS    = $(DLIBS) $(ULIBS)
MCFLAGS = -mcpu=$(MCU)
 
ASFLAGS = $(MCFLAGS) -g -gdwarf-2 -mthumb  -Wa,-amhls=$(<:.s=.lst) $(ADEFS)
CPFLAGS = $(MCFLAGS) $(OPT) -gdwarf-2 -mthumb   -fomit-frame-pointer -Wall -Wstrict-prototypes -fverbose-asm -Wa,-ahlms=$(<:.c=.lst) $(DEFS)
LDFLAGS = $(MCFLAGS) -mthumb -nostartfiles -T$(LDSCRIPT) -Wl,-Map=$(FULL_PRJ).map,--cref,--no-warn-mismatch $(LIBDIR)
 
# Generate dependency information
CPFLAGS += -MD -MP -MF .dep\$(@F).d
 
#
# makefile rules
#
 
all: $(OBJS) $(FULL_PRJ).elf  $(FULL_PRJ).hex $(FULL_PRJ).bin
	$(TRGT)size $(PROJECT)_flash.elf
 
 %o: %c
	$(CC) -c $(CPFLAGS) -I . $(INCDIR) $< -o $@

%o: %s
	$(AS) -c $(ASFLAGS) $< -o $@

%elf: $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) $(LIBS) -o $@

%hex: %elf
	$(HEX) $< $@
	
%bin: %elf
	$(BIN)  $< $@
	
clean:
	del $(OBJS)
	del $(FULL_PRJ).elf
	del $(FULL_PRJ).map
	del $(FULL_PRJ).hex
	del $(FULL_PRJ).bin
#	del $(SRC:.c=.c.bak)
	del $(SRC:.c=.lst)
#   del $(ASRC:.s=.s.bak)
	del $(ASRC:.s=.lst)
	rmdir  .dep /S /Q
    
    
# 
# Include the dependency files, should be the last of the makefile
#
#-include $(shell mkdir .dep 2>/dev/null) $(wildcard .dep/*)
#23-July-2012 /dev/null gives an error on Win 7 64-bit : Hussam
-include $(shell mkdir .dep) $(wildcard .dep/*)

# *** EOF ***