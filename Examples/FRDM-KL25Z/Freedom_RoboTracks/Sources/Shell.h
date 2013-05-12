/*
 * Shell.h
 *
 *  Created on: 23.05.2011
 *      Author: Erich Styger
 */

#ifndef SHELL_H_
#define SHELL_H_

/*!
 * \brief Sends a string to the shell/console
 * \param msg Zero terminated string to write
 */
void SHELL_SendString(unsigned char *msg);

/*! \brief Serial driver initialization */
void SHELL_Init(void);

#endif /* SHELL_H_ */
