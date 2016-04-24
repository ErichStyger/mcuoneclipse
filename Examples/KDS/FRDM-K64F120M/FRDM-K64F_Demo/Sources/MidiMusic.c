/*
 * ReadyMIDI.c
 *
 *  Created on: 31.12.2014
 *      Author: Erich Styger
 */

#include "Platform.h"
#if PL_HAS_MUSIC
#include "Floppy.h"
#include "FRTOS1.h"
#include "Midi.h"
#include "MidiMusic.h"
#include "MidiMusicReady.h"
#include "MidiPirate.h"
#include "MidiHaddaway.h"

static bool PlayTrackItem(MIDI_MusicTrack *track, uint32_t currTimeMs, uint8_t channel, uint32_t tempoUS) {
  uint32_t beatsPerSecond;
  uint32_t currentMillis;
  uint32_t ppqn; /* ticks per beat/quarter note */
  uint8_t event;
  uint32_t itemNo;

  beatsPerSecond = 1000000/tempoUS; /* (1'000'000*(1/tmpoUS)*60)/60) */
  ppqn = track->nofTicksPerQuarterNote;
  for(;;) { /* breaks */
    itemNo = track->currLine;
    if (itemNo>=track->nofLines) { /* out of list */
      return FALSE; /* do not continue any more */
    }
    currentMillis = ((uint32_t)track->lines[itemNo].beat*1000UL)/beatsPerSecond;
    currentMillis += ((uint32_t)track->lines[itemNo].tick*(tempoUS/1000))/ppqn;
    if (currentMillis>currTimeMs) {
      return TRUE; /* continue */
    }
    event = track->lines[itemNo].event;
    switch(event) {
      case MIDI_BANK:
        FLOPPY_MIDI_SetBank(channel, track->lines[itemNo].val1);
        break;
      case MIDI_NOTE_ON:
        if (track->lines[itemNo].val2==0) { /* note on with velocity zero is a note off */
          FLOPPY_MIDI_NoteOff(channel, track->lines[itemNo].val1, 0);
        } else {
          FLOPPY_MIDI_NoteOn(channel, track->lines[itemNo].val1, track->lines[itemNo].val2);
        }
        break;
      case MIDI_NOTE_OFF:
        FLOPPY_MIDI_NoteOff(channel, track->lines[itemNo].val1, track->lines[itemNo].val2);
        break;
      case MIDI_PATCH:
        FLOPPY_MIDI_SetInstrument(channel, track->lines[itemNo].val1);
        break;
      case MIDI_VOLUME:
        FLOPPY_MIDI_SetVolume(channel, track->lines[itemNo].val1);
        break;
      case MIDI_PAN:
        FLOPPY_MIDI_SetPan(channel, track->lines[itemNo].val1);
        break;
      case MIDI_END_OF_TRACK:
        FLOPPY_MIDI_AllSoundOff(channel);
        break;
    }
    track->currLine++;
  } /* for */
  return TRUE;
}

static void Play(MIDI_MusicTrack *tracks, unsigned int nofTracks, uint32_t tempoUS) {
  int itemNo;
  uint8_t channel;
  uint32_t currTimeMs;
  TickType_t startTicks;
  unsigned int nofFinished;

  /* init defaults */
  for(channel=0;channel<nofTracks;channel++) {
    FLOPPY_MIDI_SetBank(channel, 0);
    FLOPPY_MIDI_SetInstrument(channel, 0);
    FLOPPY_MIDI_SetVolume(channel, 127);
  }
  startTicks = FRTOS1_xTaskGetTickCount();
  itemNo = 0;
  for(;;) { /* breaks */
    currTimeMs = (FRTOS1_xTaskGetTickCount()-startTicks)/portTICK_RATE_MS;
    nofFinished = 0;
    for(channel=0;channel<nofTracks;channel++) {
      if (!PlayTrackItem(&tracks[channel], currTimeMs, channel, tempoUS)) {
        nofFinished++;
      }
    }
    if (nofFinished==nofTracks) { /* all finished */
      break;
    }
    FRTOS1_vTaskDelay(1/portTICK_RATE_MS);
    itemNo++;
  }
}

#define SONG_GET_READY 0
#define SONG_PIRATES   1
#define SONG_HADDAWAY  2

void MM_Play(int song) {
  #define MAX_NOF_TRACKS  8
  MIDI_MusicTrack tracks[MAX_NOF_TRACKS];
  uint8_t res;
  uint8_t nofTracks;
  uint32_t tempoUS;

  if (song==SONG_GET_READY) {
    nofTracks = MMReady_NofTracks();
  } else if (song==SONG_PIRATES) {
    nofTracks = MPirate_NofTracks();
  } else if (song==SONG_HADDAWAY) {
    nofTracks = MHaddaway_NofTracks();
  } else {
    return; /* error */
  }
  if (nofTracks>MAX_NOF_TRACKS) {
    return; /* error */
  }
  if (song==SONG_GET_READY) {
    res = MMReady_GetMidiMusicInfo(&tracks[0], nofTracks);
    tempoUS = MMReady_GetTempoUS();
  } else if (song==SONG_PIRATES) {
    res = MPirate_GetMidiMusicInfo(&tracks[0], nofTracks);
    tempoUS = MPirate_GetTempoUS();
  } else if (song==SONG_HADDAWAY) {
    res = MHaddaway_GetMidiMusicInfo(&tracks[0], nofTracks);
    tempoUS = MHaddaway_GetTempoUS();
  }
  if (res==ERR_OK) {
    Play(tracks, nofTracks, tempoUS);
  }
}

static uint8_t PrintStatus(CLS1_ConstStdIOType *io) {
  CLS1_SendStatusStr((unsigned char*)"midi", (const unsigned char*)"\r\n", io->stdOut);
  return ERR_OK;
}

uint8_t MM_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io) {
  const uint8_t *p;
  uint8_t res;
  int32_t tmp;

  if (UTIL1_strcmp((char*)cmd, CLS1_CMD_HELP)==0 || UTIL1_strcmp((char*)cmd, "midi help")==0) {
     CLS1_SendHelpStr((unsigned char*)"midi", (const unsigned char*)"Group of midi commands\r\n", io->stdOut);
     CLS1_SendHelpStr((unsigned char*)"  help|status", (unsigned char*)"Print help or status information\r\n", io->stdOut);
     CLS1_SendHelpStr((unsigned char*)"  play <number>", (const unsigned char*)"Play midi song (0, 1)\r\n", io->stdOut);
     *handled = TRUE;
     return ERR_OK;
   } else if ((UTIL1_strcmp((char*)cmd, CLS1_CMD_STATUS)==0) || (UTIL1_strcmp((char*)cmd, "midi status")==0)) {
     *handled = TRUE;
     return PrintStatus(io);
   } else if (UTIL1_strncmp((char*)cmd, "midi play", sizeof("midi play")-1)==0) {
     p = cmd+sizeof("midi play")-1;
     res = UTIL1_xatoi(&p, &tmp);
     if (res==ERR_OK && tmp>=0) {
       *handled = TRUE;
       if (tmp==SONG_GET_READY) {
         MM_Play(SONG_GET_READY);
       } else if (tmp==SONG_PIRATES) {
         MM_Play(SONG_PIRATES);
       } else if (tmp==SONG_HADDAWAY) {
         MM_Play(SONG_HADDAWAY);
       }
     }
     return res;
   }
  return ERR_OK;
}
#endif /* PL_HAS_MUSIC */
