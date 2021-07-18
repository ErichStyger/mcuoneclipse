#
# This file is part of the xPack project (http://xpack.github.io).
# Copyright (c) 2021 Liviu Ionescu
#
# This Software is provided under the terms of the MIT License.
# If a copy of the license was not distributed with this file, it can
# be obtained from https://opensource.org/licenses/MIT/.
#
# -----------------------------------------------------------------------------

# https://cmake.org/cmake/help/v3.19/
cmake_minimum_required(VERSION 3.19)

message(STATUS "CMake version: ${CMAKE_VERSION}")

if(CMAKE_BINARY_DIR STREQUAL CMAKE_SOURCE_DIR)
  message(FATAL_ERROR "In-source builds are not supported. Please use separate folder for build.")
endif()

# -----------------------------------------------------------------------------

enable_language(C)
enable_language(ASM)

# Specify the C standard.
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)

message(STATUS "Compiler: ${CMAKE_C_COMPILER_ID} ${CMAKE_C_COMPILER_VERSION}")

# Generate the compile_commands.json file to feed the indexer.
# It is recommended to be passed on the command line to make it very clear
# that it is mandatory, but can also be passed here, for just in case.
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# -----------------------------------------------------------------------------

get_filename_component(xpack_project_folder ${CMAKE_SOURCE_DIR} DIRECTORY)

# -----------------------------------------------------------------------------

# message(STATUS "Host system name: ${CMAKE_HOST_SYSTEM_NAME}")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "Project path: ${xpack_project_folder}")
# message(STATUS "Prefix path: ${CMAKE_PREFIX_PATH}")
message(STATUS "PATH: $ENV{PATH}")

# -----------------------------------------------------------------------------

project(
	hello-world
	DESCRIPTION "A simple Hello World application"
)

# -----------------------------------------------------------------------------

# https://cmake.org/cmake/help/v3.19/variable/CMAKE_LANG_COMPILER_ID.html

# Preprocessor definitions.
add_compile_definitions(
  $<$<STREQUAL:"${CMAKE_BUILD_TYPE}","Debug">:DEBUG>

  # Enable this if not already defined by the toolchain.
  # $<$<NOT:$<STREQUAL:"${CMAKE_BUILD_TYPE}","Debug">>:NDEBUG>
)

# Options for both compilers and linkers. When using -flto all options
# must also be passed to the linker.
set(common_options 

  $<$<C_COMPILER_ID:GNU,Clang,AppleClang>:-fmessage-length=0>
  $<$<C_COMPILER_ID:GNU,Clang,AppleClang>:-fsigned-char>

  $<$<C_COMPILER_ID:GNU,Clang,AppleClang>:-ffunction-sections>
  $<$<C_COMPILER_ID:GNU,Clang,AppleClang>:-fdata-sections>
  # $<$<C_COMPILER_ID:MSVC>:> # Add MSVC options here.

  # Optional, comment it out to disable link time optimizations.
  $<$<C_COMPILER_ID:GNU,Clang,AppleClang>:-flto>
)

add_compile_options(

  ${common_options}
)

add_link_options(

  ${common_options}
)

if("${CMAKE_HOST_SYSTEM_NAME}" STREQUAL "Darwin")
  # macOS always uses the Apple linker, regarless of the compiler.
  add_link_options(
    -Wl,-dead_strip
  )
else()
  add_link_options(
    $<$<C_COMPILER_ID:GNU>:-Wl,--gc-sections>
    # $<$<C_COMPILER_ID:MSVC>:> # Add MSVC options here.
  )
endif()

# -----------------------------------------------------------------------------
# Create the application.

# Monolithic build, no libraries; all sources are compiled in the same
# context, with all headers and definitions.

add_executable(application)
message(STATUS "==> application")

set_target_properties(
  application

  PROPERTIES
    OUTPUT_NAME "${CMAKE_PROJECT_NAME}"
)

# Application sources.
target_sources(
  application

  PRIVATE
    ${xpack_project_folder}/src/hello-world.c
    ${xpack_project_folder}/libs/adder/src/add.c
)

# Application includes.
target_include_directories(
  application

  PRIVATE
    ${xpack_project_folder}/include
    ${xpack_project_folder}/libs/adder/include
)

# -----------------------------------------------------------------------------
