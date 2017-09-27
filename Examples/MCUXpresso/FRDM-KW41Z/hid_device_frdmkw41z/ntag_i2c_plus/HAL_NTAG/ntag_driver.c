/*
 * Copyright (c) 2016, NXP Semiconductor
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
 * o Neither the name of NXP Semiconductor nor the names of its
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
 *
 */
/***********************************************************************/
/* INCLUDES                                                            */
/***********************************************************************/
#include "HAL_timer_driver.h"
#include "ntag_driver_intern.h"
#include "HAL_I2C_driver.h"
/***********************************************************************/
/* DEFINES                                                             */
/***********************************************************************/
#undef NTAG_DEVICE_LIST_BEGIN
#undef NTAG_DEVICE_ENTRY
#undef NTAG_DEVICE_LIST_END

#define NTAG_DEVICE_LIST_BEGIN struct NTAG_DEVICE ntag_device_list[NTAG_ID_MAX_DEVICES] = {
#ifdef HAVE_NTAG_INTERRUPT
#define NTAG_DEVICE_ENTRY(label, i2c_address, isr)                  \
    {                                                               \
        NTAG_CLOSED, HAL_I2C_INVALID_HANDLE, i2c_address, isr, {0}, \
        {                                                           \
            0                                                       \
        }                                                           \
    }
#else
#define NTAG_DEVICE_ENTRY(label, i2c_address, isr)             \
    {                                                          \
        NTAG_CLOSED, HAL_I2C_INVALID_HANDLE, i2c_address, {0}, \
        {                                                      \
            0                                                  \
        }                                                      \
    }
#endif

#define NTAG_DEVICE_LIST_END \
    }                        \
    ;

/***********************************************************************/
/* GLOBAL VARIABLES                                                    */
/***********************************************************************/
/* second include of device list for generation of ntag_device_list array */
NTAG_DEVICE_LIST_BEGIN
#include "ntag_device_list.h"
NTAG_DEVICE_LIST_END
/***********************************************************************/
/* GLOBAL PUBLIC FUNCTIONS                                             */
/***********************************************************************/

BOOL NTAG_WaitForFDPinState(NTAG_HANDLE_T ntag, NTAG_FD_STATE_T state, uint32_t timeout_ms)
{
    switch (state)
    {
        case NTAG_FD_PIN_STATE_HI:
            HAL_ISR_RegisterCallback(ntag->isr, ISR_LEVEL_HI, NULL, NULL);
            return HAL_ISR_SleepWithTimeout(ntag->isr, timeout_ms);
        case NTAG_FD_PIN_STATE_LO:
            HAL_ISR_RegisterCallback(ntag->isr, ISR_LEVEL_LO, NULL, NULL);
            return HAL_ISR_SleepWithTimeout(ntag->isr, timeout_ms);
        default:
            break;
    }
    return NTAG_ERROR_INVALID_PARAM;
}

NTAG_HANDLE_T NTAG_InitDevice(NTAG_ID_T ntag_id, HAL_I2C_HANDLE_T i2cbus)
{
    if (ntag_id < NTAG_ID_MAX_DEVICES)
    {
        if (ntag_device_list[ntag_id].status == NTAG_CLOSED)
        {
            ntag_device_list[ntag_id].i2cbus = i2cbus;
            ntag_device_list[ntag_id].status = NTAG_OK;

            return &ntag_device_list[ntag_id];
        }
    }
    return NTAG_INVALID_HANDLE;
}

void NTAG_CloseDevice(NTAG_HANDLE_T ntag)
{
    if (ntag)
    {
        ntag->i2cbus = HAL_I2C_INVALID_HANDLE;
        ntag->status = NTAG_CLOSED;
    }
}

BOOL NTAG_ReadBytes(NTAG_HANDLE_T ntag, uint16_t address, uint8_t *bytes, uint16_t len)
{
    uint16_t bytes_read = 0;

    if (ntag->status == NTAG_CLOSED)
        return TRUE;

    ntag->status = NTAG_OK;

    while (bytes_read < len)
    {
        uint8_t current_block = (address + bytes_read) / NTAG_I2C_BLOCK_SIZE;
        uint8_t begin = (address + bytes_read) % NTAG_I2C_BLOCK_SIZE;
        uint8_t current_len = MIN(len - bytes_read, NTAG_I2C_BLOCK_SIZE - begin);

        if (current_len < NTAG_I2C_BLOCK_SIZE)
        {
            size_t i = 0;

            /* read block into ntag->rx_buffer only */
            if (NTAG_ReadBlock(ntag, current_block, NULL, 0))
                break;

            /* modify rx_buffer */
            for (i = 0; i < current_len; i++)
                bytes[bytes_read + i] = ntag->rx_buffer[RX_START + begin + i];
        }
        else
        {
            /* full block read */
            if (NTAG_ReadBlock(ntag, current_block, bytes + bytes_read, NTAG_I2C_BLOCK_SIZE))
                break;
        }

        bytes_read += current_len;
    }
    return ntag->status;
}

BOOL NTAG_WriteBytes(NTAG_HANDLE_T ntag, uint16_t address, const uint8_t *bytes, uint16_t len)
{
    uint16_t bytes_written = 0;

    if (ntag->status == NTAG_CLOSED)
        return TRUE;

    ntag->status = NTAG_OK;

    while (bytes_written < len)
    {
        uint8_t current_block = (address + bytes_written) / NTAG_I2C_BLOCK_SIZE;
        uint8_t begin = (address + bytes_written) % NTAG_I2C_BLOCK_SIZE;
        uint8_t current_len = MIN(len - bytes_written, NTAG_I2C_BLOCK_SIZE - begin);

        if (current_len < NTAG_I2C_BLOCK_SIZE)
        {
            size_t i = 0;

            /* read block into ntag->rx_buffer only */
            if (NTAG_ReadBlock(ntag, current_block, NULL, 0))
                break;

            /* check if it is the first Block(0x00) and not the I2C Addr */
            /* be careful with writing of first byte in management block */
            /* the byte contains part of the serial number on read but   */
            /* on write the I2C address of the device can be modified    */
            if (0x00 == current_block && NTAG_MEM_ADRR_I2C_ADDRESS < begin)
                ntag->rx_buffer[RX_START + 0] = ntag->address;

            /* modify rx_buffer */
            for (i = 0; i < current_len; i++)
                ntag->rx_buffer[RX_START + begin + i] = bytes[bytes_written + i];

            /* writeback modified buffer */
            if (NTAG_WriteBlock(ntag, current_block, ntag->rx_buffer + RX_START, NTAG_I2C_BLOCK_SIZE))
                break;
        }
        else
        {
            /* full block write */
            if (NTAG_WriteBlock(ntag, current_block, bytes + bytes_written, NTAG_I2C_BLOCK_SIZE))
                break;
        }

        bytes_written += current_len;
    }

    return ntag->status;
}

BOOL NTAG_ReadRegister(NTAG_HANDLE_T ntag, uint8_t reg, uint8_t *val)
{
    ntag->tx_buffer[TX_START + 0] = NTAG_MEM_BLOCK_SESSION_REGS;
    ntag->tx_buffer[TX_START + 1] = reg;

    /* send block number */
    if (HAL_I2C_OK != HAL_I2C_SendBytes(ntag->i2cbus, ntag->address, ntag->tx_buffer, 2))
    {
        ntag->status = NTAG_ERROR_TX_FAILED;
        return TRUE;
    }

    /* receive bytes */
    if (HAL_I2C_OK != HAL_I2C_RecvBytes(ntag->i2cbus, ntag->address, ntag->rx_buffer, 1))
    {
        ntag->status = NTAG_ERROR_RX_FAILED;
        return TRUE;
    }

    *val = ntag->rx_buffer[RX_START + 0];
    return FALSE;
}

BOOL NTAG_WriteRegister(NTAG_HANDLE_T ntag, uint8_t reg, uint8_t mask, uint8_t val)
{
    ntag->tx_buffer[TX_START + 0] = NTAG_MEM_BLOCK_SESSION_REGS;
    ntag->tx_buffer[TX_START + 1] = reg;
    ntag->tx_buffer[TX_START + 2] = mask;
    ntag->tx_buffer[TX_START + 3] = val;

    if (HAL_I2C_OK != HAL_I2C_SendBytes(ntag->i2cbus, ntag->address, ntag->tx_buffer, 4))
    {
        ntag->status = NTAG_ERROR_TX_FAILED;
        return TRUE;
    }

    return FALSE;
}

BOOL NTAG_ReadConfiguration(NTAG_HANDLE_T ntag, uint8_t reg, uint8_t *val)
{
#ifdef NTAG_2k
    uint8_t config = NTAG_MEM_BLOCK_CONFIGURATION_2k;
#elif NTAG_1k
    uint8_t config = NTAG_MEM_BLOCK_CONFIGURATION_1k;
#endif

    uint8_t I2C_Buf[NTAG_I2C_BLOCK_SIZE];
    if (NTAG_ReadBlock(ntag, config, I2C_Buf, NTAG_I2C_BLOCK_SIZE))
        return NTAG_ERR_COMMUNICATION;

    *val = I2C_Buf[reg];
    return NTAG_ERR_OK;
}

BOOL NTAG_WriteConfiguration(NTAG_HANDLE_T ntag, uint8_t reg, uint8_t mask, uint8_t val)
{
#ifdef NTAG_2k
    uint8_t config = NTAG_MEM_BLOCK_CONFIGURATION_2k;
#elif NTAG_1k
    uint8_t config = NTAG_MEM_BLOCK_CONFIGURATION_1k;
#endif

    uint8_t I2C_Buf[NTAG_I2C_BLOCK_SIZE];
    if (NTAG_ReadBlock(ntag, config, I2C_Buf, NTAG_I2C_BLOCK_SIZE))
        return NTAG_ERR_COMMUNICATION;

    // Clear all other bits of the val
    val = val & mask;

    // Clear specific bit in the Buffer
    I2C_Buf[reg] = I2C_Buf[reg] & ~mask;

    // write bits in the Buffer
    I2C_Buf[reg] = I2C_Buf[reg] | val;

    if (NTAG_WriteBlock(ntag, config, I2C_Buf, NTAG_I2C_BLOCK_SIZE))
        return NTAG_ERR_COMMUNICATION;

    return NTAG_ERR_OK;
}

NTAG_STATUS_T NTAG_GetLastError(NTAG_HANDLE_T ntag)
{
    return ntag->status;
}

/***********************************************************************/
/* GLOBAL PRIVATE FUNCTIONS                                            */
/***********************************************************************/
BOOL NTAG_ReadBlock(NTAG_HANDLE_T ntag, uint8_t block, uint8_t *bytes, uint8_t len)
{
    size_t i = 0;

    ntag->tx_buffer[TX_START] = block;

    /* send block number */
    if (HAL_I2C_OK != HAL_I2C_SendBytes(ntag->i2cbus, ntag->address, ntag->tx_buffer, 1))
    {
        ntag->status = NTAG_ERROR_TX_FAILED;
        return TRUE;
    }

    /* receive bytes */
    if (HAL_I2C_OK != HAL_I2C_RecvBytes(ntag->i2cbus, ntag->address, ntag->rx_buffer, NTAG_I2C_BLOCK_SIZE))
    {
        ntag->status = NTAG_ERROR_RX_FAILED;
        return TRUE;
    }

    len = MIN(len, NTAG_I2C_BLOCK_SIZE);

    /* write to bytes buffer */
    for (i = 0; i < len; i++)
        bytes[i] = ntag->rx_buffer[RX_START + i];

    return FALSE;
}

BOOL NTAG_WriteBlock(NTAG_HANDLE_T ntag, uint8_t block, const uint8_t *bytes, uint8_t len)
{
    uint8_t ns_reg = 0;
    uint32_t timeout = NTAG_MAX_WRITE_DELAY_MS / 5 + 1;
    size_t i = 0;

    ntag->tx_buffer[TX_START] = block;

    len = MIN(len, NTAG_I2C_BLOCK_SIZE);

    /* copy len bytes */
    for (i = 0; i < len; i++)
        ntag->tx_buffer[TX_START + i + 1] = bytes[i];

    /* zero rest of the buffer */
    for (i = len; i < NTAG_I2C_BLOCK_SIZE; i++)
        ntag->tx_buffer[TX_START + i + 1] = 0;

    /* send block number */
    if (HAL_I2C_OK != HAL_I2C_SendBytes(ntag->i2cbus, ntag->address, ntag->tx_buffer, NTAG_I2C_BLOCK_SIZE + 1))
    {
        ntag->status = NTAG_ERROR_TX_FAILED;
        return TRUE;
    }

    /* do not wait for completion when writing SRAM */
    if (block >= NTAG_MEM_BLOCK_START_SRAM && block < NTAG_MEM_BLOCK_START_SRAM + NTAG_MEM_SRAM_BLOCKS)
        return ntag->status;

    /* wait for completion */
    do
    {
        HAL_Timer_delay_ms(5);
        if (NTAG_ReadRegister(ntag, NTAG_MEM_OFFSET_NS_REG, &ns_reg))
            break;
        timeout--;
    } while (timeout && ns_reg & NTAG_NS_REG_MASK_EEPROM_WR_BUSY);

    if (0 == timeout)
        ntag->status = NTAG_ERROR_WRITE_TIMEOUT;

    return ntag->status;
}
