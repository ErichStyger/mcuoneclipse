/*
 * Clock.h
 *
 *  Created on: 27.07.2012
 *      Author: Erich Styger
 */

#ifndef CLOCK_H_
#define CLOCK_H_

#define CORE_CLOCK       (96000000)
#define PERIPHERAL_BUS_CLOCK (CORE_CLOCK/2)

//#pragma define_section relocate_code ".data" ".data" ".data" far_abs RX
//#define __relocate_code__   __declspec(relocate_code)

void InitClock(void);

#endif /* CLOCK_H_ */
