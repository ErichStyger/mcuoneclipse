/*
  PDD layer implementation for peripheral type MCM
  (C) 2013 Freescale, Inc. All rights reserved.

  This file is static and it is generated from API-Factory
*/

#if !defined(MCM_PDD_H_)
#define MCM_PDD_H_

/* ----------------------------------------------------------------------------
   -- Test if supported MCU is active
   ---------------------------------------------------------------------------- */

#if !defined(MCU_ACTIVE)
  // No MCU is active
  #error MCM PDD library: No derivative is active. Place proper #include with PDD memory map before including PDD library.
#elif \
      !defined(MCU_MK10D10) /* MCM */ && \
      !defined(MCU_MK10D7) /* MCM */ && \
      !defined(MCU_MK10F12) /* MCM */ && \
      !defined(MCU_MK10DZ10) /* MCM */ && \
      !defined(MCU_MK11D5) /* MCM */ && \
      !defined(MCU_MK11D5WS) /* MCM */ && \
      !defined(MCU_MK12D5) /* MCM */ && \
      !defined(MCU_MK20D10) /* MCM */ && \
      !defined(MCU_MK20D7) /* MCM */ && \
      !defined(MCU_MK20F12) /* MCM */ && \
      !defined(MCU_MK20DZ10) /* MCM */ && \
      !defined(MCU_MK21D5) /* MCM */ && \
      !defined(MCU_MK21D5WS) /* MCM */ && \
      !defined(MCU_MK21F12) /* MCM */ && \
      !defined(MCU_MK21F12WS) /* MCM */ && \
      !defined(MCU_MK22D5) /* MCM */ && \
      !defined(MCU_MK22F12810) /* MCM */ && \
      !defined(MCU_MK22F12) /* MCM */ && \
      !defined(MCU_MK22F25612) /* MCM */ && \
      !defined(MCU_MK22F51212) /* MCM */ && \
      !defined(MCU_MK24F12) /* MCM */ && \
      !defined(MCU_MK30D10) /* MCM */ && \
      !defined(MCU_MK30D7) /* MCM */ && \
      !defined(MCU_MK30DZ10) /* MCM */ && \
      !defined(MCU_MK40D10) /* MCM */ && \
      !defined(MCU_MK40D7) /* MCM */ && \
      !defined(MCU_MK40DZ10) /* MCM */ && \
      !defined(MCU_MK40X256VMD100) /* MCM */ && \
      !defined(MCU_MK50D10) /* MCM */ && \
      !defined(MCU_MK50D7) /* MCM */ && \
      !defined(MCU_MK50DZ10) /* MCM */ && \
      !defined(MCU_MK51D10) /* MCM */ && \
      !defined(MCU_MK51D7) /* MCM */ && \
      !defined(MCU_MK51DZ10) /* MCM */ && \
      !defined(MCU_MK52D10) /* MCM */ && \
      !defined(MCU_MK52DZ10) /* MCM */ && \
      !defined(MCU_MK53D10) /* MCM */ && \
      !defined(MCU_MK53DZ10) /* MCM */ && \
      !defined(MCU_MK60D10) /* MCM */ && \
      !defined(MCU_MK60F12) /* MCM */ && \
      !defined(MCU_MK60F15) /* MCM */ && \
      !defined(MCU_MK60DZ10) /* MCM */ && \
      !defined(MCU_MK60N512VMD100) /* MCM */ && \
      !defined(MCU_MK61F12) /* MCM */ && \
      !defined(MCU_MK61F15) /* MCM */ && \
      !defined(MCU_MK61F12WS) /* MCM */ && \
      !defined(MCU_MK61F15WS) /* MCM */ && \
      !defined(MCU_MK63F12) /* MCM */ && \
      !defined(MCU_MK63F12WS) /* MCM */ && \
      !defined(MCU_MK64F12) /* MCM */ && \
      !defined(MCU_MK65F18) /* MCM */ && \
      !defined(MCU_MK65F18WS) /* MCM */ && \
      !defined(MCU_MK66F18) /* MCM */ && \
      !defined(MCU_MK70F12) /* MCM */ && \
      !defined(MCU_MK70F15) /* MCM */ && \
      !defined(MCU_MK70F12WS) /* MCM */ && \
      !defined(MCU_MK70F15WS) /* MCM */ && \
      !defined(MCU_MKE02Z2) /* MCM */ && \
      !defined(MCU_MKE02Z4) /* MCM */ && \
      !defined(MCU_SKEAZN642) /* MCM */ && \
      !defined(MCU_MKE04Z1284) /* MCM */ && \
      !defined(MCU_MKE04Z4) /* MCM */ && \
      !defined(MCU_SKEAZN84) /* MCM */ && \
      !defined(MCU_MKE06Z4) /* MCM */ && \
      !defined(MCU_MKL02Z4) /* MCM */ && \
      !defined(MCU_MKL03Z4) /* MCM */ && \
      !defined(MCU_MKL04Z4) /* MCM */ && \
      !defined(MCU_MKL05Z4) /* MCM */ && \
      !defined(MCU_MKL14Z4) /* MCM */ && \
      !defined(MCU_MKL15Z4) /* MCM */ && \
      !defined(MCU_MKL16Z4) /* MCM */ && \
      !defined(MCU_MKL24Z4) /* MCM */ && \
      !defined(MCU_MKL25Z4) /* MCM */ && \
      !defined(MCU_MKL26Z4) /* MCM */ && \
      !defined(MCU_MKL34Z4) /* MCM */ && \
      !defined(MCU_MKL36Z4) /* MCM */ && \
      !defined(MCU_MKL46Z4) /* MCM */ && \
      !defined(MCU_MKV10Z7) /* MCM */ && \
      !defined(MCU_MKV31F12810) /* MCM */ && \
      !defined(MCU_MKV31F25612) /* MCM */ && \
      !defined(MCU_MKV31F51212) /* MCM */ && \
      !defined(MCU_MKW01Z4) /* MCM */ && \
      !defined(MCU_MKW21D5) /* MCM */ && \
      !defined(MCU_MKW21D5WS) /* MCM */ && \
      !defined(MCU_MKW22D5) /* MCM */ && \
      !defined(MCU_MKW22D5WS) /* MCM */ && \
      !defined(MCU_MKW24D5) /* MCM */ && \
      !defined(MCU_MKW24D5WS) /* MCM */ && \
      !defined(MCU_SKEAZ1284) /* MCM */
  // Unsupported MCU is active
  #error MCM PDD library: Unsupported derivative is active.
#endif

#include "PDD_Types.h"

/* ----------------------------------------------------------------------------
   -- Method symbol definitions
   ---------------------------------------------------------------------------- */

/* Slave bus connection to AXBS input port masks constants (for
   GetSlaveBusConnectionToAxbsInputPort macro). */
#define MCM_PDD_SLAVE_BUS_CONNECTION_TO_AXBS_INPUT_PORT_0 0x1U /**< A bus slave connection to AXBS input port 0 is present */
#define MCM_PDD_SLAVE_BUS_CONNECTION_TO_AXBS_INPUT_PORT_1 0x2U /**< A bus slave connection to AXBS input port 1 is present */
#define MCM_PDD_SLAVE_BUS_CONNECTION_TO_AXBS_INPUT_PORT_2 0x4U /**< A bus slave connection to AXBS input port 2 is present */
#define MCM_PDD_SLAVE_BUS_CONNECTION_TO_AXBS_INPUT_PORT_3 0x8U /**< A bus slave connection to AXBS input port 3 is present */
#define MCM_PDD_SLAVE_BUS_CONNECTION_TO_AXBS_INPUT_PORT_4 0x10U /**< A bus slave connection to AXBS input port 4 is present */
#define MCM_PDD_SLAVE_BUS_CONNECTION_TO_AXBS_INPUT_PORT_5 0x20U /**< A bus slave connection to AXBS input port 5 is present */
#define MCM_PDD_SLAVE_BUS_CONNECTION_TO_AXBS_INPUT_PORT_6 0x40U /**< A bus slave connection to AXBS input port 6 is present */
#define MCM_PDD_SLAVE_BUS_CONNECTION_TO_AXBS_INPUT_PORT_7 0x80U /**< A bus slave connection to AXBS input port 7 is present */

/* Master bus connection to AXBS input port masks constants (for
   GetMasterBusConnectionToAxbsInputPortMask macro). */
#define MCM_PDD_MASTER_BUS_CONNECTION_TO_AXBS_INPUT_PORT_0 0x1U /**< A bus master connection to AXBS input port 0 is present */
#define MCM_PDD_MASTER_BUS_CONNECTION_TO_AXBS_INPUT_PORT_1 0x2U /**< A bus master connection to AXBS input port 1 is present */
#define MCM_PDD_MASTER_BUS_CONNECTION_TO_AXBS_INPUT_PORT_2 0x4U /**< A bus master connection to AXBS input port 2 is present */
#define MCM_PDD_MASTER_BUS_CONNECTION_TO_AXBS_INPUT_PORT_3 0x8U /**< A bus master connection to AXBS input port 3 is present */
#define MCM_PDD_MASTER_BUS_CONNECTION_TO_AXBS_INPUT_PORT_4 0x10U /**< A bus master connection to AXBS input port 4 is present */
#define MCM_PDD_MASTER_BUS_CONNECTION_TO_AXBS_INPUT_PORT_5 0x20U /**< A bus master connection to AXBS input port 5 is present */
#define MCM_PDD_MASTER_BUS_CONNECTION_TO_AXBS_INPUT_PORT_6 0x40U /**< A bus master connection to AXBS input port 6 is present */
#define MCM_PDD_MASTER_BUS_CONNECTION_TO_AXBS_INPUT_PORT_7 0x80U /**< A bus master connection to AXBS input port 7 is present */

#if ((defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MKL02Z4)) || (defined(MCU_MKL04Z4)) || (defined(MCU_MKL05Z4)) || (defined(MCU_MKL14Z4)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL16Z4)) || (defined(MCU_MKL24Z4)) || (defined(MCU_MKL25Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL34Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW01Z4)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)))
/* Crossbar master arbitration type */
  #define MCM_PDD_FIXED_PRIORITY 0U                /**< Fixed-priority arbitration for the crossbar masters */
  #define MCM_PDD_ROUND_ROBIN    0x200U            /**< Round-robin arbitration for the crossbar masters */

#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK65F18)) || (defined(MCU_MK65F18WS)) || (defined(MCU_MK66F18)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) */
/* Crossbar master arbitration type */
  #define MCM_PDD_FIXED_PRIORITY 0U                /**< Fixed-priority arbitration for the crossbar masters */
  #define MCM_PDD_ROUND_ROBIN    0x1U              /**< Round-robin arbitration for the crossbar masters */

#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK65F18)) || (defined(MCU_MK65F18WS)) || (defined(MCU_MK66F18)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) */

/* ----------------------------------------------------------------------------
   -- GetSlaveBusConnectionToAxbsInputPortMask
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns present mask value of a corresponding connection to the
 * crossbar switch's slave input port.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: MCM_PLASC.
 * @par Example:
 *      @code
 *      uint8_t result =
 *      MCM_PDD_GetSlaveBusConnectionToAxbsInputPortMask(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define MCM_PDD_GetSlaveBusConnectionToAxbsInputPortMask(PeripheralBase) ( \
    (uint8_t)(MCM_PLASC_REG(PeripheralBase) & MCM_PLASC_ASC_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- ReadCrossbarSwitchSlaveConfigurationReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads crossbar switch (AXBS) slave configuration register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 16-bit value.
 * @remarks The macro accesses the following registers: MCM_PLASC.
 * @par Example:
 *      @code
 *      uint16_t result =
 *      MCM_PDD_ReadCrossbarSwitchSlaveConfigurationReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define MCM_PDD_ReadCrossbarSwitchSlaveConfigurationReg(PeripheralBase) ( \
    MCM_PLASC_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- GetMasterBusConnectionToAxbsInputPortMask
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns present mask value of a corresponding connection to the
 * crossbar switch's master input port.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: MCM_PLAMC.
 * @par Example:
 *      @code
 *      uint8_t result =
 *      MCM_PDD_GetMasterBusConnectionToAxbsInputPortMask(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define MCM_PDD_GetMasterBusConnectionToAxbsInputPortMask(PeripheralBase) ( \
    (uint8_t)(MCM_PLAMC_REG(PeripheralBase) & MCM_PLAMC_AMC_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- ReadCrossbarSwitchMasterConfigurationReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads crossbar switch (AXBS) master configuration register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 16-bit value.
 * @remarks The macro accesses the following registers: MCM_PLAMC.
 * @par Example:
 *      @code
 *      uint16_t result =
 *      MCM_PDD_ReadCrossbarSwitchMasterConfigurationReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define MCM_PDD_ReadCrossbarSwitchMasterConfigurationReg(PeripheralBase) ( \
    MCM_PLAMC_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- SetCrossbarMastersArbitrationType
   ---------------------------------------------------------------------------- */

/**
 * @brief Selects arbitration type for crossbar masters.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Crossbar masters arbitration type. This parameter is of
 *        "Crossbar master arbitration type" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: MCM_PLACR.
 * @par Example:
 *      @code
 *      MCM_PDD_SetCrossbarMastersArbitrationType(<peripheral>_BASE_PTR,
 *      MCM_PDD_FIXED_PRIORITY);
 *      @endcode
 */
#define MCM_PDD_SetCrossbarMastersArbitrationType(PeripheralBase, State) ( \
    MCM_PLACR_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(MCM_PLACR_REG(PeripheralBase) & (uint32_t)(~(uint32_t)MCM_PLACR_ARB_MASK))) | ( \
      (uint32_t)(State))) \
  )

/* ----------------------------------------------------------------------------
   -- ReadPlatformControlReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads platform control register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: MCM_PLACR.
 * @par Example:
 *      @code
 *      uint32_t result = MCM_PDD_ReadPlatformControlReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define MCM_PDD_ReadPlatformControlReg(PeripheralBase) ( \
    MCM_PLACR_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WritePlatformControlReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes data specified by the Value parameter into platform control
 * register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the platform control register. This
 *        parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: MCM_PLACR.
 * @par Example:
 *      @code
 *      MCM_PDD_WritePlatformControlReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define MCM_PDD_WritePlatformControlReg(PeripheralBase, Value) ( \
    MCM_PLACR_REG(PeripheralBase) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- DisableStallingFlashController
   ---------------------------------------------------------------------------- */

/**
 * @brief Disable stalling flash controller.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: MCM_PLACR.
 * @par Example:
 *      @code
 *      MCM_PDD_DisableStallingFlashController(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define MCM_PDD_DisableStallingFlashController(PeripheralBase) ( \
    MCM_PLACR_REG(PeripheralBase) &= \
     (uint32_t)(~(uint32_t)MCM_PLACR_ESFC_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- EnableStallingFlashController
   ---------------------------------------------------------------------------- */

/**
 * @brief Enable stalling flash controller.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: MCM_PLACR.
 * @par Example:
 *      @code
 *      MCM_PDD_EnableStallingFlashController(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define MCM_PDD_EnableStallingFlashController(PeripheralBase) ( \
    MCM_PLACR_REG(PeripheralBase) |= \
     MCM_PLACR_ESFC_MASK \
  )

/* ----------------------------------------------------------------------------
   -- DisableFlashControllerSpeculation
   ---------------------------------------------------------------------------- */

/**
 * @brief Disable flash controller speculation.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: MCM_PLACR.
 * @par Example:
 *      @code
 *      MCM_PDD_DisableFlashControllerSpeculation(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define MCM_PDD_DisableFlashControllerSpeculation(PeripheralBase) ( \
    MCM_PLACR_REG(PeripheralBase) |= \
     MCM_PLACR_DFCS_MASK \
  )

/* ----------------------------------------------------------------------------
   -- EnableFlashControllerSpeculation
   ---------------------------------------------------------------------------- */

/**
 * @brief Enable flash controller speculation.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: MCM_PLACR.
 * @par Example:
 *      @code
 *      MCM_PDD_EnableFlashControllerSpeculation(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define MCM_PDD_EnableFlashControllerSpeculation(PeripheralBase) ( \
    MCM_PLACR_REG(PeripheralBase) &= \
     (uint32_t)(~(uint32_t)MCM_PLACR_DFCS_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- DisableFlashDataSpeculation
   ---------------------------------------------------------------------------- */

/**
 * @brief Disable flash data speculation.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: MCM_PLACR.
 * @par Example:
 *      @code
 *      MCM_PDD_DisableFlashDataSpeculation(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define MCM_PDD_DisableFlashDataSpeculation(PeripheralBase) ( \
    MCM_PLACR_REG(PeripheralBase) &= \
     (uint32_t)(~(uint32_t)MCM_PLACR_EFDS_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- EnableFlashDataSpeculation
   ---------------------------------------------------------------------------- */

/**
 * @brief Enable flash data speculation.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: MCM_PLACR.
 * @par Example:
 *      @code
 *      MCM_PDD_EnableFlashDataSpeculation(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define MCM_PDD_EnableFlashDataSpeculation(PeripheralBase) ( \
    MCM_PLACR_REG(PeripheralBase) |= \
     MCM_PLACR_EFDS_MASK \
  )

/* ----------------------------------------------------------------------------
   -- EnableFlashControllerCache
   ---------------------------------------------------------------------------- */

/**
 * @brief Enable flash controllerCache.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: MCM_PLACR.
 * @par Example:
 *      @code
 *      MCM_PDD_EnableFlashControllerCache(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define MCM_PDD_EnableFlashControllerCache(PeripheralBase) ( \
    MCM_PLACR_REG(PeripheralBase) &= \
     (uint32_t)(~(uint32_t)MCM_PLACR_DFCC_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- DisableFlashControllerCache
   ---------------------------------------------------------------------------- */

/**
 * @brief Disable flash controllerCache.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: MCM_PLACR.
 * @par Example:
 *      @code
 *      MCM_PDD_DisableFlashControllerCache(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define MCM_PDD_DisableFlashControllerCache(PeripheralBase) ( \
    MCM_PLACR_REG(PeripheralBase) |= \
     MCM_PLACR_DFCC_MASK \
  )

/* ----------------------------------------------------------------------------
   -- EnableFlashControllerInstructionCaching
   ---------------------------------------------------------------------------- */

/**
 * @brief Enable flash controller instruction caching.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: MCM_PLACR.
 * @par Example:
 *      @code
 *      MCM_PDD_EnableFlashControllerInstructionCaching(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define MCM_PDD_EnableFlashControllerInstructionCaching(PeripheralBase) ( \
    MCM_PLACR_REG(PeripheralBase) &= \
     (uint32_t)(~(uint32_t)MCM_PLACR_DFCIC_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- DisableFlashControllerInstructionCaching
   ---------------------------------------------------------------------------- */

/**
 * @brief Disable flash controller instruction caching.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: MCM_PLACR.
 * @par Example:
 *      @code
 *      MCM_PDD_DisableFlashControllerInstructionCaching(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define MCM_PDD_DisableFlashControllerInstructionCaching(PeripheralBase) ( \
    MCM_PLACR_REG(PeripheralBase) |= \
     MCM_PLACR_DFCIC_MASK \
  )

/* ----------------------------------------------------------------------------
   -- EnableFlashControllerDataCaching
   ---------------------------------------------------------------------------- */

/**
 * @brief Enable flash controller data caching.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: MCM_PLACR.
 * @par Example:
 *      @code
 *      MCM_PDD_EnableFlashControllerDataCaching(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define MCM_PDD_EnableFlashControllerDataCaching(PeripheralBase) ( \
    MCM_PLACR_REG(PeripheralBase) &= \
     (uint32_t)(~(uint32_t)MCM_PLACR_DFCDA_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- DisableFlashControllerDataCaching
   ---------------------------------------------------------------------------- */

/**
 * @brief Disable flash controller data caching.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: MCM_PLACR.
 * @par Example:
 *      @code
 *      MCM_PDD_DisableFlashControllerDataCaching(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define MCM_PDD_DisableFlashControllerDataCaching(PeripheralBase) ( \
    MCM_PLACR_REG(PeripheralBase) |= \
     MCM_PLACR_DFCDA_MASK \
  )

/* ----------------------------------------------------------------------------
   -- InvalidateFlashCache
   ---------------------------------------------------------------------------- */

/**
 * @brief Invalidates flash cache.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: MCM_PLACR.
 * @par Example:
 *      @code
 *      MCM_PDD_InvalidateFlashCache(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define MCM_PDD_InvalidateFlashCache(PeripheralBase) ( \
    MCM_PLACR_REG(PeripheralBase) |= \
     MCM_PLACR_CFCC_MASK \
  )

/* ----------------------------------------------------------------------------
   -- EnableComputeOperationWakeupOnInterrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Enable compute operation wakeup on interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: MCM_CPO.
 * @par Example:
 *      @code
 *      MCM_PDD_EnableComputeOperationWakeupOnInterrupt(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define MCM_PDD_EnableComputeOperationWakeupOnInterrupt(PeripheralBase) ( \
    MCM_CPO_REG(PeripheralBase) |= \
     MCM_CPO_CPOWOI_MASK \
  )

/* ----------------------------------------------------------------------------
   -- GetComputeOperationState
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns non zero value if compute operation entry has completed or
 * compute operation exit has not completed.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: MCM_CPO.
 * @par Example:
 *      @code
 *      uint32_t result =
 *      MCM_PDD_GetComputeOperationState(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define MCM_PDD_GetComputeOperationState(PeripheralBase) ( \
    (uint32_t)(MCM_CPO_REG(PeripheralBase) & MCM_CPO_CPOACK_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- GetComputeOperationRequest
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns non zero value if compute operation request is active.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: MCM_CPO.
 * @par Example:
 *      @code
 *      uint32_t result =
 *      MCM_PDD_GetComputeOperationRequest(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define MCM_PDD_GetComputeOperationRequest(PeripheralBase) ( \
    (uint32_t)(MCM_CPO_REG(PeripheralBase) & MCM_CPO_CPOREQ_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- SetComputeOperationRequest
   ---------------------------------------------------------------------------- */

/**
 * @brief Set compute operation request.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: MCM_CPO.
 * @par Example:
 *      @code
 *      MCM_PDD_SetComputeOperationRequest(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define MCM_PDD_SetComputeOperationRequest(PeripheralBase) ( \
    MCM_CPO_REG(PeripheralBase) |= \
     MCM_CPO_CPOREQ_MASK \
  )

/* ----------------------------------------------------------------------------
   -- ClearComputeOperationRequest
   ---------------------------------------------------------------------------- */

/**
 * @brief Clear compute operation request.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: MCM_CPO.
 * @par Example:
 *      @code
 *      MCM_PDD_ClearComputeOperationRequest(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define MCM_PDD_ClearComputeOperationRequest(PeripheralBase) ( \
    MCM_CPO_REG(PeripheralBase) &= \
     (uint32_t)(~(uint32_t)MCM_CPO_CPOREQ_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- ReadComputeOperationControlReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads compute operation control register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: MCM_CPO.
 * @par Example:
 *      @code
 *      uint32_t result =
 *      MCM_PDD_ReadComputeOperationControlReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define MCM_PDD_ReadComputeOperationControlReg(PeripheralBase) ( \
    MCM_CPO_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteComputeOperationControlReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes data specified by the Value parameter into compute operation
 * control register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the compute operation control register.
 *        This parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: MCM_CPO.
 * @par Example:
 *      @code
 *      MCM_PDD_WriteComputeOperationControlReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define MCM_PDD_WriteComputeOperationControlReg(PeripheralBase, Value) ( \
    MCM_CPO_REG(PeripheralBase) = \
     (uint32_t)(Value) \
  )
#endif  /* #if defined(MCM_PDD_H_) */

/* MCM_PDD.h, eof. */
