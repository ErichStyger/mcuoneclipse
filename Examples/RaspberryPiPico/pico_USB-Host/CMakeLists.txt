cmake_minimum_required(VERSION 3.25...3.30)

message(STATUS "Toolchain file is" ${CMAKE_TOOLCHAIN_FILE})
# Required for McuLib, to know the target system
set(
  MCULIB_TARGET RP2040 CACHE STRING 
  "Select McuLib target: MCUXPRESSO, RP2040 or ESP32"
)

# turn variable on for verbose output, useful for build debugging. Or run 'ninja --verbose' in the build folder
#set(CMAKE_VERBOSE_MAKEFILE ON CACHE BOOL "ON")

# settings for the board and hardware used
set(PICO_PLATFORM rp2040)
set(PICO_BOARD pico) # pico or pico_w

# initialize the SDK based on PICO_SDK_PATH
# note: this must happen before project()
# Include build functions from Pico SDK
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

# set project name ${CMAKE_PROJECT_NAME}
project(pico_USB-Host
  C CXX ASM
)

# set C and C++ standard to be used
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# [Platfrom specific command] Initialize the Raspberry Pi Pico SDK
pico_sdk_init()

# set variables for directories
set(PROJECT_ROOT_DIR  "${CMAKE_CURRENT_SOURCE_DIR}")
set(MCULIB_DIR        "${PROJECT_ROOT_DIR}/McuLib")
set(EXECUTABLE         ${PROJECT_NAME}.elf)
set(BUILD_DIR         "${PROJECT_ROOT_DIR}/build")
set(TEST_EXECUTABLE   "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.elf")

add_compile_options(-include "${PROJECT_ROOT_DIR}/src/IncludeMcuLibConfig.h")
include_directories("${MCULIB_DIR}/src")
include_directories("${PROJECT_ROOT_DIR}/src")

# add linker flags to print cross-reference table in map file and memory usage on console
add_link_options(-Wl,--cref,--print-memory-usage)

# to avoid that it shows up as 'Reset' USB device, see https://forums.raspberrypi.com/viewtopic.php?t=324909
add_compile_options(-DPICO_STDIO_USB_ENABLE_RESET_VIA_VENDOR_INTERFACE=0)

add_executable(${CMAKE_PROJECT_NAME}
 # add additional source files here
)

# use tinyusb implementation
#target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE PIO_USB_USE_TINYUSB)
#pico_enable_stdio_usb(${CMAKE_PROJECT_NAME} 1) 

add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
  COMMAND arm-none-eabi-size "${CMAKE_PROJECT_NAME}.elf"
  COMMENT "Printing code and data size"
)

# add component directories to the list
add_subdirectory(./src                  srcLib)

#add_subdirectory(./pico_pio_usb         pico_pio_usb)
# the second argument to add_subdirectory is needed here because this isn't
# a subdirectory, it's out of tree.
#add_subdirectory(./pico_pio_usb pico_pio_usb)

# generate extra files (map/bin/hex/uf2)
pico_add_extra_outputs(${CMAKE_PROJECT_NAME})

target_link_libraries(
  ${CMAKE_PROJECT_NAME}
  PRIVATE pico_stdlib
  PUBLIC srcLib
)
