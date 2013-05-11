/**
 * \file
 * \brief Radio Module
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * Interface to handle everything around the radio transceiver
 */

#ifndef RADIO_H_
#define RADIO_H_

#include "Platform.h"

#if PL_HAS_RADIO
#if 0
#include "FSSH1.h"
#include "SMAC1.h"
#endif
#include "Event.h"

/*! \brief Event called in case of radio transceiver reset */
void RADIO_ResetIndication(void);

/*! 
 * \brief Event called on reception of a data packet
 * \param[in] sRxPacket Pointer to the data packet received
 */
void RADIO_DataIndicationPacket(tRxPacket *sRxPacket);

#if 0
/*!
 * \brief Parses a command
 * \param cmd Command string to be parsed
 * \param handled Sets this variable to TRUE if command was handled
 * \param io I/O stream to be used for input/output
 * \return Error code, ERR_OK if everything was fine
 */
uint8_t RADIO_ParseCommand(const unsigned char *cmd, bool *handled, const FSSH1_StdIOType *io);
#endif

/*!
 * \brief Event handler for Radio events. Needs to be called as part of the normal event handling
 * \param[in] event Event to be processed
 */
void RADIO_AppHandleEvent(EVNT_Handle event);

/*! \brief Handler to deal with the Radio state machine. Needs to be called periodically to advance the state machine */
void RADIO_Handle(void);

/*! 
 * \brief Sends a data packet trough the Radio
 * \param[in] data Data to be sent (binary), zero terminated
*/
void RADIO_SendString(const char *data);

void RADIO_SendStringRaw(const char *data);

/*! \brief Radio driver initialization */
void RADIO_Init(void);

#endif /* PL_HAS_RADIO */

#endif /* RADIO_H_ */
