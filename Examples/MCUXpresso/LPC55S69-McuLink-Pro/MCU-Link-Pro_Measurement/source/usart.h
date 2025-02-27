/*
 * usart.h
 *
 * Created on: 24 May 2022
 *     Author: Peter Allenspach
 *     For HSLU T&A VM2 "Open Source MCU-Link Pro Energy Probe"
 */

#include <stdint.h>

void init_USART(void);
void USART_setBaud(uint32_t baud);
void USART_setOutput(uint8_t val);
