/**
 * \file
 * \brief Interface to the speaker on the PRG_G board.
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * This module implements to functions to use the speaker.
 */

#ifndef BOARD_SPEAKER_H_
#define BOARD_SPEAKER_H_

#include <stdint.h>

/** @addtogroup Speaker
  * @{
  */

/*!
 * \brief callback called from a timer interrupt to run the speaker from an interrupt
 */
void SPEAKER_OnInterrupt(void);

/*!
 * \brief Plays a tone on the speaker. This function will will use interrupts and will not block
 * \param freqHz Frequency in Hz
 */
void SPEAKER_StartPlaying(uint32_t freqHz);

/*! \brief Stops the timer based speaker sound started with SPEAKER_StartPlaying(). */
void SPEAKER_StopPlaying(void);

/*!
 * \brief Plays a tone on the speaker. This function will block for the specified time.
 * \param freqHz Frequency in Hz
 * \param timeMs Time in milliseconds
 */
void SPEAKER_Play(uint32_t freqHz, uint32_t timeMs);

/*!
 * \brief Driver initialization
 */
void SPEAKER_Init(void);

/**
  * @}
  */

#endif /* BOARD_SPEAKER_H_ */
