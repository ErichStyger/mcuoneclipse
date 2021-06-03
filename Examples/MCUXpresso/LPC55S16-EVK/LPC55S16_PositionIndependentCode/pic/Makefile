
#################### CONFIGURABLE SECTION ###########################
# Target can be anything you want. It will create an elf and bin file
# with this name
TARGET = main

# Define the linker script location and chip architecture.
# Change this based on your linker script name and chip architecture
LD_SCRIPT = stm32_linker.ld
MCU_SPEC  = cortex-m4

# Add assembler and C files to this, later we can add a wildcard
# to compile all c files in the directory
AS_SRC    = startup.S
C_SRC     = main.c 
LIBS_SRC  = 
DLIB_SRC = mylib.c
# Toolchain definitions (ARM bare metal defaults)
# Set the TOOLCHAIN_PATH variable to the path where it is installed
# If it is accessible globally. ie it is in your system path ($PATH)
# then leave it blank. A slash at the end of the path is required
# eg: TOOLCHAIN_PATH = /usr/local/bin/
TOOLCHAIN_PATH = 
TOOLCHAIN = $(TOOLCHAIN_PATH)arm-none-eabi-
CC 	= $(TOOLCHAIN)gcc
AS 	= $(TOOLCHAIN)as
LD 	= $(TOOLCHAIN)ld
OC 	= $(TOOLCHAIN)objcopy
OD 	= $(TOOLCHAIN)objdump
OS 	= $(TOOLCHAIN)size
GDB = $(TOOLCHAIN)gdb

######################################################################
.DELETE_ON_ERROR:

# Assembly directives.
ASFLAGS += -c
ASFLAGS += -O0
ASFLAGS += -mcpu=$(MCU_SPEC)
ASFLAGS += -mthumb
ASFLAGS += -Wall
# (Set error messages to appear on a single line.)
ASFLAGS += -fmessage-length=0

# C compilation directives
CFLAGS += -c
CFLAGS += -mcpu=$(MCU_SPEC)
CFLAGS += -mthumb
CFLAGS += -Wall
CFLAGS += -g
# (Set error messages to appear on a single line.)
CFLAGS += -fmessage-length=0
# (Set system to ignore semihosted junk)
CFLAGS += --specs=nosys.specs

# Linker directives
LSCRIPT = ./$(LD_SCRIPT)

LFLAGS += -g
LFLAGS += -nostdlib
LFLAGS += -T$(LSCRIPT)
LFLAGS += -Map $(TARGET).map
LFLAGS += --print-memory-usage

OBJS   += $(AS_SRC:.S=.o)
OBJS   += $(C_SRC:.c=.o)
OBJS   += $(LIB_SRC:.c=.o)

DLIB_CFLAGS += -mcpu=$(MCU_SPEC)
DLIB_CFLAGS += -mthumb
DLIB_CFLAGS += -Wall
DLIB_CFLAGS += -g
DLIB_CFLAGS += -fPIC
DLIB_CFLAGS += -fmessage-length=0
DLIB_CFLAGS += --specs=nosys.specs

DLIB_LFLAGS += $(DLIB_SRC:%.c=-l%)
DLIBS       += $(DLIB_SRC:%.c=lib%.so)

# The following two lines are to remove the existing so and o files
DLIBS_SO  += $(DLIB_SRC:.c=.so)
DLIBS_O   += $(DLIB_SRC:.c=.o)

# The PHONY keyword is required so that makefile does not
# consider the rule 'all' as a file
.PHONY: all
all: $(TARGET).bin

# There should be a tab here on the line with $(CC), 4 spaces does not work
%.o: %.S
	$(CC) -x assembler-with-cpp $(ASFLAGS) $< -o $@

%.o: %.s
	$(CC) -x assembler-with-cpp $(ASFLAGS) $< -o $@

# If -c is used then it will create a reloc file ie normal object file
# and not a dynamic object. For dynamic object -shared is required.
%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE) $< -o $@

%.so: %.c
	$(CC) -shared $(DLIB_CFLAGS) $< -o lib$@

$(TARGET).diss: $(TARGET).elf
	$(OD) -Dz --source $^ > $@

$(TARGET).elf: $(OBJS)
	$(LD) $^ $(LFLAGS) -o $@

$(TARGET).bin: $(TARGET).elf $(TARGET).diss
	$(OC) -S -O binary $< $@
	$(OS) $<

########################### got_only ########################### 
# @Brief This target makes executable with global variables 
# accessed through GOT while procedure calls are direct
got_only:ASFLAGS += -fPIC
got_only:CFLAGS  += -fPIC
got_only:LFLAGS  += $(DLIBS_O)
.PHONY: got_only
got_only: $(DLIBS_O) $(TARGET).bin
################################################################

########################### got_plt ############################ 
# @Brief This target makes executable with global variables 
# accessed through GOT and shared library functions through
# the PLT
got_plt:ASFLAGS += -fPIC
got_plt:CFLAGS  += -fPIC
got_plt:LFLAGS  += -L. $(DLIB_LFLAGS)
.PHONY: got_plt
got_plt: $(DLIBS_SO) $(TARGET).bin
################################################################

####################### got_plt_single #########################
# @Brief This target makes executable with global variables 
# accessed through GOT and shared library functions through
# the PLT. The GOT base is hardcoded in register r9.
got_plt_single:ASFLAGS      += -fPIC -msingle-pic-base -mpic-register=r9 -mno-pic-data-is-text-relative
got_plt_single:CFLAGS       += -fPIC -msingle-pic-base -mpic-register=r9 -mno-pic-data-is-text-relative
got_plt_single:DLIB_CFLAGS  += -fPIC -msingle-pic-base -mpic-register=r9 -mno-pic-data-is-text-relative
got_plt_single:LFLAGS       += -L. $(DLIB_LFLAGS)
.PHONY: got_plt_single
got_plt_single: $(DLIBS_SO) $(TARGET).bin
################################################################

########################### clean ############################## 
# @Brief Remove the target output files.
.PHONY: clean
clean:
	rm -f $(OBJS) $(DLIBS) $(DLIBS_O)
	rm -f $(TARGET).elf $(TARGET).bin $(TARGET).list $(TARGET).srec
	rm -f $(TARGET).diss $(TARGET).map
################################################################

########################### gdb ################################ 
# @Brief Start GDB, connect to server and load the elf
.PHONY: gdb
gdb:
	@pgrep -x "st-util" || (echo "Please start st-util"; exit -1)
	@echo "Starting GDB"
	$(GDB) -ex "target extended localhost:4242" -ex "load $(TARGET).elf" $(TARGET).elf
################################################################
