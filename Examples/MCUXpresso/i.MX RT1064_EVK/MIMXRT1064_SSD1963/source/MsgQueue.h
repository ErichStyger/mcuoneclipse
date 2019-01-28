/**
 * \file
 * \brief This is the interface to the message queue module
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * This module is used pass messages from one task to another.
 */

#ifndef MSG_QUEUE_C_
#define MSG_QUEUE_C_

#include <stdlib.h> /* for size_t */
/*!
 * \brief Get a string from the Rx queue into a buffer
 * \param buf Pointer to buffer
 * \param bufSize Size of buffer in bytes
 */
void MSG_GetStringRxQueue(unsigned char *buf, size_t bufSize);

/*!
 * \brief Get a string from the Tx queue into a buffer
 * \param buf Pointer to buffer
 * \param bufSize Size of buffer in bytes
 */
void MSG_GetStringTxQueue(unsigned char *buf, size_t bufSize);

/*!
 * \brief Sends a string to the Rx queue. Note that if the queue is full, it will block.
 * \param str Pointer to the string.
 */
void MSG_SendStringRxQueue(const unsigned char *str);

/*!
 * \brief Sends a string to the Tx queue. Note that if the queue is full, it will block.
 * \param str Pointer to the string.
 */
void MSG_SendStringTxQueue(const unsigned char *str);

/*!
 * \brief Sends a character to the Rx queue.
 * \param ch Character to send.
 */
void MSG_SendCharRxQueue(unsigned char ch);

/*!
 * \brief Sends a character to the Tx queue.
 * \param ch Character to send.
 */
void MSG_SendCharTxQueue(unsigned char ch);

/*!
 * \brief Returns the number of elements (characters) in the Rx queue.
 * \return Number of characters in the queue.
 */
unsigned short MSG_NofElementsRxQueue(void);

/*!
 * \brief Returns the number of elements (characters) in the Tx queue.
 * \return Number of characters in the queue.
 */
unsigned short MSG_NofElementsTxQueue(void);

/*!
 * \brief Receives an a message character from the Tx queue, and returns immediately if the queue is empty.
 * \return Message character, or '\0' if there was no message.
 */
unsigned char MSG_GetCharTxQueue(void);

/*!
 * \brief Receives an a message character from the Rx queue, and returns immediately if the queue is empty.
 * \return Message character, or '\0' if there was no message.
 */
unsigned char MSG_GetCharRxQueue(void);


/*! \brief Initializes the queue module */
void MSG_Init(void);

/*! \brief Deinitializes the queue module */
void MSG_Deinit(void);

#endif /* SHELL_QUEUE_C_ */
