/*
 * Platform.h
 *
 *  Created on: 13.04.2019
 *      Author: Erich Styger
 */

#ifndef PLATFORM_H_
#define PLATFORM_H_

#define PL_CONFIG_USE_RASPBERRY     (0) /* board used with Raspberry Pi */
#define PL_CONFIG_USE_BUTTONS       (1) /* using buttons (navigation switch) */
#define PL_CONFIG_USE_KBI           (1 && PL_CONFIG_USE_BUTTONS) /* using interrupts for buttons */
#define PL_CONFIG_USE_I2C           (1) /* if I2C is enabled */
#define PL_CONFIG_USE_SHT31         (1 && PL_CONFIG_USE_I2C) /* if using SHT31 sensor */
#define PL_CONFIG_USE_OLED          (1 && PL_CONFIG_USE_I2C) /* if using OLED */
#define PL_CONFIG_USE_UPS           (1 && PL_CONFIG_USE_I2C && PL_CONFIG_USE_RASPBERRY) /* if using UPS HAT */
#define PL_CONFIG_USE_GATEWAY       (1 && PL_CONFIG_USE_RASPBERRY) /* if implementing UART gateway to Raspberry Pi */
#define PL_CONFIG_USE_RASPY_UART    (1 && PL_CONFIG_USE_RASPBERRY) /* uses UART to Raspy as interface for joystick, led and sensor values */
#define PL_CONFIG_USE_SHUTDOWN      (1 && PL_CONFIG_USE_RASPBERRY) /* if implementing shutdown for Raspberry Pi */
#define PL_CONFIG_USE_SHELL         (1) /* if shell is enabled, uses RTT */
#define PL_CONFIG_USE_GUI           (1 && PL_CONFIG_USE_OLED && PL_CONFIG_USE_BUTTONS) /* use LittlevGL */
#define PL_CONFIG_USE_TOASTER       (1 && PL_CONFIG_USE_OLED) /* flying toaster screensaver */
#define PL_CONFIG_USE_GUI_KEY_NAV   (1 && PL_CONFIG_USE_BUTTONS && PL_CONFIG_USE_GUI)
#define PL_CONFIG_USE_USB_CDC       (1)

#define PL_CONFIG_USE_HW_I2C        USE_HW_I2C /* defined in IncludeMcuLibConfig.h */

/* defines for sensor.c */
#define PL_CONFIG_HAS_TSL2561       (0)
#define PL_CONFIG_HAS_MMA8451       (0)
#define PL_CONFIG_HAS_AMG8833       (0)
#define PL_CONFIG_HAS_RTC_DS3231    (0)

void PL_Init(void);
void PL_Deinit(void);

#endif /* PLATFORM_H_ */
