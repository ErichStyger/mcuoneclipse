# Call Cmake from the 'build' subfolder with the command below.
# For using Make:
# cmake -DCMAKE_MAKE_PROGRAM=make.exe -DCMAKE_TOOLCHAIN_FILE="arm-none-eabi-gcc.cmake" -G "Unix Makefiles" ..
# followed by
# 'make' or 'cmake --build .' to build it
# or see the .bat files in the project

# Append current directory to CMAKE_MODULE_PATH for making device specific cmake modules visible
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR})

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR ARM)

#set (TOOLCHAIN_PREFIX "C:/Program Files (x86)/GNU Arm Embedded Toolchain/10 2020-q4-major")
#set (TOOLCHAIN_PREFIX "C:/Raspy/arm-none-eabi-gcc-12.2.1-1.2")
set (TOOLCHAIN_PREFIX $ENV{TOOLCHAIN_PREFIX})  # set in system environment
#---------------------------------------------------------------------------------------
# Set toolchain paths
#---------------------------------------------------------------------------------------
set(TOOLCHAIN arm-none-eabi)
if(NOT DEFINED TOOLCHAIN_PREFIX)
    if(CMAKE_HOST_SYSTEM_NAME STREQUAL Linux)
        set(TOOLCHAIN_PREFIX "/usr")
    elseif(CMAKE_HOST_SYSTEM_NAME STREQUAL Darwin)
        set(TOOLCHAIN_PREFIX "/usr/local")
    elseif(CMAKE_HOST_SYSTEM_NAME STREQUAL Windows)
        message(STATUS "Please specify the TOOLCHAIN_PREFIX !\n For example: -DTOOLCHAIN_PREFIX=\"C:/Program Files/GNU Tools ARM Embedded\" ")
    else()
        set(TOOLCHAIN_PREFIX "/usr")
        message(STATUS "No TOOLCHAIN_PREFIX specified, using default: " ${TOOLCHAIN_PREFIX})
    endif()
endif()
set(TOOLCHAIN_BIN_DIR ${TOOLCHAIN_PREFIX}/bin)
set(TOOLCHAIN_INC_DIR ${TOOLCHAIN_PREFIX}/${TOOLCHAIN}/include)
set(TOOLCHAIN_LIB_DIR ${TOOLCHAIN_PREFIX}/${TOOLCHAIN}/lib)

# Set system depended extensions
if(WIN32)
    set(TOOLCHAIN_EXT ".exe" )
else()
    set(TOOLCHAIN_EXT "" )
endif()

# Perform compiler test with static library
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

# point ARM_TOOLCHAIN_BIN_DIR to things like
# set ARM_TOOLCHAIN_BIN_DIR="C:/Program Files (x86)/GNU Arm Embedded Toolchain/10 2020-q4-major/bin"
# or
# set ARM_TOOLCHAIN_BIN_DIR="C:/NXP/MCUXpressoIDE_11.7.0_9198/ide/tools/bin"
# on the system level, or have it defined here.
#set(ARM_TOOLCHAIN_BIN_DIR "C:/Program Files (x86)/GNU Arm Embedded Toolchain/10 2020-q4-major/bin")

#set(ARM_TOOLCHAIN_DIR ${ARM_TOOLCHAIN_BIN_DIR})
#set(BINUTILS_PATH ${ARM_TOOLCHAIN_BIN_DIR}) 

#set(TOOLCHAIN_PREFIX arm-none-eabi-)

#set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

#set(CMAKE_C_COMPILER "${TOOLCHAIN_PREFIX}gcc")
#set(CMAKE_ASM_COMPILER ${CMAKE_C_COMPILER})
#set(CMAKE_CXX_COMPILER "${TOOLCHAIN_PREFIX}g++")

set(CMAKE_OBJCOPY ${TOOLCHAIN_BIN_DIR}/${TOOLCHAIN}-objcopy${TOOLCHAIN_EXT} CACHE INTERNAL "objcopy tool")
set(CMAKE_SIZE_UTIL ${TOOLCHAIN_BIN_DIR}/${TOOLCHAIN}-size${TOOLCHAIN_EXT} CACHE INTERNAL "size tool")

#set(CMAKE_FIND_ROOT_PATH ${BINUTILS_PATH})
#set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
#set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
#set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

set(OBJECT_GEN_FLAGS "-O0 -fno-common -g3 -ggdb -Wall -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fno-common -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb")

set(CMAKE_C_FLAGS   "${OBJECT_GEN_FLAGS} -std=gnu99 " CACHE INTERNAL "C Compiler options")
set(CMAKE_CXX_FLAGS "${OBJECT_GEN_FLAGS} -std=c++11 " CACHE INTERNAL "C++ Compiler options")
set(CMAKE_ASM_FLAGS "${OBJECT_GEN_FLAGS} -x assembler-with-cpp " CACHE INTERNAL "ASM Compiler options")

# -Wl,--gc-sections     Perform the dead code elimination.
# --specs=nano.specs    Link with newlib-nano.
# --specs=nosys.specs   No syscalls, provide empty implementations for the POSIX system calls.
set(CMAKE_EXE_LINKER_FLAGS "-nostdlib -Wl,--gc-sections,--cref,--print-memory-usage,--sort-section=alignment --specs=nano.specs --specs=nosys.specs -mthumb -Wl,-Map=${CMAKE_PROJECT_NAME}.map" CACHE INTERNAL "Linker options")

# Options for DEBUG build
# -Og   Enables optimizations that do not interfere with debugging.
# -g    Produce debugging information in the operating system’s native format.
set(CMAKE_C_FLAGS_DEBUG "-DDEBUG -Og -ggdb" CACHE INTERNAL "C Compiler options for debug build type")
set(CMAKE_CXX_FLAGS_DEBUG "-Og -ggdb" CACHE INTERNAL "C++ Compiler options for debug build type")
set(CMAKE_ASM_FLAGS_DEBUG "" CACHE INTERNAL "ASM Compiler options for debug build type")
set(CMAKE_EXE_LINKER_FLAGS_DEBUG "-ggdb" CACHE INTERNAL "Linker options for debug build type")

# Options for RELEASE build
# -Os   Optimize for size. -Os enables all -O2 optimizations.
# -flto Runs the standard link-time optimizer.
set(CMAKE_C_FLAGS_RELEASE "-DNDEBUG -Os -flto" CACHE INTERNAL "C Compiler options for release build type")
set(CMAKE_CXX_FLAGS_RELEASE "-Os -flto" CACHE INTERNAL "C++ Compiler options for release build type")
set(CMAKE_ASM_FLAGS_RELEASE "" CACHE INTERNAL "ASM Compiler options for release build type")
set(CMAKE_EXE_LINKER_FLAGS_RELEASE "-flto" CACHE INTERNAL "Linker options for release build type")

#---------------------------------------------------------------------------------------
# Set compilers
#---------------------------------------------------------------------------------------
set(CMAKE_C_COMPILER ${TOOLCHAIN_BIN_DIR}/${TOOLCHAIN}-gcc${TOOLCHAIN_EXT} CACHE INTERNAL "C Compiler")
set(CMAKE_CXX_COMPILER ${TOOLCHAIN_BIN_DIR}/${TOOLCHAIN}-g++${TOOLCHAIN_EXT} CACHE INTERNAL "C++ Compiler")
set(CMAKE_ASM_COMPILER ${TOOLCHAIN_BIN_DIR}/${TOOLCHAIN}-gcc${TOOLCHAIN_EXT} CACHE INTERNAL "ASM Compiler")

set(CMAKE_FIND_ROOT_PATH ${TOOLCHAIN_PREFIX}/${${TOOLCHAIN}} ${CMAKE_PREFIX_PATH})
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)
