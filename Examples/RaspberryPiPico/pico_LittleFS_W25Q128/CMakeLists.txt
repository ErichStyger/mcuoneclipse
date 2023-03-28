cmake_minimum_required(VERSION 3.13)

# set(CMAKE_VERBOSE_MAKEFILE ON) # for verbose output

# initialize the SDK based on PICO_SDK_PATH
# note: this must happen before project()
include(pico_sdk_import.cmake)

project(pico_LittleFS_W25Q128 C CXX ASM) # sets ${CMAKE_PROJECT_NAME}
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

set(PICO_BOARD pico_w)  # needed for Pico-W, otherwise #include "pico/cyw43_arch.h" won't be found

# [Platfrom specific command] Initialize the Raspberry Pi Pico SDK
pico_sdk_init()

set(PROJECT_ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
add_compile_options(-include "${PROJECT_ROOT_DIR}/src/IncludeMcuLibConfig.h")

add_executable(${CMAKE_PROJECT_NAME})

# enable USB CDC and disable UART:
pico_enable_stdio_usb(${CMAKE_PROJECT_NAME} 1)
pico_enable_stdio_uart(${CMAKE_PROJECT_NAME} 0)

# add component directories to the list
add_subdirectory(../McuLib  build/McuLib)
add_subdirectory(./src      build/src)

# generate extra files (map/bin/hex/uf2)
pico_add_extra_outputs(${CMAKE_PROJECT_NAME})

target_link_libraries(
  ${CMAKE_PROJECT_NAME}
  # might have circular library dependencies, see https://stackoverflow.com/questions/45135/why-does-the-order-in-which-libraries-are-linked-sometimes-cause-errors-in-gcc
  SrcLib
  McuLib
  SrcLib  # again because of FreeRTOShooks.c
  pico_stdlib
  hardware_pio # PIO for WS2812B
)
