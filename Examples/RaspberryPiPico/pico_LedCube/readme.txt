Project for the Raspberry Pi Pico (W or non-W) controlling 8x8x8(2) RGB LED Cube with PIO and DMA.

Article about this project:
https://mcuoneclipse.com/2023/04/02/rp2040-with-pio-and-dma-to-address-ws2812b-leds/

KiCAD files:
https://github.com/ErichStyger/mcuoneclipse/tree/master/KiCAD/Projects/PicoWS2812B

Files needed: (besides this readme.txt)

./pico_sdk_import.cmake
./CMakeLists.txt
./src folder
../McuLib folder
./.gitignore


To configure (cd to project root directory where this readme is located):
run 'cmake init.bat'
Import the project as 'existing make file project' into Eclipse: File > Import > C/C++ > Existing Code as Makefile Project (give it a name, use this folder as code location, specify GNU Autotools toolchain, then build it

or: simply run 'make' to build it


cleanclean:
rmdir /S /Q build 2>nul

init:
cmake -G"Ninja" . -B build

build:
cmake --build build

clean:
cmake --build build --target clean
