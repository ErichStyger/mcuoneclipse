/*
 * Copyright (c) 2013-2015 Freescale Semiconductor, Inc.
 * Copyright 2016-2018 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "utilities/fsl_assert.h"
#include "bootloader/bl_context.h"
#include "bootloader/bl_irq_common.h"
#include "bootloader_common.h"
#include "packet/command_packet.h"
#include "fsl_i2c.h"
#include "fsl_device_registers.h"
#include "packet/serial_packet.h"

#if BL_CONFIG_I2C
//! @addtogroup i2c_peripheral
//! @{

////////////////////////////////////////////////////////////////////////////////
// Definitions
////////////////////////////////////////////////////////////////////////////////

// Allow the default to be overridden via the bootloader_config.h file.
#if !defined(BL_DEFAULT_I2C_SLAVE_ADDRESS)
//! @brief Default I2C slave address in 7-bit format.
#define BL_DEFAULT_I2C_SLAVE_ADDRESS (0x10)
//! @brief Secondary I2C slave address in 7-bit format.
#define BL_SECONDARY_I2C_SLAVE_ADDRESS (0x12)
#endif // BL_DEFAULT_I2C_SLAVE_ADDRESS

//! @brief Default width of glitches to filter in nanoseconds.
enum
{
    //! Width of glitches to filter in nanoseconds.
    kI2CGlitchFilterWidth_ns = 50
};

//! @brief Synchronization state between I2C ISR and read/write functions.
typedef struct _i2c_transfer_info
{
    const uint8_t *writeData;                                //!< The applications data to write
    volatile uint32_t bytesToTransfer;                       //!< The total number of bytes to be transmitted
    void (*data_source)(uint8_t *source_byte);               // !< Callback used to get byte to transmit.
    void (*data_sink)(uint8_t sink_byte, uint32_t instance); // !< Callback used to put received byte.
} i2c_transfer_info_t;

#define I2C_EMPTY_CHAR (0x00) //!< Empty character.

enum
{
    //! Max cycles supported to set glitch filter
    kI2CGlitchFilterMaxCycles = 31,
};

////////////////////////////////////////////////////////////////////////////////
// Prototypes
////////////////////////////////////////////////////////////////////////////////

//! @brief I2C slave poll for activity function
static bool i2c_poll_for_activity(const peripheral_descriptor_t *self);
//! @brief I2C slave init function
static status_t i2c_full_init(const peripheral_descriptor_t *self, serial_byte_receive_func_t function);
//! @brief I2C slave shutdown function
static void i2c_full_shutdown(const peripheral_descriptor_t *self);
//! @brief I2C slave internal init function
static void i2c_peripheral_init(uint32_t instance);
//! @brief I2C slave writing data function
status_t i2c_write(const peripheral_descriptor_t *self, const uint8_t *buffer, uint32_t byteCount);

static void i2c_initial_data_sink(uint8_t sink_byte, uint32_t instance);
static void i2c_data_sink(uint8_t sink_byte, uint32_t instance);
static void i2c_data_source(uint8_t *source_byte);
static void i2c_set_glitch_filter_width(I2C_Type *base, uint32_t busClock_Hz, uint32_t glitchWidth_ns);
static void i2c_SlaveIRQHandler(uint32_t instance);

////////////////////////////////////////////////////////////////////////////////
// Variables
////////////////////////////////////////////////////////////////////////////////

/*!
 * @brief I2C slave control interface information
 */
const peripheral_control_interface_t g_i2cControlInterface = {
    .pollForActivity = i2c_poll_for_activity, .init = i2c_full_init, .shutdown = i2c_full_shutdown, .pump = 0
};

/*!
 * @brief I2C slave byte interface information
 */
const peripheral_byte_inteface_t g_i2cByteInterface = {.init = NULL, .write = i2c_write };

//! @brief Global state for the I2C slave peripheral interface.
static i2c_transfer_info_t s_i2cInfo = {
    .writeData = 0, .bytesToTransfer = 0, .data_source = i2c_data_source, .data_sink = i2c_initial_data_sink
};

//! @brief Global state for the I2C slave peripheral interface.
static bool s_i2cActivity[FSL_FEATURE_SOC_I2C_COUNT] = { false };
const static uint32_t g_i2cBaseAddr[] = I2C_BASE_ADDRS;
static bool s_i2cIntialized[FSL_FEATURE_SOC_I2C_COUNT] = { false };

/*!
 * @brief I2C slave receiving data call back function
 */
static serial_byte_receive_func_t s_i2c_app_data_sink_callback;

////////////////////////////////////////////////////////////////////////////////
// Code
////////////////////////////////////////////////////////////////////////////////

#if !defined(BL_FEATURE_I2C_OPTIMIZE) || USE_ONLY_I2C(0)
//! @brief Implementation of I2C0 handler named in startup code.
//!
//! Passes instance to generic I2C IRQ handler.
void I2C0_IRQHandler(void)
{
    i2c_SlaveIRQHandler(0);
}
#endif // !defined(BL_FEATURE_I2C_OPTIMIZE) || USE_ONLY_I2C(0)

#if (!defined(BL_FEATURE_I2C_OPTIMIZE) || USE_ONLY_I2C(1)) && (FSL_FEATURE_SOC_I2C_COUNT > 1)
//! @brief Implementation of I2C1 handler named in startup code.
//!
//! Passes instance to generic I2C IRQ handler.
void I2C1_IRQHandler(void)
{
    i2c_SlaveIRQHandler(1);
}
#endif // (!defined(BL_FEATURE_I2C_OPTIMIZE) || USE_ONLY_I2C(1)) && (FSL_FEATURE_SOC_I2C_COUNT > 1)

/*FUNCTION**********************************************************************
 *
 * Function Name : i2c_poll_for_activity
 * Description   : Polling for I2C slave activities
 *
 *END**************************************************************************/
bool i2c_poll_for_activity(const peripheral_descriptor_t *self)
{
    return s_i2cActivity[self->instance];
}

/*FUNCTION**********************************************************************
 *
 * Function Name : i2c_data_source
 * Description   : I2C slave sending data function
 *
 *END**************************************************************************/
static void i2c_data_source(uint8_t *source_byte)
{
    assert(source_byte);

    if (s_i2cInfo.bytesToTransfer)
    {
        *source_byte = *s_i2cInfo.writeData++;
        s_i2cInfo.bytesToTransfer--;
    }
    else
    {
        *source_byte = 0;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : i2c_data_sink
 * Description   : I2C slave receiving data function
 *
 *END**************************************************************************/
static void i2c_data_sink(uint8_t sink_byte, uint32_t instance)
{
    s_i2c_app_data_sink_callback(sink_byte);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : i2c_initial_data_sink
 * Description   : I2C slave receiving first byte data function
 *
 *END**************************************************************************/
static void i2c_initial_data_sink(uint8_t sink_byte, uint32_t instance)
{
    if (sink_byte == kFramingPacketStartByte)
    {
        s_i2cActivity[instance] = true;
        s_i2cInfo.data_sink = i2c_data_sink;
        s_i2c_app_data_sink_callback(sink_byte);
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : i2c_peripheral_init
 * Description   : I2C slave Internal init function
 *
 *END**************************************************************************/
void i2c_peripheral_init(uint32_t instance)
{
    uint32_t baseAddr = g_i2cBaseAddr[instance];
    i2c_slave_config_t i2cSlaveConfig;

    I2C_SlaveGetDefaultConfig(&i2cSlaveConfig);
    i2cSlaveConfig.slaveAddress = BL_DEFAULT_I2C_SLAVE_ADDRESS;

    // Read the address from the configuration field. If it is not set, i.e. 0xff,
    // use the default address.
    uint8_t slaveAddress = g_bootloaderContext.propertyInterface->store->configurationData.i2cSlaveAddress;
    if (slaveAddress != 0xff)
    {
        i2cSlaveConfig.slaveAddress = slaveAddress;
    }
#if BL_FEATURE_SECONDARY_I2C_SLAVE_ADDRESS
    else if (is_secondary_i2c_slave_address_enabled())
    {
        i2cSlaveConfig.slaveAddr = BL_SECONDARY_I2C_SLAVE_ADDRESS;
    }
#endif // BL_FEATURE_SECONDARY_I2C_SLAVE_ADDRESS

    I2C_SlaveInit((I2C_Type *)baseAddr, &i2cSlaveConfig, get_bus_clock());
    I2C_Enable((I2C_Type *)baseAddr, true);
    I2C_EnableInterrupts((I2C_Type *)baseAddr, kI2C_GlobalInterruptEnable);
    i2c_set_glitch_filter_width((I2C_Type *)baseAddr, get_bus_clock(), kI2CGlitchFilterWidth_ns);

    I2C_SetSystemIRQ(instance, kPeripheralEnableIRQ);

    s_i2cInfo.data_sink = i2c_initial_data_sink;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : i2c_full_init
 * Description   : I2C slave full init function
 *
 *END**************************************************************************/
status_t i2c_full_init(const peripheral_descriptor_t *self, serial_byte_receive_func_t function)
{
    s_i2c_app_data_sink_callback = function;

    // Configure selected pin as i2c peripheral interface
    self->pinmuxConfig(self->instance, kPinmuxType_Peripheral);

    i2c_peripheral_init(self->instance);

    s_i2cIntialized[self->instance] = true;

    return kStatus_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : i2c_full_shutdown
 * Description   : I2C slave full shutdown function
 *
 *END**************************************************************************/
void i2c_full_shutdown(const peripheral_descriptor_t *self)
{
    if (s_i2cIntialized[self->instance])
    {
        uint32_t baseAddr = g_i2cBaseAddr[self->instance];
        I2C_SetSystemIRQ(self->instance, kPeripheralDisableIRQ);
        I2C_Enable((I2C_Type *)baseAddr, false);
        I2C_SlaveDeinit((I2C_Type *)baseAddr);

        // Restore selected pin to default state to reduce IDD.
        self->pinmuxConfig(self->instance, kPinmuxType_Default);

        s_i2cIntialized[self->instance] = false;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : i2c_write
 * Description   : I2C slave writing data function
 *
 *END**************************************************************************/
status_t i2c_write(const peripheral_descriptor_t *self, const uint8_t *buffer, uint32_t byteCount)
{
    s_i2cInfo.writeData = buffer;
    s_i2cInfo.bytesToTransfer = byteCount;

    while (s_i2cInfo.bytesToTransfer)
        ;

    return kStatus_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : i2c_DummyRead
 * Description   : I2C dummy read
 *
 *END**************************************************************************/
static uint8_t i2c_DummyRead(volatile I2C_Type *base)
{
    return base->D;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : i2c_SlaveIRQHandler
 * Description   : I2C slave bootloader interrupt handler
 *
 *END**************************************************************************/
static void i2c_SlaveIRQHandler(uint32_t instance)
{
    uint16_t status;
    I2C_Type *base = (I2C_Type *)g_i2cBaseAddr[instance];

    status = I2C_SlaveGetStatusFlags(base);

    bool doTransmit = false;

    /* Clear the interrupt flag*/
    base->S = (kI2C_IntPendingFlag | kI2C_ArbitrationLostFlag) & status;

    if ((status & I2C_S_ARBL_MASK) && (!(status & I2C_S_IAAS_MASK)))
    {
        // ArbitrationLost and not AddressedAsSlave
    }
    else if (status & I2C_S_IAAS_MASK) // AddressedAsSlave
    {
        if (status & I2C_S_SRW_MASK) // Master read from Slave. Slave transmit.
        {
            // Switch to TX mode
            base->C1 |= I2C_C1_TX_MASK;

            doTransmit = true;
        }
        else // Master write to Slave. Slave receive.
        {
            // Switch to RX mode.
            base->C1 &= ~I2C_C1_TX_MASK;

            // Dummy read character.
            i2c_DummyRead(base);
        }
    }
    else // not AddressedAsSlave
    {
        if (base->C1 & I2C_C1_TX_MASK) // Transmit.
        {
            if (status & I2C_S_RXAK_MASK) // No ACK from receiver.
            {
                // Switch to RX mode.
                base->C1 &= ~I2C_C1_TX_MASK;

                // Dummy read character.
                i2c_DummyRead(base);
            }
            else // ACK from receiver.
            {
                // DO TRANSMIT
                doTransmit = true;
            }
        }
        else // Receive.
        {
            // Get byte from data register.
            uint8_t sink_byte = base->D;

            s_i2cInfo.data_sink(sink_byte, instance);
        }
    }

    if (doTransmit)
    {
        uint8_t source_byte = I2C_EMPTY_CHAR;

        s_i2cInfo.data_source(&source_byte);

        // Store char to transmit register.
        base->D = source_byte;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : i2c_set_glitch_filter_width
 * Description   : I2C slave set glitch filter width
 *
 *END**************************************************************************/
void i2c_set_glitch_filter_width(I2C_Type *base, uint32_t busClock_Hz, uint32_t glitchWidth_ns)
{
#if USE_ONLY_I2C(0)
    instance = 0;
#elif USE_ONLY_I2C(1)
    instance = 1;
#endif // USE_ONLY_I2C(0)

    uint32_t busCycle_ns = 1000000 / (busClock_Hz / 1000);

    // Search for the cycle count just below the desired glitch width.
    uint32_t cycles = 0;
    while (((cycles + 1) * busCycle_ns) < glitchWidth_ns)
    {
        ++cycles;
    }

    // If we end up with zero cycles, then set the filter to a single cycle unless the
    // bus clock is greater than 10x the desired glitch width.
    if ((cycles == 0) && (busCycle_ns <= (glitchWidth_ns * 10)))
    {
        cycles = 1;
    }
    // If the cycles is greater the max cycles supported to set glitch filter,
    // then cycles should be equal to max cycles
    else if (cycles > kI2CGlitchFilterMaxCycles)
    {
        cycles = kI2CGlitchFilterMaxCycles;
    }

    uint8_t temp = base->FLT;
    base->FLT = (~I2C_FLT_FLT_MASK & temp) | cycles;
}

//! @}

#endif // BL_CONFIG_I2C
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
