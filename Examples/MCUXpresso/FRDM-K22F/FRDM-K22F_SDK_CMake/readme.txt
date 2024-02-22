readme.txt
----------

Project to show how a MCUXpresso IDE/SDK project can be used with CMake and make (or ninja)

To create the build system
- Open a command prompt in the project directory
- run 'cmake init make.bat' for building using Make files
- run 'cmake init ninja.bat' for building using ninja (building around 10x faster than with make!)

'cd' into the build folder, then you can execute either
ninja
  or
make
on the console to build the project

All the build (make or ninja) related files are inside the 'build' subfolder. The 'clean.bat' is deleting that folder. After that you have to call one of the 'cmake init' batc files again.

Using the 'build' in Eclipse uses the Eclipse managed make build. The project has two bild targets (make and ninja) to build it from Eclipse.

## Build
To initialize the build files, use
```
cmake --preset debug
```
To build it:
```
cmake --build --preset debug
```