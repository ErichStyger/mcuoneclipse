/*
 * Tetris.h
 *
 *  Created on: 01.01.2015
 *      Author: Erich Styger
 */

#ifndef MIDITETRIS_H_
#define MIDITETRIS_H_

#include "MidiMusic.h"

int MTetris_GetOffset(void);
uint8_t MTetris_NofTracks(void);
uint32_t MTetris_GetTempoUS(void);
uint8_t MTetris_GetMidiMusicInfo(MIDI_MusicTrack *tracks, uint8_t nofTracks);

#endif /* MIDITETRIS_H_ */
