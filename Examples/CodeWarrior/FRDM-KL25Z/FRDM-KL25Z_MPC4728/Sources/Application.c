/*
 * Application.c
 *      Author: Erich Styger
 */
#include "Platform.h"
#include "Application.h"
#include "Shell.h"
#include "LED1.h"
#include "FRTOS1.h"
#include "WAIT1.h"
#include "MPC4728.h"
#include "TU2.h"
#include "Q4CLeft.h"
#include "Q4CRight.h"
#if PL_HAS_MOTOR
#include "Motor.h"
#endif

typedef struct {
  uint32_t lowTicks, highTicks;
  uint8_t lowPercent, highPercent;
} QuadTime_t;

#define NOF_SIGNALS 4

typedef bool (*GetChannelBitFct)(void);

static bool Ch0Bit(void) {
  return (Q4CRight_GetVal()&1)!=0;
}

static bool Ch1Bit(void) {
  return (Q4CRight_GetVal()&2)!=0;
}

static bool Ch2Bit(void) {
  return (Q4CLeft_GetVal()&1)!=0;
}

static bool Ch3Bit(void) {
  return (Q4CLeft_GetVal()&2)!=0;
}

static GetChannelBitFct ChannelFct[NOF_SIGNALS] =
{
    Ch0Bit,
    Ch1Bit,
    Ch2Bit,
    Ch3Bit
};

static uint8_t Measure(uint8_t channel, QuadTime_t *timing) {
  uint32_t timeout;
  #define TIMEOUT_VAL 0x0fff /* just some waiting time */
  
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
  TU2_ResetCounter(TU2_DeviceData);
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
  timing->highTicks = TU2_GetCounterValue(TU2_DeviceData); 
  timeout = 0;
  TU2_ResetCounter(TU2_DeviceData);
  while(!ChannelFct[channel]()) { /* while signal is low... */
    /* wait until signal goes up */
    timeout++;
    if (timeout>TIMEOUT_VAL) {
      taskEXIT_CRITICAL();
      return ERR_FAILED;
    }
  }
  timing->lowTicks = TU2_GetCounterValue(TU2_DeviceData); 
  taskEXIT_CRITICAL();
  timing->lowPercent  = (timing->lowTicks*100UL)/((uint32_t)timing->highTicks+(uint32_t)timing->lowTicks);
  timing->highPercent = (timing->highTicks*100UL)/((uint32_t)timing->highTicks+(uint32_t)timing->lowTicks);
  return ERR_OK;
}

static uint8_t Tune(const CLS1_StdIOType *io) {
  uint8_t channel;
  uint16_t dac;
  int i;
  QuadTime_t timing;
  uint8_t buf[32];
  uint8_t res;
  uint16_t dacArr[4];
  uint8_t pd[4];
 
  MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_LEFT), 10);
  MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_RIGHT), 10);
  for(i=0;i<4;i++) { /* init */
    dacArr[i] = 0;
    pd[i] = 0;
  }
  CLS1_SendStr((uint8_t*)"Tuning....\r\n", io->stdOut);
  res = ERR_OK;
  for(channel=0;channel<NOF_SIGNALS;channel++) {
    for(i=0,dac=0;i<80 && dac<MPC4728_MAX_DAC_VAL;i++,dac += 0x10) {
      UTIL1_strcpy(buf, sizeof(buf), (uint8_t*)"Channel: ");
      UTIL1_strcatNum8u(buf, sizeof(buf), channel);
      UTIL1_strcat(buf, sizeof(buf), (uint8_t*)" DAC: 0x");
      UTIL1_strcatNum16Hex(buf, sizeof(buf), dac);
      UTIL1_chcat(buf, sizeof(buf), ' ');
      CLS1_SendStr(buf, io->stdOut);
      dacArr[channel] = dac;
      if (MPC4728_FastWriteDAC(dacArr, sizeof(dacArr), pd, sizeof(pd))!=ERR_OK) {
        CLS1_SendStr((uint8_t*)"ERROR writing DAC/EE\r\n", io->stdErr);
        res = ERR_FAILED;
        break;
      }
      WAIT1_Waitms(50); /* wait some time to allow change */
      if (Measure(channel, &timing)==ERR_OK) {
        buf[0] = '\0';
        UTIL1_strcatNum8u(buf, sizeof(buf), timing.highPercent);
        UTIL1_strcat(buf, sizeof(buf), (uint8_t*)"% high, low ");
        UTIL1_strcatNum8u(buf, sizeof(buf), timing.lowPercent);
        UTIL1_strcat(buf, sizeof(buf), (uint8_t*)"%\r\n");
        CLS1_SendStr(buf, io->stdOut);
        if (timing.highPercent==50 || timing.lowPercent==50) {
          CLS1_SendStr((uint8_t*)"Set!\r\n", io->stdErr);
          break;
        }
      } else {
        CLS1_SendStr((uint8_t*)"No signal\r\n", io->stdErr);
      }
    } /* for */
    if (res!=ERR_OK) {
      CLS1_SendStr((uint8_t*)"ERROR!\r\n", io->stdErr);
      break;
    }
  } /* for */
  MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_LEFT), 0);
  MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_RIGHT), 0);
  CLS1_SendStr((uint8_t*)"Writing to EEPROM...\r\n", io->stdOut);
  for (channel=0;channel<NOF_SIGNALS;channel++) {
    if (MPC4728_SingleWriteDACandEE(channel, dacArr[channel])!=ERR_OK) {
      CLS1_SendStr((uint8_t*)"ERROR writing DAC/EE\r\n", io->stdErr);
      res = ERR_FAILED;
      break;
    }
    WAIT1_Waitms(500); /* give EEPROM time to write data */
  }
  CLS1_SendStr((uint8_t*)"finished!\r\n", io->stdOut);
  return res;
}

static uint8_t PrintStatus(const CLS1_StdIOType *io) {
  uint8_t buf[48], buf2[16];
  QuadTime_t timing;
  int i;
  
  CLS1_SendStatusStr((unsigned char*)"app", (unsigned char*)"\r\n", io->stdOut);
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
    if (i==0 || i==1) {
      UTIL1_strcpy(buf2, sizeof(buf2), (uint8_t*)"  Right C");
    } else {
      UTIL1_strcpy(buf2, sizeof(buf2), (uint8_t*)"  Left  C");
    }
    UTIL1_strcatNum8u(buf2, sizeof(buf2), i);
    CLS1_SendStatusStr(buf2, buf, io->stdOut);
  }
  return ERR_OK;
}

static uint8_t PrintHelp(const CLS1_StdIOType *io) {
  CLS1_SendHelpStr((unsigned char*)"app", (unsigned char*)"Group of application commands\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  help|status", (unsigned char*)"Print help or status information\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  tune", (unsigned char*)"Tune all channels\r\n", io->stdOut);
  return ERR_OK;
}

byte APP_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io) {
  if (UTIL1_strcmp((char*)cmd, CLS1_CMD_HELP)==0 || UTIL1_strcmp((char*)cmd, "app help")==0) {
    *handled = TRUE;
    return PrintHelp(io);
  } else if ((UTIL1_strcmp((char*)cmd, CLS1_CMD_STATUS)==0) || (UTIL1_strcmp((char*)cmd, "app status")==0)) {
    *handled = TRUE;
    return PrintStatus(io);
  } else if ((UTIL1_strcmp((char*)cmd, "app tune")==0)) {
    *handled = TRUE;
    return Tune(io);
  }
  return ERR_OK;
}


static portTASK_FUNCTION(AppTask, pvParameters) {
  (void)pvParameters; /* not used */
  for(;;) {
    LED1_Neg();
    vTaskDelay(pdMS_TO_TICKS(500));
  } /* for */
}

void APP_Run(void) {
  if (xTaskCreate(
        AppTask,  /* pointer to the task */
        "App", /* task name for kernel awareness debugging */
        configMINIMAL_STACK_SIZE, /* task stack size */
        (void*)NULL, /* optional task startup argument */
        tskIDLE_PRIORITY,  /* initial priority */
        (TaskHandle_t*)NULL /* optional task handle to create */
      ) != pdPASS) {
    /*lint -e527 */
    for(;;){}; /* error! probably out of memory */
    /*lint +e527 */
  }
  MOT_Init();
  SHELL_Init();
  MPC4728_Init();
  FRTOS1_vTaskStartScheduler();
}

