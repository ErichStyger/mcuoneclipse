/*
 * MidiMusicReady.h
 *
 *  Created on: 01.01.2015
 *      Author: Erich Styger
 */

#ifndef MIDIMUSIPIRATE_H_
#define MIDIMUSIPIRATE_H_

#include "MidiMusic.h"

uint8_t MPirate_NofTracks(void);
uint32_t MPirate_GetTempoUS(void);
uint8_t MPirate_GetMidiMusicInfo(MIDI_MusicTrack *tracks, uint8_t nofTracks);

#endif /* MIDIMUSIPIRATE_H_ */
