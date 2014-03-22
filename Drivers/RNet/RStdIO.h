/**
 * \file
 * \brief This is the interface of the remote/radio standard I/O module
 * \author (c) 2013 Erich Styger, http://mcuoneclipse.com/
 * \note MIT License (http://opensource.org/licenses/mit-license.html), see 'RNet_License.txt'
 *
 * This module is used for radio/remote stdio.
 */

#ifndef RSTDIO_C_
#define RSTDIO_C_

#include "RNetConf.h"
%if defined(RStdioEnabled) & %RStdioEnabled='yes'
#include "RPHY.h"
#include "RNWK.h"
#include "%@Shell@'ModuleName'.h"

typedef enum RSTDIO_QueueType {
  /* Rx stdio queues: */
  RSTDIO_QUEUE_RX_IN,
  RSTDIO_QUEUE_RX_OUT,
  RSTDIO_QUEUE_RX_ERR,
  /* Tx stdio queues: */
  RSTDIO_QUEUE_TX_IN,
  RSTDIO_QUEUE_TX_OUT,
  RSTDIO_QUEUE_TX_ERR
} RSTDIO_QueueType;

/*!
 * \brief Sends a character buffer to a tx stdio queues and sends it if queue is full or has \n
 * \param queueType Which stdio queue to use
 * \param buf Data buffer.
 * \param bufSize Size of data buffer.
 * \return Error code
 */
uint8_t RSTDIO_SendToTxStdio(RSTDIO_QueueType queueType, uint8_t *buf, size_t bufSize);

uint8_t RSTDIO_AddToQueue(RSTDIO_QueueType queueType, const unsigned char *data, size_t dataSize);

/*!
 * \brief returns the Standard I/O hander for the remote Rx channel
 * \return Standard I/O handler with stdin, stdout and stderr
 */
%@Shell@'ModuleName'%.ConstStdIOTypePtr RSTDIO_GetStdioRx(void);

/*!
 * \brief Message handler for StdIO messages sent over the radio
 * \param type Message type
 * \param Size of the payload data
 * \param data Payload data
 * \param srcAddr Address of node who has sent the message
 * \param[out] handled Message handler sets this to TRUE if message was handled
 * \param packet Message data packet data
 */
uint8_t RSTDIO_HandleStdioRxMessage(RAPP_MSG_Type type, uint8_t size, uint8_t *data, RNWK_ShortAddrType srcAddr, bool *handled, RPHY_PacketDesc *packet);

/*!
 * \brief Call this routines periodically. It will parse incoming remote messages and will dispatch them between stdin, stdout and stderr.
 */
void RSTDIO_Print(%@Shell@'ModuleName'%.ConstStdIOTypePtr io);

/*! \brief Initializes the module */
void RSTDIO_Init(void);

/*! \brief Deinitializes the module */
void RSTDIO_Deinit(void);

%endif

#endif /* RSTDIO_C_ */
