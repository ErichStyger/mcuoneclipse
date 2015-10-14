/** ###################################################################
**     Filename  : Tetris.H
**     Project   : Tower_LCD
**     Processor : MCF51CN128CLK
**     Compiler  : CodeWarrior ColdFireV1 C Compiler
**     Date/Time : 07.01.2010, 13:11
**     Contents  :
**         User source code
**
** ###################################################################*/

#ifndef __Tetris_H
#define __Tetris_H

/* MODULE Tetris */

#include "GDisp1.h"

#define TETRIS_CMD_NONE      0
#define TETRIS_CMD_UP        1  /* KEY1 */
#define TETRIS_CMD_RIGHT     2  /* KEY1 */  
#define TETRIS_CMD_MIDDLE    4  /* KEY1 */  
#define TETRIS_CMD_DOWN      8  /* KEY2 */
#define TETRIS_CMD_LEFT     16  /* KEY2 */
#define TETRIS_CMD_SPECIAL 255

typedef struct {
  UI1_Screen screen;
  UI1_Window window;
  UI1_Header header;
  UI1_Icon iconClose;
  UI1_Space cmdLeft, cmdRight, cmdUp, cmdDown;
} TETRIS_WindowDesc;

void TETRIS_CreateWindow(TETRIS_WindowDesc *desc);

/* method in case of window orientation change */
void TETRIS_RefreshWindow(void);

void TETRIS_AddTime(byte nofMS);
  /* Needs to be called periodically (e.g. from a timer interrupt) to increase the game time */

/* END Tetris */

#endif

