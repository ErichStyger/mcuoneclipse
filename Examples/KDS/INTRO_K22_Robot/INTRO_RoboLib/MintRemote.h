/*
 * MintRemote.h
 *
 *  Created on: 16.09.2016
 *      Author: Erich Styger Local
 */

#ifndef SOURCES_INTRO_ROBOLIB_MINTREMOTE_H_
#define SOURCES_INTRO_ROBOLIB_MINTREMOTE_H_

#include "RApp.h"
#include "RNWK.h"
#include "RPHY.h"

uint8_t MINTREMOTE_HandleRemoteRxMessage(RAPP_MSG_Type type, uint8_t size, uint8_t *data, RNWK_ShortAddrType srcAddr, bool *handled, RPHY_PacketDesc *packet);

//uint8_t MINTREMOTE_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io);

void MINTREMOTE_Init(void);


#endif /* SOURCES_INTRO_ROBOLIB_MINTREMOTE_H_ */
