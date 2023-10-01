# LPC55S16-EVK Blinky

Project for the LPC55S16-EVK, using VS Code with CMake and Ninja, blinking the blue onboard LED.

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

## CMake commands
There are a set of CMake and build related commands you can use:

init:
```
cmake -G"Ninja" . -B build
```

build:
```
cmake --build build
```

clean:
```
cmake --build build --target clean
```

CleanClean:
```
rmdir /S /Q build 2>nul
```
