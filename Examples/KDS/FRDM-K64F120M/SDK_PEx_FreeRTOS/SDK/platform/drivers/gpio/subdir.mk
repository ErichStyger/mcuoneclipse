GPIO_DRIVER_DIR := $(SDK_ROOT)/platform/drivers/gpio
SOURCES += $(wildcard $(GPIO_DRIVER_DIR)/src/*.c)
INCLUDES += $(GPIO_DRIVER_DIR)
