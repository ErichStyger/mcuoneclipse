/*
 * MidiMusic.h
 *
 *  Created on: 01.01.2015
 *      Author: Erich Styger
 */

#ifndef MIDIMUSIC_H_
#define MIDIMUSIC_H_

#include "PE_Types.h"

typedef enum {
  MIDI_BANK,
  MIDI_PATCH,
  MIDI_NOTE_ON,
  MIDI_NOTE_OFF,
  MIDI_PAN,
  MIDI_VOLUME,
  MIDI_END_OF_TRACK
} MIDI_MusicMsg;

typedef struct {
  /* channel, note, velocity */
  uint16_t beat, tick; /* 00003:192 */
  MIDI_MusicMsg event;      /* NOTE_ON  */
  uint8_t val1;        /* G4 */
  uint8_t val2;        /* 127 */
} MIDI_MusicLine;

typedef struct {
  const MIDI_MusicLine *lines;
  uint32_t nofLines;
  uint32_t currLine;
} MIDI_MusicTrack;

void MM_Play(void);

#endif /* MIDIMUSIC_H_ */
