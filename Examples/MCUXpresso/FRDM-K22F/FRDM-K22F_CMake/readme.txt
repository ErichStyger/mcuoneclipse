CMake based project for the MCUXpresso and CMake.

You have to have Cmake installed for this.

Steps:
- use a command line/Console
- the following steps assume the name of the project directory as 'FRDM-K22F_CMake'
- cd FRDM-K22F_CMake
- mkdir build
- cd build
- cmake -G "Eclipse CDT4 - Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug -DCMAKE_ECLIPSE_GENERATE_SOURCE_PROJECT=TRUE -DCMAKE_ECLIPSE_MAKE_ARGUMENTS=-j8 ../FRDM-K22F_CMake
