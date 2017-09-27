#ifndef __HF1_CONFIG_H
#define __HF1_CONFIG_H

#define HF1_CONFIG_SETTING_HAS_ACTLR   (1 || (defined(__CORTEX_M) && __CORTEX_M>=3))
  /*!< 1: Cortex-M3, M4 have Auxiliary Control Register, ACTLR register */

#ifndef HF1_CONFIG_SETTING_DISABLE_WRITE_BUFFER
  #define HF1_CONFIG_SETTING_DISABLE_WRITE_BUFFER   (0 && HF1_CONFIG_SETTING_HAS_ACTLR)
  /*!< 1: disable write buffer in ACTLR register */
#endif

#endif /* __HF1_CONFIG_H */
