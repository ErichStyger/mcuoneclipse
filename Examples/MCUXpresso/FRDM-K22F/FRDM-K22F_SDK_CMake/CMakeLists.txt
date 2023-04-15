# CMake template file
# Use this file with
# mkdir build
# cd build
# cmake -G "Eclipse CDT4" -DCMAKE_MAKE_PROGRAM=ninja -DCMAKE_BUILD_TYPE=Debug -DCMAKE_ECLIPSE_VERSION="4.5" -DCMAKE_ECLIPSE_GENERATE_SOURCE_PROJECT=TRUE -DCMAKE_ECLIPSE_MAKE_ARGUMENTS=-j8 -DCMAKE_ECLIPSE_EXECUTABLE="C:\NXP\MCUXpressoIDE_11.6.0_8187\ide\mcuxpressoide.exe" ../src 
#

cmake_minimum_required(VERSION 3.15.3)

# Optional: print out extra messages to see what is going on. Comment it to have less verbose messages
#set(CMAKE_VERBOSE_MAKEFILE ON)

# To make sure build folder doesn't get cluttered
#set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)  # place CMakeFiles folder into the build folder
#set(CMAKE_CURRENT_BINARY_DIR ${CMAKE_BINARY_DIR}/build)
#set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)
#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)

# enable export of compiler commands to compile_commands.json
#set (CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Path to toolchain file. This one has to be before 'project()' below
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/arm-none-eabi-gcc.cmake)

# Setup project, output and linker file
set(BUILD_FOLDER ./build)
project(FRDM-K22F_CMake)
set(EXECUTABLE ${PROJECT_NAME}.elf)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/build)
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

target_link_libraries(
  ${EXECUTABLE}
  # might have circular library dependencies, see https://stackoverflow.com/questions/45135/why-does-the-order-in-which-libraries-are-linked-sometimes-cause-errors-in-gcc
  board
  drivers
  utilities
  component
)

# List of compiler defines, prefix with -D compiler option. Copy from the project settings
add_compile_options(
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

# List of includ directories
target_include_directories(${EXECUTABLE} PRIVATE
    . 
    CMSIS
    board
    component/serial_manager
    component/uart
    component/lists
    device
    drivers
    startup
    utilities
)

# Compiler options
target_compile_options(${EXECUTABLE} PRIVATE
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

# Linker options
target_link_options(${EXECUTABLE} PRIVATE
  -L "${CMAKE_SOURCE_DIR}/ld"
  -T "${LINKER_FILE}"
  -mcpu=cortex-m4
  -mthumb
  -mfpu=fpv4-sp-d16 
  -mfloat-abi=hard
  -specs=nano.specs
  -specs=nosys.specs
  -lc
  -lm
  -Wl,-Map=${EXECUTABLE_OUTPUT_PATH}/${PROJECT_NAME}.map,--cref
  -Wl,--gc-sections
  -Xlinker -print-memory-usage -Xlinker
)

add_subdirectory(./board     build/board)
add_subdirectory(./drivers   build/drivers)
add_subdirectory(./utilities build/utilities)
add_subdirectory(./component build/component)


# Optional: Print executable size as part of the post build process
add_custom_command(TARGET ${EXECUTABLE}
        POST_BUILD
        COMMAND ${CMAKE_SIZE_UTIL} ${EXECUTABLE_OUTPUT_PATH}/${EXECUTABLE})

# Optional: Create hex, bin and S-Record files after the build
add_custom_command(TARGET ${EXECUTABLE}
        POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -O srec --srec-len=64 "${EXECUTABLE_OUTPUT_PATH}/${EXECUTABLE}" "${EXECUTABLE_OUTPUT_PATH}/${PROJECT_NAME}.s19"
        COMMAND ${CMAKE_OBJCOPY} -O ihex "${EXECUTABLE_OUTPUT_PATH}/${EXECUTABLE}" "${EXECUTABLE_OUTPUT_PATH}/${PROJECT_NAME}.hex"
        COMMAND ${CMAKE_OBJCOPY} -O binary "${EXECUTABLE_OUTPUT_PATH}/${EXECUTABLE}" "${EXECUTABLE_OUTPUT_PATH}/${PROJECT_NAME}.bin" 
        )
