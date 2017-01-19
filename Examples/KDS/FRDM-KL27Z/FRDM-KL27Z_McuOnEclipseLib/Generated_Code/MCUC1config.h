#ifndef __MCUC1_CONFIG_H
#define __MCUC1_CONFIG_H

/* Identifiers used to identify the SDK */
#define MCUC1_CONFIG_SDK_GENERIC             0 /* using a generic API/SDK */
#define MCUC1_CONFIG_SDK_PROCESSOR_EXPERT    1 /* using Processor Expert SDK */
#define MCUC1_CONFIG_SDK_KINETIS_1_3         2 /* using NXP Kinetis SDK V1.3 */
#define MCUC1_CONFIG_SDK_KINETIS_2_0         3 /* using NXP Kinetis SDK V2.0 */
#define MCUC1_CONFIG_SDK_MCUXPRESSO_2_0      4 /* same as Kinetis SDK v2.0 */

/* specify the SDK and API used */
#ifndef MCUC1_CONFIG_SDK_VERSION_USED
  #define MCUC1_CONFIG_SDK_VERSION_USED  MCUC1_CONFIG_SDK_MCUXPRESSO_2_0
#endif

/* special macro to identify a set of SDKs used */
#define MCUC1_CONFIG_NXP_SDK_USED                (   (MCUC1_CONFIG_SDK_VERSION_USED==MCUC1_CONFIG_SDK_KINETIS_1_3) \
                                                  || (MCUC1_CONFIG_SDK_VERSION_USED==MCUC1_CONFIG_SDK_KINETIS_2_0) \
                                                  || (MCUC1_CONFIG_SDK_VERSION_USED==MCUC1_CONFIG_SDK_MCUXPRESSO_2_0) \
                                                 )
  /*!< Using one of the Freescale/NXP SDKs */

#define MCUC1_CONFIG_NXP_SDK_2_0_USED            (   (MCUC1_CONFIG_SDK_VERSION_USED==MCUC1_CONFIG_SDK_KINETIS_2_0) \
                                                  || (MCUC1_CONFIG_SDK_VERSION_USED==MCUC1_CONFIG_SDK_MCUXPRESSO_2_0) \
                                                 )
  /*!< Using Freescale/NXP SDK V2.0 */

#define MCUC1_CONFIG_PEX_SDK_USED                (MCUC1_CONFIG_SDK_VERSION_USED==MCUC1_CONFIG_SDK_PROCESSOR_EXPERT)
  /*!< Using Processor Expert API */

#endif /* __MCUC1_CONFIG_H */

