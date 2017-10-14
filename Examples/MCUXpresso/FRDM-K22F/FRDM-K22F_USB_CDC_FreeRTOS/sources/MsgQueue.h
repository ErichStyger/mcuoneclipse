/**
 * \file
 * \brief This is the interface to the message queue module
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * This module is used pass messages from one task to another.
 */

#ifndef MSG_QUEUE_C_
#define MSG_QUEUE_C_

/*!
 * \brief Sends a string to the Uart2Usb queue. Note that if the queue is full, it will block.
 * \param str Pointer to the string.
 */
void MSG_SendStringUart2Usb(const unsigned char *str);

/*!
 * \brief Sends a string to the Usb2Uart queue. Note that if the queue is full, it will block.
 * \param str Pointer to the string.
 */
void MSG_SendStringUsb2Uart(const unsigned char *str);

/*!
 * \brief Sends a character to the Uart2Usb queue.
 * \param ch Character to send.
 */
void MSG_SendCharUart2Usb(unsigned char ch);

/*!
 * \brief Sends a character to the Usb2Uart queue.
 * \param ch Character to send.
 */
void MSG_SendCharUsb2Uart(unsigned char ch);

/*!
 * \brief Returns the number of elements (characters) in the Usb2Uart queue.
 * \return Number of characters in the queue.
 */
unsigned short MSG_NofElementsUsb2Uart(void);

/*!
 * \brief Returns the number of elements (characters) in the Uart2Usb queue.
 * \return Number of characters in the queue.
 */
unsigned short MSG_NofElementsUart2Usb(void);

/*!
 * \brief Receives an a message character from the Usb2Uart queue, and returns immediately if the queue is empty.
 * \return Message character, or '\0' if there was no message.
 */
unsigned char MSG_GetCharUsb2Uart(void);

/*!
 * \brief Receives an a message character from the Uart2Usb queue, and returns immediately if the queue is empty.
 * \return Message character, or '\0' if there was no message.
 */
unsigned char MSG_GetCharUart2Usb(void);


/*! \brief Initializes the queue module */
void MSG_Init(void);

/*! \brief Deinitializes the queue module */
void MSG_Deinit(void);

#endif /* SHELL_QUEUE_C_ */
