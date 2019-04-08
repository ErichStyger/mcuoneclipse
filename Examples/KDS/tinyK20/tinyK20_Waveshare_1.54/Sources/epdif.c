/**
 *  @filename   :   epdif.c
 *  @brief      :   Implements EPD interface functions
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

#include "epdif.h"
#include "main.h"
#include "WAIT1.h"
#include "ResetPin.h"
#include "BusyPin.h"
#include "DcPin.h"
#include "CsPin.h"
#include "SM1.h"

void EpdDigitalWriteCallback(int pin_num, int value) {
  if (value==HIGH) {
    switch(pin_num) {
      case CS_PIN: CsPin_SetVal(); break;
      case RST_PIN: ResetPin_SetVal(); break;
      case DC_PIN: DcPin_SetVal(); break;
      //case BUSY_PIN: BusyPin_SetVal(); break;
      }
  } else {
    switch(pin_num) {
      case CS_PIN: CsPin_ClrVal(); break;
      case RST_PIN: ResetPin_ClrVal(); break;
      case DC_PIN: DcPin_ClrVal(); break;
      //case BUSY_PIN: BusyPin_ClrVal(); break;
      }
   }
}

int EpdDigitalReadCallback(int pin_num) {
  switch(pin_num) {
    case CS_PIN: return CsPin_GetVal()!=0 ? HIGH:LOW; break;
    case RST_PIN: return ResetPin_GetVal()!=0 ? HIGH:LOW; break;
    case DC_PIN: return DcPin_GetVal()!=0 ? HIGH:LOW; break;
    case BUSY_PIN: return BusyPin_GetVal()!=0 ? HIGH:LOW; break;
  }
  return LOW; /* error case */
}

void EpdDelayMsCallback(unsigned int delaytime) {
  WAIT1_Waitms(delaytime);
}

static void SendByte(uint8_t val) {
  uint8_t ch;

  while(SM1_GetCharsInTxBuf()!=0) {} /* wait until tx is empty */
  while(SM1_SendChar(val)!=ERR_OK) {} /* send character */
  while(SM1_GetCharsInTxBuf()!=0) {} /* wait until data has been sent */
  while(SM1_GetCharsInRxBuf()==0) {} /* wait until we receive data */
  while(SM1_RecvChar(&ch)!=ERR_OK) {} /* get data */
}

void EpdSpiTransferCallback(unsigned char data) {
  CsPin_ClrVal();
  SendByte(data);
  CsPin_SetVal();
}

int EpdInitCallback(void) {
  return 0;
}

