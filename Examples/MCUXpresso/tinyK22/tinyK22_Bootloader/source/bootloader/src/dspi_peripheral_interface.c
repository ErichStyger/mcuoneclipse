/*
 * Copyright (c) 2013-2015 Freescale Semiconductor, Inc.
 * Copyright 2016-2018 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "utilities/fsl_assert.h"
#include "bootloader/bl_context.h"
#include "bootloader_common.h"
#include "bootloader/bl_irq_common.h"
#include "packet/command_packet.h"
#include "fsl_dspi.h"
#include "fsl_device_registers.h"
#include "packet/serial_packet.h"

#if BL_CONFIG_DSPI

//! @addtogroup dspi_peripheral
//! @{

////////////////////////////////////////////////////////////////////////////////
// Definitions
////////////////////////////////////////////////////////////////////////////////

//! @brief Synchronization state between DSPI ISR and read/write functions.
typedef struct _dspi_transfer_info
{
    const uint8_t *writeData;                                //!< The applications data to write
    volatile uint32_t bytesToTransfer;                       //!< The total number of bytes to be transmitted
    void (*data_source)(uint8_t *source_byte);               // !< Callback used to get byte to transmit.
    void (*data_sink)(uint8_t sink_byte, uint32_t instance); // !< Callback used to put received byte.
} dspi_transfer_info_t;

////////////////////////////////////////////////////////////////////////////////
// Prototypes
////////////////////////////////////////////////////////////////////////////////

//! @brief DSPI slave poll for activity function
static bool dspi_poll_for_activity(const peripheral_descriptor_t *self);
//! @brief DSPI slave init function
static status_t dspi_full_init(const peripheral_descriptor_t *self, serial_byte_receive_func_t function);
//! @brief DSPI slave shutdown function
static void dspi_full_shutdown(const peripheral_descriptor_t *self);
//! @brief DSPI slave sending data function
static void dspi_data_source(uint8_t *source_byte);
//! @brief DSPI slave receiving data function
static void dspi_data_sink(uint8_t sink_byte, uint32_t instance);
//! @brief DSPI slave receiving first byte data function
static void dspi_initial_data_sink(uint8_t sink_byte, uint32_t instance);
//! @brief DSPI slave writing data function
status_t dspi_write(const peripheral_descriptor_t *self, const uint8_t *buffer, uint32_t byteCount);

////////////////////////////////////////////////////////////////////////////////
// Variables
////////////////////////////////////////////////////////////////////////////////

/*!
 * @brief DSPI slave control interface information
 */
const peripheral_control_interface_t g_dspiControlInterface = {
    .pollForActivity = dspi_poll_for_activity, .init = dspi_full_init, .shutdown = dspi_full_shutdown, .pump = 0
};

/*!
 * @brief DSPI slave byte interface information
 */
const peripheral_byte_inteface_t g_dspiByteInterface = {.init = NULL, .write = dspi_write };

//! @brief Global state for the DSPI slave peripheral interface.
static dspi_transfer_info_t s_dspiInfo = {
    .writeData = 0, .bytesToTransfer = 0, .data_source = dspi_data_source, .data_sink = dspi_initial_data_sink
};

//! @brief Flag for DSPI detecting device activity
static bool s_dspiActivity[FSL_FEATURE_SOC_DSPI_COUNT] = { false };

//! @brief Flag for DSPI intialization state
static bool s_dspiIntialized[FSL_FEATURE_SOC_DSPI_COUNT] = { false };

/*!
 * @brief DSPI slave receiving data call back function
 */
static serial_byte_receive_func_t s_dspi_app_data_sink_callback;

const static uint32_t g_dspiBaseAddr[] = SPI_BASE_ADDRS;

////////////////////////////////////////////////////////////////////////////////
// Code
////////////////////////////////////////////////////////////////////////////////

/*FUNCTION**********************************************************************
 *
 * Function Name : dspi_poll_for_activity
 * Description   : Polling for DSPI slave activities
 *
 *END**************************************************************************/
bool dspi_poll_for_activity(const peripheral_descriptor_t *self)
{
    return s_dspiActivity[self->instance];
}

/*FUNCTION**********************************************************************
 *
 * Function Name : dspi_data_source
 * Description   : DSPI slave sending data function
 *
 *END**************************************************************************/
void dspi_data_source(uint8_t *source_byte)
{
    assert(source_byte);

    if (s_dspiInfo.bytesToTransfer)
    {
        *source_byte = *s_dspiInfo.writeData++;
        s_dspiInfo.bytesToTransfer--;
    }
    else
    {
        *source_byte = 0;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : dspi_initial_data_sink
 * Description   : DSPI slave receiving first byte data function
 *
 *END**************************************************************************/
void dspi_initial_data_sink(uint8_t sink_byte, uint32_t instance)
{
    if (sink_byte == kFramingPacketStartByte)
    {
        s_dspiActivity[instance] = true;
        s_dspiInfo.data_sink = dspi_data_sink;
        s_dspi_app_data_sink_callback(sink_byte);
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : dspi_data_sink
 * Description   : DSPI slave receiving data function
 *
 *END**************************************************************************/
void dspi_data_sink(uint8_t sink_byte, uint32_t instance)
{
    s_dspi_app_data_sink_callback(sink_byte);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : dspi_full_init
 * Description   : DSPI slave full init function
 *
 *END**************************************************************************/
status_t dspi_full_init(const peripheral_descriptor_t *self, serial_byte_receive_func_t function)
{
    s_dspi_app_data_sink_callback = function;
    dspi_slave_config_t config;
    uint32_t baseAddr = g_dspiBaseAddr[self->instance];

    DSPI_SlaveGetDefaultConfig(&config);

    config.ctarConfig.cpol = kDSPI_ClockPolarityActiveLow;
    config.ctarConfig.cpha = kDSPI_ClockPhaseSecondEdge;

    s_dspiInfo.data_source = dspi_data_source, s_dspiInfo.data_sink = dspi_initial_data_sink,

    // Configure selected pin as spi peripheral interface
        self->pinmuxConfig(self->instance, kPinmuxType_Peripheral);
    DSPI_SlaveInit((SPI_Type *)baseAddr, &config);
    DSPI_EnableInterrupts((SPI_Type *)baseAddr, SPI_SR_TFFF_MASK | SPI_SR_RFDF_MASK | SPI_SR_TFUF_MASK);
    DSPI_SetSystemIRQ(self->instance, kPeripheralEnableIRQ);

    s_dspiIntialized[self->instance] = true;

    return kStatus_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : dspi_full_shutdown
 * Description   : DSPI slave full shutdown function
 *
 *END**************************************************************************/
void dspi_full_shutdown(const peripheral_descriptor_t *self)
{
    if (s_dspiIntialized[self->instance])
    {
        uint32_t baseAddr = g_dspiBaseAddr[self->instance];
        DSPI_SetSystemIRQ(self->instance, kPeripheralDisableIRQ);
        DSPI_Deinit((SPI_Type *)baseAddr);
        // Restore selected pin to default state to reduce IDD.
        self->pinmuxConfig(self->instance, kPinmuxType_Default);

        s_dspiIntialized[self->instance] = false;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : dspi_write
 * Description   : DSPI slave writing data function
 *
 *END**************************************************************************/
status_t dspi_write(const peripheral_descriptor_t *self, const uint8_t *buffer, uint32_t byteCount)
{
    s_dspiInfo.writeData = buffer;
    s_dspiInfo.bytesToTransfer = byteCount;

    while (s_dspiInfo.bytesToTransfer)
        ;

    return kStatus_Success;
}

void dspi_slave_irq_handler(uint32_t instance)
{
    uint32_t baseAddr = g_dspiBaseAddr[instance];

    /* catch tx fifo underflow conditions */
    if (DSPI_GetStatusFlags((SPI_Type *)baseAddr) & kDSPI_TxFifoUnderflowFlag)
    {
        DSPI_ClearStatusFlags((SPI_Type *)baseAddr, kDSPI_TxFifoUnderflowFlag);
    }

    /* Fill the tx fifo, where the fifo can be 1 entry or more */
    while (DSPI_GetStatusFlags((SPI_Type *)baseAddr) & kDSPI_TxFifoFillRequestFlag)
    {
        /* SPI transmit interrupt */
        uint32_t sourceWord = 0;
        uint8_t sourceWordTemp;

        /* get the first 8-bits of data */
        s_dspiInfo.data_source(&sourceWordTemp);
        sourceWord = sourceWordTemp;

        /* Finally, write the data to the DSPI data register */
        ((SPI_Type *)baseAddr)->PUSHR_SLAVE = sourceWord;

        /* try to clear TFFF by writing a one to it; it will not clear if TX FIFO not full */
        DSPI_ClearStatusFlags((SPI_Type *)baseAddr, kDSPI_TxFifoFillRequestFlag);
    }

    /* Fill the rx fifo, where the fifo can be 1 entry or more */
    while (DSPI_GetStatusFlags((SPI_Type *)baseAddr) & kDSPI_RxFifoDrainRequestFlag)
    {
        /* SPI receive interrupt, read the data from the DSPI data register */
        uint32_t readData = ((SPI_Type *)baseAddr)->POPR;

        /* clear the rx fifo drain request, needed for non-DMA applications as this flag
         * will remain set even if the rx fifo is empty. By manually clearing this flag, it
         * either remain clear if no more data is in the fifo, or it will set if there is
         * more data in the fifo.
         */
        DSPI_ClearStatusFlags((SPI_Type *)baseAddr, kDSPI_RxFifoDrainRequestFlag);

        /* Sink the first 8-bits */
        s_dspiInfo.data_sink((uint8_t)readData, instance);
    }
}

#if defined(SPI0)
void SPI0_IRQHandler(void)
{
    dspi_slave_irq_handler(0);
}
#endif

#if defined(SPI1)
void SPI1_IRQHandler(void)
{
    dspi_slave_irq_handler(1);
}
#endif

#if defined(SPI2)
void SPI2_IRQHandler(void)
{
    dspi_slave_irq_handler(2);
}
#endif

//! @}

#endif // BL_CONFIG_DSPI

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
