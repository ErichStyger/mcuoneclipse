cmake_minimum_required(VERSION 3.1...3.27)

option(BUILD_SHARED_LIBS "Build using object libraries" 0)

# turn variable on for verbose output, useful for build debugging. Or run 'ninja --verbose' in the build folder
#set(CMAKE_VERBOSE_MAKEFILE ON CACHE BOOL "ON")
# Path to toolchain file. This one has to be before 'project()' below
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/arm-none-eabi-gcc.cmake)

# Setup project name
project(FRDM-K22F_CMake)

# set variables for directories
set(PROJECT_ROOT_DIR  "${CMAKE_CURRENT_SOURCE_DIR}")
set(MCULIB_DIR        "${PROJECT_ROOT_DIR}/McuLib")
set(EXECUTABLE         ${PROJECT_NAME}.elf)
set(SDK_DIR           "${PROJECT_ROOT_DIR}/sdk")
set(BUILD_DIR         "${PROJECT_ROOT_DIR}/build")

set(LINKER_FILE "MK22F51212_Project_CMake_Debug.ld")

enable_language(C ASM)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# Optional: issue a message to be sure it uses the correct toolchain file.
message(STATUS "CMAKE_TOOLCHAIN_FILE is: ${CMAKE_TOOLCHAIN_FILE}")

# List of source files
set(SRC_FILES
  source/main.c
  startup/startup_mk22f51212.c
  device/system_MK22F51212.c
)

# Build the executable based on the source files
add_executable(${EXECUTABLE} ${SRC_FILES})

# Defines for the project
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
  -DDEBUG
  -D__NEWLIB__
)

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
  -L "${CMAKE_SOURCE_DIR}/ld"
  -T "${LINKER_FILE}"
)

# add linker flags to print cross-reference table in map file and memory usage on console
add_link_options(-Wl,--cref,--print-memory-usage)

add_subdirectory(./board     board)
add_subdirectory(./drivers   drivers)
add_subdirectory(./utilities utilities)
add_subdirectory(./component component)

target_link_libraries(
  ${EXECUTABLE}
  PUBLIC board
  PUBLIC drivers
  PUBLIC utilities
  PUBLIC component
)

# Optional: Print executable size as part of the post build process
add_custom_command(TARGET ${EXECUTABLE}
  POST_BUILD
  COMMAND ${CMAKE_SIZE_UTIL} ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE}
)

# Optional: Create hex, bin and S-Record files after the build
add_custom_command(TARGET ${EXECUTABLE}
  POST_BUILD
  COMMAND ${CMAKE_OBJCOPY} -O srec --srec-len=64 "${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE}" "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.s19"
  COMMAND ${CMAKE_OBJCOPY} -O ihex "${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE}" "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.hex"
  COMMAND ${CMAKE_OBJCOPY} -O binary "${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE}" "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.bin" 
)
