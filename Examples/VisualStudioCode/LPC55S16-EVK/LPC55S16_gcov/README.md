# LPC55S16-EVK Blinky

Project for the LPC55S16-EVK, using VS Code with CMake and Ninja, blinking the blue onboard LED. This project demonstrates the usage of GNU coverage (gcov).
See https://mcuoneclipse.com/2023/11/21/gnu-coverage-gcov-for-an-embedded-target-with-vs-code/

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

## LinkServer
To use the NXP LinkServer as debug probe (e.g. NXP MCU-Link or MCU-Link Pro), launch it first in a terminal/console as gdbserver:
```
c:\nxp\LinkServer_1.3.15\LinkServer.exe gdbserver --keep-alive LPC55S16:LPCXpresso55S16
```


## GNU Coverage
add gcov subdirectory
```
add to main CMakeLists.txt:
add_subdirectory(./gcov                 gcov)
```
Add rdiomon library to main CMakeLists.txt:
```
add_subdirectory(${MCULIB_DIR}/rdimon   rdimon)
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

```
gcov_write_files();
```

gcovr tool:
https://gcovr.com
pip install gcovr

Make sure gcov of toolchain is in path! Rename binary from arm-none-eabi-gcov.exe to gcov.exe

Run gcovr in root of project:
gcovr .   => text report
create folder for output (gcovv_report)
gcovr --html-details -o ./gcovr_report/main.html

\\ GCOVR_EXCL_LINE
\\ GCOVR_EXCL_START
\\ GCOVR_EXCL_STOP