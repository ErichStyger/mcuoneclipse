/**
 * \file
 * \brief This is the interface to the Nordic Semiconductor nRF24L01+
 * \author (c) 2013 Erich Styger, http://mcuoneclipse.com/
 * \note MIT License (http://opensource.org/licenses/mit-license.html), see 'RNet_License.txt'
 *
 * This module deals with the low level interface of the transceiver.
 */

#ifndef RADIO_H_
#define RADIO_H_

#include "Platform.h"

void Radio_OnInterrupt(void);

#if PL_HAS_SHELL
#include "CLS1.h"
uint8_t RADIO_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io);
#endif

uint8_t RADIO_Process(void);

/*! \brief Radio transceiver initialization */
void RADIO_Init(void);

/*! \brief Radio transceiver de-initialization */
void RADIO_Deinit(void);

#endif /* RADIO_H_ */
