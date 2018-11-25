/*
 * Platform.h
 *
 *  Created on: 18.04.2018
 *      Author: Erich Styger
 */

#ifndef SOURCES_PLATFORM_H_
#define SOURCES_PLATFORM_H_

#define PL_CONFIG_HAS_I2C_SPY     (0)
#define PL_CONFIG_HAS_SEGGER_RTT  (1)
#define PL_CONFIG_HAS_USB_CDC     (0)
#define PL_CONFIG_HAS_TSL2561     (0) /* ambient light sensor */
#define PL_CONFIG_HAS_SGP30       (0) /* air quality sensor */
#define PL_CONFIG_HAS_RTC_DS3231  (0)
#define PL_CONFIG_HAS_SPI         (1)
#define PL_CONFIG_HAS_SSD1351     (1 && PL_CONFIG_HAS_SPI)
#define PL_CONFIG_HAS_GUI         (0 && PL_CONFIG_HAS_SSD1351)
#define PL_CONFIG_HAS_KEYS        (0)
#define PL_CONFIG_HAS_GUI_KEY_NAV (0 && PL_CONFIG_HAS_GUI && PL_CONFIG_HAS_KEYS) /* GUI touchless navigation */
#define PL_CONFIG_HAS_MMA8451     (0) /* accelerometer */
#define PL_CONFIG_HAS_SHT31       (0) /* temperature/humidity */
#define PL_CONFIG_HAS_SD_CARD     (0 && PL_CONFIG_HAS_SPI)
#define PL_CONFIG_HAS_NEO_PIXEL   (1) /* WS2812B */
#define PL_CONFIG_HAS_AMG8833     (0) /* thermal sensor */

/* NEO Applications, only one can be active! */
#define PL_CONFIG_HAS_NEO_SHADOW_BOX    (1 & PL_CONFIG_HAS_NEO_PIXEL)
#define PL_CONFIG_HAS_NEO_HOUR_GLASS    (0 & PL_CONFIG_HAS_NEO_PIXEL)
#define PL_CONFIG_HAS_NEO_THERMAL_CAM   (0 & PL_CONFIG_HAS_NEO_PIXEL)

#if ((PL_CONFIG_HAS_NEO_SHADOW_BOX + PL_CONFIG_HAS_NEO_HOUR_GLASS + PL_CONFIG_HAS_NEO_THERMAL_CAM)>1)
  #error "only one configuration can be active!"
#endif

#endif /* SOURCES_PLATFORM_H_ */
