For the Raspberry Pi Pico SDK 2.0.0, a Picotool is required.
The SDK CMake and scripts try to build it if the Picotool is not present or found.
However, on Windows building the picotool might fail. For example with the following message during the build:
[build] WARNING: Disassembly is not correct
That's why a binary is provided here.

Instructions:
- Download the zip file and extract it, into 
  C:\Raspy
- Create an environment variable PICO_TOOL_PATH pointing to where you have installed it, e.g.
  PICO_TOOL_PATH=C:\Raspy\picotool\2.0.0\picotool
- In your top-level project CMakeLists.txt, add the line(right after cmake_minimum_required). 
  This ensures that the build is using our picotool binary directly and does not try to build it:
  set(picotool_DIR $ENV{PICO_TOOL_PATH})
