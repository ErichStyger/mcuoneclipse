/**
 * \file
 * \brief Configuration header file for Percepio Trace for FreeRTOS
 * Copyright (c) 2020, Erich Styger
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * This header file is used to configure settings of the Percepio trace.
 */

#ifndef __McuPercepio_CONFIG_H
#define __McuPercepio_CONFIG_H

#include "trcPortDefines.h"
#include "trcConfig.h"

#if !defined(TRC_CFG_RECORDER_MODE) || !defined(TRC_RECORDER_MODE_SNAPSHOT)
  #error "these macros are used below, but do not exist?"
#endif

#ifndef McuPercepio_CONFIG_START_TRACE_IN_STARTUP_MODE
  /* Percepio trace startup mode used for calling vTraceEnable() from Startup():
     Snapshot Mode:
       TRC_INIT: Initializes trace module. Application needs to start tracing later with vTraceEnable(TRC_START);
       TRC_START: Initializes and starts tracing
     Streaming Mode:
       TRC_INIT: Initializes trace module. Application needs to start tracing later with vTraceEnable(TRC_START);
       TRC_START: Initializes and starts tracing
       TRC_START_AWAIT_HOST: Initializes trace module and blocks and waits for data to be retrieved */
  #if TRC_CFG_RECORDER_MODE==TRC_RECORDER_MODE_SNAPSHOT
    #define McuPercepio_CONFIG_START_TRACE_IN_STARTUP_MODE  TRC_START
      /*!< Trace startup for snapshot mode: TRC_INIT or TRC_START */
  #else /* streaming mode */
    #define McuPercepio_CONFIG_START_TRACE_IN_STARTUP_MODE  TRC_START
      /*!< Trace startup for streaming mode: TRC_INIT, TRC_START or TRC_START_AWAIT_HOST */
  #endif
#endif

#endif /* __McuPercepio_CONFIG_H */
