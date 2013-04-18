#ifndef __ECG_H
#define __ECG_H

#include "platform.h"

#if PL_HAS_EKG

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
} EKG_WindowDesc;

void EKG_StartTask(EKG_WindowDesc *desc);

#endif /* PL_HAS_EKG */


#endif /* __ECG_H */

