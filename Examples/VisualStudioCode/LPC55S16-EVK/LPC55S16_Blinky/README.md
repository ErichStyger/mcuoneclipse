# LPC55S16-EVK Blinky
Project for the LPC55S16-EVK, using VS Code with CMake and Ninja, blinking the blue onboard LED.
See https://mcuoneclipse.com/2023/11/27/mcu-link-with-cortex-debug-and-linkserver/

## Environment
A recent `cmake` and `ninja` needs to be installed. For debugging you need the *NXP LinkServer* and/or *SEGGER J-Link* tools installed.

In order to have compiler and debugging tools not hardcoded in the project itself, run the `setenv` script in the project root folder.

Note that the environment has to be set *before* starting VS Code.
Alternatively, you can set the variables `TOOLCHAIN_PREFIX` and `SEGGER_PATH` on the user level.

## Building
To build the project on the console/commandline with CMake presets (see https://mcuoneclipse.com/2023/12/03/building-with-cmake-presets/):

Configure the project:
```
cmake --configure debug
```
Build it:
```
cmake --build --preset debug
```


## LinkServer
To use the NXP LinkServer as debug probe (e.g. NXP MCU-Link or MCU-Link Pro), launch it first in a terminal/console as gdbserver:
```
LinkServer gdbserver --keep-alive LPC55S16:LPCXpresso55S16
```
Alternatively, you can use the menu `Terminal` -> `Run Task` -> `start LinkServer` menu.
