/*
 * Shell.h
 *
 *      Author: Erich Styger
 */

#ifndef SHELL_H_
#define SHELL_H_

/*!
 * \brief Sends a string to the shell/console
 * \param msg Zero terminated string to write
 */
void SHELL_SendString(unsigned char *msg);

/*!
 * \brief Puts a command received from the Radio channel into a buffer.
 * \param str Zero terminated string
 */
void SHELL_RadioRxString(unsigned char *str);

/*!
 * \brief Checks if there is input from the console and parses it.
 */
void SHELL_Parse(void);

/*! \brief Serial driver initialization */
void SHELL_Init(void);

/*! \brief Serial driver de-initialization */
void SHELL_Deinit(void);

#endif /* SHELL_H_ */
