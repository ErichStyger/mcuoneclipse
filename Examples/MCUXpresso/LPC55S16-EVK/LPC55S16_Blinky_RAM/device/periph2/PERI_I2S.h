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
**         CMSIS Peripheral Access Layer for I2S
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
 * @file I2S.h
 * @version 1.1
 * @date 2019-12-03
 * @brief CMSIS Peripheral Access Layer for I2S
 *
 * CMSIS Peripheral Access Layer for I2S
 */

#if !defined(I2S_H_)
#define I2S_H_                                   /**< Symbol preventing repeated inclusion */

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
   -- I2S Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup I2S_Peripheral_Access_Layer I2S Peripheral Access Layer
 * @{
 */

/** I2S - Size of Registers Arrays */
#define I2S_SECCHANNEL_COUNT                      3u

/** I2S - Register Layout Typedef */
typedef struct {
       uint8_t RESERVED_0[3072];
  __IO uint32_t CFG1;                              /**< Configuration register 1 for the primary channel pair., offset: 0xC00 */
  __IO uint32_t CFG2;                              /**< Configuration register 2 for the primary channel pair., offset: 0xC04 */
  __IO uint32_t STAT;                              /**< Status register for the primary channel pair., offset: 0xC08 */
       uint8_t RESERVED_1[16];
  __IO uint32_t DIV;                               /**< Clock divider, used by all channel pairs., offset: 0xC1C */
  struct {                                         /* offset: 0xC20, array step: 0x20 */
    __IO uint32_t PCFG1;                             /**< Configuration register 1 for channel pair, array offset: 0xC20, array step: 0x20 */
    __IO uint32_t PCFG2;                             /**< Configuration register 2 for channel pair, array offset: 0xC24, array step: 0x20 */
    __IO uint32_t PSTAT;                             /**< Status register for channel pair, array offset: 0xC28, array step: 0x20 */
         uint8_t RESERVED_0[20];
  } SECCHANNEL[I2S_SECCHANNEL_COUNT];
       uint8_t RESERVED_2[384];
  __IO uint32_t FIFOCFG;                           /**< FIFO configuration and enable register., offset: 0xE00 */
  __IO uint32_t FIFOSTAT;                          /**< FIFO status register., offset: 0xE04 */
  __IO uint32_t FIFOTRIG;                          /**< FIFO trigger settings for interrupt and DMA request., offset: 0xE08 */
       uint8_t RESERVED_3[4];
  __IO uint32_t FIFOINTENSET;                      /**< FIFO interrupt enable set (enable) and read register., offset: 0xE10 */
  __IO uint32_t FIFOINTENCLR;                      /**< FIFO interrupt enable clear (disable) and read register., offset: 0xE14 */
  __I  uint32_t FIFOINTSTAT;                       /**< FIFO interrupt status register., offset: 0xE18 */
       uint8_t RESERVED_4[4];
  __O  uint32_t FIFOWR;                            /**< FIFO write data., offset: 0xE20 */
  __O  uint32_t FIFOWR48H;                         /**< FIFO write data for upper data bits. May only be used if the I2S is configured for 2x 24-bit data and not using DMA., offset: 0xE24 */
       uint8_t RESERVED_5[8];
  __I  uint32_t FIFORD;                            /**< FIFO read data., offset: 0xE30 */
  __I  uint32_t FIFORD48H;                         /**< FIFO read data for upper data bits. May only be used if the I2S is configured for 2x 24-bit data and not using DMA., offset: 0xE34 */
       uint8_t RESERVED_6[8];
  __I  uint32_t FIFORDNOPOP;                       /**< FIFO data read with no FIFO pop., offset: 0xE40 */
  __I  uint32_t FIFORD48HNOPOP;                    /**< FIFO data read for upper data bits with no FIFO pop. May only be used if the I2S is configured for 2x 24-bit data and not using DMA., offset: 0xE44 */
  __I  uint32_t FIFOSIZE;                          /**< FIFO size register, offset: 0xE48 */
       uint8_t RESERVED_7[432];
  __I  uint32_t ID;                                /**< I2S Module identification, offset: 0xFFC */
} I2S_Type;

/* ----------------------------------------------------------------------------
   -- I2S Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup I2S_Register_Masks I2S Register Masks
 * @{
 */

/*! @name CFG1 - Configuration register 1 for the primary channel pair. */
/*! @{ */

#define I2S_CFG1_MAINENABLE_MASK                 (0x1U)
#define I2S_CFG1_MAINENABLE_SHIFT                (0U)
/*! MAINENABLE - Main enable for I 2S function in this Flexcomm
 *  0b0..All I 2S channel pairs in this Flexcomm are disabled and the internal state machines, counters, and flags
 *       are reset. No other channel pairs can be enabled.
 *  0b1..This I 2S channel pair is enabled. Other channel pairs in this Flexcomm may be enabled in their individual PAIRENABLE bits.
 */
#define I2S_CFG1_MAINENABLE(x)                   (((uint32_t)(((uint32_t)(x)) << I2S_CFG1_MAINENABLE_SHIFT)) & I2S_CFG1_MAINENABLE_MASK)

#define I2S_CFG1_DATAPAUSE_MASK                  (0x2U)
#define I2S_CFG1_DATAPAUSE_SHIFT                 (1U)
/*! DATAPAUSE - Data flow Pause. Allows pausing data flow between the I2S serializer/deserializer
 *    and the FIFO. This could be done in order to change streams, or while restarting after a data
 *    underflow or overflow. When paused, FIFO operations can be done without corrupting data that is
 *    in the process of being sent or received. Once a data pause has been requested, the interface
 *    may need to complete sending data that was in progress before interrupting the flow of data.
 *    Software must check that the pause is actually in effect before taking action. This is done by
 *    monitoring the DATAPAUSED flag in the STAT register. When DATAPAUSE is cleared, data transfer
 *    will resume at the beginning of the next frame.
 *  0b0..Normal operation, or resuming normal operation at the next frame if the I2S has already been paused.
 *  0b1..A pause in the data flow is being requested. It is in effect when DATAPAUSED in STAT = 1.
 */
#define I2S_CFG1_DATAPAUSE(x)                    (((uint32_t)(((uint32_t)(x)) << I2S_CFG1_DATAPAUSE_SHIFT)) & I2S_CFG1_DATAPAUSE_MASK)

#define I2S_CFG1_PAIRCOUNT_MASK                  (0xCU)
#define I2S_CFG1_PAIRCOUNT_SHIFT                 (2U)
/*! PAIRCOUNT - Provides the number of I2S channel pairs in this Flexcomm This is a read-only field
 *    whose value may be different in other Flexcomms. 00 = there is 1 I2S channel pair in this
 *    Flexcomm. 01 = there are 2 I2S channel pairs in this Flexcomm. 10 = there are 3 I2S channel pairs
 *    in this Flexcomm. 11 = there are 4 I2S channel pairs in this Flexcomm.
 *  0b00..1 I2S channel pairs in this flexcomm
 *  0b01..2 I2S channel pairs in this flexcomm
 *  0b10..3 I2S channel pairs in this flexcomm
 *  0b11..4 I2S channel pairs in this flexcomm
 */
#define I2S_CFG1_PAIRCOUNT(x)                    (((uint32_t)(((uint32_t)(x)) << I2S_CFG1_PAIRCOUNT_SHIFT)) & I2S_CFG1_PAIRCOUNT_MASK)

#define I2S_CFG1_MSTSLVCFG_MASK                  (0x30U)
#define I2S_CFG1_MSTSLVCFG_SHIFT                 (4U)
/*! MSTSLVCFG - Master / slave configuration selection, determining how SCK and WS are used by all channel pairs in this Flexcomm.
 *  0b00..Normal slave mode, the default mode. SCK and WS are received from a master and used to transmit or receive data.
 *  0b01..WS synchronized master. WS is received from another master and used to synchronize the generation of
 *        SCK, when divided from the Flexcomm function clock.
 *  0b10..Master using an existing SCK. SCK is received and used directly to generate WS, as well as transmitting or receiving data.
 *  0b11..Normal master mode. SCK and WS are generated so they can be sent to one or more slave devices.
 */
#define I2S_CFG1_MSTSLVCFG(x)                    (((uint32_t)(((uint32_t)(x)) << I2S_CFG1_MSTSLVCFG_SHIFT)) & I2S_CFG1_MSTSLVCFG_MASK)

#define I2S_CFG1_MODE_MASK                       (0xC0U)
#define I2S_CFG1_MODE_SHIFT                      (6U)
/*! MODE - Selects the basic I2S operating mode. Other configurations modify this to obtain all
 *    supported cases. See Formats and modes for examples.
 *  0b00..I2S mode a.k.a. 'classic' mode. WS has a 50% duty cycle, with (for each enabled channel pair) one piece
 *        of left channel data occurring during the first phase, and one pieces of right channel data occurring
 *        during the second phase. In this mode, the data region begins one clock after the leading WS edge for the
 *        frame. For a 50% WS duty cycle, FRAMELEN must define an even number of I2S clocks for the frame. If
 *        FRAMELEN defines an odd number of clocks per frame, the extra clock will occur on the right.
 *  0b01..DSP mode where WS has a 50% duty cycle. See remark for mode 0.
 *  0b10..DSP mode where WS has a one clock long pulse at the beginning of each data frame.
 *  0b11..DSP mode where WS has a one data slot long pulse at the beginning of each data frame.
 */
#define I2S_CFG1_MODE(x)                         (((uint32_t)(((uint32_t)(x)) << I2S_CFG1_MODE_SHIFT)) & I2S_CFG1_MODE_MASK)

#define I2S_CFG1_RIGHTLOW_MASK                   (0x100U)
#define I2S_CFG1_RIGHTLOW_SHIFT                  (8U)
/*! RIGHTLOW - Right channel data is in the Low portion of FIFO data. Essentially, this swaps left
 *    and right channel data as it is transferred to or from the FIFO. This bit is not used if the
 *    data width is greater than 24 bits or if PDMDATA = 1. Note that if the ONECHANNEL field (bit 10
 *    of this register) = 1, the one channel to be used is the nominally the left channel. POSITION
 *    can still place that data in the frame where right channel data is normally located. if all
 *    enabled channel pairs have ONECHANNEL = 1, then RIGHTLOW = 1 is not allowed.
 *  0b0..The right channel is taken from the high part of the FIFO data. For example, when data is 16 bits, FIFO
 *       bits 31:16 are used for the right channel.
 *  0b1..The right channel is taken from the low part of the FIFO data. For example, when data is 16 bits, FIFO
 *       bits 15:0 are used for the right channel.
 */
#define I2S_CFG1_RIGHTLOW(x)                     (((uint32_t)(((uint32_t)(x)) << I2S_CFG1_RIGHTLOW_SHIFT)) & I2S_CFG1_RIGHTLOW_MASK)

#define I2S_CFG1_LEFTJUST_MASK                   (0x200U)
#define I2S_CFG1_LEFTJUST_SHIFT                  (9U)
/*! LEFTJUST - Left Justify data.
 *  0b0..Data is transferred between the FIFO and the I2S serializer/deserializer right justified, i.e. starting
 *       from bit 0 and continuing to the position defined by DATALEN. This would correspond to right justified data
 *       in the stream on the data bus.
 *  0b1..Data is transferred between the FIFO and the I2S serializer/deserializer left justified, i.e. starting
 *       from the MSB of the FIFO entry and continuing for the number of bits defined by DATALEN. This would
 *       correspond to left justified data in the stream on the data bus.
 */
#define I2S_CFG1_LEFTJUST(x)                     (((uint32_t)(((uint32_t)(x)) << I2S_CFG1_LEFTJUST_SHIFT)) & I2S_CFG1_LEFTJUST_MASK)

#define I2S_CFG1_ONECHANNEL_MASK                 (0x400U)
#define I2S_CFG1_ONECHANNEL_SHIFT                (10U)
/*! ONECHANNEL - Single channel mode. Applies to both transmit and receive. This configuration bit
 *    applies only to the first I2S channel pair. Other channel pairs may select this mode
 *    independently in their separate CFG1 registers.
 *  0b0..I2S data for this channel pair is treated as left and right channels.
 *  0b1..I2S data for this channel pair is treated as a single channel, functionally the left channel for this
 *       pair. In mode 0 only, the right side of the frame begins at POSITION = 0x100. This is because mode 0 makes a
 *       clear distinction between the left and right sides of the frame. When ONECHANNEL = 1, the single channel
 *       of data may be placed on the right by setting POSITION to 0x100 + the data position within the right side
 *       (e.g. 0x108 would place data starting at the 8th clock after the middle of the frame). In other modes, data
 *       for the single channel of data is placed at the clock defined by POSITION.
 */
#define I2S_CFG1_ONECHANNEL(x)                   (((uint32_t)(((uint32_t)(x)) << I2S_CFG1_ONECHANNEL_SHIFT)) & I2S_CFG1_ONECHANNEL_MASK)

#define I2S_CFG1_SCK_POL_MASK                    (0x1000U)
#define I2S_CFG1_SCK_POL_SHIFT                   (12U)
/*! SCK_POL - SCK polarity.
 *  0b0..Data is launched on SCK falling edges and sampled on SCK rising edges (standard for I2S).
 *  0b1..Data is launched on SCK rising edges and sampled on SCK falling edges.
 */
#define I2S_CFG1_SCK_POL(x)                      (((uint32_t)(((uint32_t)(x)) << I2S_CFG1_SCK_POL_SHIFT)) & I2S_CFG1_SCK_POL_MASK)

#define I2S_CFG1_WS_POL_MASK                     (0x2000U)
#define I2S_CFG1_WS_POL_SHIFT                    (13U)
/*! WS_POL - WS polarity.
 *  0b0..Data frames begin at a falling edge of WS (standard for classic I2S).
 *  0b1..WS is inverted, resulting in a data frame beginning at a rising edge of WS (standard for most 'non-classic' variations of I2S).
 */
#define I2S_CFG1_WS_POL(x)                       (((uint32_t)(((uint32_t)(x)) << I2S_CFG1_WS_POL_SHIFT)) & I2S_CFG1_WS_POL_MASK)

#define I2S_CFG1_DATALEN_MASK                    (0x1F0000U)
#define I2S_CFG1_DATALEN_SHIFT                   (16U)
/*! DATALEN - Data Length, minus 1 encoded, defines the number of data bits to be transmitted or
 *    received for all I2S channel pairs in this Flexcomm. Note that data is only driven to or received
 *    from SDA for the number of bits defined by DATALEN. DATALEN is also used in these ways by the
 *    I2S: Determines the size of data transfers between the FIFO and the I2S
 *    serializer/deserializer. See FIFO buffer configurations and usage In mode 1, 2, and 3, determines the location of
 *    right data following left data in the frame. In mode 3 (where WS has a one data slot long pulse
 *    at the beginning of each data frame) determines the duration of the WS pulse. Values: 0x00 to
 *    0x02 = not supported 0x03 = data is 4 bits in length 0x04 = data is 5 bits in length 0x1F =
 *    data is 32 bits in length
 */
#define I2S_CFG1_DATALEN(x)                      (((uint32_t)(((uint32_t)(x)) << I2S_CFG1_DATALEN_SHIFT)) & I2S_CFG1_DATALEN_MASK)
/*! @} */

/*! @name CFG2 - Configuration register 2 for the primary channel pair. */
/*! @{ */

#define I2S_CFG2_FRAMELEN_MASK                   (0x7FFU)
#define I2S_CFG2_FRAMELEN_SHIFT                  (0U)
/*! FRAMELEN - Frame Length, minus 1 encoded, defines the number of clocks and data bits in the
 *    frames that this channel pair participates in. See Frame format. 0x000 to 0x002 = not supported
 *    0x003 = frame is 4 bits in total length 0x004 = frame is 5 bits in total length 0x7FF = frame is
 *    2048 bits in total length if FRAMELEN is an defines an odd length frame (e.g. 33 clocks) in
 *    mode 0 or 1, the extra clock appears in the right half. When MODE = 3, FRAMELEN must be larger
 *    than DATALEN in order for the WS pulse to be generated correctly.
 */
#define I2S_CFG2_FRAMELEN(x)                     (((uint32_t)(((uint32_t)(x)) << I2S_CFG2_FRAMELEN_SHIFT)) & I2S_CFG2_FRAMELEN_MASK)

#define I2S_CFG2_POSITION_MASK                   (0x1FF0000U)
#define I2S_CFG2_POSITION_SHIFT                  (16U)
/*! POSITION - Data Position. Defines the location within the frame of the data for this channel
 *    pair. POSITION + DATALEN must be less than FRAMELEN. See Frame format. When MODE = 0, POSITION
 *    defines the location of data in both the left phase and right phase, starting one clock after
 *    the WS edge. In other modes, POSITION defines the location of data within the entire frame.
 *    ONECHANNEL = 1 while MODE = 0 is a special case, see the description of ONECHANNEL. The
 *    combination of DATALEN and the POSITION fields of all channel pairs must be made such that the channels
 *    do not overlap within the frame. 0x000 = data begins at bit position 0 (the first bit
 *    position) within the frame or WS phase. 0x001 = data begins at bit position 1 within the frame or WS
 *    phase. 0x002 = data begins at bit position 2 within the frame or WS phase.
 */
#define I2S_CFG2_POSITION(x)                     (((uint32_t)(((uint32_t)(x)) << I2S_CFG2_POSITION_SHIFT)) & I2S_CFG2_POSITION_MASK)
/*! @} */

/*! @name STAT - Status register for the primary channel pair. */
/*! @{ */

#define I2S_STAT_BUSY_MASK                       (0x1U)
#define I2S_STAT_BUSY_SHIFT                      (0U)
/*! BUSY - Busy status for the primary channel pair. Other BUSY flags may be found in the STAT register for each channel pair.
 *  0b0..The transmitter/receiver for channel pair is currently idle.
 *  0b1..The transmitter/receiver for channel pair is currently processing data.
 */
#define I2S_STAT_BUSY(x)                         (((uint32_t)(((uint32_t)(x)) << I2S_STAT_BUSY_SHIFT)) & I2S_STAT_BUSY_MASK)

#define I2S_STAT_SLVFRMERR_MASK                  (0x2U)
#define I2S_STAT_SLVFRMERR_SHIFT                 (1U)
/*! SLVFRMERR - Slave Frame Error flag. This applies when at least one channel pair is operating as
 *    a slave. An error indicates that the incoming WS signal did not transition as expected due to
 *    a mismatch between FRAMELEN and the actual incoming I2S stream.
 *  0b0..No error has been recorded.
 *  0b1..An error has been recorded for some channel pair that is operating in slave mode. ERROR is cleared by writing a 1 to this bit position.
 */
#define I2S_STAT_SLVFRMERR(x)                    (((uint32_t)(((uint32_t)(x)) << I2S_STAT_SLVFRMERR_SHIFT)) & I2S_STAT_SLVFRMERR_MASK)

#define I2S_STAT_LR_MASK                         (0x4U)
#define I2S_STAT_LR_SHIFT                        (2U)
/*! LR - Left/Right indication. This flag is considered to be a debugging aid and is not expected to
 *    be used by an I2S driver. Valid when one channel pair is busy. Indicates left or right data
 *    being processed for the currently busy channel pair.
 *  0b0..Left channel.
 *  0b1..Right channel.
 */
#define I2S_STAT_LR(x)                           (((uint32_t)(((uint32_t)(x)) << I2S_STAT_LR_SHIFT)) & I2S_STAT_LR_MASK)

#define I2S_STAT_DATAPAUSED_MASK                 (0x8U)
#define I2S_STAT_DATAPAUSED_SHIFT                (3U)
/*! DATAPAUSED - Data Paused status flag. Applies to all I2S channels
 *  0b0..Data is not currently paused. A data pause may have been requested but is not yet in force, waiting for
 *       an allowed pause point. Refer to the description of the DATAPAUSE control bit in the CFG1 register.
 *  0b1..A data pause has been requested and is now in force.
 */
#define I2S_STAT_DATAPAUSED(x)                   (((uint32_t)(((uint32_t)(x)) << I2S_STAT_DATAPAUSED_SHIFT)) & I2S_STAT_DATAPAUSED_MASK)
/*! @} */

/*! @name DIV - Clock divider, used by all channel pairs. */
/*! @{ */

#define I2S_DIV_DIV_MASK                         (0xFFFU)
#define I2S_DIV_DIV_SHIFT                        (0U)
/*! DIV - This field controls how this I2S block uses the Flexcomm function clock. 0x000 = The
 *    Flexcomm function clock is used directly. 0x001 = The Flexcomm function clock is divided by 2.
 *    0x002 = The Flexcomm function clock is divided by 3. 0xFFF = The Flexcomm function clock is
 *    divided by 4,096.
 */
#define I2S_DIV_DIV(x)                           (((uint32_t)(((uint32_t)(x)) << I2S_DIV_DIV_SHIFT)) & I2S_DIV_DIV_MASK)
/*! @} */

/*! @name SECCHANNEL_PCFG1 - Configuration register 1 for channel pair */
/*! @{ */

#define I2S_SECCHANNEL_PCFG1_PAIRENABLE_MASK     (0x1U)
#define I2S_SECCHANNEL_PCFG1_PAIRENABLE_SHIFT    (0U)
/*! PAIRENABLE - Enable for this channel pair.
 *  0b0..This I2S channel pair is disabled.
 *  0b1..This I2S channel pair is enabled.
 */
#define I2S_SECCHANNEL_PCFG1_PAIRENABLE(x)       (((uint32_t)(((uint32_t)(x)) << I2S_SECCHANNEL_PCFG1_PAIRENABLE_SHIFT)) & I2S_SECCHANNEL_PCFG1_PAIRENABLE_MASK)

#define I2S_SECCHANNEL_PCFG1_ONECHANNEL_MASK     (0x400U)
#define I2S_SECCHANNEL_PCFG1_ONECHANNEL_SHIFT    (10U)
/*! ONECHANNEL - Single channel mode.
 *  0b0..I2S data for this channel pair is treated as left and right channels.
 *  0b1..I2S data for this channel pair is treated as a single channel, functionally the left channel for this pair.
 */
#define I2S_SECCHANNEL_PCFG1_ONECHANNEL(x)       (((uint32_t)(((uint32_t)(x)) << I2S_SECCHANNEL_PCFG1_ONECHANNEL_SHIFT)) & I2S_SECCHANNEL_PCFG1_ONECHANNEL_MASK)
/*! @} */

/* The count of I2S_SECCHANNEL_PCFG1 */
#define I2S_SECCHANNEL_PCFG1_COUNT               (3U)

/*! @name SECCHANNEL_PCFG2 - Configuration register 2 for channel pair */
/*! @{ */

#define I2S_SECCHANNEL_PCFG2_POSITION_MASK       (0x1FF0000U)
#define I2S_SECCHANNEL_PCFG2_POSITION_SHIFT      (16U)
/*! POSITION - Data Position. */
#define I2S_SECCHANNEL_PCFG2_POSITION(x)         (((uint32_t)(((uint32_t)(x)) << I2S_SECCHANNEL_PCFG2_POSITION_SHIFT)) & I2S_SECCHANNEL_PCFG2_POSITION_MASK)
/*! @} */

/* The count of I2S_SECCHANNEL_PCFG2 */
#define I2S_SECCHANNEL_PCFG2_COUNT               (3U)

/*! @name SECCHANNEL_PSTAT - Status register for channel pair */
/*! @{ */

#define I2S_SECCHANNEL_PSTAT_BUSY_MASK           (0x1U)
#define I2S_SECCHANNEL_PSTAT_BUSY_SHIFT          (0U)
/*! BUSY - Busy status for this channel pair.
 *  0b0..The transmitter/receiver for this channel pair is currently idle.
 *  0b1..The transmitter/receiver for this channel pair is currently processing data.
 */
#define I2S_SECCHANNEL_PSTAT_BUSY(x)             (((uint32_t)(((uint32_t)(x)) << I2S_SECCHANNEL_PSTAT_BUSY_SHIFT)) & I2S_SECCHANNEL_PSTAT_BUSY_MASK)

#define I2S_SECCHANNEL_PSTAT_SLVFRMERR_MASK      (0x2U)
#define I2S_SECCHANNEL_PSTAT_SLVFRMERR_SHIFT     (1U)
/*! SLVFRMERR - Save Frame Error flag. */
#define I2S_SECCHANNEL_PSTAT_SLVFRMERR(x)        (((uint32_t)(((uint32_t)(x)) << I2S_SECCHANNEL_PSTAT_SLVFRMERR_SHIFT)) & I2S_SECCHANNEL_PSTAT_SLVFRMERR_MASK)

#define I2S_SECCHANNEL_PSTAT_LR_MASK             (0x4U)
#define I2S_SECCHANNEL_PSTAT_LR_SHIFT            (2U)
/*! LR - Left/Right indication. */
#define I2S_SECCHANNEL_PSTAT_LR(x)               (((uint32_t)(((uint32_t)(x)) << I2S_SECCHANNEL_PSTAT_LR_SHIFT)) & I2S_SECCHANNEL_PSTAT_LR_MASK)

#define I2S_SECCHANNEL_PSTAT_DATAPAUSED_MASK     (0x8U)
#define I2S_SECCHANNEL_PSTAT_DATAPAUSED_SHIFT    (3U)
/*! DATAPAUSED - Data Paused status flag.
 *  0b0..Data is not currently paused.
 *  0b1..A data pause has been requested and is now in force.
 */
#define I2S_SECCHANNEL_PSTAT_DATAPAUSED(x)       (((uint32_t)(((uint32_t)(x)) << I2S_SECCHANNEL_PSTAT_DATAPAUSED_SHIFT)) & I2S_SECCHANNEL_PSTAT_DATAPAUSED_MASK)
/*! @} */

/* The count of I2S_SECCHANNEL_PSTAT */
#define I2S_SECCHANNEL_PSTAT_COUNT               (3U)

/*! @name FIFOCFG - FIFO configuration and enable register. */
/*! @{ */

#define I2S_FIFOCFG_ENABLETX_MASK                (0x1U)
#define I2S_FIFOCFG_ENABLETX_SHIFT               (0U)
/*! ENABLETX - Enable the transmit FIFO.
 *  0b0..The transmit FIFO is not enabled.
 *  0b1..The transmit FIFO is enabled.
 */
#define I2S_FIFOCFG_ENABLETX(x)                  (((uint32_t)(((uint32_t)(x)) << I2S_FIFOCFG_ENABLETX_SHIFT)) & I2S_FIFOCFG_ENABLETX_MASK)

#define I2S_FIFOCFG_ENABLERX_MASK                (0x2U)
#define I2S_FIFOCFG_ENABLERX_SHIFT               (1U)
/*! ENABLERX - Enable the receive FIFO.
 *  0b0..The receive FIFO is not enabled.
 *  0b1..The receive FIFO is enabled.
 */
#define I2S_FIFOCFG_ENABLERX(x)                  (((uint32_t)(((uint32_t)(x)) << I2S_FIFOCFG_ENABLERX_SHIFT)) & I2S_FIFOCFG_ENABLERX_MASK)

#define I2S_FIFOCFG_TXI2SE0_MASK                 (0x4U)
#define I2S_FIFOCFG_TXI2SE0_SHIFT                (2U)
/*! TXI2SE0 - Transmit I2S empty 0. Determines the value sent by the I2S in transmit mode if the TX
 *    FIFO becomes empty. This value is sent repeatedly until the I2S is paused, the error is
 *    cleared, new data is provided, and the I2S is un-paused.
 *  0b0..If the TX FIFO becomes empty, the last value is sent. This setting may be used when the data length is 24
 *       bits or less, or when MONO = 1 for this channel pair.
 *  0b1..If the TX FIFO becomes empty, 0 is sent. Use if the data length is greater than 24 bits or if zero fill is preferred.
 */
#define I2S_FIFOCFG_TXI2SE0(x)                   (((uint32_t)(((uint32_t)(x)) << I2S_FIFOCFG_TXI2SE0_SHIFT)) & I2S_FIFOCFG_TXI2SE0_MASK)

#define I2S_FIFOCFG_PACK48_MASK                  (0x8U)
#define I2S_FIFOCFG_PACK48_SHIFT                 (3U)
/*! PACK48 - Packing format for 48-bit data. This relates to how data is entered into or taken from the FIFO by software or DMA.
 *  0b0..48-bit I2S FIFO entries are handled as all 24-bit values.
 *  0b1..48-bit I2S FIFO entries are handled as alternating 32-bit and 16-bit values.
 */
#define I2S_FIFOCFG_PACK48(x)                    (((uint32_t)(((uint32_t)(x)) << I2S_FIFOCFG_PACK48_SHIFT)) & I2S_FIFOCFG_PACK48_MASK)

#define I2S_FIFOCFG_SIZE_MASK                    (0x30U)
#define I2S_FIFOCFG_SIZE_SHIFT                   (4U)
/*! SIZE - FIFO size configuration. This is a read-only field. 0x0 = FIFO is configured as 16
 *    entries of 8 bits. 0x1, 0x2, 0x3 = not applicable to USART.
 */
#define I2S_FIFOCFG_SIZE(x)                      (((uint32_t)(((uint32_t)(x)) << I2S_FIFOCFG_SIZE_SHIFT)) & I2S_FIFOCFG_SIZE_MASK)

#define I2S_FIFOCFG_DMATX_MASK                   (0x1000U)
#define I2S_FIFOCFG_DMATX_SHIFT                  (12U)
/*! DMATX - DMA configuration for transmit.
 *  0b0..DMA is not used for the transmit function.
 *  0b1..Trigger DMA for the transmit function if the FIFO is not full. Generally, data interrupts would be disabled if DMA is enabled.
 */
#define I2S_FIFOCFG_DMATX(x)                     (((uint32_t)(((uint32_t)(x)) << I2S_FIFOCFG_DMATX_SHIFT)) & I2S_FIFOCFG_DMATX_MASK)

#define I2S_FIFOCFG_DMARX_MASK                   (0x2000U)
#define I2S_FIFOCFG_DMARX_SHIFT                  (13U)
/*! DMARX - DMA configuration for receive.
 *  0b0..DMA is not used for the receive function.
 *  0b1..Trigger DMA for the receive function if the FIFO is not empty. Generally, data interrupts would be disabled if DMA is enabled.
 */
#define I2S_FIFOCFG_DMARX(x)                     (((uint32_t)(((uint32_t)(x)) << I2S_FIFOCFG_DMARX_SHIFT)) & I2S_FIFOCFG_DMARX_MASK)

#define I2S_FIFOCFG_WAKETX_MASK                  (0x4000U)
#define I2S_FIFOCFG_WAKETX_SHIFT                 (14U)
/*! WAKETX - Wake-up for transmit FIFO level. This allows the device to be woken from reduced power
 *    modes (up to power-down, as long as the peripheral function works in that power mode) without
 *    enabling the TXLVL interrupt. Only DMA wakes up, processes data, and goes back to sleep. The
 *    CPU will remain stopped until woken by another cause, such as DMA completion. See Hardware
 *    Wake-up control register.
 *  0b0..Only enabled interrupts will wake up the device form reduced power modes.
 *  0b1..A device wake-up for DMA will occur if the transmit FIFO level reaches the value specified by TXLVL in
 *       FIFOTRIG, even when the TXLVL interrupt is not enabled.
 */
#define I2S_FIFOCFG_WAKETX(x)                    (((uint32_t)(((uint32_t)(x)) << I2S_FIFOCFG_WAKETX_SHIFT)) & I2S_FIFOCFG_WAKETX_MASK)

#define I2S_FIFOCFG_WAKERX_MASK                  (0x8000U)
#define I2S_FIFOCFG_WAKERX_SHIFT                 (15U)
/*! WAKERX - Wake-up for receive FIFO level. This allows the device to be woken from reduced power
 *    modes (up to power-down, as long as the peripheral function works in that power mode) without
 *    enabling the TXLVL interrupt. Only DMA wakes up, processes data, and goes back to sleep. The
 *    CPU will remain stopped until woken by another cause, such as DMA completion. See Hardware
 *    Wake-up control register.
 *  0b0..Only enabled interrupts will wake up the device form reduced power modes.
 *  0b1..A device wake-up for DMA will occur if the receive FIFO level reaches the value specified by RXLVL in
 *       FIFOTRIG, even when the RXLVL interrupt is not enabled.
 */
#define I2S_FIFOCFG_WAKERX(x)                    (((uint32_t)(((uint32_t)(x)) << I2S_FIFOCFG_WAKERX_SHIFT)) & I2S_FIFOCFG_WAKERX_MASK)

#define I2S_FIFOCFG_EMPTYTX_MASK                 (0x10000U)
#define I2S_FIFOCFG_EMPTYTX_SHIFT                (16U)
/*! EMPTYTX - Empty command for the transmit FIFO. When a 1 is written to this bit, the TX FIFO is emptied. */
#define I2S_FIFOCFG_EMPTYTX(x)                   (((uint32_t)(((uint32_t)(x)) << I2S_FIFOCFG_EMPTYTX_SHIFT)) & I2S_FIFOCFG_EMPTYTX_MASK)

#define I2S_FIFOCFG_EMPTYRX_MASK                 (0x20000U)
#define I2S_FIFOCFG_EMPTYRX_SHIFT                (17U)
/*! EMPTYRX - Empty command for the receive FIFO. When a 1 is written to this bit, the RX FIFO is emptied. */
#define I2S_FIFOCFG_EMPTYRX(x)                   (((uint32_t)(((uint32_t)(x)) << I2S_FIFOCFG_EMPTYRX_SHIFT)) & I2S_FIFOCFG_EMPTYRX_MASK)
/*! @} */

/*! @name FIFOSTAT - FIFO status register. */
/*! @{ */

#define I2S_FIFOSTAT_TXERR_MASK                  (0x1U)
#define I2S_FIFOSTAT_TXERR_SHIFT                 (0U)
/*! TXERR - TX FIFO error. Will be set if a transmit FIFO error occurs. This could be an overflow
 *    caused by pushing data into a full FIFO, or by an underflow if the FIFO is empty when data is
 *    needed. Cleared by writing a 1 to this bit.
 */
#define I2S_FIFOSTAT_TXERR(x)                    (((uint32_t)(((uint32_t)(x)) << I2S_FIFOSTAT_TXERR_SHIFT)) & I2S_FIFOSTAT_TXERR_MASK)

#define I2S_FIFOSTAT_RXERR_MASK                  (0x2U)
#define I2S_FIFOSTAT_RXERR_SHIFT                 (1U)
/*! RXERR - RX FIFO error. Will be set if a receive FIFO overflow occurs, caused by software or DMA
 *    not emptying the FIFO fast enough. Cleared by writing a 1 to this bit.
 */
#define I2S_FIFOSTAT_RXERR(x)                    (((uint32_t)(((uint32_t)(x)) << I2S_FIFOSTAT_RXERR_SHIFT)) & I2S_FIFOSTAT_RXERR_MASK)

#define I2S_FIFOSTAT_PERINT_MASK                 (0x8U)
#define I2S_FIFOSTAT_PERINT_SHIFT                (3U)
/*! PERINT - Peripheral interrupt. When 1, this indicates that the peripheral function has asserted
 *    an interrupt. The details can be found by reading the peripheral's STAT register.
 */
#define I2S_FIFOSTAT_PERINT(x)                   (((uint32_t)(((uint32_t)(x)) << I2S_FIFOSTAT_PERINT_SHIFT)) & I2S_FIFOSTAT_PERINT_MASK)

#define I2S_FIFOSTAT_TXEMPTY_MASK                (0x10U)
#define I2S_FIFOSTAT_TXEMPTY_SHIFT               (4U)
/*! TXEMPTY - Transmit FIFO empty. When 1, the transmit FIFO is empty. The peripheral may still be processing the last piece of data. */
#define I2S_FIFOSTAT_TXEMPTY(x)                  (((uint32_t)(((uint32_t)(x)) << I2S_FIFOSTAT_TXEMPTY_SHIFT)) & I2S_FIFOSTAT_TXEMPTY_MASK)

#define I2S_FIFOSTAT_TXNOTFULL_MASK              (0x20U)
#define I2S_FIFOSTAT_TXNOTFULL_SHIFT             (5U)
/*! TXNOTFULL - Transmit FIFO not full. When 1, the transmit FIFO is not full, so more data can be
 *    written. When 0, the transmit FIFO is full and another write would cause it to overflow.
 */
#define I2S_FIFOSTAT_TXNOTFULL(x)                (((uint32_t)(((uint32_t)(x)) << I2S_FIFOSTAT_TXNOTFULL_SHIFT)) & I2S_FIFOSTAT_TXNOTFULL_MASK)

#define I2S_FIFOSTAT_RXNOTEMPTY_MASK             (0x40U)
#define I2S_FIFOSTAT_RXNOTEMPTY_SHIFT            (6U)
/*! RXNOTEMPTY - Receive FIFO not empty. When 1, the receive FIFO is not empty, so data can be read. When 0, the receive FIFO is empty. */
#define I2S_FIFOSTAT_RXNOTEMPTY(x)               (((uint32_t)(((uint32_t)(x)) << I2S_FIFOSTAT_RXNOTEMPTY_SHIFT)) & I2S_FIFOSTAT_RXNOTEMPTY_MASK)

#define I2S_FIFOSTAT_RXFULL_MASK                 (0x80U)
#define I2S_FIFOSTAT_RXFULL_SHIFT                (7U)
/*! RXFULL - Receive FIFO full. When 1, the receive FIFO is full. Data needs to be read out to
 *    prevent the peripheral from causing an overflow.
 */
#define I2S_FIFOSTAT_RXFULL(x)                   (((uint32_t)(((uint32_t)(x)) << I2S_FIFOSTAT_RXFULL_SHIFT)) & I2S_FIFOSTAT_RXFULL_MASK)

#define I2S_FIFOSTAT_TXLVL_MASK                  (0x1F00U)
#define I2S_FIFOSTAT_TXLVL_SHIFT                 (8U)
/*! TXLVL - Transmit FIFO current level. A 0 means the TX FIFO is currently empty, and the TXEMPTY
 *    and TXNOTFULL flags will be 1. Other values tell how much data is actually in the TX FIFO at
 *    the point where the read occurs. If the TX FIFO is full, the TXEMPTY and TXNOTFULL flags will be
 *    0.
 */
#define I2S_FIFOSTAT_TXLVL(x)                    (((uint32_t)(((uint32_t)(x)) << I2S_FIFOSTAT_TXLVL_SHIFT)) & I2S_FIFOSTAT_TXLVL_MASK)

#define I2S_FIFOSTAT_RXLVL_MASK                  (0x1F0000U)
#define I2S_FIFOSTAT_RXLVL_SHIFT                 (16U)
/*! RXLVL - Receive FIFO current level. A 0 means the RX FIFO is currently empty, and the RXFULL and
 *    RXNOTEMPTY flags will be 0. Other values tell how much data is actually in the RX FIFO at the
 *    point where the read occurs. If the RX FIFO is full, the RXFULL and RXNOTEMPTY flags will be
 *    1.
 */
#define I2S_FIFOSTAT_RXLVL(x)                    (((uint32_t)(((uint32_t)(x)) << I2S_FIFOSTAT_RXLVL_SHIFT)) & I2S_FIFOSTAT_RXLVL_MASK)
/*! @} */

/*! @name FIFOTRIG - FIFO trigger settings for interrupt and DMA request. */
/*! @{ */

#define I2S_FIFOTRIG_TXLVLENA_MASK               (0x1U)
#define I2S_FIFOTRIG_TXLVLENA_SHIFT              (0U)
/*! TXLVLENA - Transmit FIFO level trigger enable. This trigger will become an interrupt if enabled
 *    in FIFOINTENSET, or a DMA trigger if DMATX in FIFOCFG is set.
 *  0b0..Transmit FIFO level does not generate a FIFO level trigger.
 *  0b1..An trigger will be generated if the transmit FIFO level reaches the value specified by the TXLVL field in this register.
 */
#define I2S_FIFOTRIG_TXLVLENA(x)                 (((uint32_t)(((uint32_t)(x)) << I2S_FIFOTRIG_TXLVLENA_SHIFT)) & I2S_FIFOTRIG_TXLVLENA_MASK)

#define I2S_FIFOTRIG_RXLVLENA_MASK               (0x2U)
#define I2S_FIFOTRIG_RXLVLENA_SHIFT              (1U)
/*! RXLVLENA - Receive FIFO level trigger enable. This trigger will become an interrupt if enabled
 *    in FIFOINTENSET, or a DMA trigger if DMARX in FIFOCFG is set.
 *  0b0..Receive FIFO level does not generate a FIFO level trigger.
 *  0b1..An trigger will be generated if the receive FIFO level reaches the value specified by the RXLVL field in this register.
 */
#define I2S_FIFOTRIG_RXLVLENA(x)                 (((uint32_t)(((uint32_t)(x)) << I2S_FIFOTRIG_RXLVLENA_SHIFT)) & I2S_FIFOTRIG_RXLVLENA_MASK)

#define I2S_FIFOTRIG_TXLVL_MASK                  (0xF00U)
#define I2S_FIFOTRIG_TXLVL_SHIFT                 (8U)
/*! TXLVL - Transmit FIFO level trigger point. This field is used only when TXLVLENA = 1. If enabled
 *    to do so, the FIFO level can wake up the device just enough to perform DMA, then return to
 *    the reduced power mode. See Hardware Wake-up control register. 0 = trigger when the TX FIFO
 *    becomes empty. 1 = trigger when the TX FIFO level decreases to one entry. 15 = trigger when the TX
 *    FIFO level decreases to 15 entries (is no longer full).
 */
#define I2S_FIFOTRIG_TXLVL(x)                    (((uint32_t)(((uint32_t)(x)) << I2S_FIFOTRIG_TXLVL_SHIFT)) & I2S_FIFOTRIG_TXLVL_MASK)

#define I2S_FIFOTRIG_RXLVL_MASK                  (0xF0000U)
#define I2S_FIFOTRIG_RXLVL_SHIFT                 (16U)
/*! RXLVL - Receive FIFO level trigger point. The RX FIFO level is checked when a new piece of data
 *    is received. This field is used only when RXLVLENA = 1. If enabled to do so, the FIFO level
 *    can wake up the device just enough to perform DMA, then return to the reduced power mode. See
 *    Hardware Wake-up control register. 0 = trigger when the RX FIFO has received one entry (is no
 *    longer empty). 1 = trigger when the RX FIFO has received two entries. 15 = trigger when the RX
 *    FIFO has received 16 entries (has become full).
 */
#define I2S_FIFOTRIG_RXLVL(x)                    (((uint32_t)(((uint32_t)(x)) << I2S_FIFOTRIG_RXLVL_SHIFT)) & I2S_FIFOTRIG_RXLVL_MASK)
/*! @} */

/*! @name FIFOINTENSET - FIFO interrupt enable set (enable) and read register. */
/*! @{ */

#define I2S_FIFOINTENSET_TXERR_MASK              (0x1U)
#define I2S_FIFOINTENSET_TXERR_SHIFT             (0U)
/*! TXERR - Determines whether an interrupt occurs when a transmit error occurs, based on the TXERR flag in the FIFOSTAT register.
 *  0b0..No interrupt will be generated for a transmit error.
 *  0b1..An interrupt will be generated when a transmit error occurs.
 */
#define I2S_FIFOINTENSET_TXERR(x)                (((uint32_t)(((uint32_t)(x)) << I2S_FIFOINTENSET_TXERR_SHIFT)) & I2S_FIFOINTENSET_TXERR_MASK)

#define I2S_FIFOINTENSET_RXERR_MASK              (0x2U)
#define I2S_FIFOINTENSET_RXERR_SHIFT             (1U)
/*! RXERR - Determines whether an interrupt occurs when a receive error occurs, based on the RXERR flag in the FIFOSTAT register.
 *  0b0..No interrupt will be generated for a receive error.
 *  0b1..An interrupt will be generated when a receive error occurs.
 */
#define I2S_FIFOINTENSET_RXERR(x)                (((uint32_t)(((uint32_t)(x)) << I2S_FIFOINTENSET_RXERR_SHIFT)) & I2S_FIFOINTENSET_RXERR_MASK)

#define I2S_FIFOINTENSET_TXLVL_MASK              (0x4U)
#define I2S_FIFOINTENSET_TXLVL_SHIFT             (2U)
/*! TXLVL - Determines whether an interrupt occurs when a the transmit FIFO reaches the level
 *    specified by the TXLVL field in the FIFOTRIG register.
 *  0b0..No interrupt will be generated based on the TX FIFO level.
 *  0b1..If TXLVLENA in the FIFOTRIG register = 1, an interrupt will be generated when the TX FIFO level decreases
 *       to the level specified by TXLVL in the FIFOTRIG register.
 */
#define I2S_FIFOINTENSET_TXLVL(x)                (((uint32_t)(((uint32_t)(x)) << I2S_FIFOINTENSET_TXLVL_SHIFT)) & I2S_FIFOINTENSET_TXLVL_MASK)

#define I2S_FIFOINTENSET_RXLVL_MASK              (0x8U)
#define I2S_FIFOINTENSET_RXLVL_SHIFT             (3U)
/*! RXLVL - Determines whether an interrupt occurs when a the receive FIFO reaches the level
 *    specified by the TXLVL field in the FIFOTRIG register.
 *  0b0..No interrupt will be generated based on the RX FIFO level.
 *  0b1..If RXLVLENA in the FIFOTRIG register = 1, an interrupt will be generated when the when the RX FIFO level
 *       increases to the level specified by RXLVL in the FIFOTRIG register.
 */
#define I2S_FIFOINTENSET_RXLVL(x)                (((uint32_t)(((uint32_t)(x)) << I2S_FIFOINTENSET_RXLVL_SHIFT)) & I2S_FIFOINTENSET_RXLVL_MASK)
/*! @} */

/*! @name FIFOINTENCLR - FIFO interrupt enable clear (disable) and read register. */
/*! @{ */

#define I2S_FIFOINTENCLR_TXERR_MASK              (0x1U)
#define I2S_FIFOINTENCLR_TXERR_SHIFT             (0U)
/*! TXERR - Writing one clears the corresponding bits in the FIFOINTENSET register. */
#define I2S_FIFOINTENCLR_TXERR(x)                (((uint32_t)(((uint32_t)(x)) << I2S_FIFOINTENCLR_TXERR_SHIFT)) & I2S_FIFOINTENCLR_TXERR_MASK)

#define I2S_FIFOINTENCLR_RXERR_MASK              (0x2U)
#define I2S_FIFOINTENCLR_RXERR_SHIFT             (1U)
/*! RXERR - Writing one clears the corresponding bits in the FIFOINTENSET register. */
#define I2S_FIFOINTENCLR_RXERR(x)                (((uint32_t)(((uint32_t)(x)) << I2S_FIFOINTENCLR_RXERR_SHIFT)) & I2S_FIFOINTENCLR_RXERR_MASK)

#define I2S_FIFOINTENCLR_TXLVL_MASK              (0x4U)
#define I2S_FIFOINTENCLR_TXLVL_SHIFT             (2U)
/*! TXLVL - Writing one clears the corresponding bits in the FIFOINTENSET register. */
#define I2S_FIFOINTENCLR_TXLVL(x)                (((uint32_t)(((uint32_t)(x)) << I2S_FIFOINTENCLR_TXLVL_SHIFT)) & I2S_FIFOINTENCLR_TXLVL_MASK)

#define I2S_FIFOINTENCLR_RXLVL_MASK              (0x8U)
#define I2S_FIFOINTENCLR_RXLVL_SHIFT             (3U)
/*! RXLVL - Writing one clears the corresponding bits in the FIFOINTENSET register. */
#define I2S_FIFOINTENCLR_RXLVL(x)                (((uint32_t)(((uint32_t)(x)) << I2S_FIFOINTENCLR_RXLVL_SHIFT)) & I2S_FIFOINTENCLR_RXLVL_MASK)
/*! @} */

/*! @name FIFOINTSTAT - FIFO interrupt status register. */
/*! @{ */

#define I2S_FIFOINTSTAT_TXERR_MASK               (0x1U)
#define I2S_FIFOINTSTAT_TXERR_SHIFT              (0U)
/*! TXERR - TX FIFO error. */
#define I2S_FIFOINTSTAT_TXERR(x)                 (((uint32_t)(((uint32_t)(x)) << I2S_FIFOINTSTAT_TXERR_SHIFT)) & I2S_FIFOINTSTAT_TXERR_MASK)

#define I2S_FIFOINTSTAT_RXERR_MASK               (0x2U)
#define I2S_FIFOINTSTAT_RXERR_SHIFT              (1U)
/*! RXERR - RX FIFO error. */
#define I2S_FIFOINTSTAT_RXERR(x)                 (((uint32_t)(((uint32_t)(x)) << I2S_FIFOINTSTAT_RXERR_SHIFT)) & I2S_FIFOINTSTAT_RXERR_MASK)

#define I2S_FIFOINTSTAT_TXLVL_MASK               (0x4U)
#define I2S_FIFOINTSTAT_TXLVL_SHIFT              (2U)
/*! TXLVL - Transmit FIFO level interrupt. */
#define I2S_FIFOINTSTAT_TXLVL(x)                 (((uint32_t)(((uint32_t)(x)) << I2S_FIFOINTSTAT_TXLVL_SHIFT)) & I2S_FIFOINTSTAT_TXLVL_MASK)

#define I2S_FIFOINTSTAT_RXLVL_MASK               (0x8U)
#define I2S_FIFOINTSTAT_RXLVL_SHIFT              (3U)
/*! RXLVL - Receive FIFO level interrupt. */
#define I2S_FIFOINTSTAT_RXLVL(x)                 (((uint32_t)(((uint32_t)(x)) << I2S_FIFOINTSTAT_RXLVL_SHIFT)) & I2S_FIFOINTSTAT_RXLVL_MASK)

#define I2S_FIFOINTSTAT_PERINT_MASK              (0x10U)
#define I2S_FIFOINTSTAT_PERINT_SHIFT             (4U)
/*! PERINT - Peripheral interrupt. */
#define I2S_FIFOINTSTAT_PERINT(x)                (((uint32_t)(((uint32_t)(x)) << I2S_FIFOINTSTAT_PERINT_SHIFT)) & I2S_FIFOINTSTAT_PERINT_MASK)
/*! @} */

/*! @name FIFOWR - FIFO write data. */
/*! @{ */

#define I2S_FIFOWR_TXDATA_MASK                   (0xFFFFFFFFU)
#define I2S_FIFOWR_TXDATA_SHIFT                  (0U)
/*! TXDATA - Transmit data to the FIFO. The number of bits used depends on configuration details. */
#define I2S_FIFOWR_TXDATA(x)                     (((uint32_t)(((uint32_t)(x)) << I2S_FIFOWR_TXDATA_SHIFT)) & I2S_FIFOWR_TXDATA_MASK)
/*! @} */

/*! @name FIFOWR48H - FIFO write data for upper data bits. May only be used if the I2S is configured for 2x 24-bit data and not using DMA. */
/*! @{ */

#define I2S_FIFOWR48H_TXDATA_MASK                (0xFFFFFFU)
#define I2S_FIFOWR48H_TXDATA_SHIFT               (0U)
/*! TXDATA - Transmit data to the FIFO. Whether this register is used and the number of bits used depends on configuration details. */
#define I2S_FIFOWR48H_TXDATA(x)                  (((uint32_t)(((uint32_t)(x)) << I2S_FIFOWR48H_TXDATA_SHIFT)) & I2S_FIFOWR48H_TXDATA_MASK)
/*! @} */

/*! @name FIFORD - FIFO read data. */
/*! @{ */

#define I2S_FIFORD_RXDATA_MASK                   (0xFFFFFFFFU)
#define I2S_FIFORD_RXDATA_SHIFT                  (0U)
/*! RXDATA - Received data from the FIFO. The number of bits used depends on configuration details. */
#define I2S_FIFORD_RXDATA(x)                     (((uint32_t)(((uint32_t)(x)) << I2S_FIFORD_RXDATA_SHIFT)) & I2S_FIFORD_RXDATA_MASK)
/*! @} */

/*! @name FIFORD48H - FIFO read data for upper data bits. May only be used if the I2S is configured for 2x 24-bit data and not using DMA. */
/*! @{ */

#define I2S_FIFORD48H_RXDATA_MASK                (0xFFFFFFU)
#define I2S_FIFORD48H_RXDATA_SHIFT               (0U)
/*! RXDATA - Received data from the FIFO. Whether this register is used and the number of bits used depends on configuration details. */
#define I2S_FIFORD48H_RXDATA(x)                  (((uint32_t)(((uint32_t)(x)) << I2S_FIFORD48H_RXDATA_SHIFT)) & I2S_FIFORD48H_RXDATA_MASK)
/*! @} */

/*! @name FIFORDNOPOP - FIFO data read with no FIFO pop. */
/*! @{ */

#define I2S_FIFORDNOPOP_RXDATA_MASK              (0xFFFFFFFFU)
#define I2S_FIFORDNOPOP_RXDATA_SHIFT             (0U)
/*! RXDATA - Received data from the FIFO. */
#define I2S_FIFORDNOPOP_RXDATA(x)                (((uint32_t)(((uint32_t)(x)) << I2S_FIFORDNOPOP_RXDATA_SHIFT)) & I2S_FIFORDNOPOP_RXDATA_MASK)
/*! @} */

/*! @name FIFORD48HNOPOP - FIFO data read for upper data bits with no FIFO pop. May only be used if the I2S is configured for 2x 24-bit data and not using DMA. */
/*! @{ */

#define I2S_FIFORD48HNOPOP_RXDATA_MASK           (0xFFFFFFU)
#define I2S_FIFORD48HNOPOP_RXDATA_SHIFT          (0U)
/*! RXDATA - Received data from the FIFO. Whether this register is used and the number of bits used depends on configuration details. */
#define I2S_FIFORD48HNOPOP_RXDATA(x)             (((uint32_t)(((uint32_t)(x)) << I2S_FIFORD48HNOPOP_RXDATA_SHIFT)) & I2S_FIFORD48HNOPOP_RXDATA_MASK)
/*! @} */

/*! @name FIFOSIZE - FIFO size register */
/*! @{ */

#define I2S_FIFOSIZE_FIFOSIZE_MASK               (0x1FU)
#define I2S_FIFOSIZE_FIFOSIZE_SHIFT              (0U)
/*! FIFOSIZE - Provides the size of the FIFO for software. The size of the SPI FIFO is 8 entries. */
#define I2S_FIFOSIZE_FIFOSIZE(x)                 (((uint32_t)(((uint32_t)(x)) << I2S_FIFOSIZE_FIFOSIZE_SHIFT)) & I2S_FIFOSIZE_FIFOSIZE_MASK)
/*! @} */

/*! @name ID - I2S Module identification */
/*! @{ */

#define I2S_ID_APERTURE_MASK                     (0xFFU)
#define I2S_ID_APERTURE_SHIFT                    (0U)
/*! APERTURE - Aperture: encoded as (aperture size/4K) -1, so 0x00 means a 4K aperture. */
#define I2S_ID_APERTURE(x)                       (((uint32_t)(((uint32_t)(x)) << I2S_ID_APERTURE_SHIFT)) & I2S_ID_APERTURE_MASK)

#define I2S_ID_MINOR_REV_MASK                    (0xF00U)
#define I2S_ID_MINOR_REV_SHIFT                   (8U)
/*! MINOR_REV - Minor revision of module implementation, starting at 0. */
#define I2S_ID_MINOR_REV(x)                      (((uint32_t)(((uint32_t)(x)) << I2S_ID_MINOR_REV_SHIFT)) & I2S_ID_MINOR_REV_MASK)

#define I2S_ID_MAJOR_REV_MASK                    (0xF000U)
#define I2S_ID_MAJOR_REV_SHIFT                   (12U)
/*! MAJOR_REV - Major revision of module implementation, starting at 0. */
#define I2S_ID_MAJOR_REV(x)                      (((uint32_t)(((uint32_t)(x)) << I2S_ID_MAJOR_REV_SHIFT)) & I2S_ID_MAJOR_REV_MASK)

#define I2S_ID_ID_MASK                           (0xFFFF0000U)
#define I2S_ID_ID_SHIFT                          (16U)
/*! ID - Unique module identifier for this IP block. */
#define I2S_ID_ID(x)                             (((uint32_t)(((uint32_t)(x)) << I2S_ID_ID_SHIFT)) & I2S_ID_ID_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group I2S_Register_Masks */


/*!
 * @}
 */ /* end of group I2S_Peripheral_Access_Layer */


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


#endif  /* I2S_H_ */

