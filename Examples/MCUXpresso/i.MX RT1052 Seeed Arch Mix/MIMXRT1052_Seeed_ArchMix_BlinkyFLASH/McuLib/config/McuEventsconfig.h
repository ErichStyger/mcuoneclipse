#ifndef __McuEvents_CONFIG_H
#define __McuEvents_CONFIG_H

#ifndef McuEvents_CONFIG_USE_EVENT_HANDLER
  #define McuEvents_CONFIG_USE_EVENT_HANDLER  (1)
    /*!< 1: Use Event handler; 0: Do not use Event Handler */
#endif

#ifndef McuEvents_CONFIG_EVENT_HANDLER_NAME
  #define McuEvents_CONFIG_EVENT_HANDLER_NAME  McuEvents_AppHandleEvent
    /*!< Name of event handler, of type 'void FunctionName(uint8_t event)' */
#endif

/*! List of events */
#define McuEvents_INIT /* Example event */ 0

#define McuEvents_CONFIG_NOF_EVENTS    1 /*!< Number of events supported */

#endif /* __McuEvents_CONFIG_H */
