/**
 * \file
 * \brief This is the interface to the Nordic Semiconductor nRF24L01+
 * \author (c) 2013-2019 Erich Styger, http://mcuoneclipse.com/
 * \note MIT License (http://opensource.org/licenses/mit-license.html), see 'RNet_License.txt'
 *
 * This module deals with the low level interface of the transceiver.
 */

#ifndef RADIO_H_
#define RADIO_H_

#include "McuRNetConfig.h"

#include "McuShell.h"
/*!
 * \brief Parses a command
 * \param cmd Command string to be parsed
 * \param handled Sets this variable to TRUE if command was handled
 * \param io I/O stream to be used for input/output
 * \return Error code, ERR_OK if everything was fine
 */
uint8_t RADIO_ParseCommand(const unsigned char *cmd, bool *handled, const McuShell_StdIOType *io);

/*!
 * \brief Set the radio communication channel
 * \param channel New channel number.
 * \return Error code, ERR_OK if everything is fine.
 */
uint8_t RADIO_SetChannel(uint8_t channel);

/*!
 * \brief Determine if the radio transceiver is in a good shape. Radio transceiver could be affected by voltage drop.
 * \return ERR_OK
 */
uint8_t RADIO_IsSane(void);

/*! 
 * \brief Radio power-on initialization.
 * \return Error code, ERR_OK if everything is ok.
 */
uint8_t RADIO_PowerUp(void);

/*! 
 * \brief Function to determine if we could power down the radio.
 * \return TRUE if there is no transmission pending so we can power down the radio.
 */
bool RADIO_CanDoPowerDown(void);

/*! 
 * \brief Power down the radio.
 * \return Error code, ERR_OK if everything is ok.
 */
uint8_t RADIO_PowerDown(void);

/*!
 * \brief Processes the radio state machine. Needs to be called frequently from the application (about every 10 ms).
 * \return Error code, ERR_OK for no failure.
 */
uint8_t RADIO_Process(void);

/*!
 * \brief Flushes the internal radio queues.
 * \return Error code, ERR_OK for no failure.
 */
uint8_t RADIO_FlushQueues(void);

/*! \brief Radio transceiver initialization */
void RADIO_Init(void);

/*! \brief Radio transceiver de-initialization */
void RADIO_Deinit(void);

#endif /* RADIO_H_ */

