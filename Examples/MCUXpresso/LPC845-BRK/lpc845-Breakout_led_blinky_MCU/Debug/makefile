################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include utilities/subdir.mk
-include startup/subdir.mk
-include source/subdir.mk
-include drivers/subdir.mk
-include board/src/subdir.mk
-include board/subdir.mk
-include CMSIS/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: lpc845-Breakout_led_blinky_MCU.axf

# Tool invocations
lpc845-Breakout_led_blinky_MCU.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -Xlinker -Map="lpc845-Breakout_led_blinky_MCU.map" -Xlinker --gc-sections -Xlinker -print-memory-usage -Xlinker --sort-section=alignment -mcpu=cortex-m0plus -mthumb -T "lpc845-Breakout_led_blinky_MCU_Debug.ld" -o "lpc845-Breakout_led_blinky_MCU.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) lpc845-Breakout_led_blinky_MCU.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "lpc845-Breakout_led_blinky_MCU.axf"; # arm-none-eabi-objcopy -v -O binary "lpc845-Breakout_led_blinky_MCU.axf" "lpc845-Breakout_led_blinky_MCU.bin" ; # checksum -p LPC845 -d "lpc845-Breakout_led_blinky_MCU.bin";
	-@echo ' '

.PHONY: all clean dependents post-build

-include ../makefile.targets
