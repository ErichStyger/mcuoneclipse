/*
 * Copyright (c) 2019, Erich Styger
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef MCUA3967_H_
#define MCUA3967_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "McuA3967config.h"
#include "McuGPIO.h"
#include <stdbool.h>

typedef void *McuA3967_Handle_t;

#if McuA3967_CONFIG_PARSE_COMMAND_ENABLED
  #include "McuShell.h" /* Command line shell */
  uint8_t McuA3967_ParseCommand(const unsigned char* cmd, bool *handled, const McuShell_StdIOType *io);

  /* handler for stepper motor */
  uint8_t McuA3967_PrintStepperStatus(McuA3967_Handle_t stepper, const unsigned char *name, const McuShell_StdIOType *io);
#endif

/*! \brief Return the RESET pin status
 * \param stepper motor handle
 * \return true if the device is in reset (RESET pin LOW), false if the device is not in reset (RESET pin HIGH)
 */
bool McuA3967_GetReset(McuA3967_Handle_t stepper);

/*! \brief Resets the A3967 using the RESET pin
 * \param stepper motor handle
 * \param reset true if the device should be reset, false otherwise
 */
void McuA3967_SetReset(McuA3967_Handle_t stepper, bool reset);

/*! \brief Returns the status of the A3967 DIR (direction) pin
 * \param stepper motor handle
 * \return true if it is forward (pin HIGH), false otherwise
 */
bool McuA3967_GetDirection(McuA3967_Handle_t stepper);

/*! \brief Sets the DIR (direction) pin of the A3967
 * \param stepper motor handle
 * \param enable true for forward, false otherwise
 */
void McuA3967_SetDirection(McuA3967_Handle_t stepper, bool forward);

/*! \brief Returns the status of the A3967, if it is enabled with the ENABLE pin
 * \param stepper motor handle
 * \return true if driver is enabled (pin LOW), false if driver is disabled (pin HIGH)
 */
bool McuA3967_GetEnable(McuA3967_Handle_t stepper);

/*! \brief Sets the ENABLE pin of the A3967
 * \param stepper motor handle
 * \param enable true to enable the IC with the ENABLE pin
 */
void McuA3967_SetEnable(McuA3967_Handle_t stepper, bool enable);

/*! \brief Sets the SLP (sleep) pin of the A3967
 * \param stepper motor handle
 * \param enable true to put the IC into sleep mode (pin LOW), false otherwise
 */
void McuA3967_SetSleep(McuA3967_Handle_t stepper, bool sleep);

/*! \brief Returns the status of the A3967, if it is in sleep mode or not
 * \param stepper motor handle
 * \return true if driver is in sleep mode (SLP pin LOW), false otherwise
 */
bool McuA3967_GetSleep(McuA3967_Handle_t stepper);

/*! \brief Return the STEP pin status
 * \param stepper motor handle
 * \return true if STEP pin is HIGH, false otherwise
 */
bool McuA3967_GetStep(McuA3967_Handle_t stepper);

/*! \brief Changes the STEP pin
 * \param stepper motor handle
 * \param status boolean value for HIGH or LOW
 */
void McuA3967_SetStep(McuA3967_Handle_t stepper, bool status);

/*!
 * \brief returns the current micro stepping mode
 * \param stepper handle for stepper motor
 * \return 1 (full), 2 (half), 4 (1/4) or 8 (1/8) micro stepping mode
 */
uint8_t McuA3967_GetMicroStepping(McuA3967_Handle_t stepper);

/*!
 * \brief returns the current micro stepping mode
 * \param mode 1 (full), 2 (half), 4 (1/4) or 8 (1/8) micro stepping mode
 */
void McuA3967_SetMicroStepping(McuA3967_Handle_t stepper, uint8_t mode);

/*!
 * \brief performs a step
 */
void McuA3967_MakeStep(McuA3967_Handle_t stepper);


typedef struct {
  McuGPIO_HwPin_t rst;      /*!< reset pin, low active. initial LOW (in reset, driver disabled). Turn HIGH to enable stepper/FET driver */
  McuGPIO_HwPin_t enable;   /*!< enable pin, low active, initial HIGH (disabled). Enables the FET functionality in the motor driver */
  McuGPIO_HwPin_t slp;      /*!< sleep pin, low active, initial LOW (sleep enabled). if low, outputs are disabled and power consumption is minimized */
  McuGPIO_HwPin_t ms1, ms2; /*!< mode select pins, configure micro step resolution, default both set to LOW. See table below */
  McuGPIO_HwPin_t step;     /*!< step pin, initially LOW. Transition from low to high will trigger a motor step */
  McuGPIO_HwPin_t dir;      /*!< direction pin, initially LOW. Either forward or backward */
} McuA3967_Config_t;

/* microstep resolution table:
 * MS1  MS2   Microstep resolution
 * L    L     full step
 * H    L     half step
 * L    H     quarter step
 * H    H     eight step
 */

void McuA3967_GetDefaultConfig(McuA3967_Config_t *config);

McuA3967_Handle_t McuA3967_InitHandle(McuA3967_Config_t *config);

McuA3967_Handle_t McuA3967_DeinitHandle(McuA3967_Handle_t stepper);

void McuA3967_Deinit(void);

void McuA3967_Init(void);

#ifdef __cplusplus
}  /* extern "C" */
#endif

#endif /* MCUA3967_H_ */
