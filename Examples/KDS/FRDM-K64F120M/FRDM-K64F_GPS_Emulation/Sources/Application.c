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

void APP_Run(void) {
  int txCtnr=0;
  int txCntr = 0;
  int gpsMsgIndex = 0;
  size_t len;

  CLS1_SendStr("\n-------------------------\nGPS Emulation\n-------------------------\n", CLS1_GetStdio()->stdOut);
  for(;;) {
    len = UTIL1_strlen((const char*)gpsRxBuf);
    if (CLS1_ReadLine(gpsRxBuf, gpsRxBuf+len, sizeof(gpsRxBuf), &GPS_stdio)) {
      LED2_On();
      /* send what we have received from the GPS to the console */
      XF1_xsprintf(uartBuf, "GPS Rx #%i ", txCntr++);
      UTIL1_strcat(uartBuf, sizeof(uartBuf), gpsRxBuf);
      CLS1_SendStr(uartBuf, CLS1_GetStdio()->stdOut);
      LED2_Off();
    }
#if 1
    /* new message */
    LED1_On();
    XF1_xsprintf(gpsTxBuf, "GPS Tx #%i ", txCtnr++);
    UTIL1_strcat(gpsTxBuf, sizeof(gpsTxBuf), gps_msg[gpsMsgIndex]);
    SendToBothUART(gpsTxBuf);
    gpsMsgIndex++;
    if (gpsMsgIndex==sizeof(gps_msg)/sizeof(gps_msg[0])) { /* go through ring buffer of messages */
      gpsMsgIndex = 0; /* restart index */
    }
    SendToBothUART("\r\n");
    LED1_Off();
#endif
    WAIT1_Waitms(1000);
  }
}
