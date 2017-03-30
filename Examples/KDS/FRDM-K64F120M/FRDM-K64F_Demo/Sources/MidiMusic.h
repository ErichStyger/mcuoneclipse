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

/* song numbers, 0, 1, 2, ... */
typedef enum {
  MIDI_SONG_NR_GET_READY,
  MIDI_SONG_NR_PIRATES_OF_CARIBIAN,
  MIDI_SONG_NR_HADDAWAY_WHAT_IS_LOVE,
  MIDI_SONG_NR_GAME_OF_THRONES,
  MIDI_SONG_NR_TETRIS,
  MIDI_SONG_NR_AXEL_F,
  MIDI_SONG_NR_GHOSTBUSTERS,
  MIDI_SONG_NR_JAMES_BOND,
  MIDI_SONG_NR_NOF_SONGS    /* must be last */
} MIDI_SongNr;

void MM_NextSongNumber(void);
void MM_PrevSongNumber(void);
void MM_PlayMusic(int song); /* -1 plays the last/stored song */
void MM_StopPlaying(void);

void MM_Play(MIDI_SongNr song);

uint8_t MM_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io);

void MM_Init(void);

#endif /* PL_HAS_MIDI */

#endif /* MIDIMUSIC_H_ */
