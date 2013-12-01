/**
 * \file
 * \brief This is the interface to Remote Controller Module
 * \author Erich Styger, erich.styger@hslu.ch
 */

#ifndef __REMOTE_H_
#define __REMOTE_H_

#include "Platform.h"
#if PL_HAS_REMOTE
#include "CLS1.h"
#include "RAPP.h"
#include "RNWK.h"
#include "RPHY.h"

uint8_t REMOTE_HandleRemoteRxMessage(RAPP_MSG_Type type, uint8_t size, uint8_t *data, RNWK_ShortAddrType srcAddr, bool *handled, RPHY_PacketDesc *packet);

/*!
 * \brief Function to find out if the remote controller is enabled or not.
 * \return TRUE if it is on, FALSE otherwise.
 */
bool REMOTE_GetOnOff(void);

/*!
 * \brief Function to turn on or off the remote controller.
 * \param[in] on TRUE for turning it on, FALSE otherwise.
 */
void REMOTE_SetOnOff(bool on);

/*!
 * \brief Parses a command
 * \param cmd Command string to be parsed
 * \param handled Sets this variable to TRUE if command was handled
 * \param io I/O stream to be used for input/output
 * \return Error code, ERR_OK if everything was fine
 */
uint8_t REMOTE_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io);

/*! \brief De-initialization of the module */
void REMOTE_Deinit(void);

/*! \brief Initialization of the module */
void REMOTE_Init(void);

#endif /* PL_REMOTE */

#endif /* __REMOTE_H_ */
