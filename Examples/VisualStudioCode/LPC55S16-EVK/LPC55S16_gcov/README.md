# LPC55S16-EVK Blinky

Project for the LPC55S16-EVK, using VS Code with CMake and Ninja, blinking the blue onboard LED. This project demonstrates the usage of GNU coverage (gcov).

## Environment
The root folder contains several batch files as helper.
In order to have compiler and J-Link not hardcoded in the project itself, rund the setenv script file.

setenv:
```
set TOOLCHAIN_PREFIX=C:/Raspy/arm-none-eabi-gcc-12.2.1-1.2
set SEGGER_PATH=C:/Program Files/SEGGER/JLink
```
Note that the commands have to be set up *before* starting VS Code, to have the environment set.
Alternatively, these variables can be set on user level.

## CMake commands
There are a set of CMake and build related commands you can use:

init:
```
cmake -G"Ninja" . -B build
```

build:
```
cmake --build build
```

clean:
```
cmake --build build --target clean
```

CleanClean:
```
rmdir /S /Q build 2>nul
```
## GNU Coverage
add gcov subdirectory
```
add to main CMakeLists.txt:
add_subdirectory(./gcov                 build/gcov)
```
Add rdiomon library to main CMakeLists.txt:
```
add_subdirectory(${MCULIB_DIR}/rdimon   build/rdimon)
```
add to target_link_libraries:
```
rdimonLib # file I/O with semihosting
```

add to McuLibConfig.h:
```
/* ---------------------------------------------------------------------------------------*/
/* McuSemihost */
#define McuSemihost_CONFIG_DEBUG_CONNECTION         McuSemihost_DEBUG_CONNECTION_SEGGER
/* ---------------------------------------------------------------------------------------*/
/* McuRdimon */
#define McuRdimon_CONFIG_IS_ENABLED       (1)       /* 1: RdiMon is enabled; 0: RdiMon is disabled*/
/* ---------------------------------------------------------------------------------------*/
```

Add to platform.h:
#define PL_CONFIG_USE_GCOV              (1 && McuRdimon_CONFIG_IS_ENABLED) /* if using gcov */

src CMakeLists.txt
```
  rdimonLib # semihosting with file I/O
  gcovLib # own gcov wrapper library
  gcov    # GNU gcov library
```

platform.c:
```
#if McuRdimon_CONFIG_IS_ENABLED
  #include "rdimon/McuRdimon.h"
#endif
#if PL_CONFIG_USE_GCOV
  #include "gcov_support.h"
  #include "gcov_test.h"
#endif
```
```
#if McuRdimon_CONFIG_IS_ENABLED
  McuRdimon_Init();
#endif
#if PL_CONFIG_USE_GCOV
  gcov_init();  /* initialize library */
  //gcov_check();
  //gcov_test(3);
#endif
```
Use newlib
if _sbrk: implementation in gcov_support.c

```
add_compile_options(--coverage)
```