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
#include "MidiGameOfThrones.h"
#include "MidiTetris.h"
#include "MidiAxelF.h"
#include "MidiGhostbusters.h"
#include "MidiBond.h"
#include "Buzzer.h"
#include "Identify.h"
#include "UTIL1.h"

typedef enum { /* bits are used for FreeRTOS direct task notifications */
  MIDI_SONG_BIT_GET_READY             = (1<<0),
  MIDI_SONG_BIT_PIRATES_OF_CARIBIAN   = (1<<1),
  MIDI_SONG_BIT_HADDAWAY_WHAT_IS_LOVE = (1<<2),
  MIDI_SONG_BIT_GAME_OF_THRONES       = (1<<3),
  MIDI_SONG_BIT_TETRIS                = (1<<4) ,
  MIDI_SONG_BIT_AXEL_F                = (1<<5),
  MIDI_SONG_BIT_GHOSTBUSTERS          = (1<<6),
  MIDI_SONG_BIT_JAMES_BOND            = (1<<7),
  MIDI_SONG_BIT_PREV = (1<<28),
  MIDI_SONG_BIT_NEXT = (1<<29),
  MIDI_SONG_BIT_START = (1<<30),
  MIDI_SONG_BIT_STOP = (1<<31)
} MIDI_SongBit;

static TaskHandle_t MidiPlayTaskHandle;
static bool MM_isPlayingSong = FALSE;
static MIDI_SongNr MM_SetSong = 1; /* skipping song 0 */

void MM_NextSongNumber(void) {
  MM_SetSong++;
  if (MM_SetSong==MIDI_SONG_NR_NOF_SONGS) {
    MM_SetSong = 1; /* skipping song 0, not interesting */
  }
  CLS1_SendStr((uint8_t*)"Next song: #", CLS1_GetStdio()->stdOut);
  CLS1_SendNum32u((uint32_t)MM_SetSong, CLS1_GetStdio()->stdOut);
  CLS1_SendStr((uint8_t*)"\r\n", CLS1_GetStdio()->stdOut);
  (void)xTaskNotify(MidiPlayTaskHandle, (1<<MM_SetSong)|MIDI_SONG_BIT_NEXT, eSetBits);
}

void MM_PrevSongNumber(void) {
  MM_SetSong--;
  if (MM_SetSong==0) {
    MM_SetSong = MIDI_SONG_NR_NOF_SONGS-1; /* skipping song 0, not interesting */
  }
  CLS1_SendStr((uint8_t*)"Prev song: #", CLS1_GetStdio()->stdOut);
  CLS1_SendNum32u((uint32_t)MM_SetSong, CLS1_GetStdio()->stdOut);
  CLS1_SendStr((uint8_t*)"\r\n", CLS1_GetStdio()->stdOut);
  (void)xTaskNotify(MidiPlayTaskHandle, (1<<MM_SetSong)|MIDI_SONG_BIT_PREV, eSetBits);
}

#if !PL_HAS_FLOPPY

static uint8_t MM_Channel = 0; /* active channel */
static int MM_Offset = 0; /* offset of midi note */

#define BUZZER_NOF_NOTES  128
static const uint16_t BUZZER_NoteFreq[BUZZER_NOF_NOTES] = {
    8, // 0
    8, // 1
    9, // 2
    9, // 3
    10, // 4
    10, // 5
    11, // 6
    12, // 7
    12, // 8
    13, // 9
    14, // 10
    15, // 11
    16, // 12
    17, // 13
    18, // 14
    19, // 15
    20, // 16
    21, // 17
    23, // 18
    24, // 19
    25, // 20
    27, // 21
    29, // 22
    30, // 23
    32, // 24
    34, // 25
    36, // 26
    38, // 27
    41, // 28
    43, // 29
    46, // 30
    48, // 31
    51, // 32
    55, // 33
    58, // 34
    61, // 35

    65, //96, // 36
    69, //91, // 37
    73, //86, // 38
    77, //81, // 39
    82, //76, // 40
    87, //72, // 41
    92, //68, // 42
    97, //64, // 43
    103, //61, // 44
    110, //57, // 45
    116, //54, // 46
    123, //51, // 47

    130, //48, // 48 (that's the highest note we can play (FLOPPY_HIGHEST_NOTE)!)
    138, //48, // 49
    146, //48 , // Note 50
    155, //48 , // Note 51
    164, //48 , // Note 52
    174, //48 , // Note 53
    184, //48 , // Note 54
    195, //48 , // Note 55
    207, //48 , // Note 56
    220, //48 , // Note 57
    233, //48 , // Note 58
    246, //48 , // Note 59
    261, //48 , // Note 60
    277, //550 , // Note 61
    293, //542 , // Note 62
    311, //534 , // Note 63
    329, //526 , // Note 64
    349, //518 , // Note 65
    369, //510 , // Note 66
    391, //503 , // Note 67
    415, //495 , // Note 68
    440, //487 , // Note 69
    466, // , // Note 70
    493, //471 , // Note 71

    523, //463 , // Note 72
    554, //455 , // Note 73
    587, //447 , // Note 74
    622, //440 , // Note 75
    659, //432 , // Note 76
    698, //424 , // Note 77
    739, //416 , // Note 78
    783, //408 , // Note 79
    830, //400 , // Note 80
    880, //392 , // Note 81
    932, //384 , // Note 82
    987, //377 , // Note 83
  /* too high below */
    369 , // Note 84
    361 , // Note 85
    353 , // Note 86
    345 , // Note 87
    337 , // Note 88
    329 , // Note 89
    321 , // Note 90
    314 , // Note 91
    306 , // Note 92
    298 , // Note 93
    290 , // Note 94
    282 , // Note 95
    274 , // Note 96
    266 , // Note 97
    258 , // Note 98
    251 , // Note 99
    243 , // Note 100
    235 , // Note 101
    227 , // Note 102
    219 , // Note 103
    211 , // Note 104
    203 , // Note 105
    195 , // Note 106
    188 , // Note 107
    180 , // Note 108
    172 , // Note 109
    164 , // Note 110
    156 , // Note 111
    148 , // Note 112
    140 , // Note 113
    132 , // Note 114
    125 , // Note 115
    117 , // Note 116
    109 , // Note 117
    101 , // Note 118
    93  , // Note 119
    85  , // Note 120
    77  , // Note 121
    69  , // Note 122
    62  , // Note 123
    54  , // Note 124
    46  , // Note 125
    38  , // Note 126
    30   // Note 127
};

static void BUZZER_SetOffset(int offset) {
  MM_Offset = offset;
}

static void BUZZER_MIDI_SetBank(uint8_t channel, uint8_t value) {
  /* not supported */
  (void)value;
  (void)channel;
}

static void BUZZER_MIDI_NoteOn(uint8_t channel, uint8_t note, uint8_t velocity) {
  if (channel==MM_Channel) {
    if (note<BUZZER_NOF_NOTES) {
      BUZ_Beep(BUZZER_NoteFreq[note], 10000/*dummy*/);
    }
  }
  (void)note;
  (void)velocity;
}

static void BUZZER_MIDI_NoteOff(uint8_t channel, uint8_t note, uint8_t velocity) {
  if (channel==MM_Channel) {
    BUZ_StopBeep();
  }
  (void)note;
  (void)velocity;
}

static void BUZZER_MIDI_SetInstrument(uint8_t channel, uint8_t instrument) {
  /* not supported */
  (void)instrument;
  (void)channel;
}

static void BUZZER_MIDI_SetVolume(uint8_t channel, uint8_t volume) {
  /* not supported */
  (void)volume;
  (void)channel;
}

static void BUZZER_MIDI_SetPan(uint8_t channel, uint8_t pan) {
  /* not supported */
  (void)pan;
  (void)channel;
}

static void BUZZER_MIDI_AllSoundOff(uint8_t channel) {
  if (channel==0) {
    BUZ_StopBeep();
  }
  (void)channel;
}
#endif /* !PL_HAS_FLOPPY */

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
#if PL_HAS_FLOPPY
        FLOPPY_MIDI_SetBank(channel, track->lines[itemNo].val1);
#else
        BUZZER_MIDI_SetBank(channel, track->lines[itemNo].val1);
#endif
        break;
      case MIDI_NOTE_ON:
        if (track->lines[itemNo].val2==0) { /* note on with velocity zero is a note off */
#if PL_HAS_FLOPPY
          FLOPPY_MIDI_NoteOff(channel, track->lines[itemNo].val1, 0);
#else
          BUZZER_MIDI_NoteOff(channel, track->lines[itemNo].val1, 0);
#endif
        } else {
#if PL_HAS_FLOPPY
          FLOPPY_MIDI_NoteOn(channel, track->lines[itemNo].val1, track->lines[itemNo].val2);
#else
          BUZZER_MIDI_NoteOn(channel, track->lines[itemNo].val1, track->lines[itemNo].val2);
#endif
        }
        break;
      case MIDI_NOTE_OFF:
#if PL_HAS_FLOPPY
        FLOPPY_MIDI_NoteOff(channel, track->lines[itemNo].val1, track->lines[itemNo].val2);
#else
        BUZZER_MIDI_NoteOff(channel, track->lines[itemNo].val1, track->lines[itemNo].val2);
#endif
        break;
      case MIDI_PATCH:
#if PL_HAS_FLOPPY
        FLOPPY_MIDI_SetInstrument(channel, track->lines[itemNo].val1);
#else
        BUZZER_MIDI_SetInstrument(channel, track->lines[itemNo].val1);
#endif
        break;
      case MIDI_VOLUME:
#if PL_HAS_FLOPPY
        FLOPPY_MIDI_SetVolume(channel, track->lines[itemNo].val1);
#else
        BUZZER_MIDI_SetVolume(channel, track->lines[itemNo].val1);
#endif
        break;
      case MIDI_PAN:
#if PL_HAS_FLOPPY
        FLOPPY_MIDI_SetPan(channel, track->lines[itemNo].val1);
#else
        BUZZER_MIDI_SetPan(channel, track->lines[itemNo].val1);
#endif
        break;
      case MIDI_END_OF_TRACK:
#if PL_HAS_FLOPPY
        FLOPPY_MIDI_AllSoundOff(channel);
#else
        BUZZER_MIDI_AllSoundOff(channel);
#endif
        break;
    }
    track->currLine++;
  } /* for */
  return TRUE;
}

static void Play(MIDI_SongNr song, MIDI_MusicTrack *tracks, unsigned int nofTracks, uint32_t tempoUS) {
  int itemNo;
  uint8_t channel;
  uint32_t currTimeMs;
  TickType_t startTicks;
  unsigned int nofFinished;
  uint32_t flags;

  for(;;) { /* breaks, start playing song */
    CLS1_SendStr((uint8_t*)"Playing song: #", CLS1_GetStdio()->stdOut);
    CLS1_SendNum32u((uint32_t)song, CLS1_GetStdio()->stdOut);
    CLS1_SendStr((uint8_t*)"\r\n", CLS1_GetStdio()->stdOut);
    /* init defaults */
#if PL_HAS_FLOPPY
    FLOPPY_InitDrives();
#endif
    for(channel=0;channel<nofTracks;channel++) {
      tracks[channel].currLine = 0; /* reset track */
#if PL_HAS_FLOPPY
      FLOPPY_MIDI_SetBank(channel, 0);
      FLOPPY_MIDI_SetInstrument(channel, 0);
      FLOPPY_MIDI_SetVolume(channel, 127);
#endif
    }
    startTicks = xTaskGetTickCount();
    itemNo = 0;
    for(;;) { /* breaks, playing song */
      (void)xTaskNotifyWait(0UL, MIDI_SONG_BIT_STOP|MIDI_SONG_BIT_START|MIDI_SONG_BIT_NEXT, &flags, 0); /* check flags */
      if (flags&(MIDI_SONG_BIT_START|MIDI_SONG_BIT_STOP|MIDI_SONG_BIT_NEXT)) {
        break; /* break current song */
      }
      currTimeMs = (xTaskGetTickCount()-startTicks)*(1000/configTICK_RATE_HZ);
      nofFinished = 0;
      for(channel=0;channel<nofTracks;channel++) {
        if (!PlayTrackItem(&tracks[channel], currTimeMs, channel, tempoUS)) {
          nofFinished++;
        }
      }
      if (nofFinished==nofTracks) { /* all finished */
        return;
      }
      vTaskDelay(pdMS_TO_TICKS(1));
      itemNo++;
    } /* for: playing song */
    if (flags&MIDI_SONG_BIT_STOP) {
      CLS1_SendStr((uint8_t*)"Stopping song: #", CLS1_GetStdio()->stdOut);
      CLS1_SendNum32u((uint32_t)song, CLS1_GetStdio()->stdOut);
      CLS1_SendStr((uint8_t*)"\r\n", CLS1_GetStdio()->stdOut);
      for(channel=0;channel<nofTracks;channel++) {
#if PL_HAS_FLOPPY
        FLOPPY_MIDI_AllSoundOff(channel);
#else
        BUZZER_MIDI_AllSoundOff(channel);
#endif
      }
      break; /* get out*/
    }
    if (flags&MIDI_SONG_BIT_START) {
      CLS1_SendStr((uint8_t*)"Restart song: #", CLS1_GetStdio()->stdOut);
      CLS1_SendNum32u((uint32_t)song, CLS1_GetStdio()->stdOut);
      CLS1_SendStr((uint8_t*)"\r\n", CLS1_GetStdio()->stdOut);
      for(channel=0;channel<nofTracks;channel++) {
#if PL_HAS_FLOPPY
        FLOPPY_MIDI_AllSoundOff(channel);
#else
        BUZZER_MIDI_AllSoundOff(channel);
#endif
      }
      /* remain in loop, start song */
    }
    if (flags&MIDI_SONG_BIT_NEXT) {
      CLS1_SendStr((uint8_t*)"Skipping to next song: #", CLS1_GetStdio()->stdOut);
      CLS1_SendNum32u((uint32_t)MM_SetSong, CLS1_GetStdio()->stdOut);
      CLS1_SendStr((uint8_t*)"\r\n", CLS1_GetStdio()->stdOut);
      for(channel=0;channel<nofTracks;channel++) {
#if PL_HAS_FLOPPY
        FLOPPY_MIDI_AllSoundOff(channel);
#else
        BUZZER_MIDI_AllSoundOff(channel);
#endif
      }
      (void)xTaskNotify(MidiPlayTaskHandle, (1<<MM_SetSong)|MIDI_SONG_BIT_START, eSetBits);
      return;
    }
  } /* for: start playing song */
}

void MM_Play(MIDI_SongNr song) {
  #define MAX_NOF_TRACKS  8
  MIDI_MusicTrack tracks[MAX_NOF_TRACKS];
  uint8_t res=ERR_FAILED;
  uint8_t nofTracks=0;
  uint32_t tempoUS=0;
  int offset=0;

  if (song==MIDI_SONG_NR_GET_READY) {
    nofTracks = MMReady_NofTracks();
    tempoUS = MMReady_GetTempoUS();
    offset = MMReady_GetOffset();
 } else if (song==MIDI_SONG_NR_PIRATES_OF_CARIBIAN) {
    nofTracks = MPirate_NofTracks();
    tempoUS = MPirate_GetTempoUS();
    offset = MPirate_GetOffset();
  } else if (song==MIDI_SONG_NR_HADDAWAY_WHAT_IS_LOVE) {
    nofTracks = MHaddaway_NofTracks();
    tempoUS = MHaddaway_GetTempoUS();
    offset = MHaddaway_GetOffset();
  } else if (song==MIDI_SONG_NR_GAME_OF_THRONES) {
    nofTracks = MGameOfThrones_NofTracks();
    tempoUS = MGameOfThrones_GetTempoUS();
    offset = MGameOfThrones_GetOffset();
  } else if (song==MIDI_SONG_NR_TETRIS) {
    nofTracks = MTetris_NofTracks();
    tempoUS = MTetris_GetTempoUS();
    offset = MTetris_GetOffset();
  } else if (song==MIDI_SONG_NR_AXEL_F) {
    nofTracks = MAxelF_NofTracks();
    tempoUS = MAxelF_GetTempoUS();
    offset = MAxelF_GetOffset();
  } else if (song==MIDI_SONG_NR_GHOSTBUSTERS) {
    nofTracks = MGhostbusters_NofTracks();
    tempoUS = MGhostbusters_GetTempoUS();
    offset = MGhostbusters_GetOffset();
  } else if (song==MIDI_SONG_NR_JAMES_BOND) {
    nofTracks = MBond_NofTracks();
    tempoUS = MBond_GetTempoUS();
    offset = MBond_GetOffset();
  } else {
    return; /* error */
  }
  if (nofTracks>MAX_NOF_TRACKS) {
    return; /* error */
  }
#if PL_HAS_FLOPPY
  FLOPPY_SetOffset(offset);
#else
  BUZZER_SetOffset(offset);
#endif
  if (song==MIDI_SONG_NR_GET_READY) {
    res = MMReady_GetMidiMusicInfo(&tracks[0], nofTracks);
  } else if (song==MIDI_SONG_NR_PIRATES_OF_CARIBIAN) {
    res = MPirate_GetMidiMusicInfo(&tracks[0], nofTracks);
  } else if (song==MIDI_SONG_NR_HADDAWAY_WHAT_IS_LOVE) {
    res = MHaddaway_GetMidiMusicInfo(&tracks[0], nofTracks);
  } else if (song==MIDI_SONG_NR_GAME_OF_THRONES) {
    res = MGameOfThrones_GetMidiMusicInfo(&tracks[0], nofTracks);
  } else if (song==MIDI_SONG_NR_TETRIS) {
    res = MTetris_GetMidiMusicInfo(&tracks[0], nofTracks);
  } else if (song==MIDI_SONG_NR_AXEL_F) {
    res = MAxelF_GetMidiMusicInfo(&tracks[0], nofTracks);
  } else if (song==MIDI_SONG_NR_GHOSTBUSTERS) {
    res = MGhostbusters_GetMidiMusicInfo(&tracks[0], nofTracks);
  } else if (song==MIDI_SONG_NR_JAMES_BOND) {
    res = MBond_GetMidiMusicInfo(&tracks[0], nofTracks);
  }
  if (res!=ERR_OK) {
    return; /* error case */
  }
  MM_isPlayingSong = TRUE;
  Play(song, tracks, nofTracks, tempoUS);
  MM_isPlayingSong = FALSE;
}

void MM_PlayMusic(int song) {
  if (song==-1) { /* use set/stored song */
    song = MM_SetSong;
  }
  (void)xTaskNotify(MidiPlayTaskHandle, (1<<song)|MIDI_SONG_BIT_START, eSetBits);
}

void MM_StopPlaying(void) {
  (void)xTaskNotify(MidiPlayTaskHandle, MIDI_SONG_BIT_STOP, eSetBits);
}

bool MM_IsPlaying(void) {
  return MM_isPlayingSong;
}

static void MidiPlayTask(void *pvParameters) {
  uint32_t flags;
  BaseType_t res;

  (void)pvParameters;
#if PL_HAS_FLOPPY
  FLOPPY_InitDrives(); /* init */
#endif
  for(;;) {
    res = xTaskNotifyWait((uint32_t)(-1), (uint32_t)(-1), &flags, portMAX_DELAY); /* check flags */
    if (res==pdPASS && (flags&MIDI_SONG_BIT_START)) {
#if PL_HAS_FLOPPY
      FLOPPY_InitDrives();
#endif
      if (flags&MIDI_SONG_BIT_GET_READY) {
        MM_Play(MIDI_SONG_NR_GET_READY);
      } else if (flags&MIDI_SONG_BIT_PIRATES_OF_CARIBIAN) {
        MM_Play(MIDI_SONG_NR_PIRATES_OF_CARIBIAN);
      } else if (flags&MIDI_SONG_BIT_HADDAWAY_WHAT_IS_LOVE) {
        MM_Play(MIDI_SONG_NR_HADDAWAY_WHAT_IS_LOVE);
      } else if (flags&MIDI_SONG_BIT_GAME_OF_THRONES) {
        MM_Play(MIDI_SONG_NR_GAME_OF_THRONES);
      } else if (flags&MIDI_SONG_BIT_TETRIS) {
        MM_Play(MIDI_SONG_NR_TETRIS);
      } else if (flags&MIDI_SONG_BIT_AXEL_F) {
        MM_Play(MIDI_SONG_NR_AXEL_F);
      } else if (flags&MIDI_SONG_BIT_GHOSTBUSTERS) {
        MM_Play(MIDI_SONG_NR_GHOSTBUSTERS);
      } else if (flags&MIDI_SONG_BIT_JAMES_BOND) {
        MM_Play(MIDI_SONG_NR_JAMES_BOND);
      }
    }
  }
}

static uint8_t PrintStatus(CLS1_ConstStdIOType *io) {
  uint8_t buf[16];
  CLS1_SendStatusStr((unsigned char*)"midi", (const unsigned char*)"\r\n", io->stdOut);

  if (MM_IsPlaying()) {
    CLS1_SendStatusStr((unsigned char*)"  playing", (const unsigned char*)"yes\r\n", io->stdOut);
  } else {
    CLS1_SendStatusStr((unsigned char*)"  playing", (const unsigned char*)"no\r\n", io->stdOut);
  }
  UTIL1_Num32sToStr(buf, sizeof(buf), MM_SetSong);
  UTIL1_strcat(buf, sizeof(buf), (const unsigned char*)"\r\n");
  CLS1_SendStatusStr((unsigned char*)"  set song", buf, io->stdOut);
#if PL_HAS_FLOPPY
  CLS1_SendStatusStr((unsigned char*)"  hardware", (const unsigned char*)"Floppy\r\n", io->stdOut);
#else
  CLS1_SendStatusStr((unsigned char*)"  hardware", (const unsigned char*)"Buzzer\r\n", io->stdOut);
  UTIL1_Num8uToStr(buf, sizeof(buf), MM_Channel);
  UTIL1_strcat(buf, sizeof(buf), (const unsigned char*)"\r\n");
  CLS1_SendStatusStr((unsigned char*)"  channel", buf, io->stdOut);
#endif
  return ERR_OK;
}

uint8_t MM_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io) {
  const uint8_t *p;
  uint8_t res;
  int32_t tmp;

  if (UTIL1_strcmp((char*)cmd, CLS1_CMD_HELP)==0 || UTIL1_strcmp((char*)cmd, "midi help")==0) {
     CLS1_SendHelpStr((unsigned char*)"midi", (const unsigned char*)"Group of midi commands\r\n", io->stdOut);
     CLS1_SendHelpStr((unsigned char*)"  help|status", (unsigned char*)"Print help or status information\r\n", io->stdOut);
     CLS1_SendHelpStr((unsigned char*)"  (play|set) <number>", (const unsigned char*)"Play midi song\r\n", io->stdOut);
#if !PL_HAS_FLOPPY
     CLS1_SendHelpStr((unsigned char*)"  channel <number>", (const unsigned char*)"Midi channel for buzzer\r\n", io->stdOut);
#endif
     //CLS1_SendHelpStr((unsigned char*)"      0", (const unsigned char*)"Get ready\r\n", io->stdOut);
     CLS1_SendHelpStr((unsigned char*)"      1", (const unsigned char*)"Pirates of the Caribbean\r\n", io->stdOut);
     CLS1_SendHelpStr((unsigned char*)"      2", (const unsigned char*)"What is Love\r\n", io->stdOut);
     CLS1_SendHelpStr((unsigned char*)"      3", (const unsigned char*)"Game of Thrones\r\n", io->stdOut);
     CLS1_SendHelpStr((unsigned char*)"      4", (const unsigned char*)"Tetris\r\n", io->stdOut);
     CLS1_SendHelpStr((unsigned char*)"      5", (const unsigned char*)"Axel F.\r\n", io->stdOut);
     CLS1_SendHelpStr((unsigned char*)"      6", (const unsigned char*)"Ghostbusters\r\n", io->stdOut);
     CLS1_SendHelpStr((unsigned char*)"      7", (const unsigned char*)"James Bond\r\n", io->stdOut);
     CLS1_SendHelpStr((unsigned char*)"  stop", (const unsigned char*)"Stop playing\r\n", io->stdOut);
     *handled = TRUE;
     return ERR_OK;
   } else if ((UTIL1_strcmp((char*)cmd, CLS1_CMD_STATUS)==0) || (UTIL1_strcmp((char*)cmd, "midi status")==0)) {
     *handled = TRUE;
     return PrintStatus(io);
   } else if (UTIL1_strcmp((char*)cmd, "midi stop")==0) {
     *handled = TRUE;
     MM_StopPlaying();
     return ERR_OK;
   } else if (UTIL1_strncmp((char*)cmd, "midi play", sizeof("midi play")-1)==0) {
     p = cmd+sizeof("midi play")-1;
     res = UTIL1_xatoi(&p, &tmp);
     if (res==ERR_OK && tmp>=1 && tmp<MIDI_SONG_NR_NOF_SONGS) {
       *handled = TRUE;
       MM_SetSong = tmp;
       MM_PlayMusic(tmp);
     }
     return res;
   } else if (UTIL1_strncmp((char*)cmd, "midi set", sizeof("midi set")-1)==0) {
     p = cmd+sizeof("midi set")-1;
     res = UTIL1_xatoi(&p, &tmp);
     if (res==ERR_OK && tmp>=0 && tmp<MIDI_SONG_NR_NOF_SONGS) {
       *handled = TRUE;
       MM_SetSong = tmp;
     }
     return res;
#if !PL_HAS_FLOPPY
   } else if (UTIL1_strncmp((char*)cmd, "midi channel", sizeof("midi channel")-1)==0) {
     p = cmd+sizeof("midi channel")-1;
     res = UTIL1_xatoi(&p, &tmp);
     if (res==ERR_OK && tmp>=0) {
       *handled = TRUE;
       MM_Channel = tmp;
     }
     return res;
#endif
   }
  return ERR_OK;
}

void MM_Init(void) {
#if !PL_HAS_FLOPPY
  ID_Devices id;

  MM_Channel = 0; /* default active channel */
  id = ID_WhichDevice();
#if 0
  if (id==ID_DEVICE_ROBO_V1_L4) {
    MM_Channel = 4;
  } else if (id==ID_DEVICE_ROBO_V1_L7) {
    MM_Channel = 7;
  }
#endif
#endif
  if (xTaskCreate(
      MidiPlayTask,  /* pointer to the task */
      "MidiPlay", /* task name for kernel awareness debugging */
      configMINIMAL_STACK_SIZE, /* task stack size */
      (void*)NULL, /* optional task startup argument */
      tskIDLE_PRIORITY+1,  /* initial priority */
      &MidiPlayTaskHandle /* optional task handle to create */
    ) != pdPASS) {
  /*lint -e527 */
  for(;;){} /* error! probably out of memory */
    /*lint +e527 */
  }
}#endif /* PL_HAS_MUSIC */
