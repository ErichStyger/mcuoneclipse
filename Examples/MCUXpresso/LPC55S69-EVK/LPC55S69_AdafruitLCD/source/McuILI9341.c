/*
 * Copyright (c) 2019, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "McuLib.h"
#include "McuILI9341.h"
#include "McuGPIO.h"
#include "McuSPI.h"
#include "McuWait.h"
#include "McuSPI.h"
#include "McuUtility.h"

/* ILI9341 register and commands */
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

#define SET_CMD_MODE()      McuGPIO_SetLow(McuILI9341_DCPin)
#define SET_DATA_MODE()     McuGPIO_SetHigh(McuILI9341_DCPin)
#define SELECT_DISPLAY()    McuGPIO_SetLow(McuILI9341_CSPin)
#define DESELECT_DISPLAY()  McuGPIO_SetHigh(McuILI9341_CSPin);

static McuGPIO_Handle_t McuILI9341_CSPin;
static McuGPIO_Handle_t McuILI9341_DCPin;

/* Initialization sequence for Adafruit ILI9341 driver, see https://github.com/adafruit/Adafruit_ILI9341/blob/master/Adafruit_ILI9341.cpp */
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

static uint8_t McuILI9341_Write8Cmd(uint8_t cmd) {
  SET_CMD_MODE();
  McuSPI_WriteByte(McuSPI_ConfigLCD, cmd);
  return ERR_OK;
}

uint8_t McuILI9341_WriteCommandArgs(uint8_t cmd, uint8_t *args, uint8_t nofArgs) {
   uint8_t res;

   res = McuILI9341_Write8Cmd(cmd);
   if (res!=ERR_OK) {
     return res;
   }
   SET_DATA_MODE(); /* go back to data mode */
   MCUSPI_WriteBytes(McuSPI_ConfigLCD, args, nofArgs);
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

/* read a byte from the configuration memory (NOT from the display memory) */
static uint8_t spi_readcommand8(uint8_t cmd, uint8_t index, uint8_t *data) {
  SET_CMD_MODE();
  McuSPI_WriteByte(McuSPI_ConfigLCD, 0xD9); /* undocumented code? */
  SET_DATA_MODE();
  McuSPI_WriteByte(McuSPI_ConfigLCD, 0x10+index);
  SET_CMD_MODE();
  McuSPI_WriteByte(McuSPI_ConfigLCD, cmd);
  SET_DATA_MODE();
  McuSPI_ReadByte(McuSPI_ConfigLCD, data);
  return ERR_OK;
}

uint8_t McuILI9341_GetDisplayPowerMode(uint8_t *mode) {
  uint8_t res;

  SELECT_DISPLAY();
  res = spi_readcommand8(MCUILI9341_RDMODE, 0, mode);
  DESELECT_DISPLAY();
  return res;
}

uint8_t McuILI9341_GetDisplayIdentification(uint8_t *manufacurer, uint8_t *driverVersion, uint8_t *driverID) {
  uint8_t res;

  SELECT_DISPLAY();
  res = spi_readcommand8(MCUILI9341_RDID1, 0, manufacurer);
  res = spi_readcommand8(MCUILI9341_RDID2, 0, driverVersion);
  res = spi_readcommand8(MCUILI9341_RDID3, 0, driverID);
  DESELECT_DISPLAY();
  return res;
}

uint8_t McuILI9341_SetWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1) {
  SELECT_DISPLAY();

  SET_CMD_MODE();
  McuSPI_WriteByte(McuSPI_ConfigLCD, MCUILI9341_CASET);
  SET_DATA_MODE();
  McuSPI_WriteByte(McuSPI_ConfigLCD, x0 >> 8);
  McuSPI_WriteByte(McuSPI_ConfigLCD, x0 & 0xFF);         // XSTART
  McuSPI_WriteByte(McuSPI_ConfigLCD, x1 >> 8);
  McuSPI_WriteByte(McuSPI_ConfigLCD, x1 & 0xFF);         // XEND

  SET_CMD_MODE();
  McuSPI_WriteByte(McuSPI_ConfigLCD, MCUILI9341_PASET); // Row addr set
  SET_DATA_MODE();
  McuSPI_WriteByte(McuSPI_ConfigLCD, y0 >> 8);
  McuSPI_WriteByte(McuSPI_ConfigLCD, y0);                // YSTART
  McuSPI_WriteByte(McuSPI_ConfigLCD, y1 >> 8);
  McuSPI_WriteByte(McuSPI_ConfigLCD, y1);                // YEND

  SET_CMD_MODE();
  McuSPI_WriteByte(McuSPI_ConfigLCD, MCUILI9341_RAMWR); // write to RAM}

  DESELECT_DISPLAY();

  return ERR_OK;
}

uint8_t McuILI9341_WritePixelData(uint16_t *pixels, size_t nofPixels) {
  SELECT_DISPLAY();
  SET_DATA_MODE();
  MCUSPI_WriteBytes(McuSPI_ConfigLCD, (uint8_t*)pixels, 2*nofPixels);
  DESELECT_DISPLAY();
  return ERR_OK;
}

uint8_t McuILI9341_DrawPixel(uint16_t x, uint16_t y, uint16_t color) {
#if McuLib_CONFIG_CPU_IS_LITTLE_ENDIAN
  /*! \todo: should change endianess in Interface control (0xF6)? */
  color = (color>>8)|(color<<8); /* swap */
#endif
  McuILI9341_SetWindow(x, y, x, y);
  SELECT_DISPLAY();
  SET_DATA_MODE();
  MCUSPI_WriteBytes(McuSPI_ConfigLCD, (uint8_t*)&color, 2);
  DESELECT_DISPLAY();
  return ERR_OK;
}

uint8_t McuILI9341_DrawBox(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color) {
#if McuLib_CONFIG_CPU_IS_LITTLE_ENDIAN
  /*! \todo: should change endianess in Interface control (0xF6)? */
  color = (color>>8)|(color<<8); /* swap */
#endif
  McuILI9341_SetWindow(x, y, x+w-1, y+h-1);
  SELECT_DISPLAY();
  SET_DATA_MODE();
  for(int i=0; i<w*h; i++) {
    MCUSPI_WriteBytes(McuSPI_ConfigLCD, (uint8_t*)&color, 2);
  }
  DESELECT_DISPLAY();
  return ERR_OK;
}

uint8_t McuILI9341_ClearDisplay(uint16_t color) {
  return McuILI9341_DrawBox(0, 0, MCUILI9341_TFTWIDTH, MCUILI9341_TFTHEIGHT, color);
}

#if MCUILI9341_CONFIG_PARSE_COMMAND_ENABLED
static uint8_t PrintHelp(const McuShell_StdIOType *io) {
  McuShell_SendHelpStr((unsigned char*)"ILI9341", (unsigned char*)"Group of ILI9341 commands\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  help|status", (unsigned char*)"Print help or status information\r\n", io->stdOut);
  return ERR_OK;
}

static uint8_t PrintStatus(const McuShell_StdIOType *io) {
  uint8_t buf[48], res;
  uint8_t man, driver, id, mode;

  McuShell_SendStatusStr((unsigned char*)"ILI9341", (unsigned char*)"\r\n", io->stdOut);

  res = McuILI9341_GetDisplayIdentification(&man, &driver, &id);
  if (res==ERR_OK) {
    McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"man: 0x");
    McuUtility_strcatNum8Hex(buf, sizeof(buf), man);
    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" driver: 0x");
    McuUtility_strcatNum8Hex(buf, sizeof(buf), driver);
    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" ID: 0x");
    McuUtility_strcatNum8Hex(buf, sizeof(buf), id);
    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  } else {
    McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"ERROR\r\n");
  }
  McuShell_SendStatusStr((unsigned char*)"  Version", (const unsigned char*)buf, io->stdOut);

  res = McuILI9341_GetDisplayPowerMode(&mode);
  if (res==ERR_OK) {
    McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"0x");
    McuUtility_strcatNum8Hex(buf, sizeof(buf), mode);
    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  } else {
    McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"ERROR\r\n");
  }
  McuShell_SendStatusStr((unsigned char*)"  Power Mode", (const unsigned char*)buf, io->stdOut);
  return ERR_OK;
}

uint8_t McuILI9341_ParseCommand(const unsigned char *cmd, bool *handled, const McuShell_StdIOType *io) {
  if (McuUtility_strcmp((char*)cmd, McuShell_CMD_HELP)==0 || McuUtility_strcmp((char*)cmd, "ILI9341 help")==0) {
    *handled = TRUE;
    return PrintHelp(io);
  } else if ((McuUtility_strcmp((char*)cmd, McuShell_CMD_STATUS)==0) || (McuUtility_strcmp((char*)cmd, "ILI9341 status")==0)) {
    *handled = TRUE;
    return PrintStatus(io);
  }
  return ERR_OK;
}
#endif /* MCUILI9341_CONFIG_PARSE_COMMAND_ENABLED */

uint8_t McuILI9341_InitLCD(void) {
  uint8_t *p;
  uint8_t res, cmd, numArgs, x;

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
  config.isHighOnInit = true;

  /* initialize TFT CS (is LOW active) */
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
