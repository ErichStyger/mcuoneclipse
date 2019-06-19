/*
  PDD layer implementation for peripheral type MSCAN
  (C) 2013 Freescale, Inc. All rights reserved.

  This file is static and it is generated from API-Factory
*/

#if !defined(MSCAN_PDD_H_)
#define MSCAN_PDD_H_

/* ----------------------------------------------------------------------------
   -- Test if supported MCU is active
   ---------------------------------------------------------------------------- */

#if !defined(MCU_ACTIVE)
  // No MCU is active
  #error MSCAN PDD library: No derivative is active. Place proper #include with PDD memory map before including PDD library.
#elif \
      !defined(MCU_MKE06Z4) /* MSCAN */ && \
      !defined(MCU_SKEAZ1284) /* MSCAN */
  // Unsupported MCU is active
  #error MSCAN PDD library: Unsupported derivative is active.
#endif

#include "PDD_Types.h"

/* ----------------------------------------------------------------------------
   -- Method symbol definitions
   ---------------------------------------------------------------------------- */

/* Status flags constants. */
#define MSCAN_PDD_WAKEUP_REQUESTED_FLAG     MSCAN_CANRFLG_WUPIF_MASK /**< Wake-up Interrupt Flag */
#define MSCAN_PDD_ERROR_COUNTER_CHANGE_FLAG MSCAN_CANRFLG_CSCIF_MASK /**< MSCAN changed current CAN bus status */
#define MSCAN_PDD_RX_BUFFER_OVERRUN_FLAG    MSCAN_CANRFLG_OVRIF_MASK /**< A data overrun detected */
#define MSCAN_PDD_RX_BUFFER_FULL_FLAG       MSCAN_CANRFLG_RXF_MASK /**< The receiver FIFO is not empty */

/* Status flags constants. */
#define MSCAN_PDD_WAKEUP_REQUESTED_INT     MSCAN_CANRIER_WUPIE_MASK /**< Wake-up Interrupt Flag */
#define MSCAN_PDD_ERROR_COUNTER_CHANGE_INT MSCAN_CANRIER_CSCIE_MASK /**< MSCAN changed current CAN bus status */
#define MSCAN_PDD_RX_BUFFER_OVERRUN_INT    MSCAN_CANRIER_OVRIE_MASK /**< A data overrun detected */
#define MSCAN_PDD_RX_BUFFER_FULL_INT       MSCAN_CANRIER_RXFIE_MASK /**< The receiver FIFO is not empty */

/* Receiver active status constants. */
#define MSCAN_PDD_TRANSMITTING_OR_IDLE 0U        /**< MSCAN is transmitting or idle */
#define MSCAN_PDD_RECEIVING            0x40U     /**< MSCAN is receiving a message (including when arbitration is lost) */

/* MSCAN synchronized constants. */
#define MSCAN_PDD_NOT_SYNCHRONIZED 0U            /**< MSCAN is not synchronized to the CAN bus */
#define MSCAN_PDD_SYNCHRONIZED     0x10U         /**< MSCAN is synchronized to the CAN bus */

/* MSCAN Engine Clock Source constants (for SetClockSource macro). */
#define MSCAN_PDD_XTAL_CLOCK 0U                  /**< The MSCAN engine clock source is the oscillator clock */
#define MSCAN_PDD_BUS_CLOCK  0x40U               /**< The MSCAN engine clock source is the peripheral clock */

/* The synchronization jump width constants. */
#define MSCAN_PDD_SYNC_JUMP_WIDTH_1_TQ 0U        /**< Synchronization jump width 1 time quanta clock cycle */
#define MSCAN_PDD_SYNC_JUMP_WIDTH_2_TQ 0x1U      /**< Synchronization jump width 2 time quanta clock cycles */
#define MSCAN_PDD_SYNC_JUMP_WIDTH_3_TQ 0x2U      /**< Synchronization jump width 3 time quanta clock cycles */
#define MSCAN_PDD_SYNC_JUMP_WIDTH_4_TQ 0x3U      /**< Synchronization jump width 4 time quanta clock cycles */

/* Rx sampling mode constants (for SetBitSampling macro). */
#define MSCAN_PDD_ONE_SAMPLE    0U               /**< Just one sample is used to determine the bit value */
#define MSCAN_PDD_THREE_SAMPLES 0x80U            /**< Three samples are used to determine the value of the received bit */

/* Time segment 2 constants. */
#define MSCAN_PDD_TIME_SEGMENT2_1_TQ 0U          /**< Time segment2 1 time quanta clock cycle */
#define MSCAN_PDD_TIME_SEGMENT2_2_TQ 0x1U        /**< Time segment2 2 time quanta clock cycles */
#define MSCAN_PDD_TIME_SEGMENT2_3_TQ 0x2U        /**< Time segment2 3 time quanta clock cycles */
#define MSCAN_PDD_TIME_SEGMENT2_4_TQ 0x3U        /**< Time segment2 4 time quanta clock cycles */
#define MSCAN_PDD_TIME_SEGMENT2_5_TQ 0x4U        /**< Time segment2 5 time quanta clock cycles */
#define MSCAN_PDD_TIME_SEGMENT2_6_TQ 0x5U        /**< Time segment2 6 time quanta clock cycles */
#define MSCAN_PDD_TIME_SEGMENT2_7_TQ 0x6U        /**< Time segment2 7 time quanta clock cycles */
#define MSCAN_PDD_TIME_SEGMENT2_8_TQ 0x7U        /**< Time segment2 8 time quanta clock cycles */

/* Time segment 1 constants. */
#define MSCAN_PDD_TIME_SEGMENT1_1_TQ  0U         /**< Time segment1 1 time quanta clock cycle */
#define MSCAN_PDD_TIME_SEGMENT1_2_TQ  0x1U       /**< Time segment1 2 time quanta clock cycles */
#define MSCAN_PDD_TIME_SEGMENT1_3_TQ  0x2U       /**< Time segment1 3 time quanta clock cycles */
#define MSCAN_PDD_TIME_SEGMENT1_4_TQ  0x3U       /**< Time segment1 4 time quanta clock cycles */
#define MSCAN_PDD_TIME_SEGMENT1_5_TQ  0x4U       /**< Time segment1 5 time quanta clock cycles */
#define MSCAN_PDD_TIME_SEGMENT1_6_TQ  0x5U       /**< Time segment1 6 time quanta clock cycles */
#define MSCAN_PDD_TIME_SEGMENT1_7_TQ  0x6U       /**< Time segment1 7 time quanta clock cycles */
#define MSCAN_PDD_TIME_SEGMENT1_8_TQ  0x7U       /**< Time segment1 8 time quanta clock cycles */
#define MSCAN_PDD_TIME_SEGMENT1_9_TQ  0x8U       /**< Time segment1 9 time quanta clock cycles */
#define MSCAN_PDD_TIME_SEGMENT1_10_TQ 0x9U       /**< Time segment1 10 time quanta clock cycles */
#define MSCAN_PDD_TIME_SEGMENT1_11_TQ 0xAU       /**< Time segment1 11 time quanta clock cycles */
#define MSCAN_PDD_TIME_SEGMENT1_12_TQ 0xBU       /**< Time segment1 12 time quanta clock cycles */
#define MSCAN_PDD_TIME_SEGMENT1_13_TQ 0xCU       /**< Time segment1 13 time quanta clock cycles */
#define MSCAN_PDD_TIME_SEGMENT1_14_TQ 0xDU       /**< Time segment1 14 time quanta clock cycles */
#define MSCAN_PDD_TIME_SEGMENT1_15_TQ 0xEU       /**< Time segment1 15 time quanta clock cycles */
#define MSCAN_PDD_TIME_SEGMENT1_16_TQ 0xFU       /**< Time segment1 16 time quanta clock cycles */

/* Receiver status bits constants */
#define MSCAN_PDD_RX_OK      0U                  /**< Receiver ok */
#define MSCAN_PDD_RX_WARNING 0x10U               /**< Receiver warning. */
#define MSCAN_PDD_RX_ERROR   0x20U               /**< Receiver error */
#define MSCAN_PDD_RX_BUS_OFF 0x30U               /**< Receiver bus-off */

/* Transmitter status bits constants */
#define MSCAN_PDD_TX_OK      0U                  /**< Transmitter ok */
#define MSCAN_PDD_TX_WARNING 0x4U                /**< Transmitter warning */
#define MSCAN_PDD_TX_ERROR   0x8U                /**< Transmitter error */
#define MSCAN_PDD_TX_BUS_OFF 0xCU                /**< Transmitter bus-off */

/* Receiver status change constants. */
#define MSCAN_PDD_RX_STATUS_DISABLE_INT      0U  /**< Do not set status change flag caused by receiver state changes */
#define MSCAN_PDD_RX_BUS_OFF_INT             0x10U /**< Set status change flag only if the receiver enters or leaves bus-off state */
#define MSCAN_PDD_RX_TX_ERROR_OR_BUS_OFF_INT 0x20U /**< Set status change flag only if the receiver enters or leaves TxError or bus-off state */
#define MSCAN_PDD_RX_ALL_STATE_INT           0x30U /**< Set status change flag on all state changes */

/* Transmitter status change constants. */
#define MSCAN_PDD_TX_STATUS_DISABLE_INT      0U  /**< Do not set status change flag caused by transmitter state changes */
#define MSCAN_PDD_TX_BUS_OFF_INT             0x4U /**< Set status change flag only if the transmitter enters or leaves bus-off state */
#define MSCAN_PDD_TX_TX_ERROR_OR_BUS_OFF_INT 0x8U /**< Set status change flag only if the transmitter enters or leaves TxError or bus-off state */
#define MSCAN_PDD_TX_ALL_STATE_INT           0xCU /**< Set status change flag on all state changes */

/* Transmit message buffer flag mask constants. */
#define MSCAN_PDD_TX_MESSAGE_BUFFER_0   0x1U     /**< Transmitter message buffer 0 mask */
#define MSCAN_PDD_TX_MESSAGE_BUFFER_1   0x2U     /**< Transmitter message buffer 1 mask */
#define MSCAN_PDD_TX_MESSAGE_BUFFER_2   0x4U     /**< Transmitter message buffer 2 mask */
#define MSCAN_PDD_TX_MESSAGE_BUFFER_ALL 0x7U     /**< Transmitter all message buffers mask */

/* Transmit message buffer interrupt mask constants. */
#define MSCAN_PDD_TX_MESSAGE_BUFFER_0_INT   0x1U /**< Transmitter message buffer 0 mask */
#define MSCAN_PDD_TX_MESSAGE_BUFFER_1_INT   0x2U /**< Transmitter message buffer 1 mask */
#define MSCAN_PDD_TX_MESSAGE_BUFFER_2_INT   0x4U /**< Transmitter message buffer 2 mask */
#define MSCAN_PDD_TX_MESSAGE_BUFFER_ALL_INT 0x7U /**< Transmitter all message buffers mask */

/* Transmit message buffer abort constants. */
#define MSCAN_PDD_TX_MESSAGE_BUFFER_0_ABORT   0x1U /**< Transmitter message buffer 0 mask */
#define MSCAN_PDD_TX_MESSAGE_BUFFER_1_ABORT   0x2U /**< Transmitter message buffer 1 mask */
#define MSCAN_PDD_TX_MESSAGE_BUFFER_2_ABORT   0x4U /**< Transmitter message buffer 2 mask */
#define MSCAN_PDD_TX_MESSAGE_BUFFER_ALL_ABORT 0x7U /**< Transmitter all message buffers mask */

/* Transmit message buffer abort constants. */
#define MSCAN_PDD_TX_MESSAGE_BUFFER_0_ABORT_ACK   0x1U /**< Transmitter message buffer 0 mask */
#define MSCAN_PDD_TX_MESSAGE_BUFFER_1_ABORT_ACK   0x2U /**< Transmitter message buffer 1 mask */
#define MSCAN_PDD_TX_MESSAGE_BUFFER_2_ABORT_ACK   0x4U /**< Transmitter message buffer 2 mask */
#define MSCAN_PDD_TX_MESSAGE_BUFFER_ALL_ABORT_ACK 0x7U /**< Transmitter all message buffers mask */

/* Transmit message buffer select constants. */
#define MSCAN_PDD_TX_MESSAGE_BUFFER_0_SELECT 0x1U /**< Transmitter message buffer 0 mask */
#define MSCAN_PDD_TX_MESSAGE_BUFFER_1_SELECT 0x2U /**< Transmitter message buffer 1 mask */
#define MSCAN_PDD_TX_MESSAGE_BUFFER_2_SELECT 0x4U /**< Transmitter message buffer 2 mask */

/* Identifier acceptance filter constants. */
#define MSCAN_PDD_TWO_32BIT_ACCEPTANCE_FILTER  0U /**< Two 32-Bit Acceptance Filters */
#define MSCAN_PDD_FOUR_16BIT_ACCEPTAN_FILTER   0x1U /**< Four 16-Bit Acceptance Filters */
#define MSCAN_PDD_EIGHT_8BIT_ACCEPTANCE_FILTER 0x2U /**< Eight 8-Bit Acceptance Filters */
#define MSCAN_PDD_FILTER_CLOSED                0x3U /**< Filter Closed */

/* Identifier acceptance hit indicator constants */
#define MSCAN_PDD_FILTER_HIT_0 0U                /**< Filter 0 Hit */
#define MSCAN_PDD_FILTER_HIT_1 0x1U              /**< Filter 1 Hit */
#define MSCAN_PDD_FILTER_HIT_2 0x2U              /**< Filter 2 Hit */
#define MSCAN_PDD_FILTER_HIT_3 0x3U              /**< Filter 3 Hit */
#define MSCAN_PDD_FILTER_HIT_4 0x4U              /**< Filter 4 Hit */
#define MSCAN_PDD_FILTER_HIT_5 0x5U              /**< Filter 5 Hit */
#define MSCAN_PDD_FILTER_HIT_6 0x6U              /**< Filter 6 Hit */
#define MSCAN_PDD_FILTER_HIT_7 0x7U              /**< Filter 7 Hit */

/* Type of message buffer ID constants (for SetRxMessageBufferID,
   SetTxMessageBufferID macros). */
#define MSCAN_PDD_BUFFER_ID_EXT 0U               /**< Extended frame format */
#define MSCAN_PDD_BUFFER_ID_STD 0x1U             /**< Standard frame format */


/* ----------------------------------------------------------------------------
   -- GetReceivedFrameFlag
   ---------------------------------------------------------------------------- */

/**
 * @brief Return value of the received frame flag.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: MSCAN_CANCTL0.
 * @par Example:
 *      @code
 *      uint8_t result = MSCAN_PDD_GetReceivedFrameFlag(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define MSCAN_PDD_GetReceivedFrameFlag(PeripheralBase) ( \
    (uint8_t)(MSCAN_CANCTL0_REG(PeripheralBase) & MSCAN_CANCTL0_RXFRM_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- ClearReceivedFrameFlag
   ---------------------------------------------------------------------------- */

/**
 * @brief Clears received frame interrupt flag.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: MSCAN_CANCTL0.
 * @par Example:
 *      @code
 *      MSCAN_PDD_ClearReceivedFrameFlag(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define MSCAN_PDD_ClearReceivedFrameFlag(PeripheralBase) ( \
    MSCAN_CANCTL0_REG(PeripheralBase) |= \
     MSCAN_CANCTL0_RXFRM_MASK \
  )

/* ----------------------------------------------------------------------------
   -- GetReceiverActiveStatusFlag
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the current receiver active status.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of "Receiver active status constants." type. The
 *         value is cast to "uint8_t".
 * @remarks The macro accesses the following registers: MSCAN_CANCTL0.
 * @par Example:
 *      @code
 *      uint8_t result =
 *      MSCAN_PDD_GetReceiverActiveStatusFlag(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define MSCAN_PDD_GetReceiverActiveStatusFlag(PeripheralBase) ( \
    (uint8_t)(MSCAN_CANCTL0_REG(PeripheralBase) & MSCAN_CANCTL0_RXACT_MASK) \
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
 * @remarks The macro accesses the following registers: MSCAN_CANCTL0.
 * @par Example:
 *      @code
 *      MSCAN_PDD_EnableOperateInWaitMode(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define MSCAN_PDD_EnableOperateInWaitMode(PeripheralBase, State) ( \
    MSCAN_CANCTL0_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(( \
       MSCAN_CANCTL0_REG(PeripheralBase)) & ( \
       (uint8_t)(~(uint8_t)MSCAN_CANCTL0_CSWAI_MASK)))) | ( \
      (uint8_t)((uint8_t)(State) << MSCAN_CANCTL0_CSWAI_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- GetSynchronizedStatusFlag
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the current MSCAN synchronized status flag.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of "MSCAN synchronized constants." type. The value is
 *         cast to "uint8_t".
 * @remarks The macro accesses the following registers: MSCAN_CANCTL0.
 * @par Example:
 *      @code
 *      uint8_t result =
 *      MSCAN_PDD_GetSynchronizedStatusFlag(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define MSCAN_PDD_GetSynchronizedStatusFlag(PeripheralBase) ( \
    (uint8_t)(MSCAN_CANCTL0_REG(PeripheralBase) & MSCAN_CANCTL0_SYNCH_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- EnableTimerSynchronization
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables or disables timer synchronization.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Parameter specifying if timer synchronization will be enabled or
 *        disabled. This parameter is of "Global enumeration used for specifying
 *        general enable/disable states (PDD_DISABLE and PDD_ENABLE defined in
 *        PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: MSCAN_CANCTL0.
 * @par Example:
 *      @code
 *      MSCAN_PDD_EnableTimerSynchronization(<peripheral>_BASE_PTR,
 *      PDD_DISABLE);
 *      @endcode
 */
#define MSCAN_PDD_EnableTimerSynchronization(PeripheralBase, State) ( \
    MSCAN_CANCTL0_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(( \
       MSCAN_CANCTL0_REG(PeripheralBase)) & ( \
       (uint8_t)(~(uint8_t)MSCAN_CANCTL0_TIME_MASK)))) | ( \
      (uint8_t)((uint8_t)(State) << MSCAN_CANCTL0_TIME_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- EnableWakeUp
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables or disables wake up feature.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Parameter specifying if wake up will be enabled or disabled.
 *        This parameter is of "Global enumeration used for specifying general
 *        enable/disable states (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)"
 *        type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: MSCAN_CANCTL0.
 * @par Example:
 *      @code
 *      MSCAN_PDD_EnableWakeUp(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define MSCAN_PDD_EnableWakeUp(PeripheralBase, State) ( \
    MSCAN_CANCTL0_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(( \
       MSCAN_CANCTL0_REG(PeripheralBase)) & ( \
       (uint8_t)(~(uint8_t)MSCAN_CANCTL0_WUPE_MASK)))) | ( \
      (uint8_t)((uint8_t)(State) << MSCAN_CANCTL0_WUPE_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- EnableSleepMode
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables or disables MSCAN sleep mode feature.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Parameter specifying if MSCAN will be in running or sleep mode.
 *        This parameter is of "Global enumeration used for specifying general
 *        enable/disable states (PDD_DISABLE and PDD_ENABLE defined in
 *        PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: MSCAN_CANCTL0.
 * @par Example:
 *      @code
 *      MSCAN_PDD_EnableSleepMode(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define MSCAN_PDD_EnableSleepMode(PeripheralBase, State) ( \
    MSCAN_CANCTL0_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(( \
       MSCAN_CANCTL0_REG(PeripheralBase)) & ( \
       (uint8_t)(~(uint8_t)MSCAN_CANCTL0_SLPRQ_MASK)))) | ( \
      (uint8_t)((uint8_t)(State) << MSCAN_CANCTL0_SLPRQ_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- GetSleepModeState
   ---------------------------------------------------------------------------- */

/**
 * @brief Return state of the sleep mode request.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: MSCAN_CANCTL0.
 * @par Example:
 *      @code
 *      uint8_t result = MSCAN_PDD_GetSleepModeState(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define MSCAN_PDD_GetSleepModeState(PeripheralBase) ( \
    (uint8_t)(MSCAN_CANCTL0_REG(PeripheralBase) & MSCAN_CANCTL0_SLPRQ_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- EnableInitializationMode
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables or disables MSCAN initialization mode feature.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Parameter specifying if MSCAN will be in normal or
 *        initialization mode. This parameter is of "Global enumeration used for specifying
 *        general enable/disable states (PDD_DISABLE and PDD_ENABLE defined in
 *        PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: MSCAN_CANCTL0.
 * @par Example:
 *      @code
 *      MSCAN_PDD_EnableInitializationMode(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define MSCAN_PDD_EnableInitializationMode(PeripheralBase, State) ( \
    MSCAN_CANCTL0_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(( \
       MSCAN_CANCTL0_REG(PeripheralBase)) & ( \
       (uint8_t)(~(uint8_t)MSCAN_CANCTL0_INITRQ_MASK)))) | ( \
      (uint8_t)(State))) \
  )

/* ----------------------------------------------------------------------------
   -- ReadControl0Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads control 0 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: MSCAN_CANCTL0.
 * @par Example:
 *      @code
 *      uint8_t result = MSCAN_PDD_ReadControl0Reg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define MSCAN_PDD_ReadControl0Reg(PeripheralBase) ( \
    MSCAN_CANCTL0_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteControl0Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes new value specified by the Value parameter into control 0
 * register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the control 0 register. This parameter is
 *        a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: MSCAN_CANCTL0.
 * @par Example:
 *      @code
 *      MSCAN_PDD_WriteControl0Reg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define MSCAN_PDD_WriteControl0Reg(PeripheralBase, Value) ( \
    MSCAN_CANCTL0_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- EnableDevice
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables/disables MSCAN device.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of device. This parameter is of "Global
 *        enumeration used for specifying general enable/disable states (PDD_DISABLE and
 *        PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: MSCAN_CANCTL1.
 * @par Example:
 *      @code
 *      MSCAN_PDD_EnableDevice(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define MSCAN_PDD_EnableDevice(PeripheralBase, State) ( \
    MSCAN_CANCTL1_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(( \
       MSCAN_CANCTL1_REG(PeripheralBase)) & ( \
       (uint8_t)(~(uint8_t)MSCAN_CANCTL1_CANE_MASK)))) | ( \
      (uint8_t)((uint8_t)(State) << MSCAN_CANCTL1_CANE_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SetClockSource
   ---------------------------------------------------------------------------- */

/**
 * @brief Set CAN Engine Clock Source.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param ClkSource Parameter specifying clock source of CAN Engine. This
 *        parameter is of "MSCAN Engine Clock Source constants (for SetClockSource
 *        macro)." type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: MSCAN_CANCTL1.
 * @par Example:
 *      @code
 *      MSCAN_PDD_SetClockSource(<peripheral>_BASE_PTR, MSCAN_PDD_XTAL_CLOCK);
 *      @endcode
 */
#define MSCAN_PDD_SetClockSource(PeripheralBase, ClkSource) ( \
    MSCAN_CANCTL1_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(( \
       MSCAN_CANCTL1_REG(PeripheralBase)) & ( \
       (uint8_t)(~(uint8_t)MSCAN_CANCTL1_CLKSRC_MASK)))) | ( \
      (uint8_t)(ClkSource))) \
  )

/* ----------------------------------------------------------------------------
   -- EnableLoopBack
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables or disables loop back mode.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Parameter specifying if Loop Back will be enabled or disabled.
 *        This parameter is of "Global enumeration used for specifying general
 *        enable/disable states (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)"
 *        type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: MSCAN_CANCTL1.
 * @par Example:
 *      @code
 *      MSCAN_PDD_EnableLoopBack(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define MSCAN_PDD_EnableLoopBack(PeripheralBase, State) ( \
    MSCAN_CANCTL1_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(( \
       MSCAN_CANCTL1_REG(PeripheralBase)) & ( \
       (uint8_t)(~(uint8_t)MSCAN_CANCTL1_LOOPB_MASK)))) | ( \
      (uint8_t)((uint8_t)(State) << MSCAN_CANCTL1_LOOPB_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- EnableListenOnlyMode
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables or disables listen only mode.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Parameter specifying if listen only mode will be enabled or
 *        disabled. This parameter is of "Global enumeration used for specifying
 *        general enable/disable states (PDD_DISABLE and PDD_ENABLE defined in
 *        PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: MSCAN_CANCTL1.
 * @par Example:
 *      @code
 *      MSCAN_PDD_EnableListenOnlyMode(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define MSCAN_PDD_EnableListenOnlyMode(PeripheralBase, State) ( \
    MSCAN_CANCTL1_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(( \
       MSCAN_CANCTL1_REG(PeripheralBase)) & ( \
       (uint8_t)(~(uint8_t)MSCAN_CANCTL1_LISTEN_MASK)))) | ( \
      (uint8_t)((uint8_t)(State) << MSCAN_CANCTL1_LISTEN_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- EnableAutomaticBusOffRecovery
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables or disables automatic bus off recovery mode.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Parameter specifying if bus off recovery will be enabled or
 *        disabled. This parameter is of "Global enumeration used for specifying
 *        general enable/disable states (PDD_DISABLE and PDD_ENABLE defined in
 *        PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: MSCAN_CANCTL1.
 * @par Example:
 *      @code
 *      MSCAN_PDD_EnableAutomaticBusOffRecovery(<peripheral>_BASE_PTR,
 *      PDD_DISABLE);
 *      @endcode
 */
#define MSCAN_PDD_EnableAutomaticBusOffRecovery(PeripheralBase, State) ( \
    ((State) == PDD_DISABLE) ? ( \
      MSCAN_CANCTL1_REG(PeripheralBase) |= \
       MSCAN_CANCTL1_BORM_MASK) : ( \
      MSCAN_CANCTL1_REG(PeripheralBase) &= \
       (uint8_t)(~(uint8_t)MSCAN_CANCTL1_BORM_MASK)) \
  )

/* ----------------------------------------------------------------------------
   -- EnableWakeUpFilter
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables or disables low-pass filter on wakeup pin.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Parameter specifying if low-pass filter will be enabled or
 *        disabled. This parameter is of "Global enumeration used for specifying
 *        general enable/disable states (PDD_DISABLE and PDD_ENABLE defined in
 *        PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: MSCAN_CANCTL1.
 * @par Example:
 *      @code
 *      MSCAN_PDD_EnableWakeUpFilter(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define MSCAN_PDD_EnableWakeUpFilter(PeripheralBase, State) ( \
    MSCAN_CANCTL1_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(( \
       MSCAN_CANCTL1_REG(PeripheralBase)) & ( \
       (uint8_t)(~(uint8_t)MSCAN_CANCTL1_WUPM_MASK)))) | ( \
      (uint8_t)((uint8_t)(State) << MSCAN_CANCTL1_WUPM_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- GetSleepModeAcknoledgeFlag
   ---------------------------------------------------------------------------- */

/**
 * @brief Return value is nonzero if MSCAN is in sleep mode.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: MSCAN_CANCTL1.
 * @par Example:
 *      @code
 *      uint8_t result =
 *      MSCAN_PDD_GetSleepModeAcknoledgeFlag(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define MSCAN_PDD_GetSleepModeAcknoledgeFlag(PeripheralBase) ( \
    (uint8_t)(MSCAN_CANCTL1_REG(PeripheralBase) & MSCAN_CANCTL1_SLPAK_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- GetInitializationModeAcknowledgeFlag
   ---------------------------------------------------------------------------- */

/**
 * @brief Return value is nonzero if MSCAN is in initialization mode.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: MSCAN_CANCTL1.
 * @par Example:
 *      @code
 *      uint8_t result =
 *      MSCAN_PDD_GetInitializationModeAcknowledgeFlag(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define MSCAN_PDD_GetInitializationModeAcknowledgeFlag(PeripheralBase) ( \
    (uint8_t)(MSCAN_CANCTL1_REG(PeripheralBase) & MSCAN_CANCTL1_INITAK_MASK) \
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
 * @remarks The macro accesses the following registers: MSCAN_CANCTL1.
 * @par Example:
 *      @code
 *      uint8_t result = MSCAN_PDD_ReadControl1Reg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define MSCAN_PDD_ReadControl1Reg(PeripheralBase) ( \
    MSCAN_CANCTL1_REG(PeripheralBase) \
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
 * @remarks The macro accesses the following registers: MSCAN_CANCTL1.
 * @par Example:
 *      @code
 *      MSCAN_PDD_WriteControl1Reg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define MSCAN_PDD_WriteControl1Reg(PeripheralBase, Value) ( \
    MSCAN_CANCTL1_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- SetSyncJumpWidthValue
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the value of the synchronization jump width.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Resync jump width value[0..3]. This parameter is a 2-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: MSCAN_CANBTR0.
 * @par Example:
 *      @code
 *      MSCAN_PDD_SetSyncJumpWidthValue(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define MSCAN_PDD_SetSyncJumpWidthValue(PeripheralBase, Value) ( \
    MSCAN_CANBTR0_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(( \
       MSCAN_CANBTR0_REG(PeripheralBase)) & ( \
       (uint8_t)(~(uint8_t)MSCAN_CANBTR0_SJW_MASK)))) | ( \
      (uint8_t)((uint8_t)(Value) << MSCAN_CANBTR0_SJW_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SetPrescalerValue
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the value of the prescaler division factor.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Prescaler division factor value[0..63]. This parameter is a
 *        6-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: MSCAN_CANBTR0.
 * @par Example:
 *      @code
 *      MSCAN_PDD_SetPrescalerValue(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define MSCAN_PDD_SetPrescalerValue(PeripheralBase, Value) ( \
    MSCAN_CANBTR0_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(( \
       MSCAN_CANBTR0_REG(PeripheralBase)) & ( \
       (uint8_t)(~(uint8_t)MSCAN_CANBTR0_BRP_MASK)))) | ( \
      (uint8_t)(Value))) \
  )

/* ----------------------------------------------------------------------------
   -- ReadBusTiming0Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads BUS timing 0 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: MSCAN_CANBTR0.
 * @par Example:
 *      @code
 *      uint8_t result = MSCAN_PDD_ReadBusTiming0Reg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define MSCAN_PDD_ReadBusTiming0Reg(PeripheralBase) ( \
    MSCAN_CANBTR0_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteBusTiming0Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes new value specified by the Value parameter into BUS timing 0
 * register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the BUS timing 0 register. This parameter
 *        is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: MSCAN_CANBTR0.
 * @par Example:
 *      @code
 *      MSCAN_PDD_WriteBusTiming0Reg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define MSCAN_PDD_WriteBusTiming0Reg(PeripheralBase, Value) ( \
    MSCAN_CANBTR0_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- SetBitSampling
   ---------------------------------------------------------------------------- */

/**
 * @brief Set CAN bit sampling at the Rx input.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Sampling Parameter specifying bit sampling at the Rx input. This
 *        parameter is of "Rx sampling mode constants (for SetBitSampling macro)."
 *        type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: MSCAN_CANBTR1.
 * @par Example:
 *      @code
 *      MSCAN_PDD_SetBitSampling(<peripheral>_BASE_PTR, MSCAN_PDD_ONE_SAMPLE);
 *      @endcode
 */
#define MSCAN_PDD_SetBitSampling(PeripheralBase, Sampling) ( \
    MSCAN_CANBTR1_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(( \
       MSCAN_CANBTR1_REG(PeripheralBase)) & ( \
       (uint8_t)(~(uint8_t)MSCAN_CANBTR1_SAMP_MASK)))) | ( \
      (uint8_t)(Sampling))) \
  )

/* ----------------------------------------------------------------------------
   -- SetPhaseSegment2Value
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the value of phase segment 2.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Phase segment 2 value[0..7]. This parameter is a 3-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: MSCAN_CANBTR1.
 * @par Example:
 *      @code
 *      MSCAN_PDD_SetPhaseSegment2Value(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define MSCAN_PDD_SetPhaseSegment2Value(PeripheralBase, Value) ( \
    MSCAN_CANBTR1_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(( \
       MSCAN_CANBTR1_REG(PeripheralBase)) & ( \
       (uint8_t)(~(uint8_t)MSCAN_CANBTR1_TSEG2_MASK)))) | ( \
      (uint8_t)((uint8_t)(Value) << MSCAN_CANBTR1_TSEG2_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SetPhaseSegment1Value
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the value of phase segment 1.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Phase segment 1 value[0..15]. This parameter is a 4-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: MSCAN_CANBTR1.
 * @par Example:
 *      @code
 *      MSCAN_PDD_SetPhaseSegment1Value(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define MSCAN_PDD_SetPhaseSegment1Value(PeripheralBase, Value) ( \
    MSCAN_CANBTR1_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(( \
       MSCAN_CANBTR1_REG(PeripheralBase)) & ( \
       (uint8_t)(~(uint8_t)MSCAN_CANBTR1_TSEG1_MASK)))) | ( \
      (uint8_t)(Value))) \
  )

/* ----------------------------------------------------------------------------
   -- ReadBusTiming1Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads BUS timing 1 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: MSCAN_CANBTR1.
 * @par Example:
 *      @code
 *      uint8_t result = MSCAN_PDD_ReadBusTiming1Reg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define MSCAN_PDD_ReadBusTiming1Reg(PeripheralBase) ( \
    MSCAN_CANBTR1_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteBusTiming1Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes new value specified by the Value parameter into BUS timing 1
 * register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the BUS timing 1 register. This parameter
 *        is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: MSCAN_CANBTR1.
 * @par Example:
 *      @code
 *      MSCAN_PDD_WriteBusTiming1Reg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define MSCAN_PDD_WriteBusTiming1Reg(PeripheralBase, Value) ( \
    MSCAN_CANBTR1_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- GetRxStatusInterruptFlags
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the value of the status register 1.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: MSCAN_CANRFLG.
 * @par Example:
 *      @code
 *      uint8_t result =
 *      MSCAN_PDD_GetRxStatusInterruptFlags(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define MSCAN_PDD_GetRxStatusInterruptFlags(PeripheralBase) ( \
    MSCAN_CANRFLG_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- ClearRxStatusInterruptFlags
   ---------------------------------------------------------------------------- */

/**
 * @brief Clears receiver interrupt flags of interrupts specified by Mask.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mask Mask of interrupt clear requests. This parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: MSCAN_CANRFLG.
 * @par Example:
 *      @code
 *      MSCAN_PDD_ClearRxStatusInterruptFlags(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define MSCAN_PDD_ClearRxStatusInterruptFlags(PeripheralBase, Mask) ( \
    MSCAN_CANRFLG_REG(PeripheralBase) = \
     (uint8_t)(Mask) \
  )

/* ----------------------------------------------------------------------------
   -- GetRxStatusBits
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns receiver status according the receiver error counter value.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of "Receiver status bits constants" type. The value
 *         is cast to "uint8_t".
 * @remarks The macro accesses the following registers: MSCAN_CANRFLG.
 * @par Example:
 *      @code
 *      uint8_t result = MSCAN_PDD_GetRxStatusBits(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define MSCAN_PDD_GetRxStatusBits(PeripheralBase) ( \
    (uint8_t)(MSCAN_CANRFLG_REG(PeripheralBase) & MSCAN_CANRFLG_RSTAT_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- GetTxStatusBits
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns receiver status according the transmitter error counter value.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of "Transmitter status bits constants" type. The
 *         value is cast to "uint8_t".
 * @remarks The macro accesses the following registers: MSCAN_CANRFLG.
 * @par Example:
 *      @code
 *      uint8_t result = MSCAN_PDD_GetTxStatusBits(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define MSCAN_PDD_GetTxStatusBits(PeripheralBase) ( \
    (uint8_t)(MSCAN_CANRFLG_REG(PeripheralBase) & MSCAN_CANRFLG_TSTAT_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- ReadRxFlagReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads receiver flag register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: MSCAN_CANRFLG.
 * @par Example:
 *      @code
 *      uint8_t result = MSCAN_PDD_ReadRxFlagReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define MSCAN_PDD_ReadRxFlagReg(PeripheralBase) ( \
    MSCAN_CANRFLG_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteRxFlagReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes new value specified by the Value parameter into receiver flag
 * register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the receiver flag register. This
 *        parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: MSCAN_CANRFLG.
 * @par Example:
 *      @code
 *      MSCAN_PDD_WriteRxFlagReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define MSCAN_PDD_WriteRxFlagReg(PeripheralBase, Value) ( \
    MSCAN_CANRFLG_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- EnableRxInterruptsMask
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables receiver interrupts defined by mask parameter.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mask Mask of interrupt requests. This parameter is a 8-bit value.
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: MSCAN_CANRIER.
 * @par Example:
 *      @code
 *      uint8_t result =
 *      MSCAN_PDD_EnableRxInterruptsMask(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define MSCAN_PDD_EnableRxInterruptsMask(PeripheralBase, Mask) ( \
    MSCAN_CANRIER_REG(PeripheralBase) |= \
     (uint8_t)(Mask) \
  )

/* ----------------------------------------------------------------------------
   -- DisableRxInterruptsMask
   ---------------------------------------------------------------------------- */

/**
 * @brief Disables receiver interrupts defined by mask parameter.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mask Mask of interrupt requests. This parameter is a 8-bit value.
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: MSCAN_CANRIER.
 * @par Example:
 *      @code
 *      uint8_t result =
 *      MSCAN_PDD_DisableRxInterruptsMask(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define MSCAN_PDD_DisableRxInterruptsMask(PeripheralBase, Mask) ( \
    MSCAN_CANRIER_REG(PeripheralBase) &= \
     (uint8_t)(~(uint8_t)(Mask)) \
  )

/* ----------------------------------------------------------------------------
   -- SetRxInterruptFlagStatusChange
   ---------------------------------------------------------------------------- */

/**
 * @brief Configures receiver status change flag.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Parameter specifying setting status change flag. This parameter
 *        is of "Receiver status change constants." type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: MSCAN_CANRIER.
 * @par Example:
 *      @code
 *      MSCAN_PDD_SetRxInterruptFlagStatusChange(<peripheral>_BASE_PTR,
 *      MSCAN_PDD_RX_STATUS_DISABLE_INT);
 *      @endcode
 */
#define MSCAN_PDD_SetRxInterruptFlagStatusChange(PeripheralBase, State) ( \
    MSCAN_CANRIER_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(( \
       MSCAN_CANRIER_REG(PeripheralBase)) & ( \
       (uint8_t)(~(uint8_t)MSCAN_CANRIER_RSTATE_MASK)))) | ( \
      (uint8_t)(State))) \
  )

/* ----------------------------------------------------------------------------
   -- SetTxInterruptFlagStatusChange
   ---------------------------------------------------------------------------- */

/**
 * @brief Configures transmitter status change flag.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Parameter specifying setting status change flag. This parameter
 *        is of "Transmitter status change constants." type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: MSCAN_CANRIER.
 * @par Example:
 *      @code
 *      MSCAN_PDD_SetTxInterruptFlagStatusChange(<peripheral>_BASE_PTR,
 *      MSCAN_PDD_TX_STATUS_DISABLE_INT);
 *      @endcode
 */
#define MSCAN_PDD_SetTxInterruptFlagStatusChange(PeripheralBase, State) ( \
    MSCAN_CANRIER_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(( \
       MSCAN_CANRIER_REG(PeripheralBase)) & ( \
       (uint8_t)(~(uint8_t)MSCAN_CANRIER_TSTATE_MASK)))) | ( \
      (uint8_t)(State))) \
  )

/* ----------------------------------------------------------------------------
   -- ReadRxInterruptEnableReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads receiver interrupt enable register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: MSCAN_CANRIER.
 * @par Example:
 *      @code
 *      uint8_t result =
 *      MSCAN_PDD_ReadRxInterruptEnableReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define MSCAN_PDD_ReadRxInterruptEnableReg(PeripheralBase) ( \
    MSCAN_CANRIER_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteRxInterruptEnableReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes new value specified by the Value parameter into receiver
 * interrupt enable register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the receiver interrupt enable register.
 *        This parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: MSCAN_CANRIER.
 * @par Example:
 *      @code
 *      MSCAN_PDD_WriteRxInterruptEnableReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define MSCAN_PDD_WriteRxInterruptEnableReg(PeripheralBase, Value) ( \
    MSCAN_CANRIER_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ClearTxMessageBufferFlagMask
   ---------------------------------------------------------------------------- */

/**
 * @brief Clears message buffer flag (load a message due for transmission)
 * defined by mask parameter.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mask Mask of interrupt requests. This parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: MSCAN_CANTFLG.
 * @par Example:
 *      @code
 *      MSCAN_PDD_ClearTxMessageBufferFlagMask(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define MSCAN_PDD_ClearTxMessageBufferFlagMask(PeripheralBase, Mask) ( \
    MSCAN_CANTFLG_REG(PeripheralBase) = \
     (uint8_t)(Mask) \
  )

/* ----------------------------------------------------------------------------
   -- GetTxMessageBufferFlagMask
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns transmitter message buffer flags.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: MSCAN_CANTFLG.
 * @par Example:
 *      @code
 *      uint8_t result =
 *      MSCAN_PDD_GetTxMessageBufferFlagMask(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define MSCAN_PDD_GetTxMessageBufferFlagMask(PeripheralBase) ( \
    MSCAN_CANTFLG_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- ReadTxFlagReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads transmitter flag register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: MSCAN_CANTFLG.
 * @par Example:
 *      @code
 *      uint8_t result = MSCAN_PDD_ReadTxFlagReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define MSCAN_PDD_ReadTxFlagReg(PeripheralBase) ( \
    MSCAN_CANTFLG_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteTxFlagReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes new value specified by the Value parameter into transmitter
 * flag register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the transmitter flag register. This
 *        parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: MSCAN_CANTFLG.
 * @par Example:
 *      @code
 *      MSCAN_PDD_WriteTxFlagReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define MSCAN_PDD_WriteTxFlagReg(PeripheralBase, Value) ( \
    MSCAN_CANTFLG_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- EnableTxMessageBufferInterruptMask
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables transmit message buffer empty interrupt defined by mask
 * parameter.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mask Mask of interrupt requests. This parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: MSCAN_CANTIER.
 * @par Example:
 *      @code
 *      MSCAN_PDD_EnableTxMessageBufferInterruptMask(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define MSCAN_PDD_EnableTxMessageBufferInterruptMask(PeripheralBase, Mask) ( \
    MSCAN_CANTIER_REG(PeripheralBase) |= \
     (uint8_t)(Mask) \
  )

/* ----------------------------------------------------------------------------
   -- DisableTxMessageBufferInterruptMask
   ---------------------------------------------------------------------------- */

/**
 * @brief Disables transmit message buffer empty interrupt defined by mask
 * parameter.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mask Mask of interrupt requests. This parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: MSCAN_CANTIER.
 * @par Example:
 *      @code
 *      MSCAN_PDD_DisableTxMessageBufferInterruptMask(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define MSCAN_PDD_DisableTxMessageBufferInterruptMask(PeripheralBase, Mask) ( \
    MSCAN_CANTIER_REG(PeripheralBase) &= \
     (uint8_t)(~(uint8_t)(Mask)) \
  )

/* ----------------------------------------------------------------------------
   -- GetTxMessageBufferInterruptMask
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns enabled transmit message buffer interrupt mask.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: MSCAN_CANTIER.
 * @par Example:
 *      @code
 *      uint8_t result =
 *      MSCAN_PDD_GetTxMessageBufferInterruptMask(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define MSCAN_PDD_GetTxMessageBufferInterruptMask(PeripheralBase) ( \
    MSCAN_CANTIER_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- ReadTxInterruptEnableReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads transmitter interrupt enable register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: MSCAN_CANTIER.
 * @par Example:
 *      @code
 *      uint8_t result =
 *      MSCAN_PDD_ReadTxInterruptEnableReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define MSCAN_PDD_ReadTxInterruptEnableReg(PeripheralBase) ( \
    MSCAN_CANTIER_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteTxInterruptEnableReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes new value specified by the Value parameter into transmitter
 * interrupt enable register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the transmitter interrupt enable
 *        register. This parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: MSCAN_CANTIER.
 * @par Example:
 *      @code
 *      MSCAN_PDD_WriteTxInterruptEnableReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define MSCAN_PDD_WriteTxInterruptEnableReg(PeripheralBase, Value) ( \
    MSCAN_CANTIER_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- TxMessageAbortRequestMask
   ---------------------------------------------------------------------------- */

/**
 * @brief Aborts transmit message buffer defined by mask parameter.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mask Mask of message buffer abort requests. This parameter is a 8-bit
 *        value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: MSCAN_CANTARQ.
 * @par Example:
 *      @code
 *      MSCAN_PDD_TxMessageAbortRequestMask(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define MSCAN_PDD_TxMessageAbortRequestMask(PeripheralBase, Mask) ( \
    MSCAN_CANTARQ_REG(PeripheralBase) |= \
     (uint8_t)(Mask) \
  )

/* ----------------------------------------------------------------------------
   -- ReadTxMessageAbortRequestReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads transmitter abort request register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: MSCAN_CANTARQ.
 * @par Example:
 *      @code
 *      uint8_t result =
 *      MSCAN_PDD_ReadTxMessageAbortRequestReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define MSCAN_PDD_ReadTxMessageAbortRequestReg(PeripheralBase) ( \
    MSCAN_CANTARQ_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteTxMessageAbortRequestReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes new value specified by the Value parameter into transmitter
 * abort request register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the transmitter abort request register.
 *        This parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: MSCAN_CANTARQ.
 * @par Example:
 *      @code
 *      MSCAN_PDD_WriteTxMessageAbortRequestReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define MSCAN_PDD_WriteTxMessageAbortRequestReg(PeripheralBase, Value) ( \
    MSCAN_CANTARQ_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- GetTxMessageAbortAcknowledgeMask
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns transmitter abort acknowledge mask.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: MSCAN_CANTAAK.
 * @par Example:
 *      @code
 *      uint8_t result =
 *      MSCAN_PDD_GetTxMessageAbortAcknowledgeMask(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define MSCAN_PDD_GetTxMessageAbortAcknowledgeMask(PeripheralBase) ( \
    MSCAN_CANTAAK_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- ReadTxMessageAbortAcknowledgeReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads transmitter abort acknowledge register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: MSCAN_CANTAAK.
 * @par Example:
 *      @code
 *      uint8_t result =
 *      MSCAN_PDD_ReadTxMessageAbortAcknowledgeReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define MSCAN_PDD_ReadTxMessageAbortAcknowledgeReg(PeripheralBase) ( \
    MSCAN_CANTAAK_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- SelectTxMessageBufferMask
   ---------------------------------------------------------------------------- */

/**
 * @brief Selects transmit message buffer defined by mask parameter.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mask Mask of select tranmit buffer. This parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: MSCAN_CANTBSEL.
 * @par Example:
 *      @code
 *      MSCAN_PDD_SelectTxMessageBufferMask(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define MSCAN_PDD_SelectTxMessageBufferMask(PeripheralBase, Mask) ( \
    MSCAN_CANTBSEL_REG(PeripheralBase) = \
     (uint8_t)(Mask) \
  )

/* ----------------------------------------------------------------------------
   -- ReadTxBufferSelectionReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads transmit buffer selection register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: MSCAN_CANTBSEL.
 * @par Example:
 *      @code
 *      uint8_t result =
 *      MSCAN_PDD_ReadTxBufferSelectionReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define MSCAN_PDD_ReadTxBufferSelectionReg(PeripheralBase) ( \
    MSCAN_CANTBSEL_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteTxBufferSelectionReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes new value specified by the Value parameter into transmit buffer
 * selection register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the transmit buffer selection register.
 *        This parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: MSCAN_CANTBSEL.
 * @par Example:
 *      @code
 *      MSCAN_PDD_WriteTxBufferSelectionReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define MSCAN_PDD_WriteTxBufferSelectionReg(PeripheralBase, Value) ( \
    MSCAN_CANTBSEL_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- SetIdAcceptanceFilterMode
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets identifier acceptance filter mode defined by mask parameter.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mode Identifier acceptance filter mode. This parameter is a 2-bit
 *        value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: MSCAN_CANIDAC.
 * @par Example:
 *      @code
 *      MSCAN_PDD_SetIdAcceptanceFilterMode(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define MSCAN_PDD_SetIdAcceptanceFilterMode(PeripheralBase, Mode) ( \
    MSCAN_CANIDAC_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(( \
       MSCAN_CANIDAC_REG(PeripheralBase)) & ( \
       (uint8_t)(~(uint8_t)MSCAN_CANIDAC_IDAM_MASK)))) | ( \
      (uint8_t)((uint8_t)(Mode) << MSCAN_CANIDAC_IDAM_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- GetIdAcceptanceHitIndicator
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns identifier acceptance hit indicator.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of "Identifier acceptance hit indicator constants"
 *         type. The value is cast to "uint8_t".
 * @remarks The macro accesses the following registers: MSCAN_CANIDAC.
 * @par Example:
 *      @code
 *      uint8_t result =
 *      MSCAN_PDD_GetIdAcceptanceHitIndicator(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define MSCAN_PDD_GetIdAcceptanceHitIndicator(PeripheralBase) ( \
    (uint8_t)(MSCAN_CANIDAC_REG(PeripheralBase) & MSCAN_CANIDAC_IDHIT_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- ReadIdAcceptanceControlReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads identifier acceptance control register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: MSCAN_CANIDAC.
 * @par Example:
 *      @code
 *      uint8_t result =
 *      MSCAN_PDD_ReadIdAcceptanceControlReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define MSCAN_PDD_ReadIdAcceptanceControlReg(PeripheralBase) ( \
    MSCAN_CANIDAC_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteIdAcceptanceControlReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes new value specified by the Value parameter into identifier
 * acceptance control register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the identifier acceptance control
 *        register. This parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: MSCAN_CANIDAC.
 * @par Example:
 *      @code
 *      MSCAN_PDD_WriteIdAcceptanceControlReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define MSCAN_PDD_WriteIdAcceptanceControlReg(PeripheralBase, Value) ( \
    MSCAN_CANIDAC_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- BusOffRecoveryRequest
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the request for recovery from the bus-off mode.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: MSCAN_CANMISC.
 * @par Example:
 *      @code
 *      MSCAN_PDD_BusOffRecoveryRequest(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define MSCAN_PDD_BusOffRecoveryRequest(PeripheralBase) ( \
    MSCAN_CANMISC_REG(PeripheralBase) &= \
     (uint8_t)(~(uint8_t)MSCAN_CANMISC_BOHOLD_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- EnableBusOffRecovery
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables or disables Bus Off Recovery.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Parameter specifying if Bus Off Recovery will be enabled or
 *        disabled. This parameter is of "Global enumeration used for specifying
 *        general enable/disable states (PDD_DISABLE and PDD_ENABLE defined in
 *        PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: MSCAN_CANMISC.
 * @par Example:
 *      @code
 *      MSCAN_PDD_EnableBusOffRecovery(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define MSCAN_PDD_EnableBusOffRecovery(PeripheralBase, State) ( \
    ((State) == PDD_DISABLE) ? ( \
      MSCAN_CANMISC_REG(PeripheralBase) |= \
       MSCAN_CANMISC_BOHOLD_MASK) : ( \
      MSCAN_CANMISC_REG(PeripheralBase) &= \
       (uint8_t)(~(uint8_t)MSCAN_CANMISC_BOHOLD_MASK)) \
  )

/* ----------------------------------------------------------------------------
   -- ReadMiscellaneousReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads miscellaneous register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: MSCAN_CANMISC.
 * @par Example:
 *      @code
 *      uint8_t result = MSCAN_PDD_ReadMiscellaneousReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define MSCAN_PDD_ReadMiscellaneousReg(PeripheralBase) ( \
    MSCAN_CANMISC_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteMiscellaneousReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes new value specified by the Value parameter into miscellaneous
 * register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the miscellaneous register. This
 *        parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: MSCAN_CANMISC.
 * @par Example:
 *      @code
 *      MSCAN_PDD_WriteMiscellaneousReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define MSCAN_PDD_WriteMiscellaneousReg(PeripheralBase, Value) ( \
    MSCAN_CANMISC_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- GetRxErrorCounter
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns receive error counter value.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: MSCAN_CANRXERR.
 * @par Example:
 *      @code
 *      uint8_t result = MSCAN_PDD_GetRxErrorCounter(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define MSCAN_PDD_GetRxErrorCounter(PeripheralBase) ( \
    MSCAN_CANRXERR_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- ReadRxErrorCounterReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads receive error counter register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: MSCAN_CANRXERR.
 * @par Example:
 *      @code
 *      uint8_t result = MSCAN_PDD_ReadRxErrorCounterReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define MSCAN_PDD_ReadRxErrorCounterReg(PeripheralBase) ( \
    MSCAN_CANRXERR_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- GetTxErrorCounter
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns transmit error counter value.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: MSCAN_CANTXERR.
 * @par Example:
 *      @code
 *      uint8_t result = MSCAN_PDD_GetTxErrorCounter(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define MSCAN_PDD_GetTxErrorCounter(PeripheralBase) ( \
    MSCAN_CANTXERR_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- ReadTxErrorCounterReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads transmit error counter register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: MSCAN_CANTXERR.
 * @par Example:
 *      @code
 *      uint8_t result = MSCAN_PDD_ReadTxErrorCounterReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define MSCAN_PDD_ReadTxErrorCounterReg(PeripheralBase) ( \
    MSCAN_CANTXERR_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- GetIdAcceptanceCode1stBank
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the value identifier acceptance code (for first bank).
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: CANIDAR_BANK_1[].
 * @par Example:
 *      @code
 *      uint32_t result =
 *      MSCAN_PDD_GetIdAcceptanceCode1stBank(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define MSCAN_PDD_GetIdAcceptanceCode1stBank(PeripheralBase) ( \
    (((uint32_t)MSCAN_CANIDAR_BANK_1_REG(PeripheralBase,0U)) << 24) | (((uint32_t)MSCAN_CANIDAR_BANK_1_REG(PeripheralBase,1U)) << 16) | (((uint32_t)MSCAN_CANIDAR_BANK_1_REG(PeripheralBase,2U)) << 8) | (((uint32_t)MSCAN_CANIDAR_BANK_1_REG(PeripheralBase,3U)) << 0) \
  )

/* ----------------------------------------------------------------------------
   -- SetIdAcceptanceCode1stBank
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the value identifier acceptance code (for first bank).
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Id Identifier acceptance code value for the first bank. This parameter
 *        is a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CANIDAR_BANK_1[].
 * @par Example:
 *      @code
 *      MSCAN_PDD_SetIdAcceptanceCode1stBank(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define MSCAN_PDD_SetIdAcceptanceCode1stBank(PeripheralBase, Id) ( \
    (MSCAN_CANIDAR_BANK_1_REG(PeripheralBase,3U) = \
     (uint8_t)((uint32_t)(Id) & 0xFFU)), \
    ((MSCAN_CANIDAR_BANK_1_REG(PeripheralBase,2U) = \
     (uint8_t)((uint32_t)((uint32_t)(Id) >> 8U) & 0xFFU)), \
    ((MSCAN_CANIDAR_BANK_1_REG(PeripheralBase,1U) = \
     (uint8_t)((uint16_t)((uint32_t)(Id) >> 16U) & 0xFFU)), \
    (MSCAN_CANIDAR_BANK_1_REG(PeripheralBase,0U) = \
     (uint8_t)((uint32_t)(Id) >> 24U)))) \
  )

/* ----------------------------------------------------------------------------
   -- ReadIdAcceptance1stBankReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the value identifier acceptance (first bank) register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Index Identifier acceptance register index. This parameter is of index
 *        type.
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: CANIDAR_BANK_1[Index].
 * @par Example:
 *      @code
 *      uint8_t result =
 *      MSCAN_PDD_ReadIdAcceptance1stBankReg(<peripheral>_BASE_PTR, periphID);
 *      @endcode
 */
#define MSCAN_PDD_ReadIdAcceptance1stBankReg(PeripheralBase, Index) ( \
    MSCAN_CANIDAR_BANK_1_REG(PeripheralBase,(Index)) \
  )

/* ----------------------------------------------------------------------------
   -- WriteIdAcceptance1stBankReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes new value specified by the Value parameter into identifier
 * acceptance (first bank) register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Index Identifier acceptance register index. This parameter is of index
 *        type.
 * @param Value Value to be written to the identifier acceptance (first bank)
 *        register. This parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CANIDAR_BANK_1[Index].
 * @par Example:
 *      @code
 *      MSCAN_PDD_WriteIdAcceptance1stBankReg(<peripheral>_BASE_PTR, periphID,
 *      1);
 *      @endcode
 */
#define MSCAN_PDD_WriteIdAcceptance1stBankReg(PeripheralBase, Index, Value) ( \
    MSCAN_CANIDAR_BANK_1_REG(PeripheralBase,(Index)) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- GetIdAcceptanceMask1stBank
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the value identifier acceptance mask (for first bank).
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: CANIDMR_BANK_1[].
 * @par Example:
 *      @code
 *      uint32_t result =
 *      MSCAN_PDD_GetIdAcceptanceMask1stBank(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define MSCAN_PDD_GetIdAcceptanceMask1stBank(PeripheralBase) ( \
    (((uint32_t)MSCAN_CANIDMR_BANK_1_REG(PeripheralBase,0U)) << 24) | (((uint32_t)MSCAN_CANIDMR_BANK_1_REG(PeripheralBase,1U)) << 16) | (((uint32_t)MSCAN_CANIDMR_BANK_1_REG(PeripheralBase,2U)) << 8) | (((uint32_t)MSCAN_CANIDMR_BANK_1_REG(PeripheralBase,3U)) << 0) \
  )

/* ----------------------------------------------------------------------------
   -- SetIdAcceptanceMask1stBank
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the value identifier acceptance mask (for first bank).
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Id Identifier acceptance mask value for the first bank. This parameter
 *        is a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CANIDMR_BANK_1[].
 * @par Example:
 *      @code
 *      MSCAN_PDD_SetIdAcceptanceMask1stBank(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define MSCAN_PDD_SetIdAcceptanceMask1stBank(PeripheralBase, Id) ( \
    (MSCAN_CANIDMR_BANK_1_REG(PeripheralBase,3U) = \
     (uint8_t)((uint32_t)(Id) & 0xFFU)), \
    ((MSCAN_CANIDMR_BANK_1_REG(PeripheralBase,2U) = \
     (uint8_t)((uint32_t)((uint32_t)(Id) >> 8U) & 0xFFU)), \
    ((MSCAN_CANIDMR_BANK_1_REG(PeripheralBase,1U) = \
     (uint8_t)((uint16_t)((uint32_t)(Id) >> 16U) & 0xFFU)), \
    (MSCAN_CANIDMR_BANK_1_REG(PeripheralBase,0U) = \
     (uint8_t)((uint32_t)(Id) >> 24U)))) \
  )

/* ----------------------------------------------------------------------------
   -- ReadIdMask1stBankReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the value identifier mask (first bank) register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Index Identifier acceptance register index. This parameter is of index
 *        type.
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: CANIDMR_BANK_1[Index].
 * @par Example:
 *      @code
 *      uint8_t result = MSCAN_PDD_ReadIdMask1stBankReg(<peripheral>_BASE_PTR,
 *      periphID);
 *      @endcode
 */
#define MSCAN_PDD_ReadIdMask1stBankReg(PeripheralBase, Index) ( \
    MSCAN_CANIDMR_BANK_1_REG(PeripheralBase,(Index)) \
  )

/* ----------------------------------------------------------------------------
   -- WriteIdMask1StBankReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes new value specified by the Value parameter into identifier mask
 * (first bank) register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Index Identifier mask register index. This parameter is of index type.
 * @param Value Value to be written to the identifier mask (first bank)
 *        register. This parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CANIDMR_BANK_1[Index].
 * @par Example:
 *      @code
 *      MSCAN_PDD_WriteIdMask1StBankReg(<peripheral>_BASE_PTR, periphID, 1);
 *      @endcode
 */
#define MSCAN_PDD_WriteIdMask1StBankReg(PeripheralBase, Index, Value) ( \
    MSCAN_CANIDMR_BANK_1_REG(PeripheralBase,(Index)) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- GetIdAcceptanceCode2ndBank
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the value identifier acceptance code (for second bank).
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: CANIDAR_BANK_2[].
 * @par Example:
 *      @code
 *      uint32_t result =
 *      MSCAN_PDD_GetIdAcceptanceCode2ndBank(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define MSCAN_PDD_GetIdAcceptanceCode2ndBank(PeripheralBase) ( \
    (((uint32_t)MSCAN_CANIDAR_BANK_2_REG(PeripheralBase,0U)) << 24) | (((uint32_t)MSCAN_CANIDAR_BANK_2_REG(PeripheralBase,1U)) << 16) | (((uint32_t)MSCAN_CANIDAR_BANK_2_REG(PeripheralBase,2U)) << 8) | (((uint32_t)MSCAN_CANIDAR_BANK_2_REG(PeripheralBase,3U)) << 0) \
  )

/* ----------------------------------------------------------------------------
   -- SetIdAcceptanceCode2ndBank
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the value identifier acceptance code (for second bank).
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Id Identifier acceptance code value for the second bank. This
 *        parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CANIDAR_BANK_2[].
 * @par Example:
 *      @code
 *      MSCAN_PDD_SetIdAcceptanceCode2ndBank(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define MSCAN_PDD_SetIdAcceptanceCode2ndBank(PeripheralBase, Id) ( \
    (MSCAN_CANIDAR_BANK_2_REG(PeripheralBase,3U) = \
     (uint8_t)((uint32_t)(Id) & 0xFFU)), \
    ((MSCAN_CANIDAR_BANK_2_REG(PeripheralBase,2U) = \
     (uint8_t)((uint32_t)((uint32_t)(Id) >> 8U) & 0xFFU)), \
    ((MSCAN_CANIDAR_BANK_2_REG(PeripheralBase,1U) = \
     (uint8_t)((uint16_t)((uint32_t)(Id) >> 16U) & 0xFFU)), \
    (MSCAN_CANIDAR_BANK_2_REG(PeripheralBase,0U) = \
     (uint8_t)((uint32_t)(Id) >> 24U)))) \
  )

/* ----------------------------------------------------------------------------
   -- ReadIdAcceptance2ndBankReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the value identifier acceptance (second bank) register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Index Identifier acceptance register index. This parameter is of index
 *        type.
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: CANIDAR_BANK_2[Index].
 * @par Example:
 *      @code
 *      uint8_t result =
 *      MSCAN_PDD_ReadIdAcceptance2ndBankReg(<peripheral>_BASE_PTR, periphID);
 *      @endcode
 */
#define MSCAN_PDD_ReadIdAcceptance2ndBankReg(PeripheralBase, Index) ( \
    MSCAN_CANIDAR_BANK_2_REG(PeripheralBase,(Index)) \
  )

/* ----------------------------------------------------------------------------
   -- WriteIdAcceptance2ndBankReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes new value specified by the Value parameter into identifier
 * acceptance (second bank) register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Index Identifier acceptance register index. This parameter is of index
 *        type.
 * @param Value Value to be written to the identifier acceptance (second bank)
 *        register. This parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CANIDAR_BANK_2[Index].
 * @par Example:
 *      @code
 *      MSCAN_PDD_WriteIdAcceptance2ndBankReg(<peripheral>_BASE_PTR, periphID,
 *      1);
 *      @endcode
 */
#define MSCAN_PDD_WriteIdAcceptance2ndBankReg(PeripheralBase, Index, Value) ( \
    MSCAN_CANIDAR_BANK_2_REG(PeripheralBase,(Index)) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- GetIdAcceptanceMask2ndBank
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the value identifier acceptance mask (for second bank).
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: CANIDMR_BANK_2[].
 * @par Example:
 *      @code
 *      uint32_t result =
 *      MSCAN_PDD_GetIdAcceptanceMask2ndBank(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define MSCAN_PDD_GetIdAcceptanceMask2ndBank(PeripheralBase) ( \
    (((uint32_t)MSCAN_CANIDMR_BANK_2_REG(PeripheralBase,0U)) << 24) | (((uint32_t)MSCAN_CANIDMR_BANK_2_REG(PeripheralBase,1U)) << 16) | (((uint32_t)MSCAN_CANIDMR_BANK_2_REG(PeripheralBase,2U)) << 8) | (((uint32_t)MSCAN_CANIDMR_BANK_2_REG(PeripheralBase,3U)) << 0) \
  )

/* ----------------------------------------------------------------------------
   -- SetIdAcceptanceMask2ndBank
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the value identifier acceptance mask (for second bank).
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Id Identifier acceptance mask value for the second bank. This
 *        parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CANIDMR_BANK_2[].
 * @par Example:
 *      @code
 *      MSCAN_PDD_SetIdAcceptanceMask2ndBank(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define MSCAN_PDD_SetIdAcceptanceMask2ndBank(PeripheralBase, Id) ( \
    (MSCAN_CANIDMR_BANK_2_REG(PeripheralBase,3U) = \
     (uint8_t)((uint32_t)(Id) & 0xFFU)), \
    ((MSCAN_CANIDMR_BANK_2_REG(PeripheralBase,2U) = \
     (uint8_t)((uint32_t)((uint32_t)(Id) >> 8U) & 0xFFU)), \
    ((MSCAN_CANIDMR_BANK_2_REG(PeripheralBase,1U) = \
     (uint8_t)((uint16_t)((uint32_t)(Id) >> 16U) & 0xFFU)), \
    (MSCAN_CANIDMR_BANK_2_REG(PeripheralBase,0U) = \
     (uint8_t)((uint32_t)(Id) >> 24U)))) \
  )

/* ----------------------------------------------------------------------------
   -- ReadIdMask2ndBankReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the value identifier mask (second bank) register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Index Identifier acceptance register index. This parameter is of index
 *        type.
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: CANIDMR_BANK_2[Index].
 * @par Example:
 *      @code
 *      uint8_t result = MSCAN_PDD_ReadIdMask2ndBankReg(<peripheral>_BASE_PTR,
 *      periphID);
 *      @endcode
 */
#define MSCAN_PDD_ReadIdMask2ndBankReg(PeripheralBase, Index) ( \
    MSCAN_CANIDMR_BANK_2_REG(PeripheralBase,(Index)) \
  )

/* ----------------------------------------------------------------------------
   -- WriteIdMask2ndBankReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes new value specified by the Value parameter into identifier mask
 * (second bank) register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Index Identifier mask register index. This parameter is of index type.
 * @param Value Value to be written to the identifier mask (second bank)
 *        register. This parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CANIDMR_BANK_2[Index].
 * @par Example:
 *      @code
 *      MSCAN_PDD_WriteIdMask2ndBankReg(<peripheral>_BASE_PTR, periphID, 1);
 *      @endcode
 */
#define MSCAN_PDD_WriteIdMask2ndBankReg(PeripheralBase, Index, Value) ( \
    MSCAN_CANIDMR_BANK_2_REG(PeripheralBase,(Index)) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- GetRxMessageBufferID
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the received message buffer ID value.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param TypeID Requested ID format. This parameter is of "Type of message
 *        buffer ID constants (for SetRxMessageBufferID, SetTxMessageBufferID
 *        macros)." type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: MSCAN_RSIDR0,
 *          MSCAN_RSIDR1, MSCAN_REIDR0, MSCAN_REIDR1, MSCAN_REIDR2, MSCAN_REIDR3 (depending
 *          on the peripheral).
 * @par Example:
 *      @code
 *      MSCAN_PDD_GetRxMessageBufferID(<peripheral>_BASE_PTR,
 *      MSCAN_PDD_BUFFER_ID_EXT);
 *      @endcode
 */
#define MSCAN_PDD_GetRxMessageBufferID(PeripheralBase, TypeID) ( \
    ((TypeID) == MSCAN_PDD_BUFFER_ID_STD) ? ( \
      (((uint32_t)MSCAN_RSIDR0_REG(PeripheralBase)) << 3) | \
      ((uint32_t)(uint8_t)(( \
       (uint8_t)(MSCAN_RSIDR1_REG(PeripheralBase) & MSCAN_RSIDR1_RSID2_RSID0_MASK)) >> ( \
       MSCAN_RSIDR1_RSID2_RSID0_SHIFT)))) : ( \
      (((uint32_t)MSCAN_REIDR0_REG(PeripheralBase)) << 21) | \
      (((uint32_t)(uint8_t)(( \
       (uint8_t)(MSCAN_REIDR1_REG(PeripheralBase) & MSCAN_REIDR1_REID20_REID18_MASK)) >> ( \
       MSCAN_REIDR1_REID20_REID18_SHIFT))) << 18) | \
      (((uint32_t)(uint8_t)(MSCAN_REIDR1_REG(PeripheralBase) & MSCAN_REIDR1_REID17_REID15_MASK)) << 15) | \
      (((uint32_t)MSCAN_REIDR2_REG(PeripheralBase)) << 7) | \
      ((uint32_t)(uint8_t)(( \
       (uint8_t)(MSCAN_REIDR3_REG(PeripheralBase) & MSCAN_REIDR3_REID6_REID0_MASK)) >> ( \
       MSCAN_REIDR3_REID6_REID0_SHIFT)))) \
  )

/* ----------------------------------------------------------------------------
   -- ReadRxBufferExtIdBits28To21Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the value receive buffer indetifier (extended part ID
 * bits[28:21]) register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: MSCAN_REIDR0.
 * @par Example:
 *      @code
 *      uint8_t result =
 *      MSCAN_PDD_ReadRxBufferExtIdBits28To21Reg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define MSCAN_PDD_ReadRxBufferExtIdBits28To21Reg(PeripheralBase) ( \
    MSCAN_REIDR0_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteRxBufferIdExtBits28To21Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes new value specified by the Value parameter into receive buffer
 * indetifier (extended part ID bits[28:21]) register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the receive buffer indetifier (extended
 *        part ID bits[28:21]) register. This parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: MSCAN_REIDR0.
 * @par Example:
 *      @code
 *      MSCAN_PDD_WriteRxBufferIdExtBits28To21Reg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define MSCAN_PDD_WriteRxBufferIdExtBits28To21Reg(PeripheralBase, Value) ( \
    MSCAN_REIDR0_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadRxBufferStdIdBits10To3Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the value receive buffer indetifier (statnard part ID
 * bits[10:3]) register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: MSCAN_RSIDR0.
 * @par Example:
 *      @code
 *      uint8_t result =
 *      MSCAN_PDD_ReadRxBufferStdIdBits10To3Reg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define MSCAN_PDD_ReadRxBufferStdIdBits10To3Reg(PeripheralBase) ( \
    MSCAN_RSIDR0_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteRxBufferStdIdBits10To3Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes new value specified by the Value parameter into receive buffer
 * indetifier (standard part ID bits[10:3]) register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the receive buffer indetifier (standard
 *        part ID bits[10:3]) register. This parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: MSCAN_RSIDR0.
 * @par Example:
 *      @code
 *      MSCAN_PDD_WriteRxBufferStdIdBits10To3Reg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define MSCAN_PDD_WriteRxBufferStdIdBits10To3Reg(PeripheralBase, Value) ( \
    MSCAN_RSIDR0_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- GetRxMessageBufferSRRExtId
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the value of substitute remote request bit in extended ID.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 1-bit value. The value is cast to "uint8_t".
 * @remarks The macro accesses the following registers: MSCAN_REIDR1.
 * @par Example:
 *      @code
 *      uint8_t result =
 *      MSCAN_PDD_GetRxMessageBufferSRRExtId(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define MSCAN_PDD_GetRxMessageBufferSRRExtId(PeripheralBase) ( \
    (uint8_t)(( \
     (uint8_t)(MSCAN_REIDR1_REG(PeripheralBase) & MSCAN_REIDR1_RSRR_MASK)) >> ( \
     MSCAN_REIDR1_RSRR_SHIFT)) \
  )

/* ----------------------------------------------------------------------------
   -- GetRxMessageBufferIDExt
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the value of ID extended bit.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of "Global enumeration used for specifying general
 *         enable/disable states (PDD_DISABLE and PDD_ENABLE defined in
 *         PDD_Types.h)" type. The value is cast to "uint8_t".
 * @remarks The macro accesses the following registers: MSCAN_REIDR1.
 * @par Example:
 *      @code
 *      uint8_t result =
 *      MSCAN_PDD_GetRxMessageBufferIDExt(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define MSCAN_PDD_GetRxMessageBufferIDExt(PeripheralBase) ( \
    ((uint8_t)(MSCAN_REIDR1_REG(PeripheralBase) & MSCAN_REIDR1_REIDE_MASK) == 0U) ? ( \
      PDD_DISABLE) : ( \
      PDD_ENABLE) \
  )

/* ----------------------------------------------------------------------------
   -- ReadRxBufferExtIdBits20To15Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the value receive buffer indetifier (extended part ID
 * bits[20:15]) register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: MSCAN_REIDR1.
 * @par Example:
 *      @code
 *      uint8_t result =
 *      MSCAN_PDD_ReadRxBufferExtIdBits20To15Reg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define MSCAN_PDD_ReadRxBufferExtIdBits20To15Reg(PeripheralBase) ( \
    MSCAN_REIDR1_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteRxBufferExtIdBits20To15Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes new value specified by the Value parameter into receive buffer
 * indetifier (extended part ID bits[20:15]) register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the receive buffer indetifier (extended
 *        part ID bits[20:15]) register. This parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: MSCAN_REIDR1.
 * @par Example:
 *      @code
 *      MSCAN_PDD_WriteRxBufferExtIdBits20To15Reg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define MSCAN_PDD_WriteRxBufferExtIdBits20To15Reg(PeripheralBase, Value) ( \
    MSCAN_REIDR1_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- GetRxMessageBufferRTRStdId
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the value of remote transmission request bit in received
 * standard ID.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 1-bit value. The value is cast to "uint8_t".
 * @remarks The macro accesses the following registers: MSCAN_RSIDR1.
 * @par Example:
 *      @code
 *      uint8_t result =
 *      MSCAN_PDD_GetRxMessageBufferRTRStdId(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define MSCAN_PDD_GetRxMessageBufferRTRStdId(PeripheralBase) ( \
    (uint8_t)(( \
     (uint8_t)(MSCAN_RSIDR1_REG(PeripheralBase) & MSCAN_RSIDR1_RSRTR_MASK)) >> ( \
     MSCAN_RSIDR1_RSRTR_SHIFT)) \
  )

/* ----------------------------------------------------------------------------
   -- ReadRxBufferStdIdBits2To0Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the value receive buffer indetifier (statnard part ID
 * bits[2:0]) register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: MSCAN_RSIDR1.
 * @par Example:
 *      @code
 *      uint8_t result =
 *      MSCAN_PDD_ReadRxBufferStdIdBits2To0Reg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define MSCAN_PDD_ReadRxBufferStdIdBits2To0Reg(PeripheralBase) ( \
    MSCAN_RSIDR1_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteRxBufferStdIdBits2To0Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes new value specified by the Value parameter into receive buffer
 * indetifier (standard part ID bits[2:0]) register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the receive buffer indetifier (standard
 *        part ID bits[2:0]) register. This parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: MSCAN_RSIDR1.
 * @par Example:
 *      @code
 *      MSCAN_PDD_WriteRxBufferStdIdBits2To0Reg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define MSCAN_PDD_WriteRxBufferStdIdBits2To0Reg(PeripheralBase, Value) ( \
    MSCAN_RSIDR1_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadRxBufferExtIdBits14To7Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the value receive buffer indetifier (extended part ID
 * bits[14:7]) register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: MSCAN_REIDR2.
 * @par Example:
 *      @code
 *      uint8_t result =
 *      MSCAN_PDD_ReadRxBufferExtIdBits14To7Reg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define MSCAN_PDD_ReadRxBufferExtIdBits14To7Reg(PeripheralBase) ( \
    MSCAN_REIDR2_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteRxBufferExtIdBits14To7Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes new value specified by the Value parameter into receive buffer
 * indetifier (extended part ID bits[14:7]) register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the receive buffer indetifier (extended
 *        part ID bits[14:7]) register. This parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: MSCAN_REIDR2.
 * @par Example:
 *      @code
 *      MSCAN_PDD_WriteRxBufferExtIdBits14To7Reg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define MSCAN_PDD_WriteRxBufferExtIdBits14To7Reg(PeripheralBase, Value) ( \
    MSCAN_REIDR2_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- GetRxMessageBufferRTRExtId
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the value of remote transmission request bit in receive
 * extended ID.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 1-bit value. The value is cast to "uint8_t".
 * @remarks The macro accesses the following registers: MSCAN_REIDR3.
 * @par Example:
 *      @code
 *      uint8_t result =
 *      MSCAN_PDD_GetRxMessageBufferRTRExtId(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define MSCAN_PDD_GetRxMessageBufferRTRExtId(PeripheralBase) ( \
    (uint8_t)(MSCAN_REIDR3_REG(PeripheralBase) & MSCAN_REIDR3_RERTR_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- ReadRxBufferExtIdBits6To0Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the value receive buffer indetifier (extended part ID
 * bits[6:0]) register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: MSCAN_REIDR3.
 * @par Example:
 *      @code
 *      uint8_t result =
 *      MSCAN_PDD_ReadRxBufferExtIdBits6To0Reg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define MSCAN_PDD_ReadRxBufferExtIdBits6To0Reg(PeripheralBase) ( \
    MSCAN_REIDR3_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteRxBufferExtIdBits6To0Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes new value specified by the Value parameter into receive buffer
 * indetifier (extended part ID bits[6:0]) register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the receive buffer indetifier (extended
 *        part ID bits[6:0]) register. This parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: MSCAN_REIDR3.
 * @par Example:
 *      @code
 *      MSCAN_PDD_WriteRxBufferExtIdBits6To0Reg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define MSCAN_PDD_WriteRxBufferExtIdBits6To0Reg(PeripheralBase, Value) ( \
    MSCAN_REIDR3_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- SetTxMessageBufferID
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the transmit message buffer ID value.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param TypeID Requested ID format. This parameter is of "Type of message
 *        buffer ID constants (for SetRxMessageBufferID, SetTxMessageBufferID
 *        macros)." type.
 * @param Value ID value. This parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: MSCAN_TSIDR0,
 *          MSCAN_TSIDR1, MSCAN_TEIDR0, MSCAN_TEIDR1, MSCAN_TEIDR2, MSCAN_TEIDR3 (depending
 *          on the peripheral).
 * @par Example:
 *      @code
 *      MSCAN_PDD_SetTxMessageBufferID(<peripheral>_BASE_PTR,
 *      MSCAN_PDD_BUFFER_ID_EXT, 1);
 *      @endcode
 */
#define MSCAN_PDD_SetTxMessageBufferID(PeripheralBase, TypeID, Value) ( \
    ((TypeID) == MSCAN_PDD_BUFFER_ID_STD) ? ( \
      (MSCAN_TSIDR0_REG(PeripheralBase) = \
       (uint8_t)((uint32_t)((uint32_t)(Value) >> 3U) & 0xFFU)), \
      (MSCAN_TSIDR1_REG(PeripheralBase) = \
       (uint8_t)(( \
        (uint8_t)(( \
         MSCAN_TSIDR1_REG(PeripheralBase)) & (( \
         (uint8_t)(~(uint8_t)MSCAN_TSIDR1_TSID2_TSID0_MASK)) & ( \
         (uint8_t)(~(uint8_t)MSCAN_TSIDR1_TSIDE_MASK))))) | ( \
        (uint8_t)((uint8_t)((uint32_t)(Value) & 0x7U) << MSCAN_TSIDR1_TSID2_TSID0_SHIFT))))) : ( \
      (MSCAN_TEIDR0_REG(PeripheralBase) = \
       (uint8_t)((uint16_t)((uint32_t)(Value) >> 21U) & 0xFFU)), \
      ((MSCAN_TEIDR1_REG(PeripheralBase) = \
       (uint8_t)(( \
        (uint8_t)(( \
         MSCAN_TEIDR1_REG(PeripheralBase)) & (( \
         (uint8_t)(~(uint8_t)MSCAN_TEIDR1_TEID20_TEID18_MASK)) & ( \
         (uint8_t)(~(uint8_t)MSCAN_TEIDR1_TEID17_TEID15_MASK))))) | (( \
        (uint8_t)(( \
         (uint8_t)((uint16_t)((uint32_t)(Value) >> 18U) & 0x7U)) << ( \
         MSCAN_TEIDR1_TEID20_TEID18_SHIFT))) | (( \
        MSCAN_TEIDR1_TEIDE_MASK) | ( \
        (uint8_t)((uint32_t)((uint32_t)(Value) >> 15U) & 0x7U)))))), \
      ((MSCAN_TEIDR2_REG(PeripheralBase) = \
       (uint8_t)((uint32_t)((uint32_t)(Value) >> 7U) & 0xFFU)), \
      (MSCAN_TEIDR3_REG(PeripheralBase) = \
       (uint8_t)(( \
        (uint8_t)(( \
         MSCAN_TEIDR3_REG(PeripheralBase)) & ( \
         (uint8_t)(~(uint8_t)MSCAN_TEIDR3_TEID6_TEID0_MASK)))) | ( \
        (uint8_t)((uint8_t)((uint32_t)(Value) & 0x7FU) << MSCAN_TEIDR3_TEID6_TEID0_SHIFT))))))) \
  )

/* ----------------------------------------------------------------------------
   -- ReadTxBufferExtIdBits28To21Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the value transmit buffer indetifier (extended part ID
 * bits[28:21]) register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: MSCAN_TEIDR0.
 * @par Example:
 *      @code
 *      uint8_t result =
 *      MSCAN_PDD_ReadTxBufferExtIdBits28To21Reg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define MSCAN_PDD_ReadTxBufferExtIdBits28To21Reg(PeripheralBase) ( \
    MSCAN_TEIDR0_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteTxBufferIdExtBits28To21Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes new value specified by the Value parameter into transmit buffer
 * indetifier (extended part ID bits[28:21]) register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the transmit buffer indetifier (extended
 *        part ID bits[28:21]) register. This parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: MSCAN_TEIDR0.
 * @par Example:
 *      @code
 *      MSCAN_PDD_WriteTxBufferIdExtBits28To21Reg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define MSCAN_PDD_WriteTxBufferIdExtBits28To21Reg(PeripheralBase, Value) ( \
    MSCAN_TEIDR0_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadTxBufferStdIdBits10To3Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the value transmit buffer indetifier (statnard part ID
 * bits[10:3]) register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: MSCAN_TSIDR0.
 * @par Example:
 *      @code
 *      uint8_t result =
 *      MSCAN_PDD_ReadTxBufferStdIdBits10To3Reg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define MSCAN_PDD_ReadTxBufferStdIdBits10To3Reg(PeripheralBase) ( \
    MSCAN_TSIDR0_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteTxBufferStdIdBits10To3Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes new value specified by the Value parameter into transmit buffer
 * indetifier (standard part ID bits[10:3]) register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the transmit buffer indetifier (standard
 *        part ID bits[10:3]) register. This parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: MSCAN_TSIDR0.
 * @par Example:
 *      @code
 *      MSCAN_PDD_WriteTxBufferStdIdBits10To3Reg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define MSCAN_PDD_WriteTxBufferStdIdBits10To3Reg(PeripheralBase, Value) ( \
    MSCAN_TSIDR0_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- EnableTxMessageBufferSRRExtId
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables/disables substitute remote request bit in transmit extended ID.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of Substitute Remote Request bit. This parameter
 *        is of "Global enumeration used for specifying general enable/disable
 *        states (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: MSCAN_TEIDR1.
 * @par Example:
 *      @code
 *      MSCAN_PDD_EnableTxMessageBufferSRRExtId(<peripheral>_BASE_PTR,
 *      PDD_DISABLE);
 *      @endcode
 */
#define MSCAN_PDD_EnableTxMessageBufferSRRExtId(PeripheralBase, State) ( \
    MSCAN_TEIDR1_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(MSCAN_TEIDR1_REG(PeripheralBase) & (uint8_t)(~(uint8_t)MSCAN_TEIDR1_TSRR_MASK))) | ( \
      (uint8_t)((uint8_t)(State) << MSCAN_TEIDR1_TSRR_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- EnableTxMessageBufferIDExt
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables/disables extended ID of the transmit message buffer.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested frame format. This parameter is of "Global enumeration
 *        used for specifying general enable/disable states (PDD_DISABLE and
 *        PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: MSCAN_TEIDR1.
 * @par Example:
 *      @code
 *      MSCAN_PDD_EnableTxMessageBufferIDExt(<peripheral>_BASE_PTR,
 *      PDD_DISABLE);
 *      @endcode
 */
#define MSCAN_PDD_EnableTxMessageBufferIDExt(PeripheralBase, State) ( \
    MSCAN_TEIDR1_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(( \
       MSCAN_TEIDR1_REG(PeripheralBase)) & ( \
       (uint8_t)(~(uint8_t)MSCAN_TEIDR1_TEIDE_MASK)))) | ( \
      (uint8_t)((uint8_t)(State) << MSCAN_TEIDR1_TEIDE_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- ReadTxBufferExtIdBits20To15Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the value transmit buffer indetifier (extended part ID
 * bits[20:15]) register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: MSCAN_TEIDR1.
 * @par Example:
 *      @code
 *      uint8_t result =
 *      MSCAN_PDD_ReadTxBufferExtIdBits20To15Reg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define MSCAN_PDD_ReadTxBufferExtIdBits20To15Reg(PeripheralBase) ( \
    MSCAN_TEIDR1_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteTxBufferExtIdBits20To15Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes new value specified by the Value parameter into transmit buffer
 * indetifier (extended part ID bits[20:15]) register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the transmit buffer indetifier (extended
 *        part ID bits[20:15]) register. This parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: MSCAN_TEIDR1.
 * @par Example:
 *      @code
 *      MSCAN_PDD_WriteTxBufferExtIdBits20To15Reg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define MSCAN_PDD_WriteTxBufferExtIdBits20To15Reg(PeripheralBase, Value) ( \
    MSCAN_TEIDR1_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- EnableTxMessageBufferRTRStdId
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables/disables remote transmission request bit in standard ID.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of Remote Transmission Request bit. This
 *        parameter is of "Global enumeration used for specifying general enable/disable
 *        states (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: MSCAN_TSIDR1.
 * @par Example:
 *      @code
 *      MSCAN_PDD_EnableTxMessageBufferRTRStdId(<peripheral>_BASE_PTR,
 *      PDD_DISABLE);
 *      @endcode
 */
#define MSCAN_PDD_EnableTxMessageBufferRTRStdId(PeripheralBase, State) ( \
    MSCAN_TSIDR1_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(( \
       MSCAN_TSIDR1_REG(PeripheralBase)) & ( \
       (uint8_t)(~(uint8_t)MSCAN_TSIDR1_TSRTR_MASK)))) | ( \
      (uint8_t)((uint8_t)(State) << MSCAN_TSIDR1_TSRTR_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- ReadTxBufferStdIdBits2To0Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the value transmit buffer indetifier (statnard part ID
 * bits[2:0]) register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: MSCAN_TSIDR1.
 * @par Example:
 *      @code
 *      uint8_t result =
 *      MSCAN_PDD_ReadTxBufferStdIdBits2To0Reg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define MSCAN_PDD_ReadTxBufferStdIdBits2To0Reg(PeripheralBase) ( \
    MSCAN_TSIDR1_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteTxBufferStdIdBits2To0Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes new value specified by the Value parameter into transmit buffer
 * indetifier (standard part ID bits[2:0]) register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the transmit buffer indetifier (standard
 *        part ID bits[2:0]) register. This parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: MSCAN_TSIDR1.
 * @par Example:
 *      @code
 *      MSCAN_PDD_WriteTxBufferStdIdBits2To0Reg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define MSCAN_PDD_WriteTxBufferStdIdBits2To0Reg(PeripheralBase, Value) ( \
    MSCAN_TSIDR1_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadTxBufferExtIdBits14To7Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the value transmit buffer indetifier (extended part ID
 * bits[14:7]) register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: MSCAN_TEIDR2.
 * @par Example:
 *      @code
 *      uint8_t result =
 *      MSCAN_PDD_ReadTxBufferExtIdBits14To7Reg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define MSCAN_PDD_ReadTxBufferExtIdBits14To7Reg(PeripheralBase) ( \
    MSCAN_TEIDR2_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteTxBufferExtIdBits14To7Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes new value specified by the Value parameter into transmit buffer
 * indetifier (extended part ID bits[14:7]) register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the transmit buffer indetifier (extended
 *        part ID bits[14:7]) register. This parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: MSCAN_TEIDR2.
 * @par Example:
 *      @code
 *      MSCAN_PDD_WriteTxBufferExtIdBits14To7Reg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define MSCAN_PDD_WriteTxBufferExtIdBits14To7Reg(PeripheralBase, Value) ( \
    MSCAN_TEIDR2_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- EnableTxMessageBufferRTRExtId
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables/disables remote transmission request bit in extended ID.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of Remote Transmission Request bit. This
 *        parameter is of "Global enumeration used for specifying general enable/disable
 *        states (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: MSCAN_TEIDR3.
 * @par Example:
 *      @code
 *      MSCAN_PDD_EnableTxMessageBufferRTRExtId(<peripheral>_BASE_PTR,
 *      PDD_DISABLE);
 *      @endcode
 */
#define MSCAN_PDD_EnableTxMessageBufferRTRExtId(PeripheralBase, State) ( \
    MSCAN_TEIDR3_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(( \
       MSCAN_TEIDR3_REG(PeripheralBase)) & ( \
       (uint8_t)(~(uint8_t)MSCAN_TEIDR3_TERTR_MASK)))) | ( \
      (uint8_t)(State))) \
  )

/* ----------------------------------------------------------------------------
   -- ReadTxBufferExtIdBits6To0Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the value transmit buffer indetifier (extended part ID
 * bits[6:0]) register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: MSCAN_TEIDR3.
 * @par Example:
 *      @code
 *      uint8_t result =
 *      MSCAN_PDD_ReadTxBufferExtIdBits6To0Reg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define MSCAN_PDD_ReadTxBufferExtIdBits6To0Reg(PeripheralBase) ( \
    MSCAN_TEIDR3_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteTxBufferExtIdBits6To0Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes new value specified by the Value parameter into transmit buffer
 * indetifier (extended part ID bits[6:0]) register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the transmit buffer indetifier (extended
 *        part ID bits[6:0]) register. This parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: MSCAN_TEIDR3.
 * @par Example:
 *      @code
 *      MSCAN_PDD_WriteTxBufferExtIdBits6To0Reg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define MSCAN_PDD_WriteTxBufferExtIdBits6To0Reg(PeripheralBase, Value) ( \
    MSCAN_TEIDR3_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- GetRxMessageBufferData
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the receive data buffer byte.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param DataIndex Data byte index. This parameter is of index type.
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: REDSR[DataIndex].
 * @par Example:
 *      @code
 *      uint8_t result =
 *      MSCAN_PDD_GetRxMessageBufferData(<peripheral>_BASE_PTR, periphID);
 *      @endcode
 */
#define MSCAN_PDD_GetRxMessageBufferData(PeripheralBase, DataIndex) ( \
    (uint8_t)MSCAN_REDSR_REG(PeripheralBase,(DataIndex)) \
  )

/* ----------------------------------------------------------------------------
   -- ReadRxBufferDataSegmentReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the value receive data buffer registers.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Index Data byte index. This parameter is of index type.
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: REDSR[Index].
 * @par Example:
 *      @code
 *      uint8_t result =
 *      MSCAN_PDD_ReadRxBufferDataSegmentReg(<peripheral>_BASE_PTR, periphID);
 *      @endcode
 */
#define MSCAN_PDD_ReadRxBufferDataSegmentReg(PeripheralBase, Index) ( \
    MSCAN_REDSR_REG(PeripheralBase,(Index)) \
  )

/* ----------------------------------------------------------------------------
   -- WriteRxBufferDataSegmentReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes new value specified by the Value parameter into receive data
 * buffer registers.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Index Data byte index. This parameter is of index type.
 * @param Value Value to be written to the receive data buffer register. This
 *        parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: REDSR[Index].
 * @par Example:
 *      @code
 *      MSCAN_PDD_WriteRxBufferDataSegmentReg(<peripheral>_BASE_PTR, periphID,
 *      1);
 *      @endcode
 */
#define MSCAN_PDD_WriteRxBufferDataSegmentReg(PeripheralBase, Index, Value) ( \
    MSCAN_REDSR_REG(PeripheralBase,(Index)) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- GetRxMessageBufferDataLength
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the value of receive message buffer data length.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 4-bit value. The value is cast to "uint8_t".
 * @remarks The macro accesses the following registers: MSCAN_RDLR.
 * @par Example:
 *      @code
 *      uint8_t result =
 *      MSCAN_PDD_GetRxMessageBufferDataLength(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define MSCAN_PDD_GetRxMessageBufferDataLength(PeripheralBase) ( \
    (uint8_t)(MSCAN_RDLR_REG(PeripheralBase) & MSCAN_RDLR_RDLC_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- ReadRxBufferDataLengthReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the value receive buffer data length register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: MSCAN_RDLR.
 * @par Example:
 *      @code
 *      uint8_t result =
 *      MSCAN_PDD_ReadRxBufferDataLengthReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define MSCAN_PDD_ReadRxBufferDataLengthReg(PeripheralBase) ( \
    MSCAN_RDLR_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteRxBufferDataLengthReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes new value specified by the Value parameter into receive buffer
 * data length register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the receive buffer data length register.
 *        This parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: MSCAN_RDLR.
 * @par Example:
 *      @code
 *      MSCAN_PDD_WriteRxBufferDataLengthReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define MSCAN_PDD_WriteRxBufferDataLengthReg(PeripheralBase, Value) ( \
    MSCAN_RDLR_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- GetRxBufferTimeStampValue
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns transmit time stamp value.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 16-bit value.
 * @remarks The macro accesses the following registers: MSCAN_RTSRH, MSCAN_RTSRL
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint16_t result =
 *      MSCAN_PDD_GetRxBufferTimeStampValue(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define MSCAN_PDD_GetRxBufferTimeStampValue(PeripheralBase) ( \
    (uint16_t)((((uint16_t)MSCAN_RTSRH_REG(PeripheralBase)) << 8) | ((uint16_t)MSCAN_RTSRL_REG(PeripheralBase))) \
  )

/* ----------------------------------------------------------------------------
   -- ReadRxBufferTimeStampHighByteReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the value receive buffer time stamp - high byte register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: MSCAN_RTSRH.
 * @par Example:
 *      @code
 *      uint8_t result =
 *      MSCAN_PDD_ReadRxBufferTimeStampHighByteReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define MSCAN_PDD_ReadRxBufferTimeStampHighByteReg(PeripheralBase) ( \
    MSCAN_RTSRH_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- ReadRxBufferTimeStampLowByteReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the value receive buffer time stamp - low byte register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: MSCAN_RTSRL.
 * @par Example:
 *      @code
 *      uint8_t result =
 *      MSCAN_PDD_ReadRxBufferTimeStampLowByteReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define MSCAN_PDD_ReadRxBufferTimeStampLowByteReg(PeripheralBase) ( \
    MSCAN_RTSRL_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- SetTxMessageBufferData
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the data field in the message buffer denominated by DataIndex.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param DataIndex Data byte index. This parameter is of index type.
 * @param Value Data byte value. This parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: TEDSR[DataIndex].
 * @par Example:
 *      @code
 *      MSCAN_PDD_SetTxMessageBufferData(<peripheral>_BASE_PTR, periphID, 1);
 *      @endcode
 */
#define MSCAN_PDD_SetTxMessageBufferData(PeripheralBase, DataIndex, Value) ( \
    MSCAN_TEDSR_REG(PeripheralBase,(DataIndex)) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadTxBufferDataSegmentReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the value transmit data buffer registers.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Index Data byte index. This parameter is of index type.
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: TEDSR[Index].
 * @par Example:
 *      @code
 *      uint8_t result =
 *      MSCAN_PDD_ReadTxBufferDataSegmentReg(<peripheral>_BASE_PTR, periphID);
 *      @endcode
 */
#define MSCAN_PDD_ReadTxBufferDataSegmentReg(PeripheralBase, Index) ( \
    MSCAN_TEDSR_REG(PeripheralBase,(Index)) \
  )

/* ----------------------------------------------------------------------------
   -- WriteTxBufferDataSegmentReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes new value specified by the Value parameter into transmit data
 * buffer registers.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Index Data byte index. This parameter is of index type.
 * @param Value Value to be written to the transmit data buffer register. This
 *        parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: TEDSR[Index].
 * @par Example:
 *      @code
 *      MSCAN_PDD_WriteTxBufferDataSegmentReg(<peripheral>_BASE_PTR, periphID,
 *      1);
 *      @endcode
 */
#define MSCAN_PDD_WriteTxBufferDataSegmentReg(PeripheralBase, Index, Value) ( \
    MSCAN_TEDSR_REG(PeripheralBase,(Index)) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- SetTxMessageBufferDataLength
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the value of receive message buffer data length.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Message buffer code value[0..8]. This parameter is a 4-bit value.
 * @return Returns a 4-bit value. The value is cast to "uint8_t".
 * @remarks The macro accesses the following registers: MSCAN_TDLR.
 * @par Example:
 *      @code
 *      uint8_t result =
 *      MSCAN_PDD_SetTxMessageBufferDataLength(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define MSCAN_PDD_SetTxMessageBufferDataLength(PeripheralBase, Value) ( \
    MSCAN_TDLR_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(MSCAN_TDLR_REG(PeripheralBase) & (uint8_t)(~(uint8_t)MSCAN_TDLR_TDLC_MASK))) | ( \
      (uint8_t)(Value))) \
  )

/* ----------------------------------------------------------------------------
   -- ReadTxBufferDataLengthReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the value transmit buffer data length register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: MSCAN_TDLR.
 * @par Example:
 *      @code
 *      uint8_t result =
 *      MSCAN_PDD_ReadTxBufferDataLengthReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define MSCAN_PDD_ReadTxBufferDataLengthReg(PeripheralBase) ( \
    MSCAN_TDLR_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteTxBufferDataLengthReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes new value specified by the Value parameter into transmit buffer
 * data length register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the transmit buffer data length register.
 *        This parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: MSCAN_TDLR.
 * @par Example:
 *      @code
 *      MSCAN_PDD_WriteTxBufferDataLengthReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define MSCAN_PDD_WriteTxBufferDataLengthReg(PeripheralBase, Value) ( \
    MSCAN_TDLR_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- SetTxBufferPriority
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes new value specified by the Value parameter into transmit buffer
 * priority register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the transmit buffer priority register.
 *        This parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: MSCAN_TBPR.
 * @par Example:
 *      @code
 *      MSCAN_PDD_SetTxBufferPriority(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define MSCAN_PDD_SetTxBufferPriority(PeripheralBase, Value) ( \
    MSCAN_TBPR_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadTxBufferPriorityReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the value transmit buffer priority register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: MSCAN_TBPR.
 * @par Example:
 *      @code
 *      uint8_t result =
 *      MSCAN_PDD_ReadTxBufferPriorityReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define MSCAN_PDD_ReadTxBufferPriorityReg(PeripheralBase) ( \
    MSCAN_TBPR_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteTxBufferPriorityReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes new value specified by the Value parameter into transmit buffer
 * priority register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the transmit buffer priority register.
 *        This parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: MSCAN_TBPR.
 * @par Example:
 *      @code
 *      MSCAN_PDD_WriteTxBufferPriorityReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define MSCAN_PDD_WriteTxBufferPriorityReg(PeripheralBase, Value) ( \
    MSCAN_TBPR_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- GetTxBufferTimeStampValue
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns transmit time stamp value.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 16-bit value.
 * @remarks The macro accesses the following registers: MSCAN_TTSRH, MSCAN_TTSRL
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint16_t result =
 *      MSCAN_PDD_GetTxBufferTimeStampValue(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define MSCAN_PDD_GetTxBufferTimeStampValue(PeripheralBase) ( \
    (uint16_t)((((uint16_t)MSCAN_TTSRH_REG(PeripheralBase)) << 8) | ((uint16_t)MSCAN_TTSRL_REG(PeripheralBase))) \
  )

/* ----------------------------------------------------------------------------
   -- ReadTxBufferTimeStampHighByteReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the value transmit buffer time stamp - high byte register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: MSCAN_TTSRH.
 * @par Example:
 *      @code
 *      uint8_t result =
 *      MSCAN_PDD_ReadTxBufferTimeStampHighByteReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define MSCAN_PDD_ReadTxBufferTimeStampHighByteReg(PeripheralBase) ( \
    MSCAN_TTSRH_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- ReadTxBufferTimeStampLowByteReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the value transmit buffer time stamp - low byte register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: MSCAN_TTSRL.
 * @par Example:
 *      @code
 *      uint8_t result =
 *      MSCAN_PDD_ReadTxBufferTimeStampLowByteReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define MSCAN_PDD_ReadTxBufferTimeStampLowByteReg(PeripheralBase) ( \
    MSCAN_TTSRL_REG(PeripheralBase) \
  )
#endif  /* #if defined(MSCAN_PDD_H_) */

/* MSCAN_PDD.h, eof. */
