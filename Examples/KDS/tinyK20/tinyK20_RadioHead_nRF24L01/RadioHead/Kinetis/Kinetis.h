/*
 * Kinetis.h
 *
 *  Created on: 23.07.2016
 *      Author: Erich Styger Local
 */

#ifndef RADIOHEAD_KINETIS_KINETIS_H_
#define RADIOHEAD_KINETIS_KINETIS_H_

#include <stdint.h>
#include <stddef.h> /* for NULL */
#include <string.h> /* for memcpy */

#define PROGMEM  /* nothing */

#define KINETIS_CE   10  /* chip enable */
#define KINETIS_SS   11  /* slave select */

typedef enum {
  OUTPUT,
  INPUT
} GPIO_Mode;

#define  LOW 0
#define HIGH 1

#ifdef __cplusplus
class HardwareSPI {
  public:
    HardwareSPI(void) {}
    HardwareSPI(int) {}
    uint8_t transfer(uint8_t val);
   // uint8_t SPIWriteRead(uint8_t val);
    void end(void);
};
#endif

typedef enum {
  RISING,
  FALLING
} INTERRUPT_Trigger;

typedef uint8_t GPIO_Pin;

void pinMode(GPIO_Pin, GPIO_Mode);

void digitalWrite(GPIO_Pin pin, uint8_t level);

uint8_t digitalRead(GPIO_Pin pin);

unsigned long millis(void);

void attachInterrupt(uint8_t interruptNumber, void (*isr0)(void), INTERRUPT_Trigger trigger);

void *memcpy_P(void *dst, const void *src, size_t srcSize);

int random(int from, int to);

void delay(uint32_t millis);

uint8_t SPIWriteRead(uint8_t val);

#ifdef __cplusplus
extern "C"
#endif
void On1msTimerInterrrupt(void);

#endif /* RADIOHEAD_KINETIS_KINETIS_H_ */
