readme.txt
----------
This folder contains all the library sources:
- config: application specific configuration files
- src: source files

Middleware:
- FreeRTOS: FreeRTOS realtime operating system, optimized and tuned for Segger SystemView and Percepio Trace
- TraceRecorder: Percipio Tracealyzer library for FreeRTOS (https://percepio.com/tz/)
- SEGGER_RTT: Segger Realtime Terminal Library (https://www.segger.com/products/debug-probes/j-link/technology/real-time-transfer/about-real-time-transfer/)
- SEGGER_SysView: Segger Systemview Library for tracing FreeRTOS (https://www.segger.com/products/development-tools/systemview/)

Components of the McuOnEclipse (in alphabetical order):
- McuArmTools: various ARM Cortex utilities
- McuCriticalSection: critical section handling
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
- McuLED: generic LED driver
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
- McuSystemView: Wrapper for the Segger SystemViewer
- McuTimeDate: Realtime clock implementation for software, hardware and external I2C RTC
- McuTimeout: generic driver for timeout handling
- McuTrigger: generic interrupt callback handling
- McuUSB: interface and wrapper to the FSL USB Stack 4.1.1
- McuUtility: various safe string manipulation and other utility functions
- McuWait: Realtime synchronization waiting routines
- McuXFormat: tiny formatting and printing, similar to sprintf

