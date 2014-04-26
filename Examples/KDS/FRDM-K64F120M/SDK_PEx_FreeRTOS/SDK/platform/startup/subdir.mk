STARTUP_DIR := $(SDK_ROOT)/platform/startup
SOURCES += $(STARTUP_DIR)/startup.c \
           $(STARTUP_DIR)/M$(CHIP)/system_M$(CHIP).c \
           $(STARTUP_DIR)/M$(CHIP)/gcc/startup_M$(CHIP).S

INCLUDES += $(STARTUP_DIR)

