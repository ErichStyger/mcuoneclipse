/**
 *\file
 *\brief Interface file for Application.c
 *\author Andreas Schoepfer
 */

#ifndef APPLICATION_H_
#define APPLICATION_H_

#include "CLS1.h"

uint8_t APP_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io);
/**
 * \brief Method to run the application.
 * The methods runs several FreeRTOS tasks and starts the scheduler.
 */
void APP_Start(void);

#endif /* APPLICATION_H_ */
