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
    FLOPPY_InitDrives();
    for(channel=0;channel<nofTracks;channel++) {
      tracks[channel].currLine = 0; /* reset track */
      FLOPPY_MIDI_SetBank(channel, 0);
      FLOPPY_MIDI_SetInstrument(channel, 0);
      FLOPPY_MIDI_SetVolume(channel, 127);
    }
    startTicks = xTaskGetTickCount();
    itemNo = 0;
    for(;;) { /* breaks, playing song */
      (void)xTaskNotifyWait(0UL, MIDI_SONG_BIT_STOP|MIDI_SONG_BIT_START|MIDI_SONG_BIT_NEXT, &flags, 0); /* check flags */
      if (flags&(MIDI_SONG_BIT_START|MIDI_SONG_BIT_STOP|MIDI_SONG_BIT_NEXT)) {
        break; /* break current song */
      }
      currTimeMs = ((xTaskGetTickCount()-startTicks)*1000)/configTICK_RATE_HZ;
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
        FLOPPY_MIDI_AllSoundOff(channel);
      }
      break; /* get out*/
    }
    if (flags&MIDI_SONG_BIT_START) {
      CLS1_SendStr((uint8_t*)"Restart song: #", CLS1_GetStdio()->stdOut);
      CLS1_SendNum32u((uint32_t)song, CLS1_GetStdio()->stdOut);
      CLS1_SendStr((uint8_t*)"\r\n", CLS1_GetStdio()->stdOut);
      for(channel=0;channel<nofTracks;channel++) {
        FLOPPY_MIDI_AllSoundOff(channel);
      }
      /* remain in loop, start song */
    }
    if (flags&MIDI_SONG_BIT_NEXT) {
      CLS1_SendStr((uint8_t*)"Skipping to next song: #", CLS1_GetStdio()->stdOut);
      CLS1_SendNum32u((uint32_t)MM_SetSong, CLS1_GetStdio()->stdOut);
      CLS1_SendStr((uint8_t*)"\r\n", CLS1_GetStdio()->stdOut);
      for(channel=0;channel<nofTracks;channel++) {
        FLOPPY_MIDI_AllSoundOff(channel);
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
  FLOPPY_SetOffset(offset);
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
  Play(song, tracks, nofTracks, tempoUS);
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

static void MidiPlayTask(void *pvParameters) {
  uint32_t flags;
  BaseType_t res;

  FLOPPY_InitDrives(); /* init */
  for(;;) {
    res = xTaskNotifyWait((uint32_t)(-1), (uint32_t)(-1), &flags, portMAX_DELAY); /* check flags */
    if (res==pdPASS && (flags&MIDI_SONG_BIT_START)) {
      FLOPPY_InitDrives();
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
  UTIL1_Num32sToStr(buf, sizeof(buf), MM_SetSong);
  UTIL1_strcat(buf, sizeof(buf), (const unsigned char*)"\r\n");
  CLS1_SendStatusStr((unsigned char*)"  set song", buf, io->stdOut);
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
   }
  return ERR_OK;
}

void MM_Init(void) {
  if (FRTOS1_xTaskCreate(
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
