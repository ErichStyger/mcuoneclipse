/*
  PDD layer implementation for peripheral type I2C
  (C) 2013 Freescale, Inc. All rights reserved.

  This file is static and it is generated from API-Factory
*/

#if !defined(I2C_PDD_H_)
#define I2C_PDD_H_

/* ----------------------------------------------------------------------------
   -- Test if supported MCU is active
   ---------------------------------------------------------------------------- */

#if !defined(MCU_ACTIVE)
  // No MCU is active
  #error I2C PDD library: No derivative is active. Place proper #include with PDD memory map before including PDD library.
#elif \
      !defined(MCU_MK10D10) /* I2C0, I2C1 */ && \
      !defined(MCU_MK10D5) /* I2C0 */ && \
      !defined(MCU_MK10D7) /* I2C0, I2C1 */ && \
      !defined(MCU_MK10F12) /* I2C0, I2C1 */ && \
      !defined(MCU_MK10DZ10) /* I2C0, I2C1 */ && \
      !defined(MCU_MK11D5) /* I2C0, I2C1 */ && \
      !defined(MCU_MK11D5WS) /* I2C0, I2C1 */ && \
      !defined(MCU_MK12D5) /* I2C0, I2C1 */ && \
      !defined(MCU_MK20D10) /* I2C0, I2C1 */ && \
      !defined(MCU_MK20D5) /* I2C0 */ && \
      !defined(MCU_MK20D7) /* I2C0, I2C1 */ && \
      !defined(MCU_MK20F12) /* I2C0, I2C1 */ && \
      !defined(MCU_MK20DZ10) /* I2C0, I2C1 */ && \
      !defined(MCU_MK21D5) /* I2C0, I2C1 */ && \
      !defined(MCU_MK21D5WS) /* I2C0, I2C1 */ && \
      !defined(MCU_MK21F12) /* I2C0, I2C1, I2C2 */ && \
      !defined(MCU_MK21F12WS) /* I2C0, I2C1, I2C2 */ && \
      !defined(MCU_MK22D5) /* I2C0, I2C1 */ && \
      !defined(MCU_MK22F12810) /* I2C0, I2C1 */ && \
      !defined(MCU_MK22F12) /* I2C0, I2C1, I2C2 */ && \
      !defined(MCU_MK22F25612) /* I2C0, I2C1 */ && \
      !defined(MCU_MK22F51212) /* I2C0, I2C1 */ && \
      !defined(MCU_MK24F12) /* I2C0, I2C1, I2C2 */ && \
      !defined(MCU_MK30D10) /* I2C0, I2C1 */ && \
      !defined(MCU_MK30D7) /* I2C0, I2C1 */ && \
      !defined(MCU_MK30DZ10) /* I2C0, I2C1 */ && \
      !defined(MCU_MK40D10) /* I2C0, I2C1 */ && \
      !defined(MCU_MK40D7) /* I2C0, I2C1 */ && \
      !defined(MCU_MK40DZ10) /* I2C0, I2C1 */ && \
      !defined(MCU_MK40X256VMD100) /* I2C0, I2C1 */ && \
      !defined(MCU_MK50D10) /* I2C0, I2C1 */ && \
      !defined(MCU_MK50D7) /* I2C0, I2C1 */ && \
      !defined(MCU_MK50DZ10) /* I2C0, I2C1 */ && \
      !defined(MCU_MK51D10) /* I2C0, I2C1 */ && \
      !defined(MCU_MK51D7) /* I2C0, I2C1 */ && \
      !defined(MCU_MK51DZ10) /* I2C0, I2C1 */ && \
      !defined(MCU_MK52D10) /* I2C0, I2C1 */ && \
      !defined(MCU_MK52DZ10) /* I2C0, I2C1 */ && \
      !defined(MCU_MK53D10) /* I2C0, I2C1 */ && \
      !defined(MCU_MK53DZ10) /* I2C0, I2C1 */ && \
      !defined(MCU_MK60D10) /* I2C0, I2C1 */ && \
      !defined(MCU_MK60F12) /* I2C0, I2C1 */ && \
      !defined(MCU_MK60F15) /* I2C0, I2C1 */ && \
      !defined(MCU_MK60DZ10) /* I2C0, I2C1 */ && \
      !defined(MCU_MK60N512VMD100) /* I2C0, I2C1 */ && \
      !defined(MCU_MK61F12) /* I2C0, I2C1 */ && \
      !defined(MCU_MK61F15) /* I2C0, I2C1 */ && \
      !defined(MCU_MK61F12WS) /* I2C0, I2C1 */ && \
      !defined(MCU_MK61F15WS) /* I2C0, I2C1 */ && \
      !defined(MCU_MK63F12) /* I2C0, I2C1, I2C2 */ && \
      !defined(MCU_MK63F12WS) /* I2C0, I2C1, I2C2 */ && \
      !defined(MCU_MK64F12) /* I2C0, I2C1, I2C2 */ && \
      !defined(MCU_MK65F18) /* I2C0, I2C1, I2C2, I2C3 */ && \
      !defined(MCU_MK65F18WS) /* I2C0, I2C1, I2C2, I2C3 */ && \
      !defined(MCU_MK66F18) /* I2C0, I2C1, I2C2, I2C3 */ && \
      !defined(MCU_MK70F12) /* I2C0, I2C1 */ && \
      !defined(MCU_MK70F15) /* I2C0, I2C1 */ && \
      !defined(MCU_MK70F12WS) /* I2C0, I2C1 */ && \
      !defined(MCU_MK70F15WS) /* I2C0, I2C1 */ && \
      !defined(MCU_MKE02Z2) /* I2C0 */ && \
      !defined(MCU_MKE02Z4) /* I2C0 */ && \
      !defined(MCU_SKEAZN642) /* I2C0 */ && \
      !defined(MCU_MKE04Z1284) /* I2C0, I2C1 */ && \
      !defined(MCU_MKE04Z4) /* I2C0 */ && \
      !defined(MCU_SKEAZN84) /* I2C0 */ && \
      !defined(MCU_MKE06Z4) /* I2C0, I2C1 */ && \
      !defined(MCU_MKL02Z4) /* I2C0, I2C1 */ && \
      !defined(MCU_MKL03Z4) /* I2C0 */ && \
      !defined(MCU_MKL04Z4) /* I2C0 */ && \
      !defined(MCU_MKL05Z4) /* I2C0 */ && \
      !defined(MCU_MKL14Z4) /* I2C0, I2C1 */ && \
      !defined(MCU_MKL15Z4) /* I2C0, I2C1 */ && \
      !defined(MCU_MKL16Z4) /* I2C0, I2C1 */ && \
      !defined(MCU_MKL24Z4) /* I2C0, I2C1 */ && \
      !defined(MCU_MKL25Z4) /* I2C0, I2C1 */ && \
      !defined(MCU_MKL26Z4) /* I2C0, I2C1 */ && \
      !defined(MCU_MKL34Z4) /* I2C0, I2C1 */ && \
      !defined(MCU_MKL36Z4) /* I2C0, I2C1 */ && \
      !defined(MCU_MKL46Z4) /* I2C0, I2C1 */ && \
      !defined(MCU_MKV10Z7) /* I2C0 */ && \
      !defined(MCU_MKV31F12810) /* I2C0, I2C1 */ && \
      !defined(MCU_MKV31F25612) /* I2C0, I2C1 */ && \
      !defined(MCU_MKV31F51212) /* I2C0, I2C1 */ && \
      !defined(MCU_MKW01Z4) /* I2C0, I2C1 */ && \
      !defined(MCU_MKW21D5) /* I2C0, I2C1 */ && \
      !defined(MCU_MKW21D5WS) /* I2C0, I2C1 */ && \
      !defined(MCU_MKW22D5) /* I2C0, I2C1 */ && \
      !defined(MCU_MKW22D5WS) /* I2C0, I2C1 */ && \
      !defined(MCU_MKW24D5) /* I2C0, I2C1 */ && \
      !defined(MCU_MKW24D5WS) /* I2C0, I2C1 */ && \
      !defined(MCU_PCK20L4) /* I2C0 */ && \
      !defined(MCU_SKEAZ1284) /* I2C0, I2C1 */
  // Unsupported MCU is active
  #error I2C PDD library: Unsupported derivative is active.
#endif

#include "PDD_Types.h"

/* ----------------------------------------------------------------------------
   -- Method symbol definitions
   ---------------------------------------------------------------------------- */

/* Status flags constants (for ReadStatusReg, GetInterruptFlags,
   ClearInterruptFlags macros). */
#define I2C_PDD_RX_ACKNOWLEDGE      I2C_S_RXAK_MASK /**< Receive acknowledge. */
#define I2C_PDD_INTERRUPT_FLAG      I2C_S_IICIF_MASK /**< Interrupt flag. */
#define I2C_PDD_SLAVE_TRANSMIT      I2C_S_SRW_MASK /**< Slave read/write request. */
#define I2C_PDD_RANGE_ADDRESS_MATCH I2C_S_RAM_MASK /**< Range address match. */
#define I2C_PDD_ARBIT_LOST          I2C_S_ARBL_MASK /**< Arbitration lost. */
#define I2C_PDD_BUS_IS_BUSY         I2C_S_BUSY_MASK /**< Bus busy - set when a START signal is detected. */
#define I2C_PDD_ADDRESSED_AS_SLAVE  I2C_S_IAAS_MASK /**< Addressed as a slave. */
#define I2C_PDD_TX_COMPLETE         I2C_S_TCF_MASK /**< Transfer complete flag. */

/* SCL timeout flags constants (for GetSCLTimeoutInterruptFlags,
   ClearSCLTimeoutInterruptFlags macros). */
#define I2C_PDD_SCL_LOW_TIMEOUT            I2C_SMB_SLTF_MASK /**< SCL low timeout flag. */
#define I2C_PDD_SCL_HI_AND_SDA_HI_TIMEOUT  I2C_SMB_SHTF1_MASK /**< SCL high timeout flag - sets when SCL and SDA are held high more than clock × LoValue / 512. */
#define I2C_PDD_SCL_HI_AND_SDA_LOW_TIMEOUT I2C_SMB_SHTF2_MASK /**< SCL high timeout flag - sets when SCL is held high and SDA is held low more than clock × LoValue/512. */

#if ((defined(MCU_MKL02Z4)) || (defined(MCU_MKL03Z4)) || (defined(MCU_MKL04Z4)) || (defined(MCU_MKL05Z4)) || (defined(MCU_MKL14Z4)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL16Z4)) || (defined(MCU_MKL24Z4)) || (defined(MCU_MKL25Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL34Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKW01Z4)))
/* Status flags constants. */
  #define I2C_PDD_BUS_STOP_FLAG I2C_FLT_STOPF_MASK /**< Stop detected on I2C bus */

#else /* (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK65F18)) || (defined(MCU_MK65F18WS)) || (defined(MCU_MK66F18)) || (defined(MCU_MKE02Z2)) || (defined(MCU_MKE02Z4)) || (defined(MCU_MKE04Z1284)) || (defined(MCU_MKE04Z4)) || (defined(MCU_MKE06Z4)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_SKEAZ1284)) || (defined(MCU_SKEAZN642)) || (defined(MCU_SKEAZN84)) */
/* Status flags constants. */
  #define I2C_PDD_BUS_STOP_FLAG  I2C_FLT_STOPF_MASK /**< Stop detected on I2C bus */
  #define I2C_PDD_BUS_START_FLAG I2C_FLT_STARTF_MASK /**< Start detected on I2C bus */

#endif /* (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK65F18)) || (defined(MCU_MK65F18WS)) || (defined(MCU_MK66F18)) || (defined(MCU_MKE02Z2)) || (defined(MCU_MKE02Z4)) || (defined(MCU_MKE04Z1284)) || (defined(MCU_MKE04Z4)) || (defined(MCU_MKE06Z4)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_SKEAZ1284)) || (defined(MCU_SKEAZN642)) || (defined(MCU_SKEAZN84)) */
/* Frequency multiplier constants (for SetFrequencyMultiplier macro). */
#define I2C_PDD_FREQUENCY_MUL_1 0U               /**< Multiplier factor = 1 */
#define I2C_PDD_FREQUENCY_MUL_2 0x1U             /**< Multiplier factor = 2 */
#define I2C_PDD_FREQUENCY_MUL_4 0x2U             /**< Multiplier factor = 4 */

/* Master mode constants (for MasterMode, GetMasterMode macros). */
#define I2C_PDD_MASTER_MODE 0x20U                /**< Master mode. */
#define I2C_PDD_SLAVE_MODE  0U                   /**< Slave mode. */

/* Transmit mode constants (for SetTransmitMode, GetTransmitMode macros). */
#define I2C_PDD_TX_DIRECTION 0x10U               /**< SDA pin set as output. */
#define I2C_PDD_RX_DIRECTION 0U                  /**< SDA pin set as input. */

/* BUS status constants (for GetBusStatus macro). */
#define I2C_PDD_BUS_IDLE 0U                      /**< Bus is idle. */
#define I2C_PDD_BUS_BUSY 0x20U                   /**< Bus is busy. */

/* Fast SMBus Acknowledge constants (for GetFastSmBusAcknowledge macro). */
#define I2C_PDD_ACK_FOLLOWING_RX_DATA 0U         /**< ACK or NACK is sent on the following receiving data byte. */
#define I2C_PDD_ACK_AFTER_RX_DATA     0x80U      /**< ACK or NACK is sent after receiving a data byte. */

/* Clock source constants (for SetSCLTimeoutBusClockSource macro). */
#define I2C_PDD_BUS_CLOCK       0x10U            /**< Bus clock frequency */
#define I2C_PDD_BUS_CLOCK_DIV64 0U               /**< Bus clock / 64 frequency */


/* ----------------------------------------------------------------------------
   -- SetSlaveAddress7bits
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes to the address register and set address length to 7 bits.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param AddrValue Slave address value[0..127]. This parameter is a 7-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2C0_A1, I2C0_C2,
 *          I2C1_A1, I2C1_C2, I2C2_A1, I2C2_C2, I2C3_A1, I2C3_C2 (depending on the
 *          peripheral).
 * @par Example:
 *      @code
 *      I2C_PDD_SetSlaveAddress7bits(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define I2C_PDD_SetSlaveAddress7bits(PeripheralBase, AddrValue) ( \
    (I2C_A1_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(I2C_A1_REG(PeripheralBase) & (uint8_t)(~(uint8_t)I2C_A1_AD_MASK))) | ( \
      (uint8_t)((uint8_t)(AddrValue) << I2C_A1_AD_SHIFT)))), \
    (I2C_C2_REG(PeripheralBase) &= \
     (uint8_t)(~(uint8_t)I2C_C2_ADEXT_MASK)) \
  )

/* ----------------------------------------------------------------------------
   -- SetSlaveAddress10bits
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes to the address register and set address length to 10 bits.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param AddrValue Slave address value[0..1023]. This parameter is a 10-bit
 *        value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2C0_A1, I2C0_C2,
 *          I2C1_A1, I2C1_C2, I2C2_A1, I2C2_C2, I2C3_A1, I2C3_C2 (depending on the
 *          peripheral).
 * @par Example:
 *      @code
 *      I2C_PDD_SetSlaveAddress10bits(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define I2C_PDD_SetSlaveAddress10bits(PeripheralBase, AddrValue) ( \
    (I2C_A1_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(I2C_A1_REG(PeripheralBase) & (uint8_t)(~(uint8_t)I2C_A1_AD_MASK))) | ( \
      (uint8_t)((uint8_t)((uint16_t)(AddrValue) & 0x7FU) << I2C_A1_AD_SHIFT)))), \
    (I2C_C2_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(I2C_C2_REG(PeripheralBase) & (uint8_t)(~(uint8_t)I2C_C2_AD_MASK))) | (( \
      (uint8_t)((uint16_t)(AddrValue) >> 7U)) | ( \
      I2C_C2_ADEXT_MASK)))) \
  )

/* ----------------------------------------------------------------------------
   -- ReadAddress1Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads address 1 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: I2C0_A1, I2C1_A1,
 *          I2C2_A1, I2C3_A1 (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint8_t result = I2C_PDD_ReadAddress1Reg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define I2C_PDD_ReadAddress1Reg(PeripheralBase) ( \
    I2C_A1_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteAddress1Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes new value specified by the Value parameter into address 1
 * register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the baud rate register. This parameter is
 *        a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2C0_A1, I2C1_A1,
 *          I2C2_A1, I2C3_A1 (depending on the peripheral).
 * @par Example:
 *      @code
 *      I2C_PDD_WriteAddress1Reg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define I2C_PDD_WriteAddress1Reg(PeripheralBase, Value) ( \
    I2C_A1_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- SetFrequencyDivider
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the prescaler to configure the I2C clock for the bit-rate
 * selection.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param FreqDividerValue Frequency divider value[0..63]. This parameter is a
 *        6-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2C0_F, I2C1_F, I2C2_F,
 *          I2C3_F (depending on the peripheral).
 * @par Example:
 *      @code
 *      I2C_PDD_SetFrequencyDivider(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define I2C_PDD_SetFrequencyDivider(PeripheralBase, FreqDividerValue) ( \
    I2C_F_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(I2C_F_REG(PeripheralBase) & (uint8_t)(~(uint8_t)I2C_F_ICR_MASK))) | ( \
      (uint8_t)(FreqDividerValue))) \
  )

/* ----------------------------------------------------------------------------
   -- SetFrequencyMultiplier
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the factor, what is used along with frequency divider to generate
 * the I2C baud rate.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param FreqMultiplierValue Frequency multiplier value[0..2]. This parameter
 *        is a 2-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2C0_F, I2C1_F, I2C2_F,
 *          I2C3_F (depending on the peripheral).
 * @par Example:
 *      @code
 *      I2C_PDD_SetFrequencyMultiplier(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define I2C_PDD_SetFrequencyMultiplier(PeripheralBase, FreqMultiplierValue) ( \
    I2C_F_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(I2C_F_REG(PeripheralBase) & (uint8_t)(~(uint8_t)I2C_F_MULT_MASK))) | ( \
      (uint8_t)((uint8_t)(FreqMultiplierValue) << I2C_F_MULT_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- ReadFrequencyDividerReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads frequency divider register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: I2C0_F, I2C1_F, I2C2_F,
 *          I2C3_F (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint8_t result = I2C_PDD_ReadFrequencyDividerReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define I2C_PDD_ReadFrequencyDividerReg(PeripheralBase) ( \
    I2C_F_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteFrequencyDividerReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes new value specified by the Value parameter into frequency
 * divider register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the frequency divider register. This
 *        parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2C0_F, I2C1_F, I2C2_F,
 *          I2C3_F (depending on the peripheral).
 * @par Example:
 *      @code
 *      I2C_PDD_WriteFrequencyDividerReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define I2C_PDD_WriteFrequencyDividerReg(PeripheralBase, Value) ( \
    I2C_F_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- EnableDevice
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables/disables I2C device.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of device. This parameter is of "Global
 *        enumeration used for specifying general enable/disable states (PDD_DISABLE and
 *        PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2C0_C1, I2C1_C1,
 *          I2C2_C1, I2C3_C1 (depending on the peripheral).
 * @par Example:
 *      @code
 *      I2C_PDD_EnableDevice(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define I2C_PDD_EnableDevice(PeripheralBase, State) ( \
    I2C_C1_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(I2C_C1_REG(PeripheralBase) & (uint8_t)(~(uint8_t)I2C_C1_IICEN_MASK))) | ( \
      (uint8_t)((uint8_t)(State) << I2C_C1_IICEN_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- EnableInterrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables the I2C interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2C0_C1, I2C1_C1,
 *          I2C2_C1, I2C3_C1 (depending on the peripheral).
 * @par Example:
 *      @code
 *      I2C_PDD_EnableInterrupt(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define I2C_PDD_EnableInterrupt(PeripheralBase) ( \
    I2C_C1_REG(PeripheralBase) |= \
     I2C_C1_IICIE_MASK \
  )

/* ----------------------------------------------------------------------------
   -- DisableInterrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Disables the I2C interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2C0_C1, I2C1_C1,
 *          I2C2_C1, I2C3_C1 (depending on the peripheral).
 * @par Example:
 *      @code
 *      I2C_PDD_DisableInterrupt(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define I2C_PDD_DisableInterrupt(PeripheralBase) ( \
    I2C_C1_REG(PeripheralBase) &= \
     (uint8_t)(~(uint8_t)I2C_C1_IICIE_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- SetMasterMode
   ---------------------------------------------------------------------------- */

/**
 * @brief Puts the I2C to the master or slave mode.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param MasterMode I2C mode value. The user should use one from the enumerated
 *        values. This parameter is of "Master mode constants (for MasterMode,
 *        GetMasterMode macros)." type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2C0_C1, I2C1_C1,
 *          I2C2_C1, I2C3_C1 (depending on the peripheral).
 * @par Example:
 *      @code
 *      I2C_PDD_SetMasterMode(<peripheral>_BASE_PTR, I2C_PDD_MASTER_MODE);
 *      @endcode
 */
#define I2C_PDD_SetMasterMode(PeripheralBase, MasterMode) ( \
    I2C_C1_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(I2C_C1_REG(PeripheralBase) & (uint8_t)(~(uint8_t)I2C_C1_MST_MASK))) | ( \
      (uint8_t)(MasterMode))) \
  )

/* ----------------------------------------------------------------------------
   -- GetMasterMode
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the current operating mode.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of "Master mode constants (for MasterMode,
 *         GetMasterMode macros)." type. The value is cast to "uint8_t".
 * @remarks The macro accesses the following registers: I2C0_C1, I2C1_C1,
 *          I2C2_C1, I2C3_C1 (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint8_t result = I2C_PDD_GetMasterMode(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define I2C_PDD_GetMasterMode(PeripheralBase) ( \
    (uint8_t)(I2C_C1_REG(PeripheralBase) & I2C_C1_MST_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- SetTransmitMode
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets data pin to the output or input direction.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param TransmitMode Direction I2C pins. The user should use one from the
 *        enumerated values. This parameter is of "Transmit mode constants (for
 *        SetTransmitMode, GetTransmitMode macros)." type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2C0_C1, I2C1_C1,
 *          I2C2_C1, I2C3_C1 (depending on the peripheral).
 * @par Example:
 *      @code
 *      I2C_PDD_SetTransmitMode(<peripheral>_BASE_PTR, I2C_PDD_TX_DIRECTION);
 *      @endcode
 */
#define I2C_PDD_SetTransmitMode(PeripheralBase, TransmitMode) ( \
    I2C_C1_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(I2C_C1_REG(PeripheralBase) & (uint8_t)(~(uint8_t)I2C_C1_TX_MASK))) | ( \
      (uint8_t)(TransmitMode))) \
  )

/* ----------------------------------------------------------------------------
   -- GetTransmitMode
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the current direction mode.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of "Transmit mode constants (for SetTransmitMode,
 *         GetTransmitMode macros)." type. The value is cast to "uint8_t".
 * @remarks The macro accesses the following registers: I2C0_C1, I2C1_C1,
 *          I2C2_C1, I2C3_C1 (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint8_t result = I2C_PDD_GetTransmitMode(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define I2C_PDD_GetTransmitMode(PeripheralBase) ( \
    (uint8_t)(I2C_C1_REG(PeripheralBase) & I2C_C1_TX_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- EnableTransmitAcknowledge
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables/disables an acknowledge signal to be sent to the bus at the
 * ninth clock bit after receiving one byte of data.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of acknowledge signal. This parameter is of
 *        "Global enumeration used for specifying general enable/disable states
 *        (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2C0_C1, I2C1_C1,
 *          I2C2_C1, I2C3_C1 (depending on the peripheral).
 * @par Example:
 *      @code
 *      I2C_PDD_EnableTransmitAcknowledge(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define I2C_PDD_EnableTransmitAcknowledge(PeripheralBase, State) ( \
    ((State) == PDD_DISABLE) ? ( \
      I2C_C1_REG(PeripheralBase) |= \
       I2C_C1_TXAK_MASK) : ( \
      I2C_C1_REG(PeripheralBase) &= \
       (uint8_t)(~(uint8_t)I2C_C1_TXAK_MASK)) \
  )

/* ----------------------------------------------------------------------------
   -- RepeatStart
   ---------------------------------------------------------------------------- */

/**
 * @brief Generates a repeated START condition.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2C0_C1, I2C1_C1,
 *          I2C2_C1, I2C3_C1 (depending on the peripheral).
 * @par Example:
 *      @code
 *      I2C_PDD_RepeatStart(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define I2C_PDD_RepeatStart(PeripheralBase) ( \
    I2C_C1_REG(PeripheralBase) |= \
     I2C_C1_RSTA_MASK \
  )

/* ----------------------------------------------------------------------------
   -- EnableWakeUp
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables or disables the wakeup function in stop3 mode.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of wakeup function. This parameter is of "Global
 *        enumeration used for specifying general enable/disable states
 *        (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2C0_C1, I2C1_C1,
 *          I2C2_C1, I2C3_C1 (depending on the peripheral).
 * @par Example:
 *      @code
 *      I2C_PDD_EnableWakeUp(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define I2C_PDD_EnableWakeUp(PeripheralBase, State) ( \
    I2C_C1_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(I2C_C1_REG(PeripheralBase) & (uint8_t)(~(uint8_t)I2C_C1_WUEN_MASK))) | ( \
      (uint8_t)((uint8_t)(State) << I2C_C1_WUEN_SHIFT))) \
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
 * @remarks The macro accesses the following registers: I2C0_C1, I2C1_C1,
 *          I2C2_C1, I2C3_C1 (depending on the peripheral).
 * @par Example:
 *      @code
 *      I2C_PDD_EnableDmaRequest(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define I2C_PDD_EnableDmaRequest(PeripheralBase, State) ( \
    I2C_C1_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(I2C_C1_REG(PeripheralBase) & (uint8_t)(~(uint8_t)I2C_C1_DMAEN_MASK))) | ( \
      (uint8_t)(State))) \
  )

/* ----------------------------------------------------------------------------
   -- ReadControl1Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads control 1 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: I2C0_C1, I2C1_C1,
 *          I2C2_C1, I2C3_C1 (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint8_t result = I2C_PDD_ReadControl1Reg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define I2C_PDD_ReadControl1Reg(PeripheralBase) ( \
    I2C_C1_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteControl1Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes new value specified by the Value parameter into control 1
 * register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the control 1 register. This parameter is
 *        a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2C0_C1, I2C1_C1,
 *          I2C2_C1, I2C3_C1 (depending on the peripheral).
 * @par Example:
 *      @code
 *      I2C_PDD_WriteControl1Reg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define I2C_PDD_WriteControl1Reg(PeripheralBase, Value) ( \
    I2C_C1_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadStatusReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the value of the status register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Use constants from group "Status flags constants (for ReadStatusReg,
 *         GetInterruptFlags, ClearInterruptFlags macros)." for processing return
 *         value.
 * @remarks The macro accesses the following registers: I2C0_S, I2C1_S, I2C2_S,
 *          I2C0_S1, I2C1_S1, I2C3_S (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint8_t result = I2C_PDD_ReadStatusReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define I2C_PDD_ReadStatusReg(PeripheralBase) ( \
    I2C_S_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- GetBusStatus
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns status of the BUS.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of "BUS status constants (for GetBusStatus macro)."
 *         type. The value is cast to "uint8_t".
 * @remarks The macro accesses the following registers: I2C0_S, I2C1_S, I2C2_S,
 *          I2C0_S1, I2C1_S1, I2C3_S (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint8_t result = I2C_PDD_GetBusStatus(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define I2C_PDD_GetBusStatus(PeripheralBase) ( \
    (uint8_t)(I2C_S_REG(PeripheralBase) & I2C_S_BUSY_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- GetInterruptFlags
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns a value that represents a mask of active (pending) interrupts.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Use constants from group "Status flags constants (for ReadStatusReg,
 *         GetInterruptFlags, ClearInterruptFlags macros)." for processing return
 *         value.
 * @remarks The macro accesses the following registers: I2C0_S, I2C1_S, I2C2_S,
 *          I2C0_S1, I2C1_S1, I2C3_S (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint8_t result = I2C_PDD_GetInterruptFlags(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define I2C_PDD_GetInterruptFlags(PeripheralBase) ( \
    (uint8_t)(( \
     I2C_S_REG(PeripheralBase)) & ( \
     (uint8_t)(( \
      I2C_S_TCF_MASK) | (( \
      I2C_S_IICIF_MASK) | (( \
      I2C_S_RAM_MASK) | (( \
      I2C_S_ARBL_MASK) | ( \
      I2C_S_IAAS_MASK))))))) \
  )

/* ----------------------------------------------------------------------------
   -- ClearInterruptFlags
   ---------------------------------------------------------------------------- */

/**
 * @brief Clears interrupt flags of interrupts specified by Mask.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mask Mask of interrupt clear requests. Use constants from group
 *        "Status flags constants (for ReadStatusReg, GetInterruptFlags,
 *        ClearInterruptFlags macros).". This parameter is 8 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2C0_S, I2C1_S, I2C2_S,
 *          I2C0_S1, I2C1_S1, I2C3_S (depending on the peripheral).
 * @par Example:
 *      @code
 *      I2C_PDD_ClearInterruptFlags(<peripheral>_BASE_PTR,
 *      I2C_PDD_RX_ACKNOWLEDGE);
 *      @endcode
 */
#define I2C_PDD_ClearInterruptFlags(PeripheralBase, Mask) ( \
    I2C_S_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(( \
       I2C_S_REG(PeripheralBase)) & ( \
       (uint8_t)(~(uint8_t)(I2C_S_IICIF_MASK | I2C_S_ARBL_MASK))))) | ( \
      (uint8_t)(Mask))) \
  )

/* ----------------------------------------------------------------------------
   -- WriteStatusReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes new value specified by the Value parameter into status register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the status register. This parameter is a
 *        8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2C0_S, I2C1_S, I2C2_S,
 *          I2C0_S1, I2C1_S1, I2C3_S (depending on the peripheral).
 * @par Example:
 *      @code
 *      I2C_PDD_WriteStatusReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define I2C_PDD_WriteStatusReg(PeripheralBase, Value) ( \
    I2C_S_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadDataReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the data register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: I2C0_D, I2C1_D, I2C2_D,
 *          I2C3_D (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint8_t result = I2C_PDD_ReadDataReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define I2C_PDD_ReadDataReg(PeripheralBase) ( \
    I2C_D_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteDataReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes data to the data register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Data Data value. This parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2C0_D, I2C1_D, I2C2_D,
 *          I2C3_D (depending on the peripheral).
 * @par Example:
 *      @code
 *      I2C_PDD_WriteDataReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define I2C_PDD_WriteDataReg(PeripheralBase, Data) ( \
    I2C_D_REG(PeripheralBase) = \
     (uint8_t)(Data) \
  )

/* ----------------------------------------------------------------------------
   -- EnableGeneralCallAddress
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables or disables general call address.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of general call address function. This parameter
 *        is of "Global enumeration used for specifying general enable/disable
 *        states (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2C0_C2, I2C1_C2,
 *          I2C2_C2, I2C3_C2 (depending on the peripheral).
 * @par Example:
 *      @code
 *      I2C_PDD_EnableGeneralCallAddress(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define I2C_PDD_EnableGeneralCallAddress(PeripheralBase, State) ( \
    I2C_C2_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(I2C_C2_REG(PeripheralBase) & (uint8_t)(~(uint8_t)I2C_C2_GCAEN_MASK))) | ( \
      (uint8_t)((uint8_t)(State) << I2C_C2_GCAEN_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- EnableAddressExtension
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables or disables extension address.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of extension address. This parameter is of
 *        "Global enumeration used for specifying general enable/disable states
 *        (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2C0_C2, I2C1_C2,
 *          I2C2_C2, I2C3_C2 (depending on the peripheral).
 * @par Example:
 *      @code
 *      I2C_PDD_EnableAddressExtension(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define I2C_PDD_EnableAddressExtension(PeripheralBase, State) ( \
    I2C_C2_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(I2C_C2_REG(PeripheralBase) & (uint8_t)(~(uint8_t)I2C_C2_ADEXT_MASK))) | ( \
      (uint8_t)((uint8_t)(State) << I2C_C2_ADEXT_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SetPadsNormalDriveMode
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets control the drive capability of the I2C pads to normal drive mode.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2C0_C2, I2C1_C2,
 *          I2C2_C2, I2C3_C2 (depending on the peripheral).
 * @par Example:
 *      @code
 *      I2C_PDD_SetPadsNormalDriveMode(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define I2C_PDD_SetPadsNormalDriveMode(PeripheralBase) ( \
    I2C_C2_REG(PeripheralBase) &= \
     (uint8_t)(~(uint8_t)I2C_C2_HDRS_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- SetPadsHighDriveMode
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets control the drive capability of the I2C pads to high drive mode.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2C0_C2, I2C1_C2,
 *          I2C2_C2, I2C3_C2 (depending on the peripheral).
 * @par Example:
 *      @code
 *      I2C_PDD_SetPadsHighDriveMode(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define I2C_PDD_SetPadsHighDriveMode(PeripheralBase) ( \
    I2C_C2_REG(PeripheralBase) |= \
     I2C_C2_HDRS_MASK \
  )

/* ----------------------------------------------------------------------------
   -- EnableSlaveBaudControlByMaster
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables or disables slave baud rate control by master device.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of slave baud rate control. This parameter is of
 *        "Global enumeration used for specifying general enable/disable states
 *        (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2C0_C2, I2C1_C2,
 *          I2C2_C2, I2C3_C2 (depending on the peripheral).
 * @par Example:
 *      @code
 *      I2C_PDD_EnableSlaveBaudControlByMaster(<peripheral>_BASE_PTR,
 *      PDD_DISABLE);
 *      @endcode
 */
#define I2C_PDD_EnableSlaveBaudControlByMaster(PeripheralBase, State) ( \
    ((State) == PDD_DISABLE) ? ( \
      I2C_C2_REG(PeripheralBase) |= \
       I2C_C2_SBRC_MASK) : ( \
      I2C_C2_REG(PeripheralBase) &= \
       (uint8_t)(~(uint8_t)I2C_C2_SBRC_MASK)) \
  )

/* ----------------------------------------------------------------------------
   -- EnableRangeAddressMatch
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables or disables range address matching.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of range address matching function. This
 *        parameter is of "Global enumeration used for specifying general enable/disable
 *        states (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2C0_C2, I2C1_C2,
 *          I2C2_C2, I2C3_C2 (depending on the peripheral).
 * @par Example:
 *      @code
 *      I2C_PDD_EnableRangeAddressMatch(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define I2C_PDD_EnableRangeAddressMatch(PeripheralBase, State) ( \
    I2C_C2_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(I2C_C2_REG(PeripheralBase) & (uint8_t)(~(uint8_t)I2C_C2_RMEN_MASK))) | ( \
      (uint8_t)((uint8_t)(State) << I2C_C2_RMEN_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- ReadControl2Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads control 2 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: I2C0_C2, I2C1_C2,
 *          I2C2_C2, I2C3_C2 (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint8_t result = I2C_PDD_ReadControl2Reg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define I2C_PDD_ReadControl2Reg(PeripheralBase) ( \
    I2C_C2_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteControl2Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes new value specified by the Value parameter into control 2
 * register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the control 2 register. This parameter is
 *        a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2C0_C2, I2C1_C2,
 *          I2C2_C2, I2C3_C2 (depending on the peripheral).
 * @par Example:
 *      @code
 *      I2C_PDD_WriteControl2Reg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define I2C_PDD_WriteControl2Reg(PeripheralBase, Value) ( \
    I2C_C2_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- SetInputGlitchFilter
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MKL02Z4)) || (defined(MCU_MKL03Z4)) || (defined(MCU_MKL04Z4)) || (defined(MCU_MKL05Z4)) || (defined(MCU_MKL14Z4)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL16Z4)) || (defined(MCU_MKL24Z4)) || (defined(MCU_MKL25Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL34Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKW01Z4)))
/**
 * @brief Sets the programming controls for the width of glitch (in terms of bus
 * clock cycles) the filter must absorb.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param FilterFactorValue Input glitch filter value[0..31]. This parameter is
 *        a 5-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2C0_FLT, I2C1_FLT,
 *          I2C2_FLT, I2C3_FLT (depending on the peripheral).
 * @par Example:
 *      @code
 *      I2C_PDD_SetInputGlitchFilter(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
  #define I2C_PDD_SetInputGlitchFilter(PeripheralBase, FilterFactorValue) ( \
      I2C_FLT_REG(PeripheralBase) = \
       (uint8_t)(( \
        (uint8_t)(( \
         I2C_FLT_REG(PeripheralBase)) & (( \
         (uint8_t)(~(uint8_t)I2C_FLT_FLT_MASK)) & ( \
         (uint8_t)(~(uint8_t)I2C_FLT_STOPF_MASK))))) | ( \
        (uint8_t)(FilterFactorValue))) \
    )
#elif ((defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK65F18)) || (defined(MCU_MK65F18WS)) || (defined(MCU_MK66F18)) || (defined(MCU_MKE02Z2)) || (defined(MCU_MKE02Z4)) || (defined(MCU_MKE04Z1284)) || (defined(MCU_MKE04Z4)) || (defined(MCU_MKE06Z4)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_SKEAZ1284)) || (defined(MCU_SKEAZN642)) || (defined(MCU_SKEAZN84)))
/**
 * @brief Sets the programming controls for the width of glitch (in terms of bus
 * clock cycles) the filter must absorb.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param FilterFactorValue Input glitch filter value[0..15]. This parameter is
 *        a 4-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2C0_FLT, I2C1_FLT,
 *          I2C2_FLT, I2C3_FLT (depending on the peripheral).
 * @par Example:
 *      @code
 *      I2C_PDD_SetInputGlitchFilter(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
  #define I2C_PDD_SetInputGlitchFilter(PeripheralBase, FilterFactorValue) ( \
      I2C_FLT_REG(PeripheralBase) = \
       (uint8_t)(( \
        (uint8_t)(( \
         I2C_FLT_REG(PeripheralBase)) & (( \
         (uint8_t)(~(uint8_t)I2C_FLT_FLT_MASK)) & (( \
         (uint8_t)(~(uint8_t)I2C_FLT_STARTF_MASK)) & ( \
         (uint8_t)(~(uint8_t)I2C_FLT_STOPF_MASK)))))) | ( \
        (uint8_t)(FilterFactorValue))) \
    )
#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) || (defined(MCU_PCK20L4)) */
/**
 * @brief Sets the programming controls for the width of glitch (in terms of bus
 * clock cycles) the filter must absorb.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param FilterFactorValue Input glitch filter value[0..31]. This parameter is
 *        a 5-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2C0_FLT, I2C1_FLT,
 *          I2C2_FLT, I2C3_FLT (depending on the peripheral).
 * @par Example:
 *      @code
 *      I2C_PDD_SetInputGlitchFilter(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
  #define I2C_PDD_SetInputGlitchFilter(PeripheralBase, FilterFactorValue) ( \
      I2C_FLT_REG(PeripheralBase) = \
       (uint8_t)(( \
        (uint8_t)(I2C_FLT_REG(PeripheralBase) & (uint8_t)(~(uint8_t)I2C_FLT_FLT_MASK))) | ( \
        (uint8_t)(FilterFactorValue))) \
    )
#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) || (defined(MCU_PCK20L4)) */

/* ----------------------------------------------------------------------------
   -- ReadInputGlitchFilterReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads input glitch filter register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: I2C0_FLT, I2C1_FLT,
 *          I2C2_FLT, I2C3_FLT (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint8_t result =
 *      I2C_PDD_ReadInputGlitchFilterReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define I2C_PDD_ReadInputGlitchFilterReg(PeripheralBase) ( \
    I2C_FLT_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteInputGlitchFilterReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes new value specified by the Value parameter into input glitch
 * filter register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the input glitch filter register. This
 *        parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2C0_FLT, I2C1_FLT,
 *          I2C2_FLT, I2C3_FLT (depending on the peripheral).
 * @par Example:
 *      @code
 *      I2C_PDD_WriteInputGlitchFilterReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define I2C_PDD_WriteInputGlitchFilterReg(PeripheralBase, Value) ( \
    I2C_FLT_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- SetRangeAddress
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the range slave address.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param RangeAddressValue Range Address value[0..127]. This parameter is a
 *        7-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2C0_RA, I2C1_RA,
 *          I2C2_RA, I2C3_RA (depending on the peripheral).
 * @par Example:
 *      @code
 *      I2C_PDD_SetRangeAddress(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define I2C_PDD_SetRangeAddress(PeripheralBase, RangeAddressValue) ( \
    I2C_RA_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(I2C_RA_REG(PeripheralBase) & (uint8_t)(~(uint8_t)I2C_RA_RAD_MASK))) | ( \
      (uint8_t)((uint8_t)(RangeAddressValue) << I2C_RA_RAD_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- ReadRangeAddressReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads value of range address register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: I2C0_RA, I2C1_RA,
 *          I2C2_RA, I2C3_RA (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint8_t result = I2C_PDD_ReadRangeAddressReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define I2C_PDD_ReadRangeAddressReg(PeripheralBase) ( \
    I2C_RA_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteRangeAddressReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes new value specified by the Value parameter into range address
 * register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the range address register. This
 *        parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2C0_RA, I2C1_RA,
 *          I2C2_RA, I2C3_RA (depending on the peripheral).
 * @par Example:
 *      @code
 *      I2C_PDD_WriteRangeAddressReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define I2C_PDD_WriteRangeAddressReg(PeripheralBase, Value) ( \
    I2C_RA_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- EnableFastSmBusNackAck
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables or disables fast SMBus NACK/ACK.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Parameter specifying if SMBus alert response will be enabled or
 *        disabled. This parameter is of "Global enumeration used for specifying
 *        general enable/disable states (PDD_DISABLE and PDD_ENABLE defined in
 *        PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2C0_SMB, I2C1_SMB,
 *          I2C2_SMB, I2C3_SMB (depending on the peripheral).
 * @par Example:
 *      @code
 *      I2C_PDD_EnableFastSmBusNackAck(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define I2C_PDD_EnableFastSmBusNackAck(PeripheralBase, State) ( \
    I2C_SMB_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(( \
       I2C_SMB_REG(PeripheralBase)) & (( \
       (uint8_t)(~(uint8_t)I2C_SMB_FACK_MASK)) & (( \
       (uint8_t)(~(uint8_t)I2C_SMB_SHTF2_MASK)) & ( \
       (uint8_t)(~(uint8_t)I2C_SMB_SLTF_MASK)))))) | ( \
      (uint8_t)((uint8_t)(State) << I2C_SMB_FACK_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- GetFastSmBusAcknowledge
   ---------------------------------------------------------------------------- */

/**
 * @brief Fast NACK/ACK enable bit.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of "Fast SMBus Acknowledge constants (for
 *         GetFastSmBusAcknowledge macro)." type. The value is cast to "uint8_t".
 * @remarks The macro accesses the following registers: I2C0_SMB, I2C1_SMB,
 *          I2C2_SMB, I2C3_SMB (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint8_t result = I2C_PDD_GetFastSmBusAcknowledge(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define I2C_PDD_GetFastSmBusAcknowledge(PeripheralBase) ( \
    (uint8_t)(I2C_SMB_REG(PeripheralBase) & I2C_SMB_FACK_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- EnableSmBusAlertResponseAddress
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables or disables SMBus alert response address.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Parameter specifying if SMBus alert response will be enabled or
 *        disabled. This parameter is of "Global enumeration used for specifying
 *        general enable/disable states (PDD_DISABLE and PDD_ENABLE defined in
 *        PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2C0_SMB, I2C1_SMB,
 *          I2C2_SMB, I2C3_SMB (depending on the peripheral).
 * @par Example:
 *      @code
 *      I2C_PDD_EnableSmBusAlertResponseAddress(<peripheral>_BASE_PTR,
 *      PDD_DISABLE);
 *      @endcode
 */
#define I2C_PDD_EnableSmBusAlertResponseAddress(PeripheralBase, State) ( \
    I2C_SMB_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(( \
       I2C_SMB_REG(PeripheralBase)) & (( \
       (uint8_t)(~(uint8_t)I2C_SMB_ALERTEN_MASK)) & (( \
       (uint8_t)(~(uint8_t)I2C_SMB_SHTF2_MASK)) & ( \
       (uint8_t)(~(uint8_t)I2C_SMB_SLTF_MASK)))))) | ( \
      (uint8_t)((uint8_t)(State) << I2C_SMB_ALERTEN_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- EnableSecondI2CAddress
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables or disables SMBus device default address.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Parameter specifying if SMBus device default address will be
 *        enabled or disabled. This parameter is of "Global enumeration used for
 *        specifying general enable/disable states (PDD_DISABLE and PDD_ENABLE
 *        defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2C0_SMB, I2C1_SMB,
 *          I2C2_SMB, I2C3_SMB (depending on the peripheral).
 * @par Example:
 *      @code
 *      I2C_PDD_EnableSecondI2CAddress(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define I2C_PDD_EnableSecondI2CAddress(PeripheralBase, State) ( \
    I2C_SMB_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(( \
       I2C_SMB_REG(PeripheralBase)) & (( \
       (uint8_t)(~(uint8_t)I2C_SMB_SIICAEN_MASK)) & (( \
       (uint8_t)(~(uint8_t)I2C_SMB_SHTF2_MASK)) & ( \
       (uint8_t)(~(uint8_t)I2C_SMB_SLTF_MASK)))))) | ( \
      (uint8_t)((uint8_t)(State) << I2C_SMB_SIICAEN_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SetSCLTimeoutBusClockSource
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets clock source of the timeout counter to Bus clock or Bus clock/64
 * frequency.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param ClockSource SCL timeout BUS clock source value. The user should use
 *        one from the enumerated values. This parameter is of "Clock source
 *        constants (for SetSCLTimeoutBusClockSource macro)." type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2C0_SMB, I2C1_SMB,
 *          I2C2_SMB, I2C3_SMB (depending on the peripheral).
 * @par Example:
 *      @code
 *      I2C_PDD_SetSCLTimeoutBusClockSource(<peripheral>_BASE_PTR,
 *      I2C_PDD_BUS_CLOCK);
 *      @endcode
 */
#define I2C_PDD_SetSCLTimeoutBusClockSource(PeripheralBase, ClockSource) ( \
    I2C_SMB_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(( \
       I2C_SMB_REG(PeripheralBase)) & (( \
       (uint8_t)(~(uint8_t)I2C_SMB_TCKSEL_MASK)) & (( \
       (uint8_t)(~(uint8_t)I2C_SMB_SHTF2_MASK)) & ( \
       (uint8_t)(~(uint8_t)I2C_SMB_SLTF_MASK)))))) | ( \
      (uint8_t)(ClockSource))) \
  )

/* ----------------------------------------------------------------------------
   -- GetSCLTimeoutInterruptFlags
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns a value that represents a mask of active (pending) interrupts.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Use constants from group "SCL timeout flags constants (for
 *         GetSCLTimeoutInterruptFlags, ClearSCLTimeoutInterruptFlags macros)." for
 *         processing return value.
 * @remarks The macro accesses the following registers: I2C0_SMB, I2C1_SMB,
 *          I2C2_SMB, I2C3_SMB (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint8_t result =
 *      I2C_PDD_GetSCLTimeoutInterruptFlags(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define I2C_PDD_GetSCLTimeoutInterruptFlags(PeripheralBase) ( \
    (uint8_t)(( \
     I2C_SMB_REG(PeripheralBase)) & ( \
     (uint8_t)(I2C_SMB_SLTF_MASK | (I2C_SMB_SHTF1_MASK | I2C_SMB_SHTF2_MASK)))) \
  )

/* ----------------------------------------------------------------------------
   -- ClearSCLTimeoutInterruptFlags
   ---------------------------------------------------------------------------- */

/**
 * @brief Clears interrupt flags of interrupts specified by Mask.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mask Mask of interrupt clear requests. Use constants from group "SCL
 *        timeout flags constants (for GetSCLTimeoutInterruptFlags,
 *        ClearSCLTimeoutInterruptFlags macros).". This parameter is 8 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2C0_SMB, I2C1_SMB,
 *          I2C2_SMB, I2C3_SMB (depending on the peripheral).
 * @par Example:
 *      @code
 *      I2C_PDD_ClearSCLTimeoutInterruptFlags(<peripheral>_BASE_PTR,
 *      I2C_PDD_SCL_LOW_TIMEOUT);
 *      @endcode
 */
#define I2C_PDD_ClearSCLTimeoutInterruptFlags(PeripheralBase, Mask) ( \
    I2C_SMB_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(( \
       I2C_SMB_REG(PeripheralBase)) & ( \
       (uint8_t)(~(uint8_t)(I2C_SMB_SLTF_MASK | I2C_SMB_SHTF2_MASK))))) | ( \
      (uint8_t)(Mask))) \
  )

/* ----------------------------------------------------------------------------
   -- EnableSCLTimeoutInterrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables SCL high and SDA low timeout interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2C0_SMB, I2C1_SMB,
 *          I2C2_SMB, I2C3_SMB (depending on the peripheral).
 * @par Example:
 *      @code
 *      I2C_PDD_EnableSCLTimeoutInterrupt(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define I2C_PDD_EnableSCLTimeoutInterrupt(PeripheralBase) ( \
    I2C_SMB_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(I2C_SMB_REG(PeripheralBase) | I2C_SMB_SHTF2IE_MASK)) & (( \
      (uint8_t)(~(uint8_t)I2C_SMB_SHTF2_MASK)) & ( \
      (uint8_t)(~(uint8_t)I2C_SMB_SLTF_MASK)))) \
  )

/* ----------------------------------------------------------------------------
   -- DisableSCLTimeoutInterrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Disables SCL high and SDA low timeout interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2C0_SMB, I2C1_SMB,
 *          I2C2_SMB, I2C3_SMB (depending on the peripheral).
 * @par Example:
 *      @code
 *      I2C_PDD_DisableSCLTimeoutInterrupt(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define I2C_PDD_DisableSCLTimeoutInterrupt(PeripheralBase) ( \
    I2C_SMB_REG(PeripheralBase) &= \
     (uint8_t)(( \
      (uint8_t)(~(uint8_t)I2C_SMB_SHTF2IE_MASK)) & (( \
      (uint8_t)(~(uint8_t)I2C_SMB_SHTF2_MASK)) & ( \
      (uint8_t)(~(uint8_t)I2C_SMB_SLTF_MASK)))) \
  )

/* ----------------------------------------------------------------------------
   -- ReadSMBusControlAndStatusReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads SMBus control and status register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: I2C0_SMB, I2C1_SMB,
 *          I2C2_SMB, I2C3_SMB (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint8_t result =
 *      I2C_PDD_ReadSMBusControlAndStatusReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define I2C_PDD_ReadSMBusControlAndStatusReg(PeripheralBase) ( \
    I2C_SMB_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteSMBusControlAndStatusReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes new value specified by the Value parameter into SMBus control
 * and status register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the SMBus control and status register.
 *        This parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2C0_SMB, I2C1_SMB,
 *          I2C2_SMB, I2C3_SMB (depending on the peripheral).
 * @par Example:
 *      @code
 *      I2C_PDD_WriteSMBusControlAndStatusReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define I2C_PDD_WriteSMBusControlAndStatusReg(PeripheralBase, Value) ( \
    I2C_SMB_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- SetSMBusSlaveAddress
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets SMBus address to the address register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param SMBusSlaveAddrValue SMBus slave address value[0..127]. This parameter
 *        is a 7-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2C0_A2, I2C1_A2,
 *          I2C2_A2, I2C3_A2 (depending on the peripheral).
 * @par Example:
 *      @code
 *      I2C_PDD_SetSMBusSlaveAddress(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define I2C_PDD_SetSMBusSlaveAddress(PeripheralBase, SMBusSlaveAddrValue) ( \
    I2C_A2_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(I2C_A2_REG(PeripheralBase) & (uint8_t)(~(uint8_t)I2C_A2_SAD_MASK))) | ( \
      (uint8_t)((uint8_t)(SMBusSlaveAddrValue) << I2C_A2_SAD_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- ReadAddress2Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads address 2 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: I2C0_A2, I2C1_A2,
 *          I2C2_A2, I2C3_A2 (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint8_t result = I2C_PDD_ReadAddress2Reg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define I2C_PDD_ReadAddress2Reg(PeripheralBase) ( \
    I2C_A2_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteAddress2Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes new value specified by the Value parameter into address 2
 * register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the address 2 register. This parameter is
 *        a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2C0_A2, I2C1_A2,
 *          I2C2_A2, I2C3_A2 (depending on the peripheral).
 * @par Example:
 *      @code
 *      I2C_PDD_WriteAddress2Reg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define I2C_PDD_WriteAddress2Reg(PeripheralBase, Value) ( \
    I2C_A2_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- SetSCLLowTimeout
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets SCL low timeout value that determines the timeout period of SCL
 * low.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param SCLLowTimeoutValue SCL low timeout value[0..65535]. This parameter is
 *        a 16-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2C0_SLTL, I2C0_SLTH,
 *          I2C1_SLTL, I2C1_SLTH, I2C2_SLTL, I2C2_SLTH, I2C3_SLTL, I2C3_SLTH
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      I2C_PDD_SetSCLLowTimeout(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define I2C_PDD_SetSCLLowTimeout(PeripheralBase, SCLLowTimeoutValue) ( \
    (I2C_SLTL_REG(PeripheralBase) = \
     (uint8_t)(SCLLowTimeoutValue)), \
    (I2C_SLTH_REG(PeripheralBase) = \
     (uint8_t)((uint16_t)(SCLLowTimeoutValue) >> 8U)) \
  )

/* ----------------------------------------------------------------------------
   -- ReadSclLowTimeoutHighReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads SCL low timeout high register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: I2C0_SLTH, I2C1_SLTH,
 *          I2C2_SLTH, I2C3_SLTH (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint8_t result =
 *      I2C_PDD_ReadSclLowTimeoutHighReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define I2C_PDD_ReadSclLowTimeoutHighReg(PeripheralBase) ( \
    I2C_SLTH_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteSclLowTimeoutHighReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes new value specified by the Value parameter into SCL low timeout
 * high register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the SCL low timeout high register. This
 *        parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2C0_SLTH, I2C1_SLTH,
 *          I2C2_SLTH, I2C3_SLTH (depending on the peripheral).
 * @par Example:
 *      @code
 *      I2C_PDD_WriteSclLowTimeoutHighReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define I2C_PDD_WriteSclLowTimeoutHighReg(PeripheralBase, Value) ( \
    I2C_SLTH_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadSclLowTimeoutLowReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads SCL low timeout high register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: I2C0_SLTL, I2C1_SLTL,
 *          I2C2_SLTL, I2C3_SLTL (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint8_t result = I2C_PDD_ReadSclLowTimeoutLowReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define I2C_PDD_ReadSclLowTimeoutLowReg(PeripheralBase) ( \
    I2C_SLTL_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteSclLowTimeoutLowReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes new value specified by the Value parameter into SCL low timeout
 * low register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the SCL low timeout low register. This
 *        parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2C0_SLTL, I2C1_SLTL,
 *          I2C2_SLTL, I2C3_SLTL (depending on the peripheral).
 * @par Example:
 *      @code
 *      I2C_PDD_WriteSclLowTimeoutLowReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define I2C_PDD_WriteSclLowTimeoutLowReg(PeripheralBase, Value) ( \
    I2C_SLTL_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- EnableStopHoldOffMode
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MKL02Z4)) || (defined(MCU_MKL03Z4)) || (defined(MCU_MKL04Z4)) || (defined(MCU_MKL05Z4)) || (defined(MCU_MKL14Z4)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL16Z4)) || (defined(MCU_MKL24Z4)) || (defined(MCU_MKL25Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL34Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKW01Z4)))
/**
 * @brief Enables/disables stop mode holdoff.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of stop mode holdoff. This parameter is of
 *        "Global enumeration used for specifying general enable/disable states
 *        (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2C0_FLT, I2C1_FLT,
 *          I2C2_FLT, I2C3_FLT (depending on the peripheral).
 * @par Example:
 *      @code
 *      I2C_PDD_EnableStopHoldOffMode(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
  #define I2C_PDD_EnableStopHoldOffMode(PeripheralBase, State) ( \
      I2C_FLT_REG(PeripheralBase) = \
       (uint8_t)(( \
        (uint8_t)(( \
         I2C_FLT_REG(PeripheralBase)) & (( \
         (uint8_t)(~(uint8_t)I2C_FLT_SHEN_MASK)) & ( \
         (uint8_t)(~(uint8_t)I2C_FLT_STOPF_MASK))))) | ( \
        (uint8_t)((uint8_t)(State) << I2C_FLT_SHEN_SHIFT))) \
    )
#else /* (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK65F18)) || (defined(MCU_MK65F18WS)) || (defined(MCU_MK66F18)) || (defined(MCU_MKE02Z2)) || (defined(MCU_MKE02Z4)) || (defined(MCU_MKE04Z1284)) || (defined(MCU_MKE04Z4)) || (defined(MCU_MKE06Z4)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_SKEAZ1284)) || (defined(MCU_SKEAZN642)) || (defined(MCU_SKEAZN84)) */
/**
 * @brief Enables/disables stop mode holdoff.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of stop mode holdoff. This parameter is of
 *        "Global enumeration used for specifying general enable/disable states
 *        (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2C0_FLT, I2C1_FLT,
 *          I2C2_FLT, I2C3_FLT (depending on the peripheral).
 * @par Example:
 *      @code
 *      I2C_PDD_EnableStopHoldOffMode(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
  #define I2C_PDD_EnableStopHoldOffMode(PeripheralBase, State) ( \
      I2C_FLT_REG(PeripheralBase) = \
       (uint8_t)(( \
        (uint8_t)(( \
         I2C_FLT_REG(PeripheralBase)) & (( \
         (uint8_t)(~(uint8_t)I2C_FLT_SHEN_MASK)) & (( \
         (uint8_t)(~(uint8_t)I2C_FLT_STARTF_MASK)) & ( \
         (uint8_t)(~(uint8_t)I2C_FLT_STOPF_MASK)))))) | ( \
        (uint8_t)((uint8_t)(State) << I2C_FLT_SHEN_SHIFT))) \
    )
#endif /* (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK65F18)) || (defined(MCU_MK65F18WS)) || (defined(MCU_MK66F18)) || (defined(MCU_MKE02Z2)) || (defined(MCU_MKE02Z4)) || (defined(MCU_MKE04Z1284)) || (defined(MCU_MKE04Z4)) || (defined(MCU_MKE06Z4)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_SKEAZ1284)) || (defined(MCU_SKEAZN642)) || (defined(MCU_SKEAZN84)) */

/* ----------------------------------------------------------------------------
   -- ReadBusStatusFlags
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the value of the bus status flags.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Use constants from group "Status flags constants." for processing
 *         return value.
 * @remarks The macro accesses the following registers: I2C0_FLT, I2C1_FLT,
 *          I2C2_FLT, I2C3_FLT (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint8_t result = I2C_PDD_ReadBusStatusFlags(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define I2C_PDD_ReadBusStatusFlags(PeripheralBase) ( \
    I2C_FLT_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- ClearBusStatusInterruptFlags
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MKL02Z4)) || (defined(MCU_MKL03Z4)) || (defined(MCU_MKL04Z4)) || (defined(MCU_MKL05Z4)) || (defined(MCU_MKL14Z4)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL16Z4)) || (defined(MCU_MKL24Z4)) || (defined(MCU_MKL25Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL34Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKW01Z4)))
/**
 * @brief Clears bus status interrupt flags of interrupts specified by Mask.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mask Mask of interrupt clear requests. Use constants from group
 *        "Status flags constants.". This parameter is 8 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2C0_FLT, I2C1_FLT,
 *          I2C2_FLT, I2C3_FLT (depending on the peripheral).
 * @par Example:
 *      @code
 *      I2C_PDD_ClearBusStatusInterruptFlags(<peripheral>_BASE_PTR,
 *      I2C_PDD_BUS_STOP_FLAG);
 *      @endcode
 */
  #define I2C_PDD_ClearBusStatusInterruptFlags(PeripheralBase, Mask) ( \
      I2C_FLT_REG(PeripheralBase) = \
       (uint8_t)(( \
        (uint8_t)(I2C_FLT_REG(PeripheralBase) & (uint8_t)(~(uint8_t)I2C_FLT_STOPF_MASK))) | ( \
        (uint8_t)(Mask))) \
    )
#else /* (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK65F18)) || (defined(MCU_MK65F18WS)) || (defined(MCU_MK66F18)) || (defined(MCU_MKE02Z2)) || (defined(MCU_MKE02Z4)) || (defined(MCU_MKE04Z1284)) || (defined(MCU_MKE04Z4)) || (defined(MCU_MKE06Z4)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_SKEAZ1284)) || (defined(MCU_SKEAZN642)) || (defined(MCU_SKEAZN84)) */
/**
 * @brief Clears bus status interrupt flags of interrupts specified by Mask.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mask Mask of interrupt clear requests. Use constants from group
 *        "Status flags constants.". This parameter is 8 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2C0_FLT, I2C1_FLT,
 *          I2C2_FLT, I2C3_FLT (depending on the peripheral).
 * @par Example:
 *      @code
 *      I2C_PDD_ClearBusStatusInterruptFlags(<peripheral>_BASE_PTR,
 *      I2C_PDD_BUS_STOP_FLAG);
 *      @endcode
 */
  #define I2C_PDD_ClearBusStatusInterruptFlags(PeripheralBase, Mask) ( \
      I2C_FLT_REG(PeripheralBase) = \
       (uint8_t)(( \
        (uint8_t)(( \
         I2C_FLT_REG(PeripheralBase)) & ( \
         (uint8_t)(~(uint8_t)(I2C_FLT_STOPF_MASK | I2C_FLT_STARTF_MASK))))) | ( \
        (uint8_t)(Mask))) \
    )
#endif /* (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK65F18)) || (defined(MCU_MK65F18WS)) || (defined(MCU_MK66F18)) || (defined(MCU_MKE02Z2)) || (defined(MCU_MKE02Z4)) || (defined(MCU_MKE04Z1284)) || (defined(MCU_MKE04Z4)) || (defined(MCU_MKE06Z4)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_SKEAZ1284)) || (defined(MCU_SKEAZN642)) || (defined(MCU_SKEAZN84)) */

/* ----------------------------------------------------------------------------
   -- EnableBusStopOrStartInterrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables the bus stop or start interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2C0_FLT, I2C1_FLT,
 *          I2C2_FLT, I2C3_FLT (depending on the peripheral).
 * @par Example:
 *      @code
 *      I2C_PDD_EnableBusStopOrStartInterrupt(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define I2C_PDD_EnableBusStopOrStartInterrupt(PeripheralBase) ( \
    I2C_FLT_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(I2C_FLT_REG(PeripheralBase) | I2C_FLT_SSIE_MASK)) & (( \
      (uint8_t)(~(uint8_t)I2C_FLT_STARTF_MASK)) & ( \
      (uint8_t)(~(uint8_t)I2C_FLT_STOPF_MASK)))) \
  )

/* ----------------------------------------------------------------------------
   -- DisableBusStopOrStartInterrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Disables the bus stop or start interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2C0_FLT, I2C1_FLT,
 *          I2C2_FLT, I2C3_FLT (depending on the peripheral).
 * @par Example:
 *      @code
 *      I2C_PDD_DisableBusStopOrStartInterrupt(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define I2C_PDD_DisableBusStopOrStartInterrupt(PeripheralBase) ( \
    I2C_FLT_REG(PeripheralBase) &= \
     (uint8_t)(( \
      (uint8_t)(~(uint8_t)I2C_FLT_SSIE_MASK)) & (( \
      (uint8_t)(~(uint8_t)I2C_FLT_STARTF_MASK)) & ( \
      (uint8_t)(~(uint8_t)I2C_FLT_STOPF_MASK)))) \
  )

/* ----------------------------------------------------------------------------
   -- EnableBusStopInterrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables the bus stop interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2C0_FLT, I2C1_FLT
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      I2C_PDD_EnableBusStopInterrupt(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define I2C_PDD_EnableBusStopInterrupt(PeripheralBase) ( \
    I2C_FLT_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(I2C_FLT_REG(PeripheralBase) | I2C_FLT_STOPIE_MASK)) & ( \
      (uint8_t)(~(uint8_t)I2C_FLT_STOPF_MASK))) \
  )

/* ----------------------------------------------------------------------------
   -- DisableBusStopInterrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Disables the bus stop interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2C0_FLT, I2C1_FLT
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      I2C_PDD_DisableBusStopInterrupt(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define I2C_PDD_DisableBusStopInterrupt(PeripheralBase) ( \
    I2C_FLT_REG(PeripheralBase) &= \
     (uint8_t)(( \
      (uint8_t)(~(uint8_t)I2C_FLT_STOPIE_MASK)) & ( \
      (uint8_t)(~(uint8_t)I2C_FLT_STOPF_MASK))) \
  )
#endif  /* #if defined(I2C_PDD_H_) */

/* I2C_PDD.h, eof. */
