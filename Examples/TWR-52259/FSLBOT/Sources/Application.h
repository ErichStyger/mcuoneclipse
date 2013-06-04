/**
 *\file
 *\brief Interface file for Application.c
 *\author Andreas Schoepfer andreas.schoepfer@stud.hslu.ch
 *\date 03.01.12
 */

#ifndef APPLICATION_H_
#define APPLICATION_H_


/**
 * \brief Method to run the application.
 * 
 * The methods runs several FreeRTOS tasks and starts the scheduler.
 */
void APP_Start(void);

#endif /* APPLICATION_H_ */
