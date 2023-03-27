
/* list of watchdog IDs (enumeration), separated by commas */
  McuWatchdog_REPORT_ID_TASK_APP,
#if PL_CONFIG_USE_GUI
  McuWatchdog_REPORT_ID_TASK_GUI,
#endif
#if PL_CONFIG_USE_SHELL
  McuWatchdog_REPORT_ID_TASK_SHELL,
#endif
#if PL_CONFIG_USE_LIGHTS
  McuWatchdog_REPORT_ID_TASK_LIGHTS,
#endif
#if PL_CONFIG_USE_WIFI
  McuWatchdog_REPORT_ID_TASK_WIFI,
#endif
