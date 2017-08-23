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
#include "HAL_I2C_driver.h"
#include "HAL_timer_driver.h"
#include "ntag_bridge.h"

/***********************************************************************/
/* DEFINES                                                             */
/***********************************************************************/

/***********************************************************************/
/* GLOBAL VARIABLES                                                    */
/***********************************************************************/

/***********************************************************************/
/* LOCAL VARIABLES                                                     */
/***********************************************************************/

/***********************************************************************/
/* GLOBAL FUNCTIONS                                                    */
/***********************************************************************/
//---------------------------------------------------------------------
BOOL NTAG_WaitForEvent(NTAG_HANDLE_T ntag, NTAG_EVENT_T event, uint32_t timeout_ms, BOOL set_fd_pin_function)
{
    uint8_t reg = 0;
    uint8_t reg_mask = 0;
    size_t i = 0;

    switch (event)
    {
#ifdef HAVE_NTAG_INTERRUPT

        case NTAG_EVENT_RF_FIELD_NOT_PRESENT_INTERRUPT:
            if (set_fd_pin_function)
                NTAG_SetFDOffFunction(ntag, RF_SWITCHED_OFF_00b);
            break;

        case NTAG_EVENT_HALT_STATE:
            if (set_fd_pin_function)
                NTAG_SetFDOffFunction(ntag, HALT_OR_RF_SWITCHED_OFF_01b);
            break;

        case NTAG_EVENT_NDEF_DATA_READ_INTERRUPT:
            if (set_fd_pin_function)
                NTAG_SetFDOffFunction(ntag, LAST_NDEF_BLOCK_READ_OR_RF_SWITCHED_OFF_10b);
            break;

        // -------- Low Interrupts -----------
        case NTAG_EVENT_FD_PIN_LO_INTERRUPT:
            return NTAG_WaitForFDPinState(ntag, NTAG_FD_PIN_STATE_LO, timeout_ms);

        case NTAG_EVENT_RF_FIELD_PRESENT_INTERRUPT:
            if (set_fd_pin_function)
                NTAG_SetFDOnFunction(ntag, RF_SWITCHED_ON_00b);
            break;

        case NTAG_EVENT_SoF:
            if (set_fd_pin_function)
                NTAG_SetFDOnFunction(ntag, FIRST_VALID_SoF_01b);
            break;

        case NTAG_EVENT_SELECT:
            if (set_fd_pin_function)
                NTAG_SetFDOnFunction(ntag, SELECTION_OF_TAG_10b);
            break;

        case NTAG_EVENT_RF_WROTE_SRAM_INTERRUPT:
        case NTAG_EVENT_RF_READ_SRAM_INTERRUPT:
            if (set_fd_pin_function)
            {
                NTAG_SetFDOffFunction(ntag, I2C_LAST_DATA_READ_OR_WRITTEN_OR_RF_SWITCHED_OFF_11b);
                NTAG_SetFDOnFunction(ntag, DATA_READY_BY_I2C_OR_DATA_READ_BY_RF_11b);
            }
            break;

#endif
        case NTAG_EVENT_RF_FIELD_PRESENT_POLLED:
        case NTAG_EVENT_RF_FIELD_NOT_PRESENT_POLLED:
            reg_mask = NTAG_NS_REG_MASK_RF_FIELD_PRESENT;
            break;
        case NTAG_EVENT_RF_READ_SRAM_POLLED:
            reg_mask = NTAG_NS_REG_MASK_SRAM_RF_READY;
            break;
        case NTAG_EVENT_RF_WROTE_SRAM_POLLED:
            reg_mask = NTAG_NS_REG_MASK_SRAM_I2C_READY;
            break;
        case NTAG_EVENT_NDEF_DATA_READ_POLLED:
            reg_mask = NTAG_NS_REG_MASK_NDEF_DATA_READ;
            break;
        default:
            return TRUE;
    }

    switch (event)
    {
        // -------- High Interrupts -----------
        case NTAG_EVENT_RF_FIELD_NOT_PRESENT_INTERRUPT:
        case NTAG_EVENT_HALT_STATE:
        case NTAG_EVENT_NDEF_DATA_READ_INTERRUPT:
            return NTAG_WaitForFDPinState(ntag, NTAG_FD_PIN_STATE_HI, timeout_ms);

        // -------- Low Interrupts -----------
        case NTAG_EVENT_FD_PIN_LO_INTERRUPT:
        case NTAG_EVENT_RF_FIELD_PRESENT_INTERRUPT:
        case NTAG_EVENT_SoF:
        case NTAG_EVENT_SELECT:
        case NTAG_EVENT_RF_WROTE_SRAM_INTERRUPT:
        case NTAG_EVENT_RF_READ_SRAM_INTERRUPT:
            return NTAG_WaitForFDPinState(ntag, NTAG_FD_PIN_STATE_LO, timeout_ms);

        default:
            break;
    }

    // Get first register read
    NTAG_ReadRegister(ntag, NTAG_MEM_OFFSET_NS_REG, &reg);
    switch (event)
    {
        // wait for 1 on bit position
        case NTAG_EVENT_RF_FIELD_PRESENT_POLLED:
        case NTAG_EVENT_RF_WROTE_SRAM_POLLED:
        case NTAG_EVENT_NDEF_DATA_READ_POLLED:
            for (/* */; i < timeout_ms && !(reg & reg_mask); i++)
            {
                HAL_Timer_delay_ms(1);
                NTAG_ReadRegister(ntag, NTAG_MEM_OFFSET_NS_REG, &reg);
            }
            return !(reg & reg_mask);

        // wait for 0 on bit position
        case NTAG_EVENT_RF_FIELD_NOT_PRESENT_POLLED:
        case NTAG_EVENT_RF_READ_SRAM_POLLED:
            for (/* */; i < timeout_ms && (reg & reg_mask); i++)
            {
                HAL_Timer_delay_ms(1);
                NTAG_ReadRegister(ntag, NTAG_MEM_OFFSET_NS_REG, &reg);
            }
            return (reg & reg_mask);

        default:
            break;
    }

    return TRUE;
}

//---------------------------------------------------------------------
BOOL NTAG_SetI2CRstOnOff(NTAG_HANDLE_T ntag, BOOL on)
{
    uint8_t val = 0;
    if (on)
        val = NTAG_NC_REG_MASK_I2C_RST_ON_OFF;
    else
        val = 0;

    return NTAG_WriteRegister(ntag, NTAG_MEM_OFFSET_NC_REG, NTAG_NC_REG_MASK_I2C_RST_ON_OFF, val);
}

//---------------------------------------------------------------------
BOOL NTAG_GetI2CRstOnOff(NTAG_HANDLE_T ntag, BOOL *on)
{
    uint8_t val;
    NTAG_ReadRegister(ntag, NTAG_MEM_OFFSET_NC_REG, &val);

    *on = ((val & NTAG_NC_REG_MASK_I2C_RST_ON_OFF) != 0);
    return NTAG_ERR_OK;
}

//---------------------------------------------------------------------
BOOL NTAG_SetRFConfigurationWrite(NTAG_HANDLE_T ntag)
{
    return NTAG_WriteConfiguration(ntag, NTAG_MEM_OFFSET_REG_LOCK, 0x01, 0x01);
}

//---------------------------------------------------------------------
BOOL NTAG_GetRFConfigurationLock(NTAG_HANDLE_T ntag, BOOL *locked)
{
    uint8_t val;
    NTAG_ReadConfiguration(ntag, NTAG_MEM_OFFSET_REG_LOCK, &val);

    if (val & 0x01)
        *locked = TRUE;
    else
        *locked = FALSE;

    return NTAG_ERR_OK;
}

//---------------------------------------------------------------------
BOOL NTAG_SetI2CConfigurationWrite(NTAG_HANDLE_T ntag)
{
    return NTAG_WriteConfiguration(ntag, NTAG_MEM_OFFSET_REG_LOCK, 0x02, 0x02);
}

//---------------------------------------------------------------------
BOOL NTAG_GetI2CConfigurationLock(NTAG_HANDLE_T ntag, BOOL *locked)
{
    uint8_t val;
    if (NTAG_ReadConfiguration(ntag, NTAG_MEM_OFFSET_REG_LOCK, &val))
        return NTAG_ERROR_RX_FAILED;

    if (val & 0x02)
        *locked = TRUE;
    else
        *locked = FALSE;

    return NTAG_OK;
}

//---------------------------------------------------------------------
BOOL NTAG_GetI2CClockStr(NTAG_HANDLE_T ntag, BOOL *clk)
{
    uint8_t val;
    NTAG_ReadRegister(ntag, NTAG_MEM_OFFSET_NC_REG, &val);

    *clk = (val & 0x01);
    return NTAG_ERR_OK;
}

//---------------------------------------------------------------------
BOOL NTAG_ReleaseI2CLocked(NTAG_HANDLE_T ntag)
{
    return NTAG_WriteRegister(ntag, NTAG_MEM_OFFSET_NC_REG, NTAG_NS_REG_MASK_I2C_LOCKED, 0x00);
}

//---------------------------------------------------------------------
BOOL NTAG_SetFDOnFunction(NTAG_HANDLE_T ntag, NTAG_FD_ON_FUNCTIONS_T func)
{
    return NTAG_WriteRegister(ntag, NTAG_MEM_OFFSET_NC_REG, NTAG_NC_REG_MASK_FD_ON, func);
}

//---------------------------------------------------------------------
BOOL NTAG_GetFDOnFunction(NTAG_HANDLE_T ntag, NTAG_FD_ON_FUNCTIONS_T *func)
{
    uint8_t val;
    NTAG_ReadRegister(ntag, NTAG_MEM_OFFSET_NC_REG, &val);

    *func = (NTAG_FD_ON_FUNCTIONS_T)(val & NTAG_NC_REG_MASK_FD_ON);
    return NTAG_ERR_OK;
}

//---------------------------------------------------------------------
BOOL NTAG_SetFDOffFunction(NTAG_HANDLE_T ntag, NTAG_FD_OFF_FUNCTIONS_T func)
{
    return NTAG_WriteRegister(ntag, NTAG_MEM_OFFSET_NC_REG, NTAG_NC_REG_MASK_FD_OFF, func);
}

//---------------------------------------------------------------------
BOOL NTAG_GetFDOffFunction(NTAG_HANDLE_T ntag, NTAG_FD_OFF_FUNCTIONS_T *func)
{
    uint8_t val;
    NTAG_ReadRegister(ntag, NTAG_MEM_OFFSET_NC_REG, &val);

    *func = (NTAG_FD_OFF_FUNCTIONS_T)(val & NTAG_NC_REG_MASK_FD_OFF);
    return NTAG_ERR_OK;
}

//---------------------------------------------------------------------
BOOL NTAG_SetPthruOnOff(NTAG_HANDLE_T ntag, BOOL on)
{
    uint8_t val = 0;
    if (on)
        val = NTAG_NC_REG_MASK_PTHRU_ON_OFF;
    else
        val = 0;

    return NTAG_WriteRegister(ntag, NTAG_MEM_OFFSET_NC_REG, NTAG_NC_REG_MASK_PTHRU_ON_OFF, val);
}

//---------------------------------------------------------------------
BOOL NTAG_GetPthruOnOff(NTAG_HANDLE_T ntag, BOOL *on)
{
    uint8_t val;
    NTAG_ReadRegister(ntag, NTAG_MEM_OFFSET_NC_REG, &val);

    *on = ((val & NTAG_NC_REG_MASK_PTHRU_ON_OFF) != 0);
    return NTAG_ERR_OK;
}

//---------------------------------------------------------------------
BOOL NTAG_SetSRAMMirrorOnOff(NTAG_HANDLE_T ntag, BOOL on)
{
    uint8_t val = 0;
    if (on)
        val = NTAG_NC_REG_MASK_SRAM_MIRROR_ON_OFF;
    else
        val = 0;

    return NTAG_WriteRegister(ntag, NTAG_MEM_OFFSET_NC_REG, NTAG_NC_REG_MASK_SRAM_MIRROR_ON_OFF, val);
}

//---------------------------------------------------------------------
BOOL NTAG_GetSRAMMirrorOnOff(NTAG_HANDLE_T ntag, BOOL *on)
{
    uint8_t val;
    NTAG_ReadRegister(ntag, NTAG_MEM_OFFSET_NC_REG, &val);

    *on = ((val & NTAG_NC_REG_MASK_SRAM_MIRROR_ON_OFF) != 0);
    return NTAG_ERR_OK;
}

//---------------------------------------------------------------------
BOOL NTAG_SetTransferDir(NTAG_HANDLE_T ntag, NTAG_TRANSFER_DIR_T dir)
{
    int16_t err = NTAG_ERR_OK;
    uint8_t current_ses_reg = 0;
    NTAG_ReadRegister(ntag, NTAG_MEM_OFFSET_NC_REG, &current_ses_reg);

    if ((current_ses_reg & NTAG_NC_REG_MASK_TRANSFER_DIR) != dir)
    {
        if (current_ses_reg & NTAG_NC_REG_MASK_PTHRU_ON_OFF)
        {
            NTAG_SetPthruOnOff(ntag, FALSE);
            err = NTAG_WriteRegister(ntag, NTAG_MEM_OFFSET_NC_REG, NTAG_NC_REG_MASK_TRANSFER_DIR, dir);
            NTAG_SetPthruOnOff(ntag, TRUE);
        }
        else
        {
            err = NTAG_WriteRegister(ntag, NTAG_MEM_OFFSET_NC_REG, NTAG_NC_REG_MASK_TRANSFER_DIR, dir);
        }
    }
    // already set do nothing
    return err;
}

//---------------------------------------------------------------------
BOOL NTAG_GetTransferDir(NTAG_HANDLE_T ntag, NTAG_TRANSFER_DIR_T *dir)
{
    uint8_t current_ses_reg = 0;
    NTAG_ReadRegister(ntag, NTAG_MEM_OFFSET_NC_REG, &current_ses_reg);
    *dir = (NTAG_TRANSFER_DIR_T)(current_ses_reg & NTAG_NC_REG_MASK_TRANSFER_DIR);

    return NTAG_ERR_OK;
}

//---------------------------------------------------------------------
BOOL NTAG_SetLastNDEFBlock(NTAG_HANDLE_T ntag, uint8_t block)
{
    int16_t err = NTAG_ERR_OK;
    if (block > 0x74)
    {
        return (NTAG_ERR_INVALID_PARAM);
    }
    err = NTAG_WriteRegister(ntag, NTAG_MEM_OFFSET_LAST_NDEF_BLOCK, 0xFF, block);
    return (err);
}

//---------------------------------------------------------------------
BOOL NTAG_GetLastNDEFBlock(NTAG_HANDLE_T ntag, uint8_t *block)
{
    int16_t err = NTAG_ERR_OK;
    uint8_t current_ses_reg = 0;
    err = NTAG_ReadRegister(ntag, NTAG_MEM_OFFSET_LAST_NDEF_BLOCK, &current_ses_reg);
    *block = current_ses_reg;
    return (err);
}

//---------------------------------------------------------------------
BOOL NTAG_SetSRAMMirrorBlock(NTAG_HANDLE_T ntag, uint8_t block)
{
    int16_t err = NTAG_ERR_OK;
    err = NTAG_WriteRegister(ntag, NTAG_MEM_OFFSET_SRAM_MIRROR_BLOCK, 0xFF, block);
    return (err);
}

//---------------------------------------------------------------------
BOOL NTAG_GetSRAMMirrorBlock(NTAG_HANDLE_T ntag, uint8_t *block)
{
    int16_t err = NTAG_ERR_OK;
    uint8_t current_ses_reg = 0;
    err = NTAG_ReadRegister(ntag, NTAG_MEM_OFFSET_SRAM_MIRROR_BLOCK, &current_ses_reg);
    *block = current_ses_reg;
    return (err);
}

//---------------------------------------------------------------------
BOOL NTAG_SetWatchdogTime(NTAG_HANDLE_T ntag, uint16_t time)
{
    int16_t err = NTAG_ERR_OK;
    err = NTAG_WriteRegister(ntag, NTAG_MEM_OFFSET_WDT_LS, 0xFF, (uint8_t)(time & 0xFF));
    if (err != NTAG_ERR_OK)
        return (err);

    err = NTAG_WriteRegister(ntag, NTAG_MEM_OFFSET_WDT_MS, 0xFF, (uint8_t)((time >> 8) & 0xFF));
    return (err);
}

//---------------------------------------------------------------------
BOOL NTAG_GetWatchdogTime(NTAG_HANDLE_T ntag, uint16_t *time)
{
    int16_t err = NTAG_ERR_OK;
    uint8_t reg = 0;
    *time = 0;
    err = NTAG_ReadRegister(ntag, NTAG_MEM_OFFSET_WDT_LS, &reg);
    *time |= (uint16_t)(reg & 0x00FF);

    err = NTAG_ReadRegister(ntag, NTAG_MEM_OFFSET_WDT_MS, &reg);
    *time |= (uint16_t)((reg << 8) & 0xFF00);

    return (err);
}
