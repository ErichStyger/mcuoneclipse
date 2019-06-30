/*
 * McuILI9341.c
 *
 *  Created on: 29.06.2019
 *      Author: Erich Styger
 */

#include "McuLib.h"
#include "McuILI9341.h"
#include "McuGPIO.h"
#include "McuSPI.h"
#include "McuWait.h"
#include "McuSPI.h"

/* ILI9341 register and commands */

#define MCUILI9341_TFTWIDTH   240      /*!< ILI9341 max TFT width */
#define MCUILI9341_TFTHEIGHT  320      /*!< ILI9341 max TFT height */

#define MCUILI9341_NOP        0x00     /*!< No-op register */
#define MCUILI9341_SWRESET    0x01     /*!< Software reset register */
#define MCUILI9341_RDDID      0x04     /*!< Read display identification information */
#define MCUILI9341_RDDST      0x09     /*!< Read Display Status */

#define MCUILI9341_SLPIN      0x10     /*!< Enter Sleep Mode */
#define MCUILI9341_SLPOUT     0x11     /*!< Sleep Out */
#define MCUILI9341_PTLON      0x12     /*!< Partial Mode ON */
#define MCUILI9341_NORON      0x13     /*!< Normal Display Mode ON */

#define MCUILI9341_RDMODE     0x0A     /*!< Read Display Power Mode */
#define MCUILI9341_RDMADCTL   0x0B     /*!< Read Display MADCTL */
#define MCUILI9341_RDPIXFMT   0x0C     /*!< Read Display Pixel Format */
#define MCUILI9341_RDIMGFMT   0x0D     /*!< Read Display Image Format */
#define MCUILI9341_RDSELFDIAG 0x0F     /*!< Read Display Self-Diagnostic Result */

#define MCUILI9341_INVOFF     0x20     /*!< Display Inversion OFF */
#define MCUILI9341_INVON      0x21     /*!< Display Inversion ON */
#define MCUILI9341_GAMMASET   0x26     /*!< Gamma Set */
#define MCUILI9341_DISPOFF    0x28     /*!< Display OFF */
#define MCUILI9341_DISPON     0x29     /*!< Display ON */

#define MCUILI9341_CASET      0x2A     /*!< Column Address Set */
#define MCUILI9341_PASET      0x2B     /*!< Page Address Set */
#define MCUILI9341_RAMWR      0x2C     /*!< Memory Write */
#define MCUILI9341_RAMRD      0x2E     /*!< Memory Read */

#define MCUILI9341_PTLAR      0x30     /*!< Partial Area */
#define MCUILI9341_VSCRDEF    0x33     /*!< Vertical Scrolling Definition */
#define MCUILI9341_MADCTL     0x36     /*!< Memory Access Control */
#define MCUILI9341_VSCRSADD   0x37     /*!< Vertical Scrolling Start Address */
#define MCUILI9341_PIXFMT     0x3A     /*!< COLMOD: Pixel Format Set */

#define MCUILI9341_FRMCTR1    0xB1     /*!< Frame Rate Control (In Normal Mode/Full Colors) */
#define MCUILI9341_FRMCTR2    0xB2     /*!< Frame Rate Control (In Idle Mode/8 colors) */
#define MCUILI9341_FRMCTR3    0xB3     /*!< Frame Rate control (In Partial Mode/Full Colors) */
#define MCUILI9341_INVCTR     0xB4     /*!< Display Inversion Control */
#define MCUILI9341_DFUNCTR    0xB6     /*!< Display Function Control */

#define MCUILI9341_PWCTR1     0xC0     /*!< Power Control 1 */
#define MCUILI9341_PWCTR2     0xC1     /*!< Power Control 2 */
#define MCUILI9341_PWCTR3     0xC2     /*!< Power Control 3 */
#define MCUILI9341_PWCTR4     0xC3     /*!< Power Control 4 */
#define MCUILI9341_PWCTR5     0xC4     /*!< Power Control 5 */
#define MCUILI9341_VMCTR1     0xC5     /*!< VCOM Control 1 */
#define MCUILI9341_VMCTR2     0xC7     /*!< VCOM Control 2 */

#define MCUILI9341_RDID1      0xDA     /*!< Read ID 1 */
#define MCUILI9341_RDID2      0xDB     /*!< Read ID 2 */
#define MCUILI9341_RDID3      0xDC     /*!< Read ID 3 */
#define MCUILI9341_RDID4      0xDD     /*!< Read ID 4 */

#define MCUILI9341_GMCTRP1    0xE0     /*!< Positive Gamma Correction */
#define MCUILI9341_GMCTRN1    0xE1     /*!< Negative Gamma Correction */


/* TFT_CS_5V: LSPI_HS_SSEL1, PIO1_1 */
#define MCUILI9341_CS_GPIO   GPIO
#define MCUILI9341_CS_PORT   1U
#define MCUILI9341_CS_PIN    1U

/* TFT_DC_5V: PIO1_5_GPIO_ARD, PIO1_5 */
#define MCUILI9341_DC_GPIO   GPIO
#define MCUILI9341_DC_PORT   1U
#define MCUILI9341_DC_PIN    5U

#define SET_CMD_MODE()      McuGPIO_Low(McuILI9341_DCPin)
#define SET_DATA_MODE()     McuGPIO_High(McuILI9341_DCPin)
#define SELECT_DISPLAY()    McuGPIO_Low(McuILI9341_CSPin)
#define DESELECT_DISPLAY()  McuGPIO_High(McuILI9341_CSPin);

static McuGPIO_Handle_t McuILI9341_CSPin;
static McuGPIO_Handle_t McuILI9341_DCPin;

/* initialisation sequence for Adafruit ILI9341 driver, see https://github.com/mongoose-os-libs/ili9341-spi/blob/master/src/mgos_ili9341.c */
static const uint8_t initlist[] = {
  0xEF, 3, 0x03, 0x80, 0x02,
  0xCF, 3, 0x00, 0xC1, 0x30,
  0xED, 4, 0x64, 0x03, 0x12, 0x81,
  0xE8, 3, 0x85, 0x00, 0x78,
  0xCB, 5, 0x39, 0x2C, 0x00, 0x34, 0x02,
  0xF7, 1, 0x20,
  0xEA, 2, 0x00, 0x00,
  MCUILI9341_PWCTR1  , 1, 0x23,              // Power control VRH[5:0]
  MCUILI9341_PWCTR2  , 1, 0x10,              // Power control SAP[2:0];BT[3:0]
  MCUILI9341_VMCTR1  , 2, 0x3e, 0x28,        // VCM control
  MCUILI9341_VMCTR2  , 1, 0x86,              // VCM control2
  MCUILI9341_MADCTL  , 1, 0x48,              // Memory Access Control
  MCUILI9341_VSCRSADD, 1, 0x00,              // Vertical scroll zero
  MCUILI9341_PIXFMT  , 1, 0x55,
  MCUILI9341_FRMCTR1 , 2, 0x00, 0x18,
  MCUILI9341_DFUNCTR , 3, 0x08, 0x82, 0x27,  // Display Function Control
  0xF2, 1, 0x00,                             // 3Gamma Function Disable
  MCUILI9341_GAMMASET , 1, 0x01,             // Gamma curve selected
  MCUILI9341_GMCTRP1 , 15, 0x0F, 0x31, 0x2B, 0x0C, 0x0E, 0x08, // Set Gamma
    0x4E, 0xF1, 0x37, 0x07, 0x10, 0x03, 0x0E, 0x09, 0x00,
  MCUILI9341_GMCTRN1 , 15, 0x00, 0x0E, 0x14, 0x03, 0x11, 0x07, // Set Gamma
    0x31, 0xC1, 0x48, 0x08, 0x0F, 0x0C, 0x31, 0x36, 0x0F,
  MCUILI9341_SLPOUT  , 0x80,                 // Exit Sleep
  MCUILI9341_DISPON  , 0x80,                 // Display on
  0x00                                       // Sentinel at the end of the list
};

static uint8_t spi_write(uint8_t *data, size_t nofBytes) {
//  McuGPIO_Low(McuILI9341_CSPin);
  while(nofBytes>0) {
    McuSPI_WriteByte(*data);
    data++;
    nofBytes--;
  }
//  McuGPIO_High(McuILI9341_CSPin);
  return ERR_OK;
}

static uint8_t McuILI9341_Write8Data(uint8_t data) {
  SET_DATA_MODE();
  return spi_write(&data, 1);
}

static uint8_t McuILI9341_Write8Cmd(uint8_t cmd) {
  SET_CMD_MODE();
  return spi_write(&cmd, 1);
}

uint8_t McuILI9341_WriteCommandArgs(uint8_t cmd, uint8_t *args, uint8_t nofArgs) {
   uint8_t res;

   res = McuILI9341_Write8Cmd(cmd);
   if (res!=ERR_OK) {
     return res;
   }
   SET_DATA_MODE(); /* go back to data mode */
   spi_write(args, nofArgs);
   return ERR_OK;
}

uint8_t McuILI9341_SoftReset(void) {
  uint8_t res;

  SELECT_DISPLAY();
  res = McuILI9341_Write8Cmd(MCUILI9341_SWRESET);
  DESELECT_DISPLAY();
  McuWait_WaitOSms(5); /* need to wait 5 ms according data sheet */
  return res;
}

uint8_t McuILI9341_InvertDisplay(bool invert) {
  uint8_t res;

  SELECT_DISPLAY();
  res = McuILI9341_Write8Cmd(invert?MCUILI9341_INVON:MCUILI9341_INVOFF);
  DESELECT_DISPLAY();
  return res;
}

uint8_t McuILI9341_DisplayOn(bool on) {
  uint8_t res;

  SELECT_DISPLAY();
  res = McuILI9341_Write8Cmd(on?MCUILI9341_DISPON:MCUILI9341_DISPOFF);
  DESELECT_DISPLAY();
  return res;
}

uint8_t McuILI9341_GetDisplayIdentification(uint8_t *manufacurer, uint8_t *driverVersion, uint8_t *driverID) {
  uint8_t res;

  SELECT_DISPLAY();
  res = McuILI9341_Write8Cmd(MCUILI9341_RDID1);
//  SET_DATA_MODE(); /* go back to data mode */
//  McuSPI_WriteByte(0xff); /* dummy */
  McuSPI_ReadByte(manufacurer);

  res = McuILI9341_Write8Cmd(MCUILI9341_RDID2);
//  SET_DATA_MODE(); /* go back to data mode */
  McuSPI_ReadByte(driverVersion);

  res = McuILI9341_Write8Cmd(MCUILI9341_RDID3);
//  SET_DATA_MODE(); /* go back to data mode */
  McuSPI_ReadByte(driverID);
  DESELECT_DISPLAY();
  return res;
}

uint8_t McuILI9341_SetWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1) {
#if 0
  do {
    ili9341_spi_write8_cmd(ILI9341_CASET); // Column addr set
    ili9341_spi_write8(x0 >> 8);
    ili9341_spi_write8(x0 & 0xFF);         // XSTART
    ili9341_spi_write8(x1 >> 8);
    ili9341_spi_write8(x1 & 0xFF);         // XEND
    ili9341_spi_write8_cmd(ILI9341_PASET); // Row addr set
    ili9341_spi_write8(y0 >> 8);
    ili9341_spi_write8(y0);                // YSTART
    ili9341_spi_write8(y1 >> 8);
    ili9341_spi_write8(y1);                // YEND
    ili9341_spi_write8_cmd(ILI9341_RAMWR); // write to RAM}
  } while(0);
#endif
  return ERR_OK;
}

uint8_t McuILI9341_DrawPixel(uint16_t x, uint16_t y, uint16_t color) {
  SET_DATA_MODE();
  return spi_write((uint8_t*)&color, 2);
}

uint8_t McuILI9341_InitLCD(void) {
  uint8_t *p;
  uint8_t res, cmd, numArgs, x;

  SET_CMD_MODE();
  SELECT_DISPLAY();
  McuSPI_WriteByte(MCUILI9341_SLPOUT); /* exit sleep */
  McuWait_WaitOSms(120);

  McuSPI_WriteByte(MCUILI9341_DISPON); /* turn on */
  McuWait_WaitOSms(5);

  McuSPI_WriteByte(MCUILI9341_DISPOFF); /* turn off */
  McuWait_WaitOSms(5);

  DESELECT_DISPLAY();

  McuILI9341_DisplayOn(true);
  McuILI9341_DisplayOn(false);

  for(;;) {

  }
  /* first do a soft reset */
  res = McuILI9341_SoftReset();
  if (res!=ERR_OK) {
    return res;
  }
  SELECT_DISPLAY();
  p = (uint8_t*)initlist;
  while(*p != 0) { /* check for sentinel */
    cmd = *p++;
    x = *p++;
    numArgs = x&0x7F; /* mask out delay bit */
    res = McuILI9341_WriteCommandArgs(cmd, p, numArgs);
    if (res!=ERR_OK) {
      DESELECT_DISPLAY();
      return res;
    }
    p += numArgs;
    if (x&0x80) { /* if delay bit is set */
      McuWait_WaitOSms(150);
    }
  }
  DESELECT_DISPLAY();
  return ERR_OK;
}

void McuILI9341_Init(void) {
  McuGPIO_Config_t config;

  McuGPIO_GetDefaultConfig(&config);
  config.isInput = false;
  config.isLowOnInit = false;

  /* initialize CS (is LOW active) */
  config.hw.pin = MCUILI9341_CS_PIN;
  config.hw.port = MCUILI9341_CS_PORT;
  config.hw.gpio = MCUILI9341_CS_GPIO;
  McuILI9341_CSPin = McuGPIO_InitGPIO(&config);

  /* initialize DC: LOW: command, HIGH: Data */
  config.hw.pin = MCUILI9341_DC_PIN;
  config.hw.port = MCUILI9341_DC_PORT;
  config.hw.gpio = MCUILI9341_DC_GPIO;
  McuILI9341_DCPin = McuGPIO_InitGPIO(&config);
}
