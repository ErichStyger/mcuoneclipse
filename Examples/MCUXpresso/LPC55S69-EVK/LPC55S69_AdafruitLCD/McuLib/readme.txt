readme.txt
----------

Repository and more details: https://github.com/ErichStyger/McuOnEclipseLibrary

This folder contains all the library sources:
- config: application specific configuration files
- src: source files

Middleware and dedicated driver folders:
- FatFS (experimental): port of the ElmChan FatFS system
- fonts: graphical LCD fonts, used by McuFontDisplay
- FreeRTOS: FreeRTOS realtime operating system, optimized and tuned for Segger SystemView and Percepio Trace
- HDD44780: Driver for HD44780 LCDs with up to 4 lines (https://mcuoneclipse.com/2012/12/22/hd44780-2x16-character-display-for-kinetis-and-freedom-board/)
- SEGGER_RTT: Segger Realtime Terminal Library (https://www.segger.com/products/debug-probes/j-link/technology/real-time-transfer/about-real-time-transfer/)
- SEGGER_SysView: Segger Systemview Library for tracing FreeRTOS (https://www.segger.com/products/development-tools/systemview/)
- TraceRecorder: Percipio Tracealyzer library for FreeRTOS (https://percepio.com/tz/)
- LittlevGL: GUI library (https://littlevgl.com/)
- minIni: a minimal INI file parser: https://www.compuphase.com/minini.htm

Components of the McuOnEclipse (in alphabetical order) inside the 'src' Folder:
- C11, C21: subdrivers of McuQuadCounter
- Clock1: subdriver of McuGenericSWSPI
- DbgRd1: subdriver of McuOneWire
- DQ1: subdriver of McuOneWire
- Input1: subdriver of McuGenericSWSPI
- InputRB1: subdriver of McuOneWire
- LEDpin1, LEDpin2, LEDpin3, LEDpin4: subdrivers for McuLED1, McuLED2, McuLED3 and McuLED4
- McuArmTools: various ARM Cortex utilities
- McuButton: Push button driver
- McuCriticalSection: critical section handling
- McuDebounce: Debouncing for McuButton
- McuDS18B20: Driver for the DS18B20 One-Wire temperature sensor library
- McuEvents: event handling using a bit array
- McuFontDisplay: Font rendering for graphical displays
- McuFXOS8700: Driver for the NXP FXOS8700 accelerometer/magnetometer
- McuGDisplay: Driver for graphical displays
- McuGenericI2C: Generic I2C driver using hardware I2C or software I2C
- McuGenericSWI2C: Software (bit banging) I2C driver
- McuGenericSWSPI: Software (bit banging) SPI driver
- McuGFont: Graphical font library driver. Several fonts are available in the 'fonts' subfolder
- McuHardfault: ARM Cortex-M hardfault handler
- McuI2CSpy: I2C sniffing utility
- McuLED: generic LED driver for multiple LEDs
- McuLED1, McuLED2, McuLED3, McuLED4: single LED driver
- McuLib: Configuration of the McuOnEclipse Library
- McuOneWire: 1-Wire communication driver
- McuPercepio: Configuration and interface to the Percepio Trace library
- McuPidFloat: Generic PID control loop using floating point values
- McuPidInt: Generic PID control loop using integer values
- McuQuadCounter: Quadrature Counter library
- McuRingBuffer: Generic Ring Buffer implementation
- McuRTOS: wrapper for FreeRTOS
- McuRTT: wrapper for Segger RTT
- McuSharpMemoryDisplay: Driver for the Sharp Memory displays
- McuShell: Driver for a command line shell
- McuSHT31: Driver for the Sensirion SHT31 temperature/humidity sensor
- McuSSD1306: display driver for SSD1306 and SH1106
- McuSTM32HALI2C: low level I2C driver using STM32 CubeMX HAL
- McuSystemView: Wrapper for the Segger SystemViewer
- McuTimeDate: Realtime clock implementation for software, hardware and external I2C RTC
- McuTimeout: generic driver for timeout handling
- McuTrigger: generic interrupt callback handling
- McuUtility: various safe string manipulation and other utility functions
- McuWait: Realtime synchronization waiting routines
- McuXFormat: tiny formatting and printing, similar to sprintf
- Output1: subdriver of McuGenericSWSPI
- SCL1, SDA1: subdrivers for McuGenericSWI2C

