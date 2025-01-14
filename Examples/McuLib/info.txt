Repository and more details: https://github.com/ErichStyger/McuOnEclipseLibrary

For CMake based build systems, templates are provided:
- ESP32:  ESP32_CMakeLists.txt
- Raspberry Pi Pico (RP2040): RP2040_CMakeLists.txt

This folder contains all the library sources:
- config: application specific configuration files
- src: source files

Middleware and dedicated driver folders:
- FatFS: port of the ElmChan FatFS system
- fonts: graphical LCD fonts, used by McuFontDisplay
- FreeRTOS: FreeRTOS realtime operating system, optimized and tuned for Segger SystemView and Percepio Trace
- HDD44780: Driver for HD44780 LCDs with up to 4 lines (https://mcuoneclipse.com/2012/12/22/hd44780-2x16-character-display-for-kinetis-and-freedom-board/)
- rdimon: Semihosting retargeting with file I/O support
- SEGGER_RTT: Segger Realtime Terminal Library (https://www.segger.com/products/debug-probes/j-link/technology/real-time-transfer/about-real-time-transfer/)
- SEGGER_SysView: Segger Systemview Library for tracing FreeRTOS (https://www.segger.com/products/development-tools/systemview/)
- TraceRecorder: Percipio Tracealyzer library for FreeRTOS (https://percepio.com/tz/)
- LittlevGL: GUI library (https://littlevgl.com/)
- littleFS: littleFS transactional and high-integrity file system (https://github.com/littlefs-project/littlefs)
- minIni: a minimal INI file parser: https://www.compuphase.com/minini.htm
- Modbus: Modbus implementation, Heidelberg Energy Control EV charger

Components of the McuOnEclipse (in alphabetical order) inside the 'src' Folder:
- C11, C21: subdrivers of McuQuadCounter
- Clock1: subdriver of McuGenericSWSPI
- DbgRd1: subdriver of McuOneWire
- DQ1: subdriver of McuOneWire
- Input1: subdriver of McuGenericSWSPI
- InputRB1: subdriver of McuOneWire
- McuArmTools: various ARM Cortex utilities
- McuButton: Push button driver
- McuCRC_*: CRC generation and calculation
- McuCriticalSection: critical section handling
- McuDebounce: Debouncing for McuButton
- McuDS18B20: Driver for the DS18B20 One-Wire temperature sensor library
- McuEE24: Driver for EEproms of type 24AA and 24LC. Supports 24AA08, 24LC08, 24AA16, 24LC16, 24AA32, 24LC32, 24AA256, 24LC256, 24FC256, 24AA512, 24LC512, 24FC256, 24AA1025, 24LC1025, 24FC1025
- McuESP32: Interfacing with ESP32 from a MCU, including USB-CDC, monitor and bootloader interface
- McuEvents: event handling using a bit array
- McuExtRTC: driver for external I2C realtime clock (RTC). Supports DS1307, DS3231, DS3232 and DS1342
- McuFontDisplay: Font rendering for graphical displays
- McuFXOS8700: Driver for the NXP FXOS8700 accelerometer/magnetometer
- McuGDisplay: Driver for graphical displays
- McuGenericI2C: Generic I2C driver using hardware I2C or software I2C
- McuGenericSWI2C: Software (bit banging) I2C driver
- McuGenericSWSPI: Software (bit banging) SPI driver
- McuGFont: Graphical font library driver. Several fonts are available in the 'fonts' subfolder
- McuGPIO: Generic GPIO pin driver
- McuHardfault: ARM Cortex-M hardfault handler
- McuI2cLib: Generic and portable I2C library using hardware I2C
- McuI2CSpy: I2C sniffing utility
- McuINA260: Driver for the Texas Instruments INA260 I2C power/voltage/current sensor
- McuIO: Generic buffered input/output driver
- McuLC709203F: Driver for the LC709203F battery/charing monitor device
- McuLED: generic LED driver for multiple LEDs
- McuLib: Configuration of the McuOnEclipse Library
- McuLog: Message and logging driver over UART, USB and RTT
- McuOneWire: 1-Wire communication driver
- McuPercepio: Configuration and interface to the Percepio Trace library
- McuPidFloat: Generic PID control loop using floating point values
- McuPidInt: Generic PID control loop using integer values
- McuQuadCounter: Quadrature Counter library
- McuRingBuffer: Generic Ring Buffer implementation
- McuRTOS: wrapper for FreeRTOS
- McuRTT: wrapper for Segger RTT
- McuSemihost: Low level semihosting for multiple debug probes, including file I/O
- McuSharpMemoryDisplay: Driver for the Sharp Memory displays
- McuShell: Driver for a command line shell
- McuShellCdcDevice: USB CDC driver for McuShell
- McuShellUart: UART driver for the McuShell
- McuSHT31: Driver for the Sensirion SHT31 temperature/humidity sensor
- McuSHT40: Driver for the Sensirion SHT40 temperature/humidity sensor
- McuSSD1306: display driver for SSD1306 and SH1106
- McuST7735: display driver for ST7735 based displays
- McuSTM32HALI2C: low level I2C driver using STM32 CubeMX HAL
- McuSPI: Hardware SPI abstraction and interface to the SPI bus
- McuSWO: SWO (ARM Single Wire Output) library and command line support
- McuTimeDate: Realtime clock implementation for software, hardware and external I2C RTC
- McuTimeout: generic driver for timeout handling
- McuTrigger: generic interrupt callback handling
- McuULN2003: stepper motor driver using the ULN2003
- McuUtility: various safe string manipulation and other utility functions
- McuWait: Realtime synchronization waiting routines
- McuWatchdog: COP/Watchdog timer module
- McuW28Q128: driver for the Winbond W28Q128 serial flash (https://mcuoneclipse.com/2019/01/06/driver-and-shell-for-winbond-w25q128-16mbyte-serial-flash-device/)
- McuX12_017: stepper motor driver for the X12.017 device
- McuXFormat: tiny formatting and printing, similar to sprintf
- Output1: subdriver of McuGenericSWSPI
- SCL1, SDA1: subdrivers for McuGenericSWI2C
- WPpin1: Write Protect pin for McuEE24

