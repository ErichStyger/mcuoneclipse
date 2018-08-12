/*
 * lcd.c
 *
 *  Created on: 08.08.2018
 *      Author: Erich Styger
 */

#include "Platform.h"
#if PL_CONFIG_USE_LCD
#include "lcd.h"
#include "GDisp1.h"
#include "fsl_elcdif.h"
#include "fsl_gpio.h"
#include <string.h> /* for memset() */
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define APP_ELCDIF   LCDIF

#define APP_HSW 41
#define APP_HFP 4
#define APP_HBP 8
#define APP_VSW 10
#define APP_VFP 4
#define APP_VBP 2
#define APP_POL_FLAGS \
    (kELCDIF_DataEnableActiveHigh | kELCDIF_VsyncActiveLow | kELCDIF_HsyncActiveLow | kELCDIF_DriveDataOnRisingClkEdge)

/* Display. */
#define LCD_DISP_GPIO GPIO1
#define LCD_DISP_GPIO_PIN 2
/* Back light. */
#define LCD_BL_GPIO GPIO2
#define LCD_BL_GPIO_PIN 31

/* Frame buffer data alignment, for better performance, the LCDIF frame buffer should be 64B align. */
#define FRAME_BUFFER_ALIGN 64

#ifndef APP_LCDIF_DATA_BUS
#define APP_LCDIF_DATA_BUS kELCDIF_DataBus24Bit
#endif

/*******************************************************************************
 * Variables
 ******************************************************************************/
static volatile bool s_frameDone = false;

#if PL_CONFIG_USE_LCD_DOUBLE_BUFFER
  #define LCD_NOF_BUFFERS (2)
#else
  #define LCD_NOF_BUFFERS (1)
#endif

static AT_NONCACHEABLE_SECTION_ALIGN(uint16_t s_frameBuffer[LCD_NOF_BUFFERS][LCD_DISPLAY_HEIGHT][LCD_DISPLAY_WIDTH], FRAME_BUFFER_ALIGN);

/*******************************************************************************
 * Code
 ******************************************************************************/
void LCD_SwitchDisplayBuffer(int idx) {
#if PL_CONFIG_USE_LCD_DOUBLE_BUFFER
    ELCDIF_SetNextBufferAddr(APP_ELCDIF, (uint32_t)s_frameBuffer[idx]);
    s_frameDone = false;
    /* Wait for previous frame complete. */
    while (!s_frameDone) {
    	vTaskDelay(pdMS_TO_TICKS(1)); /* wait */
    }
#else
    s_frameDone = false;
#endif
}

void LCD_SetPixel(int idx, int x, int y, int color) {
#if PL_CONFIG_USE_LCD_DOUBLE_BUFFER
	s_frameBuffer[idx][y][x] = color;
#else
	s_frameBuffer[0][y][x] = color;
#endif
}


static void APP_LCDIF_IRQHandler(void) {
    uint32_t intStatus;

    intStatus = ELCDIF_GetInterruptStatus(APP_ELCDIF);
    ELCDIF_ClearInterruptStatus(APP_ELCDIF, intStatus);
    if (intStatus & kELCDIF_CurFrameDone) {
        s_frameDone = true;
    }
/* Add for ARM errata 838869, affects Cortex-M4, Cortex-M4F Store immediate overlapping
  exception return operation might vector to incorrect interrupt */
#if defined __CORTEX_M && (__CORTEX_M == 4U)
    __DSB();
#endif
}

void LCDIF_IRQHandler(void) {
    APP_LCDIF_IRQHandler();
}

/* Enable interrupt. */
static void BOARD_EnableLcdInterrupt(void) {
    EnableIRQ(LCDIF_IRQn);
}

/* Initialize the LCD_DISP. */
static void BOARD_InitLcd(void) {
    volatile uint32_t i = 0x100U;

    gpio_pin_config_t config = {
        kGPIO_DigitalOutput, 0,
    };
    /* Reset the LCD. */
    GPIO_PinInit(LCD_DISP_GPIO, LCD_DISP_GPIO_PIN, &config);
    GPIO_PinWrite(LCD_DISP_GPIO, LCD_DISP_GPIO_PIN, 0);
    while (i--)    {
    }
    GPIO_PinWrite(LCD_DISP_GPIO, LCD_DISP_GPIO_PIN, 1);
    /* Backlight. */
    config.outputLogic = 1;
    GPIO_PinInit(LCD_BL_GPIO, LCD_BL_GPIO_PIN, &config);
}

static void BOARD_InitLcdifPixelClock(void) {
    /*
     * The desired output frame rate is 60Hz. So the pixel clock frequency is:
     * (480 + 41 + 4 + 18) * (272 + 10 + 4 + 2) * 60 = 9.2M.
     * Here set the LCDIF pixel clock to 9.3M.
     */

    /*
     * Initialize the Video PLL.
     * Video PLL output clock is OSC24M * (loopDivider + (denominator / numerator)) / postDivider = 93MHz.
     */
    clock_video_pll_config_t config = {
        .loopDivider = 31, .postDivider = 8, .numerator = 0, .denominator = 0,
    };

    CLOCK_InitVideoPll(&config);
    /*
     * 000 derive clock from PLL2
     * 001 derive clock from PLL3 PFD3
     * 010 derive clock from PLL5
     * 011 derive clock from PLL2 PFD0
     * 100 derive clock from PLL2 PFD1
     * 101 derive clock from PLL3 PFD1
     */
    CLOCK_SetMux(kCLOCK_LcdifPreMux, 2);
    CLOCK_SetDiv(kCLOCK_LcdifPreDiv, 4);
    CLOCK_SetDiv(kCLOCK_LcdifDiv, 1);
}

static void APP_ELCDIF_Init(void) {
    const elcdif_rgb_mode_config_t config = {
        .panelWidth = LCD_DISPLAY_WIDTH,
        .panelHeight = LCD_DISPLAY_HEIGHT,
        .hsw = APP_HSW,
        .hfp = APP_HFP,
        .hbp = APP_HBP,
        .vsw = APP_VSW,
        .vfp = APP_VFP,
        .vbp = APP_VBP,
        .polarityFlags = APP_POL_FLAGS,
        .bufferAddr = (uint32_t)s_frameBuffer[0],
        .pixelFormat = kELCDIF_PixelFormatRGB565, //kELCDIF_PixelFormatXRGB8888,
        .dataBus = APP_LCDIF_DATA_BUS,
    };
    ELCDIF_RgbModeInit(APP_ELCDIF, &config);
}

void LCD_Init(void) {
    BOARD_InitLcdifPixelClock();
    BOARD_InitLcd();
    APP_ELCDIF_Init();
    BOARD_EnableLcdInterrupt();
    /* Clear the frame buffer. */
    memset(s_frameBuffer, 0, sizeof(s_frameBuffer));
    ELCDIF_EnableInterrupts(APP_ELCDIF, kELCDIF_CurFrameDoneInterruptEnable);
    ELCDIF_RgbModeStart(APP_ELCDIF);
}
#endif /* PL_CONFIG_USE_LCD */
