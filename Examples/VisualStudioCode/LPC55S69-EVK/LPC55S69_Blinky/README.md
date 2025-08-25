# LPC55S69-EVK Blinky
Project for the LPC55S69-EVK, using VS Code with CMake and Ninja, blinking the blue onboard LED.
See https://mcuoneclipse.com/2023/11/27/mcu-link-with-cortex-debug-and-linkserver/

## Environment
The root folder contains several batch files as helper.
In order to have compiler and J-Link not hardcoded in the project itself, rund the setenv script file.

setenv:
```
set TOOLCHAIN_PREFIX=C:/Raspy/arm-none-eabi-gcc-12.2.1-1.2
set SEGGER_PATH=C:/Program Files/SEGGER/JLink
```
Note that the commands have to be set up *before* starting VS Code, to have the environment set.
Alternatively, these variables can be set on user level.

## LinkServer
To use the NXP LinkServer as debug probe (e.g. NXP MCU-Link or MCU-Link Pro), launch it first in a terminal/console as gdbserver:
```
c:\nxp\LinkServer_<version>\LinkServer.exe gdbserver --keep-alive LPC55S69:LPCXpresso55S69
```
