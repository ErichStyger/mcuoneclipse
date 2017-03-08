/*
  PDD layer implementation for peripheral type LCD
  (C) 2013 Freescale, Inc. All rights reserved.

  This file is static and it is generated from API-Factory
*/

#if !defined(LCD_PDD_H_)
#define LCD_PDD_H_

/* ----------------------------------------------------------------------------
   -- Test if supported MCU is active
   ---------------------------------------------------------------------------- */

#if !defined(MCU_ACTIVE)
  // No MCU is active
  #error LCD PDD library: No derivative is active. Place proper #include with PDD memory map before including PDD library.
#elif \
      !defined(MCU_MK30D10) /* LCD */ && \
      !defined(MCU_MK30D7) /* LCD */ && \
      !defined(MCU_MK30DZ10) /* LCD */ && \
      !defined(MCU_MK40D10) /* LCD */ && \
      !defined(MCU_MK40D7) /* LCD */ && \
      !defined(MCU_MK40DZ10) /* LCD */ && \
      !defined(MCU_MK40X256VMD100) /* LCD */ && \
      !defined(MCU_MK51D10) /* LCD */ && \
      !defined(MCU_MK51D7) /* LCD */ && \
      !defined(MCU_MK51DZ10) /* LCD */ && \
      !defined(MCU_MK53D10) /* LCD */ && \
      !defined(MCU_MK53DZ10) /* LCD */ && \
      !defined(MCU_MKL34Z4) /* LCD */ && \
      !defined(MCU_MKL36Z4) /* LCD */ && \
      !defined(MCU_MKL46Z4) /* LCD */
  // Unsupported MCU is active
  #error LCD PDD library: Unsupported derivative is active.
#endif

#include "PDD_Types.h"

/* ----------------------------------------------------------------------------
   -- Method symbol definitions
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MKL34Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)))
/* Interrupt masks (for EnableInterrupts, DisableInterrupts macros). */
  #define LCD_PDD_FAULT_DETECT_COMPLETE LCD_GCR_FDCIEN_MASK /**< Fault detect complete interrupt mask */

#else /* (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) */
/* Interrupt masks (for EnableInterrupts, DisableInterrupts macros). */
  #define LCD_PDD_FRAME_FREQUENCY       LCD_GCR_LCDIEN_MASK /**< Frame frequency interrupt mask */
  #define LCD_PDD_FAULT_DETECT_COMPLETE LCD_GCR_FDCIEN_MASK /**< Fault detect complete interrupt mask */

#endif /* (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) */
/* Load adjust constants (for SetLoadAdjust macro). */
#define LCD_PDD_LOW_LOAD_RESISTOR_NET  0U        /**< Low load (LCD glass capacitance 2nF or lower), resistor net. */
#define LCD_PDD_HIGH_LOAD_RESISTOR_NET 0x1U      /**< High Load (LCD glass capacitance 8nF or lower), resistor net. */
#define LCD_PDD_FAST_CLK_CHPUMP_8NF    0x2U      /**< Fastest clock source for charge pump (LCD glass capacitance 8nF or lower). */
#define LCD_PDD_MIDDLE_CLK_CHPUMP_6NF  0x3U      /**< Intermediate clock source for charge pump (LCD glass capacitance 6nF or lower). */
#define LCD_PDD_MIDDLE_CLK_CHPUMP_4NF  0x4U      /**< Intermediate clock source for charge pump (LCD glass capacitance 4nF or lower). */
#define LCD_PDD_SLOW_CLK_CHPUMP_2NF    0x5U      /**< Slowest clock source for charge pump (LCD glass capacitance 2nF or lower). */

#if ((defined(MCU_MKL34Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)))
/* Voltage supply constants (for SetVoltageSupplyControl macro). */
  #define LCD_PDD_VLL3_FROM_VDD   0U               /**< Drive VLL3 internally from VDD. */
  #define LCD_PDD_VLL3_FROM_VIREG 0x1U             /**< Drive VLL3 externally from VDD or drive VLL1 internally from VIREG. */

#else /* (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) */
/* Voltage supply constants (for SetVoltageSupplyControl macro). */
  #define LCD_PDD_VLL2_FROM_VDD   0U               /**< Drive VLL2 internally from VDD. */
  #define LCD_PDD_VLL3_FROM_VDD   0x1U             /**< Drive VLL3 internally from VDD. */
  #define LCD_PDD_VLL3_FROM_VIREG 0x3U             /**< Drive VLL3 externally from VDD or drive VLL1 internally from VIREG. */

#endif /* (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) */
/* Alternate Clk divider constants (for SetAlternateClkDivider macro) */
#define LCD_PDD_DIVIDE_FACTOR_1   0U             /**< LCD alternate clock divider factor 1. */
#define LCD_PDD_DIVIDE_FACTOR_8   0x1U           /**< LCD alternate clock divider factor 8. */
#define LCD_PDD_DIVIDE_FACTOR_64  0x2U           /**< LCD alternate clock divider factor 64. */
#define LCD_PDD_DIVIDE_FACTOR_512 0x3U           /**< LCD alternate clock divider factor 512. */

/* Clock source constants (for SetClkSource macro). */
#define LCD_PDD_DEFAULT_CLK   0U                 /**< Default clock(system or RTC OSC output) as the LCD clock source. */
#define LCD_PDD_ALTERNATE_CLK 0x40U              /**< Alternate clock (e.g. MCGIRCLK output) as the LCD clock source. */

/* Blink mode constants (for SetBlinkMode macro). */
#define LCD_PDD_BLANK_BLINK     0U               /**< Blank during the blink period. */
#define LCD_PDD_ALTERNATE_BLINK 0x8U             /**< Alternate display during blink period. */

/* Fault detect clock prescaler constants (for SetFaultDetectClkPrescaler
   macro). */
#define LCD_PDD_FAULT_DETECT_PRESCALER_1   0U    /**< Fault detect clock prescaler 1. */
#define LCD_PDD_FAULT_DETECT_PRESCALER_2   0x1U  /**< Fault detect clock prescaler 2. */
#define LCD_PDD_FAULT_DETECT_PRESCALER_4   0x2U  /**< Fault detect clock prescaler 4. */
#define LCD_PDD_FAULT_DETECT_PRESCALER_8   0x3U  /**< Fault detect clock prescaler 8. */
#define LCD_PDD_FAULT_DETECT_PRESCALER_16  0x4U  /**< Fault detect clock prescaler 16. */
#define LCD_PDD_FAULT_DETECT_PRESCALER_32  0x5U  /**< Fault detect clock prescaler 32. */
#define LCD_PDD_FAULT_DETECT_PRESCALER_64  0x6U  /**< Fault detect clock prescaler 64. */
#define LCD_PDD_FAULT_DETECT_PRESCALER_128 0x7U  /**< Fault detect clock prescaler 128. */

/* Fault detect sample width constants (for SetFaultDetectSampleWidth macro). */
#define LCD_PDD_SAMPLE_WIDTH_CLK_4   0U          /**< Sample window width is 4 sample clock cycles. */
#define LCD_PDD_SAMPLE_WIDTH_CLK_8   0x1U        /**< Sample window width is 8 sample clock cycles. */
#define LCD_PDD_SAMPLE_WIDTH_CLK_16  0x2U        /**< Sample window width is 16 sample clock cycles. */
#define LCD_PDD_SAMPLE_WIDTH_CLK_32  0x3U        /**< Sample window width is 32 sample clock cycles. */
#define LCD_PDD_SAMPLE_WIDTH_CLK_64  0x4U        /**< Sample window width is 64 sample clock cycles. */
#define LCD_PDD_SAMPLE_WIDTH_CLK_128 0x5U        /**< Sample window width is 128 sample clock cycles. */
#define LCD_PDD_SAMPLE_WIDTH_CLK_256 0x6U        /**< Sample window width is 256 sample clock cycles. */
#define LCD_PDD_SAMPLE_WIDTH_CLK_512 0x7U        /**< Sample window width is 512 sample clock cycles. */

/* Pin type mode constants (for SetFaultDetectPinType macro). */
#define LCD_PDD_FAULT_FRONTPLANE 0U              /**< Type of the selected pin under fault detect test is frontplane. */
#define LCD_PDD_FAULT_BACKPLANE  0x40U           /**< Type of the selected pin under fault detect test is backplane. */

/* Register index constants (for EnablePinMask, SetPinAsBackplaneMask macros). */
#define LCD_PDD_PIN_RANGE_7_0   0U               /**< Register 0, 7..0 range of LCDx pin. */
#define LCD_PDD_PIN_RANGE_15_8  0x1U             /**< Register 1, 15..8 range of LCDx pin. */
#define LCD_PDD_PIN_RANGE_23_16 0x2U             /**< Register 2, 23..16 range of LCDx pin. */
#define LCD_PDD_PIN_RANGE_31_24 0x3U             /**< Register 3, 31..24 range of LCDx pin. */
#define LCD_PDD_PIN_RANGE_39_32 0x4U             /**< Register 4, 39..32 range of LCDx pin. */
#define LCD_PDD_PIN_RANGE_47_40 0x5U             /**< Register 5, 47..40 range of LCDx pin. */
#define LCD_PDD_PIN_RANGE_55_48 0x6U             /**< Register 6, 55..48 range of LCDx pin. */
#define LCD_PDD_PIN_RANGE_63_56 0x7U             /**< Register 7, 63..56 range of LCDx pin. */

/* Clock source constants (for SetClkSource macro). */
#define LCD_PDD_CLK1 0U                          /**< Alternate clock source 1 (MCGIRCLK) as the LCD clock source. */
#define LCD_PDD_CLK2 0x800U                      /**< Alternate clock source 2 (OSC0ERCLK) as the LCD clock source. */


/* ----------------------------------------------------------------------------
   -- EnableRegulatedVoltage
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MK30D10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK53D10)) || (defined(MCU_MKL34Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)))
/**
 * @brief Enables or disables internal voltage regulator.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of regulated voltage. This parameter is of
 *        "Global enumeration used for specifying general enable/disable states
 *        (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: LCD_GCR.
 * @par Example:
 *      @code
 *      LCD_PDD_EnableRegulatedVoltage(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
  #define LCD_PDD_EnableRegulatedVoltage(PeripheralBase, State) ( \
      LCD_GCR_REG(PeripheralBase) = \
       (uint32_t)(( \
        (uint32_t)(LCD_GCR_REG(PeripheralBase) & (uint32_t)(~(uint32_t)LCD_GCR_RVEN_MASK))) | ( \
        (uint32_t)((uint32_t)(State) << LCD_GCR_RVEN_SHIFT))) \
    )
#else /* (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK53DZ10)) */
/**
 * @brief Enables or disables internal voltage regulator.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of regulated voltage. This parameter is of
 *        "Global enumeration used for specifying general enable/disable states
 *        (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: LCD_GCR.
 * @par Example:
 *      @code
 *      LCD_PDD_EnableRegulatedVoltage(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
  #define LCD_PDD_EnableRegulatedVoltage(PeripheralBase, State) ( \
      LCD_GCR_REG(PeripheralBase) = \
       (uint32_t)(( \
        (uint32_t)(( \
         LCD_GCR_REG(PeripheralBase)) & (( \
         (uint32_t)(~(uint32_t)LCD_GCR_RVEN_MASK)) & ( \
         (uint32_t)(~(uint32_t)0x40000U))))) | ( \
        (uint32_t)((uint32_t)(State) << LCD_GCR_RVEN_SHIFT))) \
    )
#endif /* (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK53DZ10)) */

/* ----------------------------------------------------------------------------
   -- SetRegulatedVoltageTrim
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MK30D10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK53D10)) || (defined(MCU_MKL34Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)))
/**
 * @brief Sets to adjust the regulated input. The regulated input is changed by
 * 1.5% for each count.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param TrimValue Regulated voltage trim value[0..15]. This parameter is a
 *        4-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: LCD_GCR.
 * @par Example:
 *      @code
 *      LCD_PDD_SetRegulatedVoltageTrim(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
  #define LCD_PDD_SetRegulatedVoltageTrim(PeripheralBase, TrimValue) ( \
      LCD_GCR_REG(PeripheralBase) = \
       (uint32_t)(( \
        (uint32_t)(LCD_GCR_REG(PeripheralBase) & (uint32_t)(~(uint32_t)LCD_GCR_RVTRIM_MASK))) | ( \
        (uint32_t)((uint32_t)(TrimValue) << LCD_GCR_RVTRIM_SHIFT))) \
    )
#else /* (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK53DZ10)) */
/**
 * @brief Sets to adjust the regulated input. The regulated input is changed by
 * 1.5% for each count.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param TrimValue Regulated voltage trim value[0..15]. This parameter is a
 *        4-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: LCD_GCR.
 * @par Example:
 *      @code
 *      LCD_PDD_SetRegulatedVoltageTrim(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
  #define LCD_PDD_SetRegulatedVoltageTrim(PeripheralBase, TrimValue) ( \
      LCD_GCR_REG(PeripheralBase) = \
       (uint32_t)(( \
        (uint32_t)(( \
         LCD_GCR_REG(PeripheralBase)) & (( \
         (uint32_t)(~(uint32_t)LCD_GCR_RVTRIM_MASK)) & ( \
         (uint32_t)(~(uint32_t)0x40000U))))) | ( \
        (uint32_t)((uint32_t)(TrimValue) << LCD_GCR_RVTRIM_SHIFT))) \
    )
#endif /* (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK53DZ10)) */

/* ----------------------------------------------------------------------------
   -- SetLoadAdjust
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MK30D10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK53D10)) || (defined(MCU_MKL34Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)))
/**
 * @brief Sets the LCD module charge pump or a resistor network to supply the
 * LCD voltages and handle different LCD glass capacitance.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param LoadAdjust Load adjust value. The user should use one from the
 *        enumerated values. This parameter is of "Load adjust constants (for
 *        SetLoadAdjust macro)." type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: LCD_GCR.
 * @par Example:
 *      @code
 *      LCD_PDD_SetLoadAdjust(<peripheral>_BASE_PTR,
 *      LCD_PDD_LOW_LOAD_RESISTOR_NET);
 *      @endcode
 */
  #define LCD_PDD_SetLoadAdjust(PeripheralBase, LoadAdjust) ( \
      ((LoadAdjust) == LCD_PDD_LOW_LOAD_RESISTOR_NET) ? ( \
        LCD_GCR_REG(PeripheralBase) &= \
         (uint32_t)(( \
          (uint32_t)(~(uint32_t)LCD_GCR_LADJ_MASK)) & ( \
          (uint32_t)(~(uint32_t)LCD_GCR_CPSEL_MASK)))) : (((LoadAdjust) == LCD_PDD_HIGH_LOAD_RESISTOR_NET) ? ( \
        LCD_GCR_REG(PeripheralBase) = \
         (uint32_t)(( \
          (uint32_t)(( \
           LCD_GCR_REG(PeripheralBase)) & (( \
           (uint32_t)(~(uint32_t)LCD_GCR_LADJ_MASK)) & ( \
           (uint32_t)(~(uint32_t)LCD_GCR_CPSEL_MASK))))) | ( \
          (uint32_t)((uint32_t)0x2U << LCD_GCR_LADJ_SHIFT)))) : (((LoadAdjust) == LCD_PDD_FAST_CLK_CHPUMP_8NF) ? ( \
        LCD_GCR_REG(PeripheralBase) = \
         (uint32_t)(( \
          (uint32_t)(LCD_GCR_REG(PeripheralBase) & (uint32_t)(~(uint32_t)LCD_GCR_LADJ_MASK))) | ( \
          LCD_GCR_CPSEL_MASK))) : (((LoadAdjust) == LCD_PDD_MIDDLE_CLK_CHPUMP_6NF) ? ( \
        LCD_GCR_REG(PeripheralBase) = \
         (uint32_t)(( \
          (uint32_t)(LCD_GCR_REG(PeripheralBase) & (uint32_t)(~(uint32_t)LCD_GCR_LADJ_MASK))) | (( \
          (uint32_t)((uint32_t)0x1U << LCD_GCR_LADJ_SHIFT)) | ( \
          LCD_GCR_CPSEL_MASK)))) : (((LoadAdjust) == LCD_PDD_MIDDLE_CLK_CHPUMP_4NF) ? ( \
        LCD_GCR_REG(PeripheralBase) = \
         (uint32_t)(( \
          (uint32_t)(LCD_GCR_REG(PeripheralBase) & (uint32_t)(~(uint32_t)LCD_GCR_LADJ_MASK))) | (( \
          (uint32_t)((uint32_t)0x2U << LCD_GCR_LADJ_SHIFT)) | ( \
          LCD_GCR_CPSEL_MASK)))) : ( \
        LCD_GCR_REG(PeripheralBase) |= \
         (uint32_t)(LCD_GCR_LADJ_MASK | LCD_GCR_CPSEL_MASK)) \
      )))) \
    )
#else /* (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK53DZ10)) */
/**
 * @brief Sets the LCD module charge pump or a resistor network to supply the
 * LCD voltages and handle different LCD glass capacitance.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param LoadAdjust Load adjust value. The user should use one from the
 *        enumerated values. This parameter is of "Load adjust constants (for
 *        SetLoadAdjust macro)." type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: LCD_GCR.
 * @par Example:
 *      @code
 *      LCD_PDD_SetLoadAdjust(<peripheral>_BASE_PTR,
 *      LCD_PDD_LOW_LOAD_RESISTOR_NET);
 *      @endcode
 */
  #define LCD_PDD_SetLoadAdjust(PeripheralBase, LoadAdjust) ( \
      ((LoadAdjust) == LCD_PDD_LOW_LOAD_RESISTOR_NET) ? ( \
        LCD_GCR_REG(PeripheralBase) &= \
         (uint32_t)(( \
          (uint32_t)(~(uint32_t)LCD_GCR_LADJ_MASK)) & (( \
          (uint32_t)(~(uint32_t)LCD_GCR_CPSEL_MASK)) & ( \
          (uint32_t)(~(uint32_t)0x40000U))))) : (((LoadAdjust) == LCD_PDD_HIGH_LOAD_RESISTOR_NET) ? ( \
        LCD_GCR_REG(PeripheralBase) = \
         (uint32_t)(( \
          (uint32_t)(( \
           LCD_GCR_REG(PeripheralBase)) & (( \
           (uint32_t)(~(uint32_t)LCD_GCR_LADJ_MASK)) & (( \
           (uint32_t)(~(uint32_t)LCD_GCR_CPSEL_MASK)) & ( \
           (uint32_t)(~(uint32_t)0x40000U)))))) | ( \
          (uint32_t)((uint32_t)0x2U << LCD_GCR_LADJ_SHIFT)))) : (((LoadAdjust) == LCD_PDD_FAST_CLK_CHPUMP_8NF) ? ( \
        LCD_GCR_REG(PeripheralBase) = \
         (uint32_t)(( \
          (uint32_t)(( \
           LCD_GCR_REG(PeripheralBase)) & (( \
           (uint32_t)(~(uint32_t)LCD_GCR_LADJ_MASK)) & ( \
           (uint32_t)(~(uint32_t)0x40000U))))) | ( \
          LCD_GCR_CPSEL_MASK))) : (((LoadAdjust) == LCD_PDD_MIDDLE_CLK_CHPUMP_6NF) ? ( \
        LCD_GCR_REG(PeripheralBase) = \
         (uint32_t)(( \
          (uint32_t)(( \
           LCD_GCR_REG(PeripheralBase)) & (( \
           (uint32_t)(~(uint32_t)LCD_GCR_LADJ_MASK)) & ( \
           (uint32_t)(~(uint32_t)0x40000U))))) | (( \
          (uint32_t)((uint32_t)0x1U << LCD_GCR_LADJ_SHIFT)) | ( \
          LCD_GCR_CPSEL_MASK)))) : (((LoadAdjust) == LCD_PDD_MIDDLE_CLK_CHPUMP_4NF) ? ( \
        LCD_GCR_REG(PeripheralBase) = \
         (uint32_t)(( \
          (uint32_t)(( \
           LCD_GCR_REG(PeripheralBase)) & (( \
           (uint32_t)(~(uint32_t)LCD_GCR_LADJ_MASK)) & ( \
           (uint32_t)(~(uint32_t)0x40000U))))) | (( \
          (uint32_t)((uint32_t)0x2U << LCD_GCR_LADJ_SHIFT)) | ( \
          LCD_GCR_CPSEL_MASK)))) : ( \
        LCD_GCR_REG(PeripheralBase) = \
         (uint32_t)(( \
          (uint32_t)(LCD_GCR_REG(PeripheralBase) | (LCD_GCR_LADJ_MASK | LCD_GCR_CPSEL_MASK))) & ( \
          (uint32_t)(~(uint32_t)0x40000U)))) \
      )))) \
    )
#endif /* (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK53DZ10)) */

/* ----------------------------------------------------------------------------
   -- SetVoltageSupplyControl
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MKL34Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)))
/**
 * @brief Sets the LCD module on external or internal power supply.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param VoltageSupply Voltage supply control value. The user should use one
 *        from the enumerated values. This parameter is a 1-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: LCD_GCR.
 * @par Example:
 *      @code
 *      LCD_PDD_SetVoltageSupplyControl(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
  #define LCD_PDD_SetVoltageSupplyControl(PeripheralBase, VoltageSupply) ( \
      LCD_GCR_REG(PeripheralBase) = \
       (uint32_t)(( \
        (uint32_t)(LCD_GCR_REG(PeripheralBase) & (uint32_t)(~(uint32_t)LCD_GCR_VSUPPLY_MASK))) | ( \
        (uint32_t)((uint32_t)(VoltageSupply) << LCD_GCR_VSUPPLY_SHIFT))) \
    )
#elif ((defined(MCU_MK30D10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK53D10)))
/**
 * @brief Sets the LCD module on external or internal power supply.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param VoltageSupply Voltage supply control value. The user should use one
 *        from the enumerated values. This parameter is a 2-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: LCD_GCR.
 * @par Example:
 *      @code
 *      LCD_PDD_SetVoltageSupplyControl(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
  #define LCD_PDD_SetVoltageSupplyControl(PeripheralBase, VoltageSupply) ( \
      LCD_GCR_REG(PeripheralBase) = \
       (uint32_t)(( \
        (uint32_t)(LCD_GCR_REG(PeripheralBase) & (uint32_t)(~(uint32_t)LCD_GCR_VSUPPLY_MASK))) | ( \
        (uint32_t)((uint32_t)(VoltageSupply) << LCD_GCR_VSUPPLY_SHIFT))) \
    )
#else /* (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK53DZ10)) */
/**
 * @brief Sets the LCD module on external or internal power supply.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param VoltageSupply Voltage supply control value. The user should use one
 *        from the enumerated values. This parameter is a 2-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: LCD_GCR.
 * @par Example:
 *      @code
 *      LCD_PDD_SetVoltageSupplyControl(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
  #define LCD_PDD_SetVoltageSupplyControl(PeripheralBase, VoltageSupply) ( \
      LCD_GCR_REG(PeripheralBase) = \
       (uint32_t)(( \
        (uint32_t)(( \
         LCD_GCR_REG(PeripheralBase)) & (( \
         (uint32_t)(~(uint32_t)LCD_GCR_VSUPPLY_MASK)) & ( \
         (uint32_t)(~(uint32_t)0x40000U))))) | ( \
        (uint32_t)((uint32_t)(VoltageSupply) << LCD_GCR_VSUPPLY_SHIFT))) \
    )
#endif /* (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK53DZ10)) */

/* ----------------------------------------------------------------------------
   -- EnableInterrupts
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MKL34Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)))
/**
 * @brief Enables module frame frequency or fault detection complete interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mask Mask of interrupts to enable. Use constants from group "Interrupt
 *        masks (for EnableInterrupts, DisableInterrupts macros).". This
 *        parameter is 32 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: LCD_GCR.
 * @par Example:
 *      @code
 *      LCD_PDD_EnableInterrupts(<peripheral>_BASE_PTR,
 *      LCD_PDD_FAULT_DETECT_COMPLETE);
 *      @endcode
 */
  #define LCD_PDD_EnableInterrupts(PeripheralBase, Mask) ( \
      LCD_GCR_REG(PeripheralBase) |= \
       (uint32_t)(Mask) \
    )
#elif ((defined(MCU_MK30D10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK53D10)))
/**
 * @brief Enables module frame frequency or fault detection complete interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mask Mask of interrupts to enable. Use constants from group "Interrupt
 *        masks (for EnableInterrupts, DisableInterrupts macros).". This
 *        parameter is 32 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: LCD_GCR.
 * @par Example:
 *      @code
 *      LCD_PDD_EnableInterrupts(<peripheral>_BASE_PTR,
 *      LCD_PDD_FRAME_FREQUENCY);
 *      @endcode
 */
  #define LCD_PDD_EnableInterrupts(PeripheralBase, Mask) ( \
      LCD_GCR_REG(PeripheralBase) |= \
       (uint32_t)(Mask) \
    )
#else /* (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK53DZ10)) */
/**
 * @brief Enables module frame frequency or fault detection complete interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mask Mask of interrupts to enable. Use constants from group "Interrupt
 *        masks (for EnableInterrupts, DisableInterrupts macros).". This
 *        parameter is 32 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: LCD_GCR.
 * @par Example:
 *      @code
 *      LCD_PDD_EnableInterrupts(<peripheral>_BASE_PTR,
 *      LCD_PDD_FRAME_FREQUENCY);
 *      @endcode
 */
  #define LCD_PDD_EnableInterrupts(PeripheralBase, Mask) ( \
      LCD_GCR_REG(PeripheralBase) = \
       (uint32_t)(( \
        (uint32_t)(LCD_GCR_REG(PeripheralBase) | (uint32_t)(Mask))) & ( \
        (uint32_t)(~(uint32_t)0x40000U))) \
    )
#endif /* (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK53DZ10)) */

/* ----------------------------------------------------------------------------
   -- DisableInterrupts
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MKL34Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)))
/**
 * @brief Disables module frame frequency or fault detection complete interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mask Mask of interrupts to disable. Use constants from group
 *        "Interrupt masks (for EnableInterrupts, DisableInterrupts macros).". This
 *        parameter is 32 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: LCD_GCR.
 * @par Example:
 *      @code
 *      LCD_PDD_DisableInterrupts(<peripheral>_BASE_PTR,
 *      LCD_PDD_FAULT_DETECT_COMPLETE);
 *      @endcode
 */
  #define LCD_PDD_DisableInterrupts(PeripheralBase, Mask) ( \
      LCD_GCR_REG(PeripheralBase) &= \
       (uint32_t)(~(uint32_t)(Mask)) \
    )
#elif ((defined(MCU_MK30D10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK53D10)))
/**
 * @brief Disables module frame frequency or fault detection complete interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mask Mask of interrupts to disable. Use constants from group
 *        "Interrupt masks (for EnableInterrupts, DisableInterrupts macros).". This
 *        parameter is 32 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: LCD_GCR.
 * @par Example:
 *      @code
 *      LCD_PDD_DisableInterrupts(<peripheral>_BASE_PTR,
 *      LCD_PDD_FRAME_FREQUENCY);
 *      @endcode
 */
  #define LCD_PDD_DisableInterrupts(PeripheralBase, Mask) ( \
      LCD_GCR_REG(PeripheralBase) &= \
       (uint32_t)(~(uint32_t)(Mask)) \
    )
#else /* (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK53DZ10)) */
/**
 * @brief Disables module frame frequency or fault detection complete interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mask Mask of interrupts to disable. Use constants from group
 *        "Interrupt masks (for EnableInterrupts, DisableInterrupts macros).". This
 *        parameter is 32 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: LCD_GCR.
 * @par Example:
 *      @code
 *      LCD_PDD_DisableInterrupts(<peripheral>_BASE_PTR,
 *      LCD_PDD_FRAME_FREQUENCY);
 *      @endcode
 */
  #define LCD_PDD_DisableInterrupts(PeripheralBase, Mask) ( \
      LCD_GCR_REG(PeripheralBase) &= \
       (uint32_t)((uint32_t)(~(uint32_t)(Mask)) & (uint32_t)(~(uint32_t)0x40000U)) \
    )
#endif /* (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK53DZ10)) */

/* ----------------------------------------------------------------------------
   -- SetAlternateClkDivider
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MK30D10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK53D10)) || (defined(MCU_MKL34Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)))
/**
 * @brief Sets the LCD module on external or internal power supply.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Divider Divide factor value. The user should use one from the
 *        enumerated values. This parameter is of "Alternate Clk divider constants (for
 *        SetAlternateClkDivider macro)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: LCD_GCR.
 * @par Example:
 *      @code
 *      LCD_PDD_SetAlternateClkDivider(<peripheral>_BASE_PTR,
 *      LCD_PDD_DIVIDE_FACTOR_1);
 *      @endcode
 */
  #define LCD_PDD_SetAlternateClkDivider(PeripheralBase, Divider) ( \
      LCD_GCR_REG(PeripheralBase) = \
       (uint32_t)(( \
        (uint32_t)(LCD_GCR_REG(PeripheralBase) & (uint32_t)(~(uint32_t)LCD_GCR_ALTDIV_MASK))) | ( \
        (uint32_t)((uint32_t)(Divider) << LCD_GCR_ALTDIV_SHIFT))) \
    )
#else /* (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK53DZ10)) */
/**
 * @brief Sets the LCD module on external or internal power supply.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Divider Divide factor value. The user should use one from the
 *        enumerated values. This parameter is of "Alternate Clk divider constants (for
 *        SetAlternateClkDivider macro)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: LCD_GCR.
 * @par Example:
 *      @code
 *      LCD_PDD_SetAlternateClkDivider(<peripheral>_BASE_PTR,
 *      LCD_PDD_DIVIDE_FACTOR_1);
 *      @endcode
 */
  #define LCD_PDD_SetAlternateClkDivider(PeripheralBase, Divider) ( \
      LCD_GCR_REG(PeripheralBase) = \
       (uint32_t)(( \
        (uint32_t)(( \
         LCD_GCR_REG(PeripheralBase)) & (( \
         (uint32_t)(~(uint32_t)LCD_GCR_ALTDIV_MASK)) & ( \
         (uint32_t)(~(uint32_t)0x40000U))))) | ( \
        (uint32_t)((uint32_t)(Divider) << LCD_GCR_ALTDIV_SHIFT))) \
    )
#endif /* (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK53DZ10)) */

/* ----------------------------------------------------------------------------
   -- EnableInWaitMode
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MKL34Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)))
/**
 * @brief Enables or disables module driver, charge pump, resistor bias network,
 * and voltage regulator stop while in Wait mode.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state in wait mode. This parameter is of "Global
 *        enumeration used for specifying general enable/disable states (PDD_DISABLE
 *        and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: LCD_GCR.
 * @par Example:
 *      @code
 *      LCD_PDD_EnableInWaitMode(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
  #define LCD_PDD_EnableInWaitMode(PeripheralBase, State) ( \
      ((State) == PDD_DISABLE) ? ( \
        LCD_GCR_REG(PeripheralBase) |= \
         LCD_GCR_LCDDOZE_MASK) : ( \
        LCD_GCR_REG(PeripheralBase) &= \
         (uint32_t)(~(uint32_t)LCD_GCR_LCDDOZE_MASK)) \
    )
#elif ((defined(MCU_MK30D10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK53D10)))
/**
 * @brief Enables or disables module driver, charge pump, resistor bias network,
 * and voltage regulator stop while in Wait mode.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state in wait mode. This parameter is of "Global
 *        enumeration used for specifying general enable/disable states (PDD_DISABLE
 *        and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: LCD_GCR.
 * @par Example:
 *      @code
 *      LCD_PDD_EnableInWaitMode(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
  #define LCD_PDD_EnableInWaitMode(PeripheralBase, State) ( \
      ((State) == PDD_DISABLE) ? ( \
        LCD_GCR_REG(PeripheralBase) |= \
         LCD_GCR_LCDWAIT_MASK) : ( \
        LCD_GCR_REG(PeripheralBase) &= \
         (uint32_t)(~(uint32_t)LCD_GCR_LCDWAIT_MASK)) \
    )
#else /* (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK53DZ10)) */
/**
 * @brief Enables or disables module driver, charge pump, resistor bias network,
 * and voltage regulator stop while in Wait mode.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state in wait mode. This parameter is of "Global
 *        enumeration used for specifying general enable/disable states (PDD_DISABLE
 *        and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: LCD_GCR.
 * @par Example:
 *      @code
 *      LCD_PDD_EnableInWaitMode(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
  #define LCD_PDD_EnableInWaitMode(PeripheralBase, State) ( \
      ((State) == PDD_DISABLE) ? ( \
        LCD_GCR_REG(PeripheralBase) = \
         (uint32_t)(( \
          (uint32_t)(LCD_GCR_REG(PeripheralBase) | LCD_GCR_LCDWAIT_MASK)) & ( \
          (uint32_t)(~(uint32_t)0x40000U)))) : ( \
        LCD_GCR_REG(PeripheralBase) &= \
         (uint32_t)((uint32_t)(~(uint32_t)LCD_GCR_LCDWAIT_MASK) & (uint32_t)(~(uint32_t)0x40000U))) \
    )
#endif /* (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK53DZ10)) */

/* ----------------------------------------------------------------------------
   -- EnableInStopMode
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MK30D10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK53D10)) || (defined(MCU_MKL34Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)))
/**
 * @brief Enables or disables module driver, charge pump, resistor bias network,
 * and voltage regulator while in Stop mode.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state in stop mode. This parameter is of "Global
 *        enumeration used for specifying general enable/disable states (PDD_DISABLE
 *        and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: LCD_GCR.
 * @par Example:
 *      @code
 *      LCD_PDD_EnableInStopMode(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
  #define LCD_PDD_EnableInStopMode(PeripheralBase, State) ( \
      ((State) == PDD_DISABLE) ? ( \
        LCD_GCR_REG(PeripheralBase) |= \
         LCD_GCR_LCDSTP_MASK) : ( \
        LCD_GCR_REG(PeripheralBase) &= \
         (uint32_t)(~(uint32_t)LCD_GCR_LCDSTP_MASK)) \
    )
#else /* (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK53DZ10)) */
/**
 * @brief Enables or disables module driver, charge pump, resistor bias network,
 * and voltage regulator while in Stop mode.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state in stop mode. This parameter is of "Global
 *        enumeration used for specifying general enable/disable states (PDD_DISABLE
 *        and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: LCD_GCR.
 * @par Example:
 *      @code
 *      LCD_PDD_EnableInStopMode(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
  #define LCD_PDD_EnableInStopMode(PeripheralBase, State) ( \
      ((State) == PDD_DISABLE) ? ( \
        LCD_GCR_REG(PeripheralBase) = \
         (uint32_t)(( \
          (uint32_t)(LCD_GCR_REG(PeripheralBase) | LCD_GCR_LCDSTP_MASK)) & ( \
          (uint32_t)(~(uint32_t)0x40000U)))) : ( \
        LCD_GCR_REG(PeripheralBase) &= \
         (uint32_t)((uint32_t)(~(uint32_t)LCD_GCR_LCDSTP_MASK) & (uint32_t)(~(uint32_t)0x40000U))) \
    )
#endif /* (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK53DZ10)) */

/* ----------------------------------------------------------------------------
   -- EnableDevice
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MK30D10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK53D10)) || (defined(MCU_MKL34Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)))
/**
 * @brief Enables LCD module driver system.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of segment LCD device. This parameter is of
 *        "Global enumeration used for specifying general enable/disable states
 *        (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: LCD_GCR.
 * @par Example:
 *      @code
 *      LCD_PDD_EnableDevice(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
  #define LCD_PDD_EnableDevice(PeripheralBase, State) ( \
      LCD_GCR_REG(PeripheralBase) = \
       (uint32_t)(( \
        (uint32_t)(LCD_GCR_REG(PeripheralBase) & (uint32_t)(~(uint32_t)LCD_GCR_LCDEN_MASK))) | ( \
        (uint32_t)((uint32_t)(State) << LCD_GCR_LCDEN_SHIFT))) \
    )
#else /* (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK53DZ10)) */
/**
 * @brief Enables LCD module driver system.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of segment LCD device. This parameter is of
 *        "Global enumeration used for specifying general enable/disable states
 *        (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: LCD_GCR.
 * @par Example:
 *      @code
 *      LCD_PDD_EnableDevice(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
  #define LCD_PDD_EnableDevice(PeripheralBase, State) ( \
      LCD_GCR_REG(PeripheralBase) = \
       (uint32_t)(( \
        (uint32_t)(( \
         LCD_GCR_REG(PeripheralBase)) & (( \
         (uint32_t)(~(uint32_t)LCD_GCR_LCDEN_MASK)) & ( \
         (uint32_t)(~(uint32_t)0x40000U))))) | ( \
        (uint32_t)((uint32_t)(State) << LCD_GCR_LCDEN_SHIFT))) \
    )
#endif /* (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK53DZ10)) */

/* ----------------------------------------------------------------------------
   -- SetClkSource
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MK30D10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK53D10)) || (defined(MCU_MKL34Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)))
/**
 * @brief Sets clock the default or alternate as the LCD clock source.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param ClkSource Clock source value. The user should use one from the
 *        enumerated values. This parameter is of "Clock source constants (for
 *        SetClkSource macro)." type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: LCD_GCR.
 * @par Example:
 *      @code
 *      LCD_PDD_SetClkSource(<peripheral>_BASE_PTR, LCD_PDD_DEFAULT_CLK);
 *      @endcode
 */
  #define LCD_PDD_SetClkSource(PeripheralBase, ClkSource) ( \
      LCD_GCR_REG(PeripheralBase) = \
       (uint32_t)(( \
        (uint32_t)(LCD_GCR_REG(PeripheralBase) & (uint32_t)(~(uint32_t)LCD_GCR_SOURCE_MASK))) | ( \
        (uint32_t)(ClkSource))) \
    )
#else /* (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK53DZ10)) */
/**
 * @brief Sets clock the default or alternate as the LCD clock source.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param ClkSource Clock source value. The user should use one from the
 *        enumerated values. This parameter is of "Clock source constants (for
 *        SetClkSource macro)." type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: LCD_GCR.
 * @par Example:
 *      @code
 *      LCD_PDD_SetClkSource(<peripheral>_BASE_PTR, LCD_PDD_DEFAULT_CLK);
 *      @endcode
 */
  #define LCD_PDD_SetClkSource(PeripheralBase, ClkSource) ( \
      LCD_GCR_REG(PeripheralBase) = \
       (uint32_t)(( \
        (uint32_t)(( \
         LCD_GCR_REG(PeripheralBase)) & (( \
         (uint32_t)(~(uint32_t)LCD_GCR_SOURCE_MASK)) & ( \
         (uint32_t)(~(uint32_t)0x40000U))))) | ( \
        (uint32_t)(ClkSource))) \
    )
#endif /* (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK53DZ10)) */

/* ----------------------------------------------------------------------------
   -- SetClkPrescaler
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MK30D10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK53D10)) || (defined(MCU_MKL34Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)))
/**
 * @brief Sets a clock divider to generate the LCD module frame frequency.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param ClkPrescaler Clock prescaler value[0..7]. This parameter is a 3-bit
 *        value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: LCD_GCR.
 * @par Example:
 *      @code
 *      LCD_PDD_SetClkPrescaler(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
  #define LCD_PDD_SetClkPrescaler(PeripheralBase, ClkPrescaler) ( \
      LCD_GCR_REG(PeripheralBase) = \
       (uint32_t)(( \
        (uint32_t)(LCD_GCR_REG(PeripheralBase) & (uint32_t)(~(uint32_t)LCD_GCR_LCLK_MASK))) | ( \
        (uint32_t)((uint32_t)(ClkPrescaler) << LCD_GCR_LCLK_SHIFT))) \
    )
#else /* (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK53DZ10)) */
/**
 * @brief Sets a clock divider to generate the LCD module frame frequency.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param ClkPrescaler Clock prescaler value[0..7]. This parameter is a 3-bit
 *        value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: LCD_GCR.
 * @par Example:
 *      @code
 *      LCD_PDD_SetClkPrescaler(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
  #define LCD_PDD_SetClkPrescaler(PeripheralBase, ClkPrescaler) ( \
      LCD_GCR_REG(PeripheralBase) = \
       (uint32_t)(( \
        (uint32_t)(( \
         LCD_GCR_REG(PeripheralBase)) & (( \
         (uint32_t)(~(uint32_t)LCD_GCR_LCLK_MASK)) & ( \
         (uint32_t)(~(uint32_t)0x40000U))))) | ( \
        (uint32_t)((uint32_t)(ClkPrescaler) << LCD_GCR_LCLK_SHIFT))) \
    )
#endif /* (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK53DZ10)) */

/* ----------------------------------------------------------------------------
   -- SetDutyCycle
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MK30D10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK53D10)) || (defined(MCU_MKL34Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)))
/**
 * @brief Sets the duty cycle of the LCD module driver.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param DutyCycle Duty cycle value[0..7]. This parameter is a 3-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: LCD_GCR.
 * @par Example:
 *      @code
 *      LCD_PDD_SetDutyCycle(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
  #define LCD_PDD_SetDutyCycle(PeripheralBase, DutyCycle) ( \
      LCD_GCR_REG(PeripheralBase) = \
       (uint32_t)(( \
        (uint32_t)(LCD_GCR_REG(PeripheralBase) & (uint32_t)(~(uint32_t)LCD_GCR_DUTY_MASK))) | ( \
        (uint32_t)(DutyCycle))) \
    )
#else /* (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK53DZ10)) */
/**
 * @brief Sets the duty cycle of the LCD module driver.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param DutyCycle Duty cycle value[0..7]. This parameter is a 3-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: LCD_GCR.
 * @par Example:
 *      @code
 *      LCD_PDD_SetDutyCycle(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
  #define LCD_PDD_SetDutyCycle(PeripheralBase, DutyCycle) ( \
      LCD_GCR_REG(PeripheralBase) = \
       (uint32_t)(( \
        (uint32_t)(( \
         LCD_GCR_REG(PeripheralBase)) & (( \
         (uint32_t)(~(uint32_t)LCD_GCR_DUTY_MASK)) & ( \
         (uint32_t)(~(uint32_t)0x40000U))))) | ( \
        (uint32_t)(DutyCycle))) \
    )
#endif /* (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK53DZ10)) */

/* ----------------------------------------------------------------------------
   -- GetFrameFreqInterruptFlag
   ---------------------------------------------------------------------------- */

/**
 * @brief Return non-zero if frame frequency interrupt flag is set, otherwise
 * returns zero.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: LCD_AR.
 * @par Example:
 *      @code
 *      uint32_t result =
 *      LCD_PDD_GetFrameFreqInterruptFlag(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define LCD_PDD_GetFrameFreqInterruptFlag(PeripheralBase) ( \
    (uint32_t)(LCD_AR_REG(PeripheralBase) & LCD_AR_LCDIF_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- ClearFrameFreqInterruptFlag
   ---------------------------------------------------------------------------- */

/**
 * @brief Clears interrupt flag of frame frequency.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: LCD_AR.
 * @par Example:
 *      @code
 *      LCD_PDD_ClearFrameFreqInterruptFlag(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define LCD_PDD_ClearFrameFreqInterruptFlag(PeripheralBase) ( \
    LCD_AR_REG(PeripheralBase) |= \
     LCD_AR_LCDIF_MASK \
  )

/* ----------------------------------------------------------------------------
   -- EnableBlinking
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MKL34Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)))
/**
 * @brief Enables or disables LCD module blinking.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of segment LCD. This parameter is of "Global
 *        enumeration used for specifying general enable/disable states (PDD_DISABLE
 *        and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: LCD_AR.
 * @par Example:
 *      @code
 *      LCD_PDD_EnableBlinking(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
  #define LCD_PDD_EnableBlinking(PeripheralBase, State) ( \
      LCD_AR_REG(PeripheralBase) = \
       (uint32_t)(( \
        (uint32_t)(LCD_AR_REG(PeripheralBase) & (uint32_t)(~(uint32_t)LCD_AR_BLINK_MASK))) | ( \
        (uint32_t)((uint32_t)(State) << LCD_AR_BLINK_SHIFT))) \
    )
#else /* (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) */
/**
 * @brief Enables or disables LCD module blinking.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of segment LCD. This parameter is of "Global
 *        enumeration used for specifying general enable/disable states (PDD_DISABLE
 *        and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: LCD_AR.
 * @par Example:
 *      @code
 *      LCD_PDD_EnableBlinking(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
  #define LCD_PDD_EnableBlinking(PeripheralBase, State) ( \
      LCD_AR_REG(PeripheralBase) = \
       (uint32_t)(( \
        (uint32_t)(( \
         LCD_AR_REG(PeripheralBase)) & (( \
         (uint32_t)(~(uint32_t)LCD_AR_BLINK_MASK)) & ( \
         (uint32_t)(~(uint32_t)LCD_AR_LCDIF_MASK))))) | ( \
        (uint32_t)((uint32_t)(State) << LCD_AR_BLINK_SHIFT))) \
    )
#endif /* (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) */

/* ----------------------------------------------------------------------------
   -- EnableAlternateMode
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MKL34Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)))
/**
 * @brief Enables or disables alternate display mode.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of segment LCD. This parameter is of "Global
 *        enumeration used for specifying general enable/disable states (PDD_DISABLE
 *        and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: LCD_AR.
 * @par Example:
 *      @code
 *      LCD_PDD_EnableAlternateMode(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
  #define LCD_PDD_EnableAlternateMode(PeripheralBase, State) ( \
      LCD_AR_REG(PeripheralBase) = \
       (uint32_t)(( \
        (uint32_t)(LCD_AR_REG(PeripheralBase) & (uint32_t)(~(uint32_t)LCD_AR_ALT_MASK))) | ( \
        (uint32_t)((uint32_t)(State) << LCD_AR_ALT_SHIFT))) \
    )
#else /* (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) */
/**
 * @brief Enables or disables alternate display mode.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of segment LCD. This parameter is of "Global
 *        enumeration used for specifying general enable/disable states (PDD_DISABLE
 *        and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: LCD_AR.
 * @par Example:
 *      @code
 *      LCD_PDD_EnableAlternateMode(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
  #define LCD_PDD_EnableAlternateMode(PeripheralBase, State) ( \
      LCD_AR_REG(PeripheralBase) = \
       (uint32_t)(( \
        (uint32_t)(( \
         LCD_AR_REG(PeripheralBase)) & (( \
         (uint32_t)(~(uint32_t)LCD_AR_ALT_MASK)) & ( \
         (uint32_t)(~(uint32_t)LCD_AR_LCDIF_MASK))))) | ( \
        (uint32_t)((uint32_t)(State) << LCD_AR_ALT_SHIFT))) \
    )
#endif /* (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) */

/* ----------------------------------------------------------------------------
   -- EnableBlankDisplayMode
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MKL34Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)))
/**
 * @brief Enables or disables blank display mode.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of segment LCD. This parameter is of "Global
 *        enumeration used for specifying general enable/disable states (PDD_DISABLE
 *        and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: LCD_AR.
 * @par Example:
 *      @code
 *      LCD_PDD_EnableBlankDisplayMode(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
  #define LCD_PDD_EnableBlankDisplayMode(PeripheralBase, State) ( \
      LCD_AR_REG(PeripheralBase) = \
       (uint32_t)(( \
        (uint32_t)(LCD_AR_REG(PeripheralBase) & (uint32_t)(~(uint32_t)LCD_AR_BLANK_MASK))) | ( \
        (uint32_t)((uint32_t)(State) << LCD_AR_BLANK_SHIFT))) \
    )
#else /* (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) */
/**
 * @brief Enables or disables blank display mode.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of segment LCD. This parameter is of "Global
 *        enumeration used for specifying general enable/disable states (PDD_DISABLE
 *        and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: LCD_AR.
 * @par Example:
 *      @code
 *      LCD_PDD_EnableBlankDisplayMode(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
  #define LCD_PDD_EnableBlankDisplayMode(PeripheralBase, State) ( \
      LCD_AR_REG(PeripheralBase) = \
       (uint32_t)(( \
        (uint32_t)(( \
         LCD_AR_REG(PeripheralBase)) & (( \
         (uint32_t)(~(uint32_t)LCD_AR_BLANK_MASK)) & ( \
         (uint32_t)(~(uint32_t)LCD_AR_LCDIF_MASK))))) | ( \
        (uint32_t)((uint32_t)(State) << LCD_AR_BLANK_SHIFT))) \
    )
#endif /* (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) */

/* ----------------------------------------------------------------------------
   -- SetBlinkMode
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MKL34Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)))
/**
 * @brief Sets blink mode displayed during the blink period.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param BlinkMode Blink mode value. The user should use one from the
 *        enumerated values. This parameter is of "Blink mode constants (for SetBlinkMode
 *        macro)." type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: LCD_AR.
 * @par Example:
 *      @code
 *      LCD_PDD_SetBlinkMode(<peripheral>_BASE_PTR, LCD_PDD_BLANK_BLINK);
 *      @endcode
 */
  #define LCD_PDD_SetBlinkMode(PeripheralBase, BlinkMode) ( \
      LCD_AR_REG(PeripheralBase) = \
       (uint32_t)(( \
        (uint32_t)(LCD_AR_REG(PeripheralBase) & (uint32_t)(~(uint32_t)LCD_AR_BMODE_MASK))) | ( \
        (uint32_t)(BlinkMode))) \
    )
#else /* (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) */
/**
 * @brief Sets blink mode displayed during the blink period.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param BlinkMode Blink mode value. The user should use one from the
 *        enumerated values. This parameter is of "Blink mode constants (for SetBlinkMode
 *        macro)." type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: LCD_AR.
 * @par Example:
 *      @code
 *      LCD_PDD_SetBlinkMode(<peripheral>_BASE_PTR, LCD_PDD_BLANK_BLINK);
 *      @endcode
 */
  #define LCD_PDD_SetBlinkMode(PeripheralBase, BlinkMode) ( \
      LCD_AR_REG(PeripheralBase) = \
       (uint32_t)(( \
        (uint32_t)(( \
         LCD_AR_REG(PeripheralBase)) & (( \
         (uint32_t)(~(uint32_t)LCD_AR_BMODE_MASK)) & ( \
         (uint32_t)(~(uint32_t)LCD_AR_LCDIF_MASK))))) | ( \
        (uint32_t)(BlinkMode))) \
    )
#endif /* (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) */

/* ----------------------------------------------------------------------------
   -- SetBlinkRate
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MKL34Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)))
/**
 * @brief Sets speed at which the LCD blinks.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param BlinkRate Blink rate value[0..7]. This parameter is a 3-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: LCD_AR.
 * @par Example:
 *      @code
 *      LCD_PDD_SetBlinkRate(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
  #define LCD_PDD_SetBlinkRate(PeripheralBase, BlinkRate) ( \
      LCD_AR_REG(PeripheralBase) = \
       (uint32_t)(( \
        (uint32_t)(LCD_AR_REG(PeripheralBase) & (uint32_t)(~(uint32_t)LCD_AR_BRATE_MASK))) | ( \
        (uint32_t)(BlinkRate))) \
    )
#else /* (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) */
/**
 * @brief Sets speed at which the LCD blinks.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param BlinkRate Blink rate value[0..7]. This parameter is a 3-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: LCD_AR.
 * @par Example:
 *      @code
 *      LCD_PDD_SetBlinkRate(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
  #define LCD_PDD_SetBlinkRate(PeripheralBase, BlinkRate) ( \
      LCD_AR_REG(PeripheralBase) = \
       (uint32_t)(( \
        (uint32_t)(( \
         LCD_AR_REG(PeripheralBase)) & (( \
         (uint32_t)(~(uint32_t)LCD_AR_BRATE_MASK)) & ( \
         (uint32_t)(~(uint32_t)LCD_AR_LCDIF_MASK))))) | ( \
        (uint32_t)(BlinkRate))) \
    )
#endif /* (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) */

/* ----------------------------------------------------------------------------
   -- SetFaultDetectClkPrescaler
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets fault detect clock prescaler.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param FaultClkPrescaler Fault detect clock prescaler value[0..7]. This
 *        parameter is a 3-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: LCD_FDCR.
 * @par Example:
 *      @code
 *      LCD_PDD_SetFaultDetectClkPrescaler(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define LCD_PDD_SetFaultDetectClkPrescaler(PeripheralBase, FaultClkPrescaler) ( \
    LCD_FDCR_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(LCD_FDCR_REG(PeripheralBase) & (uint32_t)(~(uint32_t)LCD_FDCR_FDPRS_MASK))) | ( \
      (uint32_t)((uint32_t)(FaultClkPrescaler) << LCD_FDCR_FDPRS_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SetFaultDetectSampleWidth
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the sample window width of fault detection in number of cycles.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param SampleWidth Sample window width value[0..7]. This parameter is a 3-bit
 *        value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: LCD_FDCR.
 * @par Example:
 *      @code
 *      LCD_PDD_SetFaultDetectSampleWidth(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define LCD_PDD_SetFaultDetectSampleWidth(PeripheralBase, SampleWidth) ( \
    LCD_FDCR_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(LCD_FDCR_REG(PeripheralBase) & (uint32_t)(~(uint32_t)LCD_FDCR_FDSWW_MASK))) | ( \
      (uint32_t)((uint32_t)(SampleWidth) << LCD_FDCR_FDSWW_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- EnableFaultDetect
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables or disables fault detection.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of fault detection. This parameter is of "Global
 *        enumeration used for specifying general enable/disable states
 *        (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: LCD_FDCR.
 * @par Example:
 *      @code
 *      LCD_PDD_EnableFaultDetect(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define LCD_PDD_EnableFaultDetect(PeripheralBase, State) ( \
    LCD_FDCR_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(LCD_FDCR_REG(PeripheralBase) & (uint32_t)(~(uint32_t)LCD_FDCR_FDEN_MASK))) | ( \
      (uint32_t)((uint32_t)(State) << LCD_FDCR_FDEN_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SetFaultDetectPinType
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the LCD pin to be checked by pull-up or run-time fault detection.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param PinType Requested pin type. This parameter is of "Pin type mode
 *        constants (for SetFaultDetectPinType macro)." type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: LCD_FDCR.
 * @par Example:
 *      @code
 *      LCD_PDD_SetFaultDetectPinType(<peripheral>_BASE_PTR,
 *      LCD_PDD_FAULT_FRONTPLANE);
 *      @endcode
 */
#define LCD_PDD_SetFaultDetectPinType(PeripheralBase, PinType) ( \
    LCD_FDCR_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(LCD_FDCR_REG(PeripheralBase) & (uint32_t)(~(uint32_t)LCD_FDCR_FDBPEN_MASK))) | ( \
      (uint32_t)(PinType))) \
  )

/* ----------------------------------------------------------------------------
   -- SetFaultDetectPinID
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the LCD pin to be checked by pull-up or run-time fault detection.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param DetectPinID Fault detect pin ID value[0..63]. This parameter is a
 *        6-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: LCD_FDCR.
 * @par Example:
 *      @code
 *      LCD_PDD_SetFaultDetectPinID(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define LCD_PDD_SetFaultDetectPinID(PeripheralBase, DetectPinID) ( \
    LCD_FDCR_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(LCD_FDCR_REG(PeripheralBase) & (uint32_t)(~(uint32_t)LCD_FDCR_FDPINID_MASK))) | ( \
      (uint32_t)(DetectPinID))) \
  )

/* ----------------------------------------------------------------------------
   -- GetFaultDetectInterruptFlag
   ---------------------------------------------------------------------------- */

/**
 * @brief Return value of fault detection complete flag.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: LCD_FDSR.
 * @par Example:
 *      @code
 *      uint32_t result =
 *      LCD_PDD_GetFaultDetectInterruptFlag(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define LCD_PDD_GetFaultDetectInterruptFlag(PeripheralBase) ( \
    (uint32_t)(LCD_FDSR_REG(PeripheralBase) & LCD_FDSR_FDCF_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- ClearFaultDetectInterruptFlag
   ---------------------------------------------------------------------------- */

/**
 * @brief Clears flag of fault detection complete.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: LCD_FDSR.
 * @par Example:
 *      @code
 *      LCD_PDD_ClearFaultDetectInterruptFlag(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define LCD_PDD_ClearFaultDetectInterruptFlag(PeripheralBase) ( \
    LCD_FDSR_REG(PeripheralBase) |= \
     LCD_FDSR_FDCF_MASK \
  )

/* ----------------------------------------------------------------------------
   -- GetFaultDetectValue
   ---------------------------------------------------------------------------- */

/**
 * @brief Return how many "one/high" are sampled inside the fault detect sample
 * window.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: LCD_FDSR.
 * @par Example:
 *      @code
 *      uint8_t result = LCD_PDD_GetFaultDetectValue(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define LCD_PDD_GetFaultDetectValue(PeripheralBase) ( \
    (uint8_t)(LCD_FDSR_REG(PeripheralBase) & LCD_FDSR_FDCNT_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- EnablePinMask
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables pins for LCD operation.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param RegIndex The user should use one from the enumerated values. This
 *        parameter is of index type.
 * @param PinMask 8 bits mask of pins what are arranged according RegIndex
 *        parameter. This parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: PEN[].
 * @par Example:
 *      @code
 *      LCD_PDD_EnablePinMask(<peripheral>_BASE_PTR, periphID, 1);
 *      @endcode
 */
#define LCD_PDD_EnablePinMask(PeripheralBase, RegIndex, PinMask) ( \
    ((uint8_t)((uint8_t)(RegIndex) & 0x4U) == 0U) ? ( \
      LCD_PEN_REG(PeripheralBase,0U) = \
       (uint32_t)(( \
        (uint32_t)(( \
         LCD_PEN_REG(PeripheralBase,0U)) & ( \
         (uint32_t)(~(uint32_t)((uint32_t)0xFFU << (uint8_t)((uint8_t)((uint8_t)(RegIndex) & 0x3U) << 3U)))))) | ( \
        (uint32_t)((uint32_t)(PinMask) << (uint8_t)((uint8_t)((uint8_t)(RegIndex) & 0x3U) << 3U))))) : ( \
      LCD_PEN_REG(PeripheralBase,1U) = \
       (uint32_t)(( \
        (uint32_t)(( \
         LCD_PEN_REG(PeripheralBase,1U)) & ( \
         (uint32_t)(~(uint32_t)((uint32_t)0xFFU << (uint8_t)((uint8_t)((uint8_t)(RegIndex) & 0x3U) << 3U)))))) | ( \
        (uint32_t)((uint32_t)(PinMask) << (uint8_t)((uint8_t)((uint8_t)(RegIndex) & 0x3U) << 3U))))) \
  )

/* ----------------------------------------------------------------------------
   -- SetPinAsBackplaneMask
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets pins as Enables or disables fault detection.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param RegIndex The user should use one from the enumerated values. This
 *        parameter is of index type.
 * @param PinMask 8 bits mask of pins what are arranged according RegIndex
 *        parameter. This parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: BPEN[].
 * @par Example:
 *      @code
 *      LCD_PDD_SetPinAsBackplaneMask(<peripheral>_BASE_PTR, periphID, 1);
 *      @endcode
 */
#define LCD_PDD_SetPinAsBackplaneMask(PeripheralBase, RegIndex, PinMask) ( \
    ((uint8_t)((uint8_t)(RegIndex) & 0x4U) == 0U) ? ( \
      LCD_BPEN_REG(PeripheralBase,0U) = \
       (uint32_t)(( \
        (uint32_t)(( \
         LCD_BPEN_REG(PeripheralBase,0U)) & ( \
         (uint32_t)(~(uint32_t)((uint32_t)0xFFU << (uint8_t)((uint8_t)((uint8_t)(RegIndex) & 0x3U) << 3U)))))) | ( \
        (uint32_t)((uint32_t)(PinMask) << (uint8_t)((uint8_t)((uint8_t)(RegIndex) & 0x3U) << 3U))))) : ( \
      LCD_BPEN_REG(PeripheralBase,1U) = \
       (uint32_t)(( \
        (uint32_t)(( \
         LCD_BPEN_REG(PeripheralBase,1U)) & ( \
         (uint32_t)(~(uint32_t)((uint32_t)0xFFU << (uint8_t)((uint8_t)((uint8_t)(RegIndex) & 0x3U) << 3U)))))) | ( \
        (uint32_t)((uint32_t)(PinMask) << (uint8_t)((uint8_t)((uint8_t)(RegIndex) & 0x3U) << 3U))))) \
  )

/* ----------------------------------------------------------------------------
   -- SetWaveform
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets value of the frontplanes pins for the backplane phase.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param FrontplanePinIndex Wave form register index[0..63]. This parameter is
 *        of index type.
 * @param Waveform Wave form value[0..255]. This parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: WF[].
 * @par Example:
 *      @code
 *      LCD_PDD_SetWaveform(<peripheral>_BASE_PTR, periphID, 1);
 *      @endcode
 */
#define LCD_PDD_SetWaveform(PeripheralBase, FrontplanePinIndex, Waveform) ( \
    LCD_WF_REG(PeripheralBase,(uint8_t)((uint8_t)(FrontplanePinIndex) >> 2U)) = \
     (uint32_t)(( \
      (uint32_t)(( \
       LCD_WF_REG(PeripheralBase,(uint8_t)((uint8_t)(FrontplanePinIndex) >> 2U))) & ( \
       (uint32_t)(~(uint32_t)(( \
        (uint32_t)0xFFU) << ( \
        (uint8_t)((uint8_t)((uint8_t)(FrontplanePinIndex) & 0x3U) << 3U))))))) | ( \
      (uint32_t)(( \
       (uint32_t)(Waveform)) << ( \
       (uint8_t)((uint8_t)((uint8_t)(FrontplanePinIndex) & 0x3U) << 3U))))) \
  )

/* ----------------------------------------------------------------------------
   -- GetWaveform
   ---------------------------------------------------------------------------- */

/**
 * @brief Return value of the frontplanes pins for the backplane phase.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param FrontplanePinIndex Wave form register index[0..63]. This parameter is
 *        of index type.
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: WF[].
 * @par Example:
 *      @code
 *      uint8_t result = LCD_PDD_GetWaveform(<peripheral>_BASE_PTR, periphID);
 *      @endcode
 */
#define LCD_PDD_GetWaveform(PeripheralBase, FrontplanePinIndex) ( \
    (uint8_t)(( \
     LCD_WF_REG(PeripheralBase,(uint8_t)((uint8_t)(FrontplanePinIndex) >> 2U))) >> ( \
     (uint8_t)((uint8_t)((uint8_t)(FrontplanePinIndex) & 0x3U) << 3U))) \
  )

/* ----------------------------------------------------------------------------
   -- SetAlternateWaveform
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets value of the alternate frontplanes pins for the backplane phase.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param FrontplanePinIndex Wave form register index[0..63]. This parameter is
 *        of index type.
 * @param Waveform Wave form value[0..15]. This parameter is a 4-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: WF[].
 * @par Example:
 *      @code
 *      LCD_PDD_SetAlternateWaveform(<peripheral>_BASE_PTR, periphID, 1);
 *      @endcode
 */
#define LCD_PDD_SetAlternateWaveform(PeripheralBase, FrontplanePinIndex, Waveform) ( \
    LCD_WF_REG(PeripheralBase,(uint8_t)((uint8_t)(FrontplanePinIndex) >> 2U)) = \
     (uint32_t)(( \
      (uint32_t)(( \
       LCD_WF_REG(PeripheralBase,(uint8_t)((uint8_t)(FrontplanePinIndex) >> 2U))) & ( \
       (uint32_t)(~(uint32_t)(( \
        (uint32_t)0xFU) << ( \
        (uint8_t)((uint8_t)((uint8_t)(FrontplanePinIndex) & 0x3U) << 3U) + 4U)))))) | ( \
      (uint32_t)(( \
       (uint32_t)(Waveform)) << ( \
       (uint8_t)((uint8_t)((uint8_t)(FrontplanePinIndex) & 0x3U) << 3U) + 4U)))) \
  )

/* ----------------------------------------------------------------------------
   -- GetAlternateWaveform
   ---------------------------------------------------------------------------- */

/**
 * @brief Return value of the alternate frontplanes pins for the backplane phase.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param FrontplanePinIndex Wave form register index[0..63]. This parameter is
 *        of index type.
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: WF[].
 * @par Example:
 *      @code
 *      uint8_t result = LCD_PDD_GetAlternateWaveform(<peripheral>_BASE_PTR,
 *      periphID);
 *      @endcode
 */
#define LCD_PDD_GetAlternateWaveform(PeripheralBase, FrontplanePinIndex) ( \
    (uint8_t)(( \
     (uint8_t)(( \
      (uint8_t)(( \
       LCD_WF_REG(PeripheralBase,(uint8_t)((uint8_t)(FrontplanePinIndex) >> 2U))) >> ( \
       (uint8_t)((uint8_t)((uint8_t)(FrontplanePinIndex) & 0x3U) << 3U)))) >> ( \
      4U))) & ( \
     0xFU)) \
  )

/* ----------------------------------------------------------------------------
   -- EnableFastFrameRate
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables fast frame rate.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of fast frame rate function. This parameter is
 *        of "Global enumeration used for specifying general enable/disable states
 *        (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: LCD_GCR.
 * @par Example:
 *      @code
 *      LCD_PDD_EnableFastFrameRate(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define LCD_PDD_EnableFastFrameRate(PeripheralBase, State) ( \
    LCD_GCR_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(LCD_GCR_REG(PeripheralBase) & (uint32_t)(~(uint32_t)LCD_GCR_FFR_MASK))) | ( \
      (uint32_t)((uint32_t)(State) << LCD_GCR_FFR_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SelectAlternateClkSource
   ---------------------------------------------------------------------------- */

/**
 * @brief Select which alternate clock is used as LCD clock source.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param ClkSource Alternate clock source selection. This parameter is of
 *        "Clock source constants (for SetClkSource macro)." type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: LCD_GCR.
 * @par Example:
 *      @code
 *      LCD_PDD_SelectAlternateClkSource(<peripheral>_BASE_PTR, LCD_PDD_CLK1);
 *      @endcode
 */
#define LCD_PDD_SelectAlternateClkSource(PeripheralBase, ClkSource) ( \
    LCD_GCR_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(LCD_GCR_REG(PeripheralBase) & (uint32_t)(~(uint32_t)LCD_GCR_ALTSOURCE_MASK))) | ( \
      (uint32_t)(ClkSource))) \
  )
#endif  /* #if defined(LCD_PDD_H_) */

/* LCD_PDD.h, eof. */
