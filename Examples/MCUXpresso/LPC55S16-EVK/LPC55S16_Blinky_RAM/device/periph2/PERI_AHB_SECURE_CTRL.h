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
**         CMSIS Peripheral Access Layer for AHB_SECURE_CTRL
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
 * @file AHB_SECURE_CTRL.h
 * @version 1.1
 * @date 2019-12-03
 * @brief CMSIS Peripheral Access Layer for AHB_SECURE_CTRL
 *
 * CMSIS Peripheral Access Layer for AHB_SECURE_CTRL
 */

#if !defined(AHB_SECURE_CTRL_H_)
#define AHB_SECURE_CTRL_H_                       /**< Symbol preventing repeated inclusion */

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
   -- AHB_SECURE_CTRL Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup AHB_SECURE_CTRL_Peripheral_Access_Layer AHB_SECURE_CTRL Peripheral Access Layer
 * @{
 */

/** AHB_SECURE_CTRL - Size of Registers Arrays */
#define AHB_SECURE_CTRL_SEC_CTRL_FLASH_ROM_SEC_CTRL_FLASH_MEM_RULE_COUNT 1u
#define AHB_SECURE_CTRL_SEC_CTRL_FLASH_ROM_SEC_CTRL_ROM_MEM_RULE_COUNT 4u
#define AHB_SECURE_CTRL_SEC_CTRL_FLASH_ROM_COUNT  1u
#define AHB_SECURE_CTRL_SEC_CTRL_RAMX_SEC_CTRL_RAMX_MEM_RULE_COUNT 1u
#define AHB_SECURE_CTRL_SEC_CTRL_RAMX_COUNT       1u
#define AHB_SECURE_CTRL_SEC_CTRL_RAM0_SEC_CTRL_RAM0_MEM_RULE_COUNT 1u
#define AHB_SECURE_CTRL_SEC_CTRL_RAM0_COUNT       1u
#define AHB_SECURE_CTRL_SEC_CTRL_RAM1_SEC_CTRL_RAM1_MEM_RULE_COUNT 1u
#define AHB_SECURE_CTRL_SEC_CTRL_RAM1_COUNT       1u
#define AHB_SECURE_CTRL_SEC_CTRL_RAM2_SEC_CTRL_RAM2_MEM_RULE_COUNT 1u
#define AHB_SECURE_CTRL_SEC_CTRL_RAM2_COUNT       1u
#define AHB_SECURE_CTRL_SEC_CTRL_USB_HS_SEC_CTRL_USB_HS_MEM_RULE_COUNT 1u
#define AHB_SECURE_CTRL_SEC_CTRL_USB_HS_COUNT     1u
#define AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE_COUNT 1u
#define AHB_SECURE_CTRL_SEC_CTRL_AHB_PORT9_SEC_CTRL_AHB_SEC_CTRL_MEM_RULE_COUNT 1u
#define AHB_SECURE_CTRL_SEC_CTRL_AHB_PORT9_COUNT  1u
#define AHB_SECURE_CTRL_SEC_VIO_ADDR_COUNT        10u
#define AHB_SECURE_CTRL_SEC_VIO_MISC_INFO_COUNT   10u

/** AHB_SECURE_CTRL - Register Layout Typedef */
typedef struct {
  struct {                                         /* offset: 0x0, array step: 0x30 */
    __IO uint32_t SLAVE_RULE;                        /**< Security access rules for Flash and ROM slaves., array offset: 0x0, array step: 0x30 */
         uint8_t RESERVED_0[12];
    __IO uint32_t SEC_CTRL_FLASH_MEM_RULE[AHB_SECURE_CTRL_SEC_CTRL_FLASH_ROM_SEC_CTRL_FLASH_MEM_RULE_COUNT];   /**< Security access rules for FLASH sector 0 to sector 7. Each Flash sector is 32 Kbytes. There are 8 FLASH sectors in total., array offset: 0x10, array step: index*0x30, index2*0x4 */
         uint8_t RESERVED_1[12];
    __IO uint32_t SEC_CTRL_ROM_MEM_RULE[AHB_SECURE_CTRL_SEC_CTRL_FLASH_ROM_SEC_CTRL_ROM_MEM_RULE_COUNT];   /**< Security access rules for ROM sector 0 to sector 31. Each ROM sector is 4 Kbytes. There are 32 ROM sectors in total., array offset: 0x20, array step: index*0x30, index2*0x4 */
  } SEC_CTRL_FLASH_ROM[AHB_SECURE_CTRL_SEC_CTRL_FLASH_ROM_COUNT];
  struct {                                         /* offset: 0x30, array step: 0x14 */
    __IO uint32_t SLAVE_RULE;                        /**< Security access rules for RAMX slaves., array offset: 0x30, array step: 0x14 */
         uint8_t RESERVED_0[12];
    __IO uint32_t MEM_RULE[AHB_SECURE_CTRL_SEC_CTRL_RAMX_SEC_CTRL_RAMX_MEM_RULE_COUNT];   /**< Security access rules for RAMX slaves., array offset: 0x40, array step: index*0x14, index2*0x4 */
  } SEC_CTRL_RAMX[AHB_SECURE_CTRL_SEC_CTRL_RAMX_COUNT];
       uint8_t RESERVED_0[12];
  struct {                                         /* offset: 0x50, array step: 0x14 */
    __IO uint32_t SLAVE_RULE;                        /**< Security access rules for RAM0 slaves., array offset: 0x50, array step: 0x14 */
         uint8_t RESERVED_0[12];
    __IO uint32_t MEM_RULE[AHB_SECURE_CTRL_SEC_CTRL_RAM0_SEC_CTRL_RAM0_MEM_RULE_COUNT];   /**< Security access rules for RAM0 slaves., array offset: 0x60, array step: index*0x14, index2*0x4 */
  } SEC_CTRL_RAM0[AHB_SECURE_CTRL_SEC_CTRL_RAM0_COUNT];
       uint8_t RESERVED_1[12];
  struct {                                         /* offset: 0x70, array step: 0x14 */
    __IO uint32_t SLAVE_RULE;                        /**< Security access rules for RAM1 slaves., array offset: 0x70, array step: 0x14 */
         uint8_t RESERVED_0[12];
    __IO uint32_t MEM_RULE[AHB_SECURE_CTRL_SEC_CTRL_RAM1_SEC_CTRL_RAM1_MEM_RULE_COUNT];   /**< Security access rules for RAM1 slaves., array offset: 0x80, array step: index*0x14, index2*0x4 */
  } SEC_CTRL_RAM1[AHB_SECURE_CTRL_SEC_CTRL_RAM1_COUNT];
       uint8_t RESERVED_2[12];
  struct {                                         /* offset: 0x90, array step: 0x14 */
    __IO uint32_t SLAVE_RULE;                        /**< Security access rules for RAM2 slaves., array offset: 0x90, array step: 0x14 */
         uint8_t RESERVED_0[12];
    __IO uint32_t MEM_RULE[AHB_SECURE_CTRL_SEC_CTRL_RAM2_SEC_CTRL_RAM2_MEM_RULE_COUNT];   /**< Security access rules for RAM2 slaves., array offset: 0xA0, array step: index*0x14, index2*0x4 */
  } SEC_CTRL_RAM2[AHB_SECURE_CTRL_SEC_CTRL_RAM2_COUNT];
       uint8_t RESERVED_3[12];
  struct {                                         /* offset: 0xB0, array step: 0x14 */
    __IO uint32_t SLAVE_RULE;                        /**< Security access rules for USB High speed RAM slaves., array offset: 0xB0, array step: 0x14 */
         uint8_t RESERVED_0[12];
    __IO uint32_t MEM_RULE[AHB_SECURE_CTRL_SEC_CTRL_USB_HS_SEC_CTRL_USB_HS_MEM_RULE_COUNT];   /**< Security access rules for RAM_USB_HS., array offset: 0xC0, array step: index*0x14, index2*0x4 */
  } SEC_CTRL_USB_HS[AHB_SECURE_CTRL_SEC_CTRL_USB_HS_COUNT];
       uint8_t RESERVED_4[12];
  struct {                                         /* offset: 0xD0, array step: 0x30 */
    __IO uint32_t SLAVE_RULE;                        /**< Security access rules for both APB Bridges slaves., array offset: 0xD0, array step: 0x30 */
         uint8_t RESERVED_0[12];
    __IO uint32_t SEC_CTRL_APB_BRIDGE0_MEM_CTRL0;    /**< Security access rules for APB Bridge 0 peripherals. Each APB bridge sector is 4 Kbytes. There are 32 APB Bridge 0 sectors in total., array offset: 0xE0, array step: 0x30 */
    __IO uint32_t SEC_CTRL_APB_BRIDGE0_MEM_CTRL1;    /**< Security access rules for APB Bridge 0 peripherals. Each APB bridge sector is 4 Kbytes. There are 32 APB Bridge 0 sectors in total., array offset: 0xE4, array step: 0x30 */
    __IO uint32_t SEC_CTRL_APB_BRIDGE0_MEM_CTRL2;    /**< Security access rules for APB Bridge 0 peripherals. Each APB bridge sector is 4 Kbytes. There are 32 APB Bridge 0 sectors in total., array offset: 0xE8, array step: 0x30 */
         uint8_t RESERVED_1[4];
    __IO uint32_t SEC_CTRL_APB_BRIDGE1_MEM_CTRL0;    /**< Security access rules for APB Bridge 1 peripherals. Each APB bridge sector is 4 Kbytes. There are 32 APB Bridge 1 sectors in total., array offset: 0xF0, array step: 0x30 */
    __IO uint32_t SEC_CTRL_APB_BRIDGE1_MEM_CTRL1;    /**< Security access rules for APB Bridge 1 peripherals. Each APB bridge sector is 4 Kbytes. There are 32 APB Bridge 1 sectors in total., array offset: 0xF4, array step: 0x30 */
    __IO uint32_t SEC_CTRL_APB_BRIDGE1_MEM_CTRL2;    /**< Security access rules for APB Bridge 1 peripherals. Each APB bridge sector is 4 Kbytes. There are 32 APB Bridge 1 sectors in total., array offset: 0xF8, array step: 0x30 */
    __IO uint32_t SEC_CTRL_APB_BRIDGE1_MEM_CTRL3;    /**< Security access rules for APB Bridge 1 peripherals. Each APB bridge sector is 4 Kbytes. There are 32 APB Bridge 1 sectors in total., array offset: 0xFC, array step: 0x30 */
  } SEC_CTRL_APB_BRIDGE[AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE_COUNT];
  __IO uint32_t SEC_CTRL_AHB_PORT7_SLAVE0_RULE;    /**< Security access rules for AHB peripherals., offset: 0x100 */
  __IO uint32_t SEC_CTRL_AHB_PORT7_SLAVE1_RULE;    /**< Security access rules for AHB peripherals., offset: 0x104 */
       uint8_t RESERVED_5[8];
  __IO uint32_t SEC_CTRL_AHB_PORT8_SLAVE0_RULE;    /**< Security access rules for AHB peripherals., offset: 0x110 */
  __IO uint32_t SEC_CTRL_AHB_PORT8_SLAVE1_RULE;    /**< Security access rules for AHB peripherals., offset: 0x114 */
       uint8_t RESERVED_6[8];
  struct {                                         /* offset: 0x120, array step: 0x14 */
    __IO uint32_t SLAVE0_RULE;                       /**< Security access rules for AHB peripherals., array offset: 0x120, array step: 0x14 */
    __IO uint32_t SLAVE1_RULE;                       /**< Security access rules for AHB peripherals., array offset: 0x124, array step: 0x14 */
         uint8_t RESERVED_0[8];
    __IO uint32_t SEC_CTRL_AHB_SEC_CTRL_MEM_RULE[AHB_SECURE_CTRL_SEC_CTRL_AHB_PORT9_SEC_CTRL_AHB_SEC_CTRL_MEM_RULE_COUNT];   /**< Security access rules for AHB_SEC_CTRL_AHB., array offset: 0x130, array step: index*0x14, index2*0x4 */
  } SEC_CTRL_AHB_PORT9[AHB_SECURE_CTRL_SEC_CTRL_AHB_PORT9_COUNT];
       uint8_t RESERVED_7[3276];
  __I  uint32_t SEC_VIO_ADDR[AHB_SECURE_CTRL_SEC_VIO_ADDR_COUNT]; /**< most recent security violation address for AHB layer n, array offset: 0xE00, array step: 0x4 */
       uint8_t RESERVED_8[88];
  __I  uint32_t SEC_VIO_MISC_INFO[AHB_SECURE_CTRL_SEC_VIO_MISC_INFO_COUNT]; /**< most recent security violation miscellaneous information for AHB layer n, array offset: 0xE80, array step: 0x4 */
       uint8_t RESERVED_9[88];
  __IO uint32_t SEC_VIO_INFO_VALID;                /**< security violation address/information registers valid flags, offset: 0xF00 */
       uint8_t RESERVED_10[124];
  __IO uint32_t SEC_GPIO_MASK0;                    /**< Secure GPIO mask for port 0 pins., offset: 0xF80 */
  __IO uint32_t SEC_GPIO_MASK1;                    /**< Secure GPIO mask for port 1 pins., offset: 0xF84 */
       uint8_t RESERVED_11[52];
  __IO uint32_t SEC_MASK_LOCK;                     /**< Security General Purpose register access control., offset: 0xFBC */
       uint8_t RESERVED_12[16];
  __IO uint32_t MASTER_SEC_LEVEL;                  /**< master secure level register, offset: 0xFD0 */
  __IO uint32_t MASTER_SEC_ANTI_POL_REG;           /**< master secure level anti-pole register, offset: 0xFD4 */
       uint8_t RESERVED_13[20];
  __IO uint32_t CPU0_LOCK_REG;                     /**< Miscalleneous control signals for in Cortex M33 (CPU0), offset: 0xFEC */
       uint8_t RESERVED_14[8];
  __IO uint32_t MISC_CTRL_DP_REG;                  /**< secure control duplicate register, offset: 0xFF8 */
  __IO uint32_t MISC_CTRL_REG;                     /**< secure control register, offset: 0xFFC */
} AHB_SECURE_CTRL_Type;

/* ----------------------------------------------------------------------------
   -- AHB_SECURE_CTRL Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup AHB_SECURE_CTRL_Register_Masks AHB_SECURE_CTRL Register Masks
 * @{
 */

/*! @name SEC_CTRL_FLASH_ROM_SLAVE_RULE - Security access rules for Flash and ROM slaves. */
/*! @{ */

#define AHB_SECURE_CTRL_SEC_CTRL_FLASH_ROM_SLAVE_RULE_FLASH_RULE_MASK (0x3U)
#define AHB_SECURE_CTRL_SEC_CTRL_FLASH_ROM_SLAVE_RULE_FLASH_RULE_SHIFT (0U)
/*! FLASH_RULE - Security access rules for the whole FLASH : 0x0000_0000 - 0x0003_FFFF
 *  0b00..Non-secure and Non-priviledge user access allowed.
 *  0b01..Non-secure and Privilege access allowed.
 *  0b10..Secure and Non-priviledge user access allowed.
 *  0b11..Secure and Priviledge user access allowed.
 */
#define AHB_SECURE_CTRL_SEC_CTRL_FLASH_ROM_SLAVE_RULE_FLASH_RULE(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_CTRL_FLASH_ROM_SLAVE_RULE_FLASH_RULE_SHIFT)) & AHB_SECURE_CTRL_SEC_CTRL_FLASH_ROM_SLAVE_RULE_FLASH_RULE_MASK)

#define AHB_SECURE_CTRL_SEC_CTRL_FLASH_ROM_SLAVE_RULE_ROM_RULE_MASK (0x30U)
#define AHB_SECURE_CTRL_SEC_CTRL_FLASH_ROM_SLAVE_RULE_ROM_RULE_SHIFT (4U)
/*! ROM_RULE - Security access rules for the whole ROM : 0x0300_0000 - 0x0301_FFFF
 *  0b00..Non-secure and Non-priviledge user access allowed.
 *  0b01..Non-secure and Privilege access allowed.
 *  0b10..Secure and Non-priviledge user access allowed.
 *  0b11..Secure and Priviledge user access allowed.
 */
#define AHB_SECURE_CTRL_SEC_CTRL_FLASH_ROM_SLAVE_RULE_ROM_RULE(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_CTRL_FLASH_ROM_SLAVE_RULE_ROM_RULE_SHIFT)) & AHB_SECURE_CTRL_SEC_CTRL_FLASH_ROM_SLAVE_RULE_ROM_RULE_MASK)
/*! @} */

/* The count of AHB_SECURE_CTRL_SEC_CTRL_FLASH_ROM_SLAVE_RULE */
#define AHB_SECURE_CTRL_SEC_CTRL_FLASH_ROM_SLAVE_RULE_COUNT (1U)

/*! @name SEC_CTRL_FLASH_MEM_RULE - Security access rules for FLASH sector 0 to sector 7. Each Flash sector is 32 Kbytes. There are 8 FLASH sectors in total. */
/*! @{ */

#define AHB_SECURE_CTRL_SEC_CTRL_FLASH_MEM_RULE_RULE0_MASK (0x3U)
#define AHB_SECURE_CTRL_SEC_CTRL_FLASH_MEM_RULE_RULE0_SHIFT (0U)
/*! RULE0 - secure control rule0. it can be set when check_reg's write_lock is '0'
 *  0b00..Non-secure and Non-priviledge user access allowed.
 *  0b01..Non-secure and Privilege access allowed.
 *  0b10..Secure and Non-priviledge user access allowed.
 *  0b11..Secure and Priviledge user access allowed.
 */
#define AHB_SECURE_CTRL_SEC_CTRL_FLASH_MEM_RULE_RULE0(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_CTRL_FLASH_MEM_RULE_RULE0_SHIFT)) & AHB_SECURE_CTRL_SEC_CTRL_FLASH_MEM_RULE_RULE0_MASK)

#define AHB_SECURE_CTRL_SEC_CTRL_FLASH_MEM_RULE_RULE1_MASK (0x30U)
#define AHB_SECURE_CTRL_SEC_CTRL_FLASH_MEM_RULE_RULE1_SHIFT (4U)
/*! RULE1 - secure control rule1. it can be set when check_reg's write_lock is '0'
 *  0b00..Non-secure and Non-priviledge user access allowed.
 *  0b01..Non-secure and Privilege access allowed.
 *  0b10..Secure and Non-priviledge user access allowed.
 *  0b11..Secure and Priviledge user access allowed.
 */
#define AHB_SECURE_CTRL_SEC_CTRL_FLASH_MEM_RULE_RULE1(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_CTRL_FLASH_MEM_RULE_RULE1_SHIFT)) & AHB_SECURE_CTRL_SEC_CTRL_FLASH_MEM_RULE_RULE1_MASK)

#define AHB_SECURE_CTRL_SEC_CTRL_FLASH_MEM_RULE_RULE2_MASK (0x300U)
#define AHB_SECURE_CTRL_SEC_CTRL_FLASH_MEM_RULE_RULE2_SHIFT (8U)
/*! RULE2 - secure control rule2. it can be set when check_reg's write_lock is '0'
 *  0b00..Non-secure and Non-priviledge user access allowed.
 *  0b01..Non-secure and Privilege access allowed.
 *  0b10..Secure and Non-priviledge user access allowed.
 *  0b11..Secure and Priviledge user access allowed.
 */
#define AHB_SECURE_CTRL_SEC_CTRL_FLASH_MEM_RULE_RULE2(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_CTRL_FLASH_MEM_RULE_RULE2_SHIFT)) & AHB_SECURE_CTRL_SEC_CTRL_FLASH_MEM_RULE_RULE2_MASK)

#define AHB_SECURE_CTRL_SEC_CTRL_FLASH_MEM_RULE_RULE3_MASK (0x3000U)
#define AHB_SECURE_CTRL_SEC_CTRL_FLASH_MEM_RULE_RULE3_SHIFT (12U)
/*! RULE3 - secure control rule3. it can be set when check_reg's write_lock is '0'
 *  0b00..Non-secure and Non-priviledge user access allowed.
 *  0b01..Non-secure and Privilege access allowed.
 *  0b10..Secure and Non-priviledge user access allowed.
 *  0b11..Secure and Priviledge user access allowed.
 */
#define AHB_SECURE_CTRL_SEC_CTRL_FLASH_MEM_RULE_RULE3(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_CTRL_FLASH_MEM_RULE_RULE3_SHIFT)) & AHB_SECURE_CTRL_SEC_CTRL_FLASH_MEM_RULE_RULE3_MASK)

#define AHB_SECURE_CTRL_SEC_CTRL_FLASH_MEM_RULE_RULE4_MASK (0x30000U)
#define AHB_SECURE_CTRL_SEC_CTRL_FLASH_MEM_RULE_RULE4_SHIFT (16U)
/*! RULE4 - secure control rule4. it can be set when check_reg's write_lock is '0'
 *  0b00..Non-secure and Non-priviledge user access allowed.
 *  0b01..Non-secure and Privilege access allowed.
 *  0b10..Secure and Non-priviledge user access allowed.
 *  0b11..Secure and Priviledge user access allowed.
 */
#define AHB_SECURE_CTRL_SEC_CTRL_FLASH_MEM_RULE_RULE4(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_CTRL_FLASH_MEM_RULE_RULE4_SHIFT)) & AHB_SECURE_CTRL_SEC_CTRL_FLASH_MEM_RULE_RULE4_MASK)

#define AHB_SECURE_CTRL_SEC_CTRL_FLASH_MEM_RULE_RULE5_MASK (0x300000U)
#define AHB_SECURE_CTRL_SEC_CTRL_FLASH_MEM_RULE_RULE5_SHIFT (20U)
/*! RULE5 - secure control rule5. it can be set when check_reg's write_lock is '0'
 *  0b00..Non-secure and Non-priviledge user access allowed.
 *  0b01..Non-secure and Privilege access allowed.
 *  0b10..Secure and Non-priviledge user access allowed.
 *  0b11..Secure and Priviledge user access allowed.
 */
#define AHB_SECURE_CTRL_SEC_CTRL_FLASH_MEM_RULE_RULE5(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_CTRL_FLASH_MEM_RULE_RULE5_SHIFT)) & AHB_SECURE_CTRL_SEC_CTRL_FLASH_MEM_RULE_RULE5_MASK)

#define AHB_SECURE_CTRL_SEC_CTRL_FLASH_MEM_RULE_RULE6_MASK (0x3000000U)
#define AHB_SECURE_CTRL_SEC_CTRL_FLASH_MEM_RULE_RULE6_SHIFT (24U)
/*! RULE6 - secure control rule6. it can be set when check_reg's write_lock is '0'
 *  0b00..Non-secure and Non-priviledge user access allowed.
 *  0b01..Non-secure and Privilege access allowed.
 *  0b10..Secure and Non-priviledge user access allowed.
 *  0b11..Secure and Priviledge user access allowed.
 */
#define AHB_SECURE_CTRL_SEC_CTRL_FLASH_MEM_RULE_RULE6(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_CTRL_FLASH_MEM_RULE_RULE6_SHIFT)) & AHB_SECURE_CTRL_SEC_CTRL_FLASH_MEM_RULE_RULE6_MASK)

#define AHB_SECURE_CTRL_SEC_CTRL_FLASH_MEM_RULE_RULE7_MASK (0x30000000U)
#define AHB_SECURE_CTRL_SEC_CTRL_FLASH_MEM_RULE_RULE7_SHIFT (28U)
/*! RULE7 - secure control rule7. it can be set when check_reg's write_lock is '0'
 *  0b00..Non-secure and Non-priviledge user access allowed.
 *  0b01..Non-secure and Privilege access allowed.
 *  0b10..Secure and Non-priviledge user access allowed.
 *  0b11..Secure and Priviledge user access allowed.
 */
#define AHB_SECURE_CTRL_SEC_CTRL_FLASH_MEM_RULE_RULE7(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_CTRL_FLASH_MEM_RULE_RULE7_SHIFT)) & AHB_SECURE_CTRL_SEC_CTRL_FLASH_MEM_RULE_RULE7_MASK)
/*! @} */

/* The count of AHB_SECURE_CTRL_SEC_CTRL_FLASH_MEM_RULE */
#define AHB_SECURE_CTRL_SEC_CTRL_FLASH_MEM_RULE_COUNT (1U)

/* The count of AHB_SECURE_CTRL_SEC_CTRL_FLASH_MEM_RULE */
#define AHB_SECURE_CTRL_SEC_CTRL_FLASH_MEM_RULE_COUNT2 (1U)

/*! @name SEC_CTRL_ROM_MEM_RULE - Security access rules for ROM sector 0 to sector 31. Each ROM sector is 4 Kbytes. There are 32 ROM sectors in total. */
/*! @{ */

#define AHB_SECURE_CTRL_SEC_CTRL_ROM_MEM_RULE_RULE0_MASK (0x3U)
#define AHB_SECURE_CTRL_SEC_CTRL_ROM_MEM_RULE_RULE0_SHIFT (0U)
/*! RULE0 - secure control rule0. it can be set when check_reg's write_lock is '0'
 *  0b00..Non-secure and Non-priviledge user access allowed.
 *  0b01..Non-secure and Privilege access allowed.
 *  0b10..Secure and Non-priviledge user access allowed.
 *  0b11..Secure and Priviledge user access allowed.
 */
#define AHB_SECURE_CTRL_SEC_CTRL_ROM_MEM_RULE_RULE0(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_CTRL_ROM_MEM_RULE_RULE0_SHIFT)) & AHB_SECURE_CTRL_SEC_CTRL_ROM_MEM_RULE_RULE0_MASK)

#define AHB_SECURE_CTRL_SEC_CTRL_ROM_MEM_RULE_RULE1_MASK (0x30U)
#define AHB_SECURE_CTRL_SEC_CTRL_ROM_MEM_RULE_RULE1_SHIFT (4U)
/*! RULE1 - secure control rule1. it can be set when check_reg's write_lock is '0'
 *  0b00..Non-secure and Non-priviledge user access allowed.
 *  0b01..Non-secure and Privilege access allowed.
 *  0b10..Secure and Non-priviledge user access allowed.
 *  0b11..Secure and Priviledge user access allowed.
 */
#define AHB_SECURE_CTRL_SEC_CTRL_ROM_MEM_RULE_RULE1(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_CTRL_ROM_MEM_RULE_RULE1_SHIFT)) & AHB_SECURE_CTRL_SEC_CTRL_ROM_MEM_RULE_RULE1_MASK)

#define AHB_SECURE_CTRL_SEC_CTRL_ROM_MEM_RULE_RULE2_MASK (0x300U)
#define AHB_SECURE_CTRL_SEC_CTRL_ROM_MEM_RULE_RULE2_SHIFT (8U)
/*! RULE2 - secure control rule2. it can be set when check_reg's write_lock is '0'
 *  0b00..Non-secure and Non-priviledge user access allowed.
 *  0b01..Non-secure and Privilege access allowed.
 *  0b10..Secure and Non-priviledge user access allowed.
 *  0b11..Secure and Priviledge user access allowed.
 */
#define AHB_SECURE_CTRL_SEC_CTRL_ROM_MEM_RULE_RULE2(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_CTRL_ROM_MEM_RULE_RULE2_SHIFT)) & AHB_SECURE_CTRL_SEC_CTRL_ROM_MEM_RULE_RULE2_MASK)

#define AHB_SECURE_CTRL_SEC_CTRL_ROM_MEM_RULE_RULE3_MASK (0x3000U)
#define AHB_SECURE_CTRL_SEC_CTRL_ROM_MEM_RULE_RULE3_SHIFT (12U)
/*! RULE3 - secure control rule3. it can be set when check_reg's write_lock is '0'
 *  0b00..Non-secure and Non-priviledge user access allowed.
 *  0b01..Non-secure and Privilege access allowed.
 *  0b10..Secure and Non-priviledge user access allowed.
 *  0b11..Secure and Priviledge user access allowed.
 */
#define AHB_SECURE_CTRL_SEC_CTRL_ROM_MEM_RULE_RULE3(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_CTRL_ROM_MEM_RULE_RULE3_SHIFT)) & AHB_SECURE_CTRL_SEC_CTRL_ROM_MEM_RULE_RULE3_MASK)

#define AHB_SECURE_CTRL_SEC_CTRL_ROM_MEM_RULE_RULE4_MASK (0x30000U)
#define AHB_SECURE_CTRL_SEC_CTRL_ROM_MEM_RULE_RULE4_SHIFT (16U)
/*! RULE4 - secure control rule4. it can be set when check_reg's write_lock is '0'
 *  0b00..Non-secure and Non-priviledge user access allowed.
 *  0b01..Non-secure and Privilege access allowed.
 *  0b10..Secure and Non-priviledge user access allowed.
 *  0b11..Secure and Priviledge user access allowed.
 */
#define AHB_SECURE_CTRL_SEC_CTRL_ROM_MEM_RULE_RULE4(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_CTRL_ROM_MEM_RULE_RULE4_SHIFT)) & AHB_SECURE_CTRL_SEC_CTRL_ROM_MEM_RULE_RULE4_MASK)

#define AHB_SECURE_CTRL_SEC_CTRL_ROM_MEM_RULE_RULE5_MASK (0x300000U)
#define AHB_SECURE_CTRL_SEC_CTRL_ROM_MEM_RULE_RULE5_SHIFT (20U)
/*! RULE5 - secure control rule5. it can be set when check_reg's write_lock is '0'
 *  0b00..Non-secure and Non-priviledge user access allowed.
 *  0b01..Non-secure and Privilege access allowed.
 *  0b10..Secure and Non-priviledge user access allowed.
 *  0b11..Secure and Priviledge user access allowed.
 */
#define AHB_SECURE_CTRL_SEC_CTRL_ROM_MEM_RULE_RULE5(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_CTRL_ROM_MEM_RULE_RULE5_SHIFT)) & AHB_SECURE_CTRL_SEC_CTRL_ROM_MEM_RULE_RULE5_MASK)

#define AHB_SECURE_CTRL_SEC_CTRL_ROM_MEM_RULE_RULE6_MASK (0x3000000U)
#define AHB_SECURE_CTRL_SEC_CTRL_ROM_MEM_RULE_RULE6_SHIFT (24U)
/*! RULE6 - secure control rule6. it can be set when check_reg's write_lock is '0'
 *  0b00..Non-secure and Non-priviledge user access allowed.
 *  0b01..Non-secure and Privilege access allowed.
 *  0b10..Secure and Non-priviledge user access allowed.
 *  0b11..Secure and Priviledge user access allowed.
 */
#define AHB_SECURE_CTRL_SEC_CTRL_ROM_MEM_RULE_RULE6(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_CTRL_ROM_MEM_RULE_RULE6_SHIFT)) & AHB_SECURE_CTRL_SEC_CTRL_ROM_MEM_RULE_RULE6_MASK)

#define AHB_SECURE_CTRL_SEC_CTRL_ROM_MEM_RULE_RULE7_MASK (0x30000000U)
#define AHB_SECURE_CTRL_SEC_CTRL_ROM_MEM_RULE_RULE7_SHIFT (28U)
/*! RULE7 - secure control rule7. it can be set when check_reg's write_lock is '0'
 *  0b00..Non-secure and Non-priviledge user access allowed.
 *  0b01..Non-secure and Privilege access allowed.
 *  0b10..Secure and Non-priviledge user access allowed.
 *  0b11..Secure and Priviledge user access allowed.
 */
#define AHB_SECURE_CTRL_SEC_CTRL_ROM_MEM_RULE_RULE7(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_CTRL_ROM_MEM_RULE_RULE7_SHIFT)) & AHB_SECURE_CTRL_SEC_CTRL_ROM_MEM_RULE_RULE7_MASK)
/*! @} */

/* The count of AHB_SECURE_CTRL_SEC_CTRL_ROM_MEM_RULE */
#define AHB_SECURE_CTRL_SEC_CTRL_ROM_MEM_RULE_COUNT (1U)

/* The count of AHB_SECURE_CTRL_SEC_CTRL_ROM_MEM_RULE */
#define AHB_SECURE_CTRL_SEC_CTRL_ROM_MEM_RULE_COUNT2 (4U)

/*! @name SEC_CTRL_RAMX_SLAVE_RULE - Security access rules for RAMX slaves. */
/*! @{ */

#define AHB_SECURE_CTRL_SEC_CTRL_RAMX_SLAVE_RULE_RAMX_RULE_MASK (0x3U)
#define AHB_SECURE_CTRL_SEC_CTRL_RAMX_SLAVE_RULE_RAMX_RULE_SHIFT (0U)
/*! RAMX_RULE - Security access rules for the whole RAMX : 0x0400_0000 - 0x0400_7FFF
 *  0b00..Non-secure and Non-priviledge user access allowed.
 *  0b01..Non-secure and Privilege access allowed.
 *  0b10..Secure and Non-priviledge user access allowed.
 *  0b11..Secure and Priviledge user access allowed.
 */
#define AHB_SECURE_CTRL_SEC_CTRL_RAMX_SLAVE_RULE_RAMX_RULE(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_CTRL_RAMX_SLAVE_RULE_RAMX_RULE_SHIFT)) & AHB_SECURE_CTRL_SEC_CTRL_RAMX_SLAVE_RULE_RAMX_RULE_MASK)
/*! @} */

/* The count of AHB_SECURE_CTRL_SEC_CTRL_RAMX_SLAVE_RULE */
#define AHB_SECURE_CTRL_SEC_CTRL_RAMX_SLAVE_RULE_COUNT (1U)

/*! @name SEC_CTRL_RAMX_MEM_RULE - Security access rules for RAMX slaves. */
/*! @{ */

#define AHB_SECURE_CTRL_SEC_CTRL_RAMX_MEM_RULE_RULE0_MASK (0x3U)
#define AHB_SECURE_CTRL_SEC_CTRL_RAMX_MEM_RULE_RULE0_SHIFT (0U)
/*! RULE0 - secure control rule0. it can be set when check_reg's write_lock is '0'
 *  0b00..Non-secure and Non-priviledge user access allowed.
 *  0b01..Non-secure and Privilege access allowed.
 *  0b10..Secure and Non-priviledge user access allowed.
 *  0b11..Secure and Priviledge user access allowed.
 */
#define AHB_SECURE_CTRL_SEC_CTRL_RAMX_MEM_RULE_RULE0(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_CTRL_RAMX_MEM_RULE_RULE0_SHIFT)) & AHB_SECURE_CTRL_SEC_CTRL_RAMX_MEM_RULE_RULE0_MASK)

#define AHB_SECURE_CTRL_SEC_CTRL_RAMX_MEM_RULE_RULE1_MASK (0x30U)
#define AHB_SECURE_CTRL_SEC_CTRL_RAMX_MEM_RULE_RULE1_SHIFT (4U)
/*! RULE1 - secure control rule1. it can be set when check_reg's write_lock is '0'
 *  0b00..Non-secure and Non-priviledge user access allowed.
 *  0b01..Non-secure and Privilege access allowed.
 *  0b10..Secure and Non-priviledge user access allowed.
 *  0b11..Secure and Priviledge user access allowed.
 */
#define AHB_SECURE_CTRL_SEC_CTRL_RAMX_MEM_RULE_RULE1(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_CTRL_RAMX_MEM_RULE_RULE1_SHIFT)) & AHB_SECURE_CTRL_SEC_CTRL_RAMX_MEM_RULE_RULE1_MASK)

#define AHB_SECURE_CTRL_SEC_CTRL_RAMX_MEM_RULE_RULE2_MASK (0x300U)
#define AHB_SECURE_CTRL_SEC_CTRL_RAMX_MEM_RULE_RULE2_SHIFT (8U)
/*! RULE2 - secure control rule2. it can be set when check_reg's write_lock is '0'
 *  0b00..Non-secure and Non-priviledge user access allowed.
 *  0b01..Non-secure and Privilege access allowed.
 *  0b10..Secure and Non-priviledge user access allowed.
 *  0b11..Secure and Priviledge user access allowed.
 */
#define AHB_SECURE_CTRL_SEC_CTRL_RAMX_MEM_RULE_RULE2(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_CTRL_RAMX_MEM_RULE_RULE2_SHIFT)) & AHB_SECURE_CTRL_SEC_CTRL_RAMX_MEM_RULE_RULE2_MASK)

#define AHB_SECURE_CTRL_SEC_CTRL_RAMX_MEM_RULE_RULE3_MASK (0x3000U)
#define AHB_SECURE_CTRL_SEC_CTRL_RAMX_MEM_RULE_RULE3_SHIFT (12U)
/*! RULE3 - secure control rule3. it can be set when check_reg's write_lock is '0'
 *  0b00..Non-secure and Non-priviledge user access allowed.
 *  0b01..Non-secure and Privilege access allowed.
 *  0b10..Secure and Non-priviledge user access allowed.
 *  0b11..Secure and Priviledge user access allowed.
 */
#define AHB_SECURE_CTRL_SEC_CTRL_RAMX_MEM_RULE_RULE3(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_CTRL_RAMX_MEM_RULE_RULE3_SHIFT)) & AHB_SECURE_CTRL_SEC_CTRL_RAMX_MEM_RULE_RULE3_MASK)
/*! @} */

/* The count of AHB_SECURE_CTRL_SEC_CTRL_RAMX_MEM_RULE */
#define AHB_SECURE_CTRL_SEC_CTRL_RAMX_MEM_RULE_COUNT (1U)

/* The count of AHB_SECURE_CTRL_SEC_CTRL_RAMX_MEM_RULE */
#define AHB_SECURE_CTRL_SEC_CTRL_RAMX_MEM_RULE_COUNT2 (1U)

/*! @name SEC_CTRL_RAM0_SLAVE_RULE - Security access rules for RAM0 slaves. */
/*! @{ */

#define AHB_SECURE_CTRL_SEC_CTRL_RAM0_SLAVE_RULE_RAM0_RULE_MASK (0x3U)
#define AHB_SECURE_CTRL_SEC_CTRL_RAM0_SLAVE_RULE_RAM0_RULE_SHIFT (0U)
/*! RAM0_RULE - Security access rules for the whole RAM0 : 0x2000_0000 - 0x2000_7FFF
 *  0b00..Non-secure and Non-priviledge user access allowed.
 *  0b01..Non-secure and Privilege access allowed.
 *  0b10..Secure and Non-priviledge user access allowed.
 *  0b11..Secure and Priviledge user access allowed.
 */
#define AHB_SECURE_CTRL_SEC_CTRL_RAM0_SLAVE_RULE_RAM0_RULE(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_CTRL_RAM0_SLAVE_RULE_RAM0_RULE_SHIFT)) & AHB_SECURE_CTRL_SEC_CTRL_RAM0_SLAVE_RULE_RAM0_RULE_MASK)
/*! @} */

/* The count of AHB_SECURE_CTRL_SEC_CTRL_RAM0_SLAVE_RULE */
#define AHB_SECURE_CTRL_SEC_CTRL_RAM0_SLAVE_RULE_COUNT (1U)

/*! @name SEC_CTRL_RAM0_MEM_RULE - Security access rules for RAM0 slaves. */
/*! @{ */

#define AHB_SECURE_CTRL_SEC_CTRL_RAM0_MEM_RULE_RULE0_MASK (0x3U)
#define AHB_SECURE_CTRL_SEC_CTRL_RAM0_MEM_RULE_RULE0_SHIFT (0U)
/*! RULE0 - secure control rule0. it can be set when check_reg's write_lock is '0'
 *  0b00..Non-secure and Non-priviledge user access allowed.
 *  0b01..Non-secure and Privilege access allowed.
 *  0b10..Secure and Non-priviledge user access allowed.
 *  0b11..Secure and Priviledge user access allowed.
 */
#define AHB_SECURE_CTRL_SEC_CTRL_RAM0_MEM_RULE_RULE0(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_CTRL_RAM0_MEM_RULE_RULE0_SHIFT)) & AHB_SECURE_CTRL_SEC_CTRL_RAM0_MEM_RULE_RULE0_MASK)

#define AHB_SECURE_CTRL_SEC_CTRL_RAM0_MEM_RULE_RULE1_MASK (0x30U)
#define AHB_SECURE_CTRL_SEC_CTRL_RAM0_MEM_RULE_RULE1_SHIFT (4U)
/*! RULE1 - secure control rule1. it can be set when check_reg's write_lock is '0'
 *  0b00..Non-secure and Non-priviledge user access allowed.
 *  0b01..Non-secure and Privilege access allowed.
 *  0b10..Secure and Non-priviledge user access allowed.
 *  0b11..Secure and Priviledge user access allowed.
 */
#define AHB_SECURE_CTRL_SEC_CTRL_RAM0_MEM_RULE_RULE1(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_CTRL_RAM0_MEM_RULE_RULE1_SHIFT)) & AHB_SECURE_CTRL_SEC_CTRL_RAM0_MEM_RULE_RULE1_MASK)

#define AHB_SECURE_CTRL_SEC_CTRL_RAM0_MEM_RULE_RULE2_MASK (0x300U)
#define AHB_SECURE_CTRL_SEC_CTRL_RAM0_MEM_RULE_RULE2_SHIFT (8U)
/*! RULE2 - secure control rule2. it can be set when check_reg's write_lock is '0'
 *  0b00..Non-secure and Non-priviledge user access allowed.
 *  0b01..Non-secure and Privilege access allowed.
 *  0b10..Secure and Non-priviledge user access allowed.
 *  0b11..Secure and Priviledge user access allowed.
 */
#define AHB_SECURE_CTRL_SEC_CTRL_RAM0_MEM_RULE_RULE2(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_CTRL_RAM0_MEM_RULE_RULE2_SHIFT)) & AHB_SECURE_CTRL_SEC_CTRL_RAM0_MEM_RULE_RULE2_MASK)

#define AHB_SECURE_CTRL_SEC_CTRL_RAM0_MEM_RULE_RULE3_MASK (0x3000U)
#define AHB_SECURE_CTRL_SEC_CTRL_RAM0_MEM_RULE_RULE3_SHIFT (12U)
/*! RULE3 - secure control rule3. it can be set when check_reg's write_lock is '0'
 *  0b00..Non-secure and Non-priviledge user access allowed.
 *  0b01..Non-secure and Privilege access allowed.
 *  0b10..Secure and Non-priviledge user access allowed.
 *  0b11..Secure and Priviledge user access allowed.
 */
#define AHB_SECURE_CTRL_SEC_CTRL_RAM0_MEM_RULE_RULE3(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_CTRL_RAM0_MEM_RULE_RULE3_SHIFT)) & AHB_SECURE_CTRL_SEC_CTRL_RAM0_MEM_RULE_RULE3_MASK)

#define AHB_SECURE_CTRL_SEC_CTRL_RAM0_MEM_RULE_RULE4_MASK (0x30000U)
#define AHB_SECURE_CTRL_SEC_CTRL_RAM0_MEM_RULE_RULE4_SHIFT (16U)
/*! RULE4 - secure control rule4. it can be set when check_reg's write_lock is '0'
 *  0b00..Non-secure and Non-priviledge user access allowed.
 *  0b01..Non-secure and Privilege access allowed.
 *  0b10..Secure and Non-priviledge user access allowed.
 *  0b11..Secure and Priviledge user access allowed.
 */
#define AHB_SECURE_CTRL_SEC_CTRL_RAM0_MEM_RULE_RULE4(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_CTRL_RAM0_MEM_RULE_RULE4_SHIFT)) & AHB_SECURE_CTRL_SEC_CTRL_RAM0_MEM_RULE_RULE4_MASK)

#define AHB_SECURE_CTRL_SEC_CTRL_RAM0_MEM_RULE_RULE5_MASK (0x300000U)
#define AHB_SECURE_CTRL_SEC_CTRL_RAM0_MEM_RULE_RULE5_SHIFT (20U)
/*! RULE5 - secure control rule5. it can be set when check_reg's write_lock is '0'
 *  0b00..Non-secure and Non-priviledge user access allowed.
 *  0b01..Non-secure and Privilege access allowed.
 *  0b10..Secure and Non-priviledge user access allowed.
 *  0b11..Secure and Priviledge user access allowed.
 */
#define AHB_SECURE_CTRL_SEC_CTRL_RAM0_MEM_RULE_RULE5(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_CTRL_RAM0_MEM_RULE_RULE5_SHIFT)) & AHB_SECURE_CTRL_SEC_CTRL_RAM0_MEM_RULE_RULE5_MASK)

#define AHB_SECURE_CTRL_SEC_CTRL_RAM0_MEM_RULE_RULE6_MASK (0x3000000U)
#define AHB_SECURE_CTRL_SEC_CTRL_RAM0_MEM_RULE_RULE6_SHIFT (24U)
/*! RULE6 - secure control rule6. it can be set when check_reg's write_lock is '0'
 *  0b00..Non-secure and Non-priviledge user access allowed.
 *  0b01..Non-secure and Privilege access allowed.
 *  0b10..Secure and Non-priviledge user access allowed.
 *  0b11..Secure and Priviledge user access allowed.
 */
#define AHB_SECURE_CTRL_SEC_CTRL_RAM0_MEM_RULE_RULE6(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_CTRL_RAM0_MEM_RULE_RULE6_SHIFT)) & AHB_SECURE_CTRL_SEC_CTRL_RAM0_MEM_RULE_RULE6_MASK)

#define AHB_SECURE_CTRL_SEC_CTRL_RAM0_MEM_RULE_RULE7_MASK (0x30000000U)
#define AHB_SECURE_CTRL_SEC_CTRL_RAM0_MEM_RULE_RULE7_SHIFT (28U)
/*! RULE7 - secure control rule7. it can be set when check_reg's write_lock is '0'
 *  0b00..Non-secure and Non-priviledge user access allowed.
 *  0b01..Non-secure and Privilege access allowed.
 *  0b10..Secure and Non-priviledge user access allowed.
 *  0b11..Secure and Priviledge user access allowed.
 */
#define AHB_SECURE_CTRL_SEC_CTRL_RAM0_MEM_RULE_RULE7(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_CTRL_RAM0_MEM_RULE_RULE7_SHIFT)) & AHB_SECURE_CTRL_SEC_CTRL_RAM0_MEM_RULE_RULE7_MASK)
/*! @} */

/* The count of AHB_SECURE_CTRL_SEC_CTRL_RAM0_MEM_RULE */
#define AHB_SECURE_CTRL_SEC_CTRL_RAM0_MEM_RULE_COUNT (1U)

/* The count of AHB_SECURE_CTRL_SEC_CTRL_RAM0_MEM_RULE */
#define AHB_SECURE_CTRL_SEC_CTRL_RAM0_MEM_RULE_COUNT2 (1U)

/*! @name SEC_CTRL_RAM1_SLAVE_RULE - Security access rules for RAM1 slaves. */
/*! @{ */

#define AHB_SECURE_CTRL_SEC_CTRL_RAM1_SLAVE_RULE_RAM1_RULE_MASK (0x3U)
#define AHB_SECURE_CTRL_SEC_CTRL_RAM1_SLAVE_RULE_RAM1_RULE_SHIFT (0U)
/*! RAM1_RULE - Security access rules for the whole RAM1 : 0x2000_8000 - 0x2000_BFFF
 *  0b00..Non-secure and Non-priviledge user access allowed.
 *  0b01..Non-secure and Privilege access allowed.
 *  0b10..Secure and Non-priviledge user access allowed.
 *  0b11..Secure and Priviledge user access allowed.
 */
#define AHB_SECURE_CTRL_SEC_CTRL_RAM1_SLAVE_RULE_RAM1_RULE(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_CTRL_RAM1_SLAVE_RULE_RAM1_RULE_SHIFT)) & AHB_SECURE_CTRL_SEC_CTRL_RAM1_SLAVE_RULE_RAM1_RULE_MASK)
/*! @} */

/* The count of AHB_SECURE_CTRL_SEC_CTRL_RAM1_SLAVE_RULE */
#define AHB_SECURE_CTRL_SEC_CTRL_RAM1_SLAVE_RULE_COUNT (1U)

/*! @name SEC_CTRL_RAM1_MEM_RULE - Security access rules for RAM1 slaves. */
/*! @{ */

#define AHB_SECURE_CTRL_SEC_CTRL_RAM1_MEM_RULE_RULE0_MASK (0x3U)
#define AHB_SECURE_CTRL_SEC_CTRL_RAM1_MEM_RULE_RULE0_SHIFT (0U)
/*! RULE0 - secure control rule0. it can be set when check_reg's write_lock is '0'
 *  0b00..Non-secure and Non-priviledge user access allowed.
 *  0b01..Non-secure and Privilege access allowed.
 *  0b10..Secure and Non-priviledge user access allowed.
 *  0b11..Secure and Priviledge user access allowed.
 */
#define AHB_SECURE_CTRL_SEC_CTRL_RAM1_MEM_RULE_RULE0(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_CTRL_RAM1_MEM_RULE_RULE0_SHIFT)) & AHB_SECURE_CTRL_SEC_CTRL_RAM1_MEM_RULE_RULE0_MASK)

#define AHB_SECURE_CTRL_SEC_CTRL_RAM1_MEM_RULE_RULE1_MASK (0x30U)
#define AHB_SECURE_CTRL_SEC_CTRL_RAM1_MEM_RULE_RULE1_SHIFT (4U)
/*! RULE1 - secure control rule1. it can be set when check_reg's write_lock is '0'
 *  0b00..Non-secure and Non-priviledge user access allowed.
 *  0b01..Non-secure and Privilege access allowed.
 *  0b10..Secure and Non-priviledge user access allowed.
 *  0b11..Secure and Priviledge user access allowed.
 */
#define AHB_SECURE_CTRL_SEC_CTRL_RAM1_MEM_RULE_RULE1(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_CTRL_RAM1_MEM_RULE_RULE1_SHIFT)) & AHB_SECURE_CTRL_SEC_CTRL_RAM1_MEM_RULE_RULE1_MASK)

#define AHB_SECURE_CTRL_SEC_CTRL_RAM1_MEM_RULE_RULE2_MASK (0x300U)
#define AHB_SECURE_CTRL_SEC_CTRL_RAM1_MEM_RULE_RULE2_SHIFT (8U)
/*! RULE2 - secure control rule2. it can be set when check_reg's write_lock is '0'
 *  0b00..Non-secure and Non-priviledge user access allowed.
 *  0b01..Non-secure and Privilege access allowed.
 *  0b10..Secure and Non-priviledge user access allowed.
 *  0b11..Secure and Priviledge user access allowed.
 */
#define AHB_SECURE_CTRL_SEC_CTRL_RAM1_MEM_RULE_RULE2(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_CTRL_RAM1_MEM_RULE_RULE2_SHIFT)) & AHB_SECURE_CTRL_SEC_CTRL_RAM1_MEM_RULE_RULE2_MASK)

#define AHB_SECURE_CTRL_SEC_CTRL_RAM1_MEM_RULE_RULE3_MASK (0x3000U)
#define AHB_SECURE_CTRL_SEC_CTRL_RAM1_MEM_RULE_RULE3_SHIFT (12U)
/*! RULE3 - secure control rule3. it can be set when check_reg's write_lock is '0'
 *  0b00..Non-secure and Non-priviledge user access allowed.
 *  0b01..Non-secure and Privilege access allowed.
 *  0b10..Secure and Non-priviledge user access allowed.
 *  0b11..Secure and Priviledge user access allowed.
 */
#define AHB_SECURE_CTRL_SEC_CTRL_RAM1_MEM_RULE_RULE3(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_CTRL_RAM1_MEM_RULE_RULE3_SHIFT)) & AHB_SECURE_CTRL_SEC_CTRL_RAM1_MEM_RULE_RULE3_MASK)
/*! @} */

/* The count of AHB_SECURE_CTRL_SEC_CTRL_RAM1_MEM_RULE */
#define AHB_SECURE_CTRL_SEC_CTRL_RAM1_MEM_RULE_COUNT (1U)

/* The count of AHB_SECURE_CTRL_SEC_CTRL_RAM1_MEM_RULE */
#define AHB_SECURE_CTRL_SEC_CTRL_RAM1_MEM_RULE_COUNT2 (1U)

/*! @name SEC_CTRL_RAM2_SLAVE_RULE - Security access rules for RAM2 slaves. */
/*! @{ */

#define AHB_SECURE_CTRL_SEC_CTRL_RAM2_SLAVE_RULE_RAM2_RULE_MASK (0x3U)
#define AHB_SECURE_CTRL_SEC_CTRL_RAM2_SLAVE_RULE_RAM2_RULE_SHIFT (0U)
/*! RAM2_RULE - Security access rules for the whole RAM2 : 0x2000_C000 - 0x2000_FFFF
 *  0b00..Non-secure and Non-priviledge user access allowed.
 *  0b01..Non-secure and Privilege access allowed.
 *  0b10..Secure and Non-priviledge user access allowed.
 *  0b11..Secure and Priviledge user access allowed.
 */
#define AHB_SECURE_CTRL_SEC_CTRL_RAM2_SLAVE_RULE_RAM2_RULE(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_CTRL_RAM2_SLAVE_RULE_RAM2_RULE_SHIFT)) & AHB_SECURE_CTRL_SEC_CTRL_RAM2_SLAVE_RULE_RAM2_RULE_MASK)
/*! @} */

/* The count of AHB_SECURE_CTRL_SEC_CTRL_RAM2_SLAVE_RULE */
#define AHB_SECURE_CTRL_SEC_CTRL_RAM2_SLAVE_RULE_COUNT (1U)

/*! @name SEC_CTRL_RAM2_MEM_RULE - Security access rules for RAM2 slaves. */
/*! @{ */

#define AHB_SECURE_CTRL_SEC_CTRL_RAM2_MEM_RULE_RULE0_MASK (0x3U)
#define AHB_SECURE_CTRL_SEC_CTRL_RAM2_MEM_RULE_RULE0_SHIFT (0U)
/*! RULE0 - secure control rule0. it can be set when check_reg's write_lock is '0'
 *  0b00..Non-secure and Non-priviledge user access allowed.
 *  0b01..Non-secure and Privilege access allowed.
 *  0b10..Secure and Non-priviledge user access allowed.
 *  0b11..Secure and Priviledge user access allowed.
 */
#define AHB_SECURE_CTRL_SEC_CTRL_RAM2_MEM_RULE_RULE0(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_CTRL_RAM2_MEM_RULE_RULE0_SHIFT)) & AHB_SECURE_CTRL_SEC_CTRL_RAM2_MEM_RULE_RULE0_MASK)

#define AHB_SECURE_CTRL_SEC_CTRL_RAM2_MEM_RULE_RULE1_MASK (0x30U)
#define AHB_SECURE_CTRL_SEC_CTRL_RAM2_MEM_RULE_RULE1_SHIFT (4U)
/*! RULE1 - secure control rule1. it can be set when check_reg's write_lock is '0'
 *  0b00..Non-secure and Non-priviledge user access allowed.
 *  0b01..Non-secure and Privilege access allowed.
 *  0b10..Secure and Non-priviledge user access allowed.
 *  0b11..Secure and Priviledge user access allowed.
 */
#define AHB_SECURE_CTRL_SEC_CTRL_RAM2_MEM_RULE_RULE1(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_CTRL_RAM2_MEM_RULE_RULE1_SHIFT)) & AHB_SECURE_CTRL_SEC_CTRL_RAM2_MEM_RULE_RULE1_MASK)

#define AHB_SECURE_CTRL_SEC_CTRL_RAM2_MEM_RULE_RULE2_MASK (0x300U)
#define AHB_SECURE_CTRL_SEC_CTRL_RAM2_MEM_RULE_RULE2_SHIFT (8U)
/*! RULE2 - secure control rule2. it can be set when check_reg's write_lock is '0'
 *  0b00..Non-secure and Non-priviledge user access allowed.
 *  0b01..Non-secure and Privilege access allowed.
 *  0b10..Secure and Non-priviledge user access allowed.
 *  0b11..Secure and Priviledge user access allowed.
 */
#define AHB_SECURE_CTRL_SEC_CTRL_RAM2_MEM_RULE_RULE2(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_CTRL_RAM2_MEM_RULE_RULE2_SHIFT)) & AHB_SECURE_CTRL_SEC_CTRL_RAM2_MEM_RULE_RULE2_MASK)

#define AHB_SECURE_CTRL_SEC_CTRL_RAM2_MEM_RULE_RULE3_MASK (0x3000U)
#define AHB_SECURE_CTRL_SEC_CTRL_RAM2_MEM_RULE_RULE3_SHIFT (12U)
/*! RULE3 - secure control rule3. it can be set when check_reg's write_lock is '0'
 *  0b00..Non-secure and Non-priviledge user access allowed.
 *  0b01..Non-secure and Privilege access allowed.
 *  0b10..Secure and Non-priviledge user access allowed.
 *  0b11..Secure and Priviledge user access allowed.
 */
#define AHB_SECURE_CTRL_SEC_CTRL_RAM2_MEM_RULE_RULE3(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_CTRL_RAM2_MEM_RULE_RULE3_SHIFT)) & AHB_SECURE_CTRL_SEC_CTRL_RAM2_MEM_RULE_RULE3_MASK)
/*! @} */

/* The count of AHB_SECURE_CTRL_SEC_CTRL_RAM2_MEM_RULE */
#define AHB_SECURE_CTRL_SEC_CTRL_RAM2_MEM_RULE_COUNT (1U)

/* The count of AHB_SECURE_CTRL_SEC_CTRL_RAM2_MEM_RULE */
#define AHB_SECURE_CTRL_SEC_CTRL_RAM2_MEM_RULE_COUNT2 (1U)

/*! @name SEC_CTRL_USB_HS_SLAVE_RULE - Security access rules for USB High speed RAM slaves. */
/*! @{ */

#define AHB_SECURE_CTRL_SEC_CTRL_USB_HS_SLAVE_RULE_RAM_USB_HS_RULE_MASK (0x3U)
#define AHB_SECURE_CTRL_SEC_CTRL_USB_HS_SLAVE_RULE_RAM_USB_HS_RULE_SHIFT (0U)
/*! RAM_USB_HS_RULE - Security access rules for the whole USB High Speed RAM : 0x2001_0000 - 0x2001_3FFF
 *  0b00..Non-secure and Non-priviledge user access allowed.
 *  0b01..Non-secure and Privilege access allowed.
 *  0b10..Secure and Non-priviledge user access allowed.
 *  0b11..Secure and Priviledge user access allowed.
 */
#define AHB_SECURE_CTRL_SEC_CTRL_USB_HS_SLAVE_RULE_RAM_USB_HS_RULE(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_CTRL_USB_HS_SLAVE_RULE_RAM_USB_HS_RULE_SHIFT)) & AHB_SECURE_CTRL_SEC_CTRL_USB_HS_SLAVE_RULE_RAM_USB_HS_RULE_MASK)
/*! @} */

/* The count of AHB_SECURE_CTRL_SEC_CTRL_USB_HS_SLAVE_RULE */
#define AHB_SECURE_CTRL_SEC_CTRL_USB_HS_SLAVE_RULE_COUNT (1U)

/*! @name SEC_CTRL_USB_HS_MEM_RULE - Security access rules for RAM_USB_HS. */
/*! @{ */

#define AHB_SECURE_CTRL_SEC_CTRL_USB_HS_MEM_RULE_SRAM_SECT_0_RULE_MASK (0x3U)
#define AHB_SECURE_CTRL_SEC_CTRL_USB_HS_MEM_RULE_SRAM_SECT_0_RULE_SHIFT (0U)
/*! SRAM_SECT_0_RULE - Address space: 0x2001_0000 - 0x2001_0FFF
 *  0b00..Non-secure and Non-priviledge user access allowed.
 *  0b01..Non-secure and Privilege access allowed.
 *  0b10..Secure and Non-priviledge user access allowed.
 *  0b11..Secure and Priviledge user access allowed.
 */
#define AHB_SECURE_CTRL_SEC_CTRL_USB_HS_MEM_RULE_SRAM_SECT_0_RULE(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_CTRL_USB_HS_MEM_RULE_SRAM_SECT_0_RULE_SHIFT)) & AHB_SECURE_CTRL_SEC_CTRL_USB_HS_MEM_RULE_SRAM_SECT_0_RULE_MASK)

#define AHB_SECURE_CTRL_SEC_CTRL_USB_HS_MEM_RULE_SRAM_SECT_1_RULE_MASK (0x30U)
#define AHB_SECURE_CTRL_SEC_CTRL_USB_HS_MEM_RULE_SRAM_SECT_1_RULE_SHIFT (4U)
/*! SRAM_SECT_1_RULE - Address space: 0x2001_1000 - 0x2001_1FFF
 *  0b00..Non-secure and Non-priviledge user access allowed.
 *  0b01..Non-secure and Privilege access allowed.
 *  0b10..Secure and Non-priviledge user access allowed.
 *  0b11..Secure and Priviledge user access allowed.
 */
#define AHB_SECURE_CTRL_SEC_CTRL_USB_HS_MEM_RULE_SRAM_SECT_1_RULE(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_CTRL_USB_HS_MEM_RULE_SRAM_SECT_1_RULE_SHIFT)) & AHB_SECURE_CTRL_SEC_CTRL_USB_HS_MEM_RULE_SRAM_SECT_1_RULE_MASK)

#define AHB_SECURE_CTRL_SEC_CTRL_USB_HS_MEM_RULE_SRAM_SECT_2_RULE_MASK (0x300U)
#define AHB_SECURE_CTRL_SEC_CTRL_USB_HS_MEM_RULE_SRAM_SECT_2_RULE_SHIFT (8U)
/*! SRAM_SECT_2_RULE - Address space: 0x2001_2000 - 0x2001_2FFF
 *  0b00..Non-secure and Non-priviledge user access allowed.
 *  0b01..Non-secure and Privilege access allowed.
 *  0b10..Secure and Non-priviledge user access allowed.
 *  0b11..Secure and Priviledge user access allowed.
 */
#define AHB_SECURE_CTRL_SEC_CTRL_USB_HS_MEM_RULE_SRAM_SECT_2_RULE(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_CTRL_USB_HS_MEM_RULE_SRAM_SECT_2_RULE_SHIFT)) & AHB_SECURE_CTRL_SEC_CTRL_USB_HS_MEM_RULE_SRAM_SECT_2_RULE_MASK)

#define AHB_SECURE_CTRL_SEC_CTRL_USB_HS_MEM_RULE_SRAM_SECT_3_RULE_MASK (0x3000U)
#define AHB_SECURE_CTRL_SEC_CTRL_USB_HS_MEM_RULE_SRAM_SECT_3_RULE_SHIFT (12U)
/*! SRAM_SECT_3_RULE - Address space: 0x2001_3000 - 0x2001_3FFF
 *  0b00..Non-secure and Non-priviledge user access allowed.
 *  0b01..Non-secure and Privilege access allowed.
 *  0b10..Secure and Non-priviledge user access allowed.
 *  0b11..Secure and Priviledge user access allowed.
 */
#define AHB_SECURE_CTRL_SEC_CTRL_USB_HS_MEM_RULE_SRAM_SECT_3_RULE(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_CTRL_USB_HS_MEM_RULE_SRAM_SECT_3_RULE_SHIFT)) & AHB_SECURE_CTRL_SEC_CTRL_USB_HS_MEM_RULE_SRAM_SECT_3_RULE_MASK)
/*! @} */

/* The count of AHB_SECURE_CTRL_SEC_CTRL_USB_HS_MEM_RULE */
#define AHB_SECURE_CTRL_SEC_CTRL_USB_HS_MEM_RULE_COUNT (1U)

/* The count of AHB_SECURE_CTRL_SEC_CTRL_USB_HS_MEM_RULE */
#define AHB_SECURE_CTRL_SEC_CTRL_USB_HS_MEM_RULE_COUNT2 (1U)

/*! @name SEC_CTRL_APB_BRIDGE_SLAVE_RULE - Security access rules for both APB Bridges slaves. */
/*! @{ */

#define AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE_SLAVE_RULE_APBBRIDGE0_RULE_MASK (0x3U)
#define AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE_SLAVE_RULE_APBBRIDGE0_RULE_SHIFT (0U)
/*! APBBRIDGE0_RULE - Security access rules for the whole APB Bridge 0
 *  0b00..Non-secure and Non-priviledge user access allowed.
 *  0b01..Non-secure and Privilege access allowed.
 *  0b10..Secure and Non-priviledge user access allowed.
 *  0b11..Secure and Priviledge user access allowed.
 */
#define AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE_SLAVE_RULE_APBBRIDGE0_RULE(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE_SLAVE_RULE_APBBRIDGE0_RULE_SHIFT)) & AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE_SLAVE_RULE_APBBRIDGE0_RULE_MASK)

#define AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE_SLAVE_RULE_APBBRIDGE1_RULE_MASK (0x30U)
#define AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE_SLAVE_RULE_APBBRIDGE1_RULE_SHIFT (4U)
/*! APBBRIDGE1_RULE - Security access rules for the whole APB Bridge 1
 *  0b00..Non-secure and Non-priviledge user access allowed.
 *  0b01..Non-secure and Privilege access allowed.
 *  0b10..Secure and Non-priviledge user access allowed.
 *  0b11..Secure and Priviledge user access allowed.
 */
#define AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE_SLAVE_RULE_APBBRIDGE1_RULE(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE_SLAVE_RULE_APBBRIDGE1_RULE_SHIFT)) & AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE_SLAVE_RULE_APBBRIDGE1_RULE_MASK)
/*! @} */

/* The count of AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE_SLAVE_RULE */
#define AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE_SLAVE_RULE_COUNT (1U)

/*! @name SEC_CTRL_APB_BRIDGE0_MEM_CTRL0 - Security access rules for APB Bridge 0 peripherals. Each APB bridge sector is 4 Kbytes. There are 32 APB Bridge 0 sectors in total. */
/*! @{ */

#define AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE0_MEM_CTRL0_SYSCON_RULE_MASK (0x3U)
#define AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE0_MEM_CTRL0_SYSCON_RULE_SHIFT (0U)
/*! SYSCON_RULE - System Configuration
 *  0b00..Non-secure and Non-priviledge user access allowed.
 *  0b01..Non-secure and Privilege access allowed.
 *  0b10..Secure and Non-priviledge user access allowed.
 *  0b11..Secure and Priviledge user access allowed.
 */
#define AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE0_MEM_CTRL0_SYSCON_RULE(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE0_MEM_CTRL0_SYSCON_RULE_SHIFT)) & AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE0_MEM_CTRL0_SYSCON_RULE_MASK)

#define AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE0_MEM_CTRL0_IOCON_RULE_MASK (0x30U)
#define AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE0_MEM_CTRL0_IOCON_RULE_SHIFT (4U)
/*! IOCON_RULE - I/O Configuration
 *  0b00..Non-secure and Non-priviledge user access allowed.
 *  0b01..Non-secure and Privilege access allowed.
 *  0b10..Secure and Non-priviledge user access allowed.
 *  0b11..Secure and Priviledge user access allowed.
 */
#define AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE0_MEM_CTRL0_IOCON_RULE(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE0_MEM_CTRL0_IOCON_RULE_SHIFT)) & AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE0_MEM_CTRL0_IOCON_RULE_MASK)

#define AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE0_MEM_CTRL0_GINT0_RULE_MASK (0x300U)
#define AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE0_MEM_CTRL0_GINT0_RULE_SHIFT (8U)
/*! GINT0_RULE - GPIO input Interrupt 0
 *  0b00..Non-secure and Non-priviledge user access allowed.
 *  0b01..Non-secure and Privilege access allowed.
 *  0b10..Secure and Non-priviledge user access allowed.
 *  0b11..Secure and Priviledge user access allowed.
 */
#define AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE0_MEM_CTRL0_GINT0_RULE(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE0_MEM_CTRL0_GINT0_RULE_SHIFT)) & AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE0_MEM_CTRL0_GINT0_RULE_MASK)

#define AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE0_MEM_CTRL0_GINT1_RULE_MASK (0x3000U)
#define AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE0_MEM_CTRL0_GINT1_RULE_SHIFT (12U)
/*! GINT1_RULE - GPIO input Interrupt 1
 *  0b00..Non-secure and Non-priviledge user access allowed.
 *  0b01..Non-secure and Privilege access allowed.
 *  0b10..Secure and Non-priviledge user access allowed.
 *  0b11..Secure and Priviledge user access allowed.
 */
#define AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE0_MEM_CTRL0_GINT1_RULE(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE0_MEM_CTRL0_GINT1_RULE_SHIFT)) & AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE0_MEM_CTRL0_GINT1_RULE_MASK)

#define AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE0_MEM_CTRL0_PINT_RULE_MASK (0x30000U)
#define AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE0_MEM_CTRL0_PINT_RULE_SHIFT (16U)
/*! PINT_RULE - Pin Interrupt and Pattern match
 *  0b00..Non-secure and Non-priviledge user access allowed.
 *  0b01..Non-secure and Privilege access allowed.
 *  0b10..Secure and Non-priviledge user access allowed.
 *  0b11..Secure and Priviledge user access allowed.
 */
#define AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE0_MEM_CTRL0_PINT_RULE(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE0_MEM_CTRL0_PINT_RULE_SHIFT)) & AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE0_MEM_CTRL0_PINT_RULE_MASK)

#define AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE0_MEM_CTRL0_SEC_PINT_RULE_MASK (0x300000U)
#define AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE0_MEM_CTRL0_SEC_PINT_RULE_SHIFT (20U)
/*! SEC_PINT_RULE - Secure Pin Interrupt and Pattern match
 *  0b00..Non-secure and Non-priviledge user access allowed.
 *  0b01..Non-secure and Privilege access allowed.
 *  0b10..Secure and Non-priviledge user access allowed.
 *  0b11..Secure and Priviledge user access allowed.
 */
#define AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE0_MEM_CTRL0_SEC_PINT_RULE(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE0_MEM_CTRL0_SEC_PINT_RULE_SHIFT)) & AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE0_MEM_CTRL0_SEC_PINT_RULE_MASK)

#define AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE0_MEM_CTRL0_INPUTMUX_RULE_MASK (0x3000000U)
#define AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE0_MEM_CTRL0_INPUTMUX_RULE_SHIFT (24U)
/*! INPUTMUX_RULE - Peripheral input multiplexing
 *  0b00..Non-secure and Non-priviledge user access allowed.
 *  0b01..Non-secure and Privilege access allowed.
 *  0b10..Secure and Non-priviledge user access allowed.
 *  0b11..Secure and Priviledge user access allowed.
 */
#define AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE0_MEM_CTRL0_INPUTMUX_RULE(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE0_MEM_CTRL0_INPUTMUX_RULE_SHIFT)) & AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE0_MEM_CTRL0_INPUTMUX_RULE_MASK)
/*! @} */

/* The count of AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE0_MEM_CTRL0 */
#define AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE0_MEM_CTRL0_COUNT (1U)

/*! @name SEC_CTRL_APB_BRIDGE0_MEM_CTRL1 - Security access rules for APB Bridge 0 peripherals. Each APB bridge sector is 4 Kbytes. There are 32 APB Bridge 0 sectors in total. */
/*! @{ */

#define AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE0_MEM_CTRL1_CTIMER0_RULE_MASK (0x3U)
#define AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE0_MEM_CTRL1_CTIMER0_RULE_SHIFT (0U)
/*! CTIMER0_RULE - Standard counter/Timer 0
 *  0b00..Non-secure and Non-priviledge user access allowed.
 *  0b01..Non-secure and Privilege access allowed.
 *  0b10..Secure and Non-priviledge user access allowed.
 *  0b11..Secure and Priviledge user access allowed.
 */
#define AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE0_MEM_CTRL1_CTIMER0_RULE(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE0_MEM_CTRL1_CTIMER0_RULE_SHIFT)) & AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE0_MEM_CTRL1_CTIMER0_RULE_MASK)

#define AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE0_MEM_CTRL1_CTIMER1_RULE_MASK (0x30U)
#define AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE0_MEM_CTRL1_CTIMER1_RULE_SHIFT (4U)
/*! CTIMER1_RULE - Standard counter/Timer 1
 *  0b00..Non-secure and Non-priviledge user access allowed.
 *  0b01..Non-secure and Privilege access allowed.
 *  0b10..Secure and Non-priviledge user access allowed.
 *  0b11..Secure and Priviledge user access allowed.
 */
#define AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE0_MEM_CTRL1_CTIMER1_RULE(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE0_MEM_CTRL1_CTIMER1_RULE_SHIFT)) & AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE0_MEM_CTRL1_CTIMER1_RULE_MASK)

#define AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE0_MEM_CTRL1_WWDT_RULE_MASK (0x30000U)
#define AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE0_MEM_CTRL1_WWDT_RULE_SHIFT (16U)
/*! WWDT_RULE - Windiwed wtachdog Timer
 *  0b00..Non-secure and Non-priviledge user access allowed.
 *  0b01..Non-secure and Privilege access allowed.
 *  0b10..Secure and Non-priviledge user access allowed.
 *  0b11..Secure and Priviledge user access allowed.
 */
#define AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE0_MEM_CTRL1_WWDT_RULE(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE0_MEM_CTRL1_WWDT_RULE_SHIFT)) & AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE0_MEM_CTRL1_WWDT_RULE_MASK)

#define AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE0_MEM_CTRL1_MRT_RULE_MASK (0x300000U)
#define AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE0_MEM_CTRL1_MRT_RULE_SHIFT (20U)
/*! MRT_RULE - Multi-rate Timer
 *  0b00..Non-secure and Non-priviledge user access allowed.
 *  0b01..Non-secure and Privilege access allowed.
 *  0b10..Secure and Non-priviledge user access allowed.
 *  0b11..Secure and Priviledge user access allowed.
 */
#define AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE0_MEM_CTRL1_MRT_RULE(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE0_MEM_CTRL1_MRT_RULE_SHIFT)) & AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE0_MEM_CTRL1_MRT_RULE_MASK)

#define AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE0_MEM_CTRL1_UTICK_RULE_MASK (0x3000000U)
#define AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE0_MEM_CTRL1_UTICK_RULE_SHIFT (24U)
/*! UTICK_RULE - Micro-Timer
 *  0b00..Non-secure and Non-priviledge user access allowed.
 *  0b01..Non-secure and Privilege access allowed.
 *  0b10..Secure and Non-priviledge user access allowed.
 *  0b11..Secure and Priviledge user access allowed.
 */
#define AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE0_MEM_CTRL1_UTICK_RULE(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE0_MEM_CTRL1_UTICK_RULE_SHIFT)) & AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE0_MEM_CTRL1_UTICK_RULE_MASK)
/*! @} */

/* The count of AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE0_MEM_CTRL1 */
#define AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE0_MEM_CTRL1_COUNT (1U)

/*! @name SEC_CTRL_APB_BRIDGE0_MEM_CTRL2 - Security access rules for APB Bridge 0 peripherals. Each APB bridge sector is 4 Kbytes. There are 32 APB Bridge 0 sectors in total. */
/*! @{ */

#define AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE0_MEM_CTRL2_ANACTRL_RULE_MASK (0x3000U)
#define AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE0_MEM_CTRL2_ANACTRL_RULE_SHIFT (12U)
/*! ANACTRL_RULE - Analog Modules controller
 *  0b00..Non-secure and Non-priviledge user access allowed.
 *  0b01..Non-secure and Privilege access allowed.
 *  0b10..Secure and Non-priviledge user access allowed.
 *  0b11..Secure and Priviledge user access allowed.
 */
#define AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE0_MEM_CTRL2_ANACTRL_RULE(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE0_MEM_CTRL2_ANACTRL_RULE_SHIFT)) & AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE0_MEM_CTRL2_ANACTRL_RULE_MASK)
/*! @} */

/* The count of AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE0_MEM_CTRL2 */
#define AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE0_MEM_CTRL2_COUNT (1U)

/*! @name SEC_CTRL_APB_BRIDGE1_MEM_CTRL0 - Security access rules for APB Bridge 1 peripherals. Each APB bridge sector is 4 Kbytes. There are 32 APB Bridge 1 sectors in total. */
/*! @{ */

#define AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE1_MEM_CTRL0_PMC_RULE_MASK (0x3U)
#define AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE1_MEM_CTRL0_PMC_RULE_SHIFT (0U)
/*! PMC_RULE - Power Management Controller
 *  0b00..Non-secure and Non-priviledge user access allowed.
 *  0b01..Non-secure and Privilege access allowed.
 *  0b10..Secure and Non-priviledge user access allowed.
 *  0b11..Secure and Priviledge user access allowed.
 */
#define AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE1_MEM_CTRL0_PMC_RULE(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE1_MEM_CTRL0_PMC_RULE_SHIFT)) & AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE1_MEM_CTRL0_PMC_RULE_MASK)

#define AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE1_MEM_CTRL0_SYSCTRL_RULE_MASK (0x3000U)
#define AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE1_MEM_CTRL0_SYSCTRL_RULE_SHIFT (12U)
/*! SYSCTRL_RULE - System Controller
 *  0b00..Non-secure and Non-priviledge user access allowed.
 *  0b01..Non-secure and Privilege access allowed.
 *  0b10..Secure and Non-priviledge user access allowed.
 *  0b11..Secure and Priviledge user access allowed.
 */
#define AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE1_MEM_CTRL0_SYSCTRL_RULE(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE1_MEM_CTRL0_SYSCTRL_RULE_SHIFT)) & AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE1_MEM_CTRL0_SYSCTRL_RULE_MASK)

#define AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE1_MEM_CTRL0_SPI_FILTER_RULE_MASK (0x30000U)
#define AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE1_MEM_CTRL0_SPI_FILTER_RULE_SHIFT (16U)
/*! SPI_FILTER_RULE - SPI FILTER control
 *  0b00..Non-secure and Non-priviledge user access allowed.
 *  0b01..Non-secure and Privilege access allowed.
 *  0b10..Secure and Non-priviledge user access allowed.
 *  0b11..Secure and Priviledge user access allowed.
 */
#define AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE1_MEM_CTRL0_SPI_FILTER_RULE(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE1_MEM_CTRL0_SPI_FILTER_RULE_SHIFT)) & AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE1_MEM_CTRL0_SPI_FILTER_RULE_MASK)
/*! @} */

/* The count of AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE1_MEM_CTRL0 */
#define AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE1_MEM_CTRL0_COUNT (1U)

/*! @name SEC_CTRL_APB_BRIDGE1_MEM_CTRL1 - Security access rules for APB Bridge 1 peripherals. Each APB bridge sector is 4 Kbytes. There are 32 APB Bridge 1 sectors in total. */
/*! @{ */

#define AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE1_MEM_CTRL1_CTIMER2_RULE_MASK (0x3U)
#define AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE1_MEM_CTRL1_CTIMER2_RULE_SHIFT (0U)
/*! CTIMER2_RULE - Standard counter/Timer 2
 *  0b00..Non-secure and Non-priviledge user access allowed.
 *  0b01..Non-secure and Privilege access allowed.
 *  0b10..Secure and Non-priviledge user access allowed.
 *  0b11..Secure and Priviledge user access allowed.
 */
#define AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE1_MEM_CTRL1_CTIMER2_RULE(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE1_MEM_CTRL1_CTIMER2_RULE_SHIFT)) & AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE1_MEM_CTRL1_CTIMER2_RULE_MASK)

#define AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE1_MEM_CTRL1_CTIMER3_RULE_MASK (0x30U)
#define AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE1_MEM_CTRL1_CTIMER3_RULE_SHIFT (4U)
/*! CTIMER3_RULE - Standard counter/Timer 3
 *  0b00..Non-secure and Non-priviledge user access allowed.
 *  0b01..Non-secure and Privilege access allowed.
 *  0b10..Secure and Non-priviledge user access allowed.
 *  0b11..Secure and Priviledge user access allowed.
 */
#define AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE1_MEM_CTRL1_CTIMER3_RULE(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE1_MEM_CTRL1_CTIMER3_RULE_SHIFT)) & AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE1_MEM_CTRL1_CTIMER3_RULE_MASK)

#define AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE1_MEM_CTRL1_CTIMER4_RULE_MASK (0x300U)
#define AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE1_MEM_CTRL1_CTIMER4_RULE_SHIFT (8U)
/*! CTIMER4_RULE - Standard counter/Timer 4
 *  0b00..Non-secure and Non-priviledge user access allowed.
 *  0b01..Non-secure and Privilege access allowed.
 *  0b10..Secure and Non-priviledge user access allowed.
 *  0b11..Secure and Priviledge user access allowed.
 */
#define AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE1_MEM_CTRL1_CTIMER4_RULE(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE1_MEM_CTRL1_CTIMER4_RULE_SHIFT)) & AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE1_MEM_CTRL1_CTIMER4_RULE_MASK)

#define AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE1_MEM_CTRL1_RTC_RULE_MASK (0x30000U)
#define AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE1_MEM_CTRL1_RTC_RULE_SHIFT (16U)
/*! RTC_RULE - Real Time Counter
 *  0b00..Non-secure and Non-priviledge user access allowed.
 *  0b01..Non-secure and Privilege access allowed.
 *  0b10..Secure and Non-priviledge user access allowed.
 *  0b11..Secure and Priviledge user access allowed.
 */
#define AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE1_MEM_CTRL1_RTC_RULE(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE1_MEM_CTRL1_RTC_RULE_SHIFT)) & AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE1_MEM_CTRL1_RTC_RULE_MASK)

#define AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE1_MEM_CTRL1_OSEVENT_RULE_MASK (0x300000U)
#define AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE1_MEM_CTRL1_OSEVENT_RULE_SHIFT (20U)
/*! OSEVENT_RULE - OS Event Timer
 *  0b00..Non-secure and Non-priviledge user access allowed.
 *  0b01..Non-secure and Privilege access allowed.
 *  0b10..Secure and Non-priviledge user access allowed.
 *  0b11..Secure and Priviledge user access allowed.
 */
#define AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE1_MEM_CTRL1_OSEVENT_RULE(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE1_MEM_CTRL1_OSEVENT_RULE_SHIFT)) & AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE1_MEM_CTRL1_OSEVENT_RULE_MASK)
/*! @} */

/* The count of AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE1_MEM_CTRL1 */
#define AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE1_MEM_CTRL1_COUNT (1U)

/*! @name SEC_CTRL_APB_BRIDGE1_MEM_CTRL2 - Security access rules for APB Bridge 1 peripherals. Each APB bridge sector is 4 Kbytes. There are 32 APB Bridge 1 sectors in total. */
/*! @{ */

#define AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE1_MEM_CTRL2_FLASH_CTRL_RULE_MASK (0x30000U)
#define AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE1_MEM_CTRL2_FLASH_CTRL_RULE_SHIFT (16U)
/*! FLASH_CTRL_RULE - Flash Controller
 *  0b00..Non-secure and Non-priviledge user access allowed.
 *  0b01..Non-secure and Privilege access allowed.
 *  0b10..Secure and Non-priviledge user access allowed.
 *  0b11..Secure and Priviledge user access allowed.
 */
#define AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE1_MEM_CTRL2_FLASH_CTRL_RULE(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE1_MEM_CTRL2_FLASH_CTRL_RULE_SHIFT)) & AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE1_MEM_CTRL2_FLASH_CTRL_RULE_MASK)

#define AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE1_MEM_CTRL2_PRINCE_RULE_MASK (0x300000U)
#define AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE1_MEM_CTRL2_PRINCE_RULE_SHIFT (20U)
/*! PRINCE_RULE - Prince
 *  0b00..Non-secure and Non-priviledge user access allowed.
 *  0b01..Non-secure and Privilege access allowed.
 *  0b10..Secure and Non-priviledge user access allowed.
 *  0b11..Secure and Priviledge user access allowed.
 */
#define AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE1_MEM_CTRL2_PRINCE_RULE(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE1_MEM_CTRL2_PRINCE_RULE_SHIFT)) & AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE1_MEM_CTRL2_PRINCE_RULE_MASK)
/*! @} */

/* The count of AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE1_MEM_CTRL2 */
#define AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE1_MEM_CTRL2_COUNT (1U)

/*! @name SEC_CTRL_APB_BRIDGE1_MEM_CTRL3 - Security access rules for APB Bridge 1 peripherals. Each APB bridge sector is 4 Kbytes. There are 32 APB Bridge 1 sectors in total. */
/*! @{ */

#define AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE1_MEM_CTRL3_USBHPHY_RULE_MASK (0x3U)
#define AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE1_MEM_CTRL3_USBHPHY_RULE_SHIFT (0U)
/*! USBHPHY_RULE - USB High Speed Phy controller
 *  0b00..Non-secure and Non-priviledge user access allowed.
 *  0b01..Non-secure and Privilege access allowed.
 *  0b10..Secure and Non-priviledge user access allowed.
 *  0b11..Secure and Priviledge user access allowed.
 */
#define AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE1_MEM_CTRL3_USBHPHY_RULE(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE1_MEM_CTRL3_USBHPHY_RULE_SHIFT)) & AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE1_MEM_CTRL3_USBHPHY_RULE_MASK)

#define AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE1_MEM_CTRL3_RNG_RULE_MASK (0x300U)
#define AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE1_MEM_CTRL3_RNG_RULE_SHIFT (8U)
/*! RNG_RULE - True Random Number Generator
 *  0b00..Non-secure and Non-priviledge user access allowed.
 *  0b01..Non-secure and Privilege access allowed.
 *  0b10..Secure and Non-priviledge user access allowed.
 *  0b11..Secure and Priviledge user access allowed.
 */
#define AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE1_MEM_CTRL3_RNG_RULE(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE1_MEM_CTRL3_RNG_RULE_SHIFT)) & AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE1_MEM_CTRL3_RNG_RULE_MASK)

#define AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE1_MEM_CTRL3_PUF_RULE_MASK (0x3000U)
#define AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE1_MEM_CTRL3_PUF_RULE_SHIFT (12U)
/*! PUF_RULE - PUF
 *  0b00..Non-secure and Non-priviledge user access allowed.
 *  0b01..Non-secure and Privilege access allowed.
 *  0b10..Secure and Non-priviledge user access allowed.
 *  0b11..Secure and Priviledge user access allowed.
 */
#define AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE1_MEM_CTRL3_PUF_RULE(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE1_MEM_CTRL3_PUF_RULE_SHIFT)) & AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE1_MEM_CTRL3_PUF_RULE_MASK)

#define AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE1_MEM_CTRL3_PLU_RULE_MASK (0x300000U)
#define AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE1_MEM_CTRL3_PLU_RULE_SHIFT (20U)
/*! PLU_RULE - Programmable Look-Up logic
 *  0b00..Non-secure and Non-priviledge user access allowed.
 *  0b01..Non-secure and Privilege access allowed.
 *  0b10..Secure and Non-priviledge user access allowed.
 *  0b11..Secure and Priviledge user access allowed.
 */
#define AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE1_MEM_CTRL3_PLU_RULE(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE1_MEM_CTRL3_PLU_RULE_SHIFT)) & AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE1_MEM_CTRL3_PLU_RULE_MASK)
/*! @} */

/* The count of AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE1_MEM_CTRL3 */
#define AHB_SECURE_CTRL_SEC_CTRL_APB_BRIDGE1_MEM_CTRL3_COUNT (1U)

/*! @name SEC_CTRL_AHB_PORT7_SLAVE0_RULE - Security access rules for AHB peripherals. */
/*! @{ */

#define AHB_SECURE_CTRL_SEC_CTRL_AHB_PORT7_SLAVE0_RULE_DMA0_RULE_MASK (0x300U)
#define AHB_SECURE_CTRL_SEC_CTRL_AHB_PORT7_SLAVE0_RULE_DMA0_RULE_SHIFT (8U)
/*! DMA0_RULE - DMA Controller
 *  0b00..Non-secure and Non-priviledge user access allowed.
 *  0b01..Non-secure and Privilege access allowed.
 *  0b10..Secure and Non-priviledge user access allowed.
 *  0b11..Secure and Priviledge user access allowed.
 */
#define AHB_SECURE_CTRL_SEC_CTRL_AHB_PORT7_SLAVE0_RULE_DMA0_RULE(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_CTRL_AHB_PORT7_SLAVE0_RULE_DMA0_RULE_SHIFT)) & AHB_SECURE_CTRL_SEC_CTRL_AHB_PORT7_SLAVE0_RULE_DMA0_RULE_MASK)

#define AHB_SECURE_CTRL_SEC_CTRL_AHB_PORT7_SLAVE0_RULE_FS_USB_DEV_RULE_MASK (0x30000U)
#define AHB_SECURE_CTRL_SEC_CTRL_AHB_PORT7_SLAVE0_RULE_FS_USB_DEV_RULE_SHIFT (16U)
/*! FS_USB_DEV_RULE - USB Full-speed device
 *  0b00..Non-secure and Non-priviledge user access allowed.
 *  0b01..Non-secure and Privilege access allowed.
 *  0b10..Secure and Non-priviledge user access allowed.
 *  0b11..Secure and Priviledge user access allowed.
 */
#define AHB_SECURE_CTRL_SEC_CTRL_AHB_PORT7_SLAVE0_RULE_FS_USB_DEV_RULE(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_CTRL_AHB_PORT7_SLAVE0_RULE_FS_USB_DEV_RULE_SHIFT)) & AHB_SECURE_CTRL_SEC_CTRL_AHB_PORT7_SLAVE0_RULE_FS_USB_DEV_RULE_MASK)

#define AHB_SECURE_CTRL_SEC_CTRL_AHB_PORT7_SLAVE0_RULE_SCT_RULE_MASK (0x300000U)
#define AHB_SECURE_CTRL_SEC_CTRL_AHB_PORT7_SLAVE0_RULE_SCT_RULE_SHIFT (20U)
/*! SCT_RULE - SCTimer
 *  0b00..Non-secure and Non-priviledge user access allowed.
 *  0b01..Non-secure and Privilege access allowed.
 *  0b10..Secure and Non-priviledge user access allowed.
 *  0b11..Secure and Priviledge user access allowed.
 */
#define AHB_SECURE_CTRL_SEC_CTRL_AHB_PORT7_SLAVE0_RULE_SCT_RULE(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_CTRL_AHB_PORT7_SLAVE0_RULE_SCT_RULE_SHIFT)) & AHB_SECURE_CTRL_SEC_CTRL_AHB_PORT7_SLAVE0_RULE_SCT_RULE_MASK)

#define AHB_SECURE_CTRL_SEC_CTRL_AHB_PORT7_SLAVE0_RULE_FLEXCOMM0_RULE_MASK (0x3000000U)
#define AHB_SECURE_CTRL_SEC_CTRL_AHB_PORT7_SLAVE0_RULE_FLEXCOMM0_RULE_SHIFT (24U)
/*! FLEXCOMM0_RULE - Flexcomm interface 0
 *  0b00..Non-secure and Non-priviledge user access allowed.
 *  0b01..Non-secure and Privilege access allowed.
 *  0b10..Secure and Non-priviledge user access allowed.
 *  0b11..Secure and Priviledge user access allowed.
 */
#define AHB_SECURE_CTRL_SEC_CTRL_AHB_PORT7_SLAVE0_RULE_FLEXCOMM0_RULE(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_CTRL_AHB_PORT7_SLAVE0_RULE_FLEXCOMM0_RULE_SHIFT)) & AHB_SECURE_CTRL_SEC_CTRL_AHB_PORT7_SLAVE0_RULE_FLEXCOMM0_RULE_MASK)

#define AHB_SECURE_CTRL_SEC_CTRL_AHB_PORT7_SLAVE0_RULE_FLEXCOMM1_RULE_MASK (0x30000000U)
#define AHB_SECURE_CTRL_SEC_CTRL_AHB_PORT7_SLAVE0_RULE_FLEXCOMM1_RULE_SHIFT (28U)
/*! FLEXCOMM1_RULE - Flexcomm interface 1
 *  0b00..Non-secure and Non-priviledge user access allowed.
 *  0b01..Non-secure and Privilege access allowed.
 *  0b10..Secure and Non-priviledge user access allowed.
 *  0b11..Secure and Priviledge user access allowed.
 */
#define AHB_SECURE_CTRL_SEC_CTRL_AHB_PORT7_SLAVE0_RULE_FLEXCOMM1_RULE(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_CTRL_AHB_PORT7_SLAVE0_RULE_FLEXCOMM1_RULE_SHIFT)) & AHB_SECURE_CTRL_SEC_CTRL_AHB_PORT7_SLAVE0_RULE_FLEXCOMM1_RULE_MASK)
/*! @} */

/*! @name SEC_CTRL_AHB_PORT7_SLAVE1_RULE - Security access rules for AHB peripherals. */
/*! @{ */

#define AHB_SECURE_CTRL_SEC_CTRL_AHB_PORT7_SLAVE1_RULE_FLEXCOMM2_RULE_MASK (0x3U)
#define AHB_SECURE_CTRL_SEC_CTRL_AHB_PORT7_SLAVE1_RULE_FLEXCOMM2_RULE_SHIFT (0U)
/*! FLEXCOMM2_RULE - Flexcomm interface 2
 *  0b00..Non-secure and Non-priviledge user access allowed.
 *  0b01..Non-secure and Privilege access allowed.
 *  0b10..Secure and Non-priviledge user access allowed.
 *  0b11..Secure and Priviledge user access allowed.
 */
#define AHB_SECURE_CTRL_SEC_CTRL_AHB_PORT7_SLAVE1_RULE_FLEXCOMM2_RULE(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_CTRL_AHB_PORT7_SLAVE1_RULE_FLEXCOMM2_RULE_SHIFT)) & AHB_SECURE_CTRL_SEC_CTRL_AHB_PORT7_SLAVE1_RULE_FLEXCOMM2_RULE_MASK)

#define AHB_SECURE_CTRL_SEC_CTRL_AHB_PORT7_SLAVE1_RULE_FLEXCOMM3_RULE_MASK (0x30U)
#define AHB_SECURE_CTRL_SEC_CTRL_AHB_PORT7_SLAVE1_RULE_FLEXCOMM3_RULE_SHIFT (4U)
/*! FLEXCOMM3_RULE - Flexcomm interface 3
 *  0b00..Non-secure and Non-priviledge user access allowed.
 *  0b01..Non-secure and Privilege access allowed.
 *  0b10..Secure and Non-priviledge user access allowed.
 *  0b11..Secure and Priviledge user access allowed.
 */
#define AHB_SECURE_CTRL_SEC_CTRL_AHB_PORT7_SLAVE1_RULE_FLEXCOMM3_RULE(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_CTRL_AHB_PORT7_SLAVE1_RULE_FLEXCOMM3_RULE_SHIFT)) & AHB_SECURE_CTRL_SEC_CTRL_AHB_PORT7_SLAVE1_RULE_FLEXCOMM3_RULE_MASK)

#define AHB_SECURE_CTRL_SEC_CTRL_AHB_PORT7_SLAVE1_RULE_FLEXCOMM4_RULE_MASK (0x300U)
#define AHB_SECURE_CTRL_SEC_CTRL_AHB_PORT7_SLAVE1_RULE_FLEXCOMM4_RULE_SHIFT (8U)
/*! FLEXCOMM4_RULE - Flexcomm interface 4
 *  0b00..Non-secure and Non-priviledge user access allowed.
 *  0b01..Non-secure and Privilege access allowed.
 *  0b10..Secure and Non-priviledge user access allowed.
 *  0b11..Secure and Priviledge user access allowed.
 */
#define AHB_SECURE_CTRL_SEC_CTRL_AHB_PORT7_SLAVE1_RULE_FLEXCOMM4_RULE(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_CTRL_AHB_PORT7_SLAVE1_RULE_FLEXCOMM4_RULE_SHIFT)) & AHB_SECURE_CTRL_SEC_CTRL_AHB_PORT7_SLAVE1_RULE_FLEXCOMM4_RULE_MASK)

#define AHB_SECURE_CTRL_SEC_CTRL_AHB_PORT7_SLAVE1_RULE_GPIO0_RULE_MASK (0x30000U)
#define AHB_SECURE_CTRL_SEC_CTRL_AHB_PORT7_SLAVE1_RULE_GPIO0_RULE_SHIFT (16U)
/*! GPIO0_RULE - High Speed GPIO
 *  0b00..Non-secure and Non-priviledge user access allowed.
 *  0b01..Non-secure and Privilege access allowed.
 *  0b10..Secure and Non-priviledge user access allowed.
 *  0b11..Secure and Priviledge user access allowed.
 */
#define AHB_SECURE_CTRL_SEC_CTRL_AHB_PORT7_SLAVE1_RULE_GPIO0_RULE(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_CTRL_AHB_PORT7_SLAVE1_RULE_GPIO0_RULE_SHIFT)) & AHB_SECURE_CTRL_SEC_CTRL_AHB_PORT7_SLAVE1_RULE_GPIO0_RULE_MASK)
/*! @} */

/*! @name SEC_CTRL_AHB_PORT8_SLAVE0_RULE - Security access rules for AHB peripherals. */
/*! @{ */

#define AHB_SECURE_CTRL_SEC_CTRL_AHB_PORT8_SLAVE0_RULE_USB_HS_DEV_RULE_MASK (0x30000U)
#define AHB_SECURE_CTRL_SEC_CTRL_AHB_PORT8_SLAVE0_RULE_USB_HS_DEV_RULE_SHIFT (16U)
/*! USB_HS_DEV_RULE - USB high Speed device registers
 *  0b00..Non-secure and Non-priviledge user access allowed.
 *  0b01..Non-secure and Privilege access allowed.
 *  0b10..Secure and Non-priviledge user access allowed.
 *  0b11..Secure and Priviledge user access allowed.
 */
#define AHB_SECURE_CTRL_SEC_CTRL_AHB_PORT8_SLAVE0_RULE_USB_HS_DEV_RULE(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_CTRL_AHB_PORT8_SLAVE0_RULE_USB_HS_DEV_RULE_SHIFT)) & AHB_SECURE_CTRL_SEC_CTRL_AHB_PORT8_SLAVE0_RULE_USB_HS_DEV_RULE_MASK)

#define AHB_SECURE_CTRL_SEC_CTRL_AHB_PORT8_SLAVE0_RULE_CRC_RULE_MASK (0x300000U)
#define AHB_SECURE_CTRL_SEC_CTRL_AHB_PORT8_SLAVE0_RULE_CRC_RULE_SHIFT (20U)
/*! CRC_RULE - CRC engine
 *  0b00..Non-secure and Non-priviledge user access allowed.
 *  0b01..Non-secure and Privilege access allowed.
 *  0b10..Secure and Non-priviledge user access allowed.
 *  0b11..Secure and Priviledge user access allowed.
 */
#define AHB_SECURE_CTRL_SEC_CTRL_AHB_PORT8_SLAVE0_RULE_CRC_RULE(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_CTRL_AHB_PORT8_SLAVE0_RULE_CRC_RULE_SHIFT)) & AHB_SECURE_CTRL_SEC_CTRL_AHB_PORT8_SLAVE0_RULE_CRC_RULE_MASK)

#define AHB_SECURE_CTRL_SEC_CTRL_AHB_PORT8_SLAVE0_RULE_FLEXCOMM5_RULE_MASK (0x3000000U)
#define AHB_SECURE_CTRL_SEC_CTRL_AHB_PORT8_SLAVE0_RULE_FLEXCOMM5_RULE_SHIFT (24U)
/*! FLEXCOMM5_RULE - Flexcomm interface 5
 *  0b00..Non-secure and Non-priviledge user access allowed.
 *  0b01..Non-secure and Privilege access allowed.
 *  0b10..Secure and Non-priviledge user access allowed.
 *  0b11..Secure and Priviledge user access allowed.
 */
#define AHB_SECURE_CTRL_SEC_CTRL_AHB_PORT8_SLAVE0_RULE_FLEXCOMM5_RULE(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_CTRL_AHB_PORT8_SLAVE0_RULE_FLEXCOMM5_RULE_SHIFT)) & AHB_SECURE_CTRL_SEC_CTRL_AHB_PORT8_SLAVE0_RULE_FLEXCOMM5_RULE_MASK)

#define AHB_SECURE_CTRL_SEC_CTRL_AHB_PORT8_SLAVE0_RULE_FLEXCOMM6_RULE_MASK (0x30000000U)
#define AHB_SECURE_CTRL_SEC_CTRL_AHB_PORT8_SLAVE0_RULE_FLEXCOMM6_RULE_SHIFT (28U)
/*! FLEXCOMM6_RULE - Flexcomm interface 6
 *  0b00..Non-secure and Non-priviledge user access allowed.
 *  0b01..Non-secure and Privilege access allowed.
 *  0b10..Secure and Non-priviledge user access allowed.
 *  0b11..Secure and Priviledge user access allowed.
 */
#define AHB_SECURE_CTRL_SEC_CTRL_AHB_PORT8_SLAVE0_RULE_FLEXCOMM6_RULE(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_CTRL_AHB_PORT8_SLAVE0_RULE_FLEXCOMM6_RULE_SHIFT)) & AHB_SECURE_CTRL_SEC_CTRL_AHB_PORT8_SLAVE0_RULE_FLEXCOMM6_RULE_MASK)
/*! @} */

/*! @name SEC_CTRL_AHB_PORT8_SLAVE1_RULE - Security access rules for AHB peripherals. */
/*! @{ */

#define AHB_SECURE_CTRL_SEC_CTRL_AHB_PORT8_SLAVE1_RULE_FLEXCOMM7_RULE_MASK (0x3U)
#define AHB_SECURE_CTRL_SEC_CTRL_AHB_PORT8_SLAVE1_RULE_FLEXCOMM7_RULE_SHIFT (0U)
/*! FLEXCOMM7_RULE - Flexcomm interface 7
 *  0b00..Non-secure and Non-priviledge user access allowed.
 *  0b01..Non-secure and Privilege access allowed.
 *  0b10..Secure and Non-priviledge user access allowed.
 *  0b11..Secure and Priviledge user access allowed.
 */
#define AHB_SECURE_CTRL_SEC_CTRL_AHB_PORT8_SLAVE1_RULE_FLEXCOMM7_RULE(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_CTRL_AHB_PORT8_SLAVE1_RULE_FLEXCOMM7_RULE_SHIFT)) & AHB_SECURE_CTRL_SEC_CTRL_AHB_PORT8_SLAVE1_RULE_FLEXCOMM7_RULE_MASK)

#define AHB_SECURE_CTRL_SEC_CTRL_AHB_PORT8_SLAVE1_RULE_DBG_MAILBOX_RULE_MASK (0x30000U)
#define AHB_SECURE_CTRL_SEC_CTRL_AHB_PORT8_SLAVE1_RULE_DBG_MAILBOX_RULE_SHIFT (16U)
/*! DBG_MAILBOX_RULE - Debug mailbox (aka ISP-AP)
 *  0b00..Non-secure and Non-priviledge user access allowed.
 *  0b01..Non-secure and Privilege access allowed.
 *  0b10..Secure and Non-priviledge user access allowed.
 *  0b11..Secure and Priviledge user access allowed.
 */
#define AHB_SECURE_CTRL_SEC_CTRL_AHB_PORT8_SLAVE1_RULE_DBG_MAILBOX_RULE(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_CTRL_AHB_PORT8_SLAVE1_RULE_DBG_MAILBOX_RULE_SHIFT)) & AHB_SECURE_CTRL_SEC_CTRL_AHB_PORT8_SLAVE1_RULE_DBG_MAILBOX_RULE_MASK)

#define AHB_SECURE_CTRL_SEC_CTRL_AHB_PORT8_SLAVE1_RULE_CAN0_RULE_MASK (0x300000U)
#define AHB_SECURE_CTRL_SEC_CTRL_AHB_PORT8_SLAVE1_RULE_CAN0_RULE_SHIFT (20U)
/*! CAN0_RULE - CAN-FD
 *  0b00..Non-secure and Non-priviledge user access allowed.
 *  0b01..Non-secure and Privilege access allowed.
 *  0b10..Secure and Non-priviledge user access allowed.
 *  0b11..Secure and Priviledge user access allowed.
 */
#define AHB_SECURE_CTRL_SEC_CTRL_AHB_PORT8_SLAVE1_RULE_CAN0_RULE(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_CTRL_AHB_PORT8_SLAVE1_RULE_CAN0_RULE_SHIFT)) & AHB_SECURE_CTRL_SEC_CTRL_AHB_PORT8_SLAVE1_RULE_CAN0_RULE_MASK)

#define AHB_SECURE_CTRL_SEC_CTRL_AHB_PORT8_SLAVE1_RULE_HS_LSPI_RULE_MASK (0x30000000U)
#define AHB_SECURE_CTRL_SEC_CTRL_AHB_PORT8_SLAVE1_RULE_HS_LSPI_RULE_SHIFT (28U)
/*! HS_LSPI_RULE - High Speed SPI
 *  0b00..Non-secure and Non-priviledge user access allowed.
 *  0b01..Non-secure and Privilege access allowed.
 *  0b10..Secure and Non-priviledge user access allowed.
 *  0b11..Secure and Priviledge user access allowed.
 */
#define AHB_SECURE_CTRL_SEC_CTRL_AHB_PORT8_SLAVE1_RULE_HS_LSPI_RULE(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_CTRL_AHB_PORT8_SLAVE1_RULE_HS_LSPI_RULE_SHIFT)) & AHB_SECURE_CTRL_SEC_CTRL_AHB_PORT8_SLAVE1_RULE_HS_LSPI_RULE_MASK)
/*! @} */

/*! @name SEC_CTRL_AHB_PORT9_SLAVE0_RULE - Security access rules for AHB peripherals. */
/*! @{ */

#define AHB_SECURE_CTRL_SEC_CTRL_AHB_PORT9_SLAVE0_RULE_ADC_RULE_MASK (0x3U)
#define AHB_SECURE_CTRL_SEC_CTRL_AHB_PORT9_SLAVE0_RULE_ADC_RULE_SHIFT (0U)
/*! ADC_RULE - ADC
 *  0b00..Non-secure and Non-priviledge user access allowed.
 *  0b01..Non-secure and Privilege access allowed.
 *  0b10..Secure and Non-priviledge user access allowed.
 *  0b11..Secure and Priviledge user access allowed.
 */
#define AHB_SECURE_CTRL_SEC_CTRL_AHB_PORT9_SLAVE0_RULE_ADC_RULE(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_CTRL_AHB_PORT9_SLAVE0_RULE_ADC_RULE_SHIFT)) & AHB_SECURE_CTRL_SEC_CTRL_AHB_PORT9_SLAVE0_RULE_ADC_RULE_MASK)

#define AHB_SECURE_CTRL_SEC_CTRL_AHB_PORT9_SLAVE0_RULE_USB_FS_HOST_RULE_MASK (0x300U)
#define AHB_SECURE_CTRL_SEC_CTRL_AHB_PORT9_SLAVE0_RULE_USB_FS_HOST_RULE_SHIFT (8U)
/*! USB_FS_HOST_RULE - USB Full Speed Host registers.
 *  0b00..Non-secure and Non-priviledge user access allowed.
 *  0b01..Non-secure and Privilege access allowed.
 *  0b10..Secure and Non-priviledge user access allowed.
 *  0b11..Secure and Priviledge user access allowed.
 */
#define AHB_SECURE_CTRL_SEC_CTRL_AHB_PORT9_SLAVE0_RULE_USB_FS_HOST_RULE(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_CTRL_AHB_PORT9_SLAVE0_RULE_USB_FS_HOST_RULE_SHIFT)) & AHB_SECURE_CTRL_SEC_CTRL_AHB_PORT9_SLAVE0_RULE_USB_FS_HOST_RULE_MASK)

#define AHB_SECURE_CTRL_SEC_CTRL_AHB_PORT9_SLAVE0_RULE_USB_HS_HOST_RULE_MASK (0x3000U)
#define AHB_SECURE_CTRL_SEC_CTRL_AHB_PORT9_SLAVE0_RULE_USB_HS_HOST_RULE_SHIFT (12U)
/*! USB_HS_HOST_RULE - USB High speed host registers
 *  0b00..Non-secure and Non-priviledge user access allowed.
 *  0b01..Non-secure and Privilege access allowed.
 *  0b10..Secure and Non-priviledge user access allowed.
 *  0b11..Secure and Priviledge user access allowed.
 */
#define AHB_SECURE_CTRL_SEC_CTRL_AHB_PORT9_SLAVE0_RULE_USB_HS_HOST_RULE(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_CTRL_AHB_PORT9_SLAVE0_RULE_USB_HS_HOST_RULE_SHIFT)) & AHB_SECURE_CTRL_SEC_CTRL_AHB_PORT9_SLAVE0_RULE_USB_HS_HOST_RULE_MASK)

#define AHB_SECURE_CTRL_SEC_CTRL_AHB_PORT9_SLAVE0_RULE_HASH_RULE_MASK (0x30000U)
#define AHB_SECURE_CTRL_SEC_CTRL_AHB_PORT9_SLAVE0_RULE_HASH_RULE_SHIFT (16U)
/*! HASH_RULE - SHA-2 crypto registers
 *  0b00..Non-secure and Non-priviledge user access allowed.
 *  0b01..Non-secure and Privilege access allowed.
 *  0b10..Secure and Non-priviledge user access allowed.
 *  0b11..Secure and Priviledge user access allowed.
 */
#define AHB_SECURE_CTRL_SEC_CTRL_AHB_PORT9_SLAVE0_RULE_HASH_RULE(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_CTRL_AHB_PORT9_SLAVE0_RULE_HASH_RULE_SHIFT)) & AHB_SECURE_CTRL_SEC_CTRL_AHB_PORT9_SLAVE0_RULE_HASH_RULE_MASK)

#define AHB_SECURE_CTRL_SEC_CTRL_AHB_PORT9_SLAVE0_RULE_CASPER_RULE_MASK (0x300000U)
#define AHB_SECURE_CTRL_SEC_CTRL_AHB_PORT9_SLAVE0_RULE_CASPER_RULE_SHIFT (20U)
/*! CASPER_RULE - RSA/ECC crypto accelerator
 *  0b00..Non-secure and Non-priviledge user access allowed.
 *  0b01..Non-secure and Privilege access allowed.
 *  0b10..Secure and Non-priviledge user access allowed.
 *  0b11..Secure and Priviledge user access allowed.
 */
#define AHB_SECURE_CTRL_SEC_CTRL_AHB_PORT9_SLAVE0_RULE_CASPER_RULE(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_CTRL_AHB_PORT9_SLAVE0_RULE_CASPER_RULE_SHIFT)) & AHB_SECURE_CTRL_SEC_CTRL_AHB_PORT9_SLAVE0_RULE_CASPER_RULE_MASK)

#define AHB_SECURE_CTRL_SEC_CTRL_AHB_PORT9_SLAVE0_RULE_DMA1_RULE_MASK (0x30000000U)
#define AHB_SECURE_CTRL_SEC_CTRL_AHB_PORT9_SLAVE0_RULE_DMA1_RULE_SHIFT (28U)
/*! DMA1_RULE - DMA Controller (Secure)
 *  0b00..Non-secure and Non-priviledge user access allowed.
 *  0b01..Non-secure and Privilege access allowed.
 *  0b10..Secure and Non-priviledge user access allowed.
 *  0b11..Secure and Priviledge user access allowed.
 */
#define AHB_SECURE_CTRL_SEC_CTRL_AHB_PORT9_SLAVE0_RULE_DMA1_RULE(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_CTRL_AHB_PORT9_SLAVE0_RULE_DMA1_RULE_SHIFT)) & AHB_SECURE_CTRL_SEC_CTRL_AHB_PORT9_SLAVE0_RULE_DMA1_RULE_MASK)
/*! @} */

/* The count of AHB_SECURE_CTRL_SEC_CTRL_AHB_PORT9_SLAVE0_RULE */
#define AHB_SECURE_CTRL_SEC_CTRL_AHB_PORT9_SLAVE0_RULE_COUNT (1U)

/*! @name SEC_CTRL_AHB_PORT9_SLAVE1_RULE - Security access rules for AHB peripherals. */
/*! @{ */

#define AHB_SECURE_CTRL_SEC_CTRL_AHB_PORT9_SLAVE1_RULE_GPIO1_RULE_MASK (0x3U)
#define AHB_SECURE_CTRL_SEC_CTRL_AHB_PORT9_SLAVE1_RULE_GPIO1_RULE_SHIFT (0U)
/*! GPIO1_RULE - Secure High Speed GPIO
 *  0b00..Non-secure and Non-priviledge user access allowed.
 *  0b01..Non-secure and Privilege access allowed.
 *  0b10..Secure and Non-priviledge user access allowed.
 *  0b11..Secure and Priviledge user access allowed.
 */
#define AHB_SECURE_CTRL_SEC_CTRL_AHB_PORT9_SLAVE1_RULE_GPIO1_RULE(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_CTRL_AHB_PORT9_SLAVE1_RULE_GPIO1_RULE_SHIFT)) & AHB_SECURE_CTRL_SEC_CTRL_AHB_PORT9_SLAVE1_RULE_GPIO1_RULE_MASK)

#define AHB_SECURE_CTRL_SEC_CTRL_AHB_PORT9_SLAVE1_RULE_AHB_SEC_CTRL_RULE_MASK (0x30U)
#define AHB_SECURE_CTRL_SEC_CTRL_AHB_PORT9_SLAVE1_RULE_AHB_SEC_CTRL_RULE_SHIFT (4U)
/*! AHB_SEC_CTRL_RULE - AHB Secure Controller
 *  0b00..Non-secure and Non-priviledge user access allowed.
 *  0b01..Non-secure and Privilege access allowed.
 *  0b10..Secure and Non-priviledge user access allowed.
 *  0b11..Secure and Priviledge user access allowed.
 */
#define AHB_SECURE_CTRL_SEC_CTRL_AHB_PORT9_SLAVE1_RULE_AHB_SEC_CTRL_RULE(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_CTRL_AHB_PORT9_SLAVE1_RULE_AHB_SEC_CTRL_RULE_SHIFT)) & AHB_SECURE_CTRL_SEC_CTRL_AHB_PORT9_SLAVE1_RULE_AHB_SEC_CTRL_RULE_MASK)
/*! @} */

/* The count of AHB_SECURE_CTRL_SEC_CTRL_AHB_PORT9_SLAVE1_RULE */
#define AHB_SECURE_CTRL_SEC_CTRL_AHB_PORT9_SLAVE1_RULE_COUNT (1U)

/*! @name SEC_CTRL_AHB_SEC_CTRL_MEM_RULE - Security access rules for AHB_SEC_CTRL_AHB. */
/*! @{ */

#define AHB_SECURE_CTRL_SEC_CTRL_AHB_SEC_CTRL_MEM_RULE_AHB_SEC_CTRL_SECT_0_RULE_MASK (0x3U)
#define AHB_SECURE_CTRL_SEC_CTRL_AHB_SEC_CTRL_MEM_RULE_AHB_SEC_CTRL_SECT_0_RULE_SHIFT (0U)
/*! AHB_SEC_CTRL_SECT_0_RULE - Address space: 0x400A_0000 - 0x400A_CFFF
 *  0b00..Non-secure and Non-priviledge user access allowed.
 *  0b01..Non-secure and Privilege access allowed.
 *  0b10..Secure and Non-priviledge user access allowed.
 *  0b11..Secure and Priviledge user access allowed.
 */
#define AHB_SECURE_CTRL_SEC_CTRL_AHB_SEC_CTRL_MEM_RULE_AHB_SEC_CTRL_SECT_0_RULE(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_CTRL_AHB_SEC_CTRL_MEM_RULE_AHB_SEC_CTRL_SECT_0_RULE_SHIFT)) & AHB_SECURE_CTRL_SEC_CTRL_AHB_SEC_CTRL_MEM_RULE_AHB_SEC_CTRL_SECT_0_RULE_MASK)

#define AHB_SECURE_CTRL_SEC_CTRL_AHB_SEC_CTRL_MEM_RULE_AHB_SEC_CTRL_SECT_1_RULE_MASK (0x30U)
#define AHB_SECURE_CTRL_SEC_CTRL_AHB_SEC_CTRL_MEM_RULE_AHB_SEC_CTRL_SECT_1_RULE_SHIFT (4U)
/*! AHB_SEC_CTRL_SECT_1_RULE - Address space: 0x400A_D000 - 0x400A_DFFF
 *  0b00..Non-secure and Non-priviledge user access allowed.
 *  0b01..Non-secure and Privilege access allowed.
 *  0b10..Secure and Non-priviledge user access allowed.
 *  0b11..Secure and Priviledge user access allowed.
 */
#define AHB_SECURE_CTRL_SEC_CTRL_AHB_SEC_CTRL_MEM_RULE_AHB_SEC_CTRL_SECT_1_RULE(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_CTRL_AHB_SEC_CTRL_MEM_RULE_AHB_SEC_CTRL_SECT_1_RULE_SHIFT)) & AHB_SECURE_CTRL_SEC_CTRL_AHB_SEC_CTRL_MEM_RULE_AHB_SEC_CTRL_SECT_1_RULE_MASK)

#define AHB_SECURE_CTRL_SEC_CTRL_AHB_SEC_CTRL_MEM_RULE_AHB_SEC_CTRL_SECT_2_RULE_MASK (0x300U)
#define AHB_SECURE_CTRL_SEC_CTRL_AHB_SEC_CTRL_MEM_RULE_AHB_SEC_CTRL_SECT_2_RULE_SHIFT (8U)
/*! AHB_SEC_CTRL_SECT_2_RULE - Address space: 0x400A_E000 - 0x400A_EFFF
 *  0b00..Non-secure and Non-priviledge user access allowed.
 *  0b01..Non-secure and Privilege access allowed.
 *  0b10..Secure and Non-priviledge user access allowed.
 *  0b11..Secure and Priviledge user access allowed.
 */
#define AHB_SECURE_CTRL_SEC_CTRL_AHB_SEC_CTRL_MEM_RULE_AHB_SEC_CTRL_SECT_2_RULE(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_CTRL_AHB_SEC_CTRL_MEM_RULE_AHB_SEC_CTRL_SECT_2_RULE_SHIFT)) & AHB_SECURE_CTRL_SEC_CTRL_AHB_SEC_CTRL_MEM_RULE_AHB_SEC_CTRL_SECT_2_RULE_MASK)

#define AHB_SECURE_CTRL_SEC_CTRL_AHB_SEC_CTRL_MEM_RULE_AHB_SEC_CTRL_SECT_3_RULE_MASK (0x3000U)
#define AHB_SECURE_CTRL_SEC_CTRL_AHB_SEC_CTRL_MEM_RULE_AHB_SEC_CTRL_SECT_3_RULE_SHIFT (12U)
/*! AHB_SEC_CTRL_SECT_3_RULE - Address space: 0x400A_F000 - 0x400A_FFFF
 *  0b00..Non-secure and Non-priviledge user access allowed.
 *  0b01..Non-secure and Privilege access allowed.
 *  0b10..Secure and Non-priviledge user access allowed.
 *  0b11..Secure and Priviledge user access allowed.
 */
#define AHB_SECURE_CTRL_SEC_CTRL_AHB_SEC_CTRL_MEM_RULE_AHB_SEC_CTRL_SECT_3_RULE(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_CTRL_AHB_SEC_CTRL_MEM_RULE_AHB_SEC_CTRL_SECT_3_RULE_SHIFT)) & AHB_SECURE_CTRL_SEC_CTRL_AHB_SEC_CTRL_MEM_RULE_AHB_SEC_CTRL_SECT_3_RULE_MASK)
/*! @} */

/* The count of AHB_SECURE_CTRL_SEC_CTRL_AHB_SEC_CTRL_MEM_RULE */
#define AHB_SECURE_CTRL_SEC_CTRL_AHB_SEC_CTRL_MEM_RULE_COUNT (1U)

/* The count of AHB_SECURE_CTRL_SEC_CTRL_AHB_SEC_CTRL_MEM_RULE */
#define AHB_SECURE_CTRL_SEC_CTRL_AHB_SEC_CTRL_MEM_RULE_COUNT2 (1U)

/*! @name SEC_VIO_ADDR - most recent security violation address for AHB layer n */
/*! @{ */

#define AHB_SECURE_CTRL_SEC_VIO_ADDR_SEC_VIO_ADDR_MASK (0xFFFFFFFFU)
#define AHB_SECURE_CTRL_SEC_VIO_ADDR_SEC_VIO_ADDR_SHIFT (0U)
/*! SEC_VIO_ADDR - security violation address for AHB layer */
#define AHB_SECURE_CTRL_SEC_VIO_ADDR_SEC_VIO_ADDR(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_VIO_ADDR_SEC_VIO_ADDR_SHIFT)) & AHB_SECURE_CTRL_SEC_VIO_ADDR_SEC_VIO_ADDR_MASK)
/*! @} */

/*! @name SEC_VIO_MISC_INFO - most recent security violation miscellaneous information for AHB layer n */
/*! @{ */

#define AHB_SECURE_CTRL_SEC_VIO_MISC_INFO_SEC_VIO_INFO_WRITE_MASK (0x1U)
#define AHB_SECURE_CTRL_SEC_VIO_MISC_INFO_SEC_VIO_INFO_WRITE_SHIFT (0U)
/*! SEC_VIO_INFO_WRITE - security violation access read/write indicator.
 *  0b0..Read access.
 *  0b1..Write access.
 */
#define AHB_SECURE_CTRL_SEC_VIO_MISC_INFO_SEC_VIO_INFO_WRITE(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_VIO_MISC_INFO_SEC_VIO_INFO_WRITE_SHIFT)) & AHB_SECURE_CTRL_SEC_VIO_MISC_INFO_SEC_VIO_INFO_WRITE_MASK)

#define AHB_SECURE_CTRL_SEC_VIO_MISC_INFO_SEC_VIO_INFO_DATA_ACCESS_MASK (0x2U)
#define AHB_SECURE_CTRL_SEC_VIO_MISC_INFO_SEC_VIO_INFO_DATA_ACCESS_SHIFT (1U)
/*! SEC_VIO_INFO_DATA_ACCESS - security violation access data/code indicator.
 *  0b0..Code access.
 *  0b1..Data access.
 */
#define AHB_SECURE_CTRL_SEC_VIO_MISC_INFO_SEC_VIO_INFO_DATA_ACCESS(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_VIO_MISC_INFO_SEC_VIO_INFO_DATA_ACCESS_SHIFT)) & AHB_SECURE_CTRL_SEC_VIO_MISC_INFO_SEC_VIO_INFO_DATA_ACCESS_MASK)

#define AHB_SECURE_CTRL_SEC_VIO_MISC_INFO_SEC_VIO_INFO_MASTER_SEC_LEVEL_MASK (0xF0U)
#define AHB_SECURE_CTRL_SEC_VIO_MISC_INFO_SEC_VIO_INFO_MASTER_SEC_LEVEL_SHIFT (4U)
/*! SEC_VIO_INFO_MASTER_SEC_LEVEL - bit [5:4]: master sec level and privilege level bit [7:6]: anti-pol value for master sec level and privilege level */
#define AHB_SECURE_CTRL_SEC_VIO_MISC_INFO_SEC_VIO_INFO_MASTER_SEC_LEVEL(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_VIO_MISC_INFO_SEC_VIO_INFO_MASTER_SEC_LEVEL_SHIFT)) & AHB_SECURE_CTRL_SEC_VIO_MISC_INFO_SEC_VIO_INFO_MASTER_SEC_LEVEL_MASK)

#define AHB_SECURE_CTRL_SEC_VIO_MISC_INFO_SEC_VIO_INFO_MASTER_MASK (0xF00U)
#define AHB_SECURE_CTRL_SEC_VIO_MISC_INFO_SEC_VIO_INFO_MASTER_SHIFT (8U)
/*! SEC_VIO_INFO_MASTER - security violation master number
 *  0b0000..CPU0 Code.
 *  0b0001..CPU0 System.
 *  0b0100..USB-HS Device.
 *  0b0101..SDMA0.
 *  0b1010..HASH.
 *  0b1011..USB-FS Host.
 *  0b1100..SDMA1.
 *  0b1101..CAN-FD.
 */
#define AHB_SECURE_CTRL_SEC_VIO_MISC_INFO_SEC_VIO_INFO_MASTER(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_VIO_MISC_INFO_SEC_VIO_INFO_MASTER_SHIFT)) & AHB_SECURE_CTRL_SEC_VIO_MISC_INFO_SEC_VIO_INFO_MASTER_MASK)
/*! @} */

/*! @name SEC_VIO_INFO_VALID - security violation address/information registers valid flags */
/*! @{ */

#define AHB_SECURE_CTRL_SEC_VIO_INFO_VALID_VIO_INFO_VALID0_MASK (0x1U)
#define AHB_SECURE_CTRL_SEC_VIO_INFO_VALID_VIO_INFO_VALID0_SHIFT (0U)
/*! VIO_INFO_VALID0 - violation information valid flag for AHB port 0. Write 1 to clear.
 *  0b0..Not valid.
 *  0b1..Valid (violation occurred).
 */
#define AHB_SECURE_CTRL_SEC_VIO_INFO_VALID_VIO_INFO_VALID0(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_VIO_INFO_VALID_VIO_INFO_VALID0_SHIFT)) & AHB_SECURE_CTRL_SEC_VIO_INFO_VALID_VIO_INFO_VALID0_MASK)

#define AHB_SECURE_CTRL_SEC_VIO_INFO_VALID_VIO_INFO_VALID1_MASK (0x2U)
#define AHB_SECURE_CTRL_SEC_VIO_INFO_VALID_VIO_INFO_VALID1_SHIFT (1U)
/*! VIO_INFO_VALID1 - violation information valid flag for AHB port 1. Write 1 to clear.
 *  0b0..Not valid.
 *  0b1..Valid (violation occurred).
 */
#define AHB_SECURE_CTRL_SEC_VIO_INFO_VALID_VIO_INFO_VALID1(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_VIO_INFO_VALID_VIO_INFO_VALID1_SHIFT)) & AHB_SECURE_CTRL_SEC_VIO_INFO_VALID_VIO_INFO_VALID1_MASK)

#define AHB_SECURE_CTRL_SEC_VIO_INFO_VALID_VIO_INFO_VALID2_MASK (0x4U)
#define AHB_SECURE_CTRL_SEC_VIO_INFO_VALID_VIO_INFO_VALID2_SHIFT (2U)
/*! VIO_INFO_VALID2 - violation information valid flag for AHB port 2. Write 1 to clear.
 *  0b0..Not valid.
 *  0b1..Valid (violation occurred).
 */
#define AHB_SECURE_CTRL_SEC_VIO_INFO_VALID_VIO_INFO_VALID2(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_VIO_INFO_VALID_VIO_INFO_VALID2_SHIFT)) & AHB_SECURE_CTRL_SEC_VIO_INFO_VALID_VIO_INFO_VALID2_MASK)

#define AHB_SECURE_CTRL_SEC_VIO_INFO_VALID_VIO_INFO_VALID3_MASK (0x8U)
#define AHB_SECURE_CTRL_SEC_VIO_INFO_VALID_VIO_INFO_VALID3_SHIFT (3U)
/*! VIO_INFO_VALID3 - violation information valid flag for AHB port 3. Write 1 to clear.
 *  0b0..Not valid.
 *  0b1..Valid (violation occurred).
 */
#define AHB_SECURE_CTRL_SEC_VIO_INFO_VALID_VIO_INFO_VALID3(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_VIO_INFO_VALID_VIO_INFO_VALID3_SHIFT)) & AHB_SECURE_CTRL_SEC_VIO_INFO_VALID_VIO_INFO_VALID3_MASK)

#define AHB_SECURE_CTRL_SEC_VIO_INFO_VALID_VIO_INFO_VALID4_MASK (0x10U)
#define AHB_SECURE_CTRL_SEC_VIO_INFO_VALID_VIO_INFO_VALID4_SHIFT (4U)
/*! VIO_INFO_VALID4 - violation information valid flag for AHB port 4. Write 1 to clear.
 *  0b0..Not valid.
 *  0b1..Valid (violation occurred).
 */
#define AHB_SECURE_CTRL_SEC_VIO_INFO_VALID_VIO_INFO_VALID4(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_VIO_INFO_VALID_VIO_INFO_VALID4_SHIFT)) & AHB_SECURE_CTRL_SEC_VIO_INFO_VALID_VIO_INFO_VALID4_MASK)

#define AHB_SECURE_CTRL_SEC_VIO_INFO_VALID_VIO_INFO_VALID5_MASK (0x20U)
#define AHB_SECURE_CTRL_SEC_VIO_INFO_VALID_VIO_INFO_VALID5_SHIFT (5U)
/*! VIO_INFO_VALID5 - violation information valid flag for AHB port 5. Write 1 to clear.
 *  0b0..Not valid.
 *  0b1..Valid (violation occurred).
 */
#define AHB_SECURE_CTRL_SEC_VIO_INFO_VALID_VIO_INFO_VALID5(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_VIO_INFO_VALID_VIO_INFO_VALID5_SHIFT)) & AHB_SECURE_CTRL_SEC_VIO_INFO_VALID_VIO_INFO_VALID5_MASK)

#define AHB_SECURE_CTRL_SEC_VIO_INFO_VALID_VIO_INFO_VALID6_MASK (0x40U)
#define AHB_SECURE_CTRL_SEC_VIO_INFO_VALID_VIO_INFO_VALID6_SHIFT (6U)
/*! VIO_INFO_VALID6 - violation information valid flag for AHB port 6. Write 1 to clear.
 *  0b0..Not valid.
 *  0b1..Valid (violation occurred).
 */
#define AHB_SECURE_CTRL_SEC_VIO_INFO_VALID_VIO_INFO_VALID6(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_VIO_INFO_VALID_VIO_INFO_VALID6_SHIFT)) & AHB_SECURE_CTRL_SEC_VIO_INFO_VALID_VIO_INFO_VALID6_MASK)

#define AHB_SECURE_CTRL_SEC_VIO_INFO_VALID_VIO_INFO_VALID7_MASK (0x80U)
#define AHB_SECURE_CTRL_SEC_VIO_INFO_VALID_VIO_INFO_VALID7_SHIFT (7U)
/*! VIO_INFO_VALID7 - violation information valid flag for AHB port 7. Write 1 to clear.
 *  0b0..Not valid.
 *  0b1..Valid (violation occurred).
 */
#define AHB_SECURE_CTRL_SEC_VIO_INFO_VALID_VIO_INFO_VALID7(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_VIO_INFO_VALID_VIO_INFO_VALID7_SHIFT)) & AHB_SECURE_CTRL_SEC_VIO_INFO_VALID_VIO_INFO_VALID7_MASK)

#define AHB_SECURE_CTRL_SEC_VIO_INFO_VALID_VIO_INFO_VALID8_MASK (0x100U)
#define AHB_SECURE_CTRL_SEC_VIO_INFO_VALID_VIO_INFO_VALID8_SHIFT (8U)
/*! VIO_INFO_VALID8 - violation information valid flag for AHB port 8. Write 1 to clear.
 *  0b0..Not valid.
 *  0b1..Valid (violation occurred).
 */
#define AHB_SECURE_CTRL_SEC_VIO_INFO_VALID_VIO_INFO_VALID8(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_VIO_INFO_VALID_VIO_INFO_VALID8_SHIFT)) & AHB_SECURE_CTRL_SEC_VIO_INFO_VALID_VIO_INFO_VALID8_MASK)

#define AHB_SECURE_CTRL_SEC_VIO_INFO_VALID_VIO_INFO_VALID9_MASK (0x200U)
#define AHB_SECURE_CTRL_SEC_VIO_INFO_VALID_VIO_INFO_VALID9_SHIFT (9U)
/*! VIO_INFO_VALID9 - violation information valid flag for AHB port 9. Write 1 to clear.
 *  0b0..Not valid.
 *  0b1..Valid (violation occurred).
 */
#define AHB_SECURE_CTRL_SEC_VIO_INFO_VALID_VIO_INFO_VALID9(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_VIO_INFO_VALID_VIO_INFO_VALID9_SHIFT)) & AHB_SECURE_CTRL_SEC_VIO_INFO_VALID_VIO_INFO_VALID9_MASK)
/*! @} */

/*! @name SEC_GPIO_MASK0 - Secure GPIO mask for port 0 pins. */
/*! @{ */

#define AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN0_SEC_MASK_MASK (0x1U)
#define AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN0_SEC_MASK_SHIFT (0U)
/*! PIO0_PIN0_SEC_MASK - Secure mask for pin P0_0
 *  0b1..Pin state is readable by non-secure world.
 *  0b0..Pin state is blocked to non-secure world.
 */
#define AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN0_SEC_MASK(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN0_SEC_MASK_SHIFT)) & AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN0_SEC_MASK_MASK)

#define AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN1_SEC_MASK_MASK (0x2U)
#define AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN1_SEC_MASK_SHIFT (1U)
/*! PIO0_PIN1_SEC_MASK - Secure mask for pin P0_1
 *  0b1..Pin state is readable by non-secure world.
 *  0b0..Pin state is blocked to non-secure world.
 */
#define AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN1_SEC_MASK(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN1_SEC_MASK_SHIFT)) & AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN1_SEC_MASK_MASK)

#define AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN2_SEC_MASK_MASK (0x4U)
#define AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN2_SEC_MASK_SHIFT (2U)
/*! PIO0_PIN2_SEC_MASK - Secure mask for pin P0_2
 *  0b1..Pin state is readable by non-secure world.
 *  0b0..Pin state is blocked to non-secure world.
 */
#define AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN2_SEC_MASK(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN2_SEC_MASK_SHIFT)) & AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN2_SEC_MASK_MASK)

#define AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN3_SEC_MASK_MASK (0x8U)
#define AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN3_SEC_MASK_SHIFT (3U)
/*! PIO0_PIN3_SEC_MASK - Secure mask for pin P0_3
 *  0b1..Pin state is readable by non-secure world.
 *  0b0..Pin state is blocked to non-secure world.
 */
#define AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN3_SEC_MASK(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN3_SEC_MASK_SHIFT)) & AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN3_SEC_MASK_MASK)

#define AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN4_SEC_MASK_MASK (0x10U)
#define AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN4_SEC_MASK_SHIFT (4U)
/*! PIO0_PIN4_SEC_MASK - Secure mask for pin P0_4
 *  0b1..Pin state is readable by non-secure world.
 *  0b0..Pin state is blocked to non-secure world.
 */
#define AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN4_SEC_MASK(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN4_SEC_MASK_SHIFT)) & AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN4_SEC_MASK_MASK)

#define AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN5_SEC_MASK_MASK (0x20U)
#define AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN5_SEC_MASK_SHIFT (5U)
/*! PIO0_PIN5_SEC_MASK - Secure mask for pin P0_5
 *  0b1..Pin state is readable by non-secure world.
 *  0b0..Pin state is blocked to non-secure world.
 */
#define AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN5_SEC_MASK(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN5_SEC_MASK_SHIFT)) & AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN5_SEC_MASK_MASK)

#define AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN6_SEC_MASK_MASK (0x40U)
#define AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN6_SEC_MASK_SHIFT (6U)
/*! PIO0_PIN6_SEC_MASK - Secure mask for pin P0_6
 *  0b1..Pin state is readable by non-secure world.
 *  0b0..Pin state is blocked to non-secure world.
 */
#define AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN6_SEC_MASK(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN6_SEC_MASK_SHIFT)) & AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN6_SEC_MASK_MASK)

#define AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN7_SEC_MASK_MASK (0x80U)
#define AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN7_SEC_MASK_SHIFT (7U)
/*! PIO0_PIN7_SEC_MASK - Secure mask for pin P0_7
 *  0b1..Pin state is readable by non-secure world.
 *  0b0..Pin state is blocked to non-secure world.
 */
#define AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN7_SEC_MASK(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN7_SEC_MASK_SHIFT)) & AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN7_SEC_MASK_MASK)

#define AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN8_SEC_MASK_MASK (0x100U)
#define AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN8_SEC_MASK_SHIFT (8U)
/*! PIO0_PIN8_SEC_MASK - Secure mask for pin P0_8
 *  0b1..Pin state is readable by non-secure world.
 *  0b0..Pin state is blocked to non-secure world.
 */
#define AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN8_SEC_MASK(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN8_SEC_MASK_SHIFT)) & AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN8_SEC_MASK_MASK)

#define AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN9_SEC_MASK_MASK (0x200U)
#define AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN9_SEC_MASK_SHIFT (9U)
/*! PIO0_PIN9_SEC_MASK - Secure mask for pin P0_9
 *  0b1..Pin state is readable by non-secure world.
 *  0b0..Pin state is blocked to non-secure world.
 */
#define AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN9_SEC_MASK(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN9_SEC_MASK_SHIFT)) & AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN9_SEC_MASK_MASK)

#define AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN10_SEC_MASK_MASK (0x400U)
#define AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN10_SEC_MASK_SHIFT (10U)
/*! PIO0_PIN10_SEC_MASK - Secure mask for pin P0_10
 *  0b1..Pin state is readable by non-secure world.
 *  0b0..Pin state is blocked to non-secure world.
 */
#define AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN10_SEC_MASK(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN10_SEC_MASK_SHIFT)) & AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN10_SEC_MASK_MASK)

#define AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN11_SEC_MASK_MASK (0x800U)
#define AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN11_SEC_MASK_SHIFT (11U)
/*! PIO0_PIN11_SEC_MASK - Secure mask for pin P0_11
 *  0b1..Pin state is readable by non-secure world.
 *  0b0..Pin state is blocked to non-secure world.
 */
#define AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN11_SEC_MASK(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN11_SEC_MASK_SHIFT)) & AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN11_SEC_MASK_MASK)

#define AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN12_SEC_MASK_MASK (0x1000U)
#define AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN12_SEC_MASK_SHIFT (12U)
/*! PIO0_PIN12_SEC_MASK - Secure mask for pin P0_12
 *  0b1..Pin state is readable by non-secure world.
 *  0b0..Pin state is blocked to non-secure world.
 */
#define AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN12_SEC_MASK(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN12_SEC_MASK_SHIFT)) & AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN12_SEC_MASK_MASK)

#define AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN13_SEC_MASK_MASK (0x2000U)
#define AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN13_SEC_MASK_SHIFT (13U)
/*! PIO0_PIN13_SEC_MASK - Secure mask for pin P0_13
 *  0b1..Pin state is readable by non-secure world.
 *  0b0..Pin state is blocked to non-secure world.
 */
#define AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN13_SEC_MASK(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN13_SEC_MASK_SHIFT)) & AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN13_SEC_MASK_MASK)

#define AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN14_SEC_MASK_MASK (0x4000U)
#define AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN14_SEC_MASK_SHIFT (14U)
/*! PIO0_PIN14_SEC_MASK - Secure mask for pin P0_14
 *  0b1..Pin state is readable by non-secure world.
 *  0b0..Pin state is blocked to non-secure world.
 */
#define AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN14_SEC_MASK(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN14_SEC_MASK_SHIFT)) & AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN14_SEC_MASK_MASK)

#define AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN15_SEC_MASK_MASK (0x8000U)
#define AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN15_SEC_MASK_SHIFT (15U)
/*! PIO0_PIN15_SEC_MASK - Secure mask for pin P0_15
 *  0b1..Pin state is readable by non-secure world.
 *  0b0..Pin state is blocked to non-secure world.
 */
#define AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN15_SEC_MASK(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN15_SEC_MASK_SHIFT)) & AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN15_SEC_MASK_MASK)

#define AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN16_SEC_MASK_MASK (0x10000U)
#define AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN16_SEC_MASK_SHIFT (16U)
/*! PIO0_PIN16_SEC_MASK - Secure mask for pin P0_16
 *  0b1..Pin state is readable by non-secure world.
 *  0b0..Pin state is blocked to non-secure world.
 */
#define AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN16_SEC_MASK(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN16_SEC_MASK_SHIFT)) & AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN16_SEC_MASK_MASK)

#define AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN17_SEC_MASK_MASK (0x20000U)
#define AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN17_SEC_MASK_SHIFT (17U)
/*! PIO0_PIN17_SEC_MASK - Secure mask for pin P0_17
 *  0b1..Pin state is readable by non-secure world.
 *  0b0..Pin state is blocked to non-secure world.
 */
#define AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN17_SEC_MASK(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN17_SEC_MASK_SHIFT)) & AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN17_SEC_MASK_MASK)

#define AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN18_SEC_MASK_MASK (0x40000U)
#define AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN18_SEC_MASK_SHIFT (18U)
/*! PIO0_PIN18_SEC_MASK - Secure mask for pin P0_18
 *  0b1..Pin state is readable by non-secure world.
 *  0b0..Pin state is blocked to non-secure world.
 */
#define AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN18_SEC_MASK(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN18_SEC_MASK_SHIFT)) & AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN18_SEC_MASK_MASK)

#define AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN19_SEC_MASK_MASK (0x80000U)
#define AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN19_SEC_MASK_SHIFT (19U)
/*! PIO0_PIN19_SEC_MASK - Secure mask for pin P0_19
 *  0b1..Pin state is readable by non-secure world.
 *  0b0..Pin state is blocked to non-secure world.
 */
#define AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN19_SEC_MASK(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN19_SEC_MASK_SHIFT)) & AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN19_SEC_MASK_MASK)

#define AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN20_SEC_MASK_MASK (0x100000U)
#define AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN20_SEC_MASK_SHIFT (20U)
/*! PIO0_PIN20_SEC_MASK - Secure mask for pin P0_20
 *  0b1..Pin state is readable by non-secure world.
 *  0b0..Pin state is blocked to non-secure world.
 */
#define AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN20_SEC_MASK(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN20_SEC_MASK_SHIFT)) & AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN20_SEC_MASK_MASK)

#define AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN21_SEC_MASK_MASK (0x200000U)
#define AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN21_SEC_MASK_SHIFT (21U)
/*! PIO0_PIN21_SEC_MASK - Secure mask for pin P0_21
 *  0b1..Pin state is readable by non-secure world.
 *  0b0..Pin state is blocked to non-secure world.
 */
#define AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN21_SEC_MASK(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN21_SEC_MASK_SHIFT)) & AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN21_SEC_MASK_MASK)

#define AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN22_SEC_MASK_MASK (0x400000U)
#define AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN22_SEC_MASK_SHIFT (22U)
/*! PIO0_PIN22_SEC_MASK - Secure mask for pin P0_22
 *  0b1..Pin state is readable by non-secure world.
 *  0b0..Pin state is blocked to non-secure world.
 */
#define AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN22_SEC_MASK(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN22_SEC_MASK_SHIFT)) & AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN22_SEC_MASK_MASK)

#define AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN23_SEC_MASK_MASK (0x800000U)
#define AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN23_SEC_MASK_SHIFT (23U)
/*! PIO0_PIN23_SEC_MASK - Secure mask for pin P0_23
 *  0b1..Pin state is readable by non-secure world.
 *  0b0..Pin state is blocked to non-secure world.
 */
#define AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN23_SEC_MASK(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN23_SEC_MASK_SHIFT)) & AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN23_SEC_MASK_MASK)

#define AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN24_SEC_MASK_MASK (0x1000000U)
#define AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN24_SEC_MASK_SHIFT (24U)
/*! PIO0_PIN24_SEC_MASK - Secure mask for pin P0_24
 *  0b1..Pin state is readable by non-secure world.
 *  0b0..Pin state is blocked to non-secure world.
 */
#define AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN24_SEC_MASK(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN24_SEC_MASK_SHIFT)) & AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN24_SEC_MASK_MASK)

#define AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN25_SEC_MASK_MASK (0x2000000U)
#define AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN25_SEC_MASK_SHIFT (25U)
/*! PIO0_PIN25_SEC_MASK - Secure mask for pin P0_25
 *  0b1..Pin state is readable by non-secure world.
 *  0b0..Pin state is blocked to non-secure world.
 */
#define AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN25_SEC_MASK(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN25_SEC_MASK_SHIFT)) & AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN25_SEC_MASK_MASK)

#define AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN26_SEC_MASK_MASK (0x4000000U)
#define AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN26_SEC_MASK_SHIFT (26U)
/*! PIO0_PIN26_SEC_MASK - Secure mask for pin P0_26
 *  0b1..Pin state is readable by non-secure world.
 *  0b0..Pin state is blocked to non-secure world.
 */
#define AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN26_SEC_MASK(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN26_SEC_MASK_SHIFT)) & AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN26_SEC_MASK_MASK)

#define AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN27_SEC_MASK_MASK (0x8000000U)
#define AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN27_SEC_MASK_SHIFT (27U)
/*! PIO0_PIN27_SEC_MASK - Secure mask for pin P0_27
 *  0b1..Pin state is readable by non-secure world.
 *  0b0..Pin state is blocked to non-secure world.
 */
#define AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN27_SEC_MASK(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN27_SEC_MASK_SHIFT)) & AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN27_SEC_MASK_MASK)

#define AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN28_SEC_MASK_MASK (0x10000000U)
#define AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN28_SEC_MASK_SHIFT (28U)
/*! PIO0_PIN28_SEC_MASK - Secure mask for pin P0_28
 *  0b1..Pin state is readable by non-secure world.
 *  0b0..Pin state is blocked to non-secure world.
 */
#define AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN28_SEC_MASK(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN28_SEC_MASK_SHIFT)) & AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN28_SEC_MASK_MASK)

#define AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN29_SEC_MASK_MASK (0x20000000U)
#define AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN29_SEC_MASK_SHIFT (29U)
/*! PIO0_PIN29_SEC_MASK - Secure mask for pin P0_29
 *  0b1..Pin state is readable by non-secure world.
 *  0b0..Pin state is blocked to non-secure world.
 */
#define AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN29_SEC_MASK(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN29_SEC_MASK_SHIFT)) & AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN29_SEC_MASK_MASK)

#define AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN30_SEC_MASK_MASK (0x40000000U)
#define AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN30_SEC_MASK_SHIFT (30U)
/*! PIO0_PIN30_SEC_MASK - Secure mask for pin P0_30
 *  0b1..Pin state is readable by non-secure world.
 *  0b0..Pin state is blocked to non-secure world.
 */
#define AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN30_SEC_MASK(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN30_SEC_MASK_SHIFT)) & AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN30_SEC_MASK_MASK)

#define AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN31_SEC_MASK_MASK (0x80000000U)
#define AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN31_SEC_MASK_SHIFT (31U)
/*! PIO0_PIN31_SEC_MASK - Secure mask for pin P0_31
 *  0b1..Pin state is readable by non-secure world.
 *  0b0..Pin state is blocked to non-secure world.
 */
#define AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN31_SEC_MASK(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN31_SEC_MASK_SHIFT)) & AHB_SECURE_CTRL_SEC_GPIO_MASK0_PIO0_PIN31_SEC_MASK_MASK)
/*! @} */

/*! @name SEC_GPIO_MASK1 - Secure GPIO mask for port 1 pins. */
/*! @{ */

#define AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN0_SEC_MASK_MASK (0x1U)
#define AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN0_SEC_MASK_SHIFT (0U)
/*! PIO1_PIN0_SEC_MASK - Secure mask for pin P1_0
 *  0b1..Pin state is readable by non-secure world.
 *  0b0..Pin state is blocked to non-secure world.
 */
#define AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN0_SEC_MASK(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN0_SEC_MASK_SHIFT)) & AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN0_SEC_MASK_MASK)

#define AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN1_SEC_MASK_MASK (0x2U)
#define AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN1_SEC_MASK_SHIFT (1U)
/*! PIO1_PIN1_SEC_MASK - Secure mask for pin P1_1
 *  0b1..Pin state is readable by non-secure world.
 *  0b0..Pin state is blocked to non-secure world.
 */
#define AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN1_SEC_MASK(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN1_SEC_MASK_SHIFT)) & AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN1_SEC_MASK_MASK)

#define AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN2_SEC_MASK_MASK (0x4U)
#define AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN2_SEC_MASK_SHIFT (2U)
/*! PIO1_PIN2_SEC_MASK - Secure mask for pin P1_2
 *  0b1..Pin state is readable by non-secure world.
 *  0b0..Pin state is blocked to non-secure world.
 */
#define AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN2_SEC_MASK(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN2_SEC_MASK_SHIFT)) & AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN2_SEC_MASK_MASK)

#define AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN3_SEC_MASK_MASK (0x8U)
#define AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN3_SEC_MASK_SHIFT (3U)
/*! PIO1_PIN3_SEC_MASK - Secure mask for pin P1_3
 *  0b1..Pin state is readable by non-secure world.
 *  0b0..Pin state is blocked to non-secure world.
 */
#define AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN3_SEC_MASK(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN3_SEC_MASK_SHIFT)) & AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN3_SEC_MASK_MASK)

#define AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN4_SEC_MASK_MASK (0x10U)
#define AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN4_SEC_MASK_SHIFT (4U)
/*! PIO1_PIN4_SEC_MASK - Secure mask for pin P1_4
 *  0b1..Pin state is readable by non-secure world.
 *  0b0..Pin state is blocked to non-secure world.
 */
#define AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN4_SEC_MASK(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN4_SEC_MASK_SHIFT)) & AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN4_SEC_MASK_MASK)

#define AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN5_SEC_MASK_MASK (0x20U)
#define AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN5_SEC_MASK_SHIFT (5U)
/*! PIO1_PIN5_SEC_MASK - Secure mask for pin P1_5
 *  0b1..Pin state is readable by non-secure world.
 *  0b0..Pin state is blocked to non-secure world.
 */
#define AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN5_SEC_MASK(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN5_SEC_MASK_SHIFT)) & AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN5_SEC_MASK_MASK)

#define AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN6_SEC_MASK_MASK (0x40U)
#define AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN6_SEC_MASK_SHIFT (6U)
/*! PIO1_PIN6_SEC_MASK - Secure mask for pin P1_6
 *  0b1..Pin state is readable by non-secure world.
 *  0b0..Pin state is blocked to non-secure world.
 */
#define AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN6_SEC_MASK(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN6_SEC_MASK_SHIFT)) & AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN6_SEC_MASK_MASK)

#define AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN7_SEC_MASK_MASK (0x80U)
#define AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN7_SEC_MASK_SHIFT (7U)
/*! PIO1_PIN7_SEC_MASK - Secure mask for pin P1_7
 *  0b1..Pin state is readable by non-secure world.
 *  0b0..Pin state is blocked to non-secure world.
 */
#define AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN7_SEC_MASK(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN7_SEC_MASK_SHIFT)) & AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN7_SEC_MASK_MASK)

#define AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN8_SEC_MASK_MASK (0x100U)
#define AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN8_SEC_MASK_SHIFT (8U)
/*! PIO1_PIN8_SEC_MASK - Secure mask for pin P1_8
 *  0b1..Pin state is readable by non-secure world.
 *  0b0..Pin state is blocked to non-secure world.
 */
#define AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN8_SEC_MASK(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN8_SEC_MASK_SHIFT)) & AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN8_SEC_MASK_MASK)

#define AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN9_SEC_MASK_MASK (0x200U)
#define AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN9_SEC_MASK_SHIFT (9U)
/*! PIO1_PIN9_SEC_MASK - Secure mask for pin P1_9
 *  0b1..Pin state is readable by non-secure world.
 *  0b0..Pin state is blocked to non-secure world.
 */
#define AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN9_SEC_MASK(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN9_SEC_MASK_SHIFT)) & AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN9_SEC_MASK_MASK)

#define AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN10_SEC_MASK_MASK (0x400U)
#define AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN10_SEC_MASK_SHIFT (10U)
/*! PIO1_PIN10_SEC_MASK - Secure mask for pin P1_10
 *  0b1..Pin state is readable by non-secure world.
 *  0b0..Pin state is blocked to non-secure world.
 */
#define AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN10_SEC_MASK(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN10_SEC_MASK_SHIFT)) & AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN10_SEC_MASK_MASK)

#define AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN11_SEC_MASK_MASK (0x800U)
#define AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN11_SEC_MASK_SHIFT (11U)
/*! PIO1_PIN11_SEC_MASK - Secure mask for pin P1_11
 *  0b1..Pin state is readable by non-secure world.
 *  0b0..Pin state is blocked to non-secure world.
 */
#define AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN11_SEC_MASK(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN11_SEC_MASK_SHIFT)) & AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN11_SEC_MASK_MASK)

#define AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN12_SEC_MASK_MASK (0x1000U)
#define AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN12_SEC_MASK_SHIFT (12U)
/*! PIO1_PIN12_SEC_MASK - Secure mask for pin P1_12
 *  0b1..Pin state is readable by non-secure world.
 *  0b0..Pin state is blocked to non-secure world.
 */
#define AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN12_SEC_MASK(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN12_SEC_MASK_SHIFT)) & AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN12_SEC_MASK_MASK)

#define AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN13_SEC_MASK_MASK (0x2000U)
#define AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN13_SEC_MASK_SHIFT (13U)
/*! PIO1_PIN13_SEC_MASK - Secure mask for pin P1_13
 *  0b1..Pin state is readable by non-secure world.
 *  0b0..Pin state is blocked to non-secure world.
 */
#define AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN13_SEC_MASK(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN13_SEC_MASK_SHIFT)) & AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN13_SEC_MASK_MASK)

#define AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN14_SEC_MASK_MASK (0x4000U)
#define AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN14_SEC_MASK_SHIFT (14U)
/*! PIO1_PIN14_SEC_MASK - Secure mask for pin P1_14
 *  0b1..Pin state is readable by non-secure world.
 *  0b0..Pin state is blocked to non-secure world.
 */
#define AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN14_SEC_MASK(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN14_SEC_MASK_SHIFT)) & AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN14_SEC_MASK_MASK)

#define AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN15_SEC_MASK_MASK (0x8000U)
#define AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN15_SEC_MASK_SHIFT (15U)
/*! PIO1_PIN15_SEC_MASK - Secure mask for pin P1_15
 *  0b1..Pin state is readable by non-secure world.
 *  0b0..Pin state is blocked to non-secure world.
 */
#define AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN15_SEC_MASK(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN15_SEC_MASK_SHIFT)) & AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN15_SEC_MASK_MASK)

#define AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN16_SEC_MASK_MASK (0x10000U)
#define AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN16_SEC_MASK_SHIFT (16U)
/*! PIO1_PIN16_SEC_MASK - Secure mask for pin P1_16
 *  0b1..Pin state is readable by non-secure world.
 *  0b0..Pin state is blocked to non-secure world.
 */
#define AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN16_SEC_MASK(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN16_SEC_MASK_SHIFT)) & AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN16_SEC_MASK_MASK)

#define AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN17_SEC_MASK_MASK (0x20000U)
#define AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN17_SEC_MASK_SHIFT (17U)
/*! PIO1_PIN17_SEC_MASK - Secure mask for pin P1_17
 *  0b1..Pin state is readable by non-secure world.
 *  0b0..Pin state is blocked to non-secure world.
 */
#define AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN17_SEC_MASK(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN17_SEC_MASK_SHIFT)) & AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN17_SEC_MASK_MASK)

#define AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN18_SEC_MASK_MASK (0x40000U)
#define AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN18_SEC_MASK_SHIFT (18U)
/*! PIO1_PIN18_SEC_MASK - Secure mask for pin P1_18
 *  0b1..Pin state is readable by non-secure world.
 *  0b0..Pin state is blocked to non-secure world.
 */
#define AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN18_SEC_MASK(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN18_SEC_MASK_SHIFT)) & AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN18_SEC_MASK_MASK)

#define AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN19_SEC_MASK_MASK (0x80000U)
#define AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN19_SEC_MASK_SHIFT (19U)
/*! PIO1_PIN19_SEC_MASK - Secure mask for pin P1_19
 *  0b1..Pin state is readable by non-secure world.
 *  0b0..Pin state is blocked to non-secure world.
 */
#define AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN19_SEC_MASK(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN19_SEC_MASK_SHIFT)) & AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN19_SEC_MASK_MASK)

#define AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN20_SEC_MASK_MASK (0x100000U)
#define AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN20_SEC_MASK_SHIFT (20U)
/*! PIO1_PIN20_SEC_MASK - Secure mask for pin P1_20
 *  0b1..Pin state is readable by non-secure world.
 *  0b0..Pin state is blocked to non-secure world.
 */
#define AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN20_SEC_MASK(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN20_SEC_MASK_SHIFT)) & AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN20_SEC_MASK_MASK)

#define AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN21_SEC_MASK_MASK (0x200000U)
#define AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN21_SEC_MASK_SHIFT (21U)
/*! PIO1_PIN21_SEC_MASK - Secure mask for pin P1_21
 *  0b1..Pin state is readable by non-secure world.
 *  0b0..Pin state is blocked to non-secure world.
 */
#define AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN21_SEC_MASK(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN21_SEC_MASK_SHIFT)) & AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN21_SEC_MASK_MASK)

#define AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN22_SEC_MASK_MASK (0x400000U)
#define AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN22_SEC_MASK_SHIFT (22U)
/*! PIO1_PIN22_SEC_MASK - Secure mask for pin P1_22
 *  0b1..Pin state is readable by non-secure world.
 *  0b0..Pin state is blocked to non-secure world.
 */
#define AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN22_SEC_MASK(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN22_SEC_MASK_SHIFT)) & AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN22_SEC_MASK_MASK)

#define AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN23_SEC_MASK_MASK (0x800000U)
#define AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN23_SEC_MASK_SHIFT (23U)
/*! PIO1_PIN23_SEC_MASK - Secure mask for pin P1_23
 *  0b1..Pin state is readable by non-secure world.
 *  0b0..Pin state is blocked to non-secure world.
 */
#define AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN23_SEC_MASK(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN23_SEC_MASK_SHIFT)) & AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN23_SEC_MASK_MASK)

#define AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN24_SEC_MASK_MASK (0x1000000U)
#define AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN24_SEC_MASK_SHIFT (24U)
/*! PIO1_PIN24_SEC_MASK - Secure mask for pin P1_24
 *  0b1..Pin state is readable by non-secure world.
 *  0b0..Pin state is blocked to non-secure world.
 */
#define AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN24_SEC_MASK(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN24_SEC_MASK_SHIFT)) & AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN24_SEC_MASK_MASK)

#define AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN25_SEC_MASK_MASK (0x2000000U)
#define AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN25_SEC_MASK_SHIFT (25U)
/*! PIO1_PIN25_SEC_MASK - Secure mask for pin P1_25
 *  0b1..Pin state is readable by non-secure world.
 *  0b0..Pin state is blocked to non-secure world.
 */
#define AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN25_SEC_MASK(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN25_SEC_MASK_SHIFT)) & AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN25_SEC_MASK_MASK)

#define AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN26_SEC_MASK_MASK (0x4000000U)
#define AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN26_SEC_MASK_SHIFT (26U)
/*! PIO1_PIN26_SEC_MASK - Secure mask for pin P1_26
 *  0b1..Pin state is readable by non-secure world.
 *  0b0..Pin state is blocked to non-secure world.
 */
#define AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN26_SEC_MASK(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN26_SEC_MASK_SHIFT)) & AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN26_SEC_MASK_MASK)

#define AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN27_SEC_MASK_MASK (0x8000000U)
#define AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN27_SEC_MASK_SHIFT (27U)
/*! PIO1_PIN27_SEC_MASK - Secure mask for pin P1_27
 *  0b1..Pin state is readable by non-secure world.
 *  0b0..Pin state is blocked to non-secure world.
 */
#define AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN27_SEC_MASK(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN27_SEC_MASK_SHIFT)) & AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN27_SEC_MASK_MASK)

#define AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN28_SEC_MASK_MASK (0x10000000U)
#define AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN28_SEC_MASK_SHIFT (28U)
/*! PIO1_PIN28_SEC_MASK - Secure mask for pin P1_28
 *  0b1..Pin state is readable by non-secure world.
 *  0b0..Pin state is blocked to non-secure world.
 */
#define AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN28_SEC_MASK(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN28_SEC_MASK_SHIFT)) & AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN28_SEC_MASK_MASK)

#define AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN29_SEC_MASK_MASK (0x20000000U)
#define AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN29_SEC_MASK_SHIFT (29U)
/*! PIO1_PIN29_SEC_MASK - Secure mask for pin P1_29
 *  0b1..Pin state is readable by non-secure world.
 *  0b0..Pin state is blocked to non-secure world.
 */
#define AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN29_SEC_MASK(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN29_SEC_MASK_SHIFT)) & AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN29_SEC_MASK_MASK)

#define AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN30_SEC_MASK_MASK (0x40000000U)
#define AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN30_SEC_MASK_SHIFT (30U)
/*! PIO1_PIN30_SEC_MASK - Secure mask for pin P1_30
 *  0b1..Pin state is readable by non-secure world.
 *  0b0..Pin state is blocked to non-secure world.
 */
#define AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN30_SEC_MASK(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN30_SEC_MASK_SHIFT)) & AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN30_SEC_MASK_MASK)

#define AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN31_SEC_MASK_MASK (0x80000000U)
#define AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN31_SEC_MASK_SHIFT (31U)
/*! PIO1_PIN31_SEC_MASK - Secure mask for pin P1_31
 *  0b1..Pin state is readable by non-secure world.
 *  0b0..Pin state is blocked to non-secure world.
 */
#define AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN31_SEC_MASK(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN31_SEC_MASK_SHIFT)) & AHB_SECURE_CTRL_SEC_GPIO_MASK1_PIO1_PIN31_SEC_MASK_MASK)
/*! @} */

/*! @name SEC_MASK_LOCK - Security General Purpose register access control. */
/*! @{ */

#define AHB_SECURE_CTRL_SEC_MASK_LOCK_SEC_GPIO_MASK0_LOCK_MASK (0x3U)
#define AHB_SECURE_CTRL_SEC_MASK_LOCK_SEC_GPIO_MASK0_LOCK_SHIFT (0U)
/*! SEC_GPIO_MASK0_LOCK - SEC_GPIO_MASK0 register write-lock.
 *  0b10..Writable.
 *  0b01..Restricted mode.
 */
#define AHB_SECURE_CTRL_SEC_MASK_LOCK_SEC_GPIO_MASK0_LOCK(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_MASK_LOCK_SEC_GPIO_MASK0_LOCK_SHIFT)) & AHB_SECURE_CTRL_SEC_MASK_LOCK_SEC_GPIO_MASK0_LOCK_MASK)

#define AHB_SECURE_CTRL_SEC_MASK_LOCK_SEC_GPIO_MASK1_LOCK_MASK (0xCU)
#define AHB_SECURE_CTRL_SEC_MASK_LOCK_SEC_GPIO_MASK1_LOCK_SHIFT (2U)
/*! SEC_GPIO_MASK1_LOCK - SEC_GPIO_MASK1 register write-lock.
 *  0b10..Writable.
 *  0b01..Restricted mode.
 */
#define AHB_SECURE_CTRL_SEC_MASK_LOCK_SEC_GPIO_MASK1_LOCK(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_SEC_MASK_LOCK_SEC_GPIO_MASK1_LOCK_SHIFT)) & AHB_SECURE_CTRL_SEC_MASK_LOCK_SEC_GPIO_MASK1_LOCK_MASK)
/*! @} */

/*! @name MASTER_SEC_LEVEL - master secure level register */
/*! @{ */

#define AHB_SECURE_CTRL_MASTER_SEC_LEVEL_USBFSD_MASK (0x300U)
#define AHB_SECURE_CTRL_MASTER_SEC_LEVEL_USBFSD_SHIFT (8U)
/*! USBFSD - USB Full Speed Device.
 *  0b00..Non-secure and Non-priviledge user access allowed.
 *  0b01..Non-secure and Privilege access allowed.
 *  0b10..Secure and Non-priviledge user access allowed.
 *  0b11..Secure and Priviledge user access allowed.
 */
#define AHB_SECURE_CTRL_MASTER_SEC_LEVEL_USBFSD(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_MASTER_SEC_LEVEL_USBFSD_SHIFT)) & AHB_SECURE_CTRL_MASTER_SEC_LEVEL_USBFSD_MASK)

#define AHB_SECURE_CTRL_MASTER_SEC_LEVEL_SDMA0_MASK (0xC00U)
#define AHB_SECURE_CTRL_MASTER_SEC_LEVEL_SDMA0_SHIFT (10U)
/*! SDMA0 - System DMA 0.
 *  0b00..Non-secure and Non-priviledge user access allowed.
 *  0b01..Non-secure and Privilege access allowed.
 *  0b10..Secure and Non-priviledge user access allowed.
 *  0b11..Secure and Priviledge user access allowed.
 */
#define AHB_SECURE_CTRL_MASTER_SEC_LEVEL_SDMA0(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_MASTER_SEC_LEVEL_SDMA0_SHIFT)) & AHB_SECURE_CTRL_MASTER_SEC_LEVEL_SDMA0_MASK)

#define AHB_SECURE_CTRL_MASTER_SEC_LEVEL_HASH_MASK (0x300000U)
#define AHB_SECURE_CTRL_MASTER_SEC_LEVEL_HASH_SHIFT (20U)
/*! HASH - Hash.
 *  0b00..Non-secure and Non-priviledge user access allowed.
 *  0b01..Non-secure and Privilege access allowed.
 *  0b10..Secure and Non-priviledge user access allowed.
 *  0b11..Secure and Priviledge user access allowed.
 */
#define AHB_SECURE_CTRL_MASTER_SEC_LEVEL_HASH(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_MASTER_SEC_LEVEL_HASH_SHIFT)) & AHB_SECURE_CTRL_MASTER_SEC_LEVEL_HASH_MASK)

#define AHB_SECURE_CTRL_MASTER_SEC_LEVEL_USBFSH_MASK (0xC00000U)
#define AHB_SECURE_CTRL_MASTER_SEC_LEVEL_USBFSH_SHIFT (22U)
/*! USBFSH - USB Full speed Host.
 *  0b00..Non-secure and Non-priviledge user access allowed.
 *  0b01..Non-secure and Privilege access allowed.
 *  0b10..Secure and Non-priviledge user access allowed.
 *  0b11..Secure and Priviledge user access allowed.
 */
#define AHB_SECURE_CTRL_MASTER_SEC_LEVEL_USBFSH(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_MASTER_SEC_LEVEL_USBFSH_SHIFT)) & AHB_SECURE_CTRL_MASTER_SEC_LEVEL_USBFSH_MASK)

#define AHB_SECURE_CTRL_MASTER_SEC_LEVEL_SDMA1_MASK (0x3000000U)
#define AHB_SECURE_CTRL_MASTER_SEC_LEVEL_SDMA1_SHIFT (24U)
/*! SDMA1 - System DMA 1 security level.
 *  0b00..Non-secure and Non-priviledge user access allowed.
 *  0b01..Non-secure and Privilege access allowed.
 *  0b10..Secure and Non-priviledge user access allowed.
 *  0b11..Secure and Priviledge user access allowed.
 */
#define AHB_SECURE_CTRL_MASTER_SEC_LEVEL_SDMA1(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_MASTER_SEC_LEVEL_SDMA1_SHIFT)) & AHB_SECURE_CTRL_MASTER_SEC_LEVEL_SDMA1_MASK)

#define AHB_SECURE_CTRL_MASTER_SEC_LEVEL_CANFD_MASK (0xC000000U)
#define AHB_SECURE_CTRL_MASTER_SEC_LEVEL_CANFD_SHIFT (26U)
/*! CANFD - CAN FD.
 *  0b00..Non-secure and Non-priviledge user access allowed.
 *  0b01..Non-secure and Privilege access allowed.
 *  0b10..Secure and Non-priviledge user access allowed.
 *  0b11..Secure and Priviledge user access allowed.
 */
#define AHB_SECURE_CTRL_MASTER_SEC_LEVEL_CANFD(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_MASTER_SEC_LEVEL_CANFD_SHIFT)) & AHB_SECURE_CTRL_MASTER_SEC_LEVEL_CANFD_MASK)

#define AHB_SECURE_CTRL_MASTER_SEC_LEVEL_MASTER_SEC_LEVEL_LOCK_MASK (0xC0000000U)
#define AHB_SECURE_CTRL_MASTER_SEC_LEVEL_MASTER_SEC_LEVEL_LOCK_SHIFT (30U)
/*! MASTER_SEC_LEVEL_LOCK - MASTER_SEC_LEVEL write-lock.
 *  0b10..Writable.
 *  0b01..Restricted mode.
 */
#define AHB_SECURE_CTRL_MASTER_SEC_LEVEL_MASTER_SEC_LEVEL_LOCK(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_MASTER_SEC_LEVEL_MASTER_SEC_LEVEL_LOCK_SHIFT)) & AHB_SECURE_CTRL_MASTER_SEC_LEVEL_MASTER_SEC_LEVEL_LOCK_MASK)
/*! @} */

/*! @name MASTER_SEC_ANTI_POL_REG - master secure level anti-pole register */
/*! @{ */

#define AHB_SECURE_CTRL_MASTER_SEC_ANTI_POL_REG_USBFSD_MASK (0x300U)
#define AHB_SECURE_CTRL_MASTER_SEC_ANTI_POL_REG_USBFSD_SHIFT (8U)
/*! USBFSD - USB Full Speed Device. Must be equal to NOT(MASTER_SEC_LEVEL.USBFSD)
 *  0b11..Non-secure and Non-priviledge user access allowed.
 *  0b10..Non-secure and Privilege access allowed.
 *  0b01..Secure and Non-priviledge user access allowed.
 *  0b00..Secure and Priviledge user access allowed.
 */
#define AHB_SECURE_CTRL_MASTER_SEC_ANTI_POL_REG_USBFSD(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_MASTER_SEC_ANTI_POL_REG_USBFSD_SHIFT)) & AHB_SECURE_CTRL_MASTER_SEC_ANTI_POL_REG_USBFSD_MASK)

#define AHB_SECURE_CTRL_MASTER_SEC_ANTI_POL_REG_SDMA0_MASK (0xC00U)
#define AHB_SECURE_CTRL_MASTER_SEC_ANTI_POL_REG_SDMA0_SHIFT (10U)
/*! SDMA0 - System DMA 0. Must be equal to NOT(MASTER_SEC_LEVEL.SDMA0)
 *  0b11..Non-secure and Non-priviledge user access allowed.
 *  0b10..Non-secure and Privilege access allowed.
 *  0b01..Secure and Non-priviledge user access allowed.
 *  0b00..Secure and Priviledge user access allowed.
 */
#define AHB_SECURE_CTRL_MASTER_SEC_ANTI_POL_REG_SDMA0(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_MASTER_SEC_ANTI_POL_REG_SDMA0_SHIFT)) & AHB_SECURE_CTRL_MASTER_SEC_ANTI_POL_REG_SDMA0_MASK)

#define AHB_SECURE_CTRL_MASTER_SEC_ANTI_POL_REG_HASH_MASK (0x300000U)
#define AHB_SECURE_CTRL_MASTER_SEC_ANTI_POL_REG_HASH_SHIFT (20U)
/*! HASH - Hash. Must be equal to NOT(MASTER_SEC_LEVEL.HASH)
 *  0b11..Non-secure and Non-priviledge user access allowed.
 *  0b10..Non-secure and Privilege access allowed.
 *  0b01..Secure and Non-priviledge user access allowed.
 *  0b00..Secure and Priviledge user access allowed.
 */
#define AHB_SECURE_CTRL_MASTER_SEC_ANTI_POL_REG_HASH(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_MASTER_SEC_ANTI_POL_REG_HASH_SHIFT)) & AHB_SECURE_CTRL_MASTER_SEC_ANTI_POL_REG_HASH_MASK)

#define AHB_SECURE_CTRL_MASTER_SEC_ANTI_POL_REG_USBFSH_MASK (0xC00000U)
#define AHB_SECURE_CTRL_MASTER_SEC_ANTI_POL_REG_USBFSH_SHIFT (22U)
/*! USBFSH - USB Full speed Host. Must be equal to NOT(MASTER_SEC_LEVEL.USBFSH)
 *  0b11..Non-secure and Non-priviledge user access allowed.
 *  0b10..Non-secure and Privilege access allowed.
 *  0b01..Secure and Non-priviledge user access allowed.
 *  0b00..Secure and Priviledge user access allowed.
 */
#define AHB_SECURE_CTRL_MASTER_SEC_ANTI_POL_REG_USBFSH(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_MASTER_SEC_ANTI_POL_REG_USBFSH_SHIFT)) & AHB_SECURE_CTRL_MASTER_SEC_ANTI_POL_REG_USBFSH_MASK)

#define AHB_SECURE_CTRL_MASTER_SEC_ANTI_POL_REG_SDMA1_MASK (0x3000000U)
#define AHB_SECURE_CTRL_MASTER_SEC_ANTI_POL_REG_SDMA1_SHIFT (24U)
/*! SDMA1 - System DMA 1 security level. Must be equal to NOT(MASTER_SEC_LEVEL.SDMA1)
 *  0b11..Non-secure and Non-priviledge user access allowed.
 *  0b10..Non-secure and Privilege access allowed.
 *  0b01..Secure and Non-priviledge user access allowed.
 *  0b00..Secure and Priviledge user access allowed.
 */
#define AHB_SECURE_CTRL_MASTER_SEC_ANTI_POL_REG_SDMA1(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_MASTER_SEC_ANTI_POL_REG_SDMA1_SHIFT)) & AHB_SECURE_CTRL_MASTER_SEC_ANTI_POL_REG_SDMA1_MASK)

#define AHB_SECURE_CTRL_MASTER_SEC_ANTI_POL_REG_CANFD_MASK (0xC000000U)
#define AHB_SECURE_CTRL_MASTER_SEC_ANTI_POL_REG_CANFD_SHIFT (26U)
/*! CANFD - CAN FD. Must be equal to NOT(MASTER_SEC_LEVEL.CANFD)
 *  0b11..Non-secure and Non-priviledge user access allowed.
 *  0b10..Non-secure and Privilege access allowed.
 *  0b01..Secure and Non-priviledge user access allowed.
 *  0b00..Secure and Priviledge user access allowed.
 */
#define AHB_SECURE_CTRL_MASTER_SEC_ANTI_POL_REG_CANFD(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_MASTER_SEC_ANTI_POL_REG_CANFD_SHIFT)) & AHB_SECURE_CTRL_MASTER_SEC_ANTI_POL_REG_CANFD_MASK)

#define AHB_SECURE_CTRL_MASTER_SEC_ANTI_POL_REG_MASTER_SEC_LEVEL_ANTIPOL_LOCK_MASK (0xC0000000U)
#define AHB_SECURE_CTRL_MASTER_SEC_ANTI_POL_REG_MASTER_SEC_LEVEL_ANTIPOL_LOCK_SHIFT (30U)
/*! MASTER_SEC_LEVEL_ANTIPOL_LOCK - MASTER_SEC_ANTI_POL_REG register write-lock.
 *  0b10..Writable.
 *  0b01..Restricted mode.
 */
#define AHB_SECURE_CTRL_MASTER_SEC_ANTI_POL_REG_MASTER_SEC_LEVEL_ANTIPOL_LOCK(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_MASTER_SEC_ANTI_POL_REG_MASTER_SEC_LEVEL_ANTIPOL_LOCK_SHIFT)) & AHB_SECURE_CTRL_MASTER_SEC_ANTI_POL_REG_MASTER_SEC_LEVEL_ANTIPOL_LOCK_MASK)
/*! @} */

/*! @name CPU0_LOCK_REG - Miscalleneous control signals for in Cortex M33 (CPU0) */
/*! @{ */

#define AHB_SECURE_CTRL_CPU0_LOCK_REG_LOCK_NS_VTOR_MASK (0x3U)
#define AHB_SECURE_CTRL_CPU0_LOCK_REG_LOCK_NS_VTOR_SHIFT (0U)
/*! LOCK_NS_VTOR - Cortex M33 (CPU0) VTOR_NS register write-lock.
 *  0b10..Writable.
 *  0b01..Restricted mode.
 */
#define AHB_SECURE_CTRL_CPU0_LOCK_REG_LOCK_NS_VTOR(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_CPU0_LOCK_REG_LOCK_NS_VTOR_SHIFT)) & AHB_SECURE_CTRL_CPU0_LOCK_REG_LOCK_NS_VTOR_MASK)

#define AHB_SECURE_CTRL_CPU0_LOCK_REG_LOCK_NS_MPU_MASK (0xCU)
#define AHB_SECURE_CTRL_CPU0_LOCK_REG_LOCK_NS_MPU_SHIFT (2U)
/*! LOCK_NS_MPU - Cortex M33 (CPU0) non-secure MPU register write-lock.
 *  0b10..Writable.
 *  0b01..Restricted mode.
 */
#define AHB_SECURE_CTRL_CPU0_LOCK_REG_LOCK_NS_MPU(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_CPU0_LOCK_REG_LOCK_NS_MPU_SHIFT)) & AHB_SECURE_CTRL_CPU0_LOCK_REG_LOCK_NS_MPU_MASK)

#define AHB_SECURE_CTRL_CPU0_LOCK_REG_LOCK_S_VTAIRCR_MASK (0x30U)
#define AHB_SECURE_CTRL_CPU0_LOCK_REG_LOCK_S_VTAIRCR_SHIFT (4U)
/*! LOCK_S_VTAIRCR - Cortex M33 (CPU0) VTOR_S, AIRCR.PRIS, IRCR.BFHFNMINS registers write-lock.
 *  0b10..Writable.
 *  0b01..Restricted mode.
 */
#define AHB_SECURE_CTRL_CPU0_LOCK_REG_LOCK_S_VTAIRCR(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_CPU0_LOCK_REG_LOCK_S_VTAIRCR_SHIFT)) & AHB_SECURE_CTRL_CPU0_LOCK_REG_LOCK_S_VTAIRCR_MASK)

#define AHB_SECURE_CTRL_CPU0_LOCK_REG_LOCK_S_MPU_MASK (0xC0U)
#define AHB_SECURE_CTRL_CPU0_LOCK_REG_LOCK_S_MPU_SHIFT (6U)
/*! LOCK_S_MPU - Cortex M33 (CPU0) Secure MPU registers write-lock.
 *  0b10..Writable.
 *  0b01..Restricted mode.
 */
#define AHB_SECURE_CTRL_CPU0_LOCK_REG_LOCK_S_MPU(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_CPU0_LOCK_REG_LOCK_S_MPU_SHIFT)) & AHB_SECURE_CTRL_CPU0_LOCK_REG_LOCK_S_MPU_MASK)

#define AHB_SECURE_CTRL_CPU0_LOCK_REG_LOCK_SAU_MASK (0x300U)
#define AHB_SECURE_CTRL_CPU0_LOCK_REG_LOCK_SAU_SHIFT (8U)
/*! LOCK_SAU - Cortex M33 (CPU0) SAU registers write-lock.
 *  0b10..Writable.
 *  0b01..Restricted mode.
 */
#define AHB_SECURE_CTRL_CPU0_LOCK_REG_LOCK_SAU(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_CPU0_LOCK_REG_LOCK_SAU_SHIFT)) & AHB_SECURE_CTRL_CPU0_LOCK_REG_LOCK_SAU_MASK)

#define AHB_SECURE_CTRL_CPU0_LOCK_REG_CPU0_LOCK_REG_LOCK_MASK (0xC0000000U)
#define AHB_SECURE_CTRL_CPU0_LOCK_REG_CPU0_LOCK_REG_LOCK_SHIFT (30U)
/*! CPU0_LOCK_REG_LOCK - CPU0_LOCK_REG write-lock.
 *  0b10..Writable.
 *  0b01..Restricted mode.
 */
#define AHB_SECURE_CTRL_CPU0_LOCK_REG_CPU0_LOCK_REG_LOCK(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_CPU0_LOCK_REG_CPU0_LOCK_REG_LOCK_SHIFT)) & AHB_SECURE_CTRL_CPU0_LOCK_REG_CPU0_LOCK_REG_LOCK_MASK)
/*! @} */

/*! @name MISC_CTRL_DP_REG - secure control duplicate register */
/*! @{ */

#define AHB_SECURE_CTRL_MISC_CTRL_DP_REG_WRITE_LOCK_MASK (0x3U)
#define AHB_SECURE_CTRL_MISC_CTRL_DP_REG_WRITE_LOCK_SHIFT (0U)
/*! WRITE_LOCK - Write lock.
 *  0b10..Secure control registers can be written.
 *  0b01..Restricted mode.
 */
#define AHB_SECURE_CTRL_MISC_CTRL_DP_REG_WRITE_LOCK(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_MISC_CTRL_DP_REG_WRITE_LOCK_SHIFT)) & AHB_SECURE_CTRL_MISC_CTRL_DP_REG_WRITE_LOCK_MASK)

#define AHB_SECURE_CTRL_MISC_CTRL_DP_REG_ENABLE_SECURE_CHECKING_MASK (0xCU)
#define AHB_SECURE_CTRL_MISC_CTRL_DP_REG_ENABLE_SECURE_CHECKING_SHIFT (2U)
/*! ENABLE_SECURE_CHECKING - Enable secure check for AHB matrix.
 *  0b10..Disable check.
 *  0b01..Restricted mode.
 */
#define AHB_SECURE_CTRL_MISC_CTRL_DP_REG_ENABLE_SECURE_CHECKING(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_MISC_CTRL_DP_REG_ENABLE_SECURE_CHECKING_SHIFT)) & AHB_SECURE_CTRL_MISC_CTRL_DP_REG_ENABLE_SECURE_CHECKING_MASK)

#define AHB_SECURE_CTRL_MISC_CTRL_DP_REG_ENABLE_S_PRIV_CHECK_MASK (0x30U)
#define AHB_SECURE_CTRL_MISC_CTRL_DP_REG_ENABLE_S_PRIV_CHECK_SHIFT (4U)
/*! ENABLE_S_PRIV_CHECK - Enable secure privilege check for AHB matrix.
 *  0b10..Disable check.
 *  0b01..Restricted mode.
 */
#define AHB_SECURE_CTRL_MISC_CTRL_DP_REG_ENABLE_S_PRIV_CHECK(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_MISC_CTRL_DP_REG_ENABLE_S_PRIV_CHECK_SHIFT)) & AHB_SECURE_CTRL_MISC_CTRL_DP_REG_ENABLE_S_PRIV_CHECK_MASK)

#define AHB_SECURE_CTRL_MISC_CTRL_DP_REG_ENABLE_NS_PRIV_CHECK_MASK (0xC0U)
#define AHB_SECURE_CTRL_MISC_CTRL_DP_REG_ENABLE_NS_PRIV_CHECK_SHIFT (6U)
/*! ENABLE_NS_PRIV_CHECK - Enable non-secure privilege check for AHB matrix.
 *  0b10..Disable check.
 *  0b01..Restricted mode.
 */
#define AHB_SECURE_CTRL_MISC_CTRL_DP_REG_ENABLE_NS_PRIV_CHECK(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_MISC_CTRL_DP_REG_ENABLE_NS_PRIV_CHECK_SHIFT)) & AHB_SECURE_CTRL_MISC_CTRL_DP_REG_ENABLE_NS_PRIV_CHECK_MASK)

#define AHB_SECURE_CTRL_MISC_CTRL_DP_REG_DISABLE_VIOLATION_ABORT_MASK (0x300U)
#define AHB_SECURE_CTRL_MISC_CTRL_DP_REG_DISABLE_VIOLATION_ABORT_SHIFT (8U)
/*! DISABLE_VIOLATION_ABORT - Disable secure violation abort.
 *  0b10..Enable abort fort secure checker.
 *  0b01..Disable abort fort secure checker.
 */
#define AHB_SECURE_CTRL_MISC_CTRL_DP_REG_DISABLE_VIOLATION_ABORT(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_MISC_CTRL_DP_REG_DISABLE_VIOLATION_ABORT_SHIFT)) & AHB_SECURE_CTRL_MISC_CTRL_DP_REG_DISABLE_VIOLATION_ABORT_MASK)

#define AHB_SECURE_CTRL_MISC_CTRL_DP_REG_DISABLE_SIMPLE_MASTER_STRICT_MODE_MASK (0xC00U)
#define AHB_SECURE_CTRL_MISC_CTRL_DP_REG_DISABLE_SIMPLE_MASTER_STRICT_MODE_SHIFT (10U)
/*! DISABLE_SIMPLE_MASTER_STRICT_MODE - Disable simple master strict mode.
 *  0b10..Simple master in strict mode.
 *  0b01..Simple master in tier mode.
 */
#define AHB_SECURE_CTRL_MISC_CTRL_DP_REG_DISABLE_SIMPLE_MASTER_STRICT_MODE(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_MISC_CTRL_DP_REG_DISABLE_SIMPLE_MASTER_STRICT_MODE_SHIFT)) & AHB_SECURE_CTRL_MISC_CTRL_DP_REG_DISABLE_SIMPLE_MASTER_STRICT_MODE_MASK)

#define AHB_SECURE_CTRL_MISC_CTRL_DP_REG_DISABLE_SMART_MASTER_STRICT_MODE_MASK (0x3000U)
#define AHB_SECURE_CTRL_MISC_CTRL_DP_REG_DISABLE_SMART_MASTER_STRICT_MODE_SHIFT (12U)
/*! DISABLE_SMART_MASTER_STRICT_MODE - Disable smart master strict mode.
 *  0b10..Smart master in strict mode.
 *  0b01..Smart master in tier mode.
 */
#define AHB_SECURE_CTRL_MISC_CTRL_DP_REG_DISABLE_SMART_MASTER_STRICT_MODE(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_MISC_CTRL_DP_REG_DISABLE_SMART_MASTER_STRICT_MODE_SHIFT)) & AHB_SECURE_CTRL_MISC_CTRL_DP_REG_DISABLE_SMART_MASTER_STRICT_MODE_MASK)

#define AHB_SECURE_CTRL_MISC_CTRL_DP_REG_IDAU_ALL_NS_MASK (0xC000U)
#define AHB_SECURE_CTRL_MISC_CTRL_DP_REG_IDAU_ALL_NS_SHIFT (14U)
/*! IDAU_ALL_NS - Disable IDAU.
 *  0b10..IDAU is enabled.
 *  0b01..IDAU is disable.
 */
#define AHB_SECURE_CTRL_MISC_CTRL_DP_REG_IDAU_ALL_NS(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_MISC_CTRL_DP_REG_IDAU_ALL_NS_SHIFT)) & AHB_SECURE_CTRL_MISC_CTRL_DP_REG_IDAU_ALL_NS_MASK)
/*! @} */

/*! @name MISC_CTRL_REG - secure control register */
/*! @{ */

#define AHB_SECURE_CTRL_MISC_CTRL_REG_WRITE_LOCK_MASK (0x3U)
#define AHB_SECURE_CTRL_MISC_CTRL_REG_WRITE_LOCK_SHIFT (0U)
/*! WRITE_LOCK - Write lock.
 *  0b10..Secure control registers can be written.
 *  0b01..Restricted mode.
 */
#define AHB_SECURE_CTRL_MISC_CTRL_REG_WRITE_LOCK(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_MISC_CTRL_REG_WRITE_LOCK_SHIFT)) & AHB_SECURE_CTRL_MISC_CTRL_REG_WRITE_LOCK_MASK)

#define AHB_SECURE_CTRL_MISC_CTRL_REG_ENABLE_SECURE_CHECKING_MASK (0xCU)
#define AHB_SECURE_CTRL_MISC_CTRL_REG_ENABLE_SECURE_CHECKING_SHIFT (2U)
/*! ENABLE_SECURE_CHECKING - Enable secure check for AHB matrix.
 *  0b10..Disable check.
 *  0b01..Enabled (restricted mode)
 */
#define AHB_SECURE_CTRL_MISC_CTRL_REG_ENABLE_SECURE_CHECKING(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_MISC_CTRL_REG_ENABLE_SECURE_CHECKING_SHIFT)) & AHB_SECURE_CTRL_MISC_CTRL_REG_ENABLE_SECURE_CHECKING_MASK)

#define AHB_SECURE_CTRL_MISC_CTRL_REG_ENABLE_S_PRIV_CHECK_MASK (0x30U)
#define AHB_SECURE_CTRL_MISC_CTRL_REG_ENABLE_S_PRIV_CHECK_SHIFT (4U)
/*! ENABLE_S_PRIV_CHECK - Enable secure privilege check for AHB matrix.
 *  0b10..Disable check.
 *  0b01..Enabled (restricted mode)
 */
#define AHB_SECURE_CTRL_MISC_CTRL_REG_ENABLE_S_PRIV_CHECK(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_MISC_CTRL_REG_ENABLE_S_PRIV_CHECK_SHIFT)) & AHB_SECURE_CTRL_MISC_CTRL_REG_ENABLE_S_PRIV_CHECK_MASK)

#define AHB_SECURE_CTRL_MISC_CTRL_REG_ENABLE_NS_PRIV_CHECK_MASK (0xC0U)
#define AHB_SECURE_CTRL_MISC_CTRL_REG_ENABLE_NS_PRIV_CHECK_SHIFT (6U)
/*! ENABLE_NS_PRIV_CHECK - Enable non-secure privilege check for AHB matrix.
 *  0b10..Disable check.
 *  0b01..Enabled (restricted mode)
 */
#define AHB_SECURE_CTRL_MISC_CTRL_REG_ENABLE_NS_PRIV_CHECK(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_MISC_CTRL_REG_ENABLE_NS_PRIV_CHECK_SHIFT)) & AHB_SECURE_CTRL_MISC_CTRL_REG_ENABLE_NS_PRIV_CHECK_MASK)

#define AHB_SECURE_CTRL_MISC_CTRL_REG_DISABLE_VIOLATION_ABORT_MASK (0x300U)
#define AHB_SECURE_CTRL_MISC_CTRL_REG_DISABLE_VIOLATION_ABORT_SHIFT (8U)
/*! DISABLE_VIOLATION_ABORT - Disable secure violation abort.
 *  0b10..Enable abort fort secure checker.
 *  0b01..Disable abort fort secure checker.
 */
#define AHB_SECURE_CTRL_MISC_CTRL_REG_DISABLE_VIOLATION_ABORT(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_MISC_CTRL_REG_DISABLE_VIOLATION_ABORT_SHIFT)) & AHB_SECURE_CTRL_MISC_CTRL_REG_DISABLE_VIOLATION_ABORT_MASK)

#define AHB_SECURE_CTRL_MISC_CTRL_REG_DISABLE_SIMPLE_MASTER_STRICT_MODE_MASK (0xC00U)
#define AHB_SECURE_CTRL_MISC_CTRL_REG_DISABLE_SIMPLE_MASTER_STRICT_MODE_SHIFT (10U)
/*! DISABLE_SIMPLE_MASTER_STRICT_MODE - Disable simple master strict mode.
 *  0b10..Simple master in strict mode.
 *  0b01..Simple master in tier mode.
 */
#define AHB_SECURE_CTRL_MISC_CTRL_REG_DISABLE_SIMPLE_MASTER_STRICT_MODE(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_MISC_CTRL_REG_DISABLE_SIMPLE_MASTER_STRICT_MODE_SHIFT)) & AHB_SECURE_CTRL_MISC_CTRL_REG_DISABLE_SIMPLE_MASTER_STRICT_MODE_MASK)

#define AHB_SECURE_CTRL_MISC_CTRL_REG_DISABLE_SMART_MASTER_STRICT_MODE_MASK (0x3000U)
#define AHB_SECURE_CTRL_MISC_CTRL_REG_DISABLE_SMART_MASTER_STRICT_MODE_SHIFT (12U)
/*! DISABLE_SMART_MASTER_STRICT_MODE - Disable smart master strict mode.
 *  0b10..Smart master in strict mode.
 *  0b01..Smart master in tier mode.
 */
#define AHB_SECURE_CTRL_MISC_CTRL_REG_DISABLE_SMART_MASTER_STRICT_MODE(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_MISC_CTRL_REG_DISABLE_SMART_MASTER_STRICT_MODE_SHIFT)) & AHB_SECURE_CTRL_MISC_CTRL_REG_DISABLE_SMART_MASTER_STRICT_MODE_MASK)

#define AHB_SECURE_CTRL_MISC_CTRL_REG_IDAU_ALL_NS_MASK (0xC000U)
#define AHB_SECURE_CTRL_MISC_CTRL_REG_IDAU_ALL_NS_SHIFT (14U)
/*! IDAU_ALL_NS - Disable IDAU.
 *  0b10..IDAU is enabled.
 *  0b01..IDAU is disable.
 */
#define AHB_SECURE_CTRL_MISC_CTRL_REG_IDAU_ALL_NS(x) (((uint32_t)(((uint32_t)(x)) << AHB_SECURE_CTRL_MISC_CTRL_REG_IDAU_ALL_NS_SHIFT)) & AHB_SECURE_CTRL_MISC_CTRL_REG_IDAU_ALL_NS_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group AHB_SECURE_CTRL_Register_Masks */


/*!
 * @}
 */ /* end of group AHB_SECURE_CTRL_Peripheral_Access_Layer */


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


#endif  /* AHB_SECURE_CTRL_H_ */

