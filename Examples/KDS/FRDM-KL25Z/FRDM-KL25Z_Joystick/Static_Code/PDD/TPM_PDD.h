/*
  PDD layer implementation for peripheral type TPM
  (C) 2013 Freescale, Inc. All rights reserved.

  This file is static and it is generated from API-Factory
*/

#if !defined(TPM_PDD_H_)
#define TPM_PDD_H_

/* ----------------------------------------------------------------------------
   -- Test if supported MCU is active
   ---------------------------------------------------------------------------- */

#if !defined(MCU_ACTIVE)
  // No MCU is active
  #error TPM PDD library: No derivative is active. Place proper #include with PDD memory map before including PDD library.
#elif \
      !defined(MCU_MKL02Z4) /* TPM0, TPM1 */ && \
      !defined(MCU_MKL04Z4) /* TPM0, TPM1 */ && \
      !defined(MCU_MKL05Z4) /* TPM0, TPM1 */ && \
      !defined(MCU_MKL14Z4) /* TPM0, TPM1, TPM2 */ && \
      !defined(MCU_MKL15Z4) /* TPM0, TPM1, TPM2 */ && \
      !defined(MCU_MKL16Z4) /* TPM0, TPM1, TPM2 */ && \
      !defined(MCU_MKL24Z4) /* TPM0, TPM1, TPM2 */ && \
      !defined(MCU_MKL25Z4) /* TPM0, TPM1, TPM2 */ && \
      !defined(MCU_MKL26Z4) /* TPM0, TPM1, TPM2 */ && \
      !defined(MCU_MKL34Z4) /* TPM0, TPM1, TPM2 */ && \
      !defined(MCU_MKL36Z4) /* TPM0, TPM1, TPM2 */ && \
      !defined(MCU_MKL46Z4) /* TPM0, TPM1, TPM2 */ && \
      !defined(MCU_MKW01Z4) /* TPM0, TPM1, TPM2 */
  // Unsupported MCU is active
  #error TPM PDD library: Unsupported derivative is active.
#endif

#include "PDD_Types.h"

/* ----------------------------------------------------------------------------
   -- Method symbol definitions
   ---------------------------------------------------------------------------- */

/* TPM channel constants */
#define TPM_PDD_CHANNEL_0 0U                     /**< 0 */
#define TPM_PDD_CHANNEL_1 0x1U                   /**< 1 */
#define TPM_PDD_CHANNEL_2 0x2U                   /**< 2 */
#define TPM_PDD_CHANNEL_3 0x3U                   /**< 3 */
#define TPM_PDD_CHANNEL_4 0x4U                   /**< 4 */
#define TPM_PDD_CHANNEL_5 0x5U                   /**< 5 */
#define TPM_PDD_CHANNEL_6 0x6U                   /**< 6 */
#define TPM_PDD_CHANNEL_7 0x7U                   /**< 7 */

/* Prescaler constants */
#define TPM_PDD_DIVIDE_1   0U                    /**< 1 */
#define TPM_PDD_DIVIDE_2   0x1U                  /**< 2 */
#define TPM_PDD_DIVIDE_4   0x2U                  /**< 4 */
#define TPM_PDD_DIVIDE_8   0x3U                  /**< 8 */
#define TPM_PDD_DIVIDE_16  0x4U                  /**< 16 */
#define TPM_PDD_DIVIDE_32  0x5U                  /**< 32 */
#define TPM_PDD_DIVIDE_64  0x6U                  /**< 64 */
#define TPM_PDD_DIVIDE_128 0x7U                  /**< 128 */

/* PWM aligned mode constants */
#define TPM_PDD_EDGE_ALIGNED   0U                /**< Edge aligned */
#define TPM_PDD_CENTER_ALIGNED TPM_SC_CPWMS_MASK /**< Center aligned */

#if (defined(MCU_MKL02Z4))
/* Interrupt flag masks for ClearChannelFlag */
  #define TPM_PDD_FLAG_0 TPM_STATUS_CH0F_MASK      /**< 0 */
  #define TPM_PDD_FLAG_1 TPM_STATUS_CH1F_MASK      /**< 1 */

#else /* (defined(MCU_MKL04Z4)) || (defined(MCU_MKL05Z4)) || (defined(MCU_MKL14Z4)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL16Z4)) || (defined(MCU_MKL24Z4)) || (defined(MCU_MKL25Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL34Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKW01Z4)) */
/* Interrupt flag masks for ClearChannelFlag */
  #define TPM_PDD_FLAG_0 TPM_STATUS_CH0F_MASK      /**< 0 */
  #define TPM_PDD_FLAG_1 TPM_STATUS_CH1F_MASK      /**< 1 */
  #define TPM_PDD_FLAG_2 TPM_STATUS_CH2F_MASK      /**< 2 */
  #define TPM_PDD_FLAG_3 TPM_STATUS_CH3F_MASK      /**< 3 */
  #define TPM_PDD_FLAG_4 TPM_STATUS_CH4F_MASK      /**< 4 */
  #define TPM_PDD_FLAG_5 TPM_STATUS_CH5F_MASK      /**< 5 */

#endif /* (defined(MCU_MKL04Z4)) || (defined(MCU_MKL05Z4)) || (defined(MCU_MKL14Z4)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL16Z4)) || (defined(MCU_MKL24Z4)) || (defined(MCU_MKL25Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL34Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKW01Z4)) */
/* Clock source constants. */
#define TPM_PDD_DISABLED 0U                      /**< Disabled */
#define TPM_PDD_SYSTEM   0x8U                    /**< Counter clock */
#define TPM_PDD_EXTERNAL 0x10U                   /**< External clock */

/* Edge and level constants. */
#define TPM_PDD_EDGE_NONE    0U                  /**< Disabled */
#define TPM_PDD_EDGE_RISING  0x4U                /**< Rising */
#define TPM_PDD_EDGE_FALLING 0x8U                /**< Falling */
#define TPM_PDD_EDGE_BOTH    0xCU                /**< Both */

/* Output action constants. */
#define TPM_PDD_OUTPUT_NONE   0U                 /**< Disconnect */
#define TPM_PDD_OUTPUT_TOGGLE 0x10U              /**< Toggle */
#define TPM_PDD_OUTPUT_CLEAR  0x20U              /**< Clear */
#define TPM_PDD_OUTPUT_SET    0x30U              /**< Set */

/* DBG mode constants. */
#define TPM_PDD_DBG_00 0U                        /**< TPM counter is paused and does not increment during debug mode. Trigger inputs and input capture events are also ignored. */
#define TPM_PDD_DBG_11 0xC0U                     /**< TPM counter continues in debug mode. */


/* ----------------------------------------------------------------------------
   -- SetPrescaler
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets prescale value.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Prescaler New value of the prescaler. Use constants from group
 *        "Prescaler constants". This parameter is 3 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: TPM0_SC, TPM1_SC,
 *          TPM2_SC (depending on the peripheral).
 * @par Example:
 *      @code
 *      TPM_PDD_SetPrescaler(<peripheral>_BASE_PTR, TPM_PDD_DIVIDE_1);
 *      @endcode
 */
#define TPM_PDD_SetPrescaler(PeripheralBase, Prescaler) ( \
    TPM_SC_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       TPM_SC_REG(PeripheralBase)) & (( \
       (uint32_t)(~(uint32_t)TPM_SC_PS_MASK)) & ( \
       (uint32_t)(~(uint32_t)TPM_SC_TOF_MASK))))) | ( \
      (uint32_t)(Prescaler))) \
  )

/* ----------------------------------------------------------------------------
   -- SelectPrescalerSource
   ---------------------------------------------------------------------------- */

/**
 * @brief Select clock source.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Source New value of the source. This parameter is of "Clock source
 *        constants." type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: TPM0_SC, TPM1_SC,
 *          TPM2_SC (depending on the peripheral).
 * @par Example:
 *      @code
 *      TPM_PDD_SelectPrescalerSource(<peripheral>_BASE_PTR, TPM_PDD_DISABLED);
 *      @endcode
 */
#define TPM_PDD_SelectPrescalerSource(PeripheralBase, Source) ( \
    TPM_SC_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       TPM_SC_REG(PeripheralBase)) & (( \
       (uint32_t)(~(uint32_t)TPM_SC_CMOD_MASK)) & ( \
       (uint32_t)(~(uint32_t)TPM_SC_TOF_MASK))))) | ( \
      (uint32_t)(Source))) \
  )

/* ----------------------------------------------------------------------------
   -- GetEnableDeviceStatus
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns current state of TPM device.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: TPM0_SC, TPM1_SC,
 *          TPM2_SC (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result = TPM_PDD_GetEnableDeviceStatus(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define TPM_PDD_GetEnableDeviceStatus(PeripheralBase) ( \
    (uint32_t)(TPM_SC_REG(PeripheralBase) & TPM_SC_CMOD_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- SelectPwmAlignMode
   ---------------------------------------------------------------------------- */

/**
 * @brief Configures PWM aligned mode.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mode New value of the mode. Use constants from group "PWM aligned mode
 *        constants". This parameter is 32 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: TPM0_SC, TPM1_SC,
 *          TPM2_SC (depending on the peripheral).
 * @par Example:
 *      @code
 *      TPM_PDD_SelectPwmAlignMode(<peripheral>_BASE_PTR, TPM_PDD_EDGE_ALIGNED);
 *      @endcode
 */
#define TPM_PDD_SelectPwmAlignMode(PeripheralBase, Mode) ( \
    TPM_SC_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       TPM_SC_REG(PeripheralBase)) & (( \
       (uint32_t)(~(uint32_t)TPM_SC_CPWMS_MASK)) & ( \
       (uint32_t)(~(uint32_t)TPM_SC_TOF_MASK))))) | ( \
      (uint32_t)(Mode))) \
  )

/* ----------------------------------------------------------------------------
   -- GetOverflowInterruptMask
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns overflow interrupt mask.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: TPM0_SC, TPM1_SC,
 *          TPM2_SC (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result =
 *      TPM_PDD_GetOverflowInterruptMask(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define TPM_PDD_GetOverflowInterruptMask(PeripheralBase) ( \
    (uint32_t)(TPM_SC_REG(PeripheralBase) & TPM_SC_TOIE_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- EnableOverflowInterrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables the TPM overflow interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: TPM0_SC, TPM1_SC,
 *          TPM2_SC (depending on the peripheral).
 * @par Example:
 *      @code
 *      TPM_PDD_EnableOverflowInterrupt(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define TPM_PDD_EnableOverflowInterrupt(PeripheralBase) ( \
    TPM_SC_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(TPM_SC_REG(PeripheralBase) | TPM_SC_TOIE_MASK)) & ( \
      (uint32_t)(~(uint32_t)TPM_SC_TOF_MASK))) \
  )

/* ----------------------------------------------------------------------------
   -- DisableOverflowInterrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Disables the TPM overflow interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: TPM0_SC, TPM1_SC,
 *          TPM2_SC (depending on the peripheral).
 * @par Example:
 *      @code
 *      TPM_PDD_DisableOverflowInterrupt(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define TPM_PDD_DisableOverflowInterrupt(PeripheralBase) ( \
    TPM_SC_REG(PeripheralBase) &= \
     (uint32_t)(( \
      (uint32_t)(~(uint32_t)TPM_SC_TOIE_MASK)) & ( \
      (uint32_t)(~(uint32_t)TPM_SC_TOF_MASK))) \
  )

/* ----------------------------------------------------------------------------
   -- GetOverflowInterruptFlag
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns overflow interrupt flag bit.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: TPM0_SC, TPM1_SC,
 *          TPM2_SC (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result =
 *      TPM_PDD_GetOverflowInterruptFlag(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define TPM_PDD_GetOverflowInterruptFlag(PeripheralBase) ( \
    (uint32_t)(TPM_SC_REG(PeripheralBase) & TPM_SC_TOF_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- ClearOverflowInterruptFlag
   ---------------------------------------------------------------------------- */

/**
 * @brief Clears overflow interrupt flag.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: TPM0_SC, TPM1_SC,
 *          TPM2_SC (depending on the peripheral).
 * @par Example:
 *      @code
 *      TPM_PDD_ClearOverflowInterruptFlag(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define TPM_PDD_ClearOverflowInterruptFlag(PeripheralBase) ( \
    TPM_SC_REG(PeripheralBase) |= \
     TPM_SC_TOF_MASK \
  )

/* ----------------------------------------------------------------------------
   -- WriteStatusControlReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes value to the status and control register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value New content of the status and control register. This parameter
 *        is a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: TPM0_SC, TPM1_SC,
 *          TPM2_SC (depending on the peripheral).
 * @par Example:
 *      @code
 *      TPM_PDD_WriteStatusControlReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define TPM_PDD_WriteStatusControlReg(PeripheralBase, Value) ( \
    TPM_SC_REG(PeripheralBase) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadStatusControlReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the status and control register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: TPM0_SC, TPM1_SC,
 *          TPM2_SC (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result = TPM_PDD_ReadStatusControlReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define TPM_PDD_ReadStatusControlReg(PeripheralBase) ( \
    TPM_SC_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- ReadCounterReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the counter register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: TPM0_CNT, TPM1_CNT,
 *          TPM2_CNT (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result = TPM_PDD_ReadCounterReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define TPM_PDD_ReadCounterReg(PeripheralBase) ( \
    TPM_CNT_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- InitializeCounter
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes value 0 to the counter register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: TPM0_CNT, TPM1_CNT,
 *          TPM2_CNT (depending on the peripheral).
 * @par Example:
 *      @code
 *      TPM_PDD_InitializeCounter(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define TPM_PDD_InitializeCounter(PeripheralBase) ( \
    TPM_CNT_REG(PeripheralBase) = \
     0U \
  )

/* ----------------------------------------------------------------------------
   -- WriteModuloReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes value to the modulo register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value New content of the modulo register. This parameter is a 32-bit
 *        value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: TPM0_MOD, TPM1_MOD,
 *          TPM2_MOD (depending on the peripheral).
 * @par Example:
 *      @code
 *      TPM_PDD_WriteModuloReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define TPM_PDD_WriteModuloReg(PeripheralBase, Value) ( \
    TPM_MOD_REG(PeripheralBase) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadModuloReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the modulo register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: TPM0_MOD, TPM1_MOD,
 *          TPM2_MOD (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result = TPM_PDD_ReadModuloReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define TPM_PDD_ReadModuloReg(PeripheralBase) ( \
    TPM_MOD_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- EnableChannelDma
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables the TPM channel DMA.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param ChannelIdx TPM channel index. This parameter is of index type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CnSC[ChannelIdx].
 * @par Example:
 *      @code
 *      TPM_PDD_EnableChannelDma(<peripheral>_BASE_PTR, periphID);
 *      @endcode
 */
#define TPM_PDD_EnableChannelDma(PeripheralBase, ChannelIdx) ( \
    TPM_CnSC_REG(PeripheralBase,(ChannelIdx)) = \
     (uint32_t)(( \
      (uint32_t)(TPM_CnSC_REG(PeripheralBase,(ChannelIdx)) | TPM_CnSC_DMA_MASK)) & ( \
      (uint32_t)(~(uint32_t)TPM_CnSC_CHF_MASK))) \
  )

/* ----------------------------------------------------------------------------
   -- DisableChannelDma
   ---------------------------------------------------------------------------- */

/**
 * @brief Disables the TPM channel DMA.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param ChannelIdx TPM channel index. This parameter is of index type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CnSC[ChannelIdx].
 * @par Example:
 *      @code
 *      TPM_PDD_DisableChannelDma(<peripheral>_BASE_PTR, periphID);
 *      @endcode
 */
#define TPM_PDD_DisableChannelDma(PeripheralBase, ChannelIdx) ( \
    TPM_CnSC_REG(PeripheralBase,(ChannelIdx)) &= \
     (uint32_t)(( \
      (uint32_t)(~(uint32_t)TPM_CnSC_DMA_MASK)) & ( \
      (uint32_t)(~(uint32_t)TPM_CnSC_CHF_MASK))) \
  )

/* ----------------------------------------------------------------------------
   -- SelectChannelEdgeLevel
   ---------------------------------------------------------------------------- */

/**
 * @brief Selects the TPM channel edge and level.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param ChannelIdx TPM channel index. This parameter is of index type.
 * @param ELSBA_val TPM channel ELSB:ELSA bits. This parameter is of "Edge and
 *        level constants." type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CnSC[ChannelIdx].
 * @par Example:
 *      @code
 *      TPM_PDD_SelectChannelEdgeLevel(<peripheral>_BASE_PTR, periphID,
 *      TPM_PDD_EDGE_NONE);
 *      @endcode
 */
#define TPM_PDD_SelectChannelEdgeLevel(PeripheralBase, ChannelIdx, ELSBA_val) ( \
    TPM_CnSC_REG(PeripheralBase,(ChannelIdx)) = \
     (uint32_t)(( \
      (uint32_t)(( \
       TPM_CnSC_REG(PeripheralBase,(ChannelIdx))) & (( \
       (uint32_t)(~(uint32_t)((uint32_t)0x3U << 2U))) & ( \
       (uint32_t)(~(uint32_t)TPM_CnSC_CHF_MASK))))) | ( \
      (uint32_t)(ELSBA_val))) \
  )

/* ----------------------------------------------------------------------------
   -- SelectChannelMode
   ---------------------------------------------------------------------------- */

/**
 * @brief Selects the TPM channel mode.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param ChannelIdx TPM channel index. This parameter is of index type.
 * @param MSBA_val TPM channel MSB:MSA bits. This parameter is of "Output action
 *        constants." type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CnSC[ChannelIdx].
 * @par Example:
 *      @code
 *      TPM_PDD_SelectChannelMode(<peripheral>_BASE_PTR, periphID,
 *      TPM_PDD_OUTPUT_NONE);
 *      @endcode
 */
#define TPM_PDD_SelectChannelMode(PeripheralBase, ChannelIdx, MSBA_val) ( \
    TPM_CnSC_REG(PeripheralBase,(ChannelIdx)) = \
     (uint32_t)(( \
      (uint32_t)(( \
       TPM_CnSC_REG(PeripheralBase,(ChannelIdx))) & (( \
       (uint32_t)(~(uint32_t)((uint32_t)0x3U << 4U))) & ( \
       (uint32_t)(~(uint32_t)TPM_CnSC_CHF_MASK))))) | ( \
      (uint32_t)(MSBA_val))) \
  )

/* ----------------------------------------------------------------------------
   -- GetChannelInterruptMask
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns channel interrupt mask.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param ChannelIdx TPM channel index. This parameter is of index type.
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: CnSC[ChannelIdx].
 * @par Example:
 *      @code
 *      uint32_t result =
 *      TPM_PDD_GetChannelInterruptMask(<peripheral>_BASE_PTR, periphID);
 *      @endcode
 */
#define TPM_PDD_GetChannelInterruptMask(PeripheralBase, ChannelIdx) ( \
    (uint32_t)(TPM_CnSC_REG(PeripheralBase,(ChannelIdx)) & TPM_CnSC_CHIE_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- EnableChannelInterrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables the TPM channel interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param ChannelIdx TPM channel index. This parameter is of index type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CnSC[ChannelIdx].
 * @par Example:
 *      @code
 *      TPM_PDD_EnableChannelInterrupt(<peripheral>_BASE_PTR, periphID);
 *      @endcode
 */
#define TPM_PDD_EnableChannelInterrupt(PeripheralBase, ChannelIdx) ( \
    TPM_CnSC_REG(PeripheralBase,(ChannelIdx)) = \
     (uint32_t)(( \
      (uint32_t)(TPM_CnSC_REG(PeripheralBase,(ChannelIdx)) | TPM_CnSC_CHIE_MASK)) & ( \
      (uint32_t)(~(uint32_t)TPM_CnSC_CHF_MASK))) \
  )

/* ----------------------------------------------------------------------------
   -- DisableChannelInterrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Disables the TPM channel interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param ChannelIdx TPM channel index. This parameter is of index type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CnSC[ChannelIdx].
 * @par Example:
 *      @code
 *      TPM_PDD_DisableChannelInterrupt(<peripheral>_BASE_PTR, periphID);
 *      @endcode
 */
#define TPM_PDD_DisableChannelInterrupt(PeripheralBase, ChannelIdx) ( \
    TPM_CnSC_REG(PeripheralBase,(ChannelIdx)) &= \
     (uint32_t)(( \
      (uint32_t)(~(uint32_t)TPM_CnSC_CHIE_MASK)) & ( \
      (uint32_t)(~(uint32_t)TPM_CnSC_CHF_MASK))) \
  )

/* ----------------------------------------------------------------------------
   -- GetChannelInterruptFlag
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns channel interrupt flag bit.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param ChannelIdx TPM channel index. This parameter is of index type.
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: CnSC[ChannelIdx].
 * @par Example:
 *      @code
 *      uint32_t result =
 *      TPM_PDD_GetChannelInterruptFlag(<peripheral>_BASE_PTR, periphID);
 *      @endcode
 */
#define TPM_PDD_GetChannelInterruptFlag(PeripheralBase, ChannelIdx) ( \
    (uint32_t)(TPM_CnSC_REG(PeripheralBase,(ChannelIdx)) & TPM_CnSC_CHF_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- ClearChannelInterruptFlag
   ---------------------------------------------------------------------------- */

/**
 * @brief Clears channel interrupt flag.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param ChannelIdx TPM channel index. This parameter is of index type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CnSC[ChannelIdx].
 * @par Example:
 *      @code
 *      TPM_PDD_ClearChannelInterruptFlag(<peripheral>_BASE_PTR, periphID);
 *      @endcode
 */
#define TPM_PDD_ClearChannelInterruptFlag(PeripheralBase, ChannelIdx) ( \
    TPM_CnSC_REG(PeripheralBase,(ChannelIdx)) |= \
     TPM_CnSC_CHF_MASK \
  )

/* ----------------------------------------------------------------------------
   -- ReadChannelControlReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the channel status and control register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param ChannelIdx TPM channel index. This parameter is of index type.
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: CnSC[ChannelIdx].
 * @par Example:
 *      @code
 *      uint32_t result = TPM_PDD_ReadChannelControlReg(<peripheral>_BASE_PTR,
 *      periphID);
 *      @endcode
 */
#define TPM_PDD_ReadChannelControlReg(PeripheralBase, ChannelIdx) ( \
    TPM_CnSC_REG(PeripheralBase,(ChannelIdx)) \
  )

/* ----------------------------------------------------------------------------
   -- WriteChannelControlReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes value to the channel status and control register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param ChannelIdx TPM channel index. This parameter is of index type.
 * @param Value New content of the channel status and control register. This
 *        parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CnSC[ChannelIdx].
 * @par Example:
 *      @code
 *      TPM_PDD_WriteChannelControlReg(<peripheral>_BASE_PTR, periphID, 1);
 *      @endcode
 */
#define TPM_PDD_WriteChannelControlReg(PeripheralBase, ChannelIdx, Value) ( \
    TPM_CnSC_REG(PeripheralBase,(ChannelIdx)) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadChannelValueReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the channel value register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param ChannelIdx TPM channel index. This parameter is of index type.
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: CnV[ChannelIdx].
 * @par Example:
 *      @code
 *      uint32_t result = TPM_PDD_ReadChannelValueReg(<peripheral>_BASE_PTR,
 *      periphID);
 *      @endcode
 */
#define TPM_PDD_ReadChannelValueReg(PeripheralBase, ChannelIdx) ( \
    TPM_CnV_REG(PeripheralBase,(ChannelIdx)) \
  )

/* ----------------------------------------------------------------------------
   -- WriteChannelValueReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes value to the channel value register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param ChannelIdx TPM channel index. This parameter is of index type.
 * @param Value New content of the channel value register. This parameter is a
 *        32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CnV[ChannelIdx].
 * @par Example:
 *      @code
 *      TPM_PDD_WriteChannelValueReg(<peripheral>_BASE_PTR, periphID, 1);
 *      @endcode
 */
#define TPM_PDD_WriteChannelValueReg(PeripheralBase, ChannelIdx, Value) ( \
    TPM_CnV_REG(PeripheralBase,(ChannelIdx)) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- GetChannelFlags
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the capture and compare status register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: TPM0_STATUS,
 *          TPM1_STATUS, TPM2_STATUS (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result = TPM_PDD_GetChannelFlags(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define TPM_PDD_GetChannelFlags(PeripheralBase) ( \
    TPM_STATUS_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- ClearChannelFlags
   ---------------------------------------------------------------------------- */

/**
 * @brief Clears channel interrupt flag.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mask Interrupt flag mask. This parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: TPM0_STATUS,
 *          TPM1_STATUS, TPM2_STATUS (depending on the peripheral).
 * @par Example:
 *      @code
 *      TPM_PDD_ClearChannelFlags(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define TPM_PDD_ClearChannelFlags(PeripheralBase, Mask) ( \
    TPM_STATUS_REG(PeripheralBase) = \
     (uint32_t)((uint32_t)(~(uint32_t)(Mask)) & (uint32_t)0xFFU) \
  )

/* ----------------------------------------------------------------------------
   -- SetGlobalTimeBase
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables the TPM to use an external global time base signal that is
 * generated by another TPM.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of the global time base output. This parameter
 *        is of "Global enumeration used for specifying general enable/disable
 *        states (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: TPM0_CONF, TPM1_CONF,
 *          TPM2_CONF (depending on the peripheral).
 * @par Example:
 *      @code
 *      TPM_PDD_SetGlobalTimeBase(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define TPM_PDD_SetGlobalTimeBase(PeripheralBase, State) ( \
    TPM_CONF_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(TPM_CONF_REG(PeripheralBase) & (uint32_t)(~(uint32_t)TPM_CONF_GTBEEN_MASK))) | ( \
      (uint32_t)((uint32_t)(State) << TPM_CONF_GTBEEN_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SelectDBGMode
   ---------------------------------------------------------------------------- */

/**
 * @brief Selects the TPM behavior in DBG mode.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mode New value of the DBG mode. This parameter is of "DBG mode
 *        constants." type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: TPM0_CONF, TPM1_CONF,
 *          TPM2_CONF (depending on the peripheral).
 * @par Example:
 *      @code
 *      TPM_PDD_SelectDBGMode(<peripheral>_BASE_PTR, TPM_PDD_DBG_00);
 *      @endcode
 */
#define TPM_PDD_SelectDBGMode(PeripheralBase, Mode) ( \
    TPM_CONF_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(TPM_CONF_REG(PeripheralBase) & (uint32_t)(~(uint32_t)TPM_CONF_DBGMODE_MASK))) | ( \
      (uint32_t)(Mode))) \
  )

/* ----------------------------------------------------------------------------
   -- SetDozeEnable
   ---------------------------------------------------------------------------- */

/**
 * @brief Configures the TPM behavior in doze mode.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of internal TPM counter in Doze mode. This
 *        parameter is of "Global enumeration used for specifying general
 *        enable/disable states (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: TPM0_CONF, TPM1_CONF,
 *          TPM2_CONF (depending on the peripheral).
 * @par Example:
 *      @code
 *      TPM_PDD_SetDozeEnable(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define TPM_PDD_SetDozeEnable(PeripheralBase, State) ( \
    ((State) == PDD_DISABLE) ? ( \
      TPM_CONF_REG(PeripheralBase) |= \
       TPM_CONF_DOZEEN_MASK) : ( \
      TPM_CONF_REG(PeripheralBase) &= \
       (uint32_t)(~(uint32_t)TPM_CONF_DOZEEN_MASK)) \
  )

/* ----------------------------------------------------------------------------
   -- WriteConfigurationReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes value to the configuration register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value New content of the configuration register. This parameter is a
 *        32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: TPM0_CONF, TPM1_CONF,
 *          TPM2_CONF (depending on the peripheral).
 * @par Example:
 *      @code
 *      TPM_PDD_WriteConfigurationReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define TPM_PDD_WriteConfigurationReg(PeripheralBase, Value) ( \
    TPM_CONF_REG(PeripheralBase) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadConfigurationReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the configuration register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: TPM0_CONF, TPM1_CONF,
 *          TPM2_CONF (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result = TPM_PDD_ReadConfigurationReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define TPM_PDD_ReadConfigurationReg(PeripheralBase) ( \
    TPM_CONF_REG(PeripheralBase) \
  )
#endif  /* #if defined(TPM_PDD_H_) */

/* TPM_PDD.h, eof. */
