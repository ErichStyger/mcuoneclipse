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
#ifndef NFC_DEVICE_H
#define NFC_DEVICE_H

#define NFC_TEST_DEVICE NTAG0
#define NFC_ID_MAX_DEVICES NTAG_ID_MAX_DEVICES
#define NFC_INVALID_HANDLE NTAG_INVALID_HANDLE
#define NFC_HANDLE_T NTAG_HANDLE_T
#define NFC_InitDevice NTAG_InitDevice
#define NFC_CloseDevice NTAG_CloseDevice
#define NFC_ReadBytes NTAG_ReadBytes
#define NFC_WriteBytes NTAG_WriteBytes
#define NFC_GetLastError NTAG_GetLastError
#define NFC_WaitForEvent NTAG_WaitForEvent
#define NFC_ReadRegister NTAG_ReadRegister
#define NFC_WriteRegister NTAG_WriteRegister
#define NFC_WriteBlock NTAG_WriteBlock

#define NFC_ReadRegister NTAG_ReadRegister
#define NFC_SetPthruOnOff NTAG_SetPthruOnOff
#define NFC_SetTransferDir NTAG_SetTransferDir

#define NFC_SetFDOffFunction NTAG_SetFDOffFunction
#define NFC_SetFDOnFunction NTAG_SetFDOnFunction

#define NFC_MEM_SRAM_SIZE NTAG_MEM_SRAM_SIZE

#define NFC_I2C_BLOCK_SIZE NTAG_I2C_BLOCK_SIZE
#define NFC_MEM_ADDR_START_SRAM NTAG_MEM_ADDR_START_SRAM
#define NFC_MEM_ADDR_START_USER_MEMORY NTAG_MEM_ADDR_START_USER_MEMORY
#define NFC_MEM_OFFSET_NC_REG NTAG_MEM_OFFSET_NC_REG
#define NFC_MEM_OFFSET_NS_REG NTAG_MEM_OFFSET_NS_REG
#define NFC_NC_REG_MASK_PTHRU_ON_OFF NTAG_NC_REG_MASK_PTHRU_ON_OFF
#define NFC_NS_REG_MASK_I2C_LOCKED NTAG_NS_REG_MASK_I2C_LOCKED

// switch between Interrupt and Polling mode
#ifdef INTERRUPT
#define NTAG_EVENT_RF_WROTE_SRAM NTAG_EVENT_RF_WROTE_SRAM_INTERRUPT
#define NTAG_EVENT_RF_READ_SRAM NTAG_EVENT_RF_READ_SRAM_INTERRUPT
#define NTAG_EVENT_RF_FIELD_PRESENT NTAG_EVENT_RF_FIELD_PRESENT_INTERRUPT
#else
#define NTAG_EVENT_RF_WROTE_SRAM NTAG_EVENT_RF_WROTE_SRAM_POLLED
#define NTAG_EVENT_RF_READ_SRAM NTAG_EVENT_RF_READ_SRAM_POLLED
#define NTAG_EVENT_RF_FIELD_PRESENT NTAG_EVENT_RF_FIELD_PRESENT_POLLED
#endif

#define SRAM_TIMEOUT 500

#endif /* NFC_DEVICE_H */
