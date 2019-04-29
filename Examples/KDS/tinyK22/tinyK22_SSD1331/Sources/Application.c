/*
 * Application.c
 *
 *  Created on: 30.07.2018
 *      Author: Erich Styger
 */

#include "Application.h"
//#include "LED1.h"
#include "WAIT1.h"
#include "LCD1.h"
#include "GDisp1.h"
#include "GFont1.h"
#include "FDisp1.h"

#include "lv.h"
#include "lvgl.h"

static lv_res_t my_click_action(struct _lv_obj_t * obj) {
  return LV_RES_INV;
}

extern const lv_img_t default_sclera;

static void do_image(void) {
  lv_obj_t *img1 = lv_img_create(lv_scr_act(), NULL); /*Crate an image object*/
  lv_img_set_src(img1, &default_sclera);
  lv_obj_set_pos(img1, 0, 0);      /*Set the positions*/
}

static void lvgl_test(void) {
  /*Add a button*/
  lv_obj_t *btn1 = lv_btn_create(lv_scr_act(), NULL);             /*Add to the active screen*/
  lv_obj_set_pos(btn1, 2, 2);                                    /*Adjust the position*/
  lv_obj_set_size(btn1, 60, 20);
  lv_btn_set_action(btn1, LV_BTN_ACTION_CLICK, my_click_action);   /*Assign a callback for clicking*/

  /*Add text*/
  lv_obj_t * label = lv_label_create(btn1, NULL);                  /*Put on 'btn1'*/
  lv_label_set_text(label, "Click");
}

void lv_tutorial_hello_world(void) {
    /*Create a Label on the currently active screen*/
    lv_obj_t * label1 =  lv_label_create(lv_scr_act(), NULL);

    /*Modify the Label's text*/
    lv_label_set_text(label1, "Hello world!");

    /* Align the Label to the center
     * NULL means align on parent (which is the screen now)
     * 0, 0 at the end means an x, y offset after alignment*/
    lv_obj_align(label1, NULL, LV_ALIGN_CENTER, 0, 0);
}

#if 0
static void LCD_Test(void) {
  int x, y;
  FDisp1_PixelDim fx, fy;

  // LCD1_Off();
  // LCD1_On();
  GDisp1_SetDisplayOrientation(LCD1_ORIENTATION_LANDSCAPE);
  GDisp1_Clear();
  GDisp1_DrawFilledBox(0, 0, 60, 20, GDisp1_COLOR_RED);
  fx = fy = 0;
  FDisp1_WriteString("landscape", GDisp1_COLOR_WHITE, &fx, &fy, GFont1_GetFont());
  GDisp1_UpdateFull();

  GDisp1_SetDisplayOrientation(LCD1_ORIENTATION_LANDSCAPE180);
  GDisp1_Clear();
  GDisp1_DrawFilledBox(0, 0, 60, 20, GDisp1_COLOR_GREEN);
  fx = fy = 0;
  FDisp1_WriteString("landscape180", GDisp1_COLOR_WHITE, &fx, &fy, GFont1_GetFont());
  GDisp1_UpdateFull();

  GDisp1_SetDisplayOrientation(LCD1_ORIENTATION_PORTRAIT);
  GDisp1_Clear();
  GDisp1_DrawFilledBox(0, 0, 60, 20, GDisp1_COLOR_BLUE);
  fx = fy = 0;
  FDisp1_WriteString("portrait", GDisp1_COLOR_WHITE, &fx, &fy, GFont1_GetFont());
  GDisp1_UpdateFull();

  GDisp1_SetDisplayOrientation(LCD1_ORIENTATION_PORTRAIT180);
  GDisp1_Clear();
  GDisp1_DrawFilledBox(0, 0, 60, 20, GDisp1_COLOR_YELLOW);
  fx = fy = 0;
  FDisp1_WriteString("portrait180", GDisp1_COLOR_WHITE, &fx, &fy, GFont1_GetFont());
  GDisp1_UpdateFull();
  GDisp1_SetDisplayOrientation(LCD1_ORIENTATION_LANDSCAPE); /* get back to landscape, as this is what we use for LittlevGL */
}
#endif

void APP_Run(void) {
  //LCD_Test();
  GDisp1_Clear();
  GDisp1_DrawFilledBox(0, 0, 60, 20, GDisp1_COLOR_RED);
  GDisp1_UpdateFull();

  LV_Init(); /* initialize GUI library */
  //lvgl_test(); /* create test GUI */
  do_image();
  for(;;) {
   // LED1_Neg();
    LV_Task();
    WAIT1_Waitms(5);
 //   lv_tutorial_hello_world();
 //   LV_Task();
 //   WAIT1_Waitms(5);
  }
}
