
Toolchain file from:
https://github.com/jobroe/cmake-arm-embedded


create CMakeList.txt


mkdir build
cd build
cmake ..


cmake -DCMAKE_TOOLCHAIN_FILE=toolchain-arm-none-eabi-gcc.cmake -DCMAKE_MAKE_PROGRAM=make.exe -G "Unix Makefiles" .. --debug-output

