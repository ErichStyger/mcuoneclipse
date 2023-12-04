cmake_minimum_required(VERSION 3.27)

option(BUILD_SHARED_LIBS "Build using object libraries" 0)

# Required for McuLib, to know the target system
set(
    MCULIB_TARGET MCUXPRESSO CACHE STRING 
    "Select McuLib target: RP2040, MCUXPRESSO or ESP32"
)

# Optional: print out extra messages to see what is going on. Comment it to have less verbose messages
#set(CMAKE_VERBOSE_MAKEFILE ON)

# Set variables for project directory and SDK
set(PROJECT_ROOT_DIR  "${CMAKE_CURRENT_SOURCE_DIR}")
set(MCULIB_DIR        "${PROJECT_ROOT_DIR}/../../../McuLib")
set(SDK_DIR           "${PROJECT_ROOT_DIR}/sdk")
set(BUILD_DIR         "${PROJECT_ROOT_DIR}/build")

# Path to toolchain file. This one has to be before 'project()' below
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/arm-none-eabi-gcc.cmake)

# Setup project name
project(LPC55S16_Blinky)

set(EXECUTABLE ${PROJECT_NAME}.elf)
set(EXECUTABLE_OUTPUT_PATH ${BUILD_DIR}/${CMAKE_BUILD_TYPE})
set(LINKER_FILE "${SDK_DIR}/device/linker.ld")

enable_language(C ASM)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# Build the executable based on the source files
add_executable(${EXECUTABLE} ${SRC_FILES})

# Defines for the project
set(PROJECT_DEFINES
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

if (DEFINED EXTRA_DEFINES) 
  message(STATUS "extra define: ${EXTRA_DEFINES}")
  list(APPEND PROJECT_DEFINES ${EXTRA_DEFINES})
endif()

# List of compiler defines, prefix with -D compiler option. Copy from the project settings
add_compile_options(
  ${PROJECT_DEFINES}
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
  ${PROJECT_DEFINES}
)

# Linker options
target_link_options(${EXECUTABLE} PRIVATE
  -L "${PROJECT_ROOT_DIR}/sdk/LPC55S16/mcuxpresso/" # needed to find libraries like libpower_hardabi.a
  -T "${LINKER_FILE}"
)

# McuLib to find our local header files
add_compile_options(-include "${PROJECT_ROOT_DIR}/src/IncludeMcuLibConfig.h")
add_compile_options(-I${PROJECT_ROOT_DIR}/src -I${PROJECT_ROOT_DIR}/sdk/drivers)
add_compile_options(-I${SDK_DIR}/device -I${SDK_DIR}/CMSIS -I${SDK_DIR}/board) 

add_subdirectory(./src                  src) 
add_subdirectory(${SDK_DIR}             sdk)
add_subdirectory(${MCULIB_DIR}          McuLib)
add_subdirectory(${MCULIB_DIR}/rdimon   rdimon)

target_link_libraries(
  ${EXECUTABLE}
  srcLib
  sdkLib
  McuLib
  rdimonLib # file I/O with semihosting
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
