/** ###################################################################
**     Filename  : Accelerometer.H
**     Project   : Tower_LCD
**     Processor : MCF51CN128CLK
**     Compiler  : CodeWarrior ColdFireV1 C Compiler
**     Date/Time : 15.01.2010, 18:32
**     Contents  :
**         User source code
**
** ###################################################################*/

#ifndef __Accelerometer_H
#define __Accelerometer_H

/* MODULE Accelerometer */

#include "Platform.h"

#if PL_HAS_ACCEL_DEMO

#include "UI1.h"
#include "UIG1.h"

/* descriptor for our window */
typedef struct {
  UI1_Screen screen;
  UI1_Window window;
  UI1_Header header;
  UI1_Icon iconClose;
  UI1_BarGraph accelBarGraph;
  byte data[3]; /* for x, y and z */
  UI1_Text txtX, txtY, txtZ;
  unsigned char txtBufX[sizeof("X: 000")];
  unsigned char txtBufY[sizeof("Y: 000")];
  unsigned char txtBufZ[sizeof("Z: 000")];
  UIG1_Graph graph;
} ACCEL_WindowDesc;


void ACCEL_StartDemoTask(ACCEL_WindowDesc *desc);

void ACCEL_StartOrientationTask(void);
void ACCEL_SuspendOrientationTask(void);
void ACCEL_ResumeOrientationTask(void);

int16_t ACCEL_GetX(void);
int16_t ACCEL_GetY(void);
int16_t ACCEL_GetZ(void);

void ACCEL_StopAccelDemo(void);

#endif

/* END Accelerometer */

#endif

