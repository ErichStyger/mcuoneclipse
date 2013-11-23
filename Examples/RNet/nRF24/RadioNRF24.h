/**
 * \file
 * \brief This is the interface to the Nordic Semiconductor nRF24L01+
 * \author (c) 2013 Erich Styger, http://mcuoneclipse.com/
 * \note MIT License (http://opensource.org/licenses/mit-license.html), see 'RNet_License.txt'
 *
 * This module deals with the low level interface of the transceiver.
 */

#ifndef RADIO_NRF24_H_
#define RADIO_NRF24_H_

#include "RNetConf.h"
#if PL_HAS_RADIO
#include "Radio.h"

void Radio_OnInterrupt(void);

#endif /* PL_HAS_RADIO */

#endif /* RADIO_NRF24_H_ */
