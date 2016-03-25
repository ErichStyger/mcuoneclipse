/*
 * Platform.h
 *
 *  Created on: Apr 7, 2014
 *      Author: tastyger
 */

#ifndef PLATFORM_H_
#define PLATFORM_H_

#include "PE_Types.h"

#define PL_HAS_SHELL        1
  /*!< If we use a shell */
#define PL_HAS_NRF24        1
  /*!< If we send nRF24L01+ messages */
#define PL_HAS_RSTDIO       (1 && PL_HAS_NRF24)
  /*!< If we use remote stdio redirection */
#define PL_HAS_LCD          0
  /*!< If we have a Nokia LCD attached to the board */
#define PL_HAS_SNAKE_GAME   (1 && PL_HAS_LCD)
  /*!< If we have the snake game on the LCD */

#endif /* PLATFORM_H_ */
