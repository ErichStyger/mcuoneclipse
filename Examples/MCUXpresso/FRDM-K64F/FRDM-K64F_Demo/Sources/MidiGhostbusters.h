/*
 * MidiGhostbusters.h
 *
 *  Created on: 01.01.2015
 *      Author: Erich Styger
 */

#ifndef MIDIGHOSTBUSTERS_H_
#define MIDIGHOSTBUSTERS_H_

#include "MidiMusic.h"

int MGhostbusters_GetOffset(void);
uint8_t MGhostbusters_NofTracks(void);
uint32_t MGhostbusters_GetTempoUS(void);
uint8_t MGhostbusters_GetMidiMusicInfo(MIDI_MusicTrack *tracks, uint8_t nofTracks);

#endif /* MIDIGHOSTBUSTERS_H_ */
