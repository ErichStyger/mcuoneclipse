/*
 * Orientation.h
 *
 *  Created on: 22.12.2018
 *      Author: Erich Styger
 */

#ifndef SOURCES_ORIENTATION_H_
#define SOURCES_ORIENTATION_H_

typedef enum {
  ORI_ORIENTATION_X_UP,  /* tinyK22 up */
  ORI_ORIENTATION_X_DOWN,
  ORI_ORIENTATION_Y_UP,  /* LCD up */
  ORI_ORIENTATION_Y_DOWN,
  ORI_ORIENTATION_Z_UP, /* NeoPixel up */
  ORI_ORIENTATION_Z_DOWN
} ORI_Orientation_e;

ORI_Orientation_e ORI_GetCurrentOrientation(void);

void ORI_Init(void);

#endif /* SOURCES_ORIENTATION_H_ */
