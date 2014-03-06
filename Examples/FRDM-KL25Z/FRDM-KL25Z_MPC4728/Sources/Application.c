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
} QuadTime_t;

#define NOF_SIGNALS 4

static QuadTime_t signals[NOF_SIGNALS];

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

static uint8_t Measure(uint8_t channel) {
  uint32_t timeout;
  #define TIMEOUT_VAL 0xffff
  
  signals[channel].highTicks = 0;
  signals[channel].lowTicks = 0;
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
  signals[channel].highTicks = TU2_GetCounterValue(TU2_DeviceData); 
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
  signals[channel].lowTicks = TU2_GetCounterValue(TU2_DeviceData); 
  taskEXIT_CRITICAL();
  return ERR_OK;
}

static uint8_t PrintStatus(const CLS1_StdIOType *io) {
  uint8_t buf[48], buf2[16];
  int i;
  
  CLS1_SendStatusStr((unsigned char*)"app", (unsigned char*)"\r\n", io->stdOut);
  for(i=0; i<NOF_SIGNALS; i++) {
    if (Measure(i)==ERR_OK) {
      UTIL1_strcpy(buf, sizeof(buf), (uint8_t*)"high: ");
      UTIL1_strcatNum32u(buf, sizeof(buf), signals[i].highTicks);
      UTIL1_strcat(buf, sizeof(buf), (uint8_t*)" ticks, low: ");
      UTIL1_strcatNum32u(buf, sizeof(buf), signals[i].lowTicks);
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
  CLS1_SendHelpStr((unsigned char*)"  measure", (unsigned char*)"General Call Reset\r\n", io->stdOut);
  return ERR_OK;
}

byte APP_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io) {
  if (UTIL1_strcmp((char*)cmd, CLS1_CMD_HELP)==0 || UTIL1_strcmp((char*)cmd, "app help")==0) {
    *handled = TRUE;
    return PrintHelp(io);
  } else if ((UTIL1_strcmp((char*)cmd, CLS1_CMD_STATUS)==0) || (UTIL1_strcmp((char*)cmd, "app status")==0)) {
    *handled = TRUE;
    return PrintStatus(io);
  }
  return ERR_OK;
}


static portTASK_FUNCTION(AppTask, pvParameters) {
  (void)pvParameters; /* not used */
  for(;;) {
    LED1_Neg();
    FRTOS1_vTaskDelay(500/portTICK_RATE_MS);
  } /* for */
}

void APP_Run(void) {
  if (FRTOS1_xTaskCreate(
        AppTask,  /* pointer to the task */
        "App", /* task name for kernel awareness debugging */
        configMINIMAL_STACK_SIZE, /* task stack size */
        (void*)NULL, /* optional task startup argument */
        tskIDLE_PRIORITY,  /* initial priority */
        (xTaskHandle*)NULL /* optional task handle to create */
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

