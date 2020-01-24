/*
 * MidiAxelF.h
 *
 *  Created on: 20.12.2019
 *      Author: Erich Styger
 */

#ifndef MIDISTARWARS_H_
#define MIDISTARWARS_H_

#include "MidiMusic.h"

int StarWars_GetOffset(void);
uint8_t StarWars_NofTracks(void);
uint32_t StarWars_GetTempoUS(void);
uint8_t StarWars_GetMidiMusicInfo(MIDI_MusicTrack *tracks, uint8_t nofTracks);

#endif /* MIDISTARWARS_H_ */
