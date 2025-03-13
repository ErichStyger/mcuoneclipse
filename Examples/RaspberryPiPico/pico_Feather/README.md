# Adafruit RP2040 Feather
Project for the Raspberry Pi RP204, using the Adafruit Feather board:
https://www.adafruit.com/product/4884

## Build
Project has `Debug`, `Release` and `Test` targets, using CMake Presets. 

Configure:
```
cmake --list-presets
cmake --preset Debug
cmake --preset Release
cmake --preset Test
```

Build:
```
cmake --build --list-presets
cmake --build --preset app-debug
cmake --build --preset app-release
cmake --build --preset app-test
```

Test:
```
ctest --list-presets
ctest --test-dir build/Test -R Led_1
```

Worflow:
```
cmake --workflow --list-presets
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
