/*
 * Hue Apple IR Remote
 * Author: 	Joshua Wyss
 * Date: 	24.11.2022
 *
 */

#ifndef STATES_H_
#define STATES_H_

typedef enum {
	Initialisation,
	LampIsON,
	LampIsOFF,
	TurnLampOFF,
	TurnAppOFF,
	TurnLampON,
	TurnAppON
} State_e;

State_e GetState(void); 			/* this function returns the actual state */
void State_Initialisation(void);    /* this function contains the state Initialization */
void State_LampIsON(void);			/* this function contains the state LampIsON */
void State_LampIsOFF(void);	 		/* this function contains the state LampIsOFF */
void State_TurnLampOFF(void);		/* this function contains the state TurnLampOFF */
void State_TurnAppOFF(void);		/* this function contains the state TurnAppOFF */
void State_TurnLampON(void);		/* this function contains the state TurnLampON */
void State_TurnAppON(void);			/* this function contains the state TurnAppON */

#endif /* STATES_H_ */
