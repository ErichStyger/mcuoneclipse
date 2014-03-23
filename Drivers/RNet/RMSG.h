/**
 * \file
 * \brief Radio Network Message Layer
 * \author (c) 2013-2014 Erich Styger, http://mcuoneclipse.com/
 * \note MIT License (http://opensource.org/licenses/mit-license.html), see 'RNet_License.txt'
 *
 * This module implements radio message handling module of the radio network stack.
 */

#ifndef RADIOMESSAGE_H_
#define RADIOMESSAGE_H_

#include "RNetConf.h"
#include "RPHY.h"

/*!
 * \brief Flushes the Rx queue (makes it empty).
 * \return Error code, ERR_OK for everything fine.
 */
uint8_t RMSG_FlushRxQueue(void);

/*!
 * \brief Flushes the Rx queue (makes it empty).
 * \return Error code, ERR_OK for everything fine.
 */
uint8_t RMSG_FlushTxQueue(void);

/*!
 * \brief Queues a message to be sent to the radio transceiver.
 * \param buf Pointer to the message data to be sent.
 * \param bufSize Size of buffer.
 * \param payloadSize Size of payload data.
 * \param fromISR If called from an ISR routine.
 * \param isTx If message is TX or RX.
 * \param flags Packet flags.
 * \return Error code, ERR_OK if message has been queued.
 */
uint8_t RMSG_QueuePut(uint8_t *buf, size_t bufSize, uint8_t payloadSize, bool fromISR, bool isTx, RPHY_FlagsType flags);

/*!
 * \brief Used to check if we have a message incoming from the RX queue.
 * \param[in] buf Buffer where to store the incoming message
 * \param[in] bufSize Size of buffer, must be at least of size PHY_BUFFER_SIZE
 * \param[in] payLoadPtr Pointer to payload start.
 * \param[in] payloadSize Size of payload. 
 * \return ERR_OK if we have a message, otherwise error code.
 */
uint8_t RMSG_GetRxMsg(uint8_t *buf, size_t bufSize);

/*!
 * \brief Used to check if we have a message outgoing in the TX queue.
 * \param buf Buffer where to store the incoming message
 * \param bufSize Size of buffer, must be at least of size RMSG_QUEUE_ITEM_SIZE
 * \return ERR_OK if we have a message, otherwise error code.
 */
uint8_t RMSG_GetTxMsg(uint8_t *buf, size_t bufSize);

/*!
 * \brief Add a message to the TX queue.
 * \param buf Pointer to the message data.
 * \param bufSize Size of the buffer in bytes, must be RPHY_BUFFER_SIZE.
 * \param payloadSize Size of payload in buffer.
 * \param flags Packet flags.
 * \return ERR_OK, or error code.
 */
uint8_t RMSG_QueueTxMsg(uint8_t *buf, size_t bufSize, uint8_t payloadSize, RPHY_FlagsType flags);

/*!
 * \brief Add a message to the RX queue.
 * \param buf Pointer to the message data.
 * \param bufSize Size of the buffer in bytes.
 * \param payloadSize Size of payload in buffer.
 * \param flags Packet flags
 * \return ERR_OK, or error code.
 */
uint8_t RMSG_QueueRxMsg(uint8_t *buf, size_t bufSize, uint8_t payloadSize, RPHY_FlagsType flags);

/*! \brief Initializes the module */
void RMSG_Init(void);

/*! \brief Deinitializes the module */
void RMSG_Deinit(void);

#endif /* RADIOMESSAGE_H_ */
