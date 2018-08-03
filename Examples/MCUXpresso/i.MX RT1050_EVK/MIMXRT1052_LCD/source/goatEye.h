#ifndef GOATEYE_H_
#define GOATEYE_H_

#include <stdint.h>

#define GOAT_SCLERA_WIDTH  128
#define GOAT_SCLERA_HEIGHT 128
extern const uint16_t goat_sclera[GOAT_SCLERA_HEIGHT][GOAT_SCLERA_WIDTH];

#define GOAT_IRIS_MAP_WIDTH  402
#define GOAT_IRIS_MAP_HEIGHT 64
extern const uint16_t goat_iris[GOAT_IRIS_MAP_HEIGHT][GOAT_IRIS_MAP_WIDTH];

#define GOAT_SCREEN_WIDTH  128
#define GOAT_SCREEN_HEIGHT 128
extern const uint8_t goat_upper[GOAT_SCREEN_HEIGHT][GOAT_SCREEN_WIDTH];
extern const uint8_t goat_lower[GOAT_SCREEN_HEIGHT][GOAT_SCREEN_WIDTH];

#define GOAT_IRIS_WIDTH  128
#define GOAT_IRIS_HEIGHT 128
extern const uint16_t goat_polar[GOAT_IRIS_HEIGHT][GOAT_IRIS_WIDTH];

#endif /* GOATEYE_H_ */
