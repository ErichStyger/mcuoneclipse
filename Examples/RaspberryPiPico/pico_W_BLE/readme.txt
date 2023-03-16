Project for the Raspberry Pi Pico using the BLE module and functionality.

Files needed: (besides this readme.txt):
./pico_sdk_import.cmake
./CMakeLists.txt
./src/main.c
./.gitignore

The project uses the McuLib (one folder above this directory) which is shared among different projects.

To remove all temporary files, run 'clean.bat'.
To generate make files and Eclipse project files using cmake, run 'cmake init.bat'

then run 'make' to build the project, or use Eclipse to build it and debug it.

References:
- https://mcuoneclipse.com/2022/07/16/getting-started-raspberry-pi-pico-rp2040-with-eclipse-and-j-link/

