/*
  PDD layer implementation for peripheral type UART0
  (C) 2010 Freescale, Inc. All rights reserved.

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
      !defined(MCU_MKL04Z4) /* UART0 */ && \
      !defined(MCU_MKL05Z4) /* UART0 */ && \
      !defined(MCU_MKL14Z4) /* UART0 */ && \
      !defined(MCU_MKL15Z4) /* UART0 */ && \
      !defined(MCU_MKL24Z4) /* UART0 */ && \
      !defined(MCU_MKL25Z4) /* UART0 */
  // Unsupported MCU is active
  #error UART0 PDD library: Unsupported derivative is active.
#endif

#include "PDD_Types.h"

/* ----------------------------------------------------------------------------
   -- Method symbol definitions
   ---------------------------------------------------------------------------- */

/* Interrupt masks */
#define UART0_PDD_INTERRUPT_TRANSMITTER UART0_C2_TIE_MASK /**< Transmitter interrupt enable mask */
#define UART0_PDD_INTERRUPT_TRANSMITTER_COMPLETE UART0_C2_TCIE_MASK /**< Transmitter complete interrupt enable mask */
#define UART0_PDD_INTERRUPT_RECEIVER UART0_C2_RIE_MASK /**< Receiver interrupt enable mask */
#define UART0_PDD_INTERRUPT_IDLE UART0_C2_ILIE_MASK /**< Idle interrupt enable mask */
#define UART0_PDD_INTERRUPT_PARITY_ERROR UART0_C3_PEIE_MASK /**< Parity error interrupt enable mask */
#define UART0_PDD_INTERRUPT_FRAMING_ERROR UART0_C3_FEIE_MASK /**< Framing error interrupt enable mask */
#define UART0_PDD_INTERRUPT_NOISE_ERROR UART0_C3_NEIE_MASK /**< Noise error interrupt enable mask */
#define UART0_PDD_INTERRUPT_OVERRUN_ERROR UART0_C3_ORIE_MASK /**< Overrun error interrupt enable mask */

#if ((defined(MCU_MKL04Z4)) || (defined(MCU_MKL05Z4)))
/* Clock sources */
  #define UART0_PDD_DISABLE_CLOCK 0U               /**< Disable the clock. */
  #define UART0_PDD_FLL_CLOCK 0x1U                 /**< MCG FLL clock. */
  #define UART0_PDD_EXTERNAL_REF_CLOCK 0x2U        /**< External reference clock. */
  #define UART0_PDD_INTERNAL_REF_CLOCK 0x3U        /**< Internal reference clock. */

#else /* (defined(MCU_MKL14Z4)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL24Z4)) || (defined(MCU_MKL25Z4)) */
/* Clock sources */
  #define UART0_PDD_DISABLE_CLOCK 0U               /**< Disable the clock. */
  #define UART0_PDD_PLL_FLL_CLOCK 0x1U             /**< MCG PLL or FLL clock. */
  #define UART0_PDD_EXTERNAL_REF_CLOCK 0x2U        /**< External reference clock. */
  #define UART0_PDD_INTERNAL_REF_CLOCK 0x3U        /**< Internal reference clock. */

#endif /* (defined(MCU_MKL14Z4)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL24Z4)) || (defined(MCU_MKL25Z4)) */
/* Parity types */
#define UART0_PDD_PARITY_NONE 0U                 /**< No parity */
#define UART0_PDD_PARITY_EVEN 0x2U               /**< Even parity */
#define UART0_PDD_PARITY_ODD 0x3U                /**< Even parity */

/* Data width */
#define UART0_PDD_WIDTH_8 0U                     /**< 8-bit communication */
#define UART0_PDD_WIDTH_9 0x1U                   /**< 9-bit communication */
#define UART0_PDD_WIDTH_10 0x2U                  /**< 10-bit communication */

/* Loop mode */
#define UART0_PDD_LOOP_MODE_NORMAL 0U            /**< Normal operation mode. No loopback selected. */
#define UART0_PDD_LOOP_MODE_LOCAL_LOOP 0x80U     /**< Local loopback mode. */

/* Stop bit lengths */
#define UART0_PDD_STOP_BIT_LEN_1 0U              /**< One stop bit. */
#define UART0_PDD_STOP_BIT_LEN_2 0x20U           /**< Two stop bits. */

/* Receiver power states. */
#define UART0_PDD_POWER_NORMAL 0U                /**< Normal operation. */
#define UART0_PDD_POWER_STANDBY 0x2U             /**< Standby mode (waiting for a wakeup condition). */


/* ----------------------------------------------------------------------------
   -- EnableTransmitter
   ---------------------------------------------------------------------------- */

/**
 * Enables UART transmitter.
 * @param peripheralBase Peripheral base address.
 * @param State Enables or disables transmitter.
 */
#define UART0_PDD_EnableTransmitter(peripheralBase, State) ( \
    UART0_C2_REG(peripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(UART0_C2_REG(peripheralBase) & (uint8_t)(~(uint8_t)UART0_C2_TE_MASK))) | ( \
      (uint8_t)((uint8_t)(State) << UART0_C2_TE_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- EnableReceiver
   ---------------------------------------------------------------------------- */

/**
 * Enables UART receiver.
 * @param peripheralBase Peripheral base address.
 * @param State Enables or disables receiver.
 */
#define UART0_PDD_EnableReceiver(peripheralBase, State) ( \
    UART0_C2_REG(peripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(UART0_C2_REG(peripheralBase) & (uint8_t)(~(uint8_t)UART0_C2_RE_MASK))) | ( \
      (uint8_t)((uint8_t)(State) << UART0_C2_RE_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- ReadDataReg
   ---------------------------------------------------------------------------- */

/**
 * Reads data register.
 * @param peripheralBase Peripheral base address.
 */
#define UART0_PDD_ReadDataReg(peripheralBase) ( \
    UART0_D_REG(peripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteDataReg
   ---------------------------------------------------------------------------- */

/**
 * Writes data specified by the Value parameter into data register.
 * @param peripheralBase Peripheral base address.
 * @param Value Value to be written to the data register.
 */
#define UART0_PDD_WriteDataReg(peripheralBase, Value) ( \
    UART0_D_REG(peripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- PutChar8
   ---------------------------------------------------------------------------- */

/**
 * Puts 8-bits character into the transmit buffer.
 * @param peripheralBase Peripheral base address.
 * @param Char 8-bits character to be written to the data register.
 */
#define UART0_PDD_PutChar8(peripheralBase, Char) ( \
    UART0_D_REG(peripheralBase) = \
     (uint8_t)(Char) \
  )

/* ----------------------------------------------------------------------------
   -- PutChar9
   ---------------------------------------------------------------------------- */

/**
 * Puts 9-bits character into the transmit buffer.
 * @param peripheralBase Peripheral base address.
 * @param Char 9-bits character to be written to the data register.
 */
#define UART0_PDD_PutChar9(peripheralBase, Char) ( \
    (UART0_C3_REG(peripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(UART0_C3_REG(peripheralBase) & (uint8_t)(~(uint8_t)UART0_C3_R9T8_MASK))) | ( \
      (uint8_t)((uint8_t)((uint16_t)(Char) >> 8U) << UART0_C3_R9T8_SHIFT)))), \
    (UART0_D_REG(peripheralBase) = \
     (uint8_t)(Char)) \
  )

/* ----------------------------------------------------------------------------
   -- PutChar10
   ---------------------------------------------------------------------------- */

/**
 * Puts 10-bits character into the transmit buffer.
 * @param peripheralBase Peripheral base address.
 * @param Char 10-bits character to be written to the data register.
 */
#define UART0_PDD_PutChar10(peripheralBase, Char) ( \
    (UART0_C3_REG(peripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(UART0_C3_REG(peripheralBase) & (uint8_t)(~(uint8_t)((uint8_t)0x3U << 6U)))) | ( \
      (uint8_t)((uint8_t)((uint16_t)(Char) >> 8U) << 6U)))), \
    (UART0_D_REG(peripheralBase) = \
     (uint8_t)(Char)) \
  )

/* ----------------------------------------------------------------------------
   -- GetChar8
   ---------------------------------------------------------------------------- */

/**
 * Returns a 8-bit character from the receive buffer.
 * @param peripheralBase Peripheral base address.
 */
#define UART0_PDD_GetChar8(peripheralBase) ( \
    UART0_D_REG(peripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- GetChar9Bit
   ---------------------------------------------------------------------------- */

/**
 * Returns the 9th bit of the character from the receive buffer shifted to its
 * bit position (9th). Must be called prior to calling GetChar8 to read the whole
 * 9-bit character.
 * @param peripheralBase Peripheral base address.
 */
#define UART0_PDD_GetChar9Bit(peripheralBase) ( \
    (uint16_t)(( \
     (uint16_t)(( \
      (uint16_t)(UART0_C3_REG(peripheralBase) & UART0_C3_R8T9_MASK)) >> ( \
      UART0_C3_R8T9_SHIFT))) << ( \
     8U)) \
  )

/* ----------------------------------------------------------------------------
   -- GetChar9To10thBit
   ---------------------------------------------------------------------------- */

/**
 * Returns the 9th and 10th bit of the character from the receive buffer shifted
 * to their bit positions (9th and 10th). Must be called prior to calling
 * GetChar8 to read the whole 10-bit character.
 * @param peripheralBase Peripheral base address.
 */
#define UART0_PDD_GetChar9To10thBit(peripheralBase) ( \
    (uint16_t)(( \
     (uint16_t)(( \
      (uint16_t)(( \
       (uint16_t)(UART0_C3_REG(peripheralBase) & UART0_C3_R8T9_MASK)) >> ( \
       UART0_C3_R8T9_SHIFT))) | ( \
      (uint16_t)(( \
       (uint16_t)(( \
        (uint16_t)(UART0_C3_REG(peripheralBase) & UART0_C3_R9T8_MASK)) >> ( \
        UART0_C3_R9T8_SHIFT))) << ( \
       1U))))) << ( \
     8U)) \
  )

/* ----------------------------------------------------------------------------
   -- EnableInterrupt
   ---------------------------------------------------------------------------- */

/**
 * Enables interrupts specified by the Mask parameter.
 * @param peripheralBase Peripheral base address.
 * @param Mask Interrupt mask.
 */
#define UART0_PDD_EnableInterrupt(peripheralBase, Mask) ( \
    (UART0_C2_REG(peripheralBase) |= \
     (uint8_t)((uint8_t)(Mask) & (uint8_t)(~(uint8_t)0xFU))), \
    (UART0_C3_REG(peripheralBase) |= \
     (uint8_t)((uint8_t)(Mask) & 0xFU)) \
  )

/* ----------------------------------------------------------------------------
   -- DisableInterrupt
   ---------------------------------------------------------------------------- */

/**
 * Disables interrupts specified by the Mask parameter.
 * @param peripheralBase Peripheral base address.
 * @param Mask Interrupt mask.
 */
#define UART0_PDD_DisableInterrupt(peripheralBase, Mask) ( \
    (UART0_C2_REG(peripheralBase) &= \
     (uint8_t)(~(uint8_t)((uint8_t)(Mask) & (uint8_t)(~(uint8_t)0xFU)))), \
    (UART0_C3_REG(peripheralBase) &= \
     (uint8_t)(~(uint8_t)((uint8_t)(Mask) & 0xFU))) \
  )

/* ----------------------------------------------------------------------------
   -- GetTxCompleteInterruptMask
   ---------------------------------------------------------------------------- */

/**
 * Gets the status of the transmiter complete interrupt enable bit.
 * @param peripheralBase Peripheral base address.
 */
#define UART0_PDD_GetTxCompleteInterruptMask(peripheralBase) ( \
    (uint8_t)(UART0_C2_REG(peripheralBase) & UART0_C2_TCIE_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- GetTxCompleteStatus
   ---------------------------------------------------------------------------- */

/**
 * Gets the status of the transmiter complete interrupt flag.
 * @param peripheralBase Peripheral base address.
 */
#define UART0_PDD_GetTxCompleteStatus(peripheralBase) ( \
    (uint8_t)(UART0_S1_REG(peripheralBase) & UART0_S1_TC_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- SetParity
   ---------------------------------------------------------------------------- */

/**
 * Sets a communication parity type.
 * @param peripheralBase Peripheral base address.
 * @param Parity Parity type.
 */
#define UART0_PDD_SetParity(peripheralBase, Parity) ( \
    UART0_C1_REG(peripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(UART0_C1_REG(peripheralBase) & (uint8_t)(~(uint8_t)0x3U))) | ( \
      (uint8_t)(Parity))) \
  )

/* ----------------------------------------------------------------------------
   -- SetDataWidth
   ---------------------------------------------------------------------------- */

/**
 * Sets the communication width.
 * @param peripheralBase Peripheral base address.
 * @param Width Data width.
 */
#define UART0_PDD_SetDataWidth(peripheralBase, Width) ( \
    ( \
     ((Width) == UART0_PDD_WIDTH_8) ? ( \
      UART0_C1_REG(peripheralBase) &= \
       (uint8_t)(~(uint8_t)UART0_C1_M_MASK)) : (((Width) == UART0_PDD_WIDTH_9) ? ( \
      UART0_C1_REG(peripheralBase) |= \
       (uint8_t)((uint8_t)0x1U << UART0_C1_M_SHIFT)) : ( \
      UART0_C1_REG(peripheralBase) &= \
       (uint8_t)(~(uint8_t)UART0_C1_M_MASK)) \
    )), \
    ( \
     ((Width) == UART0_PDD_WIDTH_8) ? ( \
      UART0_C4_REG(peripheralBase) &= \
       (uint8_t)(~(uint8_t)UART0_C4_M10_MASK)) : (((Width) == UART0_PDD_WIDTH_9) ? ( \
      UART0_C4_REG(peripheralBase) &= \
       (uint8_t)(~(uint8_t)UART0_C4_M10_MASK)) : ( \
      UART0_C4_REG(peripheralBase) |= \
       (uint8_t)((uint8_t)0x1U << UART0_C4_M10_SHIFT)) \
    )) \
  )

/* ----------------------------------------------------------------------------
   -- SetLoopMode
   ---------------------------------------------------------------------------- */

/**
 * Selects the loop mode operation.
 * @param peripheralBase Peripheral base address.
 * @param LoopMode Loop mode.
 */
#define UART0_PDD_SetLoopMode(peripheralBase, LoopMode) ( \
    UART0_C1_REG(peripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(UART0_C1_REG(peripheralBase) & (uint8_t)(~(uint8_t)UART0_C1_LOOPS_MASK))) | ( \
      (uint8_t)(LoopMode))) \
  )

/* ----------------------------------------------------------------------------
   -- ReadInterruptStatusReg
   ---------------------------------------------------------------------------- */

/**
 * Returns the interrupt status register.
 * @param peripheralBase Peripheral base address.
 */
#define UART0_PDD_ReadInterruptStatusReg(peripheralBase) ( \
    UART0_S1_REG(peripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- ClearInterruptFlags
   ---------------------------------------------------------------------------- */

/**
 * Clears the interrupt status flags specified by the Mask parameter.
 * @param peripheralBase Peripheral base address.
 * @param Mask Mask of the flags to be cleared.
 */
#define UART0_PDD_ClearInterruptFlags(peripheralBase, Mask) ( \
    UART0_S1_REG(peripheralBase) = \
     (uint8_t)(Mask) \
  )

/* ----------------------------------------------------------------------------
   -- SetBaudRate
   ---------------------------------------------------------------------------- */

/**
 * Sets new baud rate value.
 * @param peripheralBase Peripheral base address.
 * @param BaudRate New baud rate value.
 */
#define UART0_PDD_SetBaudRate(peripheralBase, BaudRate) ( \
    (UART0_BDH_REG(peripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(UART0_BDH_REG(peripheralBase) & (uint8_t)(~(uint8_t)UART0_BDH_SBR_MASK))) | ( \
      (uint8_t)((uint16_t)(BaudRate) >> 8U)))), \
    (UART0_BDL_REG(peripheralBase) = \
     (uint8_t)(BaudRate)) \
  )

/* ----------------------------------------------------------------------------
   -- SetOversamplingRatio
   ---------------------------------------------------------------------------- */

/**
 * Set baud rate oversampling ratio.
 * @param peripheralBase Peripheral base address.
 * @param Ratio Baud rate oversampling ratio.
 */
#define UART0_PDD_SetOversamplingRatio(peripheralBase, Ratio) ( \
    UART0_C4_REG(peripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(UART0_C4_REG(peripheralBase) & (uint8_t)(~(uint8_t)UART0_C4_OSR_MASK))) | ( \
      (uint8_t)(Ratio))) \
  )

/* ----------------------------------------------------------------------------
   -- EnableSamplingOnBothEdges
   ---------------------------------------------------------------------------- */

/**
 * Enables receiver sampling on both edges.
 * @param peripheralBase Peripheral base address.
 * @param State Enable or disable sampling on both edges.
 */
#define UART0_PDD_EnableSamplingOnBothEdges(peripheralBase, State) ( \
    UART0_C5_REG(peripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(UART0_C5_REG(peripheralBase) & (uint8_t)(~(uint8_t)UART0_C5_BOTHEDGE_MASK))) | ( \
      (uint8_t)((uint8_t)(State) << UART0_C5_BOTHEDGE_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SetStopBitLength
   ---------------------------------------------------------------------------- */

/**
 * Sets the number of stop bits.
 * @param peripheralBase Peripheral base address.
 * @param Length Stop bit length.
 */
#define UART0_PDD_SetStopBitLength(peripheralBase, Length) ( \
    UART0_BDH_REG(peripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(UART0_BDH_REG(peripheralBase) & (uint8_t)(~(uint8_t)UART0_BDH_SBNS_MASK))) | ( \
      (uint8_t)(Length))) \
  )

/* ----------------------------------------------------------------------------
   -- SetBreak
   ---------------------------------------------------------------------------- */

/**
 * Set the break signal.
 * @param peripheralBase Peripheral base address.
 */
#define UART0_PDD_SetBreak(peripheralBase) ( \
    UART0_C2_REG(peripheralBase) |= \
     UART0_C2_SBK_MASK \
  )

/* ----------------------------------------------------------------------------
   -- ClearBreak
   ---------------------------------------------------------------------------- */

/**
 * Clears the break signal.
 * @param peripheralBase Peripheral base address.
 */
#define UART0_PDD_ClearBreak(peripheralBase) ( \
    UART0_C2_REG(peripheralBase) &= \
     (uint8_t)(~(uint8_t)UART0_C2_SBK_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- GetBreak
   ---------------------------------------------------------------------------- */

/**
 * Returns .
 * @param peripheralBase Peripheral base address.
 */
#define UART0_PDD_GetBreak(peripheralBase) ( \
    (( \
      (uint8_t)(( \
       UART0_S1_REG(peripheralBase)) & ( \
       (uint8_t)(UART0_S1_FE_MASK | UART0_S1_RDRF_MASK)))) == ( \
      (uint8_t)(UART0_S1_FE_MASK | UART0_S1_RDRF_MASK))) ? ( \
      0x1U) : ( \
      0U) \
  )

/* ----------------------------------------------------------------------------
   -- SendBreak
   ---------------------------------------------------------------------------- */

/**
 * Send the break character.
 * @param peripheralBase Peripheral base address.
 */
#define UART0_PDD_SendBreak(peripheralBase) ( \
    (UART0_C2_REG(peripheralBase) |= \
     UART0_C2_SBK_MASK), \
    (UART0_C2_REG(peripheralBase) &= \
     (uint8_t)(~(uint8_t)UART0_C2_SBK_MASK)) \
  )

/* ----------------------------------------------------------------------------
   -- SetReceiverPowerState
   ---------------------------------------------------------------------------- */

/**
 * Places the receiver in a standby state where it waits for automatic hardware
 * detection of a selected wakeup condition.
 * @param peripheralBase Peripheral base address.
 * @param State Receiver power state to be set.
 */
#define UART0_PDD_SetReceiverPowerState(peripheralBase, State) ( \
    UART0_C2_REG(peripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(UART0_C2_REG(peripheralBase) & (uint8_t)(~(uint8_t)UART0_C2_RWU_MASK))) | ( \
      (uint8_t)(State))) \
  )

/* ----------------------------------------------------------------------------
   -- SetClockSource
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MKL04Z4)) || (defined(MCU_MKL05Z4)))
/**
 * Selects the clock source (in the SIM module).
 * @param peripheralBase Peripheral base address.
 * @param Source Clock source. Possible values: DISABLE_CLOCK, FLL_CLOCK,
 *        EXTERNAL_REF_CLOCK, INTERNAL_REF_CLOCK. Use constants from group "Clock
 *        sources".
 */
  #define UART0_PDD_SetClockSource(peripheralBase, Source) ( \
      SIM_SOPT2_REG(SIM_BASE_PTR) = \
       (( \
        (uint32_t)(SIM_SOPT2_REG(SIM_BASE_PTR) & (uint32_t)(~(uint32_t)SIM_SOPT2_UART0SRC_MASK))) | ( \
        (uint32_t)((uint32_t)(Source) << SIM_SOPT2_UART0SRC_SHIFT))) \
    )
#else /* (defined(MCU_MKL14Z4)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL24Z4)) || (defined(MCU_MKL25Z4)) */
/**
 * Selects the clock source (in the SIM module).
 * @param peripheralBase Peripheral base address.
 * @param Source Clock source. Possible values: DISABLE_CLOCK, PLL_FLL_CLOCK,
 *        EXTERNAL_REF_CLOCK, INTERNAL_REF_CLOCK. Use constants from group "Clock
 *        sources".
 */
  #define UART0_PDD_SetClockSource(peripheralBase, Source) ( \
      SIM_SOPT2_REG(SIM_BASE_PTR) = \
       (( \
        (uint32_t)(SIM_SOPT2_REG(SIM_BASE_PTR) & (uint32_t)(~(uint32_t)SIM_SOPT2_UART0SRC_MASK))) | ( \
        (uint32_t)((uint32_t)(Source) << SIM_SOPT2_UART0SRC_SHIFT))) \
    )
#endif /* (defined(MCU_MKL14Z4)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL24Z4)) || (defined(MCU_MKL25Z4)) */
#endif  /* #if defined(UART0_PDD_H_) */

/* UART0_PDD.h, eof. */
