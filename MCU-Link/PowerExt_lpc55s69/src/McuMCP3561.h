/*
 * Copyright (c) 2025, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 * 
 * Interface to the MCP3561 ADC
 */

 #ifndef MCP3561_H_
 #define MCP3561_H_
 
 #ifdef __cplusplus
 extern "C" {
 #endif
 
#include "McuShell.h"
/*!
 * \brief Shell command line parser
 * \param cmd Pointer to the command string
 * \param handled If command has been recognized and handled
 * \param io I/O hander used for output
 * \return Error code, ERR_OK if everything is fine
 */
uint8_t McuMCP3561_ParseCommand(const unsigned char *cmd, bool *handled, const McuShell_StdIOType *io);


#define MCP3561_STATUS_BYTE_DR_STATUS (1<<2)  /* DR_STATUS (ADC data ready interrupt status) bit (LOW ACTIVE) */

/*! 
 * \brief Poll the status byte
 * \return status byte
 */
uint8_t MCP3561_PollStatusByte(void);

/*
 * \brief read 24 Bit ADC register DATA FORMAT 00 and 01 for MUX Mode.
 */
int32_t MCP3561_ReadADCData_24Bit(void);

/*
 * \brief read 32 Bit ADC register DATA FORMAT 00 and 01 for MUX Mode.
 */
int32_t MCP3561_ReadADCData_32Bit(void);

/*
 * \brief read 32 Bit ADC register DATA FORMAT 11 for Scan Mode.
 */
int32_t MCP3561_ReadADCData_32Bit_Scan(void);

/* \brief Mux plus voltage reference for measurement */
void McuMCP3561_MuxSingleEnded_RefInPlus(void);

/* \brief Mux channel 0 for measurement */
void McuMCP3561_MuxSingleEnded_Ch0(void);

/* \brief Mux channel 0 for measurement */
void McuMCP3561_MuxSingleEnded_Ch1(void);

/*!
 * \brief Configure the MCP3561 ADC
 */
void MCP3561_Configure(void);

 /*!
  * \brief Module de-initialization
  */
 void McuMCP3561_Deinit(void);
 
 /*!
  * \brief Module Initialization
  */
 void McuMCP3561_Init(void);
 
 #ifdef __cplusplus
 }  /* extern "C" */
 #endif
 
 #endif /* MCP3561_H_ */
 