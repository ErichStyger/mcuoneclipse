/*
 * Application.c
 *
 *  Created on: 07.07.2014
 *      Author: tastyger
 */

#include "Application.h"
#include "NeoPixel.h"
#include "NeoLine.h"
#include "Cpu.h"

static void APP_Run(void) {
  (void)NEO_ClearAllPixel();
  (void)NEO_TransferPixels();
  for (;;) {
    (void)NEOL_PixelTrail(0xff, 0x00, 0x00, NEO_PIXEL_FIRST, NEO_PIXEL_LAST,  8, 25, 80);
    (void)NEOL_PixelTrail(0x00, 0xff, 0x00, NEO_PIXEL_FIRST, NEO_PIXEL_LAST, 10, 25, 40);
    (void)NEOL_PixelTrail(0x00, 0x00, 0xff, NEO_PIXEL_FIRST, NEO_PIXEL_LAST,  8, 25, 40);
    (void)NEOL_PixelTrail(0x7F, 0x00, 0x7F, NEO_PIXEL_FIRST, NEO_PIXEL_LAST,  8, 25, 40);
    (void)NEOL_PixelTrail(0x00, 0xff, 0xff, NEO_PIXEL_FIRST, NEO_PIXEL_LAST,  8, 30, 40);
    (void)NEOL_PixelTrail(0xff, 0xff, 0xff, NEO_PIXEL_FIRST, NEO_PIXEL_LAST,  8, 40, 40);
    (void)NEOL_PixelTrail(0x20, 0x40, 0x60, NEO_PIXEL_FIRST, NEO_PIXEL_LAST,  8, 50, 20);
  }
  /* at the end, clear all */
  (void)NEO_ClearAllPixel();
  (void)NEO_TransferPixels();
}

void APP_Start(void) {
  NEO_Init();
  Cpu_EnableInt(); /* enable interrupts */
  APP_Run();
}
