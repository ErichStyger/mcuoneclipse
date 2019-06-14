#ifndef __McuCriticalSection_CONFIG_H
#define __McuCriticalSection_CONFIG_H

/* select ONE of the following implementation methods: */
#ifndef McuCriticalSection_CONFIG_USE_RTOS_CRITICAL_SECTION
  #define McuCriticalSection_CONFIG_USE_RTOS_CRITICAL_SECTION 0 /* 1: use FreeRTOS critical section; 0: don't use FreeRTOS critical sections */
#endif

#ifndef McuCriticalSection_CONFIG_USE_CUSTOM_CRITICAL_SECTION
  #define McuCriticalSection_CONFIG_USE_CUSTOM_CRITICAL_SECTION 1 /* 1: Custom implementation (supported for GNU and ARM!); 0: don't use custom implementation */
#endif

#ifndef McuCriticalSection_CONFIG_USE_PEX_DEFAULT
  #define McuCriticalSection_CONFIG_USE_PEX_DEFAULT         0 /* 1: use Processor Expert default; 0: use alternative implementation */
#endif

#endif /* __McuCriticalSection_CONFIG_H */

