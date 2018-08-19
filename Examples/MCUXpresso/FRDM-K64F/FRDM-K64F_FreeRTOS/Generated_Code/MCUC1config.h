/**
 * \file
 * \brief Configuration header file for McuLibConfig
 *
 * This header file is used to configure settings of the McuLibConfig module.
 */

#ifndef __MCUC1_CONFIG_H
#define __MCUC1_CONFIG_H

/* identification of CPU/core used. __CORTEX_M is defined in CMSIS-Core.
   Otherwise CPU Family is set automatically by Processor Expert: detected: Kinetis (supported: "Kinetis", "S32K", "HCS08")
*/
#define MCUC1_CONFIG_CPU_IS_ARM_CORTEX_M    (1 || defined(__CORTEX_M))
  /*!< 1: ARM Cortex-M family, 0 otherwise */
#define MCUC1_CONFIG_CPU_IS_KINETIS         (1 && MCUC1_CONFIG_CPU_IS_ARM_CORTEX_M)
  /*!< 1: NXP Kinetis CPU family, 0: otherwise */
#define MCUC1_CONFIG_CPU_IS_S32K            (0 && MCUC1_CONFIG_CPU_IS_ARM_CORTEX_M)
  /*!< 1: NXP S32K CPU family, 0: otherwise */
#define MCUC1_CONFIG_CPU_IS_LPC             (0 && MCUC1_CONFIG_CPU_IS_ARM_CORTEX_M)
  /*!< 1: NXP LPC CPU family, 0: otherwise */
#define MCUC1_CONFIG_CPU_IS_STM32           (0 && MCUC1_CONFIG_CPU_IS_ARM_CORTEX_M)
  /*!< 1: STM32 ARM Cortex CPU family, 0: otherwise */
#define MCUC1_CONFIG_CPU_IS_HCS08           (0 && MCUC1_CONFIG_CPU_IS_ARM_CORTEX_M)
  /*!< 1: HCS08 CPU family, 0: otherwise */

/* identification of Cortex-M core. __FPU_USED can be defined in CMSIS-Core */
#define MCUC1_CONFIG_CORTEX_M      (4)
  /*!< 0: Cortex-M0, 3: M3, 4: M4, 7: M7, -1 otherwise */
#define MCUC1_CONFIG_FPU_PRESENT   (1 || (defined(__FPU_PRESENT) && (__FPU_PRESENT)==1))
  /*!< 1: floating point unit present, 0: otherwise */
#define MCUC1_CONFIG_FPU_USED      (1 || (defined(__FPU_USED) && (__FPU_USED)==1))
  /*!< 1: using floating point unit, 0: otherwise */

/* macro for little and big endianess. ARM is little endian */
#define MCUC1_CONFIG_CPU_IS_LITTLE_ENDIAN   (MCUC1_CONFIG_CPU_IS_ARM_CORTEX_M)

/* Identifiers used to identify the SDK */
#define MCUC1_CONFIG_SDK_GENERIC             0
  /*!< using a generic API/SDK */
#define MCUC1_CONFIG_SDK_PROCESSOR_EXPERT    1
  /*!< using Processor Expert SDK */
#define MCUC1_CONFIG_SDK_KINETIS_1_3         2
  /*!< using NXP Kinetis SDK V1.3 */
#define MCUC1_CONFIG_SDK_KINETIS_2_0         3
  /*!< using NXP Kinetis SDK V2.0 */
#define MCUC1_CONFIG_SDK_MCUXPRESSO_2_0      4
  /*!< same as Kinetis SDK v2.0 */
#define MCUC1_CONFIG_SDK_S32K                5
  /*!< SDK for S32K */

/* specify the SDK and API used */
#ifndef MCUC1_CONFIG_SDK_VERSION_USED
#if MCUC1_CONFIG_CPU_IS_STM32
  #define MCUC1_CONFIG_SDK_VERSION_USED  MCUC1_CONFIG_SDK_GENERIC
    /*!< identify the version of SDK/API used. For STM32 we are using a generic SDK (actually the CubeMX one) */
#else
  #define MCUC1_CONFIG_SDK_VERSION_USED  MCUC1_CONFIG_SDK_PROCESSOR_EXPERT
    /*!< identify the version of SDK/API used */
#endif
#endif


/* Configuration macro if FreeRTOS is used */
#ifndef MCUC1_CONFIG_SDK_USE_FREERTOS
  #define MCUC1_CONFIG_SDK_USE_FREERTOS           (1)
    /*!< 1: Use FreeRTOS; 0: no FreeRTOS used */
#endif

/* special macro to identify a set of SDKs used */
#define MCUC1_CONFIG_NXP_SDK_USED                (   (MCUC1_CONFIG_SDK_VERSION_USED==MCUC1_CONFIG_SDK_KINETIS_1_3) \
                                                  || (MCUC1_CONFIG_SDK_VERSION_USED==MCUC1_CONFIG_SDK_KINETIS_2_0) \
                                                  || (MCUC1_CONFIG_SDK_VERSION_USED==MCUC1_CONFIG_SDK_MCUXPRESSO_2_0) \
                                                  || (MCUC1_CONFIG_SDK_VERSION_USED==MCUC1_CONFIG_SDK_S32K) \
                                                 )
  /*!< Using one of the Freescale/NXP SDKs */

#define MCUC1_CONFIG_NXP_SDK_2_0_USED            (   (MCUC1_CONFIG_SDK_VERSION_USED==MCUC1_CONFIG_SDK_KINETIS_2_0) \
                                                  || (MCUC1_CONFIG_SDK_VERSION_USED==MCUC1_CONFIG_SDK_MCUXPRESSO_2_0) \
                                                 )
  /*!< Using Freescale/NXP SDK V2.0 */

#define MCUC1_CONFIG_PEX_SDK_USED                (MCUC1_CONFIG_SDK_VERSION_USED==MCUC1_CONFIG_SDK_PROCESSOR_EXPERT)
  /*!< Using Processor Expert API */

#endif /* __MCUC1_CONFIG_H */

