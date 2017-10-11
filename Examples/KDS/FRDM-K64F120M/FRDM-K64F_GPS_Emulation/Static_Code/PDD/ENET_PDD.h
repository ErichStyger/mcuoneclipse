/*
  PDD layer implementation for peripheral type ENET
  (C) 2013 Freescale, Inc. All rights reserved.

  This file is static and it is generated from API-Factory
*/

#if !defined(ENET_PDD_H_)
#define ENET_PDD_H_

/* ----------------------------------------------------------------------------
   -- Test if supported MCU is active
   ---------------------------------------------------------------------------- */

#if !defined(MCU_ACTIVE)
  // No MCU is active
  #error ENET PDD library: No derivative is active. Place proper #include with PDD memory map before including PDD library.
#elif \
      !defined(MCU_MK52D10) /* ENET */ && \
      !defined(MCU_MK52DZ10) /* ENET */ && \
      !defined(MCU_MK53D10) /* ENET */ && \
      !defined(MCU_MK53DZ10) /* ENET */ && \
      !defined(MCU_MK60D10) /* ENET */ && \
      !defined(MCU_MK60F12) /* ENET */ && \
      !defined(MCU_MK60F15) /* ENET */ && \
      !defined(MCU_MK60DZ10) /* ENET */ && \
      !defined(MCU_MK60N512VMD100) /* ENET */ && \
      !defined(MCU_MK61F12) /* ENET */ && \
      !defined(MCU_MK61F15) /* ENET */ && \
      !defined(MCU_MK61F12WS) /* ENET */ && \
      !defined(MCU_MK61F15WS) /* ENET */ && \
      !defined(MCU_MK63F12) /* ENET */ && \
      !defined(MCU_MK63F12WS) /* ENET */ && \
      !defined(MCU_MK64F12) /* ENET */ && \
      !defined(MCU_MK70F12) /* ENET */ && \
      !defined(MCU_MK70F15) /* ENET */ && \
      !defined(MCU_MK70F12WS) /* ENET */ && \
      !defined(MCU_MK70F15WS) /* ENET */
  // Unsupported MCU is active
  #error ENET PDD library: Unsupported derivative is active.
#endif

#include "PDD_Types.h"

/* ----------------------------------------------------------------------------
   -- Method symbol definitions
   ---------------------------------------------------------------------------- */

/* Interrupt masks */
#define ENET_PDD_BABBLING_RX_ERROR_INT      ENET_EIR_BABR_MASK /**< Babbling receive error interrupt. */
#define ENET_PDD_BABBLING_TX_ERROR_INT      ENET_EIR_BABT_MASK /**< Babbling transmit error interrupt. */
#define ENET_PDD_GRACEFUL_STOP_COMPLETE_INT ENET_EIR_GRA_MASK /**< Graceful stop complete interrupt. */
#define ENET_PDD_TX_FRAME_INT               ENET_EIR_TXF_MASK /**< Transmit frame interrupt. */
#define ENET_PDD_TX_BUFFER_INT              ENET_EIR_TXB_MASK /**< Transmit buffer interrupt. */
#define ENET_PDD_RX_FRAME_INT               ENET_EIR_RXF_MASK /**< Receive frame interrupt. */
#define ENET_PDD_RX_BUFFER_INT              ENET_EIR_RXB_MASK /**< Receive buffer interrupt. */
#define ENET_PDD_MII_INT                    ENET_EIR_MII_MASK /**< MII interrupt. */
#define ENET_PDD_ETHERNET_BUS_ERROR_INT     ENET_EIR_EBERR_MASK /**< Ethernet bus error interrupt. */
#define ENET_PDD_LATE_COLLISION_INT         ENET_EIR_LC_MASK /**< Late collision interrupt. */
#define ENET_PDD_COLLISION_RETRY_LIMIT_INT  ENET_EIR_RL_MASK /**< Collision retry limit interrupt. */
#define ENET_PDD_TX_FIFO_UNDERRUN_INT       ENET_EIR_UN_MASK /**< Transmit FIFO underrun interrupt. */
#define ENET_PDD_PAYLOAD_RX_ERROR_INT       ENET_EIR_PLR_MASK /**< Payload receive error interrupt. */
#define ENET_PDD_WAKEUP_INT                 ENET_EIR_WAKEUP_MASK /**< Node wake-up request indication interrupt. */
#define ENET_PDD_TX_TIMESTAMP_AVAIL_INT     ENET_EIR_TS_AVAIL_MASK /**< Transmit timestamp available interrupt. */
#define ENET_PDD_TIMER_PERIOD_INT           ENET_EIR_TS_TIMER_MASK /**< Timestamp timer interrupt. */

/* Filter modes */
#define ENET_PDD_NONE                         0U /**< No filtering. */
#define ENET_PDD_UNICAST_AND_MULTICAST_FILTER ENET_RCR_PROM_MASK /**< Unicast and multicast address filtering. */
#define ENET_PDD_BROADCAST_REJECT             ENET_RCR_BC_REJ_MASK /**< Broadcast frames rejection. */

/* Message Information Block counter indices */
#define ENET_PDD_RMON_T_DROP        0U           /**< Count of frames not counted correctly. */
#define ENET_PDD_RMON_T_PACKETS     0x1U         /**< RMON Tx packet count. */
#define ENET_PDD_RMON_T_BC_PKT      0x2U         /**< RMON Tx Broadcast Packets. */
#define ENET_PDD_RMON_T_MC_PKT      0x3U         /**< RMON Tx Multicast Packets. */
#define ENET_PDD_RMON_T_CRC_ALIGN   0x4U         /**< RMON Tx Packets w CRC/Align error. */
#define ENET_PDD_RMON_T_UNDERSIZE   0x5U         /**< RMON Tx Packets < 64 bytes, good crc. */
#define ENET_PDD_RMON_T_OVERSIZE    0x6U         /**< RMON Tx Packets > MAX_FL bytes, good crc. */
#define ENET_PDD_RMON_T_FRAG        0x7U         /**< RMON Tx Packets < 64 bytes, bad crc. */
#define ENET_PDD_RMON_T_JAB         0x8U         /**< RMON Tx Packets > MAX_FL bytes, bad crc. */
#define ENET_PDD_RMON_T_COL         0x9U         /**< RMON Tx collision count. */
#define ENET_PDD_RMON_T_P64         0xAU         /**< RMON Tx 64 byte packets. */
#define ENET_PDD_RMON_T_P65TO127    0xBU         /**< RMON Tx 65 to 127 byte packets. */
#define ENET_PDD_RMON_T_P128TO255   0xCU         /**< RMON Tx 128 to 255 byte packets. */
#define ENET_PDD_RMON_T_P256TO511   0xDU         /**< RMON Tx 256 to 511 byte packets. */
#define ENET_PDD_RMON_T_P512TO1023  0xEU         /**< RMON Tx 512 to 1023 byte packets. */
#define ENET_PDD_RMON_T_P1024TO2047 0xFU         /**< RMON Tx 1024 to 2047 byte packets. */
#define ENET_PDD_RMON_T_P_GTE2048   0x10U        /**< RMON Tx packets w > 2048 bytes. */
#define ENET_PDD_RMON_T_OCTETS      0x11U        /**< RMON Tx Octets. */
#define ENET_PDD_IEEE_T_DROP        0x12U        /**< Count of frames not counted correctly. */
#define ENET_PDD_IEEE_T_FRAME_OK    0x13U        /**< Frames Transmitted OK. */
#define ENET_PDD_IEEE_T_1COL        0x14U        /**< Frames Transmitted with Single Collision. */
#define ENET_PDD_IEEE_T_MCOL        0x15U        /**< Frames Transmitted with Multiple Collisions. */
#define ENET_PDD_IEEE_T_DEF         0x16U        /**< Frames Transmitted after Deferral Delay. */
#define ENET_PDD_IEEE_T_LCOL        0x17U        /**< Frames Transmitted with Late Collision. */
#define ENET_PDD_IEEE_T_EXCOL       0x18U        /**< Frames Transmitted with Excessive Collisions. */
#define ENET_PDD_IEEE_T_MACERR      0x19U        /**< Frames Transmitted with Tx FIFO Underrun. */
#define ENET_PDD_IEEE_T_CSERR       0x1AU        /**< Frames Transmitted with Carrier Sense Error. */
#define ENET_PDD_IEEE_T_SQE         0x1BU        /**< Frames Transmitted with SQE Error. */
#define ENET_PDD_IEEE_T_FDXFC       0x1CU        /**< Flow Control Pause frames transmitted. */
#define ENET_PDD_IEEE_T_OCTETS_OK   0x1DU        /**< Octet count for Frames Transmitted w/o Error. */
#define ENET_PDD_RMON_R_DROP        0x20U        /**< Count of frames not counted correctly. */
#define ENET_PDD_RMON_R_PACKETS     0x21U        /**< RMON Rx packet count. */
#define ENET_PDD_RMON_R_BC_PKT      0x22U        /**< RMON Rx Broadcast Packets. */
#define ENET_PDD_RMON_R_MC_PKT      0x23U        /**< RMON Rx Multicast Packets. */
#define ENET_PDD_RMON_R_CRC_ALIGN   0x24U        /**< RMON Rx Packets w CRC/Align error. */
#define ENET_PDD_RMON_R_UNDERSIZE   0x25U        /**< RMON Rx Packets < 64 bytes, good crc. */
#define ENET_PDD_RMON_R_OVERSIZE    0x26U        /**< RMON Rx Packets > MAX_FL bytes, good crc. */
#define ENET_PDD_RMON_R_FRAG        0x27U        /**< RMON Rx Packets < 64 bytes, bad crc. */
#define ENET_PDD_RMON_R_JAB         0x28U        /**< RMON Rx Packets > MAX_FL bytes, bad crc. */
#define ENET_PDD_RMON_R_RESVD_0     0x29U        /**< Reserved. */
#define ENET_PDD_RMON_R_P64         0x2AU        /**< RMON Rx 64 byte packets. */
#define ENET_PDD_RMON_R_P65TO127    0x2BU        /**< RMON Rx 65 to 127 byte packets. */
#define ENET_PDD_RMON_R_P128TO255   0x2CU        /**< RMON Rx 128 to 255 byte packets. */
#define ENET_PDD_RMON_R_P256TO511   0x2DU        /**< RMON Rx 256 to 511 byte packets. */
#define ENET_PDD_RMON_R_P512TO1023  0x2EU        /**< RMON Rx 512 to 1023 byte packets. */
#define ENET_PDD_RMON_R_P1024TO2047 0x2FU        /**< RMON Rx 1024 to 2047 byte packets. */
#define ENET_PDD_RMON_R_P_GTE2048   0x30U        /**< RMON Rx packets w > 2048 bytes. */
#define ENET_PDD_RMON_R_OCTETS      0x31U        /**< RMON Rx Octets. */
#define ENET_PDD_IEEE_R_DROP        0x32U        /**< Count of frames not counted correctly. */
#define ENET_PDD_IEEE_R_FRAME_OK    0x33U        /**< Frames Received OK. */
#define ENET_PDD_IEEE_R_CRC         0x34U        /**< Frames Received with CRC Error. */
#define ENET_PDD_IEEE_R_ALIGN       0x35U        /**< Frames Received with Alignment Error. */
#define ENET_PDD_IEEE_R_MACERR      0x36U        /**< Receive Fifo Overflow count. */
#define ENET_PDD_IEEE_R_FDXFC       0x37U        /**< Flow Control Pause frames received. */
#define ENET_PDD_IEEE_R_OCTETS_OK   0x38U        /**< Octet count for Frames Rcvd w/o Error  */

/* Control frame types */
#define ENET_PDD_PAUSE     ENET_RCR_PAUFWD_MASK  /**< Pause frame. */
#define ENET_PDD_NON_PAUSE ENET_RCR_CFEN_MASK    /**< Control frame other than pause frame. */

/* Received frame processing types */
#define ENET_PDD_CRC_REMOVE     ENET_RCR_CRCFWD_MASK /**< Frame CRC removal. */
#define ENET_PDD_PADDING_REMOVE ENET_RCR_PADEN_MASK /**< Frame header padding removal. */

/* Transmit frame processing types */
#define ENET_PDD_CRC_INSERT ENET_TCR_CRCFWD_MASK /**< Frame CRC insertion. */

/* Protocol checksum accelerators */
#define ENET_PDD_INSERT_ON_TX 0x1U               /**< Insert checksum into frame on transmission. */
#define ENET_PDD_DROP_ON_RX   0x2U               /**< Drop frames with wrong checksum on reception. */

/* FIFO shift types */
#define ENET_PDD_TX_ONLY   0x1U                  /**< On transmission only. */
#define ENET_PDD_RX_ONLY   0x2U                  /**< On reception only. */
#define ENET_PDD_TX_AND_RX 0x3U                  /**< On transmission and reception. */

/* Timer status flags */
#define ENET_PDD_TIMER_CHANNEL_0 ENET_TGSR_TF0_MASK /**< Timer channel 0. */
#define ENET_PDD_TIMER_CHANNEL_1 ENET_TGSR_TF1_MASK /**< Timer channel 1. */
#define ENET_PDD_TIMER_CHANNEL_2 ENET_TGSR_TF2_MASK /**< Timer channel 2. */
#define ENET_PDD_TIMER_CHANNEL_3 ENET_TGSR_TF3_MASK /**< Timer channel 3. */

/* Timer clock sources */
#define ENET_PDD_CORE_SYSTEM_CLOCK 0U            /**< Core/system clock. */
#define ENET_PDD_PLL_FLL_CLOCK     0x1U          /**< PLL or FLL clock. */
#define ENET_PDD_EXTAL_CLOCK       0x2U          /**< Extal clock. */
#define ENET_PDD_EXTERNAL_CLOCK    0x3U          /**< External clock. */

/* MII management frame operation code */
#define ENET_PDD_MII_WRITE 0x10000000U           /**< Write MII register. */
#define ENET_PDD_MII_READ  0x20000000U           /**< Read MII register. */

/* Duplex modes */
#define ENET_PDD_FULL_DUPLEX 0x4U                /**< Full duplex. */
#define ENET_PDD_HALF_DUPLEX 0U                  /**< Half duplex. */

/* Power saving modes */
#define ENET_PDD_SLEEP 0U                        /**< Sleep mode. */
#define ENET_PDD_STOP  0x1U                      /**< Stop mode. */
#define ENET_PDD_RUN   0x2U                      /**< Run mode. */

/* MII modes */
#define ENET_PDD_MII          0U                 /**< MII mode. */
#define ENET_PDD_RMII_10MBIT  0x1U               /**< 10MBit RMII mode. */
#define ENET_PDD_RMII_100MBIT 0x2U               /**< 100MBit RMII mode. */

/* MAC address sources */
#define ENET_PDD_KEEP        0U                  /**< Keep frame MAC address. */
#define ENET_PDD_AUTO        0x1U                /**< Auto-complete frame MAC address. */
#define ENET_PDD_AUTO_SUPPL0 0x2U                /**< Auto-complete supplemental MAC address 0. */
#define ENET_PDD_AUTO_SUPPL1 0x3U                /**< Auto-complete supplemental MAC address 1. */
#define ENET_PDD_AUTO_SUPPL2 0x4U                /**< Auto-complete supplemental MAC address 2. */
#define ENET_PDD_AUTO_SUPPL3 0x5U                /**< Auto-complete supplemental MAC address 3. */

/* Timer modes */
#define ENET_PDD_DISABLED                                        0U /**< Disabled. */
#define ENET_PDD_INPUT_CAPTURE_RISING_EDGE                       0x4U /**< Input capture on rising edge. */
#define ENET_PDD_INPUT_CAPTURE_FALLING_EDGE                      0x8U /**< Input capture on falling edge. */
#define ENET_PDD_INPUT_CAPTURE_BOTH_EDGES                        0xCU /**< Input capture on both edges. */
#define ENET_PDD_OUTPUT_COMPARE_SOFTWARE_ONLY                    0x10U /**< Output compare - software only. */
#define ENET_PDD_OUTPUT_COMPARE_TOGGLE_ON_COMPARE                0x14U /**< Output compare - toggle on compare. */
#define ENET_PDD_OUTPUT_COMPARE_CLEAR_ON_COMPARE                 0x18U /**< Output compare - clear on compare. */
#define ENET_PDD_OUTPUT_COMPARE_SET_ON_COMPARE                   0x1CU /**< Output compare - set on compare. */
#define ENET_PDD_OUTPUT_COMPARE_CLEAR_ON_COMPARE_SET_ON_OVERFLOW 0x28U /**< Output compare - clear on compare, set on overflow. */
#define ENET_PDD_OUTPUT_COMPARE_SET_ON_COMPARE_CLEAR_ON_OVERFLOW 0x24U /**< Output compare - set on compare, clear on overflow. */
#define ENET_PDD_OUTPUT_COMPARE_PULSE_LOW                        0x38U /**< Output compare - pulse low. */
#define ENET_PDD_OUTPUT_COMPARE_PULSE_HIGH                       0x3CU /**< Output compare - pulse high. */


/* ----------------------------------------------------------------------------
   -- EnableDevice
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)))
/**
 * @brief Enables the device, transmission and reception are possible.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ENET_ECR.
 * @par Example:
 *      @code
 *      ENET_PDD_EnableDevice(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define ENET_PDD_EnableDevice(PeripheralBase) ( \
      ENET_ECR_REG(PeripheralBase) = \
       (uint32_t)(( \
        (uint32_t)(ENET_ECR_REG(PeripheralBase) | ENET_ECR_ETHEREN_MASK)) & ( \
        (uint32_t)(~(uint32_t)0x20U))) \
    )
#else /* (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) */
/**
 * @brief Enables the device, transmission and reception are possible.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ENET_ECR.
 * @par Example:
 *      @code
 *      ENET_PDD_EnableDevice(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define ENET_PDD_EnableDevice(PeripheralBase) ( \
      ENET_ECR_REG(PeripheralBase) |= \
       ENET_ECR_ETHEREN_MASK \
    )
#endif /* (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) */

/* ----------------------------------------------------------------------------
   -- DisableDevice
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)))
/**
 * @brief Immediately stops receiving and transmission stops after a bad CRC is
 * appended to any currently transmitted frame. The buffer descriptors for an
 * aborted transmit frame are not updated. The DMA, buffer descriptor, and FIFO
 * control logic are reset including the buffer descriptor and FIFO pointers.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ENET_ECR.
 * @par Example:
 *      @code
 *      ENET_PDD_DisableDevice(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define ENET_PDD_DisableDevice(PeripheralBase) ( \
      ENET_ECR_REG(PeripheralBase) &= \
       (uint32_t)((uint32_t)(~(uint32_t)ENET_ECR_ETHEREN_MASK) & (uint32_t)(~(uint32_t)0x20U)) \
    )
#else /* (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) */
/**
 * @brief Immediately stops receiving and transmission stops after a bad CRC is
 * appended to any currently transmitted frame. The buffer descriptors for an
 * aborted transmit frame are not updated. The DMA, buffer descriptor, and FIFO
 * control logic are reset including the buffer descriptor and FIFO pointers.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ENET_ECR.
 * @par Example:
 *      @code
 *      ENET_PDD_DisableDevice(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define ENET_PDD_DisableDevice(PeripheralBase) ( \
      ENET_ECR_REG(PeripheralBase) &= \
       (uint32_t)(~(uint32_t)ENET_ECR_ETHEREN_MASK) \
    )
#endif /* (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) */

/* ----------------------------------------------------------------------------
   -- ResetDevice
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)))
/**
 * @brief Performs a hardware reset of the device and waits for its completion.
 * All registers take their reset values. Also, any transmission/reception
 * currently in progress is abruptly aborted.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ENET_ECR.
 * @par Example:
 *      @code
 *      ENET_PDD_ResetDevice(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define ENET_PDD_ResetDevice(PeripheralBase) ( \
      ENET_ECR_REG(PeripheralBase) = \
       (uint32_t)(( \
        (uint32_t)(ENET_ECR_REG(PeripheralBase) | ENET_ECR_RESET_MASK)) & ( \
        (uint32_t)(~(uint32_t)0x20U))) \
    )
#else /* (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) */
/**
 * @brief Performs a hardware reset of the device and waits for its completion.
 * All registers take their reset values. Also, any transmission/reception
 * currently in progress is abruptly aborted.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ENET_ECR.
 * @par Example:
 *      @code
 *      ENET_PDD_ResetDevice(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define ENET_PDD_ResetDevice(PeripheralBase) ( \
      ENET_ECR_REG(PeripheralBase) |= \
       ENET_ECR_RESET_MASK \
    )
#endif /* (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) */

/* ----------------------------------------------------------------------------
   -- IsResetFinished
   ---------------------------------------------------------------------------- */

/**
 * @brief Indicates whether the reset has finished.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: ENET_ECR.
 * @par Example:
 *      @code
 *      uint32_t result = ENET_PDD_IsResetFinished(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define ENET_PDD_IsResetFinished(PeripheralBase) ( \
    (uint32_t)(( \
     (uint32_t)(ENET_ECR_REG(PeripheralBase) & ENET_ECR_RESET_MASK)) ^ ( \
     ENET_ECR_RESET_MASK)) \
  )

/* ----------------------------------------------------------------------------
   -- EnableTransmission
   ---------------------------------------------------------------------------- */

/**
 * @brief Starts processing the transmit buffer descriptors ring.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ENET_TDAR.
 * @par Example:
 *      @code
 *      ENET_PDD_EnableTransmission(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define ENET_PDD_EnableTransmission(PeripheralBase) ( \
    ENET_TDAR_REG(PeripheralBase) |= \
     ENET_TDAR_TDAR_MASK \
  )

/* ----------------------------------------------------------------------------
   -- EnableReception
   ---------------------------------------------------------------------------- */

/**
 * @brief Starts processing the receive buffer descriptors ring.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ENET_RDAR.
 * @par Example:
 *      @code
 *      ENET_PDD_EnableReception(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define ENET_PDD_EnableReception(PeripheralBase) ( \
    ENET_RDAR_REG(PeripheralBase) |= \
     ENET_RDAR_RDAR_MASK \
  )

/* ----------------------------------------------------------------------------
   -- EnableInterrupts
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables interrupts specified by the mask.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mask Interrupt mask. Use constants from group "Interrupt masks". This
 *        parameter is 32 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ENET_EIMR.
 * @par Example:
 *      @code
 *      ENET_PDD_EnableInterrupts(<peripheral>_BASE_PTR,
 *      ENET_PDD_BABBLING_RX_ERROR_INT);
 *      @endcode
 */
#define ENET_PDD_EnableInterrupts(PeripheralBase, Mask) ( \
    ENET_EIMR_REG(PeripheralBase) |= \
     (uint32_t)(Mask) \
  )

/* ----------------------------------------------------------------------------
   -- DisableInterrupts
   ---------------------------------------------------------------------------- */

/**
 * @brief Disables interrupts specified by the mask.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mask Interrupt mask. Use constants from group "Interrupt masks". This
 *        parameter is 32 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ENET_EIMR.
 * @par Example:
 *      @code
 *      ENET_PDD_DisableInterrupts(<peripheral>_BASE_PTR,
 *      ENET_PDD_BABBLING_RX_ERROR_INT);
 *      @endcode
 */
#define ENET_PDD_DisableInterrupts(PeripheralBase, Mask) ( \
    ENET_EIMR_REG(PeripheralBase) &= \
     (uint32_t)(~(uint32_t)(Mask)) \
  )

/* ----------------------------------------------------------------------------
   -- GetInterruptFlags
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the interrupt flags. The return value can be masked with
 * predefined macros.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Use constants from group "Interrupt masks" for processing return
 *         value.
 * @remarks The macro accesses the following registers: ENET_EIR.
 * @par Example:
 *      @code
 *      uint32_t result = ENET_PDD_GetInterruptFlags(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define ENET_PDD_GetInterruptFlags(PeripheralBase) ( \
    ENET_EIR_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- ClearInterruptFlags
   ---------------------------------------------------------------------------- */

/**
 * @brief Clears the specified interrupt flags.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mask Interrupt mask. Use constants from group "Interrupt masks". This
 *        parameter is 32 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ENET_EIR.
 * @par Example:
 *      @code
 *      ENET_PDD_ClearInterruptFlags(<peripheral>_BASE_PTR,
 *      ENET_PDD_BABBLING_RX_ERROR_INT);
 *      @endcode
 */
#define ENET_PDD_ClearInterruptFlags(PeripheralBase, Mask) ( \
    ENET_EIR_REG(PeripheralBase) = \
     (uint32_t)(Mask) \
  )

/* ----------------------------------------------------------------------------
   -- SendMIIFrame
   ---------------------------------------------------------------------------- */

/**
 * @brief Performs the specified operation on the MII Management Interface.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param OpCode Operation code. This parameter is of "MII management frame
 *        operation code" type.
 * @param PhyAddr PHY device address. This parameter is a 5-bit value.
 * @param RegAddr Register address within the specified PHY device. This
 *        parameter is a 5-bit value.
 * @param Data MII management frame data written to the PHY register. This
 *        parameter is a 16-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ENET_MMFR.
 * @par Example:
 *      @code
 *      ENET_PDD_SendMIIFrame(<peripheral>_BASE_PTR, ENET_PDD_MII_WRITE, 1, 1,
 *      1);
 *      @endcode
 */
#define ENET_PDD_SendMIIFrame(PeripheralBase, OpCode, PhyAddr, RegAddr, Data) ( \
    ENET_MMFR_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)((uint32_t)0x1U << ENET_MMFR_ST_SHIFT)) | (( \
      (uint32_t)(OpCode)) | (( \
      (uint32_t)((uint32_t)(PhyAddr) << ENET_MMFR_PA_SHIFT)) | (( \
      (uint32_t)((uint32_t)(RegAddr) << ENET_MMFR_RA_SHIFT)) | (( \
      (uint32_t)((uint32_t)0x2U << ENET_MMFR_TA_SHIFT)) | ( \
      (uint32_t)(Data))))))) \
  )

/* ----------------------------------------------------------------------------
   -- RecvMIIFrame
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads the received MII management frame data.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Data MII management frame data read from the PHY register. This
 *        parameter is a 16-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ENET_MMFR.
 * @par Example:
 *      @code
 *      ENET_PDD_RecvMIIFrame(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define ENET_PDD_RecvMIIFrame(PeripheralBase, Data) ( \
    (Data) = (uint16_t)(ENET_MMFR_REG(PeripheralBase) & ENET_MMFR_DATA_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- SetMIIHoldtime
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the MII holdtime on the MDIO output.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Holdtime MII holdtime in bus cycle count decreased by 1 (e.g. 2 means
 *        3 bus cycles). Should be at least 10ns. This parameter is a 3-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ENET_MSCR.
 * @par Example:
 *      @code
 *      ENET_PDD_SetMIIHoldtime(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define ENET_PDD_SetMIIHoldtime(PeripheralBase, Holdtime) ( \
    ENET_MSCR_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(ENET_MSCR_REG(PeripheralBase) & (uint32_t)(~(uint32_t)ENET_MSCR_HOLDTIME_MASK))) | ( \
      (uint32_t)((uint32_t)(Holdtime) << ENET_MSCR_HOLDTIME_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- EnableMIIPreamble
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables/disables the MII preamble to be prepended to the MII
 * management frame.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Enable Enable flag. This parameter is of "Global enumeration used for
 *        specifying general enable/disable states (PDD_DISABLE and PDD_ENABLE
 *        defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ENET_MSCR.
 * @par Example:
 *      @code
 *      ENET_PDD_EnableMIIPreamble(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define ENET_PDD_EnableMIIPreamble(PeripheralBase, Enable) ( \
    ((Enable) == PDD_DISABLE) ? ( \
      ENET_MSCR_REG(PeripheralBase) |= \
       ENET_MSCR_DIS_PRE_MASK) : ( \
      ENET_MSCR_REG(PeripheralBase) &= \
       (uint32_t)(~(uint32_t)ENET_MSCR_DIS_PRE_MASK)) \
  )

/* ----------------------------------------------------------------------------
   -- SetMIISpeed
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the MII clock speed.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Speed MII speed. Relative to the bus clock frequency. Zero value turns
 *        off the MII management interface, any non-zero value sets the
 *        management interface clock to bus_clock/((value + 1) x 2). This parameter is a
 *        6-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ENET_MSCR.
 * @par Example:
 *      @code
 *      ENET_PDD_SetMIISpeed(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define ENET_PDD_SetMIISpeed(PeripheralBase, Speed) ( \
    ENET_MSCR_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       ENET_MSCR_REG(PeripheralBase)) & ( \
       (uint32_t)(~(uint32_t)ENET_MSCR_MII_SPEED_MASK)))) | ( \
      (uint32_t)((uint32_t)(Speed) << ENET_MSCR_MII_SPEED_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- EnableFilters
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)))
/**
 * @brief Enables selected ethernet address filters. Disables not selected ones.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mask Filter mask. ENET_PDD_UNICAST_AND_MULTICAST_FILTER enables
 *        unicast and multicast address filtering based on MAC address and address hash
 *        tables, ENET_PDD_BROADCAST_REJECT enables broadcast frame rejecting.
 *        Use constants from group "Filter modes". This parameter is 32 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ENET_RCR.
 * @par Example:
 *      @code
 *      ENET_PDD_EnableFilters(<peripheral>_BASE_PTR, ENET_PDD_NONE);
 *      @endcode
 */
  #define ENET_PDD_EnableFilters(PeripheralBase, Mask) ( \
      ENET_RCR_REG(PeripheralBase) = \
       (uint32_t)(( \
        (uint32_t)(( \
         ENET_RCR_REG(PeripheralBase)) & (( \
         (uint32_t)(~(uint32_t)(ENET_RCR_PROM_MASK | ENET_RCR_BC_REJ_MASK))) & (( \
         (uint32_t)(~(uint32_t)0x40U)) & (( \
         (uint32_t)(~(uint32_t)0x80U)) & ( \
         (uint32_t)(~(uint32_t)0xC00U))))))) | ( \
        (uint32_t)((uint32_t)(Mask) ^ ENET_RCR_PROM_MASK))) \
    )
#else /* (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) */
/**
 * @brief Enables selected ethernet address filters. Disables not selected ones.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mask Filter mask. ENET_PDD_UNICAST_AND_MULTICAST_FILTER enables
 *        unicast and multicast address filtering based on MAC address and address hash
 *        tables, ENET_PDD_BROADCAST_REJECT enables broadcast frame rejecting.
 *        Use constants from group "Filter modes". This parameter is 32 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ENET_RCR.
 * @par Example:
 *      @code
 *      ENET_PDD_EnableFilters(<peripheral>_BASE_PTR, ENET_PDD_NONE);
 *      @endcode
 */
  #define ENET_PDD_EnableFilters(PeripheralBase, Mask) ( \
      ENET_RCR_REG(PeripheralBase) = \
       (uint32_t)(( \
        (uint32_t)(( \
         ENET_RCR_REG(PeripheralBase)) & ( \
         (uint32_t)(~(uint32_t)(ENET_RCR_PROM_MASK | ENET_RCR_BC_REJ_MASK))))) | ( \
        (uint32_t)((uint32_t)(Mask) ^ ENET_RCR_PROM_MASK))) \
    )
#endif /* (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) */

/* ----------------------------------------------------------------------------
   -- SetDuplexMode
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)))
/**
 * @brief Enables/disables transmitting while receiving and vice-versa in the
 * ethernet MAC.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mode Duplex mode to be set. This parameter is of "Duplex modes" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ENET_TCR, ENET_RCR
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      ENET_PDD_SetDuplexMode(<peripheral>_BASE_PTR, ENET_PDD_FULL_DUPLEX);
 *      @endcode
 */
  #define ENET_PDD_SetDuplexMode(PeripheralBase, Mode) ( \
      (ENET_TCR_REG(PeripheralBase) = \
       (uint32_t)(( \
        (uint32_t)(( \
         ENET_TCR_REG(PeripheralBase)) & (( \
         (uint32_t)(~(uint32_t)ENET_TCR_FDEN_MASK)) & ( \
         (uint32_t)(~(uint32_t)0x2U))))) | ( \
        (uint32_t)(Mode)))), \
      ( \
       ((Mode) == ENET_PDD_HALF_DUPLEX) ? ( \
        ENET_RCR_REG(PeripheralBase) = \
         (uint32_t)(( \
          (uint32_t)(ENET_RCR_REG(PeripheralBase) | ENET_RCR_DRT_MASK)) & (( \
          (uint32_t)(~(uint32_t)0x40U)) & (( \
          (uint32_t)(~(uint32_t)0x80U)) & ( \
          (uint32_t)(~(uint32_t)0xC00U)))))) : ( \
        ENET_RCR_REG(PeripheralBase) &= \
         (uint32_t)(( \
          (uint32_t)(~(uint32_t)ENET_RCR_DRT_MASK)) & (( \
          (uint32_t)(~(uint32_t)0x40U)) & (( \
          (uint32_t)(~(uint32_t)0x80U)) & ( \
          (uint32_t)(~(uint32_t)0xC00U)))))) \
      ) \
    )
#else /* (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) */
/**
 * @brief Enables/disables transmitting while receiving and vice-versa in the
 * ethernet MAC.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mode Duplex mode to be set. This parameter is of "Duplex modes" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ENET_TCR, ENET_RCR
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      ENET_PDD_SetDuplexMode(<peripheral>_BASE_PTR, ENET_PDD_FULL_DUPLEX);
 *      @endcode
 */
  #define ENET_PDD_SetDuplexMode(PeripheralBase, Mode) ( \
      (ENET_TCR_REG(PeripheralBase) = \
       (uint32_t)(( \
        (uint32_t)(ENET_TCR_REG(PeripheralBase) & (uint32_t)(~(uint32_t)ENET_TCR_FDEN_MASK))) | ( \
        (uint32_t)(Mode)))), \
      ( \
       ((Mode) == ENET_PDD_HALF_DUPLEX) ? ( \
        ENET_RCR_REG(PeripheralBase) |= \
         ENET_RCR_DRT_MASK) : ( \
        ENET_RCR_REG(PeripheralBase) &= \
         (uint32_t)(~(uint32_t)ENET_RCR_DRT_MASK)) \
      ) \
    )
#endif /* (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) */

/* ----------------------------------------------------------------------------
   -- SendPauseFrame
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)))
/**
 * @brief Transmits a MAC control PAUSE frame after the current transmission is
 * completed, then resumes the transmission of data frames. This method is only
 * available if flow control is enabled.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ENET_TCR.
 * @par Example:
 *      @code
 *      ENET_PDD_SendPauseFrame(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define ENET_PDD_SendPauseFrame(PeripheralBase) ( \
      ENET_TCR_REG(PeripheralBase) = \
       (uint32_t)(( \
        (uint32_t)(ENET_TCR_REG(PeripheralBase) | ENET_TCR_TFC_PAUSE_MASK)) & ( \
        (uint32_t)(~(uint32_t)0x2U))) \
    )
#else /* (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) */
/**
 * @brief Transmits a MAC control PAUSE frame after the current transmission is
 * completed, then resumes the transmission of data frames. This method is only
 * available if flow control is enabled.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ENET_TCR.
 * @par Example:
 *      @code
 *      ENET_PDD_SendPauseFrame(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define ENET_PDD_SendPauseFrame(PeripheralBase) ( \
      ENET_TCR_REG(PeripheralBase) |= \
       ENET_TCR_TFC_PAUSE_MASK \
    )
#endif /* (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) */

/* ----------------------------------------------------------------------------
   -- SetPauseDuration
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the duration of the PAUSE frame. The PAUSE frame will contain
 * this value. This method is only available if flow control is enabled.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Duration Duration of the PAUSE frame. This parameter is a 16-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ENET_OPD.
 * @par Example:
 *      @code
 *      ENET_PDD_SetPauseDuration(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define ENET_PDD_SetPauseDuration(PeripheralBase, Duration) ( \
    ENET_OPD_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(ENET_OPD_REG(PeripheralBase) & (uint32_t)(~(uint32_t)ENET_OPD_PAUSE_DUR_MASK))) | ( \
      (uint32_t)(Duration))) \
  )

/* ----------------------------------------------------------------------------
   -- SetMACAddress
   ---------------------------------------------------------------------------- */

/**
 * @brief Changes the MAC address of the ethernet device.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Address MAC address. This parameter is of user-defined type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ENET_PALR, ENET_PAUR
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      ENET_PDD_SetMACAddress(<peripheral>_BASE_PTR, [Address]);
 *      @endcode
 */
#define ENET_PDD_SetMACAddress(PeripheralBase, Address) ( \
    (ENET_PALR_REG(PeripheralBase) = \
     (uint32_t)(( \
      (Address)[3]) | (( \
      (uint32_t)((uint32_t)((Address)[2]) << 8U)) | (( \
      (uint32_t)((uint32_t)((Address)[1]) << 16U)) | ( \
      (uint32_t)((uint32_t)((Address)[0]) << 24U)))))), \
    (ENET_PAUR_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)((uint32_t)((Address)[5]) << 16U)) | ( \
      (uint32_t)((uint32_t)((Address)[4]) << 24U)))) \
  )

/* ----------------------------------------------------------------------------
   -- GetMACAddress
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the current MAC address of the ethernet device.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Address Variable, where the current MAC address of the device will be
 *        stored. This parameter is of user-defined type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ENET_PALR, ENET_PAUR
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      ENET_PDD_GetMACAddress(<peripheral>_BASE_PTR, [Address]);
 *      @endcode
 */
#define ENET_PDD_GetMACAddress(PeripheralBase, Address) ( \
    (Address)[0] = (uint8_t)((uint32_t)((uint32_t)ENET_PALR_REG(PeripheralBase) >> 24) & 0xFFU), \
    ((Address)[1] = (uint8_t)((uint32_t)((uint32_t)ENET_PALR_REG(PeripheralBase) >> 16) & 0xFFU), \
    ((Address)[2] = (uint8_t)((uint32_t)((uint32_t)ENET_PALR_REG(PeripheralBase) >>  8) & 0xFFU), \
    ((Address)[3] = (uint8_t)((uint32_t)ENET_PALR_REG(PeripheralBase) & 0xFFU), \
    ((Address)[4] = (uint8_t)((uint32_t)((uint32_t)ENET_PAUR_REG(PeripheralBase) >> 24) & 0xFFU), \
    (Address)[5] = (uint8_t)((uint32_t)((uint32_t)ENET_PAUR_REG(PeripheralBase) >> 16) & 0xFFU))))) \
  )

/* ----------------------------------------------------------------------------
   -- SetUnicastAddrHashTableBit
   ---------------------------------------------------------------------------- */

/**
 * @brief Raises the specified bit in the unicast (individual) address hash
 * table.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Index Unicast hash table bit index. This parameter is a 6-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ENET_IALR, ENET_IAUR
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      ENET_PDD_SetUnicastAddrHashTableBit(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define ENET_PDD_SetUnicastAddrHashTableBit(PeripheralBase, Index) ( \
    ((uint8_t)((uint8_t)(Index) & 0x20U) == 0U) ? ( \
      ENET_IALR_REG(PeripheralBase) |= \
       (uint32_t)((uint32_t)0x1U << (uint8_t)(Index))) : ( \
      ENET_IAUR_REG(PeripheralBase) |= \
       (uint32_t)((uint32_t)0x1U << (uint8_t)((uint8_t)(Index) & 0x1FU))) \
  )

/* ----------------------------------------------------------------------------
   -- ClearUnicastAddrHashTable
   ---------------------------------------------------------------------------- */

/**
 * @brief Clears all bits in the unicast (individual) address hash table.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ENET_IALR, ENET_IAUR
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      ENET_PDD_ClearUnicastAddrHashTable(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define ENET_PDD_ClearUnicastAddrHashTable(PeripheralBase) ( \
    (ENET_IALR_REG(PeripheralBase) = \
     0U), \
    (ENET_IAUR_REG(PeripheralBase) = \
     0U) \
  )

/* ----------------------------------------------------------------------------
   -- SetMulticastAddrHashTableBit
   ---------------------------------------------------------------------------- */

/**
 * @brief Raises the specified bit in the multicast (group) address hash table.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Index Multicast hash table bit index. This parameter is a 6-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ENET_GALR, ENET_GAUR
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      ENET_PDD_SetMulticastAddrHashTableBit(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define ENET_PDD_SetMulticastAddrHashTableBit(PeripheralBase, Index) ( \
    ((uint8_t)((uint8_t)(Index) & 0x20U) == 0U) ? ( \
      ENET_GALR_REG(PeripheralBase) |= \
       (uint32_t)((uint32_t)0x1U << (uint8_t)(Index))) : ( \
      ENET_GAUR_REG(PeripheralBase) |= \
       (uint32_t)((uint32_t)0x1U << (uint8_t)((uint8_t)(Index) & 0x1FU))) \
  )

/* ----------------------------------------------------------------------------
   -- ClearMulticastAddrHashTable
   ---------------------------------------------------------------------------- */

/**
 * @brief Clears all bits in the multicast (group) address hash table.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ENET_GALR, ENET_GAUR
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      ENET_PDD_ClearMulticastAddrHashTable(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define ENET_PDD_ClearMulticastAddrHashTable(PeripheralBase) ( \
    (ENET_GALR_REG(PeripheralBase) = \
     0U), \
    (ENET_GAUR_REG(PeripheralBase) = \
     0U) \
  )

/* ----------------------------------------------------------------------------
   -- SetTxRingStartAddr
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the start address of the transmit buffer descriptor ring.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Address Pointer to the start of the transmit buffer descriptor ring.
 *        This parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ENET_TDSR.
 * @par Example:
 *      @code
 *      ENET_PDD_SetTxRingStartAddr(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define ENET_PDD_SetTxRingStartAddr(PeripheralBase, Address) ( \
    ENET_TDSR_REG(PeripheralBase) = \
     (uint32_t)(Address) \
  )

/* ----------------------------------------------------------------------------
   -- SetRxRingStartAddr
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the start address of the receive buffer descriptor ring.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Address Pointer to the start of the receive buffer descriptor ring.
 *        This parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ENET_RDSR.
 * @par Example:
 *      @code
 *      ENET_PDD_SetRxRingStartAddr(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define ENET_PDD_SetRxRingStartAddr(PeripheralBase, Address) ( \
    ENET_RDSR_REG(PeripheralBase) = \
     (uint32_t)(Address) \
  )

/* ----------------------------------------------------------------------------
   -- EnableEnhancedBufferDesc
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)))
/**
 * @brief Enables/disables enhanced buffer descriptors containing additional
 * information (e.g. timestamps).
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Enable Enable flag. This parameter is of "Global enumeration used for
 *        specifying general enable/disable states (PDD_DISABLE and PDD_ENABLE
 *        defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ENET_ECR.
 * @par Example:
 *      @code
 *      ENET_PDD_EnableEnhancedBufferDesc(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
  #define ENET_PDD_EnableEnhancedBufferDesc(PeripheralBase, Enable) ( \
      ((Enable) == PDD_DISABLE) ? ( \
        ENET_ECR_REG(PeripheralBase) &= \
         (uint32_t)((uint32_t)(~(uint32_t)ENET_ECR_EN1588_MASK) & (uint32_t)(~(uint32_t)0x20U))) : ( \
        ENET_ECR_REG(PeripheralBase) = \
         (uint32_t)(( \
          (uint32_t)(ENET_ECR_REG(PeripheralBase) | ENET_ECR_EN1588_MASK)) & ( \
          (uint32_t)(~(uint32_t)0x20U)))) \
    )
#else /* (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) */
/**
 * @brief Enables/disables enhanced buffer descriptors containing additional
 * information (e.g. timestamps).
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Enable Enable flag. This parameter is of "Global enumeration used for
 *        specifying general enable/disable states (PDD_DISABLE and PDD_ENABLE
 *        defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ENET_ECR.
 * @par Example:
 *      @code
 *      ENET_PDD_EnableEnhancedBufferDesc(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
  #define ENET_PDD_EnableEnhancedBufferDesc(PeripheralBase, Enable) ( \
      ((Enable) == PDD_DISABLE) ? ( \
        ENET_ECR_REG(PeripheralBase) &= \
         (uint32_t)(~(uint32_t)ENET_ECR_EN1588_MASK)) : ( \
        ENET_ECR_REG(PeripheralBase) |= \
         ENET_ECR_EN1588_MASK) \
    )
#endif /* (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) */

/* ----------------------------------------------------------------------------
   -- EnableDebug
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)))
/**
 * @brief Enables/disables MAC freeze mode when the processor is in debug mode.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Enable Enable flag. This parameter is of "Global enumeration used for
 *        specifying general enable/disable states (PDD_DISABLE and PDD_ENABLE
 *        defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ENET_ECR.
 * @par Example:
 *      @code
 *      ENET_PDD_EnableDebug(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
  #define ENET_PDD_EnableDebug(PeripheralBase, Enable) ( \
      ((Enable) == PDD_DISABLE) ? ( \
        ENET_ECR_REG(PeripheralBase) &= \
         (uint32_t)((uint32_t)(~(uint32_t)ENET_ECR_DBGEN_MASK) & (uint32_t)(~(uint32_t)0x20U))) : ( \
        ENET_ECR_REG(PeripheralBase) = \
         (uint32_t)(( \
          (uint32_t)(ENET_ECR_REG(PeripheralBase) | ENET_ECR_DBGEN_MASK)) & ( \
          (uint32_t)(~(uint32_t)0x20U)))) \
    )
#else /* (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) */
/**
 * @brief Enables/disables MAC freeze mode when the processor is in debug mode.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Enable Enable flag. This parameter is of "Global enumeration used for
 *        specifying general enable/disable states (PDD_DISABLE and PDD_ENABLE
 *        defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ENET_ECR.
 * @par Example:
 *      @code
 *      ENET_PDD_EnableDebug(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
  #define ENET_PDD_EnableDebug(PeripheralBase, Enable) ( \
      ((Enable) == PDD_DISABLE) ? ( \
        ENET_ECR_REG(PeripheralBase) &= \
         (uint32_t)(~(uint32_t)ENET_ECR_DBGEN_MASK)) : ( \
        ENET_ECR_REG(PeripheralBase) |= \
         ENET_ECR_DBGEN_MASK) \
    )
#endif /* (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) */

/* ----------------------------------------------------------------------------
   -- SetPowerSavingMode
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)))
/**
 * @brief Enables/disables power saving mode with optional magic packet
 * detection.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mode Power saving mode. This parameter is of "Power saving modes" type.
 * @param WakeUp Wake-up mode. This parameter is of "Global enumeration used for
 *        specifying general enable/disable states (PDD_DISABLE and PDD_ENABLE
 *        defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ENET_ECR.
 * @par Example:
 *      @code
 *      ENET_PDD_SetPowerSavingMode(<peripheral>_BASE_PTR, ENET_PDD_SLEEP,
 *      PDD_DISABLE);
 *      @endcode
 */
  #define ENET_PDD_SetPowerSavingMode(PeripheralBase, Mode, WakeUp) ( \
      ( \
       ((WakeUp) == PDD_DISABLE) ? ( \
        ENET_ECR_REG(PeripheralBase) &= \
         (uint32_t)((uint32_t)(~(uint32_t)ENET_ECR_MAGICEN_MASK) & (uint32_t)(~(uint32_t)0x20U))) : ( \
        ENET_ECR_REG(PeripheralBase) = \
         (uint32_t)(( \
          (uint32_t)(ENET_ECR_REG(PeripheralBase) | ENET_ECR_MAGICEN_MASK)) & ( \
          (uint32_t)(~(uint32_t)0x20U)))) \
      ), \
      (( \
       ((Mode) == ENET_PDD_SLEEP) ? ( \
        ENET_ECR_REG(PeripheralBase) = \
         (uint32_t)(( \
          (uint32_t)(ENET_ECR_REG(PeripheralBase) | ENET_ECR_SLEEP_MASK)) & ( \
          (uint32_t)(~(uint32_t)0x20U)))) : (((Mode) == ENET_PDD_STOP) ? ( \
        ENET_ECR_REG(PeripheralBase) &= \
         (uint32_t)((uint32_t)(~(uint32_t)ENET_ECR_SLEEP_MASK) & (uint32_t)(~(uint32_t)0x20U))) : ( \
        ENET_ECR_REG(PeripheralBase) &= \
         (uint32_t)((uint32_t)(~(uint32_t)ENET_ECR_SLEEP_MASK) & (uint32_t)(~(uint32_t)0x20U))) \
      )), \
      ( \
       ((Mode) == ENET_PDD_SLEEP) ? ( \
        ENET_ECR_REG(PeripheralBase) &= \
         (uint32_t)((uint32_t)(~(uint32_t)ENET_ECR_STOPEN_MASK) & (uint32_t)(~(uint32_t)0x20U))) : (((Mode) == ENET_PDD_STOP) ? ( \
        ENET_ECR_REG(PeripheralBase) = \
         (uint32_t)(( \
          (uint32_t)(ENET_ECR_REG(PeripheralBase) | ENET_ECR_STOPEN_MASK)) & ( \
          (uint32_t)(~(uint32_t)0x20U)))) : ( \
        ENET_ECR_REG(PeripheralBase) &= \
         (uint32_t)((uint32_t)(~(uint32_t)ENET_ECR_STOPEN_MASK) & (uint32_t)(~(uint32_t)0x20U))) \
      ))) \
    )
#else /* (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) */
/**
 * @brief Enables/disables power saving mode with optional magic packet
 * detection.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mode Power saving mode. This parameter is of "Power saving modes" type.
 * @param WakeUp Wake-up mode. This parameter is of "Global enumeration used for
 *        specifying general enable/disable states (PDD_DISABLE and PDD_ENABLE
 *        defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ENET_ECR.
 * @par Example:
 *      @code
 *      ENET_PDD_SetPowerSavingMode(<peripheral>_BASE_PTR, ENET_PDD_SLEEP,
 *      PDD_DISABLE);
 *      @endcode
 */
  #define ENET_PDD_SetPowerSavingMode(PeripheralBase, Mode, WakeUp) ( \
      ( \
       ((WakeUp) == PDD_DISABLE) ? ( \
        ENET_ECR_REG(PeripheralBase) &= \
         (uint32_t)(~(uint32_t)ENET_ECR_MAGICEN_MASK)) : ( \
        ENET_ECR_REG(PeripheralBase) |= \
         ENET_ECR_MAGICEN_MASK) \
      ), \
      (( \
       ((Mode) == ENET_PDD_SLEEP) ? ( \
        ENET_ECR_REG(PeripheralBase) |= \
         ENET_ECR_SLEEP_MASK) : (((Mode) == ENET_PDD_STOP) ? ( \
        ENET_ECR_REG(PeripheralBase) &= \
         (uint32_t)(~(uint32_t)ENET_ECR_SLEEP_MASK)) : ( \
        ENET_ECR_REG(PeripheralBase) &= \
         (uint32_t)(~(uint32_t)ENET_ECR_SLEEP_MASK)) \
      )), \
      ( \
       ((Mode) == ENET_PDD_SLEEP) ? ( \
        ENET_ECR_REG(PeripheralBase) &= \
         (uint32_t)(~(uint32_t)ENET_ECR_STOPEN_MASK)) : (((Mode) == ENET_PDD_STOP) ? ( \
        ENET_ECR_REG(PeripheralBase) |= \
         ENET_ECR_STOPEN_MASK) : ( \
        ENET_ECR_REG(PeripheralBase) &= \
         (uint32_t)(~(uint32_t)ENET_ECR_STOPEN_MASK)) \
      ))) \
    )
#endif /* (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) */

/* ----------------------------------------------------------------------------
   -- EnableMIBCounters
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables/disables MIB counters.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Enable Enable flag. This parameter is of "Global enumeration used for
 *        specifying general enable/disable states (PDD_DISABLE and PDD_ENABLE
 *        defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ENET_MIBC.
 * @par Example:
 *      @code
 *      ENET_PDD_EnableMIBCounters(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define ENET_PDD_EnableMIBCounters(PeripheralBase, Enable) ( \
    ((Enable) == PDD_DISABLE) ? ( \
      ENET_MIBC_REG(PeripheralBase) |= \
       ENET_MIBC_MIB_DIS_MASK) : ( \
      ENET_MIBC_REG(PeripheralBase) &= \
       (uint32_t)(~(uint32_t)ENET_MIBC_MIB_DIS_MASK)) \
  )

/* ----------------------------------------------------------------------------
   -- ClearMIBCounters
   ---------------------------------------------------------------------------- */

/**
 * @brief Clears MIB counters.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ENET_MIBC.
 * @par Example:
 *      @code
 *      ENET_PDD_ClearMIBCounters(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define ENET_PDD_ClearMIBCounters(PeripheralBase) ( \
    (ENET_MIBC_REG(PeripheralBase) |= \
     ENET_MIBC_MIB_CLEAR_MASK), \
    (ENET_MIBC_REG(PeripheralBase) &= \
     (uint32_t)(~(uint32_t)ENET_MIBC_MIB_CLEAR_MASK)) \
  )

/* ----------------------------------------------------------------------------
   -- IsMIBIdle
   ---------------------------------------------------------------------------- */

/**
 * @brief Indicates whether the MIB is in the idle state.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: ENET_MIBC.
 * @par Example:
 *      @code
 *      uint32_t result = ENET_PDD_IsMIBIdle(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define ENET_PDD_IsMIBIdle(PeripheralBase) ( \
    (uint32_t)(ENET_MIBC_REG(PeripheralBase) & ENET_MIBC_MIB_IDLE_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- GetMIBCounter
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)))
/**
 * @brief Returns the specified MIB counter value.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Counter MIB counter index. Use constants from group "Message
 *        Information Block counter indices". This parameter is 32 bits wide.
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: ENET_RMON_T_DROP,
 *          ENET_RMON_T_PACKETS (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result = ENET_PDD_GetMIBCounter(<peripheral>_BASE_PTR,
 *      ENET_PDD_RMON_T_DROP);
 *      @endcode
 */
  #define ENET_PDD_GetMIBCounter(PeripheralBase, Counter) ( \
      *(volatile uint32_t*)((uint32_t)(&ENET_RMON_T_PACKETS_REG(PeripheralBase)) + (((uint32_t)(Counter) - 1U) * 4U)) \
    )
#else /* (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) */
/**
 * @brief Returns the specified MIB counter value.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Counter MIB counter index. Use constants from group "Message
 *        Information Block counter indices". This parameter is 32 bits wide.
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: ENET_RMON_T_DROP,
 *          ENET_RMON_T_PACKETS (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result = ENET_PDD_GetMIBCounter(<peripheral>_BASE_PTR,
 *      ENET_PDD_RMON_T_DROP);
 *      @endcode
 */
  #define ENET_PDD_GetMIBCounter(PeripheralBase, Counter) ( \
      *(volatile uint32_t*)((uint32_t)(&ENET_RMON_T_DROP_REG(PeripheralBase)) + ((uint32_t)(Counter) * 4U)) \
    )
#endif /* (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) */

/* ----------------------------------------------------------------------------
   -- IsGracefulRxStop
   ---------------------------------------------------------------------------- */

/**
 * @brief Indicates whether receive has gracefully stopped.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: ENET_RCR.
 * @par Example:
 *      @code
 *      uint32_t result = ENET_PDD_IsGracefulRxStop(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define ENET_PDD_IsGracefulRxStop(PeripheralBase) ( \
    (uint32_t)(ENET_RCR_REG(PeripheralBase) & ENET_RCR_GRS_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- EnableRxPayloadLengthCheck
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)))
/**
 * @brief Enables/disables received frame payload length check with frame
 * length/type field.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Enable Enable flag. This parameter is of "Global enumeration used for
 *        specifying general enable/disable states (PDD_DISABLE and PDD_ENABLE
 *        defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ENET_RCR.
 * @par Example:
 *      @code
 *      ENET_PDD_EnableRxPayloadLengthCheck(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
  #define ENET_PDD_EnableRxPayloadLengthCheck(PeripheralBase, Enable) ( \
      ((Enable) == PDD_DISABLE) ? ( \
        ENET_RCR_REG(PeripheralBase) &= \
         (uint32_t)(( \
          (uint32_t)(~(uint32_t)ENET_RCR_NLC_MASK)) & (( \
          (uint32_t)(~(uint32_t)0x40U)) & (( \
          (uint32_t)(~(uint32_t)0x80U)) & ( \
          (uint32_t)(~(uint32_t)0xC00U)))))) : ( \
        ENET_RCR_REG(PeripheralBase) = \
         (uint32_t)(( \
          (uint32_t)(ENET_RCR_REG(PeripheralBase) | ENET_RCR_NLC_MASK)) & (( \
          (uint32_t)(~(uint32_t)0x40U)) & (( \
          (uint32_t)(~(uint32_t)0x80U)) & ( \
          (uint32_t)(~(uint32_t)0xC00U)))))) \
    )
#else /* (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) */
/**
 * @brief Enables/disables received frame payload length check with frame
 * length/type field.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Enable Enable flag. This parameter is of "Global enumeration used for
 *        specifying general enable/disable states (PDD_DISABLE and PDD_ENABLE
 *        defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ENET_RCR.
 * @par Example:
 *      @code
 *      ENET_PDD_EnableRxPayloadLengthCheck(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
  #define ENET_PDD_EnableRxPayloadLengthCheck(PeripheralBase, Enable) ( \
      ((Enable) == PDD_DISABLE) ? ( \
        ENET_RCR_REG(PeripheralBase) &= \
         (uint32_t)(~(uint32_t)ENET_RCR_NLC_MASK)) : ( \
        ENET_RCR_REG(PeripheralBase) |= \
         ENET_RCR_NLC_MASK) \
    )
#endif /* (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) */

/* ----------------------------------------------------------------------------
   -- SetMaxFrameLength
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)))
/**
 * @brief Sets the maximum frame length.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Length Maximum frame length. This parameter is a 14-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ENET_RCR.
 * @par Example:
 *      @code
 *      ENET_PDD_SetMaxFrameLength(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
  #define ENET_PDD_SetMaxFrameLength(PeripheralBase, Length) ( \
      ENET_RCR_REG(PeripheralBase) = \
       (uint32_t)(( \
        (uint32_t)(( \
         ENET_RCR_REG(PeripheralBase)) & (( \
         (uint32_t)(~(uint32_t)ENET_RCR_MAX_FL_MASK)) & (( \
         (uint32_t)(~(uint32_t)0x40U)) & (( \
         (uint32_t)(~(uint32_t)0x80U)) & ( \
         (uint32_t)(~(uint32_t)0xC00U))))))) | ( \
        (uint32_t)((uint32_t)(Length) << ENET_RCR_MAX_FL_SHIFT))) \
    )
#else /* (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) */
/**
 * @brief Sets the maximum frame length.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Length Maximum frame length. This parameter is a 14-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ENET_RCR.
 * @par Example:
 *      @code
 *      ENET_PDD_SetMaxFrameLength(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
  #define ENET_PDD_SetMaxFrameLength(PeripheralBase, Length) ( \
      ENET_RCR_REG(PeripheralBase) = \
       (uint32_t)(( \
        (uint32_t)(ENET_RCR_REG(PeripheralBase) & (uint32_t)(~(uint32_t)ENET_RCR_MAX_FL_MASK))) | ( \
        (uint32_t)((uint32_t)(Length) << ENET_RCR_MAX_FL_SHIFT))) \
    )
#endif /* (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) */

/* ----------------------------------------------------------------------------
   -- EnableControlFrames
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)))
/**
 * @brief Enables selected ethernet control frames of specified types. Disables
 * not selected ones.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mask Control frame type mask. Use constants from group "Control frame
 *        types". This parameter is 32 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ENET_RCR.
 * @par Example:
 *      @code
 *      ENET_PDD_EnableControlFrames(<peripheral>_BASE_PTR, ENET_PDD_PAUSE);
 *      @endcode
 */
  #define ENET_PDD_EnableControlFrames(PeripheralBase, Mask) ( \
      ENET_RCR_REG(PeripheralBase) = \
       (uint32_t)(( \
        (uint32_t)(( \
         ENET_RCR_REG(PeripheralBase)) & (( \
         (uint32_t)(~(uint32_t)(ENET_RCR_CFEN_MASK | ENET_RCR_PAUFWD_MASK))) & (( \
         (uint32_t)(~(uint32_t)0x40U)) & (( \
         (uint32_t)(~(uint32_t)0x80U)) & ( \
         (uint32_t)(~(uint32_t)0xC00U))))))) | ( \
        (uint32_t)((uint32_t)(Mask) ^ ENET_RCR_CFEN_MASK))) \
    )
#else /* (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) */
/**
 * @brief Enables selected ethernet control frames of specified types. Disables
 * not selected ones.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mask Control frame type mask. Use constants from group "Control frame
 *        types". This parameter is 32 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ENET_RCR.
 * @par Example:
 *      @code
 *      ENET_PDD_EnableControlFrames(<peripheral>_BASE_PTR, ENET_PDD_PAUSE);
 *      @endcode
 */
  #define ENET_PDD_EnableControlFrames(PeripheralBase, Mask) ( \
      ENET_RCR_REG(PeripheralBase) = \
       (uint32_t)(( \
        (uint32_t)(( \
         ENET_RCR_REG(PeripheralBase)) & ( \
         (uint32_t)(~(uint32_t)(ENET_RCR_CFEN_MASK | ENET_RCR_PAUFWD_MASK))))) | ( \
        (uint32_t)((uint32_t)(Mask) ^ ENET_RCR_CFEN_MASK))) \
    )
#endif /* (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) */

/* ----------------------------------------------------------------------------
   -- EnableRxFrameProcessing
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)))
/**
 * @brief Enables selected types of received frame processing. Disables not
 * selected ones.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mask Processing type mask. This parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ENET_RCR.
 * @par Example:
 *      @code
 *      ENET_PDD_EnableRxFrameProcessing(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
  #define ENET_PDD_EnableRxFrameProcessing(PeripheralBase, Mask) ( \
      ENET_RCR_REG(PeripheralBase) = \
       (uint32_t)(( \
        (uint32_t)(( \
         ENET_RCR_REG(PeripheralBase)) & (( \
         (uint32_t)(~(uint32_t)(ENET_RCR_CRCFWD_MASK | ENET_RCR_PADEN_MASK))) & (( \
         (uint32_t)(~(uint32_t)0x40U)) & (( \
         (uint32_t)(~(uint32_t)0x80U)) & ( \
         (uint32_t)(~(uint32_t)0xC00U))))))) | ( \
        (uint32_t)(Mask))) \
    )
#else /* (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) */
/**
 * @brief Enables selected types of received frame processing. Disables not
 * selected ones.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mask Processing type mask. This parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ENET_RCR.
 * @par Example:
 *      @code
 *      ENET_PDD_EnableRxFrameProcessing(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
  #define ENET_PDD_EnableRxFrameProcessing(PeripheralBase, Mask) ( \
      ENET_RCR_REG(PeripheralBase) = \
       (uint32_t)(( \
        (uint32_t)(( \
         ENET_RCR_REG(PeripheralBase)) & ( \
         (uint32_t)(~(uint32_t)(ENET_RCR_CRCFWD_MASK | ENET_RCR_PADEN_MASK))))) | ( \
        (uint32_t)(Mask))) \
    )
#endif /* (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) */

/* ----------------------------------------------------------------------------
   -- SetMIIMode
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)))
/**
 * @brief Sets MII mode.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mode MII mode. This parameter is of "MII modes" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ENET_RCR.
 * @par Example:
 *      @code
 *      ENET_PDD_SetMIIMode(<peripheral>_BASE_PTR, ENET_PDD_MII);
 *      @endcode
 */
  #define ENET_PDD_SetMIIMode(PeripheralBase, Mode) ( \
      ((Mode) == ENET_PDD_MII) ? ( \
        ENET_RCR_REG(PeripheralBase) = \
         (uint32_t)(( \
          (uint32_t)(ENET_RCR_REG(PeripheralBase) | ENET_RCR_MII_MODE_MASK)) & (( \
          (uint32_t)(~(uint32_t)ENET_RCR_RMII_MODE_MASK)) & (( \
          (uint32_t)(~(uint32_t)ENET_RCR_RMII_10T_MASK)) & (( \
          (uint32_t)(~(uint32_t)0x40U)) & (( \
          (uint32_t)(~(uint32_t)0x80U)) & ( \
          (uint32_t)(~(uint32_t)0xC00U)))))))) : (((Mode) == ENET_PDD_RMII_10MBIT) ? ( \
        ENET_RCR_REG(PeripheralBase) = \
         (uint32_t)(( \
          (uint32_t)(( \
           ENET_RCR_REG(PeripheralBase)) | (( \
           ENET_RCR_MII_MODE_MASK) | (( \
           ENET_RCR_RMII_MODE_MASK) | ( \
           ENET_RCR_RMII_10T_MASK))))) & (( \
          (uint32_t)(~(uint32_t)0x40U)) & (( \
          (uint32_t)(~(uint32_t)0x80U)) & ( \
          (uint32_t)(~(uint32_t)0xC00U)))))) : ( \
        ENET_RCR_REG(PeripheralBase) = \
         (uint32_t)(( \
          (uint32_t)(( \
           ENET_RCR_REG(PeripheralBase)) | (( \
           ENET_RCR_MII_MODE_MASK) | ( \
           ENET_RCR_RMII_MODE_MASK)))) & (( \
          (uint32_t)(~(uint32_t)ENET_RCR_RMII_10T_MASK)) & (( \
          (uint32_t)(~(uint32_t)0x40U)) & (( \
          (uint32_t)(~(uint32_t)0x80U)) & ( \
          (uint32_t)(~(uint32_t)0xC00U))))))) \
      ) \
    )
#else /* (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) */
/**
 * @brief Sets MII mode.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mode MII mode. This parameter is of "MII modes" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ENET_RCR.
 * @par Example:
 *      @code
 *      ENET_PDD_SetMIIMode(<peripheral>_BASE_PTR, ENET_PDD_MII);
 *      @endcode
 */
  #define ENET_PDD_SetMIIMode(PeripheralBase, Mode) ( \
      ((Mode) == ENET_PDD_MII) ? ( \
        ENET_RCR_REG(PeripheralBase) = \
         (uint32_t)(( \
          (uint32_t)(ENET_RCR_REG(PeripheralBase) | ENET_RCR_MII_MODE_MASK)) & (( \
          (uint32_t)(~(uint32_t)ENET_RCR_RMII_MODE_MASK)) & ( \
          (uint32_t)(~(uint32_t)ENET_RCR_RMII_10T_MASK))))) : (((Mode) == ENET_PDD_RMII_10MBIT) ? ( \
        ENET_RCR_REG(PeripheralBase) |= \
         (uint32_t)(ENET_RCR_MII_MODE_MASK | (ENET_RCR_RMII_MODE_MASK | ENET_RCR_RMII_10T_MASK))) : ( \
        ENET_RCR_REG(PeripheralBase) = \
         (uint32_t)(( \
          (uint32_t)(( \
           ENET_RCR_REG(PeripheralBase)) | (( \
           ENET_RCR_MII_MODE_MASK) | ( \
           ENET_RCR_RMII_MODE_MASK)))) & ( \
          (uint32_t)(~(uint32_t)ENET_RCR_RMII_10T_MASK)))) \
      ) \
    )
#endif /* (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) */

/* ----------------------------------------------------------------------------
   -- EnableFlowControl
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)))
/**
 * @brief Enables/disables automatic flow control. If enabled, the receiver
 * detects pause frames and stops the transmitter for a given duration.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Enable Enable flag. This parameter is of "Global enumeration used for
 *        specifying general enable/disable states (PDD_DISABLE and PDD_ENABLE
 *        defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ENET_RCR.
 * @par Example:
 *      @code
 *      ENET_PDD_EnableFlowControl(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
  #define ENET_PDD_EnableFlowControl(PeripheralBase, Enable) ( \
      ((Enable) == PDD_DISABLE) ? ( \
        ENET_RCR_REG(PeripheralBase) &= \
         (uint32_t)(( \
          (uint32_t)(~(uint32_t)ENET_RCR_FCE_MASK)) & (( \
          (uint32_t)(~(uint32_t)0x40U)) & (( \
          (uint32_t)(~(uint32_t)0x80U)) & ( \
          (uint32_t)(~(uint32_t)0xC00U)))))) : ( \
        ENET_RCR_REG(PeripheralBase) = \
         (uint32_t)(( \
          (uint32_t)(ENET_RCR_REG(PeripheralBase) | ENET_RCR_FCE_MASK)) & (( \
          (uint32_t)(~(uint32_t)0x40U)) & (( \
          (uint32_t)(~(uint32_t)0x80U)) & ( \
          (uint32_t)(~(uint32_t)0xC00U)))))) \
    )
#else /* (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) */
/**
 * @brief Enables/disables automatic flow control. If enabled, the receiver
 * detects pause frames and stops the transmitter for a given duration.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Enable Enable flag. This parameter is of "Global enumeration used for
 *        specifying general enable/disable states (PDD_DISABLE and PDD_ENABLE
 *        defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ENET_RCR.
 * @par Example:
 *      @code
 *      ENET_PDD_EnableFlowControl(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
  #define ENET_PDD_EnableFlowControl(PeripheralBase, Enable) ( \
      ((Enable) == PDD_DISABLE) ? ( \
        ENET_RCR_REG(PeripheralBase) &= \
         (uint32_t)(~(uint32_t)ENET_RCR_FCE_MASK)) : ( \
        ENET_RCR_REG(PeripheralBase) |= \
         ENET_RCR_FCE_MASK) \
    )
#endif /* (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) */

/* ----------------------------------------------------------------------------
   -- EnableInternalLoopback
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)))
/**
 * @brief Enables/disables internal loopback mode.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Enable Enable flag. This parameter is of "Global enumeration used for
 *        specifying general enable/disable states (PDD_DISABLE and PDD_ENABLE
 *        defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ENET_RCR.
 * @par Example:
 *      @code
 *      ENET_PDD_EnableInternalLoopback(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
  #define ENET_PDD_EnableInternalLoopback(PeripheralBase, Enable) ( \
      ((Enable) == PDD_DISABLE) ? ( \
        ENET_RCR_REG(PeripheralBase) &= \
         (uint32_t)(( \
          (uint32_t)(~(uint32_t)ENET_RCR_LOOP_MASK)) & (( \
          (uint32_t)(~(uint32_t)0x40U)) & (( \
          (uint32_t)(~(uint32_t)0x80U)) & ( \
          (uint32_t)(~(uint32_t)0xC00U)))))) : ( \
        ENET_RCR_REG(PeripheralBase) = \
         (uint32_t)(( \
          (uint32_t)(ENET_RCR_REG(PeripheralBase) | ENET_RCR_LOOP_MASK)) & (( \
          (uint32_t)(~(uint32_t)0x40U)) & (( \
          (uint32_t)(~(uint32_t)0x80U)) & ( \
          (uint32_t)(~(uint32_t)0xC00U)))))) \
    )
#else /* (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) */
/**
 * @brief Enables/disables internal loopback mode.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Enable Enable flag. This parameter is of "Global enumeration used for
 *        specifying general enable/disable states (PDD_DISABLE and PDD_ENABLE
 *        defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ENET_RCR.
 * @par Example:
 *      @code
 *      ENET_PDD_EnableInternalLoopback(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
  #define ENET_PDD_EnableInternalLoopback(PeripheralBase, Enable) ( \
      ((Enable) == PDD_DISABLE) ? ( \
        ENET_RCR_REG(PeripheralBase) &= \
         (uint32_t)(~(uint32_t)ENET_RCR_LOOP_MASK)) : ( \
        ENET_RCR_REG(PeripheralBase) |= \
         ENET_RCR_LOOP_MASK) \
    )
#endif /* (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) */

/* ----------------------------------------------------------------------------
   -- EnableTxFrameProcessing
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables selected type of transmitted frames processing. Disables not
 * selected ones.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mask Processing type. Use constants from group "Transmit frame
 *        processing types". This parameter is 32 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ENET_TCR.
 * @par Example:
 *      @code
 *      ENET_PDD_EnableTxFrameProcessing(<peripheral>_BASE_PTR,
 *      ENET_PDD_CRC_INSERT);
 *      @endcode
 */
#define ENET_PDD_EnableTxFrameProcessing(PeripheralBase, Mask) ( \
    ENET_TCR_REG(PeripheralBase) = \
     (uint32_t)((uint32_t)(Mask) ^ ENET_TCR_CRCFWD_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- SelectMACAddress
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)))
/**
 * @brief Specifies which MAC address is used as frame source MAC address.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Selection Source MAC address selection. This parameter is of "MAC
 *        address sources" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ENET_TCR.
 * @par Example:
 *      @code
 *      ENET_PDD_SelectMACAddress(<peripheral>_BASE_PTR, ENET_PDD_KEEP);
 *      @endcode
 */
  #define ENET_PDD_SelectMACAddress(PeripheralBase, Selection) ( \
      ((Selection) == ENET_PDD_KEEP) ? ( \
        ENET_TCR_REG(PeripheralBase) &= \
         (uint32_t)(( \
          (uint32_t)(~(uint32_t)ENET_TCR_ADDINS_MASK)) & (( \
          (uint32_t)(~(uint32_t)ENET_TCR_ADDSEL_MASK)) & ( \
          (uint32_t)(~(uint32_t)0x2U))))) : (((Selection) == ENET_PDD_AUTO) ? ( \
        ENET_TCR_REG(PeripheralBase) = \
         (uint32_t)(( \
          (uint32_t)(ENET_TCR_REG(PeripheralBase) | ENET_TCR_ADDINS_MASK)) & (( \
          (uint32_t)(~(uint32_t)ENET_TCR_ADDSEL_MASK)) & ( \
          (uint32_t)(~(uint32_t)0x2U))))) : (((Selection) == ENET_PDD_AUTO_SUPPL0) ? ( \
        ENET_TCR_REG(PeripheralBase) = \
         (uint32_t)(( \
          (uint32_t)(( \
           (uint32_t)(ENET_TCR_REG(PeripheralBase) | ENET_TCR_ADDINS_MASK)) & (( \
           (uint32_t)(~(uint32_t)ENET_TCR_ADDSEL_MASK)) & ( \
           (uint32_t)(~(uint32_t)0x2U))))) | ( \
          (uint32_t)((uint32_t)0x4U << ENET_TCR_ADDSEL_SHIFT)))) : (((Selection) == ENET_PDD_AUTO_SUPPL1) ? ( \
        ENET_TCR_REG(PeripheralBase) = \
         (uint32_t)(( \
          (uint32_t)(( \
           (uint32_t)(ENET_TCR_REG(PeripheralBase) | ENET_TCR_ADDINS_MASK)) & (( \
           (uint32_t)(~(uint32_t)ENET_TCR_ADDSEL_MASK)) & ( \
           (uint32_t)(~(uint32_t)0x2U))))) | ( \
          (uint32_t)((uint32_t)0x5U << ENET_TCR_ADDSEL_SHIFT)))) : (((Selection) == ENET_PDD_AUTO_SUPPL2) ? ( \
        ENET_TCR_REG(PeripheralBase) = \
         (uint32_t)(( \
          (uint32_t)(( \
           (uint32_t)(ENET_TCR_REG(PeripheralBase) | ENET_TCR_ADDINS_MASK)) & (( \
           (uint32_t)(~(uint32_t)ENET_TCR_ADDSEL_MASK)) & ( \
           (uint32_t)(~(uint32_t)0x2U))))) | ( \
          (uint32_t)((uint32_t)0x6U << ENET_TCR_ADDSEL_SHIFT)))) : ( \
        ENET_TCR_REG(PeripheralBase) = \
         (uint32_t)(( \
          (uint32_t)(ENET_TCR_REG(PeripheralBase) | (ENET_TCR_ADDINS_MASK | ENET_TCR_ADDSEL_MASK))) & ( \
          (uint32_t)(~(uint32_t)0x2U)))) \
      )))) \
    )
#else /* (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) */
/**
 * @brief Specifies which MAC address is used as frame source MAC address.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Selection Source MAC address selection. This parameter is of "MAC
 *        address sources" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ENET_TCR.
 * @par Example:
 *      @code
 *      ENET_PDD_SelectMACAddress(<peripheral>_BASE_PTR, ENET_PDD_KEEP);
 *      @endcode
 */
  #define ENET_PDD_SelectMACAddress(PeripheralBase, Selection) ( \
      ((Selection) == ENET_PDD_KEEP) ? ( \
        ENET_TCR_REG(PeripheralBase) &= \
         (uint32_t)(( \
          (uint32_t)(~(uint32_t)ENET_TCR_ADDINS_MASK)) & ( \
          (uint32_t)(~(uint32_t)ENET_TCR_ADDSEL_MASK)))) : (((Selection) == ENET_PDD_AUTO) ? ( \
        ENET_TCR_REG(PeripheralBase) = \
         (uint32_t)(( \
          (uint32_t)(ENET_TCR_REG(PeripheralBase) | ENET_TCR_ADDINS_MASK)) & ( \
          (uint32_t)(~(uint32_t)ENET_TCR_ADDSEL_MASK)))) : (((Selection) == ENET_PDD_AUTO_SUPPL0) ? ( \
        ENET_TCR_REG(PeripheralBase) = \
         (uint32_t)(( \
          (uint32_t)(( \
           (uint32_t)(ENET_TCR_REG(PeripheralBase) | ENET_TCR_ADDINS_MASK)) & ( \
           (uint32_t)(~(uint32_t)ENET_TCR_ADDSEL_MASK)))) | ( \
          (uint32_t)((uint32_t)0x4U << ENET_TCR_ADDSEL_SHIFT)))) : (((Selection) == ENET_PDD_AUTO_SUPPL1) ? ( \
        ENET_TCR_REG(PeripheralBase) = \
         (uint32_t)(( \
          (uint32_t)(( \
           (uint32_t)(ENET_TCR_REG(PeripheralBase) | ENET_TCR_ADDINS_MASK)) & ( \
           (uint32_t)(~(uint32_t)ENET_TCR_ADDSEL_MASK)))) | ( \
          (uint32_t)((uint32_t)0x5U << ENET_TCR_ADDSEL_SHIFT)))) : (((Selection) == ENET_PDD_AUTO_SUPPL2) ? ( \
        ENET_TCR_REG(PeripheralBase) = \
         (uint32_t)(( \
          (uint32_t)(( \
           (uint32_t)(ENET_TCR_REG(PeripheralBase) | ENET_TCR_ADDINS_MASK)) & ( \
           (uint32_t)(~(uint32_t)ENET_TCR_ADDSEL_MASK)))) | ( \
          (uint32_t)((uint32_t)0x6U << ENET_TCR_ADDSEL_SHIFT)))) : ( \
        ENET_TCR_REG(PeripheralBase) |= \
         (uint32_t)(ENET_TCR_ADDINS_MASK | ENET_TCR_ADDSEL_MASK)) \
      )))) \
    )
#endif /* (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) */

/* ----------------------------------------------------------------------------
   -- IsTransmissionPaused
   ---------------------------------------------------------------------------- */

/**
 * @brief Indicates whether the transmitter is paused by a pause frame.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: ENET_TCR.
 * @par Example:
 *      @code
 *      uint32_t result = ENET_PDD_IsTransmissionPaused(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define ENET_PDD_IsTransmissionPaused(PeripheralBase) ( \
    (uint32_t)(ENET_TCR_REG(PeripheralBase) & ENET_TCR_TFC_PAUSE_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- StartGracefulTxStop
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)))
/**
 * @brief Initiates a graceful transmit stop.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ENET_TCR.
 * @par Example:
 *      @code
 *      ENET_PDD_StartGracefulTxStop(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define ENET_PDD_StartGracefulTxStop(PeripheralBase) ( \
      ENET_TCR_REG(PeripheralBase) = \
       (uint32_t)(( \
        (uint32_t)(ENET_TCR_REG(PeripheralBase) | ENET_TCR_GTS_MASK)) & ( \
        (uint32_t)(~(uint32_t)0x2U))) \
    )
#else /* (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) */
/**
 * @brief Initiates a graceful transmit stop.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ENET_TCR.
 * @par Example:
 *      @code
 *      ENET_PDD_StartGracefulTxStop(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define ENET_PDD_StartGracefulTxStop(PeripheralBase) ( \
      ENET_TCR_REG(PeripheralBase) |= \
       ENET_TCR_GTS_MASK \
    )
#endif /* (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) */

/* ----------------------------------------------------------------------------
   -- FinishGracefulTxStop
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)))
/**
 * @brief Finishes a graceful transmit stop and enables transmission.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ENET_TCR.
 * @par Example:
 *      @code
 *      ENET_PDD_FinishGracefulTxStop(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define ENET_PDD_FinishGracefulTxStop(PeripheralBase) ( \
      ENET_TCR_REG(PeripheralBase) &= \
       (uint32_t)((uint32_t)(~(uint32_t)ENET_TCR_GTS_MASK) & (uint32_t)(~(uint32_t)0x2U)) \
    )
#else /* (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) */
/**
 * @brief Finishes a graceful transmit stop and enables transmission.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ENET_TCR.
 * @par Example:
 *      @code
 *      ENET_PDD_FinishGracefulTxStop(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define ENET_PDD_FinishGracefulTxStop(PeripheralBase) ( \
      ENET_TCR_REG(PeripheralBase) &= \
       (uint32_t)(~(uint32_t)ENET_TCR_GTS_MASK) \
    )
#endif /* (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) */

/* ----------------------------------------------------------------------------
   -- IsGracefulTxStop
   ---------------------------------------------------------------------------- */

/**
 * @brief Indicates whether transmission is gracefully stopped.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: ENET_TCR.
 * @par Example:
 *      @code
 *      uint32_t result = ENET_PDD_IsGracefulTxStop(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define ENET_PDD_IsGracefulTxStop(PeripheralBase) ( \
    (uint32_t)(ENET_TCR_REG(PeripheralBase) & ENET_TCR_GTS_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- SetTxFIFOWatermark
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the number of bytes written to transmit FIFO before transmission
 * of a frame begins.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Watermark Transmit FIFO watermark. Zero value enables store and
 *        forward, any non-zero value starts transmission after (value x 64) bytes are
 *        written to transmit FIFO. This parameter is a 6-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ENET_TFWR.
 * @par Example:
 *      @code
 *      ENET_PDD_SetTxFIFOWatermark(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define ENET_PDD_SetTxFIFOWatermark(PeripheralBase, Watermark) ( \
    ((uint8_t)(Watermark) == 0U) ? ( \
      (ENET_TFWR_REG(PeripheralBase) |= \
       ENET_TFWR_STRFWD_MASK), \
      (ENET_TFWR_REG(PeripheralBase) = \
       (uint32_t)(( \
        (uint32_t)(ENET_TFWR_REG(PeripheralBase) & (uint32_t)(~(uint32_t)ENET_TFWR_TFWR_MASK))) | ( \
        (uint32_t)(Watermark))))) : ( \
      (ENET_TFWR_REG(PeripheralBase) &= \
       (uint32_t)(~(uint32_t)ENET_TFWR_STRFWD_MASK)), \
      (ENET_TFWR_REG(PeripheralBase) = \
       (uint32_t)(( \
        (uint32_t)(ENET_TFWR_REG(PeripheralBase) & (uint32_t)(~(uint32_t)ENET_TFWR_TFWR_MASK))) | ( \
        (uint32_t)(Watermark))))) \
  )

/* ----------------------------------------------------------------------------
   -- SetRxBufferSize
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the size of receive buffers.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Size Receive buffer size aligned to 16 bytes. This parameter is a
 *        10-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ENET_MRBR.
 * @par Example:
 *      @code
 *      ENET_PDD_SetRxBufferSize(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define ENET_PDD_SetRxBufferSize(PeripheralBase, Size) ( \
    ENET_MRBR_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       ENET_MRBR_REG(PeripheralBase)) & ( \
       (uint32_t)(~(uint32_t)ENET_MRBR_R_BUF_SIZE_MASK)))) | ( \
      (uint32_t)((uint32_t)(Size) << ENET_MRBR_R_BUF_SIZE_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SetRxFIFOSectionFullThreshold
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the receive FIFO section full threshold.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value, in 64-bit words, of the receive FIFO section full
 *        threshold. This parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ENET_RSFL.
 * @par Example:
 *      @code
 *      ENET_PDD_SetRxFIFOSectionFullThreshold(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define ENET_PDD_SetRxFIFOSectionFullThreshold(PeripheralBase, Value) ( \
    ENET_RSFL_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       ENET_RSFL_REG(PeripheralBase)) & ( \
       (uint32_t)(~(uint32_t)ENET_RSFL_RX_SECTION_FULL_MASK)))) | ( \
      (uint32_t)(Value))) \
  )

/* ----------------------------------------------------------------------------
   -- SetRxFIFOSectionEmptyThreshold
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the receive FIFO section empty threshold.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value, in 64-bit words, of the receive FIFO section empty
 *        threshold. This parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ENET_RSEM.
 * @par Example:
 *      @code
 *      ENET_PDD_SetRxFIFOSectionEmptyThreshold(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define ENET_PDD_SetRxFIFOSectionEmptyThreshold(PeripheralBase, Value) ( \
    ENET_RSEM_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       ENET_RSEM_REG(PeripheralBase)) & ( \
       (uint32_t)(~(uint32_t)ENET_RSEM_RX_SECTION_EMPTY_MASK)))) | ( \
      (uint32_t)(Value))) \
  )

/* ----------------------------------------------------------------------------
   -- SetRxFIFOAlmostEmptyThreshold
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the receive FIFO almost full threshold.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value, in 64-bit words, of the receive FIFO almost empty
 *        threshold. This parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ENET_RAEM.
 * @par Example:
 *      @code
 *      ENET_PDD_SetRxFIFOAlmostEmptyThreshold(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define ENET_PDD_SetRxFIFOAlmostEmptyThreshold(PeripheralBase, Value) ( \
    ENET_RAEM_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       ENET_RAEM_REG(PeripheralBase)) & ( \
       (uint32_t)(~(uint32_t)ENET_RAEM_RX_ALMOST_EMPTY_MASK)))) | ( \
      (uint32_t)(Value))) \
  )

/* ----------------------------------------------------------------------------
   -- SetRxFIFOAlmostFullThreshold
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the receive FIFO almost full threshold.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value, in 64-bit words, of the receive FIFO almost full
 *        threshold. This parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ENET_RAFL.
 * @par Example:
 *      @code
 *      ENET_PDD_SetRxFIFOAlmostFullThreshold(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define ENET_PDD_SetRxFIFOAlmostFullThreshold(PeripheralBase, Value) ( \
    ENET_RAFL_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       ENET_RAFL_REG(PeripheralBase)) & ( \
       (uint32_t)(~(uint32_t)ENET_RAFL_RX_ALMOST_FULL_MASK)))) | ( \
      (uint32_t)(Value))) \
  )

/* ----------------------------------------------------------------------------
   -- SetTxFIFOSectionEmptyThreshold
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the transmit FIFO section empty threshold.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value, in 64-bit words, of the transmit FIFO section empty
 *        threshold. This parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ENET_TSEM.
 * @par Example:
 *      @code
 *      ENET_PDD_SetTxFIFOSectionEmptyThreshold(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define ENET_PDD_SetTxFIFOSectionEmptyThreshold(PeripheralBase, Value) ( \
    ENET_TSEM_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       ENET_TSEM_REG(PeripheralBase)) & ( \
       (uint32_t)(~(uint32_t)ENET_TSEM_TX_SECTION_EMPTY_MASK)))) | ( \
      (uint32_t)(Value))) \
  )

/* ----------------------------------------------------------------------------
   -- SetTxFIFOAlmostEmptyThreshold
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the transmit FIFO almost empty threshold.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value, in 64-bit words, of the transmit FIFO almost empty
 *        threshold. This parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ENET_TAEM.
 * @par Example:
 *      @code
 *      ENET_PDD_SetTxFIFOAlmostEmptyThreshold(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define ENET_PDD_SetTxFIFOAlmostEmptyThreshold(PeripheralBase, Value) ( \
    ENET_TAEM_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       ENET_TAEM_REG(PeripheralBase)) & ( \
       (uint32_t)(~(uint32_t)ENET_TAEM_TX_ALMOST_EMPTY_MASK)))) | ( \
      (uint32_t)(Value))) \
  )

/* ----------------------------------------------------------------------------
   -- SetTxFIFOAlmostFullThreshold
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the transmit FIFO almost full threshold.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value, in 64-bit words, of the transmit FIFO almost full
 *        threshold. This parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ENET_TAFL.
 * @par Example:
 *      @code
 *      ENET_PDD_SetTxFIFOAlmostFullThreshold(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define ENET_PDD_SetTxFIFOAlmostFullThreshold(PeripheralBase, Value) ( \
    ENET_TAFL_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       ENET_TAFL_REG(PeripheralBase)) & ( \
       (uint32_t)(~(uint32_t)ENET_TAFL_TX_ALMOST_FULL_MASK)))) | ( \
      (uint32_t)(Value))) \
  )

/* ----------------------------------------------------------------------------
   -- SetTxInterPacketGap
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the transmit inter-packet gap.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param ByteCount Transmit inter-packet gap in bytes. 0 to 7 value is set to
 *        8, 8 to 27 value is set as specified, 28 to 32 value is set to 27. This
 *        parameter is a 5-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ENET_TIPG.
 * @par Example:
 *      @code
 *      ENET_PDD_SetTxInterPacketGap(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define ENET_PDD_SetTxInterPacketGap(PeripheralBase, ByteCount) ( \
    ENET_TIPG_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(ENET_TIPG_REG(PeripheralBase) & (uint32_t)(~(uint32_t)ENET_TIPG_IPG_MASK))) | ( \
      (uint32_t)(ByteCount))) \
  )

/* ----------------------------------------------------------------------------
   -- SetFrameTruncLength
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the frame truncation length.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Length Frame truncation length. This parameter is a 14-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ENET_FTRL.
 * @par Example:
 *      @code
 *      ENET_PDD_SetFrameTruncLength(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define ENET_PDD_SetFrameTruncLength(PeripheralBase, Length) ( \
    ENET_FTRL_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(ENET_FTRL_REG(PeripheralBase) & (uint32_t)(~(uint32_t)ENET_FTRL_TRUNC_FL_MASK))) | ( \
      (uint32_t)(Length))) \
  )

/* ----------------------------------------------------------------------------
   -- SetProtocolChecksumAccelerators
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)))
/**
 * @brief Sets accelerators for known protocols based on protocol cheksums.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mask Protocol checksum accelerators mask. Use constants from group
 *        "Protocol checksum accelerators". This parameter is 32 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ENET_TACC, ENET_RACC
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      ENET_PDD_SetProtocolChecksumAccelerators(<peripheral>_BASE_PTR,
 *      ENET_PDD_INSERT_ON_TX);
 *      @endcode
 */
  #define ENET_PDD_SetProtocolChecksumAccelerators(PeripheralBase, Mask) ( \
      ( \
       ((uint32_t)((uint32_t)(Mask) & 0x1U) == 0U) ? ( \
        ENET_TACC_REG(PeripheralBase) &= \
         (uint32_t)(( \
          (uint32_t)(~(uint32_t)ENET_TACC_PROCHK_MASK)) & (( \
          (uint32_t)(~(uint32_t)0x6U)) & ( \
          (uint32_t)(~(uint32_t)0xFFFFFFE0U))))) : ( \
        ENET_TACC_REG(PeripheralBase) = \
         (uint32_t)(( \
          (uint32_t)(ENET_TACC_REG(PeripheralBase) | ENET_TACC_PROCHK_MASK)) & (( \
          (uint32_t)(~(uint32_t)0x6U)) & ( \
          (uint32_t)(~(uint32_t)0xFFFFFFE0U))))) \
      ), \
      ( \
       ((uint32_t)((uint32_t)(Mask) & 0x2U) == 0U) ? ( \
        ENET_RACC_REG(PeripheralBase) &= \
         (uint32_t)(( \
          (uint32_t)(~(uint32_t)ENET_RACC_PRODIS_MASK)) & (( \
          (uint32_t)(~(uint32_t)0x38U)) & ( \
          (uint32_t)(~(uint32_t)0xFFFFFF00U))))) : ( \
        ENET_RACC_REG(PeripheralBase) = \
         (uint32_t)(( \
          (uint32_t)(ENET_RACC_REG(PeripheralBase) | ENET_RACC_PRODIS_MASK)) & (( \
          (uint32_t)(~(uint32_t)0x38U)) & ( \
          (uint32_t)(~(uint32_t)0xFFFFFF00U))))) \
      ) \
    )
#else /* (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) */
/**
 * @brief Sets accelerators for known protocols based on protocol cheksums.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mask Protocol checksum accelerators mask. Use constants from group
 *        "Protocol checksum accelerators". This parameter is 32 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ENET_TACC, ENET_RACC
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      ENET_PDD_SetProtocolChecksumAccelerators(<peripheral>_BASE_PTR,
 *      ENET_PDD_INSERT_ON_TX);
 *      @endcode
 */
  #define ENET_PDD_SetProtocolChecksumAccelerators(PeripheralBase, Mask) ( \
      ( \
       ((uint32_t)((uint32_t)(Mask) & 0x1U) == 0U) ? ( \
        ENET_TACC_REG(PeripheralBase) &= \
         (uint32_t)(~(uint32_t)ENET_TACC_PROCHK_MASK)) : ( \
        ENET_TACC_REG(PeripheralBase) |= \
         ENET_TACC_PROCHK_MASK) \
      ), \
      ( \
       ((uint32_t)((uint32_t)(Mask) & 0x2U) == 0U) ? ( \
        ENET_RACC_REG(PeripheralBase) &= \
         (uint32_t)(~(uint32_t)ENET_RACC_PRODIS_MASK)) : ( \
        ENET_RACC_REG(PeripheralBase) |= \
         ENET_RACC_PRODIS_MASK) \
      ) \
    )
#endif /* (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) */

/* ----------------------------------------------------------------------------
   -- SetIPHeaderChecksumAccelerators
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)))
/**
 * @brief Sets accelerators for IP header checksum processing.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mask IP header checksum accelerators mask. Use constants from group
 *        "Protocol checksum accelerators". This parameter is 32 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ENET_TACC, ENET_RACC
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      ENET_PDD_SetIPHeaderChecksumAccelerators(<peripheral>_BASE_PTR,
 *      ENET_PDD_INSERT_ON_TX);
 *      @endcode
 */
  #define ENET_PDD_SetIPHeaderChecksumAccelerators(PeripheralBase, Mask) ( \
      ( \
       ((uint32_t)((uint32_t)(Mask) & 0x1U) == 0U) ? ( \
        ENET_TACC_REG(PeripheralBase) &= \
         (uint32_t)(( \
          (uint32_t)(~(uint32_t)ENET_TACC_IPCHK_MASK)) & (( \
          (uint32_t)(~(uint32_t)0x6U)) & ( \
          (uint32_t)(~(uint32_t)0xFFFFFFE0U))))) : ( \
        ENET_TACC_REG(PeripheralBase) = \
         (uint32_t)(( \
          (uint32_t)(ENET_TACC_REG(PeripheralBase) | ENET_TACC_IPCHK_MASK)) & (( \
          (uint32_t)(~(uint32_t)0x6U)) & ( \
          (uint32_t)(~(uint32_t)0xFFFFFFE0U))))) \
      ), \
      ( \
       ((uint32_t)((uint32_t)(Mask) & 0x2U) == 0U) ? ( \
        ENET_RACC_REG(PeripheralBase) &= \
         (uint32_t)(( \
          (uint32_t)(~(uint32_t)ENET_RACC_IPDIS_MASK)) & (( \
          (uint32_t)(~(uint32_t)0x38U)) & ( \
          (uint32_t)(~(uint32_t)0xFFFFFF00U))))) : ( \
        ENET_RACC_REG(PeripheralBase) = \
         (uint32_t)(( \
          (uint32_t)(ENET_RACC_REG(PeripheralBase) | ENET_RACC_IPDIS_MASK)) & (( \
          (uint32_t)(~(uint32_t)0x38U)) & ( \
          (uint32_t)(~(uint32_t)0xFFFFFF00U))))) \
      ) \
    )
#else /* (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) */
/**
 * @brief Sets accelerators for IP header checksum processing.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mask IP header checksum accelerators mask. Use constants from group
 *        "Protocol checksum accelerators". This parameter is 32 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ENET_TACC, ENET_RACC
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      ENET_PDD_SetIPHeaderChecksumAccelerators(<peripheral>_BASE_PTR,
 *      ENET_PDD_INSERT_ON_TX);
 *      @endcode
 */
  #define ENET_PDD_SetIPHeaderChecksumAccelerators(PeripheralBase, Mask) ( \
      ( \
       ((uint32_t)((uint32_t)(Mask) & 0x1U) == 0U) ? ( \
        ENET_TACC_REG(PeripheralBase) &= \
         (uint32_t)(~(uint32_t)ENET_TACC_IPCHK_MASK)) : ( \
        ENET_TACC_REG(PeripheralBase) |= \
         ENET_TACC_IPCHK_MASK) \
      ), \
      ( \
       ((uint32_t)((uint32_t)(Mask) & 0x2U) == 0U) ? ( \
        ENET_RACC_REG(PeripheralBase) &= \
         (uint32_t)(~(uint32_t)ENET_RACC_IPDIS_MASK)) : ( \
        ENET_RACC_REG(PeripheralBase) |= \
         ENET_RACC_IPDIS_MASK) \
      ) \
    )
#endif /* (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) */

/* ----------------------------------------------------------------------------
   -- SetFIFO16BitShift
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)))
/**
 * @brief Enables frame header shifting for transmitted/received frames.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Type Type of frames for which to enable frame header shifting. Use
 *        constants from group "FIFO shift types". This parameter is 32 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ENET_TACC, ENET_RACC
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      ENET_PDD_SetFIFO16BitShift(<peripheral>_BASE_PTR, ENET_PDD_TX_ONLY);
 *      @endcode
 */
  #define ENET_PDD_SetFIFO16BitShift(PeripheralBase, Type) ( \
      ( \
       ((uint32_t)((uint32_t)(Type) & 0x1U) == 0U) ? ( \
        ENET_TACC_REG(PeripheralBase) &= \
         (uint32_t)(( \
          (uint32_t)(~(uint32_t)ENET_TACC_SHIFT16_MASK)) & (( \
          (uint32_t)(~(uint32_t)0x6U)) & ( \
          (uint32_t)(~(uint32_t)0xFFFFFFE0U))))) : ( \
        ENET_TACC_REG(PeripheralBase) = \
         (uint32_t)(( \
          (uint32_t)(ENET_TACC_REG(PeripheralBase) | ENET_TACC_SHIFT16_MASK)) & (( \
          (uint32_t)(~(uint32_t)0x6U)) & ( \
          (uint32_t)(~(uint32_t)0xFFFFFFE0U))))) \
      ), \
      ( \
       ((uint32_t)((uint32_t)(Type) & 0x2U) == 0U) ? ( \
        ENET_RACC_REG(PeripheralBase) &= \
         (uint32_t)(( \
          (uint32_t)(~(uint32_t)ENET_RACC_SHIFT16_MASK)) & (( \
          (uint32_t)(~(uint32_t)0x38U)) & ( \
          (uint32_t)(~(uint32_t)0xFFFFFF00U))))) : ( \
        ENET_RACC_REG(PeripheralBase) = \
         (uint32_t)(( \
          (uint32_t)(ENET_RACC_REG(PeripheralBase) | ENET_RACC_SHIFT16_MASK)) & (( \
          (uint32_t)(~(uint32_t)0x38U)) & ( \
          (uint32_t)(~(uint32_t)0xFFFFFF00U))))) \
      ) \
    )
#else /* (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) */
/**
 * @brief Enables frame header shifting for transmitted/received frames.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Type Type of frames for which to enable frame header shifting. Use
 *        constants from group "FIFO shift types". This parameter is 32 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ENET_TACC, ENET_RACC
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      ENET_PDD_SetFIFO16BitShift(<peripheral>_BASE_PTR, ENET_PDD_TX_ONLY);
 *      @endcode
 */
  #define ENET_PDD_SetFIFO16BitShift(PeripheralBase, Type) ( \
      ( \
       ((uint32_t)((uint32_t)(Type) & 0x1U) == 0U) ? ( \
        ENET_TACC_REG(PeripheralBase) &= \
         (uint32_t)(~(uint32_t)ENET_TACC_SHIFT16_MASK)) : ( \
        ENET_TACC_REG(PeripheralBase) |= \
         ENET_TACC_SHIFT16_MASK) \
      ), \
      ( \
       ((uint32_t)((uint32_t)(Type) & 0x2U) == 0U) ? ( \
        ENET_RACC_REG(PeripheralBase) &= \
         (uint32_t)(~(uint32_t)ENET_RACC_SHIFT16_MASK)) : ( \
        ENET_RACC_REG(PeripheralBase) |= \
         ENET_RACC_SHIFT16_MASK) \
      ) \
    )
#endif /* (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) */

/* ----------------------------------------------------------------------------
   -- EnableMACErrorDrops
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)))
/**
 * @brief Enables/disables frames with MAC error to be dropped by the receiver.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Enable Enable flag. This parameter is of "Global enumeration used for
 *        specifying general enable/disable states (PDD_DISABLE and PDD_ENABLE
 *        defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ENET_RACC.
 * @par Example:
 *      @code
 *      ENET_PDD_EnableMACErrorDrops(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
  #define ENET_PDD_EnableMACErrorDrops(PeripheralBase, Enable) ( \
      ((Enable) == PDD_DISABLE) ? ( \
        ENET_RACC_REG(PeripheralBase) &= \
         (uint32_t)(( \
          (uint32_t)(~(uint32_t)ENET_RACC_LINEDIS_MASK)) & (( \
          (uint32_t)(~(uint32_t)0x38U)) & ( \
          (uint32_t)(~(uint32_t)0xFFFFFF00U))))) : ( \
        ENET_RACC_REG(PeripheralBase) = \
         (uint32_t)(( \
          (uint32_t)(ENET_RACC_REG(PeripheralBase) | ENET_RACC_LINEDIS_MASK)) & (( \
          (uint32_t)(~(uint32_t)0x38U)) & ( \
          (uint32_t)(~(uint32_t)0xFFFFFF00U))))) \
    )
#else /* (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) */
/**
 * @brief Enables/disables frames with MAC error to be dropped by the receiver.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Enable Enable flag. This parameter is of "Global enumeration used for
 *        specifying general enable/disable states (PDD_DISABLE and PDD_ENABLE
 *        defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ENET_RACC.
 * @par Example:
 *      @code
 *      ENET_PDD_EnableMACErrorDrops(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
  #define ENET_PDD_EnableMACErrorDrops(PeripheralBase, Enable) ( \
      ((Enable) == PDD_DISABLE) ? ( \
        ENET_RACC_REG(PeripheralBase) &= \
         (uint32_t)(~(uint32_t)ENET_RACC_LINEDIS_MASK)) : ( \
        ENET_RACC_REG(PeripheralBase) |= \
         ENET_RACC_LINEDIS_MASK) \
    )
#endif /* (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) */

/* ----------------------------------------------------------------------------
   -- EnablePaddingRemoval
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)))
/**
 * @brief Enables/disables padding removal for short IP frames.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Enable Enable flag. This parameter is of "Global enumeration used for
 *        specifying general enable/disable states (PDD_DISABLE and PDD_ENABLE
 *        defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ENET_RACC.
 * @par Example:
 *      @code
 *      ENET_PDD_EnablePaddingRemoval(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
  #define ENET_PDD_EnablePaddingRemoval(PeripheralBase, Enable) ( \
      ((Enable) == PDD_DISABLE) ? ( \
        ENET_RACC_REG(PeripheralBase) &= \
         (uint32_t)(( \
          (uint32_t)(~(uint32_t)ENET_RACC_PADREM_MASK)) & (( \
          (uint32_t)(~(uint32_t)0x38U)) & ( \
          (uint32_t)(~(uint32_t)0xFFFFFF00U))))) : ( \
        ENET_RACC_REG(PeripheralBase) = \
         (uint32_t)(( \
          (uint32_t)(ENET_RACC_REG(PeripheralBase) | ENET_RACC_PADREM_MASK)) & (( \
          (uint32_t)(~(uint32_t)0x38U)) & ( \
          (uint32_t)(~(uint32_t)0xFFFFFF00U))))) \
    )
#else /* (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) */
/**
 * @brief Enables/disables padding removal for short IP frames.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Enable Enable flag. This parameter is of "Global enumeration used for
 *        specifying general enable/disable states (PDD_DISABLE and PDD_ENABLE
 *        defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ENET_RACC.
 * @par Example:
 *      @code
 *      ENET_PDD_EnablePaddingRemoval(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
  #define ENET_PDD_EnablePaddingRemoval(PeripheralBase, Enable) ( \
      ((Enable) == PDD_DISABLE) ? ( \
        ENET_RACC_REG(PeripheralBase) &= \
         (uint32_t)(~(uint32_t)ENET_RACC_PADREM_MASK)) : ( \
        ENET_RACC_REG(PeripheralBase) |= \
         ENET_RACC_PADREM_MASK) \
    )
#endif /* (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) */

/* ----------------------------------------------------------------------------
   -- TIMER_EnableDevice
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables the timer.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ENET_ATCR.
 * @par Example:
 *      @code
 *      ENET_PDD_TIMER_EnableDevice(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define ENET_PDD_TIMER_EnableDevice(PeripheralBase) ( \
    ENET_ATCR_REG(PeripheralBase) |= \
     ENET_ATCR_EN_MASK \
  )

/* ----------------------------------------------------------------------------
   -- TIMER_DisableDevice
   ---------------------------------------------------------------------------- */

/**
 * @brief Disables the timer.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ENET_ATCR.
 * @par Example:
 *      @code
 *      ENET_PDD_TIMER_DisableDevice(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define ENET_PDD_TIMER_DisableDevice(PeripheralBase) ( \
    ENET_ATCR_REG(PeripheralBase) &= \
     (uint32_t)(~(uint32_t)ENET_ATCR_EN_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- TIMER_EnableSlaveMode
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables/disables timer slave mode.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Enable Enable flag. This parameter is of "Global enumeration used for
 *        specifying general enable/disable states (PDD_DISABLE and PDD_ENABLE
 *        defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ENET_ATCR.
 * @par Example:
 *      @code
 *      ENET_PDD_TIMER_EnableSlaveMode(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define ENET_PDD_TIMER_EnableSlaveMode(PeripheralBase, Enable) ( \
    ((Enable) == PDD_DISABLE) ? ( \
      ENET_ATCR_REG(PeripheralBase) &= \
       (uint32_t)(~(uint32_t)ENET_ATCR_SLAVE_MASK)) : ( \
      ENET_ATCR_REG(PeripheralBase) |= \
       ENET_ATCR_SLAVE_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- TIMER_CaptureTimer
   ---------------------------------------------------------------------------- */

/**
 * @brief Captures the current time.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ENET_ATCR.
 * @par Example:
 *      @code
 *      ENET_PDD_TIMER_CaptureTimer(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define ENET_PDD_TIMER_CaptureTimer(PeripheralBase) ( \
    ENET_ATCR_REG(PeripheralBase) |= \
     ENET_ATCR_CAPTURE_MASK \
  )

/* ----------------------------------------------------------------------------
   -- TIMER_ResetTimer
   ---------------------------------------------------------------------------- */

/**
 * @brief Resets the timer to zero.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ENET_ATCR.
 * @par Example:
 *      @code
 *      ENET_PDD_TIMER_ResetTimer(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define ENET_PDD_TIMER_ResetTimer(PeripheralBase) ( \
    ENET_ATCR_REG(PeripheralBase) |= \
     ENET_ATCR_RESTART_MASK \
  )

/* ----------------------------------------------------------------------------
   -- TIMER_EnableOutputAssertOnPeriod
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables/disables MAC output assertion on periodical event.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Enable Enable flag. This parameter is of "Global enumeration used for
 *        specifying general enable/disable states (PDD_DISABLE and PDD_ENABLE
 *        defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ENET_ATCR.
 * @par Example:
 *      @code
 *      ENET_PDD_TIMER_EnableOutputAssertOnPeriod(<peripheral>_BASE_PTR,
 *      PDD_DISABLE);
 *      @endcode
 */
#define ENET_PDD_TIMER_EnableOutputAssertOnPeriod(PeripheralBase, Enable) ( \
    ((Enable) == PDD_DISABLE) ? ( \
      ENET_ATCR_REG(PeripheralBase) &= \
       (uint32_t)(~(uint32_t)ENET_ATCR_PINPER_MASK)) : ( \
      ENET_ATCR_REG(PeripheralBase) |= \
       ENET_ATCR_PINPER_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- TIMER_EnablePeriodEvent
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables/disables periodical event.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Enable Enable flag. This parameter is of "Global enumeration used for
 *        specifying general enable/disable states (PDD_DISABLE and PDD_ENABLE
 *        defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ENET_ATCR.
 * @par Example:
 *      @code
 *      ENET_PDD_TIMER_EnablePeriodEvent(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define ENET_PDD_TIMER_EnablePeriodEvent(PeripheralBase, Enable) ( \
    ((Enable) == PDD_DISABLE) ? ( \
      ENET_ATCR_REG(PeripheralBase) &= \
       (uint32_t)(~(uint32_t)ENET_ATCR_PEREN_MASK)) : ( \
      ENET_ATCR_REG(PeripheralBase) |= \
       ENET_ATCR_PEREN_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- TIMER_EnableResetOnOffsetEvent
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables/disables reset on offset event.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Enable Enable flag. This parameter is of "Global enumeration used for
 *        specifying general enable/disable states (PDD_DISABLE and PDD_ENABLE
 *        defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ENET_ATCR.
 * @par Example:
 *      @code
 *      ENET_PDD_TIMER_EnableResetOnOffsetEvent(<peripheral>_BASE_PTR,
 *      PDD_DISABLE);
 *      @endcode
 */
#define ENET_PDD_TIMER_EnableResetOnOffsetEvent(PeripheralBase, Enable) ( \
    ((Enable) == PDD_DISABLE) ? ( \
      ENET_ATCR_REG(PeripheralBase) &= \
       (uint32_t)(~(uint32_t)ENET_ATCR_OFFRST_MASK)) : ( \
      ENET_ATCR_REG(PeripheralBase) |= \
       ENET_ATCR_OFFRST_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- TIMER_EnableOffsetEvent
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables/disables offset event.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Enable Enable flag. This parameter is of "Global enumeration used for
 *        specifying general enable/disable states (PDD_DISABLE and PDD_ENABLE
 *        defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ENET_ATCR.
 * @par Example:
 *      @code
 *      ENET_PDD_TIMER_EnableOffsetEvent(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define ENET_PDD_TIMER_EnableOffsetEvent(PeripheralBase, Enable) ( \
    ((Enable) == PDD_DISABLE) ? ( \
      ENET_ATCR_REG(PeripheralBase) &= \
       (uint32_t)(~(uint32_t)ENET_ATCR_OFFEN_MASK)) : ( \
      ENET_ATCR_REG(PeripheralBase) |= \
       ENET_ATCR_OFFEN_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- TIMER_SetTimer
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the timer.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Timer value. This parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ENET_ATVR.
 * @par Example:
 *      @code
 *      ENET_PDD_TIMER_SetTimer(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define ENET_PDD_TIMER_SetTimer(PeripheralBase, Value) ( \
    ENET_ATVR_REG(PeripheralBase) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- TIMER_GetTimer
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the last captured timer value.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: ENET_ATVR.
 * @par Example:
 *      @code
 *      uint32_t result = ENET_PDD_TIMER_GetTimer(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define ENET_PDD_TIMER_GetTimer(PeripheralBase) ( \
    ENET_ATVR_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- TIMER_SetOffset
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the timer offset.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Offset Timer offset value. This parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ENET_ATOFF.
 * @par Example:
 *      @code
 *      ENET_PDD_TIMER_SetOffset(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define ENET_PDD_TIMER_SetOffset(PeripheralBase, Offset) ( \
    ENET_ATOFF_REG(PeripheralBase) = \
     (uint32_t)(Offset) \
  )

/* ----------------------------------------------------------------------------
   -- TIMER_SetPeriod
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the timer period.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Period Timer period value. This parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ENET_ATPER.
 * @par Example:
 *      @code
 *      ENET_PDD_TIMER_SetPeriod(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define ENET_PDD_TIMER_SetPeriod(PeripheralBase, Period) ( \
    ENET_ATPER_REG(PeripheralBase) = \
     (uint32_t)(Period) \
  )

/* ----------------------------------------------------------------------------
   -- TIMER_SetCorrectionCounter
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the timer correction counter value.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Counter Correction counter value. This parameter is a 31-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ENET_ATCOR.
 * @par Example:
 *      @code
 *      ENET_PDD_TIMER_SetCorrectionCounter(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define ENET_PDD_TIMER_SetCorrectionCounter(PeripheralBase, Counter) ( \
    ENET_ATCOR_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(ENET_ATCOR_REG(PeripheralBase) & (uint32_t)(~(uint32_t)ENET_ATCOR_COR_MASK))) | ( \
      (uint32_t)(Counter))) \
  )

/* ----------------------------------------------------------------------------
   -- TIMER_SetCorrectionIncrement
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the timer correction increment value.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Increment Correction increment value. This parameter is a 7-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ENET_ATINC.
 * @par Example:
 *      @code
 *      ENET_PDD_TIMER_SetCorrectionIncrement(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define ENET_PDD_TIMER_SetCorrectionIncrement(PeripheralBase, Increment) ( \
    ENET_ATINC_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       ENET_ATINC_REG(PeripheralBase)) & ( \
       (uint32_t)(~(uint32_t)ENET_ATINC_INC_CORR_MASK)))) | ( \
      (uint32_t)((uint32_t)(Increment) << ENET_ATINC_INC_CORR_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- TIMER_SetIncrement
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the timer increment value.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Increment Timer increment value. This parameter is a 7-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ENET_ATINC.
 * @par Example:
 *      @code
 *      ENET_PDD_TIMER_SetIncrement(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define ENET_PDD_TIMER_SetIncrement(PeripheralBase, Increment) ( \
    ENET_ATINC_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(ENET_ATINC_REG(PeripheralBase) & (uint32_t)(~(uint32_t)ENET_ATINC_INC_MASK))) | ( \
      (uint32_t)(Increment))) \
  )

/* ----------------------------------------------------------------------------
   -- TIMER_GetTimestamp
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns timestamp of the last frame transmitted with TimeStamp flag
 * set.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: ENET_ATSTMP.
 * @par Example:
 *      @code
 *      uint32_t result = ENET_PDD_TIMER_GetTimestamp(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define ENET_PDD_TIMER_GetTimestamp(PeripheralBase) ( \
    ENET_ATSTMP_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- TIMER_GetStatusFlags
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the timer status flags. The return value can be masked with
 * predefined macros.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Use constants from group "Timer status flags" for processing return
 *         value.
 * @remarks The macro accesses the following registers: ENET_TGSR.
 * @par Example:
 *      @code
 *      uint32_t result = ENET_PDD_TIMER_GetStatusFlags(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define ENET_PDD_TIMER_GetStatusFlags(PeripheralBase) ( \
    ENET_TGSR_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- TIMER_ClearStatusFlags
   ---------------------------------------------------------------------------- */

/**
 * @brief Clears the specified timer status flags.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mask Status flag mask. Use constants from group "Timer status flags".
 *        This parameter is 32 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ENET_TGSR.
 * @par Example:
 *      @code
 *      ENET_PDD_TIMER_ClearStatusFlags(<peripheral>_BASE_PTR,
 *      ENET_PDD_TIMER_CHANNEL_0);
 *      @endcode
 */
#define ENET_PDD_TIMER_ClearStatusFlags(PeripheralBase, Mask) ( \
    ENET_TGSR_REG(PeripheralBase) = \
     (uint32_t)(Mask) \
  )

/* ----------------------------------------------------------------------------
   -- TIMER_EnableInterrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables interrupts for a specified channel.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel Channel index. This parameter is of index type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: TCSR[Channel].
 * @par Example:
 *      @code
 *      ENET_PDD_TIMER_EnableInterrupt(<peripheral>_BASE_PTR, periphID);
 *      @endcode
 */
#define ENET_PDD_TIMER_EnableInterrupt(PeripheralBase, Channel) ( \
    ENET_TCSR_REG(PeripheralBase,(Channel)) = \
     (uint32_t)(( \
      (uint32_t)(ENET_TCSR_REG(PeripheralBase,(Channel)) | ENET_TCSR_TIE_MASK)) & ( \
      (uint32_t)(~(uint32_t)ENET_TCSR_TF_MASK))) \
  )

/* ----------------------------------------------------------------------------
   -- TIMER_DisableInterrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Disables interrupts for a specified channel.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel Channel index. This parameter is of index type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: TCSR[Channel].
 * @par Example:
 *      @code
 *      ENET_PDD_TIMER_DisableInterrupt(<peripheral>_BASE_PTR, periphID);
 *      @endcode
 */
#define ENET_PDD_TIMER_DisableInterrupt(PeripheralBase, Channel) ( \
    ENET_TCSR_REG(PeripheralBase,(Channel)) &= \
     (uint32_t)(( \
      (uint32_t)(~(uint32_t)ENET_TCSR_TIE_MASK)) & ( \
      (uint32_t)(~(uint32_t)ENET_TCSR_TF_MASK))) \
  )

/* ----------------------------------------------------------------------------
   -- TIMER_SetMode
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the timer mode.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel Channel index. This parameter is of index type.
 * @param Mode Timer mode. This parameter is of "Timer modes" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: TCSR[Channel].
 * @par Example:
 *      @code
 *      ENET_PDD_TIMER_SetMode(<peripheral>_BASE_PTR, periphID,
 *      ENET_PDD_DISABLED);
 *      @endcode
 */
#define ENET_PDD_TIMER_SetMode(PeripheralBase, Channel, Mode) ( \
    ENET_TCSR_REG(PeripheralBase,(Channel)) = \
     (uint32_t)(( \
      (uint32_t)(( \
       ENET_TCSR_REG(PeripheralBase,(Channel))) & (( \
       (uint32_t)(~(uint32_t)ENET_TCSR_TMODE_MASK)) & ( \
       (uint32_t)(~(uint32_t)ENET_TCSR_TF_MASK))))) | ( \
      (uint32_t)(Mode))) \
  )

/* ----------------------------------------------------------------------------
   -- TIMER_EnableDMARequest
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables the DMA request for the specified channel.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel Channel index. This parameter is of index type.
 * @param Enable Enable flag. This parameter is of "Global enumeration used for
 *        specifying general enable/disable states (PDD_DISABLE and PDD_ENABLE
 *        defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: TCSR[Channel].
 * @par Example:
 *      @code
 *      ENET_PDD_TIMER_EnableDMARequest(<peripheral>_BASE_PTR, periphID,
 *      PDD_DISABLE);
 *      @endcode
 */
#define ENET_PDD_TIMER_EnableDMARequest(PeripheralBase, Channel, Enable) ( \
    ((Enable) == PDD_DISABLE) ? ( \
      ENET_TCSR_REG(PeripheralBase,(Channel)) &= \
       (uint32_t)(( \
        (uint32_t)(~(uint32_t)ENET_TCSR_TDRE_MASK)) & ( \
        (uint32_t)(~(uint32_t)ENET_TCSR_TF_MASK)))) : ( \
      ENET_TCSR_REG(PeripheralBase,(Channel)) = \
       (uint32_t)(( \
        (uint32_t)(ENET_TCSR_REG(PeripheralBase,(Channel)) | ENET_TCSR_TDRE_MASK)) & ( \
        (uint32_t)(~(uint32_t)ENET_TCSR_TF_MASK)))) \
  )

/* ----------------------------------------------------------------------------
   -- TIMER_GetCapture
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the timer value captured when a rising edge occurred on input
 * pin.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel Channel index. This parameter is of index type.
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: TCCR[Channel].
 * @par Example:
 *      @code
 *      uint32_t result = ENET_PDD_TIMER_GetCapture(<peripheral>_BASE_PTR,
 *      periphID);
 *      @endcode
 */
#define ENET_PDD_TIMER_GetCapture(PeripheralBase, Channel) ( \
    ENET_TCCR_REG(PeripheralBase,(Channel)) \
  )

/* ----------------------------------------------------------------------------
   -- TIMER_SetCompare
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the timer compare value. When timer reaches this value, output
 * pin is asserted.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel Channel index. This parameter is of index type.
 * @param Value Timer compare value. This parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: TCCR[Channel].
 * @par Example:
 *      @code
 *      ENET_PDD_TIMER_SetCompare(<peripheral>_BASE_PTR, periphID, 1);
 *      @endcode
 */
#define ENET_PDD_TIMER_SetCompare(PeripheralBase, Channel, Value) ( \
    ENET_TCCR_REG(PeripheralBase,(Channel)) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- TIMER_SetClockSource
   ---------------------------------------------------------------------------- */

/**
 * @brief Selects the timer clock source (in the SIM module).
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Source Timer clock source. Use constants from group "Timer clock
 *        sources". This parameter is 32 bits wide.
 * @return Returns a value of void type.
 * @par Example:
 *      @code
 *      ENET_PDD_TIMER_SetClockSource(<peripheral>_BASE_PTR,
 *      ENET_PDD_CORE_SYSTEM_CLOCK);
 *      @endcode
 */
#define ENET_PDD_TIMER_SetClockSource(PeripheralBase, Source) ( \
    SIM_SOPT2_REG(SIM_BASE_PTR) = \
     (( \
      (uint32_t)(SIM_SOPT2_REG(SIM_BASE_PTR) & (uint32_t)(~(uint32_t)SIM_SOPT2_TIMESRC_MASK))) | ( \
      (uint32_t)((uint32_t)(Source) << SIM_SOPT2_TIMESRC_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SetRxStatFIFOSectionEmptyThreshold
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the receive status FIFO section empty threshold.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Number of frames in the receive FIFO after which a pause frame
 *        will be sent. This parameter is a 5-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ENET_RSEM.
 * @par Example:
 *      @code
 *      ENET_PDD_SetRxStatFIFOSectionEmptyThreshold(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define ENET_PDD_SetRxStatFIFOSectionEmptyThreshold(PeripheralBase, Value) ( \
    ENET_RSEM_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       ENET_RSEM_REG(PeripheralBase)) & ( \
       (uint32_t)(~(uint32_t)ENET_RSEM_STAT_SECTION_EMPTY_MASK)))) | ( \
      (uint32_t)((uint32_t)(Value) << ENET_RSEM_STAT_SECTION_EMPTY_SHIFT))) \
  )
#endif  /* #if defined(ENET_PDD_H_) */

/* ENET_PDD.h, eof. */
