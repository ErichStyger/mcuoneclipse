/*
 * Copyright (c) 2020, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef FTM_MACROS_H_
#define FTM_MACROS_H_

/* register access macros */

/* FTM - Register accessors */
#define FTM_SC_REG(base)                         ((base)->SC)
#define FTM_CNT_REG(base)                        ((base)->CNT)
#define FTM_MOD_REG(base)                        ((base)->MOD)
#define FTM_CnSC_REG(base,index)                 ((base)->CONTROLS[index].CnSC)
#define FTM_CnV_REG(base,index)                  ((base)->CONTROLS[index].CnV)
#define FTM_CNTIN_REG(base)                      ((base)->CNTIN)
#define FTM_STATUS_REG(base)                     ((base)->STATUS)
#define FTM_MODE_REG(base)                       ((base)->MODE)
#define FTM_SYNC_REG(base)                       ((base)->SYNC)
#define FTM_OUTINIT_REG(base)                    ((base)->OUTINIT)
#define FTM_OUTMASK_REG(base)                    ((base)->OUTMASK)
#define FTM_COMBINE_REG(base)                    ((base)->COMBINE)
#define FTM_DEADTIME_REG(base)                   ((base)->DEADTIME)
#define FTM_EXTTRIG_REG(base)                    ((base)->EXTTRIG)
#define FTM_POL_REG(base)                        ((base)->POL)
#define FTM_FMS_REG(base)                        ((base)->FMS)
#define FTM_FILTER_REG(base)                     ((base)->FILTER)
#define FTM_FLTCTRL_REG(base)                    ((base)->FLTCTRL)
#define FTM_QDCTRL_REG(base)                     ((base)->QDCTRL)
#define FTM_CONF_REG(base)                       ((base)->CONF)
#define FTM_FLTPOL_REG(base)                     ((base)->FLTPOL)
#define FTM_SYNCONF_REG(base)                    ((base)->SYNCONF)
#define FTM_INVCTRL_REG(base)                    ((base)->INVCTRL)
#define FTM_SWOCTRL_REG(base)                    ((base)->SWOCTRL)
#define FTM_PWMLOAD_REG(base)                    ((base)->PWMLOAD)

/* Prescaler constants */
#define FTM_PDD_DIVIDE_1   0U                    /**< 1 */
#define FTM_PDD_DIVIDE_2   0x1U                  /**< 2 */
#define FTM_PDD_DIVIDE_4   0x2U                  /**< 4 */
#define FTM_PDD_DIVIDE_8   0x3U                  /**< 8 */
#define FTM_PDD_DIVIDE_16  0x4U                  /**< 16 */
#define FTM_PDD_DIVIDE_32  0x5U                  /**< 32 */
#define FTM_PDD_DIVIDE_64  0x6U                  /**< 64 */
#define FTM_PDD_DIVIDE_128 0x7U                  /**< 128 */

/* Clock source constants. */
#define FTM_PDD_DISABLED 0U                      /**< Disabled */
#define FTM_PDD_SYSTEM   0x8U                    /**< System clock */
#define FTM_PDD_FIXED    0x10U                   /**< Fixed clock */
#define FTM_PDD_EXTERNAL 0x18U                   /**< External clock */

#define FTM_PDD_SelectPrescalerSource(PeripheralBase, Source) ( \
    FTM_SC_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       FTM_SC_REG(PeripheralBase)) & (( \
       (uint32_t)(~(uint32_t)FTM_SC_CLKS_MASK)) & ( \
       (uint32_t)(~(uint32_t)FTM_SC_TOF_MASK))))) | ( \
      (uint32_t)(Source))) \
  )
#define FTM_PDD_InitializeCounter(PeripheralBase) ( \
    FTM_CNT_REG(PeripheralBase) = \
     0U \
  )
#define FTM_PDD_EnableChannelInterrupt(PeripheralBase, ChannelIdx) ( \
    FTM_CnSC_REG(PeripheralBase,(ChannelIdx)) = \
     (uint32_t)(( \
      (uint32_t)(FTM_CnSC_REG(PeripheralBase,(ChannelIdx)) | FTM_CnSC_CHIE_MASK)) & ( \
      (uint32_t)(~(uint32_t)FTM_CnSC_CHF_MASK))) \
  )
#define FTM_PDD_DisableChannelInterrupt(PeripheralBase, ChannelIdx) ( \
    FTM_CnSC_REG(PeripheralBase,(ChannelIdx)) &= \
     (uint32_t)(( \
      (uint32_t)(~(uint32_t)FTM_CnSC_CHIE_MASK)) & ( \
      (uint32_t)(~(uint32_t)FTM_CnSC_CHF_MASK))) \
  )
#define FTM_PDD_ClearChannelInterruptFlag(PeripheralBase, ChannelIdx) ( \
    FTM_CnSC_REG(PeripheralBase,(ChannelIdx)) &= \
     (uint32_t)(~(uint32_t)FTM_CnSC_CHF_MASK) \
  )
#define FTM_PDD_GetChannelInterruptFlag(PeripheralBase, ChannelIdx) ( \
    (uint32_t)(FTM_CnSC_REG(PeripheralBase,(ChannelIdx)) & FTM_CnSC_CHF_MASK) \
  )
#define FTM_PDD_GetOverflowInterruptFlag(PeripheralBase) ( \
    (uint32_t)(FTM_SC_REG(PeripheralBase) & FTM_SC_TOF_MASK) \
  )
#define FTM_PDD_ClearOverflowInterruptFlag(PeripheralBase) ( \
    FTM_SC_REG(PeripheralBase) &= \
     (uint32_t)(~(uint32_t)FTM_SC_TOF_MASK) \
  )
#define FTM_PDD_WriteStatusControlReg(PeripheralBase, Value) ( \
    FTM_SC_REG(PeripheralBase) = \
     (uint32_t)(Value) \
  )
#define FTM_PDD_SetPrescaler(PeripheralBase, Prescaler) ( \
    FTM_SC_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       FTM_SC_REG(PeripheralBase)) & (( \
       (uint32_t)(~(uint32_t)FTM_SC_PS_MASK)) & ( \
       (uint32_t)(~(uint32_t)FTM_SC_TOF_MASK))))) | ( \
      (uint32_t)(Prescaler))) \
  )
#define FTM_PDD_WriteModuloReg(PeripheralBase, Value) ( \
    FTM_MOD_REG(PeripheralBase) = \
     (uint32_t)(Value) \
  )
#define FTM_PDD_WriteChannelControlReg(PeripheralBase, ChannelIdx, Value) ( \
    FTM_CnSC_REG(PeripheralBase,(ChannelIdx)) = \
     (uint32_t)(Value) \
  )
#define FTM_PDD_WriteChannelValueReg(PeripheralBase, ChannelIdx, Value) ( \
    FTM_CnV_REG(PeripheralBase,(ChannelIdx)) = \
     (uint32_t)(Value) \
  )
#define FTM_PDD_ClearChannelFlags(PeripheralBase, Mask) ( \
    FTM_STATUS_REG(PeripheralBase) = \
     (uint32_t)((uint32_t)(~(uint32_t)(Mask)) & (uint32_t)0xFFU) \
  )
#define FTM_PDD_EnableChannelDma(PeripheralBase, ChannelIdx) ( \
    FTM_CnSC_REG(PeripheralBase,(ChannelIdx)) = \
     (uint32_t)(( \
      (uint32_t)(FTM_CnSC_REG(PeripheralBase,(ChannelIdx)) | FTM_CnSC_DMA_MASK)) & ( \
      (uint32_t)(~(uint32_t)FTM_CnSC_CHF_MASK))) \
  )


#endif /* FTM_MACROS_H_ */
