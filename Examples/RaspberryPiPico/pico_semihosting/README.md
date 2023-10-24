# pico_semihosting
Project using the RP2040 Pico board with VS Code, using semihosting.
See https://mcuoneclipse.com/2023/10/24/implementing-file-i-o-semihosting-for-the-rp2040-and-vs-code/

## McuLib
The project uses the McuLib. The location of the library is specified with the variable 'MCULIB_DIR' in the top-level CMakeLists.txt. The McuLib can be shared with multiple projects.

## Environment
In order for this project to work, the Rasperry Pi Pico SDK needs to be installed and shall have set two environment variables as below (example below for Windows):
```
PICO_SDK_PATH=C:\Raspy\pico\pico-sdk
PICO_TOOLCHAIN_PATH=C:\Raspy\arm-none-eabi-gcc-12.2.1-1.2\bin
```
Additionally, the launch config uses a variable pointing to the SEGGER installation, example below for windows:
```
SEGGER_PATH=C:/Program Files/SEGGER/JLink
```
The variables can be set on user level.

## CMake commands
There are a set of CMake and build related commands you can use, which are availble in .vscode/tasks.json:
- init
    ```
    cmake -G"Ninja" . -B build
    ```

- build:
    ```
    cmake --build build
    ```
- clean:
    ```
    cmake --build build --target clean
    ```

- CleanClean (on Windows, or simply delete the 'build' folder):
    ```
    rmdir /S /Q build 2>nul
    ```
