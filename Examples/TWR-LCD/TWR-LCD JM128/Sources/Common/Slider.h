/*
 * Slider.h
 *
 *  Created on: 08.09.2011
 *      Author: Erich Styger
 */

#ifndef SLIDER_H_
#define SLIDER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "Platform.h"

#if PL_HAS_SLIDER

#include "UI1.h"

/*! \brief called from the window creator to create slider controls */
void SLIDER_CreateSliders(UI1_Window *window, UI1_PixelDim x, UI1_PixelDim y, UI1_PixelDim w, UI1_PixelDim h);

/*! \brief Called for clicks and window refresh  */
void SLIDER_SliderW_WindowCallback(UI1_Window *window, UI1_Element *element, UI1_EventCallbackKind kind, UI1_Pvoid data);

/*! \brief Returns status of control as string */
void SLIDER_GetCmdString(unsigned char *buf, size_t bufSize);

#endif /* PL_HAS_SLIDER */

#ifdef __cplusplus
}
#endif

#endif /* SLIDER_H_ */
