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

typedef enum { /* bits are used for FreeRTOS direct task notifications */
  MIDI_SONG_GET_READY = (1<<0),
  MIDI_SONG_PIRATES_OF_CARIBIAN = (1<<1),
  MIDI_SONG_HADDAWAY_WHAT_IS_LOVE = (1<<2),
  MIDI_SONG_GAME_OF_THRONES = (1<<3),
  MIDI_SONG_TETRIS = (1<<4) ,
  MIDI_SONG_AXEL_F = (1<<5),
  MIDI_SONG_GHOSTBUSTERS = (1<<6),
  MIDI_SONG_JAMES_BOND = (1<<7),
  MIDI_SONG_START = (1<<30),
  MIDI_SONG_STOP = (1<<31)
} MIDI_Song;
#define MIDI_NOF_SONGS  8

void MM_PlayMusic(int song); /* -1 plays the last/stored song */
void MM_StopPlaying(void);

void MM_Play(MIDI_Song song);

uint8_t MM_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io);

void MM_Init(void);

#endif /* PL_HAS_MIDI */

#endif /* MIDIMUSIC_H_ */
