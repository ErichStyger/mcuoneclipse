/**
 * \file
 * \brief Radio Module
 * \author (c) 2013 Erich Styger, http://mcuoneclipse.com/
 * \note MIT License (http://opensource.org/licenses/mit-license.html), see 'RNet_License.txt'
 *
 * Interface to handle everything around the radio transceiver
 */

#ifndef RADIO_H_
#define RADIO_H_

#include "Platform.h"
#if PL_HAS_RADIO

#include "SMAC1.h"
#include "RPHY.h"
#include "Event.h"

#define RADIO_PAYLOAD_SIZE           SMAC1_RADIO_BUF_SIZE /* total number of payload bytes */

/*! \brief Event called in case of radio transceiver reset */
void RADIO_ResetIndication(void);

/*!
 * \brief Event handler for Radio events. Needs to be called as part of the normal event handling
 * \param[in] event Event to be processed
 */
void RADIO_AppHandleEvent(EVNT_Handle event);

uint8_t RADIO_ProcessRx(RPHY_PacketDesc *packet);

/*! \brief Handler to deal with the Radio state machine. Needs to be called periodically to advance the state machine */
uint8_t RADIO_Process(void);

/*! 
 * \brief Event called on reception of a data packet
 * \param[in] sRxPacket Pointer to the data packet received
 */
void RADIO_DataIndicationPacket(tRxPacket *sRxPacket);

#if PL_HAS_SHELL
#include "CLS1.h"
/*!
 * \brief Parses a command
 * \param cmd Command string to be parsed
 * \param handled Sets this variable to TRUE if command was handled
 * \param io I/O stream to be used for input/output
 * \return Error code, ERR_OK if everything was fine
 */
uint8_t RADIO_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io);
#endif

/*! \brief Radio driver de-initialization */
void RADIO_Deinit(void);

/*! \brief Radio driver initialization */
void RADIO_Init(void);

#endif /* PL_HAS_RADIO */

#endif /* RADIO_H_ */
