/** ###################################################################
**     Filename  : LedFont.H
**     Project   : MPR08x
**     Processor : MCF51JM128VLH
**     Compiler  : CodeWarrior ColdFireV1 C Compiler
**     Date/Time : 24.12.2008, 15:41
**     Contents  :
**         User source code
**
**     (c) Copyright UNIS, a.s. 1997-2008
**     UNIS, a.s.
**     Jundrovska 33
**     624 00 Brno
**     Czech Republic
**     http      : www.processorexpert.com
**     mail      : info@processorexpert.com
** ###################################################################*/

#ifndef __LedFont_H
#define __LedFont_H

/* MODULE LedFont */
#include "pe_types.h"
#include "ucos1.h"

#define TASK_PRIO_SCROLLER  35

extern OS_FLAG_GRP *LedFont_Flags;
#define LEDFONT_FLAG_FINISHED_SCROLLING  (1<<0) /* flag to indicate that a scrollOnce text has been finished */
#define LEDFONT_FLAG_READY               (1<<1) /* flag to indicate that we are ready to take text for scrolling */
#define LEDFONT_FLAG_QUIT                (1<<2) /* flag to indicate that we shall quit scrolling */


void LedFont_ScrollText(char *text, bool scrollOnce, bool waitForFinish);
  /* sets the text to be scrolled */

void LedFont_Scroller(void *pdata);
  /* task doing the scrolling */


/* END LedFont */

#endif

