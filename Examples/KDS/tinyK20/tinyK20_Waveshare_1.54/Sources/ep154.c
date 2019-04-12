/*****************************************************************************
* | File      	:	EPD_1in54.c
* | Author      :   Waveshare team
* | Function    :   Electronic paper driver
* | Info        :
*----------------
* |	This version:   V2.0
* | Date        :   2018-10-30
* | Info        :
* 1.Remove:ImageBuff[EPD_HEIGHT * EPD_WIDTH / 8]
* 2.Change:EPD_Display(UBYTE *Image)
*   Need to pass parameters: pointer to cached data
* 3.Change:
*   EPD_RST -> EPD_ResetPin_PIN
*   EPD_DC -> EPD_DcPin_PIN
*   EPD_CS -> EPD_CsPin_PIN
*   EPD_BUSY -> EPD_BUSY_PIN
#
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
/*
 * ep154.c
 *
 *  Created on: 23.03.2019
 *      Author: Patrick Loosli
 */
#include "ep154.h"
#include "ResetPin.h"
#include "CSPin.h"
#include "BusyPin.h"
#include "ResetPin.h"
#include "DcPin.h"
#include "SM1.h"
#include "WAIT1.h"

const unsigned char lut_full_update[] = {
    0x02, 0x02, 0x01, 0x11, 0x12, 0x12, 0x22, 0x22,
    0x66, 0x69, 0x69, 0x59, 0x58, 0x99, 0x99, 0x88,
    0x00, 0x00, 0x00, 0x00, 0xF8, 0xB4, 0x13, 0x51,
    0x35, 0x51, 0x51, 0x19, 0x01, 0x00
};

const unsigned char lut_partial_update[] = {
    0x10, 0x18, 0x18, 0x08, 0x18, 0x18, 0x08, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x13, 0x14, 0x44, 0x12,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
/**
 *  @brief: module reset.
 *          often used to awaken the module in deep sleep,
 *          see Epd::Sleep();
 */
/******************************************************************************
function :	Software reset
parameter:
******************************************************************************/
static void EPD_Reset(void)
{
	ResetPin_SetVal();
	WAIT1_Waitms(200);
    ResetPin_ClrVal();
    WAIT1_Waitms(200);
    ResetPin_SetVal();
    WAIT1_Waitms(200);
}
/******************************************************************************
function :	send command
parameter:
     Reg : Command register
******************************************************************************/
static void EPD_SendCommand(unsigned int Reg)
{
	DcPin_ClrVal();
	CsPin_ClrVal();
	SM1_SendChar(Reg);
	CsPin_SetVal();
}
/******************************************************************************
function :	send data
parameter:
    Data : Write data
******************************************************************************/
static void EPD_SendData(unsigned int Reg)
{
	DcPin_SetVal();
	CsPin_ClrVal();
	SM1_SendChar(Reg);
	CsPin_SetVal();
}
/******************************************************************************
function :	Wait until the busy_pin goes LOW
parameter:
******************************************************************************/
void EPD_WaitUntilIdle(void)
{
    while(BusyPin_GetVal()== TRUE) {      //LOW: idle, HIGH: busy
        WAIT1_Waitms(100);
    }
}

/******************************************************************************
function :	Setting the display window
parameter:
******************************************************************************/
static void EPD_SetWindows(unsigned int Xstart, unsigned int Ystart, unsigned int Xend, unsigned int Yend)
{
    EPD_SendCommand(SET_RAM_X_ADDRESS_START_END_POSITION);
    EPD_SendData((Xstart >> 3) & 0xFF);
    EPD_SendData((Xend >> 3) & 0xFF);

    EPD_SendCommand(SET_RAM_Y_ADDRESS_START_END_POSITION);
    EPD_SendData(Ystart & 0xFF);
    EPD_SendData((Ystart >> 8) & 0xFF);
    EPD_SendData(Yend & 0xFF);
    EPD_SendData((Yend >> 8) & 0xFF);
}

/******************************************************************************
function :	Set Cursor
parameter:
******************************************************************************/
static void EPD_SetCursor(unsigned int Xstart, unsigned int Ystart)
{
    EPD_SendCommand(SET_RAM_X_ADDRESS_COUNTER);
    EPD_SendData((Xstart >> 3) & 0xFF);

    EPD_SendCommand(SET_RAM_Y_ADDRESS_COUNTER);
    EPD_SendData(Ystart & 0xFF);
    EPD_SendData((Ystart >> 8) & 0xFF);

}

/******************************************************************************
function :	Turn On Display
parameter:
******************************************************************************/
static void EPD_TurnOnDisplay(void)
{
    EPD_SendCommand(DISPLAY_UPDATE_CONTROL_2);
    EPD_SendData(0xC4);
    EPD_SendCommand(MASTER_ACTIVATION);
    EPD_SendCommand(TERMINATE_FRAME_READ_WRITE);

    EPD_WaitUntilIdle();
}

/******************************************************************************
function :	Initialize the e-Paper register
parameter:
******************************************************************************/
unsigned int EPD_Init(const unsigned char* lut)
{
    EPD_Reset();

    EPD_SendCommand(DRIVER_OUTPUT_CONTROL);
    EPD_SendData((EPD_HEIGHT - 1) & 0xFF);
    EPD_SendData(((EPD_HEIGHT - 1) >> 8) & 0xFF);
    EPD_SendData(0x00);                     // GD = 0; SM = 0; TB = 0;
    EPD_SendCommand(BOOSTER_SOFT_START_CONTROL);
    EPD_SendData(0xD7);
    EPD_SendData(0xD6);
    EPD_SendData(0x9D);
    EPD_SendCommand(WRITE_VCOM_REGISTER);
    EPD_SendData(0xA8);                     // VCOM 7C
    EPD_SendCommand(SET_DUMMY_LINE_PERIOD);
    EPD_SendData(0x1A);                     // 4 dummy lines per gate
    EPD_SendCommand(SET_GATE_TIME);
    EPD_SendData(0x08);                     // 2us per line
    EPD_SendCommand(DATA_ENTRY_MODE_SETTING);
    EPD_SendData(0x03);

    //set the look-up table register
    EPD_SendCommand(WRITE_LUT_REGISTER);
    for (unsigned int i = 0; i < 30; i++) {
        EPD_SendData(lut[i]);
    }
    return 0;
}

/******************************************************************************
function :	Clear screen
parameter:
******************************************************************************/
void EPD_Clear(void)
{
	unsigned int Width, Height;
    Width = (EPD_WIDTH % 8 == 0)? (EPD_WIDTH / 8 ): (EPD_WIDTH / 8 + 1);
    Height = EPD_HEIGHT;
    EPD_SetWindows(0, 0, EPD_WIDTH, EPD_HEIGHT);
    for (unsigned int j = 0; j < Height; j++) {
        EPD_SetCursor(0, j);
        EPD_SendCommand(WRITE_RAM);
        for (unsigned int i = 0; i < Width; i++) {
            EPD_SendData(0XFF);
        }
    }
    EPD_TurnOnDisplay();
}

/******************************************************************************
function :	Sends the image buffer in RAM to e-Paper and displays
parameter:
******************************************************************************/
void EPD_Display(uint8_t *Image)
{
	unsigned int Width, Height;
    Width = (EPD_WIDTH % 8 == 0)? (EPD_WIDTH / 8 ): (EPD_WIDTH / 8 + 1);
    Height = EPD_HEIGHT;

    unsigned int Addr = 0;
    // UDOUBLE Offset = ImageName;
    EPD_SetWindows(0, 0, EPD_WIDTH, EPD_HEIGHT);
    for (unsigned int j = 0; j < Height; j++) {
        EPD_SetCursor(0, j);
        EPD_SendCommand(WRITE_RAM);
        for (unsigned int i = 0; i < Width; i++) {
            Addr = i + j * Width;
            EPD_SendData(Image[Addr]);
        }
    }
    EPD_TurnOnDisplay();
}

/******************************************************************************
function :	Enter sleep mode
parameter:
******************************************************************************/
void EPD_Sleep(void)
{
    EPD_SendCommand(DEEP_SLEEP_MODE);
    EPD_SendData(0x01);
    // EPD_WaitUntilIdle();
}

void SetFrameMemory(const unsigned char* image_buffer, int x, int y, int image_width,
		int image_height) {
    int x_end;
    int y_end;

    if (image_buffer == NULL || x < 0 || image_width < 0 ||y < 0 || image_height < 0) {
        return;
    }
    /* x point must be the multiple of 8 or the last 3 bits will be ignored */
    x &= 0xF8;
    image_width &= 0xF8;
    if (x + image_width >= EPD_WIDTH) {
        x_end = EPD_WIDTH - 1;
    } else {
        x_end = x + image_width - 1;
    }
    if (y + image_height >= EPD_HEIGHT) {
        y_end = EPD_HEIGHT - 1;
    } else {
        y_end = y + image_height - 1;
    }
    EPD_SetWindows(x, y, x_end, y_end);
    EPD_SetCursor(x, y);
    EPD_SendCommand(WRITE_RAM);
    /* send the image data */
    for (int j = 0; j < y_end - y + 1; j++) {
        for (int i = 0; i < (x_end - x + 1) / 8; i++) {
        	//Addr = x + y * image_height;
        	//Paint.Image[Addr] = (unsigned char)image_buffer[Addr];
        	EPD_SendData(image_buffer[i + j * (image_width / 8)]);
        }
    }
    EPD_SendCommand(DISPLAY_UPDATE_CONTROL_2);
    EPD_SendData(0xC4);
    EPD_SendCommand(MASTER_ACTIVATION);
    EPD_SendCommand(TERMINATE_FRAME_READ_WRITE);
    EPD_WaitUntilIdle();
}


