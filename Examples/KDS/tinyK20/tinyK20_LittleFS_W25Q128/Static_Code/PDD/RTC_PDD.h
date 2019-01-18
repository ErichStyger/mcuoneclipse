/*
  PDD layer implementation for peripheral type RTC
  (C) 2013 Freescale, Inc. All rights reserved.

  This file is static and it is generated from API-Factory
*/

#if !defined(RTC_PDD_H_)
#define RTC_PDD_H_

/* ----------------------------------------------------------------------------
   -- Test if supported MCU is active
   ---------------------------------------------------------------------------- */

#if !defined(MCU_ACTIVE)
  // No MCU is active
  #error RTC PDD library: No derivative is active. Place proper #include with PDD memory map before including PDD library.
#elif \
      !defined(MCU_MK10D10) /* RTC */ && \
      !defined(MCU_MK10D5) /* RTC */ && \
      !defined(MCU_MK10D7) /* RTC */ && \
      !defined(MCU_MK10F12) /* RTC */ && \
      !defined(MCU_MK10DZ10) /* RTC */ && \
      !defined(MCU_MK11DA5) /* RTC */ && \
      !defined(MCU_MK11DA5WS) /* RTC */ && \
      !defined(MCU_MK11D5) /* RTC */ && \
      !defined(MCU_MK11D5WS) /* RTC */ && \
      !defined(MCU_MK12D5) /* RTC */ && \
      !defined(MCU_MK20D10) /* RTC */ && \
      !defined(MCU_MK20D5) /* RTC */ && \
      !defined(MCU_MK20D7) /* RTC */ && \
      !defined(MCU_MK20F12) /* RTC */ && \
      !defined(MCU_MK20DZ10) /* RTC */ && \
      !defined(MCU_MK21DA5) /* RTC */ && \
      !defined(MCU_MK21DA5WS) /* RTC */ && \
      !defined(MCU_MK21D5) /* RTC */ && \
      !defined(MCU_MK21D5WS) /* RTC */ && \
      !defined(MCU_MK21FA12) /* RTC */ && \
      !defined(MCU_MK21FA12WS) /* RTC */ && \
      !defined(MCU_MK21F12) /* RTC */ && \
      !defined(MCU_MK21F12WS) /* RTC */ && \
      !defined(MCU_MK22D5) /* RTC */ && \
      !defined(MCU_MK22F12810) /* RTC */ && \
      !defined(MCU_MK22F12) /* RTC */ && \
      !defined(MCU_MK22F25612) /* RTC */ && \
      !defined(MCU_MK22F51212) /* RTC */ && \
      !defined(MCU_MK24F12) /* RTC */ && \
      !defined(MCU_MK30D10) /* RTC */ && \
      !defined(MCU_MK30D7) /* RTC */ && \
      !defined(MCU_MK30DZ10) /* RTC */ && \
      !defined(MCU_MK40D10) /* RTC */ && \
      !defined(MCU_MK40D7) /* RTC */ && \
      !defined(MCU_MK40DZ10) /* RTC */ && \
      !defined(MCU_MK40X256VMD100) /* RTC */ && \
      !defined(MCU_MK50D10) /* RTC */ && \
      !defined(MCU_MK50D7) /* RTC */ && \
      !defined(MCU_MK50DZ10) /* RTC */ && \
      !defined(MCU_MK51D10) /* RTC */ && \
      !defined(MCU_MK51D7) /* RTC */ && \
      !defined(MCU_MK51DZ10) /* RTC */ && \
      !defined(MCU_MK52D10) /* RTC */ && \
      !defined(MCU_MK52DZ10) /* RTC */ && \
      !defined(MCU_MK53D10) /* RTC */ && \
      !defined(MCU_MK53DZ10) /* RTC */ && \
      !defined(MCU_MK60D10) /* RTC */ && \
      !defined(MCU_MK60F12) /* RTC */ && \
      !defined(MCU_MK60F15) /* RTC */ && \
      !defined(MCU_MK60DZ10) /* RTC */ && \
      !defined(MCU_MK60N512VMD100) /* RTC */ && \
      !defined(MCU_MK61F12) /* RTC */ && \
      !defined(MCU_MK61F15) /* RTC */ && \
      !defined(MCU_MK61F12WS) /* RTC */ && \
      !defined(MCU_MK61F15WS) /* RTC */ && \
      !defined(MCU_MK63F12) /* RTC */ && \
      !defined(MCU_MK63F12WS) /* RTC */ && \
      !defined(MCU_MK64F12) /* RTC */ && \
      !defined(MCU_MK70F12) /* RTC */ && \
      !defined(MCU_MK70F15) /* RTC */ && \
      !defined(MCU_MK70F12WS) /* RTC */ && \
      !defined(MCU_MK70F15WS) /* RTC */ && \
      !defined(MCU_MKL04Z4) /* RTC */ && \
      !defined(MCU_MKL05Z4) /* RTC */ && \
      !defined(MCU_MKL14Z4) /* RTC */ && \
      !defined(MCU_MKL15Z4) /* RTC */ && \
      !defined(MCU_MKL16Z4) /* RTC */ && \
      !defined(MCU_MKL24Z4) /* RTC */ && \
      !defined(MCU_MKL25Z4) /* RTC */ && \
      !defined(MCU_MKL26Z4) /* RTC */ && \
      !defined(MCU_MKL34Z4) /* RTC */ && \
      !defined(MCU_MKL36Z4) /* RTC */ && \
      !defined(MCU_MKL46Z4) /* RTC */ && \
      !defined(MCU_MKW01Z4) /* RTC */ && \
      !defined(MCU_MKW21D5) /* RTC */ && \
      !defined(MCU_MKW21D5WS) /* RTC */ && \
      !defined(MCU_MKW22D5) /* RTC */ && \
      !defined(MCU_MKW22D5WS) /* RTC */ && \
      !defined(MCU_MKW24D5) /* RTC */ && \
      !defined(MCU_MKW24D5WS) /* RTC */
  // Unsupported MCU is active
  #error RTC PDD library: Unsupported derivative is active.
#endif

#include "PDD_Types.h"

/* ----------------------------------------------------------------------------
   -- Method symbol definitions
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)))
/* Interrupt masks */
  #define RTC_PDD_MOF_INT RTC_SR_MOF_MASK          /**< Monotonic overflow interrupt mask */
  #define RTC_PDD_TAF_INT RTC_SR_TAF_MASK          /**< Alarm interrupt mask */
  #define RTC_PDD_TOF_INT RTC_SR_TOF_MASK          /**< Timer overflow interrupt mask */
  #define RTC_PDD_TIF_INT RTC_SR_TIF_MASK          /**< Time invalid interrupt mask */

#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK63F12)) || (defined(MCU_MK64F12)) || (defined(MCU_MKL04Z4)) || (defined(MCU_MKL05Z4)) || (defined(MCU_MKL14Z4)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL16Z4)) || (defined(MCU_MKL24Z4)) || (defined(MCU_MKL25Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL34Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKW01Z4)) */
/* Interrupt masks */
  #define RTC_PDD_TAF_INT RTC_SR_TAF_MASK          /**< Alarm interrupt mask */
  #define RTC_PDD_TOF_INT RTC_SR_TOF_MASK          /**< Timer overflow interrupt mask */
  #define RTC_PDD_TIF_INT RTC_SR_TIF_MASK          /**< Time invalid interrupt mask */

#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK63F12)) || (defined(MCU_MK64F12)) || (defined(MCU_MKL04Z4)) || (defined(MCU_MKL05Z4)) || (defined(MCU_MKL14Z4)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL16Z4)) || (defined(MCU_MKL24Z4)) || (defined(MCU_MKL25Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL34Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKW01Z4)) */
/* Tamper interrupt masks */
#define RTC_PDD_TMF_INT RTC_TDR_TMF_MASK         /**< Test mode tamper interrupt mask */
#define RTC_PDD_FSF_INT RTC_TDR_FSF_MASK         /**< Flash security tamper interrupt mask */
#define RTC_PDD_TTF_INT RTC_TDR_TTF_MASK         /**< Temperature tamper interrupt mask */
#define RTC_PDD_CTF_INT RTC_TDR_CTF_MASK         /**< Clock tamper interrupt mask */
#define RTC_PDD_VTF_INT RTC_TDR_VTF_MASK         /**< Volatge tamper interrupt mask */
#define RTC_PDD_DTF_INT RTC_TDR_DTF_MASK         /**< DryIce tamper interrupt mask */

/* WakeUpPinState constants */
#define RTC_PDD_ASSERTED     0x8U                /**< Pin is asserted */
#define RTC_PDD_NOT_ASSERTED 0U                  /**< Pin is not asserted */


/* ----------------------------------------------------------------------------
   -- ReadTimeSecondsReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the Time seconds register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: RTC_TSR.
 * @par Example:
 *      @code
 *      uint32_t result = RTC_PDD_ReadTimeSecondsReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define RTC_PDD_ReadTimeSecondsReg(PeripheralBase) ( \
    RTC_TSR_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteTimeSecondsReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes value to the Time seconds register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value written to the Time seconds register. This parameter is a
 *        32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: RTC_TSR.
 * @par Example:
 *      @code
 *      RTC_PDD_WriteTimeSecondsReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define RTC_PDD_WriteTimeSecondsReg(PeripheralBase, Value) ( \
    RTC_TSR_REG(PeripheralBase) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadTimePrescalerReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the Time prescaler register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: RTC_TPR.
 * @par Example:
 *      @code
 *      uint32_t result = RTC_PDD_ReadTimePrescalerReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define RTC_PDD_ReadTimePrescalerReg(PeripheralBase) ( \
    RTC_TPR_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteTimePrescalerReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes value to the Time prescaler register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value written to the Time prescaler register. This parameter is
 *        a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: RTC_TPR.
 * @par Example:
 *      @code
 *      RTC_PDD_WriteTimePrescalerReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define RTC_PDD_WriteTimePrescalerReg(PeripheralBase, Value) ( \
    RTC_TPR_REG(PeripheralBase) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadTimeAlarmReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the Time alarm register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: RTC_TAR.
 * @par Example:
 *      @code
 *      uint32_t result = RTC_PDD_ReadTimeAlarmReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define RTC_PDD_ReadTimeAlarmReg(PeripheralBase) ( \
    RTC_TAR_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteTimeAlarmReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes value to the Time alarm register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value written to the Time alarm register. This parameter is a
 *        32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: RTC_TAR.
 * @par Example:
 *      @code
 *      RTC_PDD_WriteTimeAlarmReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define RTC_PDD_WriteTimeAlarmReg(PeripheralBase, Value) ( \
    RTC_TAR_REG(PeripheralBase) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadTimeCompensationReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the Time compensation register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: RTC_TCR.
 * @par Example:
 *      @code
 *      uint32_t result =
 *      RTC_PDD_ReadTimeCompensationReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define RTC_PDD_ReadTimeCompensationReg(PeripheralBase) ( \
    RTC_TCR_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteTimeCompensationReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes value to the Time compensation register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value written to the Time compensation register. This parameter
 *        is a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: RTC_TCR.
 * @par Example:
 *      @code
 *      RTC_PDD_WriteTimeCompensationReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define RTC_PDD_WriteTimeCompensationReg(PeripheralBase, Value) ( \
    RTC_TCR_REG(PeripheralBase) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadControlReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the Control register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: RTC_CR.
 * @par Example:
 *      @code
 *      uint32_t result = RTC_PDD_ReadControlReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define RTC_PDD_ReadControlReg(PeripheralBase) ( \
    RTC_CR_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteControlReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes value to the Control register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value written to the Control register. This parameter is a
 *        32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: RTC_CR.
 * @par Example:
 *      @code
 *      RTC_PDD_WriteControlReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define RTC_PDD_WriteControlReg(PeripheralBase, Value) ( \
    RTC_CR_REG(PeripheralBase) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- EnableUpdateMode
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables/disables update mode.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state. This parameter is of "Global enumeration used
 *        for specifying general enable/disable states (PDD_DISABLE and PDD_ENABLE
 *        defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: RTC_CR.
 * @par Example:
 *      @code
 *      RTC_PDD_EnableUpdateMode(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define RTC_PDD_EnableUpdateMode(PeripheralBase, State) ( \
    ((State) == PDD_DISABLE) ? ( \
      RTC_CR_REG(PeripheralBase) = \
       (uint32_t)(( \
        (uint32_t)(RTC_CR_REG(PeripheralBase) | RTC_CR_UM_MASK)) & ( \
        (uint32_t)(~(uint32_t)0x4000U)))) : ( \
      RTC_CR_REG(PeripheralBase) &= \
       (uint32_t)((uint32_t)(~(uint32_t)RTC_CR_UM_MASK) & (uint32_t)(~(uint32_t)0x4000U))) \
  )

/* ----------------------------------------------------------------------------
   -- EnableSupervisorAccess
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables/disables supervisor accesss.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state. This parameter is of "Global enumeration used
 *        for specifying general enable/disable states (PDD_DISABLE and PDD_ENABLE
 *        defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: RTC_CR.
 * @par Example:
 *      @code
 *      RTC_PDD_EnableSupervisorAccess(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define RTC_PDD_EnableSupervisorAccess(PeripheralBase, State) ( \
    ((State) == PDD_DISABLE) ? ( \
      RTC_CR_REG(PeripheralBase) = \
       (uint32_t)(( \
        (uint32_t)(RTC_CR_REG(PeripheralBase) | RTC_CR_SUP_MASK)) & ( \
        (uint32_t)(~(uint32_t)0x4000U)))) : ( \
      RTC_CR_REG(PeripheralBase) &= \
       (uint32_t)((uint32_t)(~(uint32_t)RTC_CR_SUP_MASK) & (uint32_t)(~(uint32_t)0x4000U))) \
  )

/* ----------------------------------------------------------------------------
   -- EnableWakeupPin
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables/disables wakeup pin.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state. This parameter is of "Global enumeration used
 *        for specifying general enable/disable states (PDD_DISABLE and PDD_ENABLE
 *        defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: RTC_CR.
 * @par Example:
 *      @code
 *      RTC_PDD_EnableWakeupPin(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define RTC_PDD_EnableWakeupPin(PeripheralBase, State) ( \
    ((State) == PDD_DISABLE) ? ( \
      RTC_CR_REG(PeripheralBase) = \
       (uint32_t)(( \
        (uint32_t)(RTC_CR_REG(PeripheralBase) | RTC_CR_WPE_MASK)) & ( \
        (uint32_t)(~(uint32_t)0x4000U)))) : ( \
      RTC_CR_REG(PeripheralBase) &= \
       (uint32_t)((uint32_t)(~(uint32_t)RTC_CR_WPE_MASK) & (uint32_t)(~(uint32_t)0x4000U))) \
  )

/* ----------------------------------------------------------------------------
   -- ForceSwReset
   ---------------------------------------------------------------------------- */

/**
 * @brief Forces the equivalent of a VBAT POR to the rest of the RTC module,
 * except the access control registers.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: RTC_CR.
 * @par Example:
 *      @code
 *      RTC_PDD_ForceSwReset(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define RTC_PDD_ForceSwReset(PeripheralBase) ( \
    (RTC_CR_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(RTC_CR_REG(PeripheralBase) | RTC_CR_SWR_MASK)) & ( \
      (uint32_t)(~(uint32_t)0x4000U)))), \
    (RTC_CR_REG(PeripheralBase) &= \
     (uint32_t)((uint32_t)(~(uint32_t)RTC_CR_SWR_MASK) & (uint32_t)(~(uint32_t)0x4000U))) \
  )

/* ----------------------------------------------------------------------------
   -- GetRtcInterruptMask
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the RTC interrupt enable register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: RTC_IER.
 * @par Example:
 *      @code
 *      uint32_t result = RTC_PDD_GetRtcInterruptMask(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define RTC_PDD_GetRtcInterruptMask(PeripheralBase) ( \
    RTC_IER_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- SetRtcInterruptMask
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables RTC interrupts defined by the Mask parameter.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mask Imterrupt mask. This parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: RTC_IER.
 * @par Example:
 *      @code
 *      RTC_PDD_SetRtcInterruptMask(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define RTC_PDD_SetRtcInterruptMask(PeripheralBase, Mask) ( \
    RTC_IER_REG(PeripheralBase) = \
     (uint32_t)(Mask) \
  )

/* ----------------------------------------------------------------------------
   -- EnableSecondsInterrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables the Seconds interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: RTC_IER.
 * @par Example:
 *      @code
 *      RTC_PDD_EnableSecondsInterrupt(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define RTC_PDD_EnableSecondsInterrupt(PeripheralBase) ( \
    RTC_IER_REG(PeripheralBase) |= \
     RTC_IER_TSIE_MASK \
  )

/* ----------------------------------------------------------------------------
   -- EnableAlarmInterrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables the Alarm interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: RTC_IER.
 * @par Example:
 *      @code
 *      RTC_PDD_EnableAlarmInterrupt(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define RTC_PDD_EnableAlarmInterrupt(PeripheralBase) ( \
    RTC_IER_REG(PeripheralBase) |= \
     RTC_IER_TAIE_MASK \
  )

/* ----------------------------------------------------------------------------
   -- EnableTimeOverflowInterrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables the Time overflow interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: RTC_IER.
 * @par Example:
 *      @code
 *      RTC_PDD_EnableTimeOverflowInterrupt(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define RTC_PDD_EnableTimeOverflowInterrupt(PeripheralBase) ( \
    RTC_IER_REG(PeripheralBase) |= \
     RTC_IER_TOIE_MASK \
  )

/* ----------------------------------------------------------------------------
   -- EnableTimeInvalidInterrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables the Time invalid interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: RTC_IER.
 * @par Example:
 *      @code
 *      RTC_PDD_EnableTimeInvalidInterrupt(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define RTC_PDD_EnableTimeInvalidInterrupt(PeripheralBase) ( \
    RTC_IER_REG(PeripheralBase) |= \
     RTC_IER_TIIE_MASK \
  )

/* ----------------------------------------------------------------------------
   -- DisableSecondsInterrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Disables the Seconds interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: RTC_IER.
 * @par Example:
 *      @code
 *      RTC_PDD_DisableSecondsInterrupt(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define RTC_PDD_DisableSecondsInterrupt(PeripheralBase) ( \
    RTC_IER_REG(PeripheralBase) &= \
     (uint32_t)(~(uint32_t)RTC_IER_TSIE_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- DisableAlarmInterrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Disables the Alarm interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: RTC_IER.
 * @par Example:
 *      @code
 *      RTC_PDD_DisableAlarmInterrupt(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define RTC_PDD_DisableAlarmInterrupt(PeripheralBase) ( \
    RTC_IER_REG(PeripheralBase) &= \
     (uint32_t)(~(uint32_t)RTC_IER_TAIE_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- DisableTimeOverflowInterrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Disables the Time overflow interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: RTC_IER.
 * @par Example:
 *      @code
 *      RTC_PDD_DisableTimeOverflowInterrupt(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define RTC_PDD_DisableTimeOverflowInterrupt(PeripheralBase) ( \
    RTC_IER_REG(PeripheralBase) &= \
     (uint32_t)(~(uint32_t)RTC_IER_TOIE_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- DisableTimeInvalidInterrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Disables the Time invalid interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: RTC_IER.
 * @par Example:
 *      @code
 *      RTC_PDD_DisableTimeInvalidInterrupt(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define RTC_PDD_DisableTimeInvalidInterrupt(PeripheralBase) ( \
    RTC_IER_REG(PeripheralBase) &= \
     (uint32_t)(~(uint32_t)RTC_IER_TIIE_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- SetWakeUpPinState
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets wake-up pin state.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state. This parameter is of "WakeUpPinState constants"
 *        type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: RTC_SR.
 * @par Example:
 *      @code
 *      RTC_PDD_SetWakeUpPinState(<peripheral>_BASE_PTR, RTC_PDD_ASSERTED);
 *      @endcode
 */
#define RTC_PDD_SetWakeUpPinState(PeripheralBase, State) ( \
    RTC_SR_REG(PeripheralBase) = \
     (uint32_t)(State) \
  )

/* ----------------------------------------------------------------------------
   -- ReadStatusReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the Status register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Use constants from group "Interrupt masks" for processing return
 *         value.
 * @remarks The macro accesses the following registers: RTC_SR.
 * @par Example:
 *      @code
 *      uint32_t result = RTC_PDD_ReadStatusReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define RTC_PDD_ReadStatusReg(PeripheralBase) ( \
    RTC_SR_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteStatusReg
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)))
/**
 * @brief Writes value to the Status register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value written to the Status register. Use constants from group
 *        "Interrupt masks". This parameter is 32 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: RTC_SR.
 * @par Example:
 *      @code
 *      RTC_PDD_WriteStatusReg(<peripheral>_BASE_PTR, RTC_PDD_MOF_INT);
 *      @endcode
 */
  #define RTC_PDD_WriteStatusReg(PeripheralBase, Value) ( \
      RTC_SR_REG(PeripheralBase) = \
       (uint32_t)(Value) \
    )
#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK63F12)) || (defined(MCU_MK64F12)) || (defined(MCU_MKL04Z4)) || (defined(MCU_MKL05Z4)) || (defined(MCU_MKL14Z4)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL16Z4)) || (defined(MCU_MKL24Z4)) || (defined(MCU_MKL25Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL34Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKW01Z4)) */
/**
 * @brief Writes value to the Status register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value written to the Status register. Use constants from group
 *        "Interrupt masks". This parameter is 32 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: RTC_SR.
 * @par Example:
 *      @code
 *      RTC_PDD_WriteStatusReg(<peripheral>_BASE_PTR, RTC_PDD_TAF_INT);
 *      @endcode
 */
  #define RTC_PDD_WriteStatusReg(PeripheralBase, Value) ( \
      RTC_SR_REG(PeripheralBase) = \
       (uint32_t)(Value) \
    )
#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK63F12)) || (defined(MCU_MK64F12)) || (defined(MCU_MKL04Z4)) || (defined(MCU_MKL05Z4)) || (defined(MCU_MKL14Z4)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL16Z4)) || (defined(MCU_MKL24Z4)) || (defined(MCU_MKL25Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL34Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKW01Z4)) */

/* ----------------------------------------------------------------------------
   -- EnableCounter
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables/disables seconds counter.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state. This parameter is of "Global enumeration used
 *        for specifying general enable/disable states (PDD_DISABLE and PDD_ENABLE
 *        defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: RTC_SR.
 * @par Example:
 *      @code
 *      RTC_PDD_EnableCounter(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define RTC_PDD_EnableCounter(PeripheralBase, State) ( \
    ((State) == PDD_DISABLE) ? ( \
      RTC_SR_REG(PeripheralBase) = \
       0U) : ( \
      RTC_SR_REG(PeripheralBase) = \
       0x10U) \
  )

/* ----------------------------------------------------------------------------
   -- GetEnableCounterStatus
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns zero if the Time counter is disabled else return non-zero
 * value.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: RTC_SR.
 * @par Example:
 *      @code
 *      uint32_t result = RTC_PDD_GetEnableCounterStatus(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define RTC_PDD_GetEnableCounterStatus(PeripheralBase) ( \
    (uint32_t)(RTC_SR_REG(PeripheralBase) & RTC_SR_TCE_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- ReadLockReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the Lock register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: RTC_LR.
 * @par Example:
 *      @code
 *      uint32_t result = RTC_PDD_ReadLockReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define RTC_PDD_ReadLockReg(PeripheralBase) ( \
    RTC_LR_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteLockReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes value to the Lock register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value written to the Lock register. This parameter is a 32-bit
 *        value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: RTC_LR.
 * @par Example:
 *      @code
 *      RTC_PDD_WriteLockReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define RTC_PDD_WriteLockReg(PeripheralBase, Value) ( \
    RTC_LR_REG(PeripheralBase) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- LockStatusReg
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F15)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F15)))
/**
 * @brief The lock register is used to block write accesses to certain registers
 * until the next VBAT_POR or software reset.Write accesses to a locked register
 * are ignored and do not generate a bus error.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: RTC_LR.
 * @par Example:
 *      @code
 *      RTC_PDD_LockStatusReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define RTC_PDD_LockStatusReg(PeripheralBase) ( \
      RTC_LR_REG(PeripheralBase) = \
       (uint32_t)(( \
        (uint32_t)(RTC_LR_REG(PeripheralBase) & (uint32_t)(~(uint32_t)RTC_LR_SRL_MASK))) | ( \
        0xF000U)) \
    )
#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKL04Z4)) || (defined(MCU_MKL05Z4)) || (defined(MCU_MKL14Z4)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL16Z4)) || (defined(MCU_MKL24Z4)) || (defined(MCU_MKL25Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL34Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKW01Z4)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/**
 * @brief The lock register is used to block write accesses to certain registers
 * until the next VBAT_POR or software reset.Write accesses to a locked register
 * are ignored and do not generate a bus error.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: RTC_LR.
 * @par Example:
 *      @code
 *      RTC_PDD_LockStatusReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define RTC_PDD_LockStatusReg(PeripheralBase) ( \
      RTC_LR_REG(PeripheralBase) &= \
       (uint32_t)(~(uint32_t)RTC_LR_SRL_MASK) \
    )
#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKL04Z4)) || (defined(MCU_MKL05Z4)) || (defined(MCU_MKL14Z4)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL16Z4)) || (defined(MCU_MKL24Z4)) || (defined(MCU_MKL25Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL34Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKW01Z4)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */

/* ----------------------------------------------------------------------------
   -- LockControlReg
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F15)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F15)))
/**
 * @brief The lock register is used to block write accesses to certain registers
 * until the next VBAT_POR or software reset.Write accesses to a locked register
 * are ignored and do not generate a bus error.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: RTC_LR.
 * @par Example:
 *      @code
 *      RTC_PDD_LockControlReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define RTC_PDD_LockControlReg(PeripheralBase) ( \
      RTC_LR_REG(PeripheralBase) = \
       (uint32_t)(( \
        (uint32_t)(RTC_LR_REG(PeripheralBase) & (uint32_t)(~(uint32_t)RTC_LR_CRL_MASK))) | ( \
        0xF000U)) \
    )
#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKL04Z4)) || (defined(MCU_MKL05Z4)) || (defined(MCU_MKL14Z4)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL16Z4)) || (defined(MCU_MKL24Z4)) || (defined(MCU_MKL25Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL34Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKW01Z4)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/**
 * @brief The lock register is used to block write accesses to certain registers
 * until the next VBAT_POR or software reset.Write accesses to a locked register
 * are ignored and do not generate a bus error.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: RTC_LR.
 * @par Example:
 *      @code
 *      RTC_PDD_LockControlReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define RTC_PDD_LockControlReg(PeripheralBase) ( \
      RTC_LR_REG(PeripheralBase) &= \
       (uint32_t)(~(uint32_t)RTC_LR_CRL_MASK) \
    )
#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKL04Z4)) || (defined(MCU_MKL05Z4)) || (defined(MCU_MKL14Z4)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL16Z4)) || (defined(MCU_MKL24Z4)) || (defined(MCU_MKL25Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL34Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKW01Z4)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */

/* ----------------------------------------------------------------------------
   -- LockTimeComensationReg
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F15)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F15)))
/**
 * @brief The lock register is used to block write accesses to certain registers
 * until the next VBAT_POR or software reset.Write accesses to a locked register
 * are ignored and do not generate a bus error.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: RTC_LR.
 * @par Example:
 *      @code
 *      RTC_PDD_LockTimeComensationReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define RTC_PDD_LockTimeComensationReg(PeripheralBase) ( \
      RTC_LR_REG(PeripheralBase) = \
       (uint32_t)(( \
        (uint32_t)(RTC_LR_REG(PeripheralBase) & (uint32_t)(~(uint32_t)RTC_LR_TCL_MASK))) | ( \
        0xF000U)) \
    )
#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKL04Z4)) || (defined(MCU_MKL05Z4)) || (defined(MCU_MKL14Z4)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL16Z4)) || (defined(MCU_MKL24Z4)) || (defined(MCU_MKL25Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL34Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKW01Z4)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/**
 * @brief The lock register is used to block write accesses to certain registers
 * until the next VBAT_POR or software reset.Write accesses to a locked register
 * are ignored and do not generate a bus error.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: RTC_LR.
 * @par Example:
 *      @code
 *      RTC_PDD_LockTimeComensationReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define RTC_PDD_LockTimeComensationReg(PeripheralBase) ( \
      RTC_LR_REG(PeripheralBase) &= \
       (uint32_t)(~(uint32_t)RTC_LR_TCL_MASK) \
    )
#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKL04Z4)) || (defined(MCU_MKL05Z4)) || (defined(MCU_MKL14Z4)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL16Z4)) || (defined(MCU_MKL24Z4)) || (defined(MCU_MKL25Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL34Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKW01Z4)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */

/* ----------------------------------------------------------------------------
   -- ReadWriteAccessReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the Write access register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: RTC_WAR.
 * @par Example:
 *      @code
 *      uint32_t result = RTC_PDD_ReadWriteAccessReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define RTC_PDD_ReadWriteAccessReg(PeripheralBase) ( \
    RTC_WAR_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteWriteAccessReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes value to the Write access register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value written to the Write access register. This parameter is a
 *        32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: RTC_WAR.
 * @par Example:
 *      @code
 *      RTC_PDD_WriteWriteAccessReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define RTC_PDD_WriteWriteAccessReg(PeripheralBase, Value) ( \
    RTC_WAR_REG(PeripheralBase) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- DisableInterruptEnableRegWrite
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F15)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F15)))
/**
 * @brief Disables write accesses to the register until the next chip system
 * reset. When accesses are blocked the bus access is not seen in the VBAT power
 * supply and does not generate a bus error.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: RTC_WAR.
 * @par Example:
 *      @code
 *      RTC_PDD_DisableInterruptEnableRegWrite(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define RTC_PDD_DisableInterruptEnableRegWrite(PeripheralBase) ( \
      RTC_WAR_REG(PeripheralBase) = \
       (uint32_t)(( \
        (uint32_t)(RTC_WAR_REG(PeripheralBase) & (uint32_t)(~(uint32_t)RTC_WAR_IERW_MASK))) | ( \
        0xF000U)) \
    )
#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/**
 * @brief Disables write accesses to the register until the next chip system
 * reset. When accesses are blocked the bus access is not seen in the VBAT power
 * supply and does not generate a bus error.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: RTC_WAR.
 * @par Example:
 *      @code
 *      RTC_PDD_DisableInterruptEnableRegWrite(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define RTC_PDD_DisableInterruptEnableRegWrite(PeripheralBase) ( \
      RTC_WAR_REG(PeripheralBase) &= \
       (uint32_t)(~(uint32_t)RTC_WAR_IERW_MASK) \
    )
#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */

/* ----------------------------------------------------------------------------
   -- DisableLockRegWrite
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F15)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F15)))
/**
 * @brief Disables write accesses to the register until the next chip system
 * reset. When accesses are blocked the bus access is not seen in the VBAT power
 * supply and does not generate a bus error.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: RTC_WAR.
 * @par Example:
 *      @code
 *      RTC_PDD_DisableLockRegWrite(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define RTC_PDD_DisableLockRegWrite(PeripheralBase) ( \
      RTC_WAR_REG(PeripheralBase) = \
       (uint32_t)(( \
        (uint32_t)(RTC_WAR_REG(PeripheralBase) & (uint32_t)(~(uint32_t)RTC_WAR_LRW_MASK))) | ( \
        0xF000U)) \
    )
#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/**
 * @brief Disables write accesses to the register until the next chip system
 * reset. When accesses are blocked the bus access is not seen in the VBAT power
 * supply and does not generate a bus error.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: RTC_WAR.
 * @par Example:
 *      @code
 *      RTC_PDD_DisableLockRegWrite(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define RTC_PDD_DisableLockRegWrite(PeripheralBase) ( \
      RTC_WAR_REG(PeripheralBase) &= \
       (uint32_t)(~(uint32_t)RTC_WAR_LRW_MASK) \
    )
#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */

/* ----------------------------------------------------------------------------
   -- DisableStatusRegWrite
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F15)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F15)))
/**
 * @brief Disables write accesses to the register until the next chip system
 * reset. When accesses are blocked the bus access is not seen in the VBAT power
 * supply and does not generate a bus error.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: RTC_WAR.
 * @par Example:
 *      @code
 *      RTC_PDD_DisableStatusRegWrite(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define RTC_PDD_DisableStatusRegWrite(PeripheralBase) ( \
      RTC_WAR_REG(PeripheralBase) = \
       (uint32_t)(( \
        (uint32_t)(RTC_WAR_REG(PeripheralBase) & (uint32_t)(~(uint32_t)RTC_WAR_SRW_MASK))) | ( \
        0xF000U)) \
    )
#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/**
 * @brief Disables write accesses to the register until the next chip system
 * reset. When accesses are blocked the bus access is not seen in the VBAT power
 * supply and does not generate a bus error.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: RTC_WAR.
 * @par Example:
 *      @code
 *      RTC_PDD_DisableStatusRegWrite(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define RTC_PDD_DisableStatusRegWrite(PeripheralBase) ( \
      RTC_WAR_REG(PeripheralBase) &= \
       (uint32_t)(~(uint32_t)RTC_WAR_SRW_MASK) \
    )
#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */

/* ----------------------------------------------------------------------------
   -- DisableControlRegWrite
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F15)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F15)))
/**
 * @brief Disables write accesses to the register until the next chip system
 * reset. When accesses are blocked the bus access is not seen in the VBAT power
 * supply and does not generate a bus error.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: RTC_WAR.
 * @par Example:
 *      @code
 *      RTC_PDD_DisableControlRegWrite(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define RTC_PDD_DisableControlRegWrite(PeripheralBase) ( \
      RTC_WAR_REG(PeripheralBase) = \
       (uint32_t)(( \
        (uint32_t)(RTC_WAR_REG(PeripheralBase) & (uint32_t)(~(uint32_t)RTC_WAR_CRW_MASK))) | ( \
        0xF000U)) \
    )
#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/**
 * @brief Disables write accesses to the register until the next chip system
 * reset. When accesses are blocked the bus access is not seen in the VBAT power
 * supply and does not generate a bus error.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: RTC_WAR.
 * @par Example:
 *      @code
 *      RTC_PDD_DisableControlRegWrite(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define RTC_PDD_DisableControlRegWrite(PeripheralBase) ( \
      RTC_WAR_REG(PeripheralBase) &= \
       (uint32_t)(~(uint32_t)RTC_WAR_CRW_MASK) \
    )
#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */

/* ----------------------------------------------------------------------------
   -- DisableTimeCompensationRegWrite
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F15)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F15)))
/**
 * @brief Disables write accesses to the register until the next chip system
 * reset. When accesses are blocked the bus access is not seen in the VBAT power
 * supply and does not generate a bus error.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: RTC_WAR.
 * @par Example:
 *      @code
 *      RTC_PDD_DisableTimeCompensationRegWrite(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define RTC_PDD_DisableTimeCompensationRegWrite(PeripheralBase) ( \
      RTC_WAR_REG(PeripheralBase) = \
       (uint32_t)(( \
        (uint32_t)(RTC_WAR_REG(PeripheralBase) & (uint32_t)(~(uint32_t)RTC_WAR_TCRW_MASK))) | ( \
        0xF000U)) \
    )
#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/**
 * @brief Disables write accesses to the register until the next chip system
 * reset. When accesses are blocked the bus access is not seen in the VBAT power
 * supply and does not generate a bus error.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: RTC_WAR.
 * @par Example:
 *      @code
 *      RTC_PDD_DisableTimeCompensationRegWrite(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define RTC_PDD_DisableTimeCompensationRegWrite(PeripheralBase) ( \
      RTC_WAR_REG(PeripheralBase) &= \
       (uint32_t)(~(uint32_t)RTC_WAR_TCRW_MASK) \
    )
#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */

/* ----------------------------------------------------------------------------
   -- DisableTimeAlarmRegWrite
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F15)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F15)))
/**
 * @brief Disables write accesses to the register until the next chip system
 * reset. When accesses are blocked the bus access is not seen in the VBAT power
 * supply and does not generate a bus error.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: RTC_WAR.
 * @par Example:
 *      @code
 *      RTC_PDD_DisableTimeAlarmRegWrite(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define RTC_PDD_DisableTimeAlarmRegWrite(PeripheralBase) ( \
      RTC_WAR_REG(PeripheralBase) = \
       (uint32_t)(( \
        (uint32_t)(RTC_WAR_REG(PeripheralBase) & (uint32_t)(~(uint32_t)RTC_WAR_TARW_MASK))) | ( \
        0xF000U)) \
    )
#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/**
 * @brief Disables write accesses to the register until the next chip system
 * reset. When accesses are blocked the bus access is not seen in the VBAT power
 * supply and does not generate a bus error.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: RTC_WAR.
 * @par Example:
 *      @code
 *      RTC_PDD_DisableTimeAlarmRegWrite(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define RTC_PDD_DisableTimeAlarmRegWrite(PeripheralBase) ( \
      RTC_WAR_REG(PeripheralBase) &= \
       (uint32_t)(~(uint32_t)RTC_WAR_TARW_MASK) \
    )
#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */

/* ----------------------------------------------------------------------------
   -- DisableTimePrescalerRegWrite
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F15)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F15)))
/**
 * @brief Disables write accesses to the register until the next chip system
 * reset. When accesses are blocked the bus access is not seen in the VBAT power
 * supply and does not generate a bus error.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: RTC_WAR.
 * @par Example:
 *      @code
 *      RTC_PDD_DisableTimePrescalerRegWrite(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define RTC_PDD_DisableTimePrescalerRegWrite(PeripheralBase) ( \
      RTC_WAR_REG(PeripheralBase) = \
       (uint32_t)(( \
        (uint32_t)(RTC_WAR_REG(PeripheralBase) & (uint32_t)(~(uint32_t)RTC_WAR_TPRW_MASK))) | ( \
        0xF000U)) \
    )
#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/**
 * @brief Disables write accesses to the register until the next chip system
 * reset. When accesses are blocked the bus access is not seen in the VBAT power
 * supply and does not generate a bus error.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: RTC_WAR.
 * @par Example:
 *      @code
 *      RTC_PDD_DisableTimePrescalerRegWrite(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define RTC_PDD_DisableTimePrescalerRegWrite(PeripheralBase) ( \
      RTC_WAR_REG(PeripheralBase) &= \
       (uint32_t)(~(uint32_t)RTC_WAR_TPRW_MASK) \
    )
#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */

/* ----------------------------------------------------------------------------
   -- DisableTimeSecondsRegWrite
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F15)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F15)))
/**
 * @brief Disables write accesses to the register until the next chip system
 * reset. When accesses are blocked the bus access is not seen in the VBAT power
 * supply and does not generate a bus error.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: RTC_WAR.
 * @par Example:
 *      @code
 *      RTC_PDD_DisableTimeSecondsRegWrite(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define RTC_PDD_DisableTimeSecondsRegWrite(PeripheralBase) ( \
      RTC_WAR_REG(PeripheralBase) = \
       (uint32_t)(( \
        (uint32_t)(RTC_WAR_REG(PeripheralBase) & (uint32_t)(~(uint32_t)RTC_WAR_TSRW_MASK))) | ( \
        0xF000U)) \
    )
#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/**
 * @brief Disables write accesses to the register until the next chip system
 * reset. When accesses are blocked the bus access is not seen in the VBAT power
 * supply and does not generate a bus error.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: RTC_WAR.
 * @par Example:
 *      @code
 *      RTC_PDD_DisableTimeSecondsRegWrite(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define RTC_PDD_DisableTimeSecondsRegWrite(PeripheralBase) ( \
      RTC_WAR_REG(PeripheralBase) &= \
       (uint32_t)(~(uint32_t)RTC_WAR_TSRW_MASK) \
    )
#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */

/* ----------------------------------------------------------------------------
   -- ReadReadAccessReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the Read access register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: RTC_RAR.
 * @par Example:
 *      @code
 *      uint32_t result = RTC_PDD_ReadReadAccessReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define RTC_PDD_ReadReadAccessReg(PeripheralBase) ( \
    RTC_RAR_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteReadAccessReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes value to the Read access register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value written to the Read access register. This parameter is a
 *        32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: RTC_RAR.
 * @par Example:
 *      @code
 *      RTC_PDD_WriteReadAccessReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define RTC_PDD_WriteReadAccessReg(PeripheralBase, Value) ( \
    RTC_RAR_REG(PeripheralBase) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- DisableInterruptEnableRegRead
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F15)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F15)))
/**
 * @brief Disables read accesses to the register until the next chip system
 * reset. When accesses are blocked the bus access is not seen in the VBAT power
 * supply and does not generate a bus error.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: RTC_RAR.
 * @par Example:
 *      @code
 *      RTC_PDD_DisableInterruptEnableRegRead(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define RTC_PDD_DisableInterruptEnableRegRead(PeripheralBase) ( \
      RTC_RAR_REG(PeripheralBase) = \
       (uint32_t)(( \
        (uint32_t)(RTC_RAR_REG(PeripheralBase) & (uint32_t)(~(uint32_t)RTC_RAR_IERR_MASK))) | ( \
        0xF000U)) \
    )
#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/**
 * @brief Disables read accesses to the register until the next chip system
 * reset. When accesses are blocked the bus access is not seen in the VBAT power
 * supply and does not generate a bus error.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: RTC_RAR.
 * @par Example:
 *      @code
 *      RTC_PDD_DisableInterruptEnableRegRead(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define RTC_PDD_DisableInterruptEnableRegRead(PeripheralBase) ( \
      RTC_RAR_REG(PeripheralBase) &= \
       (uint32_t)(~(uint32_t)RTC_RAR_IERR_MASK) \
    )
#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */

/* ----------------------------------------------------------------------------
   -- DisableLockRegRead
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F15)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F15)))
/**
 * @brief Disables read accesses to the register until the next chip system
 * reset. When accesses are blocked the bus access is not seen in the VBAT power
 * supply and does not generate a bus error.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: RTC_RAR.
 * @par Example:
 *      @code
 *      RTC_PDD_DisableLockRegRead(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define RTC_PDD_DisableLockRegRead(PeripheralBase) ( \
      RTC_RAR_REG(PeripheralBase) = \
       (uint32_t)(( \
        (uint32_t)(RTC_RAR_REG(PeripheralBase) & (uint32_t)(~(uint32_t)RTC_RAR_LRR_MASK))) | ( \
        0xF000U)) \
    )
#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/**
 * @brief Disables read accesses to the register until the next chip system
 * reset. When accesses are blocked the bus access is not seen in the VBAT power
 * supply and does not generate a bus error.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: RTC_RAR.
 * @par Example:
 *      @code
 *      RTC_PDD_DisableLockRegRead(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define RTC_PDD_DisableLockRegRead(PeripheralBase) ( \
      RTC_RAR_REG(PeripheralBase) &= \
       (uint32_t)(~(uint32_t)RTC_RAR_LRR_MASK) \
    )
#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */

/* ----------------------------------------------------------------------------
   -- DisableStatusRegRead
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F15)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F15)))
/**
 * @brief Disables read accesses to the register until the next chip system
 * reset. When accesses are blocked the bus access is not seen in the VBAT power
 * supply and does not generate a bus error.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: RTC_RAR.
 * @par Example:
 *      @code
 *      RTC_PDD_DisableStatusRegRead(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define RTC_PDD_DisableStatusRegRead(PeripheralBase) ( \
      RTC_RAR_REG(PeripheralBase) = \
       (uint32_t)(( \
        (uint32_t)(RTC_RAR_REG(PeripheralBase) & (uint32_t)(~(uint32_t)RTC_RAR_SRR_MASK))) | ( \
        0xF000U)) \
    )
#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/**
 * @brief Disables read accesses to the register until the next chip system
 * reset. When accesses are blocked the bus access is not seen in the VBAT power
 * supply and does not generate a bus error.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: RTC_RAR.
 * @par Example:
 *      @code
 *      RTC_PDD_DisableStatusRegRead(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define RTC_PDD_DisableStatusRegRead(PeripheralBase) ( \
      RTC_RAR_REG(PeripheralBase) &= \
       (uint32_t)(~(uint32_t)RTC_RAR_SRR_MASK) \
    )
#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */

/* ----------------------------------------------------------------------------
   -- DisableControlRegRead
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F15)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F15)))
/**
 * @brief Disables read accesses to the register until the next chip system
 * reset. When accesses are blocked the bus access is not seen in the VBAT power
 * supply and does not generate a bus error.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: RTC_RAR.
 * @par Example:
 *      @code
 *      RTC_PDD_DisableControlRegRead(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define RTC_PDD_DisableControlRegRead(PeripheralBase) ( \
      RTC_RAR_REG(PeripheralBase) = \
       (uint32_t)(( \
        (uint32_t)(RTC_RAR_REG(PeripheralBase) & (uint32_t)(~(uint32_t)RTC_RAR_CRR_MASK))) | ( \
        0xF000U)) \
    )
#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/**
 * @brief Disables read accesses to the register until the next chip system
 * reset. When accesses are blocked the bus access is not seen in the VBAT power
 * supply and does not generate a bus error.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: RTC_RAR.
 * @par Example:
 *      @code
 *      RTC_PDD_DisableControlRegRead(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define RTC_PDD_DisableControlRegRead(PeripheralBase) ( \
      RTC_RAR_REG(PeripheralBase) &= \
       (uint32_t)(~(uint32_t)RTC_RAR_CRR_MASK) \
    )
#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */

/* ----------------------------------------------------------------------------
   -- DisableTimeCompensationRegRead
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F15)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F15)))
/**
 * @brief Disables read accesses to the register until the next chip system
 * reset. When accesses are blocked the bus access is not seen in the VBAT power
 * supply and does not generate a bus error.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: RTC_RAR.
 * @par Example:
 *      @code
 *      RTC_PDD_DisableTimeCompensationRegRead(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define RTC_PDD_DisableTimeCompensationRegRead(PeripheralBase) ( \
      RTC_RAR_REG(PeripheralBase) = \
       (uint32_t)(( \
        (uint32_t)(RTC_RAR_REG(PeripheralBase) & (uint32_t)(~(uint32_t)RTC_RAR_TCRR_MASK))) | ( \
        0xF000U)) \
    )
#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/**
 * @brief Disables read accesses to the register until the next chip system
 * reset. When accesses are blocked the bus access is not seen in the VBAT power
 * supply and does not generate a bus error.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: RTC_RAR.
 * @par Example:
 *      @code
 *      RTC_PDD_DisableTimeCompensationRegRead(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define RTC_PDD_DisableTimeCompensationRegRead(PeripheralBase) ( \
      RTC_RAR_REG(PeripheralBase) &= \
       (uint32_t)(~(uint32_t)RTC_RAR_TCRR_MASK) \
    )
#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */

/* ----------------------------------------------------------------------------
   -- DisableTimeAlarmRegRead
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F15)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F15)))
/**
 * @brief Disables read accesses to the register until the next chip system
 * reset. When accesses are blocked the bus access is not seen in the VBAT power
 * supply and does not generate a bus error.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: RTC_RAR.
 * @par Example:
 *      @code
 *      RTC_PDD_DisableTimeAlarmRegRead(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define RTC_PDD_DisableTimeAlarmRegRead(PeripheralBase) ( \
      RTC_RAR_REG(PeripheralBase) = \
       (uint32_t)(( \
        (uint32_t)(RTC_RAR_REG(PeripheralBase) & (uint32_t)(~(uint32_t)RTC_RAR_TARR_MASK))) | ( \
        0xF000U)) \
    )
#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/**
 * @brief Disables read accesses to the register until the next chip system
 * reset. When accesses are blocked the bus access is not seen in the VBAT power
 * supply and does not generate a bus error.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: RTC_RAR.
 * @par Example:
 *      @code
 *      RTC_PDD_DisableTimeAlarmRegRead(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define RTC_PDD_DisableTimeAlarmRegRead(PeripheralBase) ( \
      RTC_RAR_REG(PeripheralBase) &= \
       (uint32_t)(~(uint32_t)RTC_RAR_TARR_MASK) \
    )
#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */

/* ----------------------------------------------------------------------------
   -- DisableTimePrescalerRegRead
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F15)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F15)))
/**
 * @brief Disables read accesses to the register until the next chip system
 * reset. When accesses are blocked the bus access is not seen in the VBAT power
 * supply and does not generate a bus error.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: RTC_RAR.
 * @par Example:
 *      @code
 *      RTC_PDD_DisableTimePrescalerRegRead(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define RTC_PDD_DisableTimePrescalerRegRead(PeripheralBase) ( \
      RTC_RAR_REG(PeripheralBase) = \
       (uint32_t)(( \
        (uint32_t)(RTC_RAR_REG(PeripheralBase) & (uint32_t)(~(uint32_t)RTC_RAR_TPRR_MASK))) | ( \
        0xF000U)) \
    )
#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/**
 * @brief Disables read accesses to the register until the next chip system
 * reset. When accesses are blocked the bus access is not seen in the VBAT power
 * supply and does not generate a bus error.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: RTC_RAR.
 * @par Example:
 *      @code
 *      RTC_PDD_DisableTimePrescalerRegRead(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define RTC_PDD_DisableTimePrescalerRegRead(PeripheralBase) ( \
      RTC_RAR_REG(PeripheralBase) &= \
       (uint32_t)(~(uint32_t)RTC_RAR_TPRR_MASK) \
    )
#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */

/* ----------------------------------------------------------------------------
   -- DisableTimeSecondsRegRead
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F15)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F15)))
/**
 * @brief Disables read accesses to the register until the next chip system
 * reset. When accesses are blocked the bus access is not seen in the VBAT power
 * supply and does not generate a bus error.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: RTC_RAR.
 * @par Example:
 *      @code
 *      RTC_PDD_DisableTimeSecondsRegRead(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define RTC_PDD_DisableTimeSecondsRegRead(PeripheralBase) ( \
      RTC_RAR_REG(PeripheralBase) = \
       (uint32_t)(( \
        (uint32_t)(RTC_RAR_REG(PeripheralBase) & (uint32_t)(~(uint32_t)RTC_RAR_TSRR_MASK))) | ( \
        0xF000U)) \
    )
#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/**
 * @brief Disables read accesses to the register until the next chip system
 * reset. When accesses are blocked the bus access is not seen in the VBAT power
 * supply and does not generate a bus error.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: RTC_RAR.
 * @par Example:
 *      @code
 *      RTC_PDD_DisableTimeSecondsRegRead(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define RTC_PDD_DisableTimeSecondsRegRead(PeripheralBase) ( \
      RTC_RAR_REG(PeripheralBase) &= \
       (uint32_t)(~(uint32_t)RTC_RAR_TSRR_MASK) \
    )
#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */

/* ----------------------------------------------------------------------------
   -- EnableMonotonicOverflowInterrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables the Monotonic counter overflow interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: RTC_IER.
 * @par Example:
 *      @code
 *      RTC_PDD_EnableMonotonicOverflowInterrupt(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define RTC_PDD_EnableMonotonicOverflowInterrupt(PeripheralBase) ( \
    RTC_IER_REG(PeripheralBase) |= \
     RTC_IER_MOIE_MASK \
  )

/* ----------------------------------------------------------------------------
   -- DisableMonotonicOverflowInterrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Disables the Monotonic counter overflow interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: RTC_IER.
 * @par Example:
 *      @code
 *      RTC_PDD_DisableMonotonicOverflowInterrupt(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define RTC_PDD_DisableMonotonicOverflowInterrupt(PeripheralBase) ( \
    RTC_IER_REG(PeripheralBase) &= \
     (uint32_t)(~(uint32_t)RTC_IER_MOIE_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- LockMonotonicCounterHighReg
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F15)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F15)))
/**
 * @brief The lock register is used to block write accesses to certain registers
 * until the next VBAT_POR or software reset.Write accesses to a locked register
 * are ignored and do not generate a bus error.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: RTC_LR.
 * @par Example:
 *      @code
 *      RTC_PDD_LockMonotonicCounterHighReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define RTC_PDD_LockMonotonicCounterHighReg(PeripheralBase) ( \
      RTC_LR_REG(PeripheralBase) = \
       (uint32_t)(( \
        (uint32_t)(RTC_LR_REG(PeripheralBase) & (uint32_t)(~(uint32_t)RTC_LR_MCHL_MASK))) | ( \
        0xF000U)) \
    )
#else /* (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/**
 * @brief The lock register is used to block write accesses to certain registers
 * until the next VBAT_POR or software reset.Write accesses to a locked register
 * are ignored and do not generate a bus error.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: RTC_LR.
 * @par Example:
 *      @code
 *      RTC_PDD_LockMonotonicCounterHighReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define RTC_PDD_LockMonotonicCounterHighReg(PeripheralBase) ( \
      RTC_LR_REG(PeripheralBase) &= \
       (uint32_t)(~(uint32_t)RTC_LR_MCHL_MASK) \
    )
#endif /* (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */

/* ----------------------------------------------------------------------------
   -- LockMonotonicCounterLowReg
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F15)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F15)))
/**
 * @brief The lock register is used to block write accesses to certain registers
 * until the next VBAT_POR or software reset.Write accesses to a locked register
 * are ignored and do not generate a bus error.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: RTC_LR.
 * @par Example:
 *      @code
 *      RTC_PDD_LockMonotonicCounterLowReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define RTC_PDD_LockMonotonicCounterLowReg(PeripheralBase) ( \
      RTC_LR_REG(PeripheralBase) = \
       (uint32_t)(( \
        (uint32_t)(RTC_LR_REG(PeripheralBase) & (uint32_t)(~(uint32_t)RTC_LR_MCLL_MASK))) | ( \
        0xF000U)) \
    )
#else /* (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/**
 * @brief The lock register is used to block write accesses to certain registers
 * until the next VBAT_POR or software reset.Write accesses to a locked register
 * are ignored and do not generate a bus error.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: RTC_LR.
 * @par Example:
 *      @code
 *      RTC_PDD_LockMonotonicCounterLowReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define RTC_PDD_LockMonotonicCounterLowReg(PeripheralBase) ( \
      RTC_LR_REG(PeripheralBase) &= \
       (uint32_t)(~(uint32_t)RTC_LR_MCLL_MASK) \
    )
#endif /* (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */

/* ----------------------------------------------------------------------------
   -- LockMonotonicEnableReg
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F15)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F15)))
/**
 * @brief The lock register is used to block write accesses to certain registers
 * until the next VBAT_POR or software reset.Write accesses to a locked register
 * are ignored and do not generate a bus error.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: RTC_LR.
 * @par Example:
 *      @code
 *      RTC_PDD_LockMonotonicEnableReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define RTC_PDD_LockMonotonicEnableReg(PeripheralBase) ( \
      RTC_LR_REG(PeripheralBase) = \
       (uint32_t)(( \
        (uint32_t)(RTC_LR_REG(PeripheralBase) & (uint32_t)(~(uint32_t)RTC_LR_MEL_MASK))) | ( \
        0xF000U)) \
    )
#else /* (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/**
 * @brief The lock register is used to block write accesses to certain registers
 * until the next VBAT_POR or software reset.Write accesses to a locked register
 * are ignored and do not generate a bus error.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: RTC_LR.
 * @par Example:
 *      @code
 *      RTC_PDD_LockMonotonicEnableReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define RTC_PDD_LockMonotonicEnableReg(PeripheralBase) ( \
      RTC_LR_REG(PeripheralBase) &= \
       (uint32_t)(~(uint32_t)RTC_LR_MEL_MASK) \
    )
#endif /* (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */

/* ----------------------------------------------------------------------------
   -- LockTamperTimeSecondsReg
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F15)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F15)))
/**
 * @brief The lock register is used to block write accesses to certain registers
 * until the next VBAT_POR or software reset.Write accesses to a locked register
 * are ignored and do not generate a bus error.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: RTC_LR.
 * @par Example:
 *      @code
 *      RTC_PDD_LockTamperTimeSecondsReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define RTC_PDD_LockTamperTimeSecondsReg(PeripheralBase) ( \
      RTC_LR_REG(PeripheralBase) = \
       (uint32_t)(( \
        (uint32_t)(RTC_LR_REG(PeripheralBase) & (uint32_t)(~(uint32_t)RTC_LR_TTSL_MASK))) | ( \
        0xF000U)) \
    )
#else /* (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/**
 * @brief The lock register is used to block write accesses to certain registers
 * until the next VBAT_POR or software reset.Write accesses to a locked register
 * are ignored and do not generate a bus error.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: RTC_LR.
 * @par Example:
 *      @code
 *      RTC_PDD_LockTamperTimeSecondsReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define RTC_PDD_LockTamperTimeSecondsReg(PeripheralBase) ( \
      RTC_LR_REG(PeripheralBase) &= \
       (uint32_t)(~(uint32_t)RTC_LR_TTSL_MASK) \
    )
#endif /* (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */

/* ----------------------------------------------------------------------------
   -- ReadTamperTimeSecondsReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the Tamper time seconds register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: RTC_TTSR.
 * @par Example:
 *      @code
 *      uint32_t result =
 *      RTC_PDD_ReadTamperTimeSecondsReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define RTC_PDD_ReadTamperTimeSecondsReg(PeripheralBase) ( \
    RTC_TTSR_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- GetTamperTime
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the Tamper time in seconds.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: RTC_TTSR.
 * @par Example:
 *      @code
 *      uint32_t result = RTC_PDD_GetTamperTime(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define RTC_PDD_GetTamperTime(PeripheralBase) ( \
    RTC_TTSR_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- ReadMonotonicEnableReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the Monotonic enable register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: RTC_MER.
 * @par Example:
 *      @code
 *      uint32_t result = RTC_PDD_ReadMonotonicEnableReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define RTC_PDD_ReadMonotonicEnableReg(PeripheralBase) ( \
    RTC_MER_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteMonotonicEnableReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes value to the Monotonic enable register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value written to the Monotonic enable register. This parameter
 *        is a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: RTC_MER.
 * @par Example:
 *      @code
 *      RTC_PDD_WriteMonotonicEnableReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define RTC_PDD_WriteMonotonicEnableReg(PeripheralBase, Value) ( \
    RTC_MER_REG(PeripheralBase) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- EnableMonotonicCounter
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables/disables Monotonis counter counter.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state. This parameter is of "Global enumeration used
 *        for specifying general enable/disable states (PDD_DISABLE and PDD_ENABLE
 *        defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: RTC_MER.
 * @par Example:
 *      @code
 *      RTC_PDD_EnableMonotonicCounter(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define RTC_PDD_EnableMonotonicCounter(PeripheralBase, State) ( \
    ((State) == PDD_DISABLE) ? ( \
      RTC_MER_REG(PeripheralBase) = \
       0U) : ( \
      RTC_MER_REG(PeripheralBase) = \
       0x10U) \
  )

/* ----------------------------------------------------------------------------
   -- GetMonotonicCounterEnableStatus
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns zero if the Monotonic counter is disabled else return non-zero
 * value.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: RTC_MER.
 * @par Example:
 *      @code
 *      uint32_t result =
 *      RTC_PDD_GetMonotonicCounterEnableStatus(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define RTC_PDD_GetMonotonicCounterEnableStatus(PeripheralBase) ( \
    (uint32_t)(RTC_MER_REG(PeripheralBase) & RTC_MER_MCE_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- ReadMonotonicCounterHighReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the Monotonic counter high register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: RTC_MCHR.
 * @par Example:
 *      @code
 *      uint32_t result =
 *      RTC_PDD_ReadMonotonicCounterHighReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define RTC_PDD_ReadMonotonicCounterHighReg(PeripheralBase) ( \
    RTC_MCHR_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteMonotonicCounterHigReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes value to the Monotonic counter high register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value written to the Monotonic counter high register. This
 *        parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: RTC_MCHR.
 * @par Example:
 *      @code
 *      RTC_PDD_WriteMonotonicCounterHigReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define RTC_PDD_WriteMonotonicCounterHigReg(PeripheralBase, Value) ( \
    RTC_MCHR_REG(PeripheralBase) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadMonotonicCounterLowReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the Monotonic counter low register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: RTC_MCLR.
 * @par Example:
 *      @code
 *      uint32_t result =
 *      RTC_PDD_ReadMonotonicCounterLowReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define RTC_PDD_ReadMonotonicCounterLowReg(PeripheralBase) ( \
    RTC_MCLR_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteMonotonicCounterLowgReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes value to the Monotonic counter low register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value written to the Monotonic counter low register. This
 *        parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: RTC_MCLR.
 * @par Example:
 *      @code
 *      RTC_PDD_WriteMonotonicCounterLowgReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define RTC_PDD_WriteMonotonicCounterLowgReg(PeripheralBase, Value) ( \
    RTC_MCLR_REG(PeripheralBase) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- DisableMonotonicCounterHighRegWrite
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F15)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F15)))
/**
 * @brief Disables write accesses to the register until the next chip system
 * reset. When accesses are blocked the bus access is not seen in the VBAT power
 * supply and does not generate a bus error.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: RTC_WAR.
 * @par Example:
 *      @code
 *      RTC_PDD_DisableMonotonicCounterHighRegWrite(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define RTC_PDD_DisableMonotonicCounterHighRegWrite(PeripheralBase) ( \
      RTC_WAR_REG(PeripheralBase) = \
       (uint32_t)(( \
        (uint32_t)(RTC_WAR_REG(PeripheralBase) & (uint32_t)(~(uint32_t)RTC_WAR_MCHW_MASK))) | ( \
        0xF000U)) \
    )
#else /* (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/**
 * @brief Disables write accesses to the register until the next chip system
 * reset. When accesses are blocked the bus access is not seen in the VBAT power
 * supply and does not generate a bus error.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: RTC_WAR.
 * @par Example:
 *      @code
 *      RTC_PDD_DisableMonotonicCounterHighRegWrite(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define RTC_PDD_DisableMonotonicCounterHighRegWrite(PeripheralBase) ( \
      RTC_WAR_REG(PeripheralBase) &= \
       (uint32_t)(~(uint32_t)RTC_WAR_MCHW_MASK) \
    )
#endif /* (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */

/* ----------------------------------------------------------------------------
   -- DisableMonotonicCounterLowRegWrite
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F15)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F15)))
/**
 * @brief Disables write accesses to the register until the next chip system
 * reset. When accesses are blocked the bus access is not seen in the VBAT power
 * supply and does not generate a bus error.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: RTC_WAR.
 * @par Example:
 *      @code
 *      RTC_PDD_DisableMonotonicCounterLowRegWrite(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define RTC_PDD_DisableMonotonicCounterLowRegWrite(PeripheralBase) ( \
      RTC_WAR_REG(PeripheralBase) = \
       (uint32_t)(( \
        (uint32_t)(RTC_WAR_REG(PeripheralBase) & (uint32_t)(~(uint32_t)RTC_WAR_MCLW_MASK))) | ( \
        0xF000U)) \
    )
#else /* (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/**
 * @brief Disables write accesses to the register until the next chip system
 * reset. When accesses are blocked the bus access is not seen in the VBAT power
 * supply and does not generate a bus error.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: RTC_WAR.
 * @par Example:
 *      @code
 *      RTC_PDD_DisableMonotonicCounterLowRegWrite(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define RTC_PDD_DisableMonotonicCounterLowRegWrite(PeripheralBase) ( \
      RTC_WAR_REG(PeripheralBase) &= \
       (uint32_t)(~(uint32_t)RTC_WAR_MCLW_MASK) \
    )
#endif /* (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */

/* ----------------------------------------------------------------------------
   -- DisableMonotonicEnableRegWrite
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F15)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F15)))
/**
 * @brief Disables write accesses to the register until the next chip system
 * reset. When accesses are blocked the bus access is not seen in the VBAT power
 * supply and does not generate a bus error.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: RTC_WAR.
 * @par Example:
 *      @code
 *      RTC_PDD_DisableMonotonicEnableRegWrite(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define RTC_PDD_DisableMonotonicEnableRegWrite(PeripheralBase) ( \
      RTC_WAR_REG(PeripheralBase) = \
       (uint32_t)(( \
        (uint32_t)(RTC_WAR_REG(PeripheralBase) & (uint32_t)(~(uint32_t)RTC_WAR_MERW_MASK))) | ( \
        0xF000U)) \
    )
#else /* (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/**
 * @brief Disables write accesses to the register until the next chip system
 * reset. When accesses are blocked the bus access is not seen in the VBAT power
 * supply and does not generate a bus error.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: RTC_WAR.
 * @par Example:
 *      @code
 *      RTC_PDD_DisableMonotonicEnableRegWrite(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define RTC_PDD_DisableMonotonicEnableRegWrite(PeripheralBase) ( \
      RTC_WAR_REG(PeripheralBase) &= \
       (uint32_t)(~(uint32_t)RTC_WAR_MERW_MASK) \
    )
#endif /* (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */

/* ----------------------------------------------------------------------------
   -- DisableTamperTimeSecondsRegWrite
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F15)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F15)))
/**
 * @brief Disables write accesses to the register until the next chip system
 * reset. When accesses are blocked the bus access is not seen in the VBAT power
 * supply and does not generate a bus error.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: RTC_WAR.
 * @par Example:
 *      @code
 *      RTC_PDD_DisableTamperTimeSecondsRegWrite(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define RTC_PDD_DisableTamperTimeSecondsRegWrite(PeripheralBase) ( \
      RTC_WAR_REG(PeripheralBase) = \
       (uint32_t)(( \
        (uint32_t)(RTC_WAR_REG(PeripheralBase) & (uint32_t)(~(uint32_t)RTC_WAR_TTSW_MASK))) | ( \
        0xF000U)) \
    )
#else /* (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/**
 * @brief Disables write accesses to the register until the next chip system
 * reset. When accesses are blocked the bus access is not seen in the VBAT power
 * supply and does not generate a bus error.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: RTC_WAR.
 * @par Example:
 *      @code
 *      RTC_PDD_DisableTamperTimeSecondsRegWrite(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define RTC_PDD_DisableTamperTimeSecondsRegWrite(PeripheralBase) ( \
      RTC_WAR_REG(PeripheralBase) &= \
       (uint32_t)(~(uint32_t)RTC_WAR_TTSW_MASK) \
    )
#endif /* (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */

/* ----------------------------------------------------------------------------
   -- DisableMonotonicCounterHighRegRead
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F15)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F15)))
/**
 * @brief Disables read accesses to the register until the next chip system
 * reset. When accesses are blocked the bus access is not seen in the VBAT power
 * supply and does not generate a bus error.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: RTC_RAR.
 * @par Example:
 *      @code
 *      RTC_PDD_DisableMonotonicCounterHighRegRead(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define RTC_PDD_DisableMonotonicCounterHighRegRead(PeripheralBase) ( \
      RTC_RAR_REG(PeripheralBase) = \
       (uint32_t)(( \
        (uint32_t)(RTC_RAR_REG(PeripheralBase) & (uint32_t)(~(uint32_t)RTC_RAR_MCHR_MASK))) | ( \
        0xF000U)) \
    )
#else /* (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/**
 * @brief Disables read accesses to the register until the next chip system
 * reset. When accesses are blocked the bus access is not seen in the VBAT power
 * supply and does not generate a bus error.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: RTC_RAR.
 * @par Example:
 *      @code
 *      RTC_PDD_DisableMonotonicCounterHighRegRead(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define RTC_PDD_DisableMonotonicCounterHighRegRead(PeripheralBase) ( \
      RTC_RAR_REG(PeripheralBase) &= \
       (uint32_t)(~(uint32_t)RTC_RAR_MCHR_MASK) \
    )
#endif /* (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */

/* ----------------------------------------------------------------------------
   -- DisableMonotonicCounterLowRegRead
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F15)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F15)))
/**
 * @brief Disables read accesses to the register until the next chip system
 * reset. When accesses are blocked the bus access is not seen in the VBAT power
 * supply and does not generate a bus error.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: RTC_RAR.
 * @par Example:
 *      @code
 *      RTC_PDD_DisableMonotonicCounterLowRegRead(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define RTC_PDD_DisableMonotonicCounterLowRegRead(PeripheralBase) ( \
      RTC_RAR_REG(PeripheralBase) = \
       (uint32_t)(( \
        (uint32_t)(RTC_RAR_REG(PeripheralBase) & (uint32_t)(~(uint32_t)RTC_RAR_MCLR_MASK))) | ( \
        0xF000U)) \
    )
#else /* (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/**
 * @brief Disables read accesses to the register until the next chip system
 * reset. When accesses are blocked the bus access is not seen in the VBAT power
 * supply and does not generate a bus error.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: RTC_RAR.
 * @par Example:
 *      @code
 *      RTC_PDD_DisableMonotonicCounterLowRegRead(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define RTC_PDD_DisableMonotonicCounterLowRegRead(PeripheralBase) ( \
      RTC_RAR_REG(PeripheralBase) &= \
       (uint32_t)(~(uint32_t)RTC_RAR_MCLR_MASK) \
    )
#endif /* (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */

/* ----------------------------------------------------------------------------
   -- DisableMonotonicEnableRegRead
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F15)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F15)))
/**
 * @brief Disables read accesses to the register until the next chip system
 * reset. When accesses are blocked the bus access is not seen in the VBAT power
 * supply and does not generate a bus error.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: RTC_RAR.
 * @par Example:
 *      @code
 *      RTC_PDD_DisableMonotonicEnableRegRead(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define RTC_PDD_DisableMonotonicEnableRegRead(PeripheralBase) ( \
      RTC_RAR_REG(PeripheralBase) = \
       (uint32_t)(( \
        (uint32_t)(RTC_RAR_REG(PeripheralBase) & (uint32_t)(~(uint32_t)RTC_RAR_MERR_MASK))) | ( \
        0xF000U)) \
    )
#else /* (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/**
 * @brief Disables read accesses to the register until the next chip system
 * reset. When accesses are blocked the bus access is not seen in the VBAT power
 * supply and does not generate a bus error.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: RTC_RAR.
 * @par Example:
 *      @code
 *      RTC_PDD_DisableMonotonicEnableRegRead(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define RTC_PDD_DisableMonotonicEnableRegRead(PeripheralBase) ( \
      RTC_RAR_REG(PeripheralBase) &= \
       (uint32_t)(~(uint32_t)RTC_RAR_MERR_MASK) \
    )
#endif /* (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */

/* ----------------------------------------------------------------------------
   -- DisableTamperTimeSecondsRegRead
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F15)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F15)))
/**
 * @brief Disables read accesses to the register until the next chip system
 * reset. When accesses are blocked the bus access is not seen in the VBAT power
 * supply and does not generate a bus error.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: RTC_RAR.
 * @par Example:
 *      @code
 *      RTC_PDD_DisableTamperTimeSecondsRegRead(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define RTC_PDD_DisableTamperTimeSecondsRegRead(PeripheralBase) ( \
      RTC_RAR_REG(PeripheralBase) = \
       (uint32_t)(( \
        (uint32_t)(RTC_RAR_REG(PeripheralBase) & (uint32_t)(~(uint32_t)RTC_RAR_TTSR_MASK))) | ( \
        0xF000U)) \
    )
#else /* (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/**
 * @brief Disables read accesses to the register until the next chip system
 * reset. When accesses are blocked the bus access is not seen in the VBAT power
 * supply and does not generate a bus error.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: RTC_RAR.
 * @par Example:
 *      @code
 *      RTC_PDD_DisableTamperTimeSecondsRegRead(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define RTC_PDD_DisableTamperTimeSecondsRegRead(PeripheralBase) ( \
      RTC_RAR_REG(PeripheralBase) &= \
       (uint32_t)(~(uint32_t)RTC_RAR_TTSR_MASK) \
    )
#endif /* (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */

/* ----------------------------------------------------------------------------
   -- LockTamperInterruptReg
   ---------------------------------------------------------------------------- */

/**
 * @brief The lock register is used to block write accesses to certain registers
 * until the next VBAT_POR or software reset.Write accesses to a locked register
 * are ignored and do not generate a bus error.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: RTC_LR.
 * @par Example:
 *      @code
 *      RTC_PDD_LockTamperInterruptReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define RTC_PDD_LockTamperInterruptReg(PeripheralBase) ( \
    RTC_LR_REG(PeripheralBase) &= \
     (uint32_t)(~(uint32_t)RTC_LR_TIL_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- LockTamperTrimReg
   ---------------------------------------------------------------------------- */

/**
 * @brief The lock register is used to block write accesses to certain registers
 * until the next VBAT_POR or software reset.Write accesses to a locked register
 * are ignored and do not generate a bus error.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: RTC_LR.
 * @par Example:
 *      @code
 *      RTC_PDD_LockTamperTrimReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define RTC_PDD_LockTamperTrimReg(PeripheralBase) ( \
    RTC_LR_REG(PeripheralBase) &= \
     (uint32_t)(~(uint32_t)RTC_LR_TTL_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- LockTamperDetectReg
   ---------------------------------------------------------------------------- */

/**
 * @brief The lock register is used to block write accesses to certain registers
 * until the next VBAT_POR or software reset.Write accesses to a locked register
 * are ignored and do not generate a bus error.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: RTC_LR.
 * @par Example:
 *      @code
 *      RTC_PDD_LockTamperDetectReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define RTC_PDD_LockTamperDetectReg(PeripheralBase) ( \
    RTC_LR_REG(PeripheralBase) &= \
     (uint32_t)(~(uint32_t)RTC_LR_TDL_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- LockTamperEnableReg
   ---------------------------------------------------------------------------- */

/**
 * @brief The lock register is used to block write accesses to certain registers
 * until the next VBAT_POR or software reset.Write accesses to a locked register
 * are ignored and do not generate a bus error.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: RTC_LR.
 * @par Example:
 *      @code
 *      RTC_PDD_LockTamperEnableReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define RTC_PDD_LockTamperEnableReg(PeripheralBase) ( \
    RTC_LR_REG(PeripheralBase) &= \
     (uint32_t)(~(uint32_t)RTC_LR_TEL_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- GetRtcTamperInterruptMask
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the RTC tamper interrupt register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: RTC_TIR.
 * @par Example:
 *      @code
 *      uint32_t result =
 *      RTC_PDD_GetRtcTamperInterruptMask(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define RTC_PDD_GetRtcTamperInterruptMask(PeripheralBase) ( \
    RTC_TIR_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- SetRtcTamperInterruptMask
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables RTC tamper interrupts defined by the Mask parameter.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mask Imterrupt mask. This parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: RTC_TIR.
 * @par Example:
 *      @code
 *      RTC_PDD_SetRtcTamperInterruptMask(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define RTC_PDD_SetRtcTamperInterruptMask(PeripheralBase, Mask) ( \
    RTC_TIR_REG(PeripheralBase) = \
     (uint32_t)(Mask) \
  )

/* ----------------------------------------------------------------------------
   -- EnableTestModeInterrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables the Test mode interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: RTC_TIR.
 * @par Example:
 *      @code
 *      RTC_PDD_EnableTestModeInterrupt(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define RTC_PDD_EnableTestModeInterrupt(PeripheralBase) ( \
    RTC_TIR_REG(PeripheralBase) |= \
     RTC_TIR_TMIE_MASK \
  )

/* ----------------------------------------------------------------------------
   -- EnableFlashSecurityInterrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables the Flash security interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: RTC_TIR.
 * @par Example:
 *      @code
 *      RTC_PDD_EnableFlashSecurityInterrupt(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define RTC_PDD_EnableFlashSecurityInterrupt(PeripheralBase) ( \
    RTC_TIR_REG(PeripheralBase) |= \
     RTC_TIR_FSIE_MASK \
  )

/* ----------------------------------------------------------------------------
   -- EnableTemperatureTamperInterrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables the Temperature tamper interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: RTC_TIR.
 * @par Example:
 *      @code
 *      RTC_PDD_EnableTemperatureTamperInterrupt(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define RTC_PDD_EnableTemperatureTamperInterrupt(PeripheralBase) ( \
    RTC_TIR_REG(PeripheralBase) |= \
     RTC_TIR_TTIE_MASK \
  )

/* ----------------------------------------------------------------------------
   -- EnableClockTamperInterrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables the Clock tamper interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: RTC_TIR.
 * @par Example:
 *      @code
 *      RTC_PDD_EnableClockTamperInterrupt(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define RTC_PDD_EnableClockTamperInterrupt(PeripheralBase) ( \
    RTC_TIR_REG(PeripheralBase) |= \
     RTC_TIR_CTIE_MASK \
  )

/* ----------------------------------------------------------------------------
   -- EnableVolatgeTamperInterrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables the Voltage tamper interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: RTC_TIR.
 * @par Example:
 *      @code
 *      RTC_PDD_EnableVolatgeTamperInterrupt(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define RTC_PDD_EnableVolatgeTamperInterrupt(PeripheralBase) ( \
    RTC_TIR_REG(PeripheralBase) |= \
     RTC_TIR_VTIE_MASK \
  )

/* ----------------------------------------------------------------------------
   -- EnableDryIceTamperInterrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables the DryIce tamper interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: RTC_TIR.
 * @par Example:
 *      @code
 *      RTC_PDD_EnableDryIceTamperInterrupt(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define RTC_PDD_EnableDryIceTamperInterrupt(PeripheralBase) ( \
    RTC_TIR_REG(PeripheralBase) |= \
     RTC_TIR_DTIE_MASK \
  )

/* ----------------------------------------------------------------------------
   -- DisableTestModeInterrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Disables the Test mode interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: RTC_TIR.
 * @par Example:
 *      @code
 *      RTC_PDD_DisableTestModeInterrupt(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define RTC_PDD_DisableTestModeInterrupt(PeripheralBase) ( \
    RTC_TIR_REG(PeripheralBase) &= \
     (uint32_t)(~(uint32_t)RTC_TIR_TMIE_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- DisableFlashSecurityInterrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Disables the Flash security interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: RTC_TIR.
 * @par Example:
 *      @code
 *      RTC_PDD_DisableFlashSecurityInterrupt(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define RTC_PDD_DisableFlashSecurityInterrupt(PeripheralBase) ( \
    RTC_TIR_REG(PeripheralBase) &= \
     (uint32_t)(~(uint32_t)RTC_TIR_FSIE_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- DisableTemperatureTamperInterrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Disables the Temperature tamper interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: RTC_TIR.
 * @par Example:
 *      @code
 *      RTC_PDD_DisableTemperatureTamperInterrupt(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define RTC_PDD_DisableTemperatureTamperInterrupt(PeripheralBase) ( \
    RTC_TIR_REG(PeripheralBase) &= \
     (uint32_t)(~(uint32_t)RTC_TIR_TTIE_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- DisableClockTamperInterrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Disables the Clock tamper interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: RTC_TIR.
 * @par Example:
 *      @code
 *      RTC_PDD_DisableClockTamperInterrupt(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define RTC_PDD_DisableClockTamperInterrupt(PeripheralBase) ( \
    RTC_TIR_REG(PeripheralBase) &= \
     (uint32_t)(~(uint32_t)RTC_TIR_CTIE_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- DisableVolatgeTamperInterrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Disables the Voltage tamper interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: RTC_TIR.
 * @par Example:
 *      @code
 *      RTC_PDD_DisableVolatgeTamperInterrupt(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define RTC_PDD_DisableVolatgeTamperInterrupt(PeripheralBase) ( \
    RTC_TIR_REG(PeripheralBase) &= \
     (uint32_t)(~(uint32_t)RTC_TIR_VTIE_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- DisableDryIceTamperInterrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Disables the DryIce tamper interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: RTC_TIR.
 * @par Example:
 *      @code
 *      RTC_PDD_DisableDryIceTamperInterrupt(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define RTC_PDD_DisableDryIceTamperInterrupt(PeripheralBase) ( \
    RTC_TIR_REG(PeripheralBase) &= \
     (uint32_t)(~(uint32_t)RTC_TIR_DTIE_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- ReadTamperDetectReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the Tamper detect register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: RTC_TDR.
 * @par Example:
 *      @code
 *      uint32_t result = RTC_PDD_ReadTamperDetectReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define RTC_PDD_ReadTamperDetectReg(PeripheralBase) ( \
    RTC_TDR_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteTamperDetectReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes value to the Tamper detect register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value written to the Tamper detect register. This parameter is a
 *        32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: RTC_TDR.
 * @par Example:
 *      @code
 *      RTC_PDD_WriteTamperDetectReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define RTC_PDD_WriteTamperDetectReg(PeripheralBase, Value) ( \
    RTC_TDR_REG(PeripheralBase) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- DisableTamperInterruptRegWrite
   ---------------------------------------------------------------------------- */

/**
 * @brief Disables write accesses to the register until the next chip system
 * reset. When accesses are blocked the bus access is not seen in the VBAT power
 * supply and does not generate a bus error.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: RTC_WAR.
 * @par Example:
 *      @code
 *      RTC_PDD_DisableTamperInterruptRegWrite(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define RTC_PDD_DisableTamperInterruptRegWrite(PeripheralBase) ( \
    RTC_WAR_REG(PeripheralBase) &= \
     (uint32_t)(~(uint32_t)RTC_WAR_TIRW_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- DisableTamperTrimRegWrite
   ---------------------------------------------------------------------------- */

/**
 * @brief Disables write accesses to the register until the next chip system
 * reset. When accesses are blocked the bus access is not seen in the VBAT power
 * supply and does not generate a bus error.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: RTC_WAR.
 * @par Example:
 *      @code
 *      RTC_PDD_DisableTamperTrimRegWrite(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define RTC_PDD_DisableTamperTrimRegWrite(PeripheralBase) ( \
    RTC_WAR_REG(PeripheralBase) &= \
     (uint32_t)(~(uint32_t)RTC_WAR_TTRW_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- DisableTamperDetectRegWrite
   ---------------------------------------------------------------------------- */

/**
 * @brief Disables write accesses to the register until the next chip system
 * reset. When accesses are blocked the bus access is not seen in the VBAT power
 * supply and does not generate a bus error.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: RTC_WAR.
 * @par Example:
 *      @code
 *      RTC_PDD_DisableTamperDetectRegWrite(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define RTC_PDD_DisableTamperDetectRegWrite(PeripheralBase) ( \
    RTC_WAR_REG(PeripheralBase) &= \
     (uint32_t)(~(uint32_t)RTC_WAR_TDRW_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- DisableTamperEnableRegWrite
   ---------------------------------------------------------------------------- */

/**
 * @brief Disables write accesses to the register until the next chip system
 * reset. When accesses are blocked the bus access is not seen in the VBAT power
 * supply and does not generate a bus error.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: RTC_WAR.
 * @par Example:
 *      @code
 *      RTC_PDD_DisableTamperEnableRegWrite(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define RTC_PDD_DisableTamperEnableRegWrite(PeripheralBase) ( \
    RTC_WAR_REG(PeripheralBase) &= \
     (uint32_t)(~(uint32_t)RTC_WAR_TERW_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- ReadTamperTrimReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the Tamper trim register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: RTC_TTR.
 * @par Example:
 *      @code
 *      uint32_t result = RTC_PDD_ReadTamperTrimReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define RTC_PDD_ReadTamperTrimReg(PeripheralBase) ( \
    RTC_TTR_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteTamperTrimReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes value to the Tamper trim register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value written to the Tamper trim register. This parameter is a
 *        32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: RTC_TTR.
 * @par Example:
 *      @code
 *      RTC_PDD_WriteTamperTrimReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define RTC_PDD_WriteTamperTrimReg(PeripheralBase, Value) ( \
    RTC_TTR_REG(PeripheralBase) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- DisableTamperInterruptRegRead
   ---------------------------------------------------------------------------- */

/**
 * @brief Disables read accesses to the register until the next chip system
 * reset. When accesses are blocked the bus access is not seen in the VBAT power
 * supply and does not generate a bus error.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: RTC_RAR.
 * @par Example:
 *      @code
 *      RTC_PDD_DisableTamperInterruptRegRead(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define RTC_PDD_DisableTamperInterruptRegRead(PeripheralBase) ( \
    RTC_RAR_REG(PeripheralBase) &= \
     (uint32_t)(~(uint32_t)RTC_RAR_TIRR_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- DisableTamperTrimRegRead
   ---------------------------------------------------------------------------- */

/**
 * @brief Disables read accesses to the register until the next chip system
 * reset. When accesses are blocked the bus access is not seen in the VBAT power
 * supply and does not generate a bus error.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: RTC_RAR.
 * @par Example:
 *      @code
 *      RTC_PDD_DisableTamperTrimRegRead(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define RTC_PDD_DisableTamperTrimRegRead(PeripheralBase) ( \
    RTC_RAR_REG(PeripheralBase) &= \
     (uint32_t)(~(uint32_t)RTC_RAR_TTRR_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- DisableTamperDetectRegRead
   ---------------------------------------------------------------------------- */

/**
 * @brief Disables read accesses to the register until the next chip system
 * reset. When accesses are blocked the bus access is not seen in the VBAT power
 * supply and does not generate a bus error.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: RTC_RAR.
 * @par Example:
 *      @code
 *      RTC_PDD_DisableTamperDetectRegRead(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define RTC_PDD_DisableTamperDetectRegRead(PeripheralBase) ( \
    RTC_RAR_REG(PeripheralBase) &= \
     (uint32_t)(~(uint32_t)RTC_RAR_TDRR_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- DisableTamperEnableRegRead
   ---------------------------------------------------------------------------- */

/**
 * @brief Disables read accesses to the register until the next chip system
 * reset. When accesses are blocked the bus access is not seen in the VBAT power
 * supply and does not generate a bus error.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: RTC_RAR.
 * @par Example:
 *      @code
 *      RTC_PDD_DisableTamperEnableRegRead(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define RTC_PDD_DisableTamperEnableRegRead(PeripheralBase) ( \
    RTC_RAR_REG(PeripheralBase) &= \
     (uint32_t)(~(uint32_t)RTC_RAR_TERR_MASK) \
  )
#endif  /* #if defined(RTC_PDD_H_) */

/* RTC_PDD.h, eof. */
