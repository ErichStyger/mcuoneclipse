# CMake with NXP MCUXpresso SDK
Project to show how a MCUXpresso IDE/SDK project can be used with CMake (command line) or with MCUXpresso IDE (managed make).
The project is using CMake presets.

## Environment
There is a 'setenv.bat' which sets the environment with a variable pointing to the ARM tool chain. Set that variable first.

## How to build with CMake
To create the build build files (once, or after a clean):
- Open a command prompt in the project directory
```
cmake --preset debug
```
To build it:
```
cmake --build --preset debug
```

All the CMake build related files are inside the 'build' subfolder. The 'clean.bat' is deleting that folder. After that you have to call one of the 'cmake init' batc files again.

Using the 'build' in Eclipse uses the Eclipse managed make, and stores it files into the 'Debug' folder.

## Links
- https://mcuoneclipse.com/tag/cmake-presets/
- https://mcuoneclipse.com/2023/12/18/modern-on-target-embedded-system-testing-with-cmake-and-ctest/
- https://mcuoneclipse.com/2023/04/19/building-a-triumvirate-from-eclipse-cdt-to-cmake-cmd-and-visual-studio-code/
- https://mcuoneclipse.com/2022/09/04/tutorial-creating-bare-bare-embedded-projects-with-cmake-with-eclipse-included/
