/*
 * dragonEye.h
 *
 *  Created on: 20.07.2018
 *      Author: Erich Styger
 */

#ifndef DRAGONEYE_H_
#define DRAGONEYE_H_

#include <stdint.h>

#define DRAGON_SCLERA_WIDTH  160
#define DRAGON_SCLERA_HEIGHT 160
extern const uint16_t dragon_sclera[DRAGON_SCLERA_HEIGHT][DRAGON_SCLERA_WIDTH];

#define DRAGON_IRIS_MAP_WIDTH  512
#define DRAGON_IRIS_MAP_HEIGHT 80
extern const uint16_t dragon_iris[DRAGON_IRIS_MAP_HEIGHT][DRAGON_IRIS_MAP_WIDTH];

#define DRAGON_SCREEN_WIDTH  128
#define DRAGON_SCREEN_HEIGHT 128
extern const uint8_t dragon_upper[DRAGON_SCREEN_HEIGHT][DRAGON_SCREEN_WIDTH];
extern const uint8_t dragon_lower[DRAGON_SCREEN_HEIGHT][DRAGON_SCREEN_WIDTH];

#define DRAGON_IRIS_WIDTH  160
#define DRAGON_IRIS_HEIGHT 160
extern const uint16_t dragon_polar[DRAGON_IRIS_HEIGHT][DRAGON_IRIS_WIDTH];

#endif /* DRAGONEYE_H_ */
