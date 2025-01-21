/*
 * Copyright (c) 2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#if PL_CONFIG_USE_UNIT_TESTS
#include "tests.h"
#include "unity.h"
#include "McuUnity.h"
#include "McuRTOS.h"
#include "McuShell.h"
#include "McuRTT.h"
#include "McuUtility.h"
#include "McuLog.h"
#include "test_leds.h"

static void TestArgFailed(void) {
  TEST_ASSERT_MESSAGE(false, "wrong test_arg value");
}

static void TestTask(void *pv) {
  int nofFailures;
  int nofBytes;
  unsigned char buf[32];

  McuLog_info("starting test task");
  UNITY_BEGIN();
  nofBytes = McuUnity_RTT_GetArgs(buf, sizeof(buf));
  if (nofBytes>0) {
     if (McuUtility_strcmp(buf, "Led_1")==0) {
      RUN_TEST(TestLeds_OnOff);
     } else if (McuUtility_strcmp(buf, "Led_2")==0) {
      RUN_TEST(TestLeds_Toggle);
     } else {
      RUN_TEST(TestArgFailed);
     }
  } else {
    RUN_TEST(TestArgFailed);
  }
  nofFailures = UNITY_END();
#if PL_CONFIG_USE_RTT
  McuUnity_Exit_JRun_RTT(nofFailures==0);
#else
  McuUnity_Exit_LinkServer_Log(nofFailures==0);
#endif
  vTaskDelete(NULL); /* terminate task */
}

void Tests_Init(void) {
  if (xTaskCreate(
      TestTask,  /* pointer to the task */
      "Test", /* task name for kernel awareness debugging */
      1500/sizeof(StackType_t), /* task stack size */
      (void*)NULL, /* optional task startup argument */
      tskIDLE_PRIORITY,  /* initial priority */
      (TaskHandle_t*)NULL /* optional task handle to create */
    ) != pdPASS)
  {
    McuLog_fatal("Failed creating task");
    for(;;){} /* error! probably out of memory */
  }
}
#endif /* PL_CONFIG_USE_UNIT_TESTS */