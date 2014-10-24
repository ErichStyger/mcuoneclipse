mcuoneclipse
============

Please see the readme files inside the folders. Don't forget to read the Wiki pages.
To follow on this project (and beyond): follow my blog on http://mcuoneclipse.com

Erich

NOTES:
- The content of the 'EclipsePlugins' folder has been move to SourceForge:
https://sourceforge.net/projects/mcuoneclipse/files/Eclipse%20Plugins
- The releases of the Processor Expert components can be found on SourceForge_
https://sourceforge.net/projects/mcuoneclipse/files/PEx%20Components/


List of Components:
===================

Component 			Description
------------------------------------------------------------------
24AA_EEPROM 			Microchip 24AA EEPROM driver.
74HC164				Driver for the 74HC164.
74HC595				Driver for 74HC595.
App_SMAC_Hell			Demo application component for the SMAC stack.
AT25HP512			Driver for the AT25HP512 EEPROM.
BitIO_to_PCA9554		Driver to map bit I/O to the PC9554 I2C Exander.
Bluetooth_EGBT			HC05/06 Bluetooth module driver.
BootLoaderDisk 			File System for Bootloader.
BootLoaderUSB 			Bootloader over USB.
ChLCD				Driver for Kent bistable display.
CTouchScanner			Capacitive touch scanner.
CTouchSensor			Sensor implementation for capacitive touch sensor.
DCF77				DCF-77 Radio signal receiver.
FAT_FileSystem 			FAT FatFS File System.
FatFsMem_USB_MSD		Memory Implementation for FatFS using USB MSD.
FatFsMemSDHC 			Memory Manager for FatFS using SDHC_LDD.
FontDisplay 			Draw text on a graphical display.
FreeRTOS 			FreeRTOS Operating System.
FreeRTOSTrace 			Trace hook implementation for FreeRTOS.
FSShell 			File System Shell and generic shell.
FSL_USB_CDC_Device		USB CDC Device for FSL USB Stack.
FSL_USB_HID_Keyboard_Device	USB HID Keyboard device for FSL USB Stack.
FSL_USB_HID_Mouse_Device	USB HID Mouse device for FSL USB Stack.
FSL_USB_MSD_Host		USB MSD Host for FSL USB Stack.
FSL_USB_Stack 			Wrapper for Freescale USB Stack.
FSShell				File System Shell (depreciated), use new Shell component instead.
GDisplay 			Graphical Display drawing routines.
GenericBitIO 			Generic Bit I/O.
GenericI2C 			Generic Software I2C driver, on top of a low level one (e.g. HW I2C or GenericSWI2C).
GenericKBI			Generic KBI interface for S08.
GenericSPI			Generic SPI implementation.
GenericSWI2C 			Generic Software I2C with 'bit banging'.
GenericSWSPI 			Generic Software SPI with 'bit banging'.
GenericTimeDate 		Generic Date/Time handling.
GFont 				Graphical Fonts.
HardFault 			Hard Fault handler for Kinetis to simplify debugging of HardFault exceptions.
I2CSpy 				Utility to inspect I2C devices.
KentChLCD			Display driver Kent bistable displays.
Key				Push button driver with debouncing.
LCDHTA 				HD44780 2x16 Character Display Driver.
LED 				Universal LED driver.
LEDbit				Same as LED, but using different name to avoid name conflict.
LEDByte				Array of LED driver.
LEDMatrix			Driver for LED matrix (rows and columns).
LEDReverseBias			LED driver to use LED as ambient light sensor.
LEDSensor			LED sensor for LED ambient light sensor.
LightComm			Communication software using normal LEDs.
LM61B				Driver for LM61B temperature sensor.
LowPower			Simple low power driver (S08).
MAG3110				Freescale MAG3110 magnetometer driver.
MaxonF2140 			DC Motor driver (PWM for speed, BitIO for direction).
MC13192 			Wireless Transceiver Driver for MC1321x and MC13192/MC1320x.
MC34673				Freescale MC34673 Li-Ion Battery Power Management IC.
MMA7260Q			Freescale MMA7260Q accelerometer.
MMA7455L			Freescale MMA7455L accelerometer.
MMA8451Q			Freescale MMA8451Q accelerometer.
MPR08x				Freescale MPR08x touch sensor IC.
MPVZ5004			Freescale MPVZ5004 pressure sensor.
nRF24L01			Nordic Semiconductor nRF24L01+ 2.4GHz transceiver.
OLED				OLED display driver.
PCA9554 			NXP PCA9554(A) I2C I/O Expander.
PCA9554BitIO 			BitIO interface to PCA9554.
PDC8544 			Display Driver for black/white Philips display found in Nokia phones.
PercepioTrace 			Percepio FreeRTOS+Trace.
PID_Float			PID implementation for floating point values.
PID_Int 			PID Control Loop with Integer values.
PtConv				PT100/PT1000 temperature conversion.
PWMServo16bit			Servo driver for 16bit PWM on ColdFire V2.
QuadCounter 			Quadratur Decoder with sampling or Input Capture.
RingBuffer			Ring Buffer for 8, 16 and 32bit entries.
RingBufferUInt8 		Ring Buffer for unsigned 8bit values.
RTC_Maxim 			Maxim I2C RTC device driver for DS3232 and DS1307.
S19 				S19 File Parser.
S65Sharp			Display driver for the Sharp S65 displays.
SD_Card 			Low Level SD-Card driver for FatFS.
Servo				PWM Servo driver.
Shell				Command line shell implementation.
SimpleEvents 			Simple Event Flags.
SMAC 				SMAC 2.4 GHz stack for MC13213 and MC13201.
SSEC 				Security driver for SPHY.
SPHY 				PHY driver for SMAC.
SPIHCS08			SPI wrapper for SPI perhiperhal on S08.
SSD1289 			Solomon Systech SSD1289 LCD.
SSEC				Encryption for SMAC.
Tacho 				Tachometer.
Timeout 			Timeout handler.
TouchScreen			Touchscreen driver for the TWR-LCD.
TouchScreenSensor		Touchscreen sensor for TWR-LCD.
Trigger 			Trigger module implementing mini-threads.
uCOS_II				uCOS-II RTOS wrapper.
Utility 			Utility functions.
UI				Graphical User Interface.
UIButton			Button widget for UI.
UICalendar			Calendar widget for UI.
UICheckBox			Checkbox widget for UI.
UIDialogWindow			DialogWindow widget for UI.
uIGraph				Linegraph widget for UI.
UIHeader			Window header widget for UI.
UIIcon				Icon widget for UI.
UIScreen			Screen widget for UI.
UIScrollmenu			Screllmenu widget for UI.
UISlider			Slider widget for UI.
UISpace				Virtual widget for UI.
UIText				Text widget for UI.
USB_CMX				CMX USB stack wrapper (ColdFire V2).
USB_HID_CMX			USB (HID) device with CMX stack (ColdFire V2).
USB_Host_CMX			USB (HID) host with CMS Stack (ColdFire V2).
UserInterface			Collection of GUI widgets for small LCDs (depreciated by UI component).
UTI				Driver for Smartec UTI Universal Transducer IC.
Wait 				Busy Waiting Routines.
