/** ###################################################################
**     Filename  : Tetris.C
**     Project   : Tower_LCD
**     Processor : MCF51JM128VLH
**     Compiler  : CodeWarrior ColdFireV1 C Compiler
**     Date/Time : 07.01.2010, 13:11
**     Contents  :
**         User source code
**
** ###################################################################*/

/* MODULE Tetris */

#include "Platform.h"

#if PL_HAS_TETRIS_DEMO

#include "Tetris.h"

#include <string.h>   
#include <stdlib.h>

#include "PE_Types.h"
#include "GDisp1.h"
#include "UTIL1.h"
#include "UTIL1.h"
#include "Platform.h"
#include "FRTOS1.h"
#include "EVNT1.h"
#include "Helv12n.h"
#include "App.h"

#define FONT                Helv12n_GetFont()
#define POLL_KEYS    0 /* 1 if we shall directly poll the keys */

static bool TETRIS_isRunning = FALSE;
static TETRIS_WindowDesc *AppDesc;

//  FONT SHAPES

const uint16_t fnt_pal[] = {
0x0000, 0x8410, 0xA534, 0xFFFF 
};

const uint8_t fnt_0[] = {
0x00, 0x03, 0x03, 0x01, 0x00, 0x03, 0x03, 0x00, 0x00, 0x03, 0x03, 0x02, 0x00, 0x03, 0x03, 0x02, 
0x00, 0x03, 0x03, 0x00, 0x00, 0x03, 0x03, 0x01, 0x00
};
const uint8_t fnt_1[] = {
0x00, 0x01, 0x03, 0x01, 0x00, 0x01, 0x03, 0x03, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x03, 0x01, 
0x00, 0x00, 0x00, 0x01, 0x03, 0x01, 0x00, 0x01, 0x03, 0x03, 0x01, 0x01
};
const uint8_t fnt_2[] = {
0x00, 0x03, 0x03, 0x01, 0x00, 0x03, 0x00, 0x00, 0x00, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00, 0x03, 
0x03, 0x00, 0x01, 0x01, 0x00, 0x03, 0x03, 0x00, 0x01, 0x00, 0x03, 0x03, 0x03
};
const uint8_t fnt_3[] = {
0x03, 0x03, 0x02, 0x00, 0x00, 0x02, 0x03, 0x03, 0x04, 0x00, 0x00, 0x02, 0x03, 0x03, 0x04, 0x00
};
const uint8_t fnt_4[] = {
0x00, 0x01, 0x03, 0x03, 0x00, 0x00, 0x01, 0x03, 0x01, 0x03, 0x00, 0x02, 0x03, 0x01, 0x03, 0x00, 
0x03, 0x03, 0x03, 0x00, 0x00, 0x00, 0x01, 0x03, 0x00
};
const uint8_t fnt_5[] = {
0x03, 0x03, 0x05, 0x00, 0x00, 0x01, 0x03, 0x03, 0x02, 0x01, 0x00, 0x00, 0x01, 0x03, 0x03, 0x04, 
0x01
};
const uint8_t fnt_6[] = {
0x00, 0x03, 0x03, 0x04, 0x00, 0x00, 0x01, 0x03, 0x03, 0x02, 0x01, 0x03, 0x03, 0x00, 0x00, 0x00, 
0x00, 0x03, 0x00, 0x03, 0x03, 0x01, 0x01
};
const uint8_t fnt_7[] = {
0x03, 0x03, 0x03, 0x00, 0x00, 0x01, 0x01, 0x03, 0x00, 0x00, 0x00, 0x02, 0x03, 0x01, 0x00, 0x01, 
0x03, 0x02, 0x00, 0x00, 0x00, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00
};
const uint8_t fnt_8[] = {
0x00, 0x03, 0x03, 0x01, 0x00, 0x03, 0x03, 0x00, 0x00, 0x03, 0x03, 0x00, 0x00, 0x03, 0x03, 0x01, 
0x00, 0x03, 0x03, 0x00, 0x00, 0x03, 0x03, 0x00, 0x00, 0x03, 0x03, 0x01, 0x00
};
const uint8_t fnt_9[] = {
0x00, 0x03, 0x03, 0x01, 0x00, 0x03, 0x00, 0x00, 0x00, 0x03, 0x03, 0x00, 0x02, 0x03, 0x03, 0x02, 
0x00, 0x00, 0x01, 0x03, 0x03, 0x04, 0x00, 0x00, 0x00
};
const uint8_t fnt_a[] = {
0x00, 0x03, 0x03, 0x01, 0x00, 0x03, 0x03, 0x00, 0x00, 0x03, 0x03, 0x07, 0x00, 0x03, 0x03, 0x02, 
0x00, 0x03, 0x03, 0x00
};
const uint8_t fnt_b[] = {
0x03, 0x03, 0x02, 0x00, 0x03, 0x03, 0x00, 0x00, 0x03, 0x03, 0x04, 0x00, 0x03, 0x03, 0x00, 0x00, 
0x03, 0x03, 0x04, 0x00
};
const uint8_t fnt_c[] = {
0x00, 0x03, 0x03, 0x01, 0x00, 0x03, 0x03, 0x00, 0x00, 0x03, 0x03, 0x02, 0x00, 0x00, 0x01, 0x03, 
0x03, 0x00, 0x00, 0x03, 0x03, 0x00, 0x00, 0x03, 0x03, 0x01, 0x00
};
const uint8_t fnt_d[] = {
0x03, 0x03, 0x02, 0x00, 0x03, 0x03, 0x00, 0x00, 0x03, 0x03, 0x02, 0x00, 0x03, 0x03, 0x02, 0x00, 
0x03, 0x03, 0x04, 0x00
};
const uint8_t fnt_e[] = {
0x03, 0x03, 0x05, 0x00, 0x00, 0x01, 0x03, 0x03, 0x05, 0x00, 0x00, 0x01, 0x03, 0x03, 0x03
};
const uint8_t fnt_f[] = {
0x03, 0x03, 0x05, 0x00, 0x00, 0x01, 0x03, 0x03, 0x05, 0x00, 0x00, 0x01, 0x03, 0x03, 0x00, 0x00, 
0x00, 0x01
};
const uint8_t fnt_g[] = {
0x00, 0x03, 0x03, 0x04, 0x00, 0x00, 0x01, 0x03, 0x03, 0x00, 0x00, 0x03, 0x03, 0x02, 0x00, 0x03, 
0x03, 0x00, 0x00, 0x03, 0x03, 0x01, 0x02
};
const uint8_t fnt_h[] = {
0x03, 0x03, 0x00, 0x00, 0x03, 0x03, 0x02, 0x00, 0x03, 0x03, 0x07, 0x00, 0x03, 0x03, 0x02, 0x00, 
0x03, 0x03, 0x00
};
const uint8_t fnt_i[] = {
0x03, 0x03, 0x03, 0x00, 0x02, 0x03, 0x01, 0x00, 0x00, 0x00, 0x02, 0x03, 0x01, 0x00, 0x00, 0x00, 
0x02, 0x03, 0x01, 0x00, 0x03, 0x03, 0x03
};
const uint8_t fnt_j[] = {
0x03, 0x03, 0x03, 0x00, 0x00, 0x00, 0x03, 0x03, 0x00, 0x00, 0x00, 0x01, 0x03, 0x03, 0x00, 0x00, 
0x00, 0x01, 0x03, 0x03, 0x00, 0x00, 0x03, 0x03, 0x01, 0x02, 0x00
};
const uint8_t fnt_k[] = {
0x03, 0x03, 0x00, 0x00, 0x01, 0x03, 0x03, 0x01, 0x02, 0x03, 0x01, 0x03, 0x03, 0x01, 0x00, 0x00, 
0x00, 0x03, 0x03, 0x00, 0x02, 0x03, 0x01, 0x03, 0x03, 0x00, 0x00, 0x01, 0x03
};
const uint8_t fnt_l[] = {
0x03, 0x03, 0x00, 0x00, 0x00, 0x01, 0x03, 0x03, 0x00, 0x00, 0x00, 0x01, 0x03, 0x03, 0x00, 0x00, 
0x00, 0x01, 0x03, 0x03, 0x00, 0x00, 0x00, 0x01, 0x03, 0x03, 0x03
};
const uint8_t fnt_m[] = {
0x03, 0x03, 0x00, 0x00, 0x03, 0x03, 0x07, 0x00, 0x03, 0x03, 0x02, 0x00, 0x03, 0x03, 0x02, 0x00, 
0x03, 0x03, 0x00
};
const uint8_t fnt_n[] = {
0x03, 0x03, 0x01, 0x02, 0x00, 0x03, 0x03, 0x00, 0x00, 0x03, 0x02, 0x03, 0x03, 0x00, 0x00, 0x03, 
0x03, 0x02, 0x00, 0x03, 0x03, 0x02, 0x00, 0x03, 0x03, 0x00
};
const uint8_t fnt_o[] = {
0x00, 0x03, 0x03, 0x01, 0x00, 0x03, 0x03, 0x00, 0x00, 0x03, 0x03, 0x02, 0x00, 0x03, 0x03, 0x02, 
0x00, 0x03, 0x03, 0x00, 0x00, 0x03, 0x03, 0x01, 0x00
};
const uint8_t fnt_p[] = {
0x03, 0x03, 0x02, 0x00, 0x03, 0x03, 0x00, 0x00, 0x03, 0x03, 0x04, 0x00, 0x03, 0x03, 0x00, 0x00, 
0x00, 0x01, 0x03, 0x03, 0x00, 0x00, 0x00, 0x01
};
const uint8_t fnt_q[] = {
0x00, 0x03, 0x03, 0x01, 0x00, 0x03, 0x03, 0x00, 0x00, 0x03, 0x03, 0x02, 0x00, 0x03, 0x03, 0x04, 
0x01, 0x00, 0x03, 0x03, 0x00, 0x01, 0x03
};
const uint8_t fnt_r[] = {
0x03, 0x03, 0x02, 0x00, 0x03, 0x03, 0x00, 0x00, 0x03, 0x03, 0x04, 0x00, 0x03, 0x03, 0x00, 0x00, 
0x03, 0x03, 0x02, 0x00, 0x03, 0x03, 0x00
};
const uint8_t fnt_s[] = {
0x02, 0x03, 0x03, 0x04, 0x00, 0x00, 0x01, 0x02, 0x03, 0x03, 0x01, 0x02, 0x00, 0x00, 0x01, 0x03, 
0x03, 0x04, 0x02
};
const uint8_t fnt_t[] = {
0x03, 0x03, 0x03, 0x00, 0x00, 0x00, 0x03, 0x02, 0x00, 0x00, 0x01, 0x03, 0x02, 0x00, 0x00, 0x01, 
0x03, 0x02, 0x00, 0x00, 0x01, 0x03, 0x02, 0x00
};
const uint8_t fnt_u[] = {
0x03, 0x03, 0x00, 0x00, 0x03, 0x03, 0x02, 0x00, 0x03, 0x03, 0x02, 0x00, 0x03, 0x03, 0x02, 0x00, 
0x03, 0x03, 0x00, 0x00, 0x03, 0x03, 0x01, 0x00
};
const uint8_t fnt_v[] = {
0x03, 0x03, 0x00, 0x00, 0x03, 0x03, 0x02, 0x00, 0x03, 0x03, 0x02, 0x00, 0x03, 0x03, 0x00, 0x01, 
0x03, 0x03, 0x01, 0x01, 0x00, 0x02, 0x03, 0x02, 0x00
};
const uint8_t fnt_w[] = {
0x03, 0x00, 0x03, 0x00, 0x03, 0x03, 0x00, 0x00, 0x03, 0x00, 0x03, 0x03, 0x00, 0x00, 0x03, 0x00, 
0x03, 0x03, 0x01, 0x02, 0x03, 0x03, 0x01, 0x02, 0x00, 0x02, 0x03
};
const uint8_t fnt_x[] = {
0x03, 0x02, 0x00, 0x02, 0x03, 0x02, 0x03, 0x02, 0x03, 0x02, 0x00, 0x02, 0x03, 0x02, 0x00, 0x02, 
0x03, 0x02, 0x03, 0x02, 0x03, 0x02, 0x00, 0x02, 0x03
};
const uint8_t fnt_y[] = {
0x03, 0x02, 0x00, 0x02, 0x03, 0x02, 0x03, 0x02, 0x03, 0x02, 0x00, 0x02, 0x03, 0x02, 0x00, 0x00, 
0x01, 0x03, 0x02, 0x00, 0x00, 0x01, 0x03, 0x02, 0x00
};
const uint8_t fnt_z[] = {
0x03, 0x03, 0x03, 0x00, 0x00, 0x00, 0x02, 0x03, 0x02, 0x00, 0x02, 0x03, 0x02, 0x00, 0x02, 0x03, 
0x02, 0x00, 0x00, 0x00, 0x03, 0x03, 0x03
};
const uint8_t fnt_cb[] = { // close bracket
0x00, 0x03, 0x01, 0x00, 0x00, 0x02, 0x03, 0x02, 0x00, 0x00, 0x01, 0x03, 0x03, 0x00, 0x00, 0x00, 
0x01, 0x03, 0x02, 0x00, 0x00, 0x00, 0x03, 0x01, 0x00, 0x00, 0x00
};
const uint8_t fnt_ob[] = { // open bracket
0x00, 0x00, 0x00, 0x01, 0x03, 0x00, 0x00, 0x00, 0x02, 0x03, 0x00, 0x00, 0x01, 0x03, 0x03, 0x00, 
0x00, 0x00, 0x01, 0x02, 0x03, 0x00, 0x00, 0x02, 0x01, 0x03, 0x00
};
const uint8_t fnt_dol[] = { // dollar
0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x01, 0x03, 0x02, 0x03, 0x03, 0x00, 0x01, 0x01, 0x03, 
0x03, 0x03, 0x00, 0x02, 0x03, 0x01, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00
};
const uint8_t fnt_eq[] = { // equals
0x00, 0x00, 0x03, 0x03, 0x03, 0x03, 0x00, 0x00, 0x03, 0x03, 0x03, 0x03, 0x00, 0x00, 0x03
};
const uint8_t fnt_ex[] = { // exclamation
0x00, 0x02, 0x03, 0x01, 0x00, 0x00, 0x00, 0x03, 0x03, 0x01, 0x00, 0x00, 0x00, 0x01, 0x03, 0x01, 
0x00, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 0x01, 0x03, 0x00, 0x00, 0x01
};
const uint8_t fnt_fs[] = { // forward slash
0x00, 0x00, 0x02, 0x03, 0x00, 0x00, 0x01, 0x03, 0x00, 0x00, 0x01, 0x03, 0x00, 0x00, 0x01, 0x03, 
0x00, 0x00, 0x01, 0x03, 0x00, 0x00, 0x02
};
const uint8_t fnt_hash[] = { // hash
0x00, 0x03, 0x00, 0x03, 0x00, 0x03, 0x03, 0x03, 0x00, 0x03, 0x00, 0x03, 0x00, 0x03, 0x03, 0x03, 
0x00, 0x03, 0x00, 0x03, 0x00
};
const uint8_t fnt_heart[] = { // heart
0x01, 0x03, 0x00, 0x03, 0x01, 0x03, 0x03, 0x03, 0x02, 0x03, 0x03, 0x01, 0x02, 0x00, 0x02, 0x03, 
0x02, 0x00, 0x00, 0x01, 0x03, 0x00, 0x00, 0x00
};
const uint8_t fnt_minus[] = { //minus
0x00, 0x00, 0x08, 0x01, 0x03, 0x03, 0x01, 0x01, 0x00, 0x00, 0x08
};
const uint8_t fnt_pc[] = { // percent
0x02, 0x03, 0x00, 0x00, 0x00, 0x03, 0x03, 0x00, 0x02, 0x00, 0x03, 0x00, 0x00, 0x01, 0x03, 0x00, 
0x00, 0x01, 0x03, 0x00, 0x02, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00, 0x03, 0x02
};
const uint8_t fnt_pl[] = { // plus
0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x02, 0x03, 0x00, 0x00, 0x00, 0x03, 0x03, 0x03, 0x00, 0x00, 
0x00, 0x03, 0x00, 0x00, 0x02, 0x03, 0x00, 0x00, 0x00
};
const uint8_t fnt_pw[] = { // power
0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x01, 0x03, 0x01, 0x03, 0x00, 0x03, 0x01, 0x00, 0x01, 0x03, 
0x01, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x03
};
const uint8_t fnt_qm[] = { // question mark
0x01, 0x03, 0x03, 0x01, 0x01, 0x03, 0x00, 0x00, 0x00, 0x02, 0x03, 0x00, 0x00, 0x00, 0x02, 0x03, 
0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x02, 0x03, 0x00, 0x00, 0x00
};
const uint8_t fnt_quot[] = { // quote
0x00, 0x00, 0x03, 0x03, 0x03, 0x00, 0x00, 0x03, 0x03, 0x00, 0x01, 0x03, 0x00, 0x01, 0x03, 0x00, 
0x00, 0x08
};
const uint8_t fnt_star[] = { // star
0x02, 0x00, 0x03, 0x00, 0x02, 0x00, 0x02, 0x03, 0x02, 0x00, 0x03, 0x03, 0x00, 0x02, 0x03, 0x03, 
0x00, 0x00, 0x02, 0x03, 0x02, 0x00, 0x02, 0x00, 0x03, 0x00, 0x02
};
const uint8_t fnt_us[] = { // underscore
0x00, 0x00, 0x0D, 0x01, 0x01, 0x03, 0x03, 0x03, 0x03
};

//
// game data
//
static const uint8_t * const fontshapes[]={	fnt_a, fnt_b, fnt_c, fnt_d, fnt_e, fnt_f, fnt_g, fnt_h, fnt_i, fnt_j, fnt_k, fnt_l, fnt_m, fnt_n, fnt_o, fnt_p, fnt_q, fnt_r, fnt_s, fnt_t, fnt_u, fnt_v, fnt_w, fnt_x, fnt_y, fnt_z, fnt_cb, fnt_ob, fnt_dol, fnt_eq, fnt_ex, fnt_fs, fnt_hash, fnt_heart, fnt_minus, fnt_pc, fnt_pl, fnt_pw, fnt_qm, fnt_quot, fnt_star, fnt_us, fnt_0, fnt_1, fnt_2, fnt_3, fnt_4, fnt_5, fnt_6, fnt_7, fnt_8, fnt_9};

/* brick definition size */
#define BRICK_DEF_W   3
#define BRICK_DEF_H   3

/* brick bitmap size */
#define BRICK_SIZE_SMALL    7  /* brick bitmap size of small bricks in game area */
#define BRICK_SIZE_LARGE    6  /* preview brick bitmap size of small bricks in game area */

static struct {
  GDisp1_PixelDim appX;  /* applet x absolute screen position */
  GDisp1_PixelDim appY;  /* applet y absolute screen position */
  GDisp1_PixelDim appW;  /* game applet width */
  GDisp1_PixelDim appH;  /* game applet height */
  GDisp1_PixelDim gridOffX; /* grid x offset */
  GDisp1_PixelDim gridOffY; /* grid y offset */
  GDisp1_PixelDim gridW; /* grid width in pixels */
  GDisp1_PixelDim gridH; /* grid width in pixels */
  GDisp1_PixelDim nextOffX; /* absolute next/preview item x position */
  GDisp1_PixelDim nextOffY; /* absolute next/preview item y position */
} gameConfig;

/* next brick */
#define NEXT_BRICK_W         16
#define NEXT_BRICK_H         16
/* level status */
#define LEVEL_POS_X          11
#define LEVEL_POS_Y          27
/* lines status */
#define LINES_POS_X          11
#define LINES_POS_Y          55
/* score status */
#define SCORE_POS_X          11
#define SCORE_POS_Y          82
/* score status */
#define BEST_POS_X           11
#define BEST_POS_Y          109

/* game area and indices into screen[][] */
#define SCREEN_IDX_X_BORDER_LEFT    1  /* left border */
#define SCREEN_IDX_X_START         (SCREEN_IDX_X_BORDER_LEFT+1)  /* play area starts with this index in screen[x][y] */
#define SCREEN_IDX_X_END           (SCREEN_IDX_X_BORDER_RIGHT-1)  /* play area ends with this index in screen[x][y] */
#define SCREEN_GRID_SIZE_X         (SCREEN_IDX_X_END-SCREEN_IDX_X_START+1) /* visible grid size */
#define SCREEN_IDX_X_BORDER_RIGHT  15  /* right border */

#define SCREEN_IDX_Y_START          1  /* play area starts with this index in screen[x][y] */
#define SCREEN_IDX_Y_END           (SCREEN_IDX_Y_BORDER_BOTTOM-1)  /* play area ends with this index in screen[x][y] */
#define SCREEN_GRID_SIZE_Y         (SCREEN_IDX_Y_END-SCREEN_IDX_Y_START+1) /* visible grid size */
#define SCREEN_IDX_Y_BORDER_BOTTOM 25  /* bottom border */

#define GRID_SIZE_X (SCREEN_IDX_X_BORDER_RIGHT+1) /* size of screen in x direction */
#define GRID_SIZE_Y (SCREEN_IDX_Y_BORDER_BOTTOM+1) /* size of screen in y direction */

static byte screen[GRID_SIZE_X][GRID_SIZE_Y];

//
// defines
//
#ifndef max
  #define max(a,b)  (((a) > (b)) ? (a) : (b))
#endif

#ifndef min
  #define min(a,b)  (((a) < (b)) ? (a) : (b))
#endif

//
// Globals - Keyboard
//
static byte event_cmd_value=TETRIS_CMD_NONE;
static byte keyboard_value=TETRIS_CMD_NONE;
static byte last_keyboard_value=TETRIS_CMD_SPECIAL;

//
// Globals - Delta Timing
//
static float DeltaTime;
static word TETRIS_TimeMS;

//static xSemaphoreHandle TETRIS_displayMutex;

#define Draw65kBitmap(x0, y0, x1, y1, bmp, compressed) \
  GDisp1_Draw65kBitmap(x0, y0, x1, y1, bmp, compressed);

#define Draw256BitmapHigh(x0, y0, x1, y1, bmp, pal, compressed) \
  GDisp1_Draw256BitmapHigh(x0, y0, x1, y1, bmp, pal, compressed);

#define DrawBox(x, y, w, h, lineW, color) \
  GDisp1_DrawBox(x, y, w, h, lineW, color);

#define DrawFilledBox(x, y, w, h, color) \
  GDisp1_DrawFilledBox(x, y, w, h, color);

#define DrawHLine(x, y, w, color) \
  GDisp1_DrawHLine(x, y, w, color);

#define DrawVLine(x, y, h, color) \
  GDisp1_DrawVLine(x, y, h, color);

//
// Globals - Game
//
static byte cx, cy, sx, sy; /* brick coordinates in screen[][] */
static byte shape, next_shape;
static GDisp1_PixelColor color, next_color;

/* game statistics */
static word score, lines, level, max_score;

static byte state, next_state;
static float keytimer=0;

static char cur_brick[BRICK_DEF_W][BRICK_DEF_H];
static char next_brick[BRICK_DEF_W][BRICK_DEF_H];
static char last_brick[BRICK_DEF_W][BRICK_DEF_H];

static const char brick1_1[BRICK_DEF_W][BRICK_DEF_H]={
	0,1,0,
	1,1,1,
	0,0,0};
static const char brick1_2[BRICK_DEF_W][BRICK_DEF_H]={
	1,0,0,
	1,1,0,
	1,0,0};
static const char brick1_3[BRICK_DEF_W][BRICK_DEF_H]={
	1,1,1,
	0,1,0,
	0,0,0};
static const char brick1_4[BRICK_DEF_W][BRICK_DEF_H]={
	0,1,0,
	1,1,0,
	0,1,0};
static const char brick2_1[BRICK_DEF_W][BRICK_DEF_H]={
	1,0,0,
	1,1,1,
	0,0,0};
static const char brick2_2[BRICK_DEF_W][BRICK_DEF_H]={
	1,1,0,
	1,0,0,
	1,0,0};
static const char brick2_3[BRICK_DEF_W][BRICK_DEF_H]={
	1,1,1,
	0,0,1,
	0,0,0};
static const char brick2_4[BRICK_DEF_W][BRICK_DEF_H]={
	0,1,0,
	0,1,0,
	1,1,0};
static const char brick3_1[BRICK_DEF_W][BRICK_DEF_H]={
	0,1,1,
	1,1,0,
	0,0,0};
static const char brick3_2[BRICK_DEF_W][BRICK_DEF_H]={
	1,0,0,
	1,1,0,
	0,1,0};
static const char brick4_1[BRICK_DEF_W][BRICK_DEF_H]={
	1,1,1,
	0,0,0,
	0,0,0};
static const char brick4_2[BRICK_DEF_W][BRICK_DEF_H]={
	1,0,0,
	1,0,0,
	1,0,0};
static const char brick5_1[BRICK_DEF_W][BRICK_DEF_H]={
	1,1,0,
	1,1,0,
	0,0,0};
static const char brick6_1[BRICK_DEF_W][BRICK_DEF_H]={
	1,0,0,
	0,0,0,
	0,0,0};

static const GDisp1_PixelColor colors[6]= {
	GDisp1_COLOR_RED,
	GDisp1_COLOR_YELLOW,
	GDisp1_COLOR_GREEN,
	GDisp1_COLOR_BLUE,
	GDisp1_COLOR_ORANGE,
	GDisp1_COLOR_GREY
};

static const GDisp1_PixelColor shape_colors[]= { /* there are 6 'real' shapes */
	GDisp1_COLOR_WHITE,  /* 0 is 'no' shape */
	GDisp1_COLOR_RED,    /* 1 */
	GDisp1_COLOR_YELLOW, /* 2 */
	GDisp1_COLOR_GREEN,  /* 3 */
	GDisp1_COLOR_BLUE,   /* 4 */
	GDisp1_COLOR_ORANGE, /* 5 */
	GDisp1_COLOR_GREY,   /* 6 */
	GDisp1_COLOR_BLACK,  /* 7 is a 'border' shape */
};


static void erase_cur_brick();
static int conflict(void);
static int left_ok(void);
static int right_ok(void);
static void make_cur_brick(void);
static int is_brick_landed(void);
//
//  Functions
//

typedef byte GameCellCoord; /* type for gamecell screen coordinate */

static void DrawGrid(GameCellCoord x, GameCellCoord y) {
  /* draws the background of the play area */
  DrawBox(
    (GDisp1_PixelDim)(gameConfig.appX+gameConfig.gridOffX+(x*BRICK_SIZE_SMALL)),
    (GDisp1_PixelDim)(gameConfig.appY+gameConfig.gridOffY+(y*BRICK_SIZE_SMALL)),
    BRICK_SIZE_SMALL,
    BRICK_SIZE_SMALL, 
    1, GDisp1_COLOR_BRIGHT_GREY);  
  DrawFilledBox(
    (GDisp1_PixelDim)(gameConfig.appX+gameConfig.gridOffX+(x*BRICK_SIZE_SMALL)+1),
    (GDisp1_PixelDim)(gameConfig.appY+gameConfig.gridOffY+(y*BRICK_SIZE_SMALL)+1),
    (GDisp1_PixelDim)(BRICK_SIZE_SMALL-2),
    (GDisp1_PixelDim)(BRICK_SIZE_SMALL-2), 
    GDisp1_COLOR_GREY);  
}

static void DrawBrickBlock(GameCellCoord x, GameCellCoord y, byte kind) {
  GDisp1_PixelDim xCoord, yCoord;
  
  xCoord = (GDisp1_PixelDim)(gameConfig.appX+gameConfig.gridOffX+(x*BRICK_SIZE_SMALL));
  yCoord = (GDisp1_PixelDim)(gameConfig.appY+gameConfig.gridOffY+(y*BRICK_SIZE_SMALL));
  
  DrawHLine(xCoord, yCoord, BRICK_SIZE_SMALL, GDisp1_COLOR_WHITE);
  DrawVLine(xCoord, (GDisp1_PixelDim)(yCoord+1), (GDisp1_PixelDim)(BRICK_SIZE_SMALL-1), GDisp1_COLOR_WHITE);
  DrawHLine((GDisp1_PixelDim)(xCoord+1), (GDisp1_PixelDim)(yCoord+BRICK_SIZE_SMALL-1), (GDisp1_PixelDim)(BRICK_SIZE_SMALL-1), GDisp1_COLOR_BLACK);
  DrawVLine((GDisp1_PixelDim)(xCoord+BRICK_SIZE_SMALL-1), (GDisp1_PixelDim)(yCoord+1), (GDisp1_PixelDim)(BRICK_SIZE_SMALL-2), GDisp1_COLOR_BLACK);
  DrawFilledBox(
    (GDisp1_PixelDim)(xCoord+1),
    (GDisp1_PixelDim)(yCoord+1),
    (GDisp1_PixelDim)(BRICK_SIZE_SMALL-2),
    (GDisp1_PixelDim)(BRICK_SIZE_SMALL-2), 
    shape_colors[kind]);  
}

static void DrawNextBrickBlock(byte j, byte i, byte kind) {
  GDisp1_PixelDim xCoord, yCoord;
  
  xCoord = (GDisp1_PixelDim)(gameConfig.appX+gameConfig.nextOffX+(j*BRICK_SIZE_LARGE));
  yCoord = (GDisp1_PixelDim)(gameConfig.appY+gameConfig.nextOffY+(i*BRICK_SIZE_LARGE));
  
  DrawHLine(xCoord, yCoord, BRICK_SIZE_LARGE, GDisp1_COLOR_WHITE);
  DrawVLine(xCoord, (GDisp1_PixelDim)(yCoord+1), (GDisp1_PixelDim)(BRICK_SIZE_LARGE-1), GDisp1_COLOR_WHITE);
  DrawHLine((GDisp1_PixelDim)(xCoord+1), (GDisp1_PixelDim)(yCoord+BRICK_SIZE_LARGE-1), (GDisp1_PixelDim)(BRICK_SIZE_LARGE-1), GDisp1_COLOR_BLACK);
  DrawVLine((GDisp1_PixelDim)(xCoord+BRICK_SIZE_LARGE-1), (GDisp1_PixelDim)(yCoord+1), (GDisp1_PixelDim)(BRICK_SIZE_LARGE-2), GDisp1_COLOR_BLACK);
  DrawFilledBox(
    (GDisp1_PixelDim)(xCoord+1),
    (GDisp1_PixelDim)(yCoord+1),
    (GDisp1_PixelDim)(BRICK_SIZE_LARGE-2),
    (GDisp1_PixelDim)(BRICK_SIZE_LARGE-2), 
    shape_colors[kind]);  
}

static void ClearNextBrickBlock(byte j, byte i) {
  DrawFilledBox(
    (GDisp1_PixelDim)(gameConfig.appX+gameConfig.nextOffX+(j*BRICK_SIZE_LARGE)),
    (GDisp1_PixelDim)(gameConfig.appY+gameConfig.nextOffY+(i*BRICK_SIZE_LARGE)),
    BRICK_SIZE_LARGE,
    BRICK_SIZE_LARGE, 
    GDisp1_COLOR_BLACK);
}

static void print_text(const char *Text, GDisp1_PixelDim tx, GDisp1_PixelDim ty) {
	unsigned int Len;
	unsigned int Index;
	unsigned char Ch;
	
	Len = strlen(Text);	
	for (Index=0; Index<Len; Index++)	{
		Ch = (unsigned char) Text[Index];
		switch(Ch) {
			case 32: break; // space
			
			case 33: Ch=30; break; // exclamation
			case 34: Ch=39; break; // quote
			case 35: Ch=32; break; // hash
			case 36: Ch=28; break; // dollar
			case 37: Ch=36; break; // percent
			case 40: Ch=27; break; // open bracket
			case 41: Ch=26; break; // close bracket
			case 42: Ch=41; break; // star
			case 43: Ch=37; break; // plus
			case 45: Ch=34; break; // minus
			case 47: Ch=31; break; // forward slash
			
			case 48: Ch=42; break; // 0
			case 49: Ch=43; break; // 1
			case 50: Ch=44; break; // 2
			case 51: Ch=45; break; // 3
			case 52: Ch=46; break; // 4
			case 53: Ch=47; break; // 5
			case 54: Ch=48; break; // 6
			case 55: Ch=49; break; // 7
			case 56: Ch=50; break; // 8
			case 57: Ch=51; break; // 9
			
			case 61: Ch=29; break; // equals
			case 63: Ch=39; break; // question mark
			case 64: Ch=33; break; // heart @
			case 94: Ch=38; break; // power
			case 95: Ch=42; break; // underscore	
			
			default:
				Ch-=65;									
			  break;
		}
		if(Ch!=32) {
	    Draw256BitmapHigh((GDisp1_PixelDim)(tx+(Index*5)), ty, (GDisp1_PixelDim)(tx+(Index*5)+4), (GDisp1_PixelDim)(ty+4), (byte*)fontshapes[Ch], (GDisp1_PixelColor*)fnt_pal, TRUE);
		}
		tx++;
	}
}

#if POLL_KEYS
static void kb_wait(bool waitForRelease) {
  /* wait until a key has been pressed */
  while(KEY1_GetKeys()==0 /*&& KEY2_GetKeys()==0*/) { /* do nothing until a key is pressed */
    WAIT1_WaitOSms(10);
  }
  if(waitForRelease) {
    while(KEY1_GetKeys()!=0 || KEY2_GetKeys()!=0) {                                            
    	WAIT1_WaitOSms(10);
    }
  }
}
#endif

static void handle_keys(void) {
	switch(keyboard_value) {
		case TETRIS_CMD_UP:		
			erase_cur_brick();
			state+=1;
			if (state==5) {
			  state=1;
			}
			make_cur_brick();
			if (conflict()) {
			  state-=1;
			}
			if (state==0) state=4;
		  break;
		case TETRIS_CMD_DOWN:
			if (is_brick_landed()==0) cy+=1;
		  break;
		case TETRIS_CMD_LEFT:
			if (left_ok()) cx-=1;
		  break;
		case TETRIS_CMD_RIGHT:
			if (right_ok()) cx+=1;
		  break;
	}
}

static byte kb_get(void) {
  byte cmd;
  
  cmd = (byte)(
#if POLL_KEYS
    (KEY1_GetKeys()+(KEY2_GetKeys()<<3)) |
#endif
    event_cmd_value);
  event_cmd_value=TETRIS_CMD_NONE;
  return cmd;
}

static void handle_cmd_input(void) {
  // handle keyboard press and auto-repeat
  last_keyboard_value=keyboard_value;
  keyboard_value=kb_get();
  if(keyboard_value==TETRIS_CMD_NONE) { /* no keys pressed */
  	last_keyboard_value=TETRIS_CMD_SPECIAL;
  	keytimer=0;
  }
  if (last_keyboard_value!=keyboard_value) {
  	handle_keys();
  	keytimer=0;	
  } else {
  	// same key held
  	keytimer+=50*DeltaTime;
  	switch(keyboard_value)	{
  		case TETRIS_CMD_UP:
  			if(keytimer>30) {
  				handle_keys();	
  				keytimer=0;	
  			}
  		  break;
  		case TETRIS_CMD_DOWN:
  			if(keytimer>3) {
  				handle_keys();	
  				keytimer=0;	
  			}
  			break;
  		case TETRIS_CMD_LEFT:
  			if(keytimer>10)	{
  				handle_keys();	
  				keytimer=0;	
  			}				
  		  break;
  		case TETRIS_CMD_RIGHT:
  			if(keytimer>10) {
  				handle_keys();	
  				keytimer=0;	
  			}				
  		  break;
  	} /* switch */
  }
}

static void write_score(void) {
  unsigned char temp[5];

  UTIL1_Num16uToStr(temp, sizeof(temp), score);
  print_text((const char*)&temp[0], (GDisp1_PixelDim)(gameConfig.appX+SCORE_POS_X), (GDisp1_PixelDim)(gameConfig.appY+SCORE_POS_Y));
}

static void write_lines(void) {
  unsigned char temp[3];

  UTIL1_Num16uToStr(temp, sizeof(temp), lines);
  print_text((const char*)&temp[0], (GDisp1_PixelDim)(gameConfig.appX+LINES_POS_X), (GDisp1_PixelDim)(gameConfig.appY+LINES_POS_Y));
}

static void write_level(void) {
	unsigned char temp[3];

  UTIL1_Num16uToStr(temp, sizeof(temp), level);
	print_text((const char*)&temp[0], (GDisp1_PixelDim)(gameConfig.appX+LEVEL_POS_X), (GDisp1_PixelDim)(gameConfig.appY+LEVEL_POS_Y));
}

static void write_best(void) {
	unsigned char temp[5];

  UTIL1_Num16uToStr(temp, sizeof(temp), max_score);
	print_text((const char*)&temp[0], (GDisp1_PixelDim)(gameConfig.appX+BEST_POS_X), (GDisp1_PixelDim)(gameConfig.appY+BEST_POS_Y));
}

static void write_next(void) {
  /* preview the next brick */
  byte i, j;
  
  for (i=0;i<BRICK_DEF_W;i++) {
    for (j=0;j<BRICK_DEF_H;j++) {
      if (next_brick[i][j]==1) {
        DrawNextBrickBlock(j, i, next_shape);
      } else {
        ClearNextBrickBlock(j, i);
      } /* if */
    } /* for */
  } /* for */
}

static bool check_game_over(void) {
	/* scan the top row, if it isnt all zeros its game over */
	/* returns true if game is over */
  byte i, j;

  for (j=SCREEN_IDX_X_START;j<=SCREEN_IDX_X_END;j++) {
    if(screen[j][SCREEN_IDX_Y_START]!=0) {	
    	// game over
    	for (i=SCREEN_IDX_Y_START;i<=SCREEN_IDX_Y_END;i++) {
    	  for (j=SCREEN_IDX_X_START;j<=SCREEN_IDX_X_END;j++) {
    	    screen[j][i]=0; // reset play area
    	  }
    	}
    	/* center game over text */
    	print_text("GAME OVER", (GDisp1_PixelDim)(gameConfig.appX+(gameConfig.appW/2)-10), (GDisp1_PixelDim)(gameConfig.appY+(gameConfig.appH/2)-10));
    	return TRUE; /* game over */
    } 
  }
  return FALSE;
}

static void refresh_screen(void) {
	/* redraw the entire play area */
  byte i, j;
	byte c;
	
	for (i=SCREEN_IDX_Y_START;i<=SCREEN_IDX_Y_END;i++)
  	for (j=SCREEN_IDX_X_START;j<=SCREEN_IDX_X_END;j++) {
	  	c=screen[j][i];
		  if(c!=0) {
		    DrawBrickBlock(j, i, c);
  		} else {
  			DrawGrid(j,i);
  		}
   }
}

static void make_brick1_1(){ byte i, j; for(i=0;i<BRICK_DEF_W;i++) for (j=0;j<BRICK_DEF_H;j++) if (brick1_1[i][j]==1) cur_brick[i][j]=1; sx=(byte)(cx-1); sy=(byte)(cy-1);}
static void make_brick1_2(){ byte i, j; for(i=0;i<BRICK_DEF_W;i++) for (j=0;j<BRICK_DEF_H;j++) if (brick1_2[i][j]==1) cur_brick[i][j]=1; sx=(byte)(cx-0); sy=(byte)(cy-1);}
static void make_brick1_3(){ byte i, j; for(i=0;i<BRICK_DEF_W;i++) for (j=0;j<BRICK_DEF_H;j++) if (brick1_3[i][j]==1) cur_brick[i][j]=1; sx=(byte)(cx-1); sy=(byte)(cy-0);}
static void make_brick1_4(){ byte i, j; for(i=0;i<BRICK_DEF_W;i++) for (j=0;j<BRICK_DEF_H;j++) if (brick1_4[i][j]==1) cur_brick[i][j]=1; sx=(byte)(cx-1); sy=(byte)(cy-1);}
static void make_brick2_1(){ byte i, j; for(i=0;i<BRICK_DEF_W;i++) for (j=0;j<BRICK_DEF_H;j++) if (brick2_1[i][j]==1) cur_brick[i][j]=1; sx=(byte)(cx-0); sy=(byte)(cy-1);}
static void make_brick2_2(){ byte i, j; for(i=0;i<BRICK_DEF_W;i++) for (j=0;j<BRICK_DEF_H;j++) if (brick2_2[i][j]==1) cur_brick[i][j]=1; sx=(byte)(cx-0); sy=(byte)(cy-0);}
static void make_brick2_3(){ byte i, j; for(i=0;i<BRICK_DEF_W;i++) for (j=0;j<BRICK_DEF_H;j++) if (brick2_3[i][j]==1) cur_brick[i][j]=1; sx=(byte)(cx-2); sy=(byte)(cy-0);}
static void make_brick2_4(){ byte i, j; for(i=0;i<BRICK_DEF_W;i++) for (j=0;j<BRICK_DEF_H;j++) if (brick2_4[i][j]==1) cur_brick[i][j]=1; sx=(byte)(cx-1); sy=(byte)(cy-2);}
static void make_brick3_1(){ byte i, j; for(i=0;i<BRICK_DEF_W;i++) for (j=0;j<BRICK_DEF_H;j++) if (brick3_1[i][j]==1) cur_brick[i][j]=1; sx=(byte)(cx-1); sy=(byte)(cy-1);}
static void make_brick3_2(){ byte i, j; for(i=0;i<BRICK_DEF_W;i++) for (j=0;j<BRICK_DEF_H;j++) if (brick3_2[i][j]==1) cur_brick[i][j]=1; sx=(byte)(cx-0); sy=(byte)(cy-1);}
static void make_brick4_1(){ byte i, j; for(i=0;i<BRICK_DEF_W;i++) for (j=0;j<BRICK_DEF_H;j++) if (brick4_1[i][j]==1) cur_brick[i][j]=1; sx=(byte)(cx-1); sy=(byte)(cy-0);}
static void make_brick4_2(){ byte i, j; for(i=0;i<BRICK_DEF_W;i++) for (j=0;j<BRICK_DEF_H;j++) if (brick4_2[i][j]==1) cur_brick[i][j]=1; sx=(byte)(cx-0); sy=(byte)(cy-1);}
static void make_brick5_1(){ byte i, j; for(i=0;i<BRICK_DEF_W;i++) for (j=0;j<BRICK_DEF_H;j++) if (brick5_1[i][j]==1) cur_brick[i][j]=1; sx=(byte)(cx-0); sy=(byte)(cy-0);}
static void make_brick6_1(){ byte i, j; for(i=0;i<BRICK_DEF_W;i++) for (j=0;j<BRICK_DEF_H;j++) if (brick6_1[i][j]==1) cur_brick[i][j]=1; sx=(byte)(cx-0); sy=(byte)(cy-0);}

static void make_cur_brick(void) {
  byte i, j; 
  
	for(i=0;i<BRICK_DEF_W;i++) {
	  for(j=0;j<BRICK_DEF_H;j++) {
	    cur_brick[i][j]=0;
	  }
	}
	switch(shape) {
		case 1: 
			if (state==1) make_brick1_1();
			if (state==2) make_brick1_2();
			if (state==3) make_brick1_3();
			if (state==4) make_brick1_4();
			break;
		case 2:
			if (state==1) make_brick2_1();
			if (state==2) make_brick2_2();
			if (state==3) make_brick2_3();
			if (state==4) make_brick2_4();
			break;
		case 3:
			if (state==1) make_brick3_1();
			if (state==2) make_brick3_2();
			if (state==3) make_brick3_1(); 
			if (state==4) make_brick3_2();
			break;			
		case 4:
			if (state==1) make_brick4_1();
			if (state==2) make_brick4_2();
			if (state==3) make_brick4_1();
			if (state==4) make_brick4_2();
			break;
		case 5:
			make_brick5_1();
			break;
		case 6:
			make_brick6_1();
			break;
	}
}

static int is_brick_landed(void) {
  byte i, j; 

	for(i=0;i<BRICK_DEF_W;i++) {
	  for (j=0;j<BRICK_DEF_H;j++) {
	    if (cur_brick[i][j]==1 && screen[sx+j][sy+i+1]!=0) {
	      return 1;
	    }
	  }
	}
	return 0;
}

static int left_ok(void) {
  byte i, j; 

	for(i=0;i<BRICK_DEF_W;i++) {
	  for (j=0;j<BRICK_DEF_H;j++) {
	    if (cur_brick[i][j]==1 && screen[sx+j-1][sy+i]!=0) {
	      return 0;
	    }
	  }
	}
	return 1;
}

static int right_ok(void) {
  byte i, j; 

	for (i=0;i<BRICK_DEF_W;i++) {
	  for (j=0;j<BRICK_DEF_H;j++) {
	    if (cur_brick[i][j]==1 && screen[sx+j+1][sy+i]!=0) {
	      return 0;
	    }
	  }
	}
	return 1;
}

static int down_ok(void) {
  byte i, j; 

	for(i=0;i<BRICK_DEF_W;i++) {
	  for (j=0;j<BRICK_DEF_H;j++) {
	    if (cur_brick[i][j]==1 && screen[sx+j][sy+i+1]!=0) {
	      return 0;
	    }
	  }
	}
	return 1;
}

static int conflict(void) {
  byte i, j; 

	for(i=0;i<BRICK_DEF_W;i++) {
	  for (j=0;j<BRICK_DEF_H;j++) {
	    if (cur_brick[i][j]==1 && screen[sx+j][sy+i]!=0) {
	      return 1;
	    }
	  }
	}
	return 0;
}

static void make_last_brick(void) {
  byte i, j; 

	for(i=0;i<BRICK_DEF_W;i++) {
	  for (j=0;j<BRICK_DEF_H;j++) {
	    last_brick[i][j]=cur_brick[i][j];
	  }
	}
}

static void make_next_brick1_1(void) { byte i, j; for(i=0;i<BRICK_DEF_W;i++) for (j=0;j<BRICK_DEF_H;j++) if(brick1_1[i][j]==1) next_brick[i][j]=1;}
static void make_next_brick1_2(void) { byte i, j; for(i=0;i<BRICK_DEF_W;i++) for (j=0;j<BRICK_DEF_H;j++) if (brick1_2[i][j]==1) next_brick[i][j]=1;}
static void make_next_brick1_3(void) { byte i, j; for(i=0;i<BRICK_DEF_W;i++) for (j=0;j<BRICK_DEF_H;j++) if (brick1_3[i][j]==1) next_brick[i][j]=1;}
static void make_next_brick1_4(void) { byte i, j; for(i=0;i<BRICK_DEF_W;i++) for (j=0;j<BRICK_DEF_H;j++) if (brick1_4[i][j]==1) next_brick[i][j]=1;}
static void make_next_brick2_1(void) { byte i, j; for(i=0;i<BRICK_DEF_W;i++) for (j=0;j<BRICK_DEF_H;j++) if (brick2_1[i][j]==1) next_brick[i][j]=1;}
static void make_next_brick2_2(void) { byte i, j; for(i=0;i<BRICK_DEF_W;i++) for (j=0;j<BRICK_DEF_H;j++) if (brick2_2[i][j]==1) next_brick[i][j]=1;}
static void make_next_brick2_3(void) { byte i, j; for(i=0;i<BRICK_DEF_W;i++) for (j=0;j<BRICK_DEF_H;j++) if (brick2_3[i][j]==1) next_brick[i][j]=1 ;}
static void make_next_brick2_4(void) { byte i, j; for(i=0;i<BRICK_DEF_W;i++) for (j=0;j<BRICK_DEF_H;j++) if (brick2_4[i][j]==1) next_brick[i][j]=1;}
static void make_next_brick3_1(void) { byte i, j; for(i=0;i<BRICK_DEF_W;i++) for (j=0;j<BRICK_DEF_H;j++) if (brick3_1[i][j]==1) next_brick[i][j]=1;}
static void make_next_brick3_2(void) { byte i, j; for(i=0;i<BRICK_DEF_W;i++) for (j=0;j<BRICK_DEF_H;j++) if (brick3_2[i][j]==1) next_brick[i][j]=1;}
static void make_next_brick4_1(void) { byte i, j; for(i=0;i<BRICK_DEF_W;i++) for (j=0;j<BRICK_DEF_H;j++) if (brick4_1[i][j]==1) next_brick[i][j]=1;}
static void make_next_brick4_2(void) { byte i, j; for(i=0;i<BRICK_DEF_W;i++) for (j=0;j<BRICK_DEF_H;j++) if (brick4_2[i][j]==1) next_brick[i][j]=1;}
static void make_next_brick5_1(void) { byte i, j; for(i=0;i<BRICK_DEF_W;i++) for (j=0;j<BRICK_DEF_H;j++) if (brick5_1[i][j]==1) next_brick[i][j]=1;}
static void make_next_brick6_1(void) { byte i, j; for(i=0;i<BRICK_DEF_W;i++) for (j=0;j<BRICK_DEF_H;j++) if (brick6_1[i][j]==1) next_brick[i][j]=1;}

static void make_next_brick(void) {
  byte i, j; 
  
	for (i=0;i<3;i++) for (j=0;j<3;j++) {
	  next_brick[i][j]=0;
	}
	switch(next_shape) {
		case 1:
			if (next_state==1) make_next_brick1_1();
			if (next_state==2) make_next_brick1_2();
			if (next_state==3) make_next_brick1_3();
			if (next_state==4) make_next_brick1_4();
			break;
		case 2:
			if (next_state==1) make_next_brick2_1();
			if (next_state==2) make_next_brick2_2();
			if (next_state==3) make_next_brick2_3();
			if (next_state==4) make_next_brick2_4();
			break;
		case 3:
			if (next_state==1) make_next_brick3_1();
			if (next_state==2) make_next_brick3_2();
			if (next_state==3) make_next_brick3_1();
			if (next_state==4) make_next_brick3_2();
			break;
		case 4:
			if (next_state==1) make_next_brick4_1();
			if (next_state==2) make_next_brick4_2();
			if (next_state==3) make_next_brick4_1();
			if (next_state==4) make_next_brick4_2();
			break;
		case 5:
			make_next_brick5_1();
			break;
		case 6:
			make_next_brick6_1();
			break;
	}
}

static void erase_brick(GameCellCoord oldx, GameCellCoord oldy) {
  byte i, j; 

	for (i=0;i<BRICK_DEF_W;i++) {
    for (j=0;j<BRICK_DEF_H;j++) {
    	if(last_brick[i][j]==1) {
  		  DrawGrid((GameCellCoord)(oldx+j), (GameCellCoord)(oldy+i));
    	}
    }
	}
}

static void erase_cur_brick(void) {
  byte i, j; 

	for (i=0;i<BRICK_DEF_W;i++) {
  	for (j=0;j<BRICK_DEF_H;j++)	{
  		if(cur_brick[i][j]==1) {
 			  DrawGrid((GameCellCoord)(sx+j), (GameCellCoord)(sy+i));
  		}
  	}
	}
}

static void display_brick(void) {	
  byte i, j; 

  /* draw a brick to the screen */
  for (i=0;i<BRICK_DEF_W;i++) {
    for (j=0;j<BRICK_DEF_H;j++) {
  	  if(cur_brick[i][j]==1) {
  	    DrawBrickBlock((GameCellCoord)(sx+j), (GameCellCoord)(sy+i), shape);
  	  }
  	}
  }
}

static void del_line(byte line) {
  /* delete a brick line on the screen */
  byte i, j; 

	for (j=SCREEN_IDX_X_START;j<=SCREEN_IDX_X_END;j++) {
	  screen[j][line]=0;	
    DrawGrid(j, line);
	}
	for (i=line;i>SCREEN_IDX_Y_START;i--) {
	  for(j=SCREEN_IDX_X_START;j<=SCREEN_IDX_X_END;j++) {
	    screen[j][i]=screen[j][i-1];
	  }
	}
	score+=5;
	if(score>max_score) {
	  max_score=score;
	}
	lines++;
	write_lines();
	refresh_screen();
}

static bool check_line(byte *line) {
  /* returns true if a line is full */
  byte i, j;
  bool full; 

	for (i=SCREEN_IDX_Y_START;i<=SCREEN_IDX_Y_END;i++) {
		full=TRUE;
		*line=0;
		for (j=SCREEN_IDX_X_START;j<=SCREEN_IDX_X_END;j++) {
		  if (screen[j][i]==0) {
		    full=FALSE;
		  }
		}
		if (full) {
		  *line=i;
		  return TRUE;
		}
	}
	return FALSE;
}

static void DrawBackground(void) {
	DrawFilledBox(gameConfig.appX, gameConfig.appY, gameConfig.appW, gameConfig.appH, GDisp1_COLOR_GREY); /* clear game window area */
  refresh_screen();
  /* border around game area */
  #define GAME_GRID_BORDER_SIZE 2
  DrawFilledBox(
    (GDisp1_PixelDim)(gameConfig.appX+gameConfig.gridOffX-GAME_GRID_BORDER_SIZE+SCREEN_IDX_X_START*BRICK_SIZE_SMALL),
    (GDisp1_PixelDim)(gameConfig.appY+gameConfig.gridOffY+SCREEN_IDX_Y_START*BRICK_SIZE_SMALL), 
    GAME_GRID_BORDER_SIZE, 
    (GDisp1_PixelDim)(SCREEN_GRID_SIZE_Y*BRICK_SIZE_SMALL),
    GDisp1_COLOR_BRIGHT_BLUE);
  DrawFilledBox(
    (GDisp1_PixelDim)(gameConfig.appX+gameConfig.gridOffX+SCREEN_IDX_X_START*BRICK_SIZE_SMALL-GAME_GRID_BORDER_SIZE),
    (GDisp1_PixelDim)(gameConfig.appY+gameConfig.gridOffY+(SCREEN_IDX_Y_START+SCREEN_GRID_SIZE_Y)*BRICK_SIZE_SMALL),
    (GDisp1_PixelDim)(SCREEN_GRID_SIZE_X*BRICK_SIZE_SMALL+2*GAME_GRID_BORDER_SIZE),
    GAME_GRID_BORDER_SIZE,
    GDisp1_COLOR_BRIGHT_BLUE);
  DrawFilledBox(
    (GDisp1_PixelDim)(gameConfig.appX+gameConfig.gridOffX+(SCREEN_IDX_X_START+SCREEN_GRID_SIZE_X)*BRICK_SIZE_SMALL),
    (GDisp1_PixelDim)(gameConfig.appY+gameConfig.gridOffY+SCREEN_IDX_Y_START*BRICK_SIZE_SMALL),
    GAME_GRID_BORDER_SIZE,
    (GDisp1_PixelDim)(SCREEN_GRID_SIZE_Y*BRICK_SIZE_SMALL),
    GDisp1_COLOR_BRIGHT_BLUE);

  print_text("NEXT",  (GDisp1_PixelDim)(gameConfig.appX+gameConfig.nextOffX-BRICK_SIZE_LARGE), (GDisp1_PixelDim)(gameConfig.appY+gameConfig.nextOffY-8-BRICK_SIZE_LARGE));
  DrawBox((GDisp1_PixelDim)(gameConfig.appX+gameConfig.nextOffX-2-BRICK_SIZE_LARGE), (GDisp1_PixelDim)(gameConfig.appY+gameConfig.nextOffY-2-BRICK_SIZE_LARGE), (GDisp1_PixelDim)(6*BRICK_SIZE_LARGE), (GDisp1_PixelDim)(6*BRICK_SIZE_LARGE), 1, GDisp1_COLOR_BRIGHT_BLUE);
  DrawFilledBox((GDisp1_PixelDim)(gameConfig.appX+gameConfig.nextOffX-BRICK_SIZE_LARGE-1), (GDisp1_PixelDim)(gameConfig.appY+gameConfig.nextOffY-1-BRICK_SIZE_LARGE), (GDisp1_PixelDim)(6*BRICK_SIZE_LARGE-2), (GDisp1_PixelDim)(6*BRICK_SIZE_LARGE-2), GDisp1_COLOR_BLACK); // clear next display

  print_text("LEVEL", (GDisp1_PixelDim)(gameConfig.appX+LEVEL_POS_X-2), (GDisp1_PixelDim)(gameConfig.appY+LEVEL_POS_Y-8));
  DrawBox((GDisp1_PixelDim)(gameConfig.appX+LEVEL_POS_X-2), (GDisp1_PixelDim)(gameConfig.appY+LEVEL_POS_Y-2), 40, 10, 1, GDisp1_COLOR_BRIGHT_BLUE);
  DrawFilledBox((GDisp1_PixelDim)(gameConfig.appX+LEVEL_POS_X-1), (GDisp1_PixelDim)(gameConfig.appY+LEVEL_POS_Y-1), 38, 8, GDisp1_COLOR_BLACK);

  print_text("LINES", (GDisp1_PixelDim)(gameConfig.appX+LINES_POS_X-2), (GDisp1_PixelDim)(gameConfig.appY+LINES_POS_Y-8));
  DrawBox((GDisp1_PixelDim)(gameConfig.appX+LINES_POS_X-2), (GDisp1_PixelDim)(gameConfig.appY+LINES_POS_Y-2), 40, 10, 1, GDisp1_COLOR_BRIGHT_BLUE);
  DrawFilledBox((GDisp1_PixelDim)(gameConfig.appX+LINES_POS_X-1), (GDisp1_PixelDim)(gameConfig.appY+LINES_POS_Y-1), 38, 8, GDisp1_COLOR_BLACK);

  print_text("SCORE", (GDisp1_PixelDim)(gameConfig.appX+SCORE_POS_X-2), (GDisp1_PixelDim)(gameConfig.appY+SCORE_POS_Y-8));
  DrawBox((GDisp1_PixelDim)(gameConfig.appX+SCORE_POS_X-2), (GDisp1_PixelDim)(gameConfig.appY+SCORE_POS_Y-2), 40, 10, 1, GDisp1_COLOR_BRIGHT_BLUE);
  DrawFilledBox((GDisp1_PixelDim)(gameConfig.appX+SCORE_POS_X-1), (GDisp1_PixelDim)(gameConfig.appY+SCORE_POS_Y-1), 38, 8, GDisp1_COLOR_BLACK);

  print_text("BEST",  (GDisp1_PixelDim)(gameConfig.appX+BEST_POS_X-2),  (GDisp1_PixelDim)(gameConfig.appY+BEST_POS_Y-8));
  DrawBox((GDisp1_PixelDim)(gameConfig.appX+BEST_POS_X-2), (GDisp1_PixelDim)(gameConfig.appY+BEST_POS_Y-2), 40, 10, 1, GDisp1_COLOR_BRIGHT_BLUE);
  DrawFilledBox((GDisp1_PixelDim)(gameConfig.appX+BEST_POS_X-1), (GDisp1_PixelDim)(gameConfig.appY+BEST_POS_Y-1), 38, 8, GDisp1_COLOR_BLACK);

  write_level();
	write_score();
	write_lines();
	write_best();
}

void TETRIS_AddTime(byte nofMS) {
  /* Needs to be called periodically (e.g. from a timer interrupt) to increase the game time */
  TETRIS_TimeMS += nofMS;
}

static void TETRIS_ClearTime(void) {
  FRTOS1_taskENTER_CRITICAL();
  TETRIS_TimeMS = 0;
  FRTOS1_taskEXIT_CRITICAL();
}

static word TETRIS_GetTime(void) {
  word val;
  
  FRTOS1_taskENTER_CRITICAL();
  val = TETRIS_TimeMS;
  FRTOS1_taskEXIT_CRITICAL();
  return val;
}

static portTASK_FUNCTION(TaskTetris, pvParameters) {
  byte line; 
  int dropmax;
  byte i, j;
  float counter, timer;
  byte TimerReset;
  word LastTimeMS;

  (void)pvParameters; /* not used */

  /* Initialize game variables */
  level=0;
  lines=0;
  score=0;
  timer=0;
  counter=0;

  cx=0;
  cy=0;
  sx=0;
  sy=0;

  shape=0;
  next_shape=0;

  keyboard_value=TETRIS_CMD_NONE;
  last_keyboard_value=TETRIS_CMD_SPECIAL;

  for (i=SCREEN_IDX_Y_START;i<=SCREEN_IDX_Y_END;i++) {
    for (j=SCREEN_IDX_X_START;j<=SCREEN_IDX_X_END;j++) {
      screen[j][i]=0; // reset play area
    }
  }
  // block off the drop area (filled tiles act as stoppers)
  for (i=SCREEN_IDX_X_BORDER_LEFT;i<=SCREEN_IDX_X_BORDER_RIGHT;i++) {
    screen[i][SCREEN_IDX_Y_BORDER_BOTTOM]=7; /* fill row below play area */
  }
  for (i=SCREEN_IDX_Y_START;i<=SCREEN_IDX_Y_BORDER_BOTTOM;i++)	{
    screen[SCREEN_IDX_X_BORDER_LEFT][i]=7; /* fill left border */
  }
  for (i=SCREEN_IDX_Y_START;i<=SCREEN_IDX_Y_BORDER_BOTTOM;i++) {
    screen[SCREEN_IDX_X_BORDER_RIGHT][i]=7; /* fill right border */
  }

  // update UI
  DrawBackground();

  /* reset timer */
  TETRIS_ClearTime();
  DeltaTime = 0;
  TimerReset = 0;
  LastTimeMS = 0;

  for(;;) { /* game loop */
    byte old_sx, old_sy;
    
    // delta timer handler    
    if(TimerReset++==10) {
    	// have to reset the timer vars periodically otherwise
    	// DeltaTime will stick and not wrap around
    	TETRIS_ClearTime();
    	TimerReset=0;    	
    	LastTimeMS=0;
    } else {    	
      word TimeMS;
  	  
  	  TimeMS = TETRIS_GetTime();
  	  DeltaTime=(TimeMS - LastTimeMS)*0.001f; // Delta Timer
  	  LastTimeMS=TimeMS;
    }
    old_sx=sx;
    old_sy=sy;

    make_last_brick();
    if (check_line(&line)) {
      del_line(line);
    }
    if (check_game_over()) {
      while(1) {}; /* wait, until process get killed */
    }
    write_score();
    level=(word)((score/25)+(timer/200)); // every 5 lines or 20 sec approx increase level
    write_next();
    write_level();
    write_best();
  	if(next_shape==0) {
      next_shape=(byte)(6*rand()/(RAND_MAX+1.0));
      next_state=1;
      next_color=colors[next_shape];
      make_next_brick();
    }
    handle_cmd_input();

    //drop the brick downwards
    timer+=10*DeltaTime;
    counter+=100*DeltaTime;

    dropmax=80-(level*5);
    if(dropmax<10) {
      dropmax=10; // limit max drop speed
    }
    if (counter>=dropmax && down_ok()) {
    	cy=(byte)(cy+1);
    	counter=0;
    }
    // generate new brick
    make_cur_brick();
    //draw the brick
    display_brick();
    //erase old brick coordinates
    if (old_sx!=sx || old_sy!=sy) {
      erase_brick(old_sx, old_sy);
    }
    //if brick lands on another brick or floor then stop the brick and make shape=0 to make a new brick
    if (is_brick_landed()) {		
    	for (i=0;i<BRICK_DEF_W;i++) {
    		for (j=0;j<BRICK_DEF_H;j++) {
    			if (cur_brick[i][j]!=0) {
    			  screen[sx+j][sy+i]=shape;
    			}
    		}
    	}
    	display_brick();			
    	shape=0;
    }
    //control if a brick is dropping , if not make a random dropping brick
    if (shape==0) {
      //if there is not dropping brick
    	shape=next_shape;
    	state=next_state;
    	color=next_color;
    	cx=10;
    	cy=2;
    	next_shape=0;
    	make_cur_brick();
    }
    if (EVNT1_GetEvent(EVNT1_APP_MODE_CHANGE)) { /* request to close application */
      EVNT1_ClearEvent(EVNT1_APP_MODE_CHANGE); /* reset event flag */
      FRTOS1_vTaskDelete(NULL); /* kill ourself */ 
    }
    FRTOS1_vTaskDelay(10/portTICK_RATE_MS);
  } /* for */
}

static void TETRIS_SendCmd(byte cmd) {
  /* event called for key pressed */
  event_cmd_value = cmd;
}

/* Specifies the game area with absolute display positions */
static void TETRIS_GameAreaInit(GDisp1_PixelDim x, GDisp1_PixelDim y, GDisp1_PixelDim w, GDisp1_PixelDim h) {
  gameConfig.appX=x;
  gameConfig.appY=y;
  gameConfig.appW=w;
  gameConfig.appH=h;
  /* center game grid inside window */
  gameConfig.gridOffX = (GDisp1_PixelDim)((gameConfig.appW-(GRID_SIZE_X*BRICK_SIZE_SMALL))/2);
  gameConfig.gridOffY = 0;
  gameConfig.gridW = (GDisp1_PixelDim)(GRID_SIZE_X*BRICK_SIZE_SMALL);
  gameConfig.gridH = (GDisp1_PixelDim)(GRID_SIZE_Y*BRICK_SIZE_SMALL);
  /* determine next/preview area */
  gameConfig.nextOffX = (GDisp1_PixelDim)(gameConfig.appW-((gameConfig.gridOffX-NEXT_BRICK_W)/2)-NEXT_BRICK_W);
  gameConfig.nextOffY = (GDisp1_PixelDim)(25);
}

/* return a touch area (relative game area/window coordinates for touch screens) to be used for the commands. Call it _after_ Init(). */
static void TETRIS_GetTouchArea(byte cmd, GDisp1_PixelDim *x, GDisp1_PixelDim *y, GDisp1_PixelDim *w, GDisp1_PixelDim *h) {
  *x = *y = *w = *h = 0;
  switch(cmd) {
    case TETRIS_CMD_UP: /* upper half of game grid */
      *x = gameConfig.gridOffX;
      *y = gameConfig.gridOffY;
      *w = gameConfig.gridW;
      *h = (GDisp1_PixelDim)(gameConfig.gridH/2);
      break;
    case TETRIS_CMD_LEFT: /* left of game grid */
      *x = 0;
      *y = gameConfig.gridOffY;
      *w = gameConfig.gridOffX;
      *h = gameConfig.gridH;
      break;
    case TETRIS_CMD_RIGHT: /* right of game grid */
      *x = (GDisp1_PixelDim)(gameConfig.gridOffX+gameConfig.gridW);
      *y = gameConfig.gridOffY;
      *w = (GDisp1_PixelDim)(gameConfig.appW-(*x));
      *h = gameConfig.gridH;
      break;
    case TETRIS_CMD_DOWN: /* lower half of game grid */
      *x = gameConfig.gridOffX;
      *y = (GDisp1_PixelDim)(gameConfig.gridOffY+gameConfig.gridH/2);
      *w = gameConfig.gridW;
      *h = (GDisp1_PixelDim)(gameConfig.gridH/2);
      break;
  } /* switch */
}

void TETRIS_RefreshWindow(void) {
  if (TETRIS_isRunning) {
    DrawBackground();
    refresh_screen();
  }
}

static void tetrisW_WindowCallback(UI1_Window *window, UI1_Element *element, UI1_EventCallbackKind kind, UI1_Pvoid data) {
  (void)window;
  (void)data; /* unused argument */
  if (kind==UI1_EVENT_CLICK) {
    if (UI1_EqualElement(element, &AppDesc->iconClose)) {
      EVNT1_SetEvent(EVNT1_APP_MODE_CHANGE); /* request to close application */
      while(EVNT1_GetEvent(EVNT1_APP_MODE_CHANGE)) {
        /* wait until task has killed itself */
        FRTOS1_vTaskDelay(50/portTICK_RATE_MS);
      }
      TETRIS_isRunning = FALSE;
      APP_SetApplicationMode(APP_MODE_MAIN_MENU);
      return;
    }
  }
  if (kind==UI1_EVENT_CLICK /*|| kind==UI1_EVENT_CLICK_MOVE*/) {
    if (UI1_EqualElement(element, &AppDesc->cmdLeft)) {
      TETRIS_SendCmd(TETRIS_CMD_LEFT);
    } else if (UI1_EqualElement(element, &AppDesc->cmdRight)) {
      TETRIS_SendCmd(TETRIS_CMD_RIGHT);
    } else if (UI1_EqualElement(element, &AppDesc->cmdUp)) {
      TETRIS_SendCmd(TETRIS_CMD_UP);
    } else if (UI1_EqualElement(element, &AppDesc->cmdDown)) {
      TETRIS_SendCmd(TETRIS_CMD_DOWN);
    }
  }
}

void TETRIS_CreateWindow(TETRIS_WindowDesc *desc) {
  UI1_PixelDim posX, posY, posW, posH;
  UI1_PixelDim gameX, gameY, gameW, gameH;
  UI1_PixelDim appletOffX, appletOffY;
  UI1_PixelDim h;

  AppDesc = desc;
  UI1_CreateScreen(&desc->screen, UI1_COLOR_WHITE);
  (void)UI1_CreateWindow(&desc->screen, &desc->window, UI1_COLOR_WHITE, 0, 0, UI1_GetWidth(), UI1_GetHeight());
  (void)UI1_CreateHeader(&desc->window, &desc->header, (unsigned char*)"TetriClone", FONT, UI1_COLOR_BLUE);
  UI1_ChangeTextFgColor(&desc->header.element, UI1_COLOR_WHITE);
  UI1_SetWindowEventCallback(&desc->window, tetrisW_WindowCallback);
  /* Icon: Close */
  h = (UI1_PixelDim)(UI1_GetElementHeight(&desc->header));
  (void)UI1_CreateIcon(&desc->window, &desc->iconClose, 1, 1, (UI1_PixelDim)(h-2), (UI1_PixelDim)(h-2), UI1_ICON_CLOSE);
  desc->iconClose.element.prop.flags |= UI1_FLAGS_ALIGN_RIGHT;
  UI1_OnWindowResize(&desc->window); /* right align element(s) if needed */
  UI1_ChangeElementColor(&desc->iconClose, UI1_COLOR_BLUE);
  UI1_ChangeIconFgColor(&desc->iconClose, UI1_COLOR_WHITE);
  UI1_EnableElementSelection(&desc->iconClose);

  /* calculate absolute screen position for the applet */
  gameX = (UI1_PixelDim)(UI1_GetElementPosX(&desc->window)+UI1_GetElementPosX(&desc->header));
  gameY = (UI1_PixelDim)(UI1_GetElementPosY(&desc->window)+UI1_GetElementHeight(&desc->header));
  gameW = UI1_GetElementWidth(&desc->header);
  gameH = (UI1_PixelDim)(UI1_GetElementHeight(&desc->window)-UI1_GetElementHeight(&desc->header));
  /* initialize game structure and paint start game screen */
  TETRIS_GameAreaInit(gameX, gameY, gameW, gameH); /* absolute screen coordinates */
  
  /* calculate applet window offsets */
  appletOffX = UI1_GetElementPosX(&desc->header);
  appletOffY = (UI1_PixelDim)(UI1_GetElementPosY(&desc->header)+UI1_GetElementHeight(&desc->header));
  /* create touch area for 'up' */
  TETRIS_GetTouchArea(TETRIS_CMD_UP, &posX, &posY, &posW, &posH); 
  UI1_CreateSpace(&desc->window, &desc->cmdUp, (UI1_PixelDim)(appletOffX+posX), (UI1_PixelDim)(appletOffY+posY), posW, posH); 
  UI1_EnableElementSelection(&desc->cmdUp);
  /* create touch area for 'left' */
  TETRIS_GetTouchArea(TETRIS_CMD_LEFT, &posX, &posY, &posW, &posH); 
  UI1_CreateSpace(&desc->window, &desc->cmdLeft, (UI1_PixelDim)(appletOffX+posX), (UI1_PixelDim)(appletOffY+posY), posW, posH); 
  UI1_EnableElementSelection(&desc->cmdLeft);
  /* create touch area for 'right' */
  TETRIS_GetTouchArea(TETRIS_CMD_RIGHT, &posX, &posY, &posW, &posH); 
  UI1_CreateSpace(&desc->window, &desc->cmdRight, (UI1_PixelDim)(appletOffX+posX), (UI1_PixelDim)(appletOffY+posY), posW, posH); 
  UI1_EnableElementSelection(&desc->cmdRight);
  /* create touch area for 'down' */
  TETRIS_GetTouchArea(TETRIS_CMD_DOWN, &posX, &posY, &posW, &posH); 
  UI1_CreateSpace(&desc->window, &desc->cmdDown, (UI1_PixelDim)(appletOffX+posX), (UI1_PixelDim)(appletOffY+posY), posW, posH); 
  UI1_EnableElementSelection(&desc->cmdDown);
  /* update the screen */
  UI1_UpdateScreen(&desc->screen);
  
  if (FRTOS1_xTaskCreate(TaskTetris, "Tetris", configMINIMAL_STACK_SIZE+50, NULL, tskIDLE_PRIORITY+1, NULL) != pdPASS) {
    for(;;) {} /* out of memory for task? */
  }
  TETRIS_isRunning = TRUE;
}

#endif /* PL_HAS_TETRIS_DEMO */

/* END Tetris */
