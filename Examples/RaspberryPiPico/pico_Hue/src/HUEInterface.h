/*
 * Hue Apple IR Remote
 * Author: 	Joshua Wyss
 * Date: 	09.12.2022
 *
 */

#ifndef HUEINTERFACE_H_
#define HUEINTERFACE_H_

#include <stdint.h>
#include <stdbool.h>

void Toggle_App_State(void); 		/*this function allows to toggle the state in the app*/
bool Get_App_State(void);			/*this function allows to get the actual app state*/
uint8_t Get_App_DutyCycle(void);	/*this function allows to get the actual dutycycle in percent*/

void HUEInterface_Init(void);
void HUEInterface_Deinit(void);

#endif /* HUEINTERFACE_H_ */
