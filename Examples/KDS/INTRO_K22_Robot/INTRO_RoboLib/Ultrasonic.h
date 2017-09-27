/**
 * \file
 * \brief This is the interface to Ultrasonic HC-SR04 module
 * \author Erich Styger, erich.styger@hslu.ch
 */

#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_

#include "Platform.h"

typedef enum {
  US_SIGNAL_OK, /* signal received ok */
  US_SIGNAL_NO_ECHO, /* No echo received, timer timeout */
  US_SIGNAL_TIMEOUT, /* Timeout */
} US_SignalState;

#if PL_HAS_ULTRASONIC
/*! 
 * \brief Called in case of an overflow during input capture. This function is called from an interrupt!
 * \param UserDataPtr Pointer to user structure
 */
void US_EventEchoOverflow(LDD_TUserData *UserDataPtr);

/*!
 * \brief Called by the input capture interrupt for a raising or falling edge of the Echo pin
 * \param UserDataPtr Pointer to user structure
 */
void US_EventEchoCapture(LDD_TUserData *UserDataPtr);

/*!
 * \brief Returns the last measured value in centimeters
 * \return distance in centimeters
 */
uint16_t US_GetLastCentimeterValue(void);

/*! 
 * \brief Convert measured microseconds to centimeters.
 * \param[in] microseconds How long the echo time was measured in microseconds
 * \param[in] temperatureCelsius Air temperature in degree Celsius
 * \return Returns the distance in centimeters
 */
uint16_t US_usToCentimeters(uint16_t microseconds, uint8_t temperatureCelsius);

/*!
 * \brief Measure the echo and return the time in microseconds.
 * \return Time of the echo (forward and backward time).
 */
uint16_t US_Measure_us(void);

#if PL_CONFIG_HAS_SHELL
#include "CLS1.h"
/*!
 * \brief Parses a command
 * \param cmd Command string to be parsed
 * \param handled Sets this variable to TRUE if command was handled
 * \param io I/O stream to be used for input/output
 * \return Error code, ERR_OK if everything was fine
 */
uint8_t US_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io);
#endif

/*!
 * \brief Driver de-initialization routine.
 */
void US_Deinit(void);

/*!
 * \brief Driver initialization routine.
 */
void US_Init(void);

#endif /* PL_HAS_ULTRASONIC */

#endif /* ULTRASONIC_H_ */
