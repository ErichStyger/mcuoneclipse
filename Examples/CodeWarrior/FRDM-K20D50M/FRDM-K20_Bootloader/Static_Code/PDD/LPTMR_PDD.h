/*
  PDD layer implementation for peripheral type LPTMR
  (C) 2013 Freescale, Inc. All rights reserved.

  This file is static and it is generated from API-Factory
*/

#if !defined(LPTMR_PDD_H_)
#define LPTMR_PDD_H_

/* ----------------------------------------------------------------------------
   -- Test if supported MCU is active
   ---------------------------------------------------------------------------- */

#if !defined(MCU_ACTIVE)
  // No MCU is active
  #error LPTMR PDD library: No derivative is active. Place proper #include with PDD memory map before including PDD library.
#elif \
      !defined(MCU_MK10D10) /* LPTMR0 */ && \
      !defined(MCU_MK10D5) /* LPTMR0 */ && \
      !defined(MCU_MK10D7) /* LPTMR0 */ && \
      !defined(MCU_MK10F12) /* LPTMR0 */ && \
      !defined(MCU_MK10DZ10) /* LPTMR0 */ && \
      !defined(MCU_MK11D5) /* LPTMR0 */ && \
      !defined(MCU_MK11D5WS) /* LPTMR0 */ && \
      !defined(MCU_MK12D5) /* LPTMR0 */ && \
      !defined(MCU_MK20D10) /* LPTMR0 */ && \
      !defined(MCU_MK20D5) /* LPTMR0 */ && \
      !defined(MCU_MK20D7) /* LPTMR0 */ && \
      !defined(MCU_MK20F12) /* LPTMR0 */ && \
      !defined(MCU_MK20DZ10) /* LPTMR0 */ && \
      !defined(MCU_MK21D5) /* LPTMR0 */ && \
      !defined(MCU_MK21D5WS) /* LPTMR0 */ && \
      !defined(MCU_MK21F12) /* LPTMR0 */ && \
      !defined(MCU_MK21F12WS) /* LPTMR0 */ && \
      !defined(MCU_MK22D5) /* LPTMR0 */ && \
      !defined(MCU_MK22F12810) /* LPTMR0 */ && \
      !defined(MCU_MK22F12) /* LPTMR0 */ && \
      !defined(MCU_MK22F25612) /* LPTMR0 */ && \
      !defined(MCU_MK22F51212) /* LPTMR0 */ && \
      !defined(MCU_MK24F12) /* LPTMR0 */ && \
      !defined(MCU_MK30D10) /* LPTMR0 */ && \
      !defined(MCU_MK30D7) /* LPTMR0 */ && \
      !defined(MCU_MK30DZ10) /* LPTMR0 */ && \
      !defined(MCU_MK40D10) /* LPTMR0 */ && \
      !defined(MCU_MK40D7) /* LPTMR0 */ && \
      !defined(MCU_MK40DZ10) /* LPTMR0 */ && \
      !defined(MCU_MK40X256VMD100) /* LPTMR0 */ && \
      !defined(MCU_MK50D10) /* LPTMR0 */ && \
      !defined(MCU_MK50D7) /* LPTMR0 */ && \
      !defined(MCU_MK50DZ10) /* LPTMR0 */ && \
      !defined(MCU_MK51D10) /* LPTMR0 */ && \
      !defined(MCU_MK51D7) /* LPTMR0 */ && \
      !defined(MCU_MK51DZ10) /* LPTMR0 */ && \
      !defined(MCU_MK52D10) /* LPTMR0 */ && \
      !defined(MCU_MK52DZ10) /* LPTMR0 */ && \
      !defined(MCU_MK53D10) /* LPTMR0 */ && \
      !defined(MCU_MK53DZ10) /* LPTMR0 */ && \
      !defined(MCU_MK60D10) /* LPTMR0 */ && \
      !defined(MCU_MK60F12) /* LPTMR0 */ && \
      !defined(MCU_MK60F15) /* LPTMR0 */ && \
      !defined(MCU_MK60DZ10) /* LPTMR0 */ && \
      !defined(MCU_MK60N512VMD100) /* LPTMR0 */ && \
      !defined(MCU_MK61F12) /* LPTMR0 */ && \
      !defined(MCU_MK61F15) /* LPTMR0 */ && \
      !defined(MCU_MK61F12WS) /* LPTMR0 */ && \
      !defined(MCU_MK61F15WS) /* LPTMR0 */ && \
      !defined(MCU_MK63F12) /* LPTMR0 */ && \
      !defined(MCU_MK63F12WS) /* LPTMR0 */ && \
      !defined(MCU_MK64F12) /* LPTMR0 */ && \
      !defined(MCU_MK65F18) /* LPTMR0 */ && \
      !defined(MCU_MK65F18WS) /* LPTMR0 */ && \
      !defined(MCU_MK66F18) /* LPTMR0 */ && \
      !defined(MCU_MK70F12) /* LPTMR0 */ && \
      !defined(MCU_MK70F15) /* LPTMR0 */ && \
      !defined(MCU_MK70F12WS) /* LPTMR0 */ && \
      !defined(MCU_MK70F15WS) /* LPTMR0 */ && \
      !defined(MCU_MKL02Z4) /* LPTMR0 */ && \
      !defined(MCU_MKL03Z4) /* LPTMR0 */ && \
      !defined(MCU_MKL04Z4) /* LPTMR0 */ && \
      !defined(MCU_MKL05Z4) /* LPTMR0 */ && \
      !defined(MCU_MKL14Z4) /* LPTMR0 */ && \
      !defined(MCU_MKL15Z4) /* LPTMR0 */ && \
      !defined(MCU_MKL16Z4) /* LPTMR0 */ && \
      !defined(MCU_MKL24Z4) /* LPTMR0 */ && \
      !defined(MCU_MKL25Z4) /* LPTMR0 */ && \
      !defined(MCU_MKL26Z4) /* LPTMR0 */ && \
      !defined(MCU_MKL34Z4) /* LPTMR0 */ && \
      !defined(MCU_MKL36Z4) /* LPTMR0 */ && \
      !defined(MCU_MKL46Z4) /* LPTMR0 */ && \
      !defined(MCU_MKV10Z7) /* LPTMR0 */ && \
      !defined(MCU_MKV31F12810) /* LPTMR0 */ && \
      !defined(MCU_MKV31F25612) /* LPTMR0 */ && \
      !defined(MCU_MKV31F51212) /* LPTMR0 */ && \
      !defined(MCU_MKW01Z4) /* LPTMR0 */ && \
      !defined(MCU_MKW21D5) /* LPTMR0 */ && \
      !defined(MCU_MKW21D5WS) /* LPTMR0 */ && \
      !defined(MCU_MKW22D5) /* LPTMR0 */ && \
      !defined(MCU_MKW22D5WS) /* LPTMR0 */ && \
      !defined(MCU_MKW24D5) /* LPTMR0 */ && \
      !defined(MCU_MKW24D5WS) /* LPTMR0 */ && \
      !defined(MCU_PCK20L4) /* LPTMR0 */
  // Unsupported MCU is active
  #error LPTMR PDD library: Unsupported derivative is active.
#endif

#include "PDD_Types.h"

/* ----------------------------------------------------------------------------
   -- Method symbol definitions
   ---------------------------------------------------------------------------- */

/* Enable freerun constants */
#define LPTMR_PDD_RESTART_ENABLED  0U            /**< Enabled */
#define LPTMR_PDD_RESTART_DISABLED LPTMR_CSR_TFC_MASK /**< Disabled */

/* Timer mode constants */
#define LPTMR_PDD_SOURCE_INTERNAL 0U             /**< Internal */
#define LPTMR_PDD_SOURCE_EXTERNAL LPTMR_CSR_TMS_MASK /**< External */

/* Prescaler/Filter constants */
#define LPTMR_PDD_PRESCALER_2     0U             /**< 2 */
#define LPTMR_PDD_PRESCALER_4     0x1U           /**< 4 */
#define LPTMR_PDD_PRESCALER_8     0x2U           /**< 8 */
#define LPTMR_PDD_PRESCALER_16    0x3U           /**< 16 */
#define LPTMR_PDD_PRESCALER_32    0x4U           /**< 32 */
#define LPTMR_PDD_PRESCALER_64    0x5U           /**< 64 */
#define LPTMR_PDD_PRESCALER_128   0x6U           /**< 128 */
#define LPTMR_PDD_PRESCALER_256   0x7U           /**< 256 */
#define LPTMR_PDD_PRESCALER_512   0x8U           /**< 512 */
#define LPTMR_PDD_PRESCALER_1024  0x9U           /**< 1024 */
#define LPTMR_PDD_PRESCALER_2048  0xAU           /**< 2048 */
#define LPTMR_PDD_PRESCALER_4096  0xBU           /**< 4096 */
#define LPTMR_PDD_PRESCALER_8192  0xCU           /**< 8192 */
#define LPTMR_PDD_PRESCALER_16384 0xDU           /**< 16384 */
#define LPTMR_PDD_PRESCALER_32768 0xEU           /**< 32768 */
#define LPTMR_PDD_PRESCALER_65536 0xFU           /**< 65536 */
#define LPTMR_PDD_FILTER_2        0x1U           /**< 2 */
#define LPTMR_PDD_FILTER_4        0x2U           /**< 4 */
#define LPTMR_PDD_FILTER_8        0x3U           /**< 8 */
#define LPTMR_PDD_FILTER_16       0x4U           /**< 16 */
#define LPTMR_PDD_FILTER_32       0x5U           /**< 32 */
#define LPTMR_PDD_FILTER_64       0x6U           /**< 64 */
#define LPTMR_PDD_FILTER_128      0x7U           /**< 128 */
#define LPTMR_PDD_FILTER_256      0x8U           /**< 256 */
#define LPTMR_PDD_FILTER_512      0x9U           /**< 512 */
#define LPTMR_PDD_FILTER_1024     0xAU           /**< 1024 */
#define LPTMR_PDD_FILTER_2048     0xBU           /**< 2048 */
#define LPTMR_PDD_FILTER_4096     0xCU           /**< 4096 */
#define LPTMR_PDD_FILTER_8192     0xDU           /**< 8192 */
#define LPTMR_PDD_FILTER_16384    0xEU           /**< 16384 */
#define LPTMR_PDD_FILTER_32768    0xFU           /**< 32768 */

/* Divider constants */
#define LPTMR_PDD_DIVIDER_1     0x1U             /**< 1 */
#define LPTMR_PDD_DIVIDER_2     0U               /**< 2 */
#define LPTMR_PDD_DIVIDER_4     0x2U             /**< 4 */
#define LPTMR_PDD_DIVIDER_8     0x4U             /**< 8 */
#define LPTMR_PDD_DIVIDER_16    0x6U             /**< 16 */
#define LPTMR_PDD_DIVIDER_32    0x8U             /**< 32 */
#define LPTMR_PDD_DIVIDER_64    0xAU             /**< 64 */
#define LPTMR_PDD_DIVIDER_128   0xCU             /**< 128 */
#define LPTMR_PDD_DIVIDER_256   0xEU             /**< 256 */
#define LPTMR_PDD_DIVIDER_512   0x10U            /**< 512 */
#define LPTMR_PDD_DIVIDER_1024  0x12U            /**< 1024 */
#define LPTMR_PDD_DIVIDER_2048  0x14U            /**< 2048 */
#define LPTMR_PDD_DIVIDER_4096  0x16U            /**< 4096 */
#define LPTMR_PDD_DIVIDER_8192  0x18U            /**< 8192 */
#define LPTMR_PDD_DIVIDER_16384 0x1AU            /**< 16384 */
#define LPTMR_PDD_DIVIDER_32768 0x1CU            /**< 32768 */
#define LPTMR_PDD_DIVIDER_65536 0x1EU            /**< 65536 */

/* Timer Pin Select constants. */
#define LPTMR_PDD_HSCMP 0U                       /**< Alt 0 */
#define LPTMR_PDD_PIN_1 0x10U                    /**< Alt 1 */
#define LPTMR_PDD_PIN_2 0x20U                    /**< Alt 2 */
#define LPTMR_PDD_PIN_3 0x30U                    /**< Alt 3 */

/* Timer Pin Polarity constants. */
#define LPTMR_PDD_POLARITY_RISING  0U            /**< Rising */
#define LPTMR_PDD_POLARITY_FALLING 0x8U          /**< Falling */

/* Prescaler bypass constants. */
#define LPTMR_PDD_BYPASS_DISABLED 0U             /**< Disabled */
#define LPTMR_PDD_BYPASS_ENABLED  0x4U           /**< Enabled */

/* Clock source constants. */
#define LPTMR_PDD_SOURCE_INTREF   0U             /**< Internal reference clock */
#define LPTMR_PDD_SOURCE_LPO1KHZ  0x1U           /**< Low power oscillator clock */
#define LPTMR_PDD_SOURCE_EXT32KHZ 0x2U           /**< External 32 kHz clock */
#define LPTMR_PDD_SOURCE_EXTREF   0x3U           /**< External reference clock */


/* ----------------------------------------------------------------------------
   -- GetInterruptMask
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns interrupt mask.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: LPTMR0_CSR.
 * @par Example:
 *      @code
 *      uint32_t result = LPTMR_PDD_GetInterruptMask(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define LPTMR_PDD_GetInterruptMask(PeripheralBase) ( \
    (uint32_t)(LPTMR_CSR_REG(PeripheralBase) & LPTMR_CSR_TIE_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- GetInterruptFlag
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns interrupt flag bit.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: LPTMR0_CSR.
 * @par Example:
 *      @code
 *      uint32_t result = LPTMR_PDD_GetInterruptFlag(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define LPTMR_PDD_GetInterruptFlag(PeripheralBase) ( \
    (uint32_t)(LPTMR_CSR_REG(PeripheralBase) & LPTMR_CSR_TCF_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- EnableInterrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables the LPT interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: LPTMR0_CSR.
 * @par Example:
 *      @code
 *      LPTMR_PDD_EnableInterrupt(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define LPTMR_PDD_EnableInterrupt(PeripheralBase) ( \
    LPTMR_CSR_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(LPTMR_CSR_REG(PeripheralBase) | LPTMR_CSR_TIE_MASK)) & ( \
      (uint32_t)(~(uint32_t)LPTMR_CSR_TCF_MASK))) \
  )

/* ----------------------------------------------------------------------------
   -- DisableInterrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Disables the LPT interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: LPTMR0_CSR.
 * @par Example:
 *      @code
 *      LPTMR_PDD_DisableInterrupt(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define LPTMR_PDD_DisableInterrupt(PeripheralBase) ( \
    LPTMR_CSR_REG(PeripheralBase) &= \
     (uint32_t)(( \
      (uint32_t)(~(uint32_t)LPTMR_CSR_TIE_MASK)) & ( \
      (uint32_t)(~(uint32_t)LPTMR_CSR_TCF_MASK))) \
  )

/* ----------------------------------------------------------------------------
   -- ClearInterruptFlag
   ---------------------------------------------------------------------------- */

/**
 * @brief Clears LPT interrupt flag.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: LPTMR0_CSR.
 * @par Example:
 *      @code
 *      LPTMR_PDD_ClearInterruptFlag(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define LPTMR_PDD_ClearInterruptFlag(PeripheralBase) ( \
    LPTMR_CSR_REG(PeripheralBase) |= \
     LPTMR_CSR_TCF_MASK \
  )

/* ----------------------------------------------------------------------------
   -- SelectPin
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets Timer Pin Select bits.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param TPS_val New value of the TPS. This parameter is of "Timer Pin Select
 *        constants." type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: LPTMR0_CSR.
 * @par Example:
 *      @code
 *      LPTMR_PDD_SelectPin(<peripheral>_BASE_PTR, LPTMR_PDD_HSCMP);
 *      @endcode
 */
#define LPTMR_PDD_SelectPin(PeripheralBase, TPS_val) ( \
    LPTMR_CSR_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       LPTMR_CSR_REG(PeripheralBase)) & (( \
       (uint32_t)(~(uint32_t)LPTMR_CSR_TPS_MASK)) & ( \
       (uint32_t)(~(uint32_t)LPTMR_CSR_TCF_MASK))))) | ( \
      (uint32_t)(TPS_val))) \
  )

/* ----------------------------------------------------------------------------
   -- SetPinPolarity
   ---------------------------------------------------------------------------- */

/**
 * @brief Configures the polarity of the input source.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Edge New value of the polarity. This parameter is of "Timer Pin
 *        Polarity constants." type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: LPTMR0_CSR.
 * @par Example:
 *      @code
 *      LPTMR_PDD_SetPinPolarity(<peripheral>_BASE_PTR,
 *      LPTMR_PDD_POLARITY_RISING);
 *      @endcode
 */
#define LPTMR_PDD_SetPinPolarity(PeripheralBase, Edge) ( \
    LPTMR_CSR_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       LPTMR_CSR_REG(PeripheralBase)) & (( \
       (uint32_t)(~(uint32_t)LPTMR_CSR_TPP_MASK)) & ( \
       (uint32_t)(~(uint32_t)LPTMR_CSR_TCF_MASK))))) | ( \
      (uint32_t)(Edge))) \
  )

/* ----------------------------------------------------------------------------
   -- EnableFreerun
   ---------------------------------------------------------------------------- */

/**
 * @brief Configures the freerun mode.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Restart New value of the restart. Use constants from group "Enable
 *        freerun constants". This parameter is 32 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: LPTMR0_CSR.
 * @par Example:
 *      @code
 *      LPTMR_PDD_EnableFreerun(<peripheral>_BASE_PTR,
 *      LPTMR_PDD_RESTART_ENABLED);
 *      @endcode
 */
#define LPTMR_PDD_EnableFreerun(PeripheralBase, Restart) ( \
    LPTMR_CSR_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       LPTMR_CSR_REG(PeripheralBase)) & (( \
       (uint32_t)(~(uint32_t)LPTMR_CSR_TFC_MASK)) & ( \
       (uint32_t)(~(uint32_t)LPTMR_CSR_TCF_MASK))))) | ( \
      (uint32_t)(Restart))) \
  )

/* ----------------------------------------------------------------------------
   -- SetTimerMode
   ---------------------------------------------------------------------------- */

/**
 * @brief Selects timer mode.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Source New value of the source. Use constants from group "Timer mode
 *        constants". This parameter is 32 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: LPTMR0_CSR.
 * @par Example:
 *      @code
 *      LPTMR_PDD_SetTimerMode(<peripheral>_BASE_PTR,
 *      LPTMR_PDD_SOURCE_INTERNAL);
 *      @endcode
 */
#define LPTMR_PDD_SetTimerMode(PeripheralBase, Source) ( \
    LPTMR_CSR_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       LPTMR_CSR_REG(PeripheralBase)) & (( \
       (uint32_t)(~(uint32_t)LPTMR_CSR_TMS_MASK)) & ( \
       (uint32_t)(~(uint32_t)LPTMR_CSR_TCF_MASK))))) | ( \
      (uint32_t)(Source))) \
  )

/* ----------------------------------------------------------------------------
   -- EnableDevice
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables the LPT device.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of LPT device. This parameter is of "Global
 *        enumeration used for specifying general enable/disable states (PDD_DISABLE
 *        and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: LPTMR0_CSR.
 * @par Example:
 *      @code
 *      LPTMR_PDD_EnableDevice(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define LPTMR_PDD_EnableDevice(PeripheralBase, State) ( \
    LPTMR_CSR_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       LPTMR_CSR_REG(PeripheralBase)) & (( \
       (uint32_t)(~(uint32_t)LPTMR_CSR_TEN_MASK)) & ( \
       (uint32_t)(~(uint32_t)LPTMR_CSR_TCF_MASK))))) | ( \
      (uint32_t)(State))) \
  )

/* ----------------------------------------------------------------------------
   -- GetEnableDeviceStatus
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns current state of LPT device.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: LPTMR0_CSR.
 * @par Example:
 *      @code
 *      uint32_t result =
 *      LPTMR_PDD_GetEnableDeviceStatus(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define LPTMR_PDD_GetEnableDeviceStatus(PeripheralBase) ( \
    (uint32_t)(LPTMR_CSR_REG(PeripheralBase) & LPTMR_CSR_TEN_MASK) \
  )

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
 *        "Prescaler/Filter constants". This parameter is 4 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: LPTMR0_PSR.
 * @par Example:
 *      @code
 *      LPTMR_PDD_SetPrescaler(<peripheral>_BASE_PTR, LPTMR_PDD_PRESCALER_2);
 *      @endcode
 */
#define LPTMR_PDD_SetPrescaler(PeripheralBase, Prescaler) ( \
    LPTMR_PSR_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(LPTMR_PSR_REG(PeripheralBase) & (uint32_t)(~(uint32_t)LPTMR_PSR_PRESCALE_MASK))) | ( \
      (uint32_t)((uint32_t)(Prescaler) << LPTMR_PSR_PRESCALE_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- EnablePrescalerBypass
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets prescaler bypass.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Bypass New value of the bypass. This parameter is of "Prescaler bypass
 *        constants." type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: LPTMR0_PSR.
 * @par Example:
 *      @code
 *      LPTMR_PDD_EnablePrescalerBypass(<peripheral>_BASE_PTR,
 *      LPTMR_PDD_BYPASS_DISABLED);
 *      @endcode
 */
#define LPTMR_PDD_EnablePrescalerBypass(PeripheralBase, Bypass) ( \
    LPTMR_PSR_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(LPTMR_PSR_REG(PeripheralBase) & (uint32_t)(~(uint32_t)LPTMR_PSR_PBYP_MASK))) | ( \
      (uint32_t)(Bypass))) \
  )

/* ----------------------------------------------------------------------------
   -- SetDivider
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets both prescale value and bypass value.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Divider New value of the divider. Use constants from group "Divider
 *        constants". This parameter is 5 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: LPTMR0_PSR.
 * @par Example:
 *      @code
 *      LPTMR_PDD_SetDivider(<peripheral>_BASE_PTR, LPTMR_PDD_DIVIDER_1);
 *      @endcode
 */
#define LPTMR_PDD_SetDivider(PeripheralBase, Divider) ( \
    LPTMR_PSR_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       LPTMR_PSR_REG(PeripheralBase)) & (( \
       (uint32_t)(~(uint32_t)LPTMR_PSR_PRESCALE_MASK)) & ( \
       (uint32_t)(~(uint32_t)LPTMR_PSR_PBYP_MASK))))) | (( \
      (uint32_t)((uint32_t)((uint32_t)(Divider) >> 1U) << LPTMR_PSR_PRESCALE_SHIFT)) | ( \
      (uint32_t)((uint32_t)((uint32_t)(Divider) & 0x1U) << LPTMR_PSR_PBYP_SHIFT)))) \
  )

/* ----------------------------------------------------------------------------
   -- SelectPrescalerSource
   ---------------------------------------------------------------------------- */

/**
 * @brief Selects clock source.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Source New value of the source. This parameter is of "Clock source
 *        constants." type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: LPTMR0_PSR.
 * @par Example:
 *      @code
 *      LPTMR_PDD_SelectPrescalerSource(<peripheral>_BASE_PTR,
 *      LPTMR_PDD_SOURCE_INTREF);
 *      @endcode
 */
#define LPTMR_PDD_SelectPrescalerSource(PeripheralBase, Source) ( \
    LPTMR_PSR_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(LPTMR_PSR_REG(PeripheralBase) & (uint32_t)(~(uint32_t)LPTMR_PSR_PCS_MASK))) | ( \
      (uint32_t)(Source))) \
  )

/* ----------------------------------------------------------------------------
   -- WriteCompareReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes value to the compare register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value New content of the compare register. This parameter is a 32-bit
 *        value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: LPTMR0_CMR.
 * @par Example:
 *      @code
 *      LPTMR_PDD_WriteCompareReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define LPTMR_PDD_WriteCompareReg(PeripheralBase, Value) ( \
    LPTMR_CMR_REG(PeripheralBase) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadCompareReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the compare register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: LPTMR0_CMR.
 * @par Example:
 *      @code
 *      uint32_t result = LPTMR_PDD_ReadCompareReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define LPTMR_PDD_ReadCompareReg(PeripheralBase) ( \
    LPTMR_CMR_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- ReadCounterReg
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MK10DZ10)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60N512VMD100)))
/**
 * @brief Returns the content of the counter register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: LPTMR0_CNR.
 * @par Example:
 *      @code
 *      uint32_t result = LPTMR_PDD_ReadCounterReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define LPTMR_PDD_ReadCounterReg(PeripheralBase) ( \
      LPTMR_CNR_REG(PeripheralBase) \
    )
#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK52D10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK65F18)) || (defined(MCU_MK65F18WS)) || (defined(MCU_MK66F18)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKL02Z4)) || (defined(MCU_MKL03Z4)) || (defined(MCU_MKL04Z4)) || (defined(MCU_MKL05Z4)) || (defined(MCU_MKL14Z4)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL16Z4)) || (defined(MCU_MKL24Z4)) || (defined(MCU_MKL25Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL34Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW01Z4)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) || (defined(MCU_PCK20L4)) */
/**
 * @brief Returns the content of the counter register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: LPTMR0_CNR.
 * @par Example:
 *      @code
 *      uint32_t result = LPTMR_PDD_ReadCounterReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define LPTMR_PDD_ReadCounterReg(PeripheralBase) ( \
      (LPTMR_CNR_REG(PeripheralBase) = \
       0U), \
      LPTMR_CNR_REG(PeripheralBase) \
    )
#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK52D10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK65F18)) || (defined(MCU_MK65F18WS)) || (defined(MCU_MK66F18)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKL02Z4)) || (defined(MCU_MKL03Z4)) || (defined(MCU_MKL04Z4)) || (defined(MCU_MKL05Z4)) || (defined(MCU_MKL14Z4)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL16Z4)) || (defined(MCU_MKL24Z4)) || (defined(MCU_MKL25Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL34Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW01Z4)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) || (defined(MCU_PCK20L4)) */

/* ----------------------------------------------------------------------------
   -- WriteControlStatusReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes value to the control status register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value New content of the control status register. This parameter is a
 *        32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: LPTMR0_CSR.
 * @par Example:
 *      @code
 *      LPTMR_PDD_WriteControlStatusReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define LPTMR_PDD_WriteControlStatusReg(PeripheralBase, Value) ( \
    LPTMR_CSR_REG(PeripheralBase) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadControlStatusReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the control status register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: LPTMR0_CSR.
 * @par Example:
 *      @code
 *      uint32_t result = LPTMR_PDD_ReadControlStatusReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define LPTMR_PDD_ReadControlStatusReg(PeripheralBase) ( \
    LPTMR_CSR_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WritePrescaleReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes value to the prescale register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value New content of the prescale register. This parameter is a 32-bit
 *        value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: LPTMR0_PSR.
 * @par Example:
 *      @code
 *      LPTMR_PDD_WritePrescaleReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define LPTMR_PDD_WritePrescaleReg(PeripheralBase, Value) ( \
    LPTMR_PSR_REG(PeripheralBase) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadPrescaleReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the prescale register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: LPTMR0_PSR.
 * @par Example:
 *      @code
 *      uint32_t result = LPTMR_PDD_ReadPrescaleReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define LPTMR_PDD_ReadPrescaleReg(PeripheralBase) ( \
    LPTMR_PSR_REG(PeripheralBase) \
  )
#endif  /* #if defined(LPTMR_PDD_H_) */

/* LPTMR_PDD.h, eof. */
