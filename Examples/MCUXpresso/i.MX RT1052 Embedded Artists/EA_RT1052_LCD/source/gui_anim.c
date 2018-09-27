/*
 * gui_anim.c
 *
 *      Author: Erich Styger
 */

#include "Platform.h"
#if PL_CONFIG_USE_GUI_ANIMATION
#include "gui_anim.h"
#include "gui_mainmenu.h"
#include "lvgl/lvgl.h"
#include "lvgl/lv_misc/lv_anim.h"

static lv_obj_t *win;

/**
 * Called when the window's close button is clicked
 * @param btn pointer to the close button
 * @return LV_ACTION_RES_INV because the window is deleted in the function
 */
static lv_res_t win_close_action(lv_obj_t *btn) {
    lv_obj_del(win);
    win = NULL;
    GUI_MainMenu_Create();
    return LV_RES_INV;
}

static void animation(void *p, int32_t val) {
	lv_obj_set_height((lv_obj_t*)p, val);
}

void gui_anim_create(void) {
	lv_obj_t *label;

    win = lv_win_create(lv_scr_act(), NULL);
    lv_win_set_title(win, "Animation");
    lv_win_add_btn(win, SYMBOL_CLOSE, win_close_action);

    /* Make the window content responsive */
    lv_win_set_layout(win, LV_LAYOUT_PRETTY);

	lv_obj_t *button1 = lv_btn_create(win, NULL);             /*Add to the active window */
	label = lv_label_create(button1, NULL);                  /*Put on 'button'*/
	lv_label_set_text(label, "Animated");

    lv_anim_t a;
    a.var = button1;							 /*Variable to animate*/
    a.start = 50;								 /*Start value*/
    a.end = 150;								 /*End value*/
    a.fp = animation;		 					 /*Function to be used to animate*/
    a.path = lv_anim_path_linear;                /*Path of animation*/
    a.end_cb = NULL; 						 	 /*Callback when the animation is ready*/
    a.act_time = 0;								 /*Set < 0 to make a delay [ms]*/
    a.time = lv_anim_speed_to_time(500, a.start, a.end);								 /*Animation length [ms]*/
    a.playback = 1;								 /*1: animate in reverse direction too when the normal is ready*/
    a.playback_pause = 500;						 /*Wait before playback [ms]*/
    a.repeat = 1;								 /*1: Repeat the animation (with or without playback)*/
    a.repeat_pause = 500;						 /*Wait before repeat [ms]*/

    lv_anim_create(&a);                          /*Start the animation*/

    lv_anim_speed_to_time(20, 0, 100);
}
#endif /* PL_CONFIG_USE_GUI_ANIMATION */
