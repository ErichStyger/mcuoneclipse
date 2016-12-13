/**
 * \file
 * \brief This is the interface to the application entry point.
 * \author (c) 2014 Erich Styger, http://mcuoneclipse.com/
 * \note MIT License (http://opensource.org/licenses/mit-license.html)
 */

#ifndef RNETAPP_H_
#define RNETAPP_H_

#include "Platform.h"

/*!
 * \brief callback for key pressed
 * \param key bitset of key pressed
 */
void RNETA_KeyPressed(uint8_t key);

/*! \brief Driver initialization */
void RNETA_Init(void);

#endif /* RNETAPP_H_ */
