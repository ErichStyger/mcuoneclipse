############################
# Command for removing files
RM := rm -rf

############################
# Compiler
CC := arm-none-eabi-gcc

############################
# Linker
LL := arm-none-eabi-gcc

############################
# Binary/exectable to build
EXE := \
  ./debug/MyMakeProject.axf

############################
# List of object files
OBJS := \
  ./debug/main.o \
  ./debug/startup_MKL25Z4.o \
  ./debug/system_MKL25Z4.o

############################
# List of dependency files
C_DEPS = \
  ./debug/main.d \
  ./debug/startup_MKL25Z4.d \
  ./debug/system_MKL25Z4.d

############################
# Include generated dependcy files (only if not clean target)
ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

############################
# Compiler options
CC_OPTIONS := -c -std=gnu99 -O0 -g -ffunction-sections -fdata-sections -fno-builtin -mcpu=cortex-m0plus -mthumb -DCPU_MKL25Z128VLK4 -D__USE_CMSIS -I"CMSIS" -I"source" 

############################
# Linker Options
LL_OPTIONS := -nostdlib -Xlinker -Map="debug/MyMakeProject.map" -Xlinker --gc-sections -Xlinker -print-memory-usage -mcpu=cortex-m0plus -mthumb -T linkerfile.ld -o $(EXE)


############################
# Main (all) target
all: $(EXE)
	@echo "*** finished building ***"

############################
# Clean target
clean:
	-$(RM) $(EXECUTABLES) $(OBJS) $(EXE)
	-$(RM) ./debug/*.map
	-@echo ' '

############################
# Rule to link the executable
$(EXE): $(OBJS) $(USER_OBJS) linkerfile.ld
	@echo 'Building target: $@'
	@echo 'Invoking: Linker'
	$(LL) $(LL_OPTIONS) $(OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '


############################
# Rule to build the files in the source folder
./debug/%.o: ./source/%.c
	@echo 'Building file: $<'
	$(CC) $(CC_OPTIONS) -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

############################
# Rule to build the files in the CMSIS folder
./debug/%.o: ./CMSIS/%.c
	@echo 'Building file: $<'
	$(CC) $(CC_OPTIONS) -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

