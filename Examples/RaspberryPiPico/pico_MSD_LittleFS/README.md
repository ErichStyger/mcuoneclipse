# Pico MSD LittleFS
Project for the Raspberry Pi Pico, using USB MSD device as interface to LittleFS file system.
See https://github.com/oyama/pico-littlefs-usb

Note: file names need to use upper-case characters!

## McuLib
The project uses the McuLib. The location of the library is specified with the variable 'MCULIB_DIR' in the top-level CMakeLists.txt. The McuLib can be shared with multiple projects.

# Newlib/Newlib-nano
Can also switch to newlib-nano by putting 
```
"target_link_options(pico_runtime INTERFACE "--specs=nosys.specs" "--specs=nano.specs")"
```
 in pico-sdk/src/rp2_common/pico_runtime/CMakeLists.txt

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

# Links
Making links to folders:
```
mklink /D McuLib ..\..\McuLib
```

## CMake commands
There are a set of CMake and build related commands you can use, which are availble in .vscode/tasks.json:
- configure:
    ```
    cmake --preset debug
    ```

- build:
    ```
    cmake --build --preset debug
    ```
- clean:
    ```
    cmake --build build --preset debug --target clean
    ```
