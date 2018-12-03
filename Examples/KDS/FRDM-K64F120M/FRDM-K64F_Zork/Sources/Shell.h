/**
 * \file
 * \brief Shell (command line) interface.
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * This module implements a command line interface to the application.
 */

#ifndef SHELL_H_
#define SHELL_H_

#include "CLS1.h"
#include "FRTOS1.h"

extern TaskHandle_t ShellTaskHandle;

/*! \brief Shell Module initialization, creates Shell task */
void SHELL_Init(void);

/*! \brief Shell driver de-initialization */
void SHELL_Deinit(void);


#endif /* SHELL_H_ */
