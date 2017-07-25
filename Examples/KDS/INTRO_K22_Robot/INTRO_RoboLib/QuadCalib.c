/*
 * QuadCalib.c
 *
 *  Created on: Jul 21, 2014
 *      Author: tastyger
 */
#include "Platform.h"
#if PL_HAS_QUAD_CALIBRATION
#include "QuadCalib.h"
#include "Shell.h"
#include "FRTOS1.h"
#include "WAIT1.h"
#include "MCP4728.h"
#include "TU_MCP4728.h"
#include "Q4CLeft.h"
#include "Q4CRight.h"
#include "Motor.h"
#if PL_HAS_DRIVE
  #include "Drive.h"
#endif


typedef struct {
  uint32_t lowTicks, highTicks;
  uint8_t lowPercent, highPercent;
} QuadTime_t;

#define NOF_SIGNALS 4

typedef bool (*GetChannelBitFct)(void);

static bool ChABit(void) {
  return (Q4CRight_GetVal()&1)!=0;
}

static bool ChBBit(void) {
  return (Q4CRight_GetVal()&2)!=0;
}

static bool ChCBit(void) {
  return (Q4CLeft_GetVal()&2)!=0;
}

static bool ChDBit(void) {
  return (Q4CLeft_GetVal()&1)!=0;
}

static GetChannelBitFct ChannelFct[NOF_SIGNALS] =
{
    ChABit,
    ChBBit,
    ChCBit,
    ChDBit
};

static uint8_t Measure(uint8_t channel, QuadTime_t *timing) {
  uint32_t timeout;
  #define TIMEOUT_VAL 0xffff /* just some waiting time */
  
  timing->highTicks = 0;
  timing->lowTicks = 0;
  timing->lowPercent = 0;
  timing->highPercent = 0;
  taskENTER_CRITICAL();
  /* trigger on raising edge */
  timeout = 0;
  while(ChannelFct[channel]()) { /* while high ... */
    /* wait until signal goes down */
    timeout++;
    if (timeout>TIMEOUT_VAL) {
      taskEXIT_CRITICAL();
      return ERR_FAILED;
    }
  }
  /* signal is low here, wait for raising edge */
  timeout = 0;
  while(!ChannelFct[channel]()) {
    /* wait until signal goes up */
    timeout++;
    if (timeout>TIMEOUT_VAL) {
      taskEXIT_CRITICAL();
      return ERR_FAILED;
    }
  }
  /* here signal is on the raising edge */
  (void)TU_MCP4728_ResetCounter(TU_MCP4728_DeviceData);
  timeout = 0;
  while(ChannelFct[channel]()) { /* while signal is high... */
    /* wait until signal goes down */
    timeout++;
    if (timeout>TIMEOUT_VAL) {
      taskEXIT_CRITICAL();
      return ERR_FAILED;
    }
  }
  /* signal is 0 now */
  timing->highTicks = TU_MCP4728_GetCounterValue(TU_MCP4728_DeviceData);
  timeout = 0;
  (void)TU_MCP4728_ResetCounter(TU_MCP4728_DeviceData);
  while(!ChannelFct[channel]()) { /* while signal is low... */
    /* wait until signal goes up */
    timeout++;
    if (timeout>TIMEOUT_VAL) {
      taskEXIT_CRITICAL();
      return ERR_FAILED;
    }
  }
  timing->lowTicks = TU_MCP4728_GetCounterValue(TU_MCP4728_DeviceData);
  taskEXIT_CRITICAL();
  timing->lowPercent  = (timing->lowTicks*100UL)/((uint32_t)timing->highTicks+(uint32_t)timing->lowTicks);
  timing->highPercent = (timing->highTicks*100UL)/((uint32_t)timing->highTicks+(uint32_t)timing->lowTicks);
  return ERR_OK;
}

static uint8_t Tune(const CLS1_StdIOType *io, uint8_t channel, MOT_MotorDevice *motorHandle) {
  #define TUNE_MOTOR_PERCENT 20
  uint16_t dac;
  QuadTime_t timing;
  uint8_t buf[48];
  uint8_t res;
 
#if PL_HAS_DRIVE
  (void)DRV_SetMode(DRV_MODE_NONE); /* turn off drive mode */
#endif
  MOT_SetSpeedPercent(motorHandle, TUNE_MOTOR_PERCENT);
  CLS1_SendStr((uint8_t*)"Tuning channel...\r\n", io->stdOut);
  res = ERR_FAILED;
  for(dac=0;dac<=MCP4728_MAX_DAC_VAL;) {
    UTIL1_strcpy(buf, sizeof(buf), (uint8_t*)"Channel: ");
    UTIL1_chcat(buf, sizeof(buf), (uint8_t)('A'+channel)); /* 0:A, 1:B, 2:C, 3:D */
    UTIL1_strcat(buf, sizeof(buf), (uint8_t*)" DAC: 0x");
    UTIL1_strcatNum16Hex(buf, sizeof(buf), dac);
    UTIL1_chcat(buf, sizeof(buf), ' ');
    CLS1_SendStr(buf, io->stdOut);
    if (MCP4728_FastWriteDAC(channel, dac)!=ERR_OK) { /* writes single channel DAC value, not updating EEPROM */
      CLS1_SendStr((uint8_t*)"ERROR writing DAC channel!\r\n", io->stdErr);
      res = ERR_FAILED;
      break;
    }
    WAIT1_WaitOSms(100); /* wait some time to allow DAC and OP-Amp change */
    if (Measure(channel, &timing)==ERR_OK) {
      buf[0] = '\0';
      UTIL1_strcatNum8u(buf, sizeof(buf), timing.highPercent);
      UTIL1_strcat(buf, sizeof(buf), (uint8_t*)"% high, low ");
      UTIL1_strcatNum8u(buf, sizeof(buf), timing.lowPercent);
      UTIL1_strcat(buf, sizeof(buf), (uint8_t*)"%\r\n");
      CLS1_SendStr(buf, io->stdOut);
      if (timing.highPercent==50 || timing.lowPercent==50) {
        CLS1_SendStr((uint8_t*)"Set!\r\n", io->stdErr);
        CLS1_SendStr((uint8_t*)"Writing to EEPROM...\r\n", io->stdOut);
        if (MCP4728_WriteDACandEE(channel, dac)!=ERR_OK) {
          CLS1_SendStr((uint8_t*)"ERROR writing DAC/EEPROM\r\n", io->stdErr);
          res = ERR_FAILED;
          break;
        }
        CLS1_SendStr((uint8_t*)"...done!\r\n", io->stdOut);
        res = ERR_OK;
        break; /* go to next channel */
      }
      dac += 0x1; /* smaller increase */
    } else {
      CLS1_SendStr((uint8_t*)"No signal\r\n", io->stdErr);
      dac += 0x10; /* larger increase */
    }
  } /* for finding DAC value */
  MOT_SetSpeedPercent(motorHandle, 0); /* turn off again */
  if (res!=ERR_OK) {
    CLS1_SendStr((uint8_t*)"ERROR!\r\n", io->stdErr);
  }
  CLS1_SendStr((uint8_t*)"Tuning finished!\r\n", io->stdOut);
  return res;
}

static uint8_t PrintStatus(const CLS1_StdIOType *io) {
  uint8_t buf[64], buf2[16];
  QuadTime_t timing;
  int i;
  
  CLS1_SendStatusStr((unsigned char*)"quadcalib", (unsigned char*)"\r\n", io->stdOut);
  for(i=0; i<NOF_SIGNALS; i++) {
    if (Measure(i, &timing)==ERR_OK) {
      buf[0] = '\0';
      UTIL1_strcatNum8u(buf, sizeof(buf), timing.lowPercent);
      UTIL1_strcat(buf, sizeof(buf), (uint8_t*)"% to ");
      UTIL1_strcatNum8u(buf, sizeof(buf), timing.highPercent);
      UTIL1_strcat(buf, sizeof(buf), (uint8_t*)"%, ");
      UTIL1_strcat(buf, sizeof(buf), (uint8_t*)"high: ");
      UTIL1_strcatNum32u(buf, sizeof(buf), timing.highTicks);
      UTIL1_strcat(buf, sizeof(buf), (uint8_t*)" ticks, low: ");
      UTIL1_strcatNum32u(buf, sizeof(buf), timing.lowTicks);
      UTIL1_strcat(buf, sizeof(buf), (uint8_t*)" ticks\r\n");
    } else {
      UTIL1_strcpy(buf, sizeof(buf), (uint8_t*)"TIMEOUT\r\n");
    }
    if (i==0) {
      UTIL1_strcpy(buf2, sizeof(buf2), (uint8_t*)"  Right A,C0");
    } else if (i==1) {
      UTIL1_strcpy(buf2, sizeof(buf2), (uint8_t*)"  Right B,C1");
    } else if (i==2) {
      UTIL1_strcpy(buf2, sizeof(buf2), (uint8_t*)"  Left  C,C2");
    } else {
      UTIL1_strcpy(buf2, sizeof(buf2), (uint8_t*)"  Left  D,C3");
    }
    CLS1_SendStatusStr(buf2, buf, io->stdOut);
  }
  return ERR_OK;
}

static uint8_t PrintHelp(const CLS1_StdIOType *io) {
  CLS1_SendHelpStr((unsigned char*)"quadcalib", (unsigned char*)"Group of application commands\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  help|status", (unsigned char*)"Print help or status information\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  tune <ch>", (unsigned char*)"Tune channel (0..3)\r\n", io->stdOut);
  return ERR_OK;
}

byte QUADCALIB_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io) {
  if (UTIL1_strcmp((char*)cmd, CLS1_CMD_HELP)==0 || UTIL1_strcmp((char*)cmd, "quadcalib help")==0) {
    *handled = TRUE;
    return PrintHelp(io);
  } else if ((UTIL1_strcmp((char*)cmd, CLS1_CMD_STATUS)==0) || (UTIL1_strcmp((char*)cmd, "quadcalib status")==0)) {
    *handled = TRUE;
    return PrintStatus(io);
  } else if ((UTIL1_strcmp((char*)cmd, "quadcalib tune 0")==0)) {
    *handled = TRUE;
    return Tune(io, 0, MOT_GetMotorHandle(MOT_MOTOR_RIGHT));
  } else if ((UTIL1_strcmp((char*)cmd, "quadcalib tune 1")==0)) {
    *handled = TRUE;
    return Tune(io, 1, MOT_GetMotorHandle(MOT_MOTOR_RIGHT));
  } else if ((UTIL1_strcmp((char*)cmd, "quadcalib tune 2")==0)) {
    *handled = TRUE;
    return Tune(io, 2, MOT_GetMotorHandle(MOT_MOTOR_LEFT));
  } else if ((UTIL1_strcmp((char*)cmd, "quadcalib tune 3")==0)) {
    *handled = TRUE;
    return Tune(io, 3, MOT_GetMotorHandle(MOT_MOTOR_LEFT));
  }
  return ERR_OK;
}
#endif /* PL_HAS_QUAD_CALIBRATION */
