/**
 * \file
 * \brief Key debouncing interface.
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * This module implements debouncing of up to 4 Keys.
 */

#ifndef KEYDEBOUNCE_H_
#define KEYDEBOUNCE_H_

/*!
 * \brief Kicks the debouncing state machine.
 */
void KEYDBNC_Scan(void);


#endif /* KEYDEBOUNCE_H_ */
