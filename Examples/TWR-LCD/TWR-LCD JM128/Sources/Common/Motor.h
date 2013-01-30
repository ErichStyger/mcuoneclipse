/** ###################################################################
**     Filename  : Motor.h
**     Project   : Tower_LCD
**     Processor : MCF51CN128CLK
**     Compiler  : CodeWarrior ColdFireV1 C Compiler
**     Date/Time : 15.01.2010, 18:32
**     Contents  :
**         User source code
**
** ###################################################################*/

#ifndef __Motor_H
#define __Motor_H

#include "platform.h"

#if PL_HAS_MOTOR_GRAPH

#include "UI1.h"
#include "UIG1.h"

/* descriptor for our window */
typedef struct {
  UI1_Screen screen;
  UI1_Window window; /* graph window */
  UI1_Space sliderSpace; /* slider space */
  UI1_Header header;
  UI1_Icon iconClose;
  UIG1_Graph graph;
} MOTOR_WindowDesc;

void MOTOR_StartTask(MOTOR_WindowDesc *desc);

#endif /* PL_HAS_MOTOR_GRAPh */


#endif /* __Motor_H */

