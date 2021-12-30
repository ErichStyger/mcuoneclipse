##
## License:  Revised BSD License, see LICENSE.TXT file included in the project
## Authors:  Diego Bienz
##
project(Tardigrade)
cmake_minimum_required(VERSION 3.6)
enable_language(ASM)

#---------------------------------------------------------------------------------------
# Target
#---------------------------------------------------------------------------------------

# All source files, including the fsl drivers of the NXP MCU
# If you plan to use an additional driver, you need to add it here
list(APPEND ${PROJECT_NAME}_SOURCES
    # Board drivers
    "${CMAKE_CURRENT_SOURCE_DIR}/board.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/uart-board.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/delay-board.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/gpio-board.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/rtc-board.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/spi-board.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/sx1262-board.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/gps-board.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/i2c-board.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/adc-board.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/eeprom-board.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/lpm-board.c"

    # LPC system startup
    "${CMAKE_CURRENT_SOURCE_DIR}/cmsis/arm-gcc/startup_LPC55S16.S"
    "${CMAKE_CURRENT_SOURCE_DIR}/cmsis/system_LPC55S16.c"

    # LPC55 board configurations
    "${CMAKE_CURRENT_SOURCE_DIR}/configs/clock_config.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/configs/pin_mux.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../mcu/lpc55/LPC55S16/drivers/fsl_common.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../mcu/lpc55/LPC55S16/drivers/fsl_clock.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../mcu/lpc55/LPC55S16/drivers/fsl_power.c"

    # MCU drivers
    "${CMAKE_CURRENT_SOURCE_DIR}/../mcu/utilities.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../mcu/lpc55/LPC55S16/drivers/fsl_flexcomm.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../mcu/lpc55/LPC55S16/drivers/fsl_reset.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../mcu/lpc55/LPC55S16/drivers/fsl_usart.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../mcu/lpc55/LPC55S16/drivers/fsl_gpio.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../mcu/lpc55/LPC55S16/drivers/fsl_pint.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../mcu/lpc55/LPC55S16/drivers/fsl_inputmux.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../mcu/lpc55/LPC55S16/drivers/fsl_rtc.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../mcu/lpc55/LPC55S16/drivers/fsl_spi.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../mcu/lpc55/LPC55S16/drivers/fsl_i2c.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../mcu/lpc55/LPC55S16/drivers/fsl_iap.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../mcu/lpc55/LPC55S16/drivers/fsl_iap_ffr.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/../mcu/lpc55/LPC55S16/drivers/fsl_power.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../mcu/lpc55/LPC55S16/drivers/fsl_ostimer.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../mcu/lpc55/LPC55S16/drivers/fsl_lpadc.c"
)

# Set language of startup file
set_property(SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/cmsis/gcc-arm/startup_LPC55S16.S" PROPERTY LANGUAGE C)

add_library(${PROJECT_NAME} OBJECT EXCLUDE_FROM_ALL ${${PROJECT_NAME}_SOURCES})

# Set target CPU
target_compile_definitions(${PROJECT_NAME} PUBLIC -DCPU_LPC55S16JBD64)

# For debug builds set the symbol DEBUG
set(CMAKE_C_FLAGS_DEBUG -DDEBUG)

# Includes of all header files, including all header files of the fsl drivers of the NXP MCU
target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/cmsis
    ${CMAKE_CURRENT_SOURCE_DIR}/cmsis/arm-gcc
    ${CMAKE_CURRENT_SOURCE_DIR}/cmsis/arm-std
    ${CMAKE_CURRENT_SOURCE_DIR}/configs
    ${CMAKE_CURRENT_SOURCE_DIR}/../mcu/lpc55
    ${CMAKE_CURRENT_SOURCE_DIR}/../mcu/lpc55/cmsis
    ${CMAKE_CURRENT_SOURCE_DIR}/../mcu/lpc55/cmsis_drivers
    ${CMAKE_CURRENT_SOURCE_DIR}/../mcu/lpc55/utilities
    ${CMAKE_CURRENT_SOURCE_DIR}/../mcu/lpc55/utilities/debug_console
    ${CMAKE_CURRENT_SOURCE_DIR}/../mcu/lpc55/utilities/str
    ${CMAKE_CURRENT_SOURCE_DIR}/../mcu/lpc55/LPC55S16
    ${CMAKE_CURRENT_SOURCE_DIR}/../mcu/lpc55/LPC55S16/drivers
    $<TARGET_PROPERTY:board,INTERFACE_INCLUDE_DIRECTORIES>
    $<TARGET_PROPERTY:system,INTERFACE_INCLUDE_DIRECTORIES>
    $<TARGET_PROPERTY:radio,INTERFACE_INCLUDE_DIRECTORIES>
    $<TARGET_PROPERTY:peripherals,INTERFACE_INCLUDE_DIRECTORIES>
)

set_property(TARGET ${PROJECT_NAME} PROPERTY C_STANDARD 11)