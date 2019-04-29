/*
  PDD layer implementation for peripheral type PMC
  (C) 2013 Freescale, Inc. All rights reserved.

  This file is static and it is generated from API-Factory
*/

#if !defined(PMC_PDD_H_)
#define PMC_PDD_H_

/* ----------------------------------------------------------------------------
   -- Test if supported MCU is active
   ---------------------------------------------------------------------------- */

#if !defined(MCU_ACTIVE)
  // No MCU is active
  #error PMC PDD library: No derivative is active. Place proper #include with PDD memory map before including PDD library.
#elif \
      !defined(MCU_MK22F12810) /* PMC */ && \
      !defined(MCU_MK22F25612) /* PMC */ && \
      !defined(MCU_MK22F51212) /* PMC */ && \
      !defined(MCU_MK24F12) /* PMC */ && \
      !defined(MCU_MK63F12) /* PMC */ && \
      !defined(MCU_MK63F12WS) /* PMC */ && \
      !defined(MCU_MK64F12) /* PMC */ && \
      !defined(MCU_MKE02Z2) /* PMC */ && \
      !defined(MCU_MKE02Z4) /* PMC */ && \
      !defined(MCU_SKEAZN642) /* PMC */ && \
      !defined(MCU_MKE04Z1284) /* PMC */ && \
      !defined(MCU_MKE04Z4) /* PMC */ && \
      !defined(MCU_SKEAZN84) /* PMC */ && \
      !defined(MCU_MKE06Z4) /* PMC */ && \
      !defined(MCU_MKV10Z7) /* PMC */ && \
      !defined(MCU_MKV31F12810) /* PMC */ && \
      !defined(MCU_MKV31F25612) /* PMC */ && \
      !defined(MCU_MKV31F51212) /* PMC */ && \
      !defined(MCU_MKW01Z4) /* PMC */ && \
      !defined(MCU_MKW21D5) /* PMC */ && \
      !defined(MCU_MKW21D5WS) /* PMC */ && \
      !defined(MCU_MKW22D5) /* PMC */ && \
      !defined(MCU_MKW22D5WS) /* PMC */ && \
      !defined(MCU_MKW24D5) /* PMC */ && \
      !defined(MCU_MKW24D5WS) /* PMC */ && \
      !defined(MCU_SKEAZ1284) /* PMC */
  // Unsupported MCU is active
  #error PMC PDD library: Unsupported derivative is active.
#endif

#include "PDD_Types.h"

/* ----------------------------------------------------------------------------
   -- Method symbol definitions
   ---------------------------------------------------------------------------- */

/* LVD trip point voltage constants. */
#define PMC_PDD_LVD_LOW  0U                      /**< Low trip point selected (V_LVD = V_LVDL). */
#define PMC_PDD_LVD_HIGH 0x1U                    /**< High trip point selected (V_LVD = V_LVDH). */

/* LVW trip point voltage constants. */
#define PMC_PDD_LVW_LOW   0U                     /**< Low trip point selected (V_LVW = V_LVW1) */
#define PMC_PDD_LVW_MID_1 0x1U                   /**< Mid 1 trip point selected (V_LVW = V_LVW2) */
#define PMC_PDD_LVW_MID_2 0x2U                   /**< Mid 2 trip point selected (V_LVW = V_LVW3) */
#define PMC_PDD_LVW_HIGH  0x3U                   /**< High trip point selected (V_LVW = V_LVW4) */


/* ----------------------------------------------------------------------------
   -- GetLowVoltageDetectFlag
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the low voltage detect flag.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: PMC_LVDSC1.
 * @par Example:
 *      @code
 *      uint8_t result = PMC_PDD_GetLowVoltageDetectFlag(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define PMC_PDD_GetLowVoltageDetectFlag(PeripheralBase) ( \
    (uint8_t)(PMC_LVDSC1_REG(PeripheralBase) & PMC_LVDSC1_LVDF_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- ClearLowVoltageDetectFlag
   ---------------------------------------------------------------------------- */

/**
 * @brief Clears low voltage detect flag.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: PMC_LVDSC1.
 * @par Example:
 *      @code
 *      PMC_PDD_ClearLowVoltageDetectFlag(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define PMC_PDD_ClearLowVoltageDetectFlag(PeripheralBase) ( \
    PMC_LVDSC1_REG(PeripheralBase) |= \
     PMC_LVDSC1_LVDACK_MASK \
  )

/* ----------------------------------------------------------------------------
   -- EnableLowVoltageDetectInterrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables the low voltage detect interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: PMC_LVDSC1.
 * @par Example:
 *      @code
 *      PMC_PDD_EnableLowVoltageDetectInterrupt(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define PMC_PDD_EnableLowVoltageDetectInterrupt(PeripheralBase) ( \
    PMC_LVDSC1_REG(PeripheralBase) |= \
     PMC_LVDSC1_LVDIE_MASK \
  )

/* ----------------------------------------------------------------------------
   -- DisableLowVoltageDetectInterrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Disables the low voltage detect interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: PMC_LVDSC1.
 * @par Example:
 *      @code
 *      PMC_PDD_DisableLowVoltageDetectInterrupt(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define PMC_PDD_DisableLowVoltageDetectInterrupt(PeripheralBase) ( \
    PMC_LVDSC1_REG(PeripheralBase) &= \
     (uint8_t)(~(uint8_t)PMC_LVDSC1_LVDIE_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- SetLowVoltageDetectReset
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables LVDF events to generate a hardware reset.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of the low voltage detect reset. This parameter
 *        is of "Global enumeration used for specifying general enable/disable
 *        states (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: PMC_LVDSC1.
 * @par Example:
 *      @code
 *      PMC_PDD_SetLowVoltageDetectReset(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define PMC_PDD_SetLowVoltageDetectReset(PeripheralBase, State) ( \
    PMC_LVDSC1_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(PMC_LVDSC1_REG(PeripheralBase) & (uint8_t)(~(uint8_t)PMC_LVDSC1_LVDRE_MASK))) | ( \
      (uint8_t)((uint8_t)(State) << PMC_LVDSC1_LVDRE_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SelectLowVoltageDetectVoltage
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MKE02Z2)) || (defined(MCU_MKE02Z4)) || (defined(MCU_MKE04Z1284)) || (defined(MCU_MKE04Z4)) || (defined(MCU_MKE06Z4)) || (defined(MCU_SKEAZ1284)) || (defined(MCU_SKEAZN642)) || (defined(MCU_SKEAZN84)))
/**
 * @brief Selects the low-voltage detect (LVD) trip point setting.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mode Parameter specifying the trip point voltage. This parameter is a
 *        1-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: PMC_LVDSC1, PMC_SPMSC2
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      PMC_PDD_SelectLowVoltageDetectVoltage(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
  #define PMC_PDD_SelectLowVoltageDetectVoltage(PeripheralBase, Mode) ( \
      PMC_SPMSC2_REG(PeripheralBase) = \
       (uint8_t)(( \
        (uint8_t)(PMC_SPMSC2_REG(PeripheralBase) & (uint8_t)(~(uint8_t)PMC_SPMSC2_LVDV_MASK))) | ( \
        (uint8_t)((uint8_t)(Mode) << PMC_SPMSC2_LVDV_SHIFT))) \
    )
#else /* (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW01Z4)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/**
 * @brief Selects the LVD trip point voltage (V_LVD).
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mode New value of the LVD trip point voltage. This parameter is of
 *        "LVD trip point voltage constants." type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: PMC_LVDSC1, PMC_SPMSC2
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      PMC_PDD_SelectLowVoltageDetectVoltage(<peripheral>_BASE_PTR,
 *      PMC_PDD_LVD_LOW);
 *      @endcode
 */
  #define PMC_PDD_SelectLowVoltageDetectVoltage(PeripheralBase, Mode) ( \
      PMC_LVDSC1_REG(PeripheralBase) = \
       (uint8_t)(( \
        (uint8_t)(PMC_LVDSC1_REG(PeripheralBase) & (uint8_t)(~(uint8_t)PMC_LVDSC1_LVDV_MASK))) | ( \
        (uint8_t)(Mode))) \
    )
#endif /* (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW01Z4)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */

/* ----------------------------------------------------------------------------
   -- WriteLVDStatusControl1Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes value to the PMC low voltage detect status and control 1
 * register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value New content of the PMC low voltage detect status and control 1
 *        register. This parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: PMC_LVDSC1.
 * @par Example:
 *      @code
 *      PMC_PDD_WriteLVDStatusControl1Reg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define PMC_PDD_WriteLVDStatusControl1Reg(PeripheralBase, Value) ( \
    PMC_LVDSC1_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadLVDStatusControl1Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the PMC low voltage detect status and control 1
 * register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: PMC_LVDSC1.
 * @par Example:
 *      @code
 *      uint8_t result =
 *      PMC_PDD_ReadLVDStatusControl1Reg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define PMC_PDD_ReadLVDStatusControl1Reg(PeripheralBase) ( \
    PMC_LVDSC1_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- GetLowVoltageWarningFlag
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the low voltage warning flag.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: PMC_LVDSC2.
 * @par Example:
 *      @code
 *      uint8_t result =
 *      PMC_PDD_GetLowVoltageWarningFlag(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define PMC_PDD_GetLowVoltageWarningFlag(PeripheralBase) ( \
    (uint8_t)(PMC_LVDSC2_REG(PeripheralBase) & PMC_LVDSC2_LVWF_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- ClearLowVoltageWarningFlag
   ---------------------------------------------------------------------------- */

/**
 * @brief Clears low voltage warning flag.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: PMC_LVDSC2.
 * @par Example:
 *      @code
 *      PMC_PDD_ClearLowVoltageWarningFlag(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define PMC_PDD_ClearLowVoltageWarningFlag(PeripheralBase) ( \
    PMC_LVDSC2_REG(PeripheralBase) |= \
     PMC_LVDSC2_LVWACK_MASK \
  )

/* ----------------------------------------------------------------------------
   -- EnableLowVoltageWarningInterrupt
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MKE02Z2)) || (defined(MCU_MKE02Z4)) || (defined(MCU_MKE04Z1284)) || (defined(MCU_MKE04Z4)) || (defined(MCU_MKE06Z4)) || (defined(MCU_SKEAZ1284)) || (defined(MCU_SKEAZN642)) || (defined(MCU_SKEAZN84)))
/**
 * @brief Enable or disable Low-Voltage warning interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Parameter specifying if low-voltage warning interrupt will be
 *        enabled or disabled. This parameter is of "Global enumeration used for
 *        specifying general enable/disable states (PDD_DISABLE and PDD_ENABLE
 *        defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: PMC_LVDSC2, PMC_SPMSC1
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      PMC_PDD_EnableLowVoltageWarningInterrupt(<peripheral>_BASE_PTR,
 *      PDD_DISABLE);
 *      @endcode
 */
  #define PMC_PDD_EnableLowVoltageWarningInterrupt(PeripheralBase, State) ( \
      PMC_SPMSC1_REG(PeripheralBase) = \
       (uint8_t)(( \
        (uint8_t)(( \
         PMC_SPMSC1_REG(PeripheralBase)) & (( \
         (uint8_t)(~(uint8_t)PMC_SPMSC1_LVWIE_MASK)) & ( \
         (uint8_t)(~(uint8_t)0x2U))))) | ( \
        (uint8_t)((uint8_t)(State) << PMC_SPMSC1_LVWIE_SHIFT))) \
    )
#else /* (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW01Z4)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/**
 * @brief Enables the low voltage warning interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: PMC_LVDSC2, PMC_SPMSC1
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      PMC_PDD_EnableLowVoltageWarningInterrupt(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define PMC_PDD_EnableLowVoltageWarningInterrupt(PeripheralBase) ( \
      PMC_LVDSC2_REG(PeripheralBase) |= \
       PMC_LVDSC2_LVWIE_MASK \
    )
#endif /* (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW01Z4)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */

/* ----------------------------------------------------------------------------
   -- DisableLowVoltageWarningInterrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Disables the low voltage warning interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: PMC_LVDSC2.
 * @par Example:
 *      @code
 *      PMC_PDD_DisableLowVoltageWarningInterrupt(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define PMC_PDD_DisableLowVoltageWarningInterrupt(PeripheralBase) ( \
    PMC_LVDSC2_REG(PeripheralBase) &= \
     (uint8_t)(~(uint8_t)PMC_LVDSC2_LVWIE_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- SelectLowVoltageWarningVoltage
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MKE02Z2)) || (defined(MCU_MKE02Z4)) || (defined(MCU_MKE04Z1284)) || (defined(MCU_MKE04Z4)) || (defined(MCU_MKE06Z4)) || (defined(MCU_SKEAZ1284)) || (defined(MCU_SKEAZN642)) || (defined(MCU_SKEAZN84)))
/**
 * @brief Selects the low-voltage warning (LVW) trip point setting.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mode Parameter specifying the trip point voltage. This parameter is a
 *        2-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: PMC_LVDSC2, PMC_SPMSC2
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      PMC_PDD_SelectLowVoltageWarningVoltage(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
  #define PMC_PDD_SelectLowVoltageWarningVoltage(PeripheralBase, Mode) ( \
      PMC_SPMSC2_REG(PeripheralBase) = \
       (uint8_t)(( \
        (uint8_t)(PMC_SPMSC2_REG(PeripheralBase) & (uint8_t)(~(uint8_t)PMC_SPMSC2_LVWV_MASK))) | ( \
        (uint8_t)((uint8_t)(Mode) << PMC_SPMSC2_LVWV_SHIFT))) \
    )
#else /* (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW01Z4)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/**
 * @brief Selects the LVW trip point voltage (VLVW).
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mode New value of the LVW trip point voltage. This parameter is of
 *        "LVW trip point voltage constants." type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: PMC_LVDSC2, PMC_SPMSC2
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      PMC_PDD_SelectLowVoltageWarningVoltage(<peripheral>_BASE_PTR,
 *      PMC_PDD_LVW_LOW);
 *      @endcode
 */
  #define PMC_PDD_SelectLowVoltageWarningVoltage(PeripheralBase, Mode) ( \
      PMC_LVDSC2_REG(PeripheralBase) = \
       (uint8_t)(( \
        (uint8_t)(PMC_LVDSC2_REG(PeripheralBase) & (uint8_t)(~(uint8_t)PMC_LVDSC2_LVWV_MASK))) | ( \
        (uint8_t)(Mode))) \
    )
#endif /* (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW01Z4)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */

/* ----------------------------------------------------------------------------
   -- WriteLVDStatusControl2Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes value to the PMC low voltage detect status and control 2
 * register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value New content of the PMC low voltage detect status and control 2
 *        register. This parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: PMC_LVDSC2.
 * @par Example:
 *      @code
 *      PMC_PDD_WriteLVDStatusControl2Reg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define PMC_PDD_WriteLVDStatusControl2Reg(PeripheralBase, Value) ( \
    PMC_LVDSC2_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadLVDStatusControl2Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the PMC low voltage detect status and control 2
 * register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: PMC_LVDSC2.
 * @par Example:
 *      @code
 *      uint8_t result =
 *      PMC_PDD_ReadLVDStatusControl2Reg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define PMC_PDD_ReadLVDStatusControl2Reg(PeripheralBase) ( \
    PMC_LVDSC2_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- SetBandgapInVLPxOperation
   ---------------------------------------------------------------------------- */

/**
 * @brief Controls whether the bandgap is enabled in lower power modes of
 * operation (VLPx, and VLLSx).
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of the bandgap. This parameter is of "Global
 *        enumeration used for specifying general enable/disable states (PDD_DISABLE
 *        and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: PMC_REGSC.
 * @par Example:
 *      @code
 *      PMC_PDD_SetBandgapInVLPxOperation(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define PMC_PDD_SetBandgapInVLPxOperation(PeripheralBase, State) ( \
    PMC_REGSC_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(( \
       PMC_REGSC_REG(PeripheralBase)) & (( \
       (uint8_t)(~(uint8_t)PMC_REGSC_BGEN_MASK)) & ( \
       (uint8_t)(~(uint8_t)PMC_REGSC_ACKISO_MASK))))) | ( \
      (uint8_t)((uint8_t)(State) << PMC_REGSC_BGEN_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- GetAcknowledgeIsolationFlag
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the acknowledge isolation flag.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: PMC_REGSC.
 * @par Example:
 *      @code
 *      uint8_t result =
 *      PMC_PDD_GetAcknowledgeIsolationFlag(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define PMC_PDD_GetAcknowledgeIsolationFlag(PeripheralBase) ( \
    (uint8_t)(PMC_REGSC_REG(PeripheralBase) & PMC_REGSC_ACKISO_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- ClearAcknowledgeIsolationFlag
   ---------------------------------------------------------------------------- */

/**
 * @brief Clears acknowledge isolation flag.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: PMC_REGSC.
 * @par Example:
 *      @code
 *      PMC_PDD_ClearAcknowledgeIsolationFlag(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define PMC_PDD_ClearAcknowledgeIsolationFlag(PeripheralBase) ( \
    PMC_REGSC_REG(PeripheralBase) |= \
     PMC_REGSC_ACKISO_MASK \
  )

/* ----------------------------------------------------------------------------
   -- GetRegulatorInRunRegulationStatus
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the regulator in run regulation status.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: PMC_REGSC.
 * @par Example:
 *      @code
 *      uint8_t result =
 *      PMC_PDD_GetRegulatorInRunRegulationStatus(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define PMC_PDD_GetRegulatorInRunRegulationStatus(PeripheralBase) ( \
    (uint8_t)(PMC_REGSC_REG(PeripheralBase) & PMC_REGSC_REGONS_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- SetBandgapBuffer
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables the bandgap buffer.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of the bandgap buffer. This parameter is of
 *        "Global enumeration used for specifying general enable/disable states
 *        (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: PMC_REGSC.
 * @par Example:
 *      @code
 *      PMC_PDD_SetBandgapBuffer(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define PMC_PDD_SetBandgapBuffer(PeripheralBase, State) ( \
    PMC_REGSC_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(( \
       PMC_REGSC_REG(PeripheralBase)) & (( \
       (uint8_t)(~(uint8_t)PMC_REGSC_BGBE_MASK)) & ( \
       (uint8_t)(~(uint8_t)PMC_REGSC_ACKISO_MASK))))) | ( \
      (uint8_t)(State))) \
  )

/* ----------------------------------------------------------------------------
   -- WriteRegulatorStatusControlReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes value to the PMC regulator status and control register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value New content of the PMC regulator status and control register.
 *        This parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: PMC_REGSC.
 * @par Example:
 *      @code
 *      PMC_PDD_WriteRegulatorStatusControlReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define PMC_PDD_WriteRegulatorStatusControlReg(PeripheralBase, Value) ( \
    PMC_REGSC_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadRegulatorStatusControlReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the PMC regulator status and control register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: PMC_REGSC.
 * @par Example:
 *      @code
 *      uint8_t result =
 *      PMC_PDD_ReadRegulatorStatusControlReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define PMC_PDD_ReadRegulatorStatusControlReg(PeripheralBase) ( \
    PMC_REGSC_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- EnableLowVoltageDetectReset
   ---------------------------------------------------------------------------- */

/**
 * @brief Enable or disable Low-Voltage Detect Reset.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Parameter specifying if low-voltage reset will be enabled or
 *        disabled. This parameter is of "Global enumeration used for specifying
 *        general enable/disable states (PDD_DISABLE and PDD_ENABLE defined in
 *        PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: PMC_SPMSC1.
 * @par Example:
 *      @code
 *      PMC_PDD_EnableLowVoltageDetectReset(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define PMC_PDD_EnableLowVoltageDetectReset(PeripheralBase, State) ( \
    PMC_SPMSC1_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(( \
       PMC_SPMSC1_REG(PeripheralBase)) & (( \
       (uint8_t)(~(uint8_t)PMC_SPMSC1_LVDRE_MASK)) & ( \
       (uint8_t)(~(uint8_t)0x2U))))) | ( \
      (uint8_t)((uint8_t)(State) << PMC_SPMSC1_LVDRE_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- EnableLowVoltageStopReset
   ---------------------------------------------------------------------------- */

/**
 * @brief Enable or disable Low-Voltage Stop Reset.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Parameter specifying if low-voltage stop will be enabled or
 *        disabled. This parameter is of "Global enumeration used for specifying
 *        general enable/disable states (PDD_DISABLE and PDD_ENABLE defined in
 *        PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: PMC_SPMSC1.
 * @par Example:
 *      @code
 *      PMC_PDD_EnableLowVoltageStopReset(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define PMC_PDD_EnableLowVoltageStopReset(PeripheralBase, State) ( \
    PMC_SPMSC1_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(( \
       PMC_SPMSC1_REG(PeripheralBase)) & (( \
       (uint8_t)(~(uint8_t)PMC_SPMSC1_LVDSE_MASK)) & ( \
       (uint8_t)(~(uint8_t)0x2U))))) | ( \
      (uint8_t)((uint8_t)(State) << PMC_SPMSC1_LVDSE_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- EnableLowVoltageDetect
   ---------------------------------------------------------------------------- */

/**
 * @brief Enable or disable Low-Voltage Detect.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Parameter specifying if low-voltage detect will be enabled or
 *        disabled. This parameter is of "Global enumeration used for specifying
 *        general enable/disable states (PDD_DISABLE and PDD_ENABLE defined in
 *        PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: PMC_SPMSC1.
 * @par Example:
 *      @code
 *      PMC_PDD_EnableLowVoltageDetect(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define PMC_PDD_EnableLowVoltageDetect(PeripheralBase, State) ( \
    PMC_SPMSC1_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(( \
       PMC_SPMSC1_REG(PeripheralBase)) & (( \
       (uint8_t)(~(uint8_t)PMC_SPMSC1_LVDE_MASK)) & ( \
       (uint8_t)(~(uint8_t)0x2U))))) | ( \
      (uint8_t)((uint8_t)(State) << PMC_SPMSC1_LVDE_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- EnableBandgapBuffer
   ---------------------------------------------------------------------------- */

/**
 * @brief Enable or disable Bandgap Buffer.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Parameter specifying if bandgap buffer will be enabled or
 *        disabled. This parameter is of "Global enumeration used for specifying
 *        general enable/disable states (PDD_DISABLE and PDD_ENABLE defined in
 *        PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: PMC_SPMSC1.
 * @par Example:
 *      @code
 *      PMC_PDD_EnableBandgapBuffer(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define PMC_PDD_EnableBandgapBuffer(PeripheralBase, State) ( \
    PMC_SPMSC1_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(( \
       PMC_SPMSC1_REG(PeripheralBase)) & (( \
       (uint8_t)(~(uint8_t)PMC_SPMSC1_BGBE_MASK)) & ( \
       (uint8_t)(~(uint8_t)0x2U))))) | ( \
      (uint8_t)(State))) \
  )

/* ----------------------------------------------------------------------------
   -- ClearFlag
   ---------------------------------------------------------------------------- */

/**
 * @brief Clears the Low-Voltage Warning Flag.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: PMC_SPMSC1.
 * @par Example:
 *      @code
 *      PMC_PDD_ClearFlag(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define PMC_PDD_ClearFlag(PeripheralBase) ( \
    PMC_SPMSC1_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(PMC_SPMSC1_REG(PeripheralBase) | PMC_SPMSC1_LVWACK_MASK)) & ( \
      (uint8_t)(~(uint8_t)0x2U))) \
  )
#endif  /* #if defined(PMC_PDD_H_) */

/* PMC_PDD.h, eof. */
