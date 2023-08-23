/**
 * \file
 * \brief Application configuration file for Trigger module
 * Copyright (c) 2020, Erich Styger
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * This header file is a configuration header file to configure the module McuTrigger.
 * You can configure the defines directly in this file or with the compiler -D option.
 */

#ifndef __McuTrigger_CONFIG_H
#define __McuTrigger_CONFIG_H

/* no configuration supported yet */
/*! Definition of triggers */
#define McuTrigger_KEY1_PRESS /* key pressed, used by the KEY bean. Format is '<triggerName>_<keyName>_PRESS' */ 0
#define McuTrigger_EXAMPLE  /* example trigger */ 1

#define McuTrigger_CONFIG_TICK_PERIOD_MS \
  (1000/1000)                           /* Period in milliseconds as defined in RTOS component properties, at which McuTrigger._AddTick() is called */

#endif /* __McuTrigger_CONFIG_H */
