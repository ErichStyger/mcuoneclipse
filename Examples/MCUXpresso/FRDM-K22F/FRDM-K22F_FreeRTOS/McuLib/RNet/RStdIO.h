/**
 * \file
 * \brief This is the interface of the remote/radio standard I/O module
 * \author (c) 2013-2014 Erich Styger, http://mcuoneclipse.com/
 * \note MIT License (http://opensource.org/licenses/mit-license.html), see 'RNet_License.txt'
 *
 * This module is used for radio/remote stdio.
 */

#ifndef RSTDIO_C_
#define RSTDIO_C_

#include "McuRNetConfig.h"
#if McuRNET_CONFIG_IS_ENABLED
#include "RApp.h"
#include "RPHY.h"
#include "RNWK.h"
#include "McuShell.h"
#include "McuRTOS.h"

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

extern uint8_t RSTDIO_DefaultShellBuffer[McuShell_DEFAULT_SHELL_BUFFER_SIZE]; /* default buffer which can be used by the application */

extern McuShell_ConstStdIOType RSTDIO_stdio; /* default standard I/O */

#define RSTDIO_PARSE_COMMAND_ENABLED  1  /* set to 1 if method ParseCommand() is present, 0 otherwise */

/*!
 * \brief Shell parser routine.
 * \param cmd Pointer to command line string.
 * \param handled Pointer to status if command has been handled. Set to TRUE if command was understood.
 * \param io Pointer to stdio handle
 * \return Error code, ERR_OK if everything was ok.
 */
uint8_t RSTDIO_ParseCommand(const unsigned char *cmd, bool *handled, const McuShell_StdIOType *io);

/*!
 * \brief Returns a queue handle for a Remote Standard I/O type
 * \param queueType Type of queue
 * \return Queue handle
 */
QueueHandle_t RSTDIO_GetQueueForType(RSTDIO_QueueType queueType);

/*!
 * \brief Returns the number of elements in the queue
 * \param queueType Queue type
 * \return Number of elements in the queue, 0 if the queue is not known.
 */
uint8_t RSTDIO_NofInQueue(RSTDIO_QueueType queueType);

/*!
 * \brief Returns a character from a queue
 * \param queueType Queue type
 * \return Character, or zero byte if queue is empty or unknown
 */
uint8_t RSTDIO_ReceiveQueueChar(RSTDIO_QueueType queueType);

/*!
 * \brief Sends a message to a tx stdio queues and sends it if queue is full or has \n at the end
 * \param queueType Which stdio queue to use
 * \param buf Data buffer.
 * \param bufSize Size of data buffer.
 * \return Error code
 */
uint8_t RSTDIO_SendToTxStdio(RSTDIO_QueueType queueType, uint8_t *buf, size_t bufSize);

/*!
 * \brief Adds a message to a tx queues without sending it
 * \param queueType Which stdio queue to use
 * \param buf Data buffer.
 * \param bufSize Size of data buffer.
 * \return Error code
 */
uint8_t RSTDIO_AddToQueue(RSTDIO_QueueType queueType, const unsigned char *data, size_t dataSize);

/*!
 * \brief returns the Standard I/O hander for the remote Rx channel
 * \return Standard I/O handler with stdin, stdout and stderr
 */
McuShell_ConstStdIOTypePtr RSTDIO_GetStdio(void);

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
 * \param io Standard I/O handle to be used for printing
 */
void RSTDIO_Print(McuShell_ConstStdIOTypePtr io);

/*!
 * \brief Same as RSTDIO_Print(), but *adds* the input (in, err) into a buffer.
 * \param buffer Buffer to be used
 * \param bufSize Size of the buffer in bytes
 * \return Number of characters added to buffer
*/
unsigned int RSTDIO_AddIntoBuffer(unsigned char *buffer, size_t bufSize);

/*!
 * \brief Sets the destination address to be used for remote standard I/O
 * \param addr Address to be used
 */
void RSTDIO_SetDestinationAddress(RNWK_ShortAddrType addr);

/*! \brief Initializes the module */
void RSTDIO_Init(void);

/*! \brief Deinitializes the module */
void RSTDIO_Deinit(void);


#endif /* McuRNET_CONFIG_IS_ENABLED */

#endif /* RSTDIO_C_ */

