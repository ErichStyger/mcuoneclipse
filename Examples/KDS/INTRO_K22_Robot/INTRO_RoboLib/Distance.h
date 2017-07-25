/*
 * Distance.h
 *
 *  Created on: Jun 23, 2013
 *      Author: Erich Styger
 */

#ifndef DISTANCE_H_
#define DISTANCE_H_

#include "Platform.h"
#if PL_HAS_DISTANCE_SENSOR
#include "CLS1.h"

uint8_t DIST_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io);

typedef enum {
  DIST_SENSOR_FRONT = (1<<0),
  DIST_SENSOR_REAR = (1<<1),
  DIST_SENSOR_LEFT = (1<<2),
  DIST_SENSOR_RIGHT = (1<<3),
} DIST_Sensor;

int16_t DIST_GetDistance(DIST_Sensor sensor);

#if PL_HAS_SIDE_DISTANCE
bool DIST_5cmLeftOn(void);
bool DIST_5cmRightOn(void);
bool DIST_10cmLeftOn(void);
bool DIST_10cmRightOn(void);
#endif

#if PL_HAS_FRONT_DISTANCE
#define DIST_IR_LEFT   (1<<2)
#define DIST_IR_MIDDLE (1<<1)
#define DIST_IR_RIGHT  (1<<0)
/*!
 * \brief Return front sensor status
 * \return Bit pattern, 0b111 means echo on all sensors, 0b100 only on left, 0b010 only on middle, 0b001 only on right, and so on.
 */
uint8_t DIST_GetSensorBitsLeft(void);
uint8_t DIST_GetSensorBitsMiddle(void);
uint8_t DIST_GetSensorBitsRight(void);
#endif

uint8_t DIST_SpeedIntoObstacle(int speedL, int speedR);
uint8_t DIST_MotorDrivingIntoObstacle(void);
uint8_t DIST_CheckSurrounding(void);
bool DIST_DriveToCenter(void);
bool DIST_NearFrontObstacle(int16_t distance);
bool DIST_NearRearObstacle(int distance);
bool DIST_NearLeftObstacle(int distance);
bool DIST_NearRightObstacle(int distance);

/*!
 * \brief Driver initialization.
 */
void DIST_Init(void);

/*!
 * \brief Driver de-initialization.
 */
void DIST_Deinit(void);

#endif /* PL_HAS_DISTANCE_SENSOR */

#endif /* DISTANCE_H_ */
