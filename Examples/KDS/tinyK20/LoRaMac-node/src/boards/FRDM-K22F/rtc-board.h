/**
 * \file rtc-board.h
 * \author Alexander Winiger (alexander.winiger@hslu.ch)
 * \date 21.09.2015
 * \brief MCU RTC timer and low power modes management
 *
 */
#ifndef __RTC_BOARD_H__
#define __RTC_BOARD_H__

#if defined(FSL_RTOS_FREE_RTOS)

/*!
 * \brief This function block the MCU from going into Low Power mode
 *
 * \param [IN] Status enable or disable
 */
void BlockLowPowerDuringTask( bool Status );

#else
/*---------------------------- Definitions ------------------------------*/

/*! @brief Table of base addresses for RTC instances. */
extern RTC_Type * const g_rtcBase[RTC_INSTANCE_COUNT];

/*!
 * \brief Timer time variable definition
 */
#ifndef TimerTime_t
typedef uint64_t TimerTime_t;
#endif

/*!
 * \brief Initializes the RTC timer
 *
 * \remark The timer is based on the RTC
 */
void RtcInit( void );

/*!
 * \brief Stop the RTC Timer
 */
void RtcStopTimer( void );

/*!
 * \brief Return the minimum timeout the RTC is able to handle
 *
 * \retval minimum value for a timeout
 */
uint32_t RtcGetMinimumTimeout( void );

/*!
 * \brief Start the RTC timer
 *
 * \remark The timer is based on the RTC Alarm running at 32.768KHz
 *
 * \param[IN] timeout       Duration of the Timer
 */
void RtcSetTimeout( uint32_t timeout );

/*!
 * \brief Get the RTC timer value
 *
 * \retval RTC Timer value
 */
TimerTime_t RtcGetTimerValue( void );

/*!
 * \brief Get the RTC timer elapsed time since the last Alarm was set
 *
 * \retval RTC Elapsed time since the last alarm
 */
uint32_t RtcGetTimerElapsedTime( void );

/*!
 * \brief This function block the MCU from going into Low Power mode
 *
 * \param [IN] Status enable or disable
 */
void BlockLowPowerDuringTask( bool Status );

/*!
 * \brief Sets the MCU in low power STOP mode
 */
void RtcEnterLowPowerStopMode( void );

/*!
 * \brief Restore the MCU to its normal operation mode
 */
void RtcRecoverMcuStatus( void );

/*!
 * \brief Perfoms a standard blocking delay in the code execution
 *
 * \param [IN] delay Delay value in ms
 */
void RtcDelayMs( uint32_t delay );

#endif

#endif // __RTC_BOARD_H__
