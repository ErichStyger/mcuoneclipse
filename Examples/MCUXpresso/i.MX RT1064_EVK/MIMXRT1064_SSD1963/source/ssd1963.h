/*
 * Copyright (c) 2013, Franz Brauße
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 * - Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef SSD1963_H
#define SSD1963_H

/* the two macros SSD_WR_CMD and SSD_WR_DATA must be defined */

/* writes the unsigned char x while asserting D/#C and #WR and then releasing
 * both control lines */
/* #define SSD_WR_CMD(x)  ((void)x) */

/* writes the unsigned char x while asserting #WR and then releasing it */
/* #define SSD_WR_DATA(x) ((void)x) */

/* the macro SSD_RD_DATA is optional, it should be defined if reading from the
 * controller is to be possible */

/* reads an unsigned char by first asserting #RD and retrieving the 8 lower bits
 * on the bus when releasing #RD */
/* #define SSD_RD_DATA()  (0) */

#ifdef SSD_IO_MACROS
#include SSD_IO_MACROS
#endif

/* these macros are allowed to evaluate their argument more than once */
#if !defined(SSD_WR_CMD) || !defined(SSD_WR_DATA)
# error SSD1963 functions need definitions of the macros SSD_WR_CMD, SSD_WR_DATA
#endif

static inline void ssd_cmd(const unsigned char k[static 1], unsigned data_len)
{
  SSD_WR_CMD(*k);
  k++;
  while (data_len) {
    SSD_WR_DATA(*k);
    k++;
    data_len--;
  }
}

#define SSD_CMD0(k)   ssd_cmd(k, sizeof(k)-1)
#define SSD_CMD(...)    SSD_CMD0(((unsigned char[]){ __VA_ARGS__ }))

/* use these raw commands with care: always read the description in the
 * SSD1963's datasheet for possible side effects, timing requirements, etc. */

#define SSD_NOP()     SSD_CMD(0x00)
#define SSD_SOFT_RESET()    SSD_CMD(0x01)
#define SSD_GET_POWER_MODE()    SSD_CMD(0x0a) /* param: 1 */
#define SSD_GET_ADDRESS_MODE()    SSD_CMD(0x0b) /* param: 1 */
#define SSD_GET_DISPLAY_MODE()    SSD_CMD(0x0d) /* param: 1 */
#define SSD_GET_TEAR_EFFECT_STATUS()  SSD_CMD(0x0e) /* param: 1 */
#define SSD_ENTER_SLEEP_MODE()    SSD_CMD(0x10)
#define SSD_EXIT_SLEEP_MODE()   SSD_CMD(0x11)
#define SSD_ENTER_PARTIAL_MODE()  SSD_CMD(0x12)
#define SSD_ENTER_NORMAL_MODE()   SSD_CMD(0x13)
#define SSD_EXIT_INVERT_MODE()    SSD_CMD(0x20)
#define SSD_ENTER_INVERT_MODE()   SSD_CMD(0x21)
/* g: [0-3] */
#define SSD_SET_GAMMA_CURVE(g)    SSD_CMD(0x26, 1 << (g))
#define SSD_SET_DISPLAY_OFF()   SSD_CMD(0x28)
#define SSD_SET_DISPLAY_ON()    SSD_CMD(0x29)
#define SSD_SET_COLUMN_ADDRESS(start_col,end_col) \
  SSD_CMD(0x2a, (start_col) >> 8, (start_col) & 0xff, (end_col) >> 8, (end_col) & 0xff)
#define SSD_SET_PAGE_ADDRESS(start_page,end_page) \
  SSD_CMD(0x2b, (start_page) >> 8, (start_page) & 0xff, (end_page) >> 8, (end_page) & 0xff)
#define SSD_WRITE_MEMORY_START()  SSD_CMD(0x2c)
#define SSD_READ_MEMORY_START()   SSD_CMD(0x2e)
#define SSD_SET_PARTIAL_AREA(start_row,end_row) \
  SSD_CMD(0x30, (start_row) >> 8, (start_row), (end_row) >> 8, (end_row))
#define SSD_SET_SCROLL_AREA(tfa,vsa,bfa) \
  SSD_CMD(0x33, (tfa) >> 8, (tfa), (vsa) >> 8, (vsa), (bfa) >> 8, (bfa))
#define SSD_SET_TEAR_OFF()    SSD_CMD(0x34)
#define SSD_SET_TEAR_ON(v_and_h_blank)  SSD_CMD(0x35, !!(v_and_h_blank))
#define SSD_SET_ADDRESS_MODE(arg) SSD_CMD(0x36, (arg))
#define SSD_SET_SCROLL_START(vsp) SSD_CMD(0x37, (vsp) >> 8, (vsp))
#define SSD_EXIT_IDLE_MODE()    SSD_CMD(0x38)
#define SSD_ENTER_IDLE_MODE()   SSD_CMD(0x39)
#define SSD_WRITE_MEMORY_CONTINUE() SSD_CMD(0x3c)
#define SSD_READ_MEMORY_CONTINUE()  SSD_CMD(0x3e)
#define SSD_SET_TEAR_SCANLINE(n)  SSD_CMD(0x44, (n) >> 8, (n))
#define SSD_GET_SCANLINE()    SSD_CMD(0x45) /* param: 2 */
#define SSD_READ_DDB()      SSD_CMD(0xa1) /* param: 5 */
#define SSD_SET_LCD_MODE(a,b,hdp,vdp,g) \
  SSD_CMD(0xb0, (a), (b), (hdp) >> 8, (hdp), (vdp) >> 8, (vdp), (g))
#define SSD_GET_LCD_MODE()    SSD_CMD(0xb1) /* param: 7 */
#define SSD_SET_HORI_PERIOD(ht,hps,hpw,lps,lpspp) \
  SSD_CMD(0xb4, (ht) >> 8, (ht), (hps) >> 8, (hps), (hpw), (lps) >> 8, (lps), (lpspp))
#define SSD_GET_HORI_PERIOD()   SSD_CMD(0xb5) /* param: 8 */
#define SSD_SET_VERT_PERIOD(vt,vps,vpw,fps) \
  SSD_CMD(0xb6, (vt) >> 8, (vt), (vps) >> 8, (vps), (vpw), (fps) >> 8, (fps))
#define SSD_GET_VERT_PERIOD()   SSD_CMD(0xb7) /* param: 7 */
#define SSD_SET_GPIO_CONF(a,b)    SSD_CMD(0xb8, (a), (b))
#define SSD_GET_GPIO_CONF()   SSD_CMD(0xb9) /* param: 2 */
#define SSD_SET_GPIO_VALUE(a)   SSD_CMD(0xba, (a))
#define SSD_GET_GPIO_STATUS()   SSD_CMD(0xbb) /* param: 1 */
#define SSD_SET_POST_PROC(a,b,c,d)  SSD_CMD(0xbc, (a), (b), (c), (d))
#define SSD_GET_POST_PROC()   SSD_CMD(0xbd) /* param: 4 */
#define SSD_SET_PWM_CONF(pwmf,pwm,c,d,e,f) \
  SSD_CMD(0xbe, (pwmf), (pwm), (c), (d), (e), (f))
#define SSD_GET_PWM_CONF()    SSD_CMD(0xbf) /* param: 7 */
#define SSD_SET_LCD_GEN0(a,gf,gr,f,gp) \
  SSD_CMD(0xc0, (a), (gf) >> 8, (gf), (gr) >> 8, (gr), (f) | (gp) >> 8, (gp))
#define SSD_GET_LCD_GEN0()    SSD_CMD(0xc1) /* param: 7 */
#define SSD_SET_LCD_GEN1(a,gf,gr,f,gp) \
  SSD_CMD(0xc2, (a), (gf) >> 8, (gf), (gr) >> 8, (gr), (f) | (gp) >> 8, (gp))
#define SSD_GET_LCD_GEN1()    SSD_CMD(0xc3) /* param: 7 */
#define SSD_SET_LCD_GEN2(a,gf,gr,f,gp) \
  SSD_CMD(0xc4, (a), (gf) >> 8, (gf), (gr) >> 8, (gr), (f) | (gp) >> 8, (gp))
#define SSD_GET_LCD_GEN2()    SSD_CMD(0xc5) /* param: 7 */
#define SSD_SET_LCD_GEN3(a,gf,gr,f,gp) \
  SSD_CMD(0xc6, (a), (gf) >> 8, (gf), (gr) >> 8, (gr), (f) | (gp) >> 8, (gp))
#define SSD_GET_LCD_GEN3()    SSD_CMD(0xc7) /* param: 7 */
#define SSD_SET_GPIO0_ROP(a,b)    SSD_CMD(0xc8, (a), (b))
#define SSD_GET_GPIO0_ROP()   SSD_CMD(0xc9) /* param: 2 */
#define SSD_SET_GPIO1_ROP(a,b)    SSD_CMD(0xca, (a), (b))
#define SSD_GET_GPIO1_ROP()   SSD_CMD(0xcb) /* param: 2 */
#define SSD_SET_GPIO2_ROP(a,b)    SSD_CMD(0xcc, (a), (b))
#define SSD_GET_GPIO2_ROP()   SSD_CMD(0xcd) /* param: 2 */
#define SSD_SET_GPIO3_ROP(a,b)    SSD_CMD(0xce, (a), (b))
#define SSD_GET_GPIO3_ROP()   SSD_CMD(0xcf) /* param: 2 */
#define SSD_SET_DBC_CONF(a)   SSD_CMD(0xd0, (a))
#define SSD_GET_DBC_CONF()    SSD_CMD(0xd1) /* param: 1 */
#define SSD_SET_DBC_TH(th1,th2,th3) \
  SSD_CMD(0xd4, (th1) >> 16, (th1) >> 8, (th1), (th2) >> 16, (th2) >> 8, (th2), (th3) >> 16, (th3) >> 8, (th3))
#define SSD_GET_DBC_TH()    SSD_CMD(0xd5) /* param: 9 */
#define SSD_SET_PLL(a)      SSD_CMD(0xe0, (a))
#define SSD_SET_PLL_MN(m,n,c)   SSD_CMD(0xe2, (m), (n), (c))
#define SSD_GET_PLL_MN()    SSD_CMD(0xe3) /* param: 3 */
#define SSD_GET_PLL_STATUS()    SSD_CMD(0xe4) /* param: 1 */
#define SSD_SET_DEEP_SLEEP()    SSD_CMD(0xe5)
#define SSD_SET_LSHIFT_FREQ(fpr)  SSD_CMD(0xe6, (fpr) >> 16, (fpr) >> 8, (fpr))
#define SSD_GET_LSHIFT_FREQ()   SSD_CMD(0xe7) /* param: 3 */
#define SSD_SET_PIXEL_DATA_INTERFACE(a) SSD_CMD(0xf0, (a))
#define SSD_GET_PIXEL_DATA_INTERFACE()  SSD_CMD(0xf1) /* param: 1 */

/* flags for SSD_SET_ADDRESS_MODE */
enum ssd_address_mode {
  SSD_ADDR_HOST_VERT_REVERSE    = 1 << 7, /* host->SSD: bottom to top */
  SSD_ADDR_HOST_HORI_REVERSE    = 1 << 6, /* host->SSD: EC to SC */
  SSD_ADDR_PANEL_COLUMN_REVERSE = 1 << 5, /* SSD->panel */
  SSD_ADDR_PANEL_LINE_REVERSE   = 1 << 4, /* SSD->panel */
  SSD_ADDR_PANEL_COLOR_REVERSE  = 1 << 3, /* SSD->panel: BGR instead of RGB */
  SSD_ADDR_PANEL_LINE_REFRESH_REVERSE = 1 << 2, /* SSD->panel: refresh from right to left side */
  SSD_ADDR_PANEL_HORI_FLIP      = 1 << 1,
  SSD_ADDR_PANEL_VERT_FLIP      = 1 << 0,
};

/* mode for SSD_SET_PIXEL_DATA_INTERFACE */
enum ssd_interface_fmt {
  SSD_DATA_8 = 0,          /* R[7:0]
                            * G[7:0]
                            * B[7:0] */

  SSD_DATA_12 = 1,         /* R[7:0] G[7:4]
                            * G[3:0] B[7:0] */

  SSD_DATA_16_PACKED = 2,  /* R1[7:0] G1[7:0]
                            * B1[7:0] R2[7:0]
                            * G2[7:0] B2[7:0] */

  SSD_DATA_16_565 = 3,     /* R[5:1] G[5:0] B[5:1] */

  SSD_DATA_18 = 4,         /* R[5:0] G[5:0] B[5:0] */

  SSD_DATA_24 = 5,         /* R[7:0] G[7:0] B[7:0] */

  SSD_DATA_9 = 6,          /* R[5:0] G[5:3]
                            * G[2:0] B[5:0] */
};

/* Some values are transmitted to the controller decremented by one; while the
 * above SSD_* command macros take those decremented parameters as are descibed
 * in the datasheet, the init functions will take care about decrementing these
 * appropriately because in this structure the more sensible non-adjusted
 * values are stored to ease calculations. */
struct ssd_init_vector {
  uint_least32_t in_clk_freq; /* XTAL or ext. clock input, both OR'ed in chip */
  uint_least8_t pll_m, pll_n;
  uint_least16_t ht, hps, hpw, lps, lpspp;
  uint_least16_t vt, vps, vpw, fps;
  uint_least16_t hdp, vdp; /* horizontal / vertical panel size */
  uint_least32_t lshift_mult;
  enum ssd_lcd_flags {
    SSD_LCD_18BIT             = 0 << (16+5),
    SSD_LCD_24BIT             = 1 << (16+5),
    SSD_LCD_COL_DEPTH_ENH_EN  = 1 << (16+4), /* only for 18 bit */
    SSD_LCD_DITHERING         = 0 << (16+3), /* only for 18 bit */
    SSD_LCD_FRC               = 1 << (16+3), /* only for 18 bit */
    SSD_LCD_LSHIFT_FALLING    = 0 << (16+2),
    SSD_LCD_LSHIFT_RISING     = 1 << (16+2),
    SSD_LCD_LLINE_LOW         = 0 << (16+1),
    SSD_LCD_LLINE_HIGH        = 1 << (16+1),
    SSD_LCD_LFRAME_LOW        = 0 << (16+0),
    SSD_LCD_LFRAME_HIGH       = 1 << (16+0),
    SSD_LCD_MODE_TFT          = 0 << ( 8+5),
    SSD_LCD_MODE_SERIAL       = 2 << ( 8+5),
    SSD_LCD_MODE_DUMMY        = 1 << ( 8+5), /* only for serial mode */
    /* only needed for SSD_LCD_MODE_SERIAL */
    SSD_LCD_EVEN_SHIFT        =          3,
    SSD_LCD_EVEN_MASK         = 7 << SSD_LCD_EVEN_SHIFT,
    SSD_LCD_ODD_SHIFT         =          0,
    SSD_LCD_ODD_MASK          = 7 << SSD_LCD_ODD_SHIFT,
    SSD_LCD_RGB               = 0,
    SSD_LCD_RBG               = 1,
    SSD_LCD_GRB               = 2,
    SSD_LCD_GBR               = 3,
    SSD_LCD_BRG               = 4,
    SSD_LCD_BGR               = 5,
  } lcd_flags; /* specify low-level TFT data transfer */
  unsigned pll_as_sysclk : 1;
};

struct ssd_display {
  enum ssd_lcd_flags lcd_flags;
  struct ssd_timings {
    uint_least16_t visible, front, sync, back;
  } hori, vert;
  uint_least32_t pxclk_min, pxclk_typ, pxclk_max;
};

/* --------------------------------------------------------------------------
 * low level init functions
 * -------------------------------------------------------------------------- */

uint_least32_t ssd_iv_get_vco_freq(const struct ssd_init_vector *iv);
uint_least32_t ssd_iv_get_pll_freq(const struct ssd_init_vector *iv);
uint_least32_t ssd_iv_get_sys_freq(const struct ssd_init_vector *iv);

/* returns the pixel clock frequency in 2**20 Hz calculated using the current
 * lshift_freq value from iv */
uint_least64_t ssd_iv_get_pixel_freq_frac(const struct ssd_init_vector *iv);

/* in Hz */
uint_least32_t ssd_iv_calc_pixel_freq(
  const struct ssd_init_vector *iv,
  uint_least16_t refresh_rate
);

/* calculates an lshift_mult setting for the desired pixel clock frequency,
 * hsync/vsync settings and PLL frequency already set in iv */
uint_least32_t ssd_iv_calc_lshift_mult(
  const struct ssd_init_vector *iv,
  uint_least32_t pixel_freq
);

void ssd_iv_set_hsync(
  struct ssd_init_vector *iv,
  unsigned display, unsigned front, unsigned sync, unsigned back,
  unsigned sync_move, unsigned lpspp
);

void ssd_iv_set_vsync(
  struct ssd_init_vector *iv,
  unsigned display, unsigned front, unsigned sync, unsigned back,
  unsigned sync_move
);

void ssd_iv_set_display(struct ssd_init_vector *iv, const struct ssd_display *d);

/* --------------------------------------------------------------------------
 * high level init functions
 * -------------------------------------------------------------------------- */

/* Prints a textual representation of all the settings in iv to stderr. */
void ssd_iv_print(const struct ssd_init_vector *iv);

enum ssd_err {
  SSD_ERR_NONE,
  SSD_ERR_VCO_OOR,
  SSD_ERR_SYS_CLK_OOR,
  SSD_ERR_PLL_M_OOR,
  SSD_ERR_PLL_N_OOR,
  SSD_ERR_LSHIFT_OOR,
  SSD_ERR_PLL_UNSTABLE,
  SSD_ERR_PXCLK_UNAVAIL,
  SSD_ERR_PXCLK_OOR,
};

const char * ssd_strerr(enum ssd_err err);

/* refresh_rate may be 0 iff the ssd_display does specify a
 * typical pixel clock != 0. Otherwise it overrides the typical pixel clock. */
enum ssd_err ssd_iv_init(
  struct ssd_init_vector *iv,
  uint_least32_t in_clk_freq,
  uint_least8_t pll_m, uint_least8_t pll_n, char pll_as_sysclk,
  const struct ssd_display *d, uint_least16_t refresh_rate
);

enum ssd_err ssd_iv_check(const struct ssd_init_vector *iv);

/* Turns off the display, initializes the PLL, sets it up as system clock if
 * requested and soft-resets the controller (meaning all register values except
 * for 0xe0 to 0xe5 are lost).
 *
 * If iv is invalid as determined by ssd_iv_check(), its error code is returned.
 *
 * If the macro SSD_RD_DATA is defined and after programming the PLL verifying
 * its stability by querying the controller fails, this function returns
 * SSD_ERR_PLL_UNSTABLE. In that case the PLL is shut down and the controller is
 * not reset. */
enum ssd_err ssd_init_pll(const struct ssd_init_vector *iv);

/* Sets up the pixel frequency, horizontal and vertical timings and turns the
 * display back on. */
enum ssd_err ssd_init_display(const struct ssd_init_vector *iv);

/* Convenience function to fully initialize the controller.
 *
 * Fills a ssd_init_vector structure with all the information given in the
 * parameters via ssd_iv_init(), then calls ssd_init_pll() followed by
 * ssd_init_display() and finally sets the given address mode and interface
 * format.
 *
 * If any of these fail, an error message is printed and the corresponding
 * error code is returned. */
enum ssd_err ssd_init(
  uint_least32_t in_clk_freq,
  uint_least8_t pll_m, uint_least8_t pll_n, char pll_as_sysclk,
  const struct ssd_display *d, uint_least16_t refresh_rate,
  enum ssd_address_mode adm, enum ssd_interface_fmt ifmt
);

#endif
