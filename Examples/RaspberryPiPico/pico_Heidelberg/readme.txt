Project for the Raspberry Pi Pico (W) controlling a Heidelberg Energy Control Wallbox over Modbus.

See  
- https://mcuoneclipse.com/2022/12/31/controlling-an-ev-charger-with-modbus-rtu/
- https://mcuoneclipse.com/2023/02/11/using-mqtt-with-the-raspberry-pi-pico-w-and-homeassistant-for-an-optimized-solar-energy-electrical-vehicle-charger/

Files needed: (besides this readme.txt)

./pico_sdk_import.cmake
./CMakeLists.txt
./src folder
./McuLib folder
./.gitignore


To configure (cd to project root directory where this readme is located):
run 'cmake init.bat'
Import the project as 'existing make file project' into Eclipse: File > Import > C/C++ > Existing Code as Makefile Project (give it a name, use this folder as code location, specify GNU Autotools toolchain, then build it

or: simply run 'make' to build it


LED Counter App:
----------------
button view with USB connector on the left
left (usb side): decrement counter
right: increment counter
up: increment brightness, keep pressed for faster increment
down: decrement brightness, keep pressed for aster decrememnt
middle: change light mode (warm white, fading, random, ...)
long press middle: turn on/off

