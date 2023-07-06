/**
 * \file
 * \brief This is the interface to the Nordic Semiconductor nRF24L01+
 * \author (c) 2013-2014 Erich Styger, http://mcuoneclipse.com/
 * \note MIT License (http://opensource.org/licenses/mit-license.html), see 'RNet_License.txt'
 *
 * This module deals with the low level interface of the transceiver.
 */

#ifndef RADIO_NRF24_H_
#define RADIO_NRF24_H_

#include "McuRNetConfig.h"
#include "Radio.h"

void RADIO_OnInterrupt(void);

#endif /* RADIO_NRF24_H_ */
