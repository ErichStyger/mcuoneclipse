PORT_HAL_DIR := $(SDK_ROOT)/platform/hal/port
SOURCES += $(wildcard $(PORT_HAL_DIR)/*.c)
INCLUDES += $(PORT_HAL_DIR)

