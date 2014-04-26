MCG_HAL_DIR := $(SDK_ROOT)/platform/hal/mcg
SOURCES += $(wildcard $(MCG_HAL_DIR)/*.c)
INCLUDES += $(MCG_HAL_DIR)

