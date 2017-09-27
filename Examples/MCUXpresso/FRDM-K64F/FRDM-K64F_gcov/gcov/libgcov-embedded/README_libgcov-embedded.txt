NOTE: Taken from https://github.com/reeteshranjan/libgcov-embedded


# libgcov-embedded
Working port of `gcov_exit` to use in embedded systems for capturing code coverage.
## Compatibility
- [gnu arm toolchain v5-2016-q3-update](https://launchpad.net/gcc-arm-embedded/5.0/5-2016-q3-update) - **NOTE**: things should work in all versions where the gcov data structures are compatible with those in this version. This means both older and newer versions.

## How to Generate .gcda Files
### Working Sample Project
It's very easy to get started if you follow [this sample](https://github.com/reeteshranjan/libgcov-embedded-example).

It is a Blinky project for stm32f4-discovery board made using [gnu arm eclipse](http://gnuarmeclipse.github.io/) with [eclipse cdt neon.1](http://www.eclipse.org/downloads/packages/eclipse-ide-cc-developers/neon1a). **NOTE**: if you don't have an stm32f4-discovery board, you can use QEMU emulator for this board with gnu arm eclipse.

Also, this repository includes sample coverage HTML reports generated using the `.gcda` files generated while running the sample project.
### From Scratch
#### Include this software
- Copy the `port` directory or all its subdirectories to your project
- Ensure that these paths are included for finding headers - `port/gcc`, `port/libgcc`, `port/src`
- Ensure that all .c files in `port/gcc`, `port/libgcc` and `port/src` are included in your build

#### Get the compilation working
- Add this preprocessor directive to your makefiles - `ENABLE_LIBGCOV_PORT=1`
- Add `--coverage` compiler option to your c and/or c++ compiler flags
- Add `--coverage` to your linker flags
- Build with your gnu arm gcc compiler and linker and verify that `.gcno` files are created for each source file in your project. **NOTE**: it would be much smoother if you create a separate directory to store your object and coverage files like done by Eclipse projects.

#### Hook it in
In your main.c or main.cpp add the following.
```
#ifdef ENABLE_LIBGCOV_PORT
#include "libgcov-embedded.h"
#endif
```
In the `main` function, make this as the beginning:
```
#ifdef ENABLE_LIBGCOV_PORT
  static_init();
#endif
```

If you have your own version of `_exit`, comment it out.

#### Manual .gcda files creation
- Set up a breakpoint at `gcov-io.c:250`. The line has this content `free(gcov_var.gcda_buf);`
- Set a watch expression for this variable `__gcov_var__ported`
- Start your debugging session and do the following each time the above breakpoint hits. It would hit once per source file in your project:
 - `__gcov_var__ported.filename` contains the full path of the `.gcda` file to create
 - `__gcov_var__ported.gcda_buf` contains the start address of coverage information for corresponding source file
 - `__gcov_var__ported.gcda_buf_pos` contains the end address of coverage information for corresponding source file
 - On gdb prompt, run `dump binary memory <value of __gcov_var__ported.filename> <hex value of __gcov_var__ported.gcda_buf> <hex value of __gcov_var__ported.gcda_buf_pos>` e.g. `dump binary memory my-proj/Debug/src/main.gcda 0x20006450 0x20006880`. This would create the `.gcda` file.

## Generate HTML visualization
### For Mac/Linux
- On Mac, install `lcov` using mac ports. On Linux, it should be there or find your Linux flavor specific package.
- Go to your build directory where your object files, `.gcno` files and `.gcda` files are there.
- Run `lcov --capture --output-file main.info --directory . --gcov-tool /usr/local/gcc-arm-none-eabi-5_4-2016q3/bin/arm-none-eabi-gcov`. **NOTE**: replace the gcov path with your actual system path in case it is installed in a different location.
- Run `genhtml -o html main.info`. It creates HTML visualization inside `html` directory.

The `index.html` file can be opened in a browser to see graphical visualization per source file.
## Limitations & Caveats
- If the in-memory coverage information is greater than 8K, it would not be generated. **Fix**: Increase the value of the macro `GCOV_GCDA_BUF_SZ` in `port/gcc/gcov-io.c` to suit your application's needs. For the testing so far, this limit has been more than sufficient.
- The port does not support merging of existing `.gcda` data with a new run's collected coverage information. This is difficult for obvious reason that an existing `.gcda` file on the host system cannot be read by the embedded system. **Fix**: None. So only if your application can benefit with a single run's coverage information, this tool is useful.

## Why this repository?
### Tutorials don't work
Getting code coverage done for stm32f4-discovery using gnu arm toolchain version 5-2016-q3-update (used during October/November 2016) and existing guides like [this](https://mcuoneclipse.com/2014/12/26/code-coverage-for-embedded-target-with-eclipse-gcc-and-gcov/) do not work.
### What's the issue?
When one calls `__gcov_flush` to run the coverage info generation process, it just hangs forever and we can't get to generating `.gcda` files.
### How is the issue taken care of?
This port was created and used in a sample project to see what caused the above hang. It was traced to an undocumented bug (causing 3 such points where code would hang indefinitely) in gcc's gcov portions. The only way to get past this issue was to have our own complete source of `__gcov_flush` (or `gcov_exit`, which I went with) with these bugs fixed, which is what exists in this repository.
