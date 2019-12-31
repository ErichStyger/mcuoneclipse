/**
 * \file
 * \brief Configuration header file for SeggerSystemView
 *
 * This header file is used to configure settings of the Segger SystemView module.
 */
#ifndef __SYS1_CONFIG_H
#define __SYS1_CONFIG_H

#ifndef SYS1_CONFIG_GENERATE_QUEUE_EVENTS
  #define SYS1_CONFIG_GENERATE_QUEUE_EVENTS  (1)
    /*!< 1: events for queues are generated. 0: no queue events are generated */
#endif

#ifndef SYS1_CONFIG_GENERATE_ISR_EVENTS
  #define SYS1_CONFIG_GENERATE_ISR_EVENTS  (1)
    /*!< 1: events for ISR are generated. 0: no ISR events are generated */
#endif

#ifndef SYS1_CONFIG_GENERATE_STREAMBUFFER_EVENTS
  #define SYS1_CONFIG_GENERATE_STREAMBUFFER_EVENTS  (1)
    /*!< 1: events for Stream Buffer are generated. 0: no Stream Buffer events are generated */
#endif

#ifndef SYS1_CONFIG_GENERATE_STEPTICK_EVENTS
  #define SYS1_CONFIG_GENERATE_STEPTICK_EVENTS  (1)
    /*!< 1: events for tickets steps are generated. 0: no ticket step events are generated */
#endif

#endif /* __SYS1_CONFIG_H */
