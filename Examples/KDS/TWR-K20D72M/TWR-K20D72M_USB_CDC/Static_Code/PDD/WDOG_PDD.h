/*
  PDD layer implementation for peripheral type WDOG
  (C) 2013 Freescale, Inc. All rights reserved.

  This file is static and it is generated from API-Factory
*/

#if !defined(WDOG_PDD_H_)
#define WDOG_PDD_H_

/* ----------------------------------------------------------------------------
   -- Test if supported MCU is active
   ---------------------------------------------------------------------------- */

#if !defined(MCU_ACTIVE)
  // No MCU is active
  #error WDOG PDD library: No derivative is active. Place proper #include with PDD memory map before including PDD library.
#elif \
      !defined(MCU_MK10D10) /* WDOG */ && \
      !defined(MCU_MK10D5) /* WDOG */ && \
      !defined(MCU_MK10D7) /* WDOG */ && \
      !defined(MCU_MK10F12) /* WDOG */ && \
      !defined(MCU_MK10DZ10) /* WDOG */ && \
      !defined(MCU_MK11DA5) /* WDOG */ && \
      !defined(MCU_MK11DA5WS) /* WDOG */ && \
      !defined(MCU_MK11D5) /* WDOG */ && \
      !defined(MCU_MK11D5WS) /* WDOG */ && \
      !defined(MCU_MK12D5) /* WDOG */ && \
      !defined(MCU_MK20D10) /* WDOG */ && \
      !defined(MCU_MK20D5) /* WDOG */ && \
      !defined(MCU_MK20D7) /* WDOG */ && \
      !defined(MCU_MK20F12) /* WDOG */ && \
      !defined(MCU_MK20DZ10) /* WDOG */ && \
      !defined(MCU_MK21DA5) /* WDOG */ && \
      !defined(MCU_MK21DA5WS) /* WDOG */ && \
      !defined(MCU_MK21D5) /* WDOG */ && \
      !defined(MCU_MK21D5WS) /* WDOG */ && \
      !defined(MCU_MK21FA12) /* WDOG */ && \
      !defined(MCU_MK21FA12WS) /* WDOG */ && \
      !defined(MCU_MK21F12) /* WDOG */ && \
      !defined(MCU_MK21F12WS) /* WDOG */ && \
      !defined(MCU_MK22D5) /* WDOG */ && \
      !defined(MCU_MK22F12810) /* WDOG */ && \
      !defined(MCU_MK22F12) /* WDOG */ && \
      !defined(MCU_MK22F25612) /* WDOG */ && \
      !defined(MCU_MK22F51212) /* WDOG */ && \
      !defined(MCU_MK24F12) /* WDOG */ && \
      !defined(MCU_MK30D10) /* WDOG */ && \
      !defined(MCU_MK30D7) /* WDOG */ && \
      !defined(MCU_MK30DZ10) /* WDOG */ && \
      !defined(MCU_MK40D10) /* WDOG */ && \
      !defined(MCU_MK40D7) /* WDOG */ && \
      !defined(MCU_MK40DZ10) /* WDOG */ && \
      !defined(MCU_MK40X256VMD100) /* WDOG */ && \
      !defined(MCU_MK50D10) /* WDOG */ && \
      !defined(MCU_MK50D7) /* WDOG */ && \
      !defined(MCU_MK50DZ10) /* WDOG */ && \
      !defined(MCU_MK51D10) /* WDOG */ && \
      !defined(MCU_MK51D7) /* WDOG */ && \
      !defined(MCU_MK51DZ10) /* WDOG */ && \
      !defined(MCU_MK52D10) /* WDOG */ && \
      !defined(MCU_MK52DZ10) /* WDOG */ && \
      !defined(MCU_MK53D10) /* WDOG */ && \
      !defined(MCU_MK53DZ10) /* WDOG */ && \
      !defined(MCU_MK60D10) /* WDOG */ && \
      !defined(MCU_MK60F12) /* WDOG */ && \
      !defined(MCU_MK60F15) /* WDOG */ && \
      !defined(MCU_MK60DZ10) /* WDOG */ && \
      !defined(MCU_MK60N512VMD100) /* WDOG */ && \
      !defined(MCU_MK61F12) /* WDOG */ && \
      !defined(MCU_MK61F15) /* WDOG */ && \
      !defined(MCU_MK61F12WS) /* WDOG */ && \
      !defined(MCU_MK61F15WS) /* WDOG */ && \
      !defined(MCU_MK63F12) /* WDOG */ && \
      !defined(MCU_MK63F12WS) /* WDOG */ && \
      !defined(MCU_MK64F12) /* WDOG */ && \
      !defined(MCU_MK70F12) /* WDOG */ && \
      !defined(MCU_MK70F15) /* WDOG */ && \
      !defined(MCU_MK70F12WS) /* WDOG */ && \
      !defined(MCU_MK70F15WS) /* WDOG */ && \
      !defined(MCU_MKE02Z2) /* WDOG */ && \
      !defined(MCU_MKE02Z4) /* WDOG */ && \
      !defined(MCU_SKEAZN642) /* WDOG */ && \
      !defined(MCU_MKE04Z1284) /* WDOG */ && \
      !defined(MCU_MKE04Z4) /* WDOG */ && \
      !defined(MCU_SKEAZN84) /* WDOG */ && \
      !defined(MCU_MKE06Z4) /* WDOG */ && \
      !defined(MCU_MKV10Z7) /* WDOG */ && \
      !defined(MCU_MKV31F12810) /* WDOG */ && \
      !defined(MCU_MKV31F25612) /* WDOG */ && \
      !defined(MCU_MKV31F51212) /* WDOG */ && \
      !defined(MCU_MKW21D5) /* WDOG */ && \
      !defined(MCU_MKW21D5WS) /* WDOG */ && \
      !defined(MCU_MKW22D5) /* WDOG */ && \
      !defined(MCU_MKW22D5WS) /* WDOG */ && \
      !defined(MCU_MKW24D5) /* WDOG */ && \
      !defined(MCU_MKW24D5WS) /* WDOG */ && \
      !defined(MCU_SKEAZ1284) /* WDOG */
  // Unsupported MCU is active
  #error WDOG PDD library: Unsupported derivative is active.
#endif

#include "PDD_Types.h"

/* ----------------------------------------------------------------------------
   -- Method symbol definitions
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MKE02Z2)) || (defined(MCU_MKE02Z4)) || (defined(MCU_MKE04Z1284)) || (defined(MCU_MKE04Z4)) || (defined(MCU_MKE06Z4)) || (defined(MCU_SKEAZ1284)) || (defined(MCU_SKEAZN642)) || (defined(MCU_SKEAZN84)))
/* Windowing mode constants */
  #define WDOG_PDD_WINDOWING_DISABLED 0U           /**< Disabled */
  #define WDOG_PDD_WINDOWING_ENABLED  WDOG_CS2_WIN_MASK /**< Enabled */

#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/* Windowing mode constants */
  #define WDOG_PDD_WINDOWING_DISABLED 0U           /**< Disabled */
  #define WDOG_PDD_WINDOWING_ENABLED  WDOG_STCTRLH_WINEN_MASK /**< Enabled */

#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
#if ((defined(MCU_MKE02Z2)) || (defined(MCU_MKE02Z4)) || (defined(MCU_MKE04Z1284)) || (defined(MCU_MKE04Z4)) || (defined(MCU_MKE06Z4)) || (defined(MCU_SKEAZ1284)) || (defined(MCU_SKEAZN642)) || (defined(MCU_SKEAZN84)))
/* Clock source constants. */
  #define WDOG_PDD_SOURCE_BUSCLOCK 0U              /**< Use bus clock as a clock source for the watchdog counter */
  #define WDOG_PDD_SOURCE_LPOCLK   0x1U            /**< Use 1 kHz internal low-power oscillator as a clock source for the watchdog counter */
  #define WDOG_PDD_SOURCE_ICSIRCLK 0x2U            /**< Use 32 kHz internal oscillator as a clock source for the watchdog counter */
  #define WDOG_PDD_SOURCE_ERCLK    0x3U            /**< Use external clock as a clock source for the watchdog counter */

#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/* Clock source constants. */
  #define WDOG_PDD_SOURCE_DEDICATED 0U             /**< Dedicated */
  #define WDOG_PDD_SOURCE_ALTERNATE WDOG_STCTRLH_CLKSRC_MASK /**< Alternate */

#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
#if ((defined(MCU_MKE02Z2)) || (defined(MCU_MKE02Z4)) || (defined(MCU_MKE04Z1284)) || (defined(MCU_MKE04Z4)) || (defined(MCU_MKE06Z4)) || (defined(MCU_SKEAZ1284)) || (defined(MCU_SKEAZN642)) || (defined(MCU_SKEAZN84)))
/* Refresh constants */
  #define WDOG_PDD_KEY_1 0x2A6U                    /**< First key of the refresh sequence */
  #define WDOG_PDD_KEY_2 0x80B4U                   /**< Second key of the refresh sequence */

#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/* Refresh constants */
  #define WDOG_PDD_KEY_1 0xA602U                   /**< First key of the refresh sequence */
  #define WDOG_PDD_KEY_2 0xB480U                   /**< Second key of the refresh sequence */

#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
#if ((defined(MCU_MKE02Z2)) || (defined(MCU_MKE02Z4)) || (defined(MCU_MKE04Z1284)) || (defined(MCU_MKE04Z4)) || (defined(MCU_MKE06Z4)) || (defined(MCU_SKEAZ1284)) || (defined(MCU_SKEAZN642)) || (defined(MCU_SKEAZN84)))
/* Unlock constants */
  #define WDOG_PDD_UNLOCK_1 0x20C5U                /**< First key of the unlock sequence */
  #define WDOG_PDD_UNLOCK_2 0x28D9U                /**< Second key of the unlock sequence */

#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/* Unlock constants */
  #define WDOG_PDD_UNLOCK_1 0xC520U                /**< First key of the unlock sequence */
  #define WDOG_PDD_UNLOCK_2 0xD928U                /**< Second key of the unlock sequence */

#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
#if ((defined(MCU_MKE02Z2)) || (defined(MCU_MKE02Z4)) || (defined(MCU_MKE04Z1284)) || (defined(MCU_MKE04Z4)) || (defined(MCU_MKE06Z4)) || (defined(MCU_SKEAZ1284)) || (defined(MCU_SKEAZN642)) || (defined(MCU_SKEAZN84)))
/* Reference clock prescaler constants */
  #define WDOG_PDD_DIVIDE_1   0U                   /**< Prescaler factor 1 */
  #define WDOG_PDD_DIVIDE_256 0x1U                 /**< Prescaler factor 256 */

#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/* Reference clock prescaler constants */
  #define WDOG_PDD_DIVIDE_1 0U                     /**< Prescaler factor 1 */
  #define WDOG_PDD_DIVIDE_2 0x1U                   /**< Prescaler factor 2 */
  #define WDOG_PDD_DIVIDE_3 0x2U                   /**< Prescaler factor 3 */
  #define WDOG_PDD_DIVIDE_4 0x3U                   /**< Prescaler factor 4 */
  #define WDOG_PDD_DIVIDE_5 0x4U                   /**< Prescaler factor 5 */
  #define WDOG_PDD_DIVIDE_6 0x5U                   /**< Prescaler factor 6 */
  #define WDOG_PDD_DIVIDE_7 0x6U                   /**< Prescaler factor 7 */
  #define WDOG_PDD_DIVIDE_8 0x7U                   /**< Prescaler factor 8 */

#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */

/* ----------------------------------------------------------------------------
   -- GetAllowUpdateStatus
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MKE02Z2)) || (defined(MCU_MKE02Z4)) || (defined(MCU_MKE04Z1284)) || (defined(MCU_MKE04Z4)) || (defined(MCU_MKE06Z4)) || (defined(MCU_SKEAZ1284)) || (defined(MCU_SKEAZN642)) || (defined(MCU_SKEAZN84)))
/**
 * @brief Returns non-zero if watchdog registers can be unlocked.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: WDOG_STCTRLH, WDOG_CS1
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint8_t result = WDOG_PDD_GetAllowUpdateStatus(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define WDOG_PDD_GetAllowUpdateStatus(PeripheralBase) ( \
      (uint8_t)(WDOG_CS1_REG(PeripheralBase) & WDOG_CS1_UPDATE_MASK) \
    )
#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/**
 * @brief Returns non-zero if watchdog registers can be unlocked.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 16-bit value.
 * @remarks The macro accesses the following registers: WDOG_STCTRLH, WDOG_CS1
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint16_t result = WDOG_PDD_GetAllowUpdateStatus(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define WDOG_PDD_GetAllowUpdateStatus(PeripheralBase) ( \
      (uint16_t)(WDOG_STCTRLH_REG(PeripheralBase) & WDOG_STCTRLH_ALLOWUPDATE_MASK) \
    )
#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */

/* ----------------------------------------------------------------------------
   -- DisableUpdate
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MKE02Z2)) || (defined(MCU_MKE02Z4)) || (defined(MCU_MKE04Z1284)) || (defined(MCU_MKE04Z4)) || (defined(MCU_MKE06Z4)) || (defined(MCU_SKEAZ1284)) || (defined(MCU_SKEAZN642)) || (defined(MCU_SKEAZN84)))
/**
 * @brief No further updates allowed to WDOG write once registers.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: WDOG_STCTRLH, WDOG_CS1
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      WDOG_PDD_DisableUpdate(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define WDOG_PDD_DisableUpdate(PeripheralBase) ( \
      WDOG_CS1_REG(PeripheralBase) &= \
       (uint8_t)(~(uint8_t)WDOG_CS1_UPDATE_MASK) \
    )
#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/**
 * @brief No further updates allowed to WDOG write once registers.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: WDOG_STCTRLH, WDOG_CS1
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      WDOG_PDD_DisableUpdate(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define WDOG_PDD_DisableUpdate(PeripheralBase) ( \
      WDOG_STCTRLH_REG(PeripheralBase) &= \
       (uint16_t)(~(uint16_t)WDOG_STCTRLH_ALLOWUPDATE_MASK) \
    )
#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */

/* ----------------------------------------------------------------------------
   -- SetWindowingMode
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MKE02Z2)) || (defined(MCU_MKE02Z4)) || (defined(MCU_MKE04Z1284)) || (defined(MCU_MKE04Z4)) || (defined(MCU_MKE06Z4)) || (defined(MCU_SKEAZ1284)) || (defined(MCU_SKEAZN642)) || (defined(MCU_SKEAZN84)))
/**
 * @brief Configures the windowing mode operation.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mode New value of the mode. Use constants from group "Windowing mode
 *        constants". This parameter is 8 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: WDOG_STCTRLH, WDOG_CS2
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      WDOG_PDD_SetWindowingMode(<peripheral>_BASE_PTR,
 *      WDOG_PDD_WINDOWING_DISABLED);
 *      @endcode
 */
  #define WDOG_PDD_SetWindowingMode(PeripheralBase, Mode) ( \
      WDOG_CS2_REG(PeripheralBase) = \
       (uint8_t)(( \
        (uint8_t)(( \
         WDOG_CS2_REG(PeripheralBase)) & (( \
         (uint8_t)(~(uint8_t)WDOG_CS2_WIN_MASK)) & ( \
         (uint8_t)(~(uint8_t)WDOG_CS2_FLG_MASK))))) | ( \
        (uint8_t)(Mode))) \
    )
#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/**
 * @brief Configures the windowing mode operation.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mode New value of the mode. Use constants from group "Windowing mode
 *        constants". This parameter is 16 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: WDOG_STCTRLH, WDOG_CS2
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      WDOG_PDD_SetWindowingMode(<peripheral>_BASE_PTR,
 *      WDOG_PDD_WINDOWING_DISABLED);
 *      @endcode
 */
  #define WDOG_PDD_SetWindowingMode(PeripheralBase, Mode) ( \
      WDOG_STCTRLH_REG(PeripheralBase) = \
       (uint16_t)(( \
        (uint16_t)(( \
         WDOG_STCTRLH_REG(PeripheralBase)) & ( \
         (uint16_t)(~(uint16_t)WDOG_STCTRLH_WINEN_MASK)))) | ( \
        (uint16_t)(Mode))) \
    )
#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */

/* ----------------------------------------------------------------------------
   -- GetInterruptMask
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MKE02Z2)) || (defined(MCU_MKE02Z4)) || (defined(MCU_MKE04Z1284)) || (defined(MCU_MKE04Z4)) || (defined(MCU_MKE06Z4)) || (defined(MCU_SKEAZ1284)) || (defined(MCU_SKEAZN642)) || (defined(MCU_SKEAZN84)))
/**
 * @brief Returns interrupt mask.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: WDOG_STCTRLH, WDOG_CS1
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint8_t result = WDOG_PDD_GetInterruptMask(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define WDOG_PDD_GetInterruptMask(PeripheralBase) ( \
      (uint8_t)(WDOG_CS1_REG(PeripheralBase) & WDOG_CS1_INT_MASK) \
    )
#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/**
 * @brief Returns interrupt mask.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 16-bit value.
 * @remarks The macro accesses the following registers: WDOG_STCTRLH, WDOG_CS1
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint16_t result = WDOG_PDD_GetInterruptMask(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define WDOG_PDD_GetInterruptMask(PeripheralBase) ( \
      (uint16_t)(WDOG_STCTRLH_REG(PeripheralBase) & WDOG_STCTRLH_IRQRSTEN_MASK) \
    )
#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */

/* ----------------------------------------------------------------------------
   -- EnableInterrupt
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MKE02Z2)) || (defined(MCU_MKE02Z4)) || (defined(MCU_MKE04Z1284)) || (defined(MCU_MKE04Z4)) || (defined(MCU_MKE06Z4)) || (defined(MCU_SKEAZ1284)) || (defined(MCU_SKEAZN642)) || (defined(MCU_SKEAZN84)))
/**
 * @brief Enables the WDOG interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: WDOG_STCTRLH, WDOG_CS1
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      WDOG_PDD_EnableInterrupt(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define WDOG_PDD_EnableInterrupt(PeripheralBase) ( \
      WDOG_CS1_REG(PeripheralBase) |= \
       WDOG_CS1_INT_MASK \
    )
#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/**
 * @brief Enables the WDOG interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: WDOG_STCTRLH, WDOG_CS1
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      WDOG_PDD_EnableInterrupt(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define WDOG_PDD_EnableInterrupt(PeripheralBase) ( \
      WDOG_STCTRLH_REG(PeripheralBase) |= \
       WDOG_STCTRLH_IRQRSTEN_MASK \
    )
#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */

/* ----------------------------------------------------------------------------
   -- DisableInterrupt
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MKE02Z2)) || (defined(MCU_MKE02Z4)) || (defined(MCU_MKE04Z1284)) || (defined(MCU_MKE04Z4)) || (defined(MCU_MKE06Z4)) || (defined(MCU_SKEAZ1284)) || (defined(MCU_SKEAZN642)) || (defined(MCU_SKEAZN84)))
/**
 * @brief Disables the WDOG interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: WDOG_STCTRLH, WDOG_CS1
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      WDOG_PDD_DisableInterrupt(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define WDOG_PDD_DisableInterrupt(PeripheralBase) ( \
      WDOG_CS1_REG(PeripheralBase) &= \
       (uint8_t)(~(uint8_t)WDOG_CS1_INT_MASK) \
    )
#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/**
 * @brief Disables the WDOG interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: WDOG_STCTRLH, WDOG_CS1
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      WDOG_PDD_DisableInterrupt(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define WDOG_PDD_DisableInterrupt(PeripheralBase) ( \
      WDOG_STCTRLH_REG(PeripheralBase) &= \
       (uint16_t)(~(uint16_t)WDOG_STCTRLH_IRQRSTEN_MASK) \
    )
#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */

/* ----------------------------------------------------------------------------
   -- SelectClockSource
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MKE02Z2)) || (defined(MCU_MKE02Z4)) || (defined(MCU_MKE04Z1284)) || (defined(MCU_MKE04Z4)) || (defined(MCU_MKE06Z4)) || (defined(MCU_SKEAZ1284)) || (defined(MCU_SKEAZN642)) || (defined(MCU_SKEAZN84)))
/**
 * @brief Selects clock source.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Source New value of the source. Use constants from group "Clock source
 *        constants.". This parameter is 8 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: WDOG_STCTRLH, WDOG_CS2
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      WDOG_PDD_SelectClockSource(<peripheral>_BASE_PTR,
 *      WDOG_PDD_SOURCE_BUSCLOCK);
 *      @endcode
 */
  #define WDOG_PDD_SelectClockSource(PeripheralBase, Source) ( \
      WDOG_CS2_REG(PeripheralBase) = \
       (uint8_t)(( \
        (uint8_t)(( \
         WDOG_CS2_REG(PeripheralBase)) & (( \
         (uint8_t)(~(uint8_t)WDOG_CS2_CLK_MASK)) & ( \
         (uint8_t)(~(uint8_t)WDOG_CS2_FLG_MASK))))) | ( \
        (uint8_t)(Source))) \
    )
#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/**
 * @brief Selects clock source.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Source New value of the source. Use constants from group "Clock source
 *        constants.". This parameter is 16 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: WDOG_STCTRLH, WDOG_CS2
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      WDOG_PDD_SelectClockSource(<peripheral>_BASE_PTR,
 *      WDOG_PDD_SOURCE_DEDICATED);
 *      @endcode
 */
  #define WDOG_PDD_SelectClockSource(PeripheralBase, Source) ( \
      WDOG_STCTRLH_REG(PeripheralBase) = \
       (uint16_t)(( \
        (uint16_t)(( \
         WDOG_STCTRLH_REG(PeripheralBase)) & ( \
         (uint16_t)(~(uint16_t)WDOG_STCTRLH_CLKSRC_MASK)))) | ( \
        (uint16_t)(Source))) \
    )
#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */

/* ----------------------------------------------------------------------------
   -- EnableDevice
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MKE02Z2)) || (defined(MCU_MKE02Z4)) || (defined(MCU_MKE04Z1284)) || (defined(MCU_MKE04Z4)) || (defined(MCU_MKE06Z4)) || (defined(MCU_SKEAZ1284)) || (defined(MCU_SKEAZN642)) || (defined(MCU_SKEAZN84)))
/**
 * @brief Enables the WDOG device.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of WDOG device. This parameter is of "Global
 *        enumeration used for specifying general enable/disable states (PDD_DISABLE
 *        and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: WDOG_STCTRLH, WDOG_CS1
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      WDOG_PDD_EnableDevice(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
  #define WDOG_PDD_EnableDevice(PeripheralBase, State) ( \
      WDOG_CS1_REG(PeripheralBase) = \
       (uint8_t)(( \
        (uint8_t)(WDOG_CS1_REG(PeripheralBase) & (uint8_t)(~(uint8_t)WDOG_CS1_EN_MASK))) | ( \
        (uint8_t)((uint8_t)(State) << WDOG_CS1_EN_SHIFT))) \
    )
#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/**
 * @brief Enables the WDOG device.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of WDOG device. This parameter is of "Global
 *        enumeration used for specifying general enable/disable states (PDD_DISABLE
 *        and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: WDOG_STCTRLH, WDOG_CS1
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      WDOG_PDD_EnableDevice(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
  #define WDOG_PDD_EnableDevice(PeripheralBase, State) ( \
      WDOG_STCTRLH_REG(PeripheralBase) = \
       (uint16_t)(( \
        (uint16_t)(( \
         WDOG_STCTRLH_REG(PeripheralBase)) & ( \
         (uint16_t)(~(uint16_t)WDOG_STCTRLH_WDOGEN_MASK)))) | ( \
        (uint16_t)(State))) \
    )
#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */

/* ----------------------------------------------------------------------------
   -- GetEnableDeviceStatus
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MKE02Z2)) || (defined(MCU_MKE02Z4)) || (defined(MCU_MKE04Z1284)) || (defined(MCU_MKE04Z4)) || (defined(MCU_MKE06Z4)) || (defined(MCU_SKEAZ1284)) || (defined(MCU_SKEAZN642)) || (defined(MCU_SKEAZN84)))
/**
 * @brief Returns current state of WDOG device.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: WDOG_STCTRLH, WDOG_CS1
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint8_t result = WDOG_PDD_GetEnableDeviceStatus(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define WDOG_PDD_GetEnableDeviceStatus(PeripheralBase) ( \
      (uint8_t)(WDOG_CS1_REG(PeripheralBase) & WDOG_CS1_EN_MASK) \
    )
#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/**
 * @brief Returns current state of WDOG device.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 16-bit value.
 * @remarks The macro accesses the following registers: WDOG_STCTRLH, WDOG_CS1
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint16_t result = WDOG_PDD_GetEnableDeviceStatus(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define WDOG_PDD_GetEnableDeviceStatus(PeripheralBase) ( \
      (uint16_t)(WDOG_STCTRLH_REG(PeripheralBase) & WDOG_STCTRLH_WDOGEN_MASK) \
    )
#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */

/* ----------------------------------------------------------------------------
   -- WriteControlHighReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes value to the watchdog status and control register high.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value New content of the watchdog status and control register high.
 *        This parameter is a 16-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: WDOG_STCTRLH.
 * @par Example:
 *      @code
 *      WDOG_PDD_WriteControlHighReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define WDOG_PDD_WriteControlHighReg(PeripheralBase, Value) ( \
    WDOG_STCTRLH_REG(PeripheralBase) = \
     (uint16_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadControlHighReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the watchdog status and control register high.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 16-bit value.
 * @remarks The macro accesses the following registers: WDOG_STCTRLH.
 * @par Example:
 *      @code
 *      uint16_t result = WDOG_PDD_ReadControlHighReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define WDOG_PDD_ReadControlHighReg(PeripheralBase) ( \
    WDOG_STCTRLH_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- GetInterruptFlag
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MKE02Z2)) || (defined(MCU_MKE02Z4)) || (defined(MCU_MKE04Z1284)) || (defined(MCU_MKE04Z4)) || (defined(MCU_MKE06Z4)) || (defined(MCU_SKEAZ1284)) || (defined(MCU_SKEAZN642)) || (defined(MCU_SKEAZN84)))
/**
 * @brief Returns interrupt flag bit.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: WDOG_STCTRLL, WDOG_CS2
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint8_t result = WDOG_PDD_GetInterruptFlag(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define WDOG_PDD_GetInterruptFlag(PeripheralBase) ( \
      (uint8_t)(WDOG_CS2_REG(PeripheralBase) & WDOG_CS2_FLG_MASK) \
    )
#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/**
 * @brief Returns interrupt flag bit.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 16-bit value.
 * @remarks The macro accesses the following registers: WDOG_STCTRLL, WDOG_CS2
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint16_t result = WDOG_PDD_GetInterruptFlag(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define WDOG_PDD_GetInterruptFlag(PeripheralBase) ( \
      (uint16_t)(WDOG_STCTRLL_REG(PeripheralBase) & WDOG_STCTRLL_INTFLG_MASK) \
    )
#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */

/* ----------------------------------------------------------------------------
   -- ClearInterruptFlag
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MKE02Z2)) || (defined(MCU_MKE02Z4)) || (defined(MCU_MKE04Z1284)) || (defined(MCU_MKE04Z4)) || (defined(MCU_MKE06Z4)) || (defined(MCU_SKEAZ1284)) || (defined(MCU_SKEAZN642)) || (defined(MCU_SKEAZN84)))
/**
 * @brief Clears interrupt flag.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: WDOG_STCTRLL, WDOG_CS2
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      WDOG_PDD_ClearInterruptFlag(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define WDOG_PDD_ClearInterruptFlag(PeripheralBase) ( \
      WDOG_CS2_REG(PeripheralBase) = \
       (uint8_t)(WDOG_CS2_FLG_MASK | 0x1U) \
    )
#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/**
 * @brief Clears interrupt flag.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: WDOG_STCTRLL, WDOG_CS2
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      WDOG_PDD_ClearInterruptFlag(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define WDOG_PDD_ClearInterruptFlag(PeripheralBase) ( \
      WDOG_STCTRLL_REG(PeripheralBase) = \
       (uint16_t)(WDOG_STCTRLL_INTFLG_MASK | 0x1U) \
    )
#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */

/* ----------------------------------------------------------------------------
   -- WriteControlLowReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes value to the watchdog status and control register low.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value New content of the watchdog status and control register low.
 *        This parameter is a 16-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: WDOG_STCTRLL.
 * @par Example:
 *      @code
 *      WDOG_PDD_WriteControlLowReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define WDOG_PDD_WriteControlLowReg(PeripheralBase, Value) ( \
    WDOG_STCTRLL_REG(PeripheralBase) = \
     (uint16_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadControlLowReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the watchdog status and control register low.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 16-bit value.
 * @remarks The macro accesses the following registers: WDOG_STCTRLL.
 * @par Example:
 *      @code
 *      uint16_t result = WDOG_PDD_ReadControlLowReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define WDOG_PDD_ReadControlLowReg(PeripheralBase) ( \
    WDOG_STCTRLL_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteTimeOutHighReg
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MKE02Z2)) || (defined(MCU_MKE02Z4)) || (defined(MCU_MKE04Z1284)) || (defined(MCU_MKE04Z4)) || (defined(MCU_MKE06Z4)) || (defined(MCU_SKEAZ1284)) || (defined(MCU_SKEAZN642)) || (defined(MCU_SKEAZN84)))
/**
 * @brief Writes value to the watchdog time-out value register high.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value New content of the watchdog time-out value register high. This
 *        parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: WDOG_TOVALH.
 * @par Example:
 *      @code
 *      WDOG_PDD_WriteTimeOutHighReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
  #define WDOG_PDD_WriteTimeOutHighReg(PeripheralBase, Value) ( \
      WDOG_TOVALH_REG(PeripheralBase) = \
       (uint8_t)(Value) \
    )
#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/**
 * @brief Writes value to the watchdog time-out value register high.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value New content of the watchdog time-out value register high. This
 *        parameter is a 16-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: WDOG_TOVALH.
 * @par Example:
 *      @code
 *      WDOG_PDD_WriteTimeOutHighReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
  #define WDOG_PDD_WriteTimeOutHighReg(PeripheralBase, Value) ( \
      WDOG_TOVALH_REG(PeripheralBase) = \
       (uint16_t)(Value) \
    )
#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */

/* ----------------------------------------------------------------------------
   -- ReadTimeOutHighReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the watchdog time-out value register high.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 16-bit value.
 * @remarks The macro accesses the following registers: WDOG_TOVALH.
 * @par Example:
 *      @code
 *      uint16_t result = WDOG_PDD_ReadTimeOutHighReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define WDOG_PDD_ReadTimeOutHighReg(PeripheralBase) ( \
    WDOG_TOVALH_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteTimeOutLowReg
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MKE02Z2)) || (defined(MCU_MKE02Z4)) || (defined(MCU_MKE04Z1284)) || (defined(MCU_MKE04Z4)) || (defined(MCU_MKE06Z4)) || (defined(MCU_SKEAZ1284)) || (defined(MCU_SKEAZN642)) || (defined(MCU_SKEAZN84)))
/**
 * @brief Writes value to the watchdog time-out value register low.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value New content of the watchdog time-out value register low. This
 *        parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: WDOG_TOVALL.
 * @par Example:
 *      @code
 *      WDOG_PDD_WriteTimeOutLowReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
  #define WDOG_PDD_WriteTimeOutLowReg(PeripheralBase, Value) ( \
      WDOG_TOVALL_REG(PeripheralBase) = \
       (uint8_t)(Value) \
    )
#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/**
 * @brief Writes value to the watchdog time-out value register low.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value New content of the watchdog time-out value register low. This
 *        parameter is a 16-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: WDOG_TOVALL.
 * @par Example:
 *      @code
 *      WDOG_PDD_WriteTimeOutLowReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
  #define WDOG_PDD_WriteTimeOutLowReg(PeripheralBase, Value) ( \
      WDOG_TOVALL_REG(PeripheralBase) = \
       (uint16_t)(Value) \
    )
#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */

/* ----------------------------------------------------------------------------
   -- ReadTimeOutLowReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the watchdog time-out value register low.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 16-bit value.
 * @remarks The macro accesses the following registers: WDOG_TOVALL.
 * @par Example:
 *      @code
 *      uint16_t result = WDOG_PDD_ReadTimeOutLowReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define WDOG_PDD_ReadTimeOutLowReg(PeripheralBase) ( \
    WDOG_TOVALL_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteWindowHighReg
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MKE02Z2)) || (defined(MCU_MKE02Z4)) || (defined(MCU_MKE04Z1284)) || (defined(MCU_MKE04Z4)) || (defined(MCU_MKE06Z4)) || (defined(MCU_SKEAZ1284)) || (defined(MCU_SKEAZN642)) || (defined(MCU_SKEAZN84)))
/**
 * @brief Writes value to the watchdog window register high.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value New content of the watchdog window register high. This parameter
 *        is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: WDOG_WINH.
 * @par Example:
 *      @code
 *      WDOG_PDD_WriteWindowHighReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
  #define WDOG_PDD_WriteWindowHighReg(PeripheralBase, Value) ( \
      WDOG_WINH_REG(PeripheralBase) = \
       (uint8_t)(Value) \
    )
#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/**
 * @brief Writes value to the watchdog window register high.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value New content of the watchdog window register high. This parameter
 *        is a 16-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: WDOG_WINH.
 * @par Example:
 *      @code
 *      WDOG_PDD_WriteWindowHighReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
  #define WDOG_PDD_WriteWindowHighReg(PeripheralBase, Value) ( \
      WDOG_WINH_REG(PeripheralBase) = \
       (uint16_t)(Value) \
    )
#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */

/* ----------------------------------------------------------------------------
   -- ReadWindowHighReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the watchdog window register high.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 16-bit value.
 * @remarks The macro accesses the following registers: WDOG_WINH.
 * @par Example:
 *      @code
 *      uint16_t result = WDOG_PDD_ReadWindowHighReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define WDOG_PDD_ReadWindowHighReg(PeripheralBase) ( \
    WDOG_WINH_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteWindowLowReg
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MKE02Z2)) || (defined(MCU_MKE02Z4)) || (defined(MCU_MKE04Z1284)) || (defined(MCU_MKE04Z4)) || (defined(MCU_MKE06Z4)) || (defined(MCU_SKEAZ1284)) || (defined(MCU_SKEAZN642)) || (defined(MCU_SKEAZN84)))
/**
 * @brief Writes value to the watchdog window register low.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value New content of the watchdog window register low. This parameter
 *        is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: WDOG_WINL.
 * @par Example:
 *      @code
 *      WDOG_PDD_WriteWindowLowReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
  #define WDOG_PDD_WriteWindowLowReg(PeripheralBase, Value) ( \
      WDOG_WINL_REG(PeripheralBase) = \
       (uint8_t)(Value) \
    )
#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/**
 * @brief Writes value to the watchdog window register low.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value New content of the watchdog window register low. This parameter
 *        is a 16-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: WDOG_WINL.
 * @par Example:
 *      @code
 *      WDOG_PDD_WriteWindowLowReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
  #define WDOG_PDD_WriteWindowLowReg(PeripheralBase, Value) ( \
      WDOG_WINL_REG(PeripheralBase) = \
       (uint16_t)(Value) \
    )
#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */

/* ----------------------------------------------------------------------------
   -- ReadWindowLowReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the watchdog window register low.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 16-bit value.
 * @remarks The macro accesses the following registers: WDOG_WINL.
 * @par Example:
 *      @code
 *      uint16_t result = WDOG_PDD_ReadWindowLowReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define WDOG_PDD_ReadWindowLowReg(PeripheralBase) ( \
    WDOG_WINL_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteRefreshReg
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MKE02Z2)) || (defined(MCU_MKE02Z4)) || (defined(MCU_MKE04Z1284)) || (defined(MCU_MKE04Z4)) || (defined(MCU_MKE06Z4)) || (defined(MCU_SKEAZ1284)) || (defined(MCU_SKEAZN642)) || (defined(MCU_SKEAZN84)))
/**
 * @brief Writes value to the watchdog refresh register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Service constant. Use constants from group "Refresh constants".
 *        This parameter is 16 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: WDOG_REFRESH, WDOG_CNT
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      WDOG_PDD_WriteRefreshReg(<peripheral>_BASE_PTR, WDOG_PDD_KEY_1);
 *      @endcode
 */
  #define WDOG_PDD_WriteRefreshReg(PeripheralBase, Value) ( \
      WDOG_CNT_REG(PeripheralBase) = \
       (uint16_t)(Value) \
    )
#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/**
 * @brief Writes value to the watchdog refresh register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Service constant. Use constants from group "Refresh constants".
 *        This parameter is 16 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: WDOG_REFRESH, WDOG_CNT
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      WDOG_PDD_WriteRefreshReg(<peripheral>_BASE_PTR, WDOG_PDD_KEY_1);
 *      @endcode
 */
  #define WDOG_PDD_WriteRefreshReg(PeripheralBase, Value) ( \
      WDOG_REFRESH_REG(PeripheralBase) = \
       (uint16_t)(Value) \
    )
#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */

/* ----------------------------------------------------------------------------
   -- ReadRefreshReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the watchdog refresh register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 16-bit value.
 * @remarks The macro accesses the following registers: WDOG_REFRESH.
 * @par Example:
 *      @code
 *      uint16_t result = WDOG_PDD_ReadRefreshReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define WDOG_PDD_ReadRefreshReg(PeripheralBase) ( \
    WDOG_REFRESH_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteUnlockReg
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MKE02Z2)) || (defined(MCU_MKE02Z4)) || (defined(MCU_MKE04Z1284)) || (defined(MCU_MKE04Z4)) || (defined(MCU_MKE06Z4)) || (defined(MCU_SKEAZ1284)) || (defined(MCU_SKEAZN642)) || (defined(MCU_SKEAZN84)))
/**
 * @brief Writes value to the watchdog refresh register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Unlock constant. Use constants from group "Unlock constants".
 *        This parameter is 16 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: WDOG_UNLOCK, WDOG_CNT
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      WDOG_PDD_WriteUnlockReg(<peripheral>_BASE_PTR, WDOG_PDD_UNLOCK_1);
 *      @endcode
 */
  #define WDOG_PDD_WriteUnlockReg(PeripheralBase, Value) ( \
      WDOG_CNT_REG(PeripheralBase) = \
       (uint16_t)(Value) \
    )
#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/**
 * @brief Writes value to the watchdog unlock register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Unlock constant. Use constants from group "Unlock constants".
 *        This parameter is 16 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: WDOG_UNLOCK, WDOG_CNT
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      WDOG_PDD_WriteUnlockReg(<peripheral>_BASE_PTR, WDOG_PDD_UNLOCK_1);
 *      @endcode
 */
  #define WDOG_PDD_WriteUnlockReg(PeripheralBase, Value) ( \
      WDOG_UNLOCK_REG(PeripheralBase) = \
       (uint16_t)(Value) \
    )
#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */

/* ----------------------------------------------------------------------------
   -- ReadUnlockReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the watchdog unlock register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 16-bit value.
 * @remarks The macro accesses the following registers: WDOG_UNLOCK.
 * @par Example:
 *      @code
 *      uint16_t result = WDOG_PDD_ReadUnlockReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define WDOG_PDD_ReadUnlockReg(PeripheralBase) ( \
    WDOG_UNLOCK_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteTimerOutputHighReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes value to the watchdog timer output register high.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value New content of the watchdog timer output register high. This
 *        parameter is a 16-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: WDOG_TMROUTH.
 * @par Example:
 *      @code
 *      WDOG_PDD_WriteTimerOutputHighReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define WDOG_PDD_WriteTimerOutputHighReg(PeripheralBase, Value) ( \
    WDOG_TMROUTH_REG(PeripheralBase) = \
     (uint16_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadTimerOutputHighReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the watchdog timer output register high.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 16-bit value.
 * @remarks The macro accesses the following registers: WDOG_TMROUTH.
 * @par Example:
 *      @code
 *      uint16_t result =
 *      WDOG_PDD_ReadTimerOutputHighReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define WDOG_PDD_ReadTimerOutputHighReg(PeripheralBase) ( \
    WDOG_TMROUTH_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteTimerOutputLowReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes value to the watchdog timer output register low.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value New content of the watchdog timer output register low. This
 *        parameter is a 16-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: WDOG_TMROUTL.
 * @par Example:
 *      @code
 *      WDOG_PDD_WriteTimerOutputLowReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define WDOG_PDD_WriteTimerOutputLowReg(PeripheralBase, Value) ( \
    WDOG_TMROUTL_REG(PeripheralBase) = \
     (uint16_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadTimerOutputLowReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the watchdog timer output register low.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 16-bit value.
 * @remarks The macro accesses the following registers: WDOG_TMROUTL.
 * @par Example:
 *      @code
 *      uint16_t result = WDOG_PDD_ReadTimerOutputLowReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define WDOG_PDD_ReadTimerOutputLowReg(PeripheralBase) ( \
    WDOG_TMROUTL_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteResetCountReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes value to the watchdog reset count register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value New content of the watchdog reset count register. This parameter
 *        is a 16-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: WDOG_RSTCNT.
 * @par Example:
 *      @code
 *      WDOG_PDD_WriteResetCountReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define WDOG_PDD_WriteResetCountReg(PeripheralBase, Value) ( \
    WDOG_RSTCNT_REG(PeripheralBase) = \
     (uint16_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadResetCountReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the watchdog reset count register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 16-bit value.
 * @remarks The macro accesses the following registers: WDOG_RSTCNT.
 * @par Example:
 *      @code
 *      uint16_t result = WDOG_PDD_ReadResetCountReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define WDOG_PDD_ReadResetCountReg(PeripheralBase) ( \
    WDOG_RSTCNT_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- SetPrescaler
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MKE02Z2)) || (defined(MCU_MKE02Z4)) || (defined(MCU_MKE04Z1284)) || (defined(MCU_MKE04Z4)) || (defined(MCU_MKE06Z4)) || (defined(MCU_SKEAZ1284)) || (defined(MCU_SKEAZN642)) || (defined(MCU_SKEAZN84)))
/**
 * @brief Sets prescale value of the watchdog counter reference clock.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Prescaler New value of the prescaler. Use constants from group
 *        "Reference clock prescaler constants". This parameter is 1 bit wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: WDOG_PRESC, WDOG_CS2
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      WDOG_PDD_SetPrescaler(<peripheral>_BASE_PTR, WDOG_PDD_DIVIDE_1);
 *      @endcode
 */
  #define WDOG_PDD_SetPrescaler(PeripheralBase, Prescaler) ( \
      WDOG_CS2_REG(PeripheralBase) = \
       (uint8_t)((uint8_t)((uint8_t)(Prescaler) << WDOG_CS2_PRES_SHIFT) | 0x1U) \
    )
#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/**
 * @brief Sets prescale value.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Prescaler New value of the prescaler. Use constants from group
 *        "Reference clock prescaler constants". This parameter is 3 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: WDOG_PRESC, WDOG_CS2
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      WDOG_PDD_SetPrescaler(<peripheral>_BASE_PTR, WDOG_PDD_DIVIDE_1);
 *      @endcode
 */
  #define WDOG_PDD_SetPrescaler(PeripheralBase, Prescaler) ( \
      WDOG_PRESC_REG(PeripheralBase) = \
       (uint16_t)((uint16_t)(Prescaler) << WDOG_PRESC_PRESCVAL_SHIFT) \
    )
#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */

/* ----------------------------------------------------------------------------
   -- WritePrescalerReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes value to the watchdog prescaler register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value New content of the watchdog prescaler register. This parameter
 *        is a 16-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: WDOG_PRESC.
 * @par Example:
 *      @code
 *      WDOG_PDD_WritePrescalerReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define WDOG_PDD_WritePrescalerReg(PeripheralBase, Value) ( \
    WDOG_PRESC_REG(PeripheralBase) = \
     (uint16_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadPrescalerReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the watchdog prescaler register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 16-bit value.
 * @remarks The macro accesses the following registers: WDOG_PRESC.
 * @par Example:
 *      @code
 *      uint16_t result = WDOG_PDD_ReadPrescalerReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define WDOG_PDD_ReadPrescalerReg(PeripheralBase) ( \
    WDOG_PRESC_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteTimeOutReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes value to the watchdog time-out value register. Because the WDOG
 * peripheral is big endian, the conversion to the little endian is done in this
 * macro.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value New content of the watchdog time-out value register. This
 *        parameter is a 16-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: WDOG_TOVAL.
 * @par Example:
 *      @code
 *      WDOG_PDD_WriteTimeOutReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define WDOG_PDD_WriteTimeOutReg(PeripheralBase, Value) ( \
    WDOG_TOVAL_REG(PeripheralBase) = \
     (uint16_t)(( \
      (uint16_t)((uint16_t)((uint16_t)(Value) & 0xFFU) << 8U)) | ( \
      (uint16_t)((uint16_t)(Value) >> 8U))) \
  )

/* ----------------------------------------------------------------------------
   -- WriteWindowReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes value to the watchdog window register. Because the WDOG
 * peripheral is big endian, the conversion to the little endian is done in this macro.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value New content of the watchdog window register. This parameter is a
 *        16-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: WDOG_WIN.
 * @par Example:
 *      @code
 *      WDOG_PDD_WriteWindowReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define WDOG_PDD_WriteWindowReg(PeripheralBase, Value) ( \
    WDOG_WIN_REG(PeripheralBase) = \
     (uint16_t)(( \
      (uint16_t)((uint16_t)((uint16_t)(Value) & 0xFFU) << 8U)) | ( \
      (uint16_t)((uint16_t)(Value) >> 8U))) \
  )
#endif  /* #if defined(WDOG_PDD_H_) */

/* WDOG_PDD.h, eof. */
