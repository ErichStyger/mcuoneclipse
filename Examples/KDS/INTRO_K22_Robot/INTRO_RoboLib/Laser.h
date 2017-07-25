/*
 * Laser.h
 *
 *  Created on: 07.12.2014
 *      Author: tastyger
 */

#ifndef LASER_H_
#define LASER_H_

void LASER_LeftRightStatus(bool *isLeft, bool *isRight);

bool LASER_LeftStatus(void);

bool LASER_RightStatus(void);

void LASER_Init(void);

void LASER_Deinit(void);


#endif /* LASER_H_ */
