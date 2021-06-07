/**
 * \file
 * \brief Interface Platform initialization of the PRG_G board.
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * This module implements the hardware dependent initialization of board and drivers and offers configuration settings.
 */

#ifndef SRC_PLATFORM_H_
#define SRC_PLATFORM_H_

#include "McuLib.h"  /* include standard types */
#include "SEGGER_RTT.h"
#include <stdint.h>

#define PL_CONFIG_USE_SHELL              (1)
#define PL_CONFIG_USE_SHELL_UART         (0)
#define PL_CONFIG_USE_RTT                (1)


#define PL_CONFIG_BOARD_ID_STM32_NUCLEO   1  /*!< Board is the STM32 Nucleo Board */
#define PL_CONFIG_BOARD_ID_TINY_K22       2  /*!< Board is the NXP K22FN512 tinyK22 board */

#define PL_CONFIG_BOARD   PL_CONFIG_BOARD_ID_STM32_NUCLEO  /*!< configures the board used */

/*!
 * \brief Platform initialization.
 */
void PL_Init(void);

/**
  * @}
  */

#endif /* SRC_PLATFORM_H_ */
