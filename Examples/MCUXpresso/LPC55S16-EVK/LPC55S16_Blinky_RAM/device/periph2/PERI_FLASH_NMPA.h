/*
** ###################################################################
**     Processors:          LPC5512JBD100
**                          LPC5512JBD64
**                          LPC5514JBD100
**                          LPC5514JBD64
**                          LPC5514JEV59
**                          LPC5516JBD100
**                          LPC5516JBD64
**                          LPC5516JEV59
**                          LPC5516JEV98
**                          LPC55S14JBD100
**                          LPC55S14JBD64
**                          LPC55S14JEV59
**                          LPC55S16JBD100
**                          LPC55S16JBD64
**                          LPC55S16JEV59
**                          LPC55S16JEV98
**
**     Version:             rev. 1.1, 2019-12-03
**     Build:               b240704
**
**     Abstract:
**         CMSIS Peripheral Access Layer for FLASH_NMPA
**
**     Copyright 1997-2016 Freescale Semiconductor, Inc.
**     Copyright 2016-2024 NXP
**     SPDX-License-Identifier: BSD-3-Clause
**
**     http:                 www.nxp.com
**     mail:                 support@nxp.com
**
**     Revisions:
**     - rev. 1.0 (2018-08-22)
**         Initial version based on v0.2UM
**     - rev. 1.1 (2019-12-03)
**         Initial version based on v0.6UM
**
** ###################################################################
*/

/*!
 * @file FLASH_NMPA.h
 * @version 1.1
 * @date 2019-12-03
 * @brief CMSIS Peripheral Access Layer for FLASH_NMPA
 *
 * CMSIS Peripheral Access Layer for FLASH_NMPA
 */

#if !defined(FLASH_NMPA_H_)
#define FLASH_NMPA_H_                            /**< Symbol preventing repeated inclusion */

#if (defined(CPU_LPC5512JBD100) || defined(CPU_LPC5512JBD64))
#include "LPC5512_COMMON.h"
#elif (defined(CPU_LPC5514JBD100) || defined(CPU_LPC5514JBD64) || defined(CPU_LPC5514JEV59))
#include "LPC5514_COMMON.h"
#elif (defined(CPU_LPC5516JBD100) || defined(CPU_LPC5516JBD64) || defined(CPU_LPC5516JEV59) || defined(CPU_LPC5516JEV98))
#include "LPC5516_COMMON.h"
#elif (defined(CPU_LPC55S14JBD100) || defined(CPU_LPC55S14JBD64) || defined(CPU_LPC55S14JEV59))
#include "LPC55S14_COMMON.h"
#elif (defined(CPU_LPC55S16JBD100) || defined(CPU_LPC55S16JBD64) || defined(CPU_LPC55S16JEV59) || defined(CPU_LPC55S16JEV98))
#include "LPC55S16_COMMON.h"
#else
  #error "No valid CPU defined!"
#endif

/* ----------------------------------------------------------------------------
   -- Device Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup Peripheral_access_layer Device Peripheral Access Layer
 * @{
 */


/*
** Start of section using anonymous unions
*/

#if defined(__ARMCC_VERSION)
  #if (__ARMCC_VERSION >= 6010050)
    #pragma clang diagnostic push
  #else
    #pragma push
    #pragma anon_unions
  #endif
#elif defined(__GNUC__)
  /* anonymous unions are enabled by default */
#elif defined(__IAR_SYSTEMS_ICC__)
  #pragma language=extended
#else
  #error Not supported compiler type
#endif

/* ----------------------------------------------------------------------------
   -- FLASH_NMPA Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup FLASH_NMPA_Peripheral_Access_Layer FLASH_NMPA Peripheral Access Layer
 * @{
 */

/** FLASH_NMPA - Size of Registers Arrays */
#define FLASH_NMPA_GPO0_GPO0_ARRAY_GPO0_ARRAY_COUNT 4u
#define FLASH_NMPA_GPO1_GPO1_ARRAY_GPO1_ARRAY_COUNT 4u
#define FLASH_NMPA_GPO2_GPO2_ARRAY_GPO2_ARRAY_COUNT 4u
#define FLASH_NMPA_GPO3_GPO3_ARRAY_GPO3_ARRAY_COUNT 4u
#define FLASH_NMPA_GPO_CHECKSUM_GPO_CHECKSUM_ARRAY_GPO_CHECKSUM_ARRAY_COUNT 4u
#define FLASH_NMPA_FINAL_TEST_BATCH_ID_FINAL_TEST_BATCH_ID_ARRAY_FINAL_TEST_BATCH_ID_ARRAY_COUNT 4u
#define FLASH_NMPA_UUID_UUID_ARRAY_UUID_ARRAY_COUNT 4u
#define FLASH_NMPA_DCDC_POWER_PROFILE_HIGH_DCDC_POWER_PROFILE_HIGH_ARRAY_DCDC_POWER_PROFILE_HIGH_ARRAY_COUNT 2u
#define FLASH_NMPA_DCDC_POWER_PROFILE_LOW_DCDC_POWER_PROFILE_LOW_ARRAY_DCDC_POWER_PROFILE_LOW_ARRAY_COUNT 2u
#define FLASH_NMPA_DCDC_POWER_PROFILE_MEDIUM_DCDC_POWER_PROFILE_MEDIUM_ARRAY_DCDC_POWER_PROFILE_MEDIUM_ARRAY_COUNT 2u
#define FLASH_NMPA_AUX_BIAS_CURVE_AMBIENT_AUX_BIAS_CURVE_AMBIENT_ARRAY_AUX_BIAS_CURVE_AMBIENT_ARRAY_COUNT 4u
#define FLASH_NMPA_AUX_BIAS_CURVE_TEMP_AUX_BIAS_CURVE_TEMP_ARRAY_AUX_BIAS_CURVE_TEMP_ARRAY_COUNT 4u
#define FLASH_NMPA_PVT_MONITOR_0_PVT_MONITOR_0_ARRAY_PVT_MONITOR_0_ARRAY_COUNT 3u
#define FLASH_NMPA_PVT_MONITOR_1_PVT_MONITOR_1_ARRAY_PVT_MONITOR_1_ARRAY_COUNT 3u
#define FLASH_NMPA_NXP_DEVICE_PRIVATE_KEY_COUNT   13u
#define FLASH_NMPA_NXP_DEVICE_CERTIFICATE_0_COUNT 4u
#define FLASH_NMPA_NXP_DEVICE_CERTIFICATE_1_COUNT 4u
#define FLASH_NMPA_NXP_DEVICE_CERTIFICATE_2_COUNT 4u
#define FLASH_NMPA_NXP_DEVICE_CERTIFICATE_3_COUNT 4u
#define FLASH_NMPA_SHA256_DIGEST_COUNT            8u
#define FLASH_NMPA_ECID_BACKUP_ECID_BACKUP_ARRAY_ECID_BACKUP_ARRAY_COUNT 4u
#define FLASH_NMPA_CHECKSUM_COUNT                 4u

/** FLASH_NMPA - Register Layout Typedef */
typedef struct {
  union {                                          /* offset: 0x0 */
    struct {                                         /* offset: 0x0 */
      __IO uint32_t GPO0_0;                            /**< GPO0 register 0 description, offset: 0x0 */
      __IO uint32_t GPO0_1;                            /**< GPO0 register 1 description, offset: 0x4 */
      __IO uint32_t GPO0_2;                            /**< GPO0 register 2 description, offset: 0x8 */
      __IO uint32_t GPO0_3;                            /**< GPO0 register 3 description, offset: 0xC */
    } GPO0;
    __IO uint32_t GPO0_ARRAY[FLASH_NMPA_GPO0_GPO0_ARRAY_GPO0_ARRAY_COUNT];   /**< GPO0 array description, array offset: 0x0, array step: 0x4 */
  };
  union {                                          /* offset: 0x10 */
    struct {                                         /* offset: 0x10 */
      __IO uint32_t GPO1_0;                            /**< GPO1 register 0 description, offset: 0x10 */
      __IO uint32_t GPO1_1;                            /**< GPO1 register 1 description, offset: 0x14 */
      __IO uint32_t GPO1_2;                            /**< GPO1 register 2 description, offset: 0x18 */
      __IO uint32_t GPO1_3;                            /**< GPO1 register 3 description, offset: 0x1C */
    } GPO1;
    __IO uint32_t GPO1_ARRAY[FLASH_NMPA_GPO1_GPO1_ARRAY_GPO1_ARRAY_COUNT];   /**< GPO1 array description, array offset: 0x10, array step: 0x4 */
  };
  union {                                          /* offset: 0x20 */
    struct {                                         /* offset: 0x20 */
      __IO uint32_t GPO2_0;                            /**< GPO2 register 0 description, offset: 0x20 */
      __IO uint32_t GPO2_1;                            /**< GPO2 register 1 description, offset: 0x24 */
      __IO uint32_t GPO2_2;                            /**< GPO2 register 2 description, offset: 0x28 */
      __IO uint32_t GPO2_3;                            /**< GPO2 register 3 description, offset: 0x2C */
    } GPO2;
    __IO uint32_t GPO2_ARRAY[FLASH_NMPA_GPO2_GPO2_ARRAY_GPO2_ARRAY_COUNT];   /**< GPO2 array description, array offset: 0x20, array step: 0x4 */
  };
  union {                                          /* offset: 0x30 */
    struct {                                         /* offset: 0x30 */
      __IO uint32_t GPO3_0;                            /**< GPO3 register 0 description, offset: 0x30 */
      __IO uint32_t GPO3_1;                            /**< GPO3 register 1 description, offset: 0x34 */
      __IO uint32_t GPO3_2;                            /**< GPO3 register 2 description, offset: 0x38 */
      __IO uint32_t GPO3_3;                            /**< GPO3 register 3 description, offset: 0x3C */
    } GPO3;
    __IO uint32_t GPO3_ARRAY[FLASH_NMPA_GPO3_GPO3_ARRAY_GPO3_ARRAY_COUNT];   /**< GPO3 array description, array offset: 0x30, array step: 0x4 */
  };
  union {                                          /* offset: 0x40 */
    struct {                                         /* offset: 0x40 */
      __IO uint32_t GPO_CHECKSUM_0;                    /**< checksum of the GPO data in words 0, offset: 0x40 */
      __IO uint32_t GPO_CHECKSUM_1;                    /**< checksum of the GPO data in words 1, offset: 0x44 */
      __IO uint32_t GPO_CHECKSUM_2;                    /**< checksum of the GPO data in words 2, offset: 0x48 */
      __IO uint32_t GPO_CHECKSUM_3;                    /**< checksum of the GPO data in words 3, offset: 0x4C */
    } GPO_CHECKSUM;
    __IO uint32_t GPO_CHECKSUM_ARRAY[FLASH_NMPA_GPO_CHECKSUM_GPO_CHECKSUM_ARRAY_GPO_CHECKSUM_ARRAY_COUNT];   /**< checksum of the GPO data in words [3:0], array offset: 0x40, array step: 0x4 */
  };
  union {                                          /* offset: 0x50 */
    struct {                                         /* offset: 0x50 */
      __IO uint32_t FINAL_TEST_BATCH_ID_0;             /**< offset: 0x50 */
      __IO uint32_t FINAL_TEST_BATCH_ID_1;             /**< offset: 0x54 */
      __IO uint32_t FINAL_TEST_BATCH_ID_2;             /**< offset: 0x58 */
      __IO uint32_t FINAL_TEST_BATCH_ID_3;             /**< offset: 0x5C */
    } FINAL_TEST_BATCH_ID;
    __IO uint32_t FINAL_TEST_BATCH_ID_ARRAY[FLASH_NMPA_FINAL_TEST_BATCH_ID_FINAL_TEST_BATCH_ID_ARRAY_FINAL_TEST_BATCH_ID_ARRAY_COUNT];   /**< array offset: 0x50, array step: 0x4 */
  };
  __IO uint32_t DEVICE_TYPE;                       /**< offset: 0x60 */
  __IO uint32_t FINAL_TEST_PROGRAM_VERSION;        /**< offset: 0x64 */
  __IO uint32_t FINAL_TEST_DATE;                   /**< offset: 0x68 */
  __IO uint32_t FINAL_TEST_TIME;                   /**< offset: 0x6C */
  union {                                          /* offset: 0x70 */
    struct {                                         /* offset: 0x70 */
      __IO uint32_t UUID_0;                            /**< offset: 0x70 */
      __IO uint32_t UUID_1;                            /**< offset: 0x74 */
      __IO uint32_t UUID_2;                            /**< offset: 0x78 */
      __IO uint32_t UUID_3;                            /**< offset: 0x7C */
    } UUID;
    __IO uint32_t UUID_ARRAY[FLASH_NMPA_UUID_UUID_ARRAY_UUID_ARRAY_COUNT];   /**< array offset: 0x70, array step: 0x4 */
  };
  __IO uint32_t WAFER_TEST1_PROGRAM_VERSION;       /**< offset: 0x80 */
  __IO uint32_t WAFER_TEST1_DATE;                  /**< offset: 0x84 */
  __IO uint32_t WAFER_TEST1_TIME;                  /**< offset: 0x88 */
       uint8_t RESERVED_0[4];
  __IO uint32_t WAFER_TEST2_PROGRAM_VERSION;       /**< offset: 0x90 */
  __IO uint32_t WAFER_TEST2_DATE;                  /**< offset: 0x94 */
  __IO uint32_t WAFER_TEST2_TIME;                  /**< offset: 0x98 */
  __IO uint32_t USBCFG;                            /**< offset: 0x9C */
  __IO uint32_t PERIPHENCFG;                       /**< offset: 0xA0 */
  __IO uint32_t RAMSIZECFG;                        /**< offset: 0xA4 */
  __IO uint32_t FLASHSIZECFG;                      /**< offset: 0xA8 */
       uint8_t RESERVED_1[4];
  __IO uint32_t RINGO_0;                           /**< offset: 0xB0 */
  __IO uint32_t RINGO_1;                           /**< offset: 0xB4 */
  __IO uint32_t RINGO_2;                           /**< offset: 0xB8 */
       uint8_t RESERVED_2[4];
  __IO uint32_t FRO_192MHZ;                        /**< offset: 0xC0 */
       uint8_t RESERVED_3[4];
  __IO uint32_t XO_32MHZ;                          /**< offset: 0xC8 */
  __IO uint32_t XO_32KHZ;                          /**< offset: 0xCC */
  __IO uint32_t FRO_1MHZ;                          /**< offset: 0xD0 */
       uint8_t RESERVED_4[4];
  union {                                          /* offset: 0xD8 */
    struct {                                         /* offset: 0xD8 */
      __IO uint32_t DCDC_POWER_PROFILE_HIGH_0;         /**< offset: 0xD8 */
      __IO uint32_t DCDC_POWER_PROFILE_HIGH_1;         /**< offset: 0xDC */
    } DCDC_POWER_PROFILE_HIGH;
    __IO uint32_t DCDC_POWER_PROFILE_HIGH_ARRAY[FLASH_NMPA_DCDC_POWER_PROFILE_HIGH_DCDC_POWER_PROFILE_HIGH_ARRAY_DCDC_POWER_PROFILE_HIGH_ARRAY_COUNT];   /**< array offset: 0xD8, array step: 0x4 */
  };
  union {                                          /* offset: 0xE0 */
    struct {                                         /* offset: 0xE0 */
      __IO uint32_t DCDC_POWER_PROFILE_LOW_0;          /**< offset: 0xE0 */
      __IO uint32_t DCDC_POWER_PROFILE_LOW_1;          /**< offset: 0xE4 */
    } DCDC_POWER_PROFILE_LOW;
    __IO uint32_t DCDC_POWER_PROFILE_LOW_ARRAY[FLASH_NMPA_DCDC_POWER_PROFILE_LOW_DCDC_POWER_PROFILE_LOW_ARRAY_DCDC_POWER_PROFILE_LOW_ARRAY_COUNT];   /**< array offset: 0xE0, array step: 0x4 */
  };
  union {                                          /* offset: 0xE8 */
    struct {                                         /* offset: 0xE8 */
      __IO uint32_t DCDC_POWER_PROFILE_MEDIUM_0;       /**< offset: 0xE8 */
      __IO uint32_t DCDC_POWER_PROFILE_MEDIUM_1;       /**< offset: 0xEC */
    } DCDC_POWER_PROFILE_MEDIUM;
    __IO uint32_t DCDC_POWER_PROFILE_MEDIUM_ARRAY[FLASH_NMPA_DCDC_POWER_PROFILE_MEDIUM_DCDC_POWER_PROFILE_MEDIUM_ARRAY_DCDC_POWER_PROFILE_MEDIUM_ARRAY_COUNT];   /**< array offset: 0xE8, array step: 0x4 */
  };
  __IO uint32_t BOD;                               /**< offset: 0xF0 */
  __IO uint32_t LDO_AO;                            /**< offset: 0xF4 */
  __IO uint32_t SDIO_DELAY;                        /**< offset: 0xF8 */
       uint8_t RESERVED_5[4];
  union {                                          /* offset: 0x100 */
    struct {                                         /* offset: 0x100 */
      __IO uint32_t AUX_BIAS_CURVE_AMBIENT_0;          /**< offset: 0x100 */
      __IO uint32_t AUX_BIAS_CURVE_AMBIENT_1;          /**< offset: 0x104 */
      __IO uint32_t AUX_BIAS_CURVE_AMBIENT_2;          /**< offset: 0x108 */
      __IO uint32_t AUX_BIAS_CURVE_AMBIENT_3;          /**< offset: 0x10C */
    } AUX_BIAS_CURVE_AMBIENT;
    __IO uint32_t AUX_BIAS_CURVE_AMBIENT_ARRAY[FLASH_NMPA_AUX_BIAS_CURVE_AMBIENT_AUX_BIAS_CURVE_AMBIENT_ARRAY_AUX_BIAS_CURVE_AMBIENT_ARRAY_COUNT];   /**< Aux Bias Curve Ambient (30degC), array offset: 0x100, array step: 0x4 */
  };
  union {                                          /* offset: 0x110 */
    struct {                                         /* offset: 0x110 */
      __IO uint32_t AUX_BIAS_CURVE_TEMP_0;             /**< offset: 0x110 */
      __IO uint32_t AUX_BIAS_CURVE_TEMP_1;             /**< offset: 0x114 */
      __IO uint32_t AUX_BIAS_CURVE_TEMP_2;             /**< offset: 0x118 */
      __IO uint32_t AUX_BIAS_CURVE_TEMP_3;             /**< offset: 0x11C */
    } AUX_BIAS_CURVE_TEMP;
    __IO uint32_t AUX_BIAS_CURVE_TEMP_ARRAY[FLASH_NMPA_AUX_BIAS_CURVE_TEMP_AUX_BIAS_CURVE_TEMP_ARRAY_AUX_BIAS_CURVE_TEMP_ARRAY_COUNT];   /**< Aux Bias Curve TEMP (105degC), array offset: 0x110, array step: 0x4 */
  };
  __IO uint32_t TEMP_SENS_VBE1VBE8_REF_1;          /**< offset: 0x120 */
  __IO uint32_t TEMP_SENS_VBE1VBE8_REF_2;          /**< offset: 0x124 */
  __IO uint32_t TEMP_SENS_SLOPE;                   /**< offset: 0x128 */
  __IO uint32_t TEMP_SENS_OFFSET;                  /**< offset: 0x12C */
  union {                                          /* offset: 0x130 */
    struct {                                         /* offset: 0x130 */
      __IO uint32_t PVT_MONITOR_0_RINGO;               /**< offset: 0x130 */
      __IO uint32_t PVT_MONITOR_0_DELAYS_LSB;          /**< offset: 0x134 */
      __IO uint32_t PVT_MONITOR_0_DELAYS_MSB;          /**< offset: 0x138 */
    } PVT_MONITOR_0;
    __IO uint32_t PVT_MONITOR_0_ARRAY[FLASH_NMPA_PVT_MONITOR_0_PVT_MONITOR_0_ARRAY_PVT_MONITOR_0_ARRAY_COUNT];   /**< array offset: 0x130, array step: 0x4 */
  };
       uint8_t RESERVED_6[4];
  union {                                          /* offset: 0x140 */
    struct {                                         /* offset: 0x140 */
      __IO uint32_t PVT_MONITOR_1_RINGO;               /**< offset: 0x140 */
      __IO uint32_t PVT_MONITOR_1_DELAYS_LSB;          /**< offset: 0x144 */
      __IO uint32_t PVT_MONITOR_1_DELAYS_MSB;          /**< offset: 0x148 */
    } PVT_MONITOR_1;
    __IO uint32_t PVT_MONITOR_1_ARRAY[FLASH_NMPA_PVT_MONITOR_1_PVT_MONITOR_1_ARRAY_PVT_MONITOR_1_ARRAY_COUNT];   /**< array offset: 0x140, array step: 0x4 */
  };
  __IO uint32_t NXP_DEVICE_PRIVATE_KEY[FLASH_NMPA_NXP_DEVICE_PRIVATE_KEY_COUNT]; /**< array offset: 0x14C, array step: 0x4 */
  __IO uint32_t NXP_DEVICE_CERTIFICATE_0[FLASH_NMPA_NXP_DEVICE_CERTIFICATE_0_COUNT]; /**< NXP Device Certificate (ECDSA_sign - r[255:128]), array offset: 0x180, array step: 0x4 */
  __IO uint32_t NXP_DEVICE_CERTIFICATE_1[FLASH_NMPA_NXP_DEVICE_CERTIFICATE_1_COUNT]; /**< NXP Device Certificate (ECDSA_sign - r[127:0]), array offset: 0x190, array step: 0x4 */
  __IO uint32_t NXP_DEVICE_CERTIFICATE_2[FLASH_NMPA_NXP_DEVICE_CERTIFICATE_2_COUNT]; /**< NXP Device Certificate (ECDSA_sign - s[255:128]), array offset: 0x1A0, array step: 0x4 */
  __IO uint32_t NXP_DEVICE_CERTIFICATE_3[FLASH_NMPA_NXP_DEVICE_CERTIFICATE_3_COUNT]; /**< NXP Device Certificate (ECDSA_sign - s[127:0]), array offset: 0x1B0, array step: 0x4 */
  __IO uint32_t SHA256_DIGEST[FLASH_NMPA_SHA256_DIGEST_COUNT]; /**< SHA-256 DIGEST (9EC00 - 9FDBC) ROM Patch Area + NXP Area (IMPORTANT NOTE: Pages used for Repair (N-8 to N-3) are excluded from the computation) SHA256_DIGEST0 for DIGEST[31:0]..SHA-256 DIGEST (9EC00 - 9FDBC) ROM Patch Area + NXP Area (IMPORTANT NOTE: Pages used for Repair (N-8 to N-3) are excluded from the computation) SHA256_DIGEST7 for DIGEST[255:224], array offset: 0x1C0, array step: 0x4 */
  union {                                          /* offset: 0x1E0 */
    struct {                                         /* offset: 0x1E0 */
      __IO uint32_t ECID_BACKUP_0;                     /**< offset: 0x1E0 */
      __IO uint32_t ECID_BACKUP_1;                     /**< offset: 0x1E4 */
      __IO uint32_t ECID_BACKUP_2;                     /**< offset: 0x1E8 */
      __IO uint32_t ECID_BACKUP_3;                     /**< offset: 0x1EC */
    } ECID_BACKUP;
    __IO uint32_t ECID_BACKUP_ARRAY[FLASH_NMPA_ECID_BACKUP_ECID_BACKUP_ARRAY_ECID_BACKUP_ARRAY_COUNT];   /**< ECID backup (the original is in page n-1), array offset: 0x1E0, array step: 0x4 */
  };
       uint32_t CHECKSUM[FLASH_NMPA_CHECKSUM_COUNT]; /**< Checksum of the whole page, array offset: 0x1F0, array step: 0x4 */
       uint8_t RESERVED_7[2732];
  __IO uint32_t DIS_ROM_HIDING;                    /**< offset: 0xCAC */
       uint8_t RESERVED_8[12];
  __IO uint32_t PUF_SRAM;                          /**< offset: 0xCBC */
} FLASH_NMPA_Type;

/* ----------------------------------------------------------------------------
   -- FLASH_NMPA Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup FLASH_NMPA_Register_Masks FLASH_NMPA Register Masks
 * @{
 */

/*! @name GPO0_0 - GPO0 register 0 description */
/*! @{ */

#define FLASH_NMPA_GPO0_0_FRO_TRIM_VALID_MASK    (0x1U)
#define FLASH_NMPA_GPO0_0_FRO_TRIM_VALID_SHIFT   (0U)
#define FLASH_NMPA_GPO0_0_FRO_TRIM_VALID(x)      (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_GPO0_0_FRO_TRIM_VALID_SHIFT)) & FLASH_NMPA_GPO0_0_FRO_TRIM_VALID_MASK)

#define FLASH_NMPA_GPO0_0_FRO32K_NTAT_MASK       (0xEU)
#define FLASH_NMPA_GPO0_0_FRO32K_NTAT_SHIFT      (1U)
#define FLASH_NMPA_GPO0_0_FRO32K_NTAT(x)         (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_GPO0_0_FRO32K_NTAT_SHIFT)) & FLASH_NMPA_GPO0_0_FRO32K_NTAT_MASK)

#define FLASH_NMPA_GPO0_0_FRO32K_PTAT_MASK       (0x70U)
#define FLASH_NMPA_GPO0_0_FRO32K_PTAT_SHIFT      (4U)
#define FLASH_NMPA_GPO0_0_FRO32K_PTAT(x)         (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_GPO0_0_FRO32K_PTAT_SHIFT)) & FLASH_NMPA_GPO0_0_FRO32K_PTAT_MASK)

#define FLASH_NMPA_GPO0_0_FRO32K_CAPCAL_MASK     (0xFF80U)
#define FLASH_NMPA_GPO0_0_FRO32K_CAPCAL_SHIFT    (7U)
#define FLASH_NMPA_GPO0_0_FRO32K_CAPCAL(x)       (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_GPO0_0_FRO32K_CAPCAL_SHIFT)) & FLASH_NMPA_GPO0_0_FRO32K_CAPCAL_MASK)

#define FLASH_NMPA_GPO0_0_FIELD_MASK             (0xFFFF0000U)
#define FLASH_NMPA_GPO0_0_FIELD_SHIFT            (16U)
#define FLASH_NMPA_GPO0_0_FIELD(x)               (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_GPO0_0_FIELD_SHIFT)) & FLASH_NMPA_GPO0_0_FIELD_MASK)
/*! @} */

/*! @name GPO0_1 - GPO0 register 1 description */
/*! @{ */

#define FLASH_NMPA_GPO0_1_FIELD_MASK             (0xFFFFFFFFU)
#define FLASH_NMPA_GPO0_1_FIELD_SHIFT            (0U)
#define FLASH_NMPA_GPO0_1_FIELD(x)               (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_GPO0_1_FIELD_SHIFT)) & FLASH_NMPA_GPO0_1_FIELD_MASK)
/*! @} */

/*! @name GPO0_2 - GPO0 register 2 description */
/*! @{ */

#define FLASH_NMPA_GPO0_2_SYSTEM_SPEED_CODE_MASK (0x3U)
#define FLASH_NMPA_GPO0_2_SYSTEM_SPEED_CODE_SHIFT (0U)
/*! SYSTEM_SPEED_CODE - 00 : FRO12MHz 01 : FRO24MHz 10 : FRO48MHz 11 : FRO96MHz */
#define FLASH_NMPA_GPO0_2_SYSTEM_SPEED_CODE(x)   (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_GPO0_2_SYSTEM_SPEED_CODE_SHIFT)) & FLASH_NMPA_GPO0_2_SYSTEM_SPEED_CODE_MASK)

#define FLASH_NMPA_GPO0_2_FLASH_CTRL_OPMODE_MASK (0xCU)
#define FLASH_NMPA_GPO0_2_FLASH_CTRL_OPMODE_SHIFT (2U)
/*! FLASH_CTRL_OPMODE - 00 : Delay Line 01 : RCLK (back up clock) 10 : PCLK (back up clock) */
#define FLASH_NMPA_GPO0_2_FLASH_CTRL_OPMODE(x)   (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_GPO0_2_FLASH_CTRL_OPMODE_SHIFT)) & FLASH_NMPA_GPO0_2_FLASH_CTRL_OPMODE_MASK)

#define FLASH_NMPA_GPO0_2_FIELD_MASK             (0xFFFFFFF0U)
#define FLASH_NMPA_GPO0_2_FIELD_SHIFT            (4U)
#define FLASH_NMPA_GPO0_2_FIELD(x)               (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_GPO0_2_FIELD_SHIFT)) & FLASH_NMPA_GPO0_2_FIELD_MASK)
/*! @} */

/*! @name GPO0_3 - GPO0 register 3 description */
/*! @{ */

#define FLASH_NMPA_GPO0_3_FIELD_MASK             (0xFFFFFFFFU)
#define FLASH_NMPA_GPO0_3_FIELD_SHIFT            (0U)
#define FLASH_NMPA_GPO0_3_FIELD(x)               (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_GPO0_3_FIELD_SHIFT)) & FLASH_NMPA_GPO0_3_FIELD_MASK)
/*! @} */

/*! @name GPO0_ARRAY - GPO0 array description */
/*! @{ */

#define FLASH_NMPA_GPO0_ARRAY_FIELD_MASK         (0xFFFFFFFFU)
#define FLASH_NMPA_GPO0_ARRAY_FIELD_SHIFT        (0U)
#define FLASH_NMPA_GPO0_ARRAY_FIELD(x)           (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_GPO0_ARRAY_FIELD_SHIFT)) & FLASH_NMPA_GPO0_ARRAY_FIELD_MASK)
/*! @} */

/* The count of FLASH_NMPA_GPO0_ARRAY */
#define FLASH_NMPA_GPO0_ARRAY_COUNT              (4U)

/*! @name GPO1_0 - GPO1 register 0 description */
/*! @{ */

#define FLASH_NMPA_GPO1_0_FINAL_TEST_NOT_DONE_MASK (0xFU)
#define FLASH_NMPA_GPO1_0_FINAL_TEST_NOT_DONE_SHIFT (0U)
/*! FINAL_TEST_NOT_DONE - FINAL_TEST_NOT_DONE[3:0]: 1010 : Final Test Not Done. All Other values: Final Test Done. */
#define FLASH_NMPA_GPO1_0_FINAL_TEST_NOT_DONE(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_GPO1_0_FINAL_TEST_NOT_DONE_SHIFT)) & FLASH_NMPA_GPO1_0_FINAL_TEST_NOT_DONE_MASK)

#define FLASH_NMPA_GPO1_0_PARTCONFIG_MASK        (0x7F0U)
#define FLASH_NMPA_GPO1_0_PARTCONFIG_SHIFT       (4U)
/*! PARTCONFIG - Device type number. (E.g : LPC5569 stored as 69 decimal) */
#define FLASH_NMPA_GPO1_0_PARTCONFIG(x)          (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_GPO1_0_PARTCONFIG_SHIFT)) & FLASH_NMPA_GPO1_0_PARTCONFIG_MASK)

#define FLASH_NMPA_GPO1_0_DEVICE_TYPE_SEC_MASK   (0x800U)
#define FLASH_NMPA_GPO1_0_DEVICE_TYPE_SEC_SHIFT  (11U)
/*! DEVICE_TYPE_SEC - Security device type: 0: LPC55xxx (Non Secure Familly) 1: LPC55Sxxx (Secure Familly) */
#define FLASH_NMPA_GPO1_0_DEVICE_TYPE_SEC(x)     (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_GPO1_0_DEVICE_TYPE_SEC_SHIFT)) & FLASH_NMPA_GPO1_0_DEVICE_TYPE_SEC_MASK)

#define FLASH_NMPA_GPO1_0_SRAM_SIZE_MASK         (0xF000U)
#define FLASH_NMPA_GPO1_0_SRAM_SIZE_SHIFT        (12U)
/*! SRAM_SIZE - SRAM_SIZE[3:0]: (For Niobe4) 0000 : 320 KB 0001 : 256 KB 0010 : 144 KB 0011 : 80 KB
 *    (For Niobe4 Mini) 0100 : 96 KB 0101 : 80 KB 0110 : 64 KB 0111 : 48 KB All others : RESERVED
 */
#define FLASH_NMPA_GPO1_0_SRAM_SIZE(x)           (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_GPO1_0_SRAM_SIZE_SHIFT)) & FLASH_NMPA_GPO1_0_SRAM_SIZE_MASK)

#define FLASH_NMPA_GPO1_0_CPU0_SECURITY_EXTENSION_DISABLE_MASK (0xF0000U)
#define FLASH_NMPA_GPO1_0_CPU0_SECURITY_EXTENSION_DISABLE_SHIFT (16U)
/*! CPU0_SECURITY_EXTENSION_DISABLE - CPU0_SECURITY_EXTENSION_DISABLE[3:0]: 1010 : CPU0 Security
 *    Extension is disabled. All Other values: CPU0 Security Extension is enabled.
 */
#define FLASH_NMPA_GPO1_0_CPU0_SECURITY_EXTENSION_DISABLE(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_GPO1_0_CPU0_SECURITY_EXTENSION_DISABLE_SHIFT)) & FLASH_NMPA_GPO1_0_CPU0_SECURITY_EXTENSION_DISABLE_MASK)

#define FLASH_NMPA_GPO1_0_FIELD_MASK             (0xF00000U)
#define FLASH_NMPA_GPO1_0_FIELD_SHIFT            (20U)
#define FLASH_NMPA_GPO1_0_FIELD(x)               (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_GPO1_0_FIELD_SHIFT)) & FLASH_NMPA_GPO1_0_FIELD_MASK)

#define FLASH_NMPA_GPO1_0_ROM_REVISION_MINOR_MASK (0xF000000U)
#define FLASH_NMPA_GPO1_0_ROM_REVISION_MINOR_SHIFT (24U)
/*! ROM_REVISION_MINOR - ROM Revision-Minor [3:0] */
#define FLASH_NMPA_GPO1_0_ROM_REVISION_MINOR(x)  (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_GPO1_0_ROM_REVISION_MINOR_SHIFT)) & FLASH_NMPA_GPO1_0_ROM_REVISION_MINOR_MASK)

#define FLASH_NMPA_GPO1_0_METAL_REVISION_ID_MASK (0xF0000000U)
#define FLASH_NMPA_GPO1_0_METAL_REVISION_ID_SHIFT (28U)
/*! METAL_REVISION_ID - METAL REVISION ID[3:0] */
#define FLASH_NMPA_GPO1_0_METAL_REVISION_ID(x)   (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_GPO1_0_METAL_REVISION_ID_SHIFT)) & FLASH_NMPA_GPO1_0_METAL_REVISION_ID_MASK)
/*! @} */

/*! @name GPO1_1 - GPO1 register 1 description */
/*! @{ */

#define FLASH_NMPA_GPO1_1_ROM_PATCH_VERSION_MASK (0xFU)
#define FLASH_NMPA_GPO1_1_ROM_PATCH_VERSION_SHIFT (0U)
/*! ROM_PATCH_VERSION - ROM Patch Version [3:0] */
#define FLASH_NMPA_GPO1_1_ROM_PATCH_VERSION(x)   (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_GPO1_1_ROM_PATCH_VERSION_SHIFT)) & FLASH_NMPA_GPO1_1_ROM_PATCH_VERSION_MASK)

#define FLASH_NMPA_GPO1_1_CUSTOMER_REVISION_ID_MASK (0xF0U)
#define FLASH_NMPA_GPO1_1_CUSTOMER_REVISION_ID_SHIFT (4U)
/*! CUSTOMER_REVISION_ID - CUSTOMER REVISION ID[3:0] */
#define FLASH_NMPA_GPO1_1_CUSTOMER_REVISION_ID(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_GPO1_1_CUSTOMER_REVISION_ID_SHIFT)) & FLASH_NMPA_GPO1_1_CUSTOMER_REVISION_ID_MASK)

#define FLASH_NMPA_GPO1_1_FIELD_MASK             (0xFFFFFF00U)
#define FLASH_NMPA_GPO1_1_FIELD_SHIFT            (8U)
#define FLASH_NMPA_GPO1_1_FIELD(x)               (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_GPO1_1_FIELD_SHIFT)) & FLASH_NMPA_GPO1_1_FIELD_MASK)
/*! @} */

/*! @name GPO1_2 - GPO1 register 2 description */
/*! @{ */

#define FLASH_NMPA_GPO1_2_HVST_MASK              (0x1U)
#define FLASH_NMPA_GPO1_2_HVST_SHIFT             (0U)
/*! HVST - High Voltage Stress: 0=not done; 1=done. */
#define FLASH_NMPA_GPO1_2_HVST(x)                (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_GPO1_2_HVST_SHIFT)) & FLASH_NMPA_GPO1_2_HVST_MASK)

#define FLASH_NMPA_GPO1_2_FIELD_MASK             (0xFFFFFFFEU)
#define FLASH_NMPA_GPO1_2_FIELD_SHIFT            (1U)
#define FLASH_NMPA_GPO1_2_FIELD(x)               (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_GPO1_2_FIELD_SHIFT)) & FLASH_NMPA_GPO1_2_FIELD_MASK)
/*! @} */

/*! @name GPO1_3 - GPO1 register 3 description */
/*! @{ */

#define FLASH_NMPA_GPO1_3_FIELD_MASK             (0xFFFFFFFFU)
#define FLASH_NMPA_GPO1_3_FIELD_SHIFT            (0U)
#define FLASH_NMPA_GPO1_3_FIELD(x)               (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_GPO1_3_FIELD_SHIFT)) & FLASH_NMPA_GPO1_3_FIELD_MASK)
/*! @} */

/*! @name GPO1_ARRAY - GPO1 array description */
/*! @{ */

#define FLASH_NMPA_GPO1_ARRAY_FIELD_MASK         (0xFFFFFFFFU)
#define FLASH_NMPA_GPO1_ARRAY_FIELD_SHIFT        (0U)
#define FLASH_NMPA_GPO1_ARRAY_FIELD(x)           (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_GPO1_ARRAY_FIELD_SHIFT)) & FLASH_NMPA_GPO1_ARRAY_FIELD_MASK)
/*! @} */

/* The count of FLASH_NMPA_GPO1_ARRAY */
#define FLASH_NMPA_GPO1_ARRAY_COUNT              (4U)

/*! @name GPO2_0 - GPO2 register 0 description */
/*! @{ */

#define FLASH_NMPA_GPO2_0_USBHS_PHY_TRIM_VALID_MASK (0x1U)
#define FLASH_NMPA_GPO2_0_USBHS_PHY_TRIM_VALID_SHIFT (0U)
#define FLASH_NMPA_GPO2_0_USBHS_PHY_TRIM_VALID(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_GPO2_0_USBHS_PHY_TRIM_VALID_SHIFT)) & FLASH_NMPA_GPO2_0_USBHS_PHY_TRIM_VALID_MASK)

#define FLASH_NMPA_GPO2_0_TRIM_USB_REG_ENV_TAIL_ADJ_VD_MASK (0x6U)
#define FLASH_NMPA_GPO2_0_TRIM_USB_REG_ENV_TAIL_ADJ_VD_SHIFT (1U)
#define FLASH_NMPA_GPO2_0_TRIM_USB_REG_ENV_TAIL_ADJ_VD(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_GPO2_0_TRIM_USB_REG_ENV_TAIL_ADJ_VD_SHIFT)) & FLASH_NMPA_GPO2_0_TRIM_USB_REG_ENV_TAIL_ADJ_VD_MASK)

#define FLASH_NMPA_GPO2_0_TRIM_USBPHY_TX_D_CAL_MASK (0x78U)
#define FLASH_NMPA_GPO2_0_TRIM_USBPHY_TX_D_CAL_SHIFT (3U)
#define FLASH_NMPA_GPO2_0_TRIM_USBPHY_TX_D_CAL(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_GPO2_0_TRIM_USBPHY_TX_D_CAL_SHIFT)) & FLASH_NMPA_GPO2_0_TRIM_USBPHY_TX_D_CAL_MASK)

#define FLASH_NMPA_GPO2_0_TRIM_USBPHY_TX_CAL45DP_MASK (0xF80U)
#define FLASH_NMPA_GPO2_0_TRIM_USBPHY_TX_CAL45DP_SHIFT (7U)
#define FLASH_NMPA_GPO2_0_TRIM_USBPHY_TX_CAL45DP(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_GPO2_0_TRIM_USBPHY_TX_CAL45DP_SHIFT)) & FLASH_NMPA_GPO2_0_TRIM_USBPHY_TX_CAL45DP_MASK)

#define FLASH_NMPA_GPO2_0_TRIM_USBPHY_TX_CAL45DN_MASK (0x1F000U)
#define FLASH_NMPA_GPO2_0_TRIM_USBPHY_TX_CAL45DN_SHIFT (12U)
#define FLASH_NMPA_GPO2_0_TRIM_USBPHY_TX_CAL45DN(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_GPO2_0_TRIM_USBPHY_TX_CAL45DN_SHIFT)) & FLASH_NMPA_GPO2_0_TRIM_USBPHY_TX_CAL45DN_MASK)

#define FLASH_NMPA_GPO2_0_TRIM_USB2_REFBIAS_TST_MASK (0x60000U)
#define FLASH_NMPA_GPO2_0_TRIM_USB2_REFBIAS_TST_SHIFT (17U)
#define FLASH_NMPA_GPO2_0_TRIM_USB2_REFBIAS_TST(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_GPO2_0_TRIM_USB2_REFBIAS_TST_SHIFT)) & FLASH_NMPA_GPO2_0_TRIM_USB2_REFBIAS_TST_MASK)

#define FLASH_NMPA_GPO2_0_TRIM_USB2_REFBIAS_VBGADJ_MASK (0x380000U)
#define FLASH_NMPA_GPO2_0_TRIM_USB2_REFBIAS_VBGADJ_SHIFT (19U)
#define FLASH_NMPA_GPO2_0_TRIM_USB2_REFBIAS_VBGADJ(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_GPO2_0_TRIM_USB2_REFBIAS_VBGADJ_SHIFT)) & FLASH_NMPA_GPO2_0_TRIM_USB2_REFBIAS_VBGADJ_MASK)

#define FLASH_NMPA_GPO2_0_TRIM_PLL_CTRL0_DIV_SEL_MASK (0x1C00000U)
#define FLASH_NMPA_GPO2_0_TRIM_PLL_CTRL0_DIV_SEL_SHIFT (22U)
#define FLASH_NMPA_GPO2_0_TRIM_PLL_CTRL0_DIV_SEL(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_GPO2_0_TRIM_PLL_CTRL0_DIV_SEL_SHIFT)) & FLASH_NMPA_GPO2_0_TRIM_PLL_CTRL0_DIV_SEL_MASK)

#define FLASH_NMPA_GPO2_0_FLASH_SIZE_MASK        (0xE000000U)
#define FLASH_NMPA_GPO2_0_FLASH_SIZE_SHIFT       (25U)
/*! FLASH_SIZE - (For Niobe4) 000 : 640 KB 001 : 512 KB 010 : 256 KB 011 : 128 KB 100 : 0 KB All
 *    others : RESERVED (For Niobe4 Mini) FLASH_SIZE[2:0] 000 : 256 KB 001 : 128 KB 010 : 80 KB
 *    (reserved) 011 : 64 KB 100 : 0 kB (reserved) All others : RESERVED
 */
#define FLASH_NMPA_GPO2_0_FLASH_SIZE(x)          (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_GPO2_0_FLASH_SIZE_SHIFT)) & FLASH_NMPA_GPO2_0_FLASH_SIZE_MASK)

#define FLASH_NMPA_GPO2_0_CPU0_SECURITY_EXTENSION_DISABLE_MASK (0xF0000000U)
#define FLASH_NMPA_GPO2_0_CPU0_SECURITY_EXTENSION_DISABLE_SHIFT (28U)
/*! CPU0_SECURITY_EXTENSION_DISABLE - CPU0_SECURITY_EXTENSION_DISABLE[3:0]: 1010 : CPU0 Security
 *    Extension is disabled. All Other values: CPU0 Security Extension is enabled.
 */
#define FLASH_NMPA_GPO2_0_CPU0_SECURITY_EXTENSION_DISABLE(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_GPO2_0_CPU0_SECURITY_EXTENSION_DISABLE_SHIFT)) & FLASH_NMPA_GPO2_0_CPU0_SECURITY_EXTENSION_DISABLE_MASK)
/*! @} */

/*! @name GPO2_1 - GPO2 register 1 description */
/*! @{ */

#define FLASH_NMPA_GPO2_1_FIELD_MASK             (0xFFFFFFFFU)
#define FLASH_NMPA_GPO2_1_FIELD_SHIFT            (0U)
#define FLASH_NMPA_GPO2_1_FIELD(x)               (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_GPO2_1_FIELD_SHIFT)) & FLASH_NMPA_GPO2_1_FIELD_MASK)
/*! @} */

/*! @name GPO2_2 - GPO2 register 2 description */
/*! @{ */

#define FLASH_NMPA_GPO2_2_FIELD_MASK             (0xFFFFFFFFU)
#define FLASH_NMPA_GPO2_2_FIELD_SHIFT            (0U)
#define FLASH_NMPA_GPO2_2_FIELD(x)               (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_GPO2_2_FIELD_SHIFT)) & FLASH_NMPA_GPO2_2_FIELD_MASK)
/*! @} */

/*! @name GPO2_3 - GPO2 register 3 description */
/*! @{ */

#define FLASH_NMPA_GPO2_3_FIELD_MASK             (0xFFFFFFFFU)
#define FLASH_NMPA_GPO2_3_FIELD_SHIFT            (0U)
#define FLASH_NMPA_GPO2_3_FIELD(x)               (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_GPO2_3_FIELD_SHIFT)) & FLASH_NMPA_GPO2_3_FIELD_MASK)
/*! @} */

/*! @name GPO2_ARRAY - GPO2 array description */
/*! @{ */

#define FLASH_NMPA_GPO2_ARRAY_FIELD_MASK         (0xFFFFFFFFU)
#define FLASH_NMPA_GPO2_ARRAY_FIELD_SHIFT        (0U)
#define FLASH_NMPA_GPO2_ARRAY_FIELD(x)           (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_GPO2_ARRAY_FIELD_SHIFT)) & FLASH_NMPA_GPO2_ARRAY_FIELD_MASK)
/*! @} */

/* The count of FLASH_NMPA_GPO2_ARRAY */
#define FLASH_NMPA_GPO2_ARRAY_COUNT              (4U)

/*! @name GPO3_0 - GPO3 register 0 description */
/*! @{ */

#define FLASH_NMPA_GPO3_0_AUX_BIAS_TRIM_VALID_MASK (0x1U)
#define FLASH_NMPA_GPO3_0_AUX_BIAS_TRIM_VALID_SHIFT (0U)
#define FLASH_NMPA_GPO3_0_AUX_BIAS_TRIM_VALID(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_GPO3_0_AUX_BIAS_TRIM_VALID_SHIFT)) & FLASH_NMPA_GPO3_0_AUX_BIAS_TRIM_VALID_MASK)

#define FLASH_NMPA_GPO3_0_AUX_BIAS_ITRIM_MASK    (0x3EU)
#define FLASH_NMPA_GPO3_0_AUX_BIAS_ITRIM_SHIFT   (1U)
#define FLASH_NMPA_GPO3_0_AUX_BIAS_ITRIM(x)      (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_GPO3_0_AUX_BIAS_ITRIM_SHIFT)) & FLASH_NMPA_GPO3_0_AUX_BIAS_ITRIM_MASK)

#define FLASH_NMPA_GPO3_0_AUX_BIAS_PTAT_ITRIM_MASK (0x7C0U)
#define FLASH_NMPA_GPO3_0_AUX_BIAS_PTAT_ITRIM_SHIFT (6U)
#define FLASH_NMPA_GPO3_0_AUX_BIAS_PTAT_ITRIM(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_GPO3_0_AUX_BIAS_PTAT_ITRIM_SHIFT)) & FLASH_NMPA_GPO3_0_AUX_BIAS_PTAT_ITRIM_MASK)

#define FLASH_NMPA_GPO3_0_AUX_BIAS_VREF1_VTRIM_MASK (0xF800U)
#define FLASH_NMPA_GPO3_0_AUX_BIAS_VREF1_VTRIM_SHIFT (11U)
#define FLASH_NMPA_GPO3_0_AUX_BIAS_VREF1_VTRIM(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_GPO3_0_AUX_BIAS_VREF1_VTRIM_SHIFT)) & FLASH_NMPA_GPO3_0_AUX_BIAS_VREF1_VTRIM_MASK)

#define FLASH_NMPA_GPO3_0_AUX_BIAS_VREF1_VCURVE_TRIM_MASK (0x70000U)
#define FLASH_NMPA_GPO3_0_AUX_BIAS_VREF1_VCURVE_TRIM_SHIFT (16U)
#define FLASH_NMPA_GPO3_0_AUX_BIAS_VREF1_VCURVE_TRIM(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_GPO3_0_AUX_BIAS_VREF1_VCURVE_TRIM_SHIFT)) & FLASH_NMPA_GPO3_0_AUX_BIAS_VREF1_VCURVE_TRIM_MASK)

#define FLASH_NMPA_GPO3_0_FIELD_MASK             (0x1F80000U)
#define FLASH_NMPA_GPO3_0_FIELD_SHIFT            (19U)
#define FLASH_NMPA_GPO3_0_FIELD(x)               (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_GPO3_0_FIELD_SHIFT)) & FLASH_NMPA_GPO3_0_FIELD_MASK)

#define FLASH_NMPA_GPO3_0_MODELNUM_EXTENSION_MASK (0xE000000U)
#define FLASH_NMPA_GPO3_0_MODELNUM_EXTENSION_SHIFT (25U)
/*! MODELNUM_EXTENSION - ModelNumber extension[2:0] */
#define FLASH_NMPA_GPO3_0_MODELNUM_EXTENSION(x)  (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_GPO3_0_MODELNUM_EXTENSION_SHIFT)) & FLASH_NMPA_GPO3_0_MODELNUM_EXTENSION_MASK)

#define FLASH_NMPA_GPO3_0_FINAL_TEST_NOT_DONE_MASK (0xF0000000U)
#define FLASH_NMPA_GPO3_0_FINAL_TEST_NOT_DONE_SHIFT (28U)
/*! FINAL_TEST_NOT_DONE - FINAL_TEST_NOT_DONE[3:0]: 1010 : Final Test Not Done. All Other values: Final Test Done. */
#define FLASH_NMPA_GPO3_0_FINAL_TEST_NOT_DONE(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_GPO3_0_FINAL_TEST_NOT_DONE_SHIFT)) & FLASH_NMPA_GPO3_0_FINAL_TEST_NOT_DONE_MASK)
/*! @} */

/*! @name GPO3_1 - GPO3 register 1 description */
/*! @{ */

#define FLASH_NMPA_GPO3_1_FIELD_MASK             (0xFFFFFFFFU)
#define FLASH_NMPA_GPO3_1_FIELD_SHIFT            (0U)
#define FLASH_NMPA_GPO3_1_FIELD(x)               (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_GPO3_1_FIELD_SHIFT)) & FLASH_NMPA_GPO3_1_FIELD_MASK)
/*! @} */

/*! @name GPO3_2 - GPO3 register 2 description */
/*! @{ */

#define FLASH_NMPA_GPO3_2_FIELD_MASK             (0xFFFFFFFFU)
#define FLASH_NMPA_GPO3_2_FIELD_SHIFT            (0U)
#define FLASH_NMPA_GPO3_2_FIELD(x)               (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_GPO3_2_FIELD_SHIFT)) & FLASH_NMPA_GPO3_2_FIELD_MASK)
/*! @} */

/*! @name GPO3_3 - GPO3 register 3 description */
/*! @{ */

#define FLASH_NMPA_GPO3_3_FIELD_MASK             (0xFFFFFFFFU)
#define FLASH_NMPA_GPO3_3_FIELD_SHIFT            (0U)
#define FLASH_NMPA_GPO3_3_FIELD(x)               (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_GPO3_3_FIELD_SHIFT)) & FLASH_NMPA_GPO3_3_FIELD_MASK)
/*! @} */

/*! @name GPO3_ARRAY - GPO3 array description */
/*! @{ */

#define FLASH_NMPA_GPO3_ARRAY_FIELD_MASK         (0xFFFFFFFFU)
#define FLASH_NMPA_GPO3_ARRAY_FIELD_SHIFT        (0U)
#define FLASH_NMPA_GPO3_ARRAY_FIELD(x)           (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_GPO3_ARRAY_FIELD_SHIFT)) & FLASH_NMPA_GPO3_ARRAY_FIELD_MASK)
/*! @} */

/* The count of FLASH_NMPA_GPO3_ARRAY */
#define FLASH_NMPA_GPO3_ARRAY_COUNT              (4U)

/*! @name GPO_CHECKSUM_0 - checksum of the GPO data in words 0 */
/*! @{ */

#define FLASH_NMPA_GPO_CHECKSUM_0_FIELD_MASK     (0xFFFFFFFFU)
#define FLASH_NMPA_GPO_CHECKSUM_0_FIELD_SHIFT    (0U)
#define FLASH_NMPA_GPO_CHECKSUM_0_FIELD(x)       (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_GPO_CHECKSUM_0_FIELD_SHIFT)) & FLASH_NMPA_GPO_CHECKSUM_0_FIELD_MASK)
/*! @} */

/*! @name GPO_CHECKSUM_1 - checksum of the GPO data in words 1 */
/*! @{ */

#define FLASH_NMPA_GPO_CHECKSUM_1_FIELD_MASK     (0xFFFFFFFFU)
#define FLASH_NMPA_GPO_CHECKSUM_1_FIELD_SHIFT    (0U)
#define FLASH_NMPA_GPO_CHECKSUM_1_FIELD(x)       (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_GPO_CHECKSUM_1_FIELD_SHIFT)) & FLASH_NMPA_GPO_CHECKSUM_1_FIELD_MASK)
/*! @} */

/*! @name GPO_CHECKSUM_2 - checksum of the GPO data in words 2 */
/*! @{ */

#define FLASH_NMPA_GPO_CHECKSUM_2_FIELD_MASK     (0xFFFFFFFFU)
#define FLASH_NMPA_GPO_CHECKSUM_2_FIELD_SHIFT    (0U)
#define FLASH_NMPA_GPO_CHECKSUM_2_FIELD(x)       (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_GPO_CHECKSUM_2_FIELD_SHIFT)) & FLASH_NMPA_GPO_CHECKSUM_2_FIELD_MASK)
/*! @} */

/*! @name GPO_CHECKSUM_3 - checksum of the GPO data in words 3 */
/*! @{ */

#define FLASH_NMPA_GPO_CHECKSUM_3_FIELD_MASK     (0xFFFFFFFFU)
#define FLASH_NMPA_GPO_CHECKSUM_3_FIELD_SHIFT    (0U)
#define FLASH_NMPA_GPO_CHECKSUM_3_FIELD(x)       (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_GPO_CHECKSUM_3_FIELD_SHIFT)) & FLASH_NMPA_GPO_CHECKSUM_3_FIELD_MASK)
/*! @} */

/*! @name GPO_CHECKSUM_ARRAY - checksum of the GPO data in words [3:0] */
/*! @{ */

#define FLASH_NMPA_GPO_CHECKSUM_ARRAY_FIELD_MASK (0xFFFFFFFFU)
#define FLASH_NMPA_GPO_CHECKSUM_ARRAY_FIELD_SHIFT (0U)
#define FLASH_NMPA_GPO_CHECKSUM_ARRAY_FIELD(x)   (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_GPO_CHECKSUM_ARRAY_FIELD_SHIFT)) & FLASH_NMPA_GPO_CHECKSUM_ARRAY_FIELD_MASK)
/*! @} */

/* The count of FLASH_NMPA_GPO_CHECKSUM_ARRAY */
#define FLASH_NMPA_GPO_CHECKSUM_ARRAY_COUNT      (4U)

/*! @name FINAL_TEST_BATCH_ID_0 -  */
/*! @{ */

#define FLASH_NMPA_FINAL_TEST_BATCH_ID_0_FIELD_MASK (0xFFFFFFFFU)
#define FLASH_NMPA_FINAL_TEST_BATCH_ID_0_FIELD_SHIFT (0U)
#define FLASH_NMPA_FINAL_TEST_BATCH_ID_0_FIELD(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_FINAL_TEST_BATCH_ID_0_FIELD_SHIFT)) & FLASH_NMPA_FINAL_TEST_BATCH_ID_0_FIELD_MASK)
/*! @} */

/*! @name FINAL_TEST_BATCH_ID_1 -  */
/*! @{ */

#define FLASH_NMPA_FINAL_TEST_BATCH_ID_1_FIELD_MASK (0xFFFFFFFFU)
#define FLASH_NMPA_FINAL_TEST_BATCH_ID_1_FIELD_SHIFT (0U)
#define FLASH_NMPA_FINAL_TEST_BATCH_ID_1_FIELD(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_FINAL_TEST_BATCH_ID_1_FIELD_SHIFT)) & FLASH_NMPA_FINAL_TEST_BATCH_ID_1_FIELD_MASK)
/*! @} */

/*! @name FINAL_TEST_BATCH_ID_2 -  */
/*! @{ */

#define FLASH_NMPA_FINAL_TEST_BATCH_ID_2_FIELD_MASK (0xFFFFFFFFU)
#define FLASH_NMPA_FINAL_TEST_BATCH_ID_2_FIELD_SHIFT (0U)
#define FLASH_NMPA_FINAL_TEST_BATCH_ID_2_FIELD(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_FINAL_TEST_BATCH_ID_2_FIELD_SHIFT)) & FLASH_NMPA_FINAL_TEST_BATCH_ID_2_FIELD_MASK)
/*! @} */

/*! @name FINAL_TEST_BATCH_ID_3 -  */
/*! @{ */

#define FLASH_NMPA_FINAL_TEST_BATCH_ID_3_FIELD_MASK (0xFFFFFFFFU)
#define FLASH_NMPA_FINAL_TEST_BATCH_ID_3_FIELD_SHIFT (0U)
#define FLASH_NMPA_FINAL_TEST_BATCH_ID_3_FIELD(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_FINAL_TEST_BATCH_ID_3_FIELD_SHIFT)) & FLASH_NMPA_FINAL_TEST_BATCH_ID_3_FIELD_MASK)
/*! @} */

/*! @name FINAL_TEST_BATCH_ID_ARRAY -  */
/*! @{ */

#define FLASH_NMPA_FINAL_TEST_BATCH_ID_ARRAY_FIELD_MASK (0xFFFFFFFFU)
#define FLASH_NMPA_FINAL_TEST_BATCH_ID_ARRAY_FIELD_SHIFT (0U)
#define FLASH_NMPA_FINAL_TEST_BATCH_ID_ARRAY_FIELD(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_FINAL_TEST_BATCH_ID_ARRAY_FIELD_SHIFT)) & FLASH_NMPA_FINAL_TEST_BATCH_ID_ARRAY_FIELD_MASK)
/*! @} */

/* The count of FLASH_NMPA_FINAL_TEST_BATCH_ID_ARRAY */
#define FLASH_NMPA_FINAL_TEST_BATCH_ID_ARRAY_COUNT (4U)

/*! @name DEVICE_TYPE -  */
/*! @{ */

#define FLASH_NMPA_DEVICE_TYPE_DEVICE_TYPE_NUM_MASK (0xFFFFU)
#define FLASH_NMPA_DEVICE_TYPE_DEVICE_TYPE_NUM_SHIFT (0U)
/*! DEVICE_TYPE_NUM - Device type number. (E.g : LPC5569 stored as 5569 decimal) */
#define FLASH_NMPA_DEVICE_TYPE_DEVICE_TYPE_NUM(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_DEVICE_TYPE_DEVICE_TYPE_NUM_SHIFT)) & FLASH_NMPA_DEVICE_TYPE_DEVICE_TYPE_NUM_MASK)

#define FLASH_NMPA_DEVICE_TYPE_DEVICE_TYPE_SEC_MASK (0x10000U)
#define FLASH_NMPA_DEVICE_TYPE_DEVICE_TYPE_SEC_SHIFT (16U)
/*! DEVICE_TYPE_SEC - Security device type: 0: LPC55xxx (Non Secure Familly) 1: LPC55Sxxx (Secure Familly) */
#define FLASH_NMPA_DEVICE_TYPE_DEVICE_TYPE_SEC(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_DEVICE_TYPE_DEVICE_TYPE_SEC_SHIFT)) & FLASH_NMPA_DEVICE_TYPE_DEVICE_TYPE_SEC_MASK)

#define FLASH_NMPA_DEVICE_TYPE_DEVICE_TYPE_PKG_MASK (0xF00000U)
#define FLASH_NMPA_DEVICE_TYPE_DEVICE_TYPE_PKG_SHIFT (20U)
/*! DEVICE_TYPE_PKG - Device package type: 0000 : HLQFP 0001 : HTQFP 0010 : HVQFN 0100 : VFBGA 1000 : WLCSP */
#define FLASH_NMPA_DEVICE_TYPE_DEVICE_TYPE_PKG(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_DEVICE_TYPE_DEVICE_TYPE_PKG_SHIFT)) & FLASH_NMPA_DEVICE_TYPE_DEVICE_TYPE_PKG_MASK)

#define FLASH_NMPA_DEVICE_TYPE_DEVICE_TYPE_PIN_MASK (0xFF000000U)
#define FLASH_NMPA_DEVICE_TYPE_DEVICE_TYPE_PIN_SHIFT (24U)
/*! DEVICE_TYPE_PIN - Number of pins on the package. */
#define FLASH_NMPA_DEVICE_TYPE_DEVICE_TYPE_PIN(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_DEVICE_TYPE_DEVICE_TYPE_PIN_SHIFT)) & FLASH_NMPA_DEVICE_TYPE_DEVICE_TYPE_PIN_MASK)
/*! @} */

/*! @name FINAL_TEST_PROGRAM_VERSION -  */
/*! @{ */

#define FLASH_NMPA_FINAL_TEST_PROGRAM_VERSION_PROGRAM_VERSION_MASK (0xFFFFFFFFU)
#define FLASH_NMPA_FINAL_TEST_PROGRAM_VERSION_PROGRAM_VERSION_SHIFT (0U)
/*! PROGRAM_VERSION - PROGRAM_VERSION [xx.yy stored as : 100*x+y] */
#define FLASH_NMPA_FINAL_TEST_PROGRAM_VERSION_PROGRAM_VERSION(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_FINAL_TEST_PROGRAM_VERSION_PROGRAM_VERSION_SHIFT)) & FLASH_NMPA_FINAL_TEST_PROGRAM_VERSION_PROGRAM_VERSION_MASK)
/*! @} */

/*! @name FINAL_TEST_DATE -  */
/*! @{ */

#define FLASH_NMPA_FINAL_TEST_DATE_DATE_MASK     (0xFFFFFFFFU)
#define FLASH_NMPA_FINAL_TEST_DATE_DATE_SHIFT    (0U)
/*! DATE - DATE [stored as : year*10000+month*100+day] */
#define FLASH_NMPA_FINAL_TEST_DATE_DATE(x)       (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_FINAL_TEST_DATE_DATE_SHIFT)) & FLASH_NMPA_FINAL_TEST_DATE_DATE_MASK)
/*! @} */

/*! @name FINAL_TEST_TIME -  */
/*! @{ */

#define FLASH_NMPA_FINAL_TEST_TIME_TIME_MASK     (0xFFFFFFFFU)
#define FLASH_NMPA_FINAL_TEST_TIME_TIME_SHIFT    (0U)
/*! TIME - TIME [stored as : hour*10000+minute*100+seconde] */
#define FLASH_NMPA_FINAL_TEST_TIME_TIME(x)       (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_FINAL_TEST_TIME_TIME_SHIFT)) & FLASH_NMPA_FINAL_TEST_TIME_TIME_MASK)
/*! @} */

/*! @name UUID_0 -  */
/*! @{ */

#define FLASH_NMPA_UUID_0_FIELD_MASK             (0xFFFFFFFFU)
#define FLASH_NMPA_UUID_0_FIELD_SHIFT            (0U)
#define FLASH_NMPA_UUID_0_FIELD(x)               (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_UUID_0_FIELD_SHIFT)) & FLASH_NMPA_UUID_0_FIELD_MASK)
/*! @} */

/*! @name UUID_1 -  */
/*! @{ */

#define FLASH_NMPA_UUID_1_FIELD_MASK             (0xFFFFFFFFU)
#define FLASH_NMPA_UUID_1_FIELD_SHIFT            (0U)
#define FLASH_NMPA_UUID_1_FIELD(x)               (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_UUID_1_FIELD_SHIFT)) & FLASH_NMPA_UUID_1_FIELD_MASK)
/*! @} */

/*! @name UUID_2 -  */
/*! @{ */

#define FLASH_NMPA_UUID_2_FIELD_MASK             (0xFFFFFFFFU)
#define FLASH_NMPA_UUID_2_FIELD_SHIFT            (0U)
#define FLASH_NMPA_UUID_2_FIELD(x)               (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_UUID_2_FIELD_SHIFT)) & FLASH_NMPA_UUID_2_FIELD_MASK)
/*! @} */

/*! @name UUID_3 -  */
/*! @{ */

#define FLASH_NMPA_UUID_3_FIELD_MASK             (0xFFFFFFFFU)
#define FLASH_NMPA_UUID_3_FIELD_SHIFT            (0U)
#define FLASH_NMPA_UUID_3_FIELD(x)               (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_UUID_3_FIELD_SHIFT)) & FLASH_NMPA_UUID_3_FIELD_MASK)
/*! @} */

/*! @name UUID_ARRAY -  */
/*! @{ */

#define FLASH_NMPA_UUID_ARRAY_FIELD_MASK         (0xFFFFFFFFU)
#define FLASH_NMPA_UUID_ARRAY_FIELD_SHIFT        (0U)
#define FLASH_NMPA_UUID_ARRAY_FIELD(x)           (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_UUID_ARRAY_FIELD_SHIFT)) & FLASH_NMPA_UUID_ARRAY_FIELD_MASK)
/*! @} */

/* The count of FLASH_NMPA_UUID_ARRAY */
#define FLASH_NMPA_UUID_ARRAY_COUNT              (4U)

/*! @name WAFER_TEST1_PROGRAM_VERSION -  */
/*! @{ */

#define FLASH_NMPA_WAFER_TEST1_PROGRAM_VERSION_WT1_PROGRAM_VERSION_MASK (0xFFFFFFFFU)
#define FLASH_NMPA_WAFER_TEST1_PROGRAM_VERSION_WT1_PROGRAM_VERSION_SHIFT (0U)
/*! WT1_PROGRAM_VERSION - WT1_PROGRAM_VERSION [xx.yy stored as : 100*x+y] */
#define FLASH_NMPA_WAFER_TEST1_PROGRAM_VERSION_WT1_PROGRAM_VERSION(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_WAFER_TEST1_PROGRAM_VERSION_WT1_PROGRAM_VERSION_SHIFT)) & FLASH_NMPA_WAFER_TEST1_PROGRAM_VERSION_WT1_PROGRAM_VERSION_MASK)
/*! @} */

/*! @name WAFER_TEST1_DATE -  */
/*! @{ */

#define FLASH_NMPA_WAFER_TEST1_DATE_WT1_DATE_MASK (0xFFFFFFFFU)
#define FLASH_NMPA_WAFER_TEST1_DATE_WT1_DATE_SHIFT (0U)
/*! WT1_DATE - WT1_DATE [stored as : year*10000+month*100+day] */
#define FLASH_NMPA_WAFER_TEST1_DATE_WT1_DATE(x)  (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_WAFER_TEST1_DATE_WT1_DATE_SHIFT)) & FLASH_NMPA_WAFER_TEST1_DATE_WT1_DATE_MASK)
/*! @} */

/*! @name WAFER_TEST1_TIME -  */
/*! @{ */

#define FLASH_NMPA_WAFER_TEST1_TIME_WT1_TIME_MASK (0xFFFFFFFFU)
#define FLASH_NMPA_WAFER_TEST1_TIME_WT1_TIME_SHIFT (0U)
/*! WT1_TIME - WT1_TIME [stored as : hour*10000+minute*100+seconde] */
#define FLASH_NMPA_WAFER_TEST1_TIME_WT1_TIME(x)  (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_WAFER_TEST1_TIME_WT1_TIME_SHIFT)) & FLASH_NMPA_WAFER_TEST1_TIME_WT1_TIME_MASK)
/*! @} */

/*! @name WAFER_TEST2_PROGRAM_VERSION -  */
/*! @{ */

#define FLASH_NMPA_WAFER_TEST2_PROGRAM_VERSION_WT2_PROGRAM_VERSION_MASK (0xFFFFFFFFU)
#define FLASH_NMPA_WAFER_TEST2_PROGRAM_VERSION_WT2_PROGRAM_VERSION_SHIFT (0U)
/*! WT2_PROGRAM_VERSION - WT2_PROGRAM_VERSION [xx.yy stored as : 100*x+y] */
#define FLASH_NMPA_WAFER_TEST2_PROGRAM_VERSION_WT2_PROGRAM_VERSION(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_WAFER_TEST2_PROGRAM_VERSION_WT2_PROGRAM_VERSION_SHIFT)) & FLASH_NMPA_WAFER_TEST2_PROGRAM_VERSION_WT2_PROGRAM_VERSION_MASK)
/*! @} */

/*! @name WAFER_TEST2_DATE -  */
/*! @{ */

#define FLASH_NMPA_WAFER_TEST2_DATE_WT2_DATE_MASK (0xFFFFFFFFU)
#define FLASH_NMPA_WAFER_TEST2_DATE_WT2_DATE_SHIFT (0U)
/*! WT2_DATE - WT2_DATE [stored as : year*10000+month*100+day] */
#define FLASH_NMPA_WAFER_TEST2_DATE_WT2_DATE(x)  (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_WAFER_TEST2_DATE_WT2_DATE_SHIFT)) & FLASH_NMPA_WAFER_TEST2_DATE_WT2_DATE_MASK)
/*! @} */

/*! @name WAFER_TEST2_TIME -  */
/*! @{ */

#define FLASH_NMPA_WAFER_TEST2_TIME_WT2_TIME_MASK (0xFFFFFFFFU)
#define FLASH_NMPA_WAFER_TEST2_TIME_WT2_TIME_SHIFT (0U)
/*! WT2_TIME - WT2_TIME [stored as : hour*10000+minute*100+seconde] */
#define FLASH_NMPA_WAFER_TEST2_TIME_WT2_TIME(x)  (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_WAFER_TEST2_TIME_WT2_TIME_SHIFT)) & FLASH_NMPA_WAFER_TEST2_TIME_WT2_TIME_MASK)
/*! @} */

/*! @name USBCFG -  */
/*! @{ */

#define FLASH_NMPA_USBCFG_XO32M_READY_TIME_OUT_MS_MASK (0xFFU)
#define FLASH_NMPA_USBCFG_XO32M_READY_TIME_OUT_MS_SHIFT (0U)
#define FLASH_NMPA_USBCFG_XO32M_READY_TIME_OUT_MS(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_USBCFG_XO32M_READY_TIME_OUT_MS_SHIFT)) & FLASH_NMPA_USBCFG_XO32M_READY_TIME_OUT_MS_MASK)

#define FLASH_NMPA_USBCFG_USB_SPEED_MASK         (0xFF00U)
#define FLASH_NMPA_USBCFG_USB_SPEED_SHIFT        (8U)
/*! USB_SPEED - USB_SPEED[7:0]= 0x00 : USB High Speed Module used for ISP 0x01 : USB Full SPeed
 *    Module used for ISP 0x02 : Neither USB High Speed module nor USB Full Speed module used for ISP
 *    0x03 - 0xFF : RESERVED
 */
#define FLASH_NMPA_USBCFG_USB_SPEED(x)           (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_USBCFG_USB_SPEED_SHIFT)) & FLASH_NMPA_USBCFG_USB_SPEED_MASK)

#define FLASH_NMPA_USBCFG_USB_USE_XO32M_CAPA_BANKS_MASK (0x10000U)
#define FLASH_NMPA_USBCFG_USB_USE_XO32M_CAPA_BANKS_SHIFT (16U)
/*! USB_USE_XO32M_CAPA_BANKS - Enable the use of Crystal 32 MHz internal Capa Banks during the
 *    configuration of the High Speed USB for ISP: 0: Disable Crystal 32 MHz CapaBanks. 1: Enable Crystal
 *    32 MHz CapaBanks.
 */
#define FLASH_NMPA_USBCFG_USB_USE_XO32M_CAPA_BANKS(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_USBCFG_USB_USE_XO32M_CAPA_BANKS_SHIFT)) & FLASH_NMPA_USBCFG_USB_USE_XO32M_CAPA_BANKS_MASK)
/*! @} */

/*! @name PERIPHENCFG -  */
/*! @{ */

#define FLASH_NMPA_PERIPHENCFG_PERIPHERAL_CONFIGURATION_MASK (0xFFFFU)
#define FLASH_NMPA_PERIPHENCFG_PERIPHERAL_CONFIGURATION_SHIFT (0U)
#define FLASH_NMPA_PERIPHENCFG_PERIPHERAL_CONFIGURATION(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_PERIPHENCFG_PERIPHERAL_CONFIGURATION_SHIFT)) & FLASH_NMPA_PERIPHENCFG_PERIPHERAL_CONFIGURATION_MASK)

#define FLASH_NMPA_PERIPHENCFG_CPU1_ENABLE_MASK  (0x80000000U)
#define FLASH_NMPA_PERIPHENCFG_CPU1_ENABLE_SHIFT (31U)
#define FLASH_NMPA_PERIPHENCFG_CPU1_ENABLE(x)    (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_PERIPHENCFG_CPU1_ENABLE_SHIFT)) & FLASH_NMPA_PERIPHENCFG_CPU1_ENABLE_MASK)
/*! @} */

/*! @name RAMSIZECFG -  */
/*! @{ */

#define FLASH_NMPA_RAMSIZECFG_SRAM_CONFIGURATION_MASK (0xFFFFFFFFU)
#define FLASH_NMPA_RAMSIZECFG_SRAM_CONFIGURATION_SHIFT (0U)
#define FLASH_NMPA_RAMSIZECFG_SRAM_CONFIGURATION(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_RAMSIZECFG_SRAM_CONFIGURATION_SHIFT)) & FLASH_NMPA_RAMSIZECFG_SRAM_CONFIGURATION_MASK)
/*! @} */

/*! @name FLASHSIZECFG -  */
/*! @{ */

#define FLASH_NMPA_FLASHSIZECFG_FLASH_CONFIGURATION_MASK (0xFFFFFFFFU)
#define FLASH_NMPA_FLASHSIZECFG_FLASH_CONFIGURATION_SHIFT (0U)
#define FLASH_NMPA_FLASHSIZECFG_FLASH_CONFIGURATION(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_FLASHSIZECFG_FLASH_CONFIGURATION_SHIFT)) & FLASH_NMPA_FLASHSIZECFG_FLASH_CONFIGURATION_MASK)
/*! @} */

/*! @name RINGO_0 -  */
/*! @{ */

#define FLASH_NMPA_RINGO_0_RINGO_0_CTRL_VALID_MASK (0x1U)
#define FLASH_NMPA_RINGO_0_RINGO_0_CTRL_VALID_SHIFT (0U)
/*! RINGO_0_CTRL_VALID - 1: RINGO_0_CTRL is valid. */
#define FLASH_NMPA_RINGO_0_RINGO_0_CTRL_VALID(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_RINGO_0_RINGO_0_CTRL_VALID_SHIFT)) & FLASH_NMPA_RINGO_0_RINGO_0_CTRL_VALID_MASK)

#define FLASH_NMPA_RINGO_0_RINGO_0_CTRL_MASK     (0xFFFFFFFEU)
#define FLASH_NMPA_RINGO_0_RINGO_0_CTRL_SHIFT    (1U)
/*! RINGO_0_CTRL - To copy RINGO_0_CTRL = ANACTRL->RINGO0_CTRL[30:0] */
#define FLASH_NMPA_RINGO_0_RINGO_0_CTRL(x)       (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_RINGO_0_RINGO_0_CTRL_SHIFT)) & FLASH_NMPA_RINGO_0_RINGO_0_CTRL_MASK)
/*! @} */

/*! @name RINGO_1 -  */
/*! @{ */

#define FLASH_NMPA_RINGO_1_RINGO_1_CTRL_VALID_MASK (0x1U)
#define FLASH_NMPA_RINGO_1_RINGO_1_CTRL_VALID_SHIFT (0U)
/*! RINGO_1_CTRL_VALID - 1: RINGO_1_CTRL is valid. */
#define FLASH_NMPA_RINGO_1_RINGO_1_CTRL_VALID(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_RINGO_1_RINGO_1_CTRL_VALID_SHIFT)) & FLASH_NMPA_RINGO_1_RINGO_1_CTRL_VALID_MASK)

#define FLASH_NMPA_RINGO_1_RINGO_1_CTRL_MASK     (0xFFFFFFFEU)
#define FLASH_NMPA_RINGO_1_RINGO_1_CTRL_SHIFT    (1U)
/*! RINGO_1_CTRL - To copy RINGO_1_CTRL = ANACTRL->RINGO1_CTRL[30:0] */
#define FLASH_NMPA_RINGO_1_RINGO_1_CTRL(x)       (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_RINGO_1_RINGO_1_CTRL_SHIFT)) & FLASH_NMPA_RINGO_1_RINGO_1_CTRL_MASK)
/*! @} */

/*! @name RINGO_2 -  */
/*! @{ */

#define FLASH_NMPA_RINGO_2_RINGO_2_CTRL_VALID_MASK (0x1U)
#define FLASH_NMPA_RINGO_2_RINGO_2_CTRL_VALID_SHIFT (0U)
/*! RINGO_2_CTRL_VALID - 1: RINGO_2_CTRL is valid. */
#define FLASH_NMPA_RINGO_2_RINGO_2_CTRL_VALID(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_RINGO_2_RINGO_2_CTRL_VALID_SHIFT)) & FLASH_NMPA_RINGO_2_RINGO_2_CTRL_VALID_MASK)

#define FLASH_NMPA_RINGO_2_RINGO_2_CTRL_MASK     (0xFFFFFFFEU)
#define FLASH_NMPA_RINGO_2_RINGO_2_CTRL_SHIFT    (1U)
/*! RINGO_2_CTRL - To copy RINGO_2_CTRL = ANACTRL->RINGO2_CTRL[30:0] */
#define FLASH_NMPA_RINGO_2_RINGO_2_CTRL(x)       (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_RINGO_2_RINGO_2_CTRL_SHIFT)) & FLASH_NMPA_RINGO_2_RINGO_2_CTRL_MASK)
/*! @} */

/*! @name FRO_192MHZ -  */
/*! @{ */

#define FLASH_NMPA_FRO_192MHZ_FRO192M_TRIM_VALID_MASK (0x1U)
#define FLASH_NMPA_FRO_192MHZ_FRO192M_TRIM_VALID_SHIFT (0U)
#define FLASH_NMPA_FRO_192MHZ_FRO192M_TRIM_VALID(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_FRO_192MHZ_FRO192M_TRIM_VALID_SHIFT)) & FLASH_NMPA_FRO_192MHZ_FRO192M_TRIM_VALID_MASK)

#define FLASH_NMPA_FRO_192MHZ_FRO192M_BIASTRIM_MASK (0x7EU)
#define FLASH_NMPA_FRO_192MHZ_FRO192M_BIASTRIM_SHIFT (1U)
/*! FRO192M_BIASTRIM - FRO192M_BIASTRIM[5:0]. */
#define FLASH_NMPA_FRO_192MHZ_FRO192M_BIASTRIM(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_FRO_192MHZ_FRO192M_BIASTRIM_SHIFT)) & FLASH_NMPA_FRO_192MHZ_FRO192M_BIASTRIM_MASK)

#define FLASH_NMPA_FRO_192MHZ_FRO192M_TEMPTRIM_MASK (0x7F00U)
#define FLASH_NMPA_FRO_192MHZ_FRO192M_TEMPTRIM_SHIFT (8U)
/*! FRO192M_TEMPTRIM - FRO192M_TEMPTRIM[6:0]. */
#define FLASH_NMPA_FRO_192MHZ_FRO192M_TEMPTRIM(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_FRO_192MHZ_FRO192M_TEMPTRIM_SHIFT)) & FLASH_NMPA_FRO_192MHZ_FRO192M_TEMPTRIM_MASK)

#define FLASH_NMPA_FRO_192MHZ_FRO192M_DACTRIM_MASK (0x1FE0000U)
#define FLASH_NMPA_FRO_192MHZ_FRO192M_DACTRIM_SHIFT (17U)
/*! FRO192M_DACTRIM - FRO192M_DACTRIM[7:0]. */
#define FLASH_NMPA_FRO_192MHZ_FRO192M_DACTRIM(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_FRO_192MHZ_FRO192M_DACTRIM_SHIFT)) & FLASH_NMPA_FRO_192MHZ_FRO192M_DACTRIM_MASK)
/*! @} */

/*! @name XO_32MHZ -  */
/*! @{ */

#define FLASH_NMPA_XO_32MHZ_XO32M_XIN_TRIM_VALID_MASK (0x1U)
#define FLASH_NMPA_XO_32MHZ_XO32M_XIN_TRIM_VALID_SHIFT (0U)
#define FLASH_NMPA_XO_32MHZ_XO32M_XIN_TRIM_VALID(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_XO_32MHZ_XO32M_XIN_TRIM_VALID_SHIFT)) & FLASH_NMPA_XO_32MHZ_XO32M_XIN_TRIM_VALID_MASK)

#define FLASH_NMPA_XO_32MHZ_XO32M_XIN_CAPCAL_6PF_MASK (0xFEU)
#define FLASH_NMPA_XO_32MHZ_XO32M_XIN_CAPCAL_6PF_SHIFT (1U)
#define FLASH_NMPA_XO_32MHZ_XO32M_XIN_CAPCAL_6PF(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_XO_32MHZ_XO32M_XIN_CAPCAL_6PF_SHIFT)) & FLASH_NMPA_XO_32MHZ_XO32M_XIN_CAPCAL_6PF_MASK)

#define FLASH_NMPA_XO_32MHZ_XO32M_XIN_CAPCAL_8PF_MASK (0x7F00U)
#define FLASH_NMPA_XO_32MHZ_XO32M_XIN_CAPCAL_8PF_SHIFT (8U)
#define FLASH_NMPA_XO_32MHZ_XO32M_XIN_CAPCAL_8PF(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_XO_32MHZ_XO32M_XIN_CAPCAL_8PF_SHIFT)) & FLASH_NMPA_XO_32MHZ_XO32M_XIN_CAPCAL_8PF_MASK)

#define FLASH_NMPA_XO_32MHZ_XO32M_XOUT_TRIM_VALID_MASK (0x8000U)
#define FLASH_NMPA_XO_32MHZ_XO32M_XOUT_TRIM_VALID_SHIFT (15U)
#define FLASH_NMPA_XO_32MHZ_XO32M_XOUT_TRIM_VALID(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_XO_32MHZ_XO32M_XOUT_TRIM_VALID_SHIFT)) & FLASH_NMPA_XO_32MHZ_XO32M_XOUT_TRIM_VALID_MASK)

#define FLASH_NMPA_XO_32MHZ_XO32M_XOUT_CAPCAL_6PF_MASK (0x7F0000U)
#define FLASH_NMPA_XO_32MHZ_XO32M_XOUT_CAPCAL_6PF_SHIFT (16U)
#define FLASH_NMPA_XO_32MHZ_XO32M_XOUT_CAPCAL_6PF(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_XO_32MHZ_XO32M_XOUT_CAPCAL_6PF_SHIFT)) & FLASH_NMPA_XO_32MHZ_XO32M_XOUT_CAPCAL_6PF_MASK)

#define FLASH_NMPA_XO_32MHZ_XO32M_XOUT_CAPCAL_8PF_MASK (0x3F800000U)
#define FLASH_NMPA_XO_32MHZ_XO32M_XOUT_CAPCAL_8PF_SHIFT (23U)
#define FLASH_NMPA_XO_32MHZ_XO32M_XOUT_CAPCAL_8PF(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_XO_32MHZ_XO32M_XOUT_CAPCAL_8PF_SHIFT)) & FLASH_NMPA_XO_32MHZ_XO32M_XOUT_CAPCAL_8PF_MASK)

#define FLASH_NMPA_XO_32MHZ_XO32M_XO_SLAVE_STATUS_MASK (0x40000000U)
#define FLASH_NMPA_XO_32MHZ_XO32M_XO_SLAVE_STATUS_SHIFT (30U)
#define FLASH_NMPA_XO_32MHZ_XO32M_XO_SLAVE_STATUS(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_XO_32MHZ_XO32M_XO_SLAVE_STATUS_SHIFT)) & FLASH_NMPA_XO_32MHZ_XO32M_XO_SLAVE_STATUS_MASK)

#define FLASH_NMPA_XO_32MHZ_XO32M_XO_AC_BUF_STATUS_MASK (0x80000000U)
#define FLASH_NMPA_XO_32MHZ_XO32M_XO_AC_BUF_STATUS_SHIFT (31U)
#define FLASH_NMPA_XO_32MHZ_XO32M_XO_AC_BUF_STATUS(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_XO_32MHZ_XO32M_XO_AC_BUF_STATUS_SHIFT)) & FLASH_NMPA_XO_32MHZ_XO32M_XO_AC_BUF_STATUS_MASK)
/*! @} */

/*! @name XO_32KHZ -  */
/*! @{ */

#define FLASH_NMPA_XO_32KHZ_XO32K_XIN_TRIM_VALID_MASK (0x1U)
#define FLASH_NMPA_XO_32KHZ_XO32K_XIN_TRIM_VALID_SHIFT (0U)
#define FLASH_NMPA_XO_32KHZ_XO32K_XIN_TRIM_VALID(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_XO_32KHZ_XO32K_XIN_TRIM_VALID_SHIFT)) & FLASH_NMPA_XO_32KHZ_XO32K_XIN_TRIM_VALID_MASK)

#define FLASH_NMPA_XO_32KHZ_XO32K_XIN_CAPCAL_6PF_MASK (0xFEU)
#define FLASH_NMPA_XO_32KHZ_XO32K_XIN_CAPCAL_6PF_SHIFT (1U)
#define FLASH_NMPA_XO_32KHZ_XO32K_XIN_CAPCAL_6PF(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_XO_32KHZ_XO32K_XIN_CAPCAL_6PF_SHIFT)) & FLASH_NMPA_XO_32KHZ_XO32K_XIN_CAPCAL_6PF_MASK)

#define FLASH_NMPA_XO_32KHZ_XO32K_XIN_CAPCAL_8PF_MASK (0x7F00U)
#define FLASH_NMPA_XO_32KHZ_XO32K_XIN_CAPCAL_8PF_SHIFT (8U)
#define FLASH_NMPA_XO_32KHZ_XO32K_XIN_CAPCAL_8PF(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_XO_32KHZ_XO32K_XIN_CAPCAL_8PF_SHIFT)) & FLASH_NMPA_XO_32KHZ_XO32K_XIN_CAPCAL_8PF_MASK)

#define FLASH_NMPA_XO_32KHZ_XO32K_XOUT_TRIM_VALID_MASK (0x8000U)
#define FLASH_NMPA_XO_32KHZ_XO32K_XOUT_TRIM_VALID_SHIFT (15U)
#define FLASH_NMPA_XO_32KHZ_XO32K_XOUT_TRIM_VALID(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_XO_32KHZ_XO32K_XOUT_TRIM_VALID_SHIFT)) & FLASH_NMPA_XO_32KHZ_XO32K_XOUT_TRIM_VALID_MASK)

#define FLASH_NMPA_XO_32KHZ_XO32K_XOUT_CAPCAL_6PF_MASK (0x7F0000U)
#define FLASH_NMPA_XO_32KHZ_XO32K_XOUT_CAPCAL_6PF_SHIFT (16U)
#define FLASH_NMPA_XO_32KHZ_XO32K_XOUT_CAPCAL_6PF(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_XO_32KHZ_XO32K_XOUT_CAPCAL_6PF_SHIFT)) & FLASH_NMPA_XO_32KHZ_XO32K_XOUT_CAPCAL_6PF_MASK)

#define FLASH_NMPA_XO_32KHZ_XO32K_XOUT_CAPCAL_8PF_MASK (0x3F800000U)
#define FLASH_NMPA_XO_32KHZ_XO32K_XOUT_CAPCAL_8PF_SHIFT (23U)
#define FLASH_NMPA_XO_32KHZ_XO32K_XOUT_CAPCAL_8PF(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_XO_32KHZ_XO32K_XOUT_CAPCAL_8PF_SHIFT)) & FLASH_NMPA_XO_32KHZ_XO32K_XOUT_CAPCAL_8PF_MASK)
/*! @} */

/*! @name FRO_1MHZ -  */
/*! @{ */

#define FLASH_NMPA_FRO_1MHZ_FRO1M_TRIM_VALID_MASK (0x1U)
#define FLASH_NMPA_FRO_1MHZ_FRO1M_TRIM_VALID_SHIFT (0U)
#define FLASH_NMPA_FRO_1MHZ_FRO1M_TRIM_VALID(x)  (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_FRO_1MHZ_FRO1M_TRIM_VALID_SHIFT)) & FLASH_NMPA_FRO_1MHZ_FRO1M_TRIM_VALID_MASK)

#define FLASH_NMPA_FRO_1MHZ_FRO1M_FREQSEL_MASK   (0xFEU)
#define FLASH_NMPA_FRO_1MHZ_FRO1M_FREQSEL_SHIFT  (1U)
/*! FRO1M_FREQSEL - Frequency trimming bits. */
#define FLASH_NMPA_FRO_1MHZ_FRO1M_FREQSEL(x)     (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_FRO_1MHZ_FRO1M_FREQSEL_SHIFT)) & FLASH_NMPA_FRO_1MHZ_FRO1M_FREQSEL_MASK)
/*! @} */

/*! @name DCDC_POWER_PROFILE_HIGH_0 -  */
/*! @{ */

#define FLASH_NMPA_DCDC_POWER_PROFILE_HIGH_0_DCDC_TRIM_VALID_MASK (0x1U)
#define FLASH_NMPA_DCDC_POWER_PROFILE_HIGH_0_DCDC_TRIM_VALID_SHIFT (0U)
/*! DCDC_TRIM_VALID - DCDC is trimed. */
#define FLASH_NMPA_DCDC_POWER_PROFILE_HIGH_0_DCDC_TRIM_VALID(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_DCDC_POWER_PROFILE_HIGH_0_DCDC_TRIM_VALID_SHIFT)) & FLASH_NMPA_DCDC_POWER_PROFILE_HIGH_0_DCDC_TRIM_VALID_MASK)

#define FLASH_NMPA_DCDC_POWER_PROFILE_HIGH_0_RC_MASK (0x7EU)
#define FLASH_NMPA_DCDC_POWER_PROFILE_HIGH_0_RC_SHIFT (1U)
/*! RC - Constant On-Time calibration. */
#define FLASH_NMPA_DCDC_POWER_PROFILE_HIGH_0_RC(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_DCDC_POWER_PROFILE_HIGH_0_RC_SHIFT)) & FLASH_NMPA_DCDC_POWER_PROFILE_HIGH_0_RC_MASK)

#define FLASH_NMPA_DCDC_POWER_PROFILE_HIGH_0_ICOMP_MASK (0x180U)
#define FLASH_NMPA_DCDC_POWER_PROFILE_HIGH_0_ICOMP_SHIFT (7U)
/*! ICOMP - Select the type of ZCD comparator. */
#define FLASH_NMPA_DCDC_POWER_PROFILE_HIGH_0_ICOMP(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_DCDC_POWER_PROFILE_HIGH_0_ICOMP_SHIFT)) & FLASH_NMPA_DCDC_POWER_PROFILE_HIGH_0_ICOMP_MASK)

#define FLASH_NMPA_DCDC_POWER_PROFILE_HIGH_0_ISEL_MASK (0x600U)
#define FLASH_NMPA_DCDC_POWER_PROFILE_HIGH_0_ISEL_SHIFT (9U)
/*! ISEL - Alter Internal biasing currents. */
#define FLASH_NMPA_DCDC_POWER_PROFILE_HIGH_0_ISEL(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_DCDC_POWER_PROFILE_HIGH_0_ISEL_SHIFT)) & FLASH_NMPA_DCDC_POWER_PROFILE_HIGH_0_ISEL_MASK)

#define FLASH_NMPA_DCDC_POWER_PROFILE_HIGH_0_ICENABLE_MASK (0x800U)
#define FLASH_NMPA_DCDC_POWER_PROFILE_HIGH_0_ICENABLE_SHIFT (11U)
/*! ICENABLE - Selection of auto scaling of COT period with variations in VDD. */
#define FLASH_NMPA_DCDC_POWER_PROFILE_HIGH_0_ICENABLE(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_DCDC_POWER_PROFILE_HIGH_0_ICENABLE_SHIFT)) & FLASH_NMPA_DCDC_POWER_PROFILE_HIGH_0_ICENABLE_MASK)

#define FLASH_NMPA_DCDC_POWER_PROFILE_HIGH_0_TMOS_MASK (0x1F000U)
#define FLASH_NMPA_DCDC_POWER_PROFILE_HIGH_0_TMOS_SHIFT (12U)
/*! TMOS - One-shot generator reference current trimming signal. */
#define FLASH_NMPA_DCDC_POWER_PROFILE_HIGH_0_TMOS(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_DCDC_POWER_PROFILE_HIGH_0_TMOS_SHIFT)) & FLASH_NMPA_DCDC_POWER_PROFILE_HIGH_0_TMOS_MASK)

#define FLASH_NMPA_DCDC_POWER_PROFILE_HIGH_0_DISABLEISENSE_MASK (0x20000U)
#define FLASH_NMPA_DCDC_POWER_PROFILE_HIGH_0_DISABLEISENSE_SHIFT (17U)
/*! DISABLEISENSE - Disable Current sensing. */
#define FLASH_NMPA_DCDC_POWER_PROFILE_HIGH_0_DISABLEISENSE(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_DCDC_POWER_PROFILE_HIGH_0_DISABLEISENSE_SHIFT)) & FLASH_NMPA_DCDC_POWER_PROFILE_HIGH_0_DISABLEISENSE_MASK)

#define FLASH_NMPA_DCDC_POWER_PROFILE_HIGH_0_VOUT_MASK (0x3C0000U)
#define FLASH_NMPA_DCDC_POWER_PROFILE_HIGH_0_VOUT_SHIFT (18U)
/*! VOUT - Set output regulation voltage. */
#define FLASH_NMPA_DCDC_POWER_PROFILE_HIGH_0_VOUT(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_DCDC_POWER_PROFILE_HIGH_0_VOUT_SHIFT)) & FLASH_NMPA_DCDC_POWER_PROFILE_HIGH_0_VOUT_MASK)

#define FLASH_NMPA_DCDC_POWER_PROFILE_HIGH_0_SLICINGENABLE_MASK (0x400000U)
#define FLASH_NMPA_DCDC_POWER_PROFILE_HIGH_0_SLICINGENABLE_SHIFT (22U)
/*! SLICINGENABLE - Enable staggered switching of power switches. */
#define FLASH_NMPA_DCDC_POWER_PROFILE_HIGH_0_SLICINGENABLE(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_DCDC_POWER_PROFILE_HIGH_0_SLICINGENABLE_SHIFT)) & FLASH_NMPA_DCDC_POWER_PROFILE_HIGH_0_SLICINGENABLE_MASK)

#define FLASH_NMPA_DCDC_POWER_PROFILE_HIGH_0_INDUCTORCLAMPENABLE_MASK (0x800000U)
#define FLASH_NMPA_DCDC_POWER_PROFILE_HIGH_0_INDUCTORCLAMPENABLE_SHIFT (23U)
/*! INDUCTORCLAMPENABLE - Enable shorting of Inductor during PFM idle time. */
#define FLASH_NMPA_DCDC_POWER_PROFILE_HIGH_0_INDUCTORCLAMPENABLE(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_DCDC_POWER_PROFILE_HIGH_0_INDUCTORCLAMPENABLE_SHIFT)) & FLASH_NMPA_DCDC_POWER_PROFILE_HIGH_0_INDUCTORCLAMPENABLE_MASK)

#define FLASH_NMPA_DCDC_POWER_PROFILE_HIGH_0_VOUT_PWD_MASK (0xF000000U)
#define FLASH_NMPA_DCDC_POWER_PROFILE_HIGH_0_VOUT_PWD_SHIFT (24U)
/*! VOUT_PWD - Set output regulation voltage during Deep Sleep. */
#define FLASH_NMPA_DCDC_POWER_PROFILE_HIGH_0_VOUT_PWD(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_DCDC_POWER_PROFILE_HIGH_0_VOUT_PWD_SHIFT)) & FLASH_NMPA_DCDC_POWER_PROFILE_HIGH_0_VOUT_PWD_MASK)
/*! @} */

/*! @name DCDC_POWER_PROFILE_HIGH_1 -  */
/*! @{ */

#define FLASH_NMPA_DCDC_POWER_PROFILE_HIGH_1_RTRIMOFFET_MASK (0xFU)
#define FLASH_NMPA_DCDC_POWER_PROFILE_HIGH_1_RTRIMOFFET_SHIFT (0U)
/*! RTRIMOFFET - Adjust the offset voltage of BJT based comparator. */
#define FLASH_NMPA_DCDC_POWER_PROFILE_HIGH_1_RTRIMOFFET(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_DCDC_POWER_PROFILE_HIGH_1_RTRIMOFFET_SHIFT)) & FLASH_NMPA_DCDC_POWER_PROFILE_HIGH_1_RTRIMOFFET_MASK)

#define FLASH_NMPA_DCDC_POWER_PROFILE_HIGH_1_RSENSETRIM_MASK (0xF0U)
#define FLASH_NMPA_DCDC_POWER_PROFILE_HIGH_1_RSENSETRIM_SHIFT (4U)
/*! RSENSETRIM - Adjust Max inductor peak current limiting. */
#define FLASH_NMPA_DCDC_POWER_PROFILE_HIGH_1_RSENSETRIM(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_DCDC_POWER_PROFILE_HIGH_1_RSENSETRIM_SHIFT)) & FLASH_NMPA_DCDC_POWER_PROFILE_HIGH_1_RSENSETRIM_MASK)

#define FLASH_NMPA_DCDC_POWER_PROFILE_HIGH_1_DTESTENABLE_MASK (0x100U)
#define FLASH_NMPA_DCDC_POWER_PROFILE_HIGH_1_DTESTENABLE_SHIFT (8U)
/*! DTESTENABLE - Enable Digital test signals. */
#define FLASH_NMPA_DCDC_POWER_PROFILE_HIGH_1_DTESTENABLE(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_DCDC_POWER_PROFILE_HIGH_1_DTESTENABLE_SHIFT)) & FLASH_NMPA_DCDC_POWER_PROFILE_HIGH_1_DTESTENABLE_MASK)

#define FLASH_NMPA_DCDC_POWER_PROFILE_HIGH_1_SETCURVE_MASK (0x600U)
#define FLASH_NMPA_DCDC_POWER_PROFILE_HIGH_1_SETCURVE_SHIFT (9U)
/*! SETCURVE - Bandgap calibration parameter. */
#define FLASH_NMPA_DCDC_POWER_PROFILE_HIGH_1_SETCURVE(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_DCDC_POWER_PROFILE_HIGH_1_SETCURVE_SHIFT)) & FLASH_NMPA_DCDC_POWER_PROFILE_HIGH_1_SETCURVE_MASK)

#define FLASH_NMPA_DCDC_POWER_PROFILE_HIGH_1_SETDC_MASK (0x7800U)
#define FLASH_NMPA_DCDC_POWER_PROFILE_HIGH_1_SETDC_SHIFT (11U)
/*! SETDC - Bandgap calibration parameter. */
#define FLASH_NMPA_DCDC_POWER_PROFILE_HIGH_1_SETDC(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_DCDC_POWER_PROFILE_HIGH_1_SETDC_SHIFT)) & FLASH_NMPA_DCDC_POWER_PROFILE_HIGH_1_SETDC_MASK)

#define FLASH_NMPA_DCDC_POWER_PROFILE_HIGH_1_DTESTSEL_MASK (0x38000U)
#define FLASH_NMPA_DCDC_POWER_PROFILE_HIGH_1_DTESTSEL_SHIFT (15U)
/*! DTESTSEL - Select the output signal for test. */
#define FLASH_NMPA_DCDC_POWER_PROFILE_HIGH_1_DTESTSEL(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_DCDC_POWER_PROFILE_HIGH_1_DTESTSEL_SHIFT)) & FLASH_NMPA_DCDC_POWER_PROFILE_HIGH_1_DTESTSEL_MASK)

#define FLASH_NMPA_DCDC_POWER_PROFILE_HIGH_1_ISCALEENABLE_MASK (0x40000U)
#define FLASH_NMPA_DCDC_POWER_PROFILE_HIGH_1_ISCALEENABLE_SHIFT (18U)
/*! ISCALEENABLE - Modify COT behavior. */
#define FLASH_NMPA_DCDC_POWER_PROFILE_HIGH_1_ISCALEENABLE(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_DCDC_POWER_PROFILE_HIGH_1_ISCALEENABLE_SHIFT)) & FLASH_NMPA_DCDC_POWER_PROFILE_HIGH_1_ISCALEENABLE_MASK)

#define FLASH_NMPA_DCDC_POWER_PROFILE_HIGH_1_FORCEBYPASS_MASK (0x80000U)
#define FLASH_NMPA_DCDC_POWER_PROFILE_HIGH_1_FORCEBYPASS_SHIFT (19U)
/*! FORCEBYPASS - Force bypass mode. */
#define FLASH_NMPA_DCDC_POWER_PROFILE_HIGH_1_FORCEBYPASS(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_DCDC_POWER_PROFILE_HIGH_1_FORCEBYPASS_SHIFT)) & FLASH_NMPA_DCDC_POWER_PROFILE_HIGH_1_FORCEBYPASS_MASK)

#define FLASH_NMPA_DCDC_POWER_PROFILE_HIGH_1_TRIMAUTOCOT_MASK (0xF00000U)
#define FLASH_NMPA_DCDC_POWER_PROFILE_HIGH_1_TRIMAUTOCOT_SHIFT (20U)
/*! TRIMAUTOCOT - Change the scaling ratio of the feedforward compensation. */
#define FLASH_NMPA_DCDC_POWER_PROFILE_HIGH_1_TRIMAUTOCOT(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_DCDC_POWER_PROFILE_HIGH_1_TRIMAUTOCOT_SHIFT)) & FLASH_NMPA_DCDC_POWER_PROFILE_HIGH_1_TRIMAUTOCOT_MASK)

#define FLASH_NMPA_DCDC_POWER_PROFILE_HIGH_1_FORCEFULLCYCLE_MASK (0x1000000U)
#define FLASH_NMPA_DCDC_POWER_PROFILE_HIGH_1_FORCEFULLCYCLE_SHIFT (24U)
/*! FORCEFULLCYCLE - Force full PFM PMOS and NMOS cycle. */
#define FLASH_NMPA_DCDC_POWER_PROFILE_HIGH_1_FORCEFULLCYCLE(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_DCDC_POWER_PROFILE_HIGH_1_FORCEFULLCYCLE_SHIFT)) & FLASH_NMPA_DCDC_POWER_PROFILE_HIGH_1_FORCEFULLCYCLE_MASK)

#define FLASH_NMPA_DCDC_POWER_PROFILE_HIGH_1_LCENABLE_MASK (0x2000000U)
#define FLASH_NMPA_DCDC_POWER_PROFILE_HIGH_1_LCENABLE_SHIFT (25U)
/*! LCENABLE - Change the range of the peak detector of current inside the inductor. */
#define FLASH_NMPA_DCDC_POWER_PROFILE_HIGH_1_LCENABLE(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_DCDC_POWER_PROFILE_HIGH_1_LCENABLE_SHIFT)) & FLASH_NMPA_DCDC_POWER_PROFILE_HIGH_1_LCENABLE_MASK)

#define FLASH_NMPA_DCDC_POWER_PROFILE_HIGH_1_TOFF_MASK (0x7C000000U)
#define FLASH_NMPA_DCDC_POWER_PROFILE_HIGH_1_TOFF_SHIFT (26U)
/*! TOFF - Constant Off-Time calibration input. */
#define FLASH_NMPA_DCDC_POWER_PROFILE_HIGH_1_TOFF(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_DCDC_POWER_PROFILE_HIGH_1_TOFF_SHIFT)) & FLASH_NMPA_DCDC_POWER_PROFILE_HIGH_1_TOFF_MASK)

#define FLASH_NMPA_DCDC_POWER_PROFILE_HIGH_1_TOFFENABLE_MASK (0x80000000U)
#define FLASH_NMPA_DCDC_POWER_PROFILE_HIGH_1_TOFFENABLE_SHIFT (31U)
/*! TOFFENABLE - Enable Constant Off-Time feature. */
#define FLASH_NMPA_DCDC_POWER_PROFILE_HIGH_1_TOFFENABLE(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_DCDC_POWER_PROFILE_HIGH_1_TOFFENABLE_SHIFT)) & FLASH_NMPA_DCDC_POWER_PROFILE_HIGH_1_TOFFENABLE_MASK)
/*! @} */

/*! @name DCDC_POWER_PROFILE_HIGH_ARRAY -  */
/*! @{ */

#define FLASH_NMPA_DCDC_POWER_PROFILE_HIGH_ARRAY_FIELD_MASK (0xFFFFFFFFU)
#define FLASH_NMPA_DCDC_POWER_PROFILE_HIGH_ARRAY_FIELD_SHIFT (0U)
#define FLASH_NMPA_DCDC_POWER_PROFILE_HIGH_ARRAY_FIELD(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_DCDC_POWER_PROFILE_HIGH_ARRAY_FIELD_SHIFT)) & FLASH_NMPA_DCDC_POWER_PROFILE_HIGH_ARRAY_FIELD_MASK)
/*! @} */

/* The count of FLASH_NMPA_DCDC_POWER_PROFILE_HIGH_ARRAY */
#define FLASH_NMPA_DCDC_POWER_PROFILE_HIGH_ARRAY_COUNT (2U)

/*! @name DCDC_POWER_PROFILE_LOW_0 -  */
/*! @{ */

#define FLASH_NMPA_DCDC_POWER_PROFILE_LOW_0_DCDC_TRIM_VALID_MASK (0x1U)
#define FLASH_NMPA_DCDC_POWER_PROFILE_LOW_0_DCDC_TRIM_VALID_SHIFT (0U)
/*! DCDC_TRIM_VALID - DCDC is trimed. */
#define FLASH_NMPA_DCDC_POWER_PROFILE_LOW_0_DCDC_TRIM_VALID(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_DCDC_POWER_PROFILE_LOW_0_DCDC_TRIM_VALID_SHIFT)) & FLASH_NMPA_DCDC_POWER_PROFILE_LOW_0_DCDC_TRIM_VALID_MASK)

#define FLASH_NMPA_DCDC_POWER_PROFILE_LOW_0_RC_MASK (0x7EU)
#define FLASH_NMPA_DCDC_POWER_PROFILE_LOW_0_RC_SHIFT (1U)
/*! RC - Constant On-Time calibration. */
#define FLASH_NMPA_DCDC_POWER_PROFILE_LOW_0_RC(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_DCDC_POWER_PROFILE_LOW_0_RC_SHIFT)) & FLASH_NMPA_DCDC_POWER_PROFILE_LOW_0_RC_MASK)

#define FLASH_NMPA_DCDC_POWER_PROFILE_LOW_0_ICOMP_MASK (0x180U)
#define FLASH_NMPA_DCDC_POWER_PROFILE_LOW_0_ICOMP_SHIFT (7U)
/*! ICOMP - Select the type of ZCD comparator. */
#define FLASH_NMPA_DCDC_POWER_PROFILE_LOW_0_ICOMP(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_DCDC_POWER_PROFILE_LOW_0_ICOMP_SHIFT)) & FLASH_NMPA_DCDC_POWER_PROFILE_LOW_0_ICOMP_MASK)

#define FLASH_NMPA_DCDC_POWER_PROFILE_LOW_0_ISEL_MASK (0x600U)
#define FLASH_NMPA_DCDC_POWER_PROFILE_LOW_0_ISEL_SHIFT (9U)
/*! ISEL - Alter Internal biasing currents. */
#define FLASH_NMPA_DCDC_POWER_PROFILE_LOW_0_ISEL(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_DCDC_POWER_PROFILE_LOW_0_ISEL_SHIFT)) & FLASH_NMPA_DCDC_POWER_PROFILE_LOW_0_ISEL_MASK)

#define FLASH_NMPA_DCDC_POWER_PROFILE_LOW_0_ICENABLE_MASK (0x800U)
#define FLASH_NMPA_DCDC_POWER_PROFILE_LOW_0_ICENABLE_SHIFT (11U)
/*! ICENABLE - Selection of auto scaling of COT period with variations in VDD. */
#define FLASH_NMPA_DCDC_POWER_PROFILE_LOW_0_ICENABLE(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_DCDC_POWER_PROFILE_LOW_0_ICENABLE_SHIFT)) & FLASH_NMPA_DCDC_POWER_PROFILE_LOW_0_ICENABLE_MASK)

#define FLASH_NMPA_DCDC_POWER_PROFILE_LOW_0_TMOS_MASK (0x1F000U)
#define FLASH_NMPA_DCDC_POWER_PROFILE_LOW_0_TMOS_SHIFT (12U)
/*! TMOS - One-shot generator reference current trimming signal. */
#define FLASH_NMPA_DCDC_POWER_PROFILE_LOW_0_TMOS(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_DCDC_POWER_PROFILE_LOW_0_TMOS_SHIFT)) & FLASH_NMPA_DCDC_POWER_PROFILE_LOW_0_TMOS_MASK)

#define FLASH_NMPA_DCDC_POWER_PROFILE_LOW_0_DISABLEISENSE_MASK (0x20000U)
#define FLASH_NMPA_DCDC_POWER_PROFILE_LOW_0_DISABLEISENSE_SHIFT (17U)
/*! DISABLEISENSE - Disable Current sensing. */
#define FLASH_NMPA_DCDC_POWER_PROFILE_LOW_0_DISABLEISENSE(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_DCDC_POWER_PROFILE_LOW_0_DISABLEISENSE_SHIFT)) & FLASH_NMPA_DCDC_POWER_PROFILE_LOW_0_DISABLEISENSE_MASK)

#define FLASH_NMPA_DCDC_POWER_PROFILE_LOW_0_VOUT_MASK (0x3C0000U)
#define FLASH_NMPA_DCDC_POWER_PROFILE_LOW_0_VOUT_SHIFT (18U)
/*! VOUT - Set output regulation voltage. */
#define FLASH_NMPA_DCDC_POWER_PROFILE_LOW_0_VOUT(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_DCDC_POWER_PROFILE_LOW_0_VOUT_SHIFT)) & FLASH_NMPA_DCDC_POWER_PROFILE_LOW_0_VOUT_MASK)

#define FLASH_NMPA_DCDC_POWER_PROFILE_LOW_0_SLICINGENABLE_MASK (0x400000U)
#define FLASH_NMPA_DCDC_POWER_PROFILE_LOW_0_SLICINGENABLE_SHIFT (22U)
/*! SLICINGENABLE - Enable staggered switching of power switches. */
#define FLASH_NMPA_DCDC_POWER_PROFILE_LOW_0_SLICINGENABLE(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_DCDC_POWER_PROFILE_LOW_0_SLICINGENABLE_SHIFT)) & FLASH_NMPA_DCDC_POWER_PROFILE_LOW_0_SLICINGENABLE_MASK)

#define FLASH_NMPA_DCDC_POWER_PROFILE_LOW_0_INDUCTORCLAMPENABLE_MASK (0x800000U)
#define FLASH_NMPA_DCDC_POWER_PROFILE_LOW_0_INDUCTORCLAMPENABLE_SHIFT (23U)
/*! INDUCTORCLAMPENABLE - Enable shorting of Inductor during PFM idle time. */
#define FLASH_NMPA_DCDC_POWER_PROFILE_LOW_0_INDUCTORCLAMPENABLE(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_DCDC_POWER_PROFILE_LOW_0_INDUCTORCLAMPENABLE_SHIFT)) & FLASH_NMPA_DCDC_POWER_PROFILE_LOW_0_INDUCTORCLAMPENABLE_MASK)

#define FLASH_NMPA_DCDC_POWER_PROFILE_LOW_0_VOUT_PWD_MASK (0xF000000U)
#define FLASH_NMPA_DCDC_POWER_PROFILE_LOW_0_VOUT_PWD_SHIFT (24U)
/*! VOUT_PWD - Set output regulation voltage during Deep Sleep. */
#define FLASH_NMPA_DCDC_POWER_PROFILE_LOW_0_VOUT_PWD(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_DCDC_POWER_PROFILE_LOW_0_VOUT_PWD_SHIFT)) & FLASH_NMPA_DCDC_POWER_PROFILE_LOW_0_VOUT_PWD_MASK)
/*! @} */

/*! @name DCDC_POWER_PROFILE_LOW_1 -  */
/*! @{ */

#define FLASH_NMPA_DCDC_POWER_PROFILE_LOW_1_RTRIMOFFET_MASK (0xFU)
#define FLASH_NMPA_DCDC_POWER_PROFILE_LOW_1_RTRIMOFFET_SHIFT (0U)
/*! RTRIMOFFET - Adjust the offset voltage of BJT based comparator. */
#define FLASH_NMPA_DCDC_POWER_PROFILE_LOW_1_RTRIMOFFET(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_DCDC_POWER_PROFILE_LOW_1_RTRIMOFFET_SHIFT)) & FLASH_NMPA_DCDC_POWER_PROFILE_LOW_1_RTRIMOFFET_MASK)

#define FLASH_NMPA_DCDC_POWER_PROFILE_LOW_1_RSENSETRIM_MASK (0xF0U)
#define FLASH_NMPA_DCDC_POWER_PROFILE_LOW_1_RSENSETRIM_SHIFT (4U)
/*! RSENSETRIM - Adjust Max inductor peak current limiting. */
#define FLASH_NMPA_DCDC_POWER_PROFILE_LOW_1_RSENSETRIM(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_DCDC_POWER_PROFILE_LOW_1_RSENSETRIM_SHIFT)) & FLASH_NMPA_DCDC_POWER_PROFILE_LOW_1_RSENSETRIM_MASK)

#define FLASH_NMPA_DCDC_POWER_PROFILE_LOW_1_DTESTENABLE_MASK (0x100U)
#define FLASH_NMPA_DCDC_POWER_PROFILE_LOW_1_DTESTENABLE_SHIFT (8U)
/*! DTESTENABLE - Enable Digital test signals. */
#define FLASH_NMPA_DCDC_POWER_PROFILE_LOW_1_DTESTENABLE(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_DCDC_POWER_PROFILE_LOW_1_DTESTENABLE_SHIFT)) & FLASH_NMPA_DCDC_POWER_PROFILE_LOW_1_DTESTENABLE_MASK)

#define FLASH_NMPA_DCDC_POWER_PROFILE_LOW_1_SETCURVE_MASK (0x600U)
#define FLASH_NMPA_DCDC_POWER_PROFILE_LOW_1_SETCURVE_SHIFT (9U)
/*! SETCURVE - Bandgap calibration parameter. */
#define FLASH_NMPA_DCDC_POWER_PROFILE_LOW_1_SETCURVE(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_DCDC_POWER_PROFILE_LOW_1_SETCURVE_SHIFT)) & FLASH_NMPA_DCDC_POWER_PROFILE_LOW_1_SETCURVE_MASK)

#define FLASH_NMPA_DCDC_POWER_PROFILE_LOW_1_SETDC_MASK (0x7800U)
#define FLASH_NMPA_DCDC_POWER_PROFILE_LOW_1_SETDC_SHIFT (11U)
/*! SETDC - Bandgap calibration parameter. */
#define FLASH_NMPA_DCDC_POWER_PROFILE_LOW_1_SETDC(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_DCDC_POWER_PROFILE_LOW_1_SETDC_SHIFT)) & FLASH_NMPA_DCDC_POWER_PROFILE_LOW_1_SETDC_MASK)

#define FLASH_NMPA_DCDC_POWER_PROFILE_LOW_1_DTESTSEL_MASK (0x38000U)
#define FLASH_NMPA_DCDC_POWER_PROFILE_LOW_1_DTESTSEL_SHIFT (15U)
/*! DTESTSEL - Select the output signal for test. */
#define FLASH_NMPA_DCDC_POWER_PROFILE_LOW_1_DTESTSEL(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_DCDC_POWER_PROFILE_LOW_1_DTESTSEL_SHIFT)) & FLASH_NMPA_DCDC_POWER_PROFILE_LOW_1_DTESTSEL_MASK)

#define FLASH_NMPA_DCDC_POWER_PROFILE_LOW_1_ISCALEENABLE_MASK (0x40000U)
#define FLASH_NMPA_DCDC_POWER_PROFILE_LOW_1_ISCALEENABLE_SHIFT (18U)
/*! ISCALEENABLE - Modify COT behavior. */
#define FLASH_NMPA_DCDC_POWER_PROFILE_LOW_1_ISCALEENABLE(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_DCDC_POWER_PROFILE_LOW_1_ISCALEENABLE_SHIFT)) & FLASH_NMPA_DCDC_POWER_PROFILE_LOW_1_ISCALEENABLE_MASK)

#define FLASH_NMPA_DCDC_POWER_PROFILE_LOW_1_FORCEBYPASS_MASK (0x80000U)
#define FLASH_NMPA_DCDC_POWER_PROFILE_LOW_1_FORCEBYPASS_SHIFT (19U)
/*! FORCEBYPASS - Force bypass mode. */
#define FLASH_NMPA_DCDC_POWER_PROFILE_LOW_1_FORCEBYPASS(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_DCDC_POWER_PROFILE_LOW_1_FORCEBYPASS_SHIFT)) & FLASH_NMPA_DCDC_POWER_PROFILE_LOW_1_FORCEBYPASS_MASK)

#define FLASH_NMPA_DCDC_POWER_PROFILE_LOW_1_TRIMAUTOCOT_MASK (0xF00000U)
#define FLASH_NMPA_DCDC_POWER_PROFILE_LOW_1_TRIMAUTOCOT_SHIFT (20U)
/*! TRIMAUTOCOT - Change the scaling ratio of the feedforward compensation. */
#define FLASH_NMPA_DCDC_POWER_PROFILE_LOW_1_TRIMAUTOCOT(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_DCDC_POWER_PROFILE_LOW_1_TRIMAUTOCOT_SHIFT)) & FLASH_NMPA_DCDC_POWER_PROFILE_LOW_1_TRIMAUTOCOT_MASK)

#define FLASH_NMPA_DCDC_POWER_PROFILE_LOW_1_FORCEFULLCYCLE_MASK (0x1000000U)
#define FLASH_NMPA_DCDC_POWER_PROFILE_LOW_1_FORCEFULLCYCLE_SHIFT (24U)
/*! FORCEFULLCYCLE - Force full PFM PMOS and NMOS cycle. */
#define FLASH_NMPA_DCDC_POWER_PROFILE_LOW_1_FORCEFULLCYCLE(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_DCDC_POWER_PROFILE_LOW_1_FORCEFULLCYCLE_SHIFT)) & FLASH_NMPA_DCDC_POWER_PROFILE_LOW_1_FORCEFULLCYCLE_MASK)

#define FLASH_NMPA_DCDC_POWER_PROFILE_LOW_1_LCENABLE_MASK (0x2000000U)
#define FLASH_NMPA_DCDC_POWER_PROFILE_LOW_1_LCENABLE_SHIFT (25U)
/*! LCENABLE - Change the range of the peak detector of current inside the inductor. */
#define FLASH_NMPA_DCDC_POWER_PROFILE_LOW_1_LCENABLE(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_DCDC_POWER_PROFILE_LOW_1_LCENABLE_SHIFT)) & FLASH_NMPA_DCDC_POWER_PROFILE_LOW_1_LCENABLE_MASK)

#define FLASH_NMPA_DCDC_POWER_PROFILE_LOW_1_TOFF_MASK (0x7C000000U)
#define FLASH_NMPA_DCDC_POWER_PROFILE_LOW_1_TOFF_SHIFT (26U)
/*! TOFF - Constant Off-Time calibration input. */
#define FLASH_NMPA_DCDC_POWER_PROFILE_LOW_1_TOFF(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_DCDC_POWER_PROFILE_LOW_1_TOFF_SHIFT)) & FLASH_NMPA_DCDC_POWER_PROFILE_LOW_1_TOFF_MASK)

#define FLASH_NMPA_DCDC_POWER_PROFILE_LOW_1_TOFFENABLE_MASK (0x80000000U)
#define FLASH_NMPA_DCDC_POWER_PROFILE_LOW_1_TOFFENABLE_SHIFT (31U)
/*! TOFFENABLE - Enable Constant Off-Time feature. */
#define FLASH_NMPA_DCDC_POWER_PROFILE_LOW_1_TOFFENABLE(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_DCDC_POWER_PROFILE_LOW_1_TOFFENABLE_SHIFT)) & FLASH_NMPA_DCDC_POWER_PROFILE_LOW_1_TOFFENABLE_MASK)
/*! @} */

/*! @name DCDC_POWER_PROFILE_LOW_ARRAY -  */
/*! @{ */

#define FLASH_NMPA_DCDC_POWER_PROFILE_LOW_ARRAY_FIELD_MASK (0xFFFFFFFFU)
#define FLASH_NMPA_DCDC_POWER_PROFILE_LOW_ARRAY_FIELD_SHIFT (0U)
#define FLASH_NMPA_DCDC_POWER_PROFILE_LOW_ARRAY_FIELD(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_DCDC_POWER_PROFILE_LOW_ARRAY_FIELD_SHIFT)) & FLASH_NMPA_DCDC_POWER_PROFILE_LOW_ARRAY_FIELD_MASK)
/*! @} */

/* The count of FLASH_NMPA_DCDC_POWER_PROFILE_LOW_ARRAY */
#define FLASH_NMPA_DCDC_POWER_PROFILE_LOW_ARRAY_COUNT (2U)

/*! @name DCDC_POWER_PROFILE_MEDIUM_0 -  */
/*! @{ */

#define FLASH_NMPA_DCDC_POWER_PROFILE_MEDIUM_0_DCDC_TRIM_VALID_MASK (0x1U)
#define FLASH_NMPA_DCDC_POWER_PROFILE_MEDIUM_0_DCDC_TRIM_VALID_SHIFT (0U)
/*! DCDC_TRIM_VALID - DCDC is trimed. */
#define FLASH_NMPA_DCDC_POWER_PROFILE_MEDIUM_0_DCDC_TRIM_VALID(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_DCDC_POWER_PROFILE_MEDIUM_0_DCDC_TRIM_VALID_SHIFT)) & FLASH_NMPA_DCDC_POWER_PROFILE_MEDIUM_0_DCDC_TRIM_VALID_MASK)

#define FLASH_NMPA_DCDC_POWER_PROFILE_MEDIUM_0_RC_MASK (0x7EU)
#define FLASH_NMPA_DCDC_POWER_PROFILE_MEDIUM_0_RC_SHIFT (1U)
/*! RC - Constant On-Time calibration. */
#define FLASH_NMPA_DCDC_POWER_PROFILE_MEDIUM_0_RC(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_DCDC_POWER_PROFILE_MEDIUM_0_RC_SHIFT)) & FLASH_NMPA_DCDC_POWER_PROFILE_MEDIUM_0_RC_MASK)

#define FLASH_NMPA_DCDC_POWER_PROFILE_MEDIUM_0_ICOMP_MASK (0x180U)
#define FLASH_NMPA_DCDC_POWER_PROFILE_MEDIUM_0_ICOMP_SHIFT (7U)
/*! ICOMP - Select the type of ZCD comparator. */
#define FLASH_NMPA_DCDC_POWER_PROFILE_MEDIUM_0_ICOMP(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_DCDC_POWER_PROFILE_MEDIUM_0_ICOMP_SHIFT)) & FLASH_NMPA_DCDC_POWER_PROFILE_MEDIUM_0_ICOMP_MASK)

#define FLASH_NMPA_DCDC_POWER_PROFILE_MEDIUM_0_ISEL_MASK (0x600U)
#define FLASH_NMPA_DCDC_POWER_PROFILE_MEDIUM_0_ISEL_SHIFT (9U)
/*! ISEL - Alter Internal biasing currents. */
#define FLASH_NMPA_DCDC_POWER_PROFILE_MEDIUM_0_ISEL(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_DCDC_POWER_PROFILE_MEDIUM_0_ISEL_SHIFT)) & FLASH_NMPA_DCDC_POWER_PROFILE_MEDIUM_0_ISEL_MASK)

#define FLASH_NMPA_DCDC_POWER_PROFILE_MEDIUM_0_ICENABLE_MASK (0x800U)
#define FLASH_NMPA_DCDC_POWER_PROFILE_MEDIUM_0_ICENABLE_SHIFT (11U)
/*! ICENABLE - Selection of auto scaling of COT period with variations in VDD. */
#define FLASH_NMPA_DCDC_POWER_PROFILE_MEDIUM_0_ICENABLE(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_DCDC_POWER_PROFILE_MEDIUM_0_ICENABLE_SHIFT)) & FLASH_NMPA_DCDC_POWER_PROFILE_MEDIUM_0_ICENABLE_MASK)

#define FLASH_NMPA_DCDC_POWER_PROFILE_MEDIUM_0_TMOS_MASK (0x1F000U)
#define FLASH_NMPA_DCDC_POWER_PROFILE_MEDIUM_0_TMOS_SHIFT (12U)
/*! TMOS - One-shot generator reference current trimming signal. */
#define FLASH_NMPA_DCDC_POWER_PROFILE_MEDIUM_0_TMOS(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_DCDC_POWER_PROFILE_MEDIUM_0_TMOS_SHIFT)) & FLASH_NMPA_DCDC_POWER_PROFILE_MEDIUM_0_TMOS_MASK)

#define FLASH_NMPA_DCDC_POWER_PROFILE_MEDIUM_0_DISABLEISENSE_MASK (0x20000U)
#define FLASH_NMPA_DCDC_POWER_PROFILE_MEDIUM_0_DISABLEISENSE_SHIFT (17U)
/*! DISABLEISENSE - Disable Current sensing. */
#define FLASH_NMPA_DCDC_POWER_PROFILE_MEDIUM_0_DISABLEISENSE(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_DCDC_POWER_PROFILE_MEDIUM_0_DISABLEISENSE_SHIFT)) & FLASH_NMPA_DCDC_POWER_PROFILE_MEDIUM_0_DISABLEISENSE_MASK)

#define FLASH_NMPA_DCDC_POWER_PROFILE_MEDIUM_0_VOUT_MASK (0x3C0000U)
#define FLASH_NMPA_DCDC_POWER_PROFILE_MEDIUM_0_VOUT_SHIFT (18U)
/*! VOUT - Set output regulation voltage. */
#define FLASH_NMPA_DCDC_POWER_PROFILE_MEDIUM_0_VOUT(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_DCDC_POWER_PROFILE_MEDIUM_0_VOUT_SHIFT)) & FLASH_NMPA_DCDC_POWER_PROFILE_MEDIUM_0_VOUT_MASK)

#define FLASH_NMPA_DCDC_POWER_PROFILE_MEDIUM_0_SLICINGENABLE_MASK (0x400000U)
#define FLASH_NMPA_DCDC_POWER_PROFILE_MEDIUM_0_SLICINGENABLE_SHIFT (22U)
/*! SLICINGENABLE - Enable staggered switching of power switches. */
#define FLASH_NMPA_DCDC_POWER_PROFILE_MEDIUM_0_SLICINGENABLE(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_DCDC_POWER_PROFILE_MEDIUM_0_SLICINGENABLE_SHIFT)) & FLASH_NMPA_DCDC_POWER_PROFILE_MEDIUM_0_SLICINGENABLE_MASK)

#define FLASH_NMPA_DCDC_POWER_PROFILE_MEDIUM_0_INDUCTORCLAMPENABLE_MASK (0x800000U)
#define FLASH_NMPA_DCDC_POWER_PROFILE_MEDIUM_0_INDUCTORCLAMPENABLE_SHIFT (23U)
/*! INDUCTORCLAMPENABLE - Enable shorting of Inductor during PFM idle time. */
#define FLASH_NMPA_DCDC_POWER_PROFILE_MEDIUM_0_INDUCTORCLAMPENABLE(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_DCDC_POWER_PROFILE_MEDIUM_0_INDUCTORCLAMPENABLE_SHIFT)) & FLASH_NMPA_DCDC_POWER_PROFILE_MEDIUM_0_INDUCTORCLAMPENABLE_MASK)

#define FLASH_NMPA_DCDC_POWER_PROFILE_MEDIUM_0_VOUT_PWD_MASK (0xF000000U)
#define FLASH_NMPA_DCDC_POWER_PROFILE_MEDIUM_0_VOUT_PWD_SHIFT (24U)
/*! VOUT_PWD - Set output regulation voltage during Deep Sleep. */
#define FLASH_NMPA_DCDC_POWER_PROFILE_MEDIUM_0_VOUT_PWD(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_DCDC_POWER_PROFILE_MEDIUM_0_VOUT_PWD_SHIFT)) & FLASH_NMPA_DCDC_POWER_PROFILE_MEDIUM_0_VOUT_PWD_MASK)
/*! @} */

/*! @name DCDC_POWER_PROFILE_MEDIUM_1 -  */
/*! @{ */

#define FLASH_NMPA_DCDC_POWER_PROFILE_MEDIUM_1_RTRIMOFFET_MASK (0xFU)
#define FLASH_NMPA_DCDC_POWER_PROFILE_MEDIUM_1_RTRIMOFFET_SHIFT (0U)
/*! RTRIMOFFET - Adjust the offset voltage of BJT based comparator. */
#define FLASH_NMPA_DCDC_POWER_PROFILE_MEDIUM_1_RTRIMOFFET(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_DCDC_POWER_PROFILE_MEDIUM_1_RTRIMOFFET_SHIFT)) & FLASH_NMPA_DCDC_POWER_PROFILE_MEDIUM_1_RTRIMOFFET_MASK)

#define FLASH_NMPA_DCDC_POWER_PROFILE_MEDIUM_1_RSENSETRIM_MASK (0xF0U)
#define FLASH_NMPA_DCDC_POWER_PROFILE_MEDIUM_1_RSENSETRIM_SHIFT (4U)
/*! RSENSETRIM - Adjust Max inductor peak current limiting. */
#define FLASH_NMPA_DCDC_POWER_PROFILE_MEDIUM_1_RSENSETRIM(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_DCDC_POWER_PROFILE_MEDIUM_1_RSENSETRIM_SHIFT)) & FLASH_NMPA_DCDC_POWER_PROFILE_MEDIUM_1_RSENSETRIM_MASK)

#define FLASH_NMPA_DCDC_POWER_PROFILE_MEDIUM_1_DTESTENABLE_MASK (0x100U)
#define FLASH_NMPA_DCDC_POWER_PROFILE_MEDIUM_1_DTESTENABLE_SHIFT (8U)
/*! DTESTENABLE - Enable Digital test signals. */
#define FLASH_NMPA_DCDC_POWER_PROFILE_MEDIUM_1_DTESTENABLE(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_DCDC_POWER_PROFILE_MEDIUM_1_DTESTENABLE_SHIFT)) & FLASH_NMPA_DCDC_POWER_PROFILE_MEDIUM_1_DTESTENABLE_MASK)

#define FLASH_NMPA_DCDC_POWER_PROFILE_MEDIUM_1_SETCURVE_MASK (0x600U)
#define FLASH_NMPA_DCDC_POWER_PROFILE_MEDIUM_1_SETCURVE_SHIFT (9U)
/*! SETCURVE - Bandgap calibration parameter. */
#define FLASH_NMPA_DCDC_POWER_PROFILE_MEDIUM_1_SETCURVE(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_DCDC_POWER_PROFILE_MEDIUM_1_SETCURVE_SHIFT)) & FLASH_NMPA_DCDC_POWER_PROFILE_MEDIUM_1_SETCURVE_MASK)

#define FLASH_NMPA_DCDC_POWER_PROFILE_MEDIUM_1_SETDC_MASK (0x7800U)
#define FLASH_NMPA_DCDC_POWER_PROFILE_MEDIUM_1_SETDC_SHIFT (11U)
/*! SETDC - Bandgap calibration parameter. */
#define FLASH_NMPA_DCDC_POWER_PROFILE_MEDIUM_1_SETDC(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_DCDC_POWER_PROFILE_MEDIUM_1_SETDC_SHIFT)) & FLASH_NMPA_DCDC_POWER_PROFILE_MEDIUM_1_SETDC_MASK)

#define FLASH_NMPA_DCDC_POWER_PROFILE_MEDIUM_1_DTESTSEL_MASK (0x38000U)
#define FLASH_NMPA_DCDC_POWER_PROFILE_MEDIUM_1_DTESTSEL_SHIFT (15U)
/*! DTESTSEL - Select the output signal for test. */
#define FLASH_NMPA_DCDC_POWER_PROFILE_MEDIUM_1_DTESTSEL(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_DCDC_POWER_PROFILE_MEDIUM_1_DTESTSEL_SHIFT)) & FLASH_NMPA_DCDC_POWER_PROFILE_MEDIUM_1_DTESTSEL_MASK)

#define FLASH_NMPA_DCDC_POWER_PROFILE_MEDIUM_1_ISCALEENABLE_MASK (0x40000U)
#define FLASH_NMPA_DCDC_POWER_PROFILE_MEDIUM_1_ISCALEENABLE_SHIFT (18U)
/*! ISCALEENABLE - Modify COT behavior. */
#define FLASH_NMPA_DCDC_POWER_PROFILE_MEDIUM_1_ISCALEENABLE(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_DCDC_POWER_PROFILE_MEDIUM_1_ISCALEENABLE_SHIFT)) & FLASH_NMPA_DCDC_POWER_PROFILE_MEDIUM_1_ISCALEENABLE_MASK)

#define FLASH_NMPA_DCDC_POWER_PROFILE_MEDIUM_1_FORCEBYPASS_MASK (0x80000U)
#define FLASH_NMPA_DCDC_POWER_PROFILE_MEDIUM_1_FORCEBYPASS_SHIFT (19U)
/*! FORCEBYPASS - Force bypass mode. */
#define FLASH_NMPA_DCDC_POWER_PROFILE_MEDIUM_1_FORCEBYPASS(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_DCDC_POWER_PROFILE_MEDIUM_1_FORCEBYPASS_SHIFT)) & FLASH_NMPA_DCDC_POWER_PROFILE_MEDIUM_1_FORCEBYPASS_MASK)

#define FLASH_NMPA_DCDC_POWER_PROFILE_MEDIUM_1_TRIMAUTOCOT_MASK (0xF00000U)
#define FLASH_NMPA_DCDC_POWER_PROFILE_MEDIUM_1_TRIMAUTOCOT_SHIFT (20U)
/*! TRIMAUTOCOT - Change the scaling ratio of the feedforward compensation. */
#define FLASH_NMPA_DCDC_POWER_PROFILE_MEDIUM_1_TRIMAUTOCOT(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_DCDC_POWER_PROFILE_MEDIUM_1_TRIMAUTOCOT_SHIFT)) & FLASH_NMPA_DCDC_POWER_PROFILE_MEDIUM_1_TRIMAUTOCOT_MASK)

#define FLASH_NMPA_DCDC_POWER_PROFILE_MEDIUM_1_FORCEFULLCYCLE_MASK (0x1000000U)
#define FLASH_NMPA_DCDC_POWER_PROFILE_MEDIUM_1_FORCEFULLCYCLE_SHIFT (24U)
/*! FORCEFULLCYCLE - Force full PFM PMOS and NMOS cycle. */
#define FLASH_NMPA_DCDC_POWER_PROFILE_MEDIUM_1_FORCEFULLCYCLE(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_DCDC_POWER_PROFILE_MEDIUM_1_FORCEFULLCYCLE_SHIFT)) & FLASH_NMPA_DCDC_POWER_PROFILE_MEDIUM_1_FORCEFULLCYCLE_MASK)

#define FLASH_NMPA_DCDC_POWER_PROFILE_MEDIUM_1_LCENABLE_MASK (0x2000000U)
#define FLASH_NMPA_DCDC_POWER_PROFILE_MEDIUM_1_LCENABLE_SHIFT (25U)
/*! LCENABLE - Change the range of the peak detector of current inside the inductor. */
#define FLASH_NMPA_DCDC_POWER_PROFILE_MEDIUM_1_LCENABLE(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_DCDC_POWER_PROFILE_MEDIUM_1_LCENABLE_SHIFT)) & FLASH_NMPA_DCDC_POWER_PROFILE_MEDIUM_1_LCENABLE_MASK)

#define FLASH_NMPA_DCDC_POWER_PROFILE_MEDIUM_1_TOFF_MASK (0x7C000000U)
#define FLASH_NMPA_DCDC_POWER_PROFILE_MEDIUM_1_TOFF_SHIFT (26U)
/*! TOFF - Constant Off-Time calibration input. */
#define FLASH_NMPA_DCDC_POWER_PROFILE_MEDIUM_1_TOFF(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_DCDC_POWER_PROFILE_MEDIUM_1_TOFF_SHIFT)) & FLASH_NMPA_DCDC_POWER_PROFILE_MEDIUM_1_TOFF_MASK)

#define FLASH_NMPA_DCDC_POWER_PROFILE_MEDIUM_1_TOFFENABLE_MASK (0x80000000U)
#define FLASH_NMPA_DCDC_POWER_PROFILE_MEDIUM_1_TOFFENABLE_SHIFT (31U)
/*! TOFFENABLE - Enable Constant Off-Time feature. */
#define FLASH_NMPA_DCDC_POWER_PROFILE_MEDIUM_1_TOFFENABLE(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_DCDC_POWER_PROFILE_MEDIUM_1_TOFFENABLE_SHIFT)) & FLASH_NMPA_DCDC_POWER_PROFILE_MEDIUM_1_TOFFENABLE_MASK)
/*! @} */

/*! @name DCDC_POWER_PROFILE_MEDIUM_ARRAY -  */
/*! @{ */

#define FLASH_NMPA_DCDC_POWER_PROFILE_MEDIUM_ARRAY_FIELD_MASK (0xFFFFFFFFU)
#define FLASH_NMPA_DCDC_POWER_PROFILE_MEDIUM_ARRAY_FIELD_SHIFT (0U)
#define FLASH_NMPA_DCDC_POWER_PROFILE_MEDIUM_ARRAY_FIELD(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_DCDC_POWER_PROFILE_MEDIUM_ARRAY_FIELD_SHIFT)) & FLASH_NMPA_DCDC_POWER_PROFILE_MEDIUM_ARRAY_FIELD_MASK)
/*! @} */

/* The count of FLASH_NMPA_DCDC_POWER_PROFILE_MEDIUM_ARRAY */
#define FLASH_NMPA_DCDC_POWER_PROFILE_MEDIUM_ARRAY_COUNT (2U)

/*! @name BOD -  */
/*! @{ */

#define FLASH_NMPA_BOD_BOD_VBAT_TRIM_VALID_MASK  (0x1U)
#define FLASH_NMPA_BOD_BOD_VBAT_TRIM_VALID_SHIFT (0U)
#define FLASH_NMPA_BOD_BOD_VBAT_TRIM_VALID(x)    (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_BOD_BOD_VBAT_TRIM_VALID_SHIFT)) & FLASH_NMPA_BOD_BOD_VBAT_TRIM_VALID_MASK)

#define FLASH_NMPA_BOD_BOD_VBAT_TRIGLVL_MASK     (0x3EU)
#define FLASH_NMPA_BOD_BOD_VBAT_TRIGLVL_SHIFT    (1U)
#define FLASH_NMPA_BOD_BOD_VBAT_TRIGLVL(x)       (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_BOD_BOD_VBAT_TRIGLVL_SHIFT)) & FLASH_NMPA_BOD_BOD_VBAT_TRIGLVL_MASK)

#define FLASH_NMPA_BOD_BOD_VBAT_HYST_MASK        (0xC0U)
#define FLASH_NMPA_BOD_BOD_VBAT_HYST_SHIFT       (6U)
#define FLASH_NMPA_BOD_BOD_VBAT_HYST(x)          (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_BOD_BOD_VBAT_HYST_SHIFT)) & FLASH_NMPA_BOD_BOD_VBAT_HYST_MASK)

#define FLASH_NMPA_BOD_BOD_CORE_TRIM_VALID_MASK  (0x10000U)
#define FLASH_NMPA_BOD_BOD_CORE_TRIM_VALID_SHIFT (16U)
#define FLASH_NMPA_BOD_BOD_CORE_TRIM_VALID(x)    (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_BOD_BOD_CORE_TRIM_VALID_SHIFT)) & FLASH_NMPA_BOD_BOD_CORE_TRIM_VALID_MASK)

#define FLASH_NMPA_BOD_BOD_CORE_TRIGLVL_MASK     (0xE0000U)
#define FLASH_NMPA_BOD_BOD_CORE_TRIGLVL_SHIFT    (17U)
#define FLASH_NMPA_BOD_BOD_CORE_TRIGLVL(x)       (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_BOD_BOD_CORE_TRIGLVL_SHIFT)) & FLASH_NMPA_BOD_BOD_CORE_TRIGLVL_MASK)

#define FLASH_NMPA_BOD_BOD_CORE_HYST_MASK        (0x600000U)
#define FLASH_NMPA_BOD_BOD_CORE_HYST_SHIFT       (21U)
#define FLASH_NMPA_BOD_BOD_CORE_HYST(x)          (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_BOD_BOD_CORE_HYST_SHIFT)) & FLASH_NMPA_BOD_BOD_CORE_HYST_MASK)
/*! @} */

/*! @name LDO_AO -  */
/*! @{ */

#define FLASH_NMPA_LDO_AO_ACTIVE_TRIM_VALID_MASK (0x1U)
#define FLASH_NMPA_LDO_AO_ACTIVE_TRIM_VALID_SHIFT (0U)
#define FLASH_NMPA_LDO_AO_ACTIVE_TRIM_VALID(x)   (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_LDO_AO_ACTIVE_TRIM_VALID_SHIFT)) & FLASH_NMPA_LDO_AO_ACTIVE_TRIM_VALID_MASK)

#define FLASH_NMPA_LDO_AO_ACTIVE_TRIM_MASK       (0x3EU)
#define FLASH_NMPA_LDO_AO_ACTIVE_TRIM_SHIFT      (1U)
#define FLASH_NMPA_LDO_AO_ACTIVE_TRIM(x)         (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_LDO_AO_ACTIVE_TRIM_SHIFT)) & FLASH_NMPA_LDO_AO_ACTIVE_TRIM_MASK)

#define FLASH_NMPA_LDO_AO_DSLP_TRIM_VALID_MASK   (0x100U)
#define FLASH_NMPA_LDO_AO_DSLP_TRIM_VALID_SHIFT  (8U)
#define FLASH_NMPA_LDO_AO_DSLP_TRIM_VALID(x)     (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_LDO_AO_DSLP_TRIM_VALID_SHIFT)) & FLASH_NMPA_LDO_AO_DSLP_TRIM_VALID_MASK)

#define FLASH_NMPA_LDO_AO_DSLP_TRIM_MASK         (0x3E00U)
#define FLASH_NMPA_LDO_AO_DSLP_TRIM_SHIFT        (9U)
#define FLASH_NMPA_LDO_AO_DSLP_TRIM(x)           (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_LDO_AO_DSLP_TRIM_SHIFT)) & FLASH_NMPA_LDO_AO_DSLP_TRIM_MASK)

#define FLASH_NMPA_LDO_AO_PDWN_TRIM_VALID_MASK   (0x10000U)
#define FLASH_NMPA_LDO_AO_PDWN_TRIM_VALID_SHIFT  (16U)
#define FLASH_NMPA_LDO_AO_PDWN_TRIM_VALID(x)     (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_LDO_AO_PDWN_TRIM_VALID_SHIFT)) & FLASH_NMPA_LDO_AO_PDWN_TRIM_VALID_MASK)

#define FLASH_NMPA_LDO_AO_PDWN_TRIM_MASK         (0x3E0000U)
#define FLASH_NMPA_LDO_AO_PDWN_TRIM_SHIFT        (17U)
#define FLASH_NMPA_LDO_AO_PDWN_TRIM(x)           (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_LDO_AO_PDWN_TRIM_SHIFT)) & FLASH_NMPA_LDO_AO_PDWN_TRIM_MASK)

#define FLASH_NMPA_LDO_AO_DPDW_TRIM_VALID_MASK   (0x1000000U)
#define FLASH_NMPA_LDO_AO_DPDW_TRIM_VALID_SHIFT  (24U)
#define FLASH_NMPA_LDO_AO_DPDW_TRIM_VALID(x)     (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_LDO_AO_DPDW_TRIM_VALID_SHIFT)) & FLASH_NMPA_LDO_AO_DPDW_TRIM_VALID_MASK)

#define FLASH_NMPA_LDO_AO_DPDW_TRIM_MASK         (0x3E000000U)
#define FLASH_NMPA_LDO_AO_DPDW_TRIM_SHIFT        (25U)
#define FLASH_NMPA_LDO_AO_DPDW_TRIM(x)           (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_LDO_AO_DPDW_TRIM_SHIFT)) & FLASH_NMPA_LDO_AO_DPDW_TRIM_MASK)
/*! @} */

/*! @name SDIO_DELAY -  */
/*! @{ */

#define FLASH_NMPA_SDIO_DELAY_SDIO_0_VALID_MASK  (0x1U)
#define FLASH_NMPA_SDIO_DELAY_SDIO_0_VALID_SHIFT (0U)
#define FLASH_NMPA_SDIO_DELAY_SDIO_0_VALID(x)    (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_SDIO_DELAY_SDIO_0_VALID_SHIFT)) & FLASH_NMPA_SDIO_DELAY_SDIO_0_VALID_MASK)

#define FLASH_NMPA_SDIO_DELAY_SDIO_0_DELAY_MASK  (0x7FEU)
#define FLASH_NMPA_SDIO_DELAY_SDIO_0_DELAY_SHIFT (1U)
/*! SDIO_0_DELAY - SDIO_0_DELAY (unit: 100 ps). */
#define FLASH_NMPA_SDIO_DELAY_SDIO_0_DELAY(x)    (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_SDIO_DELAY_SDIO_0_DELAY_SHIFT)) & FLASH_NMPA_SDIO_DELAY_SDIO_0_DELAY_MASK)
/*! @} */

/*! @name AUX_BIAS_CURVE_AMBIENT_0 -  */
/*! @{ */

#define FLASH_NMPA_AUX_BIAS_CURVE_AMBIENT_0_VREF1VCURVETRIM_0_MASK (0xFFFFU)
#define FLASH_NMPA_AUX_BIAS_CURVE_AMBIENT_0_VREF1VCURVETRIM_0_SHIFT (0U)
/*! VREF1VCURVETRIM_0 - VREF1VCURVETRIM_0 (unit: 100uV) */
#define FLASH_NMPA_AUX_BIAS_CURVE_AMBIENT_0_VREF1VCURVETRIM_0(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_AUX_BIAS_CURVE_AMBIENT_0_VREF1VCURVETRIM_0_SHIFT)) & FLASH_NMPA_AUX_BIAS_CURVE_AMBIENT_0_VREF1VCURVETRIM_0_MASK)

#define FLASH_NMPA_AUX_BIAS_CURVE_AMBIENT_0_VREF1VCURVETRIM_1_MASK (0xFFFF0000U)
#define FLASH_NMPA_AUX_BIAS_CURVE_AMBIENT_0_VREF1VCURVETRIM_1_SHIFT (16U)
/*! VREF1VCURVETRIM_1 - VREF1VCURVETRIM_1 (unit: 100uV) */
#define FLASH_NMPA_AUX_BIAS_CURVE_AMBIENT_0_VREF1VCURVETRIM_1(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_AUX_BIAS_CURVE_AMBIENT_0_VREF1VCURVETRIM_1_SHIFT)) & FLASH_NMPA_AUX_BIAS_CURVE_AMBIENT_0_VREF1VCURVETRIM_1_MASK)
/*! @} */

/*! @name AUX_BIAS_CURVE_AMBIENT_1 -  */
/*! @{ */

#define FLASH_NMPA_AUX_BIAS_CURVE_AMBIENT_1_VREF1VCURVETRIM_2_MASK (0xFFFFU)
#define FLASH_NMPA_AUX_BIAS_CURVE_AMBIENT_1_VREF1VCURVETRIM_2_SHIFT (0U)
/*! VREF1VCURVETRIM_2 - VREF1VCURVETRIM_2 (unit: 100uV) */
#define FLASH_NMPA_AUX_BIAS_CURVE_AMBIENT_1_VREF1VCURVETRIM_2(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_AUX_BIAS_CURVE_AMBIENT_1_VREF1VCURVETRIM_2_SHIFT)) & FLASH_NMPA_AUX_BIAS_CURVE_AMBIENT_1_VREF1VCURVETRIM_2_MASK)

#define FLASH_NMPA_AUX_BIAS_CURVE_AMBIENT_1_VREF1VCURVETRIM_3_MASK (0xFFFF0000U)
#define FLASH_NMPA_AUX_BIAS_CURVE_AMBIENT_1_VREF1VCURVETRIM_3_SHIFT (16U)
/*! VREF1VCURVETRIM_3 - VREF1VCURVETRIM_3 (unit: 100uV) */
#define FLASH_NMPA_AUX_BIAS_CURVE_AMBIENT_1_VREF1VCURVETRIM_3(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_AUX_BIAS_CURVE_AMBIENT_1_VREF1VCURVETRIM_3_SHIFT)) & FLASH_NMPA_AUX_BIAS_CURVE_AMBIENT_1_VREF1VCURVETRIM_3_MASK)
/*! @} */

/*! @name AUX_BIAS_CURVE_AMBIENT_2 -  */
/*! @{ */

#define FLASH_NMPA_AUX_BIAS_CURVE_AMBIENT_2_VREF1VCURVETRIM_4_MASK (0xFFFFU)
#define FLASH_NMPA_AUX_BIAS_CURVE_AMBIENT_2_VREF1VCURVETRIM_4_SHIFT (0U)
/*! VREF1VCURVETRIM_4 - VREF1VCURVETRIM_4 (unit: 100uV) */
#define FLASH_NMPA_AUX_BIAS_CURVE_AMBIENT_2_VREF1VCURVETRIM_4(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_AUX_BIAS_CURVE_AMBIENT_2_VREF1VCURVETRIM_4_SHIFT)) & FLASH_NMPA_AUX_BIAS_CURVE_AMBIENT_2_VREF1VCURVETRIM_4_MASK)

#define FLASH_NMPA_AUX_BIAS_CURVE_AMBIENT_2_VREF1VCURVETRIM_5_MASK (0xFFFF0000U)
#define FLASH_NMPA_AUX_BIAS_CURVE_AMBIENT_2_VREF1VCURVETRIM_5_SHIFT (16U)
/*! VREF1VCURVETRIM_5 - VREF1VCURVETRIM_5 (unit: 100uV) */
#define FLASH_NMPA_AUX_BIAS_CURVE_AMBIENT_2_VREF1VCURVETRIM_5(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_AUX_BIAS_CURVE_AMBIENT_2_VREF1VCURVETRIM_5_SHIFT)) & FLASH_NMPA_AUX_BIAS_CURVE_AMBIENT_2_VREF1VCURVETRIM_5_MASK)
/*! @} */

/*! @name AUX_BIAS_CURVE_AMBIENT_3 -  */
/*! @{ */

#define FLASH_NMPA_AUX_BIAS_CURVE_AMBIENT_3_VREF1VCURVETRIM_6_MASK (0xFFFFU)
#define FLASH_NMPA_AUX_BIAS_CURVE_AMBIENT_3_VREF1VCURVETRIM_6_SHIFT (0U)
/*! VREF1VCURVETRIM_6 - VREF1VCURVETRIM_6 (unit: 100uV) */
#define FLASH_NMPA_AUX_BIAS_CURVE_AMBIENT_3_VREF1VCURVETRIM_6(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_AUX_BIAS_CURVE_AMBIENT_3_VREF1VCURVETRIM_6_SHIFT)) & FLASH_NMPA_AUX_BIAS_CURVE_AMBIENT_3_VREF1VCURVETRIM_6_MASK)

#define FLASH_NMPA_AUX_BIAS_CURVE_AMBIENT_3_VREF1VCURVETRIM_7_MASK (0xFFFF0000U)
#define FLASH_NMPA_AUX_BIAS_CURVE_AMBIENT_3_VREF1VCURVETRIM_7_SHIFT (16U)
/*! VREF1VCURVETRIM_7 - VREF1VCURVETRIM_7 (unit: 100uV) */
#define FLASH_NMPA_AUX_BIAS_CURVE_AMBIENT_3_VREF1VCURVETRIM_7(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_AUX_BIAS_CURVE_AMBIENT_3_VREF1VCURVETRIM_7_SHIFT)) & FLASH_NMPA_AUX_BIAS_CURVE_AMBIENT_3_VREF1VCURVETRIM_7_MASK)
/*! @} */

/*! @name AUX_BIAS_CURVE_AMBIENT_ARRAY - Aux Bias Curve Ambient (30degC) */
/*! @{ */

#define FLASH_NMPA_AUX_BIAS_CURVE_AMBIENT_ARRAY_FIELD_MASK (0xFFFFFFFFU)
#define FLASH_NMPA_AUX_BIAS_CURVE_AMBIENT_ARRAY_FIELD_SHIFT (0U)
#define FLASH_NMPA_AUX_BIAS_CURVE_AMBIENT_ARRAY_FIELD(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_AUX_BIAS_CURVE_AMBIENT_ARRAY_FIELD_SHIFT)) & FLASH_NMPA_AUX_BIAS_CURVE_AMBIENT_ARRAY_FIELD_MASK)
/*! @} */

/* The count of FLASH_NMPA_AUX_BIAS_CURVE_AMBIENT_ARRAY */
#define FLASH_NMPA_AUX_BIAS_CURVE_AMBIENT_ARRAY_COUNT (4U)

/*! @name AUX_BIAS_CURVE_TEMP_0 -  */
/*! @{ */

#define FLASH_NMPA_AUX_BIAS_CURVE_TEMP_0_VREF1VCURVETRIM_0_MASK (0xFFFFU)
#define FLASH_NMPA_AUX_BIAS_CURVE_TEMP_0_VREF1VCURVETRIM_0_SHIFT (0U)
/*! VREF1VCURVETRIM_0 - VREF1VCURVETRIM_0 (unit: 100uV) */
#define FLASH_NMPA_AUX_BIAS_CURVE_TEMP_0_VREF1VCURVETRIM_0(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_AUX_BIAS_CURVE_TEMP_0_VREF1VCURVETRIM_0_SHIFT)) & FLASH_NMPA_AUX_BIAS_CURVE_TEMP_0_VREF1VCURVETRIM_0_MASK)

#define FLASH_NMPA_AUX_BIAS_CURVE_TEMP_0_VREF1VCURVETRIM_1_MASK (0xFFFF0000U)
#define FLASH_NMPA_AUX_BIAS_CURVE_TEMP_0_VREF1VCURVETRIM_1_SHIFT (16U)
/*! VREF1VCURVETRIM_1 - VREF1VCURVETRIM_1 (unit: 100uV) */
#define FLASH_NMPA_AUX_BIAS_CURVE_TEMP_0_VREF1VCURVETRIM_1(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_AUX_BIAS_CURVE_TEMP_0_VREF1VCURVETRIM_1_SHIFT)) & FLASH_NMPA_AUX_BIAS_CURVE_TEMP_0_VREF1VCURVETRIM_1_MASK)
/*! @} */

/*! @name AUX_BIAS_CURVE_TEMP_1 -  */
/*! @{ */

#define FLASH_NMPA_AUX_BIAS_CURVE_TEMP_1_VREF1VCURVETRIM_2_MASK (0xFFFFU)
#define FLASH_NMPA_AUX_BIAS_CURVE_TEMP_1_VREF1VCURVETRIM_2_SHIFT (0U)
/*! VREF1VCURVETRIM_2 - VREF1VCURVETRIM_2 (unit: 100uV) */
#define FLASH_NMPA_AUX_BIAS_CURVE_TEMP_1_VREF1VCURVETRIM_2(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_AUX_BIAS_CURVE_TEMP_1_VREF1VCURVETRIM_2_SHIFT)) & FLASH_NMPA_AUX_BIAS_CURVE_TEMP_1_VREF1VCURVETRIM_2_MASK)

#define FLASH_NMPA_AUX_BIAS_CURVE_TEMP_1_VREF1VCURVETRIM_3_MASK (0xFFFF0000U)
#define FLASH_NMPA_AUX_BIAS_CURVE_TEMP_1_VREF1VCURVETRIM_3_SHIFT (16U)
/*! VREF1VCURVETRIM_3 - VREF1VCURVETRIM_3 (unit: 100uV) */
#define FLASH_NMPA_AUX_BIAS_CURVE_TEMP_1_VREF1VCURVETRIM_3(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_AUX_BIAS_CURVE_TEMP_1_VREF1VCURVETRIM_3_SHIFT)) & FLASH_NMPA_AUX_BIAS_CURVE_TEMP_1_VREF1VCURVETRIM_3_MASK)
/*! @} */

/*! @name AUX_BIAS_CURVE_TEMP_2 -  */
/*! @{ */

#define FLASH_NMPA_AUX_BIAS_CURVE_TEMP_2_VREF1VCURVETRIM_4_MASK (0xFFFFU)
#define FLASH_NMPA_AUX_BIAS_CURVE_TEMP_2_VREF1VCURVETRIM_4_SHIFT (0U)
/*! VREF1VCURVETRIM_4 - VREF1VCURVETRIM_4 (unit: 100uV) */
#define FLASH_NMPA_AUX_BIAS_CURVE_TEMP_2_VREF1VCURVETRIM_4(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_AUX_BIAS_CURVE_TEMP_2_VREF1VCURVETRIM_4_SHIFT)) & FLASH_NMPA_AUX_BIAS_CURVE_TEMP_2_VREF1VCURVETRIM_4_MASK)

#define FLASH_NMPA_AUX_BIAS_CURVE_TEMP_2_VREF1VCURVETRIM_5_MASK (0xFFFF0000U)
#define FLASH_NMPA_AUX_BIAS_CURVE_TEMP_2_VREF1VCURVETRIM_5_SHIFT (16U)
/*! VREF1VCURVETRIM_5 - VREF1VCURVETRIM_5 (unit: 100uV) */
#define FLASH_NMPA_AUX_BIAS_CURVE_TEMP_2_VREF1VCURVETRIM_5(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_AUX_BIAS_CURVE_TEMP_2_VREF1VCURVETRIM_5_SHIFT)) & FLASH_NMPA_AUX_BIAS_CURVE_TEMP_2_VREF1VCURVETRIM_5_MASK)
/*! @} */

/*! @name AUX_BIAS_CURVE_TEMP_3 -  */
/*! @{ */

#define FLASH_NMPA_AUX_BIAS_CURVE_TEMP_3_VREF1VCURVETRIM_6_MASK (0xFFFFU)
#define FLASH_NMPA_AUX_BIAS_CURVE_TEMP_3_VREF1VCURVETRIM_6_SHIFT (0U)
/*! VREF1VCURVETRIM_6 - VREF1VCURVETRIM_6 (unit: 100uV) */
#define FLASH_NMPA_AUX_BIAS_CURVE_TEMP_3_VREF1VCURVETRIM_6(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_AUX_BIAS_CURVE_TEMP_3_VREF1VCURVETRIM_6_SHIFT)) & FLASH_NMPA_AUX_BIAS_CURVE_TEMP_3_VREF1VCURVETRIM_6_MASK)

#define FLASH_NMPA_AUX_BIAS_CURVE_TEMP_3_VREF1VCURVETRIM_7_MASK (0xFFFF0000U)
#define FLASH_NMPA_AUX_BIAS_CURVE_TEMP_3_VREF1VCURVETRIM_7_SHIFT (16U)
/*! VREF1VCURVETRIM_7 - VREF1VCURVETRIM_7 (unit: 100uV) */
#define FLASH_NMPA_AUX_BIAS_CURVE_TEMP_3_VREF1VCURVETRIM_7(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_AUX_BIAS_CURVE_TEMP_3_VREF1VCURVETRIM_7_SHIFT)) & FLASH_NMPA_AUX_BIAS_CURVE_TEMP_3_VREF1VCURVETRIM_7_MASK)
/*! @} */

/*! @name AUX_BIAS_CURVE_TEMP_ARRAY - Aux Bias Curve TEMP (105degC) */
/*! @{ */

#define FLASH_NMPA_AUX_BIAS_CURVE_TEMP_ARRAY_FIELD_MASK (0xFFFFFFFFU)
#define FLASH_NMPA_AUX_BIAS_CURVE_TEMP_ARRAY_FIELD_SHIFT (0U)
#define FLASH_NMPA_AUX_BIAS_CURVE_TEMP_ARRAY_FIELD(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_AUX_BIAS_CURVE_TEMP_ARRAY_FIELD_SHIFT)) & FLASH_NMPA_AUX_BIAS_CURVE_TEMP_ARRAY_FIELD_MASK)
/*! @} */

/* The count of FLASH_NMPA_AUX_BIAS_CURVE_TEMP_ARRAY */
#define FLASH_NMPA_AUX_BIAS_CURVE_TEMP_ARRAY_COUNT (4U)

/*! @name TEMP_SENS_VBE1VBE8_REF_1 -  */
/*! @{ */

#define FLASH_NMPA_TEMP_SENS_VBE1VBE8_REF_1_VBE1_MASK (0xFFFFU)
#define FLASH_NMPA_TEMP_SENS_VBE1VBE8_REF_1_VBE1_SHIFT (0U)
#define FLASH_NMPA_TEMP_SENS_VBE1VBE8_REF_1_VBE1(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_TEMP_SENS_VBE1VBE8_REF_1_VBE1_SHIFT)) & FLASH_NMPA_TEMP_SENS_VBE1VBE8_REF_1_VBE1_MASK)

#define FLASH_NMPA_TEMP_SENS_VBE1VBE8_REF_1_VBE8_MASK (0xFFFF0000U)
#define FLASH_NMPA_TEMP_SENS_VBE1VBE8_REF_1_VBE8_SHIFT (16U)
#define FLASH_NMPA_TEMP_SENS_VBE1VBE8_REF_1_VBE8(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_TEMP_SENS_VBE1VBE8_REF_1_VBE8_SHIFT)) & FLASH_NMPA_TEMP_SENS_VBE1VBE8_REF_1_VBE8_MASK)
/*! @} */

/*! @name TEMP_SENS_VBE1VBE8_REF_2 -  */
/*! @{ */

#define FLASH_NMPA_TEMP_SENS_VBE1VBE8_REF_2_VBE1_MASK (0xFFFFU)
#define FLASH_NMPA_TEMP_SENS_VBE1VBE8_REF_2_VBE1_SHIFT (0U)
#define FLASH_NMPA_TEMP_SENS_VBE1VBE8_REF_2_VBE1(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_TEMP_SENS_VBE1VBE8_REF_2_VBE1_SHIFT)) & FLASH_NMPA_TEMP_SENS_VBE1VBE8_REF_2_VBE1_MASK)

#define FLASH_NMPA_TEMP_SENS_VBE1VBE8_REF_2_VBE8_MASK (0xFFFF0000U)
#define FLASH_NMPA_TEMP_SENS_VBE1VBE8_REF_2_VBE8_SHIFT (16U)
#define FLASH_NMPA_TEMP_SENS_VBE1VBE8_REF_2_VBE8(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_TEMP_SENS_VBE1VBE8_REF_2_VBE8_SHIFT)) & FLASH_NMPA_TEMP_SENS_VBE1VBE8_REF_2_VBE8_MASK)
/*! @} */

/*! @name TEMP_SENS_SLOPE -  */
/*! @{ */

#define FLASH_NMPA_TEMP_SENS_SLOPE_VALID_MASK    (0x1U)
#define FLASH_NMPA_TEMP_SENS_SLOPE_VALID_SHIFT   (0U)
#define FLASH_NMPA_TEMP_SENS_SLOPE_VALID(x)      (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_TEMP_SENS_SLOPE_VALID_SHIFT)) & FLASH_NMPA_TEMP_SENS_SLOPE_VALID_MASK)

#define FLASH_NMPA_TEMP_SENS_SLOPE_SLOPE_x1024_MASK (0xFFFFFFFEU)
#define FLASH_NMPA_TEMP_SENS_SLOPE_SLOPE_x1024_SHIFT (1U)
/*! SLOPE_x1024 - SLOPE_x1024[30:0] */
#define FLASH_NMPA_TEMP_SENS_SLOPE_SLOPE_x1024(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_TEMP_SENS_SLOPE_SLOPE_x1024_SHIFT)) & FLASH_NMPA_TEMP_SENS_SLOPE_SLOPE_x1024_MASK)
/*! @} */

/*! @name TEMP_SENS_OFFSET -  */
/*! @{ */

#define FLASH_NMPA_TEMP_SENS_OFFSET_VALID_MASK   (0x1U)
#define FLASH_NMPA_TEMP_SENS_OFFSET_VALID_SHIFT  (0U)
#define FLASH_NMPA_TEMP_SENS_OFFSET_VALID(x)     (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_TEMP_SENS_OFFSET_VALID_SHIFT)) & FLASH_NMPA_TEMP_SENS_OFFSET_VALID_MASK)

#define FLASH_NMPA_TEMP_SENS_OFFSET_OFFSET_x1024_MASK (0xFFFFFFFEU)
#define FLASH_NMPA_TEMP_SENS_OFFSET_OFFSET_x1024_SHIFT (1U)
/*! OFFSET_x1024 - OFFSET_x1024[30:0] */
#define FLASH_NMPA_TEMP_SENS_OFFSET_OFFSET_x1024(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_TEMP_SENS_OFFSET_OFFSET_x1024_SHIFT)) & FLASH_NMPA_TEMP_SENS_OFFSET_OFFSET_x1024_MASK)
/*! @} */

/*! @name PVT_MONITOR_0_RINGO -  */
/*! @{ */

#define FLASH_NMPA_PVT_MONITOR_0_RINGO_RINGO_VALID_MASK (0x1U)
#define FLASH_NMPA_PVT_MONITOR_0_RINGO_RINGO_VALID_SHIFT (0U)
#define FLASH_NMPA_PVT_MONITOR_0_RINGO_RINGO_VALID(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_PVT_MONITOR_0_RINGO_RINGO_VALID_SHIFT)) & FLASH_NMPA_PVT_MONITOR_0_RINGO_RINGO_VALID_MASK)

#define FLASH_NMPA_PVT_MONITOR_0_RINGO_RINGO_FREQ_HZ_MASK (0xFFFFFFFEU)
#define FLASH_NMPA_PVT_MONITOR_0_RINGO_RINGO_FREQ_HZ_SHIFT (1U)
#define FLASH_NMPA_PVT_MONITOR_0_RINGO_RINGO_FREQ_HZ(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_PVT_MONITOR_0_RINGO_RINGO_FREQ_HZ_SHIFT)) & FLASH_NMPA_PVT_MONITOR_0_RINGO_RINGO_FREQ_HZ_MASK)
/*! @} */

/*! @name PVT_MONITOR_0_DELAYS_LSB -  */
/*! @{ */

#define FLASH_NMPA_PVT_MONITOR_0_DELAYS_LSB_DELAY_VALID_MASK (0x1U)
#define FLASH_NMPA_PVT_MONITOR_0_DELAYS_LSB_DELAY_VALID_SHIFT (0U)
#define FLASH_NMPA_PVT_MONITOR_0_DELAYS_LSB_DELAY_VALID(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_PVT_MONITOR_0_DELAYS_LSB_DELAY_VALID_SHIFT)) & FLASH_NMPA_PVT_MONITOR_0_DELAYS_LSB_DELAY_VALID_MASK)

#define FLASH_NMPA_PVT_MONITOR_0_DELAYS_LSB_DELAY_0_MASK (0x7FEU)
#define FLASH_NMPA_PVT_MONITOR_0_DELAYS_LSB_DELAY_0_SHIFT (1U)
/*! DELAY_0 - Delay in us. */
#define FLASH_NMPA_PVT_MONITOR_0_DELAYS_LSB_DELAY_0(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_PVT_MONITOR_0_DELAYS_LSB_DELAY_0_SHIFT)) & FLASH_NMPA_PVT_MONITOR_0_DELAYS_LSB_DELAY_0_MASK)

#define FLASH_NMPA_PVT_MONITOR_0_DELAYS_LSB_DELAY_1_MASK (0x1FF800U)
#define FLASH_NMPA_PVT_MONITOR_0_DELAYS_LSB_DELAY_1_SHIFT (11U)
/*! DELAY_1 - Delay in us. */
#define FLASH_NMPA_PVT_MONITOR_0_DELAYS_LSB_DELAY_1(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_PVT_MONITOR_0_DELAYS_LSB_DELAY_1_SHIFT)) & FLASH_NMPA_PVT_MONITOR_0_DELAYS_LSB_DELAY_1_MASK)

#define FLASH_NMPA_PVT_MONITOR_0_DELAYS_LSB_DELAY_2_MASK (0x7FE00000U)
#define FLASH_NMPA_PVT_MONITOR_0_DELAYS_LSB_DELAY_2_SHIFT (21U)
/*! DELAY_2 - Delay in us. */
#define FLASH_NMPA_PVT_MONITOR_0_DELAYS_LSB_DELAY_2(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_PVT_MONITOR_0_DELAYS_LSB_DELAY_2_SHIFT)) & FLASH_NMPA_PVT_MONITOR_0_DELAYS_LSB_DELAY_2_MASK)
/*! @} */

/*! @name PVT_MONITOR_0_DELAYS_MSB -  */
/*! @{ */

#define FLASH_NMPA_PVT_MONITOR_0_DELAYS_MSB_DELAY_3_MASK (0x3FFU)
#define FLASH_NMPA_PVT_MONITOR_0_DELAYS_MSB_DELAY_3_SHIFT (0U)
/*! DELAY_3 - Delay in us. */
#define FLASH_NMPA_PVT_MONITOR_0_DELAYS_MSB_DELAY_3(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_PVT_MONITOR_0_DELAYS_MSB_DELAY_3_SHIFT)) & FLASH_NMPA_PVT_MONITOR_0_DELAYS_MSB_DELAY_3_MASK)

#define FLASH_NMPA_PVT_MONITOR_0_DELAYS_MSB_DELAY_4_MASK (0xFFC00U)
#define FLASH_NMPA_PVT_MONITOR_0_DELAYS_MSB_DELAY_4_SHIFT (10U)
/*! DELAY_4 - Delay in us. */
#define FLASH_NMPA_PVT_MONITOR_0_DELAYS_MSB_DELAY_4(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_PVT_MONITOR_0_DELAYS_MSB_DELAY_4_SHIFT)) & FLASH_NMPA_PVT_MONITOR_0_DELAYS_MSB_DELAY_4_MASK)

#define FLASH_NMPA_PVT_MONITOR_0_DELAYS_MSB_DELAY_5_MASK (0x3FF00000U)
#define FLASH_NMPA_PVT_MONITOR_0_DELAYS_MSB_DELAY_5_SHIFT (20U)
/*! DELAY_5 - Delay in us. */
#define FLASH_NMPA_PVT_MONITOR_0_DELAYS_MSB_DELAY_5(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_PVT_MONITOR_0_DELAYS_MSB_DELAY_5_SHIFT)) & FLASH_NMPA_PVT_MONITOR_0_DELAYS_MSB_DELAY_5_MASK)
/*! @} */

/*! @name PVT_MONITOR_0_ARRAY -  */
/*! @{ */

#define FLASH_NMPA_PVT_MONITOR_0_ARRAY_FIELD_MASK (0xFFFFFFFFU)
#define FLASH_NMPA_PVT_MONITOR_0_ARRAY_FIELD_SHIFT (0U)
#define FLASH_NMPA_PVT_MONITOR_0_ARRAY_FIELD(x)  (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_PVT_MONITOR_0_ARRAY_FIELD_SHIFT)) & FLASH_NMPA_PVT_MONITOR_0_ARRAY_FIELD_MASK)
/*! @} */

/* The count of FLASH_NMPA_PVT_MONITOR_0_ARRAY */
#define FLASH_NMPA_PVT_MONITOR_0_ARRAY_COUNT     (3U)

/*! @name PVT_MONITOR_1_RINGO -  */
/*! @{ */

#define FLASH_NMPA_PVT_MONITOR_1_RINGO_RINGO_VALID_MASK (0x1U)
#define FLASH_NMPA_PVT_MONITOR_1_RINGO_RINGO_VALID_SHIFT (0U)
#define FLASH_NMPA_PVT_MONITOR_1_RINGO_RINGO_VALID(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_PVT_MONITOR_1_RINGO_RINGO_VALID_SHIFT)) & FLASH_NMPA_PVT_MONITOR_1_RINGO_RINGO_VALID_MASK)

#define FLASH_NMPA_PVT_MONITOR_1_RINGO_RINGO_FREQ_HZ_MASK (0xFFFFFFFEU)
#define FLASH_NMPA_PVT_MONITOR_1_RINGO_RINGO_FREQ_HZ_SHIFT (1U)
#define FLASH_NMPA_PVT_MONITOR_1_RINGO_RINGO_FREQ_HZ(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_PVT_MONITOR_1_RINGO_RINGO_FREQ_HZ_SHIFT)) & FLASH_NMPA_PVT_MONITOR_1_RINGO_RINGO_FREQ_HZ_MASK)
/*! @} */

/*! @name PVT_MONITOR_1_DELAYS_LSB -  */
/*! @{ */

#define FLASH_NMPA_PVT_MONITOR_1_DELAYS_LSB_DELAY_VALID_MASK (0x1U)
#define FLASH_NMPA_PVT_MONITOR_1_DELAYS_LSB_DELAY_VALID_SHIFT (0U)
#define FLASH_NMPA_PVT_MONITOR_1_DELAYS_LSB_DELAY_VALID(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_PVT_MONITOR_1_DELAYS_LSB_DELAY_VALID_SHIFT)) & FLASH_NMPA_PVT_MONITOR_1_DELAYS_LSB_DELAY_VALID_MASK)

#define FLASH_NMPA_PVT_MONITOR_1_DELAYS_LSB_DELAY_0_MASK (0x7FEU)
#define FLASH_NMPA_PVT_MONITOR_1_DELAYS_LSB_DELAY_0_SHIFT (1U)
/*! DELAY_0 - Delay in us. */
#define FLASH_NMPA_PVT_MONITOR_1_DELAYS_LSB_DELAY_0(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_PVT_MONITOR_1_DELAYS_LSB_DELAY_0_SHIFT)) & FLASH_NMPA_PVT_MONITOR_1_DELAYS_LSB_DELAY_0_MASK)

#define FLASH_NMPA_PVT_MONITOR_1_DELAYS_LSB_DELAY_1_MASK (0x1FF800U)
#define FLASH_NMPA_PVT_MONITOR_1_DELAYS_LSB_DELAY_1_SHIFT (11U)
/*! DELAY_1 - Delay in us. */
#define FLASH_NMPA_PVT_MONITOR_1_DELAYS_LSB_DELAY_1(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_PVT_MONITOR_1_DELAYS_LSB_DELAY_1_SHIFT)) & FLASH_NMPA_PVT_MONITOR_1_DELAYS_LSB_DELAY_1_MASK)

#define FLASH_NMPA_PVT_MONITOR_1_DELAYS_LSB_DELAY_2_MASK (0x7FE00000U)
#define FLASH_NMPA_PVT_MONITOR_1_DELAYS_LSB_DELAY_2_SHIFT (21U)
/*! DELAY_2 - Delay in us. */
#define FLASH_NMPA_PVT_MONITOR_1_DELAYS_LSB_DELAY_2(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_PVT_MONITOR_1_DELAYS_LSB_DELAY_2_SHIFT)) & FLASH_NMPA_PVT_MONITOR_1_DELAYS_LSB_DELAY_2_MASK)
/*! @} */

/*! @name PVT_MONITOR_1_DELAYS_MSB -  */
/*! @{ */

#define FLASH_NMPA_PVT_MONITOR_1_DELAYS_MSB_DELAY_3_MASK (0x3FFU)
#define FLASH_NMPA_PVT_MONITOR_1_DELAYS_MSB_DELAY_3_SHIFT (0U)
/*! DELAY_3 - Delay in us. */
#define FLASH_NMPA_PVT_MONITOR_1_DELAYS_MSB_DELAY_3(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_PVT_MONITOR_1_DELAYS_MSB_DELAY_3_SHIFT)) & FLASH_NMPA_PVT_MONITOR_1_DELAYS_MSB_DELAY_3_MASK)

#define FLASH_NMPA_PVT_MONITOR_1_DELAYS_MSB_DELAY_4_MASK (0xFFC00U)
#define FLASH_NMPA_PVT_MONITOR_1_DELAYS_MSB_DELAY_4_SHIFT (10U)
/*! DELAY_4 - Delay in us. */
#define FLASH_NMPA_PVT_MONITOR_1_DELAYS_MSB_DELAY_4(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_PVT_MONITOR_1_DELAYS_MSB_DELAY_4_SHIFT)) & FLASH_NMPA_PVT_MONITOR_1_DELAYS_MSB_DELAY_4_MASK)

#define FLASH_NMPA_PVT_MONITOR_1_DELAYS_MSB_DELAY_5_MASK (0x3FF00000U)
#define FLASH_NMPA_PVT_MONITOR_1_DELAYS_MSB_DELAY_5_SHIFT (20U)
/*! DELAY_5 - Delay in us. */
#define FLASH_NMPA_PVT_MONITOR_1_DELAYS_MSB_DELAY_5(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_PVT_MONITOR_1_DELAYS_MSB_DELAY_5_SHIFT)) & FLASH_NMPA_PVT_MONITOR_1_DELAYS_MSB_DELAY_5_MASK)
/*! @} */

/*! @name PVT_MONITOR_1_ARRAY -  */
/*! @{ */

#define FLASH_NMPA_PVT_MONITOR_1_ARRAY_FIELD_MASK (0xFFFFFFFFU)
#define FLASH_NMPA_PVT_MONITOR_1_ARRAY_FIELD_SHIFT (0U)
#define FLASH_NMPA_PVT_MONITOR_1_ARRAY_FIELD(x)  (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_PVT_MONITOR_1_ARRAY_FIELD_SHIFT)) & FLASH_NMPA_PVT_MONITOR_1_ARRAY_FIELD_MASK)
/*! @} */

/* The count of FLASH_NMPA_PVT_MONITOR_1_ARRAY */
#define FLASH_NMPA_PVT_MONITOR_1_ARRAY_COUNT     (3U)

/*! @name NXP_DEVICE_PRIVATE_KEY -  */
/*! @{ */

#define FLASH_NMPA_NXP_DEVICE_PRIVATE_KEY_FIELD_MASK (0xFFFFFFFFU)
#define FLASH_NMPA_NXP_DEVICE_PRIVATE_KEY_FIELD_SHIFT (0U)
#define FLASH_NMPA_NXP_DEVICE_PRIVATE_KEY_FIELD(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_NXP_DEVICE_PRIVATE_KEY_FIELD_SHIFT)) & FLASH_NMPA_NXP_DEVICE_PRIVATE_KEY_FIELD_MASK)
/*! @} */

/*! @name NXP_DEVICE_CERTIFICATE_0 - NXP Device Certificate (ECDSA_sign - r[255:128]) */
/*! @{ */

#define FLASH_NMPA_NXP_DEVICE_CERTIFICATE_0_FIELD_MASK (0xFFFFFFFFU)
#define FLASH_NMPA_NXP_DEVICE_CERTIFICATE_0_FIELD_SHIFT (0U)
#define FLASH_NMPA_NXP_DEVICE_CERTIFICATE_0_FIELD(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_NXP_DEVICE_CERTIFICATE_0_FIELD_SHIFT)) & FLASH_NMPA_NXP_DEVICE_CERTIFICATE_0_FIELD_MASK)
/*! @} */

/*! @name NXP_DEVICE_CERTIFICATE_1 - NXP Device Certificate (ECDSA_sign - r[127:0]) */
/*! @{ */

#define FLASH_NMPA_NXP_DEVICE_CERTIFICATE_1_FIELD_MASK (0xFFFFFFFFU)
#define FLASH_NMPA_NXP_DEVICE_CERTIFICATE_1_FIELD_SHIFT (0U)
#define FLASH_NMPA_NXP_DEVICE_CERTIFICATE_1_FIELD(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_NXP_DEVICE_CERTIFICATE_1_FIELD_SHIFT)) & FLASH_NMPA_NXP_DEVICE_CERTIFICATE_1_FIELD_MASK)
/*! @} */

/*! @name NXP_DEVICE_CERTIFICATE_2 - NXP Device Certificate (ECDSA_sign - s[255:128]) */
/*! @{ */

#define FLASH_NMPA_NXP_DEVICE_CERTIFICATE_2_FIELD_MASK (0xFFFFFFFFU)
#define FLASH_NMPA_NXP_DEVICE_CERTIFICATE_2_FIELD_SHIFT (0U)
#define FLASH_NMPA_NXP_DEVICE_CERTIFICATE_2_FIELD(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_NXP_DEVICE_CERTIFICATE_2_FIELD_SHIFT)) & FLASH_NMPA_NXP_DEVICE_CERTIFICATE_2_FIELD_MASK)
/*! @} */

/*! @name NXP_DEVICE_CERTIFICATE_3 - NXP Device Certificate (ECDSA_sign - s[127:0]) */
/*! @{ */

#define FLASH_NMPA_NXP_DEVICE_CERTIFICATE_3_FIELD_MASK (0xFFFFFFFFU)
#define FLASH_NMPA_NXP_DEVICE_CERTIFICATE_3_FIELD_SHIFT (0U)
#define FLASH_NMPA_NXP_DEVICE_CERTIFICATE_3_FIELD(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_NXP_DEVICE_CERTIFICATE_3_FIELD_SHIFT)) & FLASH_NMPA_NXP_DEVICE_CERTIFICATE_3_FIELD_MASK)
/*! @} */

/*! @name SHA256_DIGEST - SHA-256 DIGEST (9EC00 - 9FDBC) ROM Patch Area + NXP Area (IMPORTANT NOTE: Pages used for Repair (N-8 to N-3) are excluded from the computation) SHA256_DIGEST0 for DIGEST[31:0]..SHA-256 DIGEST (9EC00 - 9FDBC) ROM Patch Area + NXP Area (IMPORTANT NOTE: Pages used for Repair (N-8 to N-3) are excluded from the computation) SHA256_DIGEST7 for DIGEST[255:224] */
/*! @{ */

#define FLASH_NMPA_SHA256_DIGEST_FIELD_MASK      (0xFFFFFFFFU)
#define FLASH_NMPA_SHA256_DIGEST_FIELD_SHIFT     (0U)
#define FLASH_NMPA_SHA256_DIGEST_FIELD(x)        (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_SHA256_DIGEST_FIELD_SHIFT)) & FLASH_NMPA_SHA256_DIGEST_FIELD_MASK)
/*! @} */

/*! @name ECID_BACKUP_0 -  */
/*! @{ */

#define FLASH_NMPA_ECID_BACKUP_0_COORD_Y_MASK    (0xFFFFU)
#define FLASH_NMPA_ECID_BACKUP_0_COORD_Y_SHIFT   (0U)
#define FLASH_NMPA_ECID_BACKUP_0_COORD_Y(x)      (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_ECID_BACKUP_0_COORD_Y_SHIFT)) & FLASH_NMPA_ECID_BACKUP_0_COORD_Y_MASK)

#define FLASH_NMPA_ECID_BACKUP_0_COORD_X_MASK    (0xFFFF0000U)
#define FLASH_NMPA_ECID_BACKUP_0_COORD_X_SHIFT   (16U)
#define FLASH_NMPA_ECID_BACKUP_0_COORD_X(x)      (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_ECID_BACKUP_0_COORD_X_SHIFT)) & FLASH_NMPA_ECID_BACKUP_0_COORD_X_MASK)
/*! @} */

/*! @name ECID_BACKUP_1 -  */
/*! @{ */

#define FLASH_NMPA_ECID_BACKUP_1_WAFER_MASK      (0xFFU)
#define FLASH_NMPA_ECID_BACKUP_1_WAFER_SHIFT     (0U)
#define FLASH_NMPA_ECID_BACKUP_1_WAFER(x)        (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_ECID_BACKUP_1_WAFER_SHIFT)) & FLASH_NMPA_ECID_BACKUP_1_WAFER_MASK)
/*! @} */

/*! @name ECID_BACKUP_2 -  */
/*! @{ */

#define FLASH_NMPA_ECID_BACKUP_2_LOTID_LSB_MASK  (0xFFFFFFFFU)
#define FLASH_NMPA_ECID_BACKUP_2_LOTID_LSB_SHIFT (0U)
#define FLASH_NMPA_ECID_BACKUP_2_LOTID_LSB(x)    (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_ECID_BACKUP_2_LOTID_LSB_SHIFT)) & FLASH_NMPA_ECID_BACKUP_2_LOTID_LSB_MASK)
/*! @} */

/*! @name ECID_BACKUP_3 -  */
/*! @{ */

#define FLASH_NMPA_ECID_BACKUP_3_LOTID_MSB_MASK  (0xFFFFFFFFU)
#define FLASH_NMPA_ECID_BACKUP_3_LOTID_MSB_SHIFT (0U)
#define FLASH_NMPA_ECID_BACKUP_3_LOTID_MSB(x)    (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_ECID_BACKUP_3_LOTID_MSB_SHIFT)) & FLASH_NMPA_ECID_BACKUP_3_LOTID_MSB_MASK)
/*! @} */

/*! @name ECID_BACKUP_ARRAY - ECID backup (the original is in page n-1) */
/*! @{ */

#define FLASH_NMPA_ECID_BACKUP_ARRAY_FIELD_MASK  (0xFFFFFFFFU)
#define FLASH_NMPA_ECID_BACKUP_ARRAY_FIELD_SHIFT (0U)
#define FLASH_NMPA_ECID_BACKUP_ARRAY_FIELD(x)    (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_ECID_BACKUP_ARRAY_FIELD_SHIFT)) & FLASH_NMPA_ECID_BACKUP_ARRAY_FIELD_MASK)
/*! @} */

/* The count of FLASH_NMPA_ECID_BACKUP_ARRAY */
#define FLASH_NMPA_ECID_BACKUP_ARRAY_COUNT       (4U)

/*! @name DIS_ROM_HIDING -  */
/*! @{ */

#define FLASH_NMPA_DIS_ROM_HIDING_DIS_ROM_HIDING_MASK (0xFFFFFFFFU)
#define FLASH_NMPA_DIS_ROM_HIDING_DIS_ROM_HIDING_SHIFT (0U)
/*! DIS_ROM_HIDING - When 0x3CC35AA5 ROM hiding feture is disabled. All other values critical ROM is hidden. */
#define FLASH_NMPA_DIS_ROM_HIDING_DIS_ROM_HIDING(x) (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_DIS_ROM_HIDING_DIS_ROM_HIDING_SHIFT)) & FLASH_NMPA_DIS_ROM_HIDING_DIS_ROM_HIDING_MASK)
/*! @} */

/*! @name PUF_SRAM -  */
/*! @{ */

#define FLASH_NMPA_PUF_SRAM_PUF_SRAM_VALID_MASK  (0x1U)
#define FLASH_NMPA_PUF_SRAM_PUF_SRAM_VALID_SHIFT (0U)
/*! PUF_SRAM_VALID - 1: PUF_SRAM is valid. */
#define FLASH_NMPA_PUF_SRAM_PUF_SRAM_VALID(x)    (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_PUF_SRAM_PUF_SRAM_VALID_SHIFT)) & FLASH_NMPA_PUF_SRAM_PUF_SRAM_VALID_MASK)

#define FLASH_NMPA_PUF_SRAM_mode_MASK            (0x2U)
#define FLASH_NMPA_PUF_SRAM_mode_SHIFT           (1U)
/*! mode - PUF SRAM Controller operating mode */
#define FLASH_NMPA_PUF_SRAM_mode(x)              (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_PUF_SRAM_mode_SHIFT)) & FLASH_NMPA_PUF_SRAM_mode_MASK)

#define FLASH_NMPA_PUF_SRAM_ckgating_MASK        (0x4U)
#define FLASH_NMPA_PUF_SRAM_ckgating_SHIFT       (2U)
/*! ckgating - PUF SRAM Clock Gating control */
#define FLASH_NMPA_PUF_SRAM_ckgating(x)          (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_PUF_SRAM_ckgating_SHIFT)) & FLASH_NMPA_PUF_SRAM_ckgating_MASK)

#define FLASH_NMPA_PUF_SRAM_SMB_MASK             (0x300U)
#define FLASH_NMPA_PUF_SRAM_SMB_SHIFT            (8U)
/*! SMB - Source Biasing voltage.
 *  0b00..Low leakage.
 *  0b01..Medium leakage.
 *  0b10..Highest leakage.
 *  0b11..Disable.
 */
#define FLASH_NMPA_PUF_SRAM_SMB(x)               (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_PUF_SRAM_SMB_SHIFT)) & FLASH_NMPA_PUF_SRAM_SMB_MASK)

#define FLASH_NMPA_PUF_SRAM_RM_MASK              (0x1C00U)
#define FLASH_NMPA_PUF_SRAM_RM_SHIFT             (10U)
/*! RM - Read Margin control settings. */
#define FLASH_NMPA_PUF_SRAM_RM(x)                (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_PUF_SRAM_RM_SHIFT)) & FLASH_NMPA_PUF_SRAM_RM_MASK)

#define FLASH_NMPA_PUF_SRAM_WM_MASK              (0xE000U)
#define FLASH_NMPA_PUF_SRAM_WM_SHIFT             (13U)
/*! WM - Write Margin control settings. */
#define FLASH_NMPA_PUF_SRAM_WM(x)                (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_PUF_SRAM_WM_SHIFT)) & FLASH_NMPA_PUF_SRAM_WM_MASK)

#define FLASH_NMPA_PUF_SRAM_WRME_MASK            (0x10000U)
#define FLASH_NMPA_PUF_SRAM_WRME_SHIFT           (16U)
/*! WRME - Write read margin enable. */
#define FLASH_NMPA_PUF_SRAM_WRME(x)              (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_PUF_SRAM_WRME_SHIFT)) & FLASH_NMPA_PUF_SRAM_WRME_MASK)

#define FLASH_NMPA_PUF_SRAM_RAEN_MASK            (0x20000U)
#define FLASH_NMPA_PUF_SRAM_RAEN_SHIFT           (17U)
/*! RAEN - SRAM Read Assist Enable */
#define FLASH_NMPA_PUF_SRAM_RAEN(x)              (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_PUF_SRAM_RAEN_SHIFT)) & FLASH_NMPA_PUF_SRAM_RAEN_MASK)

#define FLASH_NMPA_PUF_SRAM_RAM_MASK             (0x3C0000U)
#define FLASH_NMPA_PUF_SRAM_RAM_SHIFT            (18U)
/*! RAM - SRAM Read Assist settings */
#define FLASH_NMPA_PUF_SRAM_RAM(x)               (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_PUF_SRAM_RAM_SHIFT)) & FLASH_NMPA_PUF_SRAM_RAM_MASK)

#define FLASH_NMPA_PUF_SRAM_WAEN_MASK            (0x400000U)
#define FLASH_NMPA_PUF_SRAM_WAEN_SHIFT           (22U)
/*! WAEN - SRAM Write Assist Enable */
#define FLASH_NMPA_PUF_SRAM_WAEN(x)              (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_PUF_SRAM_WAEN_SHIFT)) & FLASH_NMPA_PUF_SRAM_WAEN_MASK)

#define FLASH_NMPA_PUF_SRAM_WAM_MASK             (0x1800000U)
#define FLASH_NMPA_PUF_SRAM_WAM_SHIFT            (23U)
/*! WAM - SRAM Write Assist settings */
#define FLASH_NMPA_PUF_SRAM_WAM(x)               (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_PUF_SRAM_WAM_SHIFT)) & FLASH_NMPA_PUF_SRAM_WAM_MASK)

#define FLASH_NMPA_PUF_SRAM_STBP_MASK            (0x2000000U)
#define FLASH_NMPA_PUF_SRAM_STBP_SHIFT           (25U)
/*! STBP - STBP */
#define FLASH_NMPA_PUF_SRAM_STBP(x)              (((uint32_t)(((uint32_t)(x)) << FLASH_NMPA_PUF_SRAM_STBP_SHIFT)) & FLASH_NMPA_PUF_SRAM_STBP_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group FLASH_NMPA_Register_Masks */


/*!
 * @}
 */ /* end of group FLASH_NMPA_Peripheral_Access_Layer */


/*
** End of section using anonymous unions
*/

#if defined(__ARMCC_VERSION)
  #if (__ARMCC_VERSION >= 6010050)
    #pragma clang diagnostic pop
  #else
    #pragma pop
  #endif
#elif defined(__GNUC__)
  /* leave anonymous unions enabled */
#elif defined(__IAR_SYSTEMS_ICC__)
  #pragma language=default
#else
  #error Not supported compiler type
#endif

/*!
 * @}
 */ /* end of group Peripheral_access_layer */


#endif  /* FLASH_NMPA_H_ */

