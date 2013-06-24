/**
 * \file
 * \brief This is the interface to the queue module
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * This module is used to demonstrate FreeRTOS queues.
 */

#ifndef MYQUEUE_C_
#define MYQUEUE_C_

#include "FRTOS1.h"

extern xQueueHandle QUEUE_StdOut, QUEUE_StdIn, QUEUE_StdErr;

void QUEUE_SendData(xQueueHandle queue, const unsigned char *data, size_t dataSize);

/*!
 * \brief Sends a string to the queue. Note that if the queue is full, it will block.
 * \param str Pointer to the string.
 */
void QUEUE_SendString(xQueueHandle queue, const unsigned char *str);

/*!
 * \brief Peeks a character from the queue without removing it.
 * \param queue Queue to be used
 * \return '\0' if the queue is empty, otherwise it contains the character. 
 */
unsigned short QUEUE_NofElements(xQueueHandle queue);

/*!
 * \brief Receives an a message character from the queue, and returns immediately if the queue is empty.
 * \return Message character, or '\0' if there was no message.
 */
unsigned char QUEUE_ReceiveChar(xQueueHandle queue);

/*! \brief Initializes the queue module */
void QUEUE_Init(void);

/*! \brief Deinitializes the queue module */
void QUEUE_Deinit(void);

#endif /* MYQUEUE_C_ */
