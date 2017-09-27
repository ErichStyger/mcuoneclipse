/**
 * \file
 * \brief This is the interface to the application entry point.
 * \author (c) 2016 Erich Styger, http://mcuoneclipse.com/
 * \note MIT License (http://opensource.org/licenses/mit-license.html)
 */

#ifndef RNETAPP_H_
#define RNETAPP_H_

#include "Platform.h"
#include "RNWK.h"
#include "RApp.h"

#if PL_CONFIG_HAS_SHELL
  #include "CLS1.h"
  uint8_t RNETA_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io);
#endif

/*!
 * \brief Sends a 16bit ID plus 32bit value pair
 * \param msgType Message type
 * \param id Message ID
 * \param value Message value
 * \param addr Remote node address
 * \param flags Network flags, like request for acknowledge
 * \return Error code, ERR_OK if no failure.
 */
uint8_t RNETA_SendIdValuePairMessage(uint8_t msgType, uint16_t id, uint32_t value, RAPP_ShortAddrType addr, RAPP_FlagsType flags);

/*!
 * \brief Return the current remote node address.
 * \return Remote node address
 */
RNWK_ShortAddrType RNETA_GetDestAddr(void);

/*! \brief Driver de-initialization */
void RNETA_Deinit(void);

/*! \brief Driver initialization */
void RNETA_Init(void);

#endif /* RNETAPP_H_ */
