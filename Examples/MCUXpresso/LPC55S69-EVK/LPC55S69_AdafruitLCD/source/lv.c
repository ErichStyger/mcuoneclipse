/*
 * Copyright (c) 2019, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#if PL_CONFIG_USE_GUI
#include "lv.h"
#include "LittlevGL/lvgl/lvgl.h"
#include "McuILI9341.h"
#include "McuRB.h"
#include <string.h> /* for memset() */
#include "McuShell.h"
#include "McuRTOS.h"
#include "lcd.h"
#include "McuShell.h"
#if PL_CONFIG_USE_GUI_TOUCH_NAV
  #include "touch.h"
#endif
#if PL_CONFIG_USE_TOASTER
  #include "toaster.h"
#endif

#if PL_CONFIG_USE_GUI_SCREEN_SAVER
  static TimerHandle_t timerHndlLcdTimeout;
  #define SCREEN_SAVER_TIMEOUT_MS (10*1000) /* number of milli-seconds */
#endif

static McuRB_Handle_t ringBufferHndl;

#if PL_CONFIG_USE_GUI_SCREEN_SAVER
static void vTimerCallbackLCDExpired(TimerHandle_t pxTimer) {
  /* timer callback to turn off LCD backlight */
#if PL_CONFIG_USE_TOASTER
  TOASTER_Show();
#else
  McuILI9341_DisplayOn(false);
#endif
}
#endif

#if PL_CONFIG_USE_GUI_SCREEN_SAVER
static void KeyPressForLCD(void) {
  /* called for each key press. It turns on the LCD if it is dormant or resets the LCD backlight timeout timer */
  if (xTimerIsTimerActive(timerHndlLcdTimeout)==pdFALSE) {
    /* timer is not active: start it */
    if (xTimerStart(timerHndlLcdTimeout, 0)!=pdPASS) {
      for(;;); /* failure!?! */
    }
  #if PL_CONFIG_USE_TOASTER
    TOASTER_StopScreenSaver();
    /* and turn LCD on */
  #else
    McuILI9341_DisplayOn(true);
  #endif
  } else {
    if (xTimerReset(timerHndlLcdTimeout, 0)!=pdPASS) { /* reset timer, e.g. after key press or user input */
      for(;;); /* failure?!? */
    }
  }
}
#endif

static lv_indev_t *inputDevicePtr = NULL;

lv_indev_t * LV_GetInputDevice(void) {
  return inputDevicePtr;
}

/* Flush the content of the internal buffer the specific area on the display
 * You can use DMA or any hardware acceleration to do this operation in the background but
 * 'lv_disp_flush_ready()' has to be called when finished */
static void ex_disp_flush(struct _disp_drv_t * disp_drv, const lv_area_t * area, lv_color_t * color_p) {
  /*The most simple case (but also the slowest) to put all pixels to the screen one-by-one*/
  McuILI9341_SetWindow(area->x1, area->y1, area->x2, area->y2);
  McuILI9341_WritePixelData((uint16_t*)color_p, (area->x2-area->x1+1)*(area->y2-area->y1+1));
  /* IMPORTANT!!!
   * Inform the graphics library that you are ready with the flushing*/
  lv_disp_flush_ready(disp_drv);
}

#if USE_LV_GPU

/* If your MCU has hardware accelerator (GPU) then you can use it to blend to memories using opacity
 * It can be used only in buffered mode (LV_VDB_SIZE != 0 in lv_conf.h)*/
static void ex_mem_blend(lv_color_t * dest, const lv_color_t * src, uint32_t length, lv_opa_t opa)
{
    /*It's an example code which should be done by your GPU*/

    int32_t i;
    for(i = 0; i < length; i++) {
        dest[i] = lv_color_mix(dest[i], src[i], opa);
    }
}

/* If your MCU has hardware accelerator (GPU) then you can use it to fill a memory with a color
 * It can be used only in buffered mode (LV_VDB_SIZE != 0 in lv_conf.h)*/
static void ex_mem_fill(lv_color_t * dest, uint32_t length, lv_color_t color)
{
    /*It's an example code which should be done by your GPU*/

    int32_t i;
    for(i = 0; i < length; i++) {
        dest[i] = color;
    }
}

#endif

#if PL_CONFIG_USE_GUI_TOUCH_NAV
/* Read the touchpad and store it in 'data'
 * Return false if no more data read; true for ready again */
static bool ex_tp_read(struct _lv_indev_drv_t * indev_drv, lv_indev_data_t * data) {
  /* Read the touchpad */
  static int last_x = 0;
  static int last_y = 0;
  uint16_t x, y;
  bool pressed;

  /* set default state which is released with the last pressed coordinates */
  data->state = LV_INDEV_STATE_REL;
  data->point.x = last_x;
  data->point.y = last_y;

  if (TOUCH_IsPressed() && TOUCH_Poll(&pressed, &x, &y)==ERR_OK) {
    data->state = LV_INDEV_STATE_PR;
    last_x = x;
    last_y = y;
    data->point.x = x;
    data->point.y = y;
  #if PL_CONFIG_USE_GUI_SCREEN_SAVER
    KeyPressForLCD();
  #endif
  }
  //return TOUCH_HasMoreData();
  return false; /* no more data */
}
#endif

void LV_Task(void) {
  /* Periodically call this function.
   * The timing is not critical but should be between 1..10 ms */
  lv_task_handler();
}

#if PL_CONFIG_USE_GUI_KEY_NAV
/* called for push button events from Events.c */
void LV_ButtonEvent(uint8_t keys, uint16_t eventMask) {
  uint16_t buttonInfo;

  if (keys&LV_BTN_MASK_CENTER) {
    buttonInfo = LV_BTN_MASK_CENTER | eventMask;
    McuRB_Put(ringBufferHndl, &buttonInfo);
  } else if (keys&LV_BTN_MASK_RIGHT) {
    buttonInfo = LV_BTN_MASK_RIGHT | eventMask;
    McuRB_Put(ringBufferHndl, &buttonInfo);
  } else if (keys&LV_BTN_MASK_DOWN) {
    buttonInfo = LV_BTN_MASK_DOWN | eventMask;
    McuRB_Put(ringBufferHndl, &buttonInfo);
  } else if (keys&LV_BTN_MASK_UP) {
    buttonInfo = LV_BTN_MASK_UP | eventMask;
    McuRB_Put(ringBufferHndl, &buttonInfo);
  } else if (keys&LV_BTN_MASK_LEFT) {
    buttonInfo = LV_BTN_MASK_LEFT | eventMask;
    McuRB_Put(ringBufferHndl, &buttonInfo);
   }
}
#endif

#if PL_CONFIG_USE_GUI_KEY_NAV
static uint8_t MapKeyOrientation(uint8_t key) {
  switch(McuGDisplaySSD1306_GetDisplayOrientation()) {
    case McuSSD1306_CONFIG_ORIENTATION_PORTRAIT:
      switch(key) {
        case LV_BTN_MASK_LEFT:
          key = LV_BTN_MASK_UP;
          break;
        case LV_BTN_MASK_RIGHT:
          key = LV_BTN_MASK_DOWN;
          break;
        case LV_BTN_MASK_UP:
          key = LV_BTN_MASK_RIGHT;
          break;
        case LV_BTN_MASK_DOWN:
          key = LV_BTN_MASK_LEFT;
          break;
        case LV_BTN_MASK_CENTER:
          key = LV_BTN_MASK_CENTER;
          break;
        default:
          key = 0; /* error case? */
          break;
      } /* switch */
      break;
    case McuSSD1306_CONFIG_ORIENTATION_PORTRAIT180:
      switch(key) {
        case LV_BTN_MASK_LEFT:
          key = LV_BTN_MASK_DOWN;
          break;
        case LV_BTN_MASK_RIGHT:
          key = LV_BTN_MASK_UP;
          break;
        case LV_BTN_MASK_UP:
          key = LV_BTN_MASK_LEFT;
          break;
        case LV_BTN_MASK_DOWN:
          key = LV_BTN_MASK_RIGHT;
          break;
        case LV_BTN_MASK_CENTER:
          key = LV_BTN_MASK_CENTER;
          break;
        default:
          key = 0; /* error case? */
          break;
      } /* switch */
      break;
    case McuSSD1306_CONFIG_ORIENTATION_LANDSCAPE180:
      switch(key) {
        case LV_BTN_MASK_LEFT:
          key = LV_BTN_MASK_RIGHT;
          break;
        case LV_BTN_MASK_RIGHT:
          key = LV_BTN_MASK_LEFT;
          break;
        case LV_BTN_MASK_UP:
          key = LV_BTN_MASK_DOWN;
          break;
        case LV_BTN_MASK_DOWN:
          key = LV_BTN_MASK_UP;
          break;
        case LV_BTN_MASK_CENTER:
          key = LV_BTN_MASK_CENTER;
          break;
        default:
          key = 0; /* error case? */
          break;
      } /* switch */
      break;
    case McuSSD1306_CONFIG_ORIENTATION_LANDSCAPE:
      switch(key) {
        case LV_BTN_MASK_LEFT:
          key = LV_BTN_MASK_LEFT;
          break;
        case LV_BTN_MASK_RIGHT:
          key = LV_BTN_MASK_RIGHT;
          break;
        case LV_BTN_MASK_UP:
          key = LV_BTN_MASK_UP;
          break;
        case LV_BTN_MASK_DOWN:
          key = LV_BTN_MASK_DOWN;
          break;
        case LV_BTN_MASK_CENTER:
          key = LV_BTN_MASK_CENTER;
          break;
        default:
          key = 0; /* error case? */
          break;
      } /* switch */
      break;
    default:
      key = 0; /* error case? */
      break;
  } /* switch */
  return key;
}
#endif

#if 0
/*
 * To use a keyboard:
    USE_LV_GROUP has to be enabled in lv_conf.h
    An object group has to be created: lv_group_create() and objects have to be added: lv_group_add_obj()
    The created group has to be assigned to an input device: lv_indev_set_group(my_indev, group1);
    Use LV_GROUP_KEY_... to navigate among the objects in the group
 */
static bool keyboard_read(lv_indev_data_t *data)  {
  uint16_t keyData;

  memset(data, 0, sizeof(lv_indev_data_t)); /* initialize all fields */
  data->state = LV_INDEV_STATE_REL; /* by default, not pressed */
  if (McuRB_NofElements(ringBufferHndl)==0) {
    return false; /* no data present */
  }
  if (McuRB_Get(ringBufferHndl, &keyData)!=ERR_OK) {
    return false; /* we had data in the buffer, but now not anymore? something went wrong! */
  }
  KeyPressForLCD();
  if (keyData&(LV_MASK_PRESSED|LV_MASK_PRESSED_LONG)) {
    data->state = LV_INDEV_STATE_PR;
  } else if (keyData&(LV_MASK_RELEASED|LV_MASK_RELEASED_LONG)) {
    data->state = LV_INDEV_STATE_REL;
  }
  data->key = MapKeyOrientation(keyData&0xff);
  return McuRB_NofElements(ringBufferHndl)!=0;   /* return true if we have more data */
}
#endif

#if PL_CONFIG_USE_GUI_KEY_NAV
static bool encoder_read(lv_indev_data_t *data){
  uint16_t keyData;

  memset(data, 0, sizeof(lv_indev_data_t)); /* initialize all fields */
  data->state = LV_INDEV_STATE_REL; /* by default, not pressed */
  if (McuRB_NofElements(ringBufferHndl)==0) {
    return false; /* no data present */
  }
  if (McuRB_Get(ringBufferHndl, &keyData)!=ERR_OK) {
    return false; /* we had data in the buffer, but now not anymore? something went wrong! */
  }
  KeyPressForLCD(); /* inform LCD timer that there is a user action */
  data->state = LV_INDEV_STATE_REL; /* default state */
  keyData = (keyData&0xff00) | MapKeyOrientation(keyData&0xff);
  /* keys are changing only enc_diff, except ENTER/CENTER/PUSH which sets the LV_INDEV_STATE_PR state */
  switch(keyData&0xff) {
    case LV_BTN_MASK_LEFT:
      if (keyData&(LV_MASK_PRESSED)) {
        data->enc_diff = -1;
        McuShell_SendStr((uint8_t*)"left pressed\r\n", McuShell_GetStdio()->stdOut);
      } else if (keyData&(LV_MASK_PRESSED_LONG)) {
        data->enc_diff = -1;
        McuShell_SendStr((uint8_t*)"left long pressed\r\n", McuShell_GetStdio()->stdOut);
      } else if (keyData&(LV_MASK_RELEASED_LONG)) {
        data->enc_diff = 0;
        McuShell_SendStr((uint8_t*)"left long released\r\n", McuShell_GetStdio()->stdOut);
      } else if (keyData&(LV_MASK_RELEASED)) {
        data->enc_diff = 0;
        McuShell_SendStr((uint8_t*)"left released\r\n", McuShell_GetStdio()->stdOut);
      }
      break;
    case LV_BTN_MASK_RIGHT:
      if (keyData&(LV_MASK_PRESSED)) {
        data->enc_diff = 1;
        McuShell_SendStr((uint8_t*)"right pressed\r\n", McuShell_GetStdio()->stdOut);
      } else if (keyData&(LV_MASK_PRESSED_LONG)) {
        data->enc_diff = 1;
        McuShell_SendStr((uint8_t*)"right long pressed\r\n", McuShell_GetStdio()->stdOut);
      } else if (keyData&(LV_MASK_RELEASED_LONG)) {
        data->enc_diff = 0;
        McuShell_SendStr((uint8_t*)"right long released\r\n", McuShell_GetStdio()->stdOut);
      } else if (keyData&(LV_MASK_RELEASED)) {
        data->enc_diff = 0;
        McuShell_SendStr((uint8_t*)"right released\r\n", McuShell_GetStdio()->stdOut);
      }
      break;
    case LV_BTN_MASK_UP:
      if (keyData&(LV_MASK_PRESSED)) {
        data->enc_diff = -1;
        McuShell_SendStr((uint8_t*)"up pressed\r\n", McuShell_GetStdio()->stdOut);
      } else if (keyData&(LV_MASK_PRESSED_LONG)) {
        data->enc_diff = -1;
        McuShell_SendStr((uint8_t*)"up long pressed\r\n", McuShell_GetStdio()->stdOut);
      } else if (keyData&(LV_MASK_RELEASED_LONG)) {
        data->enc_diff = 0;
        McuShell_SendStr((uint8_t*)"up long released\r\n", McuShell_GetStdio()->stdOut);
      } else if (keyData&(LV_MASK_RELEASED)) {
        data->enc_diff = 0;
        McuShell_SendStr((uint8_t*)"up released\r\n", McuShell_GetStdio()->stdOut);
      }
      break;
    case LV_BTN_MASK_DOWN:
      if (keyData&(LV_MASK_PRESSED)) {
        data->enc_diff = 1;
        McuShell_SendStr((uint8_t*)"down pressed\r\n", McuShell_GetStdio()->stdOut);
      } else if (keyData&(LV_MASK_PRESSED_LONG)) {
        data->enc_diff = 1;
        McuShell_SendStr((uint8_t*)"down long pressed\r\n", McuShell_GetStdio()->stdOut);
      } else if (keyData&(LV_MASK_RELEASED_LONG)) {
        data->enc_diff = 0;
        McuShell_SendStr((uint8_t*)"down long released\r\n", McuShell_GetStdio()->stdOut);
      } else if (keyData&(LV_MASK_RELEASED)) {
        data->enc_diff = 0;
        McuShell_SendStr((uint8_t*)"down released\r\n", McuShell_GetStdio()->stdOut);
      }
      break;
    case LV_BTN_MASK_CENTER:
      if (keyData&(LV_MASK_PRESSED)) {
        data->state = LV_INDEV_STATE_REL;
        data->enc_diff = 0;
        McuShell_SendStr((uint8_t*)"center pressed\r\n", McuShell_GetStdio()->stdOut);
      } else if (keyData&(LV_MASK_PRESSED_LONG)) {
        data->state = LV_INDEV_STATE_PR;
        data->enc_diff = 0;
        McuShell_SendStr((uint8_t*)"center long pressed\r\n", McuShell_GetStdio()->stdOut);
      } else if (keyData&(LV_MASK_RELEASED_LONG)) {
        data->state = LV_INDEV_STATE_REL;
        data->enc_diff = 0;
        McuShell_SendStr((uint8_t*)"center long released\r\n", McuShell_GetStdio()->stdOut);
      } else if (keyData&(LV_MASK_RELEASED)) {
        data->state = LV_INDEV_STATE_REL;
        data->enc_diff = 0;
        McuShell_SendStr((uint8_t*)"center released\r\n", McuShell_GetStdio()->stdOut);
      }
      break;
  #if 0
    case LV_BTN_MASK_NEXT:
      if (keyData&(LV_MASK_PRESSED)) {
        data->state = LV_INDEV_STATE_REL;
        data->enc_diff = 1;
      } else if (keyData&(LV_MASK_PRESSED_LONG)) {
        data->state = LV_INDEV_STATE_PR;
        data->enc_diff = 0;
      } else {
        data->state = LV_INDEV_STATE_REL;
        data->enc_diff = 0;
      }
      break;
    case LV_BTN_MASK_PREV:
      if (keyData&(LV_MASK_PRESSED_LONG)) {
        data->state = LV_INDEV_STATE_PR;
        data->enc_diff = 0;
      } else {
        data->state = LV_INDEV_STATE_REL;
        data->enc_diff = -1;
      }
      break;
  #endif
    default:
      return false; /* error case? */
  } /* switch */
  return McuRB_NofElements(ringBufferHndl)!=0;   /* return true if we have more data */
}
#endif

static lv_disp_buf_t disp_buf;
static lv_color_t buf[LV_HOR_RES_MAX * 10];                     /*Declare a buffer for 10 lines*/

void LV_Init(void) {
  lv_disp_drv_t disp_drv;

  lv_init();
  lv_disp_buf_init(&disp_buf, buf, NULL, LV_HOR_RES_MAX * 10);    /*Initialize the display buffer*/
  lv_disp_drv_init(&disp_drv);
  /*Set up the functions to access to your display*/
  disp_drv.flush_cb = ex_disp_flush;            /*Used in buffered mode (LV_VDB_SIZE != 0  in lv_conf.h)*/
  disp_drv.buffer = &disp_buf;          /*Assign the buffer to the display*/

#if USE_LV_GPU
  /*Optionally add functions to access the GPU. (Only in buffered mode, LV_VDB_SIZE != 0)*/
  disp_drv.mem_blend = ex_mem_blend;              /*Blend two color array using opacity*/
  disp_drv.mem_fill = ex_mem_fill;                /*Fill a memory array with a color*/
#endif

  /*Finally register the driver*/
  lv_disp_drv_register(&disp_drv);

  /*************************
   * Input device interface
   *************************/
  lv_indev_drv_t indev_drv;                       /*Descriptor of an input device driver*/
  lv_indev_drv_init(&indev_drv);                  /*Basic initialization*/
#if PL_CONFIG_USE_GUI_TOUCH_NAV /* touch pad */
  indev_drv.type = LV_INDEV_TYPE_POINTER;         /*The touchpad is pointer type device*/
  indev_drv.read_cb = ex_tp_read;                 /*Library ready your touchpad via this function*/
  inputDevicePtr = lv_indev_drv_register(&indev_drv);              /*Finally register the driver*/
#elif PL_CONFIG_USE_GUI_KEY_NAV
  indev_drv.type = LV_INDEV_TYPE_ENCODER;
  indev_drv.read = encoder_read;
  inputDevicePtr = lv_indev_drv_register(&indev_drv);              /*Finally register the driver*/
#elif PL_CONFIG_USE_GUI_KEYPAD_NAV /* keyboard input */
  indev_drv.type = LV_INDEV_TYPE_KEYPAD;
  indev_drv.read = keyboard_read;
  inputDevicePtr = lv_indev_drv_register(&indev_drv);              /*Finally register the driver*/
#endif

#if PL_CONFIG_USE_GUI_SCREEN_SAVER
  timerHndlLcdTimeout = xTimerCreate(
    "timerLCD", /* name */
    pdMS_TO_TICKS(SCREEN_SAVER_TIMEOUT_MS), /* period/time */
    pdFALSE, /* auto reload */
    (void*)1, /* timer ID */
    vTimerCallbackLCDExpired); /* callback */
  if (timerHndlLcdTimeout==NULL) {
    for(;;); /* failure! */
  }
  if (xTimerStart(timerHndlLcdTimeout, 0)!=pdPASS) {
    for(;;); /* failure!?! */
  }
#endif
  McuRB_Config_t config;

  McuRB_GetDefaultconfig(&config);
  config.elementSize = 2;
  config.nofElements = 16;
  ringBufferHndl = McuRB_InitRB(&config);
}
#endif /* PL_CONFIG_USE_GUI */
