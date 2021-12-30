/*!
 * \file      rtc-board.c
 *
 * \brief     Target board RTC timer
 *
 * \copyright Revised BSD License, see section \ref LICENSE.
 *
 * \author    Diego Bienz
 */

#include "platform.h"
#include "board.h"
#include "eeprom-board.h"
#include "board-config.h"
#include "rtc-board.h"
#include "lpm-board.h"
#include "timer.h"
#include "gps.h"
#include "fsl_rtc.h"
#include "fsl_ostimer.h"
#include "fsl_power.h"
#include "utilities.h"

#define OSTIMER_REF					      OSTIMER
#define OSTIMER_CLK_FREQ          32768

#define BACKUP_FLASH_OFFSET       1200   /* NvmDataMgmtRestore() needs up to offset 1096 */

/*!
 * RTC timer context
 */
typedef struct {
	uint32_t Time;  // Reference time
} RtcTimerContext_t;

/*!
 * Keep the value of the RTC timer when the RTC alarm is set
 * Set with the RtcSetTimerContext function
 * Value is kept as a Reference to calculate alarm
 */
static RtcTimerContext_t RtcTimerContext;

/*!
 * State if an alarm is pending
 */
static bool PendingAlarm = false;

/*!
 * External Nmea GPS data, stored in gps.c
 */
extern NmeaGpsData_t NmeaGpsData;

/*!
 * Callback function for the OS Timer
 */
void RtcOSTimerCallback(void);

void RtcInit(void) {
	/* OS Timer initialization */
	OSTIMER_Init(OSTIMER_REF);

	/* RTC initialization */
	RTC_Init(RTC);

	rtc_datetime_t initDate;
	initDate.year = 2020U;
	initDate.month = 12U;
	initDate.day = 12U;
	initDate.hour = 12U;
	initDate.minute = 0;
	initDate.second = 0;

	/* RTC time counter has to be stopped before setting the date & time in the TSR register */
	RTC_EnableTimer(RTC, false);

	/* Set RTC time to default */
	RTC_SetDatetime(RTC, &initDate);

	/* When working under Normal Mode, the interrupt is controlled by NVIC. */
	EnableIRQ(RTC_IRQn);

	/* Start the RTC time counter */
	RTC_EnableTimer(RTC, true);
}

uint32_t RtcGetMinimumTimeout(void) {
	/* Minimum is 1 ms */
	return RtcMs2Tick(1);
}

uint32_t RtcMs2Tick(TimerTime_t milliseconds) {
	return MSEC_TO_COUNT(milliseconds, OSTIMER_CLK_FREQ);
}

TimerTime_t RtcTick2Ms(uint32_t tick) {
	return COUNT_TO_MSEC(tick, OSTIMER_CLK_FREQ);
}

void RtcDelayMs(TimerTime_t milliseconds) {
	uint64_t delayTicks = 0;
	uint64_t refTicks = RtcGetTimerValue();

	delayTicks = RtcMs2Tick(milliseconds);

	// Wait delay ms
	while (((RtcGetTimerValue() - refTicks)) < delayTicks) {
		__NOP();
	}
}

void RtcSetAlarm(uint32_t timeout) {
	RtcStartAlarm(timeout);
}

void RtcStopAlarm(void) {
	PendingAlarm = false;
}

void RtcStartAlarm(uint32_t timeout) {
	CRITICAL_SECTION_BEGIN();
	RtcStopAlarm();
	PendingAlarm = true;

  /* Set the match value with unit of ticks. */
  OSTIMER_SetMatchValue(OSTIMER_REF, timeout + RtcGetTimerValue(), RtcOSTimerCallback);

	CRITICAL_SECTION_END();
}

uint32_t RtcSetTimerContext(void) {
	RtcTimerContext.Time = RtcGetTimerValue();
	return RtcTimerContext.Time;
}

uint32_t RtcGetTimerContext(void) {
	return RtcTimerContext.Time;
}

uint32_t RtcGetCalendarTime(uint16_t *milliseconds) {
	*milliseconds = 0;
	uint32_t a, b;
  do {
    a = RTC->COUNT;
    b = RTC->COUNT;
  } while (a != b);
	return b;
}

uint32_t RtcGetTimerValue(void) {
	return OSTIMER_GetCurrentTimerValue(OSTIMER_REF);
}

uint32_t RtcGetTimerElapsedTime(void) {
	return (uint32_t)(RtcGetTimerValue() - RtcTimerContext.Time);
}

/*!
 * Data is written to the predefined address BACKUP_FLASH_ADDRESS in the flash
 */
void RtcBkupWrite(uint32_t data0, uint32_t data1) {
	uint8_t flashBackupPage[2*sizeof(uint32_t)];

	/* Save data0 to the first 4 bytes (Big endian) */
	flashBackupPage[0] = data0 >> 24;
	flashBackupPage[1] = data0 >> 16;
	flashBackupPage[2] = data0 >>  8;
	flashBackupPage[3] = data0;

	/* Save data1 to the second 4 bytes (Big endian) */
	flashBackupPage[4] = data1 >> 24;
	flashBackupPage[5] = data1 >> 16;
	flashBackupPage[6] = data1 >>  8;
	flashBackupPage[7] = data1;

	EepromMcuWriteBuffer(BACKUP_FLASH_OFFSET, flashBackupPage, sizeof(flashBackupPage));
}

/*!
 * Data is read from the predefined address BACKUP_FLASH_ADDRESS in the flash
 * CAUTION: If the data was not written to this address before, the result is unpredictable
 */
void RtcBkupRead(uint32_t *data0, uint32_t *data1) {
	uint8_t flashBackupPage[2*sizeof(uint32_t)];
	LmnStatus_t status;

	*data0 = 0;
	*data1 = 0;
	status = EepromMcuReadBuffer(BACKUP_FLASH_OFFSET, flashBackupPage, sizeof(flashBackupPage));
	if(status == LMN_STATUS_OK){
		*data0 = flashBackupPage[0];
		*data0 = (*data0  << 8) + flashBackupPage[1];
		*data0 = (*data0  << 8) + flashBackupPage[2];
		*data0 = (*data0  << 8) + flashBackupPage[3];

		*data1 = flashBackupPage[4];
		*data1 = (*data1  << 8) + flashBackupPage[5];
		*data1 = (*data1  << 8) + flashBackupPage[6];
		*data1 = (*data1  << 8) + flashBackupPage[7];
	}
}

void RtcProcess(void) {
	/* Not used on this board */
}

TimerTime_t RtcTempCompensation(TimerTime_t period, float temperature) {
	/* Not used on this board */
	return period;
}

void RtcOSTimerCallback(void){
	if (PendingAlarm) {
		RtcStopAlarm();
		TimerIrqHandler();
	}
}
