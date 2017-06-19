/*
 * MidiAxelF.h
 *
 *  Created on: 01.01.2015
 *      Author: Erich Styger
 */

#ifndef MIDIAXELF_H_
#define MIDIAXELF_H_

#include "MidiMusic.h"

int MAxelF_GetOffset(void);
uint8_t MAxelF_NofTracks(void);
uint32_t MAxelF_GetTempoUS(void);
uint8_t MAxelF_GetMidiMusicInfo(MIDI_MusicTrack *tracks, uint8_t nofTracks);

#endif /* MIDIAXELF_H_ */
