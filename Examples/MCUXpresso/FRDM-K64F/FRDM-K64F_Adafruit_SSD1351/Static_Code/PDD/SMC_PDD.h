/*
  PDD layer implementation for peripheral type SMC
  (C) 2013 Freescale, Inc. All rights reserved.

  This file is static and it is generated from API-Factory
*/

#if !defined(SMC_PDD_H_)
#define SMC_PDD_H_

/* ----------------------------------------------------------------------------
   -- Test if supported MCU is active
   ---------------------------------------------------------------------------- */

#if !defined(MCU_ACTIVE)
  // No MCU is active
  #error SMC PDD library: No derivative is active. Place proper #include with PDD memory map before including PDD library.
#elif \
      !defined(MCU_MK22F12810) /* SMC */ && \
      !defined(MCU_MK22F25612) /* SMC */ && \
      !defined(MCU_MK22F51212) /* SMC */ && \
      !defined(MCU_MK24F12) /* SMC */ && \
      !defined(MCU_MK63F12) /* SMC */ && \
      !defined(MCU_MK63F12WS) /* SMC */ && \
      !defined(MCU_MK64F12) /* SMC */ && \
      !defined(MCU_MKV10Z7) /* SMC */ && \
      !defined(MCU_MKV31F12810) /* SMC */ && \
      !defined(MCU_MKV31F25612) /* SMC */ && \
      !defined(MCU_MKV31F51212) /* SMC */ && \
      !defined(MCU_MKW01Z4) /* SMC */ && \
      !defined(MCU_MKW21D5) /* SMC */ && \
      !defined(MCU_MKW21D5WS) /* SMC */ && \
      !defined(MCU_MKW22D5) /* SMC */ && \
      !defined(MCU_MKW22D5WS) /* SMC */ && \
      !defined(MCU_MKW24D5) /* SMC */ && \
      !defined(MCU_MKW24D5WS) /* SMC */
  // Unsupported MCU is active
  #error SMC PDD library: Unsupported derivative is active.
#endif

#include "PDD_Types.h"

/* ----------------------------------------------------------------------------
   -- Method symbol definitions
   ---------------------------------------------------------------------------- */

#if (defined(MCU_MKV10Z7))
/* Power mode constants */
  #define SMC_PDD_POWER_MODE_RUN  0x1U             /**< Current power mode is RUN */
  #define SMC_PDD_POWER_MODE_STOP 0x2U             /**< Current power mode is STOP */
  #define SMC_PDD_POWER_MODE_VLPR 0x4U             /**< Current power mode is VLPR */
  #define SMC_PDD_POWER_MODE_VLPW 0x8U             /**< Current power mode is VLPW */
  #define SMC_PDD_POWER_MODE_VLPS 0x10U            /**< Current power mode is VLPS */
  #define SMC_PDD_POWER_MODE_VLLS 0x40U            /**< Current power mode is VLLS */

#elif ((defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)))
/* Power mode constants */
  #define SMC_PDD_POWER_MODE_RUN   0x1U            /**< Current power mode is RUN */
  #define SMC_PDD_POWER_MODE_STOP  0x2U            /**< Current power mode is STOP */
  #define SMC_PDD_POWER_MODE_VLPR  0x4U            /**< Current power mode is VLPR */
  #define SMC_PDD_POWER_MODE_VLPW  0x8U            /**< Current power mode is VLPW */
  #define SMC_PDD_POWER_MODE_VLPS  0x10U           /**< Current power mode is VLPS */
  #define SMC_PDD_POWER_MODE_LLS   0x20U           /**< Current power mode is LLS */
  #define SMC_PDD_POWER_MODE_VLLS  0x40U           /**< Current power mode is VLLS */
  #define SMC_PDD_POWER_MODE_HSRUN 0x80U           /**< Current power mode is HSRUN */

#else /* (defined(MCU_MK24F12)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MKW01Z4)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/* Power mode constants */
  #define SMC_PDD_POWER_MODE_RUN  0x1U             /**< Current power mode is RUN */
  #define SMC_PDD_POWER_MODE_STOP 0x2U             /**< Current power mode is STOP */
  #define SMC_PDD_POWER_MODE_VLPR 0x4U             /**< Current power mode is VLPR */
  #define SMC_PDD_POWER_MODE_VLPW 0x8U             /**< Current power mode is VLPW */
  #define SMC_PDD_POWER_MODE_VLPS 0x10U            /**< Current power mode is VLPS */
  #define SMC_PDD_POWER_MODE_LLS  0x20U            /**< Current power mode is LLS */
  #define SMC_PDD_POWER_MODE_VLLS 0x40U            /**< Current power mode is VLLS */

#endif /* (defined(MCU_MK24F12)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MKW01Z4)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
#if ((defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)))
/* Run mode control constants. */
  #define SMC_PDD_RM_RUN   0U                      /**< Normal Run mode. */
  #define SMC_PDD_RM_VLPR  0x40U                   /**< Very-Low-Power Run mode. */
  #define SMC_PDD_RM_HSRUN 0x60U                   /**< High-Speed Run mode. */

#else /* (defined(MCU_MK24F12)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKW01Z4)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/* Run mode control constants. */
  #define SMC_PDD_RM_RUN  0U                       /**< Normal Run mode. */
  #define SMC_PDD_RM_VLPR 0x40U                    /**< Very-Low-Power Run mode. */

#endif /* (defined(MCU_MK24F12)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKW01Z4)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
#if (defined(MCU_MKV10Z7))
/* Stop mode control constants. */
  #define SMC_PDD_SM_STOP  0U                      /**< Normal Stop */
  #define SMC_PDD_SM_VLPS  0x2U                    /**< Very-Low-Power Stop */
  #define SMC_PDD_SM_VLLSx 0x4U                    /**< Very-Low-Leakage Stop */

#else /* (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW01Z4)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/* Stop mode control constants. */
  #define SMC_PDD_SM_STOP  0U                      /**< Normal Stop */
  #define SMC_PDD_SM_VLPS  0x2U                    /**< Very-Low-Power Stop */
  #define SMC_PDD_SM_LLS   0x3U                    /**< Low-Leakage Stop */
  #define SMC_PDD_SM_VLLSx 0x4U                    /**< Very-Low-Leakage Stop */

#endif /* (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW01Z4)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
#if ((defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW01Z4)))
/* Partial stop option constants. */
  #define SMC_PDD_SO_STOP   0U                     /**< Normal Stop mode */
  #define SMC_PDD_SO_PSTOP1 0x40U                  /**< Partial Stop with both system and bus clocks disabled */
  #define SMC_PDD_SO_PSTOP2 0x80U                  /**< Partial Stop with system clock disabled and bus clock enabled */

#else /* (defined(MCU_MK24F12)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/* Partial stop option constants. */
  #define SMC_PDD_SO_STOP   0U                     /**< Normal Stop mode */
  #define SMC_PDD_SO_PSTOP1 0x1U                   /**< Partial Stop with both system and bus clocks disabled */
  #define SMC_PDD_SO_PSTOP2 0x2U                   /**< Partial Stop with system clock disabled and bus clock enabled */

#endif /* (defined(MCU_MK24F12)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
#if ((defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW01Z4)))
/* VLLS mode control constants. */
  #define SMC_PDD_VLLS_VLLS0 0U                    /**< VLLS0 */
  #define SMC_PDD_VLLS_VLLS1 0x1U                  /**< VLLS1 */
  #define SMC_PDD_VLLS_VLLS3 0x3U                  /**< VLLS3 */

#else /* (defined(MCU_MK24F12)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/* VLLS mode control constants. */
  #define SMC_PDD_VLLS_VLLS0 0U                    /**< VLLS0 */
  #define SMC_PDD_VLLS_VLLS1 0x1U                  /**< VLLS1 */
  #define SMC_PDD_VLLS_VLLS2 0x2U                  /**< VLLS2 */
  #define SMC_PDD_VLLS_VLLS3 0x3U                  /**< VLLS3 */

#endif /* (defined(MCU_MK24F12)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */

/* ----------------------------------------------------------------------------
   -- SetHighSpeedRunMode
   ---------------------------------------------------------------------------- */

/**
 * @brief Provided the appropriate control bits are set up in PMCTRL, this
 * write-once field allows the MCU to enter high-speed run mode (HSRUN).
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of the high-speed run mode. This parameter is of
 *        "Global enumeration used for specifying general enable/disable states
 *        (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SMC_PMPROT.
 * @par Example:
 *      @code
 *      SMC_PDD_SetHighSpeedRunMode(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define SMC_PDD_SetHighSpeedRunMode(PeripheralBase, State) ( \
    SMC_PMPROT_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(SMC_PMPROT_REG(PeripheralBase) & (uint8_t)(~(uint8_t)SMC_PMPROT_AHSRUN_MASK))) | ( \
      (uint8_t)((uint8_t)(State) << SMC_PMPROT_AHSRUN_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SetVeryLowPowerModes
   ---------------------------------------------------------------------------- */

/**
 * @brief Provided the appropriate control bits are set up in PMCTRL, this
 * write-once bit allows the MCU to enter any very-low-power mode (VLPR, VLPW, and
 * VLPS).
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of the very-low-power mode. This parameter is of
 *        "Global enumeration used for specifying general enable/disable states
 *        (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SMC_PMPROT.
 * @par Example:
 *      @code
 *      SMC_PDD_SetVeryLowPowerModes(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define SMC_PDD_SetVeryLowPowerModes(PeripheralBase, State) ( \
    SMC_PMPROT_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(SMC_PMPROT_REG(PeripheralBase) & (uint8_t)(~(uint8_t)SMC_PMPROT_AVLP_MASK))) | ( \
      (uint8_t)((uint8_t)(State) << SMC_PMPROT_AVLP_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SetLowLeakageStopMode
   ---------------------------------------------------------------------------- */

/**
 * @brief Provided the appropriate control bits are set up in PMCTRL, this write
 * once bit allows the MCU to enter any low-leakage stop mode (LLS).
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of the low-leakage stop mode. This parameter is
 *        of "Global enumeration used for specifying general enable/disable
 *        states (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SMC_PMPROT.
 * @par Example:
 *      @code
 *      SMC_PDD_SetLowLeakageStopMode(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define SMC_PDD_SetLowLeakageStopMode(PeripheralBase, State) ( \
    SMC_PMPROT_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(SMC_PMPROT_REG(PeripheralBase) & (uint8_t)(~(uint8_t)SMC_PMPROT_ALLS_MASK))) | ( \
      (uint8_t)((uint8_t)(State) << SMC_PMPROT_ALLS_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SetVeryLowLeakageStopMode
   ---------------------------------------------------------------------------- */

/**
 * @brief Provided the appropriate control bits are set up in PMCTRL, this write
 * once bit allows the MCU to enter any very-low-leakage stop mode (VLLSx).
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of the very-low-leakage stop mode. This
 *        parameter is of "Global enumeration used for specifying general enable/disable
 *        states (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SMC_PMPROT.
 * @par Example:
 *      @code
 *      SMC_PDD_SetVeryLowLeakageStopMode(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define SMC_PDD_SetVeryLowLeakageStopMode(PeripheralBase, State) ( \
    SMC_PMPROT_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(SMC_PMPROT_REG(PeripheralBase) & (uint8_t)(~(uint8_t)SMC_PMPROT_AVLLS_MASK))) | ( \
      (uint8_t)((uint8_t)(State) << SMC_PMPROT_AVLLS_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- WritePowerModeProtectionReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes value to the SMC power mode protection register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value New content of the SMC power mode protection register. This
 *        parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SMC_PMPROT.
 * @par Example:
 *      @code
 *      SMC_PDD_WritePowerModeProtectionReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define SMC_PDD_WritePowerModeProtectionReg(PeripheralBase, Value) ( \
    SMC_PMPROT_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadPowerModeProtectionReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the SMC power mode protection register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: SMC_PMPROT.
 * @par Example:
 *      @code
 *      uint8_t result =
 *      SMC_PDD_ReadPowerModeProtectionReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define SMC_PDD_ReadPowerModeProtectionReg(PeripheralBase) ( \
    SMC_PMPROT_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- SelectRunModeControl
   ---------------------------------------------------------------------------- */

/**
 * @brief Causes entry into the selected run mode.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mode New value of the run mode control. This parameter is of "Run mode
 *        control constants." type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SMC_PMCTRL.
 * @par Example:
 *      @code
 *      SMC_PDD_SelectRunModeControl(<peripheral>_BASE_PTR, SMC_PDD_RM_RUN);
 *      @endcode
 */
#define SMC_PDD_SelectRunModeControl(PeripheralBase, Mode) ( \
    SMC_PMCTRL_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(SMC_PMCTRL_REG(PeripheralBase) & (uint8_t)(~(uint8_t)SMC_PMCTRL_RUNM_MASK))) | ( \
      (uint8_t)(Mode))) \
  )

/* ----------------------------------------------------------------------------
   -- GetStopAborted
   ---------------------------------------------------------------------------- */

/**
 * @brief Indicates an interrupt or reset occured during the previous stop mode
 * entry sequence, preventing the system from entering that mode.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: SMC_PMCTRL.
 * @par Example:
 *      @code
 *      uint8_t result = SMC_PDD_GetStopAborted(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define SMC_PDD_GetStopAborted(PeripheralBase) ( \
    (uint8_t)(SMC_PMCTRL_REG(PeripheralBase) & SMC_PMCTRL_STOPA_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- SelectStopModeControl
   ---------------------------------------------------------------------------- */

/**
 * @brief Controls entry into the selected stop mode when Sleep-Now or
 * Sleep-On-Exit mode is entered with SLEEPDEEP=1.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mode New value of the stop mode control. This parameter is of "Stop
 *        mode control constants." type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SMC_PMCTRL.
 * @par Example:
 *      @code
 *      SMC_PDD_SelectStopModeControl(<peripheral>_BASE_PTR, SMC_PDD_SM_STOP);
 *      @endcode
 */
#define SMC_PDD_SelectStopModeControl(PeripheralBase, Mode) ( \
    SMC_PMCTRL_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(SMC_PMCTRL_REG(PeripheralBase) & (uint8_t)(~(uint8_t)SMC_PMCTRL_STOPM_MASK))) | ( \
      (uint8_t)(Mode))) \
  )

/* ----------------------------------------------------------------------------
   -- WritePowerModeControlReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes value to the SMC power mode control register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value New content of the SMC power mode control register. This
 *        parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SMC_PMCTRL.
 * @par Example:
 *      @code
 *      SMC_PDD_WritePowerModeControlReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define SMC_PDD_WritePowerModeControlReg(PeripheralBase, Value) ( \
    SMC_PMCTRL_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadPowerModeControlReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the SMC power mode control register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: SMC_PMCTRL.
 * @par Example:
 *      @code
 *      uint8_t result = SMC_PDD_ReadPowerModeControlReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define SMC_PDD_ReadPowerModeControlReg(PeripheralBase) ( \
    SMC_PMCTRL_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- SelectPartialStopOption
   ---------------------------------------------------------------------------- */

/**
 * @brief Controls whether a Partial Stop mode is entered when STOPM=STOP.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mode New value of the run mode control. This parameter is of "Partial
 *        stop option constants." type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SMC_STOPCTRL.
 * @par Example:
 *      @code
 *      SMC_PDD_SelectPartialStopOption(<peripheral>_BASE_PTR, SMC_PDD_SO_STOP);
 *      @endcode
 */
#define SMC_PDD_SelectPartialStopOption(PeripheralBase, Mode) ( \
    SMC_STOPCTRL_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(( \
       SMC_STOPCTRL_REG(PeripheralBase)) & ( \
       (uint8_t)(~(uint8_t)SMC_STOPCTRL_PSTOPO_MASK)))) | ( \
      (uint8_t)(Mode))) \
  )

/* ----------------------------------------------------------------------------
   -- SetPORPowerOption
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW01Z4)))
/**
 * @brief Controls whether the POR detect circuit is enabled in VLLS0 mode.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of the POR power option. This parameter is of
 *        "Global enumeration used for specifying general enable/disable states
 *        (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SMC_STOPCTRL,
 *          SMC_VLLSCTRL (depending on the peripheral).
 * @par Example:
 *      @code
 *      SMC_PDD_SetPORPowerOption(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
  #define SMC_PDD_SetPORPowerOption(PeripheralBase, State) ( \
      SMC_STOPCTRL_REG(PeripheralBase) = \
       (uint8_t)(( \
        (uint8_t)(( \
         SMC_STOPCTRL_REG(PeripheralBase)) & ( \
         (uint8_t)(~(uint8_t)SMC_STOPCTRL_PORPO_MASK)))) | ( \
        (uint8_t)((uint8_t)(State) << SMC_STOPCTRL_PORPO_SHIFT))) \
    )
#else /* (defined(MCU_MK24F12)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/**
 * @brief Controls whether the POR detect circuit is enabled in VLLS0 mode.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of the POR power option. This parameter is of
 *        "Global enumeration used for specifying general enable/disable states
 *        (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SMC_STOPCTRL,
 *          SMC_VLLSCTRL (depending on the peripheral).
 * @par Example:
 *      @code
 *      SMC_PDD_SetPORPowerOption(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
  #define SMC_PDD_SetPORPowerOption(PeripheralBase, State) ( \
      SMC_VLLSCTRL_REG(PeripheralBase) = \
       (uint8_t)(( \
        (uint8_t)(( \
         SMC_VLLSCTRL_REG(PeripheralBase)) & ( \
         (uint8_t)(~(uint8_t)SMC_VLLSCTRL_PORPO_MASK)))) | ( \
        (uint8_t)((uint8_t)(State) << SMC_VLLSCTRL_PORPO_SHIFT))) \
    )
#endif /* (defined(MCU_MK24F12)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */

/* ----------------------------------------------------------------------------
   -- SelectVLLSModeControl
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MKV10Z7)) || (defined(MCU_MKW01Z4)))
/**
 * @brief Controls which VLLS sub-mode to enter if STOPM=VLLSx.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mode New value of the VLLS mode control. This parameter is of "VLLS
 *        mode control constants." type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SMC_STOPCTRL,
 *          SMC_VLLSCTRL (depending on the peripheral).
 * @par Example:
 *      @code
 *      SMC_PDD_SelectVLLSModeControl(<peripheral>_BASE_PTR,
 *      SMC_PDD_VLLS_VLLS0);
 *      @endcode
 */
  #define SMC_PDD_SelectVLLSModeControl(PeripheralBase, Mode) ( \
      SMC_STOPCTRL_REG(PeripheralBase) = \
       (uint8_t)(( \
        (uint8_t)(( \
         SMC_STOPCTRL_REG(PeripheralBase)) & ( \
         (uint8_t)(~(uint8_t)SMC_STOPCTRL_VLLSM_MASK)))) | ( \
        (uint8_t)(Mode))) \
    )
#elif ((defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)))
/**
 * @brief Controls which VLLS sub-mode to enter if STOPM=VLLSx.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mode New value of the VLLS mode control. This parameter is of "VLLS
 *        mode control constants." type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SMC_STOPCTRL,
 *          SMC_VLLSCTRL (depending on the peripheral).
 * @par Example:
 *      @code
 *      SMC_PDD_SelectVLLSModeControl(<peripheral>_BASE_PTR,
 *      SMC_PDD_VLLS_VLLS0);
 *      @endcode
 */
  #define SMC_PDD_SelectVLLSModeControl(PeripheralBase, Mode) ( \
      SMC_STOPCTRL_REG(PeripheralBase) = \
       (uint8_t)(( \
        (uint8_t)(SMC_STOPCTRL_REG(PeripheralBase) & (uint8_t)(~(uint8_t)SMC_STOPCTRL_LLSM_MASK))) | ( \
        (uint8_t)(Mode))) \
    )
#else /* (defined(MCU_MK24F12)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/**
 * @brief Controls which VLLS sub-mode to enter if STOPM=VLLSx.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mode New value of the VLLS mode control. This parameter is of "VLLS
 *        mode control constants." type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SMC_STOPCTRL,
 *          SMC_VLLSCTRL (depending on the peripheral).
 * @par Example:
 *      @code
 *      SMC_PDD_SelectVLLSModeControl(<peripheral>_BASE_PTR,
 *      SMC_PDD_VLLS_VLLS0);
 *      @endcode
 */
  #define SMC_PDD_SelectVLLSModeControl(PeripheralBase, Mode) ( \
      SMC_VLLSCTRL_REG(PeripheralBase) = \
       (uint8_t)(( \
        (uint8_t)(( \
         SMC_VLLSCTRL_REG(PeripheralBase)) & ( \
         (uint8_t)(~(uint8_t)SMC_VLLSCTRL_VLLSM_MASK)))) | ( \
        (uint8_t)(Mode))) \
    )
#endif /* (defined(MCU_MK24F12)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */

/* ----------------------------------------------------------------------------
   -- WriteStopControlReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes value to the SMC stop control register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value New content of the SMC stop control register. This parameter is
 *        a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SMC_STOPCTRL.
 * @par Example:
 *      @code
 *      SMC_PDD_WriteStopControlReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define SMC_PDD_WriteStopControlReg(PeripheralBase, Value) ( \
    SMC_STOPCTRL_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadStopControlReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the SMC stop control register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: SMC_STOPCTRL.
 * @par Example:
 *      @code
 *      uint8_t result = SMC_PDD_ReadStopControlReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define SMC_PDD_ReadStopControlReg(PeripheralBase) ( \
    SMC_STOPCTRL_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- GetPowerMode
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)))
/**
 * @brief Returns current power mode (see Power mode constants).
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: SMC_PMSTAT.
 * @par Example:
 *      @code
 *      uint8_t result = SMC_PDD_GetPowerMode(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define SMC_PDD_GetPowerMode(PeripheralBase) ( \
      SMC_PMSTAT_REG(PeripheralBase) \
    )
#else /* (defined(MCU_MK24F12)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MKW01Z4)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/**
 * @brief Returns current power mode (see Power mode constants).
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: SMC_PMSTAT.
 * @par Example:
 *      @code
 *      uint8_t result = SMC_PDD_GetPowerMode(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define SMC_PDD_GetPowerMode(PeripheralBase) ( \
      (uint8_t)(SMC_PMSTAT_REG(PeripheralBase) & SMC_PMSTAT_PMSTAT_MASK) \
    )
#endif /* (defined(MCU_MK24F12)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MKW01Z4)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */

/* ----------------------------------------------------------------------------
   -- ReadPowerModeStatusReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the SMC power mode status register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: SMC_PMSTAT.
 * @par Example:
 *      @code
 *      uint8_t result = SMC_PDD_ReadPowerModeStatusReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define SMC_PDD_ReadPowerModeStatusReg(PeripheralBase) ( \
    SMC_PMSTAT_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- SetLowPowerWakeUp
   ---------------------------------------------------------------------------- */

/**
 * @brief Causes the SMC to exit to normal RUN mode when any active MCU
 * interrupt occurs while in a VLP mode (VLPR, VLPW or VLPS).
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of the Low Power Wake Up On Interrupt. This
 *        parameter is of "Global enumeration used for specifying general
 *        enable/disable states (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SMC_PMCTRL.
 * @par Example:
 *      @code
 *      SMC_PDD_SetLowPowerWakeUp(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define SMC_PDD_SetLowPowerWakeUp(PeripheralBase, State) ( \
    SMC_PMCTRL_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(SMC_PMCTRL_REG(PeripheralBase) & (uint8_t)(~(uint8_t)SMC_PMCTRL_LPWUI_MASK))) | ( \
      (uint8_t)((uint8_t)(State) << SMC_PMCTRL_LPWUI_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- WriteVLLSControlReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes value to the VLLS control register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value New content of the VLLS control register. This parameter is a
 *        8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SMC_VLLSCTRL.
 * @par Example:
 *      @code
 *      SMC_PDD_WriteVLLSControlReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define SMC_PDD_WriteVLLSControlReg(PeripheralBase, Value) ( \
    SMC_VLLSCTRL_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadVLLSControlReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the VLLS control register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: SMC_VLLSCTRL.
 * @par Example:
 *      @code
 *      uint8_t result = SMC_PDD_ReadVLLSControlReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define SMC_PDD_ReadVLLSControlReg(PeripheralBase) ( \
    SMC_VLLSCTRL_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- SetLPOPowerOption
   ---------------------------------------------------------------------------- */

/**
 * @brief Controls whether the 1kHZ LPO clock is enabled in LLS/VLLSx modes.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of the LPO power option. This parameter is of
 *        "Global enumeration used for specifying general enable/disable states
 *        (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SMC_STOPCTRL.
 * @par Example:
 *      @code
 *      SMC_PDD_SetLPOPowerOption(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define SMC_PDD_SetLPOPowerOption(PeripheralBase, State) ( \
    SMC_STOPCTRL_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(( \
       SMC_STOPCTRL_REG(PeripheralBase)) & ( \
       (uint8_t)(~(uint8_t)SMC_STOPCTRL_LPOPO_MASK)))) | ( \
      (uint8_t)((uint8_t)(State) << SMC_STOPCTRL_LPOPO_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SetRAM2PowerOption
   ---------------------------------------------------------------------------- */

/**
 * @brief Controls powering of RAM partition 2 in VLLS2 mode.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of the RAM2 power option. This parameter is of
 *        "Global enumeration used for specifying general enable/disable states
 *        (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SMC_VLLSCTRL.
 * @par Example:
 *      @code
 *      SMC_PDD_SetRAM2PowerOption(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define SMC_PDD_SetRAM2PowerOption(PeripheralBase, State) ( \
    SMC_VLLSCTRL_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(( \
       SMC_VLLSCTRL_REG(PeripheralBase)) & ( \
       (uint8_t)(~(uint8_t)SMC_VLLSCTRL_RAM2PO_MASK)))) | ( \
      (uint8_t)((uint8_t)(State) << SMC_VLLSCTRL_RAM2PO_SHIFT))) \
  )
#endif  /* #if defined(SMC_PDD_H_) */

/* SMC_PDD.h, eof. */
