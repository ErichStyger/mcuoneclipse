/**
 * \file
 * \brief Configuration header file for SeggerSystemView
 * Copyright (c) 2020, Erich Styger
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * This header file is used to configure settings of the Segger SystemView module.
 */
#ifndef __McuSystemView_CONFIG_H
#define __McuSystemView_CONFIG_H

#ifndef McuSystemView_CONFIG_GENERATE_QUEUE_EVENTS
  #define McuSystemView_CONFIG_GENERATE_QUEUE_EVENTS  (1)
    /*!< 1: events for queues are generated. 0: no queue events are generated */
#endif

#ifndef McuSystemView_CONFIG_GENERATE_ISR_EVENTS
  #define McuSystemView_CONFIG_GENERATE_ISR_EVENTS  (1)
    /*!< 1: events for ISR are generated. 0: no ISR events are generated */
#endif

#ifndef McuSystemView_CONFIG_GENERATE_STREAMBUFFER_EVENTS
  #define McuSystemView_CONFIG_GENERATE_STREAMBUFFER_EVENTS  (1)
    /*!< 1: events for Stream Buffer are generated. 0: no Stream Buffer events are generated */
#endif

#ifndef McuSystemView_CONFIG_GENERATE_STEPTICK_EVENTS
  #define McuSystemView_CONFIG_GENERATE_STEPTICK_EVENTS  (1)
    /*!< 1: events for tickets steps are generated. 0: no ticket step events are generated */
#endif

#ifndef McuSystemView_CONFIG_USE_STATIC_BUFFER
  #define McuSystemView_CONFIG_USE_STATIC_BUFFER  (1)
    /*!< 1: Use a static buffer to generate events instead of a buffer on the stack. 0: Use a buffer on the stack */
#endif

#ifndef McuSystemView_CONFIG_POST_MORTEM_MODE
  #define McuSystemView_CONFIG_POST_MORTEM_MODE   (0)
    /*!< 1: Enable post mortem analysis. 0: do not use it in post-morem mode */
#endif

#ifndef McuSystemView_CONFIG_RTT_BUFFER_SIZE
  #define McuSystemView_CONFIG_RTT_BUFFER_SIZE    (1024)
    /*!< Buffer size of RTT buffer, default 1024 */
#endif

#ifndef McuSystemView_CONFIG_RTT_CHANNEL
  #define McuSystemView_CONFIG_RTT_CHANNEL        (1)
    /*!< RTT channel to be used (default 1) */
#endif

#ifndef McuSystemView_CONFIG_SYSVIEW_RAM_BASE
  #define McuSystemView_CONFIG_SYSVIEW_RAM_BASE    (0x20000000)
    /*!< lowest RAM address used */
#endif

#ifndef McuSystemView_CONFIG_SYSVIEW_CONFIG_CALLBACK
  //#define McuSystemView_CONFIG_SYSVIEW_CONFIG_CALLBACK    _cbSendSystemDesc
  /*!< Custom SystemView configuration callback, default is _cbSendSystemDesc() */
#endif

// The application name to be displayed in SystemViewer
#ifndef SYSVIEW_APP_NAME
  #define SYSVIEW_APP_NAME        "Application" /* application name, configured in properties */
#endif

#define SYSVIEW_USING_PEX                         (McuLib_CONFIG_PEX_SDK_USED) /* 1: project is a Kinetis SDK Processor Expert project; 0: No Kinetis Processor Expert project */
#define SYSVIEW_USING_FREERTOS                    (McuLib_CONFIG_SDK_USE_FREERTOS) /* 1: using FreeRTOS; 0: Bare metal */

#ifndef SYSVIEW_OS_NAME
  #if SYSVIEW_USING_FREERTOS
    #define SYSVIEW_OS_NAME         "FreeRTOS"
  #else
    #define SYSVIEW_OS_NAME         "Bare-metal"
  #endif
#endif

// The target device name
#ifndef SYSVIEW_DEVICE_NAME
  #define SYSVIEW_DEVICE_NAME     "Cortex" /* device name, configured in properties */
#endif

#endif /* __McuSystemView_CONFIG_H */
