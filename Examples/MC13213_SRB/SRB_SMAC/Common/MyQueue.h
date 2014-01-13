/**
 * \file
 * \brief This is the interface to the queue module
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * This module is used to demonstrate FreeRTOS queues.
 */

#ifndef MYQUEUE_C_
#define MYQUEUE_C_

/*!
 * \brief Sends a string to the queue. Note that if the queue is full, it will block.
 * \param msg Pointer to the string.
 */
void QUEUE_SendMessage(const char_t *msg);

/*!
 * \brief Receives an item from the queue, and returns immediately if the queue is empty.
 * \return Pointer to the message, or NULL. The caller has to free the memory!
 */
const char_t *QUEUE_ReceiveMessage(void);

/*! \brief Initializes the queue */
void QUEUE_Init(void);

#endif /* MYQUEUE_C_ */
