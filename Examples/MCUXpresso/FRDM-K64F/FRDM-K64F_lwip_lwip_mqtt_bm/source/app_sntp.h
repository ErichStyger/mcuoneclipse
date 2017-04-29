/*
 * app_sntp.h
 *
 *  Created on: 29.04.2017
 *      Author: Erich Styger Local
 */

#ifndef APP_SNTP_H_
#define APP_SNTP_H_

#include "netif.h"
#if CONFIG_USE_SHELL
  #include "CLS1.h"

  uint8_t SNTP_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io);
#endif

/*!
 * \brief Initiate new time/date request
 */
uint8_t SNTP_InitiateRequest(void);

void SNTP_Init(void);

#endif /* APP_SNTP_H_ */
