/**
 *  @filename   :   epdif.h
 *  @brief      :   Header file of epdif.c providing EPD interface functions
 *                  Users have to implement all the functions in epdif.cpp
 *  @author     :   Yehui from Waveshare
 *
 *  Copyright (C) Waveshare     July 7 2017
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

#ifndef EPDIF_H
#define EPDIF_H

//#include "stm32f1xx_hal.h"

// Pin definition
#define CS_PIN           0
#define RST_PIN          1
#define DC_PIN           2
#define BUSY_PIN         3

// Pin level definition
#define LOW             0
#define HIGH            1

typedef struct {
  //GPIO_TypeDef* port;
  int pin;
} EPD_Pin;

int  EpdInitCallback(void);
void EpdDigitalWriteCallback(int pin, int value);
int  EpdDigitalReadCallback(int pin);
void EpdDelayMsCallback(unsigned int delaytime);
void EpdSpiTransferCallback(unsigned char data);

#endif /* EPDIF_H */
