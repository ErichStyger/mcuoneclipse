/*
 * Application.c
 *
 *  Created on: 11.10.2017
 *      Author: Erich Styger
 */


#include "Application.h"
#include "WAIT1.h"
#include "CLS1.h"
#include "LED1.h"
#include "LED2.h"
#include "LED3.h"
#include "GPS.h"
#include "CLS1.h"
#include "XF1.h"

#define SUPPORT_SWITCH_BAUD       (1)
#define SUPPORT_TX_GPS_MESSAGES   (1)

static bool GPSUART_KeyPressed(void) {
  return GPS_GetCharsInRxBuf()!=0;
}

static void GPSUART_SendChar(uint8_t ch) {
  uint8_t res;
  int timeoutMs = 5;

  do {
    res = GPS_SendChar((uint8_t)ch);  /* Send char */
    if (res==ERR_TXFULL) {
      WAIT1_WaitOSms(1);
    }
    if(timeoutMs<=0) {
      break; /* timeout */
    }
    timeoutMs -= 1;
  } while(res==ERR_TXFULL);
}

static void GPSUART_ReceiveChar(uint8_t *p) {
  if (GPS_RecvChar(p)!=ERR_OK) {
    *p = '\0';
  }
}

static CLS1_ConstStdIOType GPS_stdio = {
  .stdIn = GPSUART_ReceiveChar,
  .stdOut = GPSUART_SendChar,
  .stdErr = GPSUART_SendChar,
  .keyPressed = GPSUART_KeyPressed,
};

static const char *gps_msg[] =
{
    "$GNRMC,164738.00,A,4459.99971,N,07300.00041,W,0.026,,220917,,,A*7A",
    "$GNGSA,A,3,06,02,19,05,17,12,09,23,29,25,,,1.83,1.00,1.53*18",
    "$GNGSA,A,3,,,,,,,,,,,,,1.83,1.00,1.53*10",
    "$GPGSV,3,1,11,02,78,002,46,05,61,198,46,06,67,051,46,09,20,052,40*7F",
    "$GPGSV,3,2,11,12,41,275,44,14,03,024,,17,31,131,42,19,38,128,43*70",
    "$GPGSV,3,3,11,23,17,047,39,25,19,318,39,29,29,309,41*47",
    "$GLGSV,1,1,00*65",
    "$GNGLL,4459.99971,N,07300.00041,W,164738.00,A,A*68",
    "$PUBX,04,164738.00,220917,492457.99,1967,18,-633593,-72.537,21*2E"
};

static uint8_t gpsTxBuf[128];
static uint8_t gpsRxBuf[128];
static uint8_t uartBuf[128];

static void SendToBothUART(const unsigned char *msg) {
  CLS1_SendStr(msg, CLS1_GetStdio()->stdOut); /* send to shell */
  CLS1_SendStr(msg, GPS_stdio.stdOut); /* send to as emulated GPS UART */
}

#if SUPPORT_SWITCH_BAUD
static void SwitchBaud(uint8_t mode) {
  GPS_Disable(); /* disable device */
  GPS_ClearRxBuf();
  GPS_ClearTxBuf();
  (void)GPS_SetBaudRateMode(mode);
  GPS_Enable(); /* re-enable device */
}
#endif

void APP_Run(void) {
  int txCtnr=0;
  int txCntr = 0;
  int gpsMsgIndex = 0;
  size_t len;
  uint32_t countMs = 0;

  gpsRxBuf[0] = '\0'; /* initialize array */
  CLS1_SendStr("\n-------------------------\nGPS Emulation on FRDM-K64F\n-------------------------\n", CLS1_GetStdio()->stdOut);
  CLS1_SendStr("default\n", GPS_stdio.stdOut); /* send to as emulated GPS UART */
  for(;;) {
    /* check if we have received a new message line, terminated by \n from the microcontroller */
    len = UTIL1_strlen((const char*)gpsRxBuf);
    if (CLS1_ReadLine(gpsRxBuf, gpsRxBuf+len, sizeof(gpsRxBuf), &GPS_stdio)) {
      if (gpsRxBuf[0]=='\n' && gpsRxBuf[1]=='\0') {
        gpsRxBuf[0] = '\0'; /* empty buffer */
      } else if (gpsRxBuf[0]!='\0') {
        LED2_On();
        /* send what we have received from the GPS to the console */
        UTIL1_strcpy(uartBuf, sizeof(uartBuf), "GPS Rx #");
        UTIL1_strcatNum32u(uartBuf, sizeof(uartBuf), txCntr++);
        UTIL1_strcat(uartBuf, sizeof(uartBuf), ": ");
        UTIL1_strcat(uartBuf, sizeof(uartBuf), gpsRxBuf);
        CLS1_SendStr(uartBuf, CLS1_GetStdio()->stdOut);
        LED2_Off();
#if SUPPORT_SWITCH_BAUD
        if (UTIL1_strcmp(gpsRxBuf, "baud 9600\n")==0) {
          CLS1_SendStr("*** Switching to 9600!\n", CLS1_GetStdio()->stdOut);
          WAIT1_Waitms(50); /* give some time to send the above string */
          SwitchBaud(GPS_BM_9600BAUD);
        } else if (UTIL1_strcmp(gpsRxBuf, "baud 38400\n")==0) {
          CLS1_SendStr("*** Switching to 38400!\n", CLS1_GetStdio()->stdOut);
          WAIT1_Waitms(50); /* give some time to send the above string */
          SwitchBaud(GPS_BM_38400BAUD);
        } else if (UTIL1_strcmp(gpsRxBuf, "baud 115200\n")==0) {
          CLS1_SendStr("*** Switching to 115200!\n", CLS1_GetStdio()->stdOut);
          WAIT1_Waitms(50); /* give some time to send the above string */
          SwitchBaud(GPS_BM_115200BAUD);
        }
#endif
        gpsRxBuf[0] = '\0'; /* empty buffer */
      }
    }
#if SUPPORT_TX_GPS_MESSAGES
    if ((countMs%1000)==0) {
      /* send new message as GPS device */
      LED1_On();
      XF1_xsprintf(gpsTxBuf, "GPS Tx #%i ", txCtnr++);
      UTIL1_strcat(gpsTxBuf, sizeof(gpsTxBuf), gps_msg[gpsMsgIndex]);
      SendToBothUART(gpsTxBuf);
      gpsMsgIndex++;
      if (gpsMsgIndex==sizeof(gps_msg)/sizeof(gps_msg[0])) { /* iterate ring buffer of messages */
        gpsMsgIndex = 0; /* restart index */
      }
      SendToBothUART("\r\n");
      LED1_Off();
    }
#endif
    WAIT1_Waitms(50);
    countMs += 50;
  }
}
