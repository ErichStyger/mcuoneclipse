/*
 * interpolation.h
 *
 *  Created on: 10.11.2018
 *      Author: Erich Styger
 *      Source: https://github.com/adafruit/Adafruit_AMG88xx/tree/master/examples/thermal_cam_interpolate
 */

#ifndef SOURCES_INTERPOLATION_H_
#define SOURCES_INTERPOLATION_H_

#include <stdint.h>

void interpolate_image(float *src, uint8_t src_rows, uint8_t src_cols,
                       float *dest, uint8_t dest_rows, uint8_t dest_cols);
float get_point(float *p, uint8_t rows, uint8_t cols, int8_t x, int8_t y);
void set_point(float *p, uint8_t rows, uint8_t cols, int8_t x, int8_t y, float f);
void get_adjacents_1d(float *src, float *dest, uint8_t rows, uint8_t cols, int8_t x, int8_t y);
void get_adjacents_2d(float *src, float *dest, uint8_t rows, uint8_t cols, int8_t x, int8_t y);
float cubicInterpolate(float p[], float x);
float bicubicInterpolate(float p[], float x, float y);



#endif /* SOURCES_INTERPOLATION_H_ */
