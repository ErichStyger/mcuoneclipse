/*
 * Motor.h
 *
 *      Author: Erich Styger
 */

#ifndef MOTOR_H_
#define MOTOR_H_

#include "PE_Types.h"
#include "CLS1.h"

typedef enum {
  MOT_DIR_FORWARD,  /*!< Motor forward direction */
  MOT_DIR_BACKWARD  /*!< Motor backward direction */
} MOT_Direction;

typedef int8_t MOT_SpeedPercent; /* -100%...+100%, where negative is backward */

typedef struct MOT_MotorDevice_ {
  bool brake; /* if brake is enabled or not */
  MOT_SpeedPercent currSpeedPercent; /* our current speed in %, negative percent means backward */
  uint16_t currPWMvalue; /* current PWM value used */
  LDD_TError (*SetRatio16)(LDD_TDeviceData*, uint16_t);
  LDD_TDeviceData *PWMdeviceData; /* LDD device handle for PWM */
  void (*DirPutVal)(LDD_TDeviceData *, bool); /* function to set direction bit */
  LDD_TDeviceData *DIRdeviceData; /* LDD device handle for direction */
  void (*BrakePutVal)(LDD_TDeviceData *, bool); /* function to enable/disable brake */
  LDD_TDeviceData *BRAKEdeviceData; /* LDD device handle for brake pin */
  uint16_t currentValue; /* current AD current sensor value */
  uint16_t offset; /* current AD sensor offset value */
  LDD_TDeviceData *SNSdeviceData; /* LDD current AD device handle */
} MOT_MotorDevice;

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

/*!
 * \brief Shell command line parser.
 * \param[in] cmd Pointer to command string
 * \param[out] handled If command is handled by the parser
 * \param[in] io Std I/O handler of shell
 */
uint8_t MOT_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io);

/*!
 * \brief Initialization function.
 */
void MOT_Init(void);

#endif /* MOTOR_H_ */
