#
# This file is part of the µOS++ distribution.
#   (https://github.com/micro-os-plus)
# Copyright (c) 2021 Liviu Ionescu
#
# This Source Code Form is subject to the terms of the MIT License.
# If a copy of the license was not distributed with this file, it can
# be obtained from https://opensource.org/licenses/MIT/.
#
# -----------------------------------------------------------------------------

# Cross compiling.
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)

set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")

set(triple "")
set(CMAKE_C_COMPILER   "${triple}gcc")
set(CMAKE_CXX_COMPILER "${triple}g++")

# Must be explicit, not set by CMake.
set(CMAKE_SIZE "${triple}size")

# -----------------------------------------------------------------------------

# TODO: understand why CMAKE_<lang>_OUTPUT_EXTENSION is not effective

set(CMAKE_ASM_FLAGS " -x assembler-with-cpp" 
  CACHE STRING "Flags used by the ASM compiler during all build types.")

set(CMAKE_ASM_FLAGS_DEBUG "-O0 -g3" 
  CACHE STRING "Flags used by the ASM compiler during DEBUG builds.")

set(CMAKE_ASM_FLAGS_MINSIZEREL "-Os -DNDEBUG" 
  CACHE STRING "Flags used by the ASM compiler during MINSIZEREL builds.")

set(CMAKE_ASM_FLAGS_RELEASE "-O3 -DNDEBUG" 
  CACHE STRING "Flags used by the ASM compiler during RELEASE builds.")

set(CMAKE_ASM_FLAGS_RELWITHDEBINFO "-O2 -g3 -DNDEBUG" 
  CACHE STRING "Flags used by the ASM compiler during RELWITHDEBINFO builds.")

# Not effective.
set(CMAKE_ASM_OUTPUT_EXTENSION ".o")

set(CMAKE_C_FLAGS 
  CACHE STRING "Flags used by the C compiler during all build types.")

set(CMAKE_C_FLAGS_DEBUG "-O0 -g3" 
  CACHE STRING "Flags used by the C compiler during DEBUG builds.")

set(CMAKE_C_FLAGS_MINSIZEREL "-Os -DNDEBUG" 
  CACHE STRING "Flags used by the C compiler during MINSIZEREL builds.")

set(CMAKE_C_FLAGS_RELEASE "-O3 -DNDEBUG" 
  CACHE STRING "Flags used by the C compiler during RELEASE builds.")

set(CMAKE_C_FLAGS_RELWITHDEBINFO "-O2 -g3 -DNDEBUG" 
  CACHE STRING "Flags used by the C compiler during RELWITHDEBINFO builds.")

# Not effective.
set(CMAKE_C_OUTPUT_EXTENSION ".o")

set(CMAKE_CXX_FLAGS 
  CACHE STRING "Flags used by the CXX compiler during all build types.")

set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g3" 
  CACHE STRING "Flags used by the CXX compiler during DEBUG builds.")

set(CMAKE_CXX_FLAGS_MINSIZEREL "-Os -DNDEBUG" 
  CACHE STRING "Flags used by the CXX compiler during MINSIZEREL builds.")

set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG" 
  CACHE STRING "Flags used by the CXX compiler during RELEASE builds.")

set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g3 -DNDEBUG" 
  CACHE STRING "Flags used by the CXX compiler during RELWITHDEBINFO builds.")

# Not effective.
set(CMAKE_CXX_OUTPUT_EXTENSION ".o")
# set(CMAKE_CXX_OUTPUT_EXTENSION_REPLACE 1)

set(CMAKE_EXE_LINKER_FLAGS 
  CACHE STRING "Flags used by the linker during all build types.")

# Disabled, since apparently CMake already uses the C/CXX flags,
# and defining them here will double them.
if(0)
set(CMAKE_EXE_LINKER_FLAGS_DEBUG "-O0 -g3" 
  CACHE STRING "Flags used by the linker during DEBUG builds.")

set(CMAKE_EXE_LINKER_FLAGS_MINSIZEREL "-Os" 
  CACHE STRING "Flags used by the linker during MINSIZEREL builds.")

set(CMAKE_EXE_LINKER_FLAGS_RELEASE "-O3" 
  CACHE STRING "Flags used by the linker during RELEASE builds.")

set(CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO "-O2 -g3" 
  CACHE STRING "Flags used by the linker during RELWITHDEBINFO builds.")
endif()

# -----------------------------------------------------------------------------
