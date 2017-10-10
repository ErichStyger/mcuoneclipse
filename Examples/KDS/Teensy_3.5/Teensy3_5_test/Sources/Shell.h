/**
 * \file
 * \brief Shell (command line) interface.
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * This module implements a command line interface to the application.
 */

#ifndef SHELL_H_
#define SHELL_H_

/*!
 * \brief Sends a string to the shell/console stdout
 * \param msg Zero terminated string to write
 */
void SHELL_SendString(unsigned char *msg);

/*!
 * \brief Checks if there is input from the console and parses it.
 */
void SHELL_Process(void);

/*! \brief Serial driver initialization */
void SHELL_Init(void);

/*! \brief Serial driver de-initialization */
void SHELL_Deinit(void);

#endif /* SHELL_H_ */
