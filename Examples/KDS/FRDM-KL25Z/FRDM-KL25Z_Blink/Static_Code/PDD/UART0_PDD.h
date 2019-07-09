/*
  PDD layer implementation for peripheral type UART0
  (C) 2013 Freescale, Inc. All rights reserved.

  This file is static and it is generated from API-Factory
*/

#if !defined(UART0_PDD_H_)
#define UART0_PDD_H_

/* ----------------------------------------------------------------------------
   -- Test if supported MCU is active
   ---------------------------------------------------------------------------- */

#if !defined(MCU_ACTIVE)
  // No MCU is active
  #error UART0 PDD library: No derivative is active. Place proper #include with PDD memory map before including PDD library.
#elif \
      !defined(MCU_MKL02Z4) /* UART0 */ && \
      !defined(MCU_MKL04Z4) /* UART0 */ && \
      !defined(MCU_MKL05Z4) /* UART0 */ && \
      !defined(MCU_MKL14Z4) /* UART0 */ && \
      !defined(MCU_MKL15Z4) /* UART0 */ && \
      !defined(MCU_MKL16Z4) /* UART0 */ && \
      !defined(MCU_MKL24Z4) /* UART0 */ && \
      !defined(MCU_MKL25Z4) /* UART0 */ && \
      !defined(MCU_MKL26Z4) /* UART0 */ && \
      !defined(MCU_MKL34Z4) /* UART0 */ && \
      !defined(MCU_MKL36Z4) /* UART0 */ && \
      !defined(MCU_MKL46Z4) /* UART0 */ && \
      !defined(MCU_MKW01Z4) /* UART0 */
  // Unsupported MCU is active
  #error UART0 PDD library: Unsupported derivative is active.
#endif

#include "PDD_Types.h"

/* ----------------------------------------------------------------------------
   -- Method symbol definitions
   ---------------------------------------------------------------------------- */

/* Interrupt masks */
#define UART0_PDD_INTERRUPT_TRANSMITTER          UART0_C2_TIE_MASK /**< Transmitter interrupt enable mask */
#define UART0_PDD_INTERRUPT_TRANSMITTER_COMPLETE UART0_C2_TCIE_MASK /**< Transmitter complete interrupt enable mask */
#define UART0_PDD_INTERRUPT_RECEIVER             UART0_C2_RIE_MASK /**< Receiver interrupt enable mask */
#define UART0_PDD_INTERRUPT_IDLE                 UART0_C2_ILIE_MASK /**< Idle interrupt enable mask */
#define UART0_PDD_INTERRUPT_PARITY_ERROR         UART0_C3_PEIE_MASK /**< Parity error interrupt enable mask */
#define UART0_PDD_INTERRUPT_FRAMING_ERROR        UART0_C3_FEIE_MASK /**< Framing error interrupt enable mask */
#define UART0_PDD_INTERRUPT_NOISE_ERROR          UART0_C3_NEIE_MASK /**< Noise error interrupt enable mask */
#define UART0_PDD_INTERRUPT_OVERRUN_ERROR        UART0_C3_ORIE_MASK /**< Overrun error interrupt enable mask */

/* Status flags constants. */
#define UART0_PDD_TX_DATA_EMPTY_FLAG    UART0_S1_TDRE_MASK /**< Transmitter FIFO word count is at or below watermark */
#define UART0_PDD_TX_IDLE_FLAG          UART0_S1_TC_MASK /**< No transmission in progress (transmission activity complete) */
#define UART0_PDD_RX_DATA_FULL_FLAG     UART0_S1_RDRF_MASK /**< Receiver FIFO word count is above watermark */
#define UART0_PDD_RX_IDLE_FLAG          UART0_S1_IDLE_MASK /**< Receiver input has become idle (after receiving a valid frame) */
#define UART0_PDD_RX_OVERRUN_FLAG       UART0_S1_OR_MASK /**< Receiver buffer overrun */
#define UART0_PDD_RX_NOISE_FLAG         UART0_S1_NF_MASK /**< Receiver input detect a noise. */
#define UART0_PDD_RX_FRAMING_ERROR_FLAG UART0_S1_FE_MASK /**< Receiver framing error detect */
#define UART0_PDD_RX_PARITY_ERROR_FLAG  UART0_S1_PF_MASK /**< Receiver parity error detect */

/* Status 2 flags constants. */
#define UART0_PDD_LIN_BREAK_DETECT_FLAG    UART0_S2_LBKDIF_MASK /**< LIN break character is detected on the receiver input */
#define UART0_PDD_RXD_PIN_ACTIVE_EDGE_FLAG UART0_S2_RXEDGIF_MASK /**< Active edge occurs on the RxD pin */
#define UART0_PDD_RECEIVER_ACTIVE_FLAG     UART0_S2_RAF_MASK /**< Receiver active, RxD input not idle */

/* Stop bit lengths */
#define UART0_PDD_STOP_BIT_LEN_1 0U              /**< One stop bit. */
#define UART0_PDD_STOP_BIT_LEN_2 0x20U           /**< Two stop bits. */

/* Loop mode */
#define UART0_PDD_LOOP_MODE_NORMAL       0U      /**< Normal operation mode. No loopback selected. */
#define UART0_PDD_LOOP_MODE_LOCAL_LOOP   0x1U    /**< Local loopback mode. */
#define UART0_PDD_LOOP_MODE_RX_TO_TX_PIN 0x2U    /**< Receiver input connected to TXD pin (single wire operation) */

/* Data width */
#define UART0_PDD_WIDTH_8  0U                    /**< 8-bit communication */
#define UART0_PDD_WIDTH_9  0x1U                  /**< 9-bit communication */
#define UART0_PDD_WIDTH_10 0x2U                  /**< 10-bit communication */

/* Wake-up condition constants. */
#define UART0_PDD_BY_IDLE_LINE    0U             /**< Idle line wake-up */
#define UART0_PDD_BY_ADDRESS_MARK 0x8U           /**< Address mark wake-up */

/* Idle line type constants. */
#define UART0_PDD_AFTER_START_BIT 0U             /**< Idle character bit count starts after start bit. */
#define UART0_PDD_AFTER_STOP_BIT  0x4U           /**< Idle character bit count starts after stop bit. */

/* Parity types */
#define UART0_PDD_PARITY_NONE 0U                 /**< No parity */
#define UART0_PDD_PARITY_EVEN 0x2U               /**< Even parity */
#define UART0_PDD_PARITY_ODD  0x3U               /**< Even parity */

/* Receiver power states. */
#define UART0_PDD_POWER_NORMAL  0U               /**< Normal operation. */
#define UART0_PDD_POWER_STANDBY 0x2U             /**< Standby mode (waiting for a wakeup condition). */

/* UART data shift order constants */
#define UART0_PDD_LSB_FIRST 0U                   /**< Data transfers start with least significant bit */
#define UART0_PDD_MSB_FIRST 0x20U                /**< Data transfers start with most significant bit */

/* Break transmit character length constants */
#define UART0_PDD_BREAK_CHARACTER_10_11_12_BITS 0U /**< Break character is 10, 11, or 12 bits long */
#define UART0_PDD_BREAK_CHARACTER_13_14_BITS    0x4U /**< Break character is 13 or 14 bits long */

/* Transmitter pin data direction (in single-wire mode) constants */
#define UART0_PDD_TX_PIN_IS_AN_INPUT  0U         /**< TxD pin is an input in single wire mode */
#define UART0_PDD_TX_PIN_IS_AN_OUTPUT 0x20U      /**< TxD pin is an output in single wire mode */

/* Position of a parity bit */
#define UART0_PDD_PARITY_BIT_POSITION_9  0U      /**< Parity bit is the 9-th bit in the serial transmission */
#define UART0_PDD_PARITY_BIT_POSITION_10 0x20U   /**< Parity bit is the 10-th bit in the serial transmission */


/* ----------------------------------------------------------------------------
   -- SetStopBitLength
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the number of stop bits.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Length Stop bit length. This parameter is of "Stop bit lengths" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_BDH.
 * @par Example:
 *      @code
 *      UART0_PDD_SetStopBitLength(<peripheral>_BASE_PTR,
 *      UART0_PDD_STOP_BIT_LEN_1);
 *      @endcode
 */
#define UART0_PDD_SetStopBitLength(PeripheralBase, Length) ( \
    UART0_BDH_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(UART0_BDH_REG(PeripheralBase) & (uint8_t)(~(uint8_t)UART0_BDH_SBNS_MASK))) | ( \
      (uint8_t)(Length))) \
  )

/* ----------------------------------------------------------------------------
   -- SetBaudRate
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets new baud rate value.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param BaudRate New baud rate value. This parameter is a 13-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_BDH, UART0_BDL
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      UART0_PDD_SetBaudRate(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define UART0_PDD_SetBaudRate(PeripheralBase, BaudRate) ( \
    (UART0_BDH_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(UART0_BDH_REG(PeripheralBase) & (uint8_t)(~(uint8_t)UART0_BDH_SBR_MASK))) | ( \
      (uint8_t)((uint16_t)(BaudRate) >> 8U)))), \
    (UART0_BDL_REG(PeripheralBase) = \
     (uint8_t)(BaudRate)) \
  )

/* ----------------------------------------------------------------------------
   -- ReadBaudRateHighReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads baud rate high register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: UART0_BDH.
 * @par Example:
 *      @code
 *      uint8_t result = UART0_PDD_ReadBaudRateHighReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define UART0_PDD_ReadBaudRateHighReg(PeripheralBase) ( \
    UART0_BDH_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteBaudRateHighReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes new value specified by the Value parameter into baud rate high
 * register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the baud rate high register. This
 *        parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_BDH.
 * @par Example:
 *      @code
 *      UART0_PDD_WriteBaudRateHighReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define UART0_PDD_WriteBaudRateHighReg(PeripheralBase, Value) ( \
    UART0_BDH_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadBaudRateLowReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads baud rate low register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: UART0_BDL.
 * @par Example:
 *      @code
 *      uint8_t result = UART0_PDD_ReadBaudRateLowReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define UART0_PDD_ReadBaudRateLowReg(PeripheralBase) ( \
    UART0_BDL_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteBaudRateLowReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes new value specified by the Value parameter into baud rate low
 * register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the baud rate low register. This
 *        parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_BDL.
 * @par Example:
 *      @code
 *      UART0_PDD_WriteBaudRateLowReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define UART0_PDD_WriteBaudRateLowReg(PeripheralBase, Value) ( \
    UART0_BDL_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- SetLoopMode
   ---------------------------------------------------------------------------- */

/**
 * @brief Selects the loop mode operation.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param LoopMode Loop mode. This parameter is of "Loop mode" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_C1.
 * @par Example:
 *      @code
 *      UART0_PDD_SetLoopMode(<peripheral>_BASE_PTR,
 *      UART0_PDD_LOOP_MODE_NORMAL);
 *      @endcode
 */
#define UART0_PDD_SetLoopMode(PeripheralBase, LoopMode) ( \
    ((LoopMode) == UART0_PDD_LOOP_MODE_NORMAL) ? ( \
      UART0_C1_REG(PeripheralBase) &= \
       (uint8_t)(( \
        (uint8_t)(~(uint8_t)UART0_C1_LOOPS_MASK)) & ( \
        (uint8_t)(~(uint8_t)UART0_C1_RSRC_MASK)))) : (((LoopMode) == UART0_PDD_LOOP_MODE_LOCAL_LOOP) ? ( \
      UART0_C1_REG(PeripheralBase) = \
       (uint8_t)(( \
        (uint8_t)(UART0_C1_REG(PeripheralBase) | UART0_C1_LOOPS_MASK)) & ( \
        (uint8_t)(~(uint8_t)UART0_C1_RSRC_MASK)))) : ( \
      UART0_C1_REG(PeripheralBase) |= \
       (uint8_t)(UART0_C1_LOOPS_MASK | UART0_C1_RSRC_MASK)) \
    ) \
  )

/* ----------------------------------------------------------------------------
   -- EnableOperateInWaitMode
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables/disables operate in wait mode.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of device in wait mode. This parameter is of
 *        "Global enumeration used for specifying general enable/disable states
 *        (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_C1.
 * @par Example:
 *      @code
 *      UART0_PDD_EnableOperateInWaitMode(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define UART0_PDD_EnableOperateInWaitMode(PeripheralBase, State) ( \
    ((State) == PDD_DISABLE) ? ( \
      UART0_C1_REG(PeripheralBase) |= \
       UART0_C1_DOZEEN_MASK) : ( \
      UART0_C1_REG(PeripheralBase) &= \
       (uint8_t)(~(uint8_t)UART0_C1_DOZEEN_MASK)) \
  )

/* ----------------------------------------------------------------------------
   -- SetDataWidth
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the communication width.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Width Data width. This parameter is of "Data width" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_C1, UART0_C4
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      UART0_PDD_SetDataWidth(<peripheral>_BASE_PTR, UART0_PDD_WIDTH_8);
 *      @endcode
 */
#define UART0_PDD_SetDataWidth(PeripheralBase, Width) ( \
    ( \
     ((Width) == UART0_PDD_WIDTH_8) ? ( \
      UART0_C1_REG(PeripheralBase) &= \
       (uint8_t)(~(uint8_t)UART0_C1_M_MASK)) : (((Width) == UART0_PDD_WIDTH_9) ? ( \
      UART0_C1_REG(PeripheralBase) |= \
       UART0_C1_M_MASK) : ( \
      UART0_C1_REG(PeripheralBase) &= \
       (uint8_t)(~(uint8_t)UART0_C1_M_MASK)) \
    )), \
    ( \
     ((Width) == UART0_PDD_WIDTH_8) ? ( \
      UART0_C4_REG(PeripheralBase) &= \
       (uint8_t)(~(uint8_t)UART0_C4_M10_MASK)) : (((Width) == UART0_PDD_WIDTH_9) ? ( \
      UART0_C4_REG(PeripheralBase) &= \
       (uint8_t)(~(uint8_t)UART0_C4_M10_MASK)) : ( \
      UART0_C4_REG(PeripheralBase) |= \
       UART0_C4_M10_MASK) \
    )) \
  )

/* ----------------------------------------------------------------------------
   -- SetWakeupCondition
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the wake-up condition.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Condition Wake-up condition. This parameter is of "Wake-up condition
 *        constants." type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_C1.
 * @par Example:
 *      @code
 *      UART0_PDD_SetWakeupCondition(<peripheral>_BASE_PTR,
 *      UART0_PDD_BY_IDLE_LINE);
 *      @endcode
 */
#define UART0_PDD_SetWakeupCondition(PeripheralBase, Condition) ( \
    UART0_C1_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(UART0_C1_REG(PeripheralBase) & (uint8_t)(~(uint8_t)UART0_C1_WAKE_MASK))) | ( \
      (uint8_t)(Condition))) \
  )

/* ----------------------------------------------------------------------------
   -- SelectIdleLineType
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the idle line type, it determines when the receiver starts
 * counting logic 1s as idle character bits.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Type Idle line type. This parameter is of "Idle line type constants."
 *        type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_C1.
 * @par Example:
 *      @code
 *      UART0_PDD_SelectIdleLineType(<peripheral>_BASE_PTR,
 *      UART0_PDD_AFTER_START_BIT);
 *      @endcode
 */
#define UART0_PDD_SelectIdleLineType(PeripheralBase, Type) ( \
    UART0_C1_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(UART0_C1_REG(PeripheralBase) & (uint8_t)(~(uint8_t)UART0_C1_ILT_MASK))) | ( \
      (uint8_t)(Type))) \
  )

/* ----------------------------------------------------------------------------
   -- SetParity
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets a communication parity type.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Parity Parity type. This parameter is of "Parity types" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_C1.
 * @par Example:
 *      @code
 *      UART0_PDD_SetParity(<peripheral>_BASE_PTR, UART0_PDD_PARITY_NONE);
 *      @endcode
 */
#define UART0_PDD_SetParity(PeripheralBase, Parity) ( \
    UART0_C1_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(UART0_C1_REG(PeripheralBase) & (uint8_t)(~(uint8_t)0x3U))) | ( \
      (uint8_t)(Parity))) \
  )

/* ----------------------------------------------------------------------------
   -- EnableInterrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables interrupts specified by the Mask parameter.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mask Interrupt mask. Use constants from group "Interrupt masks". This
 *        parameter is 8 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_C2, UART0_C3
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      UART0_PDD_EnableInterrupt(<peripheral>_BASE_PTR,
 *      UART0_PDD_INTERRUPT_TRANSMITTER);
 *      @endcode
 */
#define UART0_PDD_EnableInterrupt(PeripheralBase, Mask) ( \
    (UART0_C2_REG(PeripheralBase) |= \
     (uint8_t)((uint8_t)(Mask) & (uint8_t)(~(uint8_t)0xFU))), \
    (UART0_C3_REG(PeripheralBase) |= \
     (uint8_t)((uint8_t)(Mask) & 0xFU)) \
  )

/* ----------------------------------------------------------------------------
   -- DisableInterrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Disables interrupts specified by the Mask parameter.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mask Interrupt mask. Use constants from group "Interrupt masks". This
 *        parameter is 8 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_C2, UART0_C3
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      UART0_PDD_DisableInterrupt(<peripheral>_BASE_PTR,
 *      UART0_PDD_INTERRUPT_TRANSMITTER);
 *      @endcode
 */
#define UART0_PDD_DisableInterrupt(PeripheralBase, Mask) ( \
    (UART0_C2_REG(PeripheralBase) &= \
     (uint8_t)(~(uint8_t)((uint8_t)(Mask) & (uint8_t)(~(uint8_t)0xFU)))), \
    (UART0_C3_REG(PeripheralBase) &= \
     (uint8_t)(~(uint8_t)((uint8_t)(Mask) & 0xFU))) \
  )

/* ----------------------------------------------------------------------------
   -- GetTxCompleteInterruptMask
   ---------------------------------------------------------------------------- */

/**
 * @brief Gets the status of the transmiter complete interrupt enable bit.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: UART0_C2.
 * @par Example:
 *      @code
 *      uint8_t result =
 *      UART0_PDD_GetTxCompleteInterruptMask(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define UART0_PDD_GetTxCompleteInterruptMask(PeripheralBase) ( \
    (uint8_t)(UART0_C2_REG(PeripheralBase) & UART0_C2_TCIE_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- EnableTransmitter
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables UART transmitter.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Enables or disables transmitter. This parameter is of "Global
 *        enumeration used for specifying general enable/disable states
 *        (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_C2.
 * @par Example:
 *      @code
 *      UART0_PDD_EnableTransmitter(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define UART0_PDD_EnableTransmitter(PeripheralBase, State) ( \
    UART0_C2_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(UART0_C2_REG(PeripheralBase) & (uint8_t)(~(uint8_t)UART0_C2_TE_MASK))) | ( \
      (uint8_t)((uint8_t)(State) << UART0_C2_TE_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- EnableReceiver
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables UART receiver.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Enables or disables receiver. This parameter is of "Global
 *        enumeration used for specifying general enable/disable states (PDD_DISABLE
 *        and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_C2.
 * @par Example:
 *      @code
 *      UART0_PDD_EnableReceiver(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define UART0_PDD_EnableReceiver(PeripheralBase, State) ( \
    UART0_C2_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(UART0_C2_REG(PeripheralBase) & (uint8_t)(~(uint8_t)UART0_C2_RE_MASK))) | ( \
      (uint8_t)((uint8_t)(State) << UART0_C2_RE_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SetReceiverPowerState
   ---------------------------------------------------------------------------- */

/**
 * @brief Places the receiver in a standby state where it waits for automatic
 * hardware detection of a selected wakeup condition.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Receiver power state to be set. This parameter is of "Receiver
 *        power states." type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_C2.
 * @par Example:
 *      @code
 *      UART0_PDD_SetReceiverPowerState(<peripheral>_BASE_PTR,
 *      UART0_PDD_POWER_NORMAL);
 *      @endcode
 */
#define UART0_PDD_SetReceiverPowerState(PeripheralBase, State) ( \
    UART0_C2_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(UART0_C2_REG(PeripheralBase) & (uint8_t)(~(uint8_t)UART0_C2_RWU_MASK))) | ( \
      (uint8_t)(State))) \
  )

/* ----------------------------------------------------------------------------
   -- SetBreak
   ---------------------------------------------------------------------------- */

/**
 * @brief Set the break signal.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_C2.
 * @par Example:
 *      @code
 *      UART0_PDD_SetBreak(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define UART0_PDD_SetBreak(PeripheralBase) ( \
    UART0_C2_REG(PeripheralBase) |= \
     UART0_C2_SBK_MASK \
  )

/* ----------------------------------------------------------------------------
   -- ClearBreak
   ---------------------------------------------------------------------------- */

/**
 * @brief Clears the break signal.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_C2.
 * @par Example:
 *      @code
 *      UART0_PDD_ClearBreak(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define UART0_PDD_ClearBreak(PeripheralBase) ( \
    UART0_C2_REG(PeripheralBase) &= \
     (uint8_t)(~(uint8_t)UART0_C2_SBK_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- SendBreak
   ---------------------------------------------------------------------------- */

/**
 * @brief Send the break character.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_C2.
 * @par Example:
 *      @code
 *      UART0_PDD_SendBreak(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define UART0_PDD_SendBreak(PeripheralBase) ( \
    (UART0_C2_REG(PeripheralBase) |= \
     UART0_C2_SBK_MASK), \
    (UART0_C2_REG(PeripheralBase) &= \
     (uint8_t)(~(uint8_t)UART0_C2_SBK_MASK)) \
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
 * @remarks The macro accesses the following registers: UART0_C2.
 * @par Example:
 *      @code
 *      uint8_t result = UART0_PDD_ReadControl2Reg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define UART0_PDD_ReadControl2Reg(PeripheralBase) ( \
    UART0_C2_REG(PeripheralBase) \
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
 * @remarks The macro accesses the following registers: UART0_C2.
 * @par Example:
 *      @code
 *      UART0_PDD_WriteControl2Reg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define UART0_PDD_WriteControl2Reg(PeripheralBase, Value) ( \
    UART0_C2_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadStatus1Flags
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the value of the status 1 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: UART0_S1.
 * @par Example:
 *      @code
 *      uint8_t result = UART0_PDD_ReadStatus1Flags(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define UART0_PDD_ReadStatus1Flags(PeripheralBase) ( \
    UART0_S1_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- ClearInterruptFlags
   ---------------------------------------------------------------------------- */

/**
 * @brief Clears the interrupt status flags specified by the Mask parameter.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mask Mask of the flags to be cleared. This parameter is a 8-bit value.
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: UART0_S1.
 * @par Example:
 *      @code
 *      uint8_t result = UART0_PDD_ClearInterruptFlags(<peripheral>_BASE_PTR,
 *      1);
 *      @endcode
 */
#define UART0_PDD_ClearInterruptFlags(PeripheralBase, Mask) ( \
    UART0_S1_REG(PeripheralBase) = \
     (uint8_t)(Mask) \
  )

/* ----------------------------------------------------------------------------
   -- GetTxCompleteStatus
   ---------------------------------------------------------------------------- */

/**
 * @brief Gets the status of the transmiter complete interrupt flag.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: UART0_S1.
 * @par Example:
 *      @code
 *      uint8_t result = UART0_PDD_GetTxCompleteStatus(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define UART0_PDD_GetTxCompleteStatus(PeripheralBase) ( \
    (uint8_t)(UART0_S1_REG(PeripheralBase) & UART0_S1_TC_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- ReadInterruptStatusReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the interrupt status register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: UART0_S1.
 * @par Example:
 *      @code
 *      uint8_t result =
 *      UART0_PDD_ReadInterruptStatusReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define UART0_PDD_ReadInterruptStatusReg(PeripheralBase) ( \
    UART0_S1_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- GetBreak
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: UART0_S1.
 * @par Example:
 *      @code
 *      uint8_t result = UART0_PDD_GetBreak(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define UART0_PDD_GetBreak(PeripheralBase) ( \
    (( \
      (uint8_t)(( \
       UART0_S1_REG(PeripheralBase)) & ( \
       (uint8_t)(UART0_S1_FE_MASK | UART0_S1_RDRF_MASK)))) == ( \
      (uint8_t)(UART0_S1_FE_MASK | UART0_S1_RDRF_MASK))) ? ( \
      0x1U) : ( \
      0U) \
  )

/* ----------------------------------------------------------------------------
   -- ReadStatus1Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads status 1 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: UART0_S1.
 * @par Example:
 *      @code
 *      uint8_t result = UART0_PDD_ReadStatus1Reg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define UART0_PDD_ReadStatus1Reg(PeripheralBase) ( \
    UART0_S1_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteStatus1Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes new value specified by the Value parameter into status 1
 * register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the status 1 register. This parameter is
 *        a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_S1.
 * @par Example:
 *      @code
 *      UART0_PDD_WriteStatus1Reg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define UART0_PDD_WriteStatus1Reg(PeripheralBase, Value) ( \
    UART0_S1_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadStatus2Flags
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the flags of the status 2 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: UART0_S2.
 * @par Example:
 *      @code
 *      uint8_t result = UART0_PDD_ReadStatus2Flags(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define UART0_PDD_ReadStatus2Flags(PeripheralBase) ( \
    (uint8_t)(( \
     UART0_S2_REG(PeripheralBase)) & ( \
     (uint8_t)(UART0_S2_LBKDIF_MASK | (UART0_S2_RXEDGIF_MASK | UART0_S2_RAF_MASK)))) \
  )

/* ----------------------------------------------------------------------------
   -- ClearStatus2Flags
   ---------------------------------------------------------------------------- */

/**
 * @brief Clears the flags of the status 2 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mask Mask of interrupt requests. This parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_S2.
 * @par Example:
 *      @code
 *      UART0_PDD_ClearStatus2Flags(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define UART0_PDD_ClearStatus2Flags(PeripheralBase, Mask) ( \
    UART0_S2_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(( \
       UART0_S2_REG(PeripheralBase)) & ( \
       (uint8_t)(~(uint8_t)(UART0_S2_LBKDIF_MASK | UART0_S2_RXEDGIF_MASK))))) | ( \
      (uint8_t)(Mask))) \
  )

/* ----------------------------------------------------------------------------
   -- SetDataShiftOrder
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the UART data shift order.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Order UART data shift order value. The user should use one from the
 *        enumerated values. This parameter is of "UART data shift order constants"
 *        type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_S2.
 * @par Example:
 *      @code
 *      UART0_PDD_SetDataShiftOrder(<peripheral>_BASE_PTR, UART0_PDD_LSB_FIRST);
 *      @endcode
 */
#define UART0_PDD_SetDataShiftOrder(PeripheralBase, Order) ( \
    UART0_S2_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(UART0_S2_REG(PeripheralBase) & (uint8_t)(~(uint8_t)UART0_S2_MSBF_MASK))) | ( \
      (uint8_t)(Order))) \
  )

/* ----------------------------------------------------------------------------
   -- EnableReceiveDataInversion
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables receive data inversion.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Enables or disables receive data inversion. This parameter is of
 *        "Global enumeration used for specifying general enable/disable states
 *        (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_S2.
 * @par Example:
 *      @code
 *      UART0_PDD_EnableReceiveDataInversion(<peripheral>_BASE_PTR,
 *      PDD_DISABLE);
 *      @endcode
 */
#define UART0_PDD_EnableReceiveDataInversion(PeripheralBase, State) ( \
    UART0_S2_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(UART0_S2_REG(PeripheralBase) & (uint8_t)(~(uint8_t)UART0_S2_RXINV_MASK))) | ( \
      (uint8_t)((uint8_t)(State) << UART0_S2_RXINV_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- EnableReceiveWakeupIdleDetect
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables receive wakeup idle detect.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Enables or disables receive wakeup idle detect. This parameter
 *        is of "Global enumeration used for specifying general enable/disable
 *        states (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_S2.
 * @par Example:
 *      @code
 *      UART0_PDD_EnableReceiveWakeupIdleDetect(<peripheral>_BASE_PTR,
 *      PDD_DISABLE);
 *      @endcode
 */
#define UART0_PDD_EnableReceiveWakeupIdleDetect(PeripheralBase, State) ( \
    UART0_S2_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(UART0_S2_REG(PeripheralBase) & (uint8_t)(~(uint8_t)UART0_S2_RWUID_MASK))) | ( \
      (uint8_t)((uint8_t)(State) << UART0_S2_RWUID_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SetBreakLength
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the break transmit character length.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Length Break transmit character length value. The user should use one
 *        from the enumerated values. This parameter is of "Break transmit
 *        character length constants" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_S2.
 * @par Example:
 *      @code
 *      UART0_PDD_SetBreakLength(<peripheral>_BASE_PTR,
 *      UART0_PDD_BREAK_CHARACTER_10_11_12_BITS);
 *      @endcode
 */
#define UART0_PDD_SetBreakLength(PeripheralBase, Length) ( \
    UART0_S2_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(UART0_S2_REG(PeripheralBase) & (uint8_t)(~(uint8_t)UART0_S2_BRK13_MASK))) | ( \
      (uint8_t)(Length))) \
  )

/* ----------------------------------------------------------------------------
   -- EnableLinBreakLongerCharacterDetection
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables LIN break detection for longer character.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Enables or disables LIN break detection for longer character.
 *        This parameter is of "Global enumeration used for specifying general
 *        enable/disable states (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)"
 *        type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_S2.
 * @par Example:
 *      @code
 *      UART0_PDD_EnableLinBreakLongerCharacterDetection(<peripheral>_BASE_PTR,
 *      PDD_DISABLE);
 *      @endcode
 */
#define UART0_PDD_EnableLinBreakLongerCharacterDetection(PeripheralBase, State) ( \
    UART0_S2_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(UART0_S2_REG(PeripheralBase) & (uint8_t)(~(uint8_t)UART0_S2_LBKDE_MASK))) | ( \
      (uint8_t)((uint8_t)(State) << UART0_S2_LBKDE_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- ReadStatus2Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads status 2 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: UART0_S2.
 * @par Example:
 *      @code
 *      uint8_t result = UART0_PDD_ReadStatus2Reg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define UART0_PDD_ReadStatus2Reg(PeripheralBase) ( \
    UART0_S2_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteStatus2Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes new value specified by the Value parameter into status 2
 * register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the status 2 register. This parameter is
 *        a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_S2.
 * @par Example:
 *      @code
 *      UART0_PDD_WriteStatus2Reg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define UART0_PDD_WriteStatus2Reg(PeripheralBase, Value) ( \
    UART0_S2_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- GetChar9Bit
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the 9th bit of the character from the receive buffer shifted
 * to its bit position (9th). Must be called prior to calling GetChar8 to read the
 * whole 9-bit character.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 9-bit value. The value is cast to "uint16_t".
 * @remarks The macro accesses the following registers: UART0_C3.
 * @par Example:
 *      @code
 *      uint16_t result = UART0_PDD_GetChar9Bit(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define UART0_PDD_GetChar9Bit(PeripheralBase) ( \
    (uint16_t)(( \
     (uint16_t)(( \
      (uint16_t)(UART0_C3_REG(PeripheralBase) & UART0_C3_R8T9_MASK)) >> ( \
      UART0_C3_R8T9_SHIFT))) << ( \
     8U)) \
  )

/* ----------------------------------------------------------------------------
   -- PutChar9
   ---------------------------------------------------------------------------- */

/**
 * @brief Puts 9-bits character into the transmit buffer.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Char 9-bits character to be written to the data register. This
 *        parameter is a 9-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_C3, UART0_D
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      UART0_PDD_PutChar9(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define UART0_PDD_PutChar9(PeripheralBase, Char) ( \
    (UART0_C3_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(UART0_C3_REG(PeripheralBase) & (uint8_t)(~(uint8_t)UART0_C3_R9T8_MASK))) | ( \
      (uint8_t)((uint8_t)((uint16_t)(Char) >> 8U) << UART0_C3_R9T8_SHIFT)))), \
    (UART0_D_REG(PeripheralBase) = \
     (uint8_t)(Char)) \
  )

/* ----------------------------------------------------------------------------
   -- PutChar10
   ---------------------------------------------------------------------------- */

/**
 * @brief Puts 10-bits character into the transmit buffer.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Char 10-bits character to be written to the data register. This
 *        parameter is a 10-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_C3, UART0_D
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      UART0_PDD_PutChar10(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define UART0_PDD_PutChar10(PeripheralBase, Char) ( \
    (UART0_C3_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(UART0_C3_REG(PeripheralBase) & (uint8_t)(~(uint8_t)((uint8_t)0x3U << 6U)))) | ( \
      (uint8_t)((uint8_t)((uint16_t)(Char) >> 8U) << 6U)))), \
    (UART0_D_REG(PeripheralBase) = \
     (uint8_t)(Char)) \
  )

/* ----------------------------------------------------------------------------
   -- GetChar9To10thBit
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the 9th and 10th bit of the character from the receive buffer
 * shifted to their bit positions (9th and 10th). Must be called prior to calling
 * GetChar8 to read the whole 10-bit character.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 10-bit value. The value is cast to "uint16_t".
 * @remarks The macro accesses the following registers: UART0_C3.
 * @par Example:
 *      @code
 *      uint16_t result = UART0_PDD_GetChar9To10thBit(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define UART0_PDD_GetChar9To10thBit(PeripheralBase) ( \
    (uint16_t)(( \
     (uint16_t)(( \
      (uint16_t)(( \
       (uint16_t)(UART0_C3_REG(PeripheralBase) & UART0_C3_R8T9_MASK)) >> ( \
       UART0_C3_R8T9_SHIFT))) | ( \
      (uint16_t)(( \
       (uint16_t)(( \
        (uint16_t)(UART0_C3_REG(PeripheralBase) & UART0_C3_R9T8_MASK)) >> ( \
        UART0_C3_R9T8_SHIFT))) << ( \
       1U))))) << ( \
     8U)) \
  )

/* ----------------------------------------------------------------------------
   -- SetTxPinDataDirection
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the transmitter pin data direction in single-wire mode.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Direction Transmitter pin data direction value. The user should use
 *        one from the enumerated values. This parameter is of "Transmitter pin
 *        data direction (in single-wire mode) constants" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_C3.
 * @par Example:
 *      @code
 *      UART0_PDD_SetTxPinDataDirection(<peripheral>_BASE_PTR,
 *      UART0_PDD_TX_PIN_IS_AN_INPUT);
 *      @endcode
 */
#define UART0_PDD_SetTxPinDataDirection(PeripheralBase, Direction) ( \
    UART0_C3_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(UART0_C3_REG(PeripheralBase) & (uint8_t)(~(uint8_t)UART0_C3_TXDIR_MASK))) | ( \
      (uint8_t)(Direction))) \
  )

/* ----------------------------------------------------------------------------
   -- EnableTransmitDataInversion
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables transmit data inversion.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Enables or disables transmit data inversion. This parameter is
 *        of "Global enumeration used for specifying general enable/disable states
 *        (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_C3.
 * @par Example:
 *      @code
 *      UART0_PDD_EnableTransmitDataInversion(<peripheral>_BASE_PTR,
 *      PDD_DISABLE);
 *      @endcode
 */
#define UART0_PDD_EnableTransmitDataInversion(PeripheralBase, State) ( \
    UART0_C3_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(UART0_C3_REG(PeripheralBase) & (uint8_t)(~(uint8_t)UART0_C3_TXINV_MASK))) | ( \
      (uint8_t)((uint8_t)(State) << UART0_C3_TXINV_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- ReadControl3Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads control 3 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: UART0_C3.
 * @par Example:
 *      @code
 *      uint8_t result = UART0_PDD_ReadControl3Reg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define UART0_PDD_ReadControl3Reg(PeripheralBase) ( \
    UART0_C3_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteControl3Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes new value specified by the Value parameter into control 3
 * register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the control 3 register. This parameter is
 *        a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_C3.
 * @par Example:
 *      @code
 *      UART0_PDD_WriteControl3Reg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define UART0_PDD_WriteControl3Reg(PeripheralBase, Value) ( \
    UART0_C3_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- PutChar8
   ---------------------------------------------------------------------------- */

/**
 * @brief Puts 8-bits character into the transmit buffer.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Char 8-bits character to be written to the data register. This
 *        parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_D.
 * @par Example:
 *      @code
 *      UART0_PDD_PutChar8(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define UART0_PDD_PutChar8(PeripheralBase, Char) ( \
    UART0_D_REG(PeripheralBase) = \
     (uint8_t)(Char) \
  )

/* ----------------------------------------------------------------------------
   -- GetChar8
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns a 8-bit character from the receive buffer.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: UART0_D.
 * @par Example:
 *      @code
 *      uint8_t result = UART0_PDD_GetChar8(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define UART0_PDD_GetChar8(PeripheralBase) ( \
    UART0_D_REG(PeripheralBase) \
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
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: UART0_D.
 * @par Example:
 *      @code
 *      uint8_t result = UART0_PDD_ReadDataReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define UART0_PDD_ReadDataReg(PeripheralBase) ( \
    UART0_D_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteDataReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes data specified by the Value parameter into data register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the data register. This parameter is a
 *        8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_D.
 * @par Example:
 *      @code
 *      UART0_PDD_WriteDataReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define UART0_PDD_WriteDataReg(PeripheralBase, Value) ( \
    UART0_D_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- GetMatchAddress1Value
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns match address 1 value.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: UART0_MA1.
 * @par Example:
 *      @code
 *      uint8_t result = UART0_PDD_GetMatchAddress1Value(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define UART0_PDD_GetMatchAddress1Value(PeripheralBase) ( \
    UART0_MA1_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- SetMatchAddress1Value
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets a new match address 1 value.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Address Match address 1 value. This parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_MA1.
 * @par Example:
 *      @code
 *      UART0_PDD_SetMatchAddress1Value(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define UART0_PDD_SetMatchAddress1Value(PeripheralBase, Address) ( \
    UART0_MA1_REG(PeripheralBase) = \
     (uint8_t)(Address) \
  )

/* ----------------------------------------------------------------------------
   -- ReadMatchAddress1Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads match address 1 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: UART0_MA1.
 * @par Example:
 *      @code
 *      uint8_t result = UART0_PDD_ReadMatchAddress1Reg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define UART0_PDD_ReadMatchAddress1Reg(PeripheralBase) ( \
    UART0_MA1_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteMatchAddress1Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes data specified by the Value parameter into match address 1
 * register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the match address 1 register. This
 *        parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_MA1.
 * @par Example:
 *      @code
 *      UART0_PDD_WriteMatchAddress1Reg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define UART0_PDD_WriteMatchAddress1Reg(PeripheralBase, Value) ( \
    UART0_MA1_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- GetMatchAddress2Value
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns match address 2 value.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: UART0_MA2.
 * @par Example:
 *      @code
 *      uint8_t result = UART0_PDD_GetMatchAddress2Value(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define UART0_PDD_GetMatchAddress2Value(PeripheralBase) ( \
    UART0_MA2_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- SetMatchAddress2Value
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets a new match address 2 value.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Address Match address 2 value. This parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_MA2.
 * @par Example:
 *      @code
 *      UART0_PDD_SetMatchAddress2Value(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define UART0_PDD_SetMatchAddress2Value(PeripheralBase, Address) ( \
    UART0_MA2_REG(PeripheralBase) = \
     (uint8_t)(Address) \
  )

/* ----------------------------------------------------------------------------
   -- ReadMatchAddress2Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads match address 2 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: UART0_MA2.
 * @par Example:
 *      @code
 *      uint8_t result = UART0_PDD_ReadMatchAddress2Reg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define UART0_PDD_ReadMatchAddress2Reg(PeripheralBase) ( \
    UART0_MA2_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteMatchAddress2Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes data specified by the Value parameter into match address 2
 * register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the match address 2 register. This
 *        parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_MA2.
 * @par Example:
 *      @code
 *      UART0_PDD_WriteMatchAddress2Reg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define UART0_PDD_WriteMatchAddress2Reg(PeripheralBase, Value) ( \
    UART0_MA2_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- EnableMatchAddress1Mode
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables address 1 match mode.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Enables or disables address 1 match mode. This parameter is of
 *        "Global enumeration used for specifying general enable/disable states
 *        (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_C4.
 * @par Example:
 *      @code
 *      UART0_PDD_EnableMatchAddress1Mode(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define UART0_PDD_EnableMatchAddress1Mode(PeripheralBase, State) ( \
    UART0_C4_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(UART0_C4_REG(PeripheralBase) & (uint8_t)(~(uint8_t)UART0_C4_MAEN1_MASK))) | ( \
      (uint8_t)((uint8_t)(State) << UART0_C4_MAEN1_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- EnableMatchAddress2Mode
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables address 2 match mode.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Enables or disables address 2 match mode. This parameter is of
 *        "Global enumeration used for specifying general enable/disable states
 *        (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_C4.
 * @par Example:
 *      @code
 *      UART0_PDD_EnableMatchAddress2Mode(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define UART0_PDD_EnableMatchAddress2Mode(PeripheralBase, State) ( \
    UART0_C4_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(UART0_C4_REG(PeripheralBase) & (uint8_t)(~(uint8_t)UART0_C4_MAEN2_MASK))) | ( \
      (uint8_t)((uint8_t)(State) << UART0_C4_MAEN2_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SetPositionOfParityBit
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the position of the parity bit.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Position Position of a parity bit. This parameter is of "Position of a
 *        parity bit" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_C4.
 * @par Example:
 *      @code
 *      UART0_PDD_SetPositionOfParityBit(<peripheral>_BASE_PTR,
 *      UART0_PDD_PARITY_BIT_POSITION_9);
 *      @endcode
 */
#define UART0_PDD_SetPositionOfParityBit(PeripheralBase, Position) ( \
    UART0_C4_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(UART0_C4_REG(PeripheralBase) & (uint8_t)(~(uint8_t)UART0_C4_M10_MASK))) | ( \
      (uint8_t)(Position))) \
  )

/* ----------------------------------------------------------------------------
   -- SetOversamplingRatio
   ---------------------------------------------------------------------------- */

/**
 * @brief Set baud rate oversampling ratio.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Ratio Baud rate oversampling ratio. This parameter is a 5-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_C4.
 * @par Example:
 *      @code
 *      UART0_PDD_SetOversamplingRatio(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define UART0_PDD_SetOversamplingRatio(PeripheralBase, Ratio) ( \
    UART0_C4_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(UART0_C4_REG(PeripheralBase) & (uint8_t)(~(uint8_t)UART0_C4_OSR_MASK))) | ( \
      (uint8_t)(Ratio))) \
  )

/* ----------------------------------------------------------------------------
   -- ReadControl4Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads control 4 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: UART0_C4.
 * @par Example:
 *      @code
 *      uint8_t result = UART0_PDD_ReadControl4Reg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define UART0_PDD_ReadControl4Reg(PeripheralBase) ( \
    UART0_C4_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteControl4Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes data specified by the Value parameter into control 4 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the control 4 register. This parameter is
 *        a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_C4.
 * @par Example:
 *      @code
 *      UART0_PDD_WriteControl4Reg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define UART0_PDD_WriteControl4Reg(PeripheralBase, Value) ( \
    UART0_C4_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- EnableTransmitDma
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables/disables a transmit DMA request.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of transmit DMA request. This parameter is of
 *        "Global enumeration used for specifying general enable/disable states
 *        (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_C5.
 * @par Example:
 *      @code
 *      UART0_PDD_EnableTransmitDma(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define UART0_PDD_EnableTransmitDma(PeripheralBase, State) ( \
    UART0_C5_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(UART0_C5_REG(PeripheralBase) & (uint8_t)(~(uint8_t)UART0_C5_TDMAE_MASK))) | ( \
      (uint8_t)((uint8_t)(State) << UART0_C5_TDMAE_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- EnableReceiveDma
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables/disables a receive DMA request.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of receive DMA request. This parameter is of
 *        "Global enumeration used for specifying general enable/disable states
 *        (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_C5.
 * @par Example:
 *      @code
 *      UART0_PDD_EnableReceiveDma(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define UART0_PDD_EnableReceiveDma(PeripheralBase, State) ( \
    UART0_C5_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(UART0_C5_REG(PeripheralBase) & (uint8_t)(~(uint8_t)UART0_C5_RDMAE_MASK))) | ( \
      (uint8_t)((uint8_t)(State) << UART0_C5_RDMAE_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- EnableSamplingOnBothEdges
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables receiver sampling on both edges.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Enable or disable sampling on both edges. This parameter is of
 *        "Global enumeration used for specifying general enable/disable states
 *        (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_C5.
 * @par Example:
 *      @code
 *      UART0_PDD_EnableSamplingOnBothEdges(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define UART0_PDD_EnableSamplingOnBothEdges(PeripheralBase, State) ( \
    UART0_C5_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(UART0_C5_REG(PeripheralBase) & (uint8_t)(~(uint8_t)UART0_C5_BOTHEDGE_MASK))) | ( \
      (uint8_t)((uint8_t)(State) << UART0_C5_BOTHEDGE_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- EnableResynchronization
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables/disables a resynchronization during received data word.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of resynchronization during received data word.
 *        This parameter is of "Global enumeration used for specifying general
 *        enable/disable states (PDD_DISABLE and PDD_ENABLE defined in
 *        PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_C5.
 * @par Example:
 *      @code
 *      UART0_PDD_EnableResynchronization(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define UART0_PDD_EnableResynchronization(PeripheralBase, State) ( \
    ((State) == PDD_DISABLE) ? ( \
      UART0_C5_REG(PeripheralBase) |= \
       UART0_C5_RESYNCDIS_MASK) : ( \
      UART0_C5_REG(PeripheralBase) &= \
       (uint8_t)(~(uint8_t)UART0_C5_RESYNCDIS_MASK)) \
  )

/* ----------------------------------------------------------------------------
   -- ReadControl5Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads control 5 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: UART0_C5.
 * @par Example:
 *      @code
 *      uint8_t result = UART0_PDD_ReadControl5Reg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define UART0_PDD_ReadControl5Reg(PeripheralBase) ( \
    UART0_C5_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteControl5Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes data specified by the Value parameter into control 5 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the control 5 register. This parameter is
 *        a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_C5.
 * @par Example:
 *      @code
 *      UART0_PDD_WriteControl5Reg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define UART0_PDD_WriteControl5Reg(PeripheralBase, Value) ( \
    UART0_C5_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )
#endif  /* #if defined(UART0_PDD_H_) */

/* UART0_PDD.h, eof. */
