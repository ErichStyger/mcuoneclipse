/*
  PDD layer implementation for peripheral type LPUART
  (C) 2013 Freescale, Inc. All rights reserved.

  This file is static and it is generated from API-Factory
*/

#if !defined(LPUART_PDD_H_)
#define LPUART_PDD_H_

/* ----------------------------------------------------------------------------
   -- Test if supported MCU is active
   ---------------------------------------------------------------------------- */

#if !defined(MCU_ACTIVE)
  // No MCU is active
  #error LPUART PDD library: No derivative is active. Place proper #include with PDD memory map before including PDD library.
#elif \
      !defined(MCU_MK22F12810) /* LPUART0 */ && \
      !defined(MCU_MK22F25612) /* LPUART0 */ && \
      !defined(MCU_MK22F51212) /* LPUART0 */ && \
      !defined(MCU_MKV31F12810) /* LPUART0 */ && \
      !defined(MCU_MKV31F25612) /* LPUART0 */ && \
      !defined(MCU_MKV31F51212) /* LPUART0 */
  // Unsupported MCU is active
  #error LPUART PDD library: Unsupported derivative is active.
#endif

#include "PDD_Types.h"

/* ----------------------------------------------------------------------------
   -- Method symbol definitions
   ---------------------------------------------------------------------------- */

/* Interrupt masks */
#define LPUART_PDD_INTERRUPT_OVERRUN_ERROR        LPUART_CTRL_ORIE_MASK /**< Overrun error interrupt enable mask */
#define LPUART_PDD_INTERRUPT_NOISE_ERROR          LPUART_CTRL_NEIE_MASK /**< Noise error interrupt enable mask */
#define LPUART_PDD_INTERRUPT_FRAMING_ERROR        LPUART_CTRL_FEIE_MASK /**< Framing error interrupt enable mask */
#define LPUART_PDD_INTERRUPT_PARITY_ERROR         LPUART_CTRL_PEIE_MASK /**< Parity error interrupt enable mask */
#define LPUART_PDD_INTERRUPT_TRANSMITTER          LPUART_CTRL_TIE_MASK /**< Transmitter interrupt enable mask */
#define LPUART_PDD_INTERRUPT_TRANSMITTER_COMPLETE LPUART_CTRL_TCIE_MASK /**< Transmitter complete interrupt enable mask */
#define LPUART_PDD_INTERRUPT_RECEIVER             LPUART_CTRL_RIE_MASK /**< Receiver interrupt enable mask */
#define LPUART_PDD_INTERRUPT_IDLE                 LPUART_CTRL_ILIE_MASK /**< Idle interrupt enable mask */
#define LPUART_PDD_INTERRUPT_MATCH1               LPUART_CTRL_MA1IE_MASK /**< Match 1 interrupt enable mask */
#define LPUART_PDD_INTERRUPT_MATCH2               LPUART_CTRL_MA2IE_MASK /**< Match 2 interrupt enable mask */

/* Status flags constants. */
#define LPUART_PDD_LIN_BREAK_DETECT_FLAG    LPUART_STAT_LBKDIF_MASK /**< LIN break character is detected on the receiver input */
#define LPUART_PDD_RXD_PIN_ACTIVE_EDGE_FLAG LPUART_STAT_RXEDGIF_MASK /**< Active edge occurs on the RxD pin */
#define LPUART_PDD_RECEIVER_ACTIVE_FLAG     LPUART_STAT_RAF_MASK /**< Receiver active, RxD input not idle */
#define LPUART_PDD_TX_DATA_EMPTY_FLAG       LPUART_STAT_TDRE_MASK /**< Transmitter FIFO word count is at or below watermark */
#define LPUART_PDD_TX_IDLE_FLAG             LPUART_STAT_TC_MASK /**< No transmission in progress (transmission activity complete) */
#define LPUART_PDD_RX_DATA_FULL_FLAG        LPUART_STAT_RDRF_MASK /**< Receiver FIFO word count is above watermark */
#define LPUART_PDD_RX_IDLE_FLAG             LPUART_STAT_IDLE_MASK /**< Receiver input has become idle (after receiving a valid frame) */
#define LPUART_PDD_RX_OVERRUN_FLAG          LPUART_STAT_OR_MASK /**< Receiver buffer overrun */
#define LPUART_PDD_RX_NOISE_FLAG            LPUART_STAT_NF_MASK /**< Receiver input detect a noise. */
#define LPUART_PDD_RX_FRAMING_ERROR_FLAG    LPUART_STAT_FE_MASK /**< Receiver framing error detect */
#define LPUART_PDD_RX_PARITY_ERROR_FLAG     LPUART_STAT_PF_MASK /**< Receiver parity error detect */
#define LPUART_PDD_MATCH_ADDRESS_1_FLAG     LPUART_STAT_MA1F_MASK /**< Match address one detect */
#define LPUART_PDD_MATCH_ADDRESS_2_FLAG     LPUART_STAT_MA2F_MASK /**< Match address two detect */

/* Position of a parity bit */
#define LPUART_PDD_PARITY_BIT_POSITION_9  0U     /**< Parity bit is the 9-th bit in the serial transmission */
#define LPUART_PDD_PARITY_BIT_POSITION_10 0x20000000U /**< Parity bit is the 10-th bit in the serial transmission */

/* Type of the match operation. */
#define LPUART_PDD_ADRESS_MATCH       0U         /**< Wake up receiver if the address match with Match 1 or Match 2. */
#define LPUART_PDD_IDLE_MATCH         0x40000U   /**< Wake up receiver if the first character after idle match with Match 1 or Match 2. */
#define LPUART_PDD_MATCH_ON_MATCH_OFF 0x80000U   /**< Wake up receiver on the Match 1 and sleep on the Match 2. */
#define LPUART_PDD_DATA_MATCH         0xC0000U   /**< Wake up receiver on Data Match and Match On/Off for transmitter CTS input. */

/* Stop bit lengths */
#define LPUART_PDD_STOP_BIT_LEN_1 0U             /**< One stop bit. */
#define LPUART_PDD_STOP_BIT_LEN_2 0x2000U        /**< Two stop bits. */

/* Data width */
#define LPUART_PDD_WIDTH_8  0U                   /**< 8-bit communication */
#define LPUART_PDD_WIDTH_9  0x1U                 /**< 9-bit communication */
#define LPUART_PDD_WIDTH_10 0x2U                 /**< 10-bit communication (10th bit can be used only as parity bit) */

/* Loop mode */
#define LPUART_PDD_LOOP_MODE_NORMAL       0U     /**< Normal operation mode. No loopback selected */
#define LPUART_PDD_LOOP_MODE_LOCAL_LOOP   0x80U  /**< Local loopback mode. Receiver input internally connected to transmitter output */
#define LPUART_PDD_LOOP_MODE_RX_TO_TX_PIN 0xA0U  /**< Receiver input connected to TXD pin (single wire operation) */

/* Wake-up condition constants. */
#define LPUART_PDD_BY_IDLE_LINE    0U            /**< Idle line wake-up */
#define LPUART_PDD_BY_ADDRESS_MARK 0x8U          /**< Address mark wake-up */

/* Idle line type constants. */
#define LPUART_PDD_AFTER_START_BIT 0U            /**< Idle character bit count starts after start bit. */
#define LPUART_PDD_AFTER_STOP_BIT  0x4U          /**< Idle character bit count starts after stop bit. */

/* Number of idle characters. */
#define LPUART_PDD_IDLE_1   0U                   /**< 1 idle character. */
#define LPUART_PDD_IDLE_2   0x100U               /**< 2 idle characters. */
#define LPUART_PDD_IDLE_4   0x200U               /**< 4 idle characters. */
#define LPUART_PDD_IDLE_8   0x300U               /**< 8 idle characters. */
#define LPUART_PDD_IDLE_16  0x400U               /**< 16 idle characters. */
#define LPUART_PDD_IDLE_32  0x500U               /**< 32 idle characters. */
#define LPUART_PDD_IDLE_64  0x600U               /**< 64 idle characters. */
#define LPUART_PDD_IDLE_128 0x700U               /**< 128 idle characters. */

/* Parity types */
#define LPUART_PDD_PARITY_NONE 0U                /**< No parity */
#define LPUART_PDD_PARITY_EVEN 0x2U              /**< Even parity */
#define LPUART_PDD_PARITY_ODD  0x3U              /**< Even parity */

/* Receiver power states. */
#define LPUART_PDD_POWER_NORMAL  0U              /**< Normal operation. */
#define LPUART_PDD_POWER_STANDBY 0x20000U        /**< Standby mode (waiting for a wakeup condition). */

/* Transmitter pin data direction (in single-wire mode) constants */
#define LPUART_PDD_TX_PIN_IS_AN_INPUT  0U        /**< TxD pin is an input in single wire mode */
#define LPUART_PDD_TX_PIN_IS_AN_OUTPUT 0x20000000U /**< TxD pin is an output in single wire mode */

/* Parity types */
#define LPUART_PDD_TX_NARROW_PULSE_1_DIV_OSR 0U  /**< 1/OSR narrow pulse */
#define LPUART_PDD_TX_NARROW_PULSE_2_DIV_OSR 0x10000U /**< 2/OSR narrow pulse */
#define LPUART_PDD_TX_NARROW_PULSE_3_DIV_OSR 0x20000U /**< 3/OSR narrow pulse */
#define LPUART_PDD_TX_NARROW_PULSE_4_DIV_OSR 0x30000U /**< 4/OSR narrow pulse */

/* Clear-to-send transmitter sampling constants */
#define LPUART_PDD_AT_START   0U                 /**< CTS input is sampled at the start of each character. */
#define LPUART_PDD_IN_TX_IDLE 0x10U              /**< CTS input is sampled when the transmitter is idle. */

/* Clear-to-send transmitter sampling constants */
#define LPUART_PDD_CTS_PIN                  0U   /**< CTS input is the LPUART_CTS pin. */
#define LPUART_PDD_INVERTED_RX_MATCH_RESULT 0x20U /**< CTS input is the inverted Receiver Match result. */

/* Request-to-send transmitter polarity constants */
#define LPUART_PDD_RTS_ACTIVE_LOW  0U            /**< Transmitter RTS is active low */
#define LPUART_PDD_RTS_ACTIVE_HIGH 0x4U          /**< Transmitter RTS is active high */

/* UART data shift order constants */
#define LPUART_PDD_LSB_FIRST 0x20000000U         /**< Data transfers start with least significant bit */
#define LPUART_PDD_MSB_FIRST 0U                  /**< Data transfers start with most significant bit */

/* Break transmit character length constants */
#define LPUART_PDD_BREAK_CHARACTER_10_11_12_BITS 0U /**< Break character is 10, 11, or 12 bits long */
#define LPUART_PDD_BREAK_CHARACTER_13_14_BITS    0x4000000U /**< Break character is 13 or 14 bits long */


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
 * @remarks The macro accesses the following registers: LPUART0_BAUD.
 * @par Example:
 *      @code
 *      LPUART_PDD_EnableMatchAddress1Mode(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define LPUART_PDD_EnableMatchAddress1Mode(PeripheralBase, State) ( \
    LPUART_BAUD_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       LPUART_BAUD_REG(PeripheralBase)) & ( \
       (uint32_t)(~(uint32_t)LPUART_BAUD_MAEN1_MASK)))) | ( \
      (uint32_t)((uint32_t)(State) << LPUART_BAUD_MAEN1_SHIFT))) \
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
 * @remarks The macro accesses the following registers: LPUART0_BAUD.
 * @par Example:
 *      @code
 *      LPUART_PDD_EnableMatchAddress2Mode(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define LPUART_PDD_EnableMatchAddress2Mode(PeripheralBase, State) ( \
    LPUART_BAUD_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       LPUART_BAUD_REG(PeripheralBase)) & ( \
       (uint32_t)(~(uint32_t)LPUART_BAUD_MAEN2_MASK)))) | ( \
      (uint32_t)((uint32_t)(State) << LPUART_BAUD_MAEN2_SHIFT))) \
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
 * @remarks The macro accesses the following registers: LPUART0_BAUD.
 * @par Example:
 *      @code
 *      LPUART_PDD_SetPositionOfParityBit(<peripheral>_BASE_PTR,
 *      LPUART_PDD_PARITY_BIT_POSITION_9);
 *      @endcode
 */
#define LPUART_PDD_SetPositionOfParityBit(PeripheralBase, Position) ( \
    LPUART_BAUD_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(LPUART_BAUD_REG(PeripheralBase) & (uint32_t)(~(uint32_t)LPUART_BAUD_M10_MASK))) | ( \
      (uint32_t)(Position))) \
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
 * @remarks The macro accesses the following registers: LPUART0_BAUD.
 * @par Example:
 *      @code
 *      LPUART_PDD_SetOversamplingRatio(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define LPUART_PDD_SetOversamplingRatio(PeripheralBase, Ratio) ( \
    LPUART_BAUD_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(LPUART_BAUD_REG(PeripheralBase) & (uint32_t)(~(uint32_t)LPUART_BAUD_OSR_MASK))) | ( \
      (uint32_t)((uint32_t)(Ratio) << LPUART_BAUD_OSR_SHIFT))) \
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
 * @remarks The macro accesses the following registers: LPUART0_BAUD.
 * @par Example:
 *      @code
 *      LPUART_PDD_EnableSamplingOnBothEdges(<peripheral>_BASE_PTR,
 *      PDD_DISABLE);
 *      @endcode
 */
#define LPUART_PDD_EnableSamplingOnBothEdges(PeripheralBase, State) ( \
    LPUART_BAUD_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       LPUART_BAUD_REG(PeripheralBase)) & ( \
       (uint32_t)(~(uint32_t)LPUART_BAUD_BOTHEDGE_MASK)))) | ( \
      (uint32_t)((uint32_t)(State) << LPUART_BAUD_BOTHEDGE_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SelectMatchConfiguration
   ---------------------------------------------------------------------------- */

/**
 * @brief Selects one of the match configuration.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param MatchType Type of the match operation. This parameter is of "Type of
 *        the match operation." type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: LPUART0_BAUD.
 * @par Example:
 *      @code
 *      LPUART_PDD_SelectMatchConfiguration(<peripheral>_BASE_PTR,
 *      LPUART_PDD_ADRESS_MATCH);
 *      @endcode
 */
#define LPUART_PDD_SelectMatchConfiguration(PeripheralBase, MatchType) ( \
    LPUART_BAUD_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       LPUART_BAUD_REG(PeripheralBase)) & ( \
       (uint32_t)(~(uint32_t)LPUART_BAUD_MATCFG_MASK)))) | ( \
      (uint32_t)(MatchType))) \
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
 * @remarks The macro accesses the following registers: LPUART0_BAUD.
 * @par Example:
 *      @code
 *      LPUART_PDD_EnableTransmitDma(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define LPUART_PDD_EnableTransmitDma(PeripheralBase, State) ( \
    LPUART_BAUD_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       LPUART_BAUD_REG(PeripheralBase)) & ( \
       (uint32_t)(~(uint32_t)LPUART_BAUD_TDMAE_MASK)))) | ( \
      (uint32_t)((uint32_t)(State) << LPUART_BAUD_TDMAE_SHIFT))) \
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
 * @remarks The macro accesses the following registers: LPUART0_BAUD.
 * @par Example:
 *      @code
 *      LPUART_PDD_EnableReceiveDma(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define LPUART_PDD_EnableReceiveDma(PeripheralBase, State) ( \
    LPUART_BAUD_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       LPUART_BAUD_REG(PeripheralBase)) & ( \
       (uint32_t)(~(uint32_t)LPUART_BAUD_RDMAE_MASK)))) | ( \
      (uint32_t)((uint32_t)(State) << LPUART_BAUD_RDMAE_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- EnableLinBreakDetectDma
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables/disables a LIN break detect DMA request.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of LIN break detect DMA request. This parameter
 *        is of "Global enumeration used for specifying general enable/disable
 *        states (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: LPUART0_BAUD.
 * @par Example:
 *      @code
 *      LPUART_PDD_EnableLinBreakDetectDma(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define LPUART_PDD_EnableLinBreakDetectDma(PeripheralBase, State) ( \
    LPUART_BAUD_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       LPUART_BAUD_REG(PeripheralBase)) & ( \
       (uint32_t)(~(uint32_t)LPUART_BAUD_LBKDIE_MASK)))) | ( \
      (uint32_t)((uint32_t)(State) << LPUART_BAUD_LBKDIE_SHIFT))) \
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
 * @remarks The macro accesses the following registers: LPUART0_BAUD.
 * @par Example:
 *      @code
 *      LPUART_PDD_SetBaudRate(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define LPUART_PDD_SetBaudRate(PeripheralBase, BaudRate) ( \
    LPUART_BAUD_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(LPUART_BAUD_REG(PeripheralBase) & (uint32_t)(~(uint32_t)LPUART_BAUD_SBR_MASK))) | ( \
      (uint32_t)(BaudRate))) \
  )

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
 * @remarks The macro accesses the following registers: LPUART0_BAUD.
 * @par Example:
 *      @code
 *      LPUART_PDD_SetStopBitLength(<peripheral>_BASE_PTR,
 *      LPUART_PDD_STOP_BIT_LEN_1);
 *      @endcode
 */
#define LPUART_PDD_SetStopBitLength(PeripheralBase, Length) ( \
    LPUART_BAUD_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(LPUART_BAUD_REG(PeripheralBase) & (uint32_t)(~(uint32_t)LPUART_BAUD_SBNS_MASK))) | ( \
      (uint32_t)(Length))) \
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
 * @remarks The macro accesses the following registers: LPUART0_CTRL,
 *          LPUART0_BAUD (depending on the peripheral).
 * @par Example:
 *      @code
 *      LPUART_PDD_SetDataWidth(<peripheral>_BASE_PTR, LPUART_PDD_WIDTH_8);
 *      @endcode
 */
#define LPUART_PDD_SetDataWidth(PeripheralBase, Width) ( \
    ( \
     ((Width) == LPUART_PDD_WIDTH_8) ? ( \
      LPUART_CTRL_REG(PeripheralBase) &= \
       (uint32_t)(~(uint32_t)LPUART_CTRL_M_MASK)) : (((Width) == LPUART_PDD_WIDTH_9) ? ( \
      LPUART_CTRL_REG(PeripheralBase) |= \
       LPUART_CTRL_M_MASK) : ( \
      LPUART_CTRL_REG(PeripheralBase) |= \
       LPUART_CTRL_M_MASK) \
    )), \
    ( \
     ((Width) == LPUART_PDD_WIDTH_8) ? ( \
      LPUART_BAUD_REG(PeripheralBase) &= \
       (uint32_t)(~(uint32_t)LPUART_BAUD_M10_MASK)) : (((Width) == LPUART_PDD_WIDTH_9) ? ( \
      LPUART_BAUD_REG(PeripheralBase) &= \
       (uint32_t)(~(uint32_t)LPUART_BAUD_M10_MASK)) : ( \
      LPUART_BAUD_REG(PeripheralBase) |= \
       LPUART_BAUD_M10_MASK) \
    )) \
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
 * @remarks The macro accesses the following registers: LPUART0_CTRL.
 * @par Example:
 *      @code
 *      LPUART_PDD_SetLoopMode(<peripheral>_BASE_PTR,
 *      LPUART_PDD_LOOP_MODE_NORMAL);
 *      @endcode
 */
#define LPUART_PDD_SetLoopMode(PeripheralBase, LoopMode) ( \
    LPUART_CTRL_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       LPUART_CTRL_REG(PeripheralBase)) & ( \
       (uint32_t)(~(uint32_t)(LPUART_CTRL_LOOPS_MASK | LPUART_CTRL_RSRC_MASK))))) | ( \
      (uint32_t)(LoopMode))) \
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
 * @remarks The macro accesses the following registers: LPUART0_CTRL.
 * @par Example:
 *      @code
 *      LPUART_PDD_SetWakeupCondition(<peripheral>_BASE_PTR,
 *      LPUART_PDD_BY_IDLE_LINE);
 *      @endcode
 */
#define LPUART_PDD_SetWakeupCondition(PeripheralBase, Condition) ( \
    LPUART_CTRL_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(LPUART_CTRL_REG(PeripheralBase) & (uint32_t)(~(uint32_t)LPUART_CTRL_WAKE_MASK))) | ( \
      (uint32_t)(Condition))) \
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
 * @remarks The macro accesses the following registers: LPUART0_CTRL.
 * @par Example:
 *      @code
 *      LPUART_PDD_SelectIdleLineType(<peripheral>_BASE_PTR,
 *      LPUART_PDD_AFTER_START_BIT);
 *      @endcode
 */
#define LPUART_PDD_SelectIdleLineType(PeripheralBase, Type) ( \
    LPUART_CTRL_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(LPUART_CTRL_REG(PeripheralBase) & (uint32_t)(~(uint32_t)LPUART_CTRL_ILT_MASK))) | ( \
      (uint32_t)(Type))) \
  )

/* ----------------------------------------------------------------------------
   -- SelectIdleConfiguration
   ---------------------------------------------------------------------------- */

/**
 * @brief Configures the number of idle characters that must be received before
 * the IDLE flag is set.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param NumberOfIdleChars Number of idle characters. This parameter is of
 *        "Number of idle characters." type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: LPUART0_CTRL.
 * @par Example:
 *      @code
 *      LPUART_PDD_SelectIdleConfiguration(<peripheral>_BASE_PTR,
 *      LPUART_PDD_IDLE_1);
 *      @endcode
 */
#define LPUART_PDD_SelectIdleConfiguration(PeripheralBase, NumberOfIdleChars) ( \
    LPUART_CTRL_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       LPUART_CTRL_REG(PeripheralBase)) & ( \
       (uint32_t)(~(uint32_t)LPUART_CTRL_IDLECFG_MASK)))) | ( \
      (uint32_t)(NumberOfIdleChars))) \
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
 * @remarks The macro accesses the following registers: LPUART0_CTRL.
 * @par Example:
 *      @code
 *      LPUART_PDD_SetParity(<peripheral>_BASE_PTR, LPUART_PDD_PARITY_NONE);
 *      @endcode
 */
#define LPUART_PDD_SetParity(PeripheralBase, Parity) ( \
    LPUART_CTRL_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(LPUART_CTRL_REG(PeripheralBase) & (uint32_t)(~(uint32_t)0x3U))) | ( \
      (uint32_t)(Parity))) \
  )

/* ----------------------------------------------------------------------------
   -- ReadControl1Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads control register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: LPUART0_CTRL.
 * @par Example:
 *      @code
 *      uint32_t result = LPUART_PDD_ReadControl1Reg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define LPUART_PDD_ReadControl1Reg(PeripheralBase) ( \
    LPUART_CTRL_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteControl1Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes new value specified by the Value parameter into control
 * register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the control register. This parameter is a
 *        32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: LPUART0_CTRL.
 * @par Example:
 *      @code
 *      LPUART_PDD_WriteControl1Reg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define LPUART_PDD_WriteControl1Reg(PeripheralBase, Value) ( \
    LPUART_CTRL_REG(PeripheralBase) = \
     (uint32_t)(Value) \
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
 *        parameter is 32 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: LPUART0_CTRL.
 * @par Example:
 *      @code
 *      LPUART_PDD_EnableInterrupt(<peripheral>_BASE_PTR,
 *      LPUART_PDD_INTERRUPT_OVERRUN_ERROR);
 *      @endcode
 */
#define LPUART_PDD_EnableInterrupt(PeripheralBase, Mask) ( \
    LPUART_CTRL_REG(PeripheralBase) |= \
     (uint32_t)(Mask) \
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
 *        parameter is 32 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: LPUART0_CTRL.
 * @par Example:
 *      @code
 *      LPUART_PDD_DisableInterrupt(<peripheral>_BASE_PTR,
 *      LPUART_PDD_INTERRUPT_OVERRUN_ERROR);
 *      @endcode
 */
#define LPUART_PDD_DisableInterrupt(PeripheralBase, Mask) ( \
    LPUART_CTRL_REG(PeripheralBase) &= \
     (uint32_t)(~(uint32_t)(Mask)) \
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
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: LPUART0_CTRL.
 * @par Example:
 *      @code
 *      uint32_t result =
 *      LPUART_PDD_GetTxCompleteInterruptMask(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define LPUART_PDD_GetTxCompleteInterruptMask(PeripheralBase) ( \
    (uint32_t)(LPUART_CTRL_REG(PeripheralBase) & LPUART_CTRL_TCIE_MASK) \
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
 * @remarks The macro accesses the following registers: LPUART0_CTRL.
 * @par Example:
 *      @code
 *      LPUART_PDD_EnableTransmitter(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define LPUART_PDD_EnableTransmitter(PeripheralBase, State) ( \
    LPUART_CTRL_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(LPUART_CTRL_REG(PeripheralBase) & (uint32_t)(~(uint32_t)LPUART_CTRL_TE_MASK))) | ( \
      (uint32_t)((uint32_t)(State) << LPUART_CTRL_TE_SHIFT))) \
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
 * @remarks The macro accesses the following registers: LPUART0_CTRL.
 * @par Example:
 *      @code
 *      LPUART_PDD_EnableReceiver(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define LPUART_PDD_EnableReceiver(PeripheralBase, State) ( \
    LPUART_CTRL_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(LPUART_CTRL_REG(PeripheralBase) & (uint32_t)(~(uint32_t)LPUART_CTRL_RE_MASK))) | ( \
      (uint32_t)((uint32_t)(State) << LPUART_CTRL_RE_SHIFT))) \
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
 * @remarks The macro accesses the following registers: LPUART0_CTRL.
 * @par Example:
 *      @code
 *      LPUART_PDD_SetReceiverPowerState(<peripheral>_BASE_PTR,
 *      LPUART_PDD_POWER_NORMAL);
 *      @endcode
 */
#define LPUART_PDD_SetReceiverPowerState(PeripheralBase, State) ( \
    LPUART_CTRL_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(LPUART_CTRL_REG(PeripheralBase) & (uint32_t)(~(uint32_t)LPUART_CTRL_RWU_MASK))) | ( \
      (uint32_t)(State))) \
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
 * @remarks The macro accesses the following registers: LPUART0_CTRL.
 * @par Example:
 *      @code
 *      LPUART_PDD_SetBreak(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define LPUART_PDD_SetBreak(PeripheralBase) ( \
    LPUART_CTRL_REG(PeripheralBase) |= \
     LPUART_CTRL_SBK_MASK \
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
 * @remarks The macro accesses the following registers: LPUART0_CTRL.
 * @par Example:
 *      @code
 *      LPUART_PDD_ClearBreak(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define LPUART_PDD_ClearBreak(PeripheralBase) ( \
    LPUART_CTRL_REG(PeripheralBase) &= \
     (uint32_t)(~(uint32_t)LPUART_CTRL_SBK_MASK) \
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
 * @remarks The macro accesses the following registers: LPUART0_CTRL.
 * @par Example:
 *      @code
 *      LPUART_PDD_SendBreak(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define LPUART_PDD_SendBreak(PeripheralBase) ( \
    (LPUART_CTRL_REG(PeripheralBase) |= \
     LPUART_CTRL_SBK_MASK), \
    (LPUART_CTRL_REG(PeripheralBase) &= \
     (uint32_t)(~(uint32_t)LPUART_CTRL_SBK_MASK)) \
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
 * @remarks The macro accesses the following registers: LPUART0_CTRL.
 * @par Example:
 *      @code
 *      LPUART_PDD_SetTxPinDataDirection(<peripheral>_BASE_PTR,
 *      LPUART_PDD_TX_PIN_IS_AN_INPUT);
 *      @endcode
 */
#define LPUART_PDD_SetTxPinDataDirection(PeripheralBase, Direction) ( \
    LPUART_CTRL_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       LPUART_CTRL_REG(PeripheralBase)) & ( \
       (uint32_t)(~(uint32_t)LPUART_CTRL_TXDIR_MASK)))) | ( \
      (uint32_t)(Direction))) \
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
 * @remarks The macro accesses the following registers: LPUART0_CTRL.
 * @par Example:
 *      @code
 *      LPUART_PDD_EnableTransmitDataInversion(<peripheral>_BASE_PTR,
 *      PDD_DISABLE);
 *      @endcode
 */
#define LPUART_PDD_EnableTransmitDataInversion(PeripheralBase, State) ( \
    LPUART_CTRL_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       LPUART_CTRL_REG(PeripheralBase)) & ( \
       (uint32_t)(~(uint32_t)LPUART_CTRL_TXINV_MASK)))) | ( \
      (uint32_t)((uint32_t)(State) << LPUART_CTRL_TXINV_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- ReadControlReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads control register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: LPUART0_CTRL.
 * @par Example:
 *      @code
 *      uint32_t result = LPUART_PDD_ReadControlReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define LPUART_PDD_ReadControlReg(PeripheralBase) ( \
    LPUART_CTRL_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteControlReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes new value specified by the Value parameter into control
 * register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the control 2 register. This parameter is
 *        a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: LPUART0_CTRL.
 * @par Example:
 *      @code
 *      LPUART_PDD_WriteControlReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define LPUART_PDD_WriteControlReg(PeripheralBase, Value) ( \
    LPUART_CTRL_REG(PeripheralBase) = \
     (uint32_t)(Value) \
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
 * @remarks The macro accesses the following registers: LPUART0_DATA.
 * @par Example:
 *      @code
 *      LPUART_PDD_PutChar8(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define LPUART_PDD_PutChar8(PeripheralBase, Char) ( \
    LPUART_DATA_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(LPUART_DATA_REG(PeripheralBase) & (uint32_t)(~(uint32_t)0xFFU))) | ( \
      (uint32_t)(Char))) \
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
 * @remarks The macro accesses the following registers: LPUART0_DATA.
 * @par Example:
 *      @code
 *      LPUART_PDD_PutChar9(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define LPUART_PDD_PutChar9(PeripheralBase, Char) ( \
    LPUART_DATA_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(LPUART_DATA_REG(PeripheralBase) & (uint32_t)(~(uint32_t)0x1FFU))) | ( \
      (uint32_t)(Char))) \
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
 * @remarks The macro accesses the following registers: LPUART0_DATA.
 * @par Example:
 *      @code
 *      LPUART_PDD_PutChar10(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define LPUART_PDD_PutChar10(PeripheralBase, Char) ( \
    LPUART_DATA_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(LPUART_DATA_REG(PeripheralBase) & (uint32_t)(~(uint32_t)0x3FFU))) | ( \
      (uint32_t)(Char))) \
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
 * @remarks The macro accesses the following registers: LPUART0_DATA.
 * @par Example:
 *      @code
 *      uint8_t result = LPUART_PDD_GetChar8(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define LPUART_PDD_GetChar8(PeripheralBase) ( \
    (uint8_t)(LPUART_DATA_REG(PeripheralBase) & 0xFFU) \
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
 * @remarks The macro accesses the following registers: LPUART0_DATA.
 * @par Example:
 *      @code
 *      uint16_t result = LPUART_PDD_GetChar9Bit(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define LPUART_PDD_GetChar9Bit(PeripheralBase) ( \
    (uint16_t)(( \
     (uint32_t)(LPUART_DATA_REG(PeripheralBase) & LPUART_DATA_R8T8_MASK)) & ( \
     (uint16_t)(~(uint16_t)0xFFU))) \
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
 * @remarks The macro accesses the following registers: LPUART0_CTRL.
 * @par Example:
 *      @code
 *      uint16_t result = LPUART_PDD_GetChar9To10thBit(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define LPUART_PDD_GetChar9To10thBit(PeripheralBase) ( \
    (uint16_t)(( \
     (uint32_t)(( \
      (uint32_t)(LPUART_CTRL_R8T9_MASK | LPUART_CTRL_R9T8_MASK)) & ( \
      LPUART_CTRL_REG(PeripheralBase)))) >> ( \
     22U)) \
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
 * @remarks The macro accesses the following registers: LPUART0_DATA.
 * @par Example:
 *      @code
 *      uint32_t result = LPUART_PDD_ReadDataReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define LPUART_PDD_ReadDataReg(PeripheralBase) ( \
    LPUART_DATA_REG(PeripheralBase) \
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
 *        32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: LPUART0_DATA.
 * @par Example:
 *      @code
 *      LPUART_PDD_WriteDataReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define LPUART_PDD_WriteDataReg(PeripheralBase, Value) ( \
    LPUART_DATA_REG(PeripheralBase) = \
     (uint32_t)(Value) \
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
 * @return Returns a 10-bit value. The value is cast to "uint16_t".
 * @remarks The macro accesses the following registers: LPUART0_MATCH.
 * @par Example:
 *      @code
 *      uint16_t result =
 *      LPUART_PDD_GetMatchAddress1Value(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define LPUART_PDD_GetMatchAddress1Value(PeripheralBase) ( \
    (uint16_t)(LPUART_MATCH_REG(PeripheralBase) & LPUART_MATCH_MA1_MASK) \
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
 * @param Address Match address 1 value. This parameter is a 10-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: LPUART0_MATCH.
 * @par Example:
 *      @code
 *      LPUART_PDD_SetMatchAddress1Value(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define LPUART_PDD_SetMatchAddress1Value(PeripheralBase, Address) ( \
    LPUART_MATCH_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       LPUART_MATCH_REG(PeripheralBase)) & ( \
       (uint32_t)(~(uint32_t)LPUART_MATCH_MA1_MASK)))) | ( \
      (uint32_t)(Address))) \
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
 * @return Returns a 10-bit value. The value is cast to "uint16_t".
 * @remarks The macro accesses the following registers: LPUART0_MATCH.
 * @par Example:
 *      @code
 *      uint16_t result =
 *      LPUART_PDD_GetMatchAddress2Value(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define LPUART_PDD_GetMatchAddress2Value(PeripheralBase) ( \
    (uint16_t)(( \
     (uint32_t)(LPUART_MATCH_REG(PeripheralBase) & LPUART_MATCH_MA2_MASK)) >> ( \
     LPUART_MATCH_MA2_SHIFT)) \
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
 * @param Address Match address 2 value. This parameter is a 10-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: LPUART0_MATCH.
 * @par Example:
 *      @code
 *      LPUART_PDD_SetMatchAddress2Value(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define LPUART_PDD_SetMatchAddress2Value(PeripheralBase, Address) ( \
    LPUART_MATCH_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       LPUART_MATCH_REG(PeripheralBase)) & ( \
       (uint32_t)(~(uint32_t)LPUART_MATCH_MA2_MASK)))) | ( \
      (uint32_t)((uint32_t)(Address) << LPUART_MATCH_MA2_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- ReadMatchAddress
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads match address register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: LPUART0_MATCH.
 * @par Example:
 *      @code
 *      uint32_t result = LPUART_PDD_ReadMatchAddress(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define LPUART_PDD_ReadMatchAddress(PeripheralBase) ( \
    LPUART_MATCH_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteMatchAddressReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes data specified by the Value parameter into match address
 * register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the match address register. This
 *        parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: LPUART0_MATCH.
 * @par Example:
 *      @code
 *      LPUART_PDD_WriteMatchAddressReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define LPUART_PDD_WriteMatchAddressReg(PeripheralBase, Value) ( \
    LPUART_MATCH_REG(PeripheralBase) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- EnableInfraredModulation
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables/disables infrared modulation.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of infrared modulation. This parameter is of
 *        "Global enumeration used for specifying general enable/disable states
 *        (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: LPUART0_MODIR.
 * @par Example:
 *      @code
 *      LPUART_PDD_EnableInfraredModulation(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define LPUART_PDD_EnableInfraredModulation(PeripheralBase, State) ( \
    LPUART_MODIR_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       LPUART_MODIR_REG(PeripheralBase)) & ( \
       (uint32_t)(~(uint32_t)LPUART_MODIR_IREN_MASK)))) | ( \
      (uint32_t)((uint32_t)(State) << LPUART_MODIR_IREN_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SetTransmitterNarrowPulse
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets a transmitter narrow pulse.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Pulse narrow pulse. This parameter is of "Parity types" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: LPUART0_MODIR.
 * @par Example:
 *      @code
 *      LPUART_PDD_SetTransmitterNarrowPulse(<peripheral>_BASE_PTR,
 *      LPUART_PDD_TX_NARROW_PULSE_1_DIV_OSR);
 *      @endcode
 */
#define LPUART_PDD_SetTransmitterNarrowPulse(PeripheralBase, Pulse) ( \
    LPUART_MODIR_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       LPUART_MODIR_REG(PeripheralBase)) & ( \
       (uint32_t)(~(uint32_t)LPUART_MODIR_TNP_MASK)))) | ( \
      (uint32_t)(Pulse))) \
  )

/* ----------------------------------------------------------------------------
   -- SetTransmitterClearToSendSampling
   ---------------------------------------------------------------------------- */

/**
 * @brief Set transmitter clear-to-send sampling point.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Point Clear-to-send transmitter sampling point selection. This
 *        parameter is of "Clear-to-send transmitter sampling constants" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: LPUART0_MODIR.
 * @par Example:
 *      @code
 *      LPUART_PDD_SetTransmitterClearToSendSampling(<peripheral>_BASE_PTR,
 *      LPUART_PDD_AT_START);
 *      @endcode
 */
#define LPUART_PDD_SetTransmitterClearToSendSampling(PeripheralBase, Point) ( \
    LPUART_MODIR_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       LPUART_MODIR_REG(PeripheralBase)) & ( \
       (uint32_t)(~(uint32_t)LPUART_MODIR_TXCTSC_MASK)))) | ( \
      (uint32_t)(Point))) \
  )

/* ----------------------------------------------------------------------------
   -- SetTransmitterClearToSendSource
   ---------------------------------------------------------------------------- */

/**
 * @brief Set transmitter clear-to-send source.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Source Clear-to-send transmitter sampling point selection. This
 *        parameter is of "Clear-to-send transmitter sampling constants" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: LPUART0_MODIR.
 * @par Example:
 *      @code
 *      LPUART_PDD_SetTransmitterClearToSendSource(<peripheral>_BASE_PTR,
 *      LPUART_PDD_CTS_PIN);
 *      @endcode
 */
#define LPUART_PDD_SetTransmitterClearToSendSource(PeripheralBase, Source) ( \
    LPUART_MODIR_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       LPUART_MODIR_REG(PeripheralBase)) & ( \
       (uint32_t)(~(uint32_t)LPUART_MODIR_TXCTSSRC_MASK)))) | ( \
      (uint32_t)(Source))) \
  )

/* ----------------------------------------------------------------------------
   -- EnableReceiverRequestToSend
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables/disables receiver request-to-send, it allows the RTS output to
 * control the CTS input of the transmitting device to prevent receiver overrun.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of receiver request-to-send. This parameter is
 *        of "Global enumeration used for specifying general enable/disable states
 *        (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: LPUART0_MODIR.
 * @par Example:
 *      @code
 *      LPUART_PDD_EnableReceiverRequestToSend(<peripheral>_BASE_PTR,
 *      PDD_DISABLE);
 *      @endcode
 */
#define LPUART_PDD_EnableReceiverRequestToSend(PeripheralBase, State) ( \
    LPUART_MODIR_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       LPUART_MODIR_REG(PeripheralBase)) & ( \
       (uint32_t)(~(uint32_t)LPUART_MODIR_RXRTSE_MASK)))) | ( \
      (uint32_t)((uint32_t)(State) << LPUART_MODIR_RXRTSE_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SetTransmitterRequestToSendPolarity
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the polarity of the transmitter RTS.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Polarity Request-to-send transmitter polarity. This parameter is of
 *        "Request-to-send transmitter polarity constants" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: LPUART0_MODIR.
 * @par Example:
 *      @code
 *      LPUART_PDD_SetTransmitterRequestToSendPolarity(<peripheral>_BASE_PTR,
 *      LPUART_PDD_RTS_ACTIVE_LOW);
 *      @endcode
 */
#define LPUART_PDD_SetTransmitterRequestToSendPolarity(PeripheralBase, Polarity) ( \
    LPUART_MODIR_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       LPUART_MODIR_REG(PeripheralBase)) & ( \
       (uint32_t)(~(uint32_t)LPUART_MODIR_TXRTSPOL_MASK)))) | ( \
      (uint32_t)(Polarity))) \
  )

/* ----------------------------------------------------------------------------
   -- EnableTransmitterRequestToSend
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables/disables transmitter request-to-send, it allows control RTS
 * before and after a transmission.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of transmitter request-to-send. This parameter
 *        is of "Global enumeration used for specifying general enable/disable
 *        states (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: LPUART0_MODIR.
 * @par Example:
 *      @code
 *      LPUART_PDD_EnableTransmitterRequestToSend(<peripheral>_BASE_PTR,
 *      PDD_DISABLE);
 *      @endcode
 */
#define LPUART_PDD_EnableTransmitterRequestToSend(PeripheralBase, State) ( \
    LPUART_MODIR_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       LPUART_MODIR_REG(PeripheralBase)) & ( \
       (uint32_t)(~(uint32_t)LPUART_MODIR_TXRTSE_MASK)))) | ( \
      (uint32_t)((uint32_t)(State) << LPUART_MODIR_TXRTSE_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- EnableTransmitterClearToSend
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables/disables transmitter clear-to-send operation.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of transmitter clear-to-send operation. This
 *        parameter is of "Global enumeration used for specifying general
 *        enable/disable states (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: LPUART0_MODIR.
 * @par Example:
 *      @code
 *      LPUART_PDD_EnableTransmitterClearToSend(<peripheral>_BASE_PTR,
 *      PDD_DISABLE);
 *      @endcode
 */
#define LPUART_PDD_EnableTransmitterClearToSend(PeripheralBase, State) ( \
    LPUART_MODIR_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       LPUART_MODIR_REG(PeripheralBase)) & ( \
       (uint32_t)(~(uint32_t)LPUART_MODIR_TXCTSE_MASK)))) | ( \
      (uint32_t)(State))) \
  )

/* ----------------------------------------------------------------------------
   -- ReadModem_InfraredReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads modem and infrared control register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: LPUART0_MODIR.
 * @par Example:
 *      @code
 *      uint32_t result =
 *      LPUART_PDD_ReadModem_InfraredReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define LPUART_PDD_ReadModem_InfraredReg(PeripheralBase) ( \
    LPUART_MODIR_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteModem_InfraredReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes data specified by the Value parameter into modem and infrared
 * control register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the modem and infrared control register.
 *        This parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: LPUART0_MODIR.
 * @par Example:
 *      @code
 *      LPUART_PDD_WriteModem_InfraredReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define LPUART_PDD_WriteModem_InfraredReg(PeripheralBase, Value) ( \
    LPUART_MODIR_REG(PeripheralBase) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadStatusFlags
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the value of the status register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: LPUART0_STAT.
 * @par Example:
 *      @code
 *      uint32_t result = LPUART_PDD_ReadStatusFlags(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define LPUART_PDD_ReadStatusFlags(PeripheralBase) ( \
    LPUART_STAT_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- ClearStatusFlags
   ---------------------------------------------------------------------------- */

/**
 * @brief Clears the flags of the status register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mask Mask of interrupt requests. This parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: LPUART0_STAT.
 * @par Example:
 *      @code
 *      LPUART_PDD_ClearStatusFlags(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define LPUART_PDD_ClearStatusFlags(PeripheralBase, Mask) ( \
    LPUART_STAT_REG(PeripheralBase) |= \
     (uint32_t)(Mask) \
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
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: LPUART0_STAT.
 * @par Example:
 *      @code
 *      uint32_t result =
 *      LPUART_PDD_ReadInterruptStatusReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define LPUART_PDD_ReadInterruptStatusReg(PeripheralBase) ( \
    LPUART_STAT_REG(PeripheralBase) \
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
 * @param Mask Mask of the flags to be cleared. This parameter is a 32-bit value.
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: LPUART0_STAT.
 * @par Example:
 *      @code
 *      uint32_t result = LPUART_PDD_ClearInterruptFlags(<peripheral>_BASE_PTR,
 *      1);
 *      @endcode
 */
#define LPUART_PDD_ClearInterruptFlags(PeripheralBase, Mask) ( \
    LPUART_STAT_REG(PeripheralBase) = \
     (uint32_t)(Mask) \
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
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: LPUART0_STAT.
 * @par Example:
 *      @code
 *      uint32_t result = LPUART_PDD_GetBreak(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define LPUART_PDD_GetBreak(PeripheralBase) ( \
    (( \
      (uint32_t)(( \
       LPUART_STAT_REG(PeripheralBase)) & ( \
       (uint32_t)(LPUART_STAT_FE_MASK | LPUART_STAT_RDRF_MASK)))) == ( \
      (uint32_t)(LPUART_STAT_FE_MASK | LPUART_STAT_RDRF_MASK))) ? ( \
      0x1U) : ( \
      0U) \
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
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: LPUART0_STAT.
 * @par Example:
 *      @code
 *      uint32_t result = LPUART_PDD_GetTxCompleteStatus(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define LPUART_PDD_GetTxCompleteStatus(PeripheralBase) ( \
    (uint32_t)(LPUART_STAT_REG(PeripheralBase) & LPUART_STAT_TC_MASK) \
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
 * @remarks The macro accesses the following registers: LPUART0_STAT.
 * @par Example:
 *      @code
 *      LPUART_PDD_SetDataShiftOrder(<peripheral>_BASE_PTR,
 *      LPUART_PDD_LSB_FIRST);
 *      @endcode
 */
#define LPUART_PDD_SetDataShiftOrder(PeripheralBase, Order) ( \
    LPUART_STAT_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       LPUART_STAT_REG(PeripheralBase)) & (( \
       (uint32_t)(~(uint32_t)LPUART_STAT_MSBF_MASK)) & (( \
       (uint32_t)(~(uint32_t)LPUART_STAT_MA2F_MASK)) & (( \
       (uint32_t)(~(uint32_t)LPUART_STAT_MA1F_MASK)) & (( \
       (uint32_t)(~(uint32_t)LPUART_STAT_PF_MASK)) & (( \
       (uint32_t)(~(uint32_t)LPUART_STAT_FE_MASK)) & (( \
       (uint32_t)(~(uint32_t)LPUART_STAT_NF_MASK)) & (( \
       (uint32_t)(~(uint32_t)LPUART_STAT_OR_MASK)) & (( \
       (uint32_t)(~(uint32_t)LPUART_STAT_IDLE_MASK)) & (( \
       (uint32_t)(~(uint32_t)LPUART_STAT_RXEDGIF_MASK)) & ( \
       (uint32_t)(~(uint32_t)LPUART_STAT_LBKDIF_MASK))))))))))))) | ( \
      (uint32_t)(Order))) \
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
 * @remarks The macro accesses the following registers: LPUART0_STAT.
 * @par Example:
 *      @code
 *      LPUART_PDD_EnableReceiveDataInversion(<peripheral>_BASE_PTR,
 *      PDD_DISABLE);
 *      @endcode
 */
#define LPUART_PDD_EnableReceiveDataInversion(PeripheralBase, State) ( \
    LPUART_STAT_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       LPUART_STAT_REG(PeripheralBase)) & (( \
       (uint32_t)(~(uint32_t)LPUART_STAT_RXINV_MASK)) & (( \
       (uint32_t)(~(uint32_t)LPUART_STAT_MA2F_MASK)) & (( \
       (uint32_t)(~(uint32_t)LPUART_STAT_MA1F_MASK)) & (( \
       (uint32_t)(~(uint32_t)LPUART_STAT_PF_MASK)) & (( \
       (uint32_t)(~(uint32_t)LPUART_STAT_FE_MASK)) & (( \
       (uint32_t)(~(uint32_t)LPUART_STAT_NF_MASK)) & (( \
       (uint32_t)(~(uint32_t)LPUART_STAT_OR_MASK)) & (( \
       (uint32_t)(~(uint32_t)LPUART_STAT_IDLE_MASK)) & (( \
       (uint32_t)(~(uint32_t)LPUART_STAT_RXEDGIF_MASK)) & ( \
       (uint32_t)(~(uint32_t)LPUART_STAT_LBKDIF_MASK))))))))))))) | ( \
      (uint32_t)((uint32_t)(State) << LPUART_STAT_RXINV_SHIFT))) \
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
 * @remarks The macro accesses the following registers: LPUART0_STAT.
 * @par Example:
 *      @code
 *      LPUART_PDD_EnableReceiveWakeupIdleDetect(<peripheral>_BASE_PTR,
 *      PDD_DISABLE);
 *      @endcode
 */
#define LPUART_PDD_EnableReceiveWakeupIdleDetect(PeripheralBase, State) ( \
    LPUART_STAT_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       LPUART_STAT_REG(PeripheralBase)) & (( \
       (uint32_t)(~(uint32_t)LPUART_STAT_RWUID_MASK)) & (( \
       (uint32_t)(~(uint32_t)LPUART_STAT_MA2F_MASK)) & (( \
       (uint32_t)(~(uint32_t)LPUART_STAT_MA1F_MASK)) & (( \
       (uint32_t)(~(uint32_t)LPUART_STAT_PF_MASK)) & (( \
       (uint32_t)(~(uint32_t)LPUART_STAT_FE_MASK)) & (( \
       (uint32_t)(~(uint32_t)LPUART_STAT_NF_MASK)) & (( \
       (uint32_t)(~(uint32_t)LPUART_STAT_OR_MASK)) & (( \
       (uint32_t)(~(uint32_t)LPUART_STAT_IDLE_MASK)) & (( \
       (uint32_t)(~(uint32_t)LPUART_STAT_RXEDGIF_MASK)) & ( \
       (uint32_t)(~(uint32_t)LPUART_STAT_LBKDIF_MASK))))))))))))) | ( \
      (uint32_t)((uint32_t)(State) << LPUART_STAT_RWUID_SHIFT))) \
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
 * @remarks The macro accesses the following registers: LPUART0_STAT.
 * @par Example:
 *      @code
 *      LPUART_PDD_SetBreakLength(<peripheral>_BASE_PTR,
 *      LPUART_PDD_BREAK_CHARACTER_10_11_12_BITS);
 *      @endcode
 */
#define LPUART_PDD_SetBreakLength(PeripheralBase, Length) ( \
    LPUART_STAT_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       LPUART_STAT_REG(PeripheralBase)) & (( \
       (uint32_t)(~(uint32_t)LPUART_STAT_BRK13_MASK)) & (( \
       (uint32_t)(~(uint32_t)LPUART_STAT_MA2F_MASK)) & (( \
       (uint32_t)(~(uint32_t)LPUART_STAT_MA1F_MASK)) & (( \
       (uint32_t)(~(uint32_t)LPUART_STAT_PF_MASK)) & (( \
       (uint32_t)(~(uint32_t)LPUART_STAT_FE_MASK)) & (( \
       (uint32_t)(~(uint32_t)LPUART_STAT_NF_MASK)) & (( \
       (uint32_t)(~(uint32_t)LPUART_STAT_OR_MASK)) & (( \
       (uint32_t)(~(uint32_t)LPUART_STAT_IDLE_MASK)) & (( \
       (uint32_t)(~(uint32_t)LPUART_STAT_RXEDGIF_MASK)) & ( \
       (uint32_t)(~(uint32_t)LPUART_STAT_LBKDIF_MASK))))))))))))) | ( \
      (uint32_t)(Length))) \
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
 * @remarks The macro accesses the following registers: LPUART0_STAT.
 * @par Example:
 *      @code
 *      LPUART_PDD_EnableLinBreakLongerCharacterDetection(<peripheral>_BASE_PTR,
 *      PDD_DISABLE);
 *      @endcode
 */
#define LPUART_PDD_EnableLinBreakLongerCharacterDetection(PeripheralBase, State) ( \
    LPUART_STAT_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       LPUART_STAT_REG(PeripheralBase)) & (( \
       (uint32_t)(~(uint32_t)LPUART_STAT_LBKDE_MASK)) & (( \
       (uint32_t)(~(uint32_t)LPUART_STAT_MA2F_MASK)) & (( \
       (uint32_t)(~(uint32_t)LPUART_STAT_MA1F_MASK)) & (( \
       (uint32_t)(~(uint32_t)LPUART_STAT_PF_MASK)) & (( \
       (uint32_t)(~(uint32_t)LPUART_STAT_FE_MASK)) & (( \
       (uint32_t)(~(uint32_t)LPUART_STAT_NF_MASK)) & (( \
       (uint32_t)(~(uint32_t)LPUART_STAT_OR_MASK)) & (( \
       (uint32_t)(~(uint32_t)LPUART_STAT_IDLE_MASK)) & (( \
       (uint32_t)(~(uint32_t)LPUART_STAT_RXEDGIF_MASK)) & ( \
       (uint32_t)(~(uint32_t)LPUART_STAT_LBKDIF_MASK))))))))))))) | ( \
      (uint32_t)((uint32_t)(State) << LPUART_STAT_LBKDE_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- ReadStatusReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads status register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: LPUART0_STAT.
 * @par Example:
 *      @code
 *      uint32_t result = LPUART_PDD_ReadStatusReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define LPUART_PDD_ReadStatusReg(PeripheralBase) ( \
    LPUART_STAT_REG(PeripheralBase) \
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
 *        32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: LPUART0_STAT.
 * @par Example:
 *      @code
 *      LPUART_PDD_WriteStatusReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define LPUART_PDD_WriteStatusReg(PeripheralBase, Value) ( \
    LPUART_STAT_REG(PeripheralBase) = \
     (uint32_t)(Value) \
  )
#endif  /* #if defined(LPUART_PDD_H_) */

/* LPUART_PDD.h, eof. */
