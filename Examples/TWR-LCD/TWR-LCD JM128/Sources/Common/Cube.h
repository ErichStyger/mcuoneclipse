/** ###################################################################
**     Filename  : Cube.H
**     Project   : Tower_LCD
**     Processor : MCF51CN128CLK
**     Compiler  : CodeWarrior ColdFireV1 C Compiler
**     Date/Time : 09.01.2010, 20:03
**     Contents  :
**         User source code
**
** ###################################################################*/

#ifndef __Cube_H
#define __Cube_H

/* MODULE Cube */

#include "UI1.h"
#include "FRTOS1.h"
#include "Platform.h"

typedef struct {
  UI1_Screen screen;
  UI1_Window windowCube;
  UI1_Header headerCube;
  UI1_Icon iconCloseCube;
#if PL_HAS_SHIP_DEMO
  UI1_Window windowShip;
  UI1_Header headerShip;
  UI1_Icon iconCloseShip;
#endif
} CUBE_WindowDesc;

void CUBE_CreateWindow(CUBE_WindowDesc *desc);

void CUBE_StopTask(xTaskHandle task);

void CUBE_OnEvent(UI1_Screen *screen, UI1_Window *window, UI1_Element *element, UI1_EventCallbackKind event);
  /* UI event handler */

void CUBE_CloseShipWindow(void);
void CUBE_CloseCubeWindow(void);

/* END Cube */

#endif

