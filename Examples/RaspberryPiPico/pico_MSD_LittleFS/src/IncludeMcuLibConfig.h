/*
 * Copyright (c) 2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/* header file is included with -include compiler option */

#ifndef MCULIB_CONFIG_CONFIG_H_
#define MCULIB_CONFIG_CONFIG_H_

/* ---------------------------------------------------------------------------------------*/
/* SDK */
#define McuLib_CONFIG_CPU_IS_KINETIS                (0)
#define McuLib_CONFIG_CORTEX_M                      (0) /* RP2040 is a Cortex-M0+ */
#define McuLib_CONFIG_CPU_IS_RPxxxx                 (1)
#define McuLib_CONFIG_CPU_VARIANT                   McuLib_CONFIG_CPU_VARIANT_RP2040
#define McuLib_CONFIG_SDK_VERSION_USED              McuLib_CONFIG_SDK_RPI_PICO
/* ---------------------------------------------------------------------- */
/* FreeRTOS */
#define McuLib_CONFIG_SDK_USE_FREERTOS              (1)
#define configMINIMAL_STACK_SIZE                    (128/sizeof(StackType_t)) /* stack size for IDLE task */
#define configTIMER_TASK_STACK_DEPTH                (600/sizeof(StackType_t)) /* stack size for Timer Service task */
#define configTOTAL_HEAP_SIZE                       (64*1024)
#define configUSE_SEGGER_SYSTEM_VIEWER_HOOKS        (1)

/* SMP port only */
#define configTICK_CORE                         0 /* indicate which core should handle the SysTick */

/* RP2040 specific */
#define configSUPPORT_PICO_SYNC_INTEROP         1
#define configSUPPORT_PICO_TIME_INTEROP         1

/* Set configNUMBER_OF_CORES to the number of available processor cores. Defaults to 1 if left undefined. */
#define configNUMBER_OF_CORES                       (1)

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
/* -------------------------------------------------*/
/* RTT */
#define McuRTT_CONFIG_RTT_BUFFER_SIZE_DOWN            (128)
#define McuRTT_CONFIG_BLOCKING_SEND                   (1) /* 0: do not block if buffer full */
#define McuRTT_CONFIG_BLOCKING_SEND_TIMEOUT_MS        (10)
#define McuRTT_CONFIG_BLOCKING_SEND_WAIT_MS           (1)
#define McuRTT_CONFIG_RTT_BUFFER_SIZE_UP              (2*1024)
/* ---------------------------------------------------------------------- */
/* McuShell */
#define McuShell_CONFIG_PROJECT_NAME_STRING         "Pico"
#define McuShell_CONFIG_PROMPT_STRING               "> "
#define McuShell_CONFIG_MULTI_CMD_ENABLED           (1)
#define McuShell_CONFIG_MULTI_CMD_SIZE              (96)
#define McuShell_CONFIG_DEFAULT_SHELL_BUFFER_SIZE   (128)
/* ---------------------------------------------------------------------- */
/* McuFlash */
#define McuFlash_CONFIG_IS_ENABLED                  (1) /* enable for MinINI with Flash FS */
#define McuFlash_CONFIG_NOF_BLOCKS                  (32) /* total number of flash blocks */
#define McuFlash_CONFIG_MEM_START                   ((XIP_BASE+2048*1024)-(McuFlash_CONFIG_NOF_BLOCKS*McuFlash_CONFIG_FLASH_BLOCK_SIZE)) /* pico has 2 MB Flash, starting from XIP_BASE */
/* -------------------------------------------------*/
/* LittleFS */
#define LITTLEFS_CONFIG_ENABLED                       (1) /* enable the LittleFS file system */
#if 0 /* using Winbond external flash */
  #define McuLittleFSBlockDevice_CONFIG_MEMORY_TYPE     McuLittleFSBlockDevice_CONFIG_MEMORY_TYPE_WINBOND_W25Q128
#else /* using internal flash with McuFlash */
  #define McuLittleFSBlockDevice_CONFIG_MEMORY_TYPE       McuLittleFSBlockDevice_CONFIG_MEMORY_TYPE_MCU_FLASH

  #define McuLittleFS_CONFIG_FILESYSTEM_PROG_BUFFER_SIZE  (McuFlash_CONFIG_FLASH_BLOCK_SIZE)
  #define McuLittleFS_CONFIG_FILESYSTEM_READ_BUFFER_SIZE  (McuFlash_CONFIG_FLASH_BLOCK_SIZE)
  #define McuLittleFS_CONFIG_FILESYSTEM_CACHE_SIZE        (McuFlash_CONFIG_FLASH_BLOCK_SIZE)

  #define McuLittleFS_CONFIG_BLOCK_SIZE                   (McuFlash_CONFIG_FLASH_BLOCK_SIZE)
  #define McuLittleFS_CONFIG_BLOCK_COUNT                  (McuFlash_CONFIG_NOF_BLOCKS)
  #define McuLittleFS_CONFIG_BLOCK_OFFSET                 ((McuFlash_CONFIG_MEM_START)/(McuFlash_CONFIG_FLASH_BLOCK_SIZE))
#endif
/* ---------------------------------------------------------------------------------------*/
/* MinINI */
#if 1 /* use minINI with littleFS */
  #define McuMinINI_CONFIG_FS                           McuMinINI_CONFIG_FS_TYPE_LITTLE_FS
#else /* use raw flash blocks for MinINI */
  #define McuMinINI_CONFIG_FS                         (McuMinINI_CONFIG_FS_TYPE_FLASH_FS) /* MinINI with internal FLASH */
  #define McuMinINI_CONFIG_FLASH_NVM_ADDR_START       ((XIP_BASE+2048*1024)-(McuMinINI_CONFIG_FLASH_NVM_NOF_BLOCKS*McuMinINI_CONFIG_FLASH_NVM_BLOCK_SIZE)) /* pico has 2 MB Flash, starting from XIP_BASE */
  #define McuMinINI_CONFIG_FLASH_NVM_NOF_BLOCKS       (1) /* just use a single block for MinINI */
  #define McuMinINI_CONFIG_FLASH_NVM_BLOCK_SIZE       (McuFlash_CONFIG_FLASH_BLOCK_SIZE) 
  #define McuMinINI_CONFIG_FLASH_NVM_MAX_DATA_SIZE    (0x1000) /* must be multiple of 4K */
  #define McuMinINI_CONFIG_BUFFER_SIZE                (128) /* maximum line and path length */
#endif
/* -------------------------------------------------*/
/* McuLog */
#define McuLog_CONFIG_IS_ENABLED                (1)
#define McuLog_CONFIG_USE_FILE                  (0)
#define McuLog_CONFIG_USE_RTT_CONSOLE           (1)
#define McuLog_CONFIG_NOF_CONSOLE_LOGGER        (2) /* RTT and USB CDC */
#define McuLog_CONFIG_USE_COLOR                 (1)
#define McuLog_CONFIG_LOG_TIMESTAMP_DATE        (0)
/* ---------------------------------------------------------------------------------------*/

#endif /* MCULIB_CONFIG_CONFIG_H_ */
