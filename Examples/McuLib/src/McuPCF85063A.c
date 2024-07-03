/*
 * Copyright (c) 2023-2024, Erich Styger
 *
 * * Driver for the NXP PCF85063A I2C RTC.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "McuPCF85063A.h"
#include "McuShell.h"
#include "McuUtility.h"
#include "McuGenericI2C.h"
#include "McuXFormat.h"

#define McuPCF85063A_I2C_DEVICE_ADDRESS   (0x51) /* 7bit I2C address, not-shifted value */

/* register memory map */
#define McuPCF85063A_ADDRESS_CONTROL_1              0x00
#define McuPCF85063A_ADDRESS_CONTROL_2              0x01
#define McuPCF85063A_ADDRESS_OFFSET                 0x02
#define McuPCF85063A_ADDRESS_RAM_BYTE               0x03
#define McuPCF85063A_ADDRESS_TIME_DATE_START_ADDR   0x04  /* start address of time and date registers */
#define McuPCF85063A_ADDRESS_TIME_START_ADDR        0x04  /* start address of time registers */
#define McuPCF85063A_ADDRESS_DATE_START_ADDR        0x07  /* start address of time registers */
#define McuPCF85063A_ADDRESS_ALARM_START_ADDR       0x0B  /* start address of alarm registers */
#define McuPCF85063A_ADDRESS_ALARM_SECOND           0x0B  /* Second_alarm */
#define McuPCF85063A_ADDRESS_ALARM_MINUTE           0x0C  /* Minute_alarm */
#define McuPCF85063A_ADDRESS_ALARM_HOUR             0x0D  /* Hour_alarm */
#define McuPCF85063A_ADDRESS_ALARM_DAY              0x0E  /* Hour_alarm */
#define McuPCF85063A_ADDRESS_ALARM_WEEKDAY          0x0F  /* Weekday_alarm */

#define McuPCF85063A_TTIME_AMPM_AM   0  /* AM */
#define McuPCF85063A_TTIME_AMPM_PM   1  /* PM */
/* hour mode is set in 12_24 bit in Control_1 */
#define McuPCF85063A_TTIME_MODE_12H  0  /* 12 hour clock mode */
#define McuPCF85063A_TTIME_MODE_24H  1  /* 14 hour clock mode */

#define McuPCF85063A_MEMORY_TIME_SIZE       (3) /* 0x4-0x6, number of bytes for time information on device */
#define McuPCF85063A_MEMORY_DATE_SIZE       (4) /* 0x7-0xA, number of bytes for date information on device */
#define McuPCF85063A_MEMORY_TIME_DATE_SIZE  (7) /* 0x4-0xA, number of bytes for data and time information on device */

typedef struct McuPCF85063A_TTIME {  /* Time in binary format */
  uint8_t hour;                      /* hours */
  uint8_t min;                       /* minutes */
  uint8_t sec;                       /* seconds */
  uint8_t am_pm;                     /* 0: AM, 1: PM */
  uint8_t mode;                      /* hour mode is set in 12_24 bit in Control_1 */
} McuPCF85063A_TTIME;

typedef struct McuPCF85063A_TDATE {  /* Date in binary format */
  uint8_t year;                      /* year */
  uint8_t month;                     /* month */
  uint8_t day;                       /* day */
  uint8_t dayOfWeek;                 /* Day of week, where 0 is the first day. In the range of 0..6 */
} McuPCF85063A_TDATE;

uint8_t McuPCF85063A_ReadBlock(uint8_t addr, uint8_t *buf, size_t bufSize) {
  return McuGenericI2C_ReadAddress(McuPCF85063A_I2C_DEVICE_ADDRESS, &addr, sizeof(addr), buf, bufSize);
}

uint8_t McuPCF85063A_WriteBlock(uint8_t addr, uint8_t *buf, size_t bufSize) {
  return McuGenericI2C_WriteAddress(McuPCF85063A_I2C_DEVICE_ADDRESS, &addr, sizeof(addr), buf, bufSize);
}

uint8_t McuPCF85063A_ReadByte(uint8_t addr, uint8_t *data) {
  return McuGenericI2C_ReadAddress(McuPCF85063A_I2C_DEVICE_ADDRESS, &addr, sizeof(addr), data, sizeof(*data));
}

uint8_t McuPCF85063A_WriteByte(uint8_t addr, uint8_t data) {
  return McuGenericI2C_WriteAddress(McuPCF85063A_I2C_DEVICE_ADDRESS, &addr, sizeof(addr), &data, sizeof(data));
}

uint8_t McuPCF85063A_ReadControl1(uint8_t *data) {
  return McuPCF85063A_ReadByte(McuPCF85063A_ADDRESS_CONTROL_1, data);
}

uint8_t McuPCF85063A_WriteControl1(uint8_t data) {
  return McuPCF85063A_WriteByte(McuPCF85063A_ADDRESS_CONTROL_1, data);
}

uint8_t McuPCF85063A_WriteSoftwareReset(void) {
  return McuPCF85063A_WriteByte(McuPCF85063A_ADDRESS_CONTROL_1, 0x58);
}

uint8_t McuPCF85063A_ReadControl2(uint8_t *data) {
  return McuPCF85063A_ReadByte(McuPCF85063A_ADDRESS_CONTROL_2, data);
}

uint8_t McuPCF85063A_WriteControl2(uint8_t data) {
  return McuPCF85063A_WriteByte(McuPCF85063A_ADDRESS_CONTROL_2, data);
}

uint8_t McuPCF85063A_WriteAlarmInterrupt(bool enable) {
  uint8_t data;

  if (McuPCF85063A_ReadControl2(&data)!=ERR_OK) { /* read current value */
    return ERR_FAILED;
  }
  /* AIE 0: disabled; 1: enabled */
  if (enable) {
    data |= (1<<7); /* set AIE (Alarm Interrupt Enable) bit */
  } else {
    data &= (1<<7); /* clear AIE (Alarm Interrupt Enable) bit */
  }
  return McuPCF85063A_WriteByte(McuPCF85063A_ADDRESS_CONTROL_2, data);
}

uint8_t McuPCF85063A_WriteClockOutputFrequency(McuPCF85063A_COF_Frequency_e frequency) {
  uint8_t data;

  if (McuPCF85063A_ReadControl2(&data)!=ERR_OK) { /* read current value */
    return ERR_FAILED;
  }
  /* Clock Output Frequency:
   * 000: 32768
   * 001: 16387
   * 010: 8196
   * 011: 4096
   * 100: 2048
   * 101: 1024
   * 110: 1
   * 111: CLKOUT=LOW */
  if (frequency>7) {
    return ERR_RANGE;
  }
  data |= (frequency&7); /* set COF bits [2:0] */
  return McuPCF85063A_WriteByte(McuPCF85063A_ADDRESS_CONTROL_2, data);
}


uint8_t McuPCF85063A_WriteResetAlarmInterrupt(void) {
  uint8_t data;

  if (McuPCF85063A_ReadControl2(&data)!=ERR_OK) { /* read current value */
    return ERR_FAILED;
  }
  /* AF: reset alarm flag with writing a 0 to it */
  data &= ~(1<<6); /* clear AF (Alarm Flag) bit */
  return McuPCF85063A_WriteByte(McuPCF85063A_ADDRESS_CONTROL_2, data);
}

uint8_t McuPCF85063A_ReadOffset(uint8_t *data) {
  return McuPCF85063A_ReadByte(McuPCF85063A_ADDRESS_OFFSET, data);
}

uint8_t McuPCF85063A_WriteOffset(uint8_t data) {
  return McuPCF85063A_WriteByte(McuPCF85063A_ADDRESS_OFFSET, data);
}

bool McuPCF85063A_Is24hMode(void) {
  uint8_t res, ctrl;

  res = McuPCF85063A_ReadControl1(&ctrl);
  if (res!=ERR_OK) {
    return true; /* default is 24h mode */
  }
  return (ctrl&(1<<1))==0; /* 0: 12-hour mode, 1: 24-hour mode */
}

uint8_t McuPCF85063A_ReadAlarmSecond(uint8_t *second, bool *enabled) {
  uint8_t data, res;

  res = McuPCF85063A_ReadByte(McuPCF85063A_ADDRESS_ALARM_SECOND, &data);
  if (res!=ERR_OK) {
    return ERR_FAILED;
  }
  *enabled = (data&(1<<7))==0; /* 1: disabled (default), 0: enabled */
  *second = ((data&0x70)>>4)*10 + (data&0x0F); /* BCD encoded */
  return ERR_OK;
}

uint8_t McuPCF85063A_WriteAlarmSecond(uint8_t second, bool enable) {
  uint8_t data;

  if (second>59) {
    return ERR_RANGE;
  }
  data = ((second/10)<<4)|(second%10); /* encoded in BCD */
  if (!enable) {
    data |= (1<<7); /* 1: disabled (default), 0: enabled */
  }
  return McuPCF85063A_WriteByte(McuPCF85063A_ADDRESS_ALARM_SECOND, data);
}

uint8_t McuPCF85063A_ReadAlarmMinute(uint8_t *minute, bool *enabled) {
  uint8_t data, res;

  res = McuPCF85063A_ReadByte(McuPCF85063A_ADDRESS_ALARM_MINUTE, &data);
  if (res!=ERR_OK) {
    return ERR_FAILED;
  }
  *enabled = (data&(1<<7))==0; /* 1: disabled (default), 0: enabled */
  *minute = ((data&0x70)>>4)*10 + (data&0x0F); /* BCD encoded */
  return ERR_OK;
}

uint8_t McuPCF85063A_WriteAlarmMinute(uint8_t minute, bool enable) {
  uint8_t data;

  if (minute>59) {
    return ERR_RANGE;
  }
  data = ((minute/10)<<4)|(minute%10); /* BCD encoded */
  if (!enable) {
    data |= (1<<7); /* 1: disabled (default), 0: enabled */
  }
  return McuPCF85063A_WriteByte(McuPCF85063A_ADDRESS_ALARM_MINUTE, data);
}

uint8_t McuPCF85063A_ReadAlarmHour(uint8_t *hour, bool *enabled, bool *is24h, bool *isAM) {
  uint8_t data, res;

  *is24h = McuPCF85063A_Is24hMode();
  res = McuPCF85063A_ReadByte(McuPCF85063A_ADDRESS_ALARM_HOUR, &data);
  if (res!=ERR_OK) {
    return ERR_FAILED;
  }
  *enabled = (data&(1<<7))==0; /* 1: disabled (default), 0: enabled */
  if (*is24h) {
    *hour = ((data&0x30)>>4)*10 + (data&0x0F); /* BCD encoded */
    *isAM = false;
  } else {
    *hour = ((data&0x70)>>4)*10 + (data&0x0F); /* BCD encoded */
    *isAM = (data&(1<<5))==0;
  }
  return ERR_OK;
}

/* Note: expects 24h hour format! */
uint8_t McuPCF85063A_WriteAlarmHour(uint8_t hour, bool enable, bool is24h, bool isAM) {
  uint8_t data;

  if (is24h && hour>23) {
    return ERR_RANGE;
  } else if (!is24h && hour>12) {
    return ERR_RANGE;
  }
  data = 0;
  if (!enable) {
    data |= (1<<7); /* 1: disabled (default), 0: enabled */
  }
  if (is24h) {
    data |= ((hour/10)<<4)|(hour%10); /* BCD encoded */
  } else {
    if (hour>12) { /* PM */
      hour -= 12;
      data |= (1<<5); /* set PM bit */
    }
    data |= (hour<<4)|(hour%10);
  }
  return McuPCF85063A_WriteByte(McuPCF85063A_ADDRESS_ALARM_HOUR, data);
}

uint8_t McuPCF85063A_ReadAlarmDay(uint8_t *day, bool *enabled) {
  uint8_t res, data;

  res = McuPCF85063A_ReadByte(McuPCF85063A_ADDRESS_ALARM_DAY, &data);
  if (res != ERR_OK) {
    return ERR_FAILED;
  }
  *enabled = (data&(1<<7))==0; /* 1: disabled (default), 0: enabled */
  *day = ((data&0x70)>>4)*10 + (data&0x0F); /* BCD encoded */
  return ERR_OK;
}

uint8_t McuPCF85063A_WriteAlarmDay(uint8_t day, bool enable) {
  uint8_t data;

  data = 0;
  if (!enable) {
    data |= (1<<7); /* 1: disabled (default), 0: enabled */
  }
  data |= ((day/10)<<4)|(day%10); /* BCD encoded */
  return McuPCF85063A_WriteByte(McuPCF85063A_ADDRESS_ALARM_DAY, data);
}

uint8_t McuPCF85063A_ReadAlarmWeekDay(uint8_t *weekDay, bool *enabled) {
  uint8_t res, data;

  res = McuPCF85063A_ReadByte(McuPCF85063A_ADDRESS_ALARM_WEEKDAY, &data);
  if (res != ERR_OK) {
    return ERR_FAILED;
  }
  *enabled = (data&(1<<7))==0; /* 1: disabled (default), 0: enabled */
  *weekDay = ((data&0x70)>>4)*10 + (data&0x0F); /* BCD encoded */
  return ERR_OK;
}

uint8_t McuPCF85063A_WriteAlarmWeekDay(uint8_t weekDay, bool enable) {
  uint8_t data;

  if (weekDay>6) {
    return ERR_RANGE;
  }
  data = 0;
  if (!enable) {
    data |= (1<<7); /* 1: disabled (default), 0: enabled */
  }
  data |= ((weekDay/10)<<4)|(weekDay%10); /* BCD encoded */
  return McuPCF85063A_WriteByte(McuPCF85063A_ADDRESS_ALARM_WEEKDAY, data);
}

uint8_t McuPCF85063A_ReadTimeDate(McuPCF85063A_TTIME *time, McuPCF85063A_TDATE *date) {
  uint8_t buf[McuPCF85063A_MEMORY_TIME_DATE_SIZE];
  bool is24hMode;

  if (McuPCF85063A_ReadBlock(McuPCF85063A_ADDRESS_TIME_DATE_START_ADDR, buf, sizeof(buf))!=ERR_OK) {
    return ERR_FAILED;
  }
  is24hMode = McuPCF85063A_Is24hMode();
  time->sec = (uint8_t)(((buf[0]&0x70)>>4)*10 + (buf[0]&0x0F)); /* seconds in BCD format */
  time->min = (uint8_t)((buf[1]>>4)*10 + (buf[1]&0x0F)); /* minutes in BCD format */
  if (is24hMode) {
    time->hour = (uint8_t)(((buf[2]&0x30)>>4)*10 + (buf[2]&0x0F)); /* hour in BCD format */
    time->mode = McuPCF85063A_TTIME_MODE_24H;
  } else {
    time->hour = (uint8_t)(((buf[2]&0x10)>>4)*10 + (buf[2]&0x0F)); /* hour in BCD format */
    time->am_pm = (uint8_t)((buf[2]&(1<<5))>>5); /* bit 5: AM/PM indicator. 0: AM, 1: PM */
    time->mode = McuPCF85063A_TTIME_MODE_12H;
  }
  date->day = (uint8_t)((buf[3]>>4)*10 + (buf[3]&0x0F)); /* BCD format */
  date->dayOfWeek =(uint8_t)(buf[4]); /* 0: Sunday, 1: Monday, ... 6: Saturday */
  date->month = (uint8_t)((buf[5]>>4)*10 + (buf[5]&0x0F)); /* 1: January */
  date->year = (uint8_t)((buf[6]>>4)*10 + (buf[6]&0x0F));
  return ERR_OK;
}

uint8_t McuPCF85063A_WriteTimeDate(McuPCF85063A_TTIME *time, McuPCF85063A_TDATE *date) {
  uint8_t buf[McuPCF85063A_MEMORY_TIME_DATE_SIZE];
  if (   ((time->mode==McuPCF85063A_TTIME_MODE_12H)&&((time->hour>12)||(time->hour==0)))
      || ((time->mode==McuPCF85063A_TTIME_MODE_24H)&&(time->hour>23))
      || (time->min>59)||(time->sec>59)
      || (date->year>99)||(date->month>12)||(date->month==0)
      || (date->day>31)||(date->day==0)
      || (date->dayOfWeek>6))
  {
    return ERR_RANGE;
  }
  buf[0] = (uint8_t)(((time->sec/10)<<4) | (time->sec%10));
  buf[1] = (uint8_t)(((time->min/10)<<4) | (time->min%10));
  buf[2] = (uint8_t)(((time->hour/10)<<4) | (time->hour%10));
  if (time->mode==McuPCF85063A_TTIME_MODE_12H) {
    buf[2] |= (time->am_pm)?(1<<5):0;
  }
  buf[3] = (uint8_t)(((date->day/10)<<4) | (date->day%10));
  buf[4] = (uint8_t)(date->dayOfWeek);
  buf[5] = (uint8_t)(((date->month/10)<<4) | (date->month%10));
  buf[6] = (uint8_t)(((date->year/10)<<4) | (date->year%10));
  if (McuPCF85063A_WriteBlock(McuPCF85063A_ADDRESS_TIME_DATE_START_ADDR, buf, sizeof(buf))!=ERR_OK) {
    return ERR_FAILED;
  }
  return ERR_OK;
}

uint8_t McuPCF85063A_WriteDate(McuPCF85063A_TDATE *date) {
  uint8_t buf[McuPCF85063A_MEMORY_DATE_SIZE];

  if (   (date->year>99)
      || (date->month>12)||(date->month==0)
      || (date->day>31)||(date->day==0)
      || (date->dayOfWeek>6)
     )
  {
    return ERR_RANGE;
  }
  buf[0] = (uint8_t)(((date->day/10)<<4) | (date->day%10));
  buf[1] = (uint8_t)(date->dayOfWeek);
  buf[2] = (uint8_t)(((date->month/10)<<4) | (date->month%10));
  buf[3] = (uint8_t)(((date->year/10)<<4) | (date->year%10));
  if (McuPCF85063A_WriteBlock(McuPCF85063A_ADDRESS_DATE_START_ADDR, buf, sizeof(buf))!=ERR_OK) {
    return ERR_FAILED;
  }
  return ERR_OK;
}

uint8_t McuPCF85063A_WriteTime(McuPCF85063A_TTIME *time) {
  uint8_t buf[McuPCF85063A_MEMORY_TIME_SIZE];

  if (   ((time->mode==McuPCF85063A_TTIME_MODE_12H)&&((time->hour>12)||(time->hour==0)))
      || ((time->mode==McuPCF85063A_TTIME_MODE_24H)&&(time->hour>23))
      || (time->min>59) || (time->sec>59)
     )
  {
    return ERR_RANGE;
  }
  buf[0] = (uint8_t)(((time->sec/10)<<4) | (time->sec%10));
  buf[1] = (uint8_t)(((time->min/10)<<4) | (time->min%10));
  buf[2] = (uint8_t)(((time->hour/10)<<4) | (time->hour%10));
  if (time->mode==McuPCF85063A_TTIME_MODE_12H) {
    buf[2] |= (time->am_pm)?(1<<5):0;
  }
  if (McuPCF85063A_WriteBlock(McuPCF85063A_ADDRESS_TIME_START_ADDR, buf, sizeof(buf))!=ERR_OK) {
    return ERR_FAILED;
  }
  return ERR_OK;
}

uint8_t McuPCF85063A_GetTime(TIMEREC *time) {
  McuPCF85063A_TTIME ttime;
  McuPCF85063A_TDATE tdate;

  if (McuPCF85063A_ReadTimeDate(&ttime, &tdate)!=ERR_OK) {
    return ERR_FAILED;
  }
  time->Hour = ttime.hour;
  time->Min = ttime.min;
  time->Sec = ttime.sec;
  time->Sec100 = 0;
  return ERR_OK;
}

uint8_t McuPCF85063A_SetTimeInfo(uint8_t Hour, uint8_t Min, uint8_t Sec, uint8_t Sec100) {
  McuPCF85063A_TTIME ttime;

  ttime.hour = Hour;
  ttime.min = Min;
  ttime.sec = Sec;
  (void)Sec100; /* ignored, as cannot be stored on device */
  ttime.mode = McuPCF85063A_TTIME_MODE_24H;
  ttime.am_pm = McuPCF85063A_TTIME_AMPM_AM;
  return McuPCF85063A_WriteTime(&ttime);
}

uint8_t McuPCF85063A_SetTime(TIMEREC *time) {
  return McuPCF85063A_SetTimeInfo(time->Hour, time->Min, time->Sec, time->Sec100);
}

uint8_t McuPCF85063A_GetDate(DATEREC *date) {
  McuPCF85063A_TTIME ttime;
  McuPCF85063A_TDATE tdate;

  if (McuPCF85063A_ReadTimeDate(&ttime, &tdate)!=ERR_OK) {
    return ERR_FAILED;
  }
  date->Year = (uint16_t)(tdate.year+2000); /* assume we are after the year 2000 */
  date->Month = tdate.month;
  date->Day = tdate.day;
  return ERR_OK;
}

uint8_t McuPCF85063A_SetDateInfo(uint16_t Year, uint8_t Month, uint8_t Day) {
  McuPCF85063A_TDATE tdate;

  if (Year>=2000) {
    tdate.year = (uint8_t)(Year-2000);
  } else if (Year>=1900) {
    tdate.year = (uint8_t)(Year-1900);
  } else {
    tdate.year = Year%100;
  }
  tdate.month = Month;
  tdate.day = Day;
  tdate.dayOfWeek = McuUtility_WeekDay(Year, Month, Day);
  return McuPCF85063A_WriteDate(&tdate);
}

uint8_t McuPCF85063A_SetDate(DATEREC *date) {
  return McuPCF85063A_SetDateInfo(date->Year, date->Month, date->Day);
}

uint8_t McuPCF85063A_GetTimeDate(TIMEREC *time, DATEREC *date) {
  McuPCF85063A_TTIME ttime;
  McuPCF85063A_TDATE tdate;

  if (McuPCF85063A_ReadTimeDate(&ttime, &tdate)!=ERR_OK) {
    return ERR_FAILED;
  }
  time->Hour = ttime.hour;
  time->Min = ttime.min;
  time->Sec = ttime.sec;
  time->Sec100 = 0;
  date->Year = (uint16_t)(tdate.year+2000);
  date->Month = tdate.month;
  date->Day = tdate.day;
  return ERR_OK;
}

uint8_t McuPCF85063A_ReadRamByte(uint8_t *data) {
  return McuPCF85063A_ReadByte(McuPCF85063A_ADDRESS_RAM_BYTE, data);
}

uint8_t McuPCF85063A_WriteRamByte(uint8_t data) {
  return McuPCF85063A_WriteByte(McuPCF85063A_ADDRESS_RAM_BYTE, data);
}

static const char *GetWeekDayString(uint8_t weekday) {
  static const char *const weekDays[]={"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
  if (weekday<=sizeof(weekDays)/sizeof(weekDays[0])) {
    return weekDays[weekday];
  } else {
    return "error";
  }
}

static uint8_t StrCatHWTimeDate(uint8_t *buf, size_t bufSize) {
  McuPCF85063A_TDATE tdate;
  McuPCF85063A_TTIME ttime;
  const char *const weekDays[]={"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

  if (McuPCF85063A_ReadTimeDate(&ttime, &tdate)!=ERR_OK) {
    return ERR_FAILED;
  }
  if (tdate.dayOfWeek<=6) {
    McuUtility_strcat(buf, bufSize, (unsigned char*)GetWeekDayString(tdate.dayOfWeek));
  }
  McuUtility_chcat(buf, bufSize, ' ');
  McuUtility_strcatNum16uFormatted(buf, bufSize, tdate.day, '0', 2);
  McuUtility_chcat(buf, bufSize, '.');
  McuUtility_strcatNum16uFormatted(buf, bufSize, tdate.month, '0', 2);
  McuUtility_chcat(buf, bufSize, '.');
  McuUtility_strcatNum16u(buf, bufSize, (uint16_t)tdate.year);
  McuUtility_strcat(buf, bufSize, (unsigned char*)", ");
  McuUtility_strcatNum16sFormatted(buf, bufSize, ttime.hour, '0', 2);
  McuUtility_chcat(buf, bufSize, ':');
  McuUtility_strcatNum16sFormatted(buf, bufSize, ttime.min, '0', 2);
  McuUtility_chcat(buf, bufSize, ':');
  McuUtility_strcatNum16sFormatted(buf, bufSize, ttime.sec, '0', 2);
  if (ttime.mode==McuPCF85063A_TTIME_MODE_24H) {
    McuUtility_strcat(buf, bufSize, (unsigned char*)" (24h)");
  } else {
    if (ttime.am_pm==McuPCF85063A_TTIME_AMPM_AM) {
    McuUtility_strcat(buf, bufSize, (unsigned char*)"am");
    } else {
      McuUtility_strcat(buf, bufSize, (unsigned char*)"pm");
    }
  }
  return ERR_OK;
}

static uint8_t StrCatHWAlarm(unsigned char *buf, size_t bufSize) {
  uint8_t res, data;
  bool enabled;
  bool is24h, isAM;

  McuUtility_strcat(buf, bufSize, (unsigned char*)"h:");
  res = McuPCF85063A_ReadAlarmHour(&data, &enabled, &is24h, &isAM);
  if (res==ERR_OK) {
    McuUtility_strcatNum8u(buf, bufSize, data);
    if (!is24h) {
      if (isAM) {
        McuUtility_strcat(buf, bufSize, (unsigned char*)"AM");
      } else {
        McuUtility_strcat(buf, bufSize, (unsigned char*)"PM");
      }
    }
    McuUtility_strcat(buf, bufSize, (unsigned char*)" (");
    if (enabled) {
      McuUtility_strcat(buf, bufSize, (unsigned char*)"on); ");
    } else {
      McuUtility_strcat(buf, bufSize, (unsigned char*)"off); ");
    }
  } else {
    McuUtility_strcat(buf, bufSize, (unsigned char*)"ERR");
  }
  McuUtility_strcat(buf, bufSize, (unsigned char*)"m:");
  res = McuPCF85063A_ReadAlarmMinute(&data, &enabled);
  if (res==ERR_OK) {
    McuUtility_strcatNum8u(buf, bufSize, data);
    McuUtility_strcat(buf, bufSize, (unsigned char*)" (");
    if (enabled) {
      McuUtility_strcat(buf, bufSize, (unsigned char*)"on); ");
    } else {
      McuUtility_strcat(buf, bufSize, (unsigned char*)"off); ");
    }
  } else {
    McuUtility_strcat(buf, bufSize, (unsigned char*)"ERR");
  }
  McuUtility_strcat(buf, bufSize, (unsigned char*)"s:");
  res = McuPCF85063A_ReadAlarmSecond(&data, &enabled);
  if (res==ERR_OK) {
    McuUtility_strcatNum8u(buf, bufSize, data);
    McuUtility_strcat(buf, bufSize, (unsigned char*)" (");
    if (enabled) {
      McuUtility_strcat(buf, bufSize, (unsigned char*)"on); ");
    } else {
      McuUtility_strcat(buf, bufSize, (unsigned char*)"off); ");
    }
  } else {
    McuUtility_strcat(buf, bufSize, (unsigned char*)"ERR");
  }
  McuUtility_strcat(buf, bufSize, (unsigned char*)"w:");
  res = McuPCF85063A_ReadAlarmWeekDay(&data, &enabled);
  if (res==ERR_OK) {
    McuUtility_strcatNum8u(buf, bufSize, data);
    McuUtility_strcat(buf, bufSize, (unsigned char*)", ");
    McuUtility_strcat(buf, bufSize, (unsigned char*)GetWeekDayString(data));
    McuUtility_strcat(buf, bufSize, (unsigned char*)" (");
    if (enabled) {
      McuUtility_strcat(buf, bufSize, (unsigned char*)"on); ");
    } else {
      McuUtility_strcat(buf, bufSize, (unsigned char*)"off); ");
    }
  } else {
    McuUtility_strcat(buf, bufSize, (unsigned char*)"ERR");
  }
  return ERR_OK;
}

static uint8_t DateCmd(const unsigned char *cmd, McuShell_ConstStdIOType *io) {
  uint8_t day, month;
  uint16_t year;
  uint8_t res = ERR_OK;

  if (McuUtility_ScanDate(&cmd, &day, &month, &year) == ERR_OK) { /* ok, format fine */
    /* update real time clock */
    res = McuPCF85063A_SetDateInfo(year, month, day);
    if (res!=ERR_OK) {
      McuShell_SendStr((unsigned char*)"*** Failure setting RTC\r\n", io->stdErr);
      res = ERR_FAILED;
    }
  } else {
    McuShell_SendStr((unsigned char*)"*** Error while reading command! ***", io->stdErr);
    McuShell_SendStr((void *)cmd, io->stdErr);
    McuShell_SendStr((unsigned char*)"\r\n", io->stdErr);
    res = ERR_FAILED;
  }
  return res;
}

static uint8_t TimeCmd(const unsigned char *cmd, McuShell_ConstStdIOType *io) {
  uint8_t hour, minute, second, hSecond;
  uint8_t res = ERR_OK;

  if (McuUtility_ScanTime(&cmd, &hour, &minute, &second, &hSecond)==ERR_OK) { /* format fine */
    /* set RTC time */
    res = McuPCF85063A_SetTimeInfo(hour, minute, second, hSecond);
    if (res != ERR_OK) {
      McuShell_SendStr((unsigned char*)"*** Failure setting RTC time\r\n", io->stdErr);
      res = ERR_FAILED;
    }
  } else {
    McuShell_SendStr((unsigned char*)"*** Error while reading command: ", io->stdErr);
    McuShell_SendStr(cmd, io->stdErr);
    McuShell_SendStr((unsigned char*)"\r\n", io->stdErr);
    res = ERR_FAILED;
  }
  return res;
}

static uint8_t CmdAlarmEnable(const unsigned char *p, bool enable) {
  uint8_t val;
  bool dummy;
  bool is24h, isAM;

  if (*p=='s') {
    if (McuPCF85063A_ReadAlarmSecond(&val, &dummy)!=ERR_OK) {
      return ERR_FAILED;
    }
    return McuPCF85063A_WriteAlarmSecond(val, enable);
  } else if (*p=='m') {
    if (McuPCF85063A_ReadAlarmMinute(&val, &dummy)!=ERR_OK) {
      return ERR_FAILED;
    }
    return McuPCF85063A_WriteAlarmMinute(val, enable);
  } else if (*p=='h') {
    if (McuPCF85063A_ReadAlarmHour(&val, &dummy, &is24h, &isAM)!=ERR_OK) {
      return ERR_FAILED;
    }
    return McuPCF85063A_WriteAlarmHour(val, enable, is24h, isAM);
  } else if (*p=='w') {
    if (McuPCF85063A_ReadAlarmWeekDay(&val, &dummy)!=ERR_OK) {
      return ERR_FAILED;
    }
    return McuPCF85063A_WriteAlarmWeekDay(val, enable);
  }
  return ERR_FAILED;
}

static uint8_t PrintStatus(McuShell_ConstStdIOType *io) {
  unsigned char buf[96];
  uint8_t res, data;

  McuShell_SendStatusStr((unsigned char*)"rtc", (const unsigned char*)"Status of PCF85063A RTC\r\n", io->stdOut);

  McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"0x");
  McuUtility_strcatNum8Hex(buf, sizeof(buf), McuPCF85063A_I2C_DEVICE_ADDRESS);
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  McuShell_SendStatusStr((unsigned char*)"  address", buf, io->stdOut);

  res = McuPCF85063A_ReadControl1(&data);
  if (res==ERR_OK) {
    McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"0x");
    McuUtility_strcatNum8Hex(buf, sizeof(buf), data);
    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)": ");
    if (data&(1<<7)) { /* EXT_TEST */
      McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"7:test(1), ");
    } else {
      McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"7:normal(0), ");
    }
    if (data&(1<<5)) { /* STOP*/
      McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"5:RCTstopped(1), ");
    } else {
      McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"5:RTCruns(0), ");
    }
    if (data&(1<<3)) { /* CIE: correction interrupt enable */
      McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"3:CIEoff(1), ");
    } else {
      McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"3:CIEon(0), ");
    }
    if (data&(1<<1)) { /* 12_24 */
      McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"1:12h(1), ");
    } else {
      McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"1:24h(0), ");
    }
    if (data&(1<<0)) { /* CAP_SEL */
      McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"0:12.5pF(1)");
    } else {
      McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"0:7pF(0)");
    }
    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  } else {
    McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"ERROR\r\n");
  }
  McuShell_SendStatusStr((uint8_t*)"  Control_1", (unsigned char*)buf, io->stdOut);

  res = McuPCF85063A_ReadControl2(&data);
  if (res==ERR_OK) {
    McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"0x");
    McuUtility_strcatNum8Hex(buf, sizeof(buf), data);
    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)": ");
    if (data&(1<<7)) { /* AIE */
      McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"7:AIEon(1), ");
    } else {
      McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"7:AIEoff(0), ");
    }
    if (data&(1<<6)) { /* AF */
      McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"6:AFon(1), ");
    } else {
      McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"6:AFoff(0), ");
    }
    if (data&(1<<5)) { /* MI */
      McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"5:MIon(1), ");
    } else {
      McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"5:MIoff(0), ");
    }
    if (data&(1<<4)) { /* HMI */
      McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"4:HMIon(1), ");
    } else {
      McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"4:HMIoff(0), ");
    }
    if (data&(1<<3)) { /* TF */
      McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"3:TFon(1), ");
    } else {
      McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"3:TFoff(0), ");
    }
    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"2..0:COF(");
    McuUtility_strcatNum8u(buf, sizeof(buf), data&0x0);
    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)")\r\n");
  } else {
    McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"ERROR\r\n");
  }
  McuShell_SendStatusStr((uint8_t*)"  Control_2", (unsigned char*)buf, io->stdOut);

  res = McuPCF85063A_ReadOffset(&data);
  if (res==ERR_OK) {
    McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"0x");
    McuUtility_strcatNum8Hex(buf, sizeof(buf), data);
    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  } else {
    McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"ERROR\r\n");
  }
  McuShell_SendStatusStr((uint8_t*)"  Offset", (unsigned char*)buf, io->stdOut);

  res = McuPCF85063A_ReadRamByte(&data);
  if (res==ERR_OK) {
    McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"0x");
    McuUtility_strcatNum8Hex(buf, sizeof(buf), data);
    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  } else {
    McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"ERROR\r\n");
  }
  McuShell_SendStatusStr((uint8_t*)"  RAM byte", (unsigned char*)buf, io->stdOut);

  buf[0] = '\0';
  if (StrCatHWAlarm(buf, sizeof(buf))) {
    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"ERROR\r\n");
  } else {
    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  }
  McuShell_SendStatusStr((unsigned char*)"  alarm", buf, io->stdOut);

  buf[0] = '\0';
  if (StrCatHWTimeDate(buf, sizeof(buf))!=ERR_OK) {
    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"ERROR\r\n");
  } else {
    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  }
  McuShell_SendStatusStr((unsigned char*)"  time/date", buf, io->stdOut);
  return ERR_OK;
}

uint8_t McuPCF85063A_ParseCommand(const unsigned char *cmd, bool *handled, const McuShell_StdIOType *io) {
  int32_t val;
  const unsigned char *p;
  bool enabled;
  uint8_t dummy;

  if (McuUtility_strcmp((char*)cmd, McuShell_CMD_HELP)==0 || McuUtility_strcmp((char*)cmd, "rtc help")==0) {
    *handled = true;
    McuShell_SendHelpStr((unsigned char*)"rtc", (const unsigned char*)"Group of PCF85063 RTC commands\r\n", io->stdOut);
    McuShell_SendHelpStr((unsigned char*)"  help|status", (const unsigned char*)"Print help or status information\r\n", io->stdOut);
    McuShell_SendHelpStr((unsigned char*)"  reset", (const unsigned char*)"Send software reset command to device\r\n", io->stdOut);
    McuShell_SendHelpStr((unsigned char*)"  write ram <val>", (const unsigned char*)"Write a byte value to the RAM\r\n", io->stdOut);
    McuShell_SendHelpStr((unsigned char*)"  write ctrl1 <val>", (const unsigned char*)"Write a byte to the Control_1 (00h) register\r\n", io->stdOut);
    McuShell_SendHelpStr((unsigned char*)"  write ctrl2 <val>", (const unsigned char*)"Write a byte to the Control_2 (01h) register\r\n", io->stdOut);
    McuShell_SendHelpStr((unsigned char*)"  write offset <val>", (const unsigned char*)"Write a byte to the Offset (02h) register\r\n", io->stdOut);
    McuShell_SendHelpStr((unsigned char*)"  time [hh:mm:ss[,z]]", (const unsigned char*)"Set the current time\r\n", io->stdOut);
    McuShell_SendHelpStr((unsigned char*)"  date [dd.mm.yyyy]", (const unsigned char*)"Set the current date\r\n", io->stdOut);
    McuShell_SendHelpStr((unsigned char*)"  alarm s|m|h|w <v>", (const unsigned char*)"Set alarm value for second, minute, hour or weekday\r\n", io->stdOut);
    McuShell_SendHelpStr((unsigned char*)"  alarm on|off s|m|h|w", (const unsigned char*)"Enable alarm for second, minute, hour or weekday\r\n", io->stdOut);
    McuShell_SendHelpStr((unsigned char*)"  alarm AIE on|off", (const unsigned char*)"Enable alarm interrupt for second, minute or hour\r\n", io->stdOut);
    McuShell_SendHelpStr((unsigned char*)"  alarm reset AF", (const unsigned char*)"Reset alarm interrupt flag\r\n", io->stdOut);
    return ERR_OK;
  } else if ((McuUtility_strcmp((char*)cmd, McuShell_CMD_STATUS)==0) || (McuUtility_strcmp((char*)cmd, "rtc status")==0)) {
    *handled = true;
    return PrintStatus(io);
  } else if (McuUtility_strncmp((char*)cmd, "rtc write ram ", sizeof("rtc write ram ")-1)==0) {
    *handled = true;
    p = cmd + sizeof("rtc write ram ")-1;
    if (McuUtility_xatoi(&p, &val)==ERR_OK && val>=0 && val<=0xff) {
      return McuPCF85063A_WriteRamByte(val);
    }
  } else if (McuUtility_strncmp((char*)cmd, "rtc write ctrl1 ", sizeof("rtc write ctrl1 ")-1)==0) {
    *handled = true;
    p = cmd + sizeof("rtc write ctrl1 ")-1;
    if (McuUtility_xatoi(&p, &val)==ERR_OK && val>=0 && val<=0xff) {
      return McuPCF85063A_WriteControl1(val);
    }
  } else if (McuUtility_strncmp((char*)cmd, "rtc write ctrl2 ", sizeof("rtc write ctrl2 ")-1)==0) {
    *handled = true;
    p = cmd + sizeof("rtc write ctrl2 ")-1;
    if (McuUtility_xatoi(&p, &val)==ERR_OK && val>=0 && val<=0xff) {
      return McuPCF85063A_WriteControl2(val);
    }
  } else if (McuUtility_strncmp((char*)cmd, "rtc write offset ", sizeof("rtc write offset ")-1)==0) {
    *handled = true;
    p = cmd + sizeof("rtc write offset ")-1;
    if (McuUtility_xatoi(&p, &val)==ERR_OK && val>=0 && val<=0xff) {
      return McuPCF85063A_WriteOffset(val);
    }
  } else if (McuUtility_strncmp((char*)cmd, "rtc date ", sizeof("rtc date ")-1)==0) {
    *handled = TRUE;
    p = cmd + sizeof("rtc date ")-1;
    return DateCmd(p, io);
  } else if (McuUtility_strncmp((char*)cmd, "rtc time ", sizeof("rtc time ")-1)==0) {
    *handled = TRUE;
    p = cmd + sizeof("rtc time ")-1;
    return TimeCmd(p, io);
  } else if (McuUtility_strncmp((char*)cmd, "rtc alarm s ", sizeof("rtc alarm s ")-1)==0) {
    *handled = TRUE;
    p = cmd + sizeof("rtc alarm s ")-1;
    if (McuPCF85063A_ReadAlarmSecond(&dummy, &enabled)!=ERR_OK) { /* get enabled state */
      return ERR_FAILED;
    }
    if (McuUtility_xatoi(&p, &val)==ERR_OK && val>=0 && val<=59) {
      return McuPCF85063A_WriteAlarmSecond(val, enabled);
    }
    return ERR_FAILED;
  } else if (McuUtility_strncmp((char*)cmd, "rtc alarm m ", sizeof("rtc alarm m ")-1)==0) {
    *handled = TRUE;
    p = cmd + sizeof("rtc alarm m")-1;
    if (McuPCF85063A_ReadAlarmMinute(&dummy, &enabled)!=ERR_OK) { /* get enabled state */
      return ERR_FAILED;
    }
    if (McuUtility_xatoi(&p, &val)==ERR_OK && val>=0 && val<=59) {
      return McuPCF85063A_WriteAlarmMinute(val, enabled);
    }
    return ERR_FAILED;
  } else if (McuUtility_strncmp((char*)cmd, "rtc alarm h ", sizeof("rtc alarm h ")-1)==0) {
    bool is24h, isAM;
    *handled = TRUE;
    p = cmd + sizeof("rtc alarm h")-1;
    if (McuPCF85063A_ReadAlarmHour(&dummy, &enabled, &is24h, &isAM)!=ERR_OK) { /* get enabled state */
      return ERR_FAILED;
    }
    if (McuUtility_xatoi(&p, &val)==ERR_OK && val>=0 && val<=23) {
      return McuPCF85063A_WriteAlarmHour(val, enabled, true, false); /* only supporting 24h format */
    }
    return ERR_FAILED;
  } else if (McuUtility_strncmp((char*)cmd, "rtc alarm w ", sizeof("rtc alarm w ")-1)==0) {
    *handled = TRUE;
    p = cmd + sizeof("rtc alarm w")-1;
    if (McuPCF85063A_ReadAlarmWeekDay(&dummy, &enabled)!=ERR_OK) { /* get enabled state */
      return ERR_FAILED;
    }
    if (McuUtility_xatoi(&p, &val)==ERR_OK && val>=0 && val<=6) {
      return McuPCF85063A_WriteAlarmWeekDay(val, enabled);
    }
    return ERR_FAILED;
  } else if (McuUtility_strcmp((char*)cmd, "rtc reset")==0) {
    *handled = true;
    return McuPCF85063A_WriteSoftwareReset();
  } else if (McuUtility_strcmp((char*)cmd, "rtc alarm AIE on")==0) {
    *handled = true;
    return McuPCF85063A_WriteAlarmInterrupt(true);
  } else if (McuUtility_strcmp((char*)cmd, "rtc alarm AIE off")==0) {
    *handled = true;
    return McuPCF85063A_WriteAlarmInterrupt(false);
  } else if (McuUtility_strcmp((char*)cmd, "rtc alarm reset AF")==0) {
    *handled = true;
    return McuPCF85063A_WriteResetAlarmInterrupt();
  } else if (McuUtility_strncmp((char*)cmd, "rtc alarm on ", sizeof("rtc alarm on ")-1)==0) {
    *handled = true;
    return CmdAlarmEnable(cmd+sizeof("rtc alarm on ")-1, true);
  } else if (McuUtility_strncmp((char*)cmd, "rtc alarm off ", sizeof("rtc alarm off ")-1)==0) {
    *handled = true;
    return CmdAlarmEnable(cmd+sizeof("rtc alarm off ")-1, false);
  }
  return ERR_OK;
}

void McuPCF85063A_Init(void) {
}
