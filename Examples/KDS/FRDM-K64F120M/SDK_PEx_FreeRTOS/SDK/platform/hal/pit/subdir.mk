PIT_HAL_DIR := $(SDK_ROOT)/platform/hal/pit
SOURCES += $(wildcard $(PIT_HAL_DIR)/*.c)
INCLUDES += $(PIT_HAL_DIR)
