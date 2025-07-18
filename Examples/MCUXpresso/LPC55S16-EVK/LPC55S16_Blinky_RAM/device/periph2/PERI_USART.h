/*
** ###################################################################
**     Processors:          LPC5512JBD100
**                          LPC5512JBD64
**                          LPC5514JBD100
**                          LPC5514JBD64
**                          LPC5514JEV59
**                          LPC5516JBD100
**                          LPC5516JBD64
**                          LPC5516JEV59
**                          LPC5516JEV98
**                          LPC55S14JBD100
**                          LPC55S14JBD64
**                          LPC55S14JEV59
**                          LPC55S16JBD100
**                          LPC55S16JBD64
**                          LPC55S16JEV59
**                          LPC55S16JEV98
**
**     Version:             rev. 1.1, 2019-12-03
**     Build:               b240704
**
**     Abstract:
**         CMSIS Peripheral Access Layer for USART
**
**     Copyright 1997-2016 Freescale Semiconductor, Inc.
**     Copyright 2016-2024 NXP
**     SPDX-License-Identifier: BSD-3-Clause
**
**     http:                 www.nxp.com
**     mail:                 support@nxp.com
**
**     Revisions:
**     - rev. 1.0 (2018-08-22)
**         Initial version based on v0.2UM
**     - rev. 1.1 (2019-12-03)
**         Initial version based on v0.6UM
**
** ###################################################################
*/

/*!
 * @file USART.h
 * @version 1.1
 * @date 2019-12-03
 * @brief CMSIS Peripheral Access Layer for USART
 *
 * CMSIS Peripheral Access Layer for USART
 */

#if !defined(USART_H_)
#define USART_H_                                 /**< Symbol preventing repeated inclusion */

#if (defined(CPU_LPC5512JBD100) || defined(CPU_LPC5512JBD64))
#include "LPC5512_COMMON.h"
#elif (defined(CPU_LPC5514JBD100) || defined(CPU_LPC5514JBD64) || defined(CPU_LPC5514JEV59))
#include "LPC5514_COMMON.h"
#elif (defined(CPU_LPC5516JBD100) || defined(CPU_LPC5516JBD64) || defined(CPU_LPC5516JEV59) || defined(CPU_LPC5516JEV98))
#include "LPC5516_COMMON.h"
#elif (defined(CPU_LPC55S14JBD100) || defined(CPU_LPC55S14JBD64) || defined(CPU_LPC55S14JEV59))
#include "LPC55S14_COMMON.h"
#elif (defined(CPU_LPC55S16JBD100) || defined(CPU_LPC55S16JBD64) || defined(CPU_LPC55S16JEV59) || defined(CPU_LPC55S16JEV98))
#include "LPC55S16_COMMON.h"
#else
  #error "No valid CPU defined!"
#endif

/* ----------------------------------------------------------------------------
   -- Device Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup Peripheral_access_layer Device Peripheral Access Layer
 * @{
 */


/*
** Start of section using anonymous unions
*/

#if defined(__ARMCC_VERSION)
  #if (__ARMCC_VERSION >= 6010050)
    #pragma clang diagnostic push
  #else
    #pragma push
    #pragma anon_unions
  #endif
#elif defined(__GNUC__)
  /* anonymous unions are enabled by default */
#elif defined(__IAR_SYSTEMS_ICC__)
  #pragma language=extended
#else
  #error Not supported compiler type
#endif

/* ----------------------------------------------------------------------------
   -- USART Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup USART_Peripheral_Access_Layer USART Peripheral Access Layer
 * @{
 */

/** USART - Register Layout Typedef */
typedef struct {
  __IO uint32_t CFG;                               /**< USART Configuration register. Basic USART configuration settings that typically are not changed during operation., offset: 0x0 */
  __IO uint32_t CTL;                               /**< USART Control register. USART control settings that are more likely to change during operation., offset: 0x4 */
  __IO uint32_t STAT;                              /**< USART Status register. The complete status value can be read here. Writing ones clears some bits in the register. Some bits can be cleared by writing a 1 to them., offset: 0x8 */
  __IO uint32_t INTENSET;                          /**< Interrupt Enable read and Set register for USART (not FIFO) status. Contains individual interrupt enable bits for each potential USART interrupt. A complete value may be read from this register. Writing a 1 to any implemented bit position causes that bit to be set., offset: 0xC */
  __O  uint32_t INTENCLR;                          /**< Interrupt Enable Clear register. Allows clearing any combination of bits in the INTENSET register. Writing a 1 to any implemented bit position causes the corresponding bit to be cleared., offset: 0x10 */
       uint8_t RESERVED_0[12];
  __IO uint32_t BRG;                               /**< Baud Rate Generator register. 16-bit integer baud rate divisor value., offset: 0x20 */
  __I  uint32_t INTSTAT;                           /**< Interrupt status register. Reflects interrupts that are currently enabled., offset: 0x24 */
  __IO uint32_t OSR;                               /**< Oversample selection register for asynchronous communication., offset: 0x28 */
  __IO uint32_t ADDR;                              /**< Address register for automatic address matching., offset: 0x2C */
       uint8_t RESERVED_1[3536];
  __IO uint32_t FIFOCFG;                           /**< FIFO configuration and enable register., offset: 0xE00 */
  __IO uint32_t FIFOSTAT;                          /**< FIFO status register., offset: 0xE04 */
  __IO uint32_t FIFOTRIG;                          /**< FIFO trigger settings for interrupt and DMA request., offset: 0xE08 */
       uint8_t RESERVED_2[4];
  __IO uint32_t FIFOINTENSET;                      /**< FIFO interrupt enable set (enable) and read register., offset: 0xE10 */
  __IO uint32_t FIFOINTENCLR;                      /**< FIFO interrupt enable clear (disable) and read register., offset: 0xE14 */
  __I  uint32_t FIFOINTSTAT;                       /**< FIFO interrupt status register., offset: 0xE18 */
       uint8_t RESERVED_3[4];
  __O  uint32_t FIFOWR;                            /**< FIFO write data., offset: 0xE20 */
       uint8_t RESERVED_4[12];
  __I  uint32_t FIFORD;                            /**< FIFO read data., offset: 0xE30 */
       uint8_t RESERVED_5[12];
  __I  uint32_t FIFORDNOPOP;                       /**< FIFO data read with no FIFO pop., offset: 0xE40 */
       uint8_t RESERVED_6[4];
  __I  uint32_t FIFOSIZE;                          /**< FIFO size register, offset: 0xE48 */
       uint8_t RESERVED_7[432];
  __I  uint32_t ID;                                /**< Peripheral identification register., offset: 0xFFC */
} USART_Type;

/* ----------------------------------------------------------------------------
   -- USART Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup USART_Register_Masks USART Register Masks
 * @{
 */

/*! @name CFG - USART Configuration register. Basic USART configuration settings that typically are not changed during operation. */
/*! @{ */

#define USART_CFG_ENABLE_MASK                    (0x1U)
#define USART_CFG_ENABLE_SHIFT                   (0U)
/*! ENABLE - USART Enable.
 *  0b0..Disabled. The USART is disabled and the internal state machine and counters are reset. While Enable = 0,
 *       all USART interrupts and DMA transfers are disabled. When Enable is set again, CFG and most other control
 *       bits remain unchanged. When re-enabled, the USART will immediately be ready to transmit because the
 *       transmitter has been reset and is therefore available.
 *  0b1..Enabled. The USART is enabled for operation.
 */
#define USART_CFG_ENABLE(x)                      (((uint32_t)(((uint32_t)(x)) << USART_CFG_ENABLE_SHIFT)) & USART_CFG_ENABLE_MASK)

#define USART_CFG_DATALEN_MASK                   (0xCU)
#define USART_CFG_DATALEN_SHIFT                  (2U)
/*! DATALEN - Selects the data size for the USART.
 *  0b00..7 bit Data length.
 *  0b01..8 bit Data length.
 *  0b10..9 bit data length. The 9th bit is commonly used for addressing in multidrop mode. See the ADDRDET bit in the CTL register.
 *  0b11..Reserved.
 */
#define USART_CFG_DATALEN(x)                     (((uint32_t)(((uint32_t)(x)) << USART_CFG_DATALEN_SHIFT)) & USART_CFG_DATALEN_MASK)

#define USART_CFG_PARITYSEL_MASK                 (0x30U)
#define USART_CFG_PARITYSEL_SHIFT                (4U)
/*! PARITYSEL - Selects what type of parity is used by the USART.
 *  0b00..No parity.
 *  0b01..Reserved.
 *  0b10..Even parity. Adds a bit to each character such that the number of 1s in a transmitted character is even,
 *        and the number of 1s in a received character is expected to be even.
 *  0b11..Odd parity. Adds a bit to each character such that the number of 1s in a transmitted character is odd,
 *        and the number of 1s in a received character is expected to be odd.
 */
#define USART_CFG_PARITYSEL(x)                   (((uint32_t)(((uint32_t)(x)) << USART_CFG_PARITYSEL_SHIFT)) & USART_CFG_PARITYSEL_MASK)

#define USART_CFG_STOPLEN_MASK                   (0x40U)
#define USART_CFG_STOPLEN_SHIFT                  (6U)
/*! STOPLEN - Number of stop bits appended to transmitted data. Only a single stop bit is required for received data.
 *  0b0..1 stop bit.
 *  0b1..2 stop bits. This setting should only be used for asynchronous communication.
 */
#define USART_CFG_STOPLEN(x)                     (((uint32_t)(((uint32_t)(x)) << USART_CFG_STOPLEN_SHIFT)) & USART_CFG_STOPLEN_MASK)

#define USART_CFG_MODE32K_MASK                   (0x80U)
#define USART_CFG_MODE32K_SHIFT                  (7U)
/*! MODE32K - Selects standard or 32 kHz clocking mode.
 *  0b0..Disabled. USART uses standard clocking.
 *  0b1..Enabled. USART uses the 32 kHz clock from the RTC oscillator as the clock source to the BRG, and uses a special bit clocking scheme.
 */
#define USART_CFG_MODE32K(x)                     (((uint32_t)(((uint32_t)(x)) << USART_CFG_MODE32K_SHIFT)) & USART_CFG_MODE32K_MASK)

#define USART_CFG_LINMODE_MASK                   (0x100U)
#define USART_CFG_LINMODE_SHIFT                  (8U)
/*! LINMODE - LIN break mode enable.
 *  0b0..Disabled. Break detect and generate is configured for normal operation.
 *  0b1..Enabled. Break detect and generate is configured for LIN bus operation.
 */
#define USART_CFG_LINMODE(x)                     (((uint32_t)(((uint32_t)(x)) << USART_CFG_LINMODE_SHIFT)) & USART_CFG_LINMODE_MASK)

#define USART_CFG_CTSEN_MASK                     (0x200U)
#define USART_CFG_CTSEN_SHIFT                    (9U)
/*! CTSEN - CTS Enable. Determines whether CTS is used for flow control. CTS can be from the input
 *    pin, or from the USART's own RTS if loopback mode is enabled.
 *  0b0..No flow control. The transmitter does not receive any automatic flow control signal.
 *  0b1..Flow control enabled. The transmitter uses the CTS input (or RTS output in loopback mode) for flow control purposes.
 */
#define USART_CFG_CTSEN(x)                       (((uint32_t)(((uint32_t)(x)) << USART_CFG_CTSEN_SHIFT)) & USART_CFG_CTSEN_MASK)

#define USART_CFG_SYNCEN_MASK                    (0x800U)
#define USART_CFG_SYNCEN_SHIFT                   (11U)
/*! SYNCEN - Selects synchronous or asynchronous operation.
 *  0b0..Asynchronous mode.
 *  0b1..Synchronous mode.
 */
#define USART_CFG_SYNCEN(x)                      (((uint32_t)(((uint32_t)(x)) << USART_CFG_SYNCEN_SHIFT)) & USART_CFG_SYNCEN_MASK)

#define USART_CFG_CLKPOL_MASK                    (0x1000U)
#define USART_CFG_CLKPOL_SHIFT                   (12U)
/*! CLKPOL - Selects the clock polarity and sampling edge of received data in synchronous mode.
 *  0b0..Falling edge. Un_RXD is sampled on the falling edge of SCLK.
 *  0b1..Rising edge. Un_RXD is sampled on the rising edge of SCLK.
 */
#define USART_CFG_CLKPOL(x)                      (((uint32_t)(((uint32_t)(x)) << USART_CFG_CLKPOL_SHIFT)) & USART_CFG_CLKPOL_MASK)

#define USART_CFG_SYNCMST_MASK                   (0x4000U)
#define USART_CFG_SYNCMST_SHIFT                  (14U)
/*! SYNCMST - Synchronous mode Master select.
 *  0b0..Slave. When synchronous mode is enabled, the USART is a slave.
 *  0b1..Master. When synchronous mode is enabled, the USART is a master.
 */
#define USART_CFG_SYNCMST(x)                     (((uint32_t)(((uint32_t)(x)) << USART_CFG_SYNCMST_SHIFT)) & USART_CFG_SYNCMST_MASK)

#define USART_CFG_LOOP_MASK                      (0x8000U)
#define USART_CFG_LOOP_SHIFT                     (15U)
/*! LOOP - Selects data loopback mode.
 *  0b0..Normal operation.
 *  0b1..Loopback mode. This provides a mechanism to perform diagnostic loopback testing for USART data. Serial
 *       data from the transmitter (Un_TXD) is connected internally to serial input of the receive (Un_RXD). Un_TXD
 *       and Un_RTS activity will also appear on external pins if these functions are configured to appear on device
 *       pins. The receiver RTS signal is also looped back to CTS and performs flow control if enabled by CTSEN.
 */
#define USART_CFG_LOOP(x)                        (((uint32_t)(((uint32_t)(x)) << USART_CFG_LOOP_SHIFT)) & USART_CFG_LOOP_MASK)

#define USART_CFG_OETA_MASK                      (0x40000U)
#define USART_CFG_OETA_SHIFT                     (18U)
/*! OETA - Output Enable Turnaround time enable for RS-485 operation.
 *  0b0..Disabled. If selected by OESEL, the Output Enable signal deasserted at the end of the last stop bit of a transmission.
 *  0b1..Enabled. If selected by OESEL, the Output Enable signal remains asserted for one character time after the
 *       end of the last stop bit of a transmission. OE will also remain asserted if another transmit begins
 *       before it is deasserted.
 */
#define USART_CFG_OETA(x)                        (((uint32_t)(((uint32_t)(x)) << USART_CFG_OETA_SHIFT)) & USART_CFG_OETA_MASK)

#define USART_CFG_AUTOADDR_MASK                  (0x80000U)
#define USART_CFG_AUTOADDR_SHIFT                 (19U)
/*! AUTOADDR - Automatic Address matching enable.
 *  0b0..Disabled. When addressing is enabled by ADDRDET, address matching is done by software. This provides the
 *       possibility of versatile addressing (e.g. respond to more than one address).
 *  0b1..Enabled. When addressing is enabled by ADDRDET, address matching is done by hardware, using the value in
 *       the ADDR register as the address to match.
 */
#define USART_CFG_AUTOADDR(x)                    (((uint32_t)(((uint32_t)(x)) << USART_CFG_AUTOADDR_SHIFT)) & USART_CFG_AUTOADDR_MASK)

#define USART_CFG_OESEL_MASK                     (0x100000U)
#define USART_CFG_OESEL_SHIFT                    (20U)
/*! OESEL - Output Enable Select.
 *  0b0..Standard. The RTS signal is used as the standard flow control function.
 *  0b1..RS-485. The RTS signal configured to provide an output enable signal to control an RS-485 transceiver.
 */
#define USART_CFG_OESEL(x)                       (((uint32_t)(((uint32_t)(x)) << USART_CFG_OESEL_SHIFT)) & USART_CFG_OESEL_MASK)

#define USART_CFG_OEPOL_MASK                     (0x200000U)
#define USART_CFG_OEPOL_SHIFT                    (21U)
/*! OEPOL - Output Enable Polarity.
 *  0b0..Low. If selected by OESEL, the output enable is active low.
 *  0b1..High. If selected by OESEL, the output enable is active high.
 */
#define USART_CFG_OEPOL(x)                       (((uint32_t)(((uint32_t)(x)) << USART_CFG_OEPOL_SHIFT)) & USART_CFG_OEPOL_MASK)

#define USART_CFG_RXPOL_MASK                     (0x400000U)
#define USART_CFG_RXPOL_SHIFT                    (22U)
/*! RXPOL - Receive data polarity.
 *  0b0..Standard. The RX signal is used as it arrives from the pin. This means that the RX rest value is 1, start
 *       bit is 0, data is not inverted, and the stop bit is 1.
 *  0b1..Inverted. The RX signal is inverted before being used by the USART. This means that the RX rest value is
 *       0, start bit is 1, data is inverted, and the stop bit is 0.
 */
#define USART_CFG_RXPOL(x)                       (((uint32_t)(((uint32_t)(x)) << USART_CFG_RXPOL_SHIFT)) & USART_CFG_RXPOL_MASK)

#define USART_CFG_TXPOL_MASK                     (0x800000U)
#define USART_CFG_TXPOL_SHIFT                    (23U)
/*! TXPOL - Transmit data polarity.
 *  0b0..Standard. The TX signal is sent out without change. This means that the TX rest value is 1, start bit is
 *       0, data is not inverted, and the stop bit is 1.
 *  0b1..Inverted. The TX signal is inverted by the USART before being sent out. This means that the TX rest value
 *       is 0, start bit is 1, data is inverted, and the stop bit is 0.
 */
#define USART_CFG_TXPOL(x)                       (((uint32_t)(((uint32_t)(x)) << USART_CFG_TXPOL_SHIFT)) & USART_CFG_TXPOL_MASK)
/*! @} */

/*! @name CTL - USART Control register. USART control settings that are more likely to change during operation. */
/*! @{ */

#define USART_CTL_TXBRKEN_MASK                   (0x2U)
#define USART_CTL_TXBRKEN_SHIFT                  (1U)
/*! TXBRKEN - Break Enable.
 *  0b0..Normal operation.
 *  0b1..Continuous break. Continuous break is sent immediately when this bit is set, and remains until this bit
 *       is cleared. A break may be sent without danger of corrupting any currently transmitting character if the
 *       transmitter is first disabled (TXDIS in CTL is set) and then waiting for the transmitter to be disabled
 *       (TXDISINT in STAT = 1) before writing 1 to TXBRKEN.
 */
#define USART_CTL_TXBRKEN(x)                     (((uint32_t)(((uint32_t)(x)) << USART_CTL_TXBRKEN_SHIFT)) & USART_CTL_TXBRKEN_MASK)

#define USART_CTL_ADDRDET_MASK                   (0x4U)
#define USART_CTL_ADDRDET_SHIFT                  (2U)
/*! ADDRDET - Enable address detect mode.
 *  0b0..Disabled. The USART presents all incoming data.
 *  0b1..Enabled. The USART receiver ignores incoming data that does not have the most significant bit of the data
 *       (typically the 9th bit) = 1. When the data MSB bit = 1, the receiver treats the incoming data normally,
 *       generating a received data interrupt. Software can then check the data to see if this is an address that
 *       should be handled. If it is, the ADDRDET bit is cleared by software and further incoming data is handled
 *       normally.
 */
#define USART_CTL_ADDRDET(x)                     (((uint32_t)(((uint32_t)(x)) << USART_CTL_ADDRDET_SHIFT)) & USART_CTL_ADDRDET_MASK)

#define USART_CTL_TXDIS_MASK                     (0x40U)
#define USART_CTL_TXDIS_SHIFT                    (6U)
/*! TXDIS - Transmit Disable.
 *  0b0..Not disabled. USART transmitter is not disabled.
 *  0b1..Disabled. USART transmitter is disabled after any character currently being transmitted is complete. This
 *       feature can be used to facilitate software flow control.
 */
#define USART_CTL_TXDIS(x)                       (((uint32_t)(((uint32_t)(x)) << USART_CTL_TXDIS_SHIFT)) & USART_CTL_TXDIS_MASK)

#define USART_CTL_CC_MASK                        (0x100U)
#define USART_CTL_CC_SHIFT                       (8U)
/*! CC - Continuous Clock generation. By default, SCLK is only output while data is being transmitted in synchronous mode.
 *  0b0..Clock on character. In synchronous mode, SCLK cycles only when characters are being sent on Un_TXD or to
 *       complete a character that is being received.
 *  0b1..Continuous clock. SCLK runs continuously in synchronous mode, allowing characters to be received on
 *       Un_RxD independently from transmission on Un_TXD).
 */
#define USART_CTL_CC(x)                          (((uint32_t)(((uint32_t)(x)) << USART_CTL_CC_SHIFT)) & USART_CTL_CC_MASK)

#define USART_CTL_CLRCCONRX_MASK                 (0x200U)
#define USART_CTL_CLRCCONRX_SHIFT                (9U)
/*! CLRCCONRX - Clear Continuous Clock.
 *  0b0..No effect. No effect on the CC bit.
 *  0b1..Auto-clear. The CC bit is automatically cleared when a complete character has been received. This bit is cleared at the same time.
 */
#define USART_CTL_CLRCCONRX(x)                   (((uint32_t)(((uint32_t)(x)) << USART_CTL_CLRCCONRX_SHIFT)) & USART_CTL_CLRCCONRX_MASK)

#define USART_CTL_AUTOBAUD_MASK                  (0x10000U)
#define USART_CTL_AUTOBAUD_SHIFT                 (16U)
/*! AUTOBAUD - Autobaud enable.
 *  0b0..Disabled. USART is in normal operating mode.
 *  0b1..Enabled. USART is in autobaud mode. This bit should only be set when the USART receiver is idle. The
 *       first start bit of RX is measured and used the update the BRG register to match the received data rate.
 *       AUTOBAUD is cleared once this process is complete, or if there is an AERR.
 */
#define USART_CTL_AUTOBAUD(x)                    (((uint32_t)(((uint32_t)(x)) << USART_CTL_AUTOBAUD_SHIFT)) & USART_CTL_AUTOBAUD_MASK)
/*! @} */

/*! @name STAT - USART Status register. The complete status value can be read here. Writing ones clears some bits in the register. Some bits can be cleared by writing a 1 to them. */
/*! @{ */

#define USART_STAT_RXIDLE_MASK                   (0x2U)
#define USART_STAT_RXIDLE_SHIFT                  (1U)
/*! RXIDLE - Receiver Idle. When 0, indicates that the receiver is currently in the process of
 *    receiving data. When 1, indicates that the receiver is not currently in the process of receiving
 *    data.
 */
#define USART_STAT_RXIDLE(x)                     (((uint32_t)(((uint32_t)(x)) << USART_STAT_RXIDLE_SHIFT)) & USART_STAT_RXIDLE_MASK)

#define USART_STAT_TXIDLE_MASK                   (0x8U)
#define USART_STAT_TXIDLE_SHIFT                  (3U)
/*! TXIDLE - Transmitter Idle. When 0, indicates that the transmitter is currently in the process of
 *    sending data.When 1, indicate that the transmitter is not currently in the process of sending
 *    data.
 */
#define USART_STAT_TXIDLE(x)                     (((uint32_t)(((uint32_t)(x)) << USART_STAT_TXIDLE_SHIFT)) & USART_STAT_TXIDLE_MASK)

#define USART_STAT_CTS_MASK                      (0x10U)
#define USART_STAT_CTS_SHIFT                     (4U)
/*! CTS - This bit reflects the current state of the CTS signal, regardless of the setting of the
 *    CTSEN bit in the CFG register. This will be the value of the CTS input pin unless loopback mode
 *    is enabled.
 */
#define USART_STAT_CTS(x)                        (((uint32_t)(((uint32_t)(x)) << USART_STAT_CTS_SHIFT)) & USART_STAT_CTS_MASK)

#define USART_STAT_DELTACTS_MASK                 (0x20U)
#define USART_STAT_DELTACTS_SHIFT                (5U)
/*! DELTACTS - This bit is set when a change in the state is detected for the CTS flag above. This bit is cleared by software. */
#define USART_STAT_DELTACTS(x)                   (((uint32_t)(((uint32_t)(x)) << USART_STAT_DELTACTS_SHIFT)) & USART_STAT_DELTACTS_MASK)

#define USART_STAT_TXDISSTAT_MASK                (0x40U)
#define USART_STAT_TXDISSTAT_SHIFT               (6U)
/*! TXDISSTAT - Transmitter Disabled Status flag. When 1, this bit indicates that the USART
 *    transmitter is fully idle after being disabled via the TXDIS bit in the CFG register (TXDIS = 1).
 */
#define USART_STAT_TXDISSTAT(x)                  (((uint32_t)(((uint32_t)(x)) << USART_STAT_TXDISSTAT_SHIFT)) & USART_STAT_TXDISSTAT_MASK)

#define USART_STAT_RXBRK_MASK                    (0x400U)
#define USART_STAT_RXBRK_SHIFT                   (10U)
/*! RXBRK - Received Break. This bit reflects the current state of the receiver break detection
 *    logic. It is set when the Un_RXD pin remains low for 16 bit times. Note that FRAMERRINT will also
 *    be set when this condition occurs because the stop bit(s) for the character would be missing.
 *    RXBRK is cleared when the Un_RXD pin goes high.
 */
#define USART_STAT_RXBRK(x)                      (((uint32_t)(((uint32_t)(x)) << USART_STAT_RXBRK_SHIFT)) & USART_STAT_RXBRK_MASK)

#define USART_STAT_DELTARXBRK_MASK               (0x800U)
#define USART_STAT_DELTARXBRK_SHIFT              (11U)
/*! DELTARXBRK - This bit is set when a change in the state of receiver break detection occurs. Cleared by software. */
#define USART_STAT_DELTARXBRK(x)                 (((uint32_t)(((uint32_t)(x)) << USART_STAT_DELTARXBRK_SHIFT)) & USART_STAT_DELTARXBRK_MASK)

#define USART_STAT_START_MASK                    (0x1000U)
#define USART_STAT_START_SHIFT                   (12U)
/*! START - This bit is set when a start is detected on the receiver input. Its purpose is primarily
 *    to allow wake-up from Deep-sleep or Power-down mode immediately when a start is detected.
 *    Cleared by software.
 */
#define USART_STAT_START(x)                      (((uint32_t)(((uint32_t)(x)) << USART_STAT_START_SHIFT)) & USART_STAT_START_MASK)

#define USART_STAT_FRAMERRINT_MASK               (0x2000U)
#define USART_STAT_FRAMERRINT_SHIFT              (13U)
/*! FRAMERRINT - Framing Error interrupt flag. This flag is set when a character is received with a
 *    missing stop bit at the expected location. This could be an indication of a baud rate or
 *    configuration mismatch with the transmitting source.
 */
#define USART_STAT_FRAMERRINT(x)                 (((uint32_t)(((uint32_t)(x)) << USART_STAT_FRAMERRINT_SHIFT)) & USART_STAT_FRAMERRINT_MASK)

#define USART_STAT_PARITYERRINT_MASK             (0x4000U)
#define USART_STAT_PARITYERRINT_SHIFT            (14U)
/*! PARITYERRINT - Parity Error interrupt flag. This flag is set when a parity error is detected in a received character. */
#define USART_STAT_PARITYERRINT(x)               (((uint32_t)(((uint32_t)(x)) << USART_STAT_PARITYERRINT_SHIFT)) & USART_STAT_PARITYERRINT_MASK)

#define USART_STAT_RXNOISEINT_MASK               (0x8000U)
#define USART_STAT_RXNOISEINT_SHIFT              (15U)
/*! RXNOISEINT - Received Noise interrupt flag. Three samples of received data are taken in order to
 *    determine the value of each received data bit, except in synchronous mode. This acts as a
 *    noise filter if one sample disagrees. This flag is set when a received data bit contains one
 *    disagreeing sample. This could indicate line noise, a baud rate or character format mismatch, or
 *    loss of synchronization during data reception.
 */
#define USART_STAT_RXNOISEINT(x)                 (((uint32_t)(((uint32_t)(x)) << USART_STAT_RXNOISEINT_SHIFT)) & USART_STAT_RXNOISEINT_MASK)

#define USART_STAT_ABERR_MASK                    (0x10000U)
#define USART_STAT_ABERR_SHIFT                   (16U)
/*! ABERR - Auto baud Error. An auto baud error can occur if the BRG counts to its limit before the
 *    end of the start bit that is being measured, essentially an auto baud time-out.
 */
#define USART_STAT_ABERR(x)                      (((uint32_t)(((uint32_t)(x)) << USART_STAT_ABERR_SHIFT)) & USART_STAT_ABERR_MASK)
/*! @} */

/*! @name INTENSET - Interrupt Enable read and Set register for USART (not FIFO) status. Contains individual interrupt enable bits for each potential USART interrupt. A complete value may be read from this register. Writing a 1 to any implemented bit position causes that bit to be set. */
/*! @{ */

#define USART_INTENSET_TXIDLEEN_MASK             (0x8U)
#define USART_INTENSET_TXIDLEEN_SHIFT            (3U)
/*! TXIDLEEN - When 1, enables an interrupt when the transmitter becomes idle (TXIDLE = 1). */
#define USART_INTENSET_TXIDLEEN(x)               (((uint32_t)(((uint32_t)(x)) << USART_INTENSET_TXIDLEEN_SHIFT)) & USART_INTENSET_TXIDLEEN_MASK)

#define USART_INTENSET_DELTACTSEN_MASK           (0x20U)
#define USART_INTENSET_DELTACTSEN_SHIFT          (5U)
/*! DELTACTSEN - When 1, enables an interrupt when there is a change in the state of the CTS input. */
#define USART_INTENSET_DELTACTSEN(x)             (((uint32_t)(((uint32_t)(x)) << USART_INTENSET_DELTACTSEN_SHIFT)) & USART_INTENSET_DELTACTSEN_MASK)

#define USART_INTENSET_TXDISEN_MASK              (0x40U)
#define USART_INTENSET_TXDISEN_SHIFT             (6U)
/*! TXDISEN - When 1, enables an interrupt when the transmitter is fully disabled as indicated by
 *    the TXDISINT flag in STAT. See description of the TXDISINT bit for details.
 */
#define USART_INTENSET_TXDISEN(x)                (((uint32_t)(((uint32_t)(x)) << USART_INTENSET_TXDISEN_SHIFT)) & USART_INTENSET_TXDISEN_MASK)

#define USART_INTENSET_DELTARXBRKEN_MASK         (0x800U)
#define USART_INTENSET_DELTARXBRKEN_SHIFT        (11U)
/*! DELTARXBRKEN - When 1, enables an interrupt when a change of state has occurred in the detection
 *    of a received break condition (break condition asserted or deasserted).
 */
#define USART_INTENSET_DELTARXBRKEN(x)           (((uint32_t)(((uint32_t)(x)) << USART_INTENSET_DELTARXBRKEN_SHIFT)) & USART_INTENSET_DELTARXBRKEN_MASK)

#define USART_INTENSET_STARTEN_MASK              (0x1000U)
#define USART_INTENSET_STARTEN_SHIFT             (12U)
/*! STARTEN - When 1, enables an interrupt when a received start bit has been detected. */
#define USART_INTENSET_STARTEN(x)                (((uint32_t)(((uint32_t)(x)) << USART_INTENSET_STARTEN_SHIFT)) & USART_INTENSET_STARTEN_MASK)

#define USART_INTENSET_FRAMERREN_MASK            (0x2000U)
#define USART_INTENSET_FRAMERREN_SHIFT           (13U)
/*! FRAMERREN - When 1, enables an interrupt when a framing error has been detected. */
#define USART_INTENSET_FRAMERREN(x)              (((uint32_t)(((uint32_t)(x)) << USART_INTENSET_FRAMERREN_SHIFT)) & USART_INTENSET_FRAMERREN_MASK)

#define USART_INTENSET_PARITYERREN_MASK          (0x4000U)
#define USART_INTENSET_PARITYERREN_SHIFT         (14U)
/*! PARITYERREN - When 1, enables an interrupt when a parity error has been detected. */
#define USART_INTENSET_PARITYERREN(x)            (((uint32_t)(((uint32_t)(x)) << USART_INTENSET_PARITYERREN_SHIFT)) & USART_INTENSET_PARITYERREN_MASK)

#define USART_INTENSET_RXNOISEEN_MASK            (0x8000U)
#define USART_INTENSET_RXNOISEEN_SHIFT           (15U)
/*! RXNOISEEN - When 1, enables an interrupt when noise is detected. See description of the RXNOISEINT bit in Table 354. */
#define USART_INTENSET_RXNOISEEN(x)              (((uint32_t)(((uint32_t)(x)) << USART_INTENSET_RXNOISEEN_SHIFT)) & USART_INTENSET_RXNOISEEN_MASK)

#define USART_INTENSET_ABERREN_MASK              (0x10000U)
#define USART_INTENSET_ABERREN_SHIFT             (16U)
/*! ABERREN - When 1, enables an interrupt when an auto baud error occurs. */
#define USART_INTENSET_ABERREN(x)                (((uint32_t)(((uint32_t)(x)) << USART_INTENSET_ABERREN_SHIFT)) & USART_INTENSET_ABERREN_MASK)
/*! @} */

/*! @name INTENCLR - Interrupt Enable Clear register. Allows clearing any combination of bits in the INTENSET register. Writing a 1 to any implemented bit position causes the corresponding bit to be cleared. */
/*! @{ */

#define USART_INTENCLR_TXIDLECLR_MASK            (0x8U)
#define USART_INTENCLR_TXIDLECLR_SHIFT           (3U)
/*! TXIDLECLR - Writing 1 clears the corresponding bit in the INTENSET register. */
#define USART_INTENCLR_TXIDLECLR(x)              (((uint32_t)(((uint32_t)(x)) << USART_INTENCLR_TXIDLECLR_SHIFT)) & USART_INTENCLR_TXIDLECLR_MASK)

#define USART_INTENCLR_DELTACTSCLR_MASK          (0x20U)
#define USART_INTENCLR_DELTACTSCLR_SHIFT         (5U)
/*! DELTACTSCLR - Writing 1 clears the corresponding bit in the INTENSET register. */
#define USART_INTENCLR_DELTACTSCLR(x)            (((uint32_t)(((uint32_t)(x)) << USART_INTENCLR_DELTACTSCLR_SHIFT)) & USART_INTENCLR_DELTACTSCLR_MASK)

#define USART_INTENCLR_TXDISCLR_MASK             (0x40U)
#define USART_INTENCLR_TXDISCLR_SHIFT            (6U)
/*! TXDISCLR - Writing 1 clears the corresponding bit in the INTENSET register. */
#define USART_INTENCLR_TXDISCLR(x)               (((uint32_t)(((uint32_t)(x)) << USART_INTENCLR_TXDISCLR_SHIFT)) & USART_INTENCLR_TXDISCLR_MASK)

#define USART_INTENCLR_DELTARXBRKCLR_MASK        (0x800U)
#define USART_INTENCLR_DELTARXBRKCLR_SHIFT       (11U)
/*! DELTARXBRKCLR - Writing 1 clears the corresponding bit in the INTENSET register. */
#define USART_INTENCLR_DELTARXBRKCLR(x)          (((uint32_t)(((uint32_t)(x)) << USART_INTENCLR_DELTARXBRKCLR_SHIFT)) & USART_INTENCLR_DELTARXBRKCLR_MASK)

#define USART_INTENCLR_STARTCLR_MASK             (0x1000U)
#define USART_INTENCLR_STARTCLR_SHIFT            (12U)
/*! STARTCLR - Writing 1 clears the corresponding bit in the INTENSET register. */
#define USART_INTENCLR_STARTCLR(x)               (((uint32_t)(((uint32_t)(x)) << USART_INTENCLR_STARTCLR_SHIFT)) & USART_INTENCLR_STARTCLR_MASK)

#define USART_INTENCLR_FRAMERRCLR_MASK           (0x2000U)
#define USART_INTENCLR_FRAMERRCLR_SHIFT          (13U)
/*! FRAMERRCLR - Writing 1 clears the corresponding bit in the INTENSET register. */
#define USART_INTENCLR_FRAMERRCLR(x)             (((uint32_t)(((uint32_t)(x)) << USART_INTENCLR_FRAMERRCLR_SHIFT)) & USART_INTENCLR_FRAMERRCLR_MASK)

#define USART_INTENCLR_PARITYERRCLR_MASK         (0x4000U)
#define USART_INTENCLR_PARITYERRCLR_SHIFT        (14U)
/*! PARITYERRCLR - Writing 1 clears the corresponding bit in the INTENSET register. */
#define USART_INTENCLR_PARITYERRCLR(x)           (((uint32_t)(((uint32_t)(x)) << USART_INTENCLR_PARITYERRCLR_SHIFT)) & USART_INTENCLR_PARITYERRCLR_MASK)

#define USART_INTENCLR_RXNOISECLR_MASK           (0x8000U)
#define USART_INTENCLR_RXNOISECLR_SHIFT          (15U)
/*! RXNOISECLR - Writing 1 clears the corresponding bit in the INTENSET register. */
#define USART_INTENCLR_RXNOISECLR(x)             (((uint32_t)(((uint32_t)(x)) << USART_INTENCLR_RXNOISECLR_SHIFT)) & USART_INTENCLR_RXNOISECLR_MASK)

#define USART_INTENCLR_ABERRCLR_MASK             (0x10000U)
#define USART_INTENCLR_ABERRCLR_SHIFT            (16U)
/*! ABERRCLR - Writing 1 clears the corresponding bit in the INTENSET register. */
#define USART_INTENCLR_ABERRCLR(x)               (((uint32_t)(((uint32_t)(x)) << USART_INTENCLR_ABERRCLR_SHIFT)) & USART_INTENCLR_ABERRCLR_MASK)
/*! @} */

/*! @name BRG - Baud Rate Generator register. 16-bit integer baud rate divisor value. */
/*! @{ */

#define USART_BRG_BRGVAL_MASK                    (0xFFFFU)
#define USART_BRG_BRGVAL_SHIFT                   (0U)
/*! BRGVAL - This value is used to divide the USART input clock to determine the baud rate, based on
 *    the input clock from the FRG. 0 = FCLK is used directly by the USART function. 1 = FCLK is
 *    divided by 2 before use by the USART function. 2 = FCLK is divided by 3 before use by the USART
 *    function. 0xFFFF = FCLK is divided by 65,536 before use by the USART function.
 */
#define USART_BRG_BRGVAL(x)                      (((uint32_t)(((uint32_t)(x)) << USART_BRG_BRGVAL_SHIFT)) & USART_BRG_BRGVAL_MASK)
/*! @} */

/*! @name INTSTAT - Interrupt status register. Reflects interrupts that are currently enabled. */
/*! @{ */

#define USART_INTSTAT_TXIDLE_MASK                (0x8U)
#define USART_INTSTAT_TXIDLE_SHIFT               (3U)
/*! TXIDLE - Transmitter Idle status. */
#define USART_INTSTAT_TXIDLE(x)                  (((uint32_t)(((uint32_t)(x)) << USART_INTSTAT_TXIDLE_SHIFT)) & USART_INTSTAT_TXIDLE_MASK)

#define USART_INTSTAT_DELTACTS_MASK              (0x20U)
#define USART_INTSTAT_DELTACTS_SHIFT             (5U)
/*! DELTACTS - This bit is set when a change in the state of the CTS input is detected. */
#define USART_INTSTAT_DELTACTS(x)                (((uint32_t)(((uint32_t)(x)) << USART_INTSTAT_DELTACTS_SHIFT)) & USART_INTSTAT_DELTACTS_MASK)

#define USART_INTSTAT_TXDISINT_MASK              (0x40U)
#define USART_INTSTAT_TXDISINT_SHIFT             (6U)
/*! TXDISINT - Transmitter Disabled Interrupt flag. */
#define USART_INTSTAT_TXDISINT(x)                (((uint32_t)(((uint32_t)(x)) << USART_INTSTAT_TXDISINT_SHIFT)) & USART_INTSTAT_TXDISINT_MASK)

#define USART_INTSTAT_DELTARXBRK_MASK            (0x800U)
#define USART_INTSTAT_DELTARXBRK_SHIFT           (11U)
/*! DELTARXBRK - This bit is set when a change in the state of receiver break detection occurs. */
#define USART_INTSTAT_DELTARXBRK(x)              (((uint32_t)(((uint32_t)(x)) << USART_INTSTAT_DELTARXBRK_SHIFT)) & USART_INTSTAT_DELTARXBRK_MASK)

#define USART_INTSTAT_START_MASK                 (0x1000U)
#define USART_INTSTAT_START_SHIFT                (12U)
/*! START - This bit is set when a start is detected on the receiver input. */
#define USART_INTSTAT_START(x)                   (((uint32_t)(((uint32_t)(x)) << USART_INTSTAT_START_SHIFT)) & USART_INTSTAT_START_MASK)

#define USART_INTSTAT_FRAMERRINT_MASK            (0x2000U)
#define USART_INTSTAT_FRAMERRINT_SHIFT           (13U)
/*! FRAMERRINT - Framing Error interrupt flag. */
#define USART_INTSTAT_FRAMERRINT(x)              (((uint32_t)(((uint32_t)(x)) << USART_INTSTAT_FRAMERRINT_SHIFT)) & USART_INTSTAT_FRAMERRINT_MASK)

#define USART_INTSTAT_PARITYERRINT_MASK          (0x4000U)
#define USART_INTSTAT_PARITYERRINT_SHIFT         (14U)
/*! PARITYERRINT - Parity Error interrupt flag. */
#define USART_INTSTAT_PARITYERRINT(x)            (((uint32_t)(((uint32_t)(x)) << USART_INTSTAT_PARITYERRINT_SHIFT)) & USART_INTSTAT_PARITYERRINT_MASK)

#define USART_INTSTAT_RXNOISEINT_MASK            (0x8000U)
#define USART_INTSTAT_RXNOISEINT_SHIFT           (15U)
/*! RXNOISEINT - Received Noise interrupt flag. */
#define USART_INTSTAT_RXNOISEINT(x)              (((uint32_t)(((uint32_t)(x)) << USART_INTSTAT_RXNOISEINT_SHIFT)) & USART_INTSTAT_RXNOISEINT_MASK)

#define USART_INTSTAT_ABERRINT_MASK              (0x10000U)
#define USART_INTSTAT_ABERRINT_SHIFT             (16U)
/*! ABERRINT - Auto baud Error Interrupt flag. */
#define USART_INTSTAT_ABERRINT(x)                (((uint32_t)(((uint32_t)(x)) << USART_INTSTAT_ABERRINT_SHIFT)) & USART_INTSTAT_ABERRINT_MASK)
/*! @} */

/*! @name OSR - Oversample selection register for asynchronous communication. */
/*! @{ */

#define USART_OSR_OSRVAL_MASK                    (0xFU)
#define USART_OSR_OSRVAL_SHIFT                   (0U)
/*! OSRVAL - Oversample Selection Value. 0 to 3 = not supported 0x4 = 5 function clocks are used to
 *    transmit and receive each data bit. 0x5 = 6 function clocks are used to transmit and receive
 *    each data bit. 0xF= 16 function clocks are used to transmit and receive each data bit.
 */
#define USART_OSR_OSRVAL(x)                      (((uint32_t)(((uint32_t)(x)) << USART_OSR_OSRVAL_SHIFT)) & USART_OSR_OSRVAL_MASK)
/*! @} */

/*! @name ADDR - Address register for automatic address matching. */
/*! @{ */

#define USART_ADDR_ADDRESS_MASK                  (0xFFU)
#define USART_ADDR_ADDRESS_SHIFT                 (0U)
/*! ADDRESS - 8-bit address used with automatic address matching. Used when address detection is
 *    enabled (ADDRDET in CTL = 1) and automatic address matching is enabled (AUTOADDR in CFG = 1).
 */
#define USART_ADDR_ADDRESS(x)                    (((uint32_t)(((uint32_t)(x)) << USART_ADDR_ADDRESS_SHIFT)) & USART_ADDR_ADDRESS_MASK)
/*! @} */

/*! @name FIFOCFG - FIFO configuration and enable register. */
/*! @{ */

#define USART_FIFOCFG_ENABLETX_MASK              (0x1U)
#define USART_FIFOCFG_ENABLETX_SHIFT             (0U)
/*! ENABLETX - Enable the transmit FIFO.
 *  0b0..The transmit FIFO is not enabled.
 *  0b1..The transmit FIFO is enabled.
 */
#define USART_FIFOCFG_ENABLETX(x)                (((uint32_t)(((uint32_t)(x)) << USART_FIFOCFG_ENABLETX_SHIFT)) & USART_FIFOCFG_ENABLETX_MASK)

#define USART_FIFOCFG_ENABLERX_MASK              (0x2U)
#define USART_FIFOCFG_ENABLERX_SHIFT             (1U)
/*! ENABLERX - Enable the receive FIFO.
 *  0b0..The receive FIFO is not enabled.
 *  0b1..The receive FIFO is enabled.
 */
#define USART_FIFOCFG_ENABLERX(x)                (((uint32_t)(((uint32_t)(x)) << USART_FIFOCFG_ENABLERX_SHIFT)) & USART_FIFOCFG_ENABLERX_MASK)

#define USART_FIFOCFG_SIZE_MASK                  (0x30U)
#define USART_FIFOCFG_SIZE_SHIFT                 (4U)
/*! SIZE - FIFO size configuration. This is a read-only field. 0x0 = FIFO is configured as 16
 *    entries of 8 bits. 0x1, 0x2, 0x3 = not applicable to USART.
 */
#define USART_FIFOCFG_SIZE(x)                    (((uint32_t)(((uint32_t)(x)) << USART_FIFOCFG_SIZE_SHIFT)) & USART_FIFOCFG_SIZE_MASK)

#define USART_FIFOCFG_DMATX_MASK                 (0x1000U)
#define USART_FIFOCFG_DMATX_SHIFT                (12U)
/*! DMATX - DMA configuration for transmit.
 *  0b0..DMA is not used for the transmit function.
 *  0b1..Trigger DMA for the transmit function if the FIFO is not full. Generally, data interrupts would be disabled if DMA is enabled.
 */
#define USART_FIFOCFG_DMATX(x)                   (((uint32_t)(((uint32_t)(x)) << USART_FIFOCFG_DMATX_SHIFT)) & USART_FIFOCFG_DMATX_MASK)

#define USART_FIFOCFG_DMARX_MASK                 (0x2000U)
#define USART_FIFOCFG_DMARX_SHIFT                (13U)
/*! DMARX - DMA configuration for receive.
 *  0b0..DMA is not used for the receive function.
 *  0b1..Trigger DMA for the receive function if the FIFO is not empty. Generally, data interrupts would be disabled if DMA is enabled.
 */
#define USART_FIFOCFG_DMARX(x)                   (((uint32_t)(((uint32_t)(x)) << USART_FIFOCFG_DMARX_SHIFT)) & USART_FIFOCFG_DMARX_MASK)

#define USART_FIFOCFG_WAKETX_MASK                (0x4000U)
#define USART_FIFOCFG_WAKETX_SHIFT               (14U)
/*! WAKETX - Wake-up for transmit FIFO level. This allows the device to be woken from reduced power
 *    modes (up to power-down, as long as the peripheral function works in that power mode) without
 *    enabling the TXLVL interrupt. Only DMA wakes up, processes data, and goes back to sleep. The
 *    CPU will remain stopped until woken by another cause, such as DMA completion. See Hardware
 *    Wake-up control register.
 *  0b0..Only enabled interrupts will wake up the device form reduced power modes.
 *  0b1..A device wake-up for DMA will occur if the transmit FIFO level reaches the value specified by TXLVL in
 *       FIFOTRIG, even when the TXLVL interrupt is not enabled.
 */
#define USART_FIFOCFG_WAKETX(x)                  (((uint32_t)(((uint32_t)(x)) << USART_FIFOCFG_WAKETX_SHIFT)) & USART_FIFOCFG_WAKETX_MASK)

#define USART_FIFOCFG_WAKERX_MASK                (0x8000U)
#define USART_FIFOCFG_WAKERX_SHIFT               (15U)
/*! WAKERX - Wake-up for receive FIFO level. This allows the device to be woken from reduced power
 *    modes (up to power-down, as long as the peripheral function works in that power mode) without
 *    enabling the TXLVL interrupt. Only DMA wakes up, processes data, and goes back to sleep. The
 *    CPU will remain stopped until woken by another cause, such as DMA completion. See Hardware
 *    Wake-up control register.
 *  0b0..Only enabled interrupts will wake up the device form reduced power modes.
 *  0b1..A device wake-up for DMA will occur if the receive FIFO level reaches the value specified by RXLVL in
 *       FIFOTRIG, even when the RXLVL interrupt is not enabled.
 */
#define USART_FIFOCFG_WAKERX(x)                  (((uint32_t)(((uint32_t)(x)) << USART_FIFOCFG_WAKERX_SHIFT)) & USART_FIFOCFG_WAKERX_MASK)

#define USART_FIFOCFG_EMPTYTX_MASK               (0x10000U)
#define USART_FIFOCFG_EMPTYTX_SHIFT              (16U)
/*! EMPTYTX - Empty command for the transmit FIFO. When a 1 is written to this bit, the TX FIFO is emptied. */
#define USART_FIFOCFG_EMPTYTX(x)                 (((uint32_t)(((uint32_t)(x)) << USART_FIFOCFG_EMPTYTX_SHIFT)) & USART_FIFOCFG_EMPTYTX_MASK)

#define USART_FIFOCFG_EMPTYRX_MASK               (0x20000U)
#define USART_FIFOCFG_EMPTYRX_SHIFT              (17U)
/*! EMPTYRX - Empty command for the receive FIFO. When a 1 is written to this bit, the RX FIFO is emptied. */
#define USART_FIFOCFG_EMPTYRX(x)                 (((uint32_t)(((uint32_t)(x)) << USART_FIFOCFG_EMPTYRX_SHIFT)) & USART_FIFOCFG_EMPTYRX_MASK)
/*! @} */

/*! @name FIFOSTAT - FIFO status register. */
/*! @{ */

#define USART_FIFOSTAT_TXERR_MASK                (0x1U)
#define USART_FIFOSTAT_TXERR_SHIFT               (0U)
/*! TXERR - TX FIFO error. Will be set if a transmit FIFO error occurs. This could be an overflow
 *    caused by pushing data into a full FIFO, or by an underflow if the FIFO is empty when data is
 *    needed. Cleared by writing a 1 to this bit.
 */
#define USART_FIFOSTAT_TXERR(x)                  (((uint32_t)(((uint32_t)(x)) << USART_FIFOSTAT_TXERR_SHIFT)) & USART_FIFOSTAT_TXERR_MASK)

#define USART_FIFOSTAT_RXERR_MASK                (0x2U)
#define USART_FIFOSTAT_RXERR_SHIFT               (1U)
/*! RXERR - RX FIFO error. Will be set if a receive FIFO overflow occurs, caused by software or DMA
 *    not emptying the FIFO fast enough. Cleared by writing a 1 to this bit.
 */
#define USART_FIFOSTAT_RXERR(x)                  (((uint32_t)(((uint32_t)(x)) << USART_FIFOSTAT_RXERR_SHIFT)) & USART_FIFOSTAT_RXERR_MASK)

#define USART_FIFOSTAT_PERINT_MASK               (0x8U)
#define USART_FIFOSTAT_PERINT_SHIFT              (3U)
/*! PERINT - Peripheral interrupt. When 1, this indicates that the peripheral function has asserted
 *    an interrupt. The details can be found by reading the peripheral's STAT register.
 */
#define USART_FIFOSTAT_PERINT(x)                 (((uint32_t)(((uint32_t)(x)) << USART_FIFOSTAT_PERINT_SHIFT)) & USART_FIFOSTAT_PERINT_MASK)

#define USART_FIFOSTAT_TXEMPTY_MASK              (0x10U)
#define USART_FIFOSTAT_TXEMPTY_SHIFT             (4U)
/*! TXEMPTY - Transmit FIFO empty. When 1, the transmit FIFO is empty. The peripheral may still be processing the last piece of data. */
#define USART_FIFOSTAT_TXEMPTY(x)                (((uint32_t)(((uint32_t)(x)) << USART_FIFOSTAT_TXEMPTY_SHIFT)) & USART_FIFOSTAT_TXEMPTY_MASK)

#define USART_FIFOSTAT_TXNOTFULL_MASK            (0x20U)
#define USART_FIFOSTAT_TXNOTFULL_SHIFT           (5U)
/*! TXNOTFULL - Transmit FIFO not full. When 1, the transmit FIFO is not full, so more data can be
 *    written. When 0, the transmit FIFO is full and another write would cause it to overflow.
 */
#define USART_FIFOSTAT_TXNOTFULL(x)              (((uint32_t)(((uint32_t)(x)) << USART_FIFOSTAT_TXNOTFULL_SHIFT)) & USART_FIFOSTAT_TXNOTFULL_MASK)

#define USART_FIFOSTAT_RXNOTEMPTY_MASK           (0x40U)
#define USART_FIFOSTAT_RXNOTEMPTY_SHIFT          (6U)
/*! RXNOTEMPTY - Receive FIFO not empty. When 1, the receive FIFO is not empty, so data can be read. When 0, the receive FIFO is empty. */
#define USART_FIFOSTAT_RXNOTEMPTY(x)             (((uint32_t)(((uint32_t)(x)) << USART_FIFOSTAT_RXNOTEMPTY_SHIFT)) & USART_FIFOSTAT_RXNOTEMPTY_MASK)

#define USART_FIFOSTAT_RXFULL_MASK               (0x80U)
#define USART_FIFOSTAT_RXFULL_SHIFT              (7U)
/*! RXFULL - Receive FIFO full. When 1, the receive FIFO is full. Data needs to be read out to
 *    prevent the peripheral from causing an overflow.
 */
#define USART_FIFOSTAT_RXFULL(x)                 (((uint32_t)(((uint32_t)(x)) << USART_FIFOSTAT_RXFULL_SHIFT)) & USART_FIFOSTAT_RXFULL_MASK)

#define USART_FIFOSTAT_TXLVL_MASK                (0x1F00U)
#define USART_FIFOSTAT_TXLVL_SHIFT               (8U)
/*! TXLVL - Transmit FIFO current level. A 0 means the TX FIFO is currently empty, and the TXEMPTY
 *    and TXNOTFULL flags will be 1. Other values tell how much data is actually in the TX FIFO at
 *    the point where the read occurs. If the TX FIFO is full, the TXEMPTY and TXNOTFULL flags will be
 *    0.
 */
#define USART_FIFOSTAT_TXLVL(x)                  (((uint32_t)(((uint32_t)(x)) << USART_FIFOSTAT_TXLVL_SHIFT)) & USART_FIFOSTAT_TXLVL_MASK)

#define USART_FIFOSTAT_RXLVL_MASK                (0x1F0000U)
#define USART_FIFOSTAT_RXLVL_SHIFT               (16U)
/*! RXLVL - Receive FIFO current level. A 0 means the RX FIFO is currently empty, and the RXFULL and
 *    RXNOTEMPTY flags will be 0. Other values tell how much data is actually in the RX FIFO at the
 *    point where the read occurs. If the RX FIFO is full, the RXFULL and RXNOTEMPTY flags will be
 *    1.
 */
#define USART_FIFOSTAT_RXLVL(x)                  (((uint32_t)(((uint32_t)(x)) << USART_FIFOSTAT_RXLVL_SHIFT)) & USART_FIFOSTAT_RXLVL_MASK)
/*! @} */

/*! @name FIFOTRIG - FIFO trigger settings for interrupt and DMA request. */
/*! @{ */

#define USART_FIFOTRIG_TXLVLENA_MASK             (0x1U)
#define USART_FIFOTRIG_TXLVLENA_SHIFT            (0U)
/*! TXLVLENA - Transmit FIFO level trigger enable. This trigger will become an interrupt if enabled
 *    in FIFOINTENSET, or a DMA trigger if DMATX in FIFOCFG is set.
 *  0b0..Transmit FIFO level does not generate a FIFO level trigger.
 *  0b1..An trigger will be generated if the transmit FIFO level reaches the value specified by the TXLVL field in this register.
 */
#define USART_FIFOTRIG_TXLVLENA(x)               (((uint32_t)(((uint32_t)(x)) << USART_FIFOTRIG_TXLVLENA_SHIFT)) & USART_FIFOTRIG_TXLVLENA_MASK)

#define USART_FIFOTRIG_RXLVLENA_MASK             (0x2U)
#define USART_FIFOTRIG_RXLVLENA_SHIFT            (1U)
/*! RXLVLENA - Receive FIFO level trigger enable. This trigger will become an interrupt if enabled
 *    in FIFOINTENSET, or a DMA trigger if DMARX in FIFOCFG is set.
 *  0b0..Receive FIFO level does not generate a FIFO level trigger.
 *  0b1..An trigger will be generated if the receive FIFO level reaches the value specified by the RXLVL field in this register.
 */
#define USART_FIFOTRIG_RXLVLENA(x)               (((uint32_t)(((uint32_t)(x)) << USART_FIFOTRIG_RXLVLENA_SHIFT)) & USART_FIFOTRIG_RXLVLENA_MASK)

#define USART_FIFOTRIG_TXLVL_MASK                (0xF00U)
#define USART_FIFOTRIG_TXLVL_SHIFT               (8U)
/*! TXLVL - Transmit FIFO level trigger point. This field is used only when TXLVLENA = 1. If enabled
 *    to do so, the FIFO level can wake up the device just enough to perform DMA, then return to
 *    the reduced power mode. See Hardware Wake-up control register. 0 = trigger when the TX FIFO
 *    becomes empty. 1 = trigger when the TX FIFO level decreases to one entry. 15 = trigger when the TX
 *    FIFO level decreases to 15 entries (is no longer full).
 */
#define USART_FIFOTRIG_TXLVL(x)                  (((uint32_t)(((uint32_t)(x)) << USART_FIFOTRIG_TXLVL_SHIFT)) & USART_FIFOTRIG_TXLVL_MASK)

#define USART_FIFOTRIG_RXLVL_MASK                (0xF0000U)
#define USART_FIFOTRIG_RXLVL_SHIFT               (16U)
/*! RXLVL - Receive FIFO level trigger point. The RX FIFO level is checked when a new piece of data
 *    is received. This field is used only when RXLVLENA = 1. If enabled to do so, the FIFO level
 *    can wake up the device just enough to perform DMA, then return to the reduced power mode. See
 *    Hardware Wake-up control register. 0 = trigger when the RX FIFO has received one entry (is no
 *    longer empty). 1 = trigger when the RX FIFO has received two entries. 15 = trigger when the RX
 *    FIFO has received 16 entries (has become full).
 */
#define USART_FIFOTRIG_RXLVL(x)                  (((uint32_t)(((uint32_t)(x)) << USART_FIFOTRIG_RXLVL_SHIFT)) & USART_FIFOTRIG_RXLVL_MASK)
/*! @} */

/*! @name FIFOINTENSET - FIFO interrupt enable set (enable) and read register. */
/*! @{ */

#define USART_FIFOINTENSET_TXERR_MASK            (0x1U)
#define USART_FIFOINTENSET_TXERR_SHIFT           (0U)
/*! TXERR - Determines whether an interrupt occurs when a transmit error occurs, based on the TXERR flag in the FIFOSTAT register.
 *  0b0..No interrupt will be generated for a transmit error.
 *  0b1..An interrupt will be generated when a transmit error occurs.
 */
#define USART_FIFOINTENSET_TXERR(x)              (((uint32_t)(((uint32_t)(x)) << USART_FIFOINTENSET_TXERR_SHIFT)) & USART_FIFOINTENSET_TXERR_MASK)

#define USART_FIFOINTENSET_RXERR_MASK            (0x2U)
#define USART_FIFOINTENSET_RXERR_SHIFT           (1U)
/*! RXERR - Determines whether an interrupt occurs when a receive error occurs, based on the RXERR flag in the FIFOSTAT register.
 *  0b0..No interrupt will be generated for a receive error.
 *  0b1..An interrupt will be generated when a receive error occurs.
 */
#define USART_FIFOINTENSET_RXERR(x)              (((uint32_t)(((uint32_t)(x)) << USART_FIFOINTENSET_RXERR_SHIFT)) & USART_FIFOINTENSET_RXERR_MASK)

#define USART_FIFOINTENSET_TXLVL_MASK            (0x4U)
#define USART_FIFOINTENSET_TXLVL_SHIFT           (2U)
/*! TXLVL - Determines whether an interrupt occurs when a the transmit FIFO reaches the level
 *    specified by the TXLVL field in the FIFOTRIG register.
 *  0b0..No interrupt will be generated based on the TX FIFO level.
 *  0b1..If TXLVLENA in the FIFOTRIG register = 1, an interrupt will be generated when the TX FIFO level decreases
 *       to the level specified by TXLVL in the FIFOTRIG register.
 */
#define USART_FIFOINTENSET_TXLVL(x)              (((uint32_t)(((uint32_t)(x)) << USART_FIFOINTENSET_TXLVL_SHIFT)) & USART_FIFOINTENSET_TXLVL_MASK)

#define USART_FIFOINTENSET_RXLVL_MASK            (0x8U)
#define USART_FIFOINTENSET_RXLVL_SHIFT           (3U)
/*! RXLVL - Determines whether an interrupt occurs when a the receive FIFO reaches the level
 *    specified by the TXLVL field in the FIFOTRIG register.
 *  0b0..No interrupt will be generated based on the RX FIFO level.
 *  0b1..If RXLVLENA in the FIFOTRIG register = 1, an interrupt will be generated when the when the RX FIFO level
 *       increases to the level specified by RXLVL in the FIFOTRIG register.
 */
#define USART_FIFOINTENSET_RXLVL(x)              (((uint32_t)(((uint32_t)(x)) << USART_FIFOINTENSET_RXLVL_SHIFT)) & USART_FIFOINTENSET_RXLVL_MASK)
/*! @} */

/*! @name FIFOINTENCLR - FIFO interrupt enable clear (disable) and read register. */
/*! @{ */

#define USART_FIFOINTENCLR_TXERR_MASK            (0x1U)
#define USART_FIFOINTENCLR_TXERR_SHIFT           (0U)
/*! TXERR - Writing one clears the corresponding bits in the FIFOINTENSET register. */
#define USART_FIFOINTENCLR_TXERR(x)              (((uint32_t)(((uint32_t)(x)) << USART_FIFOINTENCLR_TXERR_SHIFT)) & USART_FIFOINTENCLR_TXERR_MASK)

#define USART_FIFOINTENCLR_RXERR_MASK            (0x2U)
#define USART_FIFOINTENCLR_RXERR_SHIFT           (1U)
/*! RXERR - Writing one clears the corresponding bits in the FIFOINTENSET register. */
#define USART_FIFOINTENCLR_RXERR(x)              (((uint32_t)(((uint32_t)(x)) << USART_FIFOINTENCLR_RXERR_SHIFT)) & USART_FIFOINTENCLR_RXERR_MASK)

#define USART_FIFOINTENCLR_TXLVL_MASK            (0x4U)
#define USART_FIFOINTENCLR_TXLVL_SHIFT           (2U)
/*! TXLVL - Writing one clears the corresponding bits in the FIFOINTENSET register. */
#define USART_FIFOINTENCLR_TXLVL(x)              (((uint32_t)(((uint32_t)(x)) << USART_FIFOINTENCLR_TXLVL_SHIFT)) & USART_FIFOINTENCLR_TXLVL_MASK)

#define USART_FIFOINTENCLR_RXLVL_MASK            (0x8U)
#define USART_FIFOINTENCLR_RXLVL_SHIFT           (3U)
/*! RXLVL - Writing one clears the corresponding bits in the FIFOINTENSET register. */
#define USART_FIFOINTENCLR_RXLVL(x)              (((uint32_t)(((uint32_t)(x)) << USART_FIFOINTENCLR_RXLVL_SHIFT)) & USART_FIFOINTENCLR_RXLVL_MASK)
/*! @} */

/*! @name FIFOINTSTAT - FIFO interrupt status register. */
/*! @{ */

#define USART_FIFOINTSTAT_TXERR_MASK             (0x1U)
#define USART_FIFOINTSTAT_TXERR_SHIFT            (0U)
/*! TXERR - TX FIFO error. */
#define USART_FIFOINTSTAT_TXERR(x)               (((uint32_t)(((uint32_t)(x)) << USART_FIFOINTSTAT_TXERR_SHIFT)) & USART_FIFOINTSTAT_TXERR_MASK)

#define USART_FIFOINTSTAT_RXERR_MASK             (0x2U)
#define USART_FIFOINTSTAT_RXERR_SHIFT            (1U)
/*! RXERR - RX FIFO error. */
#define USART_FIFOINTSTAT_RXERR(x)               (((uint32_t)(((uint32_t)(x)) << USART_FIFOINTSTAT_RXERR_SHIFT)) & USART_FIFOINTSTAT_RXERR_MASK)

#define USART_FIFOINTSTAT_TXLVL_MASK             (0x4U)
#define USART_FIFOINTSTAT_TXLVL_SHIFT            (2U)
/*! TXLVL - Transmit FIFO level interrupt. */
#define USART_FIFOINTSTAT_TXLVL(x)               (((uint32_t)(((uint32_t)(x)) << USART_FIFOINTSTAT_TXLVL_SHIFT)) & USART_FIFOINTSTAT_TXLVL_MASK)

#define USART_FIFOINTSTAT_RXLVL_MASK             (0x8U)
#define USART_FIFOINTSTAT_RXLVL_SHIFT            (3U)
/*! RXLVL - Receive FIFO level interrupt. */
#define USART_FIFOINTSTAT_RXLVL(x)               (((uint32_t)(((uint32_t)(x)) << USART_FIFOINTSTAT_RXLVL_SHIFT)) & USART_FIFOINTSTAT_RXLVL_MASK)

#define USART_FIFOINTSTAT_PERINT_MASK            (0x10U)
#define USART_FIFOINTSTAT_PERINT_SHIFT           (4U)
/*! PERINT - Peripheral interrupt. */
#define USART_FIFOINTSTAT_PERINT(x)              (((uint32_t)(((uint32_t)(x)) << USART_FIFOINTSTAT_PERINT_SHIFT)) & USART_FIFOINTSTAT_PERINT_MASK)
/*! @} */

/*! @name FIFOWR - FIFO write data. */
/*! @{ */

#define USART_FIFOWR_TXDATA_MASK                 (0x1FFU)
#define USART_FIFOWR_TXDATA_SHIFT                (0U)
/*! TXDATA - Transmit data to the FIFO. */
#define USART_FIFOWR_TXDATA(x)                   (((uint32_t)(((uint32_t)(x)) << USART_FIFOWR_TXDATA_SHIFT)) & USART_FIFOWR_TXDATA_MASK)
/*! @} */

/*! @name FIFORD - FIFO read data. */
/*! @{ */

#define USART_FIFORD_RXDATA_MASK                 (0x1FFU)
#define USART_FIFORD_RXDATA_SHIFT                (0U)
/*! RXDATA - Received data from the FIFO. The number of bits used depends on the DATALEN and PARITYSEL settings. */
#define USART_FIFORD_RXDATA(x)                   (((uint32_t)(((uint32_t)(x)) << USART_FIFORD_RXDATA_SHIFT)) & USART_FIFORD_RXDATA_MASK)

#define USART_FIFORD_FRAMERR_MASK                (0x2000U)
#define USART_FIFORD_FRAMERR_SHIFT               (13U)
/*! FRAMERR - Framing Error status flag. This bit reflects the status for the data it is read along
 *    with from the FIFO, and indicates that the character was received with a missing stop bit at
 *    the expected location. This could be an indication of a baud rate or configuration mismatch
 *    with the transmitting source.
 */
#define USART_FIFORD_FRAMERR(x)                  (((uint32_t)(((uint32_t)(x)) << USART_FIFORD_FRAMERR_SHIFT)) & USART_FIFORD_FRAMERR_MASK)

#define USART_FIFORD_PARITYERR_MASK              (0x4000U)
#define USART_FIFORD_PARITYERR_SHIFT             (14U)
/*! PARITYERR - Parity Error status flag. This bit reflects the status for the data it is read along
 *    with from the FIFO. This bit will be set when a parity error is detected in a received
 *    character.
 */
#define USART_FIFORD_PARITYERR(x)                (((uint32_t)(((uint32_t)(x)) << USART_FIFORD_PARITYERR_SHIFT)) & USART_FIFORD_PARITYERR_MASK)

#define USART_FIFORD_RXNOISE_MASK                (0x8000U)
#define USART_FIFORD_RXNOISE_SHIFT               (15U)
/*! RXNOISE - Received Noise flag. See description of the RxNoiseInt bit in Table 354. */
#define USART_FIFORD_RXNOISE(x)                  (((uint32_t)(((uint32_t)(x)) << USART_FIFORD_RXNOISE_SHIFT)) & USART_FIFORD_RXNOISE_MASK)
/*! @} */

/*! @name FIFORDNOPOP - FIFO data read with no FIFO pop. */
/*! @{ */

#define USART_FIFORDNOPOP_RXDATA_MASK            (0x1FFU)
#define USART_FIFORDNOPOP_RXDATA_SHIFT           (0U)
/*! RXDATA - Received data from the FIFO. The number of bits used depends on the DATALEN and PARITYSEL settings. */
#define USART_FIFORDNOPOP_RXDATA(x)              (((uint32_t)(((uint32_t)(x)) << USART_FIFORDNOPOP_RXDATA_SHIFT)) & USART_FIFORDNOPOP_RXDATA_MASK)

#define USART_FIFORDNOPOP_FRAMERR_MASK           (0x2000U)
#define USART_FIFORDNOPOP_FRAMERR_SHIFT          (13U)
/*! FRAMERR - Framing Error status flag. This bit reflects the status for the data it is read along
 *    with from the FIFO, and indicates that the character was received with a missing stop bit at
 *    the expected location. This could be an indication of a baud rate or configuration mismatch
 *    with the transmitting source.
 */
#define USART_FIFORDNOPOP_FRAMERR(x)             (((uint32_t)(((uint32_t)(x)) << USART_FIFORDNOPOP_FRAMERR_SHIFT)) & USART_FIFORDNOPOP_FRAMERR_MASK)

#define USART_FIFORDNOPOP_PARITYERR_MASK         (0x4000U)
#define USART_FIFORDNOPOP_PARITYERR_SHIFT        (14U)
/*! PARITYERR - Parity Error status flag. This bit reflects the status for the data it is read along
 *    with from the FIFO. This bit will be set when a parity error is detected in a received
 *    character.
 */
#define USART_FIFORDNOPOP_PARITYERR(x)           (((uint32_t)(((uint32_t)(x)) << USART_FIFORDNOPOP_PARITYERR_SHIFT)) & USART_FIFORDNOPOP_PARITYERR_MASK)

#define USART_FIFORDNOPOP_RXNOISE_MASK           (0x8000U)
#define USART_FIFORDNOPOP_RXNOISE_SHIFT          (15U)
/*! RXNOISE - Received Noise flag. See description of the RxNoiseInt bit in Table 354. */
#define USART_FIFORDNOPOP_RXNOISE(x)             (((uint32_t)(((uint32_t)(x)) << USART_FIFORDNOPOP_RXNOISE_SHIFT)) & USART_FIFORDNOPOP_RXNOISE_MASK)
/*! @} */

/*! @name FIFOSIZE - FIFO size register */
/*! @{ */

#define USART_FIFOSIZE_FIFOSIZE_MASK             (0x1FU)
#define USART_FIFOSIZE_FIFOSIZE_SHIFT            (0U)
/*! FIFOSIZE - Provides the size of the FIFO for software. The size of the SPI FIFO is 8 entries. */
#define USART_FIFOSIZE_FIFOSIZE(x)               (((uint32_t)(((uint32_t)(x)) << USART_FIFOSIZE_FIFOSIZE_SHIFT)) & USART_FIFOSIZE_FIFOSIZE_MASK)
/*! @} */

/*! @name ID - Peripheral identification register. */
/*! @{ */

#define USART_ID_APERTURE_MASK                   (0xFFU)
#define USART_ID_APERTURE_SHIFT                  (0U)
/*! APERTURE - Aperture: encoded as (aperture size/4K) -1, so 0x00 means a 4K aperture. */
#define USART_ID_APERTURE(x)                     (((uint32_t)(((uint32_t)(x)) << USART_ID_APERTURE_SHIFT)) & USART_ID_APERTURE_MASK)

#define USART_ID_MINOR_REV_MASK                  (0xF00U)
#define USART_ID_MINOR_REV_SHIFT                 (8U)
/*! MINOR_REV - Minor revision of module implementation. */
#define USART_ID_MINOR_REV(x)                    (((uint32_t)(((uint32_t)(x)) << USART_ID_MINOR_REV_SHIFT)) & USART_ID_MINOR_REV_MASK)

#define USART_ID_MAJOR_REV_MASK                  (0xF000U)
#define USART_ID_MAJOR_REV_SHIFT                 (12U)
/*! MAJOR_REV - Major revision of module implementation. */
#define USART_ID_MAJOR_REV(x)                    (((uint32_t)(((uint32_t)(x)) << USART_ID_MAJOR_REV_SHIFT)) & USART_ID_MAJOR_REV_MASK)

#define USART_ID_ID_MASK                         (0xFFFF0000U)
#define USART_ID_ID_SHIFT                        (16U)
/*! ID - Module identifier for the selected function. */
#define USART_ID_ID(x)                           (((uint32_t)(((uint32_t)(x)) << USART_ID_ID_SHIFT)) & USART_ID_ID_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group USART_Register_Masks */


/*!
 * @}
 */ /* end of group USART_Peripheral_Access_Layer */


/*
** End of section using anonymous unions
*/

#if defined(__ARMCC_VERSION)
  #if (__ARMCC_VERSION >= 6010050)
    #pragma clang diagnostic pop
  #else
    #pragma pop
  #endif
#elif defined(__GNUC__)
  /* leave anonymous unions enabled */
#elif defined(__IAR_SYSTEMS_ICC__)
  #pragma language=default
#else
  #error Not supported compiler type
#endif

/*!
 * @}
 */ /* end of group Peripheral_access_layer */


#endif  /* USART_H_ */

