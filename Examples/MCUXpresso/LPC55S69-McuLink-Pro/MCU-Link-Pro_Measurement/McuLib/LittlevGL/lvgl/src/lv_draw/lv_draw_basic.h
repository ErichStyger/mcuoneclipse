/**
 * @file lv_draw_basic.h
 *
 */

#ifndef LV_DRAW_BASIC_H
#define LV_DRAW_BASIC_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#ifdef LV_CONF_INCLUDE_SIMPLE
#include "lv_conf.h"
#else
#include "../../../lv_conf.h"
#endif

#include "../lv_font/lv_font.h"
#include "../lv_misc/lv_color.h"
#include "../lv_misc/lv_area.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/

void lv_draw_px(lv_coord_t x, lv_coord_t y, const lv_area_t * mask_p, lv_color_t color, lv_opa_t opa);
/**
 * Fill an area in the Virtual Display Buffer
 * @param cords_p coordinates of the area to fill
 * @param mask_p fill only o this mask
 * @param color fill color
 * @param opa opacity of the area (0..255)
 */
void lv_draw_fill(const lv_area_t * cords_p, const lv_area_t * mask_p, lv_color_t color, lv_opa_t opa);

/**
 * Draw a letter in the Virtual Display Buffer
 * @param pos_p left-top coordinate of the latter
 * @param mask_p the letter will be drawn only on this area
 * @param font_p pointer to font
 * @param letter a letter to draw
 * @param color color of letter
 * @param opa opacity of letter (0..255)
 */
void lv_draw_letter(const lv_point_t * pos_p, const lv_area_t * mask_p, const lv_font_t * font_p, uint32_t letter,
                    lv_color_t color, lv_opa_t opa);

/**
 * Draw a color map to the display (image)
 * @param cords_p coordinates the color map
 * @param mask_p the map will drawn only on this area  (truncated to VDB area)
 * @param map_p pointer to a lv_color_t array
 * @param opa opacity of the map
 * @param chroma_keyed true: enable transparency of LV_IMG_LV_COLOR_TRANSP color pixels
 * @param alpha_byte true: extra alpha byte is inserted for every pixel
 * @param recolor mix the pixels with this color
 * @param recolor_opa the intense of recoloring
 */
void lv_draw_map(const lv_area_t * cords_p, const lv_area_t * mask_p, const uint8_t * map_p, lv_opa_t opa,
                 bool chroma_key, bool alpha_byte, lv_color_t recolor, lv_opa_t recolor_opa);

/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*LV_DRAW_BASIC_H*/
