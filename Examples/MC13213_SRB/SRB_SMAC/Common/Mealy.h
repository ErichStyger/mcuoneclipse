/**
 * \file
 * \brief This is the interface to the Mealy Sequential State Machine
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * We are using a Mealy Sequential Machine to test the LED driver.
 */

#ifndef __MEALY_H_
#define __MEALY_H_

#include "Platform.h"

#if PL_HAS_SHELL
  #include "CLS1.h"

/*!
   * \brief Parses a command from the shell
   * \param cmd Command string to be parsed
   * \param handled Sets this variable to TRUE if command was handled
   * \param io I/O stream to be used for input/output
   * \return Error code, ERR_OK if everything was fine
   */
  uint8_t MEALY_ParseCommand(const char *cmd, bool *handled, const CLS1_StdIOType *io);
#endif


/*! \brief This implements our Mealy Sequential Machine. */
void MEALY_Run(void);

/*! \brief Initialization routine of the state machine */
void MEALY_Init(void);

#endif /*__MEALY_H_*/
