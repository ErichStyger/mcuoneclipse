/*****************************************************************************
* | File      	:   DEV_Config.c
* | Author      :   Waveshare team
* | Function    :   Hardware underlying interface
* | Info        :
*                Used to shield the underlying layers of each master 
*                and enhance portability
*----------------
* |	This version:   V2.0
* | Date        :   2018-10-30
* | Info        :
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documnetation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to  whom the Software is
# furished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS OR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
#
******************************************************************************/
#include "DEV_Config.h"
#include "SM1.h"
#include "CsPin.h"
#include "ResetPin.h"
#include "DcPin.h"
#include "BusyPin.h"

static void SendByte(uint8_t val) {
  uint8_t ch;

  while(SM1_GetCharsInTxBuf()!=0) {} /* wait until tx is empty */
  while(SM1_SendChar(val)!=ERR_OK) {} /* send character */
  while(SM1_GetCharsInTxBuf()!=0) {} /* wait until data has been sent */
  while(SM1_GetCharsInRxBuf()==0) {} /* wait until we receive data */
  while(SM1_RecvChar(&ch)!=ERR_OK) {} /* get data */
}

void DEV_SPI_WriteByte(UBYTE value) {
  SendByte(value);
}

int DEV_Digital_Read(EPD_Pins pin) {
  switch(pin) {
    case EPD_CS_PIN: return CsPin_GetVal()!=0 ? 1:0; break;
    case EPD_RST_PIN: return ResetPin_GetVal()!=0 ? 1:0; break;
    case EPD_DC_PIN: return DcPin_GetVal()!=0 ? 1:0; break;
    case EPD_BUSY_PIN: return BusyPin_GetVal()!=0 ? 1:0; break;
  }
  return 0; /* error case */
}

void DEV_Digital_Write(EPD_Pins pin, int val) {
  if (val) {
    switch(pin) {
      case EPD_CS_PIN: CsPin_SetVal(); break;
      case EPD_RST_PIN: ResetPin_SetVal(); break;
      case EPD_DC_PIN: DcPin_SetVal(); break;
      //case EPD_BUSY_PIN: BusyPin_SetVal(); break;
      }
  } else {
    switch(pin) {
      case EPD_CS_PIN: CsPin_ClrVal(); break;
      case EPD_RST_PIN: ResetPin_ClrVal(); break;
      case EPD_DC_PIN: DcPin_ClrVal(); break;
      //case EPD_BUSY_PIN: BusyPin_ClrVal(); break;
      }
   }
}


