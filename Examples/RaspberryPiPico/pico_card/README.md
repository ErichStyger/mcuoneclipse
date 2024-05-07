# AEMBS Game
Project for the Raspberry Pi Pico for AEMBS, implementing different games.
## McuLib
The project uses the McuLib. The location of the library is specified with the variable 'MCULIB_DIR' in the top-level CMakeLists.txt. The McuLib can be shared with multiple projects.

# Newlib/Newlib-nano
Can also switch to newlib-nano by putting "target_link_options(pico_runtime INTERFACE "--specs=nosys.specs" "--specs=nano.specs")" in pico-sdk/src/rp2_common/pico_runtime/CMakeLists.txt

## Environment
In order for this project to work, the Rasperry Pi Pico SDK needs to be installed and shall have set two environment variables as below (example below for Windows):
```
PICO_SDK_PATH=C:\Raspy\pico\pico-sdk
PICO_TOOLCHAIN_PATH=C:\Raspy\arm-none-eabi-gcc-12.2.1-1.2\bin
```
Additionally, the launch config uses a variable pointing to the SEGGER installation, example below for windows:
```
SEGGER_PATH=C:/Program Files/SEGGER/JLink
```
The variables can be set on user level.

# Links
Making links to folders:

mklink /D GameCommon ..\GameCommon
mklink /D McuLib ..\..\McuLib

## CMake commands
There are a set of CMake and build related commands you can use, which are availble in .vscode/tasks.json:
- init
    ```
    cmake -G"Ninja" . -B build
    ```

- build:
    ```
    cmake --build build
    ```
- clean:
    ```
    cmake --build build --target clean
    ```

- CleanClean (on Windows, or simply delete the 'build' folder):
    ```
    rmdir /S /Q build 2>nul
    ```

## SMP Multicore
Two spinlocks used by RTOS:
```
#ifndef configSMP_SPINLOCK_0
    #define configSMP_SPINLOCK_0    PICO_SPINLOCK_ID_OS1
#endif
```
```
#ifndef configSMP_SPINLOCK_1
    #define configSMP_SPINLOCK_1    PICO_SPINLOCK_ID_OS2
#endif
```
#define configNUMBER_OF_CORES                   (1) /* number of cores for the kernel */

#define portRUNNING_ON_BOTH_CORES             ( configNUMBER_OF_CORES == portMAX_CORE_COUNT )

#define configTICK_CORE    0                /* configTICK_CORE indicates which core should handle the SysTick interrupt */
==> this makes it the primary core (ucPrimaryCoreNum)

Scheduler needs to get started on core0: 
xPortStartScheduler() starts other core: multicore_launch_core1( prvDisableInterruptsAndPortStartSchedulerOnCore );

xPortStartSchedulerOnCore() ==> starts scheduler on its core (0 and 1)

exitScheduler not implemented!

Stack????
extern uint32_t __StackOneBottom; >> linker file?

prvPassiveIdleTask
 * The passive idle task is used for all the additional cores in a SMP
 * system. There must be only 1 active idle task and the rest are passive
 * idle tasks.
