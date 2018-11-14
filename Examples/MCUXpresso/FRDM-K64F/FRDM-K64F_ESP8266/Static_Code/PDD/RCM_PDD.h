/*
  PDD layer implementation for peripheral type RCM
  (C) 2013 Freescale, Inc. All rights reserved.

  This file is static and it is generated from API-Factory
*/

#if !defined(RCM_PDD_H_)
#define RCM_PDD_H_

/* ----------------------------------------------------------------------------
   -- Test if supported MCU is active
   ---------------------------------------------------------------------------- */

#if !defined(MCU_ACTIVE)
  // No MCU is active
  #error RCM PDD library: No derivative is active. Place proper #include with PDD memory map before including PDD library.
#elif \
      !defined(MCU_MK22F12810) /* RCM */ && \
      !defined(MCU_MK22F25612) /* RCM */ && \
      !defined(MCU_MK22F51212) /* RCM */ && \
      !defined(MCU_MK24F12) /* RCM */ && \
      !defined(MCU_MK63F12) /* RCM */ && \
      !defined(MCU_MK63F12WS) /* RCM */ && \
      !defined(MCU_MK64F12) /* RCM */ && \
      !defined(MCU_MKV10Z7) /* RCM */ && \
      !defined(MCU_MKV31F12810) /* RCM */ && \
      !defined(MCU_MKV31F25612) /* RCM */ && \
      !defined(MCU_MKV31F51212) /* RCM */ && \
      !defined(MCU_MKW01Z4) /* RCM */ && \
      !defined(MCU_MKW21D5) /* RCM */ && \
      !defined(MCU_MKW21D5WS) /* RCM */ && \
      !defined(MCU_MKW22D5) /* RCM */ && \
      !defined(MCU_MKW22D5WS) /* RCM */ && \
      !defined(MCU_MKW24D5) /* RCM */ && \
      !defined(MCU_MKW24D5WS) /* RCM */
  // Unsupported MCU is active
  #error RCM PDD library: Unsupported derivative is active.
#endif

#include "PDD_Types.h"

/* ----------------------------------------------------------------------------
   -- Method symbol definitions
   ---------------------------------------------------------------------------- */

#if (defined(MCU_MKV10Z7))
/* System reset status masks constant */
  #define RCM_PDD_POWER_ON_RESET_FLAG     RCM_SRS0_POR_MASK /**< Reset caused by power-On reset flag mask */
  #define RCM_PDD_EXTERNAL_RESET_PIN_FLAG RCM_SRS0_PIN_MASK /**< Reset caused by external reset pin flag mask */
  #define RCM_PDD_WATCHDOG_TIMEOUT_FLAG   RCM_SRS0_WDOG_MASK /**< Reset caused by watchdog timeout flag mask */
  #define RCM_PDD_CLOCK_LOSS_FLAG         RCM_SRS0_LOC_MASK /**< Reset caused by a loss of external clock flag mask */
  #define RCM_PDD_LOW_VOLTAGE_FLAG        RCM_SRS0_LVD_MASK /**< Reset caused by low voltage trip or power-On reset flag mask */
  #define RCM_PDD_LOW_LEAKAGE_WAKEUP_FLAG RCM_SRS0_LVD_MASK /**< Reset caused by low leakage wakeup module wakeup source flag mask */

#elif ((defined(MCU_MK22F12810)) || (defined(MCU_MKV31F12810)))
/* System reset status masks constant */
  #define RCM_PDD_POWER_ON_RESET_FLAG     RCM_SRS0_POR_MASK /**< Reset caused by power-On reset flag mask */
  #define RCM_PDD_EXTERNAL_RESET_PIN_FLAG RCM_SRS0_PIN_MASK /**< Reset caused by external reset pin flag mask */
  #define RCM_PDD_WATCHDOG_TIMEOUT_FLAG   RCM_SRS0_WDOG_MASK /**< Reset caused by watchdog timeout flag mask */
  #define RCM_PDD_CLOCK_LOSS_FLAG         RCM_SRS0_LOC_MASK /**< Reset caused by a loss of external clock flag mask */
  #define RCM_PDD_LOW_VOLTAGE_FLAG        RCM_SRS0_LVD_MASK /**< Reset caused by low voltage trip or power-On reset flag mask */
  #define RCM_PDD_LOW_LEAKAGE_WAKEUP_FLAG RCM_SRS0_WAKEUP_MASK /**< Reset caused by low leakage wakeup module wakeup source flag mask */

#else /* (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW01Z4)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/* System reset status masks constant */
  #define RCM_PDD_POWER_ON_RESET_FLAG     RCM_SRS0_POR_MASK /**< Reset caused by power-On reset flag mask */
  #define RCM_PDD_EXTERNAL_RESET_PIN_FLAG RCM_SRS0_PIN_MASK /**< Reset caused by external reset pin flag mask */
  #define RCM_PDD_WATCHDOG_TIMEOUT_FLAG   RCM_SRS0_WDOG_MASK /**< Reset caused by watchdog timeout flag mask */
  #define RCM_PDD_LOCK_LOSS_FLAG          RCM_SRS0_LOL_MASK /**< Reset caused by a loss of lock in the PLL mask */
  #define RCM_PDD_CLOCK_LOSS_FLAG         RCM_SRS0_LOC_MASK /**< Reset caused by a loss of external clock flag mask */
  #define RCM_PDD_LOW_VOLTAGE_FLAG        RCM_SRS0_LVD_MASK /**< Reset caused by low voltage trip or power-On reset flag mask */
  #define RCM_PDD_LOW_LEAKAGE_WAKEUP_FLAG RCM_SRS0_WAKEUP_MASK /**< Reset caused by low leakage wakeup module wakeup source flag mask */

#endif /* (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW01Z4)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
#if ((defined(MCU_MKV10Z7)) || (defined(MCU_MKW01Z4)))
/* System reset status masks constant */
  #define RCM_PDD_STOP_MODE_ACKNOWLEDGE_ERROR_FLAG RCM_SRS1_SACKERR_MASK /**< Reset caused by peripheral failure to acknowledge attempt to enter stop mode */
  #define RCM_PDD_SYSTEM_RESET_REQUEST_FLAG        RCM_SRS1_MDM_AP_MASK /**< Reset caused by host debugger system setting of the System Reset Request */
  #define RCM_PDD_SOFTWARE_RESET_FLAG              RCM_SRS1_SW_MASK /**< Reset caused by software */
  #define RCM_PDD_CORE_LOCKUP_FLAG                 RCM_SRS1_LOCKUP_MASK /**< Reset caused by core LOCKUP event */

#elif ((defined(MCU_MK63F12)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW24D5)))
/* System reset status masks constant */
  #define RCM_PDD_TAMPER_DETECT_FLAG               RCM_SRS1__MASK /**< Reset caused by tamper detect */
  #define RCM_PDD_STOP_MODE_ACKNOWLEDGE_ERROR_FLAG RCM_SRS1_SACKERR_MASK /**< Reset caused by peripheral failure to acknowledge attempt to enter stop mode */
  #define RCM_PDD_EZPORT_RESET_FLAG                RCM_SRS1_EZPT_MASK /**< Reset caused by EzPort receiving the RESET command while the device is in EzPort mode */
  #define RCM_PDD_SYSTEM_RESET_REQUEST_FLAG        RCM_SRS1_MDM_AP_MASK /**< Reset caused by host debugger system setting of the System Reset Request */
  #define RCM_PDD_SOFTWARE_RESET_FLAG              RCM_SRS1_SW_MASK /**< Reset caused by software */
  #define RCM_PDD_CORE_LOCKUP_FLAG                 RCM_SRS1_LOCKUP_MASK /**< Reset caused by core LOCKUP event */
  #define RCM_PDD_JTAG_RESET_DETECT_FLAG           RCM_SRS1_JTAG_MASK /**< Reset caused by JTAG */

#elif ((defined(MCU_MK63F12WS)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5WS)))
/* System reset status masks constant */
  #define RCM_PDD_TAMPER_DETECT_FLAG               RCM_SRS1_TAMPER_MASK /**< Reset caused by tamper detect */
  #define RCM_PDD_STOP_MODE_ACKNOWLEDGE_ERROR_FLAG RCM_SRS1_SACKERR_MASK /**< Reset caused by peripheral failure to acknowledge attempt to enter stop mode */
  #define RCM_PDD_EZPORT_RESET_FLAG                RCM_SRS1_EZPT_MASK /**< Reset caused by EzPort receiving the RESET command while the device is in EzPort mode */
  #define RCM_PDD_SYSTEM_RESET_REQUEST_FLAG        RCM_SRS1_MDM_AP_MASK /**< Reset caused by host debugger system setting of the System Reset Request */
  #define RCM_PDD_SOFTWARE_RESET_FLAG              RCM_SRS1_SW_MASK /**< Reset caused by software */
  #define RCM_PDD_CORE_LOCKUP_FLAG                 RCM_SRS1_LOCKUP_MASK /**< Reset caused by core LOCKUP event */
  #define RCM_PDD_JTAG_RESET_DETECT_FLAG           RCM_SRS1_JTAG_MASK /**< Reset caused by JTAG */

#else /* (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK64F12)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) */
/* System reset status masks constant */
  #define RCM_PDD_STOP_MODE_ACKNOWLEDGE_ERROR_FLAG RCM_SRS1_SACKERR_MASK /**< Reset caused by peripheral failure to acknowledge attempt to enter stop mode */
  #define RCM_PDD_EZPORT_RESET_FLAG                RCM_SRS1_EZPT_MASK /**< Reset caused by EzPort receiving the RESET command while the device is in EzPort mode */
  #define RCM_PDD_SYSTEM_RESET_REQUEST_FLAG        RCM_SRS1_MDM_AP_MASK /**< Reset caused by host debugger system setting of the System Reset Request */
  #define RCM_PDD_SOFTWARE_RESET_FLAG              RCM_SRS1_SW_MASK /**< Reset caused by software */
  #define RCM_PDD_CORE_LOCKUP_FLAG                 RCM_SRS1_LOCKUP_MASK /**< Reset caused by core LOCKUP event */
  #define RCM_PDD_JTAG_RESET_DETECT_FLAG           RCM_SRS1_JTAG_MASK /**< Reset caused by JTAG */

#endif /* (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK64F12)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) */
/* Reset pin filter function in run and wait modes (for
   SetResetPinFilterFunctionInRunAndWaitModes macro). */
#define RCM_PDD_ALL_FILTERING_DISABLED   0U      /**< All filtering disabled */
#define RCM_PDD_BUS_CLOCK_FILTER_ENABLED 0x1U    /**< Bus clock filter enabled for normal operation */
#define RCM_PDD_LPO_CLOCK_FILTER_ENABLED 0x2U    /**< LPO clock filter enabled for normal operation */

/* Reset pin bus clock filter width constants */
#define RCM_PDD_BUS_CLOCK_FILTER_COUNT_1  0U     /**< Bus clock filter count is 1 */
#define RCM_PDD_BUS_CLOCK_FILTER_COUNT_2  0x1U   /**< Bus clock filter count is 2 */
#define RCM_PDD_BUS_CLOCK_FILTER_COUNT_3  0x2U   /**< Bus clock filter count is 3 */
#define RCM_PDD_BUS_CLOCK_FILTER_COUNT_4  0x3U   /**< Bus clock filter count is 4 */
#define RCM_PDD_BUS_CLOCK_FILTER_COUNT_5  0x4U   /**< Bus clock filter count is 5 */
#define RCM_PDD_BUS_CLOCK_FILTER_COUNT_6  0x5U   /**< Bus clock filter count is 6 */
#define RCM_PDD_BUS_CLOCK_FILTER_COUNT_7  0x6U   /**< Bus clock filter count is 7 */
#define RCM_PDD_BUS_CLOCK_FILTER_COUNT_8  0x7U   /**< Bus clock filter count is 8 */
#define RCM_PDD_BUS_CLOCK_FILTER_COUNT_9  0x8U   /**< Bus clock filter count is 9 */
#define RCM_PDD_BUS_CLOCK_FILTER_COUNT_10 0x9U   /**< Bus clock filter count is 10 */
#define RCM_PDD_BUS_CLOCK_FILTER_COUNT_11 0xAU   /**< Bus clock filter count is 11 */
#define RCM_PDD_BUS_CLOCK_FILTER_COUNT_12 0xBU   /**< Bus clock filter count is 12 */
#define RCM_PDD_BUS_CLOCK_FILTER_COUNT_13 0xCU   /**< Bus clock filter count is 13 */
#define RCM_PDD_BUS_CLOCK_FILTER_COUNT_14 0xDU   /**< Bus clock filter count is 14 */
#define RCM_PDD_BUS_CLOCK_FILTER_COUNT_15 0xEU   /**< Bus clock filter count is 15 */
#define RCM_PDD_BUS_CLOCK_FILTER_COUNT_16 0xFU   /**< Bus clock filter count is 16 */
#define RCM_PDD_BUS_CLOCK_FILTER_COUNT_17 0x10U  /**< Bus clock filter count is 17 */
#define RCM_PDD_BUS_CLOCK_FILTER_COUNT_18 0x11U  /**< Bus clock filter count is 18 */
#define RCM_PDD_BUS_CLOCK_FILTER_COUNT_19 0x12U  /**< Bus clock filter count is 19 */
#define RCM_PDD_BUS_CLOCK_FILTER_COUNT_20 0x13U  /**< Bus clock filter count is 20 */
#define RCM_PDD_BUS_CLOCK_FILTER_COUNT_21 0x14U  /**< Bus clock filter count is 21 */
#define RCM_PDD_BUS_CLOCK_FILTER_COUNT_22 0x15U  /**< Bus clock filter count is 22 */
#define RCM_PDD_BUS_CLOCK_FILTER_COUNT_23 0x16U  /**< Bus clock filter count is 23 */
#define RCM_PDD_BUS_CLOCK_FILTER_COUNT_24 0x17U  /**< Bus clock filter count is 24 */
#define RCM_PDD_BUS_CLOCK_FILTER_COUNT_25 0x18U  /**< Bus clock filter count is 25 */
#define RCM_PDD_BUS_CLOCK_FILTER_COUNT_26 0x19U  /**< Bus clock filter count is 26 */
#define RCM_PDD_BUS_CLOCK_FILTER_COUNT_27 0x1AU  /**< Bus clock filter count is 27 */
#define RCM_PDD_BUS_CLOCK_FILTER_COUNT_28 0x1BU  /**< Bus clock filter count is 28 */
#define RCM_PDD_BUS_CLOCK_FILTER_COUNT_29 0x1CU  /**< Bus clock filter count is 29 */
#define RCM_PDD_BUS_CLOCK_FILTER_COUNT_30 0x1DU  /**< Bus clock filter count is 30 */
#define RCM_PDD_BUS_CLOCK_FILTER_COUNT_31 0x1EU  /**< Bus clock filter count is 31 */
#define RCM_PDD_BUS_CLOCK_FILTER_COUNT_32 0x1FU  /**< Bus clock filter count is 32 */


/* ----------------------------------------------------------------------------
   -- ReadSystemResetStatus0
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the system reset status 0 flags mask.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Use constants from group "System reset status masks constant" for
 *         processing return value.
 * @remarks The macro accesses the following registers: RCM_SRS0.
 * @par Example:
 *      @code
 *      uint8_t result = RCM_PDD_ReadSystemResetStatus0(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define RCM_PDD_ReadSystemResetStatus0(PeripheralBase) ( \
    RCM_SRS0_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- ReadSystemResetStatus0Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads system reset status register 0.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: RCM_SRS0.
 * @par Example:
 *      @code
 *      uint8_t result =
 *      RCM_PDD_ReadSystemResetStatus0Reg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define RCM_PDD_ReadSystemResetStatus0Reg(PeripheralBase) ( \
    RCM_SRS0_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- ReadSystemResetStatus1
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the system reset status 1 flags mask.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Use constants from group "System reset status masks constant" for
 *         processing return value.
 * @remarks The macro accesses the following registers: RCM_SRS1.
 * @par Example:
 *      @code
 *      uint8_t result = RCM_PDD_ReadSystemResetStatus1(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define RCM_PDD_ReadSystemResetStatus1(PeripheralBase) ( \
    RCM_SRS1_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- ReadSystemResetStatus1Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads system reset status register 1.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: RCM_SRS1.
 * @par Example:
 *      @code
 *      uint8_t result =
 *      RCM_PDD_ReadSystemResetStatus1Reg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define RCM_PDD_ReadSystemResetStatus1Reg(PeripheralBase) ( \
    RCM_SRS1_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- EnableResetPinFilterInStopMode
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables/disables the reset pin filter in Stop and VLPS modes and also
 * during VLLS mode.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of reset pin filter in stop mode. This parameter
 *        is of "Global enumeration used for specifying general enable/disable
 *        states (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: RCM_RPFC.
 * @par Example:
 *      @code
 *      RCM_PDD_EnableResetPinFilterInStopMode(<peripheral>_BASE_PTR,
 *      PDD_DISABLE);
 *      @endcode
 */
#define RCM_PDD_EnableResetPinFilterInStopMode(PeripheralBase, State) ( \
    RCM_RPFC_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(RCM_RPFC_REG(PeripheralBase) & (uint8_t)(~(uint8_t)RCM_RPFC_RSTFLTSS_MASK))) | ( \
      (uint8_t)((uint8_t)(State) << RCM_RPFC_RSTFLTSS_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SetResetPinFilterFunctionInRunAndWaitModes
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets reset pin filter function in run and wait modes.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Function Reset pin filter function in run and wait modes. The user
 *        should use one from the enumerated values. This parameter is of "Reset pin
 *        filter function in run and wait modes (for
 *        SetResetPinFilterFunctionInRunAndWaitModes macro)." type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: RCM_RPFC.
 * @par Example:
 *      @code
 *      RCM_PDD_SetResetPinFilterFunctionInRunAndWaitModes(<peripheral>_BASE_PTR,
 *      RCM_PDD_ALL_FILTERING_DISABLED);
 *      @endcode
 */
#define RCM_PDD_SetResetPinFilterFunctionInRunAndWaitModes(PeripheralBase, Function) ( \
    RCM_RPFC_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(RCM_RPFC_REG(PeripheralBase) & (uint8_t)(~(uint8_t)RCM_RPFC_RSTFLTSRW_MASK))) | ( \
      (uint8_t)(Function))) \
  )

/* ----------------------------------------------------------------------------
   -- ReadResetPinFilterControlReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads reset pin filter control register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: RCM_RPFC.
 * @par Example:
 *      @code
 *      uint8_t result =
 *      RCM_PDD_ReadResetPinFilterControlReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define RCM_PDD_ReadResetPinFilterControlReg(PeripheralBase) ( \
    RCM_RPFC_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteResetPinFilterControlReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes new value specified by the Value parameter into reset pin
 * filter control register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the reset pin filter control register.
 *        This parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: RCM_RPFC.
 * @par Example:
 *      @code
 *      RCM_PDD_WriteResetPinFilterControlReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define RCM_PDD_WriteResetPinFilterControlReg(PeripheralBase, Value) ( \
    RCM_RPFC_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- SetResetPinFilterBusClockWidth
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the reset pin bus clock filter width.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Width Reset pin bus clock filter width. The user should use one from
 *        the enumerated values. This parameter is of "Reset pin bus clock filter
 *        width constants" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: RCM_RPFW.
 * @par Example:
 *      @code
 *      RCM_PDD_SetResetPinFilterBusClockWidth(<peripheral>_BASE_PTR,
 *      RCM_PDD_BUS_CLOCK_FILTER_COUNT_1);
 *      @endcode
 */
#define RCM_PDD_SetResetPinFilterBusClockWidth(PeripheralBase, Width) ( \
    RCM_RPFW_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(RCM_RPFW_REG(PeripheralBase) & (uint8_t)(~(uint8_t)RCM_RPFW_RSTFLTSEL_MASK))) | ( \
      (uint8_t)(Width))) \
  )

/* ----------------------------------------------------------------------------
   -- ReadResetPinFilterWidthReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads reset pin filter width register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: RCM_RPFW.
 * @par Example:
 *      @code
 *      uint8_t result =
 *      RCM_PDD_ReadResetPinFilterWidthReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define RCM_PDD_ReadResetPinFilterWidthReg(PeripheralBase) ( \
    RCM_RPFW_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteResetPinFilterWidthReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes new value specified by the Value parameter into reset pin
 * filter width register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the reset reset pin filter width
 *        register. This parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: RCM_RPFW.
 * @par Example:
 *      @code
 *      RCM_PDD_WriteResetPinFilterWidthReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define RCM_PDD_WriteResetPinFilterWidthReg(PeripheralBase, Value) ( \
    RCM_RPFW_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )
#endif  /* #if defined(RCM_PDD_H_) */

/* RCM_PDD.h, eof. */
