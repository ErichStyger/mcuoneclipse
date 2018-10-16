/**
 * \file
 * \brief Configuration header file for HardFault
 *
 * This header file is used to configure settings of the HardFault module.
 */

#ifndef __McuHardFault_CONFIG_H
#define __McuHardFault_CONFIG_H

#define McuHardFault_CONFIG_SETTING_HAS_ACTLR   (1 || (defined(__CORTEX_M) && __CORTEX_M>=3))
  /*!< 1: Cortex-M3, M4 have Auxiliary Control Register, ACTLR register */

#ifndef McuHardFault_CONFIG_SETTING_DISABLE_WRITE_BUFFER
  #define McuHardFault_CONFIG_SETTING_DISABLE_WRITE_BUFFER   (0 && McuHardFault_CONFIG_SETTING_HAS_ACTLR)
  /*!< 1: disable write buffer in ACTLR register */
#endif

#endif /* __McuHardFault_CONFIG_H */
