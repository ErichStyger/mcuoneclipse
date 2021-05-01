Cheat sheet:

Create folder on disk.
File > Add Folder to Workspace


create folder: .vscode
add file: tasks.json


mkdir build
cd build
cmake -DCMAKE_TOOLCHAIN_FILE="../arm-none-eabi-gcc.cmake" -DCMAKE_MAKE_PROGRAM=make.exe -G "Unix Makefiles" ..
make

* Debug *
Menu Run > Start Debugging
select GDB (creates launch.json)

Cortex debug: set path to GDB:
    "cortex-debug.JLinkGDBServerPath": "C:\\Program Files (x86)\\SEGGER\\JLink"