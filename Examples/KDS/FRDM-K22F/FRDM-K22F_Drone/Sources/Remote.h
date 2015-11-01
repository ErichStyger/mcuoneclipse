/*
 * Remote.h
 *
 *  Created on: 31.10.2015
 *      Author: tastyger
 */

#ifndef SOURCES_REMOTE_H_
#define SOURCES_REMOTE_H_

#include "Platform.h"

#if PL_HAS_SHELL
#include "CLS1.h"
/*!
 * \brief Shell command line parser.
 * \param[in] cmd Pointer to command string
 * \param[out] handled If command is handled by the parser
 * \param[in] io Std I/O handler of shell
 */
uint8_t REMOTE_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io);
#endif /* PL_HAS_SHELL */

uint8_t REMOTE_GetChannel(uint8_t channel, uint16_t *val);

void REMOTE_Init(void);

#endif /* SOURCES_REMOTE_H_ */
