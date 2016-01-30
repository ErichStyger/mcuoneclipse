/*
 * Platform.h
 *
 *  Created on: 27.11.2014
 *      Author: tastyger
 */

#ifndef PLATFORM_H_
#define PLATFORM_H_

#include "PE_Types.h"

#define PL_HAS_NEO_SHIELD (1) /* if we have the NeoShield with RTC */
#define PL_HAS_NEO_PIXEL  (1 && PL_HAS_NEO_SHIELD)
#define PL_HAS_RTC        (1 && PL_HAS_NEO_SHIELD)
#define PL_NEO_DEMO       (0 && PL_HAS_NEO_PIXEL) /* demo of neo pixels on stripe */
#define PL_HAS_LED3       (0 && !PL_HAS_NEO_PIXEL) /* blue LED PWM conflicts with NeoPixel timer */
#define PL_HAS_RNET       (0) /* has RNET with nRF24L01+ */
#define PL_HAS_PONG       (0) /* Pong game */
#define PL_HAS_MUSIC      (0) /* music shield */
#define PL_HAS_MIDI       (1 && PL_HAS_MUSIC)
#define PL_HAS_MP3        (1 && !PL_HAS_MIDI)
#define PL_HAS_SD_CARD    (0) /* has SD card */
#define PL_HAS_KEYS       (0) /* has push buttons */
#define PL_HAS_LEFT_BTN   (1 && PL_HAS_KEYS)
#define PL_HAS_RIGHT_BTN  (0 && PL_HAS_KEYS)
#define PL_HAS_MAZE_RACE  (0) /* has functions for the Sumo Maze race */
#define PL_HAS_LED_CUBE   (1)

#endif /* PLATFORM_H_ */
