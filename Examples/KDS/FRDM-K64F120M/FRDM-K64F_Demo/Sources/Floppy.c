/*
 * Floppy.c
 *
 *  Created on: 14.04.2016
 *      Author: Erich Styger
 */
#include "Platform.h"
#if PL_HAS_FLOPPY
#include "Floppy.h"
#include "FRTOS1.h"
#include "UTIL1.h"
#include "TI1.h"
#include "MidiMusic.h"
#include "CLS1.h"
#include "WAIT1.h"

#include "Dir0.h"
#include "Step0.h"
#include "Dir1.h"
#include "Step1.h"
#include "Dir2.h"
#include "Step2.h"
#include "Dir3.h"
#include "Step3.h"
#include "Dir4.h"
#include "Step4.h"
#include "Dir5.h"
#include "Step5.h"
#include "Dir6.h"
#include "Step6.h"
#include "Dir7.h"
#include "Step7.h"

/* songs:
 * http://www.makeuseof.com/tag/8-floppy-disk-drive-music-videos/
 * http://makezine.com/2014/08/18/how-to-play-music-using-floppy-drives/
 * http://hackaday.com/2014/01/05/the-most-beautiful-floppy-disk-jukebox-ever/
 * http://www.schoar.de/tinkering/rumblerail/
 */
/* green: enable (low active)
 * white: direction
 * green: step
 */

#define FLOPPY_NOF_NOTES    128
#define FLOPPY_HIGHES_NOTE  48 /* highest note/tone we can play */
static const uint16_t FLOPPY_NoteTicks[FLOPPY_NOF_NOTES] = {
    727, // 0
    727, // 1
    686, // 2
    648, // 3
    612, // 4
    577, // 5
    545, // 6
    514, // 7
    485, // 8
    458, // 9
    432, // 10
    408, // 11
    385, // 12
    364, // 13
    343, // 14
    324, // 15
    306, // 16
    289, // 17
    272, // 18
    257, // 19
    243, // 20
    229, // 21
    216, // 22
    204, // 23
    193, // 24
    182, // 25
    172, // 26
    162, // 27
    153, // 28
    144, // 29
    136, // 30
    129, // 31
    121, // 32
    115, // 33
    108, // 34
    102, // 35
    96, // 36
    91, // 37
    86, // 38
    81, // 39
    76, // 40
    72, // 41
    68, // 42
    64, // 43
    61, // 44
    57, // 45
    54, // 46
    51, // 47
    48, // 48 (that's the highest note we can play (FLOPPY_HIGHES_NOTE)!)
    48, // 49
    48 , // Note 50
    48 , // Note 51
    48 , // Note 52
    48 , // Note 53
    48 , // Note 54
    48 , // Note 55
    48 , // Note 56
    48 , // Note 57
    48 , // Note 58
    48 , // Note 59
    48 , // Note 60
    550 , // Note 61
    542 , // Note 62
    534 , // Note 63
    526 , // Note 64
    518 , // Note 65
    510 , // Note 66
    503 , // Note 67
    495 , // Note 68
    487 , // Note 69
    479 , // Note 70
    471 , // Note 71
    463 , // Note 72
    455 , // Note 73
    447 , // Note 74
    440 , // Note 75
    432 , // Note 76
    424 , // Note 77
    416 , // Note 78
    408 , // Note 79
    400 , // Note 80
    392 , // Note 81
    384 , // Note 82
    377 , // Note 83
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

static int FLOPPY_NoteOffset = 0; /* value added to the note played */

#define FLOPPY_NOF_DRIVES  8
#define FLOPPY_MAX_STEPS  80

static void Drv0_Dir(bool forward) { if (forward) {Dir0_SetVal();} else {Dir0_ClrVal();} }
static void Drv0_Step(void) { Step0_SetVal(); WAIT1_Waitus(5); Step0_ClrVal(); }
static void Drv0_StepSetVal(void) { Step0_SetVal(); }
static void Drv0_StepClrVal(void) { Step0_ClrVal(); }
static void Drv0_StepToggle(void) { Step0_NegVal(); }

static void Drv1_Dir(bool forward) { if (forward) {Dir1_SetVal();} else {Dir1_ClrVal();} }
static void Drv1_Step(void) { Step1_SetVal(); WAIT1_Waitus(5); Step1_ClrVal(); }
static void Drv1_StepSetVal(void) { Step1_SetVal(); }
static void Drv1_StepClrVal(void) { Step1_ClrVal(); }
static void Drv1_StepToggle(void) { Step1_NegVal(); }

static void Drv2_Dir(bool forward) { if (forward) {Dir2_SetVal();} else {Dir2_ClrVal();} }
static void Drv2_Step(void) { Step2_SetVal(); WAIT1_Waitus(5); Step2_ClrVal(); }
static void Drv2_StepSetVal(void) { Step2_SetVal(); }
static void Drv2_StepClrVal(void) { Step2_ClrVal(); }
static void Drv2_StepToggle(void) { Step2_NegVal(); }

static void Drv3_Dir(bool forward) { if (forward) {Dir3_SetVal();} else {Dir3_ClrVal();} }
static void Drv3_Step(void) { Step3_SetVal(); WAIT1_Waitus(5); Step3_ClrVal(); }
static void Drv3_StepSetVal(void) { Step3_SetVal(); }
static void Drv3_StepClrVal(void) { Step3_ClrVal(); }
static void Drv3_StepToggle(void) { Step3_NegVal(); }

static void Drv4_Dir(bool forward) { if (forward) {Dir4_SetVal();} else {Dir4_ClrVal();} }
static void Drv4_Step(void) { Step4_SetVal(); WAIT1_Waitus(5); Step4_ClrVal(); }
static void Drv4_StepSetVal(void) { Step4_SetVal(); }
static void Drv4_StepClrVal(void) { Step4_ClrVal(); }
static void Drv4_StepToggle(void) { Step4_NegVal(); }

static void Drv5_Dir(bool forward) { if (forward) {Dir5_SetVal();} else {Dir5_ClrVal();} }
static void Drv5_Step(void) { Step5_SetVal(); WAIT1_Waitus(5); Step5_ClrVal(); }
static void Drv5_StepSetVal(void) { Step5_SetVal(); }
static void Drv5_StepClrVal(void) { Step5_ClrVal(); }
static void Drv5_StepToggle(void) { Step5_NegVal(); }

static void Drv6_Dir(bool forward) { if (forward) {Dir6_SetVal();} else {Dir6_ClrVal();} }
static void Drv6_Step(void) { Step6_SetVal(); WAIT1_Waitus(5); Step6_ClrVal(); }
static void Drv6_StepSetVal(void) { Step6_SetVal(); }
static void Drv6_StepClrVal(void) { Step6_ClrVal(); }
static void Drv6_StepToggle(void) { Step6_NegVal(); }

static void Drv7_Dir(bool forward) { if (forward) {Dir7_SetVal();} else {Dir7_ClrVal();} }
static void Drv7_Step(void) { Step7_SetVal(); WAIT1_Waitus(5); Step7_ClrVal(); }
static void Drv7_StepSetVal(void) { Step7_SetVal(); }
static void Drv7_StepClrVal(void) { Step7_ClrVal(); }
static void Drv7_StepToggle(void) { Step7_NegVal(); }

typedef struct {
  bool forward; /* current direction */
  int8_t pos; /* current position, valid 0..FLOPPY_MAX_STEPS */
  uint32_t currentPeriod; /* current period in timer interrupt events. Zero if disabled */
  uint32_t currentTick;
  void(*Dir)(bool forward);
  void(*Step)(void);
  void(*StepSetVal)(void);
  void(*StepClearVal)(void);
  void(*StepToggle)(void);
} FLOPPY_Drive;

typedef FLOPPY_Drive *FLOPPY_DriveHandle;

static FLOPPY_Drive FLOPPY_Drives[FLOPPY_NOF_DRIVES];

void FLOPPY_SetOffset(int offset) {
  FLOPPY_NoteOffset = offset;
}

uint8_t FLOPPY_SetPos(FLOPPY_DriveHandle drive, int pos) {
  drive->pos = pos;
  return ERR_OK;
}

uint8_t FLOPPY_SetDirection(FLOPPY_DriveHandle drive, bool forward) {
  drive->Dir(forward);
  drive->forward = forward;
  return ERR_OK;
}

uint8_t FLOPPY_Steps(FLOPPY_DriveHandle drive, int steps) {
  if (steps>=0) {
    FLOPPY_SetDirection(drive, TRUE); /* go forward */
  } else if (steps<0) {
    FLOPPY_SetDirection(drive, FALSE); /* go backward */
  }
  while(steps!=0) {
    if (drive->pos==FLOPPY_MAX_STEPS) {
      FLOPPY_SetDirection(drive, FALSE); /* go backward */
    } else if (drive->pos==0) {
      FLOPPY_SetDirection(drive, TRUE); /* go forward */
    }
    drive->Step();
    if (steps>0) {
      steps--;
    } else {
      steps++;
    }
    if (drive->forward) {
      drive->pos++;
    } else {
      drive->pos--;
    }
    vTaskDelay(pdMS_TO_TICKS(5));
  } /* while */
  return ERR_OK;
}

void FLOPPY_OnInterrupt(void) {
  int i;

  for(i=0;i<FLOPPY_NOF_DRIVES;i++) {
    if (FLOPPY_Drives[i].currentPeriod>0) { /* not disabled */
      FLOPPY_Drives[i].currentTick++; /* increment tick */
      if (FLOPPY_Drives[i].currentTick>=FLOPPY_Drives[i].currentPeriod) { /* check if expired */
        FLOPPY_Drives[i].StepSetVal(); /* toggle pin ==> High */
        FLOPPY_Drives[i].currentTick = 0; /* reset tick counter */
        /* change direction if end has been reached */
        if (FLOPPY_Drives[i].pos==FLOPPY_MAX_STEPS) {
          FLOPPY_SetDirection(&FLOPPY_Drives[i], FALSE); /* go backward */
        } else if (FLOPPY_Drives[i].pos==0) {
          FLOPPY_SetDirection(&FLOPPY_Drives[i], TRUE); /* go forward */
        }
        if (FLOPPY_Drives[i].forward) {
          FLOPPY_Drives[i].pos++;
        } else {
          FLOPPY_Drives[i].pos--;
        }
        WAIT1_Waitus(1);
        FLOPPY_Drives[i].StepClearVal(); /* toggle pin ==> Low */
      }
    }
  }
}

void FLOPPY_MIDI_SetBank(uint8_t channel, uint8_t value) {
  /* not supported */
}

void FLOPPY_MIDI_NoteOn(uint8_t channel, uint8_t note, uint8_t velocity) {
  int tmp;

  if (channel>=FLOPPY_NOF_DRIVES) {
    return;
  }
  if (note>=FLOPPY_NOF_NOTES) {
    return;
  }
  tmp = (int)note+FLOPPY_NoteOffset;
  if (tmp<0) {
    tmp = 0;
  } else if (tmp>FLOPPY_HIGHES_NOTE) {
    tmp = FLOPPY_HIGHES_NOTE;
  }
  note = tmp;
  FLOPPY_Drives[channel].currentPeriod = FLOPPY_NoteTicks[note];
}

void FLOPPY_MIDI_NoteOff(uint8_t channel, uint8_t note, uint8_t velocity) {
  if (channel>=FLOPPY_NOF_DRIVES) {
    return;
  }
  FLOPPY_Drives[channel].currentPeriod = 0;
}

void FLOPPY_MIDI_SetInstrument(uint8_t channel, uint8_t instrument) {
  /* not supported */
}

void FLOPPY_MIDI_SetVolume(uint8_t channel, uint8_t volume) {
  /* not supported */
}

void FLOPPY_MIDI_SetPan(uint8_t channel, uint8_t pan) {
  /* not supported */
}

void FLOPPY_MIDI_AllSoundOff(uint8_t channel) {
  if (channel>=FLOPPY_NOF_DRIVES) {
    return;
  }
  FLOPPY_Drives[channel].currentPeriod = 0;
}


uint8_t FLOPPY_InitDrives(void) {
  /* moving head to home position */
  int i, j;

  for(i=0;i<FLOPPY_NOF_DRIVES;i++) {
    /* reset to initial position */
    FLOPPY_Drives[i].Dir(TRUE);
    FLOPPY_Drives[i].forward = TRUE;
    FLOPPY_Drives[i].pos = FLOPPY_MAX_STEPS;
  }

  for(j=0;j<FLOPPY_MAX_STEPS+20;j++) { /* max 400 Hz */
    for(i=0;i<FLOPPY_NOF_DRIVES;i++) {
      FLOPPY_Drives[i].StepSetVal();
    }
    vTaskDelay(pdMS_TO_TICKS(1));
    for(i=0;i<FLOPPY_NOF_DRIVES;i++) {
      FLOPPY_Drives[i].StepClearVal();
    }
    vTaskDelay(pdMS_TO_TICKS(3));
  }
  return ERR_OK;
}

static uint8_t PrintStatus(const CLS1_StdIOType *io) {
  int i;
  uint8_t buf[16], buf2[32];

  CLS1_SendStatusStr((uint8_t*)"Floppy", (uint8_t*)"\r\n", io->stdOut);
  UTIL1_Num32sToStr(buf, sizeof(buf), FLOPPY_NoteOffset);
  UTIL1_strcat(buf, sizeof(buf), (uint8_t*)"\r\n");
  CLS1_SendStatusStr((uint8_t*)"  note offset", buf, io->stdOut);
  for(i=0;i<FLOPPY_NOF_DRIVES;i++) {
    UTIL1_strcpy(buf, sizeof(buf), (uint8_t*)"  drive ");
    UTIL1_strcatNum16u(buf, sizeof(buf), (uint16_t)i);
    UTIL1_chcat(buf, sizeof(buf), ':');
    buf2[0] = '\0';
    if (FLOPPY_Drives[i].forward) {
      UTIL1_strcat(buf2, sizeof(buf2), (uint8_t*)"fw ");
    } else {
      UTIL1_strcat(buf2, sizeof(buf2), (uint8_t*)"bw ");
    }
    UTIL1_strcatNum16s(buf2, sizeof(buf2), FLOPPY_Drives[i].pos);
    UTIL1_strcat(buf2, sizeof(buf2), (uint8_t*)"\r\n");
    CLS1_SendStatusStr(buf, buf2, io->stdOut);
  }
  return ERR_OK;
}

uint8_t FLOPPY_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io) {
  const uint8_t *p;
  int32_t val;

  if (UTIL1_strcmp((char*)cmd, CLS1_CMD_HELP)==0 || UTIL1_strcmp((char*)cmd, "Floppy help")==0) {
    CLS1_SendHelpStr((unsigned char*)"Floppy", (const unsigned char*)"Group of Floppy commands\r\n", io->stdOut);
    CLS1_SendHelpStr((unsigned char*)"  help|status", (const unsigned char*)"Print help or status information\r\n", io->stdOut);
    CLS1_SendHelpStr((unsigned char*)"  dir fw <drv>", (const unsigned char*)"Set drive direction to forward\r\n", io->stdOut);
    CLS1_SendHelpStr((unsigned char*)"  dir bw <drv>", (const unsigned char*)"Set drive direction to backward\r\n", io->stdOut);
    CLS1_SendHelpStr((unsigned char*)"  home", (const unsigned char*)"Move heads to home position\r\n", io->stdOut);
    CLS1_SendHelpStr((unsigned char*)"  step <drv> <steps>", (const unsigned char*)"Perform number of steps (positive/negative)\r\n", io->stdOut);
    CLS1_SendHelpStr((unsigned char*)"  period <drv> <ticks>", (const unsigned char*)"Set period for drive, zero disables it\r\n", io->stdOut);
    CLS1_SendHelpStr((unsigned char*)"  note <drv> <note>", (const unsigned char*)"Play note (0..127)\r\n", io->stdOut);
    *handled = TRUE;
    return ERR_OK;
  } else if ((UTIL1_strcmp((char*)cmd, CLS1_CMD_STATUS)==0) || (UTIL1_strcmp((char*)cmd, "Floppy status")==0)) {
    *handled = TRUE;
    return PrintStatus(io);
  } else if (UTIL1_strncmp((char*)cmd, "Floppy dir fw", sizeof("Floppy dir fw")-1)==0) {
    *handled = TRUE;
    p = cmd + sizeof("Floppy dir fw")-1;
    if (UTIL1_xatoi(&p, &val)==ERR_OK && val>=0 && val<FLOPPY_NOF_DRIVES) {
      return FLOPPY_SetDirection(&FLOPPY_Drives[val], TRUE);
    }
    return ERR_FAILED;
  } else if (UTIL1_strncmp((char*)cmd, "Floppy dir bw", sizeof("Floppy dir bw")-1)==0) {
    *handled = TRUE;
    p = cmd + sizeof("Floppy dir bw")-1;
    if (UTIL1_xatoi(&p, &val)==ERR_OK && val>=0 && val<FLOPPY_NOF_DRIVES) {
      return FLOPPY_SetDirection(&FLOPPY_Drives[val], FALSE);
    }
    return ERR_FAILED;
  } else if (UTIL1_strcmp((char*)cmd, "Floppy home")==0) {
    *handled = TRUE;
    return FLOPPY_InitDrives();
  } else if (UTIL1_strncmp((char*)cmd, "Floppy step", sizeof("Floppy step")-1)==0) {
    *handled = TRUE;
    p = cmd + sizeof("Floppy step")-1;
    if (UTIL1_xatoi(&p, &val)==ERR_OK && val>=0 && val<FLOPPY_NOF_DRIVES) {
      uint8_t drive = val;

      if (UTIL1_xatoi(&p, &val)==ERR_OK) {
        return FLOPPY_Steps(&FLOPPY_Drives[drive], val);
      }
    }
    return ERR_FAILED;
  } else if (UTIL1_strncmp((char*)cmd, "Floppy period", sizeof("Floppy period")-1)==0) {
    *handled = TRUE;
    p = cmd + sizeof("Floppy period")-1;
    if (UTIL1_xatoi(&p, &val)==ERR_OK && val>=0 && val<FLOPPY_NOF_DRIVES) {
      uint8_t drive = val;

      if (UTIL1_xatoi(&p, &val)==ERR_OK) {
        FLOPPY_Drives[drive].currentPeriod = val;
        return ERR_OK;
      }
    }
    return ERR_FAILED;
  } else if (UTIL1_strncmp((char*)cmd, "Floppy note", sizeof("Floppy note")-1)==0) {
    *handled = TRUE;
    p = cmd + sizeof("Floppy note")-1;
    if (UTIL1_xatoi(&p, &val)==ERR_OK && val>=0 && val<FLOPPY_NOF_DRIVES) {
      uint8_t drive = val;

      if (UTIL1_xatoi(&p, &val)==ERR_OK && val<FLOPPY_NOF_NOTES) {
        FLOPPY_Drives[drive].currentPeriod = FLOPPY_NoteTicks[val];
        return ERR_OK;
      }
    }
    return ERR_FAILED;
  }
  return ERR_OK;
}

void FLOPPY_Init(void) {
  int i;

  for(i=0;i<FLOPPY_NOF_DRIVES;i++) {
    FLOPPY_Drives[i].forward = FALSE;
    FLOPPY_Drives[i].pos = 0;
    FLOPPY_Drives[i].currentPeriod = 0;
    FLOPPY_Drives[i].currentTick = 0;
  }
  FLOPPY_Drives[0].Dir = Drv0_Dir;
  FLOPPY_Drives[0].Step = Drv0_Step;
  FLOPPY_Drives[0].StepSetVal = Drv0_StepSetVal;
  FLOPPY_Drives[0].StepClearVal = Drv0_StepClrVal;
  FLOPPY_Drives[0].StepToggle = Drv0_StepToggle;

  FLOPPY_Drives[1].Dir = Drv1_Dir;
  FLOPPY_Drives[1].Step = Drv1_Step;
  FLOPPY_Drives[1].StepSetVal = Drv1_StepSetVal;
  FLOPPY_Drives[1].StepClearVal = Drv1_StepClrVal;
  FLOPPY_Drives[1].StepToggle = Drv1_StepToggle;

  FLOPPY_Drives[2].Dir = Drv2_Dir;
  FLOPPY_Drives[2].Step = Drv2_Step;
  FLOPPY_Drives[2].StepSetVal = Drv2_StepSetVal;
  FLOPPY_Drives[2].StepClearVal = Drv2_StepClrVal;
  FLOPPY_Drives[2].StepToggle = Drv2_StepToggle;

  FLOPPY_Drives[3].Dir = Drv3_Dir;
  FLOPPY_Drives[3].Step = Drv3_Step;
  FLOPPY_Drives[3].StepSetVal = Drv3_StepSetVal;
  FLOPPY_Drives[3].StepClearVal = Drv3_StepClrVal;
  FLOPPY_Drives[3].StepToggle = Drv3_StepToggle;

  FLOPPY_Drives[4].Dir = Drv4_Dir;
  FLOPPY_Drives[4].Step = Drv4_Step;
  FLOPPY_Drives[4].StepSetVal = Drv4_StepSetVal;
  FLOPPY_Drives[4].StepClearVal = Drv4_StepClrVal;
  FLOPPY_Drives[4].StepToggle = Drv4_StepToggle;

  FLOPPY_Drives[5].Dir = Drv5_Dir;
  FLOPPY_Drives[5].Step = Drv5_Step;
  FLOPPY_Drives[5].StepSetVal = Drv5_StepSetVal;
  FLOPPY_Drives[5].StepClearVal = Drv5_StepClrVal;
  FLOPPY_Drives[5].StepToggle = Drv5_StepToggle;

  FLOPPY_Drives[6].Dir = Drv6_Dir;
  FLOPPY_Drives[6].Step = Drv6_Step;
  FLOPPY_Drives[6].StepSetVal = Drv6_StepSetVal;
  FLOPPY_Drives[6].StepClearVal = Drv6_StepClrVal;
  FLOPPY_Drives[6].StepToggle = Drv6_StepToggle;

  FLOPPY_Drives[7].Dir = Drv7_Dir;
  FLOPPY_Drives[7].Step = Drv7_Step;
  FLOPPY_Drives[7].StepSetVal = Drv7_StepSetVal;
  FLOPPY_Drives[7].StepClearVal = Drv7_StepClrVal;
  FLOPPY_Drives[7].StepToggle = Drv7_StepToggle;

  TI1_Enable();
  TI1_EnableEvent();
}
#endif /* PL_HAS_FLOPPY */
