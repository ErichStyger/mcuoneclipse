cmake_minimum_required(VERSION 3.13)

# set(CMAKE_VERBOSE_MAKEFILE ON) # for verbose output

# initialize the SDK based on PICO_SDK_PATH
# note: this must happen before project()
include(pico_sdk_import.cmake)

project(picoLedCube C CXX ASM)  # sets ${CMAKE_PROJECT_NAME}
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# To make sure build folder doesn't get cluttered
set(ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)  # folder for UF2 file
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)

#set(PICO_BOARD pico_w)  # needed for Pico-W, otherwise #include "pico/cyw43_arch.h" won't be found
set(PICO_BOARD pico)  # set the 'Pico' as board

# [Platfrom specific command] Initialize the Raspberry Pi Pico SDK
pico_sdk_init()

set(PROJECT_ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
add_compile_options(-include "${PROJECT_ROOT_DIR}/src/IncludeMcuLibConfig.h")

# to avoid that it shows up as 'Reset' USB device, see https://forums.raspberrypi.com/viewtopic.php?t=324909
add_compile_options(-DPICO_STDIO_USB_ENABLE_RESET_VIA_VENDOR_INTERFACE=0)

add_executable(${CMAKE_PROJECT_NAME})

add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
  COMMAND arm-none-eabi-size "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CMAKE_PROJECT_NAME}.elf"
  COMMENT "Printing code and data size"
)
  
# enable USB CDC and disable UART:
pico_enable_stdio_usb(${CMAKE_PROJECT_NAME} 1)
pico_enable_stdio_uart(${CMAKE_PROJECT_NAME} 0)

# add component directories to the list
add_subdirectory(../../MCUXpresso/McuLib build/McuLib)
#add_subdirectory(../../MCUXpresso/McuLib/LittlevGL  build/McuLib/LittlevGL)
add_subdirectory(./src build/src)

# generate extra files (map/bin/hex/uf2)
#pico_add_extra_outputs(${CMAKE_PROJECT_NAME})
pico_add_uf2_output(${CMAKE_PROJECT_NAME}) # generate UF2 file
#pico_add_hex_output(${CMAKE_PROJECT_NAME}) # generate hex file
#pico_add_bin_output(${CMAKE_PROJECT_NAME}) # generate bin file

target_link_libraries(
  ${CMAKE_PROJECT_NAME}
  # might have circular library dependencies, see https://stackoverflow.com/questions/45135/why-does-the-order-in-which-libraries-are-linked-sometimes-cause-errors-in-gcc
  SrcLib
  McuLib
  SrcLib  # again because of FreeRTOShooks.c
  pico_stdlib
  hardware_pio # PIO for WS2812B
)
