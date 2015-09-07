/*
  PDD layer implementation for peripheral type TSI
  (C) 2013 Freescale, Inc. All rights reserved.

  This file is static and it is generated from API-Factory
*/

#if !defined(TSI_PDD_H_)
#define TSI_PDD_H_

/* ----------------------------------------------------------------------------
   -- Test if supported MCU is active
   ---------------------------------------------------------------------------- */

#if !defined(MCU_ACTIVE)
  // No MCU is active
  #error TSI PDD library: No derivative is active. Place proper #include with PDD memory map before including PDD library.
#elif \
      !defined(MCU_MK10DZ10) /* TSI0 */ && \
      !defined(MCU_MK20DZ10) /* TSI0 */ && \
      !defined(MCU_MK30DZ10) /* TSI0 */ && \
      !defined(MCU_MK40DZ10) /* TSI0 */ && \
      !defined(MCU_MK40X256VMD100) /* TSI0 */ && \
      !defined(MCU_MK50DZ10) /* TSI0 */ && \
      !defined(MCU_MK51DZ10) /* TSI0 */ && \
      !defined(MCU_MK52DZ10) /* TSI0 */ && \
      !defined(MCU_MK53DZ10) /* TSI0 */ && \
      !defined(MCU_MK60DZ10) /* TSI0 */ && \
      !defined(MCU_MK60N512VMD100) /* TSI0 */ && \
      !defined(MCU_MKL05Z4) /* TSI0 */ && \
      !defined(MCU_MKL15Z4) /* TSI0 */ && \
      !defined(MCU_MKL16Z4) /* TSI0 */ && \
      !defined(MCU_MKL25Z4) /* TSI0 */ && \
      !defined(MCU_MKL26Z4) /* TSI0 */ && \
      !defined(MCU_MKL36Z4) /* TSI0 */ && \
      !defined(MCU_MKL46Z4) /* TSI0 */ && \
      !defined(MCU_MKW01Z4) /* TSI0 */
  // Unsupported MCU is active
  #error TSI PDD library: Unsupported derivative is active.
#endif

#include "PDD_Types.h"

/* ----------------------------------------------------------------------------
   -- Method symbol definitions
   ---------------------------------------------------------------------------- */

/* Status flags constants. */
#define TSI_PDD_OUT_OF_RANGE_FLAG TSI_GENCS_OUTRGF_MASK /**< Out of range flag */
#define TSI_PDD_END_OF_SCAN_FLAG  TSI_GENCS_EOSF_MASK /**< End of scan flag */

/* Touch sensiting interrupt type constants */
#define TSI_PDD_OUT_OF_RANGE_INT_TYPE 0U         /**< Out-of-range interrupt is allowed */
#define TSI_PDD_OUT_OF_SCAN_INT_TYPE  0x10000000U /**< End-of-scan interrupt is allowed */

/* Analog mode setup constants */
#define TSI_PDD_NON_NOISE_DETECTION                                       0U /**< Capacitive sensing(non-noise detection) mode */
#define TSI_PDD_SINGLE_THRESHOLD_NOISE_DETECTION                          0x4000000U /**< Single threshold noise detection mode and the frequency limitation circuit is disabled */
#define TSI_PDD_SINGLE_THRESHOLD_NOISE_DETECTION_AND_FREQUENCY_LIMITATION 0x8000000U /**< single threshold noise detection mode and the frequency limitation circuit is enabled to work in higher frequencies operations */
#define TSI_PDD_AUTOMATIC_NOISE_DETECTION                                 0xC000000U /**< Analog to work in automatic noise detection mode */

/* Reference oscillator charge and discharge current value constants */
#define TSI_PDD_REFERENCE_OSC_CHARGE_CURRENT_500nA 0U /**< Reference oscillator charge current is 500nA */
#define TSI_PDD_REFERENCE_OSC_CHARGE_CURRENT_1uA   0x200000U /**< Reference oscillator charge current is 1uA */
#define TSI_PDD_REFERENCE_OSC_CHARGE_CURRENT_2uA   0x400000U /**< Reference oscillator charge current is 2uA */
#define TSI_PDD_REFERENCE_OSC_CHARGE_CURRENT_4uA   0x600000U /**< Reference oscillator charge current is 4uA */
#define TSI_PDD_REFERENCE_OSC_CHARGE_CURRENT_8uA   0x800000U /**< Reference oscillator charge current is 8uA */
#define TSI_PDD_REFERENCE_OSC_CHARGE_CURRENT_16uA  0xA00000U /**< Reference oscillator charge current is 16uA */
#define TSI_PDD_REFERENCE_OSC_CHARGE_CURRENT_32uA  0xC00000U /**< Reference oscillator charge current is 32uA */
#define TSI_PDD_REFERENCE_OSC_CHARGE_CURRENT_64uA  0xE00000U /**< Reference oscillator charge current is 64uA */

/* Delta voltage constants */
#define TSI_PDD_DELTA_VOLTAGE_1030mV 0U          /**< Delta volatage is 1030mV */
#define TSI_PDD_DELTA_VOLTAGE_730mV  0x80000U    /**< Delta volatage is 730mV */
#define TSI_PDD_DELTA_VOLTAGE_430mV  0x100000U   /**< Delta volatage is 430mV */
#define TSI_PDD_DELTA_VOLTAGE_290mV  0x180000U   /**< Delta volatage is 290mV */

/* External oscillator charge and discharge current value constants */
#define TSI_PDD_EXTERNAL_OSC_CHARGE_CURRENT_500nA 0U /**< External oscillator charge current is 500nA */
#define TSI_PDD_EXTERNAL_OSC_CHARGE_CURRENT_1uA   0x10000U /**< External oscillator charge current is 1uA */
#define TSI_PDD_EXTERNAL_OSC_CHARGE_CURRENT_2uA   0x20000U /**< External oscillator charge current is 2uA */
#define TSI_PDD_EXTERNAL_OSC_CHARGE_CURRENT_4uA   0x30000U /**< External oscillator charge current is 4uA */
#define TSI_PDD_EXTERNAL_OSC_CHARGE_CURRENT_8uA   0x40000U /**< External oscillator charge current is 8uA */
#define TSI_PDD_EXTERNAL_OSC_CHARGE_CURRENT_16uA  0x50000U /**< External oscillator charge current is 16uA */
#define TSI_PDD_EXTERNAL_OSC_CHARGE_CURRENT_32uA  0x60000U /**< External oscillator charge current is 32uA */
#define TSI_PDD_EXTERNAL_OSC_CHARGE_CURRENT_64uA  0x70000U /**< External oscillator charge current is 64uA */

/* External oscillator prescaler value constants */
#define TSI_PDD_EXTERNAL_OSC_DIVIDED_BY_1   0U   /**< External oscillator divided by 1 */
#define TSI_PDD_EXTERNAL_OSC_DIVIDED_BY_2   0x2000U /**< External oscillator divided by 2 */
#define TSI_PDD_EXTERNAL_OSC_DIVIDED_BY_4   0x4000U /**< External oscillator divided by 4 */
#define TSI_PDD_EXTERNAL_OSC_DIVIDED_BY_8   0x6000U /**< External oscillator divided by 8 */
#define TSI_PDD_EXTERNAL_OSC_DIVIDED_BY_16  0x8000U /**< External oscillator divided by 16 */
#define TSI_PDD_EXTERNAL_OSC_DIVIDED_BY_32  0xA000U /**< External oscillator divided by 32 */
#define TSI_PDD_EXTERNAL_OSC_DIVIDED_BY_64  0xC000U /**< External oscillator divided by 64 */
#define TSI_PDD_EXTERNAL_OSC_DIVIDED_BY_128 0xE000U /**< External oscillator divided by 128 */

/* Number of scan times per electrode constants */
#define TSI_PDD_SCAN_PER_ELECTRODE_1  0U         /**< Once per electrode */
#define TSI_PDD_SCAN_PER_ELECTRODE_2  0x100U     /**< Twice per electrode */
#define TSI_PDD_SCAN_PER_ELECTRODE_3  0x200U     /**< 3 times per electrode */
#define TSI_PDD_SCAN_PER_ELECTRODE_4  0x300U     /**< 4 times per electrode */
#define TSI_PDD_SCAN_PER_ELECTRODE_5  0x400U     /**< 5 times per electrode */
#define TSI_PDD_SCAN_PER_ELECTRODE_6  0x500U     /**< 6 times per electrode */
#define TSI_PDD_SCAN_PER_ELECTRODE_7  0x600U     /**< 7 times per electrode */
#define TSI_PDD_SCAN_PER_ELECTRODE_8  0x700U     /**< 8 times per electrode */
#define TSI_PDD_SCAN_PER_ELECTRODE_9  0x800U     /**< 9 times per electrode */
#define TSI_PDD_SCAN_PER_ELECTRODE_10 0x900U     /**< 10 times per electrode */
#define TSI_PDD_SCAN_PER_ELECTRODE_11 0xA00U     /**< 11 times per electrode */
#define TSI_PDD_SCAN_PER_ELECTRODE_12 0xB00U     /**< 12 times per electrode */
#define TSI_PDD_SCAN_PER_ELECTRODE_13 0xC00U     /**< 13 times per electrode */
#define TSI_PDD_SCAN_PER_ELECTRODE_14 0xD00U     /**< 14 times per electrode */
#define TSI_PDD_SCAN_PER_ELECTRODE_15 0xE00U     /**< 15 times per electrode */
#define TSI_PDD_SCAN_PER_ELECTRODE_16 0xF00U     /**< 16 times per electrode */
#define TSI_PDD_SCAN_PER_ELECTRODE_17 0x1000U    /**< 17 times per electrode */
#define TSI_PDD_SCAN_PER_ELECTRODE_18 0x1100U    /**< 18 times per electrode */
#define TSI_PDD_SCAN_PER_ELECTRODE_19 0x1200U    /**< 19 times per electrode */
#define TSI_PDD_SCAN_PER_ELECTRODE_20 0x1300U    /**< 20 times per electrode */
#define TSI_PDD_SCAN_PER_ELECTRODE_21 0x1400U    /**< 21 times per electrode */
#define TSI_PDD_SCAN_PER_ELECTRODE_22 0x1500U    /**< 22 times per electrode */
#define TSI_PDD_SCAN_PER_ELECTRODE_23 0x1600U    /**< 23 times per electrode */
#define TSI_PDD_SCAN_PER_ELECTRODE_24 0x1700U    /**< 24 times per electrode */
#define TSI_PDD_SCAN_PER_ELECTRODE_25 0x1800U    /**< 25 times per electrode */
#define TSI_PDD_SCAN_PER_ELECTRODE_26 0x1900U    /**< 26 times per electrode */
#define TSI_PDD_SCAN_PER_ELECTRODE_27 0x1A00U    /**< 27 times per electrode */
#define TSI_PDD_SCAN_PER_ELECTRODE_28 0x1B00U    /**< 28 times per electrode */
#define TSI_PDD_SCAN_PER_ELECTRODE_29 0x1C00U    /**< 29 times per electrode */
#define TSI_PDD_SCAN_PER_ELECTRODE_30 0x1D00U    /**< 30 times per electrode */
#define TSI_PDD_SCAN_PER_ELECTRODE_31 0x1E00U    /**< 31 times per electrode */
#define TSI_PDD_SCAN_PER_ELECTRODE_32 0x1F00U    /**< 32 times per electrode */

/* External scan trigger mode constants */
#define TSI_PDD_SOFTWARE_TRIGGER_SCAN 0U         /**< Software trigger scan mode */
#define TSI_PDD_HARDWARE_TRIGGER_SCAN 0x10U      /**< Hardware trigger scan mode */

/* Scan in progress status constants. */
#define TSI_PDD_NO_SCAN_IN_PROGRESS 0U           /**< No scan in progress */
#define TSI_PDD_SCAN_IN_PROGRESS    0x8U         /**< Scan in progress. */


/* ----------------------------------------------------------------------------
   -- EnableDevice
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MKL05Z4)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL16Z4)) || (defined(MCU_MKL25Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKW01Z4)))
/**
 * @brief Enables/disables TSI device.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of TSI device. This parameter is of "Global
 *        enumeration used for specifying general enable/disable states (PDD_DISABLE
 *        and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: TSI0_GENCS.
 * @par Example:
 *      @code
 *      TSI_PDD_EnableDevice(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
  #define TSI_PDD_EnableDevice(PeripheralBase, State) ( \
      TSI_GENCS_REG(PeripheralBase) = \
       (uint32_t)(( \
        (uint32_t)(( \
         TSI_GENCS_REG(PeripheralBase)) & (( \
         (uint32_t)(~(uint32_t)TSI_GENCS_TSIEN_MASK)) & (( \
         (uint32_t)(~(uint32_t)TSI_GENCS_EOSF_MASK)) & ( \
         (uint32_t)(~(uint32_t)TSI_GENCS_OUTRGF_MASK)))))) | ( \
        (uint32_t)((uint32_t)(State) << TSI_GENCS_TSIEN_SHIFT))) \
    )
#else /* (defined(MCU_MK10DZ10)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60N512VMD100)) */
/**
 * @brief Inputs are not checked (invalid value will cause undefined behavior).
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: TSI0_GENCS.
 * @par Example:
 *      @code
 *      TSI_PDD_EnableDevice(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define TSI_PDD_EnableDevice(PeripheralBase) ( \
      setReg32Bits(TSI_GENCS_REG(PeripheralBase), TSI_GENCS_TSIEN_MASK) \
    )
#endif /* (defined(MCU_MK10DZ10)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60N512VMD100)) */

/* ----------------------------------------------------------------------------
   -- DisableDevice
   ---------------------------------------------------------------------------- */

/**
 * @brief Inputs are not checked (invalid value will cause undefined behavior).
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @par Example:
 *      @code
 *      TSI_PDD_DisableDevice(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define TSI_PDD_DisableDevice(PeripheralBase) ( \
    clrReg32Bits(TSI_GENCS_REG(PeripheralBase), TSI_GENCS_TSIEN_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- IsDeviceEnabled
   ---------------------------------------------------------------------------- */

/**
 * @brief Inputs are not checked (invalid value will cause undefined behavior).
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @par Example:
 *      @code
 *      TSI_PDD_IsDeviceEnabled(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define TSI_PDD_IsDeviceEnabled(PeripheralBase) ( \
    testReg32Bits(TSI_GENCS_REG(PeripheralBase), TSI_GENCS_TSIEN_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- SetMask
   ---------------------------------------------------------------------------- */

/**
 * @brief Inputs are not checked (invalid value will cause undefined behavior).
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param mask  This parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @par Example:
 *      @code
 *      TSI_PDD_SetMask(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define TSI_PDD_SetMask(PeripheralBase, mask) ( \
    clrSetReg32Bits(TSI_GENCS_REG(PeripheralBase), TSI_AVAILABLE_INTERRUPT_MASK, mask) \
  )

/* ----------------------------------------------------------------------------
   -- GetMask
   ---------------------------------------------------------------------------- */

/**
 * @brief Inputs are not checked (invalid value will cause undefined behavior).
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @par Example:
 *      @code
 *      TSI_PDD_GetMask(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define TSI_PDD_GetMask(PeripheralBase) ( \
    getReg32(TSI_GENCS_REG(PeripheralBase)) & TSI_AVAILABLE_INTERRUPT_MASK \
  )

/* ----------------------------------------------------------------------------
   -- Set_ScanMode
   ---------------------------------------------------------------------------- */

/**
 * @brief Inputs are not checked (invalid value will cause undefined behavior).
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param mode  This parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @par Example:
 *      @code
 *      TSI_PDD_Set_ScanMode(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define TSI_PDD_Set_ScanMode(PeripheralBase, mode) ( \
    clrSetReg32Bits(TSI_GENCS_REG(PeripheralBase), TSI_GENCS_STM_MASK, mode) \
  )

/* ----------------------------------------------------------------------------
   -- Get_ScanMode
   ---------------------------------------------------------------------------- */

/**
 * @brief Inputs are not checked (invalid value will cause undefined behavior).
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @par Example:
 *      @code
 *      TSI_PDD_Get_ScanMode(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define TSI_PDD_Get_ScanMode(PeripheralBase) ( \
    getReg32(TSI_GENCS_REG(PeripheralBase)) & TSI_GENCS_STM_MASK \
  )

/* ----------------------------------------------------------------------------
   -- Stop_Enable
   ---------------------------------------------------------------------------- */

/**
 * @brief Inputs are not checked (invalid value will cause undefined behavior).
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @par Example:
 *      @code
 *      TSI_PDD_Stop_Enable(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define TSI_PDD_Stop_Enable(PeripheralBase) ( \
    setReg32Bits(TSI_GENCS_REG(PeripheralBase), TSI_GENCS_STPE_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- Stop_Disable
   ---------------------------------------------------------------------------- */

/**
 * @brief Inputs are not checked (invalid value will cause undefined behavior).
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @par Example:
 *      @code
 *      TSI_PDD_Stop_Disable(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define TSI_PDD_Stop_Disable(PeripheralBase) ( \
    clrReg32Bits(TSI_GENCS_REG(PeripheralBase), TSI_GENCS_STPE_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- GetInterruptFlags
   ---------------------------------------------------------------------------- */

/**
 * @brief Inputs are not checked (invalid value will cause undefined behavior).
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @par Example:
 *      @code
 *      TSI_PDD_GetInterruptFlags(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define TSI_PDD_GetInterruptFlags(PeripheralBase) ( \
    getReg32(TSI_GENCS_REG(PeripheralBase)) & TSI_AVAILABLE_FLAGS_MASK \
  )

/* ----------------------------------------------------------------------------
   -- ClearInterruptFlags
   ---------------------------------------------------------------------------- */

/**
 * @brief Inputs are not checked (invalid value will cause undefined behavior).
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param mask  This parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @par Example:
 *      @code
 *      TSI_PDD_ClearInterruptFlags(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define TSI_PDD_ClearInterruptFlags(PeripheralBase, mask) ( \
    setReg32Bits(TSI_GENCS_REG(PeripheralBase), mask) \
  )

/* ----------------------------------------------------------------------------
   -- IsScanInProgress
   ---------------------------------------------------------------------------- */

/**
 * @brief Inputs are not checked (invalid value will cause undefined behavior).
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @par Example:
 *      @code
 *      TSI_PDD_IsScanInProgress(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define TSI_PDD_IsScanInProgress(PeripheralBase) ( \
    getReg32(TSI_GENCS_REG(PeripheralBase)) &  TSI_GENCS_SCNIP_MASK \
  )

/* ----------------------------------------------------------------------------
   -- SoftwareTrigger
   ---------------------------------------------------------------------------- */

/**
 * @brief Inputs are not checked (invalid value will cause undefined behavior).
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @par Example:
 *      @code
 *      TSI_PDD_SoftwareTrigger(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define TSI_PDD_SoftwareTrigger(PeripheralBase) ( \
    setReg32Bits(TSI_GENCS_REG(PeripheralBase), TSI_GENCS_SWTS_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- Set_NumScansPerElectrode
   ---------------------------------------------------------------------------- */

/**
 * @brief Inputs are not checked (invalid value will cause undefined behavior).
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param scans  This parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @par Example:
 *      @code
 *      TSI_PDD_Set_NumScansPerElectrode(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define TSI_PDD_Set_NumScansPerElectrode(PeripheralBase, scans) ( \
    clrSetReg32Bits(TSI_GENCS_REG(PeripheralBase), TSI_GENCS_NSCN_MASK, scans) \
  )

/* ----------------------------------------------------------------------------
   -- Get_NumScansPerElectrode
   ---------------------------------------------------------------------------- */

/**
 * @brief Inputs are not checked (invalid value will cause undefined behavior).
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @par Example:
 *      @code
 *      TSI_PDD_Get_NumScansPerElectrode(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define TSI_PDD_Get_NumScansPerElectrode(PeripheralBase) ( \
    getReg32(TSI_GENCS_REG(PeripheralBase)) & TSI_GENCS_NSCN_MASK \
  )

/* ----------------------------------------------------------------------------
   -- Set_ElectrodePrescaler
   ---------------------------------------------------------------------------- */

/**
 * @brief Inputs are not checked (invalid value will cause undefined behavior).
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param divider  This parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @par Example:
 *      @code
 *      TSI_PDD_Set_ElectrodePrescaler(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define TSI_PDD_Set_ElectrodePrescaler(PeripheralBase, divider) ( \
    clrSetReg32Bits(TSI_GENCS_REG(PeripheralBase), TSI_GENCS_PS_MASK, divider) \
  )

/* ----------------------------------------------------------------------------
   -- Get_ElectrodePrescaler
   ---------------------------------------------------------------------------- */

/**
 * @brief Inputs are not checked (invalid value will cause undefined behavior).
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @par Example:
 *      @code
 *      TSI_PDD_Get_ElectrodePrescaler(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define TSI_PDD_Get_ElectrodePrescaler(PeripheralBase) ( \
    getReg32(TSI_GENCS_REG(PeripheralBase)) & TSI_GENCS_PS_MASK \
  )

/* ----------------------------------------------------------------------------
   -- Set_LPM_Clock
   ---------------------------------------------------------------------------- */

/**
 * @brief Inputs are not checked (invalid value will cause undefined behavior).
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param clock  This parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @par Example:
 *      @code
 *      TSI_PDD_Set_LPM_Clock(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define TSI_PDD_Set_LPM_Clock(PeripheralBase, clock) ( \
    clrSetReg32Bits(TSI_GENCS_REG(PeripheralBase), TSI_GENCS_LPCLKS_MASK, clock) \
  )

/* ----------------------------------------------------------------------------
   -- Get_LPM_Clock
   ---------------------------------------------------------------------------- */

/**
 * @brief Inputs are not checked (invalid value will cause undefined behavior).
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @par Example:
 *      @code
 *      TSI_PDD_Get_LPM_Clock(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define TSI_PDD_Get_LPM_Clock(PeripheralBase) ( \
    getReg32(TSI_GENCS_REG(PeripheralBase)) & TSI_GENCS_LPCLKS_MASK \
  )

/* ----------------------------------------------------------------------------
   -- Set_LPM_ScanInterval
   ---------------------------------------------------------------------------- */

/**
 * @brief Inputs are not checked (invalid value will cause undefined behavior).
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param interval  This parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @par Example:
 *      @code
 *      TSI_PDD_Set_LPM_ScanInterval(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define TSI_PDD_Set_LPM_ScanInterval(PeripheralBase, interval) ( \
    clrSetReg32Bits(TSI_GENCS_REG(PeripheralBase), TSI_GENCS_LPSCNITV_MASK, interval) \
  )

/* ----------------------------------------------------------------------------
   -- Get_LPM_ScanInterval
   ---------------------------------------------------------------------------- */

/**
 * @brief Inputs are not checked (invalid value will cause undefined behavior).
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @par Example:
 *      @code
 *      TSI_PDD_Get_LPM_ScanInterval(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define TSI_PDD_Get_LPM_ScanInterval(PeripheralBase) ( \
    getReg32(TSI_GENCS_REG(PeripheralBase)) & TSI_GENCS_LPSCNITV_MASK \
  )

/* ----------------------------------------------------------------------------
   -- Set_LPM_ScanPinSelection
   ---------------------------------------------------------------------------- */

/**
 * @brief Inputs are not checked (invalid value will cause undefined behavior).
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param pin  This parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @par Example:
 *      @code
 *      TSI_PDD_Set_LPM_ScanPinSelection(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define TSI_PDD_Set_LPM_ScanPinSelection(PeripheralBase, pin) ( \
    clrSetReg32Bits(TSI_PEN_REG(PeripheralBase), TSI_PEN_LPSP_MASK, pin) \
  )

/* ----------------------------------------------------------------------------
   -- Get_LPM_ScanPinSelection
   ---------------------------------------------------------------------------- */

/**
 * @brief Inputs are not checked (invalid value will cause undefined behavior).
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @par Example:
 *      @code
 *      TSI_PDD_Get_LPM_ScanPinSelection(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define TSI_PDD_Get_LPM_ScanPinSelection(PeripheralBase) ( \
    getReg32(TSI_PEN_REG(PeripheralBase)) & TSI_PEN_LPSP_MASK \
  )

/* ----------------------------------------------------------------------------
   -- Set_ClockDivider
   ---------------------------------------------------------------------------- */

/**
 * @brief Inputs are not checked (invalid value will cause undefined behavior).
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param div  This parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @par Example:
 *      @code
 *      TSI_PDD_Set_ClockDivider(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define TSI_PDD_Set_ClockDivider(PeripheralBase, div) ( \
    clrSetReg32Bits(TSI_SCANC_REG(PeripheralBase), TSI_SCANC_AMCLKDIV_MASK, div) \
  )

/* ----------------------------------------------------------------------------
   -- Get_ClockDivider
   ---------------------------------------------------------------------------- */

/**
 * @brief Inputs are not checked (invalid value will cause undefined behavior).
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @par Example:
 *      @code
 *      TSI_PDD_Get_ClockDivider(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define TSI_PDD_Get_ClockDivider(PeripheralBase) ( \
    getReg32(TSI_SCANC_REG(PeripheralBase)) & TSI_SCANC_AMCLKDIV_MASK \
  )

/* ----------------------------------------------------------------------------
   -- Set_ClockSource
   ---------------------------------------------------------------------------- */

/**
 * @brief Inputs are not checked (invalid value will cause undefined behavior).
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param source  This parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @par Example:
 *      @code
 *      TSI_PDD_Set_ClockSource(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define TSI_PDD_Set_ClockSource(PeripheralBase, source) ( \
    clrSetReg32Bits(TSI_SCANC_REG(PeripheralBase), TSI_SCANC_AMCLKS_MASK, source) \
  )

/* ----------------------------------------------------------------------------
   -- Get_ClockSource
   ---------------------------------------------------------------------------- */

/**
 * @brief Inputs are not checked (invalid value will cause undefined behavior).
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @par Example:
 *      @code
 *      TSI_PDD_Get_ClockSource(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define TSI_PDD_Get_ClockSource(PeripheralBase) ( \
    getReg32(TSI_SCANC_REG(PeripheralBase)) & TSI_SCANC_AMCLKS_MASK \
  )

/* ----------------------------------------------------------------------------
   -- Set_Prescaler
   ---------------------------------------------------------------------------- */

/**
 * @brief Inputs are not checked (invalid value will cause undefined behavior).
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param prescaler  This parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @par Example:
 *      @code
 *      TSI_PDD_Set_Prescaler(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define TSI_PDD_Set_Prescaler(PeripheralBase, prescaler) ( \
    clrSetReg32Bits(TSI_SCANC_REG(PeripheralBase), TSI_SCANC_AMPSC_MASK, prescaler) \
  )

/* ----------------------------------------------------------------------------
   -- Get_Prescaler
   ---------------------------------------------------------------------------- */

/**
 * @brief Inputs are not checked (invalid value will cause undefined behavior).
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @par Example:
 *      @code
 *      TSI_PDD_Get_Prescaler(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define TSI_PDD_Get_Prescaler(PeripheralBase) ( \
    getReg32(TSI_SCANC_REG(PeripheralBase)) & TSI_SCANC_AMPSC_MASK \
  )

/* ----------------------------------------------------------------------------
   -- Set_ScanModule
   ---------------------------------------------------------------------------- */

/**
 * @brief Inputs are not checked (invalid value will cause undefined behavior).
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param scan  This parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @par Example:
 *      @code
 *      TSI_PDD_Set_ScanModule(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define TSI_PDD_Set_ScanModule(PeripheralBase, scan) ( \
    clrSetReg32Bits(TSI_SCANC_REG(PeripheralBase), TSI_SCANC_SMOD_MASK, scan) \
  )

/* ----------------------------------------------------------------------------
   -- Get_ScanModule
   ---------------------------------------------------------------------------- */

/**
 * @brief Inputs are not checked (invalid value will cause undefined behavior).
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @par Example:
 *      @code
 *      TSI_PDD_Get_ScanModule(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define TSI_PDD_Get_ScanModule(PeripheralBase) ( \
    getReg32(TSI_SCANC_REG(PeripheralBase)) & TSI_SCANC_SMOD_MASK \
  )

/* ----------------------------------------------------------------------------
   -- Set_ExtOscChargeCurrent
   ---------------------------------------------------------------------------- */

/**
 * @brief Inputs are not checked (invalid value will cause undefined behavior).
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param current  This parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @par Example:
 *      @code
 *      TSI_PDD_Set_ExtOscChargeCurrent(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define TSI_PDD_Set_ExtOscChargeCurrent(PeripheralBase, current) ( \
    clrSetReg32Bits(TSI_SCANC_REG(PeripheralBase), TSI_SCANC_EXTCHRG_MASK, current) \
  )

/* ----------------------------------------------------------------------------
   -- Get_ExtOscChargeCurrent
   ---------------------------------------------------------------------------- */

/**
 * @brief Inputs are not checked (invalid value will cause undefined behavior).
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @par Example:
 *      @code
 *      TSI_PDD_Get_ExtOscChargeCurrent(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define TSI_PDD_Get_ExtOscChargeCurrent(PeripheralBase) ( \
    getReg32(TSI_SCANC_REG(PeripheralBase)) & TSI_SCANC_EXTCHRG_MASK \
  )

/* ----------------------------------------------------------------------------
   -- Set_DeltaVoltage
   ---------------------------------------------------------------------------- */

/**
 * @brief Inputs are not checked (invalid value will cause undefined behavior).
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param delta  This parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @par Example:
 *      @code
 *      TSI_PDD_Set_DeltaVoltage(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define TSI_PDD_Set_DeltaVoltage(PeripheralBase, delta) ( \
    clrSetReg32Bits(TSI_SCANC_REG(PeripheralBase), TSI_SCANC_DELVOL_MASK, delta) \
  )

/* ----------------------------------------------------------------------------
   -- Get_DeltaVoltage
   ---------------------------------------------------------------------------- */

/**
 * @brief Inputs are not checked (invalid value will cause undefined behavior).
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @par Example:
 *      @code
 *      TSI_PDD_Get_DeltaVoltage(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define TSI_PDD_Get_DeltaVoltage(PeripheralBase) ( \
    getReg32(TSI_SCANC_REG(PeripheralBase)) & TSI_SCANC_DELVOL_MASK \
  )

/* ----------------------------------------------------------------------------
   -- Set_RefOscChargeCurrent
   ---------------------------------------------------------------------------- */

/**
 * @brief Inputs are not checked (invalid value will cause undefined behavior).
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param current  This parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @par Example:
 *      @code
 *      TSI_PDD_Set_RefOscChargeCurrent(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define TSI_PDD_Set_RefOscChargeCurrent(PeripheralBase, current) ( \
    clrSetReg32Bits(TSI_SCANC_REG(PeripheralBase), TSI_SCANC_REFCHRG_MASK, current) \
  )

/* ----------------------------------------------------------------------------
   -- Get_RefOscChargeCurrent
   ---------------------------------------------------------------------------- */

/**
 * @brief Inputs are not checked (invalid value will cause undefined behavior).
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @par Example:
 *      @code
 *      TSI_PDD_Get_RefOscChargeCurrent(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define TSI_PDD_Get_RefOscChargeCurrent(PeripheralBase) ( \
    getReg32(TSI_SCANC_REG(PeripheralBase)) & TSI_SCANC_REFCHRG_MASK \
  )

/* ----------------------------------------------------------------------------
   -- Set_InternalCapacitance
   ---------------------------------------------------------------------------- */

/**
 * @brief Inputs are not checked (invalid value will cause undefined behavior).
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param farads  This parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @par Example:
 *      @code
 *      TSI_PDD_Set_InternalCapacitance(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define TSI_PDD_Set_InternalCapacitance(PeripheralBase, farads) ( \
    clrSetReg32Bits(TSI_SCANC_REG(PeripheralBase), TSI_SCANC_CAPTRM_MASK, farads) \
  )

/* ----------------------------------------------------------------------------
   -- Get_InternalCapacitance
   ---------------------------------------------------------------------------- */

/**
 * @brief Inputs are not checked (invalid value will cause undefined behavior).
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @par Example:
 *      @code
 *      TSI_PDD_Get_InternalCapacitance(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define TSI_PDD_Get_InternalCapacitance(PeripheralBase) ( \
    getReg32(TSI_SCANC_REG(PeripheralBase)) & TSI_SCANC_CAPTRM_MASK \
  )

/* ----------------------------------------------------------------------------
   -- Set_Pins
   ---------------------------------------------------------------------------- */

/**
 * @brief Inputs are not checked (invalid value will cause undefined behavior).
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param pins_mask  This parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @par Example:
 *      @code
 *      TSI_PDD_Set_Pins(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define TSI_PDD_Set_Pins(PeripheralBase, pins_mask) ( \
    clrSetReg32Bits(TSI_PEN_REG(PeripheralBase), TSI_PEN_PENX, pins_mask) \
  )

/* ----------------------------------------------------------------------------
   -- Get_Pins
   ---------------------------------------------------------------------------- */

/**
 * @brief Inputs are not checked (invalid value will cause undefined behavior).
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @par Example:
 *      @code
 *      TSI_PDD_Get_Pins(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define TSI_PDD_Get_Pins(PeripheralBase) ( \
    getReg32(TSI_PEN_REG(PeripheralBase)) & TSI_PEN_PENX \
  )

/* ----------------------------------------------------------------------------
   -- Clear_StatusFlags
   ---------------------------------------------------------------------------- */

/**
 * @brief Inputs are not checked (invalid value will cause undefined behavior).
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param clear_mask  This parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @par Example:
 *      @code
 *      TSI_PDD_Clear_StatusFlags(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define TSI_PDD_Clear_StatusFlags(PeripheralBase, clear_mask) ( \
    setReg32Bits(TSI_STATUS_REG(PeripheralBase), clear_mask) \
  )

/* ----------------------------------------------------------------------------
   -- Get_StatusFlags
   ---------------------------------------------------------------------------- */

/**
 * @brief Inputs are not checked (invalid value will cause undefined behavior).
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @par Example:
 *      @code
 *      TSI_PDD_Get_StatusFlags(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define TSI_PDD_Get_StatusFlags(PeripheralBase) ( \
    getReg32(TSI_STATUS_REG(PeripheralBase)) \
  )

/* ----------------------------------------------------------------------------
   -- Get_Counter1Value
   ---------------------------------------------------------------------------- */

/**
 * @brief Inputs are not checked (invalid value will cause undefined behavior).
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @par Example:
 *      @code
 *      TSI_PDD_Get_Counter1Value(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define TSI_PDD_Get_Counter1Value(PeripheralBase) ( \
    getReg32(TSI_CNTR1_REG(PeripheralBase)) \
  )

/* ----------------------------------------------------------------------------
   -- Get_Counter3Value
   ---------------------------------------------------------------------------- */

/**
 * @brief Inputs are not checked (invalid value will cause undefined behavior).
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @par Example:
 *      @code
 *      TSI_PDD_Get_Counter3Value(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define TSI_PDD_Get_Counter3Value(PeripheralBase) ( \
    getReg32(TSI_CNTR3_REG(PeripheralBase)) \
  )

/* ----------------------------------------------------------------------------
   -- Get_Counter5Value
   ---------------------------------------------------------------------------- */

/**
 * @brief Inputs are not checked (invalid value will cause undefined behavior).
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @par Example:
 *      @code
 *      TSI_PDD_Get_Counter5Value(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define TSI_PDD_Get_Counter5Value(PeripheralBase) ( \
    getReg32(TSI_CNTR5_REG(PeripheralBase)) \
  )

/* ----------------------------------------------------------------------------
   -- Get_Counter7Value
   ---------------------------------------------------------------------------- */

/**
 * @brief Inputs are not checked (invalid value will cause undefined behavior).
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @par Example:
 *      @code
 *      TSI_PDD_Get_Counter7Value(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define TSI_PDD_Get_Counter7Value(PeripheralBase) ( \
    getReg32(TSI_CNTR7_REG(PeripheralBase)) \
  )

/* ----------------------------------------------------------------------------
   -- Get_Counter9Value
   ---------------------------------------------------------------------------- */

/**
 * @brief Inputs are not checked (invalid value will cause undefined behavior).
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @par Example:
 *      @code
 *      TSI_PDD_Get_Counter9Value(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define TSI_PDD_Get_Counter9Value(PeripheralBase) ( \
    getReg32(TSI_CNTR9_REG(PeripheralBase)) \
  )

/* ----------------------------------------------------------------------------
   -- Get_Counter11Value
   ---------------------------------------------------------------------------- */

/**
 * @brief Inputs are not checked (invalid value will cause undefined behavior).
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @par Example:
 *      @code
 *      TSI_PDD_Get_Counter11Value(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define TSI_PDD_Get_Counter11Value(PeripheralBase) ( \
    getReg32(TSI_CNTR11_REG(PeripheralBase)) \
  )

/* ----------------------------------------------------------------------------
   -- Get_Counter13Value
   ---------------------------------------------------------------------------- */

/**
 * @brief Inputs are not checked (invalid value will cause undefined behavior).
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @par Example:
 *      @code
 *      TSI_PDD_Get_Counter13Value(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define TSI_PDD_Get_Counter13Value(PeripheralBase) ( \
    getReg32(TSI_CNTR13_REG(PeripheralBase)) \
  )

/* ----------------------------------------------------------------------------
   -- Get_Counter15Value
   ---------------------------------------------------------------------------- */

/**
 * @brief Inputs are not checked (invalid value will cause undefined behavior).
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @par Example:
 *      @code
 *      TSI_PDD_Get_Counter15Value(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define TSI_PDD_Get_Counter15Value(PeripheralBase) ( \
    getReg32(TSI_CNTR15_REG(PeripheralBase)) \
  )

/* ----------------------------------------------------------------------------
   -- Set_Threshold
   ---------------------------------------------------------------------------- */

/**
 * @brief Inputs are not checked (invalid value will cause undefined behavior).
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param threshold  This parameter is a 32-bit value.
 * @param index  This parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @par Example:
 *      @code
 *      TSI_PDD_Set_Threshold(<peripheral>_BASE_PTR, 1, 1);
 *      @endcode
 */
#define TSI_PDD_Set_Threshold(PeripheralBase, threshold, index) ( \
    setReg32(TSI_THRESHLD_REG(PeripheralBase, index), threshold) \
  )

/* ----------------------------------------------------------------------------
   -- Get_Threshold
   ---------------------------------------------------------------------------- */

/**
 * @brief Inputs are not checked (invalid value will cause undefined behavior).
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param index  This parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @par Example:
 *      @code
 *      TSI_PDD_Get_Threshold(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define TSI_PDD_Get_Threshold(PeripheralBase, index) ( \
    getReg32(TSI_THRESHLD_REG(PeripheralBase, index)) \
  )

/* ----------------------------------------------------------------------------
   -- ClockGatingEnable
   ---------------------------------------------------------------------------- */

/**
 * @brief Inputs are not checked (invalid value will cause undefined behavior).
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @par Example:
 *      @code
 *      TSI_PDD_ClockGatingEnable(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define TSI_PDD_ClockGatingEnable(PeripheralBase) ( \
    setReg32Bits(SIM_SCGC5_REG(PeripheralBase), SIM_SCGC5_TSI_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- ClockGatingDisable
   ---------------------------------------------------------------------------- */

/**
 * @brief Inputs are not checked (invalid value will cause undefined behavior).
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @par Example:
 *      @code
 *      TSI_PDD_ClockGatingDisable(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define TSI_PDD_ClockGatingDisable(PeripheralBase) ( \
    clrReg32Bits(SIM_SCGC5_REG(PeripheralBase), SIM_SCGC5_TSI_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- ReadStatusFlags
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the value of the status flags.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: TSI0_GENCS.
 * @par Example:
 *      @code
 *      uint32_t result = TSI_PDD_ReadStatusFlags(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define TSI_PDD_ReadStatusFlags(PeripheralBase) ( \
    (uint32_t)(( \
     TSI_GENCS_REG(PeripheralBase)) & ( \
     (uint32_t)(TSI_GENCS_OUTRGF_MASK | TSI_GENCS_EOSF_MASK))) \
  )

/* ----------------------------------------------------------------------------
   -- ClearStatusFlags
   ---------------------------------------------------------------------------- */

/**
 * @brief Clears the flags of the status 2 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mask Mask of interrupt requests. This parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: TSI0_GENCS.
 * @par Example:
 *      @code
 *      TSI_PDD_ClearStatusFlags(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define TSI_PDD_ClearStatusFlags(PeripheralBase, Mask) ( \
    TSI_GENCS_REG(PeripheralBase) |= \
     (uint32_t)(Mask) \
  )

/* ----------------------------------------------------------------------------
   -- SetTouchSensitingInterruptType
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the touch sensiting interrupt type.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Type Touch sensiting interrupt type. This parameter is of "Touch
 *        sensiting interrupt type constants" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: TSI0_GENCS.
 * @par Example:
 *      @code
 *      TSI_PDD_SetTouchSensitingInterruptType(<peripheral>_BASE_PTR,
 *      TSI_PDD_OUT_OF_RANGE_INT_TYPE);
 *      @endcode
 */
#define TSI_PDD_SetTouchSensitingInterruptType(PeripheralBase, Type) ( \
    TSI_GENCS_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       TSI_GENCS_REG(PeripheralBase)) & (( \
       (uint32_t)(~(uint32_t)TSI_GENCS_ESOR_MASK)) & (( \
       (uint32_t)(~(uint32_t)TSI_GENCS_EOSF_MASK)) & ( \
       (uint32_t)(~(uint32_t)TSI_GENCS_OUTRGF_MASK)))))) | ( \
      (uint32_t)(Type))) \
  )

/* ----------------------------------------------------------------------------
   -- SetAnalogModeSetup
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the analog mode setup.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mode Analog mode setup. This parameter is of "Analog mode setup
 *        constants" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: TSI0_GENCS.
 * @par Example:
 *      @code
 *      TSI_PDD_SetAnalogModeSetup(<peripheral>_BASE_PTR,
 *      TSI_PDD_NON_NOISE_DETECTION);
 *      @endcode
 */
#define TSI_PDD_SetAnalogModeSetup(PeripheralBase, Mode) ( \
    TSI_GENCS_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       TSI_GENCS_REG(PeripheralBase)) & (( \
       (uint32_t)(~(uint32_t)TSI_GENCS_MODE_MASK)) & (( \
       (uint32_t)(~(uint32_t)TSI_GENCS_EOSF_MASK)) & ( \
       (uint32_t)(~(uint32_t)TSI_GENCS_OUTRGF_MASK)))))) | ( \
      (uint32_t)(Mode))) \
  )

/* ----------------------------------------------------------------------------
   -- SetReferenceOscillatorChargeCurrent
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the reference oscillator charge and discharge current value.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Charge and discharge current value. This parameter is of
 *        "Reference oscillator charge and discharge current value constants" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: TSI0_GENCS.
 * @par Example:
 *      @code
 *      TSI_PDD_SetReferenceOscillatorChargeCurrent(<peripheral>_BASE_PTR,
 *      TSI_PDD_REFERENCE_OSC_CHARGE_CURRENT_500nA);
 *      @endcode
 */
#define TSI_PDD_SetReferenceOscillatorChargeCurrent(PeripheralBase, Value) ( \
    TSI_GENCS_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       TSI_GENCS_REG(PeripheralBase)) & (( \
       (uint32_t)(~(uint32_t)TSI_GENCS_REFCHRG_MASK)) & (( \
       (uint32_t)(~(uint32_t)TSI_GENCS_EOSF_MASK)) & ( \
       (uint32_t)(~(uint32_t)TSI_GENCS_OUTRGF_MASK)))))) | ( \
      (uint32_t)(Value))) \
  )

/* ----------------------------------------------------------------------------
   -- SetDeltaVoltage
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the delta voltage value applied to electrode oscilator.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Delta voltage value. This parameter is of "Delta voltage
 *        constants" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: TSI0_GENCS.
 * @par Example:
 *      @code
 *      TSI_PDD_SetDeltaVoltage(<peripheral>_BASE_PTR,
 *      TSI_PDD_DELTA_VOLTAGE_1030mV);
 *      @endcode
 */
#define TSI_PDD_SetDeltaVoltage(PeripheralBase, Value) ( \
    TSI_GENCS_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       TSI_GENCS_REG(PeripheralBase)) & (( \
       (uint32_t)(~(uint32_t)TSI_GENCS_DVOLT_MASK)) & (( \
       (uint32_t)(~(uint32_t)TSI_GENCS_EOSF_MASK)) & ( \
       (uint32_t)(~(uint32_t)TSI_GENCS_OUTRGF_MASK)))))) | ( \
      (uint32_t)(Value))) \
  )

/* ----------------------------------------------------------------------------
   -- SetExternalOscillatorChargeCurrent
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the external (electrode) oscillator charge and discharge current
 * value.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Charge and discharge current value. This parameter is of
 *        "External oscillator charge and discharge current value constants" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: TSI0_GENCS.
 * @par Example:
 *      @code
 *      TSI_PDD_SetExternalOscillatorChargeCurrent(<peripheral>_BASE_PTR,
 *      TSI_PDD_EXTERNAL_OSC_CHARGE_CURRENT_500nA);
 *      @endcode
 */
#define TSI_PDD_SetExternalOscillatorChargeCurrent(PeripheralBase, Value) ( \
    TSI_GENCS_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       TSI_GENCS_REG(PeripheralBase)) & (( \
       (uint32_t)(~(uint32_t)TSI_GENCS_EXTCHRG_MASK)) & (( \
       (uint32_t)(~(uint32_t)TSI_GENCS_EOSF_MASK)) & ( \
       (uint32_t)(~(uint32_t)TSI_GENCS_OUTRGF_MASK)))))) | ( \
      (uint32_t)(Value))) \
  )

/* ----------------------------------------------------------------------------
   -- SetExternalOscillatorPrescaler
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the external (electrode) oscillator prescaler value.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Prescaler value. This parameter is of "External oscillator
 *        prescaler value constants" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: TSI0_GENCS.
 * @par Example:
 *      @code
 *      TSI_PDD_SetExternalOscillatorPrescaler(<peripheral>_BASE_PTR,
 *      TSI_PDD_EXTERNAL_OSC_DIVIDED_BY_1);
 *      @endcode
 */
#define TSI_PDD_SetExternalOscillatorPrescaler(PeripheralBase, Value) ( \
    TSI_GENCS_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       TSI_GENCS_REG(PeripheralBase)) & (( \
       (uint32_t)(~(uint32_t)TSI_GENCS_PS_MASK)) & (( \
       (uint32_t)(~(uint32_t)TSI_GENCS_EOSF_MASK)) & ( \
       (uint32_t)(~(uint32_t)TSI_GENCS_OUTRGF_MASK)))))) | ( \
      (uint32_t)(Value))) \
  )

/* ----------------------------------------------------------------------------
   -- SetNumberOfScanTimesPerElectrode
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the  the scan number for each electrode.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Type Prescaler value. This parameter is of "Number of scan times per
 *        electrode constants" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: TSI0_GENCS.
 * @par Example:
 *      @code
 *      TSI_PDD_SetNumberOfScanTimesPerElectrode(<peripheral>_BASE_PTR,
 *      TSI_PDD_SCAN_PER_ELECTRODE_1);
 *      @endcode
 */
#define TSI_PDD_SetNumberOfScanTimesPerElectrode(PeripheralBase, Type) ( \
    TSI_GENCS_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       TSI_GENCS_REG(PeripheralBase)) & (( \
       (uint32_t)(~(uint32_t)TSI_GENCS_NSCN_MASK)) & (( \
       (uint32_t)(~(uint32_t)TSI_GENCS_EOSF_MASK)) & ( \
       (uint32_t)(~(uint32_t)TSI_GENCS_OUTRGF_MASK)))))) | ( \
      (uint32_t)(Type))) \
  )

/* ----------------------------------------------------------------------------
   -- EnableInterrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables the TSI interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: TSI0_GENCS.
 * @par Example:
 *      @code
 *      TSI_PDD_EnableInterrupt(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define TSI_PDD_EnableInterrupt(PeripheralBase) ( \
    TSI_GENCS_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(TSI_GENCS_REG(PeripheralBase) | TSI_GENCS_TSIIEN_MASK)) & (( \
      (uint32_t)(~(uint32_t)TSI_GENCS_EOSF_MASK)) & ( \
      (uint32_t)(~(uint32_t)TSI_GENCS_OUTRGF_MASK)))) \
  )

/* ----------------------------------------------------------------------------
   -- DisableInterrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Disables the TSI interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: TSI0_GENCS.
 * @par Example:
 *      @code
 *      TSI_PDD_DisableInterrupt(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define TSI_PDD_DisableInterrupt(PeripheralBase) ( \
    TSI_GENCS_REG(PeripheralBase) &= \
     (uint32_t)(( \
      (uint32_t)(~(uint32_t)TSI_GENCS_TSIIEN_MASK)) & (( \
      (uint32_t)(~(uint32_t)TSI_GENCS_EOSF_MASK)) & ( \
      (uint32_t)(~(uint32_t)TSI_GENCS_OUTRGF_MASK)))) \
  )

/* ----------------------------------------------------------------------------
   -- EnableModuleFunctionInLowPowerMode
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables/disables TSI module function in low power mode.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of TSI module in low power mode. This parameter
 *        is of "Global enumeration used for specifying general enable/disable
 *        states (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: TSI0_GENCS.
 * @par Example:
 *      @code
 *      TSI_PDD_EnableModuleFunctionInLowPowerMode(<peripheral>_BASE_PTR,
 *      PDD_DISABLE);
 *      @endcode
 */
#define TSI_PDD_EnableModuleFunctionInLowPowerMode(PeripheralBase, State) ( \
    TSI_GENCS_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       TSI_GENCS_REG(PeripheralBase)) & (( \
       (uint32_t)(~(uint32_t)TSI_GENCS_STPE_MASK)) & (( \
       (uint32_t)(~(uint32_t)TSI_GENCS_EOSF_MASK)) & ( \
       (uint32_t)(~(uint32_t)TSI_GENCS_OUTRGF_MASK)))))) | ( \
      (uint32_t)((uint32_t)(State) << TSI_GENCS_STPE_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SetScanTriggerMode
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the scan trigger mode.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mode Trigger mode. This parameter is of "External scan trigger mode
 *        constants" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: TSI0_GENCS.
 * @par Example:
 *      @code
 *      TSI_PDD_SetScanTriggerMode(<peripheral>_BASE_PTR,
 *      TSI_PDD_SOFTWARE_TRIGGER_SCAN);
 *      @endcode
 */
#define TSI_PDD_SetScanTriggerMode(PeripheralBase, Mode) ( \
    TSI_GENCS_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       TSI_GENCS_REG(PeripheralBase)) & (( \
       (uint32_t)(~(uint32_t)TSI_GENCS_STM_MASK)) & (( \
       (uint32_t)(~(uint32_t)TSI_GENCS_EOSF_MASK)) & ( \
       (uint32_t)(~(uint32_t)TSI_GENCS_OUTRGF_MASK)))))) | ( \
      (uint32_t)(Mode))) \
  )

/* ----------------------------------------------------------------------------
   -- GetScanProgressStatus
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the scan in progress status.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of "Scan in progress status constants." type. The
 *         value is cast to "uint32_t".
 * @remarks The macro accesses the following registers: TSI0_GENCS.
 * @par Example:
 *      @code
 *      uint32_t result = TSI_PDD_GetScanProgressStatus(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define TSI_PDD_GetScanProgressStatus(PeripheralBase) ( \
    (uint32_t)(TSI_GENCS_REG(PeripheralBase) & TSI_GENCS_SCNIP_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- EnableCurrentSourcePairSwap
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables/disables current source pair swap.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of current source pair swap. This parameter is
 *        of "Global enumeration used for specifying general enable/disable states
 *        (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: TSI0_GENCS.
 * @par Example:
 *      @code
 *      TSI_PDD_EnableCurrentSourcePairSwap(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define TSI_PDD_EnableCurrentSourcePairSwap(PeripheralBase, State) ( \
    TSI_GENCS_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       TSI_GENCS_REG(PeripheralBase)) & (( \
       (uint32_t)(~(uint32_t)TSI_GENCS_CURSW_MASK)) & (( \
       (uint32_t)(~(uint32_t)TSI_GENCS_EOSF_MASK)) & ( \
       (uint32_t)(~(uint32_t)TSI_GENCS_OUTRGF_MASK)))))) | ( \
      (uint32_t)((uint32_t)(State) << TSI_GENCS_CURSW_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- ReadGeneralControlAndStatusReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads general control and status register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: TSI0_GENCS.
 * @par Example:
 *      @code
 *      uint32_t result =
 *      TSI_PDD_ReadGeneralControlAndStatusReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define TSI_PDD_ReadGeneralControlAndStatusReg(PeripheralBase) ( \
    TSI_GENCS_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteGeneralControlAndStatusReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes new value specified by the Value parameter into general control
 * and status register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the general control and status register.
 *        This parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: TSI0_GENCS.
 * @par Example:
 *      @code
 *      TSI_PDD_WriteGeneralControlAndStatusReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define TSI_PDD_WriteGeneralControlAndStatusReg(PeripheralBase, Value) ( \
    TSI_GENCS_REG(PeripheralBase) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- SelectInitialChannel
   ---------------------------------------------------------------------------- */

/**
 * @brief Selects current channel to be measured.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param ChannelNum Channel number value[0..15]. This parameter is a 4-bit
 *        value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: TSI0_DATA.
 * @par Example:
 *      @code
 *      TSI_PDD_SelectInitialChannel(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define TSI_PDD_SelectInitialChannel(PeripheralBase, ChannelNum) ( \
    TSI_DATA_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(TSI_DATA_REG(PeripheralBase) & (uint32_t)(~(uint32_t)TSI_DATA_TSICH_MASK))) | ( \
      (uint32_t)((uint32_t)(ChannelNum) << TSI_DATA_TSICH_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- EnableDmaRequest
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables or disables the DMA transfer.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of DMA function. This parameter is of "Global
 *        enumeration used for specifying general enable/disable states
 *        (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: TSI0_DATA.
 * @par Example:
 *      @code
 *      TSI_PDD_EnableDmaRequest(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define TSI_PDD_EnableDmaRequest(PeripheralBase, State) ( \
    TSI_DATA_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(TSI_DATA_REG(PeripheralBase) & (uint32_t)(~(uint32_t)TSI_DATA_DMAEN_MASK))) | ( \
      (uint32_t)((uint32_t)(State) << TSI_DATA_DMAEN_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SoftwareStartElectrodeChannelScan
   ---------------------------------------------------------------------------- */

/**
 * @brief Starts the electrode channel scan.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: TSI0_DATA.
 * @par Example:
 *      @code
 *      TSI_PDD_SoftwareStartElectrodeChannelScan(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define TSI_PDD_SoftwareStartElectrodeChannelScan(PeripheralBase) ( \
    TSI_DATA_REG(PeripheralBase) |= \
     TSI_DATA_SWTS_MASK \
  )

/* ----------------------------------------------------------------------------
   -- GetConversionCounterValue
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the value of the TSI conversion counter.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 16-bit value.
 * @remarks The macro accesses the following registers: TSI0_DATA.
 * @par Example:
 *      @code
 *      uint16_t result =
 *      TSI_PDD_GetConversionCounterValue(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define TSI_PDD_GetConversionCounterValue(PeripheralBase) ( \
    (uint16_t)(TSI_DATA_REG(PeripheralBase) & TSI_DATA_TSICNT_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- ReadDataReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads data register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: TSI0_DATA.
 * @par Example:
 *      @code
 *      uint32_t result = TSI_PDD_ReadDataReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define TSI_PDD_ReadDataReg(PeripheralBase) ( \
    TSI_DATA_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteDataReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes new value specified by the Value parameter into data register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the data register. This parameter is a
 *        32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: TSI0_DATA.
 * @par Example:
 *      @code
 *      TSI_PDD_WriteDataReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define TSI_PDD_WriteDataReg(PeripheralBase, Value) ( \
    TSI_DATA_REG(PeripheralBase) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- SetWakeupHighTresholedValue
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the wakeup channel High-threshold value.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value High-threshold value[0..65535]. This parameter is a 16-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: TSI0_TSHD.
 * @par Example:
 *      @code
 *      TSI_PDD_SetWakeupHighTresholedValue(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define TSI_PDD_SetWakeupHighTresholedValue(PeripheralBase, Value) ( \
    TSI_TSHD_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(TSI_TSHD_REG(PeripheralBase) & (uint32_t)(~(uint32_t)TSI_TSHD_THRESH_MASK))) | ( \
      (uint32_t)((uint32_t)(Value) << TSI_TSHD_THRESH_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SetWakeupLowTresholedValue
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the wakeup channel Low-threshold value.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Low-threshold value[0..65535]. This parameter is a 16-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: TSI0_TSHD.
 * @par Example:
 *      @code
 *      TSI_PDD_SetWakeupLowTresholedValue(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define TSI_PDD_SetWakeupLowTresholedValue(PeripheralBase, Value) ( \
    TSI_TSHD_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(TSI_TSHD_REG(PeripheralBase) & (uint32_t)(~(uint32_t)TSI_TSHD_THRESL_MASK))) | ( \
      (uint32_t)(Value))) \
  )

/* ----------------------------------------------------------------------------
   -- ReadThresholdReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads threshold register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: TSI0_TSHD.
 * @par Example:
 *      @code
 *      uint32_t result = TSI_PDD_ReadThresholdReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define TSI_PDD_ReadThresholdReg(PeripheralBase) ( \
    TSI_TSHD_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteThresholdReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes new value specified by the Value parameter into threshold
 * register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the threshold register. This parameter is
 *        a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: TSI0_TSHD.
 * @par Example:
 *      @code
 *      TSI_PDD_WriteThresholdReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define TSI_PDD_WriteThresholdReg(PeripheralBase, Value) ( \
    TSI_TSHD_REG(PeripheralBase) = \
     (uint32_t)(Value) \
  )
#endif  /* #if defined(TSI_PDD_H_) */

/* TSI_PDD.h, eof. */
