/*
 * Platform.h
 *
 *      Author: Erich Styger
 */

#ifndef PLATFORM_H_
#define PLATFORM_H_

#define PL_CONFIG_HAS_SSD1606   (0)  /* using SSD1606 I2C display */
#define PL_CONFIG_HAS_HD44780   (0)  /* if using LCDHTA 16 character display */
#define PL_CONFIG_HAS_ACCEL     (1)
#define PL_HAS_FREEMASTER       (0)
#define PL_HAS_RTOS             (1)
#define PL_IS_FRDM              (1)
#define PL_CONFIG_USE_I2C       (1)

#endif /* PLATFORM_H_ */
