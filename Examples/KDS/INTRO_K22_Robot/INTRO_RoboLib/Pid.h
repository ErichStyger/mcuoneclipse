/**
 * \file
 * \brief This is the interface to PID Module
 * \author Erich Styger, erich.styger@hslu.ch
 */

#ifndef PID_H_
#define PID_H_

#include "Platform.h"
#if PL_HAS_PID

typedef enum {
  PID_CONFIG_LINE_FW,
  PID_CONFIG_LINE_BW,
  PID_CONFIG_POS_LEFT,
  PID_CONFIG_POS_RIGHT,
  PID_CONFIG_SPEED_LEFT,
  PID_CONFIG_SPEED_RIGHT
} PID_ConfigType;

typedef struct {
  int32_t pFactor100;
  int32_t iFactor100;
  int32_t dFactor100;
  int32_t iAntiWindup;
  uint8_t maxSpeedPercent; /* max speed if 100% on the line, 0xffff would be full speed */
  int32_t lastError;
  int32_t integral;
} PID_Config;

uint8_t PID_GetPIDConfig(PID_ConfigType config, PID_Config **confP);

#if PL_CONFIG_HAS_SHELL
#include "CLS1.h"
/*!
 * \brief Shell command line parser.
 * \param[in] cmd Pointer to command string
 * \param[out] handled If command is handled by the parser
 * \param[in] io Std I/O handler of shell
 */
uint8_t PID_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io);
#endif

/*!
 * \brief Performs PID on a line
 * \param currLinePos Current line position
 * \param setLinePos Desired line position
 * \param currLineWidth Indication of line width (in 1000er units for a line)
 * \param forward If we are moving forward or backward
 */
void PID_Line(uint16_t currLinePos, uint16_t setLinePos, uint16_t currLineWidth, bool forward);

/*!
 * \brief Performs PID closed loop calculation for the speed
 * \param currSpeed Current speed of motor
 * \param setSpeed desired speed of motor
 * \param isLeft TRUE if is for the left motor, otherwise for the right motor
 */
void PID_Speed(int32_t currSpeed, int32_t setSpeed, bool isLeft);

/*!
 * \brief Performs PID closed loop calculation for the line position
 * \param currPos Current position of wheel
 * \param setPos Desired wheel position
 * \param isLeft TRUE if is for the left wheel, otherwise for the right wheel
 */
void PID_Pos(int32_t currPos, int32_t setPos, bool isLeft);

/*! \brief Driver initialization */
void PID_Start(void);

/*! \brief Driver initialization */
void PID_Init(void);

/*! \brief Driver de-initialization */
void PID_Deinit(void);

#endif /* PL_HAS_PID */

#endif /* PID_H_ */
