/** ###################################################################
**     Filename  : Accelerometer.C
**     Project   : Tower_LCD
**     Processor : MCF51JM128VLH
**     Compiler  : CodeWarrior ColdFireV1 C Compiler
**     Date/Time : 15.01.2010, 18:32
**     Contents  :
**         User source code
**
** ###################################################################*/

/* MODULE Accelerometer */

#include "Platform.h"

#include "Accelerometer.h"
#include "AnalogDigital.h"
#include "UTIL1.h"
#if PL_USE_RTOS
  #include "FRTOS1.h"
#endif
#if PL_HAS_UI
  #include "App.h"
  #include "Helv08n.h"
  #include "Helv12n.h"
  #include "UIG1.h"
#endif
#if PL_HAS_HW_ACCELEROMETER
  #include "ACCEL1.h"
#endif
#include "I2C.h"
#include "EVNT1.h"

#if PL_HAS_ACCEL_DEMO

#if PL_USE_SINGLE_FONT /* use only one font */
  #define FONT   PL_FONT()
#else
  #define FONT   Helv12n_GetFont()
#endif

static TaskHandle_t xHandleTaskAccelOrientation;  /* display orientation task */
static ACCEL_WindowDesc *appWp;

#define VAL_1G           5500 /* about 1g value */
#define VAL_MINUS_1G    -5500 /* about -1g value */

void ACCEL_StopAccelDemo(void) {
  EVNT1_SetEvent(EVNT1_APP_MODE_CHANGE); /* request to close application */
  while(EVNT1_GetEvent(EVNT1_APP_MODE_CHANGE)) {
    /* wait until task has killed itself */
    vTaskDelay(pdMS_TO_TICKS(50));
  }
  APP_SetApplicationMode(APP_MODE_MAIN_MENU);
}

static void accelW_WindowCallback(UI1_Window *window, UI1_Element *element, UI1_EventCallbackKind kind, UI1_Pvoid data) {
  (void)window;
  (void)data; /* unused argument */
  if (kind==UI1_EVENT_CLICK) {
    if (UI1_EqualElement(element, &appWp->iconClose)) {
      ACCEL_StopAccelDemo();
      return;
    }
  }
}

static portTASK_FUNCTION(TaskAccelOrientation, pvParameters) {
  int16_t x,z;
  UI1_DisplayOrientation orientation;

  (void)pvParameters;
  FRTOS1_vTaskSuspend(NULL);
  for (;;) {
    { /* protect critical section in display */
      x = ACCEL_GetX();
      z = ACCEL_GetZ();
#if PL_TWR_LCD_REV_0
      if (z>=VAL_1G && x>=VAL_MINUS_1G) {
        orientation = UI1_ORIENTATION_LANDSCAPE180;
      } else if (z<=VAL_MINUS_1G && x>=VAL_MINUS_1G) {
        orientation = UI1_ORIENTATION_LANDSCAPE;
      } else if (x<=VAL_MINUS_1G && z>=VAL_MINUS_1G) {
        orientation = UI1_ORIENTATION_PORTRAIT;
      } else {
        orientation = UI1_ORIENTATION_PORTRAIT180;
      }
#elif PL_TWR_LCD_REV_A
      if (z>=VAL_1G && x>=VAL_MINUS_1G) {
        orientation = UI1_ORIENTATION_LANDSCAPE;
      } else if (z<=VAL_MINUS_1G && x>=VAL_MINUS_1G) {
        orientation = UI1_ORIENTATION_LANDSCAPE180;
      } else if (x<=VAL_MINUS_1G && z>=VAL_MINUS_1G) {
        orientation = UI1_ORIENTATION_PORTRAIT180;
      } else {
        orientation = UI1_ORIENTATION_PORTRAIT;
      }
#endif
      if (orientation != UI1_GetDisplayOrientation()) {
        /* need to do some protection, as we are changing the display.... */
        GDisp1_GetDisplay();
        FRTOS1_vTaskSuspendAll();
        UI1_SetDisplayOrientation(orientation);
        FRTOS1_xTaskResumeAll();
        GDisp1_GiveDisplay();
      }
    }
    vTaskDelay(pdMS_TO_TICKS(500));
  } /* for */
}

void ACCEL_SuspendOrientationTask(void) {
  vTaskSuspend(xHandleTaskAccelOrientation);
}

void ACCEL_ResumeOrientationTask(void) {
  vTaskResume(xHandleTaskAccelOrientation);
}

static portTASK_FUNCTION(TaskAccelDemo, pvParameters) {
  int16_t x,y,z;
  ACCEL_WindowDesc *ui = (ACCEL_WindowDesc*)pvParameters;
  unsigned char buf[sizeof("X: 123")];
  UIG1_DataPoint data[3], prevData[3];

  appWp = ui;
#if PL_APP_MODE_I2C_LCD
  I2C_ClearBuffers();
#endif
  data[0].color = UI1_COLOR_RED;
  data[0].data = 0;
  data[1].color = UI1_COLOR_BLUE;
  data[1].data = 0;
  data[2].color = UI1_COLOR_DARK_GREEN;
  data[3].data = 0;
  prevData[0].color = UI1_COLOR_RED;
  prevData[0].data = 0;
  prevData[1].color = UI1_COLOR_BLUE;
  prevData[1].data = 0;
  prevData[2].color = UI1_COLOR_DARK_GREEN;
  prevData[2].data = 0;
  for (;;) {
    /* we are getting the values in milli-g (means: around -1200 to +1200 */
#if PL_HAS_AUTO_DEMO && PL_HAS_HW_ACCELEROMETER
    /* for demo, make values more interesting */
    x = ACCEL1_GetX();
    y = ACCEL1_GetY();
    z = ACCEL1_GetZ();
    while (z>900) { /* put in range */
      z /= 2;
    }
#else
    x = ACCEL_GetX();
    y = ACCEL_GetY();
    z = ACCEL_GetZ();
#endif
    /* cap to -100..+100 */
    x /= 11; /* little bit more than 10, just to have 1g not always hitting the limit of 100% */
    y /= 11;
    z /= 11;
    /* make sure it is in the -100..+100 range */
    if (x>100) { x = 100; } else if (x<-100) { x = -100; }
    if (y>100) { y = 100; } else if (y<-100) { y = -100; }
    if (z>100) { z = 100; } else if (z<-100) { z = -100; }
    /* midpoint of graph is at 50% */
    x = 50+(x/2); /* scale between 0..100% */
    y = 50+(y/2); /* scale between 0..100% */
    z = 50+(z/2); /* scale between 0..100% */
    UTIL1_strcpy(buf, sizeof(buf), (unsigned char*)"X: ");  UTIL1_strcatNum16s(buf, sizeof(buf), x);
    UI1_ChangeText(&ui->window, (UI1_Element *)&ui->txtX, sizeof(ui->txtBufX), buf);
    UTIL1_strcpy(buf, sizeof(buf), (unsigned char*)"Y: ");  UTIL1_strcatNum16s(buf, sizeof(buf), y);
    UI1_ChangeText(&ui->window, (UI1_Element *)&ui->txtY, sizeof(ui->txtBufY), buf);
    UTIL1_strcpy(buf, sizeof(buf), (unsigned char*)"Z: ");  UTIL1_strcatNum16s(buf, sizeof(buf), z);
    UI1_ChangeText(&ui->window, (UI1_Element *)&ui->txtZ, sizeof(ui->txtBufZ), buf);
    (void)UI1_ChangeBarGraphData(&ui->window, &ui->accelBarGraph, 0, (uint8_t)x);
    (void)UI1_ChangeBarGraphData(&ui->window, &ui->accelBarGraph, 1, (uint8_t)y);
    (void)UI1_ChangeBarGraphData(&ui->window, &ui->accelBarGraph, 2, (uint8_t)z);
    /* graph */
    data[0].data = (uint8_t)x;
    data[1].data = (uint8_t)y;
    data[2].data = (uint8_t)z;
    (void)UIG1_AddDataLine((UI1_Element *)&ui->graph, &prevData[0], &data[0], 3);
    prevData[0].data = data[0].data;
    prevData[1].data = data[1].data;
    prevData[2].data = data[2].data;
    if (EVNT1_GetEvent(EVNT1_APP_MODE_CHANGE)) { /* request to close application */
      EVNT1_ClearEvent(EVNT1_APP_MODE_CHANGE); /* reset event flag */
      vTaskDelete(NULL); /* kill ourself */
    }
    vTaskDelay(pdMS_TO_TICKS(25));
  }
}

void ACCEL_StartDemoTask(ACCEL_WindowDesc *desc) {
  UI1_PixelDim yPos, h;

  UI1_CreateScreen(&desc->screen, UI1_COLOR_WHITE);
  (void)UI1_CreateWindow(&desc->screen, &desc->window, UI1_COLOR_BRIGHT_GREEN, 0, 0, UI1_GetWidth(), UI1_GetHeight());
  (void)UI1_CreateHeader(&desc->window, &desc->header, (unsigned char*)"Accelerometer", FONT, UI1_COLOR_BLUE);
  UI1_ChangeTextFgColor(&desc->header.element, UI1_COLOR_WHITE);
  UI1_SetWindowEventCallback(&desc->window, accelW_WindowCallback);
  /* Icon: Close */
  h = (UI1_PixelDim)(UI1_GetElementHeight(&desc->header));
  (void)UI1_CreateIcon(&desc->window, &desc->iconClose, 1, 1, (UI1_PixelDim)(h-2), (UI1_PixelDim)(h-2), UI1_ICON_CLOSE);
  desc->iconClose.element.prop.flags |= UI1_FLAGS_ALIGN_RIGHT;
  UI1_OnWindowResize(&desc->window); /* right align element(s) if needed */
  UI1_ChangeElementColor(&desc->iconClose, UI1_COLOR_BLUE);
  UI1_ChangeIconFgColor(&desc->iconClose, UI1_COLOR_WHITE);
  UI1_EnableElementSelection(&desc->iconClose);
  yPos = (UI1_PixelDim)(UI1_GetElementPosY(&desc->window)+UI1_GetElementHeight(&desc->header)+5);
  /* barGraph */
  desc->data[0] = 0;
  desc->data[1] = 0;
  desc->data[2] = 0;
  (void)UI1_CreateBarGraph(&desc->window, &desc->accelBarGraph, 5, yPos, 170, 170,
     UI1_COLOR_BRIGHT_GREEN,
     (byte*)&desc->data, sizeof(desc->data),
     UI1_COLOR_RED, /* bar color */
     1, /* border width */
     UI1_COLOR_BLACK, /* border color */
     5 /* border space */
   );
  yPos = (UI1_PixelDim)(UI1_GetElementPosY(&desc->accelBarGraph)+UI1_GetElementHeight(&desc->accelBarGraph)+5);
  /* X */
  desc->txtBufX[0] = '\0';
  (void)UI1_CreateText(&desc->window, &desc->txtX,  5, yPos, 0, 0, &desc->txtBufX[0], FONT);
  /* Y */
  desc->txtBufY[0] = '\0';
  (void)UI1_CreateText(&desc->window, &desc->txtY, 58, yPos, 0, 0, &desc->txtBufY[0], FONT);
  /* Z */
  desc->txtBufZ[0] = '\0';
  (void)UI1_CreateText(&desc->window, &desc->txtZ, 110, yPos, 0, 0, &desc->txtBufZ[0], FONT);

  UIG1_CreateGraph(&desc->window, &desc->graph,
      (UI1_PixelDim)(UI1_GetElementPosX(&desc->accelBarGraph)+UI1_GetElementWidth(&desc->accelBarGraph)+10), UI1_GetElementPosY(&desc->accelBarGraph),
      125, UI1_GetElementHeight(&desc->accelBarGraph));
  /* update the screen */
  UI1_UpdateScreen(&desc->screen);

  FRTOS1_xTaskCreate(TaskAccelDemo, "Accel", configMINIMAL_STACK_SIZE+50, desc, tskIDLE_PRIORITY+1, NULL);
}

void ACCEL_StartOrientationTask(void) {
#if PL_HAS_HW_ACCELEROMETER
  ACCEL1_CalibrateZ1g(); /* assume device is flat during reset/power-up */
  //ACCEL1_CalibrateX1g(); /* flat on switch side */
  //ACCEL1_CalibrateY1g(); /* flat on LCD side */
#endif
#if PL_HAS_ACCEL_ORIENT
  FRTOS1_xTaskCreate(TaskAccelOrientation, (signed portCHAR *)"AccelOrient", configMINIMAL_STACK_SIZE+50, NULL, tskIDLE_PRIORITY+1, &xHandleTaskAccelOrientation);
#endif
}

#if PL_HAS_HW_ACCELEROMETER
int16_t ACCEL_GetX(void) {
  return ACCEL1_GetXmg();
}

int16_t ACCEL_GetY(void) {
  return ACCEL1_GetYmg();
}

int16_t ACCEL_GetZ(void) {
  return ACCEL1_GetZmg();
}
#elif PL_APP_MODE_I2C_LCD /* use I2C */
int16_t ACCEL_GetX(void) {
  return I2C_GetAccelX();
}

int16_t ACCEL_GetY(void) {
  return I2C_GetAccelY();
}

int16_t ACCEL_GetZ(void) {
  return I2C_GetAccelZ();
}

#endif /* PL_HAS_HW_ACCELEROMETER */

#endif /* PL_HAS_ACCEL_DEMO */


/* END Accelerometer */
