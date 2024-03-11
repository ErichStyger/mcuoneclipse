/**
 * \file
 * \brief Configuration header file for GenericTimeDate
 * Copyright (c) 2020, Erich Styger
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * This header file is used to configure settings of the generic timc/date module.
 */

#ifndef __McuTimeDate_CONFIG_H
#define __McuTimeDate_CONFIG_H

#ifndef McuTimeDate_CONFIG_PARSE_COMMAND_ENABLED
  #define McuTimeDate_CONFIG_PARSE_COMMAND_ENABLED          (1)
    /*!< set to 1 if method ParseCommand() is present, 0 otherwise */
#endif

#ifndef McuTimeDate_CONFIG_INIT_IN_PE_LOWLEVEL_INIT
  #define McuTimeDate_CONFIG_INIT_IN_PE_LOWLEVEL_INIT       (1)
    /*!< 1: call Init() during Processor Expert LowLevelInit(), 0: application needs to call Init() */
#endif

/* ******************** settings for software RTC ********************************** */
#ifndef McuTimeDate_CONFIG_USE_SOFTWARE_RTC
  #define McuTimeDate_CONFIG_USE_SOFTWARE_RTC               (1)
    /*!< set to 1 if using software RTC, 0 otherwise */
#endif

/* RTC Initialization options during Init() */
#define McuTimeDate_INIT_SOFTWARE_RTC_FROM_DEFAULTS         0  /* init software RTC from default values */
#define McuTimeDate_INIT_SOFTWARE_RTC_FROM_INTERNAL_RTC     1  /* init software RTC from internal RTC values */
#define McuTimeDate_INIT_SOFTWARE_RTC_FROM_EXTERNAL_RTC     2  /* init software RTC from external RTC values */

#ifndef McuTimeDate_CONFIG_INIT_SOFTWARE_RTC_METHOD
  #define McuTimeDate_CONFIG_INIT_SOFTWARE_RTC_METHOD       McuTimeDate_INIT_SOFTWARE_RTC_FROM_DEFAULTS
    /*!< which method to use during Init() */
#endif

/* ****************** settings for internal hardware RTC *************************** */

#ifndef McuTimeDate_CONFIG_USE_INTERNAL_HW_RTC
  #define McuTimeDate_CONFIG_USE_INTERNAL_HW_RTC            (0)
    /*!< set to 1 if using internal HW RTC, 0 otherwise */
#endif

#if McuTimeDate_CONFIG_USE_INTERNAL_HW_RTC
  #ifndef McuTimeDate_CONFIG_RTC_PERIPHERAL
    #define McuTimeDate_CONFIG_RTC_PERIPHERAL                                      ((RTC_Type *)RTC_BASE)
      /*!< Periopheral used by SDK to access RTC */
  #endif
#endif

/* ****************** settings for external hardware RTC *************************** */
#ifndef McuTimeDate_CONFIG_USE_EXTERNAL_HW_RTC
  #define McuTimeDate_CONFIG_USE_EXTERNAL_HW_RTC            (0)
    /*!< set to 1 if using external HW RTC driver, 0 otherwise */
#endif

/* ********************************************************************************* */
/* SetTime() and SetDate() configuration */
#ifndef McuTimeDate_CONFIG_SET_TIME_DATE_METHOD_USES_SOFTWARE_RTC
  #define McuTimeDate_CONFIG_SET_TIME_DATE_METHOD_USES_SOFTWARE_RTC   (1)
    /*!< 1: SetTime() and SetDate() write to software RTC. 0: do not use software RTC in SetTime() and SetDate() */
#endif

#ifndef McuTimeDate_CONFIG_SET_TIME_DATE_METHOD_USES_INTERNAL_RTC
  #define McuTimeDate_CONFIG_SET_TIME_DATE_METHOD_USES_INTERNAL_RTC   (0)
    /*!< 1: SetTime() and SetDate() write to internal RTC. 0: do not use internal RTC in SetTime() and SetDate() */
#endif

#ifndef McuTimeDate_CONFIG_SET_TIME_DATE_METHOD_USES_EXTERNAL_RTC
  #define McuTimeDate_CONFIG_SET_TIME_DATE_METHOD_USES_EXTERNAL_RTC   (1)
    /*!< 1: SetTime() and SetDate() write to external RTC. 0: do not use external RTC in SetTime() and SetDate() */
#endif

/* ********************************************************************************* */
/* GetTime() and GetDate() configuration options: */
#define McuTimeDate_GET_TIME_DATE_METHOD_SOFTWARE_RTC       1 /* use software RTC */
#define McuTimeDate_GET_TIME_DATE_METHOD_INTERNAL_RTC       2 /* use internal RTC */
#define McuTimeDate_GET_TIME_DATE_METHOD_EXTERNAL_RTC       3 /* use external RTC */

#ifndef McuTimeDate_CONFIG_USE_GET_TIME_DATE_METHOD
  #define McuTimeDate_CONFIG_USE_GET_TIME_DATE_METHOD       McuTimeDate_GET_TIME_DATE_METHOD_SOFTWARE_RTC /* specifies method to get time and date */
    /*!< specifies method to get time and date */
#endif

/* default time and date format strings */
#ifndef McuTimeDate_CONFIG_DEFAULT_TIME_FORMAT_STR
  #define McuTimeDate_CONFIG_DEFAULT_TIME_FORMAT_STR  "hh:mm:ss,cc"
#endif
#ifndef McuTimeDate_CONFIG_DEFAULT_DATE_FORMAT_STR
  #define McuTimeDate_CONFIG_DEFAULT_DATE_FORMAT_STR  "dd.mm.yyyy"
#endif

#ifndef McuTimeDate_CONFIG_TICK_TIME_MS
  #define McuTimeDate_CONFIG_TICK_TIME_MS \
    (1000/1000)                         /* Period in milliseconds as defined in RTOS component properties, at which McuTimeDate_AddTick() is called */
#endif

/* date/time defaults: */

/* default time/date values */
#ifndef McuTimeDate_CONFIG_DEFAULT_INITIAL_TIME_HOUR
  #define McuTimeDate_CONFIG_DEFAULT_INITIAL_TIME_HOUR 17
#endif
#ifndef McuTimeDate_CONFIG_DEFAULT_INITIAL_TIME_MIN
  #define McuTimeDate_CONFIG_DEFAULT_INITIAL_TIME_MIN 51
#endif
#ifndef McuTimeDate_CONFIG_DEFAULT_INITIAL_TIME_SEC
  #define McuTimeDate_CONFIG_DEFAULT_INITIAL_TIME_SEC 31
#endif
#ifndef McuTimeDate_CONFIG_DEFAULT_INITIAL_DATE_YEAR
  #define McuTimeDate_CONFIG_DEFAULT_INITIAL_DATE_YEAR 2019
#endif
#ifndef McuTimeDate_CONFIG_DEFAULT_INITIAL_DATE_MONTH
  #define McuTimeDate_CONFIG_DEFAULT_INITIAL_DATE_MONTH 8
#endif
#ifndef McuTimeDate_CONFIG_DEFAULT_INITIAL_DATE_DAY
  #define McuTimeDate_CONFIG_DEFAULT_INITIAL_DATE_DAY 1
#endif

/* interface to external RTC */
#ifndef McuTimeDate_CONFIG_EXT_RTC_HEADER_FILE_NAME
  #define McuTimeDate_CONFIG_EXT_RTC_HEADER_FILE_NAME        "McuExtRTC.h"
#endif

#ifndef McuTimeDate_CONFIG_EXT_RTC_GET_TIME_FCT
  #define McuTimeDate_CONFIG_EXT_RTC_GET_TIME_FCT            McuExtRTC_GetTime
    /*!< function to get the external RTC time */
#endif

#ifndef McuTimeDate_CONFIG_EXT_RTC_SET_TIME_FCT
  #define McuTimeDate_CONFIG_EXT_RTC_SET_TIME_FCT            McuExtRTC_SetTime
    /*!< function to set the external RTC time */
#endif

#ifndef McuTimeDate_CONFIG_EXT_RTC_GET_DATE_FCT
  #define McuTimeDate_CONFIG_EXT_RTC_GET_DATE_FCT            McuExtRTC_GetDate
    /*!< function to get the external RTC date */
#endif

#ifndef McuTimeDate_CONFIG_EXT_RTC_SET_DATE_FCT
  #define McuTimeDate_CONFIG_EXT_RTC_SET_DATE_FCT            McuExtRTC_SetDate
    /*!< function to get the external RTC date */
#endif

#endif /* __McuTimeDate_CONFIG_H */
