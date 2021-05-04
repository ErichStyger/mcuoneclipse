
Toolchain file from:
https://github.com/jobroe/cmake-arm-embedded


create CMakeList.txt


mkdir debug
cd debug
# makes VS build files!
# cmake ..
#

cmake -DCMAKE_TOOLCHAIN_FILE="../toolchain-arm-none-eabi-gcc.cmake" -DCMAKE_MAKE_PROGRAM=make.exe -G "Unix Makefiles" .. --debug-output

cmake --build . -- -j 4

https://dev.to/younup/cmake-on-stm32-the-beginning-3766

Kits:
https://vector-of-bool.github.io/docs/vscode-cmake-tools/kits.html#kits


cmake -DCMAKE_TOOLCHAIN_FILE="arm-none-eabi-gcc.cmake" .. 
