/**
 * \file
 * \brief Motor driver interface.
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * This module a driver for up to two small DC motors.
 */

#ifndef MOTOR_H_
#define MOTOR_H_

#include "Platform.h"
#if PL_CONFIG_HAS_MOTOR

#define MOTOR_HAS_INVERT 1  /* if we support motor revert at runtime */

typedef enum {
  MOT_DIR_FORWARD,  /*!< Motor forward direction */
  MOT_DIR_BACKWARD  /*!< Motor backward direction */
} MOT_Direction;

typedef int8_t MOT_SpeedPercent; /*!< -100%...+100%, where negative is backward */

typedef struct MOT_MotorDevice_ {
#if MOTOR_HAS_INVERT
  bool inverted;
#endif
  MOT_SpeedPercent currSpeedPercent; /*!< our current speed in %, negative percent means backward */
  uint16_t currPWMvalue; /*!< current PWM value used */
  uint8_t (*SetRatio16)(uint16_t); /*!< function to set the ratio */
  void (*DirPutVal)(bool); /*!< function to set direction bit */
} MOT_MotorDevice;

typedef enum {
  MOT_MOTOR_LEFT, /*!< left motor */
  MOT_MOTOR_RIGHT /*!< right motor */
} MOT_MotorSide;

#if MOTOR_HAS_INVERT
/*!
 * \brief Inverts the forward/backward signal for a motor
 * \param motor Motor handle
 * \param revert TRUE to invert logic, FALSE otherwise
 */
void MOT_Invert(MOT_MotorDevice *motor, bool invert);
#endif


/*!
 * \brief Function to get a pointer to a motor (motor handle)
 * \param side Which motor
 * \return Pointer/handle to the motor
 */
MOT_MotorDevice *MOT_GetMotorHandle(MOT_MotorSide side);

/*!
 * \brief Changes the speed of a motor, in the range of -100% (backward) to +100% (forward).
 * \param motor Motor handle.
 * \param relPercent Relative speed percentage to change.
 */
void MOT_ChangeSpeedPercent(MOT_MotorDevice *motor, MOT_SpeedPercent relPercent);

/*!
 * \brief Sets the speed of a motor, in the range of -100% (backward) to +100% (forward).
 * \param motor Motor handle.
 * \param percent Motor speed value, from -100 (full speed backward) to +100 (full speed forward).
 */
void MOT_SetSpeedPercent(MOT_MotorDevice *motor, MOT_SpeedPercent percent);

/*!
 * \brief Updates the motor % speed based on actual PWM value.
 * \param motor Motor handle.
 * \param dir Current direction of motor.
 */
void MOT_UpdatePercent(MOT_MotorDevice *motor, MOT_Direction dir);

/*!
 * \brief Sets the PWM value for the motor.
 * \param[in] motor Motor handle
 * \param[in] val New PWM value.
 */
void MOT_SetVal(MOT_MotorDevice *motor, uint16_t val);

/*!
 * \brief Return the current PWM value of the motor.
 * \param[in] motor Motor handle
 * \return Current PWM value.
 */
uint16_t MOT_GetVal(MOT_MotorDevice *motor);

/*!
 * \brief Change the direction of the motor
 * \param[in] motor Motor handle
 * \param[in] dir Direction to be used
 */
void MOT_SetDirection(MOT_MotorDevice *motor, MOT_Direction dir);

/*!
 * \brief Returns the direction of the motor
 * \param[in] motor Motor handle
 * \return Current direction of the motor
 */
MOT_Direction MOT_GetDirection(MOT_MotorDevice *motor);

#if PL_CONFIG_HAS_SHELL
#include "CLS1.h"
/*!
 * \brief Shell command line parser.
 * \param[in] cmd Pointer to command string
 * \param[out] handled If command is handled by the parser
 * \param[in] io Std I/O handler of shell
 */
uint8_t MOT_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io);
#endif /* PL_CONFIG_HAS_SHELL */

/*!
 * \brief Deinitialization function.
 */
void MOT_Deinit(void);

/*!
 * \brief Initialization function.
 */
void MOT_Init(void);

#endif /* PL_CONFIG_HAS_MOTOR */

#endif /* MOTOR_H_ */
