REM del *.elf *.bin *.dis *.hex *.uf2 *.map
del CMakeCache.txt Makefile cmake_install.cmake
rmdir /S /Q build pioasm generated elf2uf2 pico-sdk CMakeFiles

del src\*.a 
del src\Makefile src\cmake_install.cmake
rmdir /S /Q src\CMakeFiles
