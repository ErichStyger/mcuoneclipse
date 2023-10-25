cmake_minimum_required(VERSION 3.2...3.5)

#set(CMAKE_BUILD_TYPE Release)
#set(CMAKE_BUILD_TYPE Debug)  # default

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
project(pico_semihosting
  C CXX ASM
)

# set C and C++ standard to be used
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# [Platfrom specific command] Initialize the Raspberry Pi Pico SDK
pico_sdk_init()

# set variables for directories
set(PROJECT_ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
set(MCULIB_DIR       "${CMAKE_CURRENT_SOURCE_DIR}/../../McuLib")

# make sure, that the output files and binaries are in the build folder
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/build)

add_compile_options(-include "${PROJECT_ROOT_DIR}/src/IncludeMcuLibConfig.h")
add_compile_options(-I "${PROJECT_ROOT_DIR}/src") # McuLib to find our local header files

# add linker flags to print cross-reference table in map file and memory usage on console
add_link_options(-Wl,--cref,--print-memory-usage)

# to avoid that it shows up as 'Reset' USB device, see https://forums.raspberrypi.com/viewtopic.php?t=324909
add_compile_options(-DPICO_STDIO_USB_ENABLE_RESET_VIA_VENDOR_INTERFACE=0)

add_executable(${CMAKE_PROJECT_NAME}
  # add additional source files here
)

add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
  COMMAND arm-none-eabi-size "${CMAKE_PROJECT_NAME}.elf"
  COMMENT "Printing code and data size"
)

# add component directories to the list
add_subdirectory(${MCULIB_DIR}          build/McuLib)
add_subdirectory(${MCULIB_DIR}/rdimon   build/rdimon)
add_subdirectory(./src                  build/src)

# generate extra files (map/bin/hex/uf2)
pico_add_extra_outputs(${CMAKE_PROJECT_NAME})

target_link_libraries(
  ${CMAKE_PROJECT_NAME}
  # might have circular library dependencies, see https://stackoverflow.com/questions/45135/why-does-the-order-in-which-libraries-are-linked-sometimes-cause-errors-in-gcc
  pico_stdlib # pico SDK standard library
  rdimonLib # file I/O with semihosting
  SrcLib  # need to have the other standard libraries here, as we overwrite the weak function in runtime.c
  McuLib
  SrcLib  # again because of FreeRTOShooks.c
)
