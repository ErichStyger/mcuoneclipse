Project for the Raspberry Pi Pico (W) controlling a Heidelberg Energy Control Wallbox over Modbus.
See  https://mcuoneclipse.com/2022/12/31/controlling-an-ev-charger-with-modbus-rtu/

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

