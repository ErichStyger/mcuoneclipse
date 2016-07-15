/**
 * \file
 * \brief This is the interface to the application entry point.
 * \author (c) 2013 Erich Styger, http://mcuoneclipse.com/
 * \note MIT License (http://opensource.org/licenses/mit-license.html)
 */

#ifndef RNETAPP_H_
#define RNETAPP_H_

#include "Platform.h"
#include "RNWK.h"

#if PL_CONFIG_HAS_SHELL
  #include "CLS1.h"
  uint8_t RNETA_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io);
#endif

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
