/*
 * KinetisTrace.h
 *
 *  Created on: 09.10.2016
 *      Author: Erich Styger
 */

#ifndef SOURCES_KINETISTRACE_H_
#define SOURCES_KINETISTRACE_H_

#include <stdint.h>

void KinetisTrace_EnableGPIOForETM(void);

void KinetisTrace_EnableETB(uint32_t mask);

void KinetisTrace_Init(void);

#endif /* SOURCES_KINETISTRACE_H_ */
