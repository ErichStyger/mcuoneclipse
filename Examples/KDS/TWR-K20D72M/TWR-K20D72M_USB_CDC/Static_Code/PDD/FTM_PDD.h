/*
  PDD layer implementation for peripheral type FTM
  (C) 2013 Freescale, Inc. All rights reserved.

  This file is static and it is generated from API-Factory
*/

#if !defined(FTM_PDD_H_)
#define FTM_PDD_H_

/* ----------------------------------------------------------------------------
   -- Test if supported MCU is active
   ---------------------------------------------------------------------------- */

#if !defined(MCU_ACTIVE)
  // No MCU is active
  #error FTM PDD library: No derivative is active. Place proper #include with PDD memory map before including PDD library.
#elif \
      !defined(MCU_MK10D10) /* FTM0, FTM1, FTM2 */ && \
      !defined(MCU_MK10D5) /* FTM0, FTM1 */ && \
      !defined(MCU_MK10D7) /* FTM0, FTM1, FTM2 */ && \
      !defined(MCU_MK10F12) /* FTM0, FTM1, FTM2, FTM3 */ && \
      !defined(MCU_MK10DZ10) /* FTM0, FTM1, FTM2 */ && \
      !defined(MCU_MK11DA5) /* FTM0, FTM1, FTM2 */ && \
      !defined(MCU_MK11DA5WS) /* FTM0, FTM1, FTM2 */ && \
      !defined(MCU_MK11D5) /* FTM0, FTM1, FTM2 */ && \
      !defined(MCU_MK11D5WS) /* FTM0, FTM1, FTM2 */ && \
      !defined(MCU_MK12D5) /* FTM0, FTM1, FTM2 */ && \
      !defined(MCU_MK20D10) /* FTM0, FTM1, FTM2 */ && \
      !defined(MCU_MK20D5) /* FTM0, FTM1 */ && \
      !defined(MCU_MK20D7) /* FTM0, FTM1, FTM2 */ && \
      !defined(MCU_MK20F12) /* FTM0, FTM1, FTM2, FTM3 */ && \
      !defined(MCU_MK20DZ10) /* FTM0, FTM1, FTM2 */ && \
      !defined(MCU_MK21DA5) /* FTM0, FTM1, FTM2 */ && \
      !defined(MCU_MK21DA5WS) /* FTM0, FTM1, FTM2 */ && \
      !defined(MCU_MK21D5) /* FTM0, FTM1, FTM2 */ && \
      !defined(MCU_MK21D5WS) /* FTM0, FTM1, FTM2 */ && \
      !defined(MCU_MK21FA12) /* FTM0, FTM1, FTM2, FTM3 */ && \
      !defined(MCU_MK21FA12WS) /* FTM0, FTM1, FTM2, FTM3 */ && \
      !defined(MCU_MK21F12) /* FTM0, FTM1, FTM2, FTM3 */ && \
      !defined(MCU_MK21F12WS) /* FTM0, FTM1, FTM2, FTM3 */ && \
      !defined(MCU_MK22D5) /* FTM0, FTM1, FTM2 */ && \
      !defined(MCU_MK22F12810) /* FTM0, FTM1, FTM2 */ && \
      !defined(MCU_MK22F12) /* FTM0, FTM1, FTM2, FTM3 */ && \
      !defined(MCU_MK22F25612) /* FTM0, FTM1, FTM2 */ && \
      !defined(MCU_MK22F51212) /* FTM0, FTM1, FTM2, FTM3 */ && \
      !defined(MCU_MK24F12) /* FTM0, FTM1, FTM2, FTM3 */ && \
      !defined(MCU_MK30D10) /* FTM0, FTM1, FTM2 */ && \
      !defined(MCU_MK30D7) /* FTM0, FTM1, FTM2 */ && \
      !defined(MCU_MK30DZ10) /* FTM0, FTM1, FTM2 */ && \
      !defined(MCU_MK40D10) /* FTM0, FTM1, FTM2 */ && \
      !defined(MCU_MK40D7) /* FTM0, FTM1, FTM2 */ && \
      !defined(MCU_MK40DZ10) /* FTM0, FTM1, FTM2 */ && \
      !defined(MCU_MK40X256VMD100) /* FTM0, FTM1, FTM2 */ && \
      !defined(MCU_MK50D10) /* FTM0, FTM1, FTM2 */ && \
      !defined(MCU_MK50D7) /* FTM0, FTM1, FTM2 */ && \
      !defined(MCU_MK50DZ10) /* FTM0, FTM1, FTM2 */ && \
      !defined(MCU_MK51D10) /* FTM0, FTM1, FTM2 */ && \
      !defined(MCU_MK51D7) /* FTM0, FTM1, FTM2 */ && \
      !defined(MCU_MK51DZ10) /* FTM0, FTM1, FTM2 */ && \
      !defined(MCU_MK52D10) /* FTM0, FTM1, FTM2 */ && \
      !defined(MCU_MK52DZ10) /* FTM0, FTM1, FTM2 */ && \
      !defined(MCU_MK53D10) /* FTM0, FTM1, FTM2 */ && \
      !defined(MCU_MK53DZ10) /* FTM0, FTM1, FTM2 */ && \
      !defined(MCU_MK60D10) /* FTM0, FTM1, FTM2 */ && \
      !defined(MCU_MK60F12) /* FTM0, FTM1, FTM2, FTM3 */ && \
      !defined(MCU_MK60F15) /* FTM0, FTM1, FTM2, FTM3 */ && \
      !defined(MCU_MK60DZ10) /* FTM0, FTM1, FTM2 */ && \
      !defined(MCU_MK60N512VMD100) /* FTM0, FTM1, FTM2 */ && \
      !defined(MCU_MK61F12) /* FTM0, FTM1, FTM2, FTM3 */ && \
      !defined(MCU_MK61F15) /* FTM0, FTM1, FTM2, FTM3 */ && \
      !defined(MCU_MK61F12WS) /* FTM0, FTM1, FTM2, FTM3 */ && \
      !defined(MCU_MK61F15WS) /* FTM0, FTM1, FTM2, FTM3 */ && \
      !defined(MCU_MK63F12) /* FTM0, FTM1, FTM2, FTM3 */ && \
      !defined(MCU_MK63F12WS) /* FTM0, FTM1, FTM2, FTM3 */ && \
      !defined(MCU_MK64F12) /* FTM0, FTM1, FTM2, FTM3 */ && \
      !defined(MCU_MK70F12) /* FTM0, FTM1, FTM2, FTM3 */ && \
      !defined(MCU_MK70F15) /* FTM0, FTM1, FTM2, FTM3 */ && \
      !defined(MCU_MK70F12WS) /* FTM0, FTM1, FTM2, FTM3 */ && \
      !defined(MCU_MK70F15WS) /* FTM0, FTM1, FTM2, FTM3 */ && \
      !defined(MCU_MKE02Z2) /* FTM0, FTM1, FTM2 */ && \
      !defined(MCU_MKE02Z4) /* FTM0, FTM1, FTM2 */ && \
      !defined(MCU_SKEAZN642) /* FTM0, FTM1, FTM2 */ && \
      !defined(MCU_MKE04Z1284) /* FTM0, FTM1, FTM2 */ && \
      !defined(MCU_MKE04Z4) /* FTM0, FTM2 */ && \
      !defined(MCU_SKEAZN84) /* FTM0, FTM2 */ && \
      !defined(MCU_MKE06Z4) /* FTM0, FTM1, FTM2 */ && \
      !defined(MCU_MKV10Z7) /* FTM0, FTM1, FTM2 */ && \
      !defined(MCU_MKV31F12810) /* FTM0, FTM1, FTM2 */ && \
      !defined(MCU_MKV31F25612) /* FTM0, FTM1, FTM2 */ && \
      !defined(MCU_MKV31F51212) /* FTM0, FTM1, FTM2, FTM3 */ && \
      !defined(MCU_MKW21D5) /* FTM0, FTM1, FTM2 */ && \
      !defined(MCU_MKW21D5WS) /* FTM0, FTM1, FTM2 */ && \
      !defined(MCU_MKW22D5) /* FTM0, FTM1, FTM2 */ && \
      !defined(MCU_MKW22D5WS) /* FTM0, FTM1, FTM2 */ && \
      !defined(MCU_MKW24D5) /* FTM0, FTM1, FTM2 */ && \
      !defined(MCU_MKW24D5WS) /* FTM0, FTM1, FTM2 */ && \
      !defined(MCU_SKEAZ1284) /* FTM0, FTM1, FTM2 */
  // Unsupported MCU is active
  #error FTM PDD library: Unsupported derivative is active.
#endif

#include "PDD_Types.h"

/* ----------------------------------------------------------------------------
   -- Method symbol definitions
   ---------------------------------------------------------------------------- */

/* FTM channel constants */
#define FTM_PDD_CHANNEL_0 0U                     /**< 0 */
#define FTM_PDD_CHANNEL_1 0x1U                   /**< 1 */
#define FTM_PDD_CHANNEL_2 0x2U                   /**< 2 */
#define FTM_PDD_CHANNEL_3 0x3U                   /**< 3 */
#define FTM_PDD_CHANNEL_4 0x4U                   /**< 4 */
#define FTM_PDD_CHANNEL_5 0x5U                   /**< 5 */
#define FTM_PDD_CHANNEL_6 0x6U                   /**< 6 */
#define FTM_PDD_CHANNEL_7 0x7U                   /**< 7 */

/* Prescaler constants */
#define FTM_PDD_DIVIDE_1   0U                    /**< 1 */
#define FTM_PDD_DIVIDE_2   0x1U                  /**< 2 */
#define FTM_PDD_DIVIDE_4   0x2U                  /**< 4 */
#define FTM_PDD_DIVIDE_8   0x3U                  /**< 8 */
#define FTM_PDD_DIVIDE_16  0x4U                  /**< 16 */
#define FTM_PDD_DIVIDE_32  0x5U                  /**< 32 */
#define FTM_PDD_DIVIDE_64  0x6U                  /**< 64 */
#define FTM_PDD_DIVIDE_128 0x7U                  /**< 128 */

/* PWM aligned mode constants */
#define FTM_PDD_EDGE_ALIGNED   0U                /**< Edge aligned */
#define FTM_PDD_CENTER_ALIGNED FTM_SC_CPWMS_MASK /**< Center aligned */

/* Interrupt flag masks for ClearChannelFlag */
#define FTM_PDD_FLAG_0 0x1U                      /**< 0 */
#define FTM_PDD_FLAG_1 0x2U                      /**< 1 */
#define FTM_PDD_FLAG_2 0x4U                      /**< 2 */
#define FTM_PDD_FLAG_3 0x8U                      /**< 3 */
#define FTM_PDD_FLAG_4 0x10U                     /**< 4 */
#define FTM_PDD_FLAG_5 0x20U                     /**< 5 */
#define FTM_PDD_FLAG_6 0x40U                     /**< 6 */
#define FTM_PDD_FLAG_7 0x80U                     /**< 7 */

/* FTM channel masks. */
#define FTM_PDD_CHANNEL_0_MASK 0x1U              /**< Channel 0 mask */
#define FTM_PDD_CHANNEL_1_MASK 0x2U              /**< Channel 1 mask */
#define FTM_PDD_CHANNEL_2_MASK 0x4U              /**< Channel 2 mask */
#define FTM_PDD_CHANNEL_3_MASK 0x8U              /**< Channel 3 mask */
#define FTM_PDD_CHANNEL_4_MASK 0x10U             /**< Channel 4 mask */
#define FTM_PDD_CHANNEL_5_MASK 0x20U             /**< Channel 5 mask */
#define FTM_PDD_CHANNEL_6_MASK 0x40U             /**< Channel 6 mask */
#define FTM_PDD_CHANNEL_7_MASK 0x80U             /**< Channel 7 mask */

/* Deadtime prescaler constants */
#define FTM_PDD_DT_DIVIDE_1  0U                  /**< 1 */
#define FTM_PDD_DT_DIVIDE_4  0x2U                /**< 4 */
#define FTM_PDD_DT_DIVIDE_16 0x3U                /**< 16 */

/* Clock source constants. */
#define FTM_PDD_DISABLED 0U                      /**< Disabled */
#define FTM_PDD_SYSTEM   0x8U                    /**< System clock */
#define FTM_PDD_FIXED    0x10U                   /**< Fixed clock */
#define FTM_PDD_EXTERNAL 0x18U                   /**< External clock */

/* Edge and level constants. */
#define FTM_PDD_EDGE_NONE    0U                  /**< Disabled */
#define FTM_PDD_EDGE_RISING  0x4U                /**< Rising */
#define FTM_PDD_EDGE_FALLING 0x8U                /**< Falling */
#define FTM_PDD_EDGE_BOTH    0xCU                /**< Both */

/* Output action constants. */
#define FTM_PDD_OUTPUT_NONE   0U                 /**< Disconnect */
#define FTM_PDD_OUTPUT_TOGGLE 0x10U              /**< Toggle */
#define FTM_PDD_OUTPUT_CLEAR  0x20U              /**< Clear */
#define FTM_PDD_OUTPUT_SET    0x30U              /**< Set */

/* Fault mode constants. */
#define FTM_PDD_FAULT_DISABLED      0U           /**< Fault control is disabled for all channels. */
#define FTM_PDD_FAULT_EVEN_MANUAL   0x20U        /**< Fault control is enabled for even channels only (channels 0, 2, 4, and 6), and the selected mode is the manual fault clearing. */
#define FTM_PDD_FAULT_ALL_MANUAL    0x40U        /**< Fault control is enabled for all channels, and the selected mode is the manual fault clearing. */
#define FTM_PDD_FAULT_ALL_AUTOMATIC 0x60U        /**< Fault control is enabled for all channels, and the selected mode is the automatic fault clearing. */

/* PWM synchronization mode constants. */
#define FTM_PDD_NO_RESTRICTIONS   0U             /**< Software and hardware triggers can be used by MOD, CnV, OUTMASK, and FTM counter synchronization. */
#define FTM_PDD_WITH_RESTRICTIONS 0x8U           /**< Software trigger can only be used by MOD and CnV synchronization, and hardware triggers can only be used by OUTMASK and FTM counter synchronization. */

/* Output mask synchronization constants. */
#define FTM_PDD_RISING_EDGES        0U           /**< OUTMASK register is updated with the value of its buffer in all rising edges of the system clock. */
#define FTM_PDD_PWM_SYNCHRONIZATION 0x8U         /**< OUTMASK register is updated with the value of its buffer only by the PWM synchronization. */

/* FTM counter synchronization constants. */
#define FTM_PDD_COUNT_NORMALLY 0U                /**< FTM counter continues to count normally. */
#define FTM_PDD_UPDATE         0x4U              /**< FTM counter is updated with its initial value when the selected trigger is detected. */

/* Phase input polarity constants. */
#define FTM_PDD_QD_NORMAL_POLARITY   0U          /**< Phase input signal is not inverted before identifying the rising and falling edges of this signal. */
#define FTM_PDD_QD_INVERTED_POLARITY 0x1U        /**< Phase input signal is inverted before identifying the rising and falling edges of this signal. */

/* Quadrature decoder encoding mode constants. */
#define FTM_PDD_QD_PHASEA_AND_PHASEB   0U        /**< Phase A and phase B encoding mode. */
#define FTM_PDD_QD_COUNT_AND_DIRECTION 0x8U      /**< Count and direction encoding mode. */

/* BDM mode constants. */
#define FTM_PDD_BDM_00 0U                        /**< FTM counter: stopped. CH(n)F bit: can be set. FTM Channels Output: Functional mode. Writes to MOD, CNTIN, and C(n)V registers: Writes to these registers bypass the registers buffers. */
#define FTM_PDD_BDM_01 0x40U                     /**< FTM counter: stopped. CH(n)F bit: is not set. FTM Channels Output: The channels outputs are forced to their safe value according to POLn bit. Writes to MOD, CNTIN, and C(n)V registers: Writes to these registers bypass the registers buffers. */
#define FTM_PDD_BDM_10 0x80U                     /**< FTM counter: stopped. CH(n)F bit: is not set. FTM Channels Output: The channels outputs are frozen when the chip enters in BDM mode. Writes to MOD, CNTIN, and C(n)V registers: Writes to these registers bypass the registers buffers. */
#define FTM_PDD_BDM_11 0xC0U                     /**< FTM counter: Functional mode. CH(n)F bit: can be set. FTM Channels Output: Functional mode. Writes to MOD, CNTIN, and C(n)V registers: Functional mode. */

/* Fault input polarity constants. */
#define FTM_PDD_FAULT_POLARITY_HIGH 0U           /**< The fault input polarity is active high. A one at the fault input indicates a fault. */
#define FTM_PDD_FAULT_POLARITY_LOW  0x1U         /**< The fault input polarity is active low. A zero at the fault input indicates a fault. */

/* Synchronization mode constants. */
#define FTM_PDD_SYNC_LEGACY   0U                 /**< Legacy PWM synchronization is selected. */
#define FTM_PDD_SYNC_ENHANCED 0x80U              /**< Enhanced PWM synchronization is selected. */

/* Register synchronization constants. */
#define FTM_PDD_SYNC_BY_SYSTEM_CLOCK 0U          /**< Register is updated with its buffer value at all rising edges of system clock. */
#define FTM_PDD_SYNC_BY_PWM          0x1U        /**< Register is updated with its buffer value by the PWM synchronization. */


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
 * @remarks The macro accesses the following registers: FTM0_SC, FTM1_SC,
 *          FTM2_SC, FTM3_SC (depending on the peripheral).
 * @par Example:
 *      @code
 *      FTM_PDD_SetPrescaler(<peripheral>_BASE_PTR, FTM_PDD_DIVIDE_1);
 *      @endcode
 */
#define FTM_PDD_SetPrescaler(PeripheralBase, Prescaler) ( \
    FTM_SC_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       FTM_SC_REG(PeripheralBase)) & (( \
       (uint32_t)(~(uint32_t)FTM_SC_PS_MASK)) & ( \
       (uint32_t)(~(uint32_t)FTM_SC_TOF_MASK))))) | ( \
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
 * @remarks The macro accesses the following registers: FTM0_SC, FTM1_SC,
 *          FTM2_SC, FTM3_SC (depending on the peripheral).
 * @par Example:
 *      @code
 *      FTM_PDD_SelectPrescalerSource(<peripheral>_BASE_PTR, FTM_PDD_DISABLED);
 *      @endcode
 */
#define FTM_PDD_SelectPrescalerSource(PeripheralBase, Source) ( \
    FTM_SC_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       FTM_SC_REG(PeripheralBase)) & (( \
       (uint32_t)(~(uint32_t)FTM_SC_CLKS_MASK)) & ( \
       (uint32_t)(~(uint32_t)FTM_SC_TOF_MASK))))) | ( \
      (uint32_t)(Source))) \
  )

/* ----------------------------------------------------------------------------
   -- GetEnableDeviceStatus
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns current state of FTM device.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: FTM0_SC, FTM1_SC,
 *          FTM2_SC, FTM3_SC (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result = FTM_PDD_GetEnableDeviceStatus(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTM_PDD_GetEnableDeviceStatus(PeripheralBase) ( \
    (uint32_t)(FTM_SC_REG(PeripheralBase) & FTM_SC_CLKS_MASK) \
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
 * @remarks The macro accesses the following registers: FTM0_SC, FTM1_SC,
 *          FTM2_SC, FTM3_SC (depending on the peripheral).
 * @par Example:
 *      @code
 *      FTM_PDD_SelectPwmAlignMode(<peripheral>_BASE_PTR, FTM_PDD_EDGE_ALIGNED);
 *      @endcode
 */
#define FTM_PDD_SelectPwmAlignMode(PeripheralBase, Mode) ( \
    FTM_SC_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       FTM_SC_REG(PeripheralBase)) & (( \
       (uint32_t)(~(uint32_t)FTM_SC_CPWMS_MASK)) & ( \
       (uint32_t)(~(uint32_t)FTM_SC_TOF_MASK))))) | ( \
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
 * @remarks The macro accesses the following registers: FTM0_SC, FTM1_SC,
 *          FTM2_SC, FTM3_SC (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result =
 *      FTM_PDD_GetOverflowInterruptMask(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTM_PDD_GetOverflowInterruptMask(PeripheralBase) ( \
    (uint32_t)(FTM_SC_REG(PeripheralBase) & FTM_SC_TOIE_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- EnableOverflowInterrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables the FTM overflow interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTM0_SC, FTM1_SC,
 *          FTM2_SC, FTM3_SC (depending on the peripheral).
 * @par Example:
 *      @code
 *      FTM_PDD_EnableOverflowInterrupt(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTM_PDD_EnableOverflowInterrupt(PeripheralBase) ( \
    FTM_SC_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(FTM_SC_REG(PeripheralBase) | FTM_SC_TOIE_MASK)) & ( \
      (uint32_t)(~(uint32_t)FTM_SC_TOF_MASK))) \
  )

/* ----------------------------------------------------------------------------
   -- DisableOverflowInterrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Disables the FTM overflow interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTM0_SC, FTM1_SC,
 *          FTM2_SC, FTM3_SC (depending on the peripheral).
 * @par Example:
 *      @code
 *      FTM_PDD_DisableOverflowInterrupt(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTM_PDD_DisableOverflowInterrupt(PeripheralBase) ( \
    FTM_SC_REG(PeripheralBase) &= \
     (uint32_t)(( \
      (uint32_t)(~(uint32_t)FTM_SC_TOIE_MASK)) & ( \
      (uint32_t)(~(uint32_t)FTM_SC_TOF_MASK))) \
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
 * @remarks The macro accesses the following registers: FTM0_SC, FTM1_SC,
 *          FTM2_SC, FTM3_SC (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result =
 *      FTM_PDD_GetOverflowInterruptFlag(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTM_PDD_GetOverflowInterruptFlag(PeripheralBase) ( \
    (uint32_t)(FTM_SC_REG(PeripheralBase) & FTM_SC_TOF_MASK) \
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
 * @remarks The macro accesses the following registers: FTM0_SC, FTM1_SC,
 *          FTM2_SC, FTM3_SC (depending on the peripheral).
 * @par Example:
 *      @code
 *      FTM_PDD_ClearOverflowInterruptFlag(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTM_PDD_ClearOverflowInterruptFlag(PeripheralBase) ( \
    FTM_SC_REG(PeripheralBase) &= \
     (uint32_t)(~(uint32_t)FTM_SC_TOF_MASK) \
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
 * @remarks The macro accesses the following registers: FTM0_CNT, FTM1_CNT,
 *          FTM2_CNT, FTM3_CNT (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result = FTM_PDD_ReadCounterReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTM_PDD_ReadCounterReg(PeripheralBase) ( \
    FTM_CNT_REG(PeripheralBase) \
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
 * @remarks The macro accesses the following registers: FTM0_CNT, FTM1_CNT,
 *          FTM2_CNT, FTM3_CNT (depending on the peripheral).
 * @par Example:
 *      @code
 *      FTM_PDD_InitializeCounter(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTM_PDD_InitializeCounter(PeripheralBase) ( \
    FTM_CNT_REG(PeripheralBase) = \
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
 * @remarks The macro accesses the following registers: FTM0_MOD, FTM1_MOD,
 *          FTM2_MOD, FTM3_MOD (depending on the peripheral).
 * @par Example:
 *      @code
 *      FTM_PDD_WriteModuloReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define FTM_PDD_WriteModuloReg(PeripheralBase, Value) ( \
    FTM_MOD_REG(PeripheralBase) = \
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
 * @remarks The macro accesses the following registers: FTM0_MOD, FTM1_MOD,
 *          FTM2_MOD, FTM3_MOD (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result = FTM_PDD_ReadModuloReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTM_PDD_ReadModuloReg(PeripheralBase) ( \
    FTM_MOD_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- EnableChannelDma
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables the FTM channel DMA.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param ChannelIdx FTM channel index. Use constants from group "FTM channel
 *        constants". This parameter is 32 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CnSC[ChannelIdx].
 * @par Example:
 *      @code
 *      FTM_PDD_EnableChannelDma(<peripheral>_BASE_PTR, FTM_PDD_CHANNEL_0);
 *      @endcode
 */
#define FTM_PDD_EnableChannelDma(PeripheralBase, ChannelIdx) ( \
    FTM_CnSC_REG(PeripheralBase,(ChannelIdx)) = \
     (uint32_t)(( \
      (uint32_t)(FTM_CnSC_REG(PeripheralBase,(ChannelIdx)) | FTM_CnSC_DMA_MASK)) & ( \
      (uint32_t)(~(uint32_t)FTM_CnSC_CHF_MASK))) \
  )

/* ----------------------------------------------------------------------------
   -- DisableChannelDma
   ---------------------------------------------------------------------------- */

/**
 * @brief Disables the FTM channel DMA.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param ChannelIdx FTM channel index. Use constants from group "FTM channel
 *        constants". This parameter is 32 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CnSC[ChannelIdx].
 * @par Example:
 *      @code
 *      FTM_PDD_DisableChannelDma(<peripheral>_BASE_PTR, FTM_PDD_CHANNEL_0);
 *      @endcode
 */
#define FTM_PDD_DisableChannelDma(PeripheralBase, ChannelIdx) ( \
    FTM_CnSC_REG(PeripheralBase,(ChannelIdx)) &= \
     (uint32_t)(( \
      (uint32_t)(~(uint32_t)FTM_CnSC_DMA_MASK)) & ( \
      (uint32_t)(~(uint32_t)FTM_CnSC_CHF_MASK))) \
  )

/* ----------------------------------------------------------------------------
   -- SelectChannelEdgeLevel
   ---------------------------------------------------------------------------- */

/**
 * @brief Selects the FTM channel edge and level.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param ChannelIdx FTM channel index. Use constants from group "FTM channel
 *        constants". This parameter is 32 bits wide.
 * @param ELSBA_val FTM channel ELSB:ELSA bits. This parameter is of "Edge and
 *        level constants." type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CnSC[ChannelIdx].
 * @par Example:
 *      @code
 *      FTM_PDD_SelectChannelEdgeLevel(<peripheral>_BASE_PTR,
 *      FTM_PDD_CHANNEL_0, FTM_PDD_EDGE_NONE);
 *      @endcode
 */
#define FTM_PDD_SelectChannelEdgeLevel(PeripheralBase, ChannelIdx, ELSBA_val) ( \
    FTM_CnSC_REG(PeripheralBase,(ChannelIdx)) = \
     (uint32_t)(( \
      (uint32_t)(( \
       FTM_CnSC_REG(PeripheralBase,(ChannelIdx))) & (( \
       (uint32_t)(~(uint32_t)((uint32_t)0x3U << 2U))) & ( \
       (uint32_t)(~(uint32_t)FTM_CnSC_CHF_MASK))))) | ( \
      (uint32_t)(ELSBA_val))) \
  )

/* ----------------------------------------------------------------------------
   -- SelectChannelMode
   ---------------------------------------------------------------------------- */

/**
 * @brief Selects the FTM channel mode.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param ChannelIdx FTM channel index. Use constants from group "FTM channel
 *        constants". This parameter is 32 bits wide.
 * @param MSBA_val FTM channel MSB:MSA bits. This parameter is of "Output action
 *        constants." type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CnSC[ChannelIdx].
 * @par Example:
 *      @code
 *      FTM_PDD_SelectChannelMode(<peripheral>_BASE_PTR, FTM_PDD_CHANNEL_0,
 *      FTM_PDD_OUTPUT_NONE);
 *      @endcode
 */
#define FTM_PDD_SelectChannelMode(PeripheralBase, ChannelIdx, MSBA_val) ( \
    FTM_CnSC_REG(PeripheralBase,(ChannelIdx)) = \
     (uint32_t)(( \
      (uint32_t)(( \
       FTM_CnSC_REG(PeripheralBase,(ChannelIdx))) & (( \
       (uint32_t)(~(uint32_t)((uint32_t)0x3U << 4U))) & ( \
       (uint32_t)(~(uint32_t)FTM_CnSC_CHF_MASK))))) | ( \
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
 * @param ChannelIdx FTM channel index. Use constants from group "FTM channel
 *        constants". This parameter is 32 bits wide.
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: CnSC[ChannelIdx].
 * @par Example:
 *      @code
 *      uint32_t result =
 *      FTM_PDD_GetChannelInterruptMask(<peripheral>_BASE_PTR, FTM_PDD_CHANNEL_0);
 *      @endcode
 */
#define FTM_PDD_GetChannelInterruptMask(PeripheralBase, ChannelIdx) ( \
    (uint32_t)(FTM_CnSC_REG(PeripheralBase,(ChannelIdx)) & FTM_CnSC_CHIE_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- EnableChannelInterrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables the FTM channel interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param ChannelIdx FTM channel index. Use constants from group "FTM channel
 *        constants". This parameter is 32 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CnSC[ChannelIdx].
 * @par Example:
 *      @code
 *      FTM_PDD_EnableChannelInterrupt(<peripheral>_BASE_PTR,
 *      FTM_PDD_CHANNEL_0);
 *      @endcode
 */
#define FTM_PDD_EnableChannelInterrupt(PeripheralBase, ChannelIdx) ( \
    FTM_CnSC_REG(PeripheralBase,(ChannelIdx)) = \
     (uint32_t)(( \
      (uint32_t)(FTM_CnSC_REG(PeripheralBase,(ChannelIdx)) | FTM_CnSC_CHIE_MASK)) & ( \
      (uint32_t)(~(uint32_t)FTM_CnSC_CHF_MASK))) \
  )

/* ----------------------------------------------------------------------------
   -- DisableChannelInterrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Disables the FTM channel interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param ChannelIdx FTM channel index. Use constants from group "FTM channel
 *        constants". This parameter is 32 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CnSC[ChannelIdx].
 * @par Example:
 *      @code
 *      FTM_PDD_DisableChannelInterrupt(<peripheral>_BASE_PTR,
 *      FTM_PDD_CHANNEL_0);
 *      @endcode
 */
#define FTM_PDD_DisableChannelInterrupt(PeripheralBase, ChannelIdx) ( \
    FTM_CnSC_REG(PeripheralBase,(ChannelIdx)) &= \
     (uint32_t)(( \
      (uint32_t)(~(uint32_t)FTM_CnSC_CHIE_MASK)) & ( \
      (uint32_t)(~(uint32_t)FTM_CnSC_CHF_MASK))) \
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
 * @param ChannelIdx FTM channel index. Use constants from group "FTM channel
 *        constants". This parameter is 32 bits wide.
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: CnSC[ChannelIdx].
 * @par Example:
 *      @code
 *      uint32_t result =
 *      FTM_PDD_GetChannelInterruptFlag(<peripheral>_BASE_PTR, FTM_PDD_CHANNEL_0);
 *      @endcode
 */
#define FTM_PDD_GetChannelInterruptFlag(PeripheralBase, ChannelIdx) ( \
    (uint32_t)(FTM_CnSC_REG(PeripheralBase,(ChannelIdx)) & FTM_CnSC_CHF_MASK) \
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
 * @param ChannelIdx FTM channel index. Use constants from group "FTM channel
 *        constants". This parameter is 32 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CnSC[ChannelIdx].
 * @par Example:
 *      @code
 *      FTM_PDD_ClearChannelInterruptFlag(<peripheral>_BASE_PTR,
 *      FTM_PDD_CHANNEL_0);
 *      @endcode
 */
#define FTM_PDD_ClearChannelInterruptFlag(PeripheralBase, ChannelIdx) ( \
    FTM_CnSC_REG(PeripheralBase,(ChannelIdx)) &= \
     (uint32_t)(~(uint32_t)FTM_CnSC_CHF_MASK) \
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
 * @param ChannelIdx FTM channel index. Use constants from group "FTM channel
 *        constants". This parameter is 32 bits wide.
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: CnSC[ChannelIdx].
 * @par Example:
 *      @code
 *      uint32_t result = FTM_PDD_ReadChannelControlReg(<peripheral>_BASE_PTR,
 *      FTM_PDD_CHANNEL_0);
 *      @endcode
 */
#define FTM_PDD_ReadChannelControlReg(PeripheralBase, ChannelIdx) ( \
    FTM_CnSC_REG(PeripheralBase,(ChannelIdx)) \
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
 * @param ChannelIdx FTM channel index. Use constants from group "FTM channel
 *        constants". This parameter is 32 bits wide.
 * @param Value New content of the channel status and control register. This
 *        parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CnSC[ChannelIdx].
 * @par Example:
 *      @code
 *      FTM_PDD_WriteChannelControlReg(<peripheral>_BASE_PTR,
 *      FTM_PDD_CHANNEL_0, 1);
 *      @endcode
 */
#define FTM_PDD_WriteChannelControlReg(PeripheralBase, ChannelIdx, Value) ( \
    FTM_CnSC_REG(PeripheralBase,(ChannelIdx)) = \
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
 * @param ChannelIdx FTM channel index. Use constants from group "FTM channel
 *        constants". This parameter is 32 bits wide.
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: CnV[ChannelIdx].
 * @par Example:
 *      @code
 *      uint32_t result = FTM_PDD_ReadChannelValueReg(<peripheral>_BASE_PTR,
 *      FTM_PDD_CHANNEL_0);
 *      @endcode
 */
#define FTM_PDD_ReadChannelValueReg(PeripheralBase, ChannelIdx) ( \
    FTM_CnV_REG(PeripheralBase,(ChannelIdx)) \
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
 * @param ChannelIdx FTM channel index. Use constants from group "FTM channel
 *        constants". This parameter is 32 bits wide.
 * @param Value New content of the channel value register. This parameter is a
 *        32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CnV[ChannelIdx].
 * @par Example:
 *      @code
 *      FTM_PDD_WriteChannelValueReg(<peripheral>_BASE_PTR, FTM_PDD_CHANNEL_0,
 *      1);
 *      @endcode
 */
#define FTM_PDD_WriteChannelValueReg(PeripheralBase, ChannelIdx, Value) ( \
    FTM_CnV_REG(PeripheralBase,(ChannelIdx)) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- WriteInitialValueReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes value to the counter initial value register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value New content of the counter initial value register. This
 *        parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTM0_CNTIN, FTM1_CNTIN,
 *          FTM2_CNTIN, FTM3_CNTIN (depending on the peripheral).
 * @par Example:
 *      @code
 *      FTM_PDD_WriteInitialValueReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define FTM_PDD_WriteInitialValueReg(PeripheralBase, Value) ( \
    FTM_CNTIN_REG(PeripheralBase) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadInitialValueReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the counter initial value register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: FTM0_CNTIN, FTM1_CNTIN,
 *          FTM2_CNTIN, FTM3_CNTIN (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result = FTM_PDD_ReadInitialValueReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTM_PDD_ReadInitialValueReg(PeripheralBase) ( \
    FTM_CNTIN_REG(PeripheralBase) \
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
 * @remarks The macro accesses the following registers: FTM0_STATUS,
 *          FTM1_STATUS, FTM2_STATUS, FTM3_STATUS (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result = FTM_PDD_GetChannelFlags(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTM_PDD_GetChannelFlags(PeripheralBase) ( \
    FTM_STATUS_REG(PeripheralBase) \
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
 * @param Mask Interrupt flag mask. Use constants from group "Interrupt flag
 *        masks for ClearChannelFlag". This parameter is 8 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTM0_STATUS,
 *          FTM1_STATUS, FTM2_STATUS, FTM3_STATUS (depending on the peripheral).
 * @par Example:
 *      @code
 *      FTM_PDD_ClearChannelFlags(<peripheral>_BASE_PTR, FTM_PDD_FLAG_0);
 *      @endcode
 */
#define FTM_PDD_ClearChannelFlags(PeripheralBase, Mask) ( \
    FTM_STATUS_REG(PeripheralBase) = \
     (uint32_t)((uint32_t)(~(uint32_t)(Mask)) & (uint32_t)0xFFU) \
  )

/* ----------------------------------------------------------------------------
   -- EnableFaultInterrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables the FTM fault interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTM0_MODE, FTM1_MODE,
 *          FTM2_MODE, FTM3_MODE (depending on the peripheral).
 * @par Example:
 *      @code
 *      FTM_PDD_EnableFaultInterrupt(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTM_PDD_EnableFaultInterrupt(PeripheralBase) ( \
    FTM_MODE_REG(PeripheralBase) |= \
     FTM_MODE_FAULTIE_MASK \
  )

/* ----------------------------------------------------------------------------
   -- DisableFaultInterrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Disables the FTM fault interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTM0_MODE, FTM1_MODE,
 *          FTM2_MODE, FTM3_MODE (depending on the peripheral).
 * @par Example:
 *      @code
 *      FTM_PDD_DisableFaultInterrupt(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTM_PDD_DisableFaultInterrupt(PeripheralBase) ( \
    FTM_MODE_REG(PeripheralBase) &= \
     (uint32_t)(~(uint32_t)FTM_MODE_FAULTIE_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- WriteProtectionDisable
   ---------------------------------------------------------------------------- */

/**
 * @brief Disables the write protection.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTM0_MODE, FTM1_MODE,
 *          FTM2_MODE, FTM3_MODE (depending on the peripheral).
 * @par Example:
 *      @code
 *      FTM_PDD_WriteProtectionDisable(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTM_PDD_WriteProtectionDisable(PeripheralBase) ( \
    FTM_MODE_REG(PeripheralBase) |= \
     FTM_MODE_WPDIS_MASK \
  )

/* ----------------------------------------------------------------------------
   -- InitializeOutputs
   ---------------------------------------------------------------------------- */

/**
 * @brief Initialize the channel outputs.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTM0_MODE, FTM1_MODE,
 *          FTM2_MODE, FTM3_MODE (depending on the peripheral).
 * @par Example:
 *      @code
 *      FTM_PDD_InitializeOutputs(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTM_PDD_InitializeOutputs(PeripheralBase) ( \
    FTM_MODE_REG(PeripheralBase) |= \
     FTM_MODE_INIT_MASK \
  )

/* ----------------------------------------------------------------------------
   -- WriteFeaturesModeReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes value to the feature mode selection register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value New content of the feature mode selection register. This
 *        parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTM0_MODE, FTM1_MODE,
 *          FTM2_MODE, FTM3_MODE (depending on the peripheral).
 * @par Example:
 *      @code
 *      FTM_PDD_WriteFeaturesModeReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define FTM_PDD_WriteFeaturesModeReg(PeripheralBase, Value) ( \
    FTM_MODE_REG(PeripheralBase) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadFeaturesModeReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the features mode selection register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: FTM0_MODE, FTM1_MODE,
 *          FTM2_MODE, FTM3_MODE (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result = FTM_PDD_ReadFeaturesModeReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTM_PDD_ReadFeaturesModeReg(PeripheralBase) ( \
    FTM_MODE_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteSynchronizationReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes value to the synchronization register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value New content of the synchronization register. This parameter is a
 *        32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTM0_SYNC, FTM1_SYNC,
 *          FTM2_SYNC, FTM3_SYNC (depending on the peripheral).
 * @par Example:
 *      @code
 *      FTM_PDD_WriteSynchronizationReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define FTM_PDD_WriteSynchronizationReg(PeripheralBase, Value) ( \
    FTM_SYNC_REG(PeripheralBase) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadSynchronizationReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the synchronization register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: FTM0_SYNC, FTM1_SYNC,
 *          FTM2_SYNC, FTM3_SYNC (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result = FTM_PDD_ReadSynchronizationReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTM_PDD_ReadSynchronizationReg(PeripheralBase) ( \
    FTM_SYNC_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteInitialOutputReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes value to the initial state for channels output register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value New content of the initial state for channel output register.
 *        This parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTM0_OUTINIT,
 *          FTM1_OUTINIT, FTM2_OUTINIT, FTM3_OUTINIT (depending on the peripheral).
 * @par Example:
 *      @code
 *      FTM_PDD_WriteInitialOutputReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define FTM_PDD_WriteInitialOutputReg(PeripheralBase, Value) ( \
    FTM_OUTINIT_REG(PeripheralBase) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadInitialOutputReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the initial state for channels output register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: FTM0_OUTINIT,
 *          FTM1_OUTINIT, FTM2_OUTINIT, FTM3_OUTINIT (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result = FTM_PDD_ReadInitialOutputReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTM_PDD_ReadInitialOutputReg(PeripheralBase) ( \
    FTM_OUTINIT_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteOutputMaskReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes value to the output mask register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value New content of the output mask register. This parameter is a
 *        32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTM0_OUTMASK,
 *          FTM1_OUTMASK, FTM2_OUTMASK, FTM3_OUTMASK (depending on the peripheral).
 * @par Example:
 *      @code
 *      FTM_PDD_WriteOutputMaskReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define FTM_PDD_WriteOutputMaskReg(PeripheralBase, Value) ( \
    FTM_OUTMASK_REG(PeripheralBase) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadOutputMaskReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the output mask register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: FTM0_OUTMASK,
 *          FTM1_OUTMASK, FTM2_OUTMASK, FTM3_OUTMASK (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result = FTM_PDD_ReadOutputMaskReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTM_PDD_ReadOutputMaskReg(PeripheralBase) ( \
    FTM_OUTMASK_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteCombineReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes value to the function for linked channels register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value New content of the function for linked channels register. This
 *        parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTM0_COMBINE,
 *          FTM1_COMBINE, FTM2_COMBINE, FTM3_COMBINE (depending on the peripheral).
 * @par Example:
 *      @code
 *      FTM_PDD_WriteCombineReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define FTM_PDD_WriteCombineReg(PeripheralBase, Value) ( \
    FTM_COMBINE_REG(PeripheralBase) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadCombineReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the function for linked channels register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: FTM0_COMBINE,
 *          FTM1_COMBINE, FTM2_COMBINE, FTM3_COMBINE (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result = FTM_PDD_ReadCombineReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTM_PDD_ReadCombineReg(PeripheralBase) ( \
    FTM_COMBINE_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteDeadtimeReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes value to the deadtime insertion control register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value New content of the deadtime insertion control register. This
 *        parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTM0_DEADTIME,
 *          FTM1_DEADTIME, FTM2_DEADTIME, FTM3_DEADTIME (depending on the peripheral).
 * @par Example:
 *      @code
 *      FTM_PDD_WriteDeadtimeReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define FTM_PDD_WriteDeadtimeReg(PeripheralBase, Value) ( \
    FTM_DEADTIME_REG(PeripheralBase) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadDeadtimeReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the deadtime insertion control register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: FTM0_DEADTIME,
 *          FTM1_DEADTIME, FTM2_DEADTIME, FTM3_DEADTIME (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result = FTM_PDD_ReadDeadtimeReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTM_PDD_ReadDeadtimeReg(PeripheralBase) ( \
    FTM_DEADTIME_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteExternalTriggerReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes value to the FTM external trigger register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value New content of the FTM external trigger register. This parameter
 *        is a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTM0_EXTTRIG,
 *          FTM1_EXTTRIG, FTM2_EXTTRIG, FTM3_EXTTRIG (depending on the peripheral).
 * @par Example:
 *      @code
 *      FTM_PDD_WriteExternalTriggerReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define FTM_PDD_WriteExternalTriggerReg(PeripheralBase, Value) ( \
    FTM_EXTTRIG_REG(PeripheralBase) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadExternalTriggerReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the FTM external trigger register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: FTM0_EXTTRIG,
 *          FTM1_EXTTRIG, FTM2_EXTTRIG, FTM3_EXTTRIG (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result = FTM_PDD_ReadExternalTriggerReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTM_PDD_ReadExternalTriggerReg(PeripheralBase) ( \
    FTM_EXTTRIG_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WritePolarityReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes value to the channels polarity register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value New content of the channels polarity register. This parameter is
 *        a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTM0_POL, FTM1_POL,
 *          FTM2_POL, FTM3_POL (depending on the peripheral).
 * @par Example:
 *      @code
 *      FTM_PDD_WritePolarityReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define FTM_PDD_WritePolarityReg(PeripheralBase, Value) ( \
    FTM_POL_REG(PeripheralBase) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadPolarityReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the channels polarity register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: FTM0_POL, FTM1_POL,
 *          FTM2_POL, FTM3_POL (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result = FTM_PDD_ReadPolarityReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTM_PDD_ReadPolarityReg(PeripheralBase) ( \
    FTM_POL_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- ReadFaultStatusReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the fault mode status register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: FTM0_FMS, FTM1_FMS,
 *          FTM2_FMS, FTM3_FMS (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result = FTM_PDD_ReadFaultStatusReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTM_PDD_ReadFaultStatusReg(PeripheralBase) ( \
    FTM_FMS_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteProtectionEnable
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables the write protection.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTM0_FMS, FTM1_FMS,
 *          FTM2_FMS, FTM3_FMS (depending on the peripheral).
 * @par Example:
 *      @code
 *      FTM_PDD_WriteProtectionEnable(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTM_PDD_WriteProtectionEnable(PeripheralBase) ( \
    FTM_FMS_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(FTM_FMS_REG(PeripheralBase) | FTM_FMS_WPEN_MASK)) & (( \
      (uint32_t)(~(uint32_t)FTM_FMS_FAULTF0_MASK)) & (( \
      (uint32_t)(~(uint32_t)FTM_FMS_FAULTF1_MASK)) & (( \
      (uint32_t)(~(uint32_t)FTM_FMS_FAULTF2_MASK)) & (( \
      (uint32_t)(~(uint32_t)FTM_FMS_FAULTF3_MASK)) & ( \
      (uint32_t)(~(uint32_t)FTM_FMS_FAULTF_MASK))))))) \
  )

/* ----------------------------------------------------------------------------
   -- WriteInputCaptureFilterReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes value to the input capture filter control register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value New content of the input capture filter control register. This
 *        parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTM0_FILTER,
 *          FTM1_FILTER, FTM2_FILTER, FTM3_FILTER (depending on the peripheral).
 * @par Example:
 *      @code
 *      FTM_PDD_WriteInputCaptureFilterReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define FTM_PDD_WriteInputCaptureFilterReg(PeripheralBase, Value) ( \
    FTM_FILTER_REG(PeripheralBase) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadInputCaptureFilterReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the input capture filter control register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: FTM0_FILTER,
 *          FTM1_FILTER, FTM2_FILTER, FTM3_FILTER (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result =
 *      FTM_PDD_ReadInputCaptureFilterReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTM_PDD_ReadInputCaptureFilterReg(PeripheralBase) ( \
    FTM_FILTER_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteFaultControlReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes value to the fault control register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value New content of the fault control register. This parameter is a
 *        32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTM0_FLTCTRL,
 *          FTM1_FLTCTRL, FTM2_FLTCTRL, FTM3_FLTCTRL (depending on the peripheral).
 * @par Example:
 *      @code
 *      FTM_PDD_WriteFaultControlReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define FTM_PDD_WriteFaultControlReg(PeripheralBase, Value) ( \
    FTM_FLTCTRL_REG(PeripheralBase) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadFaultControlReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the fault control register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: FTM0_FLTCTRL,
 *          FTM1_FLTCTRL, FTM2_FLTCTRL, FTM3_FLTCTRL (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result = FTM_PDD_ReadFaultControlReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTM_PDD_ReadFaultControlReg(PeripheralBase) ( \
    FTM_FLTCTRL_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteQuadratureDecoderReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes value to the quadrature decoder control and status register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value New content of the quadrature decoder control and status
 *        register. This parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTM0_QDCTRL,
 *          FTM1_QDCTRL, FTM2_QDCTRL, FTM3_QDCTRL (depending on the peripheral).
 * @par Example:
 *      @code
 *      FTM_PDD_WriteQuadratureDecoderReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define FTM_PDD_WriteQuadratureDecoderReg(PeripheralBase, Value) ( \
    FTM_QDCTRL_REG(PeripheralBase) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadQuadratureDecoderReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the quadrature decoder control and status
 * register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: FTM0_QDCTRL,
 *          FTM1_QDCTRL, FTM2_QDCTRL, FTM3_QDCTRL (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result =
 *      FTM_PDD_ReadQuadratureDecoderReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTM_PDD_ReadQuadratureDecoderReg(PeripheralBase) ( \
    FTM_QDCTRL_REG(PeripheralBase) \
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
 * @remarks The macro accesses the following registers: FTM0_CONF, FTM1_CONF,
 *          FTM2_CONF, FTM3_CONF (depending on the peripheral).
 * @par Example:
 *      @code
 *      FTM_PDD_WriteConfigurationReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define FTM_PDD_WriteConfigurationReg(PeripheralBase, Value) ( \
    FTM_CONF_REG(PeripheralBase) = \
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
 * @remarks The macro accesses the following registers: FTM0_CONF, FTM1_CONF,
 *          FTM2_CONF, FTM3_CONF (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result = FTM_PDD_ReadConfigurationReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTM_PDD_ReadConfigurationReg(PeripheralBase) ( \
    FTM_CONF_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteFaultInputPolarityReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes value to the FTM fault input polarity register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value New content of the FTM fault input polarity register. This
 *        parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTM0_FLTPOL,
 *          FTM1_FLTPOL, FTM2_FLTPOL, FTM3_FLTPOL (depending on the peripheral).
 * @par Example:
 *      @code
 *      FTM_PDD_WriteFaultInputPolarityReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define FTM_PDD_WriteFaultInputPolarityReg(PeripheralBase, Value) ( \
    FTM_FLTPOL_REG(PeripheralBase) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadFaultInputPolarityReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the FTM fault input polarity register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: FTM0_FLTPOL,
 *          FTM1_FLTPOL, FTM2_FLTPOL, FTM3_FLTPOL (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result =
 *      FTM_PDD_ReadFaultInputPolarityReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTM_PDD_ReadFaultInputPolarityReg(PeripheralBase) ( \
    FTM_FLTPOL_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteSynchronizationConfigReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes value to the synchronization configuration register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value New content of the synchronization configuration register. This
 *        parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTM0_SYNCONF,
 *          FTM1_SYNCONF, FTM2_SYNCONF, FTM3_SYNCONF (depending on the peripheral).
 * @par Example:
 *      @code
 *      FTM_PDD_WriteSynchronizationConfigReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define FTM_PDD_WriteSynchronizationConfigReg(PeripheralBase, Value) ( \
    FTM_SYNCONF_REG(PeripheralBase) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadSynchronizationConfigReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the synchronization configuration register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: FTM0_SYNCONF,
 *          FTM1_SYNCONF, FTM2_SYNCONF, FTM3_SYNCONF (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result =
 *      FTM_PDD_ReadSynchronizationConfigReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTM_PDD_ReadSynchronizationConfigReg(PeripheralBase) ( \
    FTM_SYNCONF_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteInvertingReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes value to the FTM inverting control register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value New content of the FTM inverting control register. This
 *        parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTM0_INVCTRL,
 *          FTM1_INVCTRL, FTM2_INVCTRL, FTM3_INVCTRL (depending on the peripheral).
 * @par Example:
 *      @code
 *      FTM_PDD_WriteInvertingReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define FTM_PDD_WriteInvertingReg(PeripheralBase, Value) ( \
    FTM_INVCTRL_REG(PeripheralBase) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadInvertingReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the FTM inverting control register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: FTM0_INVCTRL,
 *          FTM1_INVCTRL, FTM2_INVCTRL, FTM3_INVCTRL (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result = FTM_PDD_ReadInvertingReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTM_PDD_ReadInvertingReg(PeripheralBase) ( \
    FTM_INVCTRL_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteSoftwareOutputReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes value to the FTM software output control register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value New content of the FTM software output control register. This
 *        parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTM0_SWOCTRL,
 *          FTM1_SWOCTRL, FTM2_SWOCTRL, FTM3_SWOCTRL (depending on the peripheral).
 * @par Example:
 *      @code
 *      FTM_PDD_WriteSoftwareOutputReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define FTM_PDD_WriteSoftwareOutputReg(PeripheralBase, Value) ( \
    FTM_SWOCTRL_REG(PeripheralBase) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadSoftwareOutputReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the FTM software output control register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: FTM0_SWOCTRL,
 *          FTM1_SWOCTRL, FTM2_SWOCTRL, FTM3_SWOCTRL (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result = FTM_PDD_ReadSoftwareOutputReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTM_PDD_ReadSoftwareOutputReg(PeripheralBase) ( \
    FTM_SWOCTRL_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WritePwmLoadReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes value to the FTM PWM load register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value New content of the FTM PWM load register. This parameter is a
 *        32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTM0_PWMLOAD,
 *          FTM1_PWMLOAD, FTM2_PWMLOAD, FTM3_PWMLOAD (depending on the peripheral).
 * @par Example:
 *      @code
 *      FTM_PDD_WritePwmLoadReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define FTM_PDD_WritePwmLoadReg(PeripheralBase, Value) ( \
    FTM_PWMLOAD_REG(PeripheralBase) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadPwmLoadReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the FTM PWM load register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: FTM0_PWMLOAD,
 *          FTM1_PWMLOAD, FTM2_PWMLOAD, FTM3_PWMLOAD (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result = FTM_PDD_ReadPwmLoadReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTM_PDD_ReadPwmLoadReg(PeripheralBase) ( \
    FTM_PWMLOAD_REG(PeripheralBase) \
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
 * @remarks The macro accesses the following registers: FTM0_SC, FTM1_SC,
 *          FTM2_SC, FTM3_SC (depending on the peripheral).
 * @par Example:
 *      @code
 *      FTM_PDD_WriteStatusControlReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define FTM_PDD_WriteStatusControlReg(PeripheralBase, Value) ( \
    FTM_SC_REG(PeripheralBase) = \
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
 * @remarks The macro accesses the following registers: FTM0_SC, FTM1_SC,
 *          FTM2_SC, FTM3_SC (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result = FTM_PDD_ReadStatusControlReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTM_PDD_ReadStatusControlReg(PeripheralBase) ( \
    FTM_SC_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- SetCounterResetByCapture
   ---------------------------------------------------------------------------- */

/**
 * @brief Counter reset is driven by the selected event of the channel (n) in
 * the Input Capture mode.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param ChannelIdx FTM channel index. Use constants from group "FTM channel
 *        constants". This parameter is 32 bits wide.
 * @param State Requested state of FTM counter reset when the selected channel
 *        (n) input event is detected. This parameter is of "Global enumeration
 *        used for specifying general enable/disable states (PDD_DISABLE and
 *        PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CnSC[ChannelIdx].
 * @par Example:
 *      @code
 *      FTM_PDD_SetCounterResetByCapture(<peripheral>_BASE_PTR,
 *      FTM_PDD_CHANNEL_0, PDD_DISABLE);
 *      @endcode
 */
#define FTM_PDD_SetCounterResetByCapture(PeripheralBase, ChannelIdx, State) ( \
    FTM_CnSC_REG(PeripheralBase,(ChannelIdx)) = \
     (uint32_t)(( \
      (uint32_t)(( \
       FTM_CnSC_REG(PeripheralBase,(ChannelIdx))) & (( \
       (uint32_t)(~(uint32_t)FTM_CnSC_ICRST_MASK)) & ( \
       (uint32_t)(~(uint32_t)FTM_CnSC_CHF_MASK))))) | ( \
      (uint32_t)((uint32_t)(State) << FTM_CnSC_ICRST_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SelectFaultControlMode
   ---------------------------------------------------------------------------- */

/**
 * @brief Select the FTM fault control mode.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mode New value of the fault control mode. This parameter is of "Fault
 *        mode constants." type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTM0_MODE, FTM1_MODE,
 *          FTM2_MODE, FTM3_MODE (depending on the peripheral).
 * @par Example:
 *      @code
 *      FTM_PDD_SelectFaultControlMode(<peripheral>_BASE_PTR,
 *      FTM_PDD_FAULT_DISABLED);
 *      @endcode
 */
#define FTM_PDD_SelectFaultControlMode(PeripheralBase, Mode) ( \
    FTM_MODE_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(FTM_MODE_REG(PeripheralBase) & (uint32_t)(~(uint32_t)FTM_MODE_FAULTM_MASK))) | ( \
      (uint32_t)(Mode))) \
  )

/* ----------------------------------------------------------------------------
   -- SetCaptureTestMode
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables the capture test mode.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of the capture test mode. This parameter is of
 *        "Global enumeration used for specifying general enable/disable states
 *        (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTM0_MODE, FTM1_MODE,
 *          FTM2_MODE, FTM3_MODE (depending on the peripheral).
 * @par Example:
 *      @code
 *      FTM_PDD_SetCaptureTestMode(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define FTM_PDD_SetCaptureTestMode(PeripheralBase, State) ( \
    FTM_MODE_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(FTM_MODE_REG(PeripheralBase) & (uint32_t)(~(uint32_t)FTM_MODE_CAPTEST_MASK))) | ( \
      (uint32_t)((uint32_t)(State) << FTM_MODE_CAPTEST_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SelectPWMSynchronizationMode
   ---------------------------------------------------------------------------- */

/**
 * @brief Selects which triggers can be used by MOD, CnV, OUTMASK, and FTM
 * counter synchronization.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mode New value of the PWM synchronization mode. This parameter is of
 *        "PWM synchronization mode constants." type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTM0_MODE, FTM1_MODE,
 *          FTM2_MODE, FTM3_MODE (depending on the peripheral).
 * @par Example:
 *      @code
 *      FTM_PDD_SelectPWMSynchronizationMode(<peripheral>_BASE_PTR,
 *      FTM_PDD_NO_RESTRICTIONS);
 *      @endcode
 */
#define FTM_PDD_SelectPWMSynchronizationMode(PeripheralBase, Mode) ( \
    FTM_MODE_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(FTM_MODE_REG(PeripheralBase) & (uint32_t)(~(uint32_t)FTM_MODE_PWMSYNC_MASK))) | ( \
      (uint32_t)(Mode))) \
  )

/* ----------------------------------------------------------------------------
   -- SetFTMEnable
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables all registers including the FTM-specific registers (second set
 * of registers) are available for use with no restrictions.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of the FTM enable. This parameter is of "Global
 *        enumeration used for specifying general enable/disable states
 *        (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTM0_MODE, FTM1_MODE,
 *          FTM2_MODE, FTM3_MODE (depending on the peripheral).
 * @par Example:
 *      @code
 *      FTM_PDD_SetFTMEnable(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define FTM_PDD_SetFTMEnable(PeripheralBase, State) ( \
    FTM_MODE_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(FTM_MODE_REG(PeripheralBase) & (uint32_t)(~(uint32_t)FTM_MODE_FTMEN_MASK))) | ( \
      (uint32_t)(State))) \
  )

/* ----------------------------------------------------------------------------
   -- PWMSoftwareTrigger
   ---------------------------------------------------------------------------- */

/**
 * @brief Selects the software trigger as the PWM synchronization trigger.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTM0_SYNC, FTM1_SYNC,
 *          FTM2_SYNC, FTM3_SYNC (depending on the peripheral).
 * @par Example:
 *      @code
 *      FTM_PDD_PWMSoftwareTrigger(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTM_PDD_PWMSoftwareTrigger(PeripheralBase) ( \
    FTM_SYNC_REG(PeripheralBase) |= \
     FTM_SYNC_SWSYNC_MASK \
  )

/* ----------------------------------------------------------------------------
   -- SetPWMHardwareTrigger2
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables hardware trigger 2 to the PWM synchronization.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of the PWM synchronization hardware trigger 2.
 *        This parameter is of "Global enumeration used for specifying general
 *        enable/disable states (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)"
 *        type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTM0_SYNC, FTM1_SYNC,
 *          FTM2_SYNC, FTM3_SYNC (depending on the peripheral).
 * @par Example:
 *      @code
 *      FTM_PDD_SetPWMHardwareTrigger2(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define FTM_PDD_SetPWMHardwareTrigger2(PeripheralBase, State) ( \
    FTM_SYNC_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(FTM_SYNC_REG(PeripheralBase) & (uint32_t)(~(uint32_t)FTM_SYNC_TRIG2_MASK))) | ( \
      (uint32_t)((uint32_t)(State) << FTM_SYNC_TRIG2_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SetPWMHardwareTrigger1
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables hardware trigger 1 to the PWM synchronization.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of the PWM synchronization hardware trigger 1.
 *        This parameter is of "Global enumeration used for specifying general
 *        enable/disable states (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)"
 *        type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTM0_SYNC, FTM1_SYNC,
 *          FTM2_SYNC, FTM3_SYNC (depending on the peripheral).
 * @par Example:
 *      @code
 *      FTM_PDD_SetPWMHardwareTrigger1(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define FTM_PDD_SetPWMHardwareTrigger1(PeripheralBase, State) ( \
    FTM_SYNC_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(FTM_SYNC_REG(PeripheralBase) & (uint32_t)(~(uint32_t)FTM_SYNC_TRIG1_MASK))) | ( \
      (uint32_t)((uint32_t)(State) << FTM_SYNC_TRIG1_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SetPWMHardwareTrigger0
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables hardware trigger 0 to the PWM synchronization.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of the PWM synchronization hardware trigger 0.
 *        This parameter is of "Global enumeration used for specifying general
 *        enable/disable states (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)"
 *        type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTM0_SYNC, FTM1_SYNC,
 *          FTM2_SYNC, FTM3_SYNC (depending on the peripheral).
 * @par Example:
 *      @code
 *      FTM_PDD_SetPWMHardwareTrigger0(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define FTM_PDD_SetPWMHardwareTrigger0(PeripheralBase, State) ( \
    FTM_SYNC_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(FTM_SYNC_REG(PeripheralBase) & (uint32_t)(~(uint32_t)FTM_SYNC_TRIG0_MASK))) | ( \
      (uint32_t)((uint32_t)(State) << FTM_SYNC_TRIG0_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SelectOutputMaskSynchronization
   ---------------------------------------------------------------------------- */

/**
 * @brief Selects when the OUTMASK register is updated with the value of its
 * buffer.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mode New value of the output mask synchronization. This parameter is
 *        of "Output mask synchronization constants." type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTM0_SYNC, FTM1_SYNC,
 *          FTM2_SYNC, FTM3_SYNC (depending on the peripheral).
 * @par Example:
 *      @code
 *      FTM_PDD_SelectOutputMaskSynchronization(<peripheral>_BASE_PTR,
 *      FTM_PDD_RISING_EDGES);
 *      @endcode
 */
#define FTM_PDD_SelectOutputMaskSynchronization(PeripheralBase, Mode) ( \
    FTM_SYNC_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(FTM_SYNC_REG(PeripheralBase) & (uint32_t)(~(uint32_t)FTM_SYNC_SYNCHOM_MASK))) | ( \
      (uint32_t)(Mode))) \
  )

/* ----------------------------------------------------------------------------
   -- SelectFTMCounterSynchronization
   ---------------------------------------------------------------------------- */

/**
 * @brief Determines if the FTM counter is reinitialized when the selected
 * trigger for the synchronization is detected.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mode New value of the FTM counter synchronization. This parameter is
 *        of "FTM counter synchronization constants." type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTM0_SYNC, FTM1_SYNC,
 *          FTM2_SYNC, FTM3_SYNC (depending on the peripheral).
 * @par Example:
 *      @code
 *      FTM_PDD_SelectFTMCounterSynchronization(<peripheral>_BASE_PTR,
 *      FTM_PDD_COUNT_NORMALLY);
 *      @endcode
 */
#define FTM_PDD_SelectFTMCounterSynchronization(PeripheralBase, Mode) ( \
    FTM_SYNC_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(FTM_SYNC_REG(PeripheralBase) & (uint32_t)(~(uint32_t)FTM_SYNC_REINIT_MASK))) | ( \
      (uint32_t)(Mode))) \
  )

/* ----------------------------------------------------------------------------
   -- SetMaximumLoadingPoint
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables the maximum loading point to PWM synchronization.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of the maximum loading point to PWM
 *        synchronization. This parameter is of "Global enumeration used for specifying
 *        general enable/disable states (PDD_DISABLE and PDD_ENABLE defined in
 *        PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTM0_SYNC, FTM1_SYNC,
 *          FTM2_SYNC, FTM3_SYNC (depending on the peripheral).
 * @par Example:
 *      @code
 *      FTM_PDD_SetMaximumLoadingPoint(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define FTM_PDD_SetMaximumLoadingPoint(PeripheralBase, State) ( \
    FTM_SYNC_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(FTM_SYNC_REG(PeripheralBase) & (uint32_t)(~(uint32_t)FTM_SYNC_CNTMAX_MASK))) | ( \
      (uint32_t)((uint32_t)(State) << FTM_SYNC_CNTMAX_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SetMinimumLoadingPoint
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables the minimum loading point to PWM synchronization.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of the maximum loading point to PWM
 *        synchronization. This parameter is of "Global enumeration used for specifying
 *        general enable/disable states (PDD_DISABLE and PDD_ENABLE defined in
 *        PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTM0_SYNC, FTM1_SYNC,
 *          FTM2_SYNC, FTM3_SYNC (depending on the peripheral).
 * @par Example:
 *      @code
 *      FTM_PDD_SetMinimumLoadingPoint(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define FTM_PDD_SetMinimumLoadingPoint(PeripheralBase, State) ( \
    FTM_SYNC_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(FTM_SYNC_REG(PeripheralBase) & (uint32_t)(~(uint32_t)FTM_SYNC_CNTMIN_MASK))) | ( \
      (uint32_t)(State))) \
  )

/* ----------------------------------------------------------------------------
   -- SetFaultControl67
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables the fault control in channels 6 and 7.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of the fault control. This parameter is of
 *        "Global enumeration used for specifying general enable/disable states
 *        (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTM0_COMBINE,
 *          FTM1_COMBINE, FTM2_COMBINE, FTM3_COMBINE (depending on the peripheral).
 * @par Example:
 *      @code
 *      FTM_PDD_SetFaultControl67(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define FTM_PDD_SetFaultControl67(PeripheralBase, State) ( \
    FTM_COMBINE_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       FTM_COMBINE_REG(PeripheralBase)) & ( \
       (uint32_t)(~(uint32_t)FTM_COMBINE_FAULTEN3_MASK)))) | ( \
      (uint32_t)((uint32_t)(State) << FTM_COMBINE_FAULTEN3_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SetFaultControl45
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables the fault control in channels 4 and 5.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of the fault control. This parameter is of
 *        "Global enumeration used for specifying general enable/disable states
 *        (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTM0_COMBINE,
 *          FTM1_COMBINE, FTM2_COMBINE, FTM3_COMBINE (depending on the peripheral).
 * @par Example:
 *      @code
 *      FTM_PDD_SetFaultControl45(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define FTM_PDD_SetFaultControl45(PeripheralBase, State) ( \
    FTM_COMBINE_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       FTM_COMBINE_REG(PeripheralBase)) & ( \
       (uint32_t)(~(uint32_t)FTM_COMBINE_FAULTEN2_MASK)))) | ( \
      (uint32_t)((uint32_t)(State) << FTM_COMBINE_FAULTEN2_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SetFaultControl23
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables the fault control in channels 2 and 3.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of the fault control. This parameter is of
 *        "Global enumeration used for specifying general enable/disable states
 *        (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTM0_COMBINE,
 *          FTM1_COMBINE, FTM2_COMBINE, FTM3_COMBINE (depending on the peripheral).
 * @par Example:
 *      @code
 *      FTM_PDD_SetFaultControl23(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define FTM_PDD_SetFaultControl23(PeripheralBase, State) ( \
    FTM_COMBINE_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       FTM_COMBINE_REG(PeripheralBase)) & ( \
       (uint32_t)(~(uint32_t)FTM_COMBINE_FAULTEN1_MASK)))) | ( \
      (uint32_t)((uint32_t)(State) << FTM_COMBINE_FAULTEN1_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SetFaultControl01
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables the fault control in channels 0 and 1.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of the fault control. This parameter is of
 *        "Global enumeration used for specifying general enable/disable states
 *        (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTM0_COMBINE,
 *          FTM1_COMBINE, FTM2_COMBINE, FTM3_COMBINE (depending on the peripheral).
 * @par Example:
 *      @code
 *      FTM_PDD_SetFaultControl01(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define FTM_PDD_SetFaultControl01(PeripheralBase, State) ( \
    FTM_COMBINE_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       FTM_COMBINE_REG(PeripheralBase)) & ( \
       (uint32_t)(~(uint32_t)FTM_COMBINE_FAULTEN0_MASK)))) | ( \
      (uint32_t)((uint32_t)(State) << FTM_COMBINE_FAULTEN0_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SetSynchronization67
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables PWM synchronization of registers C6V and C7V.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of the synchronization. This parameter is of
 *        "Global enumeration used for specifying general enable/disable states
 *        (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTM0_COMBINE,
 *          FTM1_COMBINE, FTM2_COMBINE, FTM3_COMBINE (depending on the peripheral).
 * @par Example:
 *      @code
 *      FTM_PDD_SetSynchronization67(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define FTM_PDD_SetSynchronization67(PeripheralBase, State) ( \
    FTM_COMBINE_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       FTM_COMBINE_REG(PeripheralBase)) & ( \
       (uint32_t)(~(uint32_t)FTM_COMBINE_SYNCEN3_MASK)))) | ( \
      (uint32_t)((uint32_t)(State) << FTM_COMBINE_SYNCEN3_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SetSynchronization45
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables PWM synchronization of registers C4V and C5V.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of the synchronization. This parameter is of
 *        "Global enumeration used for specifying general enable/disable states
 *        (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTM0_COMBINE,
 *          FTM1_COMBINE, FTM2_COMBINE, FTM3_COMBINE (depending on the peripheral).
 * @par Example:
 *      @code
 *      FTM_PDD_SetSynchronization45(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define FTM_PDD_SetSynchronization45(PeripheralBase, State) ( \
    FTM_COMBINE_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       FTM_COMBINE_REG(PeripheralBase)) & ( \
       (uint32_t)(~(uint32_t)FTM_COMBINE_SYNCEN2_MASK)))) | ( \
      (uint32_t)((uint32_t)(State) << FTM_COMBINE_SYNCEN2_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SetSynchronization23
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables PWM synchronization of registers C2V and C3V.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of the synchronization. This parameter is of
 *        "Global enumeration used for specifying general enable/disable states
 *        (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTM0_COMBINE,
 *          FTM1_COMBINE, FTM2_COMBINE, FTM3_COMBINE (depending on the peripheral).
 * @par Example:
 *      @code
 *      FTM_PDD_SetSynchronization23(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define FTM_PDD_SetSynchronization23(PeripheralBase, State) ( \
    FTM_COMBINE_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       FTM_COMBINE_REG(PeripheralBase)) & ( \
       (uint32_t)(~(uint32_t)FTM_COMBINE_SYNCEN1_MASK)))) | ( \
      (uint32_t)((uint32_t)(State) << FTM_COMBINE_SYNCEN1_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SetSynchronization01
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables PWM synchronization of registers C0V and C1V.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of the synchronization. This parameter is of
 *        "Global enumeration used for specifying general enable/disable states
 *        (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTM0_COMBINE,
 *          FTM1_COMBINE, FTM2_COMBINE, FTM3_COMBINE (depending on the peripheral).
 * @par Example:
 *      @code
 *      FTM_PDD_SetSynchronization01(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define FTM_PDD_SetSynchronization01(PeripheralBase, State) ( \
    FTM_COMBINE_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       FTM_COMBINE_REG(PeripheralBase)) & ( \
       (uint32_t)(~(uint32_t)FTM_COMBINE_SYNCEN0_MASK)))) | ( \
      (uint32_t)((uint32_t)(State) << FTM_COMBINE_SYNCEN0_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SetDeadTime67
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables the deadtime insertion in the channels 6 and 7.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of the deadtime insertion. This parameter is of
 *        "Global enumeration used for specifying general enable/disable states
 *        (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTM0_COMBINE,
 *          FTM1_COMBINE, FTM2_COMBINE, FTM3_COMBINE (depending on the peripheral).
 * @par Example:
 *      @code
 *      FTM_PDD_SetDeadTime67(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define FTM_PDD_SetDeadTime67(PeripheralBase, State) ( \
    FTM_COMBINE_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       FTM_COMBINE_REG(PeripheralBase)) & ( \
       (uint32_t)(~(uint32_t)FTM_COMBINE_DTEN3_MASK)))) | ( \
      (uint32_t)((uint32_t)(State) << FTM_COMBINE_DTEN3_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SetDeadTime45
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables the deadtime insertion in the channels 4 and 5.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of the deadtime insertion. This parameter is of
 *        "Global enumeration used for specifying general enable/disable states
 *        (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTM0_COMBINE,
 *          FTM1_COMBINE, FTM2_COMBINE, FTM3_COMBINE (depending on the peripheral).
 * @par Example:
 *      @code
 *      FTM_PDD_SetDeadTime45(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define FTM_PDD_SetDeadTime45(PeripheralBase, State) ( \
    FTM_COMBINE_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       FTM_COMBINE_REG(PeripheralBase)) & ( \
       (uint32_t)(~(uint32_t)FTM_COMBINE_DTEN2_MASK)))) | ( \
      (uint32_t)((uint32_t)(State) << FTM_COMBINE_DTEN2_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SetDeadTime23
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables the deadtime insertion in the channels 2 and 3.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of the deadtime insertion. This parameter is of
 *        "Global enumeration used for specifying general enable/disable states
 *        (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTM0_COMBINE,
 *          FTM1_COMBINE, FTM2_COMBINE, FTM3_COMBINE (depending on the peripheral).
 * @par Example:
 *      @code
 *      FTM_PDD_SetDeadTime23(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define FTM_PDD_SetDeadTime23(PeripheralBase, State) ( \
    FTM_COMBINE_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       FTM_COMBINE_REG(PeripheralBase)) & ( \
       (uint32_t)(~(uint32_t)FTM_COMBINE_DTEN1_MASK)))) | ( \
      (uint32_t)((uint32_t)(State) << FTM_COMBINE_DTEN1_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SetDeadTime01
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables the deadtime insertion in the channels 0 and 1.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of the deadtime insertion. This parameter is of
 *        "Global enumeration used for specifying general enable/disable states
 *        (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTM0_COMBINE,
 *          FTM1_COMBINE, FTM2_COMBINE, FTM3_COMBINE (depending on the peripheral).
 * @par Example:
 *      @code
 *      FTM_PDD_SetDeadTime01(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define FTM_PDD_SetDeadTime01(PeripheralBase, State) ( \
    FTM_COMBINE_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       FTM_COMBINE_REG(PeripheralBase)) & ( \
       (uint32_t)(~(uint32_t)FTM_COMBINE_DTEN0_MASK)))) | ( \
      (uint32_t)((uint32_t)(State) << FTM_COMBINE_DTEN0_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SetDualEdgeCaptures6
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables the capture of the FTM counter value according to the channel
 * 6 input event and the configuration of the dual edge capture bits.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of the dual edge captures for channel 6. This
 *        parameter is of "Global enumeration used for specifying general
 *        enable/disable states (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTM0_COMBINE,
 *          FTM1_COMBINE, FTM2_COMBINE, FTM3_COMBINE (depending on the peripheral).
 * @par Example:
 *      @code
 *      FTM_PDD_SetDualEdgeCaptures6(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define FTM_PDD_SetDualEdgeCaptures6(PeripheralBase, State) ( \
    FTM_COMBINE_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       FTM_COMBINE_REG(PeripheralBase)) & ( \
       (uint32_t)(~(uint32_t)FTM_COMBINE_DECAP3_MASK)))) | ( \
      (uint32_t)((uint32_t)(State) << FTM_COMBINE_DECAP3_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SetDualEdgeCaptures4
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables the capture of the FTM counter value according to the channel
 * 4 input event and the configuration of the dual edge capture bits.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of the dual edge captures for channel 4. This
 *        parameter is of "Global enumeration used for specifying general
 *        enable/disable states (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTM0_COMBINE,
 *          FTM1_COMBINE, FTM2_COMBINE, FTM3_COMBINE (depending on the peripheral).
 * @par Example:
 *      @code
 *      FTM_PDD_SetDualEdgeCaptures4(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define FTM_PDD_SetDualEdgeCaptures4(PeripheralBase, State) ( \
    FTM_COMBINE_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       FTM_COMBINE_REG(PeripheralBase)) & ( \
       (uint32_t)(~(uint32_t)FTM_COMBINE_DECAP2_MASK)))) | ( \
      (uint32_t)((uint32_t)(State) << FTM_COMBINE_DECAP2_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SetDualEdgeCaptures2
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables the capture of the FTM counter value according to the channel
 * 2 input event and the configuration of the dual edge capture bits.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of the dual edge captures for channel 2. This
 *        parameter is of "Global enumeration used for specifying general
 *        enable/disable states (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTM0_COMBINE,
 *          FTM1_COMBINE, FTM2_COMBINE, FTM3_COMBINE (depending on the peripheral).
 * @par Example:
 *      @code
 *      FTM_PDD_SetDualEdgeCaptures2(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define FTM_PDD_SetDualEdgeCaptures2(PeripheralBase, State) ( \
    FTM_COMBINE_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       FTM_COMBINE_REG(PeripheralBase)) & ( \
       (uint32_t)(~(uint32_t)FTM_COMBINE_DECAP1_MASK)))) | ( \
      (uint32_t)((uint32_t)(State) << FTM_COMBINE_DECAP1_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SetDualEdgeCaptures0
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables the capture of the FTM counter value according to the channel
 * 0 input event and the configuration of the dual edge capture bits.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of the dual edge captures for channel 0. This
 *        parameter is of "Global enumeration used for specifying general
 *        enable/disable states (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTM0_COMBINE,
 *          FTM1_COMBINE, FTM2_COMBINE, FTM3_COMBINE (depending on the peripheral).
 * @par Example:
 *      @code
 *      FTM_PDD_SetDualEdgeCaptures0(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define FTM_PDD_SetDualEdgeCaptures0(PeripheralBase, State) ( \
    FTM_COMBINE_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       FTM_COMBINE_REG(PeripheralBase)) & ( \
       (uint32_t)(~(uint32_t)FTM_COMBINE_DECAP0_MASK)))) | ( \
      (uint32_t)((uint32_t)(State) << FTM_COMBINE_DECAP0_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SetDualEdgeCaptureMode67
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables the Dual Edge Capture mode in the channels 6 and 7.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of the dual edge capture mode. This parameter is
 *        of "Global enumeration used for specifying general enable/disable
 *        states (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTM0_COMBINE,
 *          FTM1_COMBINE, FTM2_COMBINE, FTM3_COMBINE (depending on the peripheral).
 * @par Example:
 *      @code
 *      FTM_PDD_SetDualEdgeCaptureMode67(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define FTM_PDD_SetDualEdgeCaptureMode67(PeripheralBase, State) ( \
    FTM_COMBINE_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       FTM_COMBINE_REG(PeripheralBase)) & ( \
       (uint32_t)(~(uint32_t)FTM_COMBINE_DECAPEN3_MASK)))) | ( \
      (uint32_t)((uint32_t)(State) << FTM_COMBINE_DECAPEN3_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SetDualEdgeCaptureMode45
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables the Dual Edge Capture mode in the channels 4 and 5.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of the dual edge capture mode. This parameter is
 *        of "Global enumeration used for specifying general enable/disable
 *        states (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTM0_COMBINE,
 *          FTM1_COMBINE, FTM2_COMBINE, FTM3_COMBINE (depending on the peripheral).
 * @par Example:
 *      @code
 *      FTM_PDD_SetDualEdgeCaptureMode45(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define FTM_PDD_SetDualEdgeCaptureMode45(PeripheralBase, State) ( \
    FTM_COMBINE_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       FTM_COMBINE_REG(PeripheralBase)) & ( \
       (uint32_t)(~(uint32_t)FTM_COMBINE_DECAPEN2_MASK)))) | ( \
      (uint32_t)((uint32_t)(State) << FTM_COMBINE_DECAPEN2_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SetDualEdgeCaptureMode23
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables the Dual Edge Capture mode in the channels 2 and 3.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of the dual edge capture mode. This parameter is
 *        of "Global enumeration used for specifying general enable/disable
 *        states (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTM0_COMBINE,
 *          FTM1_COMBINE, FTM2_COMBINE, FTM3_COMBINE (depending on the peripheral).
 * @par Example:
 *      @code
 *      FTM_PDD_SetDualEdgeCaptureMode23(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define FTM_PDD_SetDualEdgeCaptureMode23(PeripheralBase, State) ( \
    FTM_COMBINE_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       FTM_COMBINE_REG(PeripheralBase)) & ( \
       (uint32_t)(~(uint32_t)FTM_COMBINE_DECAPEN1_MASK)))) | ( \
      (uint32_t)((uint32_t)(State) << FTM_COMBINE_DECAPEN1_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SetDualEdgeCaptureMode01
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables the Dual Edge Capture mode in the channels 0 and 1.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of the dual edge capture mode. This parameter is
 *        of "Global enumeration used for specifying general enable/disable
 *        states (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTM0_COMBINE,
 *          FTM1_COMBINE, FTM2_COMBINE, FTM3_COMBINE (depending on the peripheral).
 * @par Example:
 *      @code
 *      FTM_PDD_SetDualEdgeCaptureMode01(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define FTM_PDD_SetDualEdgeCaptureMode01(PeripheralBase, State) ( \
    FTM_COMBINE_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       FTM_COMBINE_REG(PeripheralBase)) & ( \
       (uint32_t)(~(uint32_t)FTM_COMBINE_DECAPEN0_MASK)))) | ( \
      (uint32_t)((uint32_t)(State) << FTM_COMBINE_DECAPEN0_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SetComplementaryMode67
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables Complementary mode for the combined channels. In Complementary
 * mode the channel 7 output is the inverse of the channel 6 output.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of the complementary mode. This parameter is of
 *        "Global enumeration used for specifying general enable/disable states
 *        (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTM0_COMBINE,
 *          FTM1_COMBINE, FTM2_COMBINE, FTM3_COMBINE (depending on the peripheral).
 * @par Example:
 *      @code
 *      FTM_PDD_SetComplementaryMode67(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define FTM_PDD_SetComplementaryMode67(PeripheralBase, State) ( \
    FTM_COMBINE_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       FTM_COMBINE_REG(PeripheralBase)) & ( \
       (uint32_t)(~(uint32_t)FTM_COMBINE_COMP3_MASK)))) | ( \
      (uint32_t)((uint32_t)(State) << FTM_COMBINE_COMP3_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SetComplementaryMode45
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables Complementary mode for the combined channels. In Complementary
 * mode the channel 5 output is the inverse of the channel 4 output.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of the complementary mode. This parameter is of
 *        "Global enumeration used for specifying general enable/disable states
 *        (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTM0_COMBINE,
 *          FTM1_COMBINE, FTM2_COMBINE, FTM3_COMBINE (depending on the peripheral).
 * @par Example:
 *      @code
 *      FTM_PDD_SetComplementaryMode45(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define FTM_PDD_SetComplementaryMode45(PeripheralBase, State) ( \
    FTM_COMBINE_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       FTM_COMBINE_REG(PeripheralBase)) & ( \
       (uint32_t)(~(uint32_t)FTM_COMBINE_COMP2_MASK)))) | ( \
      (uint32_t)((uint32_t)(State) << FTM_COMBINE_COMP2_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SetComplementaryMode23
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables Complementary mode for the combined channels. In Complementary
 * mode the channel 3 output is the inverse of the channel 2 output.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of the complementary mode. This parameter is of
 *        "Global enumeration used for specifying general enable/disable states
 *        (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTM0_COMBINE,
 *          FTM1_COMBINE, FTM2_COMBINE, FTM3_COMBINE (depending on the peripheral).
 * @par Example:
 *      @code
 *      FTM_PDD_SetComplementaryMode23(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define FTM_PDD_SetComplementaryMode23(PeripheralBase, State) ( \
    FTM_COMBINE_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       FTM_COMBINE_REG(PeripheralBase)) & ( \
       (uint32_t)(~(uint32_t)FTM_COMBINE_COMP1_MASK)))) | ( \
      (uint32_t)((uint32_t)(State) << FTM_COMBINE_COMP1_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SetComplementaryMode01
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables Complementary mode for the combined channels. In Complementary
 * mode the channel 1 output is the inverse of the channel 0 output.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of the complementary mode. This parameter is of
 *        "Global enumeration used for specifying general enable/disable states
 *        (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTM0_COMBINE,
 *          FTM1_COMBINE, FTM2_COMBINE, FTM3_COMBINE (depending on the peripheral).
 * @par Example:
 *      @code
 *      FTM_PDD_SetComplementaryMode01(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define FTM_PDD_SetComplementaryMode01(PeripheralBase, State) ( \
    FTM_COMBINE_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       FTM_COMBINE_REG(PeripheralBase)) & ( \
       (uint32_t)(~(uint32_t)FTM_COMBINE_COMP0_MASK)))) | ( \
      (uint32_t)((uint32_t)(State) << FTM_COMBINE_COMP0_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SetCombineChannels67
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables the combine feature for channels 6 and 7.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of the combine channels. This parameter is of
 *        "Global enumeration used for specifying general enable/disable states
 *        (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTM0_COMBINE,
 *          FTM1_COMBINE, FTM2_COMBINE, FTM3_COMBINE (depending on the peripheral).
 * @par Example:
 *      @code
 *      FTM_PDD_SetCombineChannels67(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define FTM_PDD_SetCombineChannels67(PeripheralBase, State) ( \
    FTM_COMBINE_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       FTM_COMBINE_REG(PeripheralBase)) & ( \
       (uint32_t)(~(uint32_t)FTM_COMBINE_COMBINE3_MASK)))) | ( \
      (uint32_t)((uint32_t)(State) << FTM_COMBINE_COMBINE3_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SetCombineChannels45
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables the combine feature for channels 4 and 5.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of the combine channels. This parameter is of
 *        "Global enumeration used for specifying general enable/disable states
 *        (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTM0_COMBINE,
 *          FTM1_COMBINE, FTM2_COMBINE, FTM3_COMBINE (depending on the peripheral).
 * @par Example:
 *      @code
 *      FTM_PDD_SetCombineChannels45(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define FTM_PDD_SetCombineChannels45(PeripheralBase, State) ( \
    FTM_COMBINE_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       FTM_COMBINE_REG(PeripheralBase)) & ( \
       (uint32_t)(~(uint32_t)FTM_COMBINE_COMBINE2_MASK)))) | ( \
      (uint32_t)((uint32_t)(State) << FTM_COMBINE_COMBINE2_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SetCombineChannels23
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables the combine feature for channels 2 and 3.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of the combine channels. This parameter is of
 *        "Global enumeration used for specifying general enable/disable states
 *        (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTM0_COMBINE,
 *          FTM1_COMBINE, FTM2_COMBINE, FTM3_COMBINE (depending on the peripheral).
 * @par Example:
 *      @code
 *      FTM_PDD_SetCombineChannels23(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define FTM_PDD_SetCombineChannels23(PeripheralBase, State) ( \
    FTM_COMBINE_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       FTM_COMBINE_REG(PeripheralBase)) & ( \
       (uint32_t)(~(uint32_t)FTM_COMBINE_COMBINE1_MASK)))) | ( \
      (uint32_t)((uint32_t)(State) << FTM_COMBINE_COMBINE1_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SetCombineChannels01
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables the combine feature for channels 0 and 1.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of the combine channels. This parameter is of
 *        "Global enumeration used for specifying general enable/disable states
 *        (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTM0_COMBINE,
 *          FTM1_COMBINE, FTM2_COMBINE, FTM3_COMBINE (depending on the peripheral).
 * @par Example:
 *      @code
 *      FTM_PDD_SetCombineChannels01(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define FTM_PDD_SetCombineChannels01(PeripheralBase, State) ( \
    FTM_COMBINE_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       FTM_COMBINE_REG(PeripheralBase)) & ( \
       (uint32_t)(~(uint32_t)FTM_COMBINE_COMBINE0_MASK)))) | ( \
      (uint32_t)(State))) \
  )

/* ----------------------------------------------------------------------------
   -- SetDeadtimePrescaler
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets deadtime prescale value.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Prescaler New value of the deadtime prescaler. Use constants from
 *        group "Deadtime prescaler constants". This parameter is 2 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTM0_DEADTIME,
 *          FTM1_DEADTIME, FTM2_DEADTIME, FTM3_DEADTIME (depending on the peripheral).
 * @par Example:
 *      @code
 *      FTM_PDD_SetDeadtimePrescaler(<peripheral>_BASE_PTR,
 *      FTM_PDD_DT_DIVIDE_1);
 *      @endcode
 */
#define FTM_PDD_SetDeadtimePrescaler(PeripheralBase, Prescaler) ( \
    FTM_DEADTIME_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       FTM_DEADTIME_REG(PeripheralBase)) & ( \
       (uint32_t)(~(uint32_t)FTM_DEADTIME_DTPS_MASK)))) | ( \
      (uint32_t)((uint32_t)(Prescaler) << FTM_DEADTIME_DTPS_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SetDeadtimeValue
   ---------------------------------------------------------------------------- */

/**
 * @brief Selects the deadtime insertion value for the deadtime counter. The
 * deadtime counter is clocked by a scaled version of the system clock.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value New value of the deadtime. This parameter is a 6-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTM0_DEADTIME,
 *          FTM1_DEADTIME, FTM2_DEADTIME, FTM3_DEADTIME (depending on the peripheral).
 * @par Example:
 *      @code
 *      FTM_PDD_SetDeadtimeValue(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define FTM_PDD_SetDeadtimeValue(PeripheralBase, Value) ( \
    FTM_DEADTIME_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       FTM_DEADTIME_REG(PeripheralBase)) & ( \
       (uint32_t)(~(uint32_t)FTM_DEADTIME_DTVAL_MASK)))) | ( \
      (uint32_t)(Value))) \
  )

/* ----------------------------------------------------------------------------
   -- GetChannelTriggerFlag
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns channel trigger flag bit.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: FTM0_EXTTRIG,
 *          FTM1_EXTTRIG, FTM2_EXTTRIG, FTM3_EXTTRIG (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result = FTM_PDD_GetChannelTriggerFlag(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTM_PDD_GetChannelTriggerFlag(PeripheralBase) ( \
    (uint32_t)(FTM_EXTTRIG_REG(PeripheralBase) & FTM_EXTTRIG_TRIGF_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- SetInitializationTrigger
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables the generation of the trigger when the FTM counter is equal to
 * the CNTIN register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of the generation of the trigger. This parameter
 *        is of "Global enumeration used for specifying general enable/disable
 *        states (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTM0_EXTTRIG,
 *          FTM1_EXTTRIG, FTM2_EXTTRIG, FTM3_EXTTRIG (depending on the peripheral).
 * @par Example:
 *      @code
 *      FTM_PDD_SetInitializationTrigger(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define FTM_PDD_SetInitializationTrigger(PeripheralBase, State) ( \
    FTM_EXTTRIG_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       FTM_EXTTRIG_REG(PeripheralBase)) & (( \
       (uint32_t)(~(uint32_t)FTM_EXTTRIG_INITTRIGEN_MASK)) & ( \
       (uint32_t)(~(uint32_t)FTM_EXTTRIG_TRIGF_MASK))))) | ( \
      (uint32_t)((uint32_t)(State) << FTM_EXTTRIG_INITTRIGEN_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SetChannelTrigger0
   ---------------------------------------------------------------------------- */

/**
 * @brief Enable the generation of the channel trigger when the FTM counter is
 * equal to the C0V register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of the channel 0 trigger. This parameter is of
 *        "Global enumeration used for specifying general enable/disable states
 *        (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTM0_EXTTRIG,
 *          FTM1_EXTTRIG, FTM2_EXTTRIG, FTM3_EXTTRIG (depending on the peripheral).
 * @par Example:
 *      @code
 *      FTM_PDD_SetChannelTrigger0(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define FTM_PDD_SetChannelTrigger0(PeripheralBase, State) ( \
    FTM_EXTTRIG_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       FTM_EXTTRIG_REG(PeripheralBase)) & (( \
       (uint32_t)(~(uint32_t)FTM_EXTTRIG_CH0TRIG_MASK)) & ( \
       (uint32_t)(~(uint32_t)FTM_EXTTRIG_TRIGF_MASK))))) | ( \
      (uint32_t)((uint32_t)(State) << FTM_EXTTRIG_CH0TRIG_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SetChannelTrigger1
   ---------------------------------------------------------------------------- */

/**
 * @brief Enable the generation of the channel trigger when the FTM counter is
 * equal to the C1V register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of the channel 1 trigger. This parameter is of
 *        "Global enumeration used for specifying general enable/disable states
 *        (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTM0_EXTTRIG,
 *          FTM1_EXTTRIG, FTM2_EXTTRIG, FTM3_EXTTRIG (depending on the peripheral).
 * @par Example:
 *      @code
 *      FTM_PDD_SetChannelTrigger1(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define FTM_PDD_SetChannelTrigger1(PeripheralBase, State) ( \
    FTM_EXTTRIG_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       FTM_EXTTRIG_REG(PeripheralBase)) & (( \
       (uint32_t)(~(uint32_t)FTM_EXTTRIG_CH1TRIG_MASK)) & ( \
       (uint32_t)(~(uint32_t)FTM_EXTTRIG_TRIGF_MASK))))) | ( \
      (uint32_t)((uint32_t)(State) << FTM_EXTTRIG_CH1TRIG_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SetChannelTrigger2
   ---------------------------------------------------------------------------- */

/**
 * @brief Enable the generation of the channel trigger when the FTM counter is
 * equal to the C2V register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of the channel 2 trigger. This parameter is of
 *        "Global enumeration used for specifying general enable/disable states
 *        (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTM0_EXTTRIG,
 *          FTM1_EXTTRIG, FTM2_EXTTRIG, FTM3_EXTTRIG (depending on the peripheral).
 * @par Example:
 *      @code
 *      FTM_PDD_SetChannelTrigger2(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define FTM_PDD_SetChannelTrigger2(PeripheralBase, State) ( \
    FTM_EXTTRIG_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       FTM_EXTTRIG_REG(PeripheralBase)) & (( \
       (uint32_t)(~(uint32_t)FTM_EXTTRIG_CH2TRIG_MASK)) & ( \
       (uint32_t)(~(uint32_t)FTM_EXTTRIG_TRIGF_MASK))))) | ( \
      (uint32_t)(State))) \
  )

/* ----------------------------------------------------------------------------
   -- SetChannelTrigger3
   ---------------------------------------------------------------------------- */

/**
 * @brief Enable the generation of the channel trigger when the FTM counter is
 * equal to the C3V register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of the channel 3 trigger. This parameter is of
 *        "Global enumeration used for specifying general enable/disable states
 *        (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTM0_EXTTRIG,
 *          FTM1_EXTTRIG, FTM2_EXTTRIG, FTM3_EXTTRIG (depending on the peripheral).
 * @par Example:
 *      @code
 *      FTM_PDD_SetChannelTrigger3(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define FTM_PDD_SetChannelTrigger3(PeripheralBase, State) ( \
    FTM_EXTTRIG_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       FTM_EXTTRIG_REG(PeripheralBase)) & (( \
       (uint32_t)(~(uint32_t)FTM_EXTTRIG_CH3TRIG_MASK)) & ( \
       (uint32_t)(~(uint32_t)FTM_EXTTRIG_TRIGF_MASK))))) | ( \
      (uint32_t)((uint32_t)(State) << FTM_EXTTRIG_CH3TRIG_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SetChannelTrigger4
   ---------------------------------------------------------------------------- */

/**
 * @brief Enable the generation of the channel trigger when the FTM counter is
 * equal to the C4V register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of the channel 4 trigger. This parameter is of
 *        "Global enumeration used for specifying general enable/disable states
 *        (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTM0_EXTTRIG,
 *          FTM1_EXTTRIG, FTM2_EXTTRIG, FTM3_EXTTRIG (depending on the peripheral).
 * @par Example:
 *      @code
 *      FTM_PDD_SetChannelTrigger4(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define FTM_PDD_SetChannelTrigger4(PeripheralBase, State) ( \
    FTM_EXTTRIG_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       FTM_EXTTRIG_REG(PeripheralBase)) & (( \
       (uint32_t)(~(uint32_t)FTM_EXTTRIG_CH4TRIG_MASK)) & ( \
       (uint32_t)(~(uint32_t)FTM_EXTTRIG_TRIGF_MASK))))) | ( \
      (uint32_t)((uint32_t)(State) << FTM_EXTTRIG_CH4TRIG_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SetChannelTrigger5
   ---------------------------------------------------------------------------- */

/**
 * @brief Enable the generation of the channel trigger when the FTM counter is
 * equal to the C5V register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of the channel 5 trigger. This parameter is of
 *        "Global enumeration used for specifying general enable/disable states
 *        (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTM0_EXTTRIG,
 *          FTM1_EXTTRIG, FTM2_EXTTRIG, FTM3_EXTTRIG (depending on the peripheral).
 * @par Example:
 *      @code
 *      FTM_PDD_SetChannelTrigger5(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define FTM_PDD_SetChannelTrigger5(PeripheralBase, State) ( \
    FTM_EXTTRIG_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       FTM_EXTTRIG_REG(PeripheralBase)) & (( \
       (uint32_t)(~(uint32_t)FTM_EXTTRIG_CH5TRIG_MASK)) & ( \
       (uint32_t)(~(uint32_t)FTM_EXTTRIG_TRIGF_MASK))))) | ( \
      (uint32_t)((uint32_t)(State) << FTM_EXTTRIG_CH5TRIG_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SetInputFilter3
   ---------------------------------------------------------------------------- */

/**
 * @brief Selects the filter value for the channel 3 input.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value New value of the channel filter. This parameter is a 4-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTM0_FILTER,
 *          FTM1_FILTER, FTM2_FILTER, FTM3_FILTER (depending on the peripheral).
 * @par Example:
 *      @code
 *      FTM_PDD_SetInputFilter3(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define FTM_PDD_SetInputFilter3(PeripheralBase, Value) ( \
    FTM_FILTER_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       FTM_FILTER_REG(PeripheralBase)) & ( \
       (uint32_t)(~(uint32_t)FTM_FILTER_CH3FVAL_MASK)))) | ( \
      (uint32_t)((uint32_t)(Value) << FTM_FILTER_CH3FVAL_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SetInputFilter2
   ---------------------------------------------------------------------------- */

/**
 * @brief Selects the filter value for the channel 2 input.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value New value of the channel filter. This parameter is a 4-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTM0_FILTER,
 *          FTM1_FILTER, FTM2_FILTER, FTM3_FILTER (depending on the peripheral).
 * @par Example:
 *      @code
 *      FTM_PDD_SetInputFilter2(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define FTM_PDD_SetInputFilter2(PeripheralBase, Value) ( \
    FTM_FILTER_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       FTM_FILTER_REG(PeripheralBase)) & ( \
       (uint32_t)(~(uint32_t)FTM_FILTER_CH2FVAL_MASK)))) | ( \
      (uint32_t)((uint32_t)(Value) << FTM_FILTER_CH2FVAL_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SetInputFilter1
   ---------------------------------------------------------------------------- */

/**
 * @brief Selects the filter value for the channel 1 input.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value New value of the channel filter. This parameter is a 4-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTM0_FILTER,
 *          FTM1_FILTER, FTM2_FILTER, FTM3_FILTER (depending on the peripheral).
 * @par Example:
 *      @code
 *      FTM_PDD_SetInputFilter1(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define FTM_PDD_SetInputFilter1(PeripheralBase, Value) ( \
    FTM_FILTER_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       FTM_FILTER_REG(PeripheralBase)) & ( \
       (uint32_t)(~(uint32_t)FTM_FILTER_CH1FVAL_MASK)))) | ( \
      (uint32_t)((uint32_t)(Value) << FTM_FILTER_CH1FVAL_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SetInputFilter0
   ---------------------------------------------------------------------------- */

/**
 * @brief Selects the filter value for the channel 0 input.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value New value of the channel filter. This parameter is a 4-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTM0_FILTER,
 *          FTM1_FILTER, FTM2_FILTER, FTM3_FILTER (depending on the peripheral).
 * @par Example:
 *      @code
 *      FTM_PDD_SetInputFilter0(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define FTM_PDD_SetInputFilter0(PeripheralBase, Value) ( \
    FTM_FILTER_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       FTM_FILTER_REG(PeripheralBase)) & ( \
       (uint32_t)(~(uint32_t)FTM_FILTER_CH0FVAL_MASK)))) | ( \
      (uint32_t)(Value))) \
  )

/* ----------------------------------------------------------------------------
   -- SetFaultInpuFilter
   ---------------------------------------------------------------------------- */

/**
 * @brief Selects the filter value for the fault inputs.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value New value of the fault input filter. This parameter is a 4-bit
 *        value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTM0_FLTCTRL,
 *          FTM1_FLTCTRL, FTM2_FLTCTRL, FTM3_FLTCTRL (depending on the peripheral).
 * @par Example:
 *      @code
 *      FTM_PDD_SetFaultInpuFilter(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define FTM_PDD_SetFaultInpuFilter(PeripheralBase, Value) ( \
    FTM_FLTCTRL_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       FTM_FLTCTRL_REG(PeripheralBase)) & ( \
       (uint32_t)(~(uint32_t)FTM_FLTCTRL_FFVAL_MASK)))) | ( \
      (uint32_t)((uint32_t)(Value) << FTM_FLTCTRL_FFVAL_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SetFaultInputFilter3
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables the filter for the fault 3 input.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of the fault input filter. This parameter is of
 *        "Global enumeration used for specifying general enable/disable states
 *        (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTM0_FLTCTRL,
 *          FTM1_FLTCTRL, FTM2_FLTCTRL, FTM3_FLTCTRL (depending on the peripheral).
 * @par Example:
 *      @code
 *      FTM_PDD_SetFaultInputFilter3(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define FTM_PDD_SetFaultInputFilter3(PeripheralBase, State) ( \
    FTM_FLTCTRL_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       FTM_FLTCTRL_REG(PeripheralBase)) & ( \
       (uint32_t)(~(uint32_t)FTM_FLTCTRL_FFLTR3EN_MASK)))) | ( \
      (uint32_t)((uint32_t)(State) << FTM_FLTCTRL_FFLTR3EN_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SetFaultInputFilter2
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables the filter for the fault 2 input.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of the fault input filter. This parameter is of
 *        "Global enumeration used for specifying general enable/disable states
 *        (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTM0_FLTCTRL,
 *          FTM1_FLTCTRL, FTM2_FLTCTRL, FTM3_FLTCTRL (depending on the peripheral).
 * @par Example:
 *      @code
 *      FTM_PDD_SetFaultInputFilter2(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define FTM_PDD_SetFaultInputFilter2(PeripheralBase, State) ( \
    FTM_FLTCTRL_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       FTM_FLTCTRL_REG(PeripheralBase)) & ( \
       (uint32_t)(~(uint32_t)FTM_FLTCTRL_FFLTR2EN_MASK)))) | ( \
      (uint32_t)((uint32_t)(State) << FTM_FLTCTRL_FFLTR2EN_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SetFaultInputFilter1
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables the filter for the fault 1 input.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of the fault input filter. This parameter is of
 *        "Global enumeration used for specifying general enable/disable states
 *        (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTM0_FLTCTRL,
 *          FTM1_FLTCTRL, FTM2_FLTCTRL, FTM3_FLTCTRL (depending on the peripheral).
 * @par Example:
 *      @code
 *      FTM_PDD_SetFaultInputFilter1(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define FTM_PDD_SetFaultInputFilter1(PeripheralBase, State) ( \
    FTM_FLTCTRL_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       FTM_FLTCTRL_REG(PeripheralBase)) & ( \
       (uint32_t)(~(uint32_t)FTM_FLTCTRL_FFLTR1EN_MASK)))) | ( \
      (uint32_t)((uint32_t)(State) << FTM_FLTCTRL_FFLTR1EN_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SetFaultInputFilter0
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables the filter for the fault 0 input.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of the fault input filter. This parameter is of
 *        "Global enumeration used for specifying general enable/disable states
 *        (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTM0_FLTCTRL,
 *          FTM1_FLTCTRL, FTM2_FLTCTRL, FTM3_FLTCTRL (depending on the peripheral).
 * @par Example:
 *      @code
 *      FTM_PDD_SetFaultInputFilter0(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define FTM_PDD_SetFaultInputFilter0(PeripheralBase, State) ( \
    FTM_FLTCTRL_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       FTM_FLTCTRL_REG(PeripheralBase)) & ( \
       (uint32_t)(~(uint32_t)FTM_FLTCTRL_FFLTR0EN_MASK)))) | ( \
      (uint32_t)((uint32_t)(State) << FTM_FLTCTRL_FFLTR0EN_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SetFaultInput3
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables the fault 3 input.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of the fault input filter. This parameter is of
 *        "Global enumeration used for specifying general enable/disable states
 *        (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTM0_FLTCTRL,
 *          FTM1_FLTCTRL, FTM2_FLTCTRL, FTM3_FLTCTRL (depending on the peripheral).
 * @par Example:
 *      @code
 *      FTM_PDD_SetFaultInput3(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define FTM_PDD_SetFaultInput3(PeripheralBase, State) ( \
    FTM_FLTCTRL_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       FTM_FLTCTRL_REG(PeripheralBase)) & ( \
       (uint32_t)(~(uint32_t)FTM_FLTCTRL_FAULT3EN_MASK)))) | ( \
      (uint32_t)((uint32_t)(State) << FTM_FLTCTRL_FAULT3EN_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SetFaultInput2
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables the fault 2 input.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of the fault input filter. This parameter is of
 *        "Global enumeration used for specifying general enable/disable states
 *        (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTM0_FLTCTRL,
 *          FTM1_FLTCTRL, FTM2_FLTCTRL, FTM3_FLTCTRL (depending on the peripheral).
 * @par Example:
 *      @code
 *      FTM_PDD_SetFaultInput2(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define FTM_PDD_SetFaultInput2(PeripheralBase, State) ( \
    FTM_FLTCTRL_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       FTM_FLTCTRL_REG(PeripheralBase)) & ( \
       (uint32_t)(~(uint32_t)FTM_FLTCTRL_FAULT2EN_MASK)))) | ( \
      (uint32_t)((uint32_t)(State) << FTM_FLTCTRL_FAULT2EN_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SetFaultInput1
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables the fault 1 input.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of the fault input filter. This parameter is of
 *        "Global enumeration used for specifying general enable/disable states
 *        (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTM0_FLTCTRL,
 *          FTM1_FLTCTRL, FTM2_FLTCTRL, FTM3_FLTCTRL (depending on the peripheral).
 * @par Example:
 *      @code
 *      FTM_PDD_SetFaultInput1(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define FTM_PDD_SetFaultInput1(PeripheralBase, State) ( \
    FTM_FLTCTRL_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       FTM_FLTCTRL_REG(PeripheralBase)) & ( \
       (uint32_t)(~(uint32_t)FTM_FLTCTRL_FAULT1EN_MASK)))) | ( \
      (uint32_t)((uint32_t)(State) << FTM_FLTCTRL_FAULT1EN_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SetFaultInput0
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables the fault 0 input.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of the fault input filter. This parameter is of
 *        "Global enumeration used for specifying general enable/disable states
 *        (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTM0_FLTCTRL,
 *          FTM1_FLTCTRL, FTM2_FLTCTRL, FTM3_FLTCTRL (depending on the peripheral).
 * @par Example:
 *      @code
 *      FTM_PDD_SetFaultInput0(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define FTM_PDD_SetFaultInput0(PeripheralBase, State) ( \
    FTM_FLTCTRL_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       FTM_FLTCTRL_REG(PeripheralBase)) & ( \
       (uint32_t)(~(uint32_t)FTM_FLTCTRL_FAULT0EN_MASK)))) | ( \
      (uint32_t)(State))) \
  )

/* ----------------------------------------------------------------------------
   -- SetPhaseAInputFilter
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables the filter for the quadrature decoder phase A input.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of the filter for quadrature decoder. This
 *        parameter is of "Global enumeration used for specifying general
 *        enable/disable states (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTM0_QDCTRL,
 *          FTM1_QDCTRL, FTM2_QDCTRL, FTM3_QDCTRL (depending on the peripheral).
 * @par Example:
 *      @code
 *      FTM_PDD_SetPhaseAInputFilter(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define FTM_PDD_SetPhaseAInputFilter(PeripheralBase, State) ( \
    FTM_QDCTRL_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       FTM_QDCTRL_REG(PeripheralBase)) & ( \
       (uint32_t)(~(uint32_t)FTM_QDCTRL_PHAFLTREN_MASK)))) | ( \
      (uint32_t)((uint32_t)(State) << FTM_QDCTRL_PHAFLTREN_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SetPhaseBInputFilter
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables the filter for the quadrature decoder phase B input.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of the filter for quadrature decoder. This
 *        parameter is of "Global enumeration used for specifying general
 *        enable/disable states (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTM0_QDCTRL,
 *          FTM1_QDCTRL, FTM2_QDCTRL, FTM3_QDCTRL (depending on the peripheral).
 * @par Example:
 *      @code
 *      FTM_PDD_SetPhaseBInputFilter(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define FTM_PDD_SetPhaseBInputFilter(PeripheralBase, State) ( \
    FTM_QDCTRL_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       FTM_QDCTRL_REG(PeripheralBase)) & ( \
       (uint32_t)(~(uint32_t)FTM_QDCTRL_PHBFLTREN_MASK)))) | ( \
      (uint32_t)((uint32_t)(State) << FTM_QDCTRL_PHBFLTREN_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SelectPhaseAInputPolarity
   ---------------------------------------------------------------------------- */

/**
 * @brief Selects the polarity for the quadrature decoder phase A input.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mode New value of the phase A input polarity. This parameter is of
 *        "Phase input polarity constants." type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTM0_QDCTRL,
 *          FTM1_QDCTRL, FTM2_QDCTRL, FTM3_QDCTRL (depending on the peripheral).
 * @par Example:
 *      @code
 *      FTM_PDD_SelectPhaseAInputPolarity(<peripheral>_BASE_PTR,
 *      FTM_PDD_QD_NORMAL_POLARITY);
 *      @endcode
 */
#define FTM_PDD_SelectPhaseAInputPolarity(PeripheralBase, Mode) ( \
    FTM_QDCTRL_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(FTM_QDCTRL_REG(PeripheralBase) & (uint32_t)(~(uint32_t)FTM_QDCTRL_PHAPOL_MASK))) | ( \
      (uint32_t)((uint32_t)(Mode) << FTM_QDCTRL_PHAPOL_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SelectPhaseBInputPolarity
   ---------------------------------------------------------------------------- */

/**
 * @brief Selects the polarity for the quadrature decoder phase B input.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mode New value of the phase B input polarity. This parameter is of
 *        "Phase input polarity constants." type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTM0_QDCTRL,
 *          FTM1_QDCTRL, FTM2_QDCTRL, FTM3_QDCTRL (depending on the peripheral).
 * @par Example:
 *      @code
 *      FTM_PDD_SelectPhaseBInputPolarity(<peripheral>_BASE_PTR,
 *      FTM_PDD_QD_NORMAL_POLARITY);
 *      @endcode
 */
#define FTM_PDD_SelectPhaseBInputPolarity(PeripheralBase, Mode) ( \
    FTM_QDCTRL_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(FTM_QDCTRL_REG(PeripheralBase) & (uint32_t)(~(uint32_t)FTM_QDCTRL_PHBPOL_MASK))) | ( \
      (uint32_t)((uint32_t)(Mode) << FTM_QDCTRL_PHBPOL_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SelectQDMode
   ---------------------------------------------------------------------------- */

/**
 * @brief Selects the encoding mode used in the quadrature decoder mode.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mode New value of the quadrature decoder encoding mode. This parameter
 *        is of "Quadrature decoder encoding mode constants." type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTM0_QDCTRL,
 *          FTM1_QDCTRL, FTM2_QDCTRL, FTM3_QDCTRL (depending on the peripheral).
 * @par Example:
 *      @code
 *      FTM_PDD_SelectQDMode(<peripheral>_BASE_PTR,
 *      FTM_PDD_QD_PHASEA_AND_PHASEB);
 *      @endcode
 */
#define FTM_PDD_SelectQDMode(PeripheralBase, Mode) ( \
    FTM_QDCTRL_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       FTM_QDCTRL_REG(PeripheralBase)) & ( \
       (uint32_t)(~(uint32_t)FTM_QDCTRL_QUADMODE_MASK)))) | ( \
      (uint32_t)(Mode))) \
  )

/* ----------------------------------------------------------------------------
   -- GetQDCounterDirection
   ---------------------------------------------------------------------------- */

/**
 * @brief Indicates the counting direction in quadrature mode.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: FTM0_QDCTRL,
 *          FTM1_QDCTRL, FTM2_QDCTRL, FTM3_QDCTRL (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result = FTM_PDD_GetQDCounterDirection(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTM_PDD_GetQDCounterDirection(PeripheralBase) ( \
    (uint32_t)(FTM_QDCTRL_REG(PeripheralBase) & FTM_QDCTRL_QUADIR_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- GetQDTimerOverflowDirection
   ---------------------------------------------------------------------------- */

/**
 * @brief Indicates if the TOF bit was set on the top or the bottom of counting
 * in quadrature decoder mode.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: FTM0_QDCTRL,
 *          FTM1_QDCTRL, FTM2_QDCTRL, FTM3_QDCTRL (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result =
 *      FTM_PDD_GetQDTimerOverflowDirection(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTM_PDD_GetQDTimerOverflowDirection(PeripheralBase) ( \
    (uint32_t)(FTM_QDCTRL_REG(PeripheralBase) & FTM_QDCTRL_TOFDIR_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- SetQDMode
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables the quadrature decoder mode. In this mode, the phase A and B
 * input signals control the FTM counter direction.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of the quadrature decoder. This parameter is of
 *        "Global enumeration used for specifying general enable/disable states
 *        (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTM0_QDCTRL,
 *          FTM1_QDCTRL, FTM2_QDCTRL, FTM3_QDCTRL (depending on the peripheral).
 * @par Example:
 *      @code
 *      FTM_PDD_SetQDMode(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define FTM_PDD_SetQDMode(PeripheralBase, State) ( \
    FTM_QDCTRL_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(FTM_QDCTRL_REG(PeripheralBase) & (uint32_t)(~(uint32_t)FTM_QDCTRL_QUADEN_MASK))) | ( \
      (uint32_t)(State))) \
  )

/* ----------------------------------------------------------------------------
   -- SetGlobalTimeBaseOutput
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables the global time base signal generation to other FTMs.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of the global time base output. This parameter
 *        is of "Global enumeration used for specifying general enable/disable
 *        states (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTM0_CONF, FTM1_CONF,
 *          FTM2_CONF, FTM3_CONF (depending on the peripheral).
 * @par Example:
 *      @code
 *      FTM_PDD_SetGlobalTimeBaseOutput(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define FTM_PDD_SetGlobalTimeBaseOutput(PeripheralBase, State) ( \
    FTM_CONF_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(FTM_CONF_REG(PeripheralBase) & (uint32_t)(~(uint32_t)FTM_CONF_GTBEOUT_MASK))) | ( \
      (uint32_t)((uint32_t)(State) << FTM_CONF_GTBEOUT_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SetGlobalTimeBase
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables the FTM to use an external global time base signal that is
 * generated by another FTM.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of the global time base output. This parameter
 *        is of "Global enumeration used for specifying general enable/disable
 *        states (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTM0_CONF, FTM1_CONF,
 *          FTM2_CONF, FTM3_CONF (depending on the peripheral).
 * @par Example:
 *      @code
 *      FTM_PDD_SetGlobalTimeBase(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define FTM_PDD_SetGlobalTimeBase(PeripheralBase, State) ( \
    FTM_CONF_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(FTM_CONF_REG(PeripheralBase) & (uint32_t)(~(uint32_t)FTM_CONF_GTBEEN_MASK))) | ( \
      (uint32_t)((uint32_t)(State) << FTM_CONF_GTBEEN_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SelectBDMMode
   ---------------------------------------------------------------------------- */

/**
 * @brief Selects Selects the FTM behavior in BDM mode.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mode New value of the quadrature decoder encoding mode. This parameter
 *        is of "BDM mode constants." type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTM0_CONF, FTM1_CONF,
 *          FTM2_CONF, FTM3_CONF (depending on the peripheral).
 * @par Example:
 *      @code
 *      FTM_PDD_SelectBDMMode(<peripheral>_BASE_PTR, FTM_PDD_BDM_00);
 *      @endcode
 */
#define FTM_PDD_SelectBDMMode(PeripheralBase, Mode) ( \
    FTM_CONF_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(FTM_CONF_REG(PeripheralBase) & (uint32_t)(~(uint32_t)FTM_CONF_BDMMODE_MASK))) | ( \
      (uint32_t)(Mode))) \
  )

/* ----------------------------------------------------------------------------
   -- SetTOFFrequency
   ---------------------------------------------------------------------------- */

/**
 * @brief Selects the ratio between the number of counter overflows to the
 * number of times the TOF bit is set.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value New value of the TOF frequency. This parameter is a 5-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTM0_CONF, FTM1_CONF,
 *          FTM2_CONF, FTM3_CONF (depending on the peripheral).
 * @par Example:
 *      @code
 *      FTM_PDD_SetTOFFrequency(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define FTM_PDD_SetTOFFrequency(PeripheralBase, Value) ( \
    FTM_CONF_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(FTM_CONF_REG(PeripheralBase) & (uint32_t)(~(uint32_t)FTM_CONF_NUMTOF_MASK))) | ( \
      (uint32_t)(Value))) \
  )

/* ----------------------------------------------------------------------------
   -- SelectFaultInput3Polarity
   ---------------------------------------------------------------------------- */

/**
 * @brief Selects the polarity of the fault input 3.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mode New value of the fault input polarity. This parameter is of
 *        "Fault input polarity constants." type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTM0_FLTPOL,
 *          FTM1_FLTPOL, FTM2_FLTPOL, FTM3_FLTPOL (depending on the peripheral).
 * @par Example:
 *      @code
 *      FTM_PDD_SelectFaultInput3Polarity(<peripheral>_BASE_PTR,
 *      FTM_PDD_FAULT_POLARITY_HIGH);
 *      @endcode
 */
#define FTM_PDD_SelectFaultInput3Polarity(PeripheralBase, Mode) ( \
    FTM_FLTPOL_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       FTM_FLTPOL_REG(PeripheralBase)) & ( \
       (uint32_t)(~(uint32_t)FTM_FLTPOL_FLT3POL_MASK)))) | ( \
      (uint32_t)((uint32_t)(Mode) << FTM_FLTPOL_FLT3POL_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SelectFaultInput2Polarity
   ---------------------------------------------------------------------------- */

/**
 * @brief Selects the polarity of the fault input 2.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mode New value of the fault input polarity. This parameter is of
 *        "Fault input polarity constants." type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTM0_FLTPOL,
 *          FTM1_FLTPOL, FTM2_FLTPOL, FTM3_FLTPOL (depending on the peripheral).
 * @par Example:
 *      @code
 *      FTM_PDD_SelectFaultInput2Polarity(<peripheral>_BASE_PTR,
 *      FTM_PDD_FAULT_POLARITY_HIGH);
 *      @endcode
 */
#define FTM_PDD_SelectFaultInput2Polarity(PeripheralBase, Mode) ( \
    FTM_FLTPOL_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       FTM_FLTPOL_REG(PeripheralBase)) & ( \
       (uint32_t)(~(uint32_t)FTM_FLTPOL_FLT2POL_MASK)))) | ( \
      (uint32_t)((uint32_t)(Mode) << FTM_FLTPOL_FLT2POL_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SelectFaultInput1Polarity
   ---------------------------------------------------------------------------- */

/**
 * @brief Selects the polarity of the fault input 1.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mode New value of the fault input polarity. This parameter is of
 *        "Fault input polarity constants." type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTM0_FLTPOL,
 *          FTM1_FLTPOL, FTM2_FLTPOL, FTM3_FLTPOL (depending on the peripheral).
 * @par Example:
 *      @code
 *      FTM_PDD_SelectFaultInput1Polarity(<peripheral>_BASE_PTR,
 *      FTM_PDD_FAULT_POLARITY_HIGH);
 *      @endcode
 */
#define FTM_PDD_SelectFaultInput1Polarity(PeripheralBase, Mode) ( \
    FTM_FLTPOL_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       FTM_FLTPOL_REG(PeripheralBase)) & ( \
       (uint32_t)(~(uint32_t)FTM_FLTPOL_FLT1POL_MASK)))) | ( \
      (uint32_t)((uint32_t)(Mode) << FTM_FLTPOL_FLT1POL_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SelectFaultInput0Polarity
   ---------------------------------------------------------------------------- */

/**
 * @brief Selects the polarity of the fault input 0.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mode New value of the fault input polarity. This parameter is of
 *        "Fault input polarity constants." type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTM0_FLTPOL,
 *          FTM1_FLTPOL, FTM2_FLTPOL, FTM3_FLTPOL (depending on the peripheral).
 * @par Example:
 *      @code
 *      FTM_PDD_SelectFaultInput0Polarity(<peripheral>_BASE_PTR,
 *      FTM_PDD_FAULT_POLARITY_HIGH);
 *      @endcode
 */
#define FTM_PDD_SelectFaultInput0Polarity(PeripheralBase, Mode) ( \
    FTM_FLTPOL_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       FTM_FLTPOL_REG(PeripheralBase)) & ( \
       (uint32_t)(~(uint32_t)FTM_FLTPOL_FLT0POL_MASK)))) | ( \
      (uint32_t)(Mode))) \
  )

/* ----------------------------------------------------------------------------
   -- SetHWTriggerSWOCTRL
   ---------------------------------------------------------------------------- */

/**
 * @brief A hardware trigger activates the SWOCTRL register synchronization.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of the HW trigger. This parameter is of "Global
 *        enumeration used for specifying general enable/disable states
 *        (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTM0_SYNCONF,
 *          FTM1_SYNCONF, FTM2_SYNCONF, FTM3_SYNCONF (depending on the peripheral).
 * @par Example:
 *      @code
 *      FTM_PDD_SetHWTriggerSWOCTRL(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define FTM_PDD_SetHWTriggerSWOCTRL(PeripheralBase, State) ( \
    FTM_SYNCONF_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       FTM_SYNCONF_REG(PeripheralBase)) & ( \
       (uint32_t)(~(uint32_t)FTM_SYNCONF_HWSOC_MASK)))) | ( \
      (uint32_t)((uint32_t)(State) << FTM_SYNCONF_HWSOC_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SetHWTriggerINVCTRL
   ---------------------------------------------------------------------------- */

/**
 * @brief A hardware trigger activates the INVCTRL register synchronization.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of the HW trigger. This parameter is of "Global
 *        enumeration used for specifying general enable/disable states
 *        (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTM0_SYNCONF,
 *          FTM1_SYNCONF, FTM2_SYNCONF, FTM3_SYNCONF (depending on the peripheral).
 * @par Example:
 *      @code
 *      FTM_PDD_SetHWTriggerINVCTRL(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define FTM_PDD_SetHWTriggerINVCTRL(PeripheralBase, State) ( \
    FTM_SYNCONF_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       FTM_SYNCONF_REG(PeripheralBase)) & ( \
       (uint32_t)(~(uint32_t)FTM_SYNCONF_HWINVC_MASK)))) | ( \
      (uint32_t)((uint32_t)(State) << FTM_SYNCONF_HWINVC_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SetHWTriggerOUTMASK
   ---------------------------------------------------------------------------- */

/**
 * @brief A hardware trigger activates the OUTMASK register synchronization.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of the HW trigger. This parameter is of "Global
 *        enumeration used for specifying general enable/disable states
 *        (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTM0_SYNCONF,
 *          FTM1_SYNCONF, FTM2_SYNCONF, FTM3_SYNCONF (depending on the peripheral).
 * @par Example:
 *      @code
 *      FTM_PDD_SetHWTriggerOUTMASK(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define FTM_PDD_SetHWTriggerOUTMASK(PeripheralBase, State) ( \
    FTM_SYNCONF_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(FTM_SYNCONF_REG(PeripheralBase) & (uint32_t)(~(uint32_t)FTM_SYNCONF_HWOM_MASK))) | ( \
      (uint32_t)((uint32_t)(State) << FTM_SYNCONF_HWOM_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SetHWTriggerWRBUF
   ---------------------------------------------------------------------------- */

/**
 * @brief A hardware trigger activates MOD, CNTIN, and CV registers
 * synchronization.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of the HW trigger. This parameter is of "Global
 *        enumeration used for specifying general enable/disable states
 *        (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTM0_SYNCONF,
 *          FTM1_SYNCONF, FTM2_SYNCONF, FTM3_SYNCONF (depending on the peripheral).
 * @par Example:
 *      @code
 *      FTM_PDD_SetHWTriggerWRBUF(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define FTM_PDD_SetHWTriggerWRBUF(PeripheralBase, State) ( \
    FTM_SYNCONF_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       FTM_SYNCONF_REG(PeripheralBase)) & ( \
       (uint32_t)(~(uint32_t)FTM_SYNCONF_HWWRBUF_MASK)))) | ( \
      (uint32_t)((uint32_t)(State) << FTM_SYNCONF_HWWRBUF_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SetHWTriggerRSTCNT
   ---------------------------------------------------------------------------- */

/**
 * @brief A hardware trigger activates the FTM counter synchronization.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of the HW trigger. This parameter is of "Global
 *        enumeration used for specifying general enable/disable states
 *        (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTM0_SYNCONF,
 *          FTM1_SYNCONF, FTM2_SYNCONF, FTM3_SYNCONF (depending on the peripheral).
 * @par Example:
 *      @code
 *      FTM_PDD_SetHWTriggerRSTCNT(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define FTM_PDD_SetHWTriggerRSTCNT(PeripheralBase, State) ( \
    FTM_SYNCONF_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       FTM_SYNCONF_REG(PeripheralBase)) & ( \
       (uint32_t)(~(uint32_t)FTM_SYNCONF_HWRSTCNT_MASK)))) | ( \
      (uint32_t)((uint32_t)(State) << FTM_SYNCONF_HWRSTCNT_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SetSWTriggerSWOCTRL
   ---------------------------------------------------------------------------- */

/**
 * @brief The software trigger activates the SWOCTRL register synchronization.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of the SW trigger. This parameter is of "Global
 *        enumeration used for specifying general enable/disable states
 *        (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTM0_SYNCONF,
 *          FTM1_SYNCONF, FTM2_SYNCONF, FTM3_SYNCONF (depending on the peripheral).
 * @par Example:
 *      @code
 *      FTM_PDD_SetSWTriggerSWOCTRL(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define FTM_PDD_SetSWTriggerSWOCTRL(PeripheralBase, State) ( \
    FTM_SYNCONF_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       FTM_SYNCONF_REG(PeripheralBase)) & ( \
       (uint32_t)(~(uint32_t)FTM_SYNCONF_SWSOC_MASK)))) | ( \
      (uint32_t)((uint32_t)(State) << FTM_SYNCONF_SWSOC_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SetSWTriggerINVCTRL
   ---------------------------------------------------------------------------- */

/**
 * @brief The software trigger activates the INVCTRL register synchronization.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of the SW trigger. This parameter is of "Global
 *        enumeration used for specifying general enable/disable states
 *        (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTM0_SYNCONF,
 *          FTM1_SYNCONF, FTM2_SYNCONF, FTM3_SYNCONF (depending on the peripheral).
 * @par Example:
 *      @code
 *      FTM_PDD_SetSWTriggerINVCTRL(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define FTM_PDD_SetSWTriggerINVCTRL(PeripheralBase, State) ( \
    FTM_SYNCONF_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       FTM_SYNCONF_REG(PeripheralBase)) & ( \
       (uint32_t)(~(uint32_t)FTM_SYNCONF_SWINVC_MASK)))) | ( \
      (uint32_t)((uint32_t)(State) << FTM_SYNCONF_SWINVC_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SetSWTriggerOUTMASK
   ---------------------------------------------------------------------------- */

/**
 * @brief The software trigger activates the OUTMASK register synchronization.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of the SW trigger. This parameter is of "Global
 *        enumeration used for specifying general enable/disable states
 *        (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTM0_SYNCONF,
 *          FTM1_SYNCONF, FTM2_SYNCONF, FTM3_SYNCONF (depending on the peripheral).
 * @par Example:
 *      @code
 *      FTM_PDD_SetSWTriggerOUTMASK(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define FTM_PDD_SetSWTriggerOUTMASK(PeripheralBase, State) ( \
    FTM_SYNCONF_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(FTM_SYNCONF_REG(PeripheralBase) & (uint32_t)(~(uint32_t)FTM_SYNCONF_SWOM_MASK))) | ( \
      (uint32_t)((uint32_t)(State) << FTM_SYNCONF_SWOM_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SetSWTriggerWRBUF
   ---------------------------------------------------------------------------- */

/**
 * @brief The software trigger activates MOD, CNTIN, and CV registers
 * synchronization.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of the SW trigger. This parameter is of "Global
 *        enumeration used for specifying general enable/disable states
 *        (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTM0_SYNCONF,
 *          FTM1_SYNCONF, FTM2_SYNCONF, FTM3_SYNCONF (depending on the peripheral).
 * @par Example:
 *      @code
 *      FTM_PDD_SetSWTriggerWRBUF(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define FTM_PDD_SetSWTriggerWRBUF(PeripheralBase, State) ( \
    FTM_SYNCONF_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       FTM_SYNCONF_REG(PeripheralBase)) & ( \
       (uint32_t)(~(uint32_t)FTM_SYNCONF_SWWRBUF_MASK)))) | ( \
      (uint32_t)((uint32_t)(State) << FTM_SYNCONF_SWWRBUF_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SetSWTriggerRSTCNT
   ---------------------------------------------------------------------------- */

/**
 * @brief The software trigger activates the FTM counter synchronization.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of the SW trigger. This parameter is of "Global
 *        enumeration used for specifying general enable/disable states
 *        (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTM0_SYNCONF,
 *          FTM1_SYNCONF, FTM2_SYNCONF, FTM3_SYNCONF (depending on the peripheral).
 * @par Example:
 *      @code
 *      FTM_PDD_SetSWTriggerRSTCNT(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define FTM_PDD_SetSWTriggerRSTCNT(PeripheralBase, State) ( \
    FTM_SYNCONF_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       FTM_SYNCONF_REG(PeripheralBase)) & ( \
       (uint32_t)(~(uint32_t)FTM_SYNCONF_SWRSTCNT_MASK)))) | ( \
      (uint32_t)((uint32_t)(State) << FTM_SYNCONF_SWRSTCNT_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SelectSynchronizationMode
   ---------------------------------------------------------------------------- */

/**
 * @brief Selects the PWM synchronization mode.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mode New value of the synchronization mode. This parameter is of
 *        "Synchronization mode constants." type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTM0_SYNCONF,
 *          FTM1_SYNCONF, FTM2_SYNCONF, FTM3_SYNCONF (depending on the peripheral).
 * @par Example:
 *      @code
 *      FTM_PDD_SelectSynchronizationMode(<peripheral>_BASE_PTR,
 *      FTM_PDD_SYNC_LEGACY);
 *      @endcode
 */
#define FTM_PDD_SelectSynchronizationMode(PeripheralBase, Mode) ( \
    FTM_SYNCONF_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       FTM_SYNCONF_REG(PeripheralBase)) & ( \
       (uint32_t)(~(uint32_t)FTM_SYNCONF_SYNCMODE_MASK)))) | ( \
      (uint32_t)(Mode))) \
  )

/* ----------------------------------------------------------------------------
   -- SelectSWOCTRLSynchronization
   ---------------------------------------------------------------------------- */

/**
 * @brief Selects SWOCTRL register synchronization.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mode New value of the SWOCTRL synchronization. This parameter is of
 *        "Register synchronization constants." type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTM0_SYNCONF,
 *          FTM1_SYNCONF, FTM2_SYNCONF, FTM3_SYNCONF (depending on the peripheral).
 * @par Example:
 *      @code
 *      FTM_PDD_SelectSWOCTRLSynchronization(<peripheral>_BASE_PTR,
 *      FTM_PDD_SYNC_BY_SYSTEM_CLOCK);
 *      @endcode
 */
#define FTM_PDD_SelectSWOCTRLSynchronization(PeripheralBase, Mode) ( \
    FTM_SYNCONF_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(FTM_SYNCONF_REG(PeripheralBase) & (uint32_t)(~(uint32_t)FTM_SYNCONF_SWOC_MASK))) | ( \
      (uint32_t)((uint32_t)(Mode) << FTM_SYNCONF_SWOC_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SelectINVCTRLSynchronization
   ---------------------------------------------------------------------------- */

/**
 * @brief Selects INVCTRL register synchronization.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mode New value of the INVCTRL synchronization. This parameter is of
 *        "Register synchronization constants." type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTM0_SYNCONF,
 *          FTM1_SYNCONF, FTM2_SYNCONF, FTM3_SYNCONF (depending on the peripheral).
 * @par Example:
 *      @code
 *      FTM_PDD_SelectINVCTRLSynchronization(<peripheral>_BASE_PTR,
 *      FTM_PDD_SYNC_BY_SYSTEM_CLOCK);
 *      @endcode
 */
#define FTM_PDD_SelectINVCTRLSynchronization(PeripheralBase, Mode) ( \
    FTM_SYNCONF_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(FTM_SYNCONF_REG(PeripheralBase) & (uint32_t)(~(uint32_t)FTM_SYNCONF_INVC_MASK))) | ( \
      (uint32_t)((uint32_t)(Mode) << FTM_SYNCONF_INVC_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SelectCNTINSynchronization
   ---------------------------------------------------------------------------- */

/**
 * @brief Selects CNTIN register synchronization.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mode New value of the CNTIN synchronization. This parameter is of
 *        "Register synchronization constants." type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTM0_SYNCONF,
 *          FTM1_SYNCONF, FTM2_SYNCONF, FTM3_SYNCONF (depending on the peripheral).
 * @par Example:
 *      @code
 *      FTM_PDD_SelectCNTINSynchronization(<peripheral>_BASE_PTR,
 *      FTM_PDD_SYNC_BY_SYSTEM_CLOCK);
 *      @endcode
 */
#define FTM_PDD_SelectCNTINSynchronization(PeripheralBase, Mode) ( \
    FTM_SYNCONF_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       FTM_SYNCONF_REG(PeripheralBase)) & ( \
       (uint32_t)(~(uint32_t)FTM_SYNCONF_CNTINC_MASK)))) | ( \
      (uint32_t)((uint32_t)(Mode) << FTM_SYNCONF_CNTINC_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SetHardwareTriggerMode
   ---------------------------------------------------------------------------- */

/**
 * @brief The FTM clears the TRIGj bit when the hardware trigger j is detected,
 * where j = 0, 1,2.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of the hardware trigger mode. This parameter is
 *        of "Global enumeration used for specifying general enable/disable
 *        states (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTM0_SYNCONF,
 *          FTM1_SYNCONF, FTM2_SYNCONF, FTM3_SYNCONF (depending on the peripheral).
 * @par Example:
 *      @code
 *      FTM_PDD_SetHardwareTriggerMode(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define FTM_PDD_SetHardwareTriggerMode(PeripheralBase, State) ( \
    ((State) == PDD_DISABLE) ? ( \
      FTM_SYNCONF_REG(PeripheralBase) |= \
       FTM_SYNCONF_HWTRIGMODE_MASK) : ( \
      FTM_SYNCONF_REG(PeripheralBase) &= \
       (uint32_t)(~(uint32_t)FTM_SYNCONF_HWTRIGMODE_MASK)) \
  )

/* ----------------------------------------------------------------------------
   -- SetPairChannels3Inverting
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables the pair channels 3 inverting.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of the pair channels 3 inverting. This parameter
 *        is of "Global enumeration used for specifying general enable/disable
 *        states (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTM0_INVCTRL,
 *          FTM1_INVCTRL, FTM2_INVCTRL, FTM3_INVCTRL (depending on the peripheral).
 * @par Example:
 *      @code
 *      FTM_PDD_SetPairChannels3Inverting(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define FTM_PDD_SetPairChannels3Inverting(PeripheralBase, State) ( \
    FTM_INVCTRL_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       FTM_INVCTRL_REG(PeripheralBase)) & ( \
       (uint32_t)(~(uint32_t)FTM_INVCTRL_INV3EN_MASK)))) | ( \
      (uint32_t)((uint32_t)(State) << FTM_INVCTRL_INV3EN_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SetPairChannels2Inverting
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables the pair channels 2 inverting.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of the pair channels 2 inverting. This parameter
 *        is of "Global enumeration used for specifying general enable/disable
 *        states (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTM0_INVCTRL,
 *          FTM1_INVCTRL, FTM2_INVCTRL, FTM3_INVCTRL (depending on the peripheral).
 * @par Example:
 *      @code
 *      FTM_PDD_SetPairChannels2Inverting(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define FTM_PDD_SetPairChannels2Inverting(PeripheralBase, State) ( \
    FTM_INVCTRL_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       FTM_INVCTRL_REG(PeripheralBase)) & ( \
       (uint32_t)(~(uint32_t)FTM_INVCTRL_INV2EN_MASK)))) | ( \
      (uint32_t)((uint32_t)(State) << FTM_INVCTRL_INV2EN_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SetPairChannels1Inverting
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables the pair channels 1 inverting.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of the pair channels 1 inverting. This parameter
 *        is of "Global enumeration used for specifying general enable/disable
 *        states (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTM0_INVCTRL,
 *          FTM1_INVCTRL, FTM2_INVCTRL, FTM3_INVCTRL (depending on the peripheral).
 * @par Example:
 *      @code
 *      FTM_PDD_SetPairChannels1Inverting(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define FTM_PDD_SetPairChannels1Inverting(PeripheralBase, State) ( \
    FTM_INVCTRL_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       FTM_INVCTRL_REG(PeripheralBase)) & ( \
       (uint32_t)(~(uint32_t)FTM_INVCTRL_INV1EN_MASK)))) | ( \
      (uint32_t)((uint32_t)(State) << FTM_INVCTRL_INV1EN_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SetPairChannels0Inverting
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables the pair channels 0 inverting.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of the pair channels 0 inverting. This parameter
 *        is of "Global enumeration used for specifying general enable/disable
 *        states (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTM0_INVCTRL,
 *          FTM1_INVCTRL, FTM2_INVCTRL, FTM3_INVCTRL (depending on the peripheral).
 * @par Example:
 *      @code
 *      FTM_PDD_SetPairChannels0Inverting(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define FTM_PDD_SetPairChannels0Inverting(PeripheralBase, State) ( \
    FTM_INVCTRL_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       FTM_INVCTRL_REG(PeripheralBase)) & ( \
       (uint32_t)(~(uint32_t)FTM_INVCTRL_INV0EN_MASK)))) | ( \
      (uint32_t)(State))) \
  )
#endif  /* #if defined(FTM_PDD_H_) */

/* FTM_PDD.h, eof. */
