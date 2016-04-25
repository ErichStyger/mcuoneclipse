/*
 * MidiMusicReady.h
 *
 *  Created on: 01.01.2015
 *      Author: Erich Styger
 */

#ifndef MIDIMUSICREADY_H_
#define MIDIMUSICREADY_H_

#include "MidiMusic.h"

int MMReady_GetOffset(void);
uint8_t MMReady_NofTracks(void);
uint32_t MMReady_GetTempoUS(void);
uint8_t MMReady_GetMidiMusicInfo(MIDI_MusicTrack *tracks, uint8_t nofTracks);

#endif /* MIDIMUSICREADY_H_ */
