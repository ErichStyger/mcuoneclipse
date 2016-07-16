/**
 * \file i2c-board.c
 * \author Alexander Winiger (alexander.winiger@hslu.ch)
 * \date 15.09.2015
 * \brief Target board I2C driver implementation
 *
 */

#include "board.h"
#include "i2c-board.h"

/*----------------------- Local Definitions ------------------------------*/
/*!
 *  The value of the maximal timeout for I2C waiting loops 
 */
#define TIMEOUT_MAX                                 0x8000 

/*!
 * MCU I2C peripherals enumeration
 */
typedef enum {
    I2C_0 = (uint32_t) I2C0_BASE_PTR
} I2cName;

/*------------------------ Local Variables -------------------------------*/
I2cAddrSize I2cInternalAddrSize = I2C_ADDR_SIZE_8;

void I2cMcuInit(I2c_t *obj, PinNames scl, PinNames sda)
{

}

void I2cMcuFormat(I2c_t *obj, I2cMode mode, I2cDutyCycle dutyCycle, bool I2cAckEnable,
        I2cAckAddrMode AckAddrMode, uint32_t I2cFrequency)
{

}

void I2cMcuDeInit(I2c_t *obj)
{
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
    return SUCCESS;
}

uint8_t I2cMcuReadBuffer(I2c_t *obj, uint8_t deviceAddr, uint16_t addr, uint8_t *buffer,
        uint16_t size)
{
    return SUCCESS;
}

/* Implementation of I2C0 handler named in startup code. */
void I2C0_IRQHandler(void)
{

}
