#ifndef SOURCES_COLOR_H_
#define SOURCES_COLOR_H_
//gamma calibration of colors gamma=3.2
extern const uint8_t gamma8[];
#define packColor(rgb) ((uint32_t)gamma8[rgb.g] | (((uint32_t)gamma8[rgb.r])<<8) | (((uint32_t)gamma8[rgb.b])<<16))&0xFFFFFF
typedef struct{
  uint8_t r;
  uint8_t g;
  uint8_t b;
} Color;

typedef uint32_t RGB;
//declare some RGB colors
static Color
White = {255,255,255},
Black = {0,0,0},
Red = {255,0,0},
Green = {0,255,0},
Blue = {0,0,255},
Brown = {0x1b,0x3c,0},
Gray = {192,192,192},
Yellow = {255,255,0},
Crimson = {80,0,0},
Purple = {153,0,255};
#endif /* SOURCES_COLOR_H_ */
