/*
 * Hue Apple IR Remote
 * Autor: 	Joshua Wyss
 * Date: 	24.11.2022
 *
 */
#ifndef LED_H_
#define LED_H_

#include <stdbool.h>

void RGB_ON(void); 							/* turn all parts of the RGB LED ON */
void RGB_OFF(void); 						/* turn all parts of the RGB LED OFF */
void RGB_Controll(bool R, bool G, bool B);  /* control the individual parts of the RGB LED */
void LED_RED(bool onORoff);					/* control only the red part from the RGB LED*/
void LED_GREEN(bool onORoff);				/* control only the green part from the RGB LED*/
void LED_BLUE(bool onORoff);				/* control only the blue part from the RGB LED*/

void LED_Init(void);
void LED_Deinit(void);

#endif /* LED_H_ */
