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

void gui_anim_create(void) {
   // refr_task = lv_task_create(refresh_task, REFR_TIME, LV_TASK_PRIO_LOW, NULL);

    win = lv_win_create(lv_scr_act(), NULL);
    lv_win_set_title(win, "Animation");
    lv_win_add_btn(win, SYMBOL_CLOSE, win_close_action);

    /* Make the window content responsive */
    lv_win_set_layout(win, LV_LAYOUT_PRETTY);

}
#endif /* PL_CONFIG_USE_GUI_ANIMATION */
