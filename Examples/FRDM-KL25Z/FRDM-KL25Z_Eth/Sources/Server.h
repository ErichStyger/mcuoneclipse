/**
 * \file
 * \brief Interface for HTTP server using W5100.
 * \author (c) 2014 Erich Styger, http://mcuoneclipse.com/
 * \note MIT License (http://opensource.org/licenses/mit-license.html).
 * Credits to:
 * - http://www.ermicro.com/blog/?p=1773
 * - http://www.seanet.com/~karllunt/w5100_library.html
 *
 * This module implements a web/HTTP server with Wiztronic W5100 Ethernet chip.
 */

#ifndef SERVER_H_
#define SERVER_H_

#include "PE_Types.h"

/*!
 * \brief Server main process. Needs to be called frequently from the application.
 * \param socket Socket number, 0 to 4
 */
void SERVER_Process(uint8_t socket);

/*!
 * \brief Driver dinitialization.
 */
void SERVER_Init(void);

/*!
 * \brief Driver de-initialization.
 */
void SERVER_Deinit(void);

#endif /* SERVER_H_ */
