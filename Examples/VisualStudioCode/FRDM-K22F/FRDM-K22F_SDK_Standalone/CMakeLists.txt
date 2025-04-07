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
project(ares_tinyk22)

set(EXECUTABLE ${PROJECT_NAME}.elf)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LINKER_FILE "${SDK_DIR}/device/linker.ld")

enable_language(C ASM)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# Build the executable based on the source files
add_executable(${EXECUTABLE} ${SRC_FILES})

set(PROJECT_DEFINES
  -DCPU_MK22FN512VLH12
  -DCPU_MK22FN512VLH12_cm4
  -DSDK_OS_BAREMETAL
  -DSDK_DEBUGCONSOLE=1
  -DCR_INTEGER_PRINTF
  -DPRINTF_FLOAT_ENABLE=0
  -DSERIAL_PORT_TYPE_UART=1
  -D__MCUXPRESSO
  -D__USE_CMSIS
  -DNDEBUG
  -D__NEWLIB__
)

if (CMAKE_BUILD_TYPE STREQUAL "gcov")
  list(APPEND PROJECT_DEFINES -DPL_CONFIG_USE_GCOV=1)
endif()

if (CMAKE_BUILD_TYPE STREQUAL "gprof")
  list(APPEND PROJECT_DEFINES -DPL_CONFIG_USE_GPROF=1)
endif()

add_compile_options(
  ${PROJECT_DEFINES}

  -O0
  -fno-common
  -g3
  -Wall

  -ffunction-sections 
  -fdata-sections 

  -ffreestanding 
  #-fno-builtin 
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
  -T "${LINKER_FILE}"
)

# McuLib to find our local header files
add_compile_options(-include "${PROJECT_ROOT_DIR}/src/IncludeMcuLibConfig.h")
add_compile_options(-Wno-builtin-macro-redefined)

include_directories(${PROJECT_ROOT_DIR}/src)
include_directories(${PROJECT_ROOT_DIR}/sdk/drivers)
include_directories(${SDK_DIR}/device)
include_directories(${SDK_DIR}/CMSIS)
include_directories(${SDK_DIR}/board) 

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
