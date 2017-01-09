OUT_DIR := out
# add traling / if not empty
ifeq ($(strip $(OUT_DIR)), )
	OBJ_FOLDER =
else
	OBJ_FOLDER = $(strip $(OUT_DIR))/
endif
TOOLCHAIN=/opt/Freescale/KDS_v3/toolchain/bin/arm-none-eabi-
CC=$(TOOLCHAIN)gcc
AS = $(TOOLCHAIN)gcc -x assembler-with-cpp
LD = $(TOOLCHAIN)g++
COMPILER_OPTIONS = -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -std=c99 -MMD -MP -g3
#DEPEND_OPTS = -MF $(OBJ_FOLDER)$(@F:.o=.d)
# Targets
TARGET := FRDM-K64F_NeoPixel_SDK
TARGET_EXT := elf
RM := rm -rf
# Linker options

LD_PATH := Project_Settings/Linker_Files/
LD_SCRIPT := MK64FN1M0xxx12_flash.ld
#LD_OPTIONS = $(COMPILER_OPTIONS) -std=c99 -Xlinker --gc-sections -specs=nano.specs -specs=nosys.specs -T $(LD_PATH)$(LD_SCRIPT)  
LD_OPTIONS = -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -g3 -T "MK64FN1M0xxx12_flash.ld" -Xlinker --gc-sections -L"/home/karibe/workspace.kds/FRDM-K64F_NeoPixel_SDK/Project_Settings/Linker_Files" -Wl,-Map,$(OBJ_FOLDER)$(TARGET)".map" -specs=nosys.specs -specs=nano.specs    


#LD_OPTIONS += -nostartfiles


SRC_DIRS = Sources Project_Settings/Startup_Code SDK/platform/drivers/src/edma SDK/platform/drivers/src/ftm SDK/platform/drivers/src/gpio SDK/platform/hal/src/dmamux SDK/platform/hal/src/edma SDK/platform/hal/src/ftm SDK/platform/hal/src/gpio SDK/platform/hal/src/mcg SDK/platform/hal/src/osc SDK/platform/hal/src/port SDK/platform/hal/src/sim/MK64F12 SDK/platform/system/src/clock/MK64F12 SDK/platform/system/src/interrupt 

INC_DIRS_F = SDK/platform/drivers/inc SDK/platform/devices SDK/platform/devices/MK64F12/include SDK/platform/system/src/clock/MK64F12 SDK/platform/hal/inc SDK/platform/hal/src/sim/MK64F12 SDK/platform/osa/inc SDK/platform/system/inc SDK/platform/system/src/clock/MK64F12 SDK/platform/CMSIS/Include Project_Settings/Startup_Code

INC_DIRS := $(foreach dir,$(INC_DIRS_F),-I"$(dir)")

CFLAGS = $(COMPILER_OPTIONS) -g3 -D"CPU_MK64FN1M0VMD12" -D"CLOCK_SETUP=1" -D"FSL_OSA_BM_TIMER_CONFIG=0" -MF"$(@:%.o=%.d)" -MT"$@" $(INC_DIRS) -c
ASFLAGS = $(COMPILER_OPTIONS) $(INC_DIRS) -c


C_SRCS := $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.c))
C_OBJS := $(patsubst %.c,$(OBJ_FOLDER)%.o,$(notdir $(C_SRCS)))
S_SRCS := $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.S))
S_OBJS := $(patsubst %.S,$(OBJ_FOLDER)%.o,$(notdir $(S_SRCS)))

VPATH := $(SRC_DIRS)

$(OBJ_FOLDER)%.o : %.c
	@echo 'Building file: $(@F)'
	@echo '--------------------'
	@echo 'Invoking: MCU C Compiler'
	$(CC) $(CFLAGS) $< -o $@
	@echo 'Finished building: $(@F)'
	@echo ' '
	
$(OBJ_FOLDER)%.o : %.S
	@echo 'Building file: $(@F)'
	@echo '--------------------'
	@echo 'Invoking: MCU Assembler'
	$(AS) $(ASFLAGS) $< -o $@
	@echo 'Finished building: $(@F)'
	@echo ' '
	
all: clean create_outputdir $(OBJ_FOLDER)$(TARGET).$(TARGET_EXT) print_size
	
create_outputdir:
	$(shell mkdir $(OBJ_FOLDER) 2>/dev/null)

# Tool invocations
$(OBJ_FOLDER)$(TARGET).$(TARGET_EXT): $(C_OBJS) $(S_OBJS)
	@echo 'Building target: $@'
	@echo '-------------------'
	@echo 'Invoking: MCU Linker'
	$(LD) $(LD_OPTIONS) -o $(OBJ_FOLDER)$(TARGET).$(TARGET_EXT) $(S_OBJS) $(C_OBJS) 
	@echo 'Finished building target: $@'
	@echo ' '

clean:
	@echo 'Removing entire out directory'
	@echo '-----------------------------'
	$(RM) $(TARGET).$(TARGET_EXT) $(OBJ_FOLDER)*.* $(OBJ_FOLDER)
	@echo ' '

print_size:
	@echo 'Printing size'
	@echo '-------------'
	arm-none-eabi-size --format=berkeley "$(OBJ_FOLDER)$(TARGET).$(TARGET_EXT)";
	@echo ' '
gamma: 
	@echo 'Building gamma values generating binary'
	@echo '---------------------------------------'
	gcc -o gamma/gamma gamma/generateGamma.c -lm
	@echo 'Generating gamma values array'
	@echo '-----------------------------'
	./gamma/gamma
	@echo 'removing gamma values generating binary'
	@echo '---------------------------------------'
	$(RM) gamma/gamma

.PHONY: all clean dependents print_size gamma
