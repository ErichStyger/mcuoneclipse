/*
 * Orientation.c
 *
 *  Created on: 22.12.2018
 *      Author: Erich Styger
 */


#include "Platform.h"
#if PL_HAS_ORIENTATION
#include "Orientation.h"
#include "FRTOS1.h"
#include "MMA1.h"
#if PL_CONFIG_HAS_GUI
  #include "GDisp1.h"
  #include "gui/gui.h"
#endif
#if PL_CONFIG_HAS_NEO_PIXEL
  #include "LedDisp.h"
#endif

#if PL_CONFIG_HAS_MMA8451

static ORI_Orientation_e currOrientation = -1;

ORI_Orientation_e ORI_GetCurrentOrientation(void) {
  return currOrientation;
}

void ORI_DetermineCurrentOrientation(void) {
  int16_t xmg, ymg, zmg;
  ORI_Orientation_e newOrientation = -1;

  xmg = MMA1_GetXmg();
  ymg = MMA1_GetYmg();
  zmg = MMA1_GetZmg();
  if(xmg>200) {
    newOrientation = ORI_ORIENTATION_X_UP; /* tinyK22 up */
  } else if (xmg<-200) {
    newOrientation = ORI_ORIENTATION_X_DOWN; /* tinyK22 down */
  } else if (ymg>200) {
    newOrientation = ORI_ORIENTATION_Y_UP; /* LCD up */
  } else if (ymg<-200) {
    newOrientation = ORI_ORIENTATION_Y_DOWN; /* LCD down */
  } else if (zmg>200) {
    newOrientation = ORI_ORIENTATION_Z_UP; /* NeoPixel up */
  } else if (zmg<-200) {
    newOrientation = ORI_ORIENTATION_Z_DOWN; /* NeoPixel down */
  }
  if (newOrientation!=currOrientation) {
    currOrientation = newOrientation;
    switch(newOrientation) {
      case ORI_ORIENTATION_X_UP:
    #if PL_CONFIG_HAS_NEO_PIXEL
        LedDisp_SetDisplayOrientation(LedDisp_ORIENTATION_PORTRAIT);
    #endif
    #if PL_CONFIG_HAS_GUI
        GUI_ChangeOrientation(GDisp1_ORIENTATION_PORTRAIT);
    #endif
        break;

      case ORI_ORIENTATION_X_DOWN:
    #if PL_CONFIG_HAS_NEO_PIXEL
        LedDisp_SetDisplayOrientation(LedDisp_ORIENTATION_PORTRAIT180);
    #endif
    #if PL_CONFIG_HAS_GUI
        GUI_ChangeOrientation(GDisp1_ORIENTATION_PORTRAIT180);
    #endif
        break;

      case ORI_ORIENTATION_Y_UP:
    #if PL_CONFIG_HAS_NEO_PIXEL
        GUI_ChangeOrientation(LedDisp_ORIENTATION_LANDSCAPE180);
    #endif
    #if PL_CONFIG_HAS_GUI
        GUI_ChangeOrientation(GDisp1_ORIENTATION_LANDSCAPE);
    #endif
        break;

      case ORI_ORIENTATION_Y_DOWN:
    #if PL_CONFIG_HAS_NEO_PIXEL
        LedDisp_SetDisplayOrientation(LedDisp_ORIENTATION_LANDSCAPE);
    #endif
    #if PL_CONFIG_HAS_GUI
        GUI_ChangeOrientation(GDisp1_ORIENTATION_LANDSCAPE180);
    #endif
        break;

      case ORI_ORIENTATION_Z_UP:
    #if PL_CONFIG_HAS_NEO_PIXEL
        LedDisp_SetDisplayOrientation(LedDisp_ORIENTATION_LANDSCAPE);
    #endif
    #if PL_CONFIG_HAS_SSD1351
        GUI_ChangeOrientation(GDisp1_ORIENTATION_LANDSCAPE180);
    #endif
        break;

      case ORI_ORIENTATION_Z_DOWN:
    #if PL_CONFIG_HAS_NEO_PIXEL
        LedDisp_SetDisplayOrientation(LedDisp_ORIENTATION_LANDSCAPE);
    #endif
    #if PL_CONFIG_HAS_GUI
        GUI_ChangeOrientation(GDisp1_ORIENTATION_LANDSCAPE);
    #endif
      break;
    } /* switch */
  } /* if */
}
#endif

static void OrientationTask(void *p) {
   bool isEnabled = FALSE;
   uint8_t res;

   for(;;) {
     res = MMA1_isEnabled(&isEnabled);
     if(res==ERR_OK) {
       break;
     }
     CLS1_SendStr((uint8_t*)"Failed MMA1_isEnabled(), retry ...\r\n", CLS1_GetStdio()->stdErr);
     vTaskDelay(pdMS_TO_TICKS(100));
   }
   if (!isEnabled) {
     for(;;) {
       CLS1_SendStr((uint8_t*)"Enabling MMA8541 sensor.\r\n", CLS1_GetStdio()->stdOut);
       res = MMA1_Enable();
       if(res==ERR_OK) {
         break;
       }
       CLS1_SendStr((uint8_t*)"Failed MMA1_isEnabled(), retry ...\r\n", CLS1_GetStdio()->stdErr);
       vTaskDelay(pdMS_TO_TICKS(100));
     }
   }

  for(;;) {
    vTaskDelay(pdMS_TO_TICKS(1000)); /* don't access the sensor immediately after power-up! */
    ORI_DetermineCurrentOrientation();
  }
}

void ORI_Init(void) {
  if (xTaskCreate(
        OrientationTask,  /* pointer to the task */
        "Orientation", /* task name for kernel awareness debugging */
        600/sizeof(StackType_t), /* task stack size */
        (void*)NULL, /* optional task startup argument */
        tskIDLE_PRIORITY+3,  /* initial priority */
        (xTaskHandle*)NULL /* optional task handle to create */
      ) != pdPASS) {
    /*lint -e527 */
    for(;;){}; /* error! probably out of memory */
    /*lint +e527 */
  }
}

#endif /* PL_HAS_ORIENTATION */
