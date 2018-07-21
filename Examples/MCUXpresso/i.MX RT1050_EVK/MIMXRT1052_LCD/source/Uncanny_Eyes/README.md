# Uncanny_Eyes

'Uncanny eyes' for Adafruit 1.5" OLED (product #1431) or 1.44" TFT LCD (#2088).  Works on PJRC Teensy 3.x and on Adafruit M0 and M4 boards (Feather, Metro, etc.).  This code uses features specific to these boards and WILL NOT work on normal Arduino or other boards!

How-to guide with parts list and 3D models is here:
https://learn.adafruit.com/animated-electronic-eyes-using-teensy-3-1/overview

Teensy 3.x w/OLED screens: use 72 MHz board speed -- 96 MHz requires throttling back SPI bitrate and actually runs slower!

Directory 'uncannyEyes' contains Arduino sketch for PJRC Teensy 3.1 & Adafruit M0 & M4. 'graphics' subfolder has various eye designs, as #include-able header files.

Folder 'convert' contains Python sketch for generating graphics header files. Requires Python Imaging Library. Example images are also in this directory.
