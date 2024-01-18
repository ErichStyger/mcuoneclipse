/*
 * Copyright (c) 2016-2020, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/* header file is included with -include compiler option
Instructions:
 - Remove the 'Template_' from the name and place this file into your 'src' folder.
 - Include it with the -include compiler option with:  "${ProjDirPath}/source/IncludeMcuLibConfig.h"
 - Add the following to the -I compiler option:
../McuLib
../McuLib/config
../McuLib/config/fonts
../McuLib/fonts
../McuLib/src
../McuLib/FreeRTOS/Source/include
../McuLib/FreeRTOS/Source/portable/GCC/ARM_CM4F
../McuLib/SEGGER_RTT
../McuLib/SEGGER_Sysview
../McuLib/TraceRecorder
../McuLib/TraceRecorder/config
../McuLib/TraceRecorder/include
../McuLib/TraceRecorder/streamports/Jlink_RTT/include
../McuLib/HD44780
../McuLib/FatFS
../McuLib/FatFS/source
 */

#ifndef INCLUDEMCULIBCONFIG_H_
#define INCLUDEMCULIBCONFIG_H_

/* ------------------- SDK/Library ---------------------------*/
#define McuLib_CONFIG_SDK_VERSION_USED  McuLib_CONFIG_SDK_MCUXPRESSO_2_0
/* set the CPU. See McuLibConfig.h for all supported CPUs */
#if 0 /* example configuration for LPC845 */
  #define McuLib_CONFIG_CPU_IS_LPC        (1)  /* LPC family */
  #define McuLib_CONFIG_CORTEX_M          (0)    /*!< 0: Cortex-M0, 3: M3, 4: M4, 7: M7, 33: M33, -1 otherwise */
#elif 0 /* example configuration for LPC55xx */
  #define McuLib_CONFIG_CPU_IS_LPC        (1)  /* LPC family */
  #define McuLib_CONFIG_CPU_IS_LPC55xx    (1)  /* LPC55xx */
  #define McuLib_CONFIG_CORTEX_M          (33)    /*!< 0: Cortex-M0, 3: M3, 4: M4, 7: M7, 33: M33, -1 otherwise */
#elif 1 /* example configuration for Kinetis K22 */
  #define McuLib_CONFIG_CPU_IS_KINETIS    (1)  /* NXP Kinetis family */
  #define McuLib_CONFIG_CORTEX_M          (4)  /*!< 0: Cortex-M0, 3: M3, 4: M4, 7: M7, 33: M33, -1 otherwise */
#elif 0 /* example configuration for i.MX RT */
  #define McuLib_CONFIG_CPU_IS_IMXRT      (1)  /* i.MX RT family */
  #define McuLib_CONFIG_CORTEX_M          (7)  /*!< 0: Cortex-M0, 3: M3, 4: M4, 7: M7, 33: M33, -1 otherwise */
#endif
/* ------------------- RTOS ---------------------------*/
#define McuLib_CONFIG_SDK_USE_FREERTOS       (1)
#define configUSE_TICKLESS_IDLE				 (1)
/* #define configUSE_SEGGER_SYSTEM_VIEWER_HOOKS (1) */
/* #define configTOTAL_HEAP_SIZE                (24*1024) */
/* #define configUSE_HEAP_SECTION_NAME          (1) */
/* #define configHEAP_SECTION_NAME_STRING       ".bss.$SRAM_LOWER.FreeRTOS" */

#define configNUMBER_OF_CORES                       (2)
#if configNUMBER_OF_CORES>1
  /* When using SMP (i.e. configNUMBER_OF_CORES is greater than one), set
  * configRUN_MULTIPLE_PRIORITIES to 0 to allow multiple tasks to run
  * simultaneously only if they do not have equal priority, thereby maintaining
  * the paradigm of a lower priority task never running if a higher priority task
  * is able to run. If configRUN_MULTIPLE_PRIORITIES is set to 1, multiple tasks
  * with different priorities may run simultaneously - so a higher and lower
  * priority task may run on different cores at the same time. */
  #define configRUN_MULTIPLE_PRIORITIES             0

  /* When using SMP (i.e. configNUMBER_OF_CORES is greater than one), set
  * configUSE_CORE_AFFINITY to 1 to enable core affinity feature. When core
  * affinity feature is enabled, the vTaskCoreAffinitySet and vTaskCoreAffinityGet
  * APIs can be used to set and retrieve which cores a task can run on. If
  * configUSE_CORE_AFFINITY is set to 0 then the FreeRTOS scheduler is free to
  * run any task on any available core. */
  #define configUSE_CORE_AFFINITY                   1

  /* When using SMP (i.e. configNUMBER_OF_CORES is greater than one), if
  * configUSE_TASK_PREEMPTION_DISABLE is set to 1, individual tasks can be set to
  * either pre-emptive or co-operative mode using the vTaskPreemptionDisable and
  * vTaskPreemptionEnable APIs. */
  #define configUSE_TASK_PREEMPTION_DISABLE         0

  /* When using SMP (i.e. configNUMBER_OF_CORES is greater than one), set
  * configUSE_PASSIVE_IDLE_HOOK to 1 to allow the application writer to use
  * the passive idle task hook to add background functionality without the overhead
  * of a separate task. Defaults to 0 if left undefined. */
  #define configUSE_PASSIVE_IDLE_HOOK               0

  /* When using SMP (i.e. configNUMBER_OF_CORES is greater than one),
  * configTIMER_SERVICE_TASK_CORE_AFFINITY allows the application writer to set
  * the core affinity of the RTOS Daemon/Timer Service task. Defaults to
  * tskNO_AFFINITY if left undefined. */
  #define configTIMER_SERVICE_TASK_CORE_AFFINITY    tskNO_AFFINITY
#endif
/* ------------------- FatFS ---------------------------*/
#define McuLib_CONFIG_USE_FAT_FS             (0)

#endif /* INCLUDEMCULIBCONFIG_H_ */
