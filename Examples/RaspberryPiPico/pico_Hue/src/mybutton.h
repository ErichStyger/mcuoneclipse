/*
 * Hue Apple IR Remote
 * Author: 	Joshua Wyss
 * Date: 	24.11.2022
 *
 */

#ifndef MYBUTTON_H_
#define MYBUTTON_H_

#include <stdbool.h>

/* this function returns true when a rising edge was detected */
bool GetButtonState(void);

void MyButton_Init(void);
void MyButton_Deinit(void);

#endif /* MYBUTTON_H_ */
