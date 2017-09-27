/*
 * MidiBond.h
 *
 *  Created on: 01.01.2015
 *      Author: Erich Styger
 */

#ifndef MIDIBOND_H_
#define MIDIBOND_H_

#include "MidiMusic.h"

int MBond_GetOffset(void);
uint8_t MBond_NofTracks(void);
uint32_t MBond_GetTempoUS(void);
uint8_t MBond_GetMidiMusicInfo(MIDI_MusicTrack *tracks, uint8_t nofTracks);

#endif /* MIDIBOND_H_ */
