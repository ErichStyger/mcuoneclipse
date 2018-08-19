/*
 * touch.c
 *
 *  Created on: 03.08.2018
 *      Author: Erich Styger
 */

#include "Platform.h"
#if PL_CONFIG_USE_TOUCH
#include "touch.h"
#include "fsl_lpi2c.h"
#include "fsl_ft5406_rt.h"

/* Macros for the touch touch controller. */
#define BOARD_TOUCH_I2C LPI2C1

/* Select USB1 PLL (480 MHz) as master lpi2c clock source */
#define LPI2C_CLOCK_SOURCE_SELECT (0U)
/* Clock divider for master lpi2c clock source */
#define LPI2C_CLOCK_SOURCE_DIVIDER (5U)

#define BOARD_TOUCH_I2C_CLOCK_FREQ ((CLOCK_GetFreq(kCLOCK_Usb1PllClk) / 8) / (LPI2C_CLOCK_SOURCE_DIVIDER + 1U))
#define BOARD_TOUCH_I2C_BAUDRATE 100000U

/* Touch driver handle. */
static ft5406_rt_handle_t touchHandle;

void TOUCH_Init(void) {
    lpi2c_master_config_t masterConfig = {0};
    /*
    * masterConfig.debugEnable = false;
    * masterConfig.ignoreAck = false;
    * masterConfig.pinConfig = kLPI2C_2PinOpenDrain;
    * masterConfig.baudRate_Hz = 100000U;
    * masterConfig.busIdleTimeout_ns = 0;
    * masterConfig.pinLowTimeout_ns = 0;
    * masterConfig.sdaGlitchFilterWidth_ns = 0;
    * masterConfig.sclGlitchFilterWidth_ns = 0;
    */
    LPI2C_MasterGetDefaultConfig(&masterConfig);

    /* Change the default baudrate configuration */
    masterConfig.baudRate_Hz = BOARD_TOUCH_I2C_BAUDRATE;

    /* Initialize the LPI2C master peripheral */
    LPI2C_MasterInit(BOARD_TOUCH_I2C, &masterConfig, BOARD_TOUCH_I2C_CLOCK_FREQ);

    /* Initialize the touch handle. */
    FT5406_RT_Init(&touchHandle, BOARD_TOUCH_I2C);
}

void TOUCH_Deinit(void) {
    LPI2C_MasterDeinit(BOARD_TOUCH_I2C);
}

int TOUCH_Poll(bool *pressed, int *x, int *y) {
    touch_event_t touch_event;
    int touch_x, touch_y;

    if (kStatus_Success != FT5406_RT_GetSingleTouch(&touchHandle, &touch_event, &touch_x, &touch_y)) {
        return 0;
    } else if (touch_event != kTouch_Reserved) {
    	*pressed = (touch_event == kTouch_Down) || (touch_event == kTouch_Contact);
    	*x = touch_y;
    	*y = touch_x;
        return 1;
    }
    return 0;
}
#endif /* PL_CONFIG_USE_TOUCH */
