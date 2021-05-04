# About

The aim of this project is to provide a software development environment based on CMake, GCC and openOCD for several bare metal ARM platforms.

# Requirements

   * CMake >= 3.6
   * GCC arm-none-abi
     * Linux Arch: `arm-none-eabi-gcc` `arm-none-eabi-binutils` `arm-none-eabi-newlib`
     * Ubuntu packages: Since the package of the official repo is very old it is recommended to use this [PPA](https://launchpad.net/~team-gcc-arm-embedded/+archive/ubuntu/ppa)

# Features

 * General CMake Toolchain file for arm-none-eabi-gcc
 * Target specific extension of Toolchain file

# Usage

Add this project as git submodule to your repository:

    git submodule add https://github.com/jobroe/cmake-arm-embedded.git cmake


Set the Linker Script and include the target specific cmake module in your project CMakeLists.txt e.g.:

```
set(LINKER_SCRIPT "${Gecko_SDK_PATH}/platform/Device/SiliconLabs/EFR32MG12P/Source/GCC/efr32mg12p.ld")

include(efr32mg)

```

Go to your project root directory, create build directory and enter it:

    mkdir build

    cd build

run to configure:

    cmake -DCMAKE_TOOLCHAIN_FILE=cmake/toolchain-arm-none-eabi.cmake ..

and finally to build:

    make
