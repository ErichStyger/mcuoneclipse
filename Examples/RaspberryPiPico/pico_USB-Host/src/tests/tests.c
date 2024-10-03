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
  TEST_ASSERT_MESSAGE(false, "wrong test_arg value, check JLinkScript file");
}

static void TestTask(void *pv) {
  int nofFailures;
  uint32_t test_arg = -1;
  int nofBytes;
  unsigned char buf[32];

  McuLog_info("starting test task");
#if 1 /* new JRun */  
  nofBytes = McuUnity_RTT_GetArgs(buf, sizeof(buf));
  SEGGER_RTT_printf(0, "args = %s, nofBytes = %d\n", buf);
  if (nofBytes>0) {
     if (McuUtility_strcmp(buf, "Led_1")==0) {
      test_arg = 1;
     } else if (McuUtility_strcmp(buf, "Led_2")==0) {
      test_arg = 2;
     }
  } else {
    test_arg = -1;
  }
#else
  test_arg = McuUnity_GetArgument(); /* get test arguments */
#endif
  UNITY_BEGIN();
  switch(test_arg) {
    case 1:   RUN_TEST(TestLeds_OnOff); break;
    case 2:   RUN_TEST(TestLeds_Toggle); break;
    default:  RUN_TEST(TestArgFailed); break;
  }
  nofFailures = UNITY_END();
  /* report failed or passed */
  if (nofFailures==0) {
    McuShell_SendStr("*** PASSED ***\n", McuRTT_stdio.stdOut);
  } else {
    McuShell_SendStr("*** FAILED ***\n", McuRTT_stdio.stdOut);
  }
  McuShell_SendStr("*STOP*\n", McuRTT_stdio.stdOut); /* stop JRun */
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