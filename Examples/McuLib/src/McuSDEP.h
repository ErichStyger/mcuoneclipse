/*
 * Copyright (c) 2024, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 * SDEP (Simple Data Exchange Protocol) has been developed by Adafruit
 * (see https://learn.adafruit.com/introducing-the-adafruit-bluefruit-spi-breakout/sdep-spi-data-transport)
 */

#ifndef _MCUSDEP_H_
#define _MCUSDEP_H_

#include "McuSDEPconfig.h"
#if McuSDEP_CONFIG_IS_ENABLED
#include <stdbool.h>
#include <stdint.h>
#include "McuShell.h"
#include "McuIO.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct McuSDEPmessage_t {
  uint8_t type;         /* message type, e.g. McuSDEP_MSG_TYPE_COMMAND */
  uint16_t cmdId;       /* command ID, e.g. McuSDEP_CMD_TYPE_PING */
  uint8_t payloadSize;  /* number of payload bytes */
  uint8_t *payload;     /* payload of data */
  uint8_t crc;          /* CRC8 of the message */
} McuSDEPmessage_t;

#define McuSDEP_MESSAGE_MAX_NOF_BYTES        131
#define McuSDEP_MESSAGE_MAX_PAYLOAD_BYTES    127
#define McuSDEP_PAYLOADBYTE_MORE_DATA_BIT    0x80

/* message types (U8) */
#define McuSDEP_MSG_TYPE_COMMAND  		   0x10
#define McuSDEP_MSG_TYPE_RESPONSE  	     0x20
#define McuSDEP_MSG_TYPE_ALERT  		     0x40
#define McuSDEP_MSG_TYPE_ERROR  		     0x80

#include "McuSDEP_IDs.h" /* application specific SDEP IDs */

/* --------------------------------------------------------------------------------- */
/* optional buffer incoming rx data for SDEP */
/* --------------------------------------------------------------------------------- */
void McuSDEP_SetSdepIO(McuIO_Desc_t *io);
McuIO_Desc_t *McuSDEP_GetSdepIO(void);

void McuSDEP_StoreCharInSdepBuffer(char ch);
/* --------------------------------------------------------------------------------- */
/*!
 * \brief Set a callback to forward non-SDEP characters.
 * \param forward_char_cb Callback to be called for forwarding. Can be NULL.
 */
void McuSDEP_SetForwardCharCallback(void (*forward_char_cb)(char));

/*!
 * \brief Set a callback to get data into SDEP buffer.
 * \param rx_cb Callback to be called for getting data. Can be NULL.
 */
void McuSDEP_SetRxToBufferCallback(int (*rx_cb)(void));

/*!
 * \brief Send an SDEP message.
 * \param io I/O to be used.
 * \param msg Message to be sent.
 * \return ERR_OK for success.
 */
uint8_t McuSDEP_SendMessage(McuIO_Desc_t *io, McuSDEPmessage_t *msg);

/*!
* \brief Shell command line handler
* \param cmd String to command to be parsed
* \param handled Returns if command has been handled
* \param io I/O channel
* \return Error code, ERR_OK if everything is ok
*/
uint8_t McuSDEP_ParseCommand(const uint8_t *cmd, bool *handled, McuShell_ConstStdIOType *io);

/*!
 * \brief Set the current McuLog channel. Preferred to use RTT or a non-SDEP channel.
*/
void McuSDEP_SetLogChannel(uint8_t channel);

/*!
 * \brief Get the current McuLog channel.
 * \return The current log channel number.
*/
uint8_t McuSDEP_GetLogChannel(void);

/*!
 * \brief Define which can be used to log an SDEP related message. That way does not interfer with SDEP communication channel.
 */
#define McuSDEP_Log(...) McuLog_ChannelLog(McuSDEP_GetLogChannel(), McuLog_TRACE, __BASE_FILE__, __LINE__, __VA_ARGS__)

/*!
 * \brief Driver de-initialization.
 */
void McuSDEP_Deinit(void);

/*!
 * \brief Driver initialization.
 */
void McuSDEP_Init(void);

#ifdef __cplusplus
}  /* extern "C" */
#endif

#endif /* McuSDEP_CONFIG_IS_ENABLED */

#endif /* _MCUSDEP_H_ */