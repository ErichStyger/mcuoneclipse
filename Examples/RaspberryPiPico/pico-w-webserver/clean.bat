del *.elf *.bin *.dis *.hex *.uf2 *.map
del CMakeCache.txt Makefile
rmdir /S /Q build pioasm generated elf2uf2 pico-sdk CMakeFiles cmake_install.cmake

del src\*.a 
del src\Makefile src\cmake_install.cmake
rmdir /S /Q src\CMakeFiles

del McuLib\*.a
del McuLib\Makefile McuLib\cmake_install.cmake
rmdir /S /Q McuLib\CMakeFiles

