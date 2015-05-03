/*
 * Copyright (c) 2013 - 2015, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef __FSL_SAI_HAL_H__
#define __FSL_SAI_HAL_H__


#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include "fsl_device_registers.h"
#if FSL_FEATURE_SOC_I2S_COUNT


/*!
 * @addtogroup sai_hal
 * @{
 */
 
/*! @file */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @brief Define the bus type of sai */
typedef enum _sai_protocol
{
    kSaiBusI2SLeft = 0x0u, /*!< Uses I2S left aligned format. @internal gui name="Left aligned" */
    kSaiBusI2SRight = 0x1u,/*!< Uses I2S right aligned format. @internal gui name="Right aligned" */
    kSaiBusI2SType = 0x2u, /*!< Uses I2S format. @internal gui name="I2S format" */
    kSaiBusPCMA = 0x3u,    /*!< Uses I2S PCM A format. @internal gui name="PCM A format" */
    kSaiBusPCMB = 0x4u,    /*!< Uses I2S PCM B format. @internal gui name="PCM B format" */
    kSaiBusAC97 = 0x5u     /*!< Uses I2S AC97 format. @internal gui name="AC97 format" */
 } sai_protocol_t;

/*! @brief Master or slave mode */
typedef enum _sai_master_slave
{
    kSaiMaster = 0x0u,/*!< Master mode */
    kSaiSlave = 0x1u/*!< Slave mode */
} sai_master_slave_t;

typedef enum _sai_mono_stereo
{
    kSaiMono = 0x0u, /*!< 1 channel in frame. @internal gui name="Mono" */
    kSaiStereo = 0x1u /*!< 2 channels in frame. @internal gui name="Stereo" */
} sai_mono_stereo_t;

/*! @brief Synchronous or asynchronous mode */
typedef enum _sai_sync_mode
{
    kSaiModeAsync = 0x0u,/*!< Asynchronous mode @internal gui name="Asynchronous" */
    kSaiModeSync = 0x1u,/*!< Synchronous mode (with receiver or transmit) @internal gui name="Synchronous" */
    kSaiModeSyncWithOtherTx = 0x2u,/*!< Synchronous with another SAI transmit @internal gui name="Synchronous with another Tx" */
    kSaiModeSyncWithOtherRx = 0x3u/*!< Synchronous with another SAI receiver @internal gui name="Synchronous with another Rx" */
} sai_sync_mode_t;

/*! @brief Mater clock source */
typedef enum _sai_mclk_source
{
    kSaiMclkSourceSysclk = 0x0u,/*!< Master clock from the system clock @internal gui name="System clock" */
    kSaiMclkSourceSelect1 = 0x1u,/*!< Master clock from source 1 @internal gui name="Input clock 1" */
    kSaiMclkSourceSelect2 = 0x2u,/*!< Master clock from source 2 @internal gui name="Input clock 2" */
    kSaiMclkSourceSelect3 = 0x3u/*!< Master clock from source 3 @internal gui name="Input clock 3" */
} sai_mclk_source_t;

/*! @brief Bit clock source */
typedef enum _sai_bclk_source
{
    kSaiBclkSourceBusclk = 0x0u,/*!< Bit clock using bus clock. @internal gui name="Bus clock" */
    kSaiBclkSourceMclkDiv = 0x1u,/*!< Bit clock using master clock divider. @internal gui name="Master clock" */
    kSaiBclkSourceOtherSai0 = 0x2u,/*!< Bit clock from other SAI device. @internal gui name="From SAI0" */
    kSaiBclkSourceOtherSai1 = 0x3u/*!< Bit clock from other SAI device. @internal gui name="From SAI1" */
} sai_bclk_source_t;

/*! @brief The SAI state flag. */
typedef enum _sai_interrupt_request
{
    kSaiIntrequestWordStart = 0x1000u,/*!< Word start flag, means the first word in a frame detected */
    kSaiIntrequestSyncError = 0x800u,/*!< Sync error flag, means the sync error is detected */
    kSaiIntrequestFIFOWarning = 0x200u,/*!< FIFO warning flag, means the FIFO is empty */
    kSaiIntrequestFIFOError = 0x400u,/*!< FIFO error flag */
    kSaiIntrequestFIFORequest = 0x100u,/*!< FIFO request, means reached watermark */
    kSaiIntRequestAll = 0x1F00 /* All interrupt source */
} sai_interrupt_request_t;

/*! @brief The DMA request sources */
typedef enum _sai_dma_request
{
    kSaiDmaReqFIFOWarning = 0x2u,/*!< FIFO warning caused by the DMA request */
    kSaiDmaReqFIFORequest = 0x1u,/*!< FIFO request caused by the DMA request */
    kSaiDmaReqAll = 0x3u /* All dma request source */
} sai_dma_request_t;

/*! @brief The SAI state flag */
typedef enum _sai_state_flag
{
    kSaiStateFlagWordStart = 0x100000u,/*!< Word start flag, means the first word in a frame detected. */
    kSaiStateFlagSyncError = 0x80000u,/*!< Sync error flag, means the sync error is detected */
    kSaiStateFlagFIFOError = 0x40000u,/*!< FIFO error flag */
    kSaiStateFlagFIFORequest = 0x10000u, /*!< FIFO request flag. */
    kSaiStateFlagFIFOWarning = 0x20000u, /*!< FIFO warning flag. */
    kSaiStateFlagSoftReset = 0x1000000u, /*!< Software reset flag */
    kSaiStateFlagAll = 0x11F0000u /*!< All flags. */
} sai_state_flag_t;

/*! @brief The reset type */
typedef enum _sai_reset_type
{
    kSaiResetTypeSoftware = 0x1000000u,/*!< Software reset, reset the logic state */
    kSaiResetTypeFIFO = 0x2000000u,/*!< FIFO reset, reset the FIFO read and write pointer */
    kSaiResetAll = 0x3000000u /*!< All reset. */
} sai_reset_type_t;

/*
 * @brief The SAI running mode
 * The mode includes normal mode, debug mode, and stop mode.
 */
typedef enum _sai_running_mode
{
    kSaiRunModeDebug = 0x0,/*!< In debug mode */ 
    kSaiRunModeStop = 0x1/*!< In stop mode */
} sai_run_mode_t;

#if FSL_FEATURE_SAI_HAS_FIFO_PACKING

/*
 * @brief The SAI packing mode
 * The mode includes 8 bit and 16 bit packing.
 */
typedef enum _sai_fifo_packing
{
    kSaiFifoPackingDisabled = 0x0, /*!< Packing disabled. */
    kSaiFifoPacking8bit = 0x2,/*!< 8 bit packing enabled. */
    kSaiFifoPacking16bit = 0x3 /*!< 16bit packing enabled. */
} sai_fifo_packing_t;
#endif

/*! @brief SAI clock configuration structure. */
typedef struct SaiClockSetting
{
    sai_mclk_source_t mclk_src; /*!< Master clock source. */
    sai_bclk_source_t bclk_src; /*!< Bit clock source. */
    uint32_t mclk_src_freq; /*!< Master clock source frequency. */
    uint32_t mclk; /*!< Master clock frequency. */
    uint32_t bclk; /*!< Bit clock frequency. */
    uint32_t bclk_src_freq; /* Bit clock source frequency. */
} sai_clock_setting_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
* @name Module control
* @{
*/

/*!
 * @brief  Initializes the SAI Tx.
 *
 * The initialization resets the SAI module by setting the SR bit of TCSR register.
 * Note that the function writes 0 to every control registers.
 * @param base Register base address of SAI module.
 */
void SAI_HAL_TxInit(I2S_Type * base);

/*!
 * @brief  Initializes the SAI Rx.
 *
 * The initialization resets the SAI module by setting the SR bit of RCSR register.
 * Note that the function writes 0 to every control registers.
 * @param base Register base address of SAI module.
 */
void SAI_HAL_RxInit(I2S_Type * base);

/*!
 * @brief Sets Tx protocol relevant settings.
 *
 * The bus mode means which protocol SAI uses. It can be I2S left, right and so on. Each protocol
 * has a different configuration on bit clock and frame sync.
 * @param base Register base address of SAI module.
 * @param protocol The protocol selection. It can be I2S left aligned, I2S right aligned, etc.
 */
void SAI_HAL_TxSetProtocol(I2S_Type * base, sai_protocol_t protocol);

/*!
 * @brief Sets Rx protocol relevant settings.
 *
 * The bus mode means which protocol SAI uses. It can be I2S left, right and so on. Each protocol
 * has a different configuration on bit clock and frame sync.
 * @param base Register base address of SAI module.
 * @param protocol The protocol selection. It can be I2S left aligned, I2S right aligned, etc.
 */
void SAI_HAL_RxSetProtocol(I2S_Type * base, sai_protocol_t protocol);

/*!
 * @brief Sets master or slave mode.
 *
 * The function determines master or slave mode. Master mode  provides its
 * own clock and slave mode  uses an external clock.
 * @param base Register base address of SAI module.
 * @param master_slave_mode Mater or slave mode.
 */
void SAI_HAL_TxSetMasterSlave(I2S_Type * base, sai_master_slave_t master_slave_mode);

/*!
 * @brief Sets master or slave mode.
 *
 * The function determines master or slave mode. Master mode provides its
 * own clock and slave mode  uses external clock.
 * @param base Register base address of SAI module.
 * @param master_slave_mode Mater or slave mode.
 */
void SAI_HAL_RxSetMasterSlave(I2S_Type * base, sai_master_slave_t master_slave_mode);

/*! @}*/

/*!
* @name Overall Clock configuration
* @{
*/

/*!
 * @brief Setup clock for SAI Tx.
 *
 * This function can sets the clock settings according to the configure structure.
 * In this configuration setting structure, users can set clock source, clock source frequency,
 * and frequency of master clock and bit clock.
 * If bit clock source is master clock, the master clock frequency should equal to bit clock source
 * frequency. If bit clock source is not master clock, then settings about master clock have no
 * effect to the setting.
 * @param base Register base address of SAI module.
 * @param clk_config Pointer to sai clock configuration structure.
 */
void SAI_HAL_TxClockSetup(I2S_Type * base, sai_clock_setting_t *clk_config);

/*!
 * @brief Setup clock for SAI Rx.
 *
 * This function can sets the clock settings according to the configure structure.
 * In this configuration setting structure, users can set clock source, clock source frequency,
 * and frequency of master clock and bit clock.
 * If bit clock source is master clock, the master clock frequency should equal to bit clock source
 * frequency. If bit clock source is not master clock, then settings about master clock have no
 * effect to the setting.
 * @param base Register base address of SAI module.
 * @param clk_config Pointer to sai clock configuration structure.
 */
void SAI_HAL_RxClockSetup(I2S_Type * base, sai_clock_setting_t *clk_config);

/*! @}*/

/*!
* @name Master clock configuration
* @{
*/

/*!
 * @brief Sets the master clock source.
 *
 * The source of the clock is different from socs.
 * This function sets the clock source for SAI master clock source.
 * Master clock is used to produce the bit clock for the data transfer.
 * @param base Register base address of SAI module.
 * @param source Mater clock source
 */
static inline void SAI_HAL_SetMclkSrc(I2S_Type * base, sai_mclk_source_t source)
{
    I2S_BWR_MCR_MICS(base,source);
}

/*!
 * @brief Gets the master clock source.
 *
 * The source of the clock is different from socs.
 * This function gets the clock source for SAI master clock source.
 * Master clock is used to produce the bit clock for the data transfer.
 * @param base Register base address of SAI module.
 * @return Mater clock source
 */
static inline uint32_t SAI_HAL_GetMclkSrc(I2S_Type * base)
{
    return I2S_BRD_MCR_MICS(base);
}

/*!
 * @brief Enable or disable MCLK internal.
 * 
 * This function enable or disable internal MCLK.
 * @param base Register base address of SAI module.
 * @param enable True means enable, false means disable.
 */
static inline void SAI_HAL_SetMclkDividerCmd(I2S_Type * base, bool enable)
{
    I2S_BWR_MCR_MOE(base,enable);
}

#if FSL_FEATURE_SAI_HAS_MCLKDIV_REGISTER
/*!
 * @brief Sets the divider of the master clock.
 *
 * Using the divider to get the master clock frequency wanted from the source. 
 * mclk = clk_source * fract/divide. The input is the master clock frequency needed and the source clock frequency.
 * The master clock is decided by the sample rate and the multi-clock number.
 * Notice that mclk should less than src_clk, or it would do hang as the HW refuses to write in this situation.
 * @param base Register base address of SAI module.
 * @param mclk Master clock frequency needed.
 * @param src_clk The source clock frequency.
 */
void SAI_HAL_SetMclkDiv(I2S_Type * base, uint32_t mclk, uint32_t src_clk);
#endif

/*! @}*/

/*!
* @name Bit clock configuration
* @{
*/

/*!
 * @brief Sets the bit clock source of Tx. It is generated by the master clock, bus clock and other devices.
 *
 * The function sets the source of the bit clock. The bit clock can be produced by the master
 * clock and from the bus clock or other SAI Tx/Rx. Tx and Rx in the SAI module use the same bit 
 * clock either from Tx or Rx.
 * @param base Register base address of SAI module.
 * @param source Bit clock source.
 */
static inline void SAI_HAL_TxSetBclkSrc(I2S_Type * base, sai_bclk_source_t source)
{
    I2S_BWR_TCR2_MSEL(base,source);
}

/*!
 * @brief Sets bit clock source of the Rx. It is generated by the master clock, bus clock and other devices.
 *
 * The function sets the source of the bit clock. The bit clock can be produced by the master
 * clock, and from the bus clock or other SAI Tx/Rx. Tx and Rx in the SAI module use the same bit 
 * clock either from Tx or Rx.
 * @param base Register base address of SAI module.
 * @param source Bit clock source.
 */
static inline void SAI_HAL_RxSetBclkSrc(I2S_Type * base, sai_bclk_source_t source)
{
    I2S_BWR_RCR2_MSEL(base,source);
}

/*!
 * @brief Gets the bit clock source of Tx. It is generated by the master clock, bus clock and other devices.
 *
 * The function gets the source of the bit clock. The bit clock can be produced by the master
 * clock and from the bus clock or other SAI Tx/Rx. Tx and Rx in the SAI module use the same bit 
 * clock either from Tx or Rx.
 * @param base Register base address of SAI module.
 * @return Bit clock source.
 */
static inline uint32_t SAI_HAL_TxGetBclkSrc(I2S_Type * base)
{
    return I2S_BRD_TCR2_MSEL(base);
}

/*!
 * @brief Gets bit clock source of the Rx. It is generated by the master clock, bus clock and other devices.
 *
 * The function gets the source of the bit clock. The bit clock can be produced by the master
 * clock, and from the bus clock or other SAI Tx/Rx. Tx and Rx in the SAI module use the same bit 
 * clock either from Tx or Rx.
 * @param base Register base address of SAI module.
 * @return Bit clock source.
 */
static inline uint32_t SAI_HAL_RxGetBclkSrc(I2S_Type * base)
{
    return I2S_BRD_RCR2_MSEL(base);
}

/*!
 * @brief Sets the Tx bit clock divider value.
 *
 * bclk = mclk / divider. At the same time, bclk = sample_rate * channel * bits. This means
 * how much time is needed to transfer one bit.
 * Notice: The function is called while the bit clock source is the master clock.
 * @param base Register base address of SAI module.
 * @param divider The divide number of bit clock.
 */
static inline void SAI_HAL_TxSetBclkDiv(I2S_Type * base, uint32_t divider)
{
    I2S_BWR_TCR2_DIV(base,divider/2 -1);
}

/*!
 * @brief Sets the Rx bit clock divider value.
 *
 * bclk = mclk / divider. At the same time, bclk = sample_rate * channel * bits. This means
 * how much time is needed to transfer one bit.
 * Notice: The function is called while the bit clock source is the master clock.
 * @param base Register base address of SAI module.
 * @param divider The divide number of bit clock.
 */
static inline void SAI_HAL_RxSetBclkDiv(I2S_Type * base, uint32_t divider)
{
    I2S_BWR_RCR2_DIV(base,divider/2 -1);
}

/*!
 * @brief Enables or disables the Tx bit clock input bit.
 * 
 * @param saiBaseAddr Register base address of SAI module.
 * @param enable True means enable, false means disable.
 */
static inline void SAI_HAL_TxSetBclkInputCmd(I2S_Type * base, bool enable)
{
    I2S_BWR_TCR2_BCI(base,enable);
}

/*!
 * @brief Enables or disables the Rx bit clock input bit.
 * 
 * @param saiBaseAddr Register base address of SAI module.
 * @param enable True means enable, false means disable.
 */
static inline void SAI_HAL_RxSetBclkInputCmd(I2S_Type * base, bool enable)
{
    I2S_BWR_RCR2_BCI(base,enable);
}
/*!
 * @brief Sets the Tx bit clock swap.
 *
 * This field swaps the bit clock used by the transmitter. When the transmitter is configured in 
 * asynchronous mode and this bit is set, the transmitter is clocked by the receiver bit clock. 
 * This allows the transmitter and receiver to share the same bit clock, but the transmitter 
 * continues to use the transmit frame sync (SAI_TX_SYNC).
 * When the transmitter is configured in synchronous mode, the transmitter BCS field and receiver
 * BCS field must be set to the same value. When both are set, the transmitter and receiver are both
 * clocked by the transmitter bit clock (SAI_TX_BCLK) but use the receiver frame sync (SAI_RX_SYNC).
 * @param saiBaseAddr Register base address of SAI module.
 * @param enable True means swap bit closk, false means no swap.
 */
static inline void SAI_HAL_TxSetSwapBclkCmd(I2S_Type * base, bool enable)
{
    I2S_BWR_TCR2_BCS(base,enable);
}

/*!
 * @brief Sets the Rx bit clock swap.
 *
 * This field swaps the bit clock used by the receiver. When the receiver is configured in 
 * asynchronous mode and this bit is set, the receiver is clocked by the transmitter bit clock
 * (SAI_TX_BCLK). This allows the transmitter and receiver to share the same bit clock, but the 
 * receiver continues to use the receiver frame sync (SAI_RX_SYNC). 
 * When the receiver is configured in synchronous mode, the transmitter BCS field and receiver BCS 
 * field must be set to the same value. When both are set, the transmitter and receiver are both 
 * clocked by the receiver bit clock (SAI_RX_BCLK) but use the transmitter frame sync (SAI_TX_SYNC).
 * @param saiBaseAddr Register base address of SAI module.
 * @param enable True means swap bit closk, false means no swap.
 */
static inline void SAI_HAL_RxSetSwapBclkCmd(I2S_Type * base, bool enable)
{
    I2S_BWR_RCR2_BCS(base, enable);
}
/*! @} */

/*!
* @name Mono or stereo configuration
* @{
*/

/*!
 * @brief Set Tx audio channel number. Can be mono or stereo. 
 * 
 * @param base Register base address of SAI module.
 * @param mono_stereo Mono or stereo mode.
 */
void SAI_HAL_TxSetMonoStereo(I2S_Type * base, sai_mono_stereo_t mono_stereo);

/*!
 * @brief Set Rx audio channel number. Can be mono or stereo. 
 * 
 * @param base Register base address of SAI module.
 * @param mono_stereo Mono or stereo mode.
 */
void SAI_HAL_RxSetMonoStereo(I2S_Type * base, sai_mono_stereo_t mono_stereo);

/*! @} */

/*!
* @name Word configurations
* @{
*/

/*!
 * @brief Set Tx word width. 
 * 
 * This interface is for i2s and PCM series protocol, it would set the width of first word and other word 
 * the same. At the same time, for i2s series protocol, it will set frame sync width the equal to the 
 * word width.
 * @param base Register base address of SAI module.
 * @param protocol Protocol used for tx now.
 * @param bits Tx word width.
 */
void SAI_HAL_TxSetWordWidth(I2S_Type * base, sai_protocol_t protocol, uint32_t bits);

/*!
 * @brief Set Rx word width. 
 * 
 * This interface is for i2s and PCM series protocol, it would set the width of first word and other word 
 * the same. At the same time, for i2s series protocol, it will set frame sync width the equal to the 
 * word width.
 * @param base Register base address of SAI module.
 * @param protocol Protocol used for rx now.
 * @param bits Rx word width.
 */
void SAI_HAL_RxSetWordWidth(I2S_Type * base, sai_protocol_t protocol, uint32_t bits);

/*!@}*/

#if (FSL_FEATURE_SAI_FIFO_COUNT > 1)
/*!
* @name watermark settings
* @{
*/

/*!
 * @brief Sets the Tx watermark value.
 *
 * While the value in the FIFO is less or equal to the watermark , it generates an interrupt 
 * request or a DMA request. The watermark value cannot be greater than the depth of FIFO.
 * @param base Register base address of SAI module.
 * @param watermark Watermark value of a FIFO.
 */
static inline void SAI_HAL_TxSetWatermark(I2S_Type * base, uint32_t watermark)
{
    I2S_BWR_TCR1_TFW(base, watermark);
}

/*!
 * @brief Sets the Tx watermark value.
 *
 * While the value in the FIFO is more or equal to the watermark , it generates an interrupt 
 * request or a DMA request. The watermark value cannot be greater than the depth of FIFO.
 * @param base Register base address of SAI module.
 * @param watermark Watermark value of a FIFO.
 */
static inline void SAI_HAL_RxSetWatermark(I2S_Type * base, uint32_t watermark)
{
    I2S_BWR_RCR1_RFW(base, watermark);
}

/*!
 * @brief Gets the Tx watermark value.
 *
 * @param base Register base address of SAI module.
 * @return The Tx watermark value.
 */
static inline uint32_t SAI_HAL_TxGetWatermark(I2S_Type * base)
{
    return I2S_BRD_TCR1_TFW(base);
}

/*!
 * @brief Gets the Rx watermark value.
 *
 * @param base Register base address of SAI module.
 * @return The Tx watermark value.
 */
static inline uint32_t SAI_HAL_RxGetWatermark(I2S_Type * base)
{
    return I2S_BRD_RCR1_RFW(base);
}

#endif

/*! @}*/

/*!
 * @brief SAI Tx sync mode setting. 
 *
 * The mode can be asynchronous mode, synchronous, or synchronous with another SAI device.
 * When configured for a synchronous mode of operation, the receiver must be configured for the 
 * asynchronous operation.
 * @param base Register base address of SAI module.
 * @param sync_mode Synchronous mode or Asynchronous mode.
 */
void SAI_HAL_TxSetSyncMode(I2S_Type * base, sai_sync_mode_t sync_mode);

/*!
 * @brief SAI Rx sync mode setting. 
 *
 * The mode can be asynchronous mode, synchronous, or synchronous with another SAI device.
 * When configured for a synchronous mode of operation, the receiver must be configured for the 
 * asynchronous operation.
 * @param base Register base address of SAI module.
 * @param sync_mode Synchronous mode or Asynchronous mode.
 */
void SAI_HAL_RxSetSyncMode(I2S_Type * base, sai_sync_mode_t sync_mode);

#if (FSL_FEATURE_SAI_FIFO_COUNT > 1)
/*!
 * @brief Gets the Tx FIFO read and write pointer.
 *
 * It is used to determine whether the FIFO is full or empty and know how much space there is for FIFO.
 * If read_ptr == write_ptr, the FIFO is empty. While the bit of the read_ptr and the write_ptr are
 * equal except for the MSB, the FIFO is full.
 * @param base Register base address of SAI module.
 * @param fifo_channel FIFO channel selected.
 * @param r_ptr Pointer to get tx fifo read pointer.
 * @param w_ptr Pointer to get tx fifo write pointer.
 */
void SAI_HAL_TxGetFifoWRPointer(I2S_Type * base,  uint32_t fifo_channel, 
       uint32_t * r_ptr, uint32_t * w_ptr);

/*!
 * @brief Gets the Rx FIFO read and write pointer.
 *
 * It is used to determine whether the FIFO is full or empty and know how much space there is for FIFO.
 * If read_ptr == write_ptr, the FIFO is empty. While the bit of the read_ptr and the write_ptr are
 * equal except for the MSB, the FIFO is full.
 * @param base Register base address of SAI module.
 * @param fifo_channel FIFO channel selected.
 * @param r_ptr Pointer to get rx fifo read pointer.
 * @param w_ptr Pointer to get rx fifo write pointer.
 */
void SAI_HAL_RxGetFifoWRPointer(I2S_Type * base,  uint32_t fifo_channel,
        uint32_t * r_ptr, uint32_t * w_ptr);
#endif

/*!
 * @brief Gets the TDR register address.
 *
 * This function determines the dest/src address of the DMA transfer.
 * @param base Register base address of SAI module.
 * @param fifo_channel FIFO channel selected.
 * @return TDR register or RDR register address
 */
static inline uint32_t SAI_HAL_TxGetFifoAddr(I2S_Type * base, uint32_t fifo_channel)
{
    return (uint32_t)(&I2S_TDR_REG(base, fifo_channel));
}

/*!
 * @brief Gets the RDR register address.
 *
 * This function determines the dest/src address of the DMA transfer.
 * @param base Register base address of SAI module.
 * @param fifo_channel FIFO channel selected.
 * @return TDR register or RDR register address
 */
static inline uint32_t SAI_HAL_RxGetFifoAddr(I2S_Type * base, uint32_t fifo_channel)
{
    return (uint32_t)(&I2S_RDR_REG(base, fifo_channel));
}

/*!
 * @brief Enables the SAI Tx module.
 *
 * Enables the Tx. This function enables both the bit clock and the transfer channel.
 * @param base Register base address of SAI module.
 */
static inline void SAI_HAL_TxEnable(I2S_Type * base)
{
    I2S_BWR_TCSR_BCE(base,true);
    I2S_BWR_TCSR_TE(base,true);
}

/*!
 * @brief Enables the SAI Rx module.
 *
 * Enables the Rx. This function enables both the bit clock and the receive channel.
 * @param base Register base address of SAI module.
 */
static inline void SAI_HAL_RxEnable(I2S_Type * base)
{
    I2S_BWR_RCSR_BCE(base,true);    
    I2S_BWR_RCSR_RE(base,true);
}

/*!
 * @brief Disables the Tx module.
 *
 * Disables the Tx. This function disables both the bit clock and the transfer channel.
 * @param base Register base address of SAI module.
 */
static inline void SAI_HAL_TxDisable(I2S_Type * base)
{
    I2S_BWR_TCSR_TE(base,false);
    I2S_BWR_TCSR_BCE(base,false);
}

/*!
 * @brief Disables the Rx module.
 *
 * Disables the Rx. This function disables both the bit clock and the receive channel.
 * @param base Register base address of SAI module.
 */
static inline void SAI_HAL_RxDisable(I2S_Type * base)
{
    I2S_BWR_RCSR_RE(base,false);
    I2S_BWR_RCSR_BCE(base,false);
}

/*!
 * @brief Enables the Tx interrupt from different interrupt sources.
 *
 * The interrupt source can be : Word start flag, Sync error flag, FIFO error flag, FIFO warning flag, FIFO request flag.
 * This function sets which flag causes an interrupt request. 
 * @param base Register base address of SAI module.
 * @param source SAI interrupt request source.
 * @param enable Enable or disable.
 */
void SAI_HAL_TxSetIntCmd(I2S_Type * base, uint32_t source, bool enable);

/*!
 * @brief Enables the Rx interrupt from different interrupt sources.
 *
 * The interrupt source can be : Word start flag, Sync error flag, FIFO error flag, FIFO warning flag, FIFO request flag.
 * This function sets which flag causes an interrupt request. 
 * @param base Register base address of SAI module.
 * @param source SAI interrupt request source.
 * @param enable Enable or disable.
 */
void SAI_HAL_RxSetIntCmd(I2S_Type * base, uint32_t source, bool enable);

/*!
 * @brief Enables the Tx DMA request from different sources.
 *
 * The DMA sources can be: FIFO warning and FIFO request.
 * This function enables the DMA request from different DMA request sources.
 * @param base Register base address of SAI module.
 * @param source SAI DMA request source.
 * @param enable Enable or disable.
 */
void SAI_HAL_TxSetDmaCmd(I2S_Type * base, uint32_t source, bool enable);

/*!
 * @brief Enables the Rx DMA request from different sources.
 *
 * The DMA sources can be: FIFO warning and FIFO request.
 * This function enables the DMA request from different DMA request sources.
 * @param base Register base address of SAI module.
 * @param source SAI DMA request source.
 * @param enable Enable or disable.
 */
void SAI_HAL_RxSetDmaCmd(I2S_Type * base, uint32_t source, bool enable);

/*!
 * @brief Clears the Tx state flags.
 *
 * The function is used to clear the flags manually. It can clear word start, FIFO warning, FIFO error,
 * FIFO request flag.
 * @param base Register base address of SAI module.
 * @param flag SAI state flag type. The flag can be word start, sync error, FIFO error/warning.
 */
void SAI_HAL_TxClearStateFlag(I2S_Type * base, uint32_t flag_mask);

/*!
 * @brief Clears the Rx state flags.
 *
 * The function is used to clear the flags manually. It can clear word start, FIFO warning, FIFO error,
 * FIFO request flag.
 * @param base Register base address of SAI module.
 * @param flag SAI state flag type. The flag can be word start, sync error, FIFO error/warning.
 */
void SAI_HAL_RxClearStateFlag(I2S_Type * base, uint32_t flag_mask);

/*!
 * @brief Resets the Tx module.
 *
 * There are two kinds of resets: Software reset and FIFO reset.
 * Software reset: resets all transmitter internal logic, including the bit clock generation, 
 * status flags and FIFO pointers. It does not reset the configuration registers.
 * FIFO reset: synchronizes the FIFO write pointer to the same value as the FIFO read pointer. 
 * This empties the FIFO contents and is to be used after the Transmit FIFO Error Flag is set,
 * and before the FIFO is re-initialized and the Error Flag is cleared.
 * @param base Register base address of SAI module.
 * @param type SAI reset type.
 */
void SAI_HAL_TxSetReset(I2S_Type * base, uint32_t reset_mask);

/*!
 * @brief Resets the Rx module.
 *
 * There are two kinds of resets: Software reset and FIFO reset.
 * Software reset: resets all transmitter internal logic, including the bit clock generation, 
 * status flags and FIFO pointers. It does not reset the configuration registers.
 * FIFO reset: synchronizes the FIFO write pointer to the same value as the FIFO read pointer. 
 * This empties the FIFO contents and is to be used after the Transmit FIFO Error Flag is set,
 * and before the FIFO is re-initialized and the Error Flag is cleared.
 * @param base Register base address of SAI module.
 * @param type SAI reset type.
 */
void SAI_HAL_RxSetReset(I2S_Type * base, uint32_t reset_mask);

/*!
 * @brief Sets the Tx FIFO channel.
 *
 * A SAI base includes a Tx and an Rx. Each has several channels according to 
 * different platforms. A channel means a path for the audio data input/output.
 * @param base Register base address of SAI module.
 * @param fifo_channel FIFO channel number.
 */
static inline void SAI_HAL_TxSetDataChn(I2S_Type * base, uint8_t fifo_channel)
{
    I2S_BWR_TCR3_TCE(base, 1u << fifo_channel);
}

/*!
 * @brief Sets the Rx FIFO channel.
 *
 * A SAI base includes a Tx and a Rx. Each has several channels according to 
 * different platforms. A channel means a path for the audio data input/output.
 * @param base Register base address of SAI module.
 * @param fifo_channel FIFO channel number.
 */
static inline void SAI_HAL_RxSetDataChn(I2S_Type * base, uint8_t fifo_channel)
{
    I2S_BWR_RCR3_RCE(base, 1u << fifo_channel);
}

/*!
 * @brief Sets the running mode of the Tx. There is a debug mode, stop mode, and a normal mode.
 *
 * This function can set the working mode of the SAI base. Stop mode is always 
 * used in low power cases, and the debug mode disables the  SAI after the current 
 * transmit/receive is completed.
 * @param base Register base address of SAI module.
 * @param run_mode SAI running mode.
 * @param enable Enable or disable a mode.
 */
void SAI_HAL_TxSetRunModeCmd(I2S_Type * base, sai_run_mode_t run_mode, bool enable);

/*!
 * @brief Sets the running mode of the Rx. There is a debug mode, stop mode, and a normal mode.
 *
 * This function can set the working mode of the SAI base. Stop mode is always 
 * used in low power cases, and the debug mode disables the  SAI after the current 
 * transmit/receive is completed.
 * @param base Register base address of SAI module.
 * @param run_mode SAI running mode.
 * @param enable Enable or disable a mode.
 */
void SAI_HAL_RxSetRunModeCmd(I2S_Type * base, sai_run_mode_t run_mode, bool enable);

/*!
 * @brief Gets the state of the flags in the TCSR.
 * @param base Register base address of SAI module.
 * @param flag State flag type, it can be FIFO error, FIFO warning and so on.
 * @return True if detect word start otherwise false.
 */
static inline uint32_t SAI_HAL_TxGetStateFlag(I2S_Type * base, uint32_t flag_mask)
{
    return (I2S_RD_TCSR(base) & flag_mask);
}

/*!
 * @brief Gets the state of the flags in the RCSR.
 * @param base Register base address of SAI module.
 * @param flag State flag type, it can be FIFO error, FIFO warning and so on.
 * @return True if detect word start otherwise false.
 */
static inline uint32_t SAI_HAL_RxGetStateFlag(I2S_Type * base, uint32_t flag_mask)
{
    return (I2S_RD_RCSR(base) & flag_mask);
}

/*!
 * @brief Receives the data from the FIFO.
 * @param base Register base address of SAI module.
 * @param rx_channel Rx FIFO channel.
 * @param data Pointer to the address to be written in.
 * @return Received data. 
 */
static inline uint32_t SAI_HAL_ReceiveData(I2S_Type * base, uint32_t rx_channel)
{
    assert(rx_channel < FSL_FEATURE_SAI_CHANNEL_COUNT);   
    return I2S_RD_RDR(base, rx_channel);
}

/*!
 * @brief Transmits data to the FIFO.
 * @param base Register base address of SAI module.
 * @param tx_channel Tx FIFO channel.
 * @param data Data value which needs to be written into FIFO.
 */
static inline void SAI_HAL_SendData(I2S_Type * base, uint32_t tx_channel, uint32_t data)
{
    assert(tx_channel < FSL_FEATURE_SAI_CHANNEL_COUNT);  
    I2S_WR_TDR(base,tx_channel,data);
}

/*!
* @brief Uses blocking to receive data.
* @param base The SAI base.
* @param rx_channel Rx FIFO channel.
* @return Received data.
*/
void SAI_HAL_ReceiveDataBlocking(I2S_Type * base, uint32_t rx_channel,
    uint8_t * rxBuff, uint32_t size);

/*!
* @brief Uses blocking to send data.
* @param base The SAI base.
* @param tx_channel Tx FIFO channel.
* @param data Data value which needs to be written into FIFO.
*/
void SAI_HAL_SendDataBlocking(I2S_Type * base, uint32_t tx_channel, 
    uint8_t * txBuff, uint32_t size);

#if FSL_FEATURE_SAI_HAS_ON_DEMAND_MODE
/*!
 * @brief Tx on-demand mode setting.
 *
 * When set, the frame sync is generated internally. A frame sync is only generated when the 
 * FIFO warning flag is clear.
 * @param base Register base address of SAI module.
 * @param enable True means on demand mode enable, false means disable.
 */
static inline void SAI_HAL_TxSetOndemandCmd(I2S_Type * base, bool enable)
{
    I2S_BWR_TCR4_ONDEM(base, enable);
}

/*!
 * @brief Rx on-demand mode setting.
 *
 * When set, the frame sync is generated internally. A frame sync is only generated when the 
 * FIFO warning flag is clear.
 * @param base Register base address of SAI module.
 * @param enable True means on demand mode enable, false means disable.
 */
static inline void SAI_HAL_RxSetOndemandCmd(I2S_Type * base, bool enable)
{
    I2S_BWR_RCR4_ONDEM(base, enable);
}
#endif

#if FSL_FEATURE_SAI_HAS_FIFO_FUNCTION_AFTER_ERROR
/*!
 * @brief Tx FIFO continues on error.
 *
 * Configures when the SAI continues transmitting after a FIFO error has been detected.
 * @param base Register base address of SAI module.
 * @param enable True means on demand mode enable, false means disable.
 */
static inline void SAI_HAL_TxSetFIFOErrorContinueCmd(I2S_Type * base, bool enable)
{
    I2S_BWR_TCR4_FCONT(base, enable);
}

/*!
 * @brief Rx FIFO continues on error.
 *
 * Configures when the SAI continues transmitting after a FIFO error has been detected.
 * @param base Register base address of SAI module.
 * @param enable True means on demand mode enable, false means disable.
 */
static inline void SAI_HAL_RxSetFIFOErrorContinueCmd(I2S_Type * base, bool enable)
{
    I2S_BWR_RCR4_FCONT(base, enable);
}
#endif

#if FSL_FEATURE_SAI_HAS_FIFO_PACKING
/*!
 * @brief Tx FIFO packing mode setting.
 *
 * Enables packing 8-bit data or 16-bit data into each 32-bit FIFO word. If the word size is 
 * greater than 8-bit or 16-bit, only the first 8-bit or 16-bits are loaded from the FIFO. 
 * The first word in each frame always starts with a new 32-bit FIFO word and the first bit shifted
 * must be configured within the first packed word. When FIFO packing is enabled, the FIFO write
 * pointer only increments when the full 32-bit FIFO word has been written by software.
 * @param base Register base address of SAI module.
 * @param mode FIFO packing mode.
 */
static inline void SAI_HAL_TxSetFIFOPackingMode(I2S_Type * base, sai_fifo_packing_t mode)
{
    I2S_BWR_TCR4_FPACK(base,mode);
}

/*!
 * @brief Rx FIFO packing mode setting.
 *
 * Enables packing 8-bit data or 16-bit data into each 32-bit FIFO word. If the word size is 
 * greater than 8-bit or 16-bit, only the first 8-bit or 16-bits are loaded from the FIFO. 
 * The first word in each frame always starts with a new 32-bit FIFO word and the first bit shifted
 * must be configured within the first packed word. When FIFO packing is enabled, the FIFO write
 * pointer only increments when the full 32-bit FIFO word has been written by software.
 * @param base Register base address of SAI module.
 * @param mode FIFO packing mode.
 */
static inline void SAI_HAL_RxSetFIFOPackingMode(I2S_Type * base, sai_fifo_packing_t mode)
{
    I2S_BWR_RCR4_FPACK(base,mode);
}
#endif

#if defined(__cplusplus)
}
#endif

/*! @} */

#endif
#endif /* __FSL_SAI_HAL_H__ */
/*******************************************************************************
* EOF
*******************************************************************************/
