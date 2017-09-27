/*
 * Robots.h
 *
 *  Created on: 27.08.2015
 *      Author: tastyger
 */

#ifndef SOURCES_INTRO_ROBOLIB_ROBOTS_H_
#define SOURCES_INTRO_ROBOLIB_ROBOTS_H_

/*---------------------------------------------------------------------*/
/* different robots: */
/* FRDM-KL25Z based robots: */
#define ROBO_POLOLU         0   /* FRDM-KL25Z robot on Pololu chassis/board, standard robot */
#define ROBO_POLOLU_WHITE   1   /* FRDM-KL25Z robot on Pololu chassis/board, white robot with 3 IR front sensors */
#define ROBO_KUDO0          2   /* FRDM-KL25Z 'green' robot with wheel encoders */
#define ROBO_KUDO1          3   /* FRDM-KL25Z 'green' robot with wheel encoders */
#define ROBO_KUDO2          4   /* FRDM-KL25Z 'green' robot with wheel encoders */
#define ROBO_BROWNY         5   /* this is for 'brown Rev2' (internal PCB). */

/* K22 based robots: */
#define ROBO_GREENY         6   /* green K22 production robot, e.g. Lab Robots L2, L3, L4, L5, L6, with nRF24L01+/Bluetooth and Ultrasonic module */
#define ROBO_BLACK22        7   /* black wheel K22 robot, standard without any extras (laser/etc) */
#define ROBO_VADER          8   /* ROBO_BLACK_22, black darth vader robot */
#define ROBO_PIRATE         9   /* ROBO_BLACK_22, black pirate robot */

/* K22 V2 2016 robots: */
#define ROBO_V2_BLACK_WHEEL     10   /* black new V2 robot whith black wheels (L20, L21) */
#define ROBO_V2_BLACK_WHEEL_BW  11   /* black new V2 robot whith black wheels (L22) */
/*---------------------------------------------------------------------*/

#endif /* SOURCES_INTRO_ROBOLIB_ROBOTS_H_ */
