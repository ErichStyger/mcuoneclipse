/*
 * ISRtrace.h
 *
 *  Created on: 03.06.2012
 *      Author: Erich Styger
 */

#ifndef ISRTRACE_H_
#define ISRTRACE_H_

#define ID_ISR_TACHO 1       /* lowest valid ID is 1 */
#define PRIO_OF_ISR_TACHO 6  /* 6.1 the hardware priority of the interrupt */

#define ID_ISR_RADIO 2       /* lowest valid ID is 1 */
#define PRIO_OF_ISR_RADIO 5  /* 5.mid the hardware priority of the interrupt */

#define ID_ISR_QUAD 3       /* lowest valid ID is 1 */
#define PRIO_OF_ISR_QUAD 7  /* 7.7 the hardware priority of the interrupt */

#endif /* ISRTRACE_H_ */
