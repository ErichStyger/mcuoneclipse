/*
 * gui.c
 *
 *  Created on: 03.08.2018
 *      Author: Erich Styger
 */
#include <platform.h>
#if PL_CONFIG_USE_LVGL

#include "gui.h"
#include "lv.h"
#include "LittlevGL/lvgl/lvgl.h"
#include "FreeRTOS.h"
#include "task.h"
#include "McuSSD1306.h"
#if PL_CONFIG_HAS_KEYS
  #include "KEY1.h"
#endif
//#include "gui_mainmenu.h"
#include "McuGDisplaySSD1306.h"
#include "McuFontDisplay.h"

static TaskHandle_t GUI_TaskHndl;

/* task notification bits */
#define GUI_SET_ORIENTATION_LANDSCAPE    (1<<0)
#define GUI_SET_ORIENTATION_LANDSCAPE180 (1<<1)
#define GUI_SET_ORIENTATION_PORTRAIT     (1<<2)
#define GUI_SET_ORIENTATION_PORTRAIT180  (1<<3)

#if PL_CONFIG_HAS_GUI_KEY_NAV
#define GUI_GROUP_NOF_IN_STACK   4
static GUI_Group_t groups;
typedef struct {
  lv_group_t *stack[GUI_GROUP_NOF_IN_STACK]; /* stack of GUI groups */
  uint8_t sp; /* stack pointer, points to next free element */
} GUI_Group_t;

/* style modification callback for the focus of an element */
static void style_mod_cb(lv_style_t *style) {
#if LV_COLOR_DEPTH != 1
    /*Make the style to be a little bit orange*/
    style->body.border.opa = LV_OPA_COVER;
    style->body.border.color = LV_COLOR_ORANGE;

    /*If not empty or has border then emphasis the border*/
    if(style->body.empty == 0 || style->body.border.width != 0) style->body.border.width = LV_DPI / 50;

    style->body.main_color = lv_color_mix(style->body.main_color, LV_COLOR_ORANGE, LV_OPA_70);
    style->body.grad_color = lv_color_mix(style->body.grad_color, LV_COLOR_ORANGE, LV_OPA_70);
    style->body.shadow.color = lv_color_mix(style->body.shadow.color, LV_COLOR_ORANGE, LV_OPA_60);

    style->text.color = lv_color_mix(style->text.color, LV_COLOR_ORANGE, LV_OPA_70);
#else
    style->body.border.opa = LV_OPA_COVER;
    style->body.border.color = LV_COLOR_BLACK;
    style->body.border.width = 3;
#endif
}

void GUI_AddObjToGroup(lv_obj_t *obj) {
  lv_group_add_obj(GUI_GroupPeek(), obj);
}

void GUI_RemoveObjFromGroup_(lv_obj_t *obj) {
  lv_group_remove_obj(obj);
}

lv_group_t *GUI_GroupPeek(void) {
  if (groups.sp == 0) {
    return NULL;
  }
  return groups.stack[groups.sp-1];
}

void GUI_GroupPull(void) {
  if (groups.sp == 0) {
    return;
  }
  lv_group_del(groups.stack[groups.sp-1]);
  groups.sp--;
  lv_indev_set_group(LV_GetInputDevice(), groups.stack[groups.sp-1]); /* assign group to input device */
}

void GUI_GroupPush(void) {
  lv_group_t *gui_group;

  if (groups.sp >= GUI_GROUP_NOF_IN_STACK) {
    return;
  }
  gui_group = lv_group_create();
  lv_indev_set_group(LV_GetInputDevice(), gui_group); /* assign group to input device */
  /* change the default focus style which is an orange'ish thing */
  lv_group_set_style_mod_cb(gui_group, style_mod_cb);
  groups.stack[groups.sp] = gui_group;
  groups.sp++;
}

#endif /* PL_CONFIG_HAS_GUI_KEY_NAV */

void GUI_ChangeOrientation(McuSSD1306_DisplayOrientation orientation) {
  switch(orientation) {
    case McuSSD1306_ORIENTATION_LANDSCAPE:
      (void)xTaskNotify(GUI_TaskHndl, GUI_SET_ORIENTATION_LANDSCAPE, eSetBits);
      break;
    case McuSSD1306_ORIENTATION_LANDSCAPE180:
      (void)xTaskNotify(GUI_TaskHndl, GUI_SET_ORIENTATION_LANDSCAPE180, eSetBits);
      break;
    case McuSSD1306_ORIENTATION_PORTRAIT:
      (void)xTaskNotify(GUI_TaskHndl, GUI_SET_ORIENTATION_PORTRAIT, eSetBits);
      break;
    case McuSSD1306_ORIENTATION_PORTRAIT180:
      (void)xTaskNotify(GUI_TaskHndl, GUI_SET_ORIENTATION_PORTRAIT180, eSetBits);
      break;
    default:
      break;
  }
}

void GUI_MainMenuCreate(void) {
#if 0
  lv_obj_t *gui_win;

  //GUI_GroupPush();
  /* create window */
  gui_win = lv_win_create(lv_scr_act(), NULL);
  lv_win_set_title(gui_win, "Main Menu");

  /* Make the window content responsive */
  lv_win_set_layout(gui_win, LV_LAYOUT_PRETTY); /* this will arrange the buttons */
#endif
#if 1
  /*Create a normal button*/
  lv_obj_t * btn1 = lv_btn_create(lv_scr_act(), NULL);
  lv_obj_set_pos(btn1, 5, 5);
  lv_obj_set_size(btn1, 60, 20);
  //lv_cont_set_fit(btn1, true, true); /*Enable resizing horizontally and vertically*/
//  lv_obj_align(btn1, label, LV_ALIGN_OUT_BOTTOM_MID, 0, 10);
  lv_obj_t *label = lv_label_create(btn1, NULL);
  lv_label_set_text(label, "Test abc");
//  lv_obj_set_free_num(btn1, 1);   /*Set a unique number for the button*/
  //lv_btn_set_action(btn1, LV_BTN_ACTION_CLICK, btn_click_action);

  /*Add a label to the button*/
 // label = lv_label_create(btn1, NULL);
  //lv_label_set_text(label, "Normal");
//  GUI_AddObjToGroup(btn1);
#endif
}

static void GuiTask(void *p) {
  uint32_t notifcationValue;

  vTaskDelay(pdMS_TO_TICKS(500)); /* give hardware time to power up */
  //LCD1_Init();
#if 0 /* display tests */
    McuGDisplaySSD1306_PixelDim x, y;
    char *str;
    x = y = 2;
    LCD1_SetDisplayOrientation(GDisp1_ORIENTATION_LANDSCAPE);
    if (GDisp1_GetDisplayOrientation()==GDisp1_ORIENTATION_LANDSCAPE) {
      str = "Landscape";
    } else  if (GDisp1_GetDisplayOrientation()==GDisp1_ORIENTATION_LANDSCAPE180) {
      str = "Landscape180";
    } else  if (GDisp1_GetDisplayOrientation()==GDisp1_ORIENTATION_PORTRAIT) {
      str = "Portrait";
    } else  if (GDisp1_GetDisplayOrientation()==GDisp1_ORIENTATION_PORTRAIT180) {
      str = "Portrait180";
    }

    GDisp1_Clear();
    GDisp1_DrawBox(0, 0, 50, 20, 2, GDisp1_COLOR_BLUE);
    FDisp1_WriteString(str, GDisp1_COLOR_RED, &x, &y, GFONT1_GetFont());
    GDisp1_UpdateFull();
#endif
    GUI_MainMenuCreate();
	for(;;) {
      (void)xTaskNotifyWait(0UL, GUI_SET_ORIENTATION_LANDSCAPE|GUI_SET_ORIENTATION_LANDSCAPE180|GUI_SET_ORIENTATION_PORTRAIT|GUI_SET_ORIENTATION_PORTRAIT180, &notifcationValue, 0); /* check flags */
      if (notifcationValue!=0) {
        lv_area_t area;

        if (notifcationValue&GUI_SET_ORIENTATION_LANDSCAPE) {
          McuGDisplaySSD1306_SetDisplayOrientation(McuGDisplaySSD1306_ORIENTATION_LANDSCAPE);
          area.x1 = 0;
          area.y1 = 0;
          area.x2 = McuGDisplaySSD1306_GetWidth()-1;
          area.y2 = McuGDisplaySSD1306_GetHeight()-1;
          lv_inv_area(&area);
          lv_refr_now();
        } else if (notifcationValue&GUI_SET_ORIENTATION_LANDSCAPE180) {
          McuGDisplaySSD1306_SetDisplayOrientation(McuGDisplaySSD1306_ORIENTATION_LANDSCAPE180);
          area.x1 = 0;
          area.y1 = 0;
          area.x2 = McuGDisplaySSD1306_GetWidth()-1;
          area.y2 = McuGDisplaySSD1306_GetHeight()-1;
          lv_inv_area(&area);
        } else if (notifcationValue&GUI_SET_ORIENTATION_PORTRAIT) {
          McuGDisplaySSD1306_SetDisplayOrientation(McuGDisplaySSD1306_ORIENTATION_PORTRAIT);
          area.x1 = 0;
          area.y1 = 0;
          area.x2 = McuGDisplaySSD1306_GetWidth()-1;
          area.y2 = McuGDisplaySSD1306_GetHeight()-1;
          lv_inv_area(&area);
        } else if (notifcationValue&GUI_SET_ORIENTATION_PORTRAIT180) {
          McuGDisplaySSD1306_SetDisplayOrientation(McuGDisplaySSD1306_ORIENTATION_PORTRAIT180);
          area.x1 = 0;
          area.y1 = 0;
          area.x2 = McuGDisplaySSD1306_GetWidth()-1;
          area.y2 = McuGDisplaySSD1306_GetHeight()-1;
          lv_inv_area(&area);
          lv_obj_invalidate(lv_scr_act());
        }
      }
      LV_Task(); /* call this every 1-20 ms */
  #if PL_CONFIG_HAS_KEYS
      KEY1_ScanKeys();
  #endif
	  vTaskDelay(pdMS_TO_TICKS(10));
   }
}

void GUI_Init(void) {
  LV_Init(); /* initialize GUI library */
  //lv_theme_set_current(lv_theme_night_init(128, NULL));
  //lv_theme_set_current(lv_theme_alien_init(128, NULL));
  //lv_theme_set_current(lv_theme_default_init(128, NULL));
  //lv_theme_set_current(lv_theme_material_init(128, NULL));
  lv_theme_set_current(lv_theme_mono_init(128, NULL));
  //lv_theme_set_current(lv_theme_zen_init(128, NULL));
  //lv_theme_set_current(lv_theme_nemo_init(128, NULL));

	//lv_theme_t *th = lv_theme_get_current();
	/* change default button style */
 // lv_style_btn_rel.body.radius = LV_DPI / 15;
 // lv_style_btn_rel.body.padding.hor = LV_DPI / 8;
 // lv_style_btn_rel.body.padding.ver = LV_DPI / 12;


  GUI_MainMenuCreate();


  if (xTaskCreate(GuiTask, "Gui", 2000/sizeof(StackType_t), NULL, tskIDLE_PRIORITY+1, &GUI_TaskHndl) != pdPASS) {
    for(;;){} /* error */
  }
#if PL_CONFIG_HAS_GUI_KEY_NAV
  groups.sp = 0;
#endif
}
#endif /* PL_CONFIG_HAS_GUI */
