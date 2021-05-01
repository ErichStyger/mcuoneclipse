Cheat sheet:

Create folder on disk.
File > Add Folder to Workspace


create folder: .vscode
add file:


mkdir build
cd build
cmake -DCMAKE_TOOLCHAIN_FILE="../arm-none-eabi-gcc.cmake" -DCMAKE_MAKE_PROGRAM=make.exe -G "Unix Makefiles" ..
make

