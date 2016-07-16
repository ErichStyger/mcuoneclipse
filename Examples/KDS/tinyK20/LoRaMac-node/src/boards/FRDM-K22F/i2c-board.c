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
 *  The value of the maximal timeout for I2C waiting loops 
 */
#define TIMEOUT_MAX                                 0x8000 

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
#if 0
    obj->I2c = (I2C_TypeDef *) g_i2cBase[FXOS8700CQ_I2C_INSTANCE];

    GpioInit(&obj->Scl, scl, PIN_ALTERNATE_FCT, PIN_PUSH_PULL, PIN_PULL_UP, 0);
    GpioInit(&obj->Sda, sda, PIN_ALTERNATE_FCT, PIN_PUSH_PULL, PIN_PULL_UP, 0);

    /* Enable clock for I2C.*/
    CLOCK_SYS_EnableI2cClock (FXOS8700CQ_I2C_INSTANCE);

    /* Initialize peripheral to known state.*/
    I2C_HAL_Init(obj->I2c);

    /* Enable module.*/
    I2C_HAL_Enable(obj->I2c);
#else
    if (obj->I2c->instance < 0 || obj->I2c->instance > I2C_INSTANCE_COUNT) return;

    GpioInit(&obj->Scl, scl, PIN_ALTERNATE_FCT, PIN_OPEN_DRAIN, PIN_PULL_UP, 0);
    GpioInit(&obj->Sda, sda, PIN_ALTERNATE_FCT, PIN_OPEN_DRAIN, PIN_PULL_UP, 0);

    I2C_DRV_MasterInit(obj->I2c->instance, &obj->I2c->state);
#endif
}

void I2cMcuFormat(I2c_t *obj, I2cMode mode, I2cDutyCycle dutyCycle, bool I2cAckEnable,
        I2cAckAddrMode AckAddrMode, uint32_t I2cFrequency)
{
#if 0
    /* Get the current bus clock.*/
    uint32_t i2cClockFreq = CLOCK_SYS_GetI2cFreq(FXOS8700CQ_I2C_INSTANCE);

    I2C_HAL_SetBaudRate(obj->I2c, i2cClockFreq, I2cFrequency, NULL);
#else
    obj->I2c->slave.baudRate_kbps = (I2cFrequency / 1000);
#endif
}

void I2cMcuDeInit(I2c_t *obj)
{
#if 0
    /* Disable module.*/
    I2C_HAL_Disable(obj->I2c);

    /* Disable clock for I2C.*/
    CLOCK_SYS_DisableI2cClock (FXOS8700CQ_I2C_INSTANCE);
#else
    I2C_DRV_MasterDeinit(obj->I2c->instance);
#endif

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
#if 0
    if (I2C_HAL_MasterSendDataPolling(obj->I2c, deviceAddr, (const uint8_t*) &addr, 1, buffer,
                    size)) return FAIL;
#else
#endif
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
#if 0
    if (I2C_HAL_MasterReceiveDataPolling(obj->I2c, deviceAddr, NULL, 0, buffer, size) != kStatus_I2C_Success) return FAIL;
#else
    /* Adjust address */
    if (obj->I2c->slave.address != deviceAddr) obj->I2c->slave.address = deviceAddr;
    /* Read data */
    if (I2C_DRV_MasterReceiveDataBlocking(obj->I2c->instance, &obj->I2c->slave,
            (const uint8_t*) &addr, 1, buffer, size, 200) != kStatus_I2C_Success) return FAIL;
#endif

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
