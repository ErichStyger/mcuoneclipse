/*
 * MidiGameOfThrones.h
 *
 *  Created on: 01.01.2015
 *      Author: Erich Styger
 */

#ifndef MIDIGAMEOFTHRONES_H_
#define MIDIGAMEOFTHRONES_H_

#include "MidiMusic.h"

int MGameOfThrones_GetOffset(void);
uint8_t MGameOfThrones_NofTracks(void);
uint32_t MGameOfThrones_GetTempoUS(void);
uint8_t MGameOfThrones_GetMidiMusicInfo(MIDI_MusicTrack *tracks, uint8_t nofTracks);

#endif /* MIDIGAMEOFTHRONES_H_ */
