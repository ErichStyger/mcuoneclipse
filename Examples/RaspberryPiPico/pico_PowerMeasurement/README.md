# Power Measurement with RP2040 Pico Board
This project uses CMake with Ninja and the RP2040 SDK to blink the on-board LED.

To project features different power measurement modules:
- INA260: https://www.adafruit.com/product/4226, Adafruit INA260 High or Low Side Voltage, Current, Power Sensor
- ADS1115: https://www.adafruit.com/product/1085, ADS1115 16-Bit ADC - 4 Channel with Programmable Gain Amplifier - STEMMA QT / Qwiic

## Build
Project has `Debug`, `Release` and `Test` targets, using CMake Presets. 

Configure:
```
cmake --list-presets
cmake --preset Debug
cmake --preset Release
cmake --preset Test
```

Build:
```
cmake --build --list-presets
cmake --build --preset app-debug
cmake --build --preset app-release
cmake --build --preset app-test
```

Test:
```
ctest --list-presets
ctest --test-dir build/Test -R Led_1
```

Worflow:
```
cmake --workflow --list-presets
```
