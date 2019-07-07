#ifndef __McuTimeDate_CONFIG_H
#define __McuTimeDate_CONFIG_H

/* if command line parser is enabled */
#define McuTimeDate_PARSE_COMMAND_ENABLED  1  /* set to 1 if method ParseCommand() is present, 0 otherwise */

/* if Init() is called durint startup */
#define McuTimeDate_INIT_IN_STARTUP                         1 /* 1: call Init() during startup, 0: application needs to call Init() */

/* RTC Initialization options during Init() */
#define McuTimeDate_INIT_SOFTWARE_RTC_FROM_DEFAULTS         0  /* init software RTC from default values */
#define McuTimeDate_INIT_SOFTWARE_RTC_FROM_INTERNAL_RTC     1  /* init software RTC from internal RTC values */
#define McuTimeDate_INIT_SOFTWARE_RTC_FROM_EXTERNAL_RTC     2  /* init software RTC from external RTC values */

/* settings for software RTC */
#define McuTimeDate_USE_SOFTWARE_RTC                        1  /* set to 1 if using software RTC, 0 otherwise */
#define McuTimeDate_INIT_SOFTWARE_RTC_METHOD                McuTimeDate_INIT_SOFTWARE_RTC_FROM_DEFAULTS /* which method to use during Init() */

/* settings for internal hardware RTC */
#define McuTimeDate_USE_INTERNAL_HW_RTC                     0  /* set to 1 if using internal HW RTC, 0 otherwise */
#define McuTimeDate_USE_INTERNAL_HW_RTC_BEAN                0  /* set to 1 if using HW RTC using normal bean driver, 0 otherwise */
#define McuTimeDate_USE_INTERNAL_HW_RTC_LDD                 0  /* set to 1 if using HW RTC using LDD driver, 0 otherwise */

#define McuTimeDate_USE_EXTERNAL_HW_RTC                     0  /* set to 1 if using external HW RTC driver, 0 otherwise */

#if McuTimeDate_USE_INTERNAL_HW_RTC_BEAN
  #define McuTimeDate_HAS_SEC100_IN_TIMEREC                 0 /* Bean version have no Sec100!  */
#else
  #define McuTimeDate_HAS_SEC100_IN_TIMEREC                 1 /* non-Bean version have Sec100  */
#endif

/* SetTime() and SetDate() configuration */
#define McuTimeDate_SET_TIME_DATE_METHOD_USES_SOFTWARE_RTC  1 /* 1: Enable setting software RTC time/date */
#define McuTimeDate_SET_TIME_DATE_METHOD_USES_INTERNAL_RTC  0 /* 1: Enable setting internal RTC time/date */
#define McuTimeDate_SET_TIME_DATE_METHOD_USES_EXTERNAL_RTC  0 /* 1: Enable setting external RTC time/date */

/* GetTime() and GetDate() configuration */
#define McuTimeDate_GET_TIME_DATE_METHOD_SOFTWARE_RTC       1 /* use software RTC */
#define McuTimeDate_GET_TIME_DATE_METHOD_INTERNAL_RTC       2 /* use internal RTC */
#define McuTimeDate_GET_TIME_DATE_METHOD_EXTERNAL_RTC       3 /* use external RTC */
#define McuTimeDate_USE_GET_TIME_DATE_METHOD                McuTimeDate_GET_TIME_DATE_METHOD_SOFTWARE_RTC /* specifies method to get time and date */

/* default time and date format strings */
#define McuTimeDate_DEFAULT_TIME_FORMAT_STR  "hh:mm:ss,cc"
#define McuTimeDate_DEFAULT_DATE_FORMAT_STR  "dd.mm.yyyy"


#endif /* __McuTimeDate_CONFIG_H */
