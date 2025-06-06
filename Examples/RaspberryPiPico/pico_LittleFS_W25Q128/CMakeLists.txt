cmake_minimum_required(VERSION 3.13)

# Required for McuLib, to know the target system
set(
  MCULIB_TARGET RP2040 CACHE STRING 
  "Select McuLib target: MCUXPRESSO, RP2040 or ESP32"
)

# turn variable on for verbose output, useful for makefile debugging
#set(CMAKE_VERBOSE_MAKEFILE ON)

# settings for the board and hardware used
set(PICO_PLATFORM rp2040)
set(PICO_BOARD pico) # pico or pico_w

# set build type. Without 'Debug', it won't generate line information if using build subfolders.
set(CMAKE_BUILD_TYPE Debug)

# initialize the SDK based on PICO_SDK_PATH
# note: this must happen before project()
# Include build functions from Pico SDK
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

# set project name ${CMAKE_PROJECT_NAME}
project(pico_LittleFS_W25Q128
  C CXX ASM
)

# set C and C++ standard to be used
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# [Platfrom specific command] Initialize the Raspberry Pi Pico SDK
pico_sdk_init()

# add options for McuLib usage
set(PROJECT_ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
add_compile_options(-include "${PROJECT_ROOT_DIR}/src/IncludeMcuLibConfig.h")
add_compile_options(-I "${PROJECT_ROOT_DIR}/src") # McuLib to find our local header files

# to avoid that it shows up as 'Reset' USB device, see https://forums.raspberrypi.com/viewtopic.php?t=324909
add_compile_options(-DPICO_STDIO_USB_ENABLE_RESET_VIA_VENDOR_INTERFACE=0)

add_executable(${CMAKE_PROJECT_NAME}
 # add additional source files here
)

add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
  COMMAND arm-none-eabi-size "${CMAKE_PROJECT_NAME}.elf"
  COMMENT "Printing code and data size"
)

# enable USB CDC and disable UART:
pico_enable_stdio_usb(${CMAKE_PROJECT_NAME} 1)
pico_enable_stdio_uart(${CMAKE_PROJECT_NAME} 0)

# add component directories to the list
add_subdirectory(../../McuLib build/McuLib)
add_subdirectory(./src build/src)

# generate extra files (map/bin/hex/uf2)
pico_add_extra_outputs(${CMAKE_PROJECT_NAME})

target_link_libraries(
  ${CMAKE_PROJECT_NAME}
  PUBLIC SrcLib
  PUBLIC pico_stdlib
  PUBLIC hardware_pio # PIO for WS2812B
)
