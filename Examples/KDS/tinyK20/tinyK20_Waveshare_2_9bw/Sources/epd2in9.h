/**
 *  @filename   :   epd2in9.h
 *  @brief      :   Header file for e-paper library epd2in9.c
 *  @author     :   Yehui from Waveshare
 *  
 *  Copyright (C) Waveshare     September 12 2017
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documnetation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to  whom the Software is
 * furished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS OR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef EPD2IN9_H
#define EPD2IN9_H

#include "fonts.h"

// Display resolution
#define EPD_WIDTH       128
#define EPD_HEIGHT      296

// EPD2IN9 commands
#define DRIVER_OUTPUT_CONTROL                       0x01
#define BOOSTER_SOFT_START_CONTROL                  0x0C
#define GATE_SCAN_START_POSITION                    0x0F
#define DEEP_SLEEP_MODE                             0x10
#define DATA_ENTRY_MODE_SETTING                     0x11
#define SW_RESET                                    0x12
#define TEMPERATURE_SENSOR_CONTROL                  0x1A
#define MASTER_ACTIVATION                           0x20
#define DISPLAY_UPDATE_CONTROL_1                    0x21
#define DISPLAY_UPDATE_CONTROL_2                    0x22
#define WRITE_RAM                                   0x24
#define WRITE_VCOM_REGISTER                         0x2C
#define WRITE_LUT_REGISTER                          0x32
#define SET_DUMMY_LINE_PERIOD                       0x3A
#define SET_GATE_TIME                               0x3B
#define BORDER_WAVEFORM_CONTROL                     0x3C
#define SET_RAM_X_ADDRESS_START_END_POSITION        0x44
#define SET_RAM_Y_ADDRESS_START_END_POSITION        0x45
#define SET_RAM_X_ADDRESS_COUNTER                   0x4E
#define SET_RAM_Y_ADDRESS_COUNTER                   0x4F
#define TERMINATE_FRAME_READ_WRITE                  0xFF

extern const unsigned char lut_full_update[];
extern const unsigned char lut_partial_update[];

typedef struct EPD_t {
  int reset_pin;
  int dc_pin;
  int cs_pin;
  int busy_pin;
  int width;
  int height;
  const unsigned char* lut;
} EPD;

/* Hardware operating functions */
/* public functions */
int  EPD_Init(EPD* epd, const unsigned char* lut);
void EPD_SendCommand(EPD* epd, unsigned char command);
void EPD_SendData(EPD* epd, unsigned char data);
void EPD_WaitUntilIdle(EPD* epd);
void EPD_Reset(EPD* epd);
void EPD_SetFrameMemory(
  EPD* epd,
  const unsigned char* image_buffer,
  int x,
  int y,
  int image_width,
  int image_height
);
void EPD_ClearFrameMemory(EPD* epd, unsigned char color);
void EPD_DisplayFrame(EPD* epd);
void EPD_Sleep(EPD* epd);
void EPD_DelayMs(EPD* epd, unsigned int delay_time);
void EPD_DigitalWrite(EPD* epd, int pin, int value);
int  EPD_DigitalRead(EPD* epd, int pin);

/* private functions */
static void EPD_SetLut(EPD* epd, const unsigned char* lut);
static void EPD_SetMemoryArea(EPD* epd, int x_start, int y_start, int x_end, int y_end);
static void EPD_SetMemoryPointer(EPD* epd, int x, int y);

#endif /* EPD2IN9_H */

/* END OF FILE */
