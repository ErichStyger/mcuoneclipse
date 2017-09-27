/**
 * \file
 * \brief Interface to drive the robot.
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * This module allows to drive the robot and to perform turns.
 */

#ifndef DRIVE_H_
#define DRIVE_H_

#include "Platform.h"
#if PL_HAS_DRIVE

#if PL_CONFIG_HAS_SHELL
#include "CLS1.h"

/*!
 * \brief Parses a command
 * \param cmd Command string to be parsed
 * \param handled Sets this variable to TRUE if command was handled
 * \param io I/O stream to be used for input/output
 * \return Error code, ERR_OK if everything was fine
 */
uint8_t DRV_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io);
#endif /* PL_CONFIG_HAS_SHELL */

typedef enum {
  DRV_MODE_NONE,
  DRV_MODE_STOP,
  DRV_MODE_SPEED,
#if PL_HAS_QUADRATURE
  DRV_MODE_POS,
#endif
} DRV_Mode;

uint8_t DRV_SetSpeed(int32_t left, int32_t right);
#if PL_HAS_QUADRATURE
uint8_t DRV_SetPos(int32_t left, int32_t right);
#endif
bool DRV_IsDrivingBackward(void);
uint8_t DRV_SetMode(DRV_Mode mode);
DRV_Mode DRV_GetMode(void);
bool DRV_IsStopped(void);
bool DRV_HasTurned(void);

/*!
 * \brief Stops the engines
 * \param timoutMs timout in milliseconds for operation
 * \return ERR_OK if stopped, ERR_BUSY for timeout condition.
 */
uint8_t DRV_Stop(int32_t timeoutMs);

/*!
 * \brief Driver initialization.
 */
void DRV_Init(void);

/*!
 * \brief Driver de-initialization.
 */
void DRV_Deinit(void);

#endif /* PL_HAS_DRIVE */

#endif /* DRIVE_H_ */
