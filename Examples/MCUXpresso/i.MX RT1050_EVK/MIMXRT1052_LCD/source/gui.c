/*
 * gui.c
 *
 *  Created on: 03.08.2018
 *      Author: Erich Styger Local
 */
#include "gui.h"
#include "lv.h"
#include "lvgl.h"

/**
 * Called when a button is released
 * @param btn pointer to the released button
 * @return LV_RES_OK because the object is not deleted in this function
 */
static  lv_res_t btn_rel_action(lv_obj_t * btn) {
    /*Increase the button width*/
    lv_coord_t width = lv_obj_get_width(btn);
    lv_obj_set_width(btn, width + 20);

    return LV_RES_OK;
}

/**
 * Called when a new option is chosen in the drop down list
 * @param ddlist pointer to the drop down list
 * @return LV_RES_OK because the object is not deleted in this function
 */
static  lv_res_t ddlist_action(lv_obj_t * ddlist) {
    uint16_t opt = lv_ddlist_get_selected(ddlist);      /*Get the id of selected option*/

    lv_obj_t * slider = lv_obj_get_free_ptr(ddlist);      /*Get the saved slider*/
    lv_slider_set_value(slider, (opt * 100) / 4);       /*Modify the slider value according to the selection*/
    return LV_RES_OK;
}

void lv_tutorial_objects(void) {
    /********************
     * CREATE A SCREEN
     *******************/
    /* Create a new screen and load it
     * Screen can be created from any type object type
     * Now a Page is used which is an objects with scrollable content*/
    lv_obj_t * scr = lv_page_create(NULL, NULL);
    lv_scr_load(scr);

    /****************
     * ADD A TITLE
     ****************/
    lv_obj_t * label = lv_label_create(scr, NULL); /*First parameters (scr) is the parent*/
    lv_label_set_text(label, "Object usage demo");  /*Set the text*/
    lv_obj_set_x(label, 50);                        /*Set the x coordinate*/

    /***********************
     * CREATE TWO BUTTONS
     ***********************/
    /*Create a button*/
    lv_obj_t * btn1 = lv_btn_create(lv_scr_act(), NULL);         /*Create a button on the currently loaded screen*/
    lv_btn_set_action(btn1, LV_BTN_ACTION_CLICK, btn_rel_action); /*Set function to be called when the button is released*/
    lv_obj_align(btn1, label, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 10);  /*Align below the label*/

    /*Create a label on the button (the 'label' variable can be reused)*/
    label = lv_label_create(btn1, NULL);
    lv_label_set_text(label, "Button 1");

    /*Copy the previous button*/
    lv_obj_t * btn2 = lv_btn_create(lv_scr_act(), btn1);        /*Second parameter is an object to copy*/
    lv_obj_align(btn2, btn1, LV_ALIGN_OUT_RIGHT_MID, 50, 0);    /*Align next to the prev. button.*/

    /*Create a label on the button*/
    label = lv_label_create(btn2, NULL);
    lv_label_set_text(label, "Button 2");

    /****************
     * ADD A SLIDER
     ****************/
    lv_obj_t * slider = lv_slider_create(scr, NULL);                            /*Create a slider*/
    lv_obj_set_size(slider, lv_obj_get_width(lv_scr_act())  / 3, LV_DPI / 3);   /*Set the size*/
    lv_obj_align(slider, btn1, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 10);                /*Align below the first button*/
    lv_slider_set_value(slider, 30);                                            /*Set the current value*/

    /***********************
     * ADD A DROP DOWN LIST
     ************************/
    lv_obj_t * ddlist = lv_ddlist_create(lv_scr_act(), NULL);            /*Create a drop down list*/
    lv_obj_align(ddlist, slider, LV_ALIGN_OUT_RIGHT_TOP, 50, 0);         /*Align next to the slider*/
    lv_obj_set_free_ptr(ddlist, slider);                                   /*Save the pointer of the slider in the ddlist (used in 'ddlist_action()')*/
    lv_obj_set_top(ddlist, true);                                        /*Enable to be on the top when clicked*/
    lv_ddlist_set_options(ddlist, "None\nLittle\nHalf\nA lot\nAll"); /*Set the options*/
    lv_ddlist_set_action(ddlist, ddlist_action);                         /*Set function to call on new option is chosen*/

    /****************
     * CREATE A CHART
     ****************/
    lv_obj_t * chart = lv_chart_create(lv_scr_act(), NULL);                         /*Create the chart*/
    lv_obj_set_size(chart, lv_obj_get_width(scr) / 2, lv_obj_get_width(scr) / 4);   /*Set the size*/
    lv_obj_align(chart, slider, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 10);                   /*Align below the slider*/
    lv_chart_set_series_width(chart, 3);                                            /*Set the line width*/

    /*Add a RED data series and set some points*/
    lv_chart_series_t * dl1 = lv_chart_add_series(chart, LV_COLOR_RED);
    lv_chart_set_next(chart, dl1, 10);
    lv_chart_set_next(chart, dl1, 25);
    lv_chart_set_next(chart, dl1, 45);
    lv_chart_set_next(chart, dl1, 80);

    /*Add a BLUE data series and set some points*/
    lv_chart_series_t * dl2 = lv_chart_add_series(chart, LV_COLOR_MAKE(0x40, 0x70, 0xC0));
    lv_chart_set_next(chart, dl2, 10);
    lv_chart_set_next(chart, dl2, 25);
    lv_chart_set_next(chart, dl2, 45);
    lv_chart_set_next(chart, dl2, 80);
    lv_chart_set_next(chart, dl2, 75);
    lv_chart_set_next(chart, dl2, 505);
}

static lv_res_t my_click_action(struct _lv_obj_t * obj) {
  return LV_RES_INV;
}

static void lvgl_test(void) {
  /*Add a button*/
  lv_obj_t * btn1 = lv_btn_create(lv_scr_act(), NULL);             /*Add to the active screen*/
  lv_obj_set_pos(btn1, 2, 2);                                    /*Adjust the position*/
  lv_obj_set_size(btn1, 96, 30);
  lv_btn_set_action(btn1, LV_BTN_ACTION_CLICK, my_click_action);   /*Assign a callback for clicking*/

  /*Add text*/
  lv_obj_t * label = lv_label_create(btn1, NULL);                  /*Put on 'btn1'*/
  lv_label_set_text(label, "Click");
}

static void lv_tutorial_hello_world(void) {
    /*Create a Label on the currently active screen*/
    lv_obj_t *label1 =  lv_label_create(lv_scr_act(), NULL);

    /*Modify the Label's text*/
    lv_label_set_text(label1, "Hello world!");

    /* Align the Label to the center
     * NULL means align on parent (which is the screen now)
     * 0, 0 at the end means an x, y offset after alignment*/
    lv_obj_align(label1, NULL, LV_ALIGN_CENTER, 0, 0);
}

void GUI_Run(void) {
	lv_tutorial_objects();
	//lv_tutorial_hello_world();
	//lvgl_test();
}
