/*
 * MidiMusic.h
 *
 *  Created on: 01.01.2015
 *      Author: Erich Styger
 */

#ifndef MIDIMUSIC_H_
#define MIDIMUSIC_H_

#include "Platform.h"
#if PL_HAS_MIDI
#include "CLS1.h"

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
  uint16_t beat;
  uint32_t tick; /* 00003:192 */
  MIDI_MusicMsg event; /* NOTE_ON  */
  uint8_t val1;        /* G4 */
  uint8_t val2;        /* 127 */
} MIDI_MusicLine;

typedef struct {
  uint16_t nofTicksPerQuarterNote;
  const MIDI_MusicLine *lines;
  uint32_t nofLines;
  uint32_t currLine;
} MIDI_MusicTrack;

void MM_Play(int song);

uint8_t MM_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io);
#endif /* PL_HAS_MIDI */

#endif /* MIDIMUSIC_H_ */
