/*
 * Copyright (c) 2023-2024, Erich Styger
 *
 * Driver for the NXP PCF85063A I2C RTC.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef MCUPCF85063A_H_
#define MCUPCF85063A_H_

#include "McuPCF85063A_config.h"
#include "McuShell.h"
#include "McuTimeDate.h"

#ifdef __cplusplus
extern "C" {
#endif

/*!
 * \brief Shell command line parser.
 * \param cmd Shell command string
 * \param handled Set to true if command was handled, untouched otherwise
 * \param io Standard I/O handler to be used
 * \return Error code, ERR_OK if no failure
 */
uint8_t McuPCF85063A_ParseCommand(const unsigned char *cmd, bool *handled, const McuShell_StdIOType *io);

/*!
 * \brief Get the RTC time.
 * \param time Pointer store the time information
 * \return Error code, ERR_OK if no failure
 */
uint8_t McuPCF85063A_GetTime(TIMEREC *time);

/*!
 * \brief Get the RTC date.
 * \param date Pointer to store the date information
 * \return Error code, ERR_OK if no failure
 */
uint8_t McuPCF85063A_GetDate(DATEREC *date);

/*!
 * \brief Set the RTC time.
 * \param time Pointer to time information
 * \return Error code, ERR_OK if no failure
 */
uint8_t McuPCF85063A_SetTime(TIMEREC *time);

/*!
 * \brief Set the RTC date.
 * \param date Pointer to date information
 * \return Error code, ERR_OK if no failure
 */
uint8_t McuPCF85063A_SetDate(DATEREC *date);

/*!
 * \brief Get the current time and date from the RTC
 * \param time Pointer where to store the time
 * \param date Pointer where to store the date
 * \return Error code, ERR_OK if no failure.
 */
uint8_t McuPCF85063A_GetTimeDate(TIMEREC *time, DATEREC *date);

/*!
 * \brief Set the RTC time information
 * \param Hour The hour, in the range of 0-23
 * \param Min The minute, in the range of 0-59
 * \param Sec The second, in the range of 0-59
 * \praam Sec100 The 0.01 sec part, in the range of 0-99
 * \return Error code, ERR_OK if no failure.
 */
uint8_t McuPCF85063A_SetTimeInfo(uint8_t Hour, uint8_t Min, uint8_t Sec, uint8_t Sec100);

/*!
 * \brief set the RTC date information
 * \param Year The year, for example 2024
 * \param Month The month, for example 11
 * \param Day The day of the month, in the range of 0-31, depending of the month
 * \return Error code, ERR_OK if no failure.
 */
uint8_t McuPCF85063A_SetDateInfo(uint16_t Year, uint8_t Month, uint8_t Day);

/*! \brief different RTC clock output frequencies */
typedef enum McuPCF85063A_COF_Frequency_e {
  McuPCF85063A_COF_FREQ_32768 = 0,
  McuPCF85063A_COF_FREQ_16384 = 1,
  McuPCF85063A_COF_FREQ_8192  = 2,
  McuPCF85063A_COF_FREQ_4096  = 3,
  McuPCF85063A_COF_FREQ_2048  = 4,
  McuPCF85063A_COF_FREQ_1024  = 5,
  McuPCF85063A_COF_FREQ_1     = 6,
  McuPCF85063A_COF_FREQ_OFF   = 7
} McuPCF85063A_COF_Frequency_e;

/*!
 * \brief Configure a new clock output frequency
 * \param Frequency Frequency to use
 * \return Error code, ERR_OK if no failure.
 */
uint8_t McuPCF85063A_WriteClockOutputFrequency(McuPCF85063A_COF_Frequency_e frequency);

/*!
 * \brief Read the alarm second time value
 * \param second Pointer to store the value
 * \param enabled Returns if the alarm is enabled or not.
 * \return Error code, ERR_OK if no failure.
 */
uint8_t McuPCF85063A_ReadAlarmSecond(uint8_t *second, bool *enabled);

/*!
 * \brief Write the Alarm second time value
 * \param second Second time alarm value
 * \param enabled true to enable the alarm, false otherwise
 * \return Error code, ERR_OK if no failure.
 */
uint8_t McuPCF85063A_WriteAlarmSecond(uint8_t second, bool enable);

/*!
 * \brief Read the alarm minute value
 * \param minute Where to store the minute value
 * \param enabled Returns if the alarm is enabled or not.
 * \return Error code, ERR_OK if no failure.
 */
uint8_t McuPCF85063A_ReadAlarmMinute(uint8_t *minute, bool *enabled);

/*!
 * \brief Write the alarm minute value
 * \param minute Minute value to write
 * \param enable If the alarm has to be enabled or not
 * \return Error code, ERR_OK if no failure.
 */
uint8_t McuPCF85063A_WriteAlarmMinute(uint8_t minute, bool enable);

/*!
 * \brief Read the alarm hour value
 * \param hour Where to store the alarm hour value
 * \param enabled Returns if the alarm is enabled or not.
 * \param is24h Returns true if the hour format is 24 hours, false otherwise
 * \param isAM Returns true if the hour is an AM value, false otherwise
 * \return Error code, ERR_OK if no failure.
 */
uint8_t McuPCF85063A_ReadAlarmHour(uint8_t *hour, bool *enabled, bool *is24h, bool *isAM);

/*!
 * \brief Write the alarm hour value
 * \param hour Hour value
 * \param enable If the alarm has to be enabled or not
 * \param is24h true if hour value is for 24h format, false otherwise
 * \param isAM true if hour value is AM, false otherwise
 * \return Error code, ERR_OK if no failure.
 */
uint8_t McuPCF85063A_WriteAlarmHour(uint8_t hour, bool enable, bool is24h, bool isAM);

/*!
 * \brief Read the alarm day
 * \param day Used to store the alarm day value
 * \param enabled Returns if the alarm is enabled or not.
 * \return Error code, ERR_OK if no failure.
 */
uint8_t McuPCF85063A_ReadAlarmDay(uint8_t *day, bool *enabled);

/*!
 * \brief Write the alarm day value
 * \param day Day value for the alarm
 * \param enable If the alarm has to be enabled or not
 * \return Error code, ERR_OK if no failure.
 */
uint8_t McuPCF85063A_WriteAlarmDay(uint8_t day, bool enable);

/*!
 * \brief Read the alarm week day
 * \param weekDay Used to store the day
 * \param enabled Returns if the alarm is enabled or not.
 * \return Error code, ERR_OK if no failure.
 */
uint8_t McuPCF85063A_ReadAlarmWeekDay(uint8_t *weekDay, bool *enabled);

/*!
 * \brief Write the alarm week day
 * \param weekDay The day of week (0-6)
 * \param enable If alarm is enabled
 * \return Error code, ERR_OK if no failure.
 */
uint8_t McuPCF85063A_WriteAlarmWeekDay(uint8_t weekDay, bool enable);

/*!
 * \brief Perform a software reset
 * \return Error code, ERR_OK if no failure.
 */
uint8_t McuPCF85063A_WriteSoftwareReset(void);

/*!
 * \brief Write the alarm interrupt flag setting
 * \param enable Use true to enable it, false otherwise
 * \return Error code, ERR_OK if no failure.
 */
uint8_t McuPCF85063A_WriteAlarmInterrupt(bool enable);

/*!
 * \brief Reset the alarm interrupt flag
 * \return Error code, ERR_OK if no failure.
 */
uint8_t McuPCF85063A_WriteResetAlarmInterrupt(void);


/*!
 * \brief Driver de-initialization.
 */
void McuPCF85063A_Deinit(void);

/*!
 * \brief Driver initialization.
 */
void McuPCF85063A_Init(void);

#ifdef __cplusplus
}  /* extern "C" */
#endif

#endif /* MCUPCF85063A_H_ */
