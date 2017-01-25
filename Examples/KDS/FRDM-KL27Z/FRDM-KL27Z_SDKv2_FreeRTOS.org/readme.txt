readme.txt
----------

This is a 'plain vanilla' Kinetis SKD v2.0 project with Kinetis Design Studio V3.2.0 using the 'stock' Eclipse 9.0.0 from FreeRTOS.org.

Basic steps:
- create SDK project with the wizard, with all drivers and no RTOS
- download FreeRTOS zip file https://sourceforge.net/projects/freertos/files/FreeRTOS/
- Place FreeRTOS inside the FreeRTOS project folder
- remove all the not needed ports and demos
- use a suitable FreeRTOSConfig.h from one of the Demos. Update the configuration as needed.
- only compile the heap managers (disable/remove the others)
- update the compiler include paths for the FreeRTOS header files

See my blog http://www.mcuoneclipse.com for other tutorials and projects

Enjoy :-)
