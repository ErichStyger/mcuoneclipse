#ifndef __CS1_CONFIG_H
#define __CS1_CONFIG_H

/* select ONE of the following implementation methods: */
#ifndef CS1_CONFIG_USE_RTOS_CRITICAL_SECTION
  #define CS1_CONFIG_USE_RTOS_CRITICAL_SECTION              0 /* 1: use FreeRTOS critical section; 0: don't use FreeRTOS critical sections */
#endif

#ifndef CS1_CONFIG_USE_CUSTOM_CRITICAL_SECTION
  #define CS1_CONFIG_USE_CUSTOM_CRITICAL_SECTION            1 /* 1: Custom implementation (supported for GNU and ARM!); 0: don't use custom implementation */
#endif

#ifndef CS1_CONFIG_USE_PEX_DEFAULT
  #define CS1_CONFIG_USE_PEX_DEFAULT                        0 /* 1: use Processor Expert default; 0: use alternative implementation */
#endif

#endif /* __CS1_CONFIG_H */

