/*
 * MintRobot.h
 *
 *  Created on: 22.08.2016
 *      Author: Erich Styger Local
 */

#ifndef SOURCES_INTRO_ROBOLIB_MINTROBOT_H_
#define SOURCES_INTRO_ROBOLIB_MINTROBOT_H_

#include "Platform.h"
#if PL_HAS_MINT_ROBOT
#include "CLS1.h"
#include "RApp.h"
#include "RNWK.h"
#include "RPHY.h"

uint8_t MINT_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io);

uint8_t MINT_HandleRemoteRxMessage(RAPP_MSG_Type type, uint8_t size, uint8_t *data, RNWK_ShortAddrType srcAddr, bool *handled, RPHY_PacketDesc *packet);

bool MINT_AllowedToDrive(void);

void MINT_Init(void);

#endif /* PL_HAS_MINT_ROBOT */

#endif /* SOURCES_INTRO_ROBOLIB_MINTROBOT_H_ */
