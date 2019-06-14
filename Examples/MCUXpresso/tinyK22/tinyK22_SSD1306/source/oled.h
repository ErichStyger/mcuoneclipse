/*
 * oled.h
 *
 *      Author: Erich Styger
 */

#ifndef OLED_H_
#define OLED_H_

#include <stdint.h>
#include <stdbool.h>

void OLED_PrintShutdownHelp(void);
void OLED_PrintShutdownMsg(void);

void OLED_doOLED(void);

void OLED_ShowUPS(float voltage, float charge, bool isCharging);

void OLED_ShowTemperatureHumidity(float temperature, float humidity);

void OLED_ShowRxTx(uint32_t nofRx, uint32_t nofTx);

void OLED_Init(void);
void OLED_Deinit(void);

#endif /* OLED_H_ */
