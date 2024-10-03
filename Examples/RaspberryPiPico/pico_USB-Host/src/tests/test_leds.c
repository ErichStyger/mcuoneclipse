/*
 * Copyright (c) 2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#if PL_CONFIG_USE_UNIT_TESTS
#include "test_leds.h"
#include "McuRTOS.h"
#include "McuLED.h"
#include "leds.h"
#include "unity/unity.h"

void TestLeds_OnOff(void) {
  Leds_On(LEDS_BLUE);
  TEST_ASSERT_MESSAGE(Leds_Get(LEDS_BLUE), "Blue LED shall be on");
  Leds_Off(LEDS_BLUE);
  TEST_ASSERT_MESSAGE(!Leds_Get(LEDS_BLUE), "Blue LED shall be off");
  
  Leds_On(LEDS_RED);
  TEST_ASSERT_MESSAGE(Leds_Get(LEDS_RED), "Red LED shall be on");
  Leds_Off(LEDS_RED);
  TEST_ASSERT_MESSAGE(!Leds_Get(LEDS_RED), "Red LED shall be off");

  Leds_On(LEDS_GREEN);
  TEST_ASSERT_MESSAGE(Leds_Get(LEDS_GREEN), "Green LED shall be on");
  Leds_Off(LEDS_GREEN);
  TEST_ASSERT_MESSAGE(!Leds_Get(LEDS_GREEN), "Green LED shall be off");
  //TEST_ASSERT_MESSAGE(true, "Test, assert is always true"); /* success */
}

void TestLeds_Toggle(void) {
  Leds_Off(LEDS_BLUE);
  TEST_ASSERT_MESSAGE(!Leds_Get(LEDS_BLUE), "Blue LED shall be off");
  Leds_Neg(LEDS_BLUE);
  TEST_ASSERT_MESSAGE(Leds_Get(LEDS_BLUE), "Blue LED shall be on");
  Leds_Neg(LEDS_BLUE);
  TEST_ASSERT_MESSAGE(!Leds_Get(LEDS_BLUE), "Blue LED shall be off");

  Leds_Off(LEDS_RED);
  TEST_ASSERT_MESSAGE(!Leds_Get(LEDS_RED), "Red LED shall be off");
  Leds_Neg(LEDS_RED);
  TEST_ASSERT_MESSAGE(Leds_Get(LEDS_RED), "Red LED shall be on");
  Leds_Neg(LEDS_RED);
  TEST_ASSERT_MESSAGE(!Leds_Get(LEDS_RED), "Red LED shall be off");

  Leds_Off(LEDS_GREEN);
  TEST_ASSERT_MESSAGE(!Leds_Get(LEDS_GREEN), "Green LED shall be off");
  Leds_Neg(LEDS_GREEN);
  TEST_ASSERT_MESSAGE(Leds_Get(LEDS_GREEN), "Green LED shall be on");
  Leds_Neg(LEDS_GREEN);
  TEST_ASSERT_MESSAGE(!Leds_Get(LEDS_GREEN), "Green LED shall be off");
  //TEST_ASSERT(false); /* failure */
  //TEST_ASSERT_MESSAGE(true, "Test, testing successful assert"); /* success */
}
#endif /* PL_CONFIG_USE_UNIT_TESTS */