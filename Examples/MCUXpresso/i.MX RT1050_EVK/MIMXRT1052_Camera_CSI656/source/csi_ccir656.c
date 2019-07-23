/*
 * Copyright (c) 2017, NXP Semiconductors, Inc.
 * All rights reserved.
 *
 * 
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_elcdif.h"
#include "fsl_pxp.h"
#include "fsl_camera.h"
#include "fsl_camera_receiver.h"
#include "fsl_camera_device.h"

#include "board.h"
#include "fsl_debug_console.h"

#include "fsl_gpio.h"
#include "fsl_csi.h"
#include "fsl_csi_camera_adapter.h"
#include "fsl_ov7725.h"
#include "fsl_mt9m114.h"
#include "fsl_iomuxc.h"
#include "pin_mux.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* LCD definition. */
#define APP_ELCDIF LCDIF

#define APP_LCD_HEIGHT 272
#define APP_LCD_WIDTH 480
#define APP_HSW 41
#define APP_HFP 4
#define APP_HBP 8
#define APP_VSW 10
#define APP_VFP 4
#define APP_VBP 2
#define APP_LCD_POL_FLAGS \
    (kELCDIF_DataEnableActiveHigh | kELCDIF_VsyncActiveLow | kELCDIF_HsyncActiveLow | kELCDIF_DriveDataOnRisingClkEdge)

#define APP_LCDIF_DATA_BUS kELCDIF_DataBus16Bit

/* Display. */
#define LCD_DISP_GPIO GPIO1
#define LCD_DISP_GPIO_PIN 2
/* Back light. */
#define LCD_BL_GPIO GPIO2
#define LCD_BL_GPIO_PIN 31

/* Camera definition. */
#define APP_CAMERA_HEIGHT 272
#define APP_CAMERA_WIDTH 480
#define APP_CAMERA_CONTROL_FLAGS (kCAMERA_HrefActiveHigh | kCAMERA_DataLatchOnRisingEdge)

#define APP_PXP PXP

#define APP_CAMERA_OV7725 0
#define APP_CAMERA_MT9M114 1

//#define APP_CAMERA_TYPE APP_CAMERA_MT9M114
#define APP_CAMERA_TYPE APP_CAMERA_OV7725

/* Frame buffer data alignment. */
#define FRAME_BUFFER_ALIGN 64

#ifndef APP_LCDIF_DATA_BUS
#define APP_LCDIF_DATA_BUS kELCDIF_DataBus24Bit
#endif

/* Pixel format YUV422, bytesPerPixel is 2. */
#define APP_BPP 2

#define APP_CAMERA_FRAME_BUFFER_COUNT 4

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
extern camera_device_handle_t cameraDevice;
extern camera_receiver_handle_t cameraReceiver;

/*******************************************************************************
 * Variables
 ******************************************************************************/
AT_NONCACHEABLE_SECTION_ALIGN(
    static uint16_t s_cameraBuffer[APP_CAMERA_FRAME_BUFFER_COUNT][APP_CAMERA_HEIGHT][APP_CAMERA_WIDTH],
    FRAME_BUFFER_ALIGN);
AT_NONCACHEABLE_SECTION_ALIGN(static uint32_t s_lcdBuffer[2][APP_LCD_HEIGHT][APP_LCD_WIDTH], FRAME_BUFFER_ALIGN);

/*******************************************************************************
 * Code
 ******************************************************************************/

extern void CSI_DriverIRQHandler(void);

void CSI_IRQHandler(void)
{
    CSI_DriverIRQHandler();
    __DSB();
}

/* Initialize the LCD_DISP. */
void BOARD_InitLcd(void)
{
    gpio_pin_config_t config = {
        kGPIO_DigitalOutput, 0,
    };

    /* Backlight. */
    config.outputLogic = 1;
    GPIO_PinInit(LCD_BL_GPIO, LCD_BL_GPIO_PIN, &config);
}

void BOARD_InitLcdifPixClock(void)
{
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

/* OV7725 connect to CSI. */
static csi_resource_t csiResource = {
    .csiBase = CSI,
};

static csi_private_data_t csiPrivateData;

camera_receiver_handle_t cameraReceiver = {
    .resource = &csiResource, .ops = &csi_ops, .privateData = &csiPrivateData,
};

static void BOARD_PullCameraResetPin(bool pullUp)
{
    /* Reset pin is connected to DCDC_3V3. */
    return;
}

#if (APP_CAMERA_TYPE == APP_CAMERA_OV7725)
static void BOARD_PullCameraPowerDownPin(bool pullUp)
{
    if (pullUp)
    {
        GPIO_PinWrite(GPIO1, 4, 1);
    }
    else
    {
        GPIO_PinWrite(GPIO1, 4, 0);
    }
}

static ov7725_resource_t ov7725Resource = {
    .i2cSendFunc = BOARD_Camera_I2C_SendSCCB,
    .i2cReceiveFunc = BOARD_Camera_I2C_ReceiveSCCB,
    .pullResetPin = BOARD_PullCameraResetPin,
    .pullPowerDownPin = BOARD_PullCameraPowerDownPin,
    .inputClockFreq_Hz = 24000000,
};

camera_device_handle_t cameraDevice = {
    .resource = &ov7725Resource, .ops = &ov7725_ops,
};
#else
/*
 * MT9M114 camera module has PWDN pin, but the pin is not
 * connected internally, MT9M114 does not have power down pin.
 * The reset pin is connected to high, so the module could
 * not be reseted, so at the begining, use GPIO to let camera
 * release the I2C bus.
 */
static void i2c_release_bus_delay(void)
{
    uint32_t i = 0;
    for (i = 0; i < 0x200; i++)
    {
        __NOP();
    }
}

#define CAMERA_I2C_SCL_GPIO GPIO1
#define CAMERA_I2C_SCL_PIN 16
#define CAMERA_I2C_SDA_GPIO GPIO1
#define CAMERA_I2C_SDA_PIN 17

void BOARD_I2C_ReleaseBus(void)
{
    uint8_t i = 0;
    const gpio_pin_config_t pin_config = {.direction = kGPIO_DigitalOutput, .outputLogic = 1};

    CLOCK_EnableClock(kCLOCK_Iomuxc);

    IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_01_GPIO1_IO17, 0U);
    IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_00_GPIO1_IO16, 0U);

    GPIO_PinInit(CAMERA_I2C_SCL_GPIO, CAMERA_I2C_SCL_PIN, &pin_config);
    GPIO_PinInit(CAMERA_I2C_SDA_GPIO, CAMERA_I2C_SDA_PIN, &pin_config);

    /* Drive SDA low first to simulate a start */
    GPIO_PinWrite(CAMERA_I2C_SDA_GPIO, CAMERA_I2C_SDA_PIN, 0U);
    i2c_release_bus_delay();

    /* Send 9 pulses on SCL and keep SDA high */
    for (i = 0; i < 9; i++)
    {
        GPIO_PinWrite(CAMERA_I2C_SCL_GPIO, CAMERA_I2C_SCL_PIN, 0U);
        i2c_release_bus_delay();

        GPIO_PinWrite(CAMERA_I2C_SDA_GPIO, CAMERA_I2C_SDA_PIN, 1U);
        i2c_release_bus_delay();

        GPIO_PinWrite(CAMERA_I2C_SCL_GPIO, CAMERA_I2C_SCL_PIN, 1U);
        i2c_release_bus_delay();
        i2c_release_bus_delay();
    }

    /* Send stop */
    GPIO_PinWrite(CAMERA_I2C_SCL_GPIO, CAMERA_I2C_SCL_PIN, 0U);
    i2c_release_bus_delay();

    GPIO_PinWrite(CAMERA_I2C_SDA_GPIO, CAMERA_I2C_SDA_PIN, 0U);
    i2c_release_bus_delay();

    GPIO_PinWrite(CAMERA_I2C_SCL_GPIO, CAMERA_I2C_SCL_PIN, 1U);
    i2c_release_bus_delay();

    GPIO_PinWrite(CAMERA_I2C_SDA_GPIO, CAMERA_I2C_SDA_PIN, 1U);
    i2c_release_bus_delay();
}

static mt9m114_resource_t mt9m114Resource = {
    .i2cSendFunc = BOARD_Camera_I2C_Send,
    .i2cReceiveFunc = BOARD_Camera_I2C_Receive,
    .pullResetPin = BOARD_PullCameraResetPin,
    .inputClockFreq_Hz = 24000000,
};

camera_device_handle_t cameraDevice = {
    .resource = &mt9m114Resource, .ops = &mt9m114_ops,
};
#endif

void BOARD_InitCameraResource(void)
{
    BOARD_Camera_I2C_Init();

    /* CSI MCLK select 24M. */
    /*
     * CSI clock source:
     *
     * 00 derive clock from osc_clk (24M)
     * 01 derive clock from PLL2 PFD2
     * 10 derive clock from pll3_120M
     * 11 derive clock from PLL3 PFD1
     */
    CLOCK_SetMux(kCLOCK_CsiMux, 0);
    /*
     * CSI clock divider:
     *
     * 000 divide by 1
     * 001 divide by 2
     * 010 divide by 3
     * 011 divide by 4
     * 100 divide by 5
     * 101 divide by 6
     * 110 divide by 7
     * 111 divide by 8
     */
    CLOCK_SetDiv(kCLOCK_CsiDiv, 0);

    /*
     * For RT1050, there is not dedicate clock gate for CSI MCLK, it use CSI
     * clock gate.
     */

    /* Set the pins for CSI reset and power down. */
    gpio_pin_config_t pinConfig = {
        kGPIO_DigitalOutput, 1,
    };

    GPIO_PinInit(GPIO1, 4, &pinConfig);
}



/*!
 * @brief Main function
 */
int main(void)
{
    uint32_t fullCameraBufferAddr;

    /*
     * LCD inactive frame buffer index.
     * At begining, LCD buffer 0 is active buffer, LCD buffer 1 is inactive buffer.
     */
    uint8_t lcdInactiveFbIdx = 1;

    BOARD_ConfigMPU();
    BOARD_InitPins();
    BOARD_InitDEBUG_UARTPins();
    BOARD_InitSDRAMPins();
#if (APP_CAMERA_TYPE != APP_CAMERA_OV7725)
    BOARD_I2C_ReleaseBus();
#endif
    BOARD_InitCSIPins();
    BOARD_InitLCDPins();
    BOARD_BootClockRUN();
    BOARD_InitLcdifPixClock();
    BOARD_InitDebugConsole();
    BOARD_InitLcd();
    BOARD_InitCameraResource();

    memset(s_lcdBuffer, 0, sizeof(s_lcdBuffer));

    PRINTF("CSI CCIR656 example start...\r\n");

    /*
     * Configure the LCDIF.
     */
    const elcdif_rgb_mode_config_t lcdConfig = {
        .panelWidth = APP_LCD_WIDTH,
        .panelHeight = APP_LCD_HEIGHT,
        .hsw = APP_HSW,
        .hfp = APP_HFP,
        .hbp = APP_HBP,
        .vsw = APP_VSW,
        .vfp = APP_VFP,
        .vbp = APP_VBP,
        .bufferAddr = (uint32_t)s_lcdBuffer[0],
        .polarityFlags = APP_LCD_POL_FLAGS,
        .pixelFormat = kELCDIF_PixelFormatXRGB8888,
        .dataBus = APP_LCDIF_DATA_BUS,
    };

    ELCDIF_RgbModeInit(APP_ELCDIF, &lcdConfig);

    const camera_config_t cameraConfig = {
        .pixelFormat = kVIDEO_PixelFormatYUYV,
        .bytesPerPixel = APP_BPP,
        .resolution = FSL_VIDEO_RESOLUTION(APP_CAMERA_WIDTH, APP_CAMERA_HEIGHT),
        .frameBufferLinePitch_Bytes = APP_CAMERA_WIDTH * APP_BPP,
        .interface = kCAMERA_InterfaceCCIR656,
        .controlFlags = APP_CAMERA_CONTROL_FLAGS,
        .framePerSec = 30,
    };

    /*
     * Configure the PXP for color space conversion.
     */
    PXP_Init(APP_PXP);

    pxp_ps_buffer_config_t psBufferConfig = {
        .pixelFormat = kPXP_PsPixelFormatUYVY1P422,
        .swapByte = false,
        .bufferAddrU = 0U,
        .bufferAddrV = 0U,
        .pitchBytes = APP_CAMERA_WIDTH * APP_BPP,
    };

    PXP_SetProcessSurfaceBackGroundColor(APP_PXP, 0U);

    PXP_SetProcessSurfacePosition(APP_PXP, 0U, 0U, APP_CAMERA_WIDTH - 1U, APP_CAMERA_HEIGHT - 1U);

    /* Disable AS. */
    PXP_SetAlphaSurfacePosition(APP_PXP, 0xFFFFU, 0xFFFFU, 0U, 0U);

    /* Output config. */
    pxp_output_buffer_config_t outputBufferConfig = {
        .pixelFormat = kPXP_OutputPixelFormatRGB888,
        .interlacedMode = kPXP_OutputProgressive,
        .buffer1Addr = 0U,
        .pitchBytes = APP_LCD_WIDTH * 4,
        .width = APP_LCD_WIDTH,
        .height = APP_LCD_HEIGHT,
    };

    PXP_SetCsc1Mode(APP_PXP, kPXP_Csc1YCbCr2RGB);
    PXP_EnableCsc1(APP_PXP, true);

    /*
     * Configure the camera.
     */
    CAMERA_RECEIVER_Init(&cameraReceiver, &cameraConfig, NULL, NULL);

    CAMERA_DEVICE_Init(&cameraDevice, &cameraConfig);

    CAMERA_DEVICE_Start(&cameraDevice);

    /* Submit the empty frame buffers to buffer queue. */
    for (uint32_t i = 0; i < APP_CAMERA_FRAME_BUFFER_COUNT; i++)
    {
        CAMERA_RECEIVER_SubmitEmptyBuffer(&cameraReceiver, (uint32_t)(s_cameraBuffer[i]));
    }

    CAMERA_RECEIVER_Start(&cameraReceiver);

    ELCDIF_RgbModeStart(APP_ELCDIF);

    while (1)
    {
        /* Wait to get the full frame buffer to show. */
        while (kStatus_Success != CAMERA_RECEIVER_GetFullBuffer(&cameraReceiver, &fullCameraBufferAddr))
        {
        }

        /* Convert the camera input picture to RGB format. */
        psBufferConfig.bufferAddr = fullCameraBufferAddr;
        PXP_SetProcessSurfaceBufferConfig(APP_PXP, &psBufferConfig);

        outputBufferConfig.buffer0Addr = (uint32_t)s_lcdBuffer[lcdInactiveFbIdx];
        PXP_SetOutputBufferConfig(APP_PXP, &outputBufferConfig);

        PXP_Start(APP_PXP);

        /* Wait for PXP process complete. */
        while (!(kPXP_CompleteFlag & PXP_GetStatusFlags(APP_PXP)))
        {
        }
        PXP_ClearStatusFlags(APP_PXP, kPXP_CompleteFlag);

        ELCDIF_ClearInterruptStatus(APP_ELCDIF, kELCDIF_CurFrameDone);
        /* Set the new frame to LCD. */
        ELCDIF_SetNextBufferAddr(APP_ELCDIF, (uint32_t)s_lcdBuffer[lcdInactiveFbIdx]);

        /* Return the camera buffer to camera queue. */
        CAMERA_RECEIVER_SubmitEmptyBuffer(&cameraReceiver, fullCameraBufferAddr);

        /* Wait for the new set LCD frame buffer active. */
        while (!(kELCDIF_CurFrameDone & ELCDIF_GetInterruptStatus(APP_ELCDIF)))
        {
        }

        lcdInactiveFbIdx ^= 1;
    }
}
