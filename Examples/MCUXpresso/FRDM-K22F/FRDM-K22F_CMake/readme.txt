CMake based project for the MCUXpresso and CMake.

You have to have Cmake installed for this.

- Create a new folder for the project.
- copy the following files and directories:
  - CMSIS/                    # CMSIS library files
  - device/                   # device specific files and startup code
  - src/                      # source folder with main()
  - CMakeLists.txt            # CMake main file
  - arm-none-eabi-gcc.cmake   # compiler/toolchain kit definition
  - CreateEclipseProject.bat  # batch file to create the Eclipse project
  - .gitignore                # ignore file for Eclipse. Only the necessary files for the template

Steps:
- use a command line/Console
- the following steps assume the name of the project directory as 'FRDM-K22F_CMake'
- cd FRDM-K22F_CMake
- mkdir build
- cd build
- cmake -G "Eclipse CDT4 - Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug -DCMAKE_ECLIPSE_GENERATE_SOURCE_PROJECT=TRUE -DCMAKE_ECLIPSE_MAKE_ARGUMENTS=-j8 ../FRDM-K22F_CMake
