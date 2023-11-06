cmake_minimum_required(VERSION 3.15.3)

option(BUILD_SHARED_LIBS "Build using object libraries" 0)

# Required for McuLib, to know the target system
set(
    MCULIB_TARGET MCUXPRESSO CACHE STRING 
    "Select McuLib target: RP2040, MCUXPRESSO or ESP32"
)

# Optional: print out extra messages to see what is going on. Comment it to have less verbose messages
#set(CMAKE_VERBOSE_MAKEFILE ON)

# set build type. Without 'Debug', it won't generate line information if using build subfolders.
set(CMAKE_BUILD_TYPE DEBUG)

# enable export of compiler commands to compile_commands.json
#set (CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Path to toolchain file. This one has to be before 'project()' below
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/arm-none-eabi-gcc.cmake)

# Setup project, output and linker file
set(BUILD_FOLDER ./build)
project(LPC55S16_gcov)

set(EXECUTABLE ${PROJECT_NAME}.elf)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/build)
set(LINKER_FILE "../sdk/device/linker.ld")

enable_language(C ASM)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(CMAKE_BUILD_TYPE Debug)

# Optional: issue a message to be sure it uses the correct toolchain file.
message(STATUS "CMAKE_TOOLCHAIN_FILE is: ${CMAKE_TOOLCHAIN_FILE}")

# List of source files
set(SRC_FILES
  ./sdk/startup/startup_lpc55s16.c
  ./sdk/device/system_LPC55S16.c
)

# Build the executable based on the source files
add_executable(${EXECUTABLE} ${SRC_FILES})

# List of compiler defines, prefix with -D compiler option. Copy from the project settings
add_compile_options(
  -DCPU_LPC55S16JBD100
  -DCPU_LPC55S16JBD100_cm33
  -DSDK_OS_BAREMETAL
  -DSDK_DEBUGCONSOLE=1
  -DCR_INTEGER_PRINTF
  -DPRINTF_FLOAT_ENABLE=0
  -DSERIAL_PORT_TYPE_UART=1
  -D__MCUXPRESSO
  -D__USE_CMSIS
  -DDEBUG
  -D__NEWLIB__

   -O0 
   -fno-common 
   -g3 
   -Wall 
  
   -ffunction-sections 
   -fdata-sections 
  
   -ffreestanding 
   -fno-builtin 
   -fmerge-constants 
   -mcpu=cortex-m4 
   -mfpu=fpv4-sp-d16 
   -mfloat-abi=hard 
   -mthumb
)

target_compile_definitions(${EXECUTABLE} PRIVATE
  -DCPU_LPC55S16JBD100
  -DCPU_LPC55S16JBD100_cm33
  -DSDK_OS_BAREMETAL
  -DSDK_DEBUGCONSOLE=1
  -DCR_INTEGER_PRINTF
  -DPRINTF_FLOAT_ENABLE=0
  -DSERIAL_PORT_TYPE_UART=1
  -D__MCUXPRESSO
  -D__USE_CMSIS
  -DDEBUG
  -D__NEWLIB__
)

set(PROJECT_ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
add_compile_options(-include "${PROJECT_ROOT_DIR}/src/IncludeMcuLibConfig.h")

# Linker options
target_link_options(${EXECUTABLE} PRIVATE
  -L "${PROJECT_ROOT_DIR}/sdk/LPC55S16/mcuxpresso/"
  -T "${LINKER_FILE}"
)

# McuLib to find our local header files
add_compile_options(-I${PROJECT_ROOT_DIR}/src -I${PROJECT_ROOT_DIR}/sdk/drivers)

# RNET to find SDK header files
add_compile_options(-I${PROJECT_ROOT_DIR}/sdk/device -I${PROJECT_ROOT_DIR}/sdk/CMSIS -I${PROJECT_ROOT_DIR}/sdk/board) 

add_subdirectory(./sdk              build/sdk) 
add_subdirectory(./src              build/src)
add_subdirectory(./../../../McuLib  build/McuLib)
add_subdirectory(./sdk/board        build/sdk/board)
add_subdirectory(./sdk/drivers      build/sdk/drivers)
add_subdirectory(./sdk/utilities    build/sdk/utilities)
add_subdirectory(./sdk/component    build/sdk/component)

target_link_libraries(
  ${EXECUTABLE}
  sdkLib
  componentLib
  McuLib
  boardLib
  driversLib
  utilitiesLib
  srcLib
)

# Optional: Print executable size as part of the post build process
add_custom_command(TARGET ${EXECUTABLE}
  POST_BUILD
  COMMAND ${CMAKE_SIZE_UTIL} ${EXECUTABLE_OUTPUT_PATH}/${EXECUTABLE}
)

# Optional: Create hex, bin and S-Record files after the build
add_custom_command(TARGET ${EXECUTABLE}
  POST_BUILD
  COMMAND ${CMAKE_OBJCOPY} -O srec --srec-len=64 "${EXECUTABLE_OUTPUT_PATH}/${EXECUTABLE}" "${EXECUTABLE_OUTPUT_PATH}/${PROJECT_NAME}.s19"
  COMMAND ${CMAKE_OBJCOPY} -O ihex "${EXECUTABLE_OUTPUT_PATH}/${EXECUTABLE}" "${EXECUTABLE_OUTPUT_PATH}/${PROJECT_NAME}.hex"
  COMMAND ${CMAKE_OBJCOPY} -O binary "${EXECUTABLE_OUTPUT_PATH}/${EXECUTABLE}" "${EXECUTABLE_OUTPUT_PATH}/${PROJECT_NAME}.bin" 
)
