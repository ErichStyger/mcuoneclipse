/*
 * Copyright (c) 2019, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
 
#include "platform.h"
#if PL_CONFIG_USE_GUI
#include "lv.h"
#include "LittlevGL/lvgl/lvgl.h"
#include "McuGDisplaySSD1306.h"
#include "McuSSD1306.h"
#include "McuRB.h"
#include <string.h> /* for memset() */
#include "McuShell.h"
#include "McuRTOS.h"
#include "McuLog.h"
#include "lcd.h"
#include "gui.h"

static McuRB_Handle_t ringBufferHndl;

#define LVGL_TICK_TIMER_PERIOD_MS  (1)
static TimerHandle_t timerHndlLvglTick;

static void vTimerCallbackLvglTick(TimerHandle_t pxTimer) {
  lv_tick_inc(LVGL_TICK_TIMER_PERIOD_MS);
}

static lv_indev_t *inputDevicePtr;

lv_indev_t *LV_GetInputDevice(void) {
  return inputDevicePtr;
}

/* Flush the content of the internal buffer the specific area on the display
 * You can use DMA or any hardware acceleration to do this operation in the background but
 * 'lv_flush_ready()' has to be called when finished
 * This function is required only when LV_VDB_SIZE != 0 in lv_conf.h*/
static void myDispFlush(lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p) {
  /*The most simple case (but also the slowest) to put all pixels to the screen one-by-one*/
  int32_t x, y;
  int32_t x1, y1, x2, y2;

  x1 = area->x1;
  y1 = area->y1;
  x2 = area->x2;
  y2 = area->y2;
  for(y = y1; y <= y2; y++) {
    for(x = x1; x <= x2; x++) {
      /* Put a pixel to the display. */
      LCD_SetPixel(x, y, color_p->full);
      color_p++;
    }
  }
  LCD_UpdateRegion(x1, y1, x2-x1+1, y2-y1+1);
  /* IMPORTANT!!!
   * Inform the graphics library that you are ready with the flushing*/
  lv_disp_flush_ready(disp_drv);
}

void LV_Task(void) {
  /* Periodically call this function.
   * The timing is not critical but should be between 1..10 ms */
  lv_task_handler();
}

/* called for push button events from Events.c */
void LV_ButtonEvent(uint8_t keys, uint16_t eventMask) {
  uint16_t buttonInfo;
  uint8_t res = ERR_OK;

  if (keys&LV_BTN_MASK_CENTER) {
    buttonInfo = LV_BTN_MASK_CENTER | eventMask;
    res = McuRB_Put(ringBufferHndl, &buttonInfo);
  } else if (keys&LV_BTN_MASK_RIGHT) {
    buttonInfo = LV_BTN_MASK_RIGHT | eventMask;
    res = McuRB_Put(ringBufferHndl, &buttonInfo);
  } else if (keys&LV_BTN_MASK_DOWN) {
    buttonInfo = LV_BTN_MASK_DOWN | eventMask;
    res = McuRB_Put(ringBufferHndl, &buttonInfo);
  } else if (keys&LV_BTN_MASK_UP) {
    buttonInfo = LV_BTN_MASK_UP | eventMask;
    res = McuRB_Put(ringBufferHndl, &buttonInfo);
  } else if (keys&LV_BTN_MASK_LEFT) {
    buttonInfo = LV_BTN_MASK_LEFT | eventMask;
    res = McuRB_Put(ringBufferHndl, &buttonInfo);
  } else if (keys&LV_BTN_MASK_PREV) {
    buttonInfo = LV_BTN_MASK_PREV | eventMask;
    res = McuRB_Put(ringBufferHndl, &buttonInfo);
  } else if (keys&LV_BTN_MASK_NEXT) {
    buttonInfo = LV_BTN_MASK_NEXT | eventMask;
    res = McuRB_Put(ringBufferHndl, &buttonInfo);
  }
  if (res!=ERR_OK) {
    McuLog_fatal("failed enter key into ring buffer");
  }
}

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
        case LV_BTN_MASK_PREV:
          key = LV_BTN_MASK_PREV;
          break;
        case LV_BTN_MASK_NEXT:
          key = LV_BTN_MASK_NEXT;
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
        case LV_BTN_MASK_PREV:
          key = LV_BTN_MASK_PREV;
          break;
        case LV_BTN_MASK_NEXT:
          key = LV_BTN_MASK_NEXT;
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
        case LV_BTN_MASK_PREV:
          key = LV_BTN_MASK_NEXT;
          break;
        case LV_BTN_MASK_NEXT:
          key = LV_BTN_MASK_PREV;
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
        case LV_BTN_MASK_PREV:
          key = LV_BTN_MASK_PREV;
          break;
        case LV_BTN_MASK_NEXT:
          key = LV_BTN_MASK_NEXT;
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

static void button_read(lv_indev_drv_t *indev_drv, lv_indev_data_t *data) {
  /* this callback gets called by LVGL to get the current button status */
  uint16_t keyData;

  (void)indev_drv; /* not used */
  memset(data, 0, sizeof(lv_indev_data_t)); /* initialize all fields */
  data->state = LV_INDEV_STATE_RELEASED; /* by default, not pressed */
  data->key = LV_KEY_ESC; /* default, not a normal keypad key */
  data->enc_diff = 0; /* default */
  data->continue_reading = false; /* by default, do not continue reading */
  if (McuRB_NofElements(ringBufferHndl)==0) {
    return; /* no data present */
  }
  if (McuRB_Get(ringBufferHndl, &keyData)!=ERR_OK) {
    return; /* we had data in the buffer, but now not anymore? something went wrong! */
  }
  GUI_NotifyUserAction(); /* inform about a user action */

#if McuSSD1306_CONFIG_DYNAMIC_DISPLAY_ORIENTATION
  keyData = (keyData&0xff00) | MapKeyOrientation(keyData&0xff);
#endif
  /* assign the key to return to LVGL */
#if PL_CONFIG_USE_BUTTON_NEXT_PREV
  switch(keyData&0xff) {
    case LV_BTN_MASK_PREV:      data->key = LV_KEY_PREV;  break;
    case LV_BTN_MASK_NEXT:      data->key = LV_KEY_NEXT;  break;
    case LV_BTN_MASK_LEFT:      data->key = LV_KEY_LEFT;  break;
    case LV_BTN_MASK_RIGHT:     data->key = LV_KEY_RIGHT; break;
    case LV_BTN_MASK_UP:        data->key = LV_KEY_UP;    break;
    case LV_BTN_MASK_DOWN:      data->key = LV_KEY_DOWN;  break;
    case LV_BTN_MASK_CENTER:    data->key = LV_KEY_ENTER; break;
    default:  data->key = LV_KEY_ESC; break;
  } /* switch */
#else
  /* only have nav switch */
  /* other idea: https://github.com/foldedtoad/ssd1306_lvgl
   * btn0: iterate through screens
   * btn1: iterate through editable items (group)
   * btn2: increase field value
   * btn3: decrease field value
   */
  switch(keyData&0xff) {
    case LV_BTN_MASK_PREV:      data->key = LV_KEY_ESC;   break; /* dummy */
    case LV_BTN_MASK_NEXT:      data->key = LV_KEY_ESC;   break; /* dummy */
    case LV_BTN_MASK_LEFT:      data->key = LV_KEY_PREV;  break;
    case LV_BTN_MASK_RIGHT:     data->key = LV_KEY_NEXT;  break;
    case LV_BTN_MASK_UP:        data->key = LV_KEY_UP;    break;
    case LV_BTN_MASK_DOWN:      data->key = LV_KEY_DOWN;  break;
    case LV_BTN_MASK_CENTER:    data->key = LV_KEY_ENTER; break;
    default:  data->key = LV_KEY_ESC; break;
  } /* switch */
#endif
  /* determine the button status */
  if (keyData&(LV_MASK_PRESSED)) {
    data->state = LV_INDEV_STATE_PRESSED;
  } else if (keyData&(LV_MASK_PRESSED_LONG)) {
    data->state = LV_INDEV_STATE_PRESSED;
  } else if (keyData&(LV_MASK_RELEASED_LONG)) {
    data->state = LV_INDEV_STATE_RELEASED;
  } else if (keyData&(LV_MASK_RELEASED)) {
    data->state = LV_INDEV_STATE_RELEASED;
  } else { /* should not happen? */
    data->state = LV_INDEV_STATE_RELEASED;
  }
  data->continue_reading = McuRB_NofElements(ringBufferHndl)!=0;   /* return true if we have more data */
}

void LV_ClearButtonEventQueue(void) {
  McuRB_Clear(ringBufferHndl);
}

#define DISP_BUF_SIZE (LV_HOR_RES*LV_VER_RES/8)

static lv_disp_draw_buf_t draw_buf; /* drawing buffer handle */
static lv_color_t buf1[DISP_BUF_SIZE]; /* for best performance, using a buffer with the size of the display */
static lv_disp_drv_t disp_drv; /* display driver */
static lv_disp_t *disp;
static lv_indev_drv_t indev_drv;                       /*Descriptor of an input device driver*/

void LV_Init(void) {
  lv_init(); /* initialize lvgl */
  lv_disp_draw_buf_init(&draw_buf, buf1, NULL, DISP_BUF_SIZE);
  lv_disp_drv_init(&disp_drv);      /* basic display driver initialization */
  disp_drv.flush_cb = myDispFlush;  /* set driver display upate function */
  disp_drv.draw_buf = &draw_buf;    /* Assign the buffer to the display */
  disp_drv.hor_res = LV_HOR_RES;    /* Set the horizontal resolution of the display */
  disp_drv.ver_res = LV_VER_RES;    /* Set the vertical resolution of the display */
  disp = lv_disp_drv_register(&disp_drv); /* Finally register the driver */

  lv_theme_t* theme = lv_theme_mono_init(disp, true/*dark bg*/, LV_FONT_DEFAULT);
  lv_disp_set_theme(disp, theme);

  /*************************
   * Input device interface
   *************************/
  lv_indev_drv_init(&indev_drv);                  /*Basic initialization*/
#if 0 /* touch pad */
  indev_drv.type = LV_INDEV_TYPE_POINTER;         /*The touchpad is pointer type device*/
  indev_drv.read_cb = ex_tp_read;                 /*Library ready your touchpad via this function*/
#elif 0
  indev_drv.type = LV_INDEV_TYPE_ENCODER;
  indev_drv.read_cb = button_read;
#else /* keyboard input */
  indev_drv.type = LV_INDEV_TYPE_KEYPAD;
  indev_drv.read_cb = button_read;
#endif
  inputDevicePtr = lv_indev_drv_register(&indev_drv);              /*Finally register the driver*/

  /* use FreeRTOS tick timer as timer base for LVGL, so it works with tickless idle mode too */
  timerHndlLvglTick = xTimerCreate(
    "lvglTick", /* name */
    pdMS_TO_TICKS(LVGL_TICK_TIMER_PERIOD_MS), /* period/time */
    pdTRUE, /* auto reload */
    (void*)1, /* timer ID */
    vTimerCallbackLvglTick); /* callback */
  if (timerHndlLvglTick==NULL) {
    McuLog_fatal("failed creating lvgl tick timer");
    for(;;); /* failure! */
  }
  if (xTimerStart(timerHndlLvglTick, 0)!=pdPASS) {
    McuLog_fatal("failed starting lvgl tick timer");
    for(;;); /* failure!?! */
  }

  McuRB_Config_t config;

  McuRB_GetDefaultconfig(&config);
  config.elementSize = 2;
  config.nofElements = 16;
  ringBufferHndl = McuRB_InitRB(&config);
}
#endif /* PL_CONFIG_USE_GUI */
