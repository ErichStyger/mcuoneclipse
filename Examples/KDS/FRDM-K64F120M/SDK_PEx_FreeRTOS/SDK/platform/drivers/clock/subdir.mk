CLOCK_DRIVER_DIR := $(SDK_ROOT)/platform/drivers/clock
SOURCES += $(wildcard $(CLOCK_DRIVER_DIR)/src/*.c)
INCLUDES += $(CLOCK_DRIVER_DIR)

