/*
 * ReadyMIDI.c
 *
 *  Created on: 31.12.2014
 *      Author: Erich Styger
 */

#include "Platform.h"
#if PL_HAS_MUSIC
#include "VS1.h"
#include "FRTOS1.h"
#include "MidiMusic.h"
#include "MidiMusicReady.h"
#include "MidiPirate.h"

static bool PlayTrackItem(MIDI_MusicTrack *track, unsigned int currTimeMs, uint8_t channel) {
  uint32_t beatsPerSecond = 2; /* 120 bpm */
  uint32_t currentMillis;
  uint32_t ppqn; /* ticks per beat/quarter note */
  uint32_t tempo = 110;
  uint8_t event;
  unsigned int itemNo;

  ppqn = track->nofTicksPerQuarterNote;
  for(;;) { /* breaks */
    itemNo = track->currLine;
    if (itemNo>=track->nofLines) { /* out of list */
      return FALSE; /* do not continue any more */
    }
    currentMillis = ((uint32_t)track->lines[itemNo].beat*1000UL)/beatsPerSecond;
    currentMillis += ((uint32_t)track->lines[itemNo].tick*60000UL)/ppqn/tempo;
    if (currentMillis>currTimeMs) {
      return TRUE; /* continue */
    }
    event = track->lines[itemNo].event;
    switch(event) {
      case MIDI_BANK:
        VS1_MIDI_SetBank(channel, track->lines[itemNo].val1);
        break;
      case MIDI_NOTE_ON:
        if (track->lines[itemNo].val2==0) { /* note on with velocity zero is a note off */
          VS1_MIDI_NoteOff(channel, track->lines[itemNo].val1, 0);
        } else {
          VS1_MIDI_NoteOn(channel, track->lines[itemNo].val1, track->lines[itemNo].val2);
        }
        break;
      case MIDI_NOTE_OFF:
        VS1_MIDI_NoteOff(channel, track->lines[itemNo].val1, track->lines[itemNo].val2);
        break;
      case MIDI_PATCH:
        VS1_MIDI_SetInstrument(channel, track->lines[itemNo].val1);
        break;
      case MIDI_VOLUME:
        VS1_MIDI_SetVolume(channel, track->lines[itemNo].val1);
        break;
      case MIDI_PAN:
        VS1_MIDI_SetPan(channel, track->lines[itemNo].val1);
        break;
      case MIDI_END_OF_TRACK:
        VS1_MIDI_AllSoundOff(channel);
        break;
    }
    track->currLine++;
  } /* for */
  return TRUE;
}

static void Play(MIDI_MusicTrack *tracks, unsigned int nofTracks) {
  int itemNo;
  uint8_t channel;
  uint32_t currTimeMs;
  TickType_t startTicks;
  unsigned int nofFinished;

  /* init defaults */
  for(channel=0;channel<nofTracks;channel++) {
    VS1_MIDI_SetBank(channel, 0);
    VS1_MIDI_SetInstrument(channel, VS1_MIDI_INSTR_Default);
    VS1_MIDI_SetVolume(channel, 127);
  }
  startTicks = FRTOS1_xTaskGetTickCount();
  itemNo = 0;
  for(;;) { /* breaks */
    currTimeMs = (FRTOS1_xTaskGetTickCount()-startTicks)/portTICK_RATE_MS;
#if 0
    if (currTimeMs>15000) {
      break;
    }
#endif
    nofFinished = 0;
    for(channel=0;channel<nofTracks;channel++) {
      if (!PlayTrackItem(&tracks[channel], currTimeMs, channel)) {
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

void MM_PlayPirate(void) {
#define NOF_TRACKS  8
  MIDI_MusicTrack tracks[NOF_TRACKS];
  uint8_t res;

  if (MPirate_NofTracks()>NOF_TRACKS) {
    for(;;){} /* error */
  }
  res = MPirate_GetMidiMusicInfo(&tracks[0], NOF_TRACKS);
  if (res==ERR_OK) {
    Play(tracks, NOF_TRACKS);
  }
}

void MM_Play(void) {
  MIDI_MusicTrack tracks[2];
  uint8_t res;

  res = MMReady_GetMidiMusicInfo(&tracks[0], sizeof(tracks)/sizeof(tracks[0]));
  if (res==ERR_OK) {
    Play(tracks, sizeof(tracks)/sizeof(tracks[0]));
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
       if (tmp==0) {
         MM_Play();
       } else if (tmp==1) {
         MM_PlayPirate();
       }
     }
     return res;
   }
  return ERR_OK;
}
#endif /* PL_HAS_MUSIC */
