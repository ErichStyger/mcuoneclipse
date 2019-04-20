/*
 * Platform.h
 *
 *  Created on: 13.04.2019
 *      Author: Erich Styger
 */

#ifndef PLATFORM_H_
#define PLATFORM_H_

#define PL_CONFIG_USE_I2C           (1) /* if I2C is enabled */
#define PL_CONFIG_USE_SHT31         (1 && PL_CONFIG_USE_I2C) /* if using SHT31 sensor */
#define PL_CONFIG_USE_OLED          (1 && PL_CONFIG_USE_I2C) /* if using OLED */
#define PL_CONFIG_USE_UPS           (1 && PL_CONFIG_USE_I2C) /* if using UPS HAT */
#define PL_CONFIG_USE_GATEWAY       (1) /* if implementing UART gateway to Raspberry Pi */
#define PL_CONFIG_USE_SHUTDOWN      (1) /* if implementing shutdown for Raspberry Pi */
#define PL_CONFIG_HAS_SHELL         (0) /* if shell is enabled */
#define PL_CONFIG_USE_LVGL          (1 && PL_CONFIG_USE_OLED) /* use LittlevGL */

#define PL_CONFIG_HAS_KEYS          (1)
#define PL_CONFIG_HAS_GUI_KEY_NAV   (1 && PL_CONFIG_HAS_KEYS)

void PL_Init(void);
void PL_Deinit(void);

#endif /* PLATFORM_H_ */
