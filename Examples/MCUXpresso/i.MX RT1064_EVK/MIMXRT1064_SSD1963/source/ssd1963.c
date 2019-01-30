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

#define _POSIX_C_SOURCE 199309L /* for nanosleep() */
#define __STDC_FORMAT_MACROS  /* for PRI* macros */

#include <time.h>   /* for nanosleep() */
#include <errno.h>    /* for ssd_sleep() */
#include <assert.h>   /* for ssd_sleep() */
#include <inttypes.h>
#include <stdio.h>
#include <string.h>   /* for memset() */

#include "ssd1963.h"

/* this function may need adjustment when compiling for a non-POSIX compatible
 * platform */

/* 0 <= ms < 1000 */
static void ssd_sleep(unsigned ms)
{
  struct timespec req = { 0, ms * 1000000L };
  while (nanosleep(&req, &req) == -1)
    assert(errno == EINTR);
}

#define ARRAY_SIZE(arr)   (sizeof(arr)/sizeof(*(arr)))
#define STR(x)      #x
#define XSTR(x)     STR(x)

#define SSD_VCO_MIN   250000000
#define SSD_VCO_MAX   800000000
#define SSD_SYS_MIN     1000000
#define SSD_SYS_MAX   110000000

uint_least32_t ssd_iv_get_vco_freq(const struct ssd_init_vector *iv)
{
  return iv->in_clk_freq * iv->pll_m;
}

uint_least32_t ssd_iv_get_pll_freq(const struct ssd_init_vector *iv)
{
  return ssd_iv_get_vco_freq(iv) / iv->pll_n;
}

uint_least32_t ssd_iv_get_sys_freq(const struct ssd_init_vector *iv)
{
  return iv->pll_as_sysclk ? ssd_iv_get_pll_freq(iv) : iv->in_clk_freq;
}

uint_least64_t ssd_iv_get_pixel_freq_frac(const struct ssd_init_vector *iv)
{
  uint_least64_t f;

  f  = ssd_iv_get_vco_freq(iv);
  f *= iv->lshift_mult;
  f /= iv->pll_n;

  if (iv->lcd_flags & SSD_LCD_MODE_SERIAL)
    f <<= 2;

  return f;
}

uint_least32_t ssd_iv_calc_pixel_freq(
  const struct ssd_init_vector *iv,
  uint_least16_t refresh_rate
) {
  return (uint_least32_t)refresh_rate * iv->ht * iv->vt;
}

uint_least32_t ssd_iv_calc_lshift_mult(
  const struct ssd_init_vector *iv,
  uint_least32_t pixel_freq
) {
  uint_least64_t pclk = pixel_freq;

  if (iv->lcd_flags & SSD_LCD_MODE_SERIAL)
    pclk <<= 18;
  else
    pclk <<= 20;

  /* divide scaled pixel clock by PLL freq */
  return pclk * iv->pll_n / ssd_iv_get_vco_freq(iv);
}

void ssd_iv_set_hsync(
  struct ssd_init_vector *iv,
  unsigned display, unsigned front, unsigned sync, unsigned back,
  unsigned sync_move, unsigned lpspp
) {
  iv->hdp = display;
  iv->ht = display + front + sync + back;
  iv->hpw = sync;
  iv->hps = sync_move + sync + back;
  iv->lps = sync_move;
  iv->lpspp = lpspp;
}

void ssd_iv_set_vsync(
  struct ssd_init_vector *iv,
  unsigned display, unsigned front, unsigned sync, unsigned back,
  unsigned sync_move
) {
  iv->vdp = display;
  iv->vt = display + front + sync + back;
  iv->vpw = sync;
  iv->vps = sync_move + sync + back;
  iv->fps = sync_move;
}

void ssd_iv_set_display(struct ssd_init_vector *iv, const struct ssd_display *d)
{
  iv->lcd_flags = d->lcd_flags;
  ssd_iv_set_hsync(iv,
    d->hori.visible, d->hori.front, d->hori.sync, d->hori.back,
    0, 0);
  ssd_iv_set_vsync(iv,
    d->vert.visible, d->vert.front, d->vert.sync, d->vert.back,
    0);
}

void ssd_iv_print(const struct ssd_init_vector *iv)
{
  uint_least64_t pclk_scaled = ssd_iv_get_pixel_freq_frac(iv);
  fprintf(stderr,
    "in_clk_freq: %g MHz, "
    "PLL: %" PRIdLEAST32 "/%" PRIdLEAST32 " -> %g MHz, "
    "VCO: %g MHz\n"
    "sys: %g MHz, "
    "px clk: %" PRIdLEAST64 ".%" PRIdLEAST64 " Hz, "
    "lshift: %" PRIdLEAST32 ", rate: %g Hz\n"
    "ht, hps, hpw, lps, lpspp: %" PRIdLEAST16 " %" PRIdLEAST16 " %" PRIdLEAST16 " %" PRIdLEAST16 " %" PRIdLEAST16 "\n"
    "vt, vps, vpw, fps       : %" PRIdLEAST16 " %" PRIdLEAST16 " %" PRIdLEAST16 " %" PRIdLEAST16 "\n"
    "hdp: %" PRIdLEAST16 ", "
    "vdp: %" PRIdLEAST16 ", "
    "lcd-flags: 0x%02x 0x%02x 0x%02x\n",
    iv->in_clk_freq / 1e6,
    iv->pll_m, iv->pll_n, ssd_iv_get_pll_freq(iv) / 1e6,
    ssd_iv_get_vco_freq(iv) / 1e6,
    ssd_iv_get_sys_freq(iv) / 1e6,
    pclk_scaled >> 20, pclk_scaled & ((1L << 20) - 1),
    iv->lshift_mult, pclk_scaled / (0x1p20 * iv->ht * iv->vt),
    iv->ht, iv->hps, iv->hpw, iv->lps, iv->lpspp,
    iv->vt, iv->vps, iv->vpw, iv->fps,
    iv->hdp,
    iv->vdp,
    iv->lcd_flags >> 16, (iv->lcd_flags >> 8) & 0xff, iv->lcd_flags & 0xff);
}

const char * ssd_strerr(enum ssd_err err)
{
  static char buf[64];
  static const char *err_msgs[] = {
    [SSD_ERR_NONE]
    = "success",
    [SSD_ERR_VCO_OOR]
    = "VCO frequency out of range (" XSTR(SSD_VCO_MIN) "," XSTR(SSD_VCO_MAX) ") Hz",
    [SSD_ERR_SYS_CLK_OOR]
    = "system clock frequency out of range [" XSTR(SSD_SYS_MIN) "," XSTR(SSD_SYS_MAX) "] Hz",
    [SSD_ERR_PLL_M_OOR]
    = "PLL multiplier m out representable range",
    [SSD_ERR_PLL_N_OOR]
    = "PLL divider n out of representable range",
    [SSD_ERR_LSHIFT_OOR]
    = "LSHIFT multiplier out of representable range",
    [SSD_ERR_PLL_UNSTABLE]
    = "PLL did not stabilize",
    [SSD_ERR_PXCLK_UNAVAIL]
    = "refresh_rate not set and no typical pixel clock frequency available for the display",
    [SSD_ERR_PXCLK_OOR]
    = "pixel clock frequency out of range for the display"
  };

  if (err < ARRAY_SIZE(err_msgs))
    return err_msgs[err];

  snprintf(buf, sizeof(buf),
    "unknown error value %d: out of valid range",
    err);
  return buf;
}

enum ssd_err ssd_iv_init(
  struct ssd_init_vector *iv,
  uint_least32_t in_clk_freq,
  uint_least8_t pll_m, uint_least8_t pll_n, char pll_as_sysclk,
  const struct ssd_display *d, uint_least16_t refresh_rate
) {
  enum ssd_err r = SSD_ERR_NONE;
  uint_least32_t pclk;

  iv->in_clk_freq   = in_clk_freq;
  iv->pll_m         = pll_m;
  iv->pll_n         = pll_n;
  iv->pll_as_sysclk = pll_as_sysclk;

  ssd_iv_set_display(iv, d);

  r = ssd_iv_check(iv);
  if (r == SSD_ERR_LSHIFT_OOR)
    r = SSD_ERR_NONE;
  if (r != SSD_ERR_NONE)
    return r;

  if (refresh_rate)
    pclk      = ssd_iv_calc_pixel_freq(iv, refresh_rate);
  else if (d->pxclk_typ)
    pclk      = d->pxclk_typ;
  else
    return SSD_ERR_PXCLK_UNAVAIL;

  if ((d->pxclk_min && pclk < d->pxclk_min) ||
      (d->pxclk_max && pclk > d->pxclk_max))
    r = SSD_ERR_PXCLK_OOR;

  iv->lshift_mult   = ssd_iv_calc_lshift_mult(iv, pclk);
  pclk              = ssd_iv_get_pixel_freq_frac(iv) >> 20;

  if ((d->pxclk_min && pclk < d->pxclk_min) ||
      (d->pxclk_max && pclk > d->pxclk_max))
    r = SSD_ERR_PXCLK_OOR;

  return r;
}

enum ssd_err ssd_iv_check(const struct ssd_init_vector *iv)
{
  uint_least32_t vco;

  if (!iv->pll_m || iv->pll_m - 1 >= 1 << 8)
    return SSD_ERR_PLL_M_OOR;
  if (!iv->pll_n || iv->pll_n - 1 >= 1 << 4)
    return SSD_ERR_PLL_N_OOR;

  vco = ssd_iv_get_vco_freq(iv);
  if (!(SSD_VCO_MIN < vco && vco < SSD_VCO_MAX))
    return SSD_ERR_VCO_OOR;
  if (ssd_iv_get_sys_freq(iv) > SSD_SYS_MAX)
    return SSD_ERR_SYS_CLK_OOR;

  if (!iv->lshift_mult || iv->lshift_mult - 1 >= (uint_least32_t)1 << 19)
    return SSD_ERR_LSHIFT_OOR;

  return SSD_ERR_NONE;
}

enum ssd_err ssd_init_pll(const struct ssd_init_vector *iv)
{
  enum ssd_err r = SSD_ERR_NONE;

  r = ssd_iv_check(iv);
  if (r != SSD_ERR_NONE)
    return r;

  SSD_SET_DISPLAY_OFF();

  /* disable usage of PLL as system clock and the PLL itself */
  SSD_SET_PLL(0x00);

  SSD_SET_PLL_MN(
    iv->pll_m - 1,
    iv->pll_n - 1,
    0x04);         /* effectuate PLL settings */

  /* enable PLL and wait 100ms for it to settle */
  SSD_SET_PLL(0x01);
  ssd_sleep(100);

#ifdef SSD_RD_DATA
  SSD_GET_PLL_STATUS();
  if (!(SSD_RD_DATA() & 0x04)) {
    /* PLL unstable, deactivate it */
    SSD_SET_PLL(0x00);
    return SSD_ERR_PLL_UNSTABLE;
  }
#endif

  /* ok, PLL stable, use as system clock if requested */
  if (iv->pll_as_sysclk)
    SSD_SET_PLL(0x03);

  /* need to wait 5ms after soft reset */
  SSD_SOFT_RESET();
  ssd_sleep(5);

  return r;
}

enum ssd_err ssd_init_display(const struct ssd_init_vector *iv)
{
  enum ssd_err r = SSD_ERR_NONE;

  r = ssd_iv_check(iv);
  if (r != SSD_ERR_NONE)
    return r;

  SSD_SET_LSHIFT_FREQ(iv->lshift_mult - 1);

  SSD_SET_LCD_MODE(
    (iv->lcd_flags >> 16),
    (iv->lcd_flags >>  8) & 0xff,
    iv->hdp - 1,
    iv->vdp - 1,
    (iv->lcd_flags      ) & 0xff);

  SSD_SET_HORI_PERIOD(
    iv->ht - 1,
    iv->hps + (iv->lcd_flags & SSD_LCD_MODE_SERIAL ? iv->lpspp : 0),
    iv->hpw - 1,
    iv->lps,
    iv->lpspp);

  SSD_SET_VERT_PERIOD(
    iv->vt - 1,
    iv->vps,
    iv->vpw - 1,
    iv->fps);

  SSD_SET_DISPLAY_ON();

  return r;
}

enum ssd_err ssd_init(
  uint_least32_t in_clk_freq,
  uint_least8_t pll_m, uint_least8_t pll_n, char pll_as_sysclk,
  const struct ssd_display *d, uint_least16_t refresh_rate,
  enum ssd_address_mode adm, enum ssd_interface_fmt ifmt
) {
  enum ssd_err r;
  struct ssd_init_vector iv;

  memset(&iv, 0, sizeof(iv));

  r = ssd_iv_init(&iv,
    in_clk_freq, pll_m, pll_n, pll_as_sysclk,
    d, refresh_rate);

  ssd_iv_print(&iv);
  if (r != SSD_ERR_NONE) {
    fprintf(stderr, "error %d init'ing iv: %s\n", r, ssd_strerr(r));
    return r;
  }

  r = ssd_init_pll(&iv);
  if (r != SSD_ERR_NONE) {
    fprintf(stderr, "error %d init'ing PLL: %s\n", r, ssd_strerr(r));
    return r;
  }

  r = ssd_init_display(&iv);
  if (r != SSD_ERR_NONE) {
    fprintf(stderr, "error %d init'ing display: %s\n", r, ssd_strerr(r));
    return r;
  }

  SSD_SET_ADDRESS_MODE(adm);
  SSD_SET_PIXEL_DATA_INTERFACE(ifmt);

  return r;
}
