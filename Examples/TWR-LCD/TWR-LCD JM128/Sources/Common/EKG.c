/** ###################################################################
**     Filename  : Motor.C
**     Project   : Tower_LCD
**     Processor : MCF51JM128VLH
**     Compiler  : CodeWarrior ColdFireV1 C Compiler
**     Date/Time : 15.01.2010, 18:32
**     Contents  :
**         User source code
**
** ###################################################################*/

/* MODULE Motor */

#include "platform.h"
#if PL_HAS_EKG
#include "EKG.h"
#include "UTIL1.h"
#include "FRTOS1.h"
#include "App.h"
#include "Helv08n.h"
#include "Helv12n.h"
#include "I2C.h"
#include "UIG1.h"
#include "EVNT1.h"

#if PL_USE_SINGLE_FONT /* use only one font */
  #define FONT   PL_FONT()
#else
  #define FONT   Helv12n_GetFont()
#endif

static xTaskHandle xHandleTask;         /* window task handle */
static EKG_WindowDesc *appWp;

static void ekgGraphW_WindowCallback(UI1_Window *window, UI1_Element *element, UI1_EventCallbackKind kind, UI1_Pvoid data) {
  (void)data; (void)window;
  if (kind==UI1_EVENT_CLICK) {
    if (UI1_EqualElement(element, &appWp->iconClose)) {
      EVNT1_SetEvent(EVNT1_APP_MODE_CHANGE); /* request to close application */
      while(EVNT1_GetEvent(EVNT1_APP_MODE_CHANGE)) {
        /* wait until task has killed itself */
        FRTOS1_vTaskDelay(50/portTICK_RATE_MS);
      }
      APP_SetApplicationMode(APP_MODE_MAIN_MENU);
      return;
    }
  }
}

static uint8_t RangeRaw(int16_t raw) {
  /* maps raw values from -27000..+27000 range to 0..100% */
  int8_t val;

  /* speed is in the range of -27000...+27000 */
  val = (int8_t)(raw/270);
  /* scale to -100 to +100 */
  if (val>100) { val = 100; } else if (val<-100) { val = -100; }
  /* midpoint of graph is at 50% */
  val = 50+(val/2); /* scale between 0..100% */
  return (uint8_t)val;
}

static uint8_t RangeRate(uint8_t rate) {
  /* maps heart rate from 0..+200 range to 0..100% */
  int8_t val;

  val = (int8_t)(rate/2);
  return (uint8_t)val;
}


static portTASK_FUNCTION(TaskEKG, pvParameters) {
  EKG_WindowDesc *ui = (EKG_WindowDesc*)pvParameters;
  UIG1_DataPoint data[2], prevData[2];
  uint8_t i;

  appWp = ui;
#if PL_APP_MODE_I2C_LCD
  I2C_ClearBuffers();
#endif
  /* current speed: */
  data[0].color = UI1_COLOR_RED;
  data[0].data = 0;
  /* desired PID speed: */
  data[1].color = UI1_COLOR_BLUE;
  data[1].data = 0;
  /* previous data information */
  prevData[0].color = UI1_COLOR_BLUE;
  prevData[0].data = 0;
  prevData[1].color = UI1_COLOR_RED;
  prevData[1].data = 0;

  for (;;) {
#if PL_HAS_I2C_COMM
    if (I2C_GetEKGIsDataReady()) {
      data[0].data = RangeRate(I2C_GetEKGHeartRate());
      for(i=0;i<32;i++) {
        data[1].data = RangeRaw(I2C_GetEKGRaw(i));
        (void)UIG1_AddDataLine((UI1_Element *)&ui->graph, &prevData[0], &data[0], 2);
        /* remember data for next iteration */
        prevData[0].data = data[0].data;
        prevData[1].data = data[1].data;
      } /* for */
      I2C_ResetEKGIsDataReady();
    }
#else
    data[0].data = 50;
    data[1].data = 60;
    (void)UIG1_AddDataLine((UI1_Element *)&ui->graph, &prevData[0], &data[0], 2);
    /* remember data for next iteration */
    prevData[0].data = data[0].data;
    prevData[1].data = data[1].data;
#endif

    if (EVNT1_GetEvent(EVNT1_APP_MODE_CHANGE)) { /* request to close application */
      EVNT1_ClearEvent(EVNT1_APP_MODE_CHANGE); /* reset event flag */
      xHandleTask = NULL;
      FRTOS1_vTaskDelete(NULL); /* kill ourself */
    }
    FRTOS1_vTaskDelay(10/portTICK_RATE_MS);
  } /* for */
}

void EKG_StartTask(EKG_WindowDesc *desc) {
  UI1_PixelDim yPos, h;

  UI1_CreateScreen(&desc->screen, UI1_COLOR_WHITE);
  (void)UI1_CreateWindow(&desc->screen, &desc->window, UI1_COLOR_BRIGHT_GREEN, 0, 0, UI1_GetWidth(), UI1_GetHeight());
  (void)UI1_CreateHeader(&desc->window, &desc->header, (unsigned char*)"EKG", FONT, UI1_COLOR_BLUE);
  UI1_ChangeTextFgColor(&desc->header.element, UI1_COLOR_WHITE);
  UI1_SetWindowEventCallback(&desc->window, ekgGraphW_WindowCallback);
  /* Icon: Close */
  h = (UI1_PixelDim)(UI1_GetElementHeight(&desc->header));
  (void)UI1_CreateIcon(&desc->window, &desc->iconClose, 1, 1, (UI1_PixelDim)(h-2), (UI1_PixelDim)(h-2), UI1_ICON_CLOSE);
  desc->iconClose.element.prop.flags |= UI1_FLAGS_ALIGN_RIGHT;
  UI1_OnWindowResize(&desc->window); /* right align element(s) if needed */
  UI1_ChangeElementColor(&desc->iconClose, UI1_COLOR_BLUE);
  UI1_ChangeIconFgColor(&desc->iconClose, UI1_COLOR_WHITE);
  UI1_EnableElementSelection(&desc->iconClose);
  yPos = (UI1_PixelDim)(UI1_GetElementPosY(&desc->window)+UI1_GetElementHeight(&desc->header));
  /* graph */
  UIG1_CreateGraph(&desc->window, &desc->graph, 0, yPos,
      (UI1_PixelDim)(UI1_GetElementWidth(&desc->header)),
      (UI1_PixelDim)(UI1_GetElementHeight(&desc->window)-UI1_GetElementHeight(&desc->header)));
  appWp = desc; /* need to set it, as the update below will call the callback, and we need it there! */
  /* update the screen */
  UI1_UpdateScreen(&desc->screen);

  FRTOS1_xTaskCreate(TaskEKG, (signed portCHAR *)"EKG", configMINIMAL_STACK_SIZE, desc, tskIDLE_PRIORITY+1, &xHandleTask);
}

#endif /* PL_HAS_MOTOR_GRAPH */
