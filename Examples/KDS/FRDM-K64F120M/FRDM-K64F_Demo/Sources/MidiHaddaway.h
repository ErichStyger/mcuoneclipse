/*
 * Haddaway.h
 *
 *  Created on: 01.01.2015
 *      Author: Erich Styger
 */

#ifndef MIDIHADDAWAY_H_
#define MIDIHADDAWAY_H_

#include "MidiMusic.h"

uint8_t MHaddaway_NofTracks(void);
uint32_t MHaddaway_GetTempoUS(void);
uint8_t MHaddaway_GetMidiMusicInfo(MIDI_MusicTrack *tracks, uint8_t nofTracks);

#endif /* MIDIHADDAWAY_H_ */
