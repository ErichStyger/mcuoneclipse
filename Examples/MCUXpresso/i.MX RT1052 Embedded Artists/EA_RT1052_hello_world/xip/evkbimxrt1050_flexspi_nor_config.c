/*
 * The Clear BSD License
 * Copyright 2017 NXP
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted (subject to the limitations in the disclaimer below) provided
 * that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of the copyright holder nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * NO EXPRESS OR IMPLIED LICENSES TO ANY PARTY'S PATENT RIGHTS ARE GRANTED BY THIS LICENSE.
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

#include "evkbimxrt1050_flexspi_nor_config.h"

/*******************************************************************************
 * Code
 ******************************************************************************/
#if defined(XIP_BOOT_HEADER_ENABLE) && (XIP_BOOT_HEADER_ENABLE == 1)
#if defined(__CC_ARM) || defined(__GNUC__)
__attribute__((section(".boot_hdr.conf")))
#elif defined(__ICCARM__)
#pragma location = ".boot_hdr.conf"
#endif

// Number of dummy cycles for non-SPI modes
#define NON_SPI_DUMMY_CYCLES 18
#define CTRL_REG_BYTE3_VAL (((NON_SPI_DUMMY_CYCLES - 8) >> 1) | 0x10)

const flexspi_nor_config_t hyperflash_config = {
    .memConfig =
        {
            .tag = FLEXSPI_CFG_BLK_TAG,
            .version = FLEXSPI_CFG_BLK_VERSION,
            .readSampleClkSrc = kFlexSPIReadSampleClk_ExternalInputFromDqsPad,
            .csHoldTime = 2u,
            .csSetupTime = 4u,
            .columnAddressWidth = 0u,
            .deviceModeCfgEnable = 1u,
            .deviceModeSeq = {.seqId=14,.seqNum=1}, // index/size of Write Status Register Byte 2 (31h) sequence
            .deviceModeArg = 0x88 | (CTRL_REG_BYTE3_VAL << 8),
            // Enable DDR mode, Safe configuration
            .controllerMiscOption =
                (1u << kFlexSpiMiscOffset_DdrModeEnable) |
                (1u << kFlexSpiMiscOffset_SafeConfigFreqEnable),
            .sflashPadType = kSerialFlash_8Pads,
            .serialClkFreq = kFlexSpiSerialClk_133MHz,
            .deviceType = 1, // serial NOR
            .sflashA1Size = 4u * 1024u * 1024u,
            .dataValidTime = {20u, 0u},
            .lookupTable =
                {
                    //Read Array
                    [0] =  FLEXSPI_LUT_SEQ(CMD_SDR, FLEXSPI_8PAD, 0x0B, RADDR_DDR, FLEXSPI_8PAD, 32),
                    [1] =  FLEXSPI_LUT_SEQ(DUMMY_DDR, FLEXSPI_8PAD, (NON_SPI_DUMMY_CYCLES*2+1), READ_DDR, FLEXSPI_8PAD, 128),
                    //[2] =  FLEXSPI_LUT_SEQ(JMP_ON_CS, FLEXSPI_8PAD, 0, 0,0,0),
                    
                    // Read Status (byte 1)
                    [4] =  FLEXSPI_LUT_SEQ(CMD_SDR, FLEXSPI_8PAD, 0x05, DUMMY_DDR, FLEXSPI_8PAD, 8),
                    [5] =  FLEXSPI_LUT_SEQ(READ_DDR, FLEXSPI_8PAD, 1, 0,0,0),
                    
                    // Write Enable     
                    [12] =  FLEXSPI_LUT_SEQ(CMD_SDR, FLEXSPI_1PAD, 0x06, 0,0,0),
                    
                    // Block Erase 4K
                    [20] =  FLEXSPI_LUT_SEQ(CMD_SDR, FLEXSPI_1PAD, 0x20, RADDR_SDR, FLEXSPI_1PAD, 32),
                    
                    // Page Program
                    [36] =  FLEXSPI_LUT_SEQ(CMD_SDR, FLEXSPI_1PAD, 0x02, RADDR_SDR, FLEXSPI_1PAD, 32),
                    [37] =  FLEXSPI_LUT_SEQ(WRITE_SDR, FLEXSPI_1PAD, 128, 0,0,0),
                    
                    // Chip Erase 
                    [44] =  FLEXSPI_LUT_SEQ(CMD_SDR, FLEXSPI_1PAD, 0x60, 0,0,0),
                    
                    // Write Status Register Byte 1
                    [48] =  FLEXSPI_LUT_SEQ(CMD_SDR, FLEXSPI_1PAD, 0x01, WRITE_SDR, FLEXSPI_1PAD, 1),
                    
                    // Write Status Register Byte 2
                    [52] =  FLEXSPI_LUT_SEQ(CMD_SDR, FLEXSPI_1PAD, 0x31, WRITE_SDR, FLEXSPI_1PAD, 1),
                    
                    // Write Status/Control Registers
                    [56] =  FLEXSPI_LUT_SEQ(CMD_SDR, FLEXSPI_1PAD, 0x71, CMD_SDR, FLEXSPI_1PAD, 2),
                    [57] =  FLEXSPI_LUT_SEQ(WRITE_SDR, FLEXSPI_1PAD, 2, 0,0,0),
                },
        },
    .pageSize = 256u,
    .sectorSize = 4u * 1024u,
    .blockSize = 4u * 1024u,
    .isUniformBlockSize = true,
.ipcmdSerialClkFreq = kFlexSpiSerialClk_30MHz,
};
#endif /* XIP_BOOT_HEADER_ENABLE */
