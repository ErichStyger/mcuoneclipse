/*
 * Relay.h
 *
 *  Created on: Jun 3, 2013
 *      Author: tastyger
 */

#ifndef RELAY_H_
#define RELAY_H_

#include "PE_Types.h"

#define REL_NOF_RELAYS    8 /* number of relay available */

/*!
 * \brief Turns a relay on.
 * @param relNo Relay number, in the range from 0..(REL_NOF_RELAYS-1)
 */
void REL_On(uint8_t relNo);

/*!
 * \brief Turns a relay off.
 * @param relNo Relay number, in the range from 0..(REL_NOF_RELAYS-1)
 */
void REL_Off(uint8_t relNo);

/*!
 * Initialization of driver
 */
void REL_Init(void);

#endif /* RELAIS_H_ */
