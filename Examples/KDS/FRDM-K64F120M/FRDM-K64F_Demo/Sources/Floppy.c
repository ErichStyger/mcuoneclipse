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
#include "En0.h"
#include "Dir0.h"
#include "Step0.h"
#include "En1.h"
#include "Dir1.h"
#include "Step1.h"
#include "WAIT1.h"

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

#define FLOPPY_NOF_NOTES  128
static const uint16_t FLOPPY_NoteTicks[FLOPPY_NOF_NOTES] = {
  61156, // Note 0
  57723, // Note 1
  54483, // Note 2
  51425, // Note 3
  48539, // Note 4
  45815, // Note 5
  43243, // Note 6
  40816, // Note 7
  38525, // Note 8
  36363, // Note 9
  34322, // Note 10
  32396, // Note 11
  30578, // Note 12
  28861, // Note 13
  27241, // Note 14
  25712, // Note 15
  24269, // Note 16
  22907, // Note 17
  21621, // Note 18
  20408, // Note 19
  19262, // Note 20
  18181, // Note 21
  17161, // Note 22
  16198, // Note 23
  15289, // Note 24
  14430, // Note 25
  13620, // Note 26
  12856, // Note 27
  12134, // Note 28
  11453, // Note 29
  10810, // Note 30
  10204, // Note 31
  9631, // Note 32
  9090, // Note 33
  8580, // Note 34
  8099, // Note 35
  7644, // Note 36
  7215, // Note 37
  6810, // Note 38
  6428, // Note 39
  6067, // Note 40
  5726, // Note 41
  5405, // Note 42
  5102, // Note 43
  4815, // Note 44
  4545, // Note 45
  4290, // Note 46
  4049, // Note 47
  3822, // Note 48
  3607, // Note 49
  3405, // Note 50
  3214, // Note 51
  3033, // Note 52
  2863, // Note 53
  2702, // Note 54
  2551, // Note 55
  2407, // Note 56
  2272, // Note 57
  2145, // Note 58
  2024, // Note 59
  1911, // Note 60
  1803, // Note 61
  1702, // Note 62
  1607, // Note 63
  1516, // Note 64
  1431, // Note 65
  1351, // Note 66
  1275, // Note 67
  1203, // Note 68
  1136, // Note 69
  1072, // Note 70
  1012, // Note 71
  955, // Note 72
  901, // Note 73
  851, // Note 74
  803, // Note 75
  758, // Note 76
  715, // Note 77
  675, // Note 78
  637, // Note 79
  601, // Note 80
  568, // Note 81
  536, // Note 82
  506, // Note 83
  477, // Note 84
  450, // Note 85
  425, // Note 86
  401, // Note 87
  379, // Note 88
  357, // Note 89
  337, // Note 90
  318, // Note 91
  300, // Note 92
  284, // Note 93
  268, // Note 94
  253, // Note 95
  238, // Note 96
  225, // Note 97
  212, // Note 98
  200, // Note 99
  189, // Note 100
  178, // Note 101
  168, // Note 102
  159, // Note 103
  150, // Note 104
  142, // Note 105
  134, // Note 106
  126, // Note 107
  119, // Note 108
  112, // Note 109
  106, // Note 110
  100, // Note 111
  94, // Note 112
  89, // Note 113
  84, // Note 114
  79, // Note 115
  75, // Note 116
  71, // Note 117
  67, // Note 118
  63, // Note 119
  59, // Note 120
  56, // Note 121
  53, // Note 122
  50, // Note 123
  47, // Note 124
  44, // Note 125
  42, // Note 126
  39, // Note 127
};

#define FLOPPY_NOF_DRIVES  2
#define FLOPPY_MAX_STEPS  80

static void Drv0_Dir(bool forward) { if (forward) {Dir0_SetVal();} else {Dir0_ClrVal();} }
static void Drv0_ToggleStep(void) { Step0_NegVal(); }
static void Drv0_Step(void) { Step0_SetVal(); WAIT1_Waitus(5); Step0_ClrVal(); }
static void Drv0_Enable(void) { En0_ClrVal(); }
static void Drv0_Disable(void) { En0_SetVal(); }

static void Drv1_Dir(bool forward) { if (forward) {Dir1_SetVal();} else {Dir1_ClrVal();} }
static void Drv1_ToggleStep(void) { Step1_NegVal(); }
static void Drv1_Step(void) { Step1_SetVal(); WAIT1_Waitus(5); Step1_ClrVal(); }
static void Drv1_Enable(void) { En1_ClrVal(); }
static void Drv1_Disable(void) { En1_SetVal(); }

typedef struct {
  bool forward; /* current direction */
  bool enabled; /* if enabled or not */
  int8_t pos; /* current position, valid 0..FLOPPY_MAX_STEPS */
  uint32_t currentPeriod; /* current period in timer interrupt events. Zero if disabled */
  uint32_t currentTick;
  void(*Dir)(bool forward);
  void(*Step)(void);
  void(*ToggleStep)(void);
  void(*Enable)(void);
  void(*Disable)(void);
} FLOPPY_Drive;
typedef FLOPPY_Drive *FLOPPY_DriveHandle;

static FLOPPY_Drive FLOPPY_Drives[FLOPPY_NOF_DRIVES];

uint8_t FLOPPY_Enable(FLOPPY_DriveHandle drive) {
  if (!drive->enabled) {
    drive->Enable();
    drive->enabled = TRUE;
  }
  return ERR_OK;
}

uint8_t FLOPPY_Disable(FLOPPY_DriveHandle drive) {
  if (drive->enabled) {
    drive->enabled = FALSE;
    drive->Disable();
  }
  return ERR_OK;
}

uint8_t FLOPPY_SetPos(FLOPPY_DriveHandle drive, int pos) {
  drive->pos = pos;
  return ERR_OK;
}

uint8_t FLOPPY_SetDirection(FLOPPY_DriveHandle drive, bool forward) {
  if (drive->forward!=forward) { /* only if not already same direction */
    drive->Dir(forward);
    drive->forward = forward;
  }
  return ERR_OK;
}

uint8_t FLOPPY_Steps(FLOPPY_DriveHandle drive, int steps) {
  if (steps>0 && drive->pos<FLOPPY_MAX_STEPS) {
    FLOPPY_SetDirection(drive, TRUE);
  } else if (steps<0 && drive->pos>0) {
    FLOPPY_SetDirection(drive, FALSE);
  }
  while(steps!=0) {
    drive->Step();
    if (steps>0) {
      steps--;
    } else {
      steps++;
    }
    vTaskDelay(pdMS_TO_TICKS(5));
    if (drive->forward) {
      drive->pos++;
    } else {
      drive->pos--;
    }
    if (drive->pos==FLOPPY_MAX_STEPS) {
      FLOPPY_SetDirection(drive, FALSE); /* go backward */
    } else if (drive->pos==0) {
      FLOPPY_SetDirection(drive, TRUE); /* go forward */
    }
  }
  return ERR_OK;
}

void FLOPPY_OneStep(FLOPPY_DriveHandle drive) {
  if (drive->pos==FLOPPY_MAX_STEPS) {
    FLOPPY_SetDirection(drive, FALSE); /* go backward */
  } else if (drive->pos==0) {
    FLOPPY_SetDirection(drive, TRUE); /* go forward */
  }
  if (drive->forward) {
    drive->pos++;
  } else {
    drive->pos--;
  }
  drive->Step();
}

void FLOPPY_OnInterrupt(void) {
  int i;

  for(i=0;i<FLOPPY_NOF_DRIVES;i++) {
    if (FLOPPY_Drives[i].currentPeriod>0) { /* not disabled */
      FLOPPY_Drives[i].currentTick++; /* increment tick */
      if (FLOPPY_Drives[i].currentTick>=FLOPPY_Drives[i].currentPeriod) { /* check if expired */
        FLOPPY_Drives[i].ToggleStep(); /* toggle pin */
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
        FLOPPY_Drives[i].ToggleStep(); /* toggle pin */
      }
    }
  }
}

void FLOPPY_MIDI_SetBank(uint8_t channel, uint8_t value) {
  /* not supported */
}

void FLOPPY_MIDI_NoteOn(uint8_t channel, uint8_t note, uint8_t velocity) {
  if (channel>=FLOPPY_NOF_DRIVES) {
    return;
  }
  if (note>=FLOPPY_NOF_NOTES) {
    return;
  }
  if (note<=FLOPPY_NOF_NOTES+12) {
    note += 12; /* adjust note */
  }
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
    FLOPPY_Drives[i].Enable();
    FLOPPY_Drives[i].enabled = TRUE;
    FLOPPY_Drives[i].Dir(FALSE);
    FLOPPY_Drives[i].forward = FALSE;
    for(j=0;j<FLOPPY_MAX_STEPS+10;j++) {
      FLOPPY_Drives[i].Step();
      vTaskDelay(pdMS_TO_TICKS(1));
    }
    FLOPPY_Drives[i].pos = 0;
  }
  return ERR_OK;
}

static void FloppyTask(void *pvParameters) {
  FLOPPY_InitDrives();
  TI1_Enable();
  TI1_EnableEvent();
  MM_Play();
  for(;;) {
    vTaskDelay(pdMS_TO_TICKS(50));
  }
}

static uint8_t PrintStatus(const CLS1_StdIOType *io) {
  int i;
  uint8_t buf[16], buf2[32];

  CLS1_SendStatusStr((uint8_t*)"Floppy", (uint8_t*)"\r\n", io->stdOut);
  for(i=0;i<FLOPPY_NOF_DRIVES;i++) {
    UTIL1_strcpy(buf, sizeof(buf), (uint8_t*)"  drive ");
    UTIL1_strcatNum16u(buf, sizeof(buf), (uint16_t)i);
    UTIL1_chcat(buf, sizeof(buf), ':');
    buf2[0] = '\0';
    if (FLOPPY_Drives[i].enabled) {
      UTIL1_strcat(buf2, sizeof(buf2), (uint8_t*)"enabled  ");
    } else {
      UTIL1_strcat(buf2, sizeof(buf2), (uint8_t*)"disabled ");
    }
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
    CLS1_SendHelpStr((unsigned char*)"  home", (const unsigned char*)"Move heads to home position\r\n", io->stdOut);
    CLS1_SendHelpStr((unsigned char*)"  step <drv> <steps>", (const unsigned char*)"Perform number of steps (positive/negative)\r\n", io->stdOut);
    CLS1_SendHelpStr((unsigned char*)"  period <drv> <ticks>", (const unsigned char*)"Set period for drive, zero disables it\r\n", io->stdOut);
    CLS1_SendHelpStr((unsigned char*)"  note <drv> <note>", (const unsigned char*)"Play note (0..127)\r\n", io->stdOut);
    *handled = TRUE;
    return ERR_OK;
  } else if ((UTIL1_strcmp((char*)cmd, CLS1_CMD_STATUS)==0) || (UTIL1_strcmp((char*)cmd, "Floppy status")==0)) {
    *handled = TRUE;
    return PrintStatus(io);
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

  if (FRTOS1_xTaskCreate(
      FloppyTask,  /* pointer to the task */
      "Floppy", /* task name for kernel awareness debugging */
      configMINIMAL_STACK_SIZE, /* task stack size */
      (void*)NULL, /* optional task startup argument */
      tskIDLE_PRIORITY+1,  /* initial priority */
      (xTaskHandle*)NULL /* optional task handle to create */
    ) != pdPASS) {
  /*lint -e527 */
  for(;;){} /* error! probably out of memory */
    /*lint +e527 */
  }
  for(i=0;i<FLOPPY_NOF_DRIVES;i++) {
    FLOPPY_Drives[i].forward = FALSE;
    FLOPPY_Drives[i].enabled = FALSE;
    FLOPPY_Drives[i].pos = 0;
    FLOPPY_Drives[i].currentPeriod = 0;
    FLOPPY_Drives[i].currentTick = 0;
  }
  FLOPPY_Drives[0].Dir = Drv0_Dir;
  FLOPPY_Drives[0].Disable = Drv0_Disable;
  FLOPPY_Drives[0].Enable = Drv0_Enable;
  FLOPPY_Drives[0].Step = Drv0_Step;
  FLOPPY_Drives[0].ToggleStep = Drv0_ToggleStep;

  FLOPPY_Drives[1].Dir = Drv1_Dir;
  FLOPPY_Drives[1].Disable = Drv1_Disable;
  FLOPPY_Drives[1].Enable = Drv1_Enable;
  FLOPPY_Drives[1].Step = Drv1_Step;
  FLOPPY_Drives[1].ToggleStep = Drv1_ToggleStep;
}
#endif /* PL_HAS_FLOPPY */
