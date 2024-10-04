# pico_USB-Host
Project for the Adafruit RP2040 with USB Type A Host:
https://learn.adafruit.com/adafruit-feather-rp2040-with-usb-type-a-host
USB Host D+ pin: GPIO16
USB Host D- pin: GPIO17

USB-Host is based on the work of https://github.com/sekigon-gonnoc/Pico-PIO-USB


## cheat sheet
Configure:
cmake --list-presets
cmake --preset debug
cmake --preset test

Build:
cmake --build --list-presets
cmake --build --preset app-debug
cmake --build --preset app-test

Test:
ctest --list-presets
ctest --test-dir build/test -R Led_1

"C:/Program Files/SEGGER/JLink/JRun.exe" "--verbose" "--device" "RP2040_M0_0" "--rtt" "-if" "SWD" "--args" "Led_1" "C:/Users/Erich Styger.N0007139/Data/HSLU/Vorlesung/TSM_SoftwEng/git/projects/TSM_PicoW_Blinky/build/test/TSM_PicoW_Blinky.elf"

Worflow:
cmake --workflow --list-presets

## McuLib
The project uses the McuLib. The location of the library is specified with the variable 'MCULIB_DIR' in the top-level CMakeLists.txt. The McuLib can be shared with multiple projects.

## Environment
In order for this project to work, the Rasperry Pi Pico SDK needs to be installed and shall have set two environment variables as below (example below for Windows):
```
PICO_SDK_PATH=C:\Raspy\pico\pico-sdk
PICO_TOOLCHAIN_PATH=C:\Raspy\arm-none-eabi-gcc-13.2.1-1.1\bin
```
Additionally, the launch config uses a variable pointing to the SEGGER installation, example below for Windows:
```
SEGGER_PATH=C:/Program Files/SEGGER/JLink
```
The variables can be set on user level.

If using OpenOCD, have a variable pointing to OpenOCD executable too, for example
```
OPENOCD_PATH=C:/OpenOCD/xpack-openocd-0.12.0-1-win32-x64/xpack-openocd-0.12.0-1/bin
```

## Coverage with gcov
Install gcovr with
```
pip install gcovr
```
On Windows, it is possible that gets installed in a local environment, e.g.
C:\Users\<user name>\AppData\Local\Packages\PythonSoftwareFoundation.Python.3.12_qbz5n2kfra8p0\LocalCache\local-packages\Python312\Scripts
and gcovr.exe won't be found. Either use the path or copy gcovr.exe into a path which can be found.

For coverage, enable PL_CONFIG_USE_GCOV in platform.h.

To generate a text report:
```
gcovr .
```
To generate a HTML report (directory gcovr must exist):
```
gcovr --html-details -o ./gcovr/main.html
```
or use Terminal -> Run Task... -> gcovr

## Unit Tests
Enable 'PL_CONFIG_USE_UNIT_TESTS' in platform.h

Run JRun manually:
```
"c:\Program Files\SEGGER\JLink\JRun.exe" --device RP2040_M0_0 -if SWD build/debug-test/TSM_PicoW_Blinky.elf
"c:\Program Files\SEGGER\JLink\JRun.exe" --device RP2040_M0_0 -if SWD --jlinkscriptfile test.JLinkScript build/debug-test/TSM_PicoW_Sensor.elf
"c:\Program Files\SEGGER\JLink\JRun.exe" --device RP2040_M0_0 -if SWD --rtt --jlinkscriptfile src\tests\test_1.JLinkScript build/debug-test/TSM_PicoW_Blinky.elf
```
Manual test run:
```
ctest -v --test-dir build/debug-test --timeout 15 --output-on-failure
```
