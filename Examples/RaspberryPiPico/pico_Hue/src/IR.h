/*
 * Hue Apple IR Remote
 * Author: 	Joshua Wyss
 * Date: 	24.11.2022
 *
 */

#ifndef IR_H_
#define IR_H_

#include <stdint.h>

/*this function allows to send the IR command to toggle the lamp state*/
void Toggle_Lamp_State(void);

/*the following functions allow to send every command of the apple IR Remote*/
void IR_PowerOnOff_tx(void);
void IR_Up_tx(uint8_t count);
void IR_Down_tx(uint8_t count);
void IR_Left_tx(uint8_t count);
void IR_Right_tx(uint8_t count);
void IR_Menu_tx(void);
void IR_Sync_tx(void);

void IR_Init(void);
void IR_Deinit(void);

#endif /* IR_H_ */

