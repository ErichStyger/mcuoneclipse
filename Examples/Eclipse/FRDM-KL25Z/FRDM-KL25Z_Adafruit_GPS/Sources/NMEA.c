/**
 * \file
 * \brief NMEA Parser and GPS handling
 * \author (c) 2014 Erich Styger, http://mcuoneclipse.com/
 * \note MIT License (http://opensource.org/licenses/mit-license.html)
 *
 * This module implements the NMEA parser plus a task handling the serial connection to the GPS module.
 */

#include "Platform.h"
#if PL_HAS_GPS
#include "NMEA.h"
#include "FRTOS1.h"
#include "GPS.h"
#include "CLS1.h"
#include "CS1.h"
#include "LEDR.h"
#include "LEDG.h"

#define NMEA_GMT_OFFSET  2  /* (GMT+1) plus summer time */

static bool NMEA_printMsg = FALSE; /* set to TRUE if we print NMEA messages to the console */
static bool NMEA_parseMsg = TRUE; /* set to TRUE if we parse NMEA messages */
static uint8_t NMEA_msg[83]; /* contains current message. Maximum 80 bytes for message, plus \r\n, plus zero byte */
static uint8_t NMEA_msgIdx; /* index into NMEA_msg[] */
static uint32_t NMEA_nofPPS; /* number of PPS ticks received */

typedef struct {
  uint8_t hour, minute, second;
  uint16_t milliSecond;
} NMEA_TimeT;

typedef struct {
  uint8_t day, month, year;
} NMEA_DateT;

typedef struct { /* 4703.2781,N,00835.1051,E */
  int16_t degree;  /* 47° */
  uint8_t minutesIntegral; /* 03 */
  uint16_t minutesfractional; /* e.g. 2781' */
} NMEA_CoordT;

typedef struct {
  uint16_t integral, fractional;
} NMEA_SpeedT;

typedef struct {
  uint16_t integral, fractional;
} NMEA_AngleT;

static struct {
  bool isActive;
  bool hasTime;
  NMEA_TimeT time;
  bool hasDate;
  NMEA_DateT date;
  NMEA_CoordT latitude, longitude;
  NMEA_SpeedT speed;
  NMEA_AngleT angle;
} NMEA_Data;

static void Err(uint8_t *msg) {
  CLS1_ConstStdIOType *io = CLS1_GetStdio();

  CLS1_SendStr((uint8_t*)"ERROR: ", io->stdErr);
  CLS1_SendStr(msg, io->stdErr);
  CLS1_SendStr((uint8_t*)"\r\n", io->stdErr);
}

void NMEA_OnPPS(void) {
  NMEA_nofPPS++;
}

static uint8_t VerifyCheckSum(uint8_t *msg) {
  size_t len;
  uint8_t checksum, sum;
  unsigned int i;
  const unsigned char *p;
  uint8_t buf[48];

  len = UTIL1_strlen((char*)msg);
  if (len>5) {
    if (msg[len]=='\0'&& msg[len-1]=='\n' && msg[len-2]=='\r') { /* \r\n and zero byte */
      if (msg[len-5]=='*') { /* two byte checksum, starts with '*' */
        p = &msg[len-4];
        if (UTIL1_ScanHex8uNumberNoPrefix(&p, &checksum)==ERR_OK) {
          sum = 0;
          for(i=1;i<len-5;i++) { /* checksum between $...*, but not with '$' and '*' */
            sum ^= msg[i];
          } /* for */
          if (checksum==sum) { /* checksum ok */
            return ERR_OK;
          }
        }
      }
    }
  }
  UTIL1_strcpy(buf, sizeof(buf), (uint8_t*)"Checksum failure, expected 0x");
  UTIL1_strcatNum8Hex(buf, sizeof(buf), checksum);
  UTIL1_strcat(buf, sizeof(buf), (uint8_t*)", have 0x");
  UTIL1_strcatNum8Hex(buf, sizeof(buf), sum);
  UTIL1_strcat(buf, sizeof(buf), (uint8_t*)"!!!");
  Err(buf);
  return ERR_FAILED;
}

uint8_t NMEA_GetTime(uint8_t *hour, uint8_t *minute, uint8_t *second, uint16_t* mSecond) {
  int8_t h;
  NMEA_TimeT time;

  if (NMEA_Data.hasTime) {
    FRTOS1_taskENTER_CRITICAL();
    time = NMEA_Data.time; /* struct copy */
    FRTOS1_taskEXIT_CRITICAL();
    /* adjust with GMT offset */
    h = time.hour+NMEA_GMT_OFFSET;
    if (h>=24) { /* overflow */
      h -= 24;
    } else if (h<0) {
      h += 24;
    }
    time.hour = (uint8_t)h;
    /* return values */
    *hour = time.hour;
    *minute = time.minute;
    *second = time.second;
    *mSecond = time.milliSecond;
    return ERR_OK;
  } else {
    return ERR_FAILED;
  }
}

uint8_t NMEA_GetDate(uint8_t *day, uint8_t *month, uint16_t *year) {
  NMEA_DateT date;

  if (NMEA_Data.hasDate) {
    FRTOS1_taskENTER_CRITICAL();
    date = NMEA_Data.date; /* struct copy */
    FRTOS1_taskEXIT_CRITICAL();
    /* return values */
    *day = date.day;
    *month = date.month;
    *year = date.year+2000;
    return ERR_OK;
  } else {
    return ERR_FAILED;
  }
}

uint8_t NMEA_GetLatitude(NMEA_CoordT *coord) {
  FRTOS1_taskENTER_CRITICAL();
  *coord = NMEA_Data.latitude; /* struct copy */
  FRTOS1_taskEXIT_CRITICAL();
  return ERR_OK;
}

uint8_t NMEA_GetLongitude(NMEA_CoordT *coord) {
  FRTOS1_taskENTER_CRITICAL();
  *coord = NMEA_Data.longitude; /* struct copy */
  FRTOS1_taskEXIT_CRITICAL();
  return ERR_OK;
}

uint8_t NMEA_GetSpeed(NMEA_SpeedT *speed) {
  FRTOS1_taskENTER_CRITICAL();
  *speed = NMEA_Data.speed; /* struct copy */
  FRTOS1_taskEXIT_CRITICAL();
  return ERR_OK;
}

uint8_t NMEA_GetAngle(NMEA_AngleT *angle) {
  FRTOS1_taskENTER_CRITICAL();
  *angle = NMEA_Data.angle; /* struct copy */
  FRTOS1_taskEXIT_CRITICAL();
  return ERR_OK;
}

static uint8_t ParseTime(const uint8_t **p, NMEA_TimeT *time) {
  /* ",113046.096" */
  uint32_t val;
  const uint8_t *q;

  time->hour = 0;
  time->minute = 0;
  time->second = 0;
  time->milliSecond = 0;
  q = *p;
  if (*q!=',') {
    return ERR_FAILED;
  }
  q++;
  if (UTIL1_ScanDecimal32uNumber(&q, &val)!=ERR_OK) {
    return ERR_FAILED;
  }
  time->hour = val/10000;
  val %= 10000;
  time->minute = val/100;
  val %= 100;
  time->second = val;
  if (*q!='.') {
    return ERR_FAILED;
  }
  q++;
  if (UTIL1_ScanDecimal32uNumber(&q, &val)!=ERR_OK) {
    return ERR_FAILED;
  }
  time->milliSecond = val;
  *p = q;
  return ERR_OK;
}

static uint8_t ParseDate(const uint8_t **p, NMEA_DateT *date) {
  /* ",230514" */
  uint32_t val;
  const uint8_t *q;

  date->day = 0;
  date->month = 0;
  date->year = 0;
  q = *p;
  if (*q!=',') {
    return ERR_FAILED;
  }
  q++;
  if (UTIL1_ScanDecimal32uNumber(&q, &val)!=ERR_OK) {
    return ERR_FAILED;
  }
  date->day = val/10000;
  val %= 10000;
  date->month = val/100;
  val %= 100;
  date->year = val;
  *p = q;
  return ERR_OK;
}

static uint8_t ParseCoordinate(const uint8_t **p, NMEA_CoordT *coord, bool isLongitude) {
  /* ",4703.2781,N" */
  const uint8_t *q, *t;
  uint8_t degreeBuf[4]; /* latitude has two chars, longitude is three chars */

  coord->degree = 0;
  coord->minutesIntegral = 0;
  coord->minutesfractional = 0;
  q = *p;
  if (*q!=',') {
    return ERR_FAILED;
  }
  q++; /* skip ',' */
  if (*q==',') {
    coord->degree = 0;
    coord->minutesIntegral = 0;
    coord->minutesfractional = 0;
  } else {
    /* the degrees are in the first two digits! */
    degreeBuf[0] = q[0];
    degreeBuf[1] = q[1];
    if (isLongitude) {
      degreeBuf[2] = q[2];
      degreeBuf[3] = '\0';
    } else {
      degreeBuf[2] = '\0';
    }
    t = &degreeBuf[0];
    if (UTIL1_ScanDecimal16sNumber(&t, &coord->degree)!=ERR_OK) {
      return ERR_FAILED;
    }
    if (isLongitude) {
      q += 3; /* skip the two degree digits */
    } else {
      q += 2; /* skip the two degree digits */
    }
    /* parse the minutes */
    if (UTIL1_ScanDecimal8uNumber(&q, &coord->minutesIntegral)!=ERR_OK) {
      return ERR_FAILED;
    }
    if (*q!='.') {
      return ERR_FAILED;
    }
    q++;
    if (UTIL1_ScanDecimal16uNumber(&q, &coord->minutesfractional)!=ERR_OK) {
      return ERR_FAILED;
    }
  }
  if (*q!=',') {
    return ERR_FAILED;
  }
  q++; /* skip ',' */
  if (*q=='N' || *q=='E') {
    /* positive */
    q++; /* skip 'N' or 'E' */
  } else if ( *q=='W' || *q=='E') {
    /* negative */
    coord->degree = -coord->degree;
    q++; /* skip 'W' or 'E' */
  } else if (*q==',') { /* no data */
    /* keep default */
  } else {
    return ERR_FAILED;
  }
  *p = q;
  return ERR_OK;
}

static uint8_t ParseSpeed(const uint8_t **p, NMEA_SpeedT *speed) {
  /* ",4703.2781,N" */
  const uint8_t *q;

  speed->integral = 0;
  speed->fractional = 0;
  q = *p;
  if (*q!=',') {
    return ERR_FAILED;
  }
  q++; /* skip ',' */
  if (*q==',') {
    speed->integral = 0;
    speed->fractional = 0;
  } else {
    if (UTIL1_ScanDecimal16uNumber(&q, &speed->integral)!=ERR_OK) {
      return ERR_FAILED;
    }
    if (*q!='.') {
      return ERR_FAILED;
    }
    q++;
    if (UTIL1_ScanDecimal16uNumber(&q, &speed->fractional)!=ERR_OK) {
      return ERR_FAILED;
    }
  }
  *p = q;
  return ERR_OK;
}

static uint8_t ParseAngle(const uint8_t **p, NMEA_AngleT *angle) {
  /* ",4703.2781,N" */
  const uint8_t *q;

  angle->integral = 0;
  angle->fractional = 0;
  q = *p;
  if (*q!=',') {
    return ERR_FAILED;
  }
  q++; /* skip ',' */
  if (*q==',') {
    angle->integral = 0;
    angle->fractional = 0;
  } else {
    if (UTIL1_ScanDecimal16uNumber(&q, &angle->integral)!=ERR_OK) {
      return ERR_FAILED;
    }
    if (*q!='.') {
      return ERR_FAILED;
    }
    q++;
    if (UTIL1_ScanDecimal16uNumber(&q, &angle->fractional)!=ERR_OK) {
      return ERR_FAILED;
    }
  }
  *p = q;
  return ERR_OK;
}

static uint8_t ParseGPRMC(const uint8_t **p) {
  /* Minimum recommended data */
  /* $GPRMC,113046.096,V,,,,,0.00,0.00,230514,,,N*42 */
  uint8_t res;
  NMEA_TimeT time;
  NMEA_DateT date;
  NMEA_CoordT coord;
  NMEA_SpeedT speed;
  NMEA_AngleT angle;
  const uint8_t *q;

  q = *p;
  /* ",113046.096" */
  res = ParseTime(&q, &time);
  if (res!=ERR_OK) {
    return res;
  }
  FRTOS1_taskENTER_CRITICAL();
  NMEA_Data.time = time; /* struct copy */
  NMEA_Data.hasTime = TRUE;
  FRTOS1_taskEXIT_CRITICAL();

  /* ",V" or ",A" */
  if (*q!=',') {
    return ERR_FAILED;
  }
  q++; /* skip ',' */
  if (*q=='V') {
    /* V: void data */
    NMEA_Data.isActive = FALSE;
  } else if (*q=='A') {
    /* A: active data */
    NMEA_Data.isActive = TRUE;
  } else {
    return ERR_FAILED;
  }
  q++; /* skip V or A */
  if (ParseCoordinate(&q, &coord, FALSE)!=ERR_OK) {
    return ERR_FAILED;
  }
  FRTOS1_taskENTER_CRITICAL();
  NMEA_Data.latitude = coord; /* struct copy */
  FRTOS1_taskEXIT_CRITICAL();

  if (ParseCoordinate(&q, &coord, TRUE)!=ERR_OK) {
    return ERR_FAILED;
  }
  FRTOS1_taskENTER_CRITICAL();
  NMEA_Data.longitude = coord; /* struct copy */
  FRTOS1_taskEXIT_CRITICAL();

  if (ParseSpeed(&q, &speed)!=ERR_OK) {
    return ERR_FAILED;
  }
  FRTOS1_taskENTER_CRITICAL();
  NMEA_Data.speed = speed; /* struct copy */
  FRTOS1_taskEXIT_CRITICAL();

  if (ParseAngle(&q, &angle)!=ERR_OK) {
    return ERR_FAILED;
  }
  FRTOS1_taskENTER_CRITICAL();
  NMEA_Data.angle = angle; /* struct copy */
  FRTOS1_taskEXIT_CRITICAL();

  res = ParseDate(&q, &date);
  if (res!=ERR_OK) {
    return res;
  }
  FRTOS1_taskENTER_CRITICAL();
  NMEA_Data.date = date; /* struct copy */
  NMEA_Data.hasDate = TRUE;
  FRTOS1_taskEXIT_CRITICAL();

  *p = q;
  return ERR_OK;
}

static uint8_t ParseMsg(void) {
  const uint8_t *p;

  if (UTIL1_strncmp((char*)NMEA_msg, (char*)"$GPRMC", sizeof("$GPRMC")-1)==0) { /* recommended minimum data message */
    p = NMEA_msg+sizeof("$GPRMC")-1; /* skip start */
    return ParseGPRMC(&p); /* parse message */
  }
  return ERR_OK;
}

static void ReadChar(uint8_t ch) {
  static uint8_t prevCh = '\0'; /* needed to detect \r\n as end of a message */

  if (NMEA_parseMsg) { /* enabled to parse messages? */
    if (ch=='$') { /* check start of a message */
      NMEA_msgIdx = 0; /* reset index */
      prevCh = '\0'; /* reset previous char */
    }
    if (NMEA_msgIdx<sizeof(NMEA_msg)-1) { /* check for buffer overflow */
      NMEA_msg[NMEA_msgIdx++] = ch; /* store character */
    } else { /* message too long! */
      Err((uint8_t*)"Buffer overflow!");
      NMEA_msgIdx = 0;
      prevCh = '\0';
    }
    if (NMEA_msgIdx>sizeof("$GPxxx,") && (ch=='\n' && prevCh=='\r')) { /* valid end of message */
      NMEA_msg[NMEA_msgIdx] = '\0'; /* terminate */
      /* reached end of a message */
      if (UTIL1_strncmp((char*)NMEA_msg, (char*)"$GP", sizeof("$GP")-1)==0) { /* valid start of a message? */
        if (VerifyCheckSum(NMEA_msg)==ERR_OK) { /* check first the checksum */
          ParseMsg(); /* checksum ok, parse message and store data */
        } else {
          Err((uint8_t*)"Checksum failure!");
        }
      } else {
        Err((uint8_t*)"Message does not start with \"$GP\"?");
      }
    }
  }
  prevCh = ch;
}

static portTASK_FUNCTION(NmeaTask, pvParameters) {
  GPS_TComData ch;

  (void)pvParameters; /* parameter not used */
  GPS_ClearRxBuf(); /* clear GPS RX buffer, as it already could contain some data */
  for(;;) {
    /* indicate we are receiving data from GPS with green and red LED */
    if (GPS_GetCharsInRxBuf()==0) {
      LEDR_Neg(); LEDG_Off(); /* blink red led if no GPS data */
    } else {
      LEDR_Off(); LEDG_Neg(); /* blink green led if we have GPS data */
    }
    while(GPS_GetCharsInRxBuf()!=0) { /* do we have data? */
      if (GPS_RecvChar(&ch)==ERR_OK) { /* yes, and no problem to get it */
        ReadChar(ch); /* read character and store in buffer */
        if (NMEA_printMsg) { /* print messages to console? */
          CLS1_SendChar(ch); /* yes, print it */
        } /* if */
      } /* if */
    } /* while */
    FRTOS1_vTaskDelay(200/portTICK_RATE_MS); /* give back some time */
  }
}

static uint8_t PrintHelp(const CLS1_StdIOType *io) {
  CLS1_SendHelpStr((unsigned char*)"nmea", (unsigned char*)"Group of nmea commands\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  help|status", (unsigned char*)"Print help or status information\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  print msg (on|off)", (unsigned char*)"Enable and disable printing messages on console\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  parse msg (on|off)", (unsigned char*)"Enable and disable parsing of messages\r\n", io->stdOut);
  return ERR_OK;
}

static uint8_t PrintStatus(const CLS1_StdIOType *io) {
  uint8_t buf[40], res;
  uint8_t day, month;
  uint16_t year;
  NMEA_CoordT coord;
  NMEA_SpeedT speed;
  NMEA_AngleT angle;
  uint8_t hour, minute, second;
  uint16_t milliSecond;

  CLS1_SendStatusStr((unsigned char*)"nmea", (unsigned char*)"\r\n", io->stdOut);
  CLS1_SendStatusStr((unsigned char*)"  print msg", NMEA_printMsg?(const unsigned char*)"on\r\n":(const unsigned char*)"off\r\n", io->stdOut);
  CLS1_SendStatusStr((unsigned char*)"  parse msg", NMEA_parseMsg?(const unsigned char*)"on\r\n":(const unsigned char*)"off\r\n", io->stdOut);

  CLS1_SendStatusStr((unsigned char*)"  active", NMEA_Data.isActive?(const unsigned char*)"yes\r\n":(const unsigned char*)"no\r\n", io->stdOut);

  buf[0] = 0;
  UTIL1_strcatNum8s(buf, sizeof(buf), NMEA_GMT_OFFSET);
  UTIL1_strcat(buf, sizeof(buf), (uint8_t*)" hours\r\n");
  CLS1_SendStatusStr((unsigned char*)"  GMT offset", buf, io->stdOut);

  buf[0] = 0;
  res = NMEA_GetTime(&hour, &minute, &second, &milliSecond);
  if (res==ERR_OK) {
    UTIL1_strcatNum32sFormatted(buf, sizeof(buf), hour, '0', 2);
    UTIL1_chcat(buf, sizeof(buf), ':');
    UTIL1_strcatNum32sFormatted(buf, sizeof(buf), minute, '0', 2);
    UTIL1_chcat(buf, sizeof(buf), ':');
    UTIL1_strcatNum32sFormatted(buf, sizeof(buf), second, '0', 2);
    UTIL1_chcat(buf, sizeof(buf), ',');
    UTIL1_strcatNum32sFormatted(buf, sizeof(buf), milliSecond, '0', 3);
    UTIL1_strcat(buf, sizeof(buf), (uint8_t*)"\r\n");
  } else {
    UTIL1_strcpy(buf, sizeof(buf), (uint8_t*)"FAILED\r\n");
  }
  CLS1_SendStatusStr((unsigned char*)"  time", buf, io->stdOut);

  buf[0] = 0;
  res = NMEA_GetDate(&day, &month, &year);
  if (res==ERR_OK) {
    UTIL1_strcatNum32sFormatted(buf, sizeof(buf), day, '0', 2);
    UTIL1_chcat(buf, sizeof(buf), '.');
    UTIL1_strcatNum32sFormatted(buf, sizeof(buf), month, '0', 2);
    UTIL1_chcat(buf, sizeof(buf), '.');
    UTIL1_strcatNum32sFormatted(buf, sizeof(buf), year, '0', 4);
    UTIL1_strcat(buf, sizeof(buf), (uint8_t*)"\r\n");
  } else {
    UTIL1_strcpy(buf, sizeof(buf), (uint8_t*)"FAILED\r\n");
  }
  CLS1_SendStatusStr((unsigned char*)"  date", buf, io->stdOut);

  buf[0] = 0;
  res = NMEA_GetLatitude(&coord);
  if (res==ERR_OK) {
    if (coord.degree>=0) {
      UTIL1_chcat(buf, sizeof(buf), '+');
    }
    UTIL1_strcatNum32sFormatted(buf, sizeof(buf), coord.degree, '0', 2);
    UTIL1_strcat(buf, sizeof(buf), (uint8_t*)"° ");
    UTIL1_strcatNum32sFormatted(buf, sizeof(buf), coord.minutesIntegral, '0', 2);
    UTIL1_chcat(buf, sizeof(buf), '.');
    UTIL1_strcatNum16u(buf, sizeof(buf), coord.minutesfractional);
    UTIL1_strcat(buf, sizeof(buf), (uint8_t*)"', ");
  } else {
    UTIL1_strcpy(buf, sizeof(buf), (uint8_t*)"FAILED\r\n");
  }
  res = NMEA_GetLongitude(&coord);
  if (res==ERR_OK) {
    if (coord.degree>=0) {
      UTIL1_chcat(buf, sizeof(buf), '+');
    }
    UTIL1_strcatNum32sFormatted(buf, sizeof(buf), coord.degree, '0', 3);
    UTIL1_strcat(buf, sizeof(buf), (uint8_t*)"° ");
    UTIL1_strcatNum32sFormatted(buf, sizeof(buf), coord.minutesIntegral, '0', 2);
    UTIL1_chcat(buf, sizeof(buf), '.');
    UTIL1_strcatNum16u(buf, sizeof(buf), coord.minutesfractional);
    UTIL1_strcat(buf, sizeof(buf), (uint8_t*)"'\r\n");
  } else {
    UTIL1_strcpy(buf, sizeof(buf), (uint8_t*)"FAILED\r\n");
  }
  CLS1_SendStatusStr((unsigned char*)"  pos", buf, io->stdOut);

  buf[0] = 0;
  res = NMEA_GetSpeed(&speed);
  if (res==ERR_OK) {
    UTIL1_strcatNum16s(buf, sizeof(buf), speed.integral);
    UTIL1_chcat(buf, sizeof(buf), '.');
    UTIL1_strcatNum16s(buf, sizeof(buf), speed.fractional);
    UTIL1_strcat(buf, sizeof(buf), (uint8_t*)"\r\n");
  } else {
    UTIL1_strcpy(buf, sizeof(buf), (uint8_t*)"FAILED\r\n");
  }
  CLS1_SendStatusStr((unsigned char*)"  speed", buf, io->stdOut);

  buf[0] = 0;
  res = NMEA_GetAngle(&angle);
  if (res==ERR_OK) {
    UTIL1_strcatNum16s(buf, sizeof(buf), angle.integral);
    UTIL1_chcat(buf, sizeof(buf), '.');
    UTIL1_strcatNum16s(buf, sizeof(buf), angle.fractional);
    UTIL1_strcat(buf, sizeof(buf), (uint8_t*)"\r\n");
  } else {
    UTIL1_strcpy(buf, sizeof(buf), (uint8_t*)"FAILED\r\n");
  }
  CLS1_SendStatusStr((unsigned char*)"  angle", buf, io->stdOut);

  buf[0] = 0;
  UTIL1_strcatNum32u(buf, sizeof(buf), NMEA_nofPPS);
  UTIL1_strcat(buf, sizeof(buf), (uint8_t*)"\r\n");
  CLS1_SendStatusStr((unsigned char*)"  PPS count", buf, io->stdOut);

  return ERR_OK;
}

uint8_t NMEA_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io) {
#if PL_HAS_GPS
  if (UTIL1_strcmp((char*)cmd, CLS1_CMD_HELP)==0 || UTIL1_strcmp((char*)cmd, "nmea help")==0) {
    *handled = TRUE;
    return PrintHelp(io);
  } else if ((UTIL1_strcmp((char*)cmd, CLS1_CMD_STATUS)==0) || (UTIL1_strcmp((char*)cmd, "nmea status")==0)) {
    *handled = TRUE;
    return PrintStatus(io);
  } else if (UTIL1_strcmp((char*)cmd, "nmea print msg on")==0) {
    *handled = TRUE;
    NMEA_printMsg = TRUE;
  } else if (UTIL1_strcmp((char*)cmd, "nmea print msg off")==0) {
    *handled = TRUE;
    NMEA_printMsg = FALSE;
  } else if (UTIL1_strcmp((char*)cmd, "nmea parse msg on")==0) {
    *handled = TRUE;
    NMEA_parseMsg = TRUE;
  } else if (UTIL1_strcmp((char*)cmd, "nmea parse msg off")==0) {
    *handled = TRUE;
    NMEA_parseMsg = FALSE;
  }
#endif
  return ERR_OK;
}

void NMEA_Init(void) {
  NMEA_Data.hasTime = FALSE;
  NMEA_Data.hasDate = FALSE;
  NMEA_nofPPS = 0;
  if (FRTOS1_xTaskCreate(
        NmeaTask,  /* pointer to the task */
        "NMEA", /* task name for kernel awareness debugging */
        configMINIMAL_STACK_SIZE, /* task stack size */
        (void*)NULL, /* optional task startup argument */
        tskIDLE_PRIORITY+1,  /* initial priority */
        (xTaskHandle*)NULL /* optional task handle to create */
      ) != pdPASS) {
    /*lint -e527 */
    for(;;){}; /* error! probably out of memory */
    /*lint +e527 */
  }
}
#endif /* PL_HAS_GPS */

