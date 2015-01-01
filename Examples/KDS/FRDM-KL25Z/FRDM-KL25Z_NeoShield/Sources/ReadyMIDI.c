/*
 * ReadyMIDI.c
 *
 *  Created on: 31.12.2014
 *      Author: tastyger
 */

#include "Platform.h"
#include "VS1.h"
#include "FRTOS1.h"

typedef enum {
  MIDI_BANK,
  MIDI_PATCH,
  MIDI_NOTE_ON,
  MIDI_NOTE_OFF,
  MIDI_PAN,
  MIDI_VOLUME,
  MIDI_END_OF_TRACK
} MIDI_Msg;

typedef struct {
  /* channel, note, velocity */
  uint16_t beat, tick; /* 00003:192 */
  MIDI_Msg event;      /* NOTE_ON  */
  uint8_t val1;        /* G4 */
  uint8_t val2;        /* 127 */
} MIDI_Line;

typedef struct {
  const MIDI_Line *lines;
  uint32_t nofLines;
  uint32_t currLine;
} MIDI_Track;

static const MIDI_Line song_ch0[] =
{
/* beat,ticks, event,          note,              value */
  {0,  0, MIDI_BANK,      0, 0},
  {0,  0, MIDI_PATCH,     VS1_MIDI_INSTR_Default, 0},
  {0,  0, MIDI_PAN,       64, 0},
  {0,  0, MIDI_VOLUME,    127, 0},
  {0,  0, MIDI_NOTE_ON ,  VS1_MIDI_NOTE_Fh6, 127},
  {0, 64, MIDI_NOTE_OFF,  VS1_MIDI_NOTE_Fh6, 100},
  {0, 96, MIDI_NOTE_ON ,  VS1_MIDI_NOTE_G6 , 127},
  {0,160, MIDI_NOTE_OFF,  VS1_MIDI_NOTE_G6 , 100},
  {0,192, MIDI_NOTE_ON ,  VS1_MIDI_NOTE_G6 , 127},
  {0,256, MIDI_NOTE_OFF,  VS1_MIDI_NOTE_G6 , 100},
  {0,288, MIDI_NOTE_ON ,  VS1_MIDI_NOTE_G6 , 127},
  {0,352, MIDI_NOTE_OFF,  VS1_MIDI_NOTE_G6 , 100},
  {1,  0, MIDI_NOTE_ON ,  VS1_MIDI_NOTE_Fh5, 127},
  {1, 64, MIDI_NOTE_OFF,  VS1_MIDI_NOTE_Fh5, 100},
  {1, 96, MIDI_NOTE_ON ,  VS1_MIDI_NOTE_G5 , 127},
  {1,160, MIDI_NOTE_OFF,  VS1_MIDI_NOTE_G5 , 100},
  {1,192, MIDI_NOTE_ON ,  VS1_MIDI_NOTE_G5 , 127},
  {1,256, MIDI_NOTE_OFF,  VS1_MIDI_NOTE_G5 , 100},
  {1,288, MIDI_NOTE_ON ,  VS1_MIDI_NOTE_G5 , 127},
  {1,352, MIDI_NOTE_OFF,  VS1_MIDI_NOTE_G5 , 100},
  {2,  0, MIDI_NOTE_ON ,  VS1_MIDI_NOTE_Fh4, 127},
  {2, 64, MIDI_NOTE_OFF,  VS1_MIDI_NOTE_Fh4, 100},
  {2, 96, MIDI_NOTE_ON ,  VS1_MIDI_NOTE_G4 , 127},
  {2,160, MIDI_NOTE_OFF,  VS1_MIDI_NOTE_G4 , 100},
  {2,192, MIDI_NOTE_ON ,  VS1_MIDI_NOTE_G4 , 127},
  {2,256, MIDI_NOTE_OFF,  VS1_MIDI_NOTE_G4 , 100},
  {2,288, MIDI_NOTE_ON ,  VS1_MIDI_NOTE_G4 , 127},
  {2,352, MIDI_NOTE_OFF,  VS1_MIDI_NOTE_G4 , 100},
  {3,192, MIDI_NOTE_ON ,  VS1_MIDI_NOTE_G6 , 127},
  {3,256, MIDI_NOTE_OFF,  VS1_MIDI_NOTE_G6 , 100},
  {3,288, MIDI_NOTE_ON ,  VS1_MIDI_NOTE_G6 , 127},
  {3,352, MIDI_NOTE_OFF,  VS1_MIDI_NOTE_G6 , 100},
  {4,  0, MIDI_NOTE_ON ,  VS1_MIDI_NOTE_G6 , 127},
  {4, 64, MIDI_NOTE_OFF,  VS1_MIDI_NOTE_G6 , 100},
  {4, 96, MIDI_NOTE_ON ,  VS1_MIDI_NOTE_G6 , 127},
  {4,160, MIDI_NOTE_OFF,  VS1_MIDI_NOTE_G6 , 100},
  {4,288, MIDI_NOTE_ON ,  VS1_MIDI_NOTE_E6 , 127},
  {4,352, MIDI_NOTE_OFF,  VS1_MIDI_NOTE_E6 , 100},
  {5, 96, MIDI_NOTE_ON ,  VS1_MIDI_NOTE_G6 , 127},
  {5,160, MIDI_NOTE_OFF,  VS1_MIDI_NOTE_G6 , 100},
  {5,192, MIDI_NOTE_ON ,  VS1_MIDI_NOTE_E6 , 127},
  {5,256, MIDI_NOTE_OFF,  VS1_MIDI_NOTE_E6 , 100},
  {6,  0, MIDI_NOTE_ON ,  VS1_MIDI_NOTE_G6 , 127},
  {6, 64, MIDI_NOTE_OFF,  VS1_MIDI_NOTE_G6 , 100},
  {6, 96, MIDI_NOTE_ON ,  VS1_MIDI_NOTE_A6 , 127},
  {6,160, MIDI_NOTE_OFF,  VS1_MIDI_NOTE_A6 , 100},
  {6,192, MIDI_NOTE_ON ,  VS1_MIDI_NOTE_E6 , 127},
  {6,256, MIDI_NOTE_OFF,  VS1_MIDI_NOTE_E6 , 100},
  {6,288, MIDI_NOTE_ON ,  VS1_MIDI_NOTE_E6 , 127},
  {6,352, MIDI_NOTE_OFF,  VS1_MIDI_NOTE_E6 , 100},
  {7,  0, MIDI_NOTE_ON ,  VS1_MIDI_NOTE_E6 , 127},
  {7, 64, MIDI_NOTE_OFF,  VS1_MIDI_NOTE_E6 , 100},
  {7,192, MIDI_NOTE_ON ,  VS1_MIDI_NOTE_D6 , 127},
  {7,256, MIDI_NOTE_OFF,  VS1_MIDI_NOTE_D6 , 100},
  {7,288, MIDI_NOTE_ON ,  VS1_MIDI_NOTE_C6 , 127},
  {7,352, MIDI_NOTE_OFF,  VS1_MIDI_NOTE_C6 , 100},
  {8, 96, MIDI_NOTE_ON ,  VS1_MIDI_NOTE_Ch6, 127},
  {8,160, MIDI_NOTE_OFF,  VS1_MIDI_NOTE_Ch6, 100},
  {8,288, MIDI_NOTE_ON ,  VS1_MIDI_NOTE_G5 , 127},
  {8,352, MIDI_NOTE_OFF,  VS1_MIDI_NOTE_G5 , 100},
  {9, 96, MIDI_NOTE_ON ,  VS1_MIDI_NOTE_Ch6, 127},
  {9,160, MIDI_NOTE_OFF,  VS1_MIDI_NOTE_Ch6, 100},
  {9,192, MIDI_NOTE_ON ,  VS1_MIDI_NOTE_G5 , 127},
  {9,256, MIDI_NOTE_OFF,  VS1_MIDI_NOTE_G5 , 100},
  {10,  0, MIDI_NOTE_ON,   VS1_MIDI_NOTE_Ch6, 127},
  {10, 64, MIDI_NOTE_OFF,  VS1_MIDI_NOTE_Ch6, 100},
  {10,192, MIDI_NOTE_ON ,  VS1_MIDI_NOTE_D6 , 127},
  {10,256, MIDI_NOTE_OFF,  VS1_MIDI_NOTE_D6 , 100},
  {10,288, MIDI_NOTE_ON ,  VS1_MIDI_NOTE_D6 , 127},
  {10,352, MIDI_NOTE_OFF,  VS1_MIDI_NOTE_D6 , 100},
  {11,  0, MIDI_NOTE_ON ,  VS1_MIDI_NOTE_D6 , 127},
  {11,256, MIDI_NOTE_OFF,  VS1_MIDI_NOTE_D6 , 100},
  {11,256, MIDI_END_OF_TRACK, 0,  0}
};

static const MIDI_Line song_ch1[] =
{
/* beat,ticks, event,          note,              value */
  {0,  0, MIDI_BANK,      0, 0},
  {0,  0, MIDI_PATCH ,    VS1_MIDI_INSTR_Default, 0},
  {0,  0, MIDI_PAN,       64,                  0},
  {0,  0, MIDI_VOLUME,    127,                 0},
  {3,192, MIDI_NOTE_ON ,  VS1_MIDI_NOTE_G4 , 127},
  {3,256, MIDI_NOTE_OFF,  VS1_MIDI_NOTE_G4 , 100},
  {3,288, MIDI_NOTE_ON ,  VS1_MIDI_NOTE_A4 , 127},
  {3,352, MIDI_NOTE_OFF,  VS1_MIDI_NOTE_A4 , 100},
  {4,  0, MIDI_NOTE_ON ,  VS1_MIDI_NOTE_B4 , 127},
  {4, 64, MIDI_NOTE_OFF,  VS1_MIDI_NOTE_B4 , 100},
  {4, 96, MIDI_NOTE_ON ,  VS1_MIDI_NOTE_C5 , 127},
  {4,160, MIDI_NOTE_OFF,  VS1_MIDI_NOTE_C5 , 100},
  {4,192, MIDI_NOTE_ON ,  VS1_MIDI_NOTE_G4 , 127},
  {4,256, MIDI_NOTE_OFF,  VS1_MIDI_NOTE_G4 , 100},
  {4,288, MIDI_NOTE_ON ,  VS1_MIDI_NOTE_C5 , 127},
  {4,352, MIDI_NOTE_OFF,  VS1_MIDI_NOTE_C5 , 100},
  {5,  0, MIDI_NOTE_ON ,  VS1_MIDI_NOTE_G4 , 127},
  {5, 64, MIDI_NOTE_OFF,  VS1_MIDI_NOTE_G4 , 100},
  {5, 96, MIDI_NOTE_ON ,  VS1_MIDI_NOTE_C5 , 127},
  {5,160, MIDI_NOTE_OFF,  VS1_MIDI_NOTE_C5 , 100},
  {5,192, MIDI_NOTE_ON ,  VS1_MIDI_NOTE_G4 , 127},
  {5,256, MIDI_NOTE_OFF,  VS1_MIDI_NOTE_G4 , 100},
  {5,288, MIDI_NOTE_ON ,  VS1_MIDI_NOTE_C5 , 127},
  {5,352, MIDI_NOTE_OFF,  VS1_MIDI_NOTE_C5 , 100},
  {6,  0, MIDI_NOTE_ON ,  VS1_MIDI_NOTE_G4 , 127},
  {6, 64, MIDI_NOTE_OFF,  VS1_MIDI_NOTE_G4 , 100},
  {6, 96, MIDI_NOTE_ON ,  VS1_MIDI_NOTE_C5 , 127},
  {6,160, MIDI_NOTE_OFF,  VS1_MIDI_NOTE_C5 , 100},
  {6,192, MIDI_NOTE_ON ,  VS1_MIDI_NOTE_G4 , 127},
  {6,256, MIDI_NOTE_OFF,  VS1_MIDI_NOTE_G4 , 100},
  {6,288, MIDI_NOTE_ON ,  VS1_MIDI_NOTE_C5 , 127},
  {6,352, MIDI_NOTE_OFF,  VS1_MIDI_NOTE_C5 , 100},
  {7,  0, MIDI_NOTE_ON ,  VS1_MIDI_NOTE_G4 , 127},
  {7, 64, MIDI_NOTE_OFF,  VS1_MIDI_NOTE_G4 , 100},
  {7, 96, MIDI_NOTE_ON ,  VS1_MIDI_NOTE_C5 , 127},
  {7,160, MIDI_NOTE_OFF,  VS1_MIDI_NOTE_C5 , 100},
  {7,192, MIDI_NOTE_ON ,  VS1_MIDI_NOTE_G4 , 127},
  {7,256, MIDI_NOTE_OFF,  VS1_MIDI_NOTE_G4 , 100},
  {7,288, MIDI_NOTE_ON ,  VS1_MIDI_NOTE_C5 , 127},
  {7,352, MIDI_NOTE_OFF,  VS1_MIDI_NOTE_C5 , 100},
  {8,  0, MIDI_NOTE_ON ,  VS1_MIDI_NOTE_G4 , 127},
  {8, 64, MIDI_NOTE_OFF,  VS1_MIDI_NOTE_G4 , 100},
  {8, 96, MIDI_NOTE_ON ,  VS1_MIDI_NOTE_Ah4, 127},
  {8,160, MIDI_NOTE_OFF,  VS1_MIDI_NOTE_Ah4, 100},
  {8,192, MIDI_NOTE_ON ,  VS1_MIDI_NOTE_G4 , 127},
  {8,256, MIDI_NOTE_OFF,  VS1_MIDI_NOTE_G4 , 100},
  {8,288, MIDI_NOTE_ON ,  VS1_MIDI_NOTE_Ah4, 127},
  {8,352, MIDI_NOTE_OFF,  VS1_MIDI_NOTE_Ah4, 100},
  {9,  0, MIDI_NOTE_ON ,  VS1_MIDI_NOTE_G4 , 127},
  {9, 64, MIDI_NOTE_OFF,  VS1_MIDI_NOTE_G4 , 100},
  {9, 96, MIDI_NOTE_ON ,  VS1_MIDI_NOTE_Ah4, 127},
  {9,160, MIDI_NOTE_OFF,  VS1_MIDI_NOTE_Ah4, 100},
  {9,192, MIDI_NOTE_ON ,  VS1_MIDI_NOTE_G4 , 127},
  {9,256, MIDI_NOTE_OFF,  VS1_MIDI_NOTE_G4 , 100},
  {9,288, MIDI_NOTE_ON ,  VS1_MIDI_NOTE_Ah4, 127},
  {9,352, MIDI_NOTE_OFF,  VS1_MIDI_NOTE_Ah4, 100},
  {10,  0, MIDI_NOTE_ON,  VS1_MIDI_NOTE_G4,  127},
  {10, 64, MIDI_NOTE_OFF, VS1_MIDI_NOTE_G4,  100},
  {10, 96, MIDI_NOTE_ON , VS1_MIDI_NOTE_B4,  127},
  {10,160, MIDI_NOTE_OFF, VS1_MIDI_NOTE_B4,  100},
  {10,192, MIDI_NOTE_ON , VS1_MIDI_NOTE_G4,  127},
  {10,256, MIDI_NOTE_OFF, VS1_MIDI_NOTE_G4,  100},
  {10,288, MIDI_NOTE_ON , VS1_MIDI_NOTE_B4,  127},
  {10,352, MIDI_NOTE_OFF, VS1_MIDI_NOTE_B4,  100},
  {11,  0, MIDI_NOTE_ON , VS1_MIDI_NOTE_G4,  127},
  {11,256, MIDI_NOTE_OFF, VS1_MIDI_NOTE_G4,  100},
  {11,256, MIDI_END_OF_TRACK, 0,  0}
};

static bool PlayTrackItem(MIDI_Track *track, unsigned int currTimeMs, uint8_t channel) {
  uint32_t beatsPerSecond = 2; /* 120 bpm */
  uint32_t currentMillis;
  uint32_t ppqn = 400; /* ticks per beat */
  uint32_t tempo = 110;
  uint8_t event;
  unsigned int itemNo;

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
        VS1_MIDI_NoteOn(channel, track->lines[itemNo].val1, track->lines[itemNo].val2);
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

static void Play(MIDI_Track *tracks, unsigned int nofTracks) {
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

void PlayTrack(void) {
  MIDI_Track tracks[2];

  tracks[0].lines = &song_ch0[0];
  tracks[0].nofLines = sizeof(song_ch0)/sizeof(song_ch0[0]);
  tracks[0].currLine = 0;
  tracks[1].lines = &song_ch1[0];
  tracks[1].nofLines = sizeof(song_ch1)/sizeof(song_ch1[0]);
  tracks[1].currLine = 0;
  Play(tracks, sizeof(tracks)/sizeof(tracks[0]));
}
