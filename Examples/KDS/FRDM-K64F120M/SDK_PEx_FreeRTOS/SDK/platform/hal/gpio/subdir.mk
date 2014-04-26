GPIO_HAL_DIR := $(SDK_ROOT)/platform/hal/gpio
SOURCES += $(wildcard $(GPIO_HAL_DIR)/*.c)
INCLUDES += $(GPIO_HAL_DIR)
