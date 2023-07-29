default: all

CC = g++
LINK_TARGET = $(OBJ_DIR)app
DEPEND_OPTS = -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)"
SRC_DIR = ./
OBJ_DIR = ./
OBJS = \
	$(OBJ_DIR)main.o
############################
# List of dependency files
C_DEPS = \
  $(OBJ_DIR)main.d

############################
# Include generated dependcy files (only if not clean target)
ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

all: $(LINK_TARGET)
	@echo All done!

clean:
	-@rm $(LINK_TARGET)
	-@rm $(OBJS)
	-@rm $(C_DEPS)
	@echo Clean done!

############################
# Pattern rule to compile a file
# $@ matches the target
# $< matches the first dependent
$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(CC) $(DEPEND_OPTS) -g3 -c "$<" -o "$@"

$(LINK_TARGET): $(OBJS)
	$(CC) $(OBJS) -ggdb -o $@

