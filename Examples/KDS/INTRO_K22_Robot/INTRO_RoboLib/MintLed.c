/*
 * MintLed.c
 *  Driver for 3 PCA9685 16-channel, 12-bit PWM LED controller
 *  I2C addresses:
 *  U1: 0b100000
 *  U2: 0b100010
 *  U3: 0b100001
 *
 *  Created on: 22.08.2016
 *      Author: Erich Styger Local
 */

#include "Platform.h"
#if PL_HAS_MINT_LED
#include "MintLed.h"
#include "PCA9685.h"
#include "GI2C1.h"
#include "Distance.h"

#define MINTLED_NOF_PCA   3  /* number of PCA9685 */

#if MINTLED_NOF_PCA >= 1
  #include "PCAOE1.h"
#endif
#if MINTLED_NOF_PCA >= 2
  #include "PCAOE2.h"
#endif
#if MINTLED_NOF_PCA >= 3
  #include "PCAOE3.h"
#endif

#if MINTLED_NOF_PCA >= 1
  #define MINTLED_U1_I2C_ADDR  (0b1000000)
#endif
#if MINTLED_NOF_PCA >= 2
  #define MINTLED_U2_I2C_ADDR  (0b1000001)
#endif
#if MINTLED_NOF_PCA >= 3
  #define MINTLED_U3_I2C_ADDR  (0b1000010)
#endif

typedef enum {
#if MINTLED_NOF_PCA >= 1
  /* U1, LED0-14 */
  MINT_LED_D1,
  MINT_LED_D2,
  MINT_LED_D3,
  MINT_LED_D4,
  MINT_LED_D5,
#endif
#if MINTLED_NOF_PCA >= 2
  /* U2, LED0-14 */
  MINT_LED_D6,
  MINT_LED_D7,
  MINT_LED_D8,
  MINT_LED_D9,
  MINT_LED_D10,
#endif
#if MINTLED_NOF_PCA >= 3
  /* U2, LED0-8 */
  MINT_LED_D11,
  MINT_LED_D12,
  MINT_LED_D13,
#endif
  MINT_LED_NOF_LEDS /* must be last */
} MINT_LED;

typedef struct {
  uint8_t i2cAddr; /* I2C address of LED */
  uint8_t ledNo; /* LED number (0 for LED0 inside the PCA9685) */
} PCA9685_LEDDesc;

/* array of LED descriptor: each entry describes a LED (red, green and blue) */
static const PCA9685_LEDDesc PCA9685_LEDs[][3] =
{
#if MINTLED_NOF_PCA >= 1
  /* MINT_LED_D1 */  {{MINTLED_U1_I2C_ADDR, 0}, {MINTLED_U1_I2C_ADDR, 1}, {MINTLED_U1_I2C_ADDR, 2}},
  /* MINT_LED_D2 */  {{MINTLED_U1_I2C_ADDR, 3}, {MINTLED_U1_I2C_ADDR, 4}, {MINTLED_U1_I2C_ADDR, 5}},
  /* MINT_LED_D3 */  {{MINTLED_U1_I2C_ADDR, 6}, {MINTLED_U1_I2C_ADDR, 7}, {MINTLED_U1_I2C_ADDR, 8}},
  /* MINT_LED_D4 */  {{MINTLED_U1_I2C_ADDR, 9}, {MINTLED_U1_I2C_ADDR, 10}, {MINTLED_U1_I2C_ADDR, 11}},
  /* MINT_LED_D5 */  {{MINTLED_U1_I2C_ADDR, 12}, {MINTLED_U1_I2C_ADDR, 13}, {MINTLED_U1_I2C_ADDR, 14}},
#endif
#if MINTLED_NOF_PCA >= 2
  /* MINT_LED_D6 */  {{MINTLED_U2_I2C_ADDR, 0}, {MINTLED_U2_I2C_ADDR, 1}, {MINTLED_U2_I2C_ADDR, 2}},
  /* MINT_LED_D7 */  {{MINTLED_U2_I2C_ADDR, 3}, {MINTLED_U2_I2C_ADDR, 4}, {MINTLED_U2_I2C_ADDR, 5}},
  /* MINT_LED_D8 */  {{MINTLED_U2_I2C_ADDR, 6}, {MINTLED_U2_I2C_ADDR, 7}, {MINTLED_U2_I2C_ADDR, 8}},
  /* MINT_LED_D9 */  {{MINTLED_U2_I2C_ADDR, 9}, {MINTLED_U2_I2C_ADDR, 10}, {MINTLED_U2_I2C_ADDR, 11}},
  /* MINT_LED_D10 */ {{MINTLED_U2_I2C_ADDR, 12}, {MINTLED_U2_I2C_ADDR, 13}, {MINTLED_U2_I2C_ADDR, 14}},
#endif
#if MINTLED_NOF_PCA >= 3
  /* MINT_LED_D11 */  {{MINTLED_U3_I2C_ADDR, 3}, {MINTLED_U3_I2C_ADDR, 4}, {MINTLED_U3_I2C_ADDR, 5}},
  /* MINT_LED_D12 */  {{MINTLED_U3_I2C_ADDR, 0}, {MINTLED_U3_I2C_ADDR, 1}, {MINTLED_U3_I2C_ADDR, 2}},
  /* MINT_LED_D13 */  {{MINTLED_U3_I2C_ADDR, 6}, {MINTLED_U3_I2C_ADDR, 7}, {MINTLED_U3_I2C_ADDR, 8}},
#endif
};

#define MINT_LED_MIDDLE_LED MINT_LED_D13  /* position of middle LED */

typedef uint16_t MINTELED_Color; /* have 12 bits PWM */

typedef struct {
  MINTELED_Color r, g, b;
} MINTLED_RGBLed;


static MINTLED_RGBLed LEDs[MINT_LED_NOF_LEDS];
static volatile MINTLED_ModeType newLEDMode, currLEDMode;

/*!
 * \brief Turns all the devices on or off
 */
static void MINTLED_On(bool on) {
  if (on) { /* low active */
#if MINTLED_NOF_PCA >= 1
    PCAOE1_ClrVal();
#endif
#if MINTLED_NOF_PCA >= 2
    PCAOE2_ClrVal();
#endif
#if MINTLED_NOF_PCA >= 3
    PCAOE3_ClrVal();
#endif
  } else {
#if MINTLED_NOF_PCA >= 1
    PCAOE1_SetVal();
#endif
#if MINTLED_NOF_PCA >= 2
    PCAOE2_SetVal();
#endif
#if MINTLED_NOF_PCA >= 3
    PCAOE3_SetVal();
#endif
  }
}

#if 0
void MINTLED_WriteAddress(uint8_t deviceI2CAddr, uint8_t addr, uint8_t val) {
  (void)GI2C1_WriteAddress(deviceI2CAddr, &addr, sizeof(addr), &val, sizeof(val));
}
#endif

static uint8_t I2CDeviceAddr(uint8_t deviceID) {
  if (deviceID==0) {
    return MINTLED_U1_I2C_ADDR;
#if MINTLED_NOF_PCA >= 2
  } else if (deviceID==1) {
    return MINTLED_U2_I2C_ADDR;
#endif
#if MINTLED_NOF_PCA >= 3
  } else if (deviceID==2) {
    return MINTLED_U3_I2C_ADDR;
#endif
  } else {
    return 0xff;
  }
}

#if 0 /* not used */
static uint8_t MINTLED_SetChannelPWM(uint8_t deviceID, uint8_t channel, uint16_t value) {
  uint8_t deviceI2CAddr = I2CDeviceAddr(deviceID);

  if (channel>15) { /* only channel 0..15 per device */
    return ERR_FAILED;
  }
  if (value>4095) {
    value = 4096;
  }
  PCA9685_SetChannelPWM(deviceI2CAddr, channel, value);
  return ERR_OK;
}
#endif

/*!
 * \brief Writes the PWM info to all of the PCA9685
 */
static void MINTLED_Update(void) {
  int i;

  for (i=0;i<MINT_LED_NOF_LEDS;i++) {
    PCA9685_SetChannelPWM(PCA9685_LEDs[i][0].i2cAddr, PCA9685_LEDs[i][0].ledNo, LEDs[i].r);
    PCA9685_SetChannelPWM(PCA9685_LEDs[i][1].i2cAddr, PCA9685_LEDs[i][1].ledNo, LEDs[i].g);
    PCA9685_SetChannelPWM(PCA9685_LEDs[i][2].i2cAddr, PCA9685_LEDs[i][2].ledNo, LEDs[i].b);
  } /* for */
}

static void MINTLED_SetLEDColor(MINT_LED led, MINTELED_Color red, MINTELED_Color green, MINTELED_Color blue) {
  if (led<MINT_LED_NOF_LEDS) {
    LEDs[led].r = red&0xfff;
    LEDs[led].g = green&0xfff;
    LEDs[led].b = blue&0xfff;
  }
}

static void SetAllLed(uint16_t red, uint16_t green, uint16_t blue) {
  int i;

  for (i=0;i<MINT_LED_NOF_LEDS;i++) {
    MINTLED_SetLEDColor(i, red, green, blue);
  }
}

void MINTLED_SetMode(MINTLED_ModeType mode) {
  newLEDMode = mode;
}

static const uint8_t *MINTLED_ModeToStr(MINTLED_ModeType mode) {
  switch(mode) {
    case MINTLED_MODE_NONE:               return (uint8_t*)"NONE";
    case MINTLED_MODE_ERROR:              return (uint8_t*)"ERROR";
    case MINTLED_MODE_TEST:               return (uint8_t*)"TEST";
    case MINTLED_MODE_JOYSTICK:           return (uint8_t*)"JOYSTICK";
    case MINTLED_MODE_AUTOMATIC:          return (uint8_t*)"AUTOMATIC";
    case MINTLED_MODE_BALL_REQUESTD:      return (uint8_t*)"BALL_REQUESTED";
    case MINTLED_MODE_WAIT_BALL_REMOVAL:  return (uint8_t*)"WAIT_BALL_REOVAL";
    case MINTLED_MODE_BALL_LOADED:        return (uint8_t*)"BALL_LOADED";
    case MINTLED_MODE_GOTO_START:         return (uint8_t*)"GOTO_START";
    case MINTLED_MODE_GOTO_FINISH:        return (uint8_t*)"GOTO_FINISH";
    case MINTLED_MODE_MANUAL_ON_START:    return (uint8_t*)"MANUAL_ON_START";
    case MINTLED_MODE_MANUAL_ON_FINISH:   return (uint8_t*)"MANUAL_ON_FINISH";
    case MINTLED_MODE_STANDBY:            return (uint8_t*)"STANDBY";
    default:
      break;
  }
  return (uint8_t*)"????";
}

#if 0
static void Test(void) {
  #define NOF_REG_TO_READ  6
  uint8_t data[MINTLED_NOF_PCA][NOF_REG_TO_READ];
  int i, j;
  uint8_t res, deviceI2CAddr;

  for(i=0;i<MINTLED_NOF_PCA;i++) {
    deviceI2CAddr = I2CDeviceAddr(i);
    for(j=0;j<NOF_REG_TO_READ;j++) {
      res = GI2C1_ReadByteAddress8(deviceI2CAddr, j, &data[i][j]);
      if (res!=ERR_OK) {
        for(;;);
      }
    }
  }
}
#endif

static void MintLedTask(void *param) {
  int cntr, i;
  uint16_t val;

  (void)param; /* not used */
  /* init */
  for(i=0;i<MINTLED_NOF_PCA;i++) {
    PCA9685_Reset(I2CDeviceAddr(i)); /* reset and disable PWM */
    PCA9685_SetPWMFrequency(I2CDeviceAddr(i), 1600); /* set base frequency */
  }
  //Test();
  SetAllLed(0,0,0); /* init data and clear all LEDs */
  currLEDMode = MINTLED_MODE_NONE;
  for(;;) {
    if (newLEDMode!=currLEDMode) { /* switch to different mode */
      currLEDMode = newLEDMode;
      MINTLED_On(TRUE); /* turn on */
      cntr = 0; /* reset counter */
    }
    if (currLEDMode==MINTLED_MODE_NONE) {
      /* change LED by shell for testing purpose */
    } else if (currLEDMode==MINTLED_MODE_ERROR) {
      /* blinking all in red */
      if (cntr==0) {
        SetAllLed(0xfff, 0, 0);
        MINTLED_Update();
        cntr++;
      } else if (cntr==5) {
        SetAllLed(0, 0, 0);
        MINTLED_Update();
        cntr = 0;
      } else {
        cntr++;
      }
    } else if (currLEDMode==MINTLED_MODE_TEST) {
      /* test pattern on LEDs to spot hardware problems */
      if (cntr==0) {
        SetAllLed(0xfff, 0, 0);
        MINTLED_Update();
      } else if (cntr==20) {
        SetAllLed(0, 0xfff, 0);
        MINTLED_Update();
      } else if (cntr==40) {
        SetAllLed(0,0,0xfff);
        MINTLED_Update();
      } else if (cntr==60) {
        SetAllLed(0,0,0);
        MINTLED_Update();
      } else if (cntr==80) {
        cntr = -1;
      }
      cntr++;
    } else if (currLEDMode==MINTLED_MODE_JOYSTICK) {
      /* slow up dimming of LEDs in orange */
      if (cntr==0) {
        SetAllLed(0, 0, 0);
        cntr++;
      } else if (cntr<=20) { /* increase brightness */
        uint8_t wall;

        val = cntr*(0xfff/20);
        SetAllLed(val, val, 0); /* all green by default */
        wall = DIST_CheckSurrounding();
        if (wall!=0) {
          if (wall&(1<<0)) { /* rear */
            MINTLED_SetLEDColor(3, 0xfff, 0, 0);
            MINTLED_SetLEDColor(4, 0xfff, 0, 0);
            MINTLED_SetLEDColor(5, 0xfff, 0, 0);
            MINTLED_SetLEDColor(6, 0xfff, 0, 0);
          }
          if (wall&(1<<1)) { /* right */
            MINTLED_SetLEDColor(6, 0xfff, 0, 0);
            MINTLED_SetLEDColor(7, 0xfff, 0, 0);
            MINTLED_SetLEDColor(8, 0xfff, 0, 0);
            MINTLED_SetLEDColor(9, 0xfff, 0, 0);
          }
          if (wall&(1<<2)) { /* front */
            MINTLED_SetLEDColor(9, 0xfff, 0, 0);
            MINTLED_SetLEDColor(10, 0xfff, 0, 0);
            MINTLED_SetLEDColor(11, 0xfff, 0, 0);
            MINTLED_SetLEDColor(0, 0xfff, 0, 0);
          }
          if (wall&(1<<3)) { /* left */
            MINTLED_SetLEDColor(0, 0xfff, 0, 0);
            MINTLED_SetLEDColor(1, 0xfff, 0, 0);
            MINTLED_SetLEDColor(2, 0xfff, 0, 0);
            MINTLED_SetLEDColor(3, 0xfff, 0, 0);
          }
        }
        cntr++;
      } else {
        cntr = 0; /* start over again */
      }
      MINTLED_Update();
    } else if (currLEDMode==MINTLED_MODE_AUTOMATIC) {
      /* slow up dimming of LEDs in white */
      if (cntr==0) {
        SetAllLed(0, 0, 0);
        cntr++;
      } else if (cntr<=20) { /* increase brightness */
        uint16_t val;

        val = cntr*(0xfff/20);
        SetAllLed(val, val, val);
        cntr++;
      } else {
        cntr = 0; /* start over again */
      }
      MINTLED_Update();
    } else if (currLEDMode==MINTLED_MODE_BALL_REQUESTD) {
      /* show all LED in blue */
      if (cntr==0) { /* init */
        SetAllLed(0, 0, 0); /* all off */
        MINTLED_Update();
        cntr++;
      } else if (cntr<=20) { /* increase brightness */
        uint16_t val;

        val = cntr*(0xfff/20);
        SetAllLed(0, 0, val); /* all blue */
        //MINTLED_SetLEDColor(MINT_LED_MIDDLE_LED, 0, 0, val); /* middle LED */
        MINTLED_Update();
        cntr++;
      } else {
        cntr = 0;
      }
    } else if (currLEDMode==MINTLED_MODE_BALL_LOADED) {
      /* slow up-down dimming of LEDs in blue */
      if (cntr==0) {
        SetAllLed(0, 0, 0);
        cntr++;
      } else if (cntr<=20) { /* increase blue brightness */
        val = cntr*(0xfff/20);
        SetAllLed(0, 0, val);
        cntr++;
      } else if (cntr<=40) { /* reduce color again */
        val = 0xfff-((cntr-20)*(0xfff/20));
        SetAllLed(0, 0, val);
        cntr++;
      } else {
        cntr = 0; /* start over again */
      }
      MINTLED_Update();
    } else if (currLEDMode==MINTLED_MODE_WAIT_BALL_REMOVAL) {
      /* show all LED in green */
      if (cntr==0) { /* init */
        SetAllLed(0, 0, 0); /* all off */
        cntr++;
      } else if (cntr<=50) { /* increase blue brightness */
        val = cntr*(0xfff/50);
        SetAllLed(0, val, 0);
        //MINTLED_SetLEDColor(MINT_LED_MIDDLE_LED, 0, val, 0); /* middle LED */
        cntr++;
      } else {
        cntr = 0;
      }
      MINTLED_Update();
    } else if (currLEDMode==MINTLED_MODE_GOTO_START) {
      /* green LED running around (excluding the middle LED) */
      if (cntr==0) { /* init */
        SetAllLed(0, 0, 0);
        MINTLED_SetLEDColor(0, 0, 0, 0xfff); /* first LED on */
      } else if (cntr<=MINT_LED_NOF_LEDS-2) { /*  excluding middle LED */
        MINTLED_SetLEDColor(cntr-1, 0, 0, 0); /* clear previous led */
        MINTLED_SetLEDColor(cntr, 0, 0, 0xfff); /* turn on next LED */
      } else if (cntr==MINT_LED_NOF_LEDS-1) { /* last LED is middle LED */
        MINTLED_SetLEDColor(cntr-1, 0, 0, 0); /* clear last led */
        MINTLED_SetLEDColor(0, 0, 0, 0xfff); /* turn on first LED */
        cntr = 0;
      }
      MINTLED_Update();
      cntr++;
    } else if (currLEDMode==MINTLED_MODE_GOTO_FINISH) {
#if 1
      /* right half green, left half blue */
      if (cntr==0) { /* init */
        SetAllLed(0, 0, 0); /* all off */
      } else if (cntr==5) { /* blink */
        /* left blue */
        MINTLED_SetLEDColor(11, 0, 0, 0xfff);
        MINTLED_SetLEDColor(0, 0, 0, 0xfff);
        MINTLED_SetLEDColor(1, 0, 0, 0xfff);
        MINTLED_SetLEDColor(2, 0, 0, 0xfff);
        MINTLED_SetLEDColor(3, 0, 0, 0xfff);
        MINTLED_SetLEDColor(4, 0, 0, 0xfff);
        /* right green */
        MINTLED_SetLEDColor(5, 0, 0xfff, 0);
        MINTLED_SetLEDColor(6, 0, 0xfff, 0);
        MINTLED_SetLEDColor(7, 0, 0xfff, 0);
        MINTLED_SetLEDColor(8, 0, 0xfff, 0);
        MINTLED_SetLEDColor(9, 0, 0xfff, 0);
        MINTLED_SetLEDColor(10, 0, 0xfff, 0);
        /* middle red */
        MINTLED_SetLEDColor(12, 0xfff, 0, 0);

      } else if (cntr==10) {
        SetAllLed(0, 0, 0); /* all off */
        cntr = 0;
      }
#else
      /* orange LED running around (excluding the middle LED) */
      if (cntr==0) { /* init */
        SetAllLed(0, 0, 0);
        MINTLED_SetLEDColor(0, 0, 0, 0xfff); /* first LED on */
      } else if (cntr<=MINT_LED_NOF_LEDS-2) { /*  excluding middle LED */
        MINTLED_SetLEDColor(cntr-1, 0, 0, 0); /* clear previous led */
        MINTLED_SetLEDColor(cntr, 0, 0, 0xfff); /* turn on next LED */
      } else if (cntr==MINT_LED_NOF_LEDS-1) { /* last LED is middle LED */
        MINTLED_SetLEDColor(cntr-1, 0, 0, 0); /* clear last led */
        MINTLED_SetLEDColor(0, 0, 0, 0xfff); /* turn on first LED */
        cntr = 0;
      }
#endif
      MINTLED_Update();
      cntr++;
    } else if (currLEDMode==MINTLED_MODE_STANDBY) {
      /* all in green, low brightness */
      if (cntr==0) { /* init */
        SetAllLed(0, 0x8f, 0);
        MINTLED_Update();
        cntr++;
      }
    } else if (currLEDMode==MINTLED_MODE_MANUAL_ON_START) {
#if 0
      /* blink all in green */
      if (cntr==0) { /* init */
        SetAllLed(0, 0, 0); /* all off */
      } else if (cntr==5) { /* blink */
        SetAllLed(0, 0xfff, 0); /* all on */
      } else if (cntr==10) {
        SetAllLed(0, 0, 0); /* all off */
        cntr = 0;
      }
#else
      /* left half green, right half blue */
      if (cntr==0) { /* init */
        SetAllLed(0, 0, 0); /* all off */
      } else if (cntr==5) { /* blink */
        /* left green */
        MINTLED_SetLEDColor(11, 0, 0xfff, 0);
        MINTLED_SetLEDColor(0, 0, 0xfff, 0);
        MINTLED_SetLEDColor(1, 0, 0xfff, 0);
        MINTLED_SetLEDColor(2, 0, 0xfff, 0);
        MINTLED_SetLEDColor(3, 0, 0xfff, 0);
        MINTLED_SetLEDColor(4, 0, 0xfff, 0);
        /* right blue */
        MINTLED_SetLEDColor(5, 0, 0, 0xfff);
        MINTLED_SetLEDColor(6, 0, 0, 0xfff);
        MINTLED_SetLEDColor(7, 0, 0, 0xfff);
        MINTLED_SetLEDColor(8, 0, 0, 0xfff);
        MINTLED_SetLEDColor(9, 0, 0, 0xfff);
        MINTLED_SetLEDColor(10, 0, 0, 0xfff);
        /* middle red */
        MINTLED_SetLEDColor(12, 0xfff, 0, 0);

      } else if (cntr==10) {
        SetAllLed(0, 0, 0); /* all off */
        cntr = 0;
      }
#endif
      cntr++;
      MINTLED_Update();
    } else if (currLEDMode==MINTLED_MODE_MANUAL_ON_FINISH) {
      /* blink all in blue */
      if (cntr==0) { /* init */
        SetAllLed(0, 0, 0); /* all off */
      } else if (cntr==5) { /* blink */
        SetAllLed(0, 0, 0xfff); /* all on */
      } else if (cntr==10) {
        SetAllLed(0, 0, 0); /* all off */
        cntr = 0;
      }
      cntr++;
      MINTLED_Update();
    }
    vTaskDelay(pdMS_TO_TICKS(100));
  }
}

static void MINTLED_PrintHelp(const CLS1_StdIOType *io) {
  CLS1_SendHelpStr((unsigned char*)"mintled", (unsigned char*)"Group of mint LED commands\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  help|status", (unsigned char*)"Shows mint  help or status\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  rgb <led> red geen blue", (unsigned char*)"Sets color of led, e.g. 'rgb 2 0xf10 0x50 0\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  mode <nr>", (unsigned char*)"Set LED mode\r\n", io->stdOut);
}

static void MINTLED_PrintStatus(const CLS1_StdIOType *io) {
  uint8_t buf[32];

  CLS1_SendStatusStr((unsigned char*)"mintled", (unsigned char*)"\r\n", io->stdOut);
  UTIL1_Num16uToStr(buf, sizeof(buf), currLEDMode);
  UTIL1_strcat(buf, sizeof(buf), (uint8_t*)" ");
  UTIL1_strcat(buf, sizeof(buf), MINTLED_ModeToStr(currLEDMode));
  UTIL1_strcat(buf, sizeof(buf), (uint8_t*)"\r\n");
  CLS1_SendStatusStr((unsigned char*)"  mode", buf, io->stdOut);

  UTIL1_Num16uToStr(buf, sizeof(buf), MINTLED_NOF_PCA);
  UTIL1_strcat(buf, sizeof(buf), (uint8_t*)"\r\n");
  CLS1_SendStatusStr((unsigned char*)"  PCA9685", buf, io->stdOut);

  UTIL1_Num16uToStr(buf, sizeof(buf), MINT_LED_NOF_LEDS);
  UTIL1_strcat(buf, sizeof(buf), (uint8_t*)"\r\n");
  CLS1_SendStatusStr((unsigned char*)"  LEDs", buf, io->stdOut);
}

uint8_t MINTLED_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io) {
  uint8_t res = ERR_OK;

  if (UTIL1_strcmp((char*)cmd, (char*)CLS1_CMD_HELP)==0 || UTIL1_strcmp((char*)cmd, (char*)"mintled help")==0) {
    MINTLED_PrintHelp(io);
    *handled = TRUE;
  } else if (UTIL1_strcmp((char*)cmd, (char*)CLS1_CMD_STATUS)==0 || UTIL1_strcmp((char*)cmd, (char*)"mintled status")==0) {
    MINTLED_PrintStatus(io);
    *handled = TRUE;
  } else if (UTIL1_strncmp((char*)cmd, (char*)"mintled mode ", sizeof("mintled mode ")-1)==0) {
    const unsigned char *p;
    int32_t val;

    *handled = TRUE;
    p = cmd+sizeof("mintled mode ")-1;
    res = UTIL1_xatoi(&p, &val);
    if (res==ERR_OK && val>=0 && val<MINTLED_MODE_NOF_MODES) {
      /* clear all before switching to custom mode */
      SetAllLed(0,0,0); /* all off */
      MINTLED_Update(); /* updated LEDs */
      MINTLED_SetMode(val);
    } else {
      res = ERR_FAILED;
    }
  } else if (UTIL1_strncmp((char*)cmd, (char*)"mintled rgb ", sizeof("mintled rgb ")-1)==0) {
    const unsigned char *p;
    int32_t led, red, green, blue;

    *handled = TRUE;
    p = cmd+sizeof("mintled rgb ")-1;
    if (   UTIL1_xatoi(&p, &led)==ERR_OK && led>=0 && led<=MINT_LED_NOF_LEDS
        && UTIL1_xatoi(&p, &red)==ERR_OK
        && UTIL1_xatoi(&p, &green)==ERR_OK
        && UTIL1_xatoi(&p, &blue)==ERR_OK
       )
    {
      MINTLED_SetLEDColor(led, red, green, blue);
      MINTLED_Update();
    } else {
      res = ERR_FAILED;
    }
  }
  return res;
}


void MINTLED_Init(void) {
  newLEDMode = MINTLED_MODE_NONE;
  if (xTaskCreate(MintLedTask, "MintLed", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL) != pdPASS) {
    for(;;){} /* error */
  }
}

#endif /* PL_HAS_MINT_LED */
