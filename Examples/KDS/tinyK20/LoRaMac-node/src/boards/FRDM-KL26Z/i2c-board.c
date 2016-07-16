/**
 * \file i2c-board.c
 * \author Alexander Winiger (alexander.winiger@hslu.ch)
 * \date 15.09.2015
 * \brief Target board I2C driver implementation
 *
 */

#include "board.h"
#include "i2c-board.h"
#include "fsl_i2c_master_driver.h"
#include "fsl_i2c_shared_function.h"
#include "fsl_clock_manager.h"
#include "fsl_interrupt_manager.h"

/*----------------------- Local Definitions ------------------------------*/

/*!
 * MCU I2C peripherals enumeration
 */
typedef enum {
    I2C_0 = (uint32_t) I2C0_BASE, I2C_1 = (uint32_t) I2C1_BASE
} I2cName;

/*------------------------ Local Variables -------------------------------*/
I2cAddrSize I2cInternalAddrSize = I2C_ADDR_SIZE_8;

void I2cMcuInit(I2c_t *obj, PinNames scl, PinNames sda)
{
    if (obj->I2c->instance < 0 || obj->I2c->instance > I2C_INSTANCE_COUNT) return;

    GpioInit(&obj->Scl, scl, PIN_ALTERNATE_FCT, PIN_OPEN_DRAIN, PIN_PULL_UP, 0);
    GpioInit(&obj->Sda, sda, PIN_ALTERNATE_FCT, PIN_OPEN_DRAIN, PIN_PULL_UP, 0);

    I2C_DRV_MasterInit(obj->I2c->instance, &obj->I2c->state);
}

void I2cMcuFormat(I2c_t *obj, I2cMode mode, I2cDutyCycle dutyCycle, bool I2cAckEnable,
        I2cAckAddrMode AckAddrMode, uint32_t I2cFrequency)
{
    obj->I2c->slave.baudRate_kbps = (I2cFrequency / 1000);
}

void I2cMcuDeInit(I2c_t *obj)
{
    I2C_DRV_MasterDeinit(obj->I2c->instance);

    GpioInit(&obj->Scl, obj->Scl.pin, PIN_ANALOGIC, PIN_PUSH_PULL, PIN_NO_PULL, 0);
    GpioInit(&obj->Sda, obj->Sda.pin, PIN_ANALOGIC, PIN_PUSH_PULL, PIN_NO_PULL, 0);
}

void I2cSetAddrSize(I2c_t *obj, I2cAddrSize addrSize)
{
    I2cInternalAddrSize = addrSize;
}

uint8_t I2cMcuWriteBuffer(I2c_t *obj, uint8_t deviceAddr, uint16_t addr, uint8_t *buffer,
        uint16_t size)
{
    /* Adjust address */
    if (obj->I2c->slave.address != deviceAddr) obj->I2c->slave.address = deviceAddr;
    /* Write data */
    if (I2C_DRV_MasterSendDataBlocking(obj->I2c->instance, &obj->I2c->slave, (const uint8_t*) &addr,
            1, buffer, size, 200) != kStatus_I2C_Success) return FAIL;
    return SUCCESS;
}

uint8_t I2cMcuReadBuffer(I2c_t *obj, uint8_t deviceAddr, uint16_t addr, uint8_t *buffer,
        uint16_t size)
{
    /* Adjust address */
    if (obj->I2c->slave.address != deviceAddr) obj->I2c->slave.address = deviceAddr;
    /* Read data */
    if (I2C_DRV_MasterReceiveDataBlocking(obj->I2c->instance, &obj->I2c->slave,
            (const uint8_t*) &addr, 1, buffer, size, 200) != kStatus_I2C_Success) return FAIL;

    return SUCCESS;
}

/* Implementation of I2C0 handler named in startup code. */
void I2C0_IRQHandler(void)
{
    I2C_DRV_IRQHandler (I2C0_IDX);
}

/* Implementation of I2C1 handler named in startup code. */
void I2C1_IRQHandler(void)
{
    I2C_DRV_IRQHandler (I2C1_IDX);
}
