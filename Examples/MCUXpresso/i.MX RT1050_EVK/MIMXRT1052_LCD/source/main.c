/*
 * The Clear BSD License
 * Copyright (c) 2017, NXP Semiconductors, Inc.
 * All rights reserved.
 *
 * 
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted (subject to the limitations in the disclaimer below) provided
 *  that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of the copyright holder nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * NO EXPRESS OR IMPLIED LICENSES TO ANY PARTY'S PATENT RIGHTS ARE GRANTED BY THIS LICENSE.
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include "Platform.h"
#include "fsl_common.h"
#include "fsl_elcdif.h"
#include "fsl_debug_console.h"

#include "pin_mux.h"
#include "board.h"
#include "fsl_gpio.h"
#include "clock_config.h"

#include "GDisp1.h"
#include "FreeRTOS.h"
#include "task.h"

#if PL_CONFIG_EYE_DEMO
  #include "uncannyEyes.h"
#endif
#include "LED.h"

#if PL_CONFIG_USE_GUI
  #include "lv.h"
  #include "lvgl.h"
  #include "gui.h"
  #include "touch.h"
#endif

/*******************************************************************************
 * Definitions
 ******************************************************************************/

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
volatile bool s_frameDone = false;

AT_NONCACHEABLE_SECTION_ALIGN(uint16_t s_frameBuffer[2][APP_IMG_HEIGHT][APP_IMG_WIDTH], FRAME_BUFFER_ALIGN);

/*******************************************************************************
 * Code
 ******************************************************************************/
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
        .panelWidth = APP_IMG_WIDTH,
        .panelHeight = APP_IMG_HEIGHT,
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

static void AppTask(void *p) {
    /* Clear the frame buffer. */
    memset(s_frameBuffer, 0, sizeof(s_frameBuffer));
    ELCDIF_EnableInterrupts(APP_ELCDIF, kELCDIF_CurFrameDoneInterruptEnable);
    ELCDIF_RgbModeStart(APP_ELCDIF);
#if PL_CONFIG_EYE_DEMO
    EYES_Init();
    GDisp1_UpdateFull(); /* show black screen */
    EYES_ShowLogo();
	for(;;) {
		//vTaskDelay(pdMS_TO_TICKS(100));
    	EYES_Run();
	}
#elif PL_CONFIG_USE_GUI
	vTaskDelay(pdMS_TO_TICKS(100));
	GUI_Init();
    for(;;) {
    	LED_Toggle();
    	vTaskDelay(pdMS_TO_TICKS(500));
	}
#else
    for(;;) {
		vTaskDelay(pdMS_TO_TICKS(10));
	}
#endif
}

/*!
 * @brief Main function
 */
int main(void) {
    BOARD_ConfigMPU();
    BOARD_InitPins();
    BOARD_InitI2C1Pins();
    BOARD_InitSemcPins();
    BOARD_BootClockRUN();
    BOARD_InitLcdifPixelClock();
    BOARD_InitDebugConsole();
    BOARD_InitLcd();
#if PL_CONFIG_USE_GUI
    TOUCH_Init();
#endif
    APP_ELCDIF_Init();
    BOARD_EnableLcdInterrupt();
    LED_Init();

//    PRINTF("LCD example start...\r\n");
    xTaskCreate(/* The function that implements the task. */
                AppTask,
                /* Text name for the task, just to help debugging. */
                "App",
                /* The size (in words) of the stack that should be created
                for the task. */
                configMINIMAL_STACK_SIZE + 800,
                /* A parameter that can be passed into the task.  Not used
                in this simple demo. */
                NULL,
                /* The priority to assign to the task.  tskIDLE_PRIORITY
                (which is 0) is the lowest priority.  configMAX_PRIORITIES - 1
                is the highest priority. */
                1,
                /* Used to obtain a handle to the created task.  Not used in
                this simple demo, so set to NULL. */
                NULL);
    vTaskStartScheduler();
    for(;;) {} /* should never get here */
}
