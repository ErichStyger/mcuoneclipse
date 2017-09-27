/*
 * Laser.c
 *
 *  Created on: 07.12.2014
 *      Author: tastyger
 */

#include "Platform.h"
#if PL_HAS_LASER
#include "Laser.h"
#include "PCA1.h"
#include "Bit_D5.h" /* left laser */

/* left laser connector: X9 ENABLE IOEXPAND5, caution, different for prototype shield!
 * right laser connector: X4 ENABLE IOEXPAND0
 */
#define LASER_RIGHT_BIT_POS  5 /* IO_EXPAND_5 */
#define LASER_LEFT_BIT_POS   0 /* IO_EXPAND_0 */

#define LASER_LEFT_IS_DEAD   1

void LASER_LeftRightStatus(bool *isLeft, bool *isRight) {
  uint8_t val;

  val = PCA1_ReadInput();
#if LASER_LEFT_IS_DEAD
  *isLeft = FALSE;
#else
  *isLeft = (val&(1<<LASER_LEFT_BIT_POS))==0;
#endif
  *isRight = (val&(1<<LASER_RIGHT_BIT_POS))==0;
}

bool LASER_RightStatus(void) {
  uint8_t val;

  val = PCA1_ReadInput();
  return (val&(1<<LASER_RIGHT_BIT_POS))==0;
}

bool LASER_LeftStatus(void) {
#if LASER_LEFT_IS_DEAD
  return FALSE;
#else
  uint8_t val;

  val = PCA1_ReadInput();
  return (val&(1<<LASER_LEFT_BIT_POS))==0;
#endif
}

void LASER_DeInit(void) {
  /* nothing */
}

void LASER_Init(void) {
  /* nothing */
}

#endif /* PL_HAS_LASER */
