/*
 * Copyright (c) 2020, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include "platform.h"
#include "leds.h"
#include "McuLED.h"
#include "pin_mux.h"
#include "fsl_iomuxc.h"

McuLED_Handle_t LEDS_Led;

void LEDS_Deinit(void) {
  LEDS_Led = McuLED_DeinitLed(LEDS_Led);
}

void LEDS_Init(void) {
  McuLED_Config_t config;

  McuLED_GetDefaultConfig(&config);
  config.isLowActive = true;
  config.hw.gpio = GPIO1;
  config.hw.pin = 11;
#if 1
  #define _IOMUXC_GPR_GPR26_GPIO_SEL_MASK 0x0800U /*!< Select GPIO1 or GPIO2: affected bits mask */

  IOMUXC_SetPinMux(IOMUXC_GPIO_11_GPIOMUX_IO11, 0U);
  IOMUXC_SetPinMux(IOMUXC_GPIO_AD_09_ARM_TRACE_SWO, 0U);
  IOMUXC_GPR->GPR26 = ((IOMUXC_GPR->GPR26 &
    (~(_IOMUXC_GPR_GPR26_GPIO_SEL_MASK)))
      | IOMUXC_GPR_GPR26_GPIO_SEL(0x00U)
    );
  IOMUXC_SetPinConfig(IOMUXC_GPIO_11_GPIOMUX_IO11, 0x10A0U);
#else
  McuGPIO_SetMux(&config.hw, IOMUXC_GPIO_AD_B0_09_GPIO1_IO09); /* set special i.MX RT muxing fields */
#endif
  LEDS_Led = McuLED_InitLed(&config);
}

