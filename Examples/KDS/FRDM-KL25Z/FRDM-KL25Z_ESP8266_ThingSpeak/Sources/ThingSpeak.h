/*
 * ThingSpeak.h
 *
 *      Author: Erich Styger
 */

#ifndef THINGSPEAK_H_
#define THINGSPEAK_H_


#include "CLS1.h"

/*!
 * \brief Command line parser routine
 * \param cmd Pointer to command line string
 * \param handled Return value if command has been handled
 * \param io Standard Shell I/O handler
 * \return Error code, ERR_OK for no failure
 */
uint8_t THING_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io);

/*!
 * \brief Driver initialization
 */
void THING_Deinit(void);

/*!
 * \brief Driver de-initialization
 */
void THING_Init(void);

#endif /* THINGSPEAK_H_ */
