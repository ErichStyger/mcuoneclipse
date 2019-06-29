/*
#include <McuSPI.h>
 * McuIL9341.c
 *
 *  Created on: 29.06.2019
 *      Author: Erich Styger
 */

#include "McuLib.h"
#include "McuIL9341.h"
#include "McuGPIO.h"
#include "McuSPI.h"

/* IL9341 register and commands */

#define MCUIL9341_TFTWIDTH   240      /*!< ILI9341 max TFT width */
#define MCUIL9341_TFTHEIGHT  320      /*!< ILI9341 max TFT height */

#define MCUIL9341_NOP        0x00     /*!< No-op register */
#define MCUIL9341_SWRESET    0x01     /*!< Software reset register */
#define MCUIL9341_RDDID      0x04     /*!< Read display identification information */
#define MCUIL9341_RDDST      0x09     /*!< Read Display Status */

#define MCUIL9341_SLPIN      0x10     /*!< Enter Sleep Mode */
#define MCUIL9341_SLPOUT     0x11     /*!< Sleep Out */
#define MCUIL9341_PTLON      0x12     /*!< Partial Mode ON */
#define MCUIL9341_NORON      0x13     /*!< Normal Display Mode ON */

#define MCUIL9341_RDMODE     0x0A     /*!< Read Display Power Mode */
#define MCUIL9341_RDMADCTL   0x0B     /*!< Read Display MADCTL */
#define MCUIL9341_RDPIXFMT   0x0C     /*!< Read Display Pixel Format */
#define MCUIL9341_RDIMGFMT   0x0D     /*!< Read Display Image Format */
#define MCUIL9341_RDSELFDIAG 0x0F     /*!< Read Display Self-Diagnostic Result */

#define MCUIL9341_INVOFF     0x20     /*!< Display Inversion OFF */
#define MCUIL9341_INVON      0x21     /*!< Display Inversion ON */
#define MCUIL9341_GAMMASET   0x26     /*!< Gamma Set */
#define MCUIL9341_DISPOFF    0x28     /*!< Display OFF */
#define MCUIL9341_DISPON     0x29     /*!< Display ON */

#define MCUIL9341_CASET      0x2A     /*!< Column Address Set */
#define MCUIL9341_PASET      0x2B     /*!< Page Address Set */
#define MCUIL9341_RAMWR      0x2C     /*!< Memory Write */
#define MCUIL9341_RAMRD      0x2E     /*!< Memory Read */

#define MCUIL9341_PTLAR      0x30     /*!< Partial Area */
#define MCUIL9341_VSCRDEF    0x33     /*!< Vertical Scrolling Definition */
#define MCUIL9341_MADCTL     0x36     /*!< Memory Access Control */
#define MCUIL9341_VSCRSADD   0x37     /*!< Vertical Scrolling Start Address */
#define MCUIL9341_PIXFMT     0x3A     /*!< COLMOD: Pixel Format Set */

#define MCUIL9341_FRMCTR1    0xB1     /*!< Frame Rate Control (In Normal Mode/Full Colors) */
#define MCUIL9341_FRMCTR2    0xB2     /*!< Frame Rate Control (In Idle Mode/8 colors) */
#define MCUIL9341_FRMCTR3    0xB3     /*!< Frame Rate control (In Partial Mode/Full Colors) */
#define MCUIL9341_INVCTR     0xB4     /*!< Display Inversion Control */
#define MCUIL9341_DFUNCTR    0xB6     /*!< Display Function Control */

#define MCUIL9341_PWCTR1     0xC0     /*!< Power Control 1 */
#define MCUIL9341_PWCTR2     0xC1     /*!< Power Control 2 */
#define MCUIL9341_PWCTR3     0xC2     /*!< Power Control 3 */
#define MCUIL9341_PWCTR4     0xC3     /*!< Power Control 4 */
#define MCUIL9341_PWCTR5     0xC4     /*!< Power Control 5 */
#define MCUIL9341_VMCTR1     0xC5     /*!< VCOM Control 1 */
#define MCUIL9341_VMCTR2     0xC7     /*!< VCOM Control 2 */

#define MCUIL9341_RDID1      0xDA     /*!< Read ID 1 */
#define MCUIL9341_RDID2      0xDB     /*!< Read ID 2 */
#define MCUIL9341_RDID3      0xDC     /*!< Read ID 3 */
#define MCUIL9341_RDID4      0xDD     /*!< Read ID 4 */

#define MCUIL9341_GMCTRP1    0xE0     /*!< Positive Gamma Correction */
#define MCUIL9341_GMCTRN1    0xE1     /*!< Negative Gamma Correction */


/* TFT_CS_5V: LSPI_HS_SSEL1, PIO1_1 */
#define MCUIL9341_CS_GPIO   GPIO
#define MCUIL9341_CS_PORT   1U
#define MCUIL9341_CS_PIN    1U

/* TFT_DC_5V: PIO1_5_GPIO_ARD, PIO1_5 */
#define MCUIL9341_DC_GPIO   GPIO
#define MCUIL9341_DC_PORT   1U
#define MCUIL9341_DC_PIN    5U

static McuGPIO_Handle_t McuIL9341_CSPin;
static McuGPIO_Handle_t McuIL9341_DCPin;

static uint8_t spi_write(uint8_t *data, size_t nofBytes) {
  McuGPIO_Low(McuIL9341_CSPin);
  while(nofBytes>0) {
    McuSPI_WriteByte(*data);
    data++;
    nofBytes--;
  }
  McuGPIO_High(McuIL9341_CSPin);
  return ERR_OK;
}

uint8_t McuIL9341_Write8(uint8_t data) {
  McuGPIO_High(McuIL9341_DCPin);
  return spi_write(&data, 1);
}

uint8_t McuIL9341_Write8Cmd(uint8_t cmd) {
  McuGPIO_Low(McuIL9341_DCPin);
  return spi_write(&cmd, 1);
}

uint8_t McuIL9341_SoftReset(void) {
  return McuIL9341_Write8Cmd(MCUIL9341_SWRESET);
}

uint8_t McuIL9341_InitLCD(void) {
  return McuIL9341_SoftReset();
}

void McuIL9341_Init(void) {
  McuGPIO_Config_t config;

  McuGPIO_GetDefaultConfig(&config);
  config.isInput = false;
  config.isLowOnInit = false;

  /* initialize CS (is LOW active) */
  config.hw.pin = MCUIL9341_CS_PIN;
  config.hw.port = MCUIL9341_CS_PORT;
  config.hw.gpio = MCUIL9341_CS_GPIO;
  McuIL9341_CSPin = McuGPIO_InitGPIO(&config);

  /* initialize DC: LOW: command, HIGH: Data */
  config.hw.pin = MCUIL9341_DC_PIN;
  config.hw.port = MCUIL9341_DC_PORT;
  config.hw.gpio = MCUIL9341_DC_GPIO;
  McuIL9341_DCPin = McuGPIO_InitGPIO(&config);
}
