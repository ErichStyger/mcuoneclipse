/**
 * \file
 * \brief Sounder interface.
 * \author Erich Styger, erich.styger@hslu.ch
 * \date 21.03.2011
 *
 * This module implements the driver for the sounder.
 */

#ifndef SOUNDER_H_
#define SOUNDER_H_

#include "Platform.h"

#if PL_HAS_SOUNDER
  /*!
   * \brief Will make the sounder beep for the given time.
   * \param ms Time in milliseconds.
   * \param Hz Frequency in Hz. This is not supported on all targets.
   */
  void SND_Beep(uint16_t ms, uint16_t Hz);

  /*! \brief Sounder initialization */
  void SND_Init(void);
#else
  #define SND_Beep(ms, hz) /* nothing */
  #define SND_Init() /* nothing */
#endif

#endif /* SOUNDER_H_ */
