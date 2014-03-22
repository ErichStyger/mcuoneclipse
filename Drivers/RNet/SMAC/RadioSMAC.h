/**
 * \file
 * \brief Private Radio Module for the MC1320x/MC12321x transceivers.
 * \author (c) 2013 Erich Styger, http://mcuoneclipse.com/
 * \note MIT License (http://opensource.org/licenses/mit-license.html), see 'RNet_License.txt'
 *
 * Interface to handle everything around the radio transceiver
 */

#ifndef RADIO_SMAC_H_
#define RADIO_SMAC_H_

#include "RNetConf.h"
#include "Radio.h"
#include "Event.h"

/*!
 * \brief Event handler for Radio events. Needs to be called as part of the normal event handling
 * \param[in] event Event to be processed
 */
void RADIO_AppHandleEvent(EVNT_Handle event);

/*! \brief Called in the event of a radio transceiver interrupt */
void RADIO_OnInterrupt(void);

#endif /* RADIO_SMAC_H_ */
