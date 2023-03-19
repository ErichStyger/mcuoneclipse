Project for the Raspberry Pi Pico using the BLE module and functionality.

See:
https://mcuoneclipse.com/2023/03/19/ble-with-wifi-and-freertos-on-raspberry-pi-pico-w/

The project implements a client and a server (standalone BLE):
The server provides temperature data, and the client gets the data from the server.

To switch between client and server:
a) change PL_CONFIG_STANDALONE_BLE_TEMP_SENSOR_CLIENT in src/app_platform.h
b) touch the file src/btstack_config.h to force a recompilation of the BT library

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

