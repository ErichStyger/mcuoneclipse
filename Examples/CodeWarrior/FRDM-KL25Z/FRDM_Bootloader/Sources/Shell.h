/*
 * Shell.h
 *
 *      Author: Erich Styger
 */

#ifndef SHELL_H_
#define SHELL_H_

/*!
 * \brief Checks if there is input from the console and parses it.
 */
void SHELL_Parse(void);

/*! \brief Serial driver initialization */
void SHELL_Init(void);

/*! \brief Serial driver de-initialization */
void SHELL_Deinit(void);

#endif /* SHELL_H_ */
